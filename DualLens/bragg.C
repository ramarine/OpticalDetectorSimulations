// bragg_fit.C
// Usage (ROOT): .L bragg_fit.C+
//                auto res = FitBraggAndEnergy(hBragg, /*xfit_min*/0.0, /*xfit_max*/hBragg->GetXaxis()->GetXmax(),
//                                             /*usePSTAR*/false, /*pstarCSV*/"");
//                printf("R_fit = %.4f cm, E0 = %.3f MeV\n", res.R_cm, res.E0_MeV);

#include <TF1.h>
#include <TH1.h>
#include <TMath.h>
#include <TGraph.h>
#include <TFile.h>
#include <TString.h>
#include <TROOT.h>
#include <TSystem.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>


void bragg(){
  auto res = FitBraggAndEnergy(hBragg, /*xfit_min*/0.0, /*xfit_max*/hBragg->GetXaxis()->GetXmax(),/*usePSTAR*/false, /*pstarCSV*/"");
  printf("R_fit = %.4f cm, E0 = %.3f MeV\n", res.R_cm, res.E0_MeV);


}

struct FitResult {
  double R_cm;
  double E0_MeV;
  TF1*   f;  // fitted function (owned by ROOT)
};

static double braggFunc(double* xx, double* pp) {
  const double x = xx[0];             // depth [cm]
  const double A = pp[0];             // amplitude
  const double R = pp[1];             // range [cm]
  const double pexp = pp[2];          // power-law exponent (~1.7-1.8)
  const double lambda = pp[3];        // nuclear attenuation length [cm]
  const double sigma = pp[4];          // range straggling [cm]
  const double B = pp[5];             // constant background

  const double t = R - x;             // residual range
  const double eps = 1e-4;
  const double tpos = (t > eps ? t : eps);

  // Smooth cutoff beyond R to emulate distal fall-off
  const double H = 0.5 * (1.0 + TMath::Erf(t / (TMath::Sqrt2() * TMath::Max(sigma, 1e-4))));

  const double core = A * TMath::Power(tpos, -pexp) * TMath::Exp(-tpos / TMath::Max(lambda, 1e-3));
  return H * core + B;
}

// Optional: invert PSTAR table to get E(R) via interpolation.
// Expects CSV with columns: Energy_MeV, Range_g_per_cm2 (header allowed).
static TGraph* LoadPSTAR_E_of_R(const std::string& csv, double material_density_g_cm3) {
  std::ifstream fin(csv.c_str());
  if (!fin) return nullptr;
  std::vector<double> R, E; // R in cm (convert from g/cm^2 by dividing density)
  std::string line;
  bool headerSkipped = false;

  while (std::getline(fin, line)) {
    if (line.empty()) continue;
    std::stringstream ss(line);
    std::string c0, c1;
    if (!headerSkipped) { // try to skip header if not numeric
      std::stringstream t(line);
      double test;
      if (!(t >> test)) { headerSkipped = true; continue; }
    }
    ss.clear(); ss.str(line);
    double eMeV = 0, r_gcm2 = 0;
    char sep;
    if (!(ss >> eMeV)) continue;
    if (ss.peek() == ',' || ss.peek() == ';' || ss.peek() == '\t') ss >> sep;
    if (!(ss >> r_gcm2)) continue;
    double r_cm = r_gcm2 / material_density_g_cm3;
    R.push_back(r_cm);
    E.push_back(eMeV);
  }
  if (R.empty()) return nullptr;
  // Create monotonic graph E(R)
  auto gr = new TGraph((int)R.size(), R.data(), E.data());
  return gr;
}

FitResult FitBraggAndEnergy(TH1* h, double xfit_min, double xfit_max,
                            bool usePSTAR=false, const std::string& pstarCSV="",
                            double material_density_g_cm3=1.0) {
  FitResult out{NAN, NAN, nullptr};

  // Initial guesses from histogram
  const int ibmax = h->GetMaximumBin();
  const double xmax = h->GetXaxis()->GetBinCenter(ibmax);
  const double ymax = h->GetBinContent(ibmax);
  const double bw = h->GetXaxis()->GetBinWidth(ibmax);

  TF1* f = new TF1("fBragg", braggFunc, xfit_min, xfit_max, 6);
  f->SetParNames("A","R","p","lambda","sigma","B");
  f->SetParameters(ymax, xmax + 0.5*bw, 1.75, 50.0, 0.02 * TMath::Max(xmax, 1.0), 0.0);
  f->SetParLimits(2, 1.6, 1.9);   // p in [1.6,1.9]
  f->SetParLimits(3, 5.0, 500.0); // lambda
  f->SetParLimits(4, 0.1*bw, 0.2 * TMath::Max(xmax, 1.0)); // sigma
  f->SetParLimits(1, xfit_min + 0.2*(xfit_max-xfit_min), xfit_max); // R near distal end

  // Weighted fit over specified range
  h->Fit(f, "RQN"); // quiet; use "RQ" to see output
  h->Fit(f, "R");   // second pass

  const double R_fit = f->GetParameter(1);
  out.R_cm = R_fit;
  out.f = f;

  // Option A: Bragg–Kleeman mapping (default water numbers from literature)
  double E0 = NAN;
  if (!usePSTAR) {
    const double alpha = 0.00246; // water [cm / MeV^p]
    const double pexp  = f->GetParameter(2);
    E0 = TMath::Power(R_fit / alpha, 1.0 / pexp);
  } else {
    // Option B: PSTAR inversion for your material (csv from https://physics.nist.gov/PhysRefData/Star/Text/PSTAR.html)
    TGraph* gEofR = LoadPSTAR_E_of_R(pstarCSV, material_density_g_cm3);
    if (gEofR) {
      E0 = gEofR->Eval(R_fit); // linear interpolation E(R)
    }
  }
  out.E0_MeV = E0;
  return out;
}
