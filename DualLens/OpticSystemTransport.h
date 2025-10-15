#include "TROOT.h"
#include "TMath.h"
#include "TMatrixD.h"
#include <iostream>
#include "Ray.h"
#include "Surface.h"

#ifndef __OPTICS__
#define __OPTICS__

class Element {

 public:
  int m_id;

 Element(int id): m_id( id ) {;}

  int getId() const { return m_id; }


};

class Cube: public Element {
  private:
   double half_side;
   double posz; // Center of the window
   double width; // Width of the window
   PlanarSquareSurface *inputsurface;
   PlanarSquareSurface *outputsurface;
   double indexrefraction;
   bool debug;
 
  public:
     Cube(double posz0, double width0, double half_side0,  double indexrefraction0, int id = 0 ):Element(id){
     posz = posz0;
     width = width0;
     half_side = half_side0;
     indexrefraction = indexrefraction0;
     debug = false;
 
     inputsurface = new PlanarSquareSurface(posz-width/2.,half_side);
     outputsurface = new PlanarSquareSurface(posz+width/2.,half_side);
   }
 
   void SetDebug(bool a ) {
     debug = a;
     inputsurface->SetDebug(debug);
     outputsurface->SetDebug(debug);
   }
 
   bool Transport( Ray &ray ){
 
     double outsideindexrefraction = ray.GetIdxR();
     if (ray.GetZ() < posz - width/2.){
       if( ! inputsurface->Transport(ray) ) return false;
       if( ! inputsurface->Refraction(ray,indexrefraction) ) return false;
     } else {
       ray.SetIdxR(indexrefraction);
     }
    
     if( ! outputsurface->Transport(ray) ) return false;
     if( ! outputsurface->Refraction(ray,outsideindexrefraction) ) return false;
    

     return true;
   }
 };

class Disc: public Element {
 private:
  double TR;
  double posz; // Center of the window
  double width; // Width of the window
  PlanarSurface *inputsurface;
  PlanarSurface *outputsurface;
  double indexrefraction;
  bool debug;

 public:
    Disc(double posz0, double width0, double TR0,  double indexrefraction0, int id = 0 ):Element(id){
    posz = posz0;
    width = width0;
    TR = TR0;
    indexrefraction = indexrefraction0;
    debug = false;

    inputsurface = new PlanarSurface(posz-width/2.,TR);
    outputsurface = new PlanarSurface(posz+width/2.,TR);
  }

  void SetDebug(bool a ) {
    debug = a;
    inputsurface->SetDebug(debug);
    outputsurface->SetDebug(debug);
  }

  bool Transport( Ray &ray ){

    double outsideindexrefraction = ray.GetIdxR();
    if (ray.GetZ() < posz - width/2.){
      if( ! inputsurface->Transport(ray) ) return false;
      if( ! inputsurface->Refraction(ray,indexrefraction) ) return false;
    } else {
      ray.SetIdxR(indexrefraction);
    }

    if( ! outputsurface->Transport(ray) ) return false;

    if( ! outputsurface->Refraction(ray,outsideindexrefraction) ) return false;

    return true;
  }
};

class Lens: public Element {
 private:
  double indexrefraction;
  double TR;
  double R;
  double posz; // Center of the lense at center
  double width; // Width of the lense at center
  SphericalSurface *inputsurface;
  SphericalSurface *outputsurface;
  bool debug;

 public:
    Lens(double posz0, double width0, double R0, double TR0,  double indexrefraction0, int id = 0 ):Element(id) {

    posz = posz0;
    width = width0;
    TR = TR0;
    R = R0;
    indexrefraction = indexrefraction0;
    debug = false;

    inputsurface = new SphericalSurface(posz-width/2.+R,R,TR);
    outputsurface = new SphericalSurface(posz+width/2.-R,R,TR);
  }
  //Get/Set Methodsl
  double GetApRad(){
    return TR;
  }

  double GetLensPos(){
    return posz;
  }

  double GetThickness(){
    return width;
  }
  double GetFocalLength() {
    double inverse_f = (indexrefraction - 1)*(1/R +1/R);
    return 1/inverse_f;
  }

  void SetDebug(bool a ) {
    debug = a;
    inputsurface->SetDebug(debug);
    outputsurface->SetDebug(debug);
  }

  bool Transport( Ray &ray ){

    double outsideindexrefraction = ray.GetIdxR();

    if( ! inputsurface->Transport(ray) ) return false;

    if( ! inputsurface->Refraction(ray,indexrefraction) ) return false;

    if( ! outputsurface->Transport(ray) ) return false;

    if( ! outputsurface->Refraction(ray,outsideindexrefraction) ) return false;

    return true;
  }
};


class PlaneConvexLens: public Element {
  private:
   double indexrefraction;
   double TR;
   double R;
   double posz; // Center of the lense at center
   double width; // Width of the lense at center
   PlanarSurface *inputsurface;
   SphericalSurface *outputsurface;
   bool debug;
 
  public:
     PlaneConvexLens(double posz0, double width0, double R0, double TR0,  double indexrefraction0, int id = 0 ):Element(id) {
 
     posz = posz0;
     width = width0;
     TR = TR0;
     R = R0;
     indexrefraction = indexrefraction0;
     debug = false;
 
    //  inputsurface = new SphericalSurface(posz-width/2.+R,R,TR);
    inputsurface = new PlanarSurface(posz-width/2.,TR);
    outputsurface = new SphericalSurface(posz+width/2.-R,R,TR);
   }
   //Get/Set Methodsl
   double GetApRad(){
     return TR;
   }
 
   double GetLensPos(){
     return posz;
   }
 
   double GetThickness(){
     return width;
   }
   double GetFocalLength() {
     double inverse_f = (indexrefraction - 1)*(1/R);
     return 1/inverse_f;
   }
 
   void SetDebug(bool a ) {
     debug = a;
     inputsurface->SetDebug(debug);
     outputsurface->SetDebug(debug);
   }
 
   bool Transport( Ray &ray ){
 
     double outsideindexrefraction = ray.GetIdxR();
 
     if( ! inputsurface->Transport(ray) ) return false;
 
     if( ! inputsurface->Refraction(ray,indexrefraction) ) return false;
 
     if( ! outputsurface->Transport(ray) ) return false;
 
     if( ! outputsurface->Refraction(ray,outsideindexrefraction) ) return false;
 
     return true;
   }
 
 };


class Aperture: public Element {
 private:
  double TR;
  double posz; // Center of the window
  double width; // Width of the window
  PlanarSurface *inputsurface;
  PlanarSurface *outputsurface;
  bool debug;

 public:
    Aperture(double posz0, double width0, double TR0, int id = 0 ):Element(id){
    posz = posz0;
    width = width0;
    TR = TR0;
    debug = false;
    inputsurface = new PlanarSurface(posz-width/2.,TR);
    outputsurface = new PlanarSurface(posz+width/2.,TR);
  }
  double GetPos(){
    return posz;
  }

  double GetWidth(){
    return width;
  }

  double GetTR(){
    return TR; 
  }

  void SetDebug(bool a ) {
    debug = a;
    inputsurface->SetDebug(debug);
    outputsurface->SetDebug(debug);
  }

  bool Transport( Ray &ray ){

    double outsideindexrefraction = ray.GetIdxR();

    if( ! inputsurface->Transport(ray) ) return false;
    if( ! outputsurface->Transport(ray) ) return false;

    return true;
  }
};

#endif
