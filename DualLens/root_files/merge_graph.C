
#include "TRandom.h"
#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TGraph.h"


void merge_graph(){



  TMultiGraph *mg_PhtVsPos = new TMultiGraph();
  TMultiGraph *mg_PhtVsEff_Mag = new TMultiGraph();
  TMultiGraph *mg_LensAccMagVsPos = new TMultiGraph();
  TMultiGraph *mg_MagVsPos = new TMultiGraph();
  TMultiGraph *mg_LensAccVsPos = new TMultiGraph();
  TMultiGraph *mg_AberrVsPos = new TMultiGraph();
  TMultiGraph *mg_MagVsPht= new TMultiGraph();
  //loop on your files reading each TGraph and add it to the TMultiGraph
  std::vector<TFile*> file_store;
  TFile *f1;
  f1 = TFile::Open("graphs_4427-11.root");
  TFile *f2;
  f2 = TFile::Open("graphs_4427-20.root");
  TFile *f3;
  f3 = TFile::Open("graphs_4427-30.root");
  TFile *f4;
  f4 = TFile::Open("graphs_4427-40.root");

  TFile *f5;
  f5 = TFile::Open("graphs_2727-6.root");
  TFile *f6;
  f6 = TFile::Open("graphs_2727-13.root");

  TFile *f7;
  f7 = TFile::Open("graphs_4444-16.root");

  //TFile *f8;
  //f8 = TFile::Open("graphs_4444-26.root");

  TFile *f8;
  f8 = TFile::Open("graphs_2718-5.root");

  TFile *f9;
  f9 = TFile::Open("graphs_2718-13.root");


  // file_store.push_back(f1);
  // file_store.push_back(f2);
  // file_store.push_back(f3);
  file_store.push_back(f4);
  file_store.push_back(f5);
  file_store.push_back(f6);
  file_store.push_back(f7);
  file_store.push_back(f8);
  // file_store.push_back(f9);

  std::vector<int> postns;
  // postns.push_back(11);//4427
  // postns.push_back(20);//4427
  // postns.push_back(30);//4427
  postns.push_back(40);//4427
  postns.push_back(6);//2727
  postns.push_back(13);//2727
  postns.push_back(16);//2727
  postns.push_back(5);//2727
  // postns.push_back(13);//2727

  std::vector<int> focfoc;
  // focfoc.push_back(4427);
  // focfoc.push_back(4427);
  // focfoc.push_back(4427);
  focfoc.push_back(4427);
  focfoc.push_back(2727);
  focfoc.push_back(2727);
  focfoc.push_back(4444);
  focfoc.push_back(2718);
  // focfoc.push_back(2718);



  std::vector<int> colors;

  // colors.push_back(2);
  // colors.push_back(3);
  // colors.push_back(4);
  colors.push_back(4);
  colors.push_back(6);
  colors.push_back(7);
  colors.push_back(8);
  colors.push_back(20);
  // colors.push_back(23);
  for ( int i(0); i< file_store.size(); i++){


    std::vector<double> Mag;
    std::vector<double> Pht;
    std::vector<double> Pos;





    TGraph* PhtVsPos;
    file_store.at(i)->GetObject("PhtVsPos", PhtVsPos);
    PhtVsPos->SetName("PhtVsPos");
    PhtVsPos->SetLineColor(colors.at(i));
    PhtVsPos->SetTitle(Form("%d-%d " , focfoc.at(i),postns.at(i) ));



    TGraph* PhtVsEff_Mag;
    file_store.at(i)->GetObject("PhtVsEff-Mag", PhtVsEff_Mag);
    PhtVsEff_Mag->SetName("PhtVsEff_Mag");
    PhtVsEff_Mag->SetLineColor(colors.at(i));
    PhtVsEff_Mag->SetTitle(Form("%d-%d " , focfoc.at(i),postns.at(i) ));

    TGraph* LensAccMagVsPos;
    file_store.at(i)->GetObject("LensAccMagVsPos", LensAccMagVsPos);
    LensAccMagVsPos->SetName("LensAccMagVsPos");
    LensAccMagVsPos->SetLineColor(colors.at(i));
    LensAccMagVsPos->SetTitle(Form("%d-%d " ,postns.at(i), focfoc.at(i) ));

    TGraph* MagVsPos;
    file_store.at(i)->GetObject("MagVsPos", MagVsPos);
    MagVsPos->SetName("MagVsPos");
    MagVsPos->SetLineColor(colors.at(i));
    MagVsPos->SetTitle(Form("%d-%d " , focfoc.at(i),postns.at(i) ));

    TGraph* LensAccVsPos;
    file_store.at(i)->GetObject("LensAccVsPos", LensAccVsPos);
    LensAccVsPos->SetName("LensAccVsPos");
    LensAccVsPos->SetLineColor(colors.at(i));
    LensAccVsPos->SetTitle(Form("%d-%d " , focfoc.at(i),postns.at(i) ));


    TGraph* AberrVsPos;
    file_store.at(i)->GetObject("AberrVsPos", AberrVsPos);
    AberrVsPos->SetName("AberrVsPos");
    AberrVsPos->SetLineColor(colors.at(i));
    AberrVsPos->SetTitle(Form("%d-%d " , focfoc.at(i),postns.at(i) ));


    double x(0.), y(0.), z(0);



    for (int j(0); j < PhtVsPos->GetMaxSize(); j++){
      PhtVsPos->GetPoint(j,x,y);
      Pos.push_back(x);
      Pht.push_back(y);
      MagVsPos->GetPoint(j,x,z);
      Mag.push_back(z);

    }
    TGraph* MagVsPht = new TGraph (PhtVsPos->GetMaxSize(), &Mag[0], &Pht[0] );
    MagVsPht->SetName("MagVsPht");
    MagVsPht->SetLineColor(colors.at(i));
    MagVsPht->SetLineWidth(3);
    MagVsPht->SetTitle(Form("%d-%d " , focfoc.at(i),postns.at(i) ));

    PhtVsPos->GetXaxis()->SetTitleOffset(0.5);
    PhtVsPos->SetMarkerColorAlpha(kBlack,1);
    PhtVsEff_Mag->SetMarkerColorAlpha(kBlack,1);
    LensAccMagVsPos->SetMarkerColorAlpha(kBlack,1);
    MagVsPos->SetMarkerColorAlpha(kBlack,1);
    LensAccVsPos->SetMarkerColorAlpha(kBlack,1);
    AberrVsPos->SetMarkerColorAlpha(kBlack,1);
    MagVsPht->SetMarkerColorAlpha(kBlack,1);

    mg_PhtVsPos->Add(PhtVsPos);
    mg_PhtVsEff_Mag->Add(PhtVsEff_Mag);
    mg_LensAccMagVsPos->Add(LensAccMagVsPos);
    mg_MagVsPos->Add(MagVsPos);
    mg_LensAccVsPos->Add(LensAccVsPos);
    mg_AberrVsPos->Add(AberrVsPos);
    mg_MagVsPht->Add(MagVsPht);
  /*
  mg_PhtVsPos
PhtVsEff_Mag
    LensAccMagVsPos
  MagVsPos
  LensAccVsPos
  AberrVsPos
  */

  }
  TCanvas *c_PhtVsPos = new TCanvas("c_PhtVsPos","Phot/Ch vs Pos", 800,600);
  c_PhtVsPos->cd();
  mg_PhtVsPos->GetXaxis()->SetTitle("Lens position (mm)");
  mg_PhtVsPos->GetYaxis()->SetTitle("Maximum photons per channel");

  mg_PhtVsPos->Draw("AL*");//[/code]

  c_PhtVsPos->BuildLegend();

  // TCanvas * c_PhtVsEff_Mag = new TCanvas("c2","", 800,600);
  // mg_PhtVsEff_Mag->Draw("AL*");
  // c_PhtVsEff_Mag->BuildLegend();


  TCanvas * c_LensAccMagVsPos = new TCanvas("c3","", 800,600);
  mg_LensAccMagVsPos->GetXaxis()->SetTitle("Lens position (mm)");
  mg_LensAccMagVsPos->GetYaxis()->SetTitle("Lens acceptance");

  mg_LensAccMagVsPos->Draw("AL*");
  c_LensAccMagVsPos->BuildLegend();

  TCanvas * c_MagVsPos = new TCanvas("c4"," Mag Vs Pos", 800,600);
  mg_MagVsPos->GetXaxis()->SetTitle("Lens position (mm)");
  mg_MagVsPos->GetYaxis()->SetTitle("Magnitude");
  mg_MagVsPos->Draw("AL*");
  c_MagVsPos->BuildLegend();

  TCanvas * c_LensAccVsPos = new TCanvas("c5","", 800,600);
  mg_LensAccVsPos->Draw("AL*");
  c_LensAccVsPos->BuildLegend();

  TCanvas * c_AberrVsPos = new TCanvas("c6","", 800,600);
  mg_AberrVsPos->GetXaxis()->SetTitle("Lens position (mm)");
  mg_AberrVsPos->GetYaxis()->SetTitle(" Mean deviation from true point (mm) ");
  mg_AberrVsPos->Draw("AL*");
  c_AberrVsPos->BuildLegend();

  TCanvas * c_MagVsPht = new TCanvas("c7","", 800,600);
  mg_MagVsPht->GetYaxis()->SetTitle("Photons per channel");
  mg_MagVsPht->GetXaxis()->SetTitle(" Magnitude ");
  mg_MagVsPht->Draw("AL*");
  c_MagVsPht->BuildLegend();




}
