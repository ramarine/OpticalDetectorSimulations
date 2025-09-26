#include "OpticSystemTransport.h" 
#include "TRandom.h"
#include "TF1.h"  
#include "TH1D.h" 
#include "TH2D.h" 
#include "TH3D.h" 
#include "TProfile.h"
#include "TCanvas.h" 

//double Simulation(double size = 1., double lensposition = 149.10 +6.5/2. , double sensorpos =183.42  , bool debug = false){ //:: 30mm lens
double Simulation(double size = 60., double lensposition = 152. , double sensorpos = 216.  , bool debug = false){// works with 50 mm lens.
  //double Simulation(double size = 1., double lensposition = 220., double sensorpos = 252.5,bool debug = false){
  //double Simulation(double size = 1., double lenwsposition = 220., double sensorpos = 220.+64.70,bool debug = false){ // works with 50mm diam lens
  Double_t WLS_Zpos = 0.0;
  Double_t lens_ApRad = 50./2.; //Lens Aperture Radius

  

  
  // Edmund optics 63-556 :::::: 30 mm 
  //lensposition = 149.10 +6.5/2; sensorpos =183.42;
  /*
  lensposition = 220.,  sensorpos = 220.+24.70;
  Double_t lens_th = 6.5;
  Double_t lens_ApRad = 30./2.; //Lens Aperture Radius
  Lens lens(lensposition,lens_th,45.61,lens_ApRad,1.833,3);
  
  Aperture  a1(lensposition+4.0,1.,15.,2); // original
  Aperture  a0(98.,1.,100.,2);
  
  */
  
  // Edmund optics 63-560 :::: 40mm
  /*lensposition = 149.10 +6.5/2; sensorpos =206.54;
  Aperture  a1(lensposition+4.75, 1. , 20. ,2); 
  double lens_th = 8.5;
  Lens lens(lensposition,lens_th,60.85,40./2.,1.833,3);
  Double_t lens_ApRad = 40./2.; //Lens Aperture Radius
  Aperture  a0(98.,1.,100.,2);
*/
  
   
    

  
  //Aperture  a0(98.,1.,60.,2); //original
  //Aperture  a0(98.,1.,100.,2); // fully open aperture

  
  Disc  w(93.,8.,50.,1.458,1);

  //misc variables
  std::vector<double> PhtPerBin;
  std::vector<double> eff_mag;
  std::vector<Double_t> xOnPEN;
  std::vector<Double_t> yOnPEN;

  //Efficiencies for weighting the entries in the histograms
  Double_t distr_fact = 0.5;
  Double_t MPPC_QE = 0.4;//
  Double_t Acr_tr = 0.9;
  double PEN_QE = 0.25;
  double mesh_t = 0.8;

  
  
  double NDecay = 1.;
  double MIP_e = 244;// eV / mm
    //double MIP_e = 590;// eV / mm 
  double InEnergy = MIP_e * size;
  
  double w_Ar = 26.4;// eV
  double prim_electr = InEnergy / w_Ar;  
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
  //  FILE *input = fopen(  "WLS_dist_1_5.txt" , "r");// First number is size, and second number is WLS_Xpos
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
    

  //-------------------------
  //propagate the photons towards the PEN
  //-------------------------
  Double_t lens_th = 16.;
  lensposition = 149.10 +6.5/2; sensorpos =216.9;
  
    
    /*  for( int pos(0); pos<1; pos++){  
  //Edmund optics 32-978 ::::: 50 mm 
    xOnPEN.clear();
    yOnPEN.clear();
    if (pos == 0) lensposition = 149.10 +6.5/2; sensorpos =216.9;
    if (pos == 1) lensposition = 200.; sensorpos =257.3;
    if (pos == 2) lensposition = 220.; sensorpos =275.6;
    */
      Lens lens(lensposition,lens_th,74.78,50./2.,1.833,3);
      
      Aperture  a1(lensposition+8.5, 1., 25.,2);
      Aperture  a0(98.,1.,100.,2);
    
  
  
    
    for (int pos(0); pos < 1; pos++){
      xOnPEN.clear();
      yOnPEN.clear();
      hsensorlens->Reset("ICESM");
      h1_2d->Reset("ICESM");
      hsensornolens->Reset("ICESM");
      hwindow2 ->Reset("ICESM");
      

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

      if (pos == 0) lensposition = 149.10 +6.5/2; sensorpos =216.9;
      if (pos == 1) lensposition = 149.10 +6.5/2; sensorpos =216.9;
      //if (pos == 1) lensposition = 200.; sensorpos =257.3;
      if (pos == 2) lensposition = 220.; sensorpos =275.6;



      lens.SetDebug(debug);
      a0.SetDebug(debug);  
      a1.SetDebug(debug);  
      w.SetDebug(debug);
      
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
      
      if( TMath::Sqrt((x+thx*(lensposition+(lens_th/2)))*(x+thx*(lensposition+(lens_th/2)))+(y+thy*(lensposition+(lens_th/2)))*(y+thy*(lensposition+(lens_th/2)))) < lens_ApRad ) 
      photAtLens++;

      
      double xf; 
      double yf; 
      double thxf;
      double thyf;
      
      if( !w.Transport(ray) ) continue;
      
      hwindow->Fill(ray.GetX(),ray.GetY());
      
      if( !a0.Transport(ray) ){ std::cout << "blocked in a0 " << std::endl; continue;}
      
      double Ratlens0 = TMath::Sqrt(ray.GetX()*ray.GetX()+ray.GetY()*ray.GetY());
      
      
      if( !lens.Transport(ray) ) continue;
      //ray.Transport(lensposition);
      
      hlens->Fill(ray.GetX(), ray.GetY());
      //std::cout << " GetZ " << ray.GetZ() << std::endl ;
      
      
      
      if( !a1.Transport(ray) ) {
	cout << "blocked in a1 " << endl;
	continue;}
      double Ratlens = TMath::Sqrt(ray.GetX()*ray.GetX()+ray.GetY()*ray.GetY());
      
      // Get Params at the lens:
      ray.Transport(lensposition); 
      
      
      Double_t FY =  (2* (ray.GetY() +  lens_ApRad) / (2*lens_ApRad) ) -1;
      Double_t FX =  (2* (ray.GetX() +  lens_ApRad) / (2*lens_ApRad) ) -1;   
      //cout << " z at lens " << ray.GetZ() << endl;
      
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
	dx_mean += DX;}
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
    //eff x magnification scan
    
    double bin_content = 0;
    for (int i(1); i <17; i++){
      
      bin_content += hsensorlens->GetBinContent (i,i);   
    }
    

    PhtPerBin.push_back(bin_content / 16 / NDecay);
    eff_mag.push_back(( (double)hsensorlens->GetEntries()/(double)ntot) * 1/(MPPC_QE*Acr_tr*PEN_QE* mesh_t ));
    
    std::cout << " The max number of photons per channel: " << bin_content / 16 / NDecay  << std::endl;
    std::cout << " eff * mag " << ( (double)hsensorlens->GetEntries()/(double)ntot) * 1/(MPPC_QE*Acr_tr*PEN_QE* mesh_t ) << " lensposition " << lensposition <<std::endl;
    
    }
  
  
  
  
  TCanvas *c = new TCanvas("c","",800,800);  
  c->Divide(2,3); 
  c->cd(1); 
  h2x->Draw("colz"); 
  hpx->Fit("pol1","","same"); 
  
  for(int i = 0; i < 100; i++ ) { 
    haberr->Fill(hpx->GetBinError(i+1)); 
  }
  c->cd(2); 
  h2y->Draw("colz"); 
  hpy->Fit("pol1","","same"); 
  for(int i = 0; i < 100; i++ ) { 
    haberr->Fill(hpy->GetBinError(i+1)); 
  }
  
  c->cd(3); 
  
  hsensorlens->Draw("colz"); 
  
  c->cd(4);
  hsensornolens->Draw("colz");

  c->cd(5); 
  hwindow->Draw("colz");

  c->cd(6);
  hdxr->Draw("box");

  c->Update(); 

  TCanvas *c1 = new TCanvas("c1","",400,400);
  hCtPerEvt->Draw();
  c1->Update();

  TCanvas *clens = new TCanvas ("clens", "", 800, 800);
  hlens -> Draw("colz");
  
  TCanvas * cRIC = new TCanvas("cRIC" , "c", 800,800);
  cRIC->Divide(2,1);
  cRIC->cd(1);
  hRICy -> Draw("colz");
  cRIC->cd(2);
  hRICx -> Draw("colz");
  //cRIC->SaveAs("/Users/robertamarinei/Desktop/Year1_PhD/TPC/LatexPresentation/TPC_Full_Simulation-Theoretical_Photons_Detected/Images/hRIC_Aperture.pdf", "pdf");
  TCanvas * c1_2d = new TCanvas("c1_2d", "" , 600, 600);
  h1_2d->Draw("colz");
  TEllipse *el1 = new TEllipse(0,0, WLS_size/2,WLS_size/2);
  el1->SetFillColor(6);
  el1->SetFillStyle(0);
  el1->SetLineColor(11);
  el1->SetLineWidth(12);
  el1->Draw("same");
  TCanvas * ctest = new TCanvas("ctest", "" , 600, 600);
  //htest->Scale ( MPPC_QE * Acr_tr * mesh_t);
  hsensorlens->Draw("colz");
  //testspherical->Draw();
  //ctest->SaveAs("/Users/robertamarinei/Desktop/Year1_PhD/TPC/LatexPresentation/TPC_Full_Simulation-Theoretical_Photons_Detected/Images/hsensorlens.pdf", "pdf");
  double scale = 1./(hpx->GetFunction("pol1")->GetParameter(1));  
  // Double_t MPPC_QE = 0.4;
  // Double_t Acr_tr = 0.9;
  // Double_t mesh_t = 0.8 ;



  
  std::cout <<std::endl<<std::endl; 
  std::cout << " ------------------------------------------------------------ " << std::endl;
  std::cout << "Total phton at ThGEM " << ntot << endl;
  std::cout << " Scale factor  " <<  scale << std::endl; 
  std::cout << " Mean dispersion at sensor " <<  haberr->GetMean() << std::endl; 
  std::cout << " Mean dispersion at image " <<   haberr->GetMean()*scale << std::endl;
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

  
  TGraph * gr_eff_mag = new TGraph (PhtPerBin.size(),&PhtPerBin[0], &eff_mag[0] );
  TCanvas * ceff_mag = new TCanvas("ceff_magg"," ", 600,600);
  gr_eff_mag->SetLineColor(2);
  gr_eff_mag->SetLineWidth(4);
  gr_eff_mag->SetMarkerColor(4);
  gr_eff_mag->SetMarkerSize(1.5);
  gr_eff_mag->SetMarkerStyle(21);
  gr_eff_mag->SetTitle("Option ACP example");
  gr_eff_mag->GetXaxis()->SetTitle("X title");
  gr_eff_mag->GetYaxis()->SetTitle("Y title");
  
  gr_eff_mag->Draw("AL");
  return 0;
}

