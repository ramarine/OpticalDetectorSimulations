// README//

//difference between this and the v1 is that in v1 the PEN was modeled as a circle. Here we model it as a square


// The lens position here (from this version and above) is the distance between the PEN and the first lenst.
// Whenever we define a startpos of 130 (PEN -> Lens) an extra WLS_Zpos is going to be added such as to account for
// the distance between the ThGEM and the WLS.

//  in the input one has to put the distance between the PEN and lens1 and the distance between PEN and Sensor.
// This

#include "OpticSystemTransport.h"
#include "TRandom.h"
#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TProfile.h"
#include "TCanvas.h"

//double Simulation(double size = 1., double lensposition = 149.10 +6.5/2. , double sensorpos =183.42  , bool debug = false){ //:: 30mm lens
double Simulation(double size = 200., double lensposition = 0. , double sensorpos = 0.  , bool debug = false){// works with 50 mm lens.
  //double Simulation(double size = 1., double lensposition = 220., double sensorpos = 252.5,bool debug = false){
  //double Simulation(double size = 1., double lenwsposition = 220., double sensorpos = 220.+64.70,bool debug = false){ // works with 50mm diam lens



  debug = false;
  TFile * graphs  =  new TFile("graphs.root", "UPDATE");
  //FILE *input = fopen(  "lenspositns.txt" , "r");
  // FILE *input = fopen(  "lenspositns_short.txt" , "r");
  //FILE *input = fopen(  "/Users/robertamarinei/Desktop/Year1_PhD/TPC/TPC_sim/RobertSim/FullPhotonCount/FindFocus_DualLens/DualLensPos_44_44-26.txt" , "r");

  //FILE *input = fopen(  "/Users/robertamarinei/Desktop/Year1_PhD/TPC/TPC_sim/RobertSim/FullPhotonCount/FindFocus_DualLens/DualLensPos_44_44-16.txt" , "r");

  //FILE *input = fopen("/Users/robertamarinei/Desktop/Year1_PhD/TPC/TPC_sim/RobertSim/FullPhotonCount/FindFocus_DualLens/DualLensPos_27_27-6.txt" , "r");

  // FILE *input = fopen("/Users/robertamarinei/Desktop/Year1_PhD/TPC/TPC_sim/RobertSim/FullPhotonCount/FindFocus_DualLens/DualLensPos_27_27-13.txt" , "r");

  //FILE *input = fopen("/Users/robertamarinei/Desktop/Year1_PhD/TPC/TPC_sim/RobertSim/FullPhotonCount/FindFocus_DualLens/DualLensPos_44_27-11.txt" , "r");

  //FILE *input = fopen("/Users/robertamarinei/Desktop/Year1_PhD/TPC/TPC_sim/RobertSim/FullPhotonCount/FindFocus_DualLens/DualLensPos_44_27-20.txt" , "r");

  //FILE *input = fopen("/Users/robertamarinei/Desktop/Year1_PhD/TPC/TPC_sim/RobertSim/FullPhotonCount/FindFocus_DualLens/DualLensPos_44_27-30.txt" , "r");

  //FILE *input = fopen("/Users/robertamarinei/Desktop/Year1_PhD/TPC/TPC_sim/RobertSim/FullPhotonCount/FindFocus_DualLens/DualLensPos_44_27-40.txt" , "r");

  //FILE *input = fopen("/Users/robertamarinei/Desktop/Year1_PhD/TPC/TPC_sim/RobertSim/FullPhotonCount/FindFocus_DualLens/DualLensPos_27_18-5.txt" , "r");

  //FILE *input = fopen("/Users/robertamarinei/Desktop/Year1_PhD/TPC/TPC_sim/RobertSim/FullPhotonCount/FindFocus_DualLens/DualLensPos_27_18-13.txt" , "r");


  // FILE *input = fopen(  "DualLensPos_27_27-13.txt" , "r");
  FILE *input = fopen(  "test.txt" , "r");
  std::vector<double>lenspositions_v;
  std::vector<double>sensorpositions_v;
  double col_1;
  double col_2;

  while(fscanf(input, "%lf %lf", &col_1 , &col_2) ==2 ){
    lenspositions_v.push_back(col_1);
    sensorpositions_v.push_back(col_2);
  }



  lensposition = 0;
  Double_t lensposition_2(0);
  std::vector<Aperture*> a1_store;
  std::vector<Lens*> lens_store;
  std::vector<Lens*> lens_store_2;


  // Edmund optics 63-556 ::::::50mm + 30 mm
  /*
  Double_t  lens_th_30 = 6.5;
  Double_t  lens_th_50 = 16.;
  Double_t lens_ApRad_50 = 50./2.; //Lens Aperture Radius
  Double_t lens_ApRad_30 = 30./2.; //Lens Aperture Radius
  Double_t lens_ApRad(0), lens_th(0);
  double d_1_2 = 40; //distance between the two lenses




  for (int i(0); i<lenspositions_v.size(); i++){

  lens_store.push_back(new Lens(lenspositions_v.at(i), lens_th_50, 74.78, lens_ApRad_50,1.833,3));
  lens_store_2.push_back(new Lens(lenspositions_v.at(i) + d_1_2, lens_th_30, 45.61, lens_ApRad_30,1.833,3));

  a1_store.push_back(new Aperture(lenspositions_v.at(i)+4, 1.,  15., 2));
}

*/

//Edmund optics ::::::: 50 + 50mm
/*
Double_t lens_ApRad = 50./2;
Double_t lens_th = 16.;
double d_1_2 = 26;


for (int i(0); i<lenspositions_v.size(); i++){
lens_store.push_back(new Lens(lenspositions_v.at(i), lens_th, 74.78, lens_ApRad,1.833,3));
lens_store_2.push_back(new Lens(lenspositions_v.at(i) + d_1_2, lens_th, 74.78, lens_ApRad,1.833,3));
// a1_store.push_back(new Aperture(lenspositions_v.at(i)+8.5, 1.,  100., 2));
}

*/

// Edmund optics 63-556 :::::: 30 +30 mm
/*
Double_t  lens_th = 6.5;
Double_t lens_ApRad = 30./2.; //Lens Aperture Radius
Double_t d_1_2 = 13;



for (int i(0); i<lenspositions_v.size(); i++){
lens_store.push_back(new Lens(lenspositions_v.at(i), lens_th, 45.61, lens_ApRad, 1.833,3));
lens_store_2.push_back(new Lens(lenspositions_v.at(i) + d_1_2, lens_th, 45.61, lens_ApRad,1.833,3));

a1_store.push_back(new Aperture(lenspositions_v.at(i)+4, 1.,  15., 2));
}
*/



// Edmund optics 63-556 :::::: 30 +20 mm #63-550
//Load lenses of 30 + 30 mm

// The reference of the distances is the ThGEM. In Reality, the relevant distance is the distance between PEN and First Lens, Second Lens and MPPC.
//For Configuration TwentyTed the card file for our detector is this:


Double_t lens_th_30 = 6.5;
Double_t lens_Surf_R1 = 45.61; // the radius of the left most curved surface.
Double_t lens_th_20 = 5.0;
Double_t lens_th = 0;
Double_t d_1_2 = lens_th_30/2+lens_th_30/2 + 6.5; //  2*30 mm lenses with 13mm between the optical centres
Double_t lens_ApRad = 30./2.; //Lens Aperture Radius
Double_t Flange_Thick = 22;//mm thickness of flange //REAL CONFIG 18 distances:
Double_t WLS_Zpos = 2.6;//2.6 REAL CONFIG 18 distances:

Double_t d_ThGEMtoFlange  = 125;
Double_t PEN_to_Flange = d_ThGEMtoFlange - WLS_Zpos; //REAL CONFIG 18 distances:
Double_t w_pos = d_ThGEMtoFlange + Flange_Thick/2; //REAL CONFIG 18 distances:



// For re-doing the lens sensitivity plots:
// PEN_to_Flange = 40;

//Efficiencies for weighting the entries in the histograms
Double_t distr_fact = 0.5;
Double_t MPPC_QE = 0.4;//
Double_t Acr_tr = 0.9;
double PEN_QE = 0.25;//0.25;
double mesh_t = 0.8;//0.8;

double NDecay = 10.;
// double MIP_e = 244;// COSMIC Ray eV / mm
double MIP_e = 8900;// ALPHA eV / mm
//double MIP_e = 590;// eV / mm
double part_propag = 60;//mm
double InEnergy = MIP_e * part_propag;

double w_Ar = 26.4;// eV
double prim_electr = InEnergy / w_Ar;//
if (part_propag > 100){
  cout << " !!!!! The primary particle propagates more than the surface of the ThGEM. Corrections applied to the number of primary electrons reaching the ThGEM. " << endl;
  prim_electr = prim_electr/2;// this accounts for primary particles propagating more than the surgace of the ThGEM
}
double PhotoNo = 500;
int PhtAtThGEM = (int) NDecay * PhotoNo * prim_electr;
double photAtLens = 0;

//----------------
//DIFFUSION PARAMETERS
//----------------
Double_t dt_Ar = 1200;//um/sqrt(cm)
Double_t dt_CF4 = 100;
//Double_t dt(0.3);
Double_t dt = dt_Ar * TMath::Sqrt(10) * 1e-3;// mm diameter of the diffusion for a 10 cm propagation through the TPC
double tr_size = 1.;

for (int i(0);  i < lenspositions_v.size(); i++){
  lens_store.push_back(new Lens(WLS_Zpos+lenspositions_v.at(i),lens_th_30,lens_Surf_R1,lens_ApRad, 1.833,3));
  lens_store_2.push_back(new Lens(WLS_Zpos+lenspositions_v.at(i)+d_1_2,lens_th_30,lens_Surf_R1,lens_ApRad, 1.833,3));
  a1_store.push_back(new Aperture(WLS_Zpos+lenspositions_v.at(i) -lens_th_30/2 - 3 ,1.,14.,2));
}

//Aperture  a0(101.,1.,100.,2);
//Aperture  a0(98.,1.,100.,2);// ORIGINAL
//Disc  w(93.,8.,50.,1.458,1);// ORIGINAL
Disc  w(w_pos,8.3,50.,1.458,1);//
double pmt_pos = w_pos+5;
Disc pmt(pmt_pos,2.,12.5,1.458,1);// ORIGINAL


// Edmund optics 63-560 :::: 40mm
/*lensposition = 149.10 +6.5/2; sensorpos =206.54;
Aperture  a1(lensposition+4.75, 1. , 20. ,2);
double lens_th = 8.5;
Lens lens(lensposition,lens_th,60.85,40./2.,1.833,3);
Double_t lens_ApRad = 40./2.; //Lens Aperture Radius
Aperture  a0(98.,1.,100.,2);
*/

for (int i(0); i< lens_store.size(); i++){
  lens_store.at(i)->SetDebug(debug);
  lens_store_2.at(i)->SetDebug(debug);
  a1_store.at(i)->SetDebug(debug);
}

// a0.SetDebug(debug);
w.SetDebug(debug);

//misc variables
std::vector<double> PhtPerBin;
std::vector<double> eff_mag;
std::vector<Double_t> xOnPEN;
std::vector<Double_t> yOnPEN;
std::vector<double>lens_acc;
std::vector<double>mag_store;
std::vector<double>aberr_store;

//double WLS_Xpos = 0.; // Pen postion relative to GEM

// You can recompute the matrices for different distances by (i.e. if you want to scan parameters):
//
// opt.setdistances(d_source_silica,d_silica_lens,d_lens_sensor)
// opt.ComputeMatrices();

TRandom r;

Double_t dx_mean(0);
Double_t WLS_size = 200;
TH1D *hCtPerEvt = new TH1D("hCtPerEvt","",20,-0.5,19.5);  // RMS is always positive
TH2D     *h2x = new TH2D("h2x","  ",100,-size-2,size+2,100,-20,20);
TH2D     *h2y = new TH2D("h2y",";Position at PEN (mm);Position at MPPC (mm)",100,-WLS_size/2.,WLS_size/2.,100,-WLS_size/2./5.,WLS_size/2./5.);
TProfile *hpx = new TProfile("hpx","  ",100,-size -2,size +2,-20,20,"S");
TProfile *hpy = new TProfile("hpy","  ",100,-WLS_size/2.,WLS_size/2.,-WLS_size/2./5.,WLS_size/2./5.,"S");

TH2D     *hsensornolens = new TH2D("hsensornolens"," ",16,-8.,8.,16,-8.,8.);
TH2D     *hsensorlens = new TH2D("hsensorlens"," ; X position on MPPC (mm); Y position on MPPC (mm) ",16,-8.,8.,16,-8.,8.);
TH2D     *hlens = new TH2D("hlens"," ; X Position on lens (mm); Y Position on lens (mm) ",100,-lens_ApRad -10,lens_ApRad+10, 100, -lens_ApRad -10 , lens_ApRad +10);


TH2D     *hwindow = new TH2D("hwindow","  ",100,-50.,50.,100,-50.,50.);
TH2D     *hwindow2 = new TH2D("hwindow2","  ",100,-50.,50.,100,-50.,50.);

TH1D *haberr = new TH1D("haberr","",1000,0.,size/10.);  // RMS is always positive
TH1D *htest = new TH1D("htest","",1000,-8,8);  // RMS is always positive


TH3D *testspherical = new TH3D("testspherical","",100,-1.,1.,100,-1.,1.,100,-1.,1.);
TH3D *hdxr = new TH3D("hdxr","",100,0.,25.,100,-size,size,100,-size/5.,size/5.);

//Histograms Robert Amarinei

TH2D *hRICy = new TH2D("hRICy",";Fractional Pupil Coordonate (at lens); Displacement at lens (mm) ",100, -1.1, 1.1, 100,-5,5);  // RMS is always positive
TH2D *hRICx = new TH2D("hRICx",";Fractional Pupil Coordonate (at lens); Displacement at lens (mm)",100, -1.1, 1.1, 100,-5,5);  // RMS is always positive

double D = 100.;
double d1 = w_pos;

// double anglimit = TMath::ATan((D/2.)/d1);

//std::cout << anglimit << "  " << TMath::Cos(anglimit) << std::endl;

Int_t j(0);
Double_t x_file(0.), y_file(0.), theta_file(0.), phi_file(0.);
std::vector<double> x_WLS;
std::vector<double> y_WLS;
std::vector<double> theta_r;
std::vector<double> phi_r;

double centerX(0.), centerY(0.);
TH2D *h1_2d  = new TH2D("h1_PEN_dist","Photon distribution on Screen at PEN ; X (mm); Y(mm) ", 200, -65,65,200, -65,65);
TH2D *hpmt_2d  = new TH2D("h_PMT_dist"," Photon distribution on the Photocathode of PMT ; X (mm); Y (mm) ", 200, -30,30,200, -30,30);
std::cout << "PhAtThGEM " << PhtAtThGEM << std::endl;
std::cout << "PhAtThGEM " << PhtAtThGEM << std::endl;
int ntot = 0;


//-------------------------
//propagate the photons towards the PEN
//-------------------------

//  for (int pos(0); pos < a1_store.size(); pos++){
for (int pos(0); pos < lens_store.size(); pos++){

  lensposition = lens_store.at(pos)->GetLensPos();
  lens_th = lens_store.at(pos)->GetThickness();
  lens_ApRad = lens_store.at(pos)->GetApRad();

  lensposition_2 = lens_store_2.at(pos)->GetLensPos();

  double l1 = lensposition;
  double l2 = lensposition_2;

  sensorpos = sensorpositions_v.at(pos) + WLS_Zpos;
  cout << "  lensposition " << lensposition << "sens pos " << sensorpos <<  "  lens_th " << lens_th << "  Lens_ApRad " << lens_ApRad << endl;

  xOnPEN.clear();
  yOnPEN.clear();
  hsensorlens->Reset("ICESM");
  h1_2d->Reset("ICESM");
  hsensornolens->Reset("ICESM");
  hwindow2 ->Reset("ICESM");
  hlens->Reset("ICESM");

  hdxr->Reset("ICESM");
  h2y->Reset("ICESM");
  hpy->Reset("ICESM");
  hpx->Reset("ICESM");
  h2x->Reset("ICESM");
  hwindow2->Reset("ICESM");
  hsensornolens->Reset("ICESM");
  photAtLens = 0;
  hwindow->Reset("ICESM");
  hRICy->Reset("ICESM");
  hRICx->Reset("ICESM");
  dx_mean = 0;


  for (int i0(0); i0 < (int)PhtAtThGEM/2 ; i0++){// here the two accounts for photons emitted towards the cathode
    double rand_rad = dt/2 * TMath::Sqrt(r.Uniform());
    double ang = r.Uniform()  * 2 * TMath::Pi();
    //double x = centerX + rand_rad * cos(ang);
    //double y = centerY + rand_rad * sin(ang);
    //double  x = r.Uniform(-size/2,size/2);
    //double y=x;
    // double x = r.Uniform(-size/2 / TMath::Sqrt(2) , size/2 / TMath::Sqrt(2));

    // Position for cosmic ray
    // double x = r.Uniform(-50 , 50) ;
    // double y = x+ r.Uniform(-dt/2,dt/2);

    // Position for alpha
    double x = 0 + r.Uniform(-dt/2,dt/2);//
    // double y = r.Uniform(0,part_propag) + r.Uniform(-dt/2,dt/2);
    double y = r.Uniform(-part_propag/2,part_propag/2) + r.Uniform(-dt/2,dt/2);

    double z = 0.;
    //double costheta = r.Uniform(TMath::Cos(anglimit),1.);
    double costheta = r.Uniform(0,1.);
    double phi = r.Uniform(0.,2*3.141592);
    //cout << " theta " << TMath::ACos(costheta)  * 180 / TMath::Pi()<< endl;
    double sintheta = TMath::Sqrt(1.-(costheta*costheta));

    double vx = sintheta*TMath::Cos(phi);
    double vy = sintheta*TMath::Sin(phi);
    double vz = costheta;

    // The angle is wrt the lens surface vector (perpendicular to surface).

    double thx = (vx/vz);
    double thy = (vy/vz);

    // if( TMath::Sqrt((x+thx*WLS_Zpos)*(x+thx*WLS_Zpos)+(y+thy*WLS_Zpos)*(y+thy*WLS_Zpos)) < WLS_size/2.  && r.Uniform() < PEN_QE && r.Uniform() < mesh_t ){

    if( -50 < x+thx*WLS_Zpos && x+thx*WLS_Zpos < 50  && -50 < y+thy*WLS_Zpos && y+thy*WLS_Zpos < 50 &&  r.Uniform() < PEN_QE && r.Uniform() < mesh_t ){
      xOnPEN.push_back(x+thx*WLS_Zpos);
      yOnPEN.push_back(y+thy*WLS_Zpos);
      h1_2d->Fill(x+thx*WLS_Zpos, y+thy*WLS_Zpos );
    }
  }

  //- END propagation on PEN

  ntot =  PhtAtThGEM;
  //  cout << " SIZE " << ntot << endl;
  int sensornolens = 0;


  //ntot = 1e6;
  for(int i = 0; i < xOnPEN.size();i++) {

    double x = xOnPEN.at(i);
    double y = yOnPEN.at(i);
    //double x = r.Uniform(-size,size);
    //double y = x;
    double z = 0.;
    //double costheta = r.Uniform(TMath::Cos(anglimit),1.);
    double costheta = r.Uniform(-1.,1.);
    if( costheta < 0. ) continue; // Take only the photons in the forward direction.

    double phi = r.Uniform(0.,2*3.141592);
    //cout << " theta " << TMath::ACos(costheta)  * 180 / TMath::Pi()<< endl;
    double sintheta = TMath::Sqrt(1.-(costheta*costheta));

    double vx = sintheta*TMath::Cos(phi);
    double vy = sintheta*TMath::Sin(phi);
    double vz = costheta;

    testspherical->Fill(vx,vy,vz);

    Ray ray(x,y,z,vx,vy,vz,1.);

    // The angle is wrt the lens surface vector (perpendicular to surface).

    double thx = (vx/vz);
    double thy = (vy/vz);

    //cout << " x " << x << " y " << y << endl;
    if( TMath::Sqrt((x+thx*d1)*(x+thx*d1)+(y+thy*d1)*(y+thy*d1)) < D/2. )
    hwindow2->Fill(x+thx*d1,y+thy*d1);

    if( TMath::Abs(x+thx*d1)<8. &&  TMath::Abs(y+thy*d1)< 8.) {
      hsensornolens->Fill(x+thx*d1,y+thy*d1);
    }


    if( TMath::Sqrt((x+thx*(lensposition+(lens_th/2)))*(x+thx*(lensposition+(lens_th/2)))+(y+thy*(lensposition+(lens_th/2)))*(y+thy*(lensposition+(lens_th/2)))) < lens_ApRad ) 	  photAtLens++;


    double xf;
    double yf;
    double thxf;
    double thyf;

    if( !w.Transport(ray) ) continue;
    ray.Transport(w_pos);

    hwindow->Fill(ray.GetX(),ray.GetY());

    if( pmt.Transport(ray) ){
      ray.Transport(pmt_pos);
      Double_t rand_PMT= r.Uniform();
      Bool_t PMT_con = rand_PMT < PEN_QE;
      if (PMT_con == true) hpmt_2d->Fill(ray.GetX(), ray.GetY());
    }

    if( !a1_store.at(pos)->Transport(ray) )continue;
    ray.Transport(a1_store.at(pos)->GetPos());




    //if( !obj.at(pos)->Transport(ray) ) continue;
    if( !lens_store.at(pos)->Transport(ray) ) continue;
    hlens->Fill(ray.GetX(), ray.GetY());

    double Ratlens = TMath::Sqrt(ray.GetX()*ray.GetX()+ray.GetY()*ray.GetY());

    // Get Params at the lens:
    ray.Transport(lensposition);


    Double_t FY =  (2* (ray.GetY() +  lens_ApRad) / (2*lens_ApRad) ) -1;
    Double_t FX =  (2* (ray.GetX() +  lens_ApRad) / (2*lens_ApRad) ) -1;
    //cout << " z at lens " << ray.GetZ() << endl;

    if( !lens_store_2.at(pos)->Transport(ray) ) continue;

    // Image

    ray.Transport(sensorpos);
    //cout << " z at image " << ray.GetZ() << endl;
    Double_t DY = ray.GetY();
    Double_t DX = ray.GetX();
    //if (-size<y - WLS_size/2. && size < 1) hRICy-> Fill(FY, DY);
    if (-1<y && y < 1) hRICy-> Fill(FY, DY);
    //if (-size<x && size < 1) hRICx ->Fill(FX,DX);
    if (-1<x && x < 1 && FX > 0){
      hRICx ->Fill(FX,DX);
      dx_mean += DX;
    }
    //ray.Print();
    Double_t con1 = r.Uniform();
    Double_t con2 = r.Uniform();
    Double_t con3 = r.Uniform();
    Double_t con4 = r.Uniform();
    Bool_t eff_con = con1 < MPPC_QE && con2 < Acr_tr ;

    //cout << " con1 " << con1 << " con2 " << con2 << " con3 " << con3 << endl;
    if( TMath::Abs(ray.GetX())<8. &&  TMath::Abs(ray.GetY())< 8. && eff_con ) {

      hsensorlens->Fill(ray.GetX(),ray.GetY());

      htest->Fill(ray.GetX());

      //hsensorlens->Fill(ray.GetX(),ray.GetY());
      hdxr->Fill(Ratlens,x,ray.GetX());
      // scaled image.

      h2x->Fill(x,ray.GetX());
      //cout << " x " << x << " ray.GetX()= " << ray.GetX() << endl;
      hpx->Fill(x,ray.GetX());
      h2y->Fill(y,ray.GetY());
      hpy->Fill(y,ray.GetY());


    }
  }


  //eff x magnification scan


  double bin_content = 0;
  for (int i(6); i <12; i++){

    bin_content += hsensorlens->GetBinContent (i,i);
  }

  h2x->FitSlicesX(); // This fits gaussians in slices of Y
  h2y->FitSlicesX(); // This fits gaussians in slices of Y


  TH1D *h2xmean = (TH1D*) gROOT->FindObject("h2x_1"); // This gets the histogram of  mean of the fitted gaussian as function of reco points.
  TH1D *h2ymean = (TH1D*) gROOT->FindObject("h2y_1");

  h2xmean->Fit("pol1","","",-7.,7.);
  h2ymean->Fit("pol1","","",-7.,7.);

  // double scale = ((h2xmean->GetFunction("pol1")->GetParameter(1))+(h2ymean->GetFunction("pol1")->GetParameter(1))) /2.;

  TH1D *h2xsigma = (TH1D*) gROOT->FindObject("h2x_2"); // This gets the histogram of  sigmas of the fitted gaussian as function of reco points.
  h2xsigma->Fit("pol0","","",-3.,3.);   // To obtain the aberration, this is mainly the spread of true points
  double aberr = (h2xsigma->GetFunction("pol0")->GetParameter(0));



  //TCanvas * c_f = new TCanvas ("c_f", "", 600,600);
  //h2xmean->Draw();
  // h2xsigma->Draw();


  PhtPerBin.push_back(bin_content / 6 / NDecay);
  eff_mag.push_back(( (double)hsensorlens->GetEntries()/(double)ntot) * 1/(MPPC_QE*Acr_tr*PEN_QE* mesh_t ));
  lens_acc.push_back(hlens->GetEntries()/ntot);
  hpx->Fit("pol1","","same");
  //mag_store.push_back(TMath::Abs(1./(hpx->GetFunction("pol1")->GetParameter(1))));
  // mag_store.push_back(TMath::Abs(((h2xmean->GetFunction("pol1")->GetParameter(1))+(h2ymean->GetFunction("pol1")->GetParameter(1))) /2.));
  mag_store.push_back(TMath::Abs(h2ymean->GetFunction("pol1")->GetParameter(1)));
  aberr_store.push_back(aberr);

  std::cout << " The max number of photons per channel: " << bin_content / 16 / NDecay  << std::endl;
  std::cout << " eff * mag " << ( (double)hsensorlens->GetEntries()/(double)ntot) * 1/(MPPC_QE*Acr_tr*PEN_QE* mesh_t ) << " lensposition " << lensposition <<std::endl;
  std::cout << " Photons reaching the lens " << hlens->GetEntries() << " ratio " << hlens->GetEntries()/ntot << " lens/pen "  << hlens->GetEntries()/xOnPEN.size() << std::endl;

}
TCanvas *c_h2y = new TCanvas("ch2y", "", 800,600);
h2y->Draw("colz");
hpy->Fit("pol1","","same");
TCanvas *c = new TCanvas("c","",1200,800);
c->Divide(2,3);
c->cd(1);
h2x->Draw("colz");
hpx->Fit("pol1","","same");

for(int i = 0; i < 100; i++ ) {
  haberr->Fill(hpy->GetBinError(i+1));
}
c->cd(2);
h2y->Draw("colz");
hpy->Fit("pol1","","same");
for(int i = 0; i < 100; i++ ) {
  haberr->Fill(hpy->GetBinError(i+1));
}

c->cd(3);
hsensorlens->Scale(1/NDecay);
hsensorlens->Draw("colz");

c->cd(4);
hsensornolens->Scale(1/NDecay);
hsensornolens->Draw("colz");

c->cd(5);
hwindow->Scale(1/NDecay);
hwindow->Draw("colz");

c->cd(6);
hdxr->Draw("box");

c->Update();

TCanvas *c1 = new TCanvas("c1","",800,600);
hCtPerEvt->Draw();
c1->Update();

TCanvas *clens = new TCanvas ("clens", "", 800, 600);
hlens->Scale(1/NDecay);
hlens -> Draw("colz");

TCanvas * cRIC = new TCanvas("cRIC" , "c", 800,600);
cRIC->Divide(2,1);
cRIC->cd(1);
hRICy -> Draw("colz");
cRIC->cd(2);
hRICx -> Draw("colz");
//cRIC->SaveAs("/Users/robertamarinei/Desktop/Year1_PhD/TPC/LatexPresentation/TPC_Full_Simulation-Theoretical_Photons_Detected/Images/hRIC_Aperture.pdf", "pdf");
TCanvas * c1_2d = new TCanvas("c1_2d", "" , 800, 600);
// h1_2d->GetYaxis()->SetTitleOffset(1);
gStyle->SetOptStat("e");
h1_2d->Draw("colz");
TCanvas * chPMT_2d = new TCanvas("chPMT_2d", "" , 800, 600);
hpmt_2d->Draw("colz");
TEllipse *el1 = new TEllipse(0,0, WLS_size/2,WLS_size/2);
el1->SetFillColor(6);
el1->SetFillStyle(0);
el1->SetLineColor(11);
el1->SetLineWidth(12);
el1->Draw("same");
TCanvas * ctest = new TCanvas("ctest", "" , 800, 600);
//htest->Scale ( MPPC_QE * Acr_tr * mesh_t);
hsensorlens->Draw("colz");
//testspherical->Draw();
//ctest->SaveAs("/Users/robertamarinei/Desktop/Year1_PhD/TPC/LatexPresentation/TPC_Full_Simulation-Theoretical_Photons_Detected/Images/hsensorlens.pdf", "pdf");
double scale = 1./(hpx->GetFunction("pol1")->GetParameter(1));
//double scale = ((h2xmean->GetFunction("pol1")->GetParameter(1))+(h2ymean->GetFunction("pol1")->GetParameter(1))) /2.;
// Double_t MPPC_QE = 0.4;
// Double_t Acr_tr = 0.9;
// Double_t mesh_t = 0.8 ;




std::cout <<std::endl<<std::endl;
std::cout << " -------------------For all events--------------------------- " << std::endl;
std::cout << " Total phton at ThGEM " << ntot << endl;
std::cout << " Scale factor  " <<  scale << std::endl;
std::cout << " Scale factor  " <<  mag_store.back() << std::endl;
std::cout << " Mean dispersion at PEN " <<  haberr->GetMean() << std::endl;
std::cout << " Mean dispersion at image " <<   haberr->GetMean()*scale << std::endl;
std::cout << " Photons emitted at PEN " << xOnPEN.size() << " Fraction " << (double)xOnPEN.size()/ntot<< endl;
std::cout << " Photons emitted at PMT " << hpmt_2d->GetEntries() << " Fraction " << (double)hpmt_2d->GetEntries()/ntot<< endl;
std::cout << " Photons at window " << hwindow->GetEntries() <<  " ratio " << hwindow->GetEntries()/ntot << " window/pen " << hwindow -> GetEntries()/ xOnPEN.size()  <<  endl;
std::cout << " Photons at window (direct calc) " << hwindow2->GetEntries() <<  " ratio " << hwindow2->GetEntries()/ntot << std::endl;
std::cout << " Photons reaching the lens " << hlens->GetEntries() << " ratio " << hlens->GetEntries()/ntot << " lens/pen "  << hlens->GetEntries()/xOnPEN.size() << std::endl;
std::cout << " Fraction of photons reaching the sensor " << std::endl;
std::cout << "       With lens " << (double)hsensorlens->GetEntries()/(double)ntot<< std::endl;
std::cout << "       With no lense " << (double)hsensornolens->GetEntries()/(double)ntot << std::endl;
std::cout <<  " Including the MPPC QE, Window Transparence, Grid Transparency, With Lense: " <<  (double)hsensorlens->GetEntries()  << endl;
std::cout << " ------------------------------------------------------------------- " << std::endl;
std::cout << "Lens Performance " << dx_mean/hRICx->GetEntries() << " SensorPos " << sensorpos << std::endl;

std::cout << " ------------------------------------------------------------------- " << std::endl;


std::cout << " --------------------------- For one event ------------- " << std::endl;
std::cout << " Total phton at ThGEM " << ntot/NDecay << endl;
std::cout << " Photons emitted at PEN " << xOnPEN.size()/NDecay << " Fraction " << (double)xOnPEN.size()/ntot<< endl;
std::cout << " Photons at window " << hwindow->GetEntries()/NDecay <<  " ratio " << hwindow->GetEntries()/ntot << " window/pen " << hwindow -> GetEntries()/ xOnPEN.size()  <<  endl;
std::cout << " Photons emitted at PMT " << hpmt_2d->GetEntries()/NDecay << " Fraction " << (double)hpmt_2d->GetEntries()/ntot<< endl;

std::cout << " --------------------------- Geometry ------------- " << std::endl;
cout<<" The position of the widnow (its center): " <<  w_pos << endl;

TCanvas * c_aberr = new TCanvas("Aberration"," ", 600,600);
TGraph * gr_aberr_pos = new TGraph(lens_acc.size(), &lenspositions_v[0], &aberr_store[0]);
gr_aberr_pos->SetName("AberrVsPos");
gr_aberr_pos->SetLineColor(2);
gr_aberr_pos->SetLineWidth(4);
gr_aberr_pos->SetMarkerColor(4);
gr_aberr_pos->SetMarkerSize(1.5);
gr_aberr_pos->SetMarkerStyle(21);
gr_aberr_pos->SetTitle("Aberration of lens ");
gr_aberr_pos->GetYaxis()->SetTitle(" Mean deviation from true point ");
gr_aberr_pos->GetXaxis()->SetTitle("Position from PEN [mm]");

gr_aberr_pos->Draw("AL*");

TCanvas * c_acc_pos_lens = new TCanvas("_acc_pos_lens"," ", 600,600);
TGraph * gr_acc_pos_lens = new TGraph(lens_acc.size(), &lenspositions_v[0], &lens_acc[0]);
gr_acc_pos_lens->SetName("LensAccVsPos");
gr_acc_pos_lens->SetLineColor(2);
gr_acc_pos_lens->SetLineWidth(4);
gr_acc_pos_lens->SetMarkerColor(4);
gr_acc_pos_lens->SetMarkerSize(1.5);
gr_acc_pos_lens->SetMarkerStyle(21);
gr_acc_pos_lens->SetTitle("Lens Geometrical Acceptance");
gr_acc_pos_lens->GetYaxis()->SetTitle("Acceptance");
gr_acc_pos_lens->GetXaxis()->SetTitle("Position");

gr_acc_pos_lens->Draw("AL*");

TCanvas * c_mag_pos = new TCanvas("_mag_pos ", "", 600,600);


TGraph * gr_mag_pos = new TGraph(lens_acc.size(), &lenspositions_v[0], &mag_store[0]);
gr_mag_pos->SetName("MagVsPos");
gr_mag_pos->SetLineColor(2);
gr_mag_pos->SetLineWidth(4);
gr_mag_pos->SetMarkerColor(4);
gr_mag_pos->SetMarkerSize(1.5);
gr_mag_pos->SetMarkerStyle(21);
gr_mag_pos->SetTitle("Lens Magnitude");
gr_mag_pos->GetYaxis()->SetTitle(" Magnitude ");
gr_mag_pos->GetXaxis()->SetTitle("Position");

gr_mag_pos->Draw("AL*");

std::vector<double> acc_mag_lens;
for (int i(0); i< mag_store.size(); i++){
  acc_mag_lens.push_back(lens_acc.at(i)*mag_store.at(i));
}


TCanvas * c_LensAccMag_pos = new TCanvas("Acc_mag_pos ", "", 600,600);


TGraph * gr_LensAccMag_pos = new TGraph(lens_acc.size(), &lenspositions_v[0], &acc_mag_lens[0]);
gr_LensAccMag_pos->SetName("LensAccMagVsPos");
gr_LensAccMag_pos->SetLineColor(2);
gr_LensAccMag_pos->SetLineWidth(4);
gr_LensAccMag_pos->SetMarkerColor(4);
gr_LensAccMag_pos->SetMarkerSize(1.5);
gr_LensAccMag_pos->SetMarkerStyle(21);
gr_LensAccMag_pos->SetTitle("Lens Magnitude * Acceptance");
gr_LensAccMag_pos->GetYaxis()->SetTitle(" Magnitude * Acceptance");
gr_LensAccMag_pos->GetXaxis()->SetTitle("Position");

gr_LensAccMag_pos->Draw("AL*");



TGraph * gr_eff_mag = new TGraph (PhtPerBin.size(), &eff_mag[0],&PhtPerBin[0] );
gr_eff_mag->SetName("PhtVsEff-Mag");
TCanvas * ceff_mag = new TCanvas("ceff_magg"," ", 600,600);
gr_eff_mag->SetLineColor(2);
gr_eff_mag->SetLineWidth(4);
gr_eff_mag->SetMarkerColor(4);
gr_eff_mag->SetMarkerSize(1.5);
gr_eff_mag->SetMarkerStyle(21);
gr_eff_mag->SetTitle(Form("WLS @ %f ", WLS_Zpos));
gr_eff_mag->GetYaxis()->SetTitle("Photon per channel");
gr_eff_mag->GetXaxis()->SetTitle("MPPC Acceptance * Magnitude");


gr_eff_mag->Draw("AL*");

TGraph * gr_pos_count = new TGraph (PhtPerBin.size(), &lenspositions_v[0],&PhtPerBin[0] );
TCanvas * c_pos_count = new TCanvas("c_pos_count"," ", 600,600);
gr_pos_count->SetName("PhtVsPos");
gr_pos_count->SetLineColor(2);
gr_pos_count->SetLineWidth(4);
gr_pos_count->SetMarkerColor(4);
gr_pos_count->SetMarkerSize(1.5);
gr_pos_count->SetMarkerStyle(21);
gr_pos_count->SetTitle(Form("WLS @ %f ", WLS_Zpos));
gr_pos_count->GetYaxis()->SetTitle("Photon per channel");
gr_pos_count->GetXaxis()->SetTitle("Distance from PEN (mm)");

gr_pos_count->Draw("AL*");


double f(0);
f = lens_store.at(0)->GetFocalLength();
double f2 = lens_store_2.at(0)->GetFocalLength();
double lens_th_2(0), lens_ApRad_2 (0);


TFile *file = new TFile(Form("graphs_%d%d-%d.root", (int)f, (int)f2, int(d_1_2)), "recreate");



gr_pos_count->Write();
gr_eff_mag->Write();
gr_LensAccMag_pos->Write();
gr_mag_pos->Write();
gr_acc_pos_lens->Write();
gr_aberr_pos->Write();
delete file;

for (int i(0); i< lens_store.size(); i++){
  delete(lens_store.at(i));
  //delete(a1_store.at(i));
}


return 0;




}
