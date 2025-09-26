#ifdef __CLING__
#pragma cling optimize(0)
#endif
void PhtPerChannel_LensPos()
{
//=========Macro generated from canvas: c_PhtVsPos/Phot/Ch vs Pos
//=========  (Tue Mar 21 15:23:52 2023) by ROOT version 6.26/06
   TCanvas *c_PhtVsPos = new TCanvas("c_PhtVsPos", "Phot/Ch vs Pos",517,115,800,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptTitle(0);
   c_PhtVsPos->Range(14.72973,-1.713986,230.2703,50.75416);
   c_PhtVsPos->SetFillColor(0);
   c_PhtVsPos->SetBorderMode(0);
   c_PhtVsPos->SetBorderSize(2);
   c_PhtVsPos->SetTickx(1);
   c_PhtVsPos->SetTicky(1);
   c_PhtVsPos->SetLeftMargin(0.13);
   c_PhtVsPos->SetRightMargin(0.13);
   c_PhtVsPos->SetTopMargin(0.05);
   c_PhtVsPos->SetBottomMargin(0.16);
   c_PhtVsPos->SetFrameBorderMode(0);
   c_PhtVsPos->SetFrameBorderMode(0);

   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("");
   Double_t off = 12.5;

   Double_t PhtVsPos_fx1[30] = {
   50,
   55,
   60,
   65,
   70,
   75,
   80,
   85,
   90,
   95,
   100,
   105,
   110,
   115,
   120,
   125,
   130,
   135,
   140,
   145,
   150,
   155,
   160,
   165,
   170,
   175,
   180,
   185,
   190,
   195};
   Double_t PhtVsPos_fy1[30] = {
   38.29,
   41.37,
   41.32667,
   40.80333,
   39.92,
   38.82167,
   36.03833,
   38.01667,
   35.75833,
   34.89167,
   35.25333,
   34.29333,
   33.73,
   32.615,
   30.225,
   31.36667,
   29.78167,
   29.135,
   28.59167,
   27.655,
   26.815,
   26.895,
   26.51333,
   25.76333,
   24.89,
   23.9,
   23.69333,
   23.49,
   21.81667,
   21.07667};
   for (int i(0); i < 30; i++){
     PhtVsPos_fy1[i]+=off;
   }
   TGraph *graph = new TGraph(30,PhtVsPos_fx1,PhtVsPos_fy1);
   graph->SetName("PhtVsPos");
   graph->SetTitle("4427-40 ");
   graph->SetFillStyle(1000);
   graph->SetLineColor(4);
   graph->SetLineWidth(4);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000000");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(3);
   graph->SetMarkerSize(1.5);

   TH1F *Graph_PhtVsPos1 = new TH1F("Graph_PhtVsPos1","4427-40 ",100,35.5,209.5);
   Graph_PhtVsPos1->SetMinimum(19.04733);
   Graph_PhtVsPos1->SetMaximum(43.39933);
   Graph_PhtVsPos1->SetDirectory(0);
   Graph_PhtVsPos1->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_PhtVsPos1->SetLineColor(ci);
   Graph_PhtVsPos1->GetXaxis()->SetTitle("Distance from PEN [mm]");
   Graph_PhtVsPos1->GetXaxis()->SetLabelFont(42);
   Graph_PhtVsPos1->GetXaxis()->SetTitleOffset(0.5);
   Graph_PhtVsPos1->GetXaxis()->SetTitleFont(42);
   Graph_PhtVsPos1->GetYaxis()->SetTitle("Photon Per Channel");
   Graph_PhtVsPos1->GetYaxis()->SetLabelFont(42);
   Graph_PhtVsPos1->GetYaxis()->SetTitleFont(42);
   Graph_PhtVsPos1->GetZaxis()->SetLabelFont(42);
   Graph_PhtVsPos1->GetZaxis()->SetTitleOffset(1);
   Graph_PhtVsPos1->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_PhtVsPos1);

   multigraph->Add(graph,"");

   Double_t PhtVsPos_fx2[30] = {
   50,
   55,
   60,
   65,
   70,
   75,
   80,
   85,
   90,
   95,
   100,
   105,
   110,
   115,
   120,
   125,
   130,
   135,
   140,
   145,
   150,
   155,
   160,
   165,
   170,
   175,
   180,
   185,
   190,
   195};

   Double_t PhtVsPos_fy2[30] = {
   41.115,
   36.31167,
   33.63,
   33.24333,
   30.24333,
   28.78167,
   28.68167,
   25.03167,
   25.35833,
   25.11833,
   23.31,
   21.75667,
   20.71,
   19.80167,
   19.055,
   18.43833,
   17.51333,
   17.295,
   16.48667,
   15.39,
   15.63833,
   14.57833,
   14.58333,
   13.88167,
   13.87833,
   13.42833,
   12.45833,
   12.64,
   11.76167,
   11.8};
   for (int i(0); i < 30; i++){
     PhtVsPos_fy2[i]+=off;
   }
   graph = new TGraph(30,PhtVsPos_fx2,PhtVsPos_fy2);
   graph->SetName("PhtVsPos");
   graph->SetTitle("2727-6 ");
   graph->SetFillStyle(1000);
   graph->SetLineColor(6);
   graph->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(3);
   graph->SetMarkerSize(1.5);

   TH1F *Graph_PhtVsPos2 = new TH1F("Graph_PhtVsPos2","2727-6 ",100,35.5,209.5);
   Graph_PhtVsPos2->SetMinimum(8.826333);
   Graph_PhtVsPos2->SetMaximum(44.05033);
   Graph_PhtVsPos2->SetDirectory(0);
   Graph_PhtVsPos2->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_PhtVsPos2->SetLineColor(ci);
   Graph_PhtVsPos2->GetXaxis()->SetTitle("Distance from PEN [mm]");
   Graph_PhtVsPos2->GetXaxis()->SetLabelFont(42);
   Graph_PhtVsPos2->GetXaxis()->SetTitleOffset(0.5);
   Graph_PhtVsPos2->GetXaxis()->SetTitleFont(42);
   Graph_PhtVsPos2->GetYaxis()->SetTitle("Photon Per Channel");
   Graph_PhtVsPos2->GetYaxis()->SetLabelFont(42);
   Graph_PhtVsPos2->GetYaxis()->SetTitleFont(42);
   Graph_PhtVsPos2->GetZaxis()->SetLabelFont(42);
   Graph_PhtVsPos2->GetZaxis()->SetTitleOffset(1);
   Graph_PhtVsPos2->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_PhtVsPos2);

   multigraph->Add(graph,"");

   Double_t PhtVsPos_fx3[30] = {
   50,
   55,
   60,
   65,
   70,
   75,
   80,
   85,
   90,
   95,
   100,
   105,
   110,
   115,
   120,
   125,
   130,
   135,
   140,
   145,
   150,
   155,
   160,
   165,
   170,
   175,
   180,
   185,
   190,
   195};
   Double_t PhtVsPos_fy3[30] = {
   46.24667,
   40.79333,
   38.73167,
   33.98333,
   35.90667,
   34.255,
   28.35167,
   30.01333,
   28.25667,
   27.425,
   26.08833,
   24.51333,
   23.61167,
   23.55,
   22.76,
   21.86833,
   19.83,
   19.98333,
   19.49333,
   19.02833,
   18.375,
   17.22167,
   17.06833,
   16.745,
   16.49167,
   15.75833,
   15.25167,
   14.02333,
   14.545,
   14.425};
   for (int i(0); i < 30; i++){
     PhtVsPos_fy3[i]+=off;
   }
   graph = new TGraph(30,PhtVsPos_fx3,PhtVsPos_fy3);
   graph->SetName("PhtVsPos");
   graph->SetTitle("2727-13 ");
   graph->SetFillStyle(1000);
   graph->SetLineColor(7);
   graph->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(3);
   graph->SetMarkerSize(1.5);

   TH1F *Graph_PhtVsPos3 = new TH1F("Graph_PhtVsPos3","2727-13 ",100,35.5,209.5);
   Graph_PhtVsPos3->SetMinimum(10.801);
   Graph_PhtVsPos3->SetMaximum(49.469);
   Graph_PhtVsPos3->SetDirectory(0);
   Graph_PhtVsPos3->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_PhtVsPos3->SetLineColor(ci);
   Graph_PhtVsPos3->GetXaxis()->SetTitle("Distance from PEN [mm]");
   Graph_PhtVsPos3->GetXaxis()->SetLabelFont(42);
   Graph_PhtVsPos3->GetXaxis()->SetTitleOffset(0.5);
   Graph_PhtVsPos3->GetXaxis()->SetTitleFont(42);
   Graph_PhtVsPos3->GetYaxis()->SetTitle("Photon Per Channel");
   Graph_PhtVsPos3->GetYaxis()->SetLabelFont(42);
   Graph_PhtVsPos3->GetYaxis()->SetTitleFont(42);
   Graph_PhtVsPos3->GetZaxis()->SetLabelFont(42);
   Graph_PhtVsPos3->GetZaxis()->SetTitleOffset(1);
   Graph_PhtVsPos3->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_PhtVsPos3);

   multigraph->Add(graph,"");

   Double_t PhtVsPos_fx4[30] = {
   50,
   55,
   60,
   65,
   70,
   75,
   80,
   85,
   90,
   95,
   100,
   105,
   110,
   115,
   120,
   125,
   130,
   135,
   140,
   145,
   150,
   155,
   160,
   165,
   170,
   175,
   180,
   185,
   190,
   195};
   Double_t PhtVsPos_fy4[30] = {
   35.695,
   37.29,
   37.69,
   37.24,
   37.25333,
   36.025,
   35.28,
   34.115,
   32.60333,
   31.475,
   30.19167,
   28.855,
   27.99,
   26.935,
   26.03167,
   24.93333,
   24.21167,
   22.56167,
   22.58167,
   21.28333,
   20.35167,
   20.61833,
   20.13333,
   19.16667,
   18.62667,
   17.045,
   17.40167,
   16.95333,
   15.91,
   16.20167};
   for (int i(0); i < 30; i++){
     PhtVsPos_fy4[i]+=off;
   }
   graph = new TGraph(30,PhtVsPos_fx4,PhtVsPos_fy4);
   graph->SetName("PhtVsPos");
   graph->SetTitle("4444-16 ");
   graph->SetFillStyle(1000);
   graph->SetLineColor(8);
   graph->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(3);
   graph->SetMarkerSize(1.5);

   TH1F *Graph_PhtVsPos4 = new TH1F("Graph_PhtVsPos4","4444-16 ",100,35.5,209.5);
   Graph_PhtVsPos4->SetMinimum(13.732);
   Graph_PhtVsPos4->SetMaximum(39.868);
   Graph_PhtVsPos4->SetDirectory(0);
   Graph_PhtVsPos4->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_PhtVsPos4->SetLineColor(ci);
   Graph_PhtVsPos4->GetXaxis()->SetTitle("Distance from PEN [mm]");
   Graph_PhtVsPos4->GetXaxis()->SetLabelFont(42);
   Graph_PhtVsPos4->GetXaxis()->SetTitleOffset(0.5);
   Graph_PhtVsPos4->GetXaxis()->SetTitleFont(42);
   Graph_PhtVsPos4->GetYaxis()->SetTitle("Photon Per Channel");
   Graph_PhtVsPos4->GetYaxis()->SetLabelFont(42);
   Graph_PhtVsPos4->GetYaxis()->SetTitleFont(42);
   Graph_PhtVsPos4->GetZaxis()->SetLabelFont(42);
   Graph_PhtVsPos4->GetZaxis()->SetTitleOffset(1);
   Graph_PhtVsPos4->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_PhtVsPos4);

   multigraph->Add(graph,"");

   Double_t PhtVsPos_fx5[30] = {
   50,
   55,
   60,
   65,
   70,
   75,
   80,
   85,
   90,
   95,
   100,
   105,
   110,
   115,
   120,
   125,
   130,
   135,
   140,
   145,
   150,
   155,
   160,
   165,
   170,
   175,
   180,
   185,
   190,
   195};
   Double_t PhtVsPos_fy5[30] = {
   35.77,
   32.59833,
   32.43167,
   27.72333,
   26.04167,
   25.80667,
   22.37833,
   23.005,
   22.125,
   21.09167,
   19.60667,
   19.26167,
   17.39667,
   17.56667,
   16.78833,
   15.785,
   15.35833,
   14.99667,
   13.515,
   13.92333,
   13.455,
   13.01,
   12.4,
   12.04167,
   11.47333,
   10.895,
   10.39333,
   9.646667,
   8.886667,
   8.565};
   for (int i(0); i < 30; i++){
     PhtVsPos_fy5[i]+=off;
   }
   graph = new TGraph(30,PhtVsPos_fx5,PhtVsPos_fy5);
   graph->SetName("PhtVsPos");
   graph->SetTitle("2718-5 ");
   graph->SetFillStyle(1000);
   graph->SetLineColor(20);
   graph->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(3);
   graph->SetMarkerSize(1.5);

   TH1F *Graph_PhtVsPos5 = new TH1F("Graph_PhtVsPos5","2718-5 ",100,35.5,209.5);
   Graph_PhtVsPos5->SetMinimum(5.8445);
   Graph_PhtVsPos5->SetMaximum(38.4905);
   Graph_PhtVsPos5->SetDirectory(0);
   Graph_PhtVsPos5->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_PhtVsPos5->SetLineColor(ci);
   Graph_PhtVsPos5->GetXaxis()->SetTitle("Distance from PEN [mm]");
   Graph_PhtVsPos5->GetXaxis()->SetLabelFont(42);
   Graph_PhtVsPos5->GetXaxis()->SetTitleOffset(0.5);
   Graph_PhtVsPos5->GetXaxis()->SetTitleFont(42);
   Graph_PhtVsPos5->GetYaxis()->SetTitle("Photon Per Channel");
   Graph_PhtVsPos5->GetYaxis()->SetLabelFont(42);
   Graph_PhtVsPos5->GetYaxis()->SetTitleFont(42);
   Graph_PhtVsPos5->GetZaxis()->SetLabelFont(42);
   Graph_PhtVsPos5->GetZaxis()->SetTitleOffset(1);
   Graph_PhtVsPos5->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_PhtVsPos5);

   multigraph->Add(graph,"");
   multigraph->Draw("AL*");
   multigraph->GetXaxis()->SetLimits(42.75, 202.25);
   multigraph->GetXaxis()->SetTitle("Lens position (mm)");
   multigraph->GetXaxis()->SetLabelFont(132);
   multigraph->GetXaxis()->SetLabelSize(0.05);
   multigraph->GetXaxis()->SetTitleSize(0.06);
   multigraph->GetXaxis()->SetTitleOffset(1);
   multigraph->GetXaxis()->SetTitleFont(132);
   multigraph->GetYaxis()->SetTitle("Maximum photons per channel");
   multigraph->GetYaxis()->SetLabelFont(132);
   multigraph->GetYaxis()->SetLabelSize(0.05);
   multigraph->GetYaxis()->SetTitleSize(0.06);
   multigraph->GetYaxis()->SetTitleOffset(1);
   multigraph->GetYaxis()->SetTitleFont(132);

   TLegend *leg = new TLegend(0.5902256,0.6156522,0.8082707,0.8991304,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph_PhtVsPos1","4427-40 ","lpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(4);
   entry->SetLineStyle(1);
   entry->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(3);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph_PhtVsPos2","2727-6 ","lpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(6);
   entry->SetLineStyle(1);
   entry->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(3);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph_PhtVsPos3","2727-13 ","lpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(7);
   entry->SetLineStyle(1);
   entry->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(3);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph_PhtVsPos4","4444-16 ","lpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(8);
   entry->SetLineStyle(1);
   entry->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(3);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph_PhtVsPos5","2718-5 ","lpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(20);
   entry->SetLineStyle(1);
   entry->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(3);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   leg->Draw();
   c_PhtVsPos->Modified();
   c_PhtVsPos->cd();
   c_PhtVsPos->SetSelected(c_PhtVsPos);
}
