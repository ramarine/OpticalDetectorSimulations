#include <iostream>
#include "OpticSystemTransport.h" 
#include "TRandom.h"
#include "TF1.h"  
#include "TH1D.h" 
#include "TH2D.h" 
#include "TH3D.h" 
#include "TProfile.h"
#include "TCanvas.h"

double Omega(double pos, double rad){

  return TMath::Pi()* rad*rad/ (pos*pos);
}




void SolidAngle(){
  //------------
  //Efficiencies
  //------------

  //  Double_t mesh_t = 0.8;
  //Double_t PEN_QE = 0.25;
  Double_t PEN_acc = 0.5;

  Double_t mesh_t = .8;
  Double_t PEN_QE = .25;
  Double_t Acr_tr = 0.9;
  
  //-----------------
  //Object | Lens properties
  //-----------------
  double lensposition = 220-8;// mm from PEN
  double lens_ApRad = 25.;
  double wposition = 93.;
  double w_ApRad = 50.;
  
  double Om = Omega(lensposition,lens_ApRad);
  double RelOmega = Omega(lensposition,lens_ApRad)/(TMath::Pi() *4);

  double Om_w = Omega (wposition, w_ApRad);
  double RelOmega_w = Om_w/(TMath::Pi() *4);
  //-----------------
  //Photons in detector
  //-----------------

  double NDecay = 1;
  double PhotoNo = 5000;
  double PhtAtThGEM =  NDecay * PhotoNo * 5900./26.4;
  
  //double PhtAtPEN =  PhtAtThGEM * PEN_acc * PEN_QE * mesh_t *Acr_tr;
  double PhtAtPEN =  PhtAtThGEM *PEN_acc;

  double ExpPhot_w = PhtAtPEN * RelOmega_w; // at window
  double ExpPhot_lens = PhtAtPEN * RelOmega; // at window
  Printf(" Photons produce at ThGEM %f ", PhtAtThGEM); 
  Printf( " Photons emitted from PEN %f , fraction %f  ", PhtAtPEN, PhtAtPEN/PhtAtThGEM);
  Printf (" Relative S.A. of window (%f,%f)= %f ", wposition, w_ApRad, RelOmega_w);
  Printf( " Photons expected  at window %f - ratio to ntot %f", ExpPhot_w , ExpPhot_w/PhtAtThGEM);
  Printf( " Solid Angle of Lens(%f,%f)= %f ",lensposition, lens_ApRad,Om);
  Printf( " Relative S.A. of Lens(%f,%f)= %f ",lensposition, lens_ApRad,RelOmega);
  Printf( " Photons expected  at LENS %f - ratio to ntot %f", ExpPhot_lens, ExpPhot_lens/PhtAtThGEM);

  
  TRandom r;
  Double_t distr_fact = 0.5;
  Double_t MPPC_QE = 0.4;//
    
  double ct(0);
  double tot = 1e7;
  for (int i(0); i < int(tot);i++){
    Double_t con1 = r.Uniform();
    Double_t con2 = r.Uniform();
    Double_t con3 = r.Uniform();
    Double_t con4 = r.Uniform();
    Bool_t eff_con = con1 < MPPC_QE && con2 < Acr_tr &&  con4 < distr_fact ;
    if (eff_con) ct++;

  }

  cout << "   ct " << ct << " tot " << tot <<" rratio " << ct/tot << endl;
}
