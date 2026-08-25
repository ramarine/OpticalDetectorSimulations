#include "OpticSystemTransport.h"
#include "TRandom.h"
#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TProfile.h"
#include "TCanvas.h"


void Debug(int i=0){
    std::cout << " DEBUG DEBUG DEBUG " << i << std::endl;
}

double SimpleTest(void){
  
    double size = 200.; double lensposition = 0.; double sensorpos = 0.;
    bool debug = false;
    TFile *graphs = new TFile("graphs.root", "UPDATE");
  
    TRandom r;
    
    Cube ECube(-50.0,100.0,50.0,1.58,0);

    // ConvexPlaneLens(double posz0, double width0, double R0, double TR0,  double indexrefraction0, int id = 0 )
#if 0 
    // 50x75 planoconvex lense
    double width1 = 11.0;
    double pos1 = width1/2.;
    double Radious1 = 38.76;
    double Diameter1 = 50.;
    
    // 50x100 planoconvex lense
    double width1 = 10.0;
    double pos1 = width1/2.;
    double Radious1 = 51.68;
    double Diameter1 = 50.;
    double Index1 = 1.52; // N-BK
#endif
    // 100x300 planoconvex lense
    double width1 = 10.0;
    double pos1 = width1/2.;
    double Radious1 = 103.36;
    double Diameter1 = 100.;
    double Index1 = 1.52; // N-BK

    ConvexPlaneLens ELens(pos1,width1,Radious1,Diameter1/2.,Index1,1);

    double posApp = pos1+width1/2.+50.;
    
    Aperture App(posApp,0.1,10.,2); 
    
#if 0    
    // CCX 25x25
    double pos2 = pos1+150.;
    double width2 = 5.5;
    double Radious2 = 39.22;
    double Diameter2 = 25.;
    double Index2 = 1.52; // N-BK
    Lens ELens2(pos2,width2,Radious2,Diameter2/2.,Index2,2);
   // 25x40
    double width2 = 5.6;
    double pos2 = pos1+260.;
    double Radious2 = 20.67;
    double Diameter2 = 25.;
    double Index2 = 1.52; // N-BK
    PlaneConvexLens ELens2(pos2,width2,Radious2,Diameter2/2.,Index2,2);
    // 40x80
    double width2 = 8.0;
    double pos2 = pos1+290.;
    double Radious2 = 41.34;
    double Diameter2 = 40.;
    double Index2 = 1.52; // N-BK
    
#endif
    // PCX 25x25
    double pos2 = pos1+100.;
    double width2 = 8.0;
    double Radious2 = 16.82;
    double Diameter2 = 25.;
    double Index2 = 1.52; // N-BK
    PlaneConvexLens ELens2(pos2,width2,Radious2,Diameter2/2.,Index2,3);
    
    int total = 1e+6;
    int accepted = 0;

    double length = 100.;

    TH2D *SensorXY = new TH2D("Sensorxy"," ",16,-20,20,16,-20,20);

    double SensorPos = pos2+15.;
    double ObjectPos = -50.;

    TH2D *RZ = new TH2D("rz"," ",1000,-1.,SensorPos*(1.1),100,-60,60);
     
    for(int i = 0; i < total; i++ ) {

      double costheta = r.Uniform(0.,1.);
      double phi = r.Uniform(0,2.*3.141592);
      double sintheta = TMath::Sqrt(1.-(costheta*costheta));
      double vx = sintheta*TMath::Cos(phi), vy = sintheta*TMath::Sin(phi), vz = costheta;
      double y = r.Uniform(-length/2.,length/2.);
      double x = 0;
      double z = ObjectPos;
      
      Ray ray(x, y, z, vx, vy, vz, 1.);

      RZ->Fill(ray.GetZ(),ray.GetY());
      
      if (!ECube.Transport(ray)) continue;
      
      RZ->Fill(ray.GetZ(),ray.GetY());
      
      if (!ELens.Transport(ray)) continue;
      RZ->Fill(ray.GetZ(),ray.GetY());

      for(double zp = pos1+width1/2.;zp < posApp-0.001;zp+=(posApp-pos1-width1/2.)/100.){ 
        ray.Transport(zp);
        RZ->Fill(ray.GetZ(),ray.GetY());
      }

      if (!App.Transport(ray)) continue;
  
      for(double zp = posApp;zp < pos2-width2/2.;zp+=(pos2-width2/2.-posApp)/100.){ 
	ray.Transport(zp);
	RZ->Fill(ray.GetZ(),ray.GetY());
      }
          
      if (!ELens2.Transport(ray)) continue;
      RZ->Fill(ray.GetZ(),ray.GetY());

      for(double zp = pos2+width2/2.;zp < SensorPos;zp+=(SensorPos-pos2-width1/2.)/100.){ 
	ray.Transport(zp);
	RZ->Fill(ray.GetZ(),ray.GetY());
      }
      
      ray.Transport(SensorPos);
      SensorXY->Fill(ray.GetX(),ray.GetY()); 
      RZ->Fill(ray.GetZ(),ray.GetY());

      if( TMath::Abs(ray.GetX()) < 20. && TMath::Abs(ray.GetY()) < 20. )  accepted++; 
      
    }

    TCanvas *cR = new TCanvas("cR","  ",600,600);
    cR->cd();
    RZ->Draw("color");
    cR->Update();

    TCanvas *cP = new TCanvas("cP","  ",600,600);
    cP->cd();
    SensorXY->Draw("color");
    cP->Update();


    std::cout << " Fraction accepted " << (double)accepted/(double)total << std::endl;

    double dedx = 0.2; // Mev/mm
    
    
    std::cout << " Numbe of phtons " << 10000./2.*(dedx*length)*(double)accepted/(double)total << std::endl;
    
    return 0.;
}
