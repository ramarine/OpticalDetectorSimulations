#include "Element.h"
#include "TRandom.h"

#ifndef __CUBE__
#define __CUBE__

class Cube: public Element {
  private:
   double half_side;
   double boxsize; 
   double posz; // Center of the window
   double width; // Width of the window
   PlanarSquareSurface *inputsurface;
   PlanarSquareSurface *outputsurface;
   double indexrefraction;
   bool debug;
   TRandom *r; 
 
  public:
     Cube(double posz0, double width0, double half_side0,  double indexrefraction0, int id = 0 ):Element(id){
     posz = posz0;
     width = width0;
     half_side = half_side0;
     boxsize = 2.*half_side; 
     indexrefraction = indexrefraction0;
     debug = false;

     r = new TRandom();
     
     inputsurface = new PlanarSquareSurface(posz-width/2.,half_side);
     outputsurface = new PlanarSquareSurface(posz+width/2.,half_side);
   }
 
   void SetDebug(bool a ) {
     debug = a;
     inputsurface->SetDebug(debug);
     outputsurface->SetDebug(debug);
   }


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



   bool InternalReflection(Ray &ray,double zpos ) {
     double x = ray.GetX();  double y = ray.GetY(); double z = ray.GetZ();
     double vx = ray.GetVX();  double vy = ray.GetVY(); double vz = ray.GetVZ();
     
     // Get the position when the ray crosses the exit plane
     double lambda = (zpos-z)/vz;
     if( lambda < 0.0 ) return false; // wrong direction. 
     
     // Get the X and Y coordinates
     double xcross = x+vx*lambda;
     double ycross = y+vy*lambda;
     
     ray.Transport(zpos);
          
     // Check how many changes of detector blocks in X and Y
     int nchangesx = (int)((abs(xcross)+half_side)/boxsize);
     int nchangesy = (int)((abs(ycross)+half_side)/boxsize);
     
     if( nchangesx > 0  ) {
       double cos1; 
       double R = ReflFactor2surf(abs(vx),indexrefraction,1,cos1);
       if( R < 1. ) 
	 if( r->Uniform(0.,1.) > TMath::Power(R,nchangesx) ) return false;
     }
     
     if( nchangesy > 0 ) {
       double cos1; 
       double R = ReflFactor2surf(abs(vy),indexrefraction,1,cos1);
       if( R < 1. ) 
	 if( r->Uniform(0.,1.) > TMath::Power(R,nchangesy) ) return false;
     } 
     
     // Build the reflected image
     x = xcross- nchangesx*boxsize*vx/abs(vx); 
     y = ycross- nchangesy*boxsize*vy/abs(vy); 
     z = zpos;
     
     if( nchangesx%2 == 1 ) { vx = -vx; x = -x;}
     if( nchangesy%2 == 1 ) { vy = -vy; y = -y; } 
#if 0 
     if( nchangesx == 1  ) 
       std::cout << nchangesx << "  " << xcross << " -->  " << x << std::endl;
#endif   
     ray.SetPos(x,y,z);
     ray.SetDir(vx,vy,vz);
     
     return true; 
   }
   
   
   bool BackSurfaceReflection( Ray &ray, double zpos){
     
     if( !InternalReflection(ray, zpos ) ) return false;
     
     if( (zpos-ray.GetZ())*ray.GetVZ() < 0.0 ) std::cout << " Error " << ray.GetVZ() << std::endl;
     
     double x = ray.GetX();
     double y = ray.GetY();
     double z = ray.GetZ();
     double vx = ray.GetVX();
     double vy = ray.GetVY();
     double vz = ray.GetVZ();
          
     // We have arrived to the farther surface check for reflexion 	  
     double cos1; 
     double R = ReflFactor2surf(abs(vz),indexrefraction,1,cos1);
     if( R < 1. ) 
       if( r->Uniform(0.,1.) > R ) return false;
     
     x = ray.GetX();  y = ray.GetY(); z = zpos;
     vx = ray.GetVX();  vy = ray.GetVY(); vz = -vz;
     
     ray.SetPos(x,y,z); // ray starts at the reflexion point.
     ray.SetDir(vx,vy,vz);
     
     if( vz < 0 ) 
       std::cout <<"  Error " << vz << std::endl;
     
     return true; 
   }
  
 
   bool Transport( Ray &ray ){


     double outsideindexrefraction = ray.GetIdxR();
     if (ray.GetZ() < posz - width/2. ){  // Outside
       if( ray.GetVZ() > 0. ) { 
	 if( ! inputsurface->Transport(ray) ) return false;   // Geometrical Acceptance 
	 if( ! inputsurface->Refraction(ray,indexrefraction) ) return false;  // Check for Refraction probabilities.
       }
       else
	 return false;
     } else {  // Inside the cube 
       ray.SetIdxR(indexrefraction);
     }
     
     if( ray.GetVZ() < 0.  ) { // backward going tracks 
       if( !BackSurfaceReflection(ray,-boxsize) )
	 return false;
       else 
	 ray.AddPointTrajectory();
     }
     
     if( !InternalReflection(ray,0.) ) return false;        
     
     ray.AddPointTrajectory();
     
     if( ! outputsurface->Transport(ray) ) return false;
     if( ! outputsurface->Refraction(ray,outsideindexrefraction) ) return false;
     ray.AddPointTrajectory();
     
     return true;
   }
 };

#endif 
