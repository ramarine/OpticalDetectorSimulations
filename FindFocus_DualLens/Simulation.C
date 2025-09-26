// The lens position here (from this version and above) is the distance between the PEN and the first lenst.
// Whenever we define a startpos of 130 (PEN -> Lens) an extra WLS_Zpos is going to be added such as to account for
// the distance between the ThGEM and the WLS.

// the same happens with the

#include "OpticSystemTransport.h"
#include "TRandom.h"
#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TProfile.h"
#include "TCanvas.h"


//double Simulation(double size = 1., double lensposition = 149.10 +6.5/2. , double sensorpos =183.42  , bool debug = false){ //:: 30mm lens
using namespace std;

double Simulation(double size = 200., double lensposition = 152. , double sensorpos = 216.  , bool debug = false){// works with 50 mm lens.
  //double Simulation(double size = 1., double lensposition = 220., double sensorpos = 252.5,bool debug = false){
  //double Simulation(double size = 1., double lenwsposition = 220., double sensorpos = 220.+64.70,bool debug = false){ // works with 50mm diam lens




  TFile * graphs  =  new TFile("graphs.root", "UPDATE");

  std::vector <Lens*> lens_store;
  std::vector <Lens*> lens_store_2;
  std::vector <Aperture*> a1_store;
  double startpos = 172;// 110 is the minimum position. i.e. if the lens would touch the window.

  //Lenses:::::::::: of 50mm + 30mm
  /*
  Double_t lens_th_30 = 6.5;
  Double_t lens_th = lens_th_30;
  Double_t lens_th_50 = 16;
  Double_t lens_ApRad = 30./2.; //Lens Aperture Radius
  Double_t d_1_2 = lens_th_30/2 + lens_th_50/2  ;

  //Load lenses of, 50mm and 30mm

  for (int i(0); i<30; i++){
  lens_store.push_back(new Lens(startpos,lens_th_50,74.78,50./2.,1.833,3));
  lens_store_2.push_back(new Lens(startpos+d_1_2,lens_th_30,45.61,lens_ApRad,1.833,3));
  a1_store.push_back(new Aperture(startpos+4.0,1.,15.,2));
  startpos +=5;

}

*/


//Edmund Optics :::::::: 50 +50 mm
//Load lenses of 50 + 50mm
/*
Double_t lens_ApRad = 50./2;
Double_t lens_th = 16.;
Double_t d_1_2 = lens_th +10;
for (int i(0); i<30; i++){
lens_store.push_back(new Lens(startpos,lens_th,74.78,lens_ApRad,1.833,3));
lens_store_2.push_back(new Lens(startpos + d_1_2, lens_th, 74.78, lens_ApRad,1.833,3));
a1_store.push_back(new Aperture(startpos+8.5, 1., 100. ,2));
startpos+=5;
}
*/



// Edmund optics 63-556 :::::: 30 +30 mm
//Load lenses of 30 + 30 mm
/*
Double_t lens_th_30 = 6.5;
Double_t lens_th = lens_th_30;
Double_t d_1_2 = lens_th+lens_th;
Double_t lens_ApRad = 30./2.; //Lens Aperture Radius




for (int i(0); i<30; i++){
lens_store.push_back(new Lens(startpos,lens_th_30,45.61,lens_ApRad,1.833,3));
lens_store_2.push_back(new Lens(startpos+d_1_2,lens_th_30,45.61,lens_ApRad,1.833,3));
a1_store.push_back(new Aperture(startpos+4.0,1.,15.,2));
startpos +=5;
}

*/
// Edmund optics 63-556 :::::: 30 +20 mm #63-550
//Load lenses of 30 + 30 mm



Double_t lens_th_30 = 6.5;
Double_t lens_Surf_R1 = 45.61; // the radius of the left most curved surface.
Double_t lens_th_20 = 5.0;
Double_t lens_th = 0;
Double_t d_1_2 = lens_th_30/2+lens_th_30/2 + 6.5; //  2*30 mm lenses with 13mm between the optical centres
Double_t lens_ApRad = 30./2.; //Lens Aperture Radius
Double_t Flange_Thick = 22;//mm thickness of flange
Double_t WLS_Zpos = 2.8;
Double_t PEN_to_Flange = 116.;
Double_t d_ThGEMtoFlange = PEN_to_Flange + WLS_Zpos;//mm
Double_t w_pos = d_ThGEMtoFlange + Flange_Thick/2; //center of the window



//Aperture  a0(101.,1.,100.,2);
//  Aperture  a0(98.,1.,100.,2);// ORIGINAL
//Disc  w(93.,8.,50.,1.458,1);// ORIGINAL
Disc  w(w_pos,8.3,50.,1.458,1);//




for (int i(0); i<30; i++){
  //-WLS_Zpos+startpos = distance from PEN to lens
  lens_store.push_back(new Lens(WLS_Zpos+startpos,lens_th_30,lens_Surf_R1,lens_ApRad, 1.833,3));
  lens_store_2.push_back(new Lens(WLS_Zpos+startpos+d_1_2,lens_th_30, lens_Surf_R1  , lens_ApRad , 1.833,3));
  a1_store.push_back(new Aperture(WLS_Zpos+startpos -lens_th_30/2 - 3 ,1.,15.,2));
  startpos +=2;
}




Double_t lensposition_2;




// Edmund optics 63-560 :::: 40mm
/*lensposition = 149.10 +6.5/2; sensorpos =206.54;

double lens_th = 8.5;
Lens lens(lensposition,lens_th,60.85,40./2.,1.833,3);
Double_t lens_ApRad = 40./2.; //Lens Aperture Radius
Aperture  a1(lensposition+4.75, 1. , 20. ,2);
Aperture  a0(98.,1.,100.,2);
*/





//Aperture  a0(98.,1.,60.,2); //original
//Aperture  a0(98.,1.,100.,2); // fully open aperture



for (int i(0); i < lens_store.size(); i++){

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
std::vector<Double_t> std_dev_store;
std::vector<Double_t> sensorpos_store;

//Efficiencies for weighting the entries in the histograms
Double_t distr_fact = 0.5;
Double_t MPPC_QE = 0.4;//
Double_t Acr_tr = 0.9;
double PEN_QE = 0.25;
double mesh_t = 0.8;



double NDecay = 10.;
double MIP_e = 244;// eV / mm
//double MIP_e = 590;// eV / mm
double InEnergy = MIP_e * size;

double w_Ar = 26.4;// eV
double prim_electr = InEnergy / w_Ar;
//double PhotoNo = 5000;
double PhotoNo = 5000;
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
//double WLS_Xpos = 0.; // Pen postion relative to GEM
//  FILE *input = fospen(  "WLS_dist_1_5.txt" , "r");// First number is size, and second number is WLS_Xpos
//FILE *input = fopen(  "WLS_dist_5000_0.700000.txt" , "r");

// You can recompute the matrices for different distances by (i.e. if you want to scan parameters):
//
// opt.setdistances(d_source_silica,d_silica_lens,d_lens_sensor)
// opt.ComputeMatrices();

TRandom r;

Double_t dx_mean(0);
Double_t WLS_size = 200;
TH1D *hCtPerEvt = new TH1D("hCtPerEvt","",20,-0.5,19.5);  // RMS is always positive
TH2D     *h2x = new TH2D("h2x","  ",100,-size-2,size+2,100,-20,20);
TH2D     *h2y = new TH2D("h2y","  ",100,-WLS_size/2.,WLS_size/2.,100,-WLS_size/2./5.,WLS_size/2./5.);
TProfile *hpx = new TProfile("hpx","  ",100,-size -2,size +2,-20,20,"S");
TProfile *hpy = new TProfile("hpy","  ",100,-WLS_size/2.,WLS_size/2.,-WLS_size/2./5.,WLS_size/2./5.,"S");

TH2D     *hsensornolens = new TH2D("hsensornolens"," ",16,-8.,8.,16,-8.,8.);
TH2D     *hsensorlens = new TH2D("hsensorlens"," ; X Position on MPPC[mm]; Y Position on MPPC[mm] ",16,-8.,8.,16,-8.,8.);
TH2D     *hlens = new TH2D("hlens"," ; X Position on lens[mm]; Y Position on lens[mm] ",100,-lens_ApRad -10,lens_ApRad+10, 100, -lens_ApRad -10 , lens_ApRad +10);


TH2D     *hwindow = new TH2D("hwindow","  ",100,-50.,50.,100,-50.,50.);
TH2D     *hwindow2 = new TH2D("hwindow2","  ",100,-50.,50.,100,-50.,50.);

TH1D *haberr = new TH1D("haberr","",1000,0.,size/10.);  // RMS is always positive
TH1D *htest = new TH1D("htest","",1000,-8,8);  // RMS is always positive


TH3D *testspherical = new TH3D("testspherical","",100,-1.,1.,100,-1.,1.,100,-1.,1.);
TH3D *hdxr = new TH3D("hdxr","",100,0.,25.,100,-size,size,100,-size/5.,size/5.);

//Histograms Robert Amarinei

TH2D *hRICy = new TH2D("hRICy",";Fractional Pupil Coordonate (at lens); Displacement at lens [mm] ",100, -1.1, 1.1, 100,-5,5);  // RMS is always positive
TH2D *hRICx = new TH2D("hRICx",";Fractional Pupil Coordonate (at lens); Displacement at lens [mm]",100, -1.1, 1.1, 100,-5,5);  // RMS is always positive

double D = 100.;
double d1 = 93.;

// double anglimit = TMath::ATan((D/2.)/d1);

//std::cout << anglimit << "  " << TMath::Cos(anglimit) << std::endl;

Int_t j(0);
Double_t x_file(0.), y_file(0.), theta_file(0.), phi_file(0.);
std::vector<double> x_WLS;
std::vector<double> y_WLS;
std::vector<double> theta_r;
std::vector<double> phi_r;

double centerX(0.), centerY(0.);
TH2D *h1_2d  = new TH2D("h1_2d","Photon distribution on Screen at PEN ; Z[mm]; Y[mm] ", 200, -WLS_size/2 - 30,WLS_size/2 + 30,200, -WLS_size/2 - 30,WLS_size/2 + 30);
std::cout << "PhAtThGEM " << PhtAtThGEM << std::endl;
int ntot = 0;



double f(0);
f = lens_store.at(0)->GetFocalLength();
double f2 = lens_store_2.at(0)->GetFocalLength();
double  lens_th_2(0), lens_ApRad_2 (0);
ofstream myfile;

myfile.open (Form("DualLensPos_%d_%d-%d_NewBatch.txt", (int)f, (int)f2, int(d_1_2)));


// for (int lens_place(0); lens_place < lens_store.size(); lens_place++){
for (int lens_place(0); lens_place < 4; lens_place++){
  std_dev_store.clear();
  sensorpos_store.clear();
  PhtPerBin.clear();
  std::vector<double> eff_mag;


  lensposition = lens_store.at(lens_place)->GetLensPos();
  lens_th = lens_store.at(lens_place)->GetThickness();
  lens_ApRad = lens_store.at(lens_place)->GetApRad();


  lensposition_2 = lens_store_2.at(lens_place)->GetLensPos();
  lens_th_2 = lens_store_2.at(lens_place)->GetThickness();
  lens_ApRad_2 = lens_store_2.at(lens_place)->GetApRad();

  double i1(0), o2(0), i2(0), l1(0), l2(0);
  l1 = lensposition;
  l2 = lensposition_2;
  i1 = l1*f /(l1-f);
  o2 = - (i1 - (l2 - l1 )); // the object is at the right of the lens -> gets minus sign


  i2 = o2*f2/(o2 - f2);

  sensorpos =  lensposition_2 + i2 - 5;

  cout << "Sensor pos from second lens" << sensorpos - lensposition_2  << endl;

  //    sensorpos = lensposition +( (lensposition*f)/(lensposition - f)) - 7 ;
  cout << "LENSPOSITION from PEN: " << lensposition - WLS_Zpos << endl;

  for (int pt(0); pt < 17; pt++){

    //cout << "In for loop sensor " << sensorpos << endl;
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




    //-------------------------
    //propagate the photons towards the PEN
    //-------------------------

    for (int i0(0); i0 < (int)PhtAtThGEM/2 ; i0++ ) {
      double rand_rad = dt/2 * TMath::Sqrt(r.Uniform());
      double ang = r.Uniform()  * 2 * TMath::Pi();
      //double x = centerX + rand_rad * cos(ang);
      //double y = centerY + rand_rad * sin(ang);
      //double  x = r.Uniform(-size/2,size/2);
      //double y=x;
      double x = r.Uniform(-size/2 / TMath::Sqrt(2) , size/2 / TMath::Sqrt(2));
      double y = x;
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

      if( TMath::Sqrt((x+thx*WLS_Zpos)*(x+thx*WLS_Zpos)+(y+thy*WLS_Zpos)*(y+thy*WLS_Zpos)) < WLS_size/2.  && r.Uniform() < PEN_QE && r.Uniform() < mesh_t ){
        xOnPEN.push_back(x+thx*WLS_Zpos);
        yOnPEN.push_back(y+thy*WLS_Zpos);
        h1_2d->Fill(x+thx*WLS_Zpos, y+thy*WLS_Zpos );
      }

    }

    //-----------------END propagation on PEN

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

      //	if( TMath::Sqrt((x+thx*(lens_store.at(lens_place)->GetLensPos()+(lens_store.at(lens_place)->GetThickness()/2)))*(x+thx*(lens_store.at(lens_place)->GetLensPos()+(lens_store.at(lens_place)->GetThickness()/2)))+(y+thy*(lens_store.at(lens_place)->GetLensPos()+(lens_store.at(lens_place)->GetThickness()/2)))*(y+thy*(lens_store.at(lens_place)->GetLensPos()+(lens_store.at(lens_place)->GetThickness()/2)))) < lens_store.at(lens_place)->GetApRad()) 	  photAtLens++;

      if( TMath::Sqrt((x+thx*(lensposition+(lens_th/2)))*(x+thx*(lensposition+(lens_th/2)))+(y+thy*(lensposition+(lens_th/2)))*(y+thy*(lensposition+(lens_th/2)))) < lens_ApRad) 	  photAtLens++;


      double xf;
      double yf;
      double thxf;
      double thyf;

      if( !w.Transport(ray) ) continue;
      hwindow->Fill(ray.GetX(),ray.GetY());
      ray.Transport(w_pos);

      //if( !a0.Transport(ray) ){ std::cout << "blocked in a0 " << std::endl; continue;}

      double Ratlens0 = TMath::Sqrt(ray.GetX()*ray.GetX()+ray.GetY()*ray.GetY());



      // Transportation towards the first

      if( !lens_store.at(lens_place)->Transport(ray) ) continue;
      hlens->Fill(ray.GetX(), ray.GetY());
      //if(  !a1_store.at(lens_place)->Transport(ray) ) { cout << "blocked in a1 " << endl; continue;}
      double Ratlens = TMath::Sqrt(ray.GetX()*ray.GetX()+ray.GetY()*ray.GetY());
      ray.Transport(lens_store.at(lens_place)->GetLensPos());


      Double_t FY =  (2* (ray.GetY() +  lens_ApRad) / (2*lens_ApRad) ) -1;
      Double_t FX =  (2* (ray.GetX() +  lens_ApRad) / (2*lens_ApRad) ) -1;
      //cout << " z at lens " << ray.GetZ() << endl;

      if( !lens_store_2.at(lens_place)->Transport(ray) ) continue;
      ray.Transport(lens_store_2.at(lens_place)->GetLensPos());

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

      Double_t con1 = r.Uniform();
      Double_t con2 = r.Uniform();
      Double_t con3 = r.Uniform();
      Double_t con4 = r.Uniform();
      Bool_t eff_con = con1 < MPPC_QE && con2 < Acr_tr ;
      //cout << " con1 " << con1 << " con2 " << con2 << " con3 " << con3 << endl;
      if( TMath::Abs(ray.GetX())<8. &&  TMath::Abs(ray.GetY())< 8. && eff_con ) {

        hsensorlens->Fill(ray.GetX(),ray.GetY());

        htest->Fill(ray.GetX());
        //hsensorlens->Scale(MPPC_QE*Acr_tr*mesh_t);
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
    // std deviation of central bins
    double avg_std = 0;
    for(int i(7); i < 11; i++){
      avg_std += hsensorlens->ProjectionX("",i,i,"")->GetStdDev();
    }


    std_dev_store.push_back(avg_std/4);
    sensorpos_store.push_back(sensorpos);

    // number of photons per most populous channel
    double bin_content = 0;
    for (int i(0); i <16; i++){

      bin_content += hsensorlens->GetBinContent (i,i)  ;
    }

    //cout << "STD DEV " << avg_std/4 << " No. Of Phots " << bin_content / 16 / NDecay <<endl;

    PhtPerBin.push_back(bin_content / 16 / NDecay);
    eff_mag.push_back(( (double)hsensorlens->GetEntries()/(double)ntot) * 1/(MPPC_QE*Acr_tr*PEN_QE* mesh_t ));

    sensorpos += 0.5;
  }


  // find smallest standard deviation
  cout << " smalelst std dev "<<*min_element(std_dev_store.begin(), std_dev_store.end()) << endl;
  double key = *min_element(std_dev_store.begin(), std_dev_store.end());

  std::vector<double>::iterator itr = std::find(std_dev_store.begin(), std_dev_store.end(), key);

  int index = 0;
  if (itr != std_dev_store.cend()){
    index = std::distance(std_dev_store.begin(), itr);
    cout << " INDEX " << index << endl;
  }



  // find largest number of photons per pixel
  cout << " largest no of pht "<<*max_element(PhtPerBin.begin(), PhtPerBin.end()) << endl;
  double key2 = *max_element(PhtPerBin.begin(), PhtPerBin.end());

  std::vector<double>::iterator itr2 = std::find(PhtPerBin.begin(), PhtPerBin.end(), key2);

  int index2 = 0;
  if (itr2 != PhtPerBin.cend()){
    index2 = std::distance(PhtPerBin.begin(), itr2);
    cout << " INDEX 2 " << index2 << endl;
  }

  cout << " For a lensposition (from PEN) " << lens_store.at(lens_place)->GetLensPos() - WLS_Zpos << " the best sensorpos from lens 2 (std wise) is " <<  sensorpos_store.at(index)- lens_store_2.at(lens_place)->GetLensPos() << " PhtPerPix " << PhtPerBin.at(index) << endl;
  cout << " For a lensposition (from PEN)" << lens_store.at(lens_place)->GetLensPos()  - WLS_Zpos<< " the best sensorpos from lens 2 (pht wise) is " <<  sensorpos_store.at(index2)- lens_store_2.at(lens_place)->GetLensPos() << " PhtPerPix " << PhtPerBin.at(index2) <<endl;
  myfile << lens_store.at(lens_place)->GetLensPos() - WLS_Zpos << " " << sensorpos_store.at(index2) - WLS_Zpos   << endl;


}

std::cout <<std::endl<<std::endl;
std::cout << " ------------------------------------------------------------ " << std::endl;
std::cout << "Total phton at ThGEM " << ntot << endl;
//std::cout << " Scale factor  " <<  scale << std::endl;
std::cout << " Mean dispersion at sensor " <<  haberr->GetMean() << std::endl;
//std::cout << " Mean dispersion at image " <<   haberr->GetMean()*scale << std::endl;
std::cout << " Photons emitted at PEN " << xOnPEN.size() << " Fraction " << (double)xOnPEN.size()/ntot<< endl;
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

myfile.close();
return 0;
}
