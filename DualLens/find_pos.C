#include <iostream>


void find_pos(){
  /*
  double l1 = 100;
  double d = 10;
  double l2 = l1+d;
  double f1 = 27;
  double f2 = 27;
  */

  double l1 = 55;
  double d = 10;
  double l2 = l1+d;
  double f1 = 44;
  double f2 = 27;

  
  double i1 = l1 * f1 / (l1-f1);
  
  double o2 = - (i1 - d); //gets - sign because "an object at the right of the lens gets a negative sign " 

  double i2 = o2*f2/(o2-f2);

  double mag1 = - i1/l1;
  double mag2 = - i2/o2;
  
  cout << " The image 2 is at  " << i2 << " mm  after the second lens" << endl;
  cout << " mag 1 is " << - i1/l1 << endl; 
  cout << " mag 2 is " << - i2 / o2 << endl; // if the magnification is positive then the orientation of the image is in the same size 
  cout << " total mag " << mag1 * mag2 << endl;

  double det_mag = 1/mag1/mag2;
  cout << "our mag " << TMath::Abs(det_mag) << endl;


  TCanvas * c2 = new TCanvas ("c2","",600,600);
  TF1 *Mag_2Lens = new TF1("object/image as a function of space between lenses ", " TMath::Abs(1 / ( ([0]/[1] * (       ((x-[0]) * [2]) / ((x - [0]) *((x-[0]) - [2]))    ))))  ", 6.5,40);
   
  Mag_2Lens->SetParameter(0, i1);// does not depend on d
  Mag_2Lens->SetParameter(1, l1);// does not depend on d
  Mag_2Lens->SetParameter(2, f2);

  Mag_2Lens->SetTitle(Form(" The magnitude of:  f1 = %f and f2=  %f", f1 , f2));
  Mag_2Lens->GetXaxis()->SetTitle("Distance between two lenses");
  Mag_2Lens->GetYaxis()->SetTitle("Magnitude");
  Mag_2Lens->Draw();
  







  /*

  TCanvas * c1 = new TCanvas ("c1","",600,600);
  // TF1 *Mag_1Lens = new TF1("Mag of 1 lens","[0]/ (x - [0]))",30,200);
  TF1 *Mag_1Lens = new TF1("Mag of 1 lens","(x - [0] / [0]) ",30,200);
   
  Mag_1Lens->SetParameter(0, f1);
  Mag_1Lens->SetTitle(Form(" The magnitude of one lens of %f focal distance", f1));
  Mag_1Lens->GetXaxis()->SetTitle("Distance from Object");
  Mag_1Lens->Draw();

  */
  
  
  
  
  
  //  return (i1 - (l2-l1)) * f2 / (i1 - (l2-l1) -f2) ;
  
}
