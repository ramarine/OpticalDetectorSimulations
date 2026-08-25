#include "OpticSystemTransport.h"
#include "Cube.h" 
#include "TRandom.h"
#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TFile.h"
#include "TGraph.h"
#include "TProfile.h"
#include "TCanvas.h"

void Debug(int i=0){
    std::cout << " DEBUG DEBUG DEBUG " << i << std::endl;
}

TH2D *Yback; 

double boxsize = 100.;
double IndexCube = 1.588;
TRandom r;

double ReflFactor2surf(double cos0, double n0, double n1, double &cos1 ) {
  double sin0 =sqrt(1-cos0*cos0);
  double sin1 = n0/n1*sin0;
  
  if( sin1 >=  1. ) return 1.; 
  
  cos1 = sqrt(1-sin1*sin1); 
  
  double rs = (n0*cos0-n1*cos1)/(n0*cos0+n1*cos1);
  double rp = (n1*cos0-n0*cos1)/(n1*cos0+n0*cos1);
  
  double R = (rs*rs+rp*rp)/2.; // reflection scintn0-n1
  
  return R;
}


double SimulationCube(double positionparticle = -50.){
  
    double lensposition = 0.; double sensorpos = 0.;
    bool debug = false;
    TFile *graphs = new TFile("graphs.root", "UPDATE");
  
    Cube ECube(-boxsize/2.,boxsize,boxsize/2.,IndexCube,0);

    // 30x30 convex lense
    double width1    = 6.5;
    double pos1      = 7.+14.6+17.26+width1/2.;
    double Radious1  = 45.61;
    double Diameter1 = 30.;
    double Index1    = 1.805;
    
    double posApp = pos1-width1/2.;
    
    Aperture App(posApp,0.1,5.,1); 
    
    Lens ELens(pos1,width1,Radious1,Diameter1/2.,Index1,2);

    double pos2 = pos1+5.+width1;
    
    Lens ELens2(pos2,width1,Radious1,Diameter1/2.,Index1,3);
    
    int total = 1.e+7;
    int accepted = 0;

    double length = boxsize;

    Yback = new TH2D("yback"," ",100,-boxsize/2.,boxsize/2.,100,-1.,1.); 
    
    TH1D *MonX_end = new TH1D("MonXend","",100,-60.,60.);
    TH1D *MonX_cnt = new TH1D("MonXcnt","",100,-60.,60.); 
    
    TH2D *SensorXY = new TH2D("Sensorxy"," ",16,-19./2.,19./2.,16,-19./2.,19./2.);

    double SensorPos = pos2+11.7+width1/2.;
    double ObjectPos = positionparticle;

    TH2D *YZ = new TH2D("yz"," ",1000,-boxsize,SensorPos*(1.1),100,-60,60);
    TH2D *XZ = new TH2D("xz"," ",1000,-boxsize,SensorPos*(1.1),100,-60,60);
   

    TH1D *Mag = new TH1D("Mag"," ",1000,0.,2.);
    TH2D *Mag2D = new TH2D("Mag2D"," ",100,0.,length/2.*sqrt(2.),100,0.,19./2.*sqrt(2.));
    
    std::cout << " Object at " << ObjectPos << " mm " << std::endl;
    
    for(int i = 0; i < total; i++ ) {

      double costheta = r.Uniform(-1.,1.);
      double phi = r.Uniform(0,2.*3.141592);
      double sintheta = TMath::Sqrt(1.-(costheta*costheta));
      double vx = sintheta*TMath::Cos(phi);
      double vy = sintheta*TMath::Sin(phi);
      double vz = costheta;
      double x = 0.0;
      double y = r.Uniform(-length/2.,length/4.);
      double z = ObjectPos+r.Gaus(0.,3.);
      Ray ray(x, y, z, vx, vy, vz, 1);

      ray.AddPointTrajectory();
            
      if( !ECube.Transport(ray) ) continue;
      
      if (!App.Transport(ray)) continue;
      
      if (!ELens.Transport(ray)) continue;
      
      if (!ELens2.Transport(ray)) continue;
      
      ray.Transport(SensorPos);
      ray.AddPointTrajectory();
      
      double roriginal = sqrt(x*x+y*y);
      double rdetector = sqrt(ray.GetX()*ray.GetX()+ray.GetY()*ray.GetY());
      
      
      Mag->Fill(TMath::Abs(rdetector/roriginal));
      Mag2D->Fill(roriginal,rdetector);
      
      double xdet = 1./sqrt(2.)*(ray.GetX()+ray.GetY());
      double ydet = 1./sqrt(2.)*(ray.GetX()-ray.GetY());
      
      if( TMath::Abs(xdet) < 19./2. && TMath::Abs(ydet) < 19./2. ) {
	accepted++;
	
	SensorXY->Fill(xdet,ydet); 
	
	vector<double> xt;vector<double> yt;vector<double> zt;
	ray.GetTrajectory(xt,yt,zt);
	
	for(int i = 0; i < xt.size(); i++ ) {
  //	  YZ->Fill(zt[i],yt[i]);
  //	  XZ->Fill(zt[i],xt[i]);

	  if( i < xt.size()-1 ) { // Fill points until next
            for( int indx = 0; indx < 200.;indx++ ) {
              double zl = (zt[i+1]-zt[i])/200.*indx+zt[i];
	      double yl = (yt[i+1]-yt[i])/(zt[i+1]-zt[i])*(zl-zt[i])+yt[i];
	      double xl = (xt[i+1]-xt[i])/(zt[i+1]-zt[i])*(zl-zt[i])+xt[i];
	      YZ->Fill(zl,yl);
	      XZ->Fill(zl,xl);
	    }
	  } 
	}
	
	
      }
    }
  
    TCanvas *cR = new TCanvas("cR","  ",1200,1200);
    cR->Divide(1,2);
    cR->cd(1);
    gPad->SetLogz();
    YZ->GetYaxis()->SetTitle("Y(mm)");
    YZ->GetXaxis()->SetTitle("Z(mm)");
    YZ->Draw("color");
    cR->cd(2);
    gPad->SetLogz();
    XZ->GetYaxis()->SetTitle("X(mm)");
    XZ->GetXaxis()->SetTitle("Z(mm)");
    XZ->Draw("color");
    cR->Update();


    TCanvas *cM = new TCanvas("cM","  ",600,1200);
    cM->Divide(1,2);
    cM->cd(1);
    Mag->Draw("color");
    cM->cd(2);
    Mag2D->Fit("pol1");
    Mag2D->Draw("color");
    cM->Update();
    

    TCanvas *cP = new TCanvas("cP","  ",600,600);
    cP->cd();
    SensorXY->Draw("color");
    cP->Update();


    std::cout << " Fraction accepted " << (double)accepted/(double)total << std::endl;

    double dedx = 0.2; // Mev/mm
    
    
    std::cout << " Numbe of phtons " << 10000.*(dedx*length)*(double)accepted/(double)total*0.3 << std::endl;
    
    return 0.;
}
