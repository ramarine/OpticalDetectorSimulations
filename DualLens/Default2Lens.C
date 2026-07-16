#include "OpticSystemTransport.h"
#include "TRandom.h"
#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TGraph.h"
#include "TProfile.h"
#include "TCanvas.h"


void Debug(int i=0){
    std::cout << " DEBUG DEBUG DEBUG " << i << std::endl;
}

double Default2Lens(double positionparticle = -50.){
  
    double size = 200.; double lensposition = 0.; double sensorpos = 0.;
    bool debug = false;
    TFile *graphs = new TFile("graphs.root", "UPDATE");
  
    TRandom r;

    double IndexCube = 1.58;

    //   IndexCube = 1.;
    
    Cube ECube(-50.0,100.0,50.0,IndexCube,0);

    // Lens at the side of the cube  (50x50) 
    // PlaneConvexLens ECubeLens(12.0/2.,12.0,39.24,50.0/2.,1.52,0);
    // Lens at the side of the cube  (75x75) 
    // PlaneConvexLens ECubeLens(18.86/2.,18.86,73.50,75.0/2.,1.52,0);
    // Lens at the side of the cube  (100x100) 
        PlaneConvexLens ECubePCXLens(20./2.,20.,77.53,100.0/2.,1.52,0);
    // Lens at the side of the cube  (100x200) 
    // PlaneConvexLens ECubeLens(14./2.,14.,103.36,100.0/2.,1.52,0);

	PlaneConcavLens ECubePCVLens(11.3/2.,11.3,51.68,50.0/2.,5.0,1.52,0);
	

    // ConvexPlaneLens(double posz0, double width0, double R0, double TR0,  double indexrefraction0, int id = 0 )

    // 100x300 planoconvex lense
    double width1 = 6.5;
    double pos1 = 7.+14.6+17.26+width1/2.;
    double Radious1 = 45.61;
    double Diameter1 = 30.;
    double Index1 = 1.833;  // N-SF11

    double posApp = pos1-width1/2.;
    
    Aperture App(posApp,0.1,30.,2); 
    
    Lens ELens(pos1,width1,Radious1,Diameter1/2.,Index1,1);

    double pos2 = pos1+5.+width1;
    
    Lens ELens2(pos2,width1,Radious1,Diameter1/2.,Index1,3);
    
    int total = 1e+6;
    int accepted = 0;

    double length = 100.;

    TH2D *SensorXY = new TH2D("Sensorxy"," ",16,-10,10,16,-10,10);

    double SensorPos = pos2+11.7+width1/2.;
    double ObjectPos = positionparticle;

    TH2D *RZ = new TH2D("rz"," ",1000,-1.,SensorPos*(1.1),100,-60,60);
   
    TH1D *Zat0 = new TH1D("zat0"," ",1000,ObjectPos-50.,ObjectPos+120.);
    TH1D *Zat0Sel = new TH1D("zat0Sel"," ",1000,ObjectPos-50.,ObjectPos+120.);

    TH1D *Mag = new TH1D("Mag"," ",1000,0.,2.);
    TH2D *Mag2D = new TH2D("Mag2D"," ",100,-length/2.,length/2.,100,-10.,10.);
    
    
    for(int i = 0; i < total; i++ ) {

      double costheta = r.Uniform(0.,1.);
      double phi = r.Uniform(0,2.*3.141592);
      double sintheta = TMath::Sqrt(1.-(costheta*costheta));
      double vx = sintheta*TMath::Cos(phi), vy = sintheta*TMath::Sin(phi), vz = costheta;
      double y = r.Uniform(-length/2.,length/2.);
      double x = 0;
      double z = ObjectPos;
      
      Ray ray(x, y, z, vx, vy, vz, 1.);
      
      if (!ECube.Transport(ray)) continue;
      //  if (!ECubePCXLens.Transport(ray)) continue;
      if (!ECubePCVLens.Transport(ray)) continue;
      
      // Compute the crossing point with y = 0
      double zat0 = ray.GetZ()+(y-ray.GetY())*ray.GetVZ()/ray.GetVY();
      Zat0->Fill(zat0);
      
      if (!App.Transport(ray)) continue;
      
      if (!ELens.Transport(ray)) continue;

      if (!ELens2.Transport(ray)) continue;

      ray.Transport(SensorPos);
      ray.AddPointTrajectory();
      SensorXY->Fill(ray.GetX(),ray.GetY()); 

      Mag->Fill(TMath::Abs(ray.GetY()/y));
      Mag2D->Fill(y,ray.GetY());

      
      if( TMath::Abs(ray.GetX()) < 10. && TMath::Abs(ray.GetY()) < 10. ) {
	Zat0Sel->Fill(zat0);
	accepted++;
	
	vector<double> xt;vector<double> yt;vector<double> zt;
	ray.GetTrajectory(xt,yt,zt);

	for(int i = 0; i < xt.size(); i++ ) {
	  RZ->Fill(zt[i],yt[i]);

	  if( i < xt.size()-1 ) { // Fill points until next 
	    for( double zl = zt[i];zl < zt[i+1]; zl += (zt[i+1]-zt[i])/200.){
	      double yl = (yt[i+1]-yt[i])/(zt[i+1]-zt[i])*(zl-zt[i])+yt[i];
	      RZ->Fill(zl,yl);
	    }
	  } 
	}

	
      }
    }

    TCanvas *cR = new TCanvas("cR","  ",1200,600);
    cR->cd();
    cR->SetLogz();
    RZ->Draw("color");
    cR->Update();

    TCanvas *cP = new TCanvas("cP","  ",600,600);
    cP->cd();
    SensorXY->Draw("color");
    cP->Update();

    TCanvas *cM = new TCanvas("cM","  ",600,1200);
    cM->Divide(1,2);
    cM->cd(1);
    Mag->Draw("color");
    cM->cd(2);
    Mag2D->Fit("pol1");
    Mag2D->Draw("color");
    cM->Update();
    
    

    std::cout << " Fraction accepted " << (double)accepted/(double)total << std::endl;

    double dedx = 0.2; // Mev/mm
    
    
    std::cout << " Numbe of phtons " << 10000./2.*(dedx*length)*(double)accepted/(double)total*0.3 << std::endl;
    
    return 0.;
}
