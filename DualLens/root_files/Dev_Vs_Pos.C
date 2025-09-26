#ifdef __CLING__
#pragma cling optimize(0)
#endif
void Dev_Vs_Pos()
{
//=========Macro generated from canvas: c6/
//=========  (Tue Mar 21 16:22:30 2023) by ROOT version 6.26/06
   TCanvas *c6 = new TCanvas("c6", "",368,101,800,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptTitle(0);
   c6->Range(14.72973,0.7740942,230.2703,6.680951);
   c6->SetFillColor(0);
   c6->SetBorderMode(0);
   c6->SetBorderSize(2);
   c6->SetTickx(1);
   c6->SetTicky(1);
   c6->SetLeftMargin(0.13);
   c6->SetRightMargin(0.13);
   c6->SetTopMargin(0.05);
   c6->SetBottomMargin(0.16);
   c6->SetFrameBorderMode(0);
   c6->SetFrameBorderMode(0);

   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("");
   Double_t off = 9.;

   Double_t AberrVsPos_fx1[30] = {
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
   Double_t AberrVsPos_fy1[30] = {
   1.931301,
   2.056996,
   2.071486,
   2.144829,
   2.182291,
   2.187325,
   2.315741,
   2.300736,
   2.388989,
   2.547839,
   2.44972,
   2.462874,
   2.499445,
   2.595904,
   3.016005,
   2.844048,
   2.946331,
   3.232122,
   3.287151,
   3.382321,
   3.388622,
   3.238367,
   3.337422,
   3.521026,
   3.633392,
   3.860024,
   3.70464,
   3.698042,
   4.081829,
   4.167027};
   for (int i(0); i< 30; i++){
     AberrVsPos_fy1[i]/=off;
   }
   TGraph *graph = new TGraph(30,AberrVsPos_fx1,AberrVsPos_fy1);
   graph->SetName("AberrVsPos");
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

   TH1F *Graph_AberrVsPos1 = new TH1F("Graph_AberrVsPos1","4427-40 ",100,35.5,209.5);
   Graph_AberrVsPos1->SetMinimum(1.707728);
   Graph_AberrVsPos1->SetMaximum(4.3906);
   Graph_AberrVsPos1->SetDirectory(0);
   Graph_AberrVsPos1->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_AberrVsPos1->SetLineColor(ci);
   Graph_AberrVsPos1->GetXaxis()->SetTitle("Position from PEN [mm]");
   Graph_AberrVsPos1->GetXaxis()->SetLabelFont(42);
   Graph_AberrVsPos1->GetXaxis()->SetTitleOffset(1);
   Graph_AberrVsPos1->GetXaxis()->SetTitleFont(42);
   Graph_AberrVsPos1->GetYaxis()->SetTitle(" Mean deviation from true point ");
   Graph_AberrVsPos1->GetYaxis()->SetLabelFont(42);
   Graph_AberrVsPos1->GetYaxis()->SetTitleFont(42);
   Graph_AberrVsPos1->GetZaxis()->SetLabelFont(42);
   Graph_AberrVsPos1->GetZaxis()->SetTitleOffset(1);
   Graph_AberrVsPos1->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_AberrVsPos1);

   multigraph->Add(graph,"");

   Double_t AberrVsPos_fx2[30] = {
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
   Double_t AberrVsPos_fy2[30] = {
   2.136466,
   2.420162,
   2.583022,
   2.492454,
   2.697365,
   2.904308,
   2.746972,
   3.212189,
   3.115793,
   2.858446,
   3.002061,
   3.474324,
   3.656876,
   3.799482,
   4.047516,
   4.148857,
   4.269147,
   3.575154,
   3.994483,
   4.948186,
   4.346003,
   5.111124,
   4.596818,
   4.544978,
   4.164436,
   4.217674,
   4.366915,
   5.017702,
   4.554215,
   5.186256};
   for (int i(0); i< 30; i++){
     AberrVsPos_fy2[i]/=off;
   }
   graph = new TGraph(30,AberrVsPos_fx2,AberrVsPos_fy2);
   graph->SetName("AberrVsPos");
   graph->SetTitle("2727-6 ");
   graph->SetFillStyle(1000);
   graph->SetLineColor(6);
   graph->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(3);
   graph->SetMarkerSize(1.5);

   TH1F *Graph_AberrVsPos2 = new TH1F("Graph_AberrVsPos2","2727-6 ",100,35.5,209.5);
   Graph_AberrVsPos2->SetMinimum(1.831487);
   Graph_AberrVsPos2->SetMaximum(5.491235);
   Graph_AberrVsPos2->SetDirectory(0);
   Graph_AberrVsPos2->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_AberrVsPos2->SetLineColor(ci);
   Graph_AberrVsPos2->GetXaxis()->SetTitle("Position from PEN [mm]");
   Graph_AberrVsPos2->GetXaxis()->SetLabelFont(42);
   Graph_AberrVsPos2->GetXaxis()->SetTitleOffset(1);
   Graph_AberrVsPos2->GetXaxis()->SetTitleFont(42);
   Graph_AberrVsPos2->GetYaxis()->SetTitle(" Mean deviation from true point ");
   Graph_AberrVsPos2->GetYaxis()->SetLabelFont(42);
   Graph_AberrVsPos2->GetYaxis()->SetTitleFont(42);
   Graph_AberrVsPos2->GetZaxis()->SetLabelFont(42);
   Graph_AberrVsPos2->GetZaxis()->SetTitleOffset(1);
   Graph_AberrVsPos2->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_AberrVsPos2);

   multigraph->Add(graph,"");

   Double_t AberrVsPos_fx3[30] = {
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
   Double_t AberrVsPos_fy3[30] = {
   2.135436,
   2.22047,
   2.355903,
   2.715456,
   2.356842,
   2.552865,
   3.306242,
   2.865375,
   2.985238,
   3.18924,
   3.293092,
   3.463578,
   3.594044,
   3.376833,
   3.485935,
   3.609902,
   4.220591,
   3.917279,
   3.546777,
   3.737963,
   3.820653,
   3.835951,
   4.533152,
   4.811615,
   4.137,
   4.844393,
   5.00182,
   6.002586,
   4.472823,
   4.562879};
   for (int i(0); i< 30; i++){
     AberrVsPos_fy3[i]/=off;
   }
   graph = new TGraph(30,AberrVsPos_fx3,AberrVsPos_fy3);
   graph->SetName("AberrVsPos");
   graph->SetTitle("2727-13 ");
   graph->SetFillStyle(1000);
   graph->SetLineColor(7);
   graph->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(3);
   graph->SetMarkerSize(1.5);

   TH1F *Graph_AberrVsPos3 = new TH1F("Graph_AberrVsPos3","2727-13 ",100,35.5,209.5);
   Graph_AberrVsPos3->SetMinimum(1.748721);
   Graph_AberrVsPos3->SetMaximum(6.389301);
   Graph_AberrVsPos3->SetDirectory(0);
   Graph_AberrVsPos3->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_AberrVsPos3->SetLineColor(ci);
   Graph_AberrVsPos3->GetXaxis()->SetTitle("Position from PEN [mm]");
   Graph_AberrVsPos3->GetXaxis()->SetLabelFont(42);
   Graph_AberrVsPos3->GetXaxis()->SetTitleOffset(1);
   Graph_AberrVsPos3->GetXaxis()->SetTitleFont(42);
   Graph_AberrVsPos3->GetYaxis()->SetTitle(" Mean deviation from true point ");
   Graph_AberrVsPos3->GetYaxis()->SetLabelFont(42);
   Graph_AberrVsPos3->GetYaxis()->SetTitleFont(42);
   Graph_AberrVsPos3->GetZaxis()->SetLabelFont(42);
   Graph_AberrVsPos3->GetZaxis()->SetTitleOffset(1);
   Graph_AberrVsPos3->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_AberrVsPos3);

   multigraph->Add(graph,"");

   Double_t AberrVsPos_fx4[30] = {
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
   Double_t AberrVsPos_fy4[30] = {
   1.966958,
   2.031497,
   2.103705,
   2.158518,
   2.189657,
   2.193362,
   2.212077,
   2.238037,
   2.267331,
   2.316707,
   2.397631,
   2.394502,
   2.402742,
   2.48518,
   2.562792,
   2.692546,
   2.756801,
   3.132631,
   3.011231,
   3.311205,
   3.454667,
   3.353456,
   3.405864,
   3.465233,
   3.472654,
   4.033212,
   3.745138,
   3.808112,
   4.325888,
   3.997875};
   for (int i(0); i< 30; i++){
     AberrVsPos_fy4[i]/=off;
   }
   graph = new TGraph(30,AberrVsPos_fx4,AberrVsPos_fy4);
   graph->SetName("AberrVsPos");
   graph->SetTitle("4444-16 ");
   graph->SetFillStyle(1000);
   graph->SetLineColor(8);
   graph->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(3);
   graph->SetMarkerSize(1.5);

   TH1F *Graph_AberrVsPos4 = new TH1F("Graph_AberrVsPos4","4444-16 ",100,35.5,209.5);
   Graph_AberrVsPos4->SetMinimum(1.731065);
   Graph_AberrVsPos4->SetMaximum(4.561781);
   Graph_AberrVsPos4->SetDirectory(0);
   Graph_AberrVsPos4->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_AberrVsPos4->SetLineColor(ci);
   Graph_AberrVsPos4->GetXaxis()->SetTitle("Position from PEN [mm]");
   Graph_AberrVsPos4->GetXaxis()->SetLabelFont(42);
   Graph_AberrVsPos4->GetXaxis()->SetTitleOffset(1);
   Graph_AberrVsPos4->GetXaxis()->SetTitleFont(42);
   Graph_AberrVsPos4->GetYaxis()->SetTitle(" Mean deviation from true point ");
   Graph_AberrVsPos4->GetYaxis()->SetLabelFont(42);
   Graph_AberrVsPos4->GetYaxis()->SetTitleFont(42);
   Graph_AberrVsPos4->GetZaxis()->SetLabelFont(42);
   Graph_AberrVsPos4->GetZaxis()->SetTitleOffset(1);
   Graph_AberrVsPos4->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_AberrVsPos4);

   multigraph->Add(graph,"");

   Double_t AberrVsPos_fx5[30] = {
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
   Double_t AberrVsPos_fy5[30] = {
   2.277166,
   2.46038,
   2.396699,
   2.881788,
   3.07982,
   2.94191,
   3.527764,
   3.32434,
   3.115283,
   3.240074,
   3.820178,
   3.576074,
   4.334764,
   3.871241,
   3.996873,
   4.122306,
   4.289288,
   4.475019,
   5.363683,
   4.782459,
   4.860738,
   5.075097,
   4.387034,
   5.36348,
   5.540061,
   5.659185,
   5.874045,
   5.045538,
   6.173498,
   5.954198};
   for (int i(0); i< 30; i++){
     AberrVsPos_fy5[i]/=off;
   }
   graph = new TGraph(30,AberrVsPos_fx5,AberrVsPos_fy5);
   graph->SetName("AberrVsPos");
   graph->SetTitle("2718-5 ");
   graph->SetFillStyle(1000);
   graph->SetLineColor(20);
   graph->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(3);
   graph->SetMarkerSize(1.5);

   TH1F *Graph_AberrVsPos5 = new TH1F("Graph_AberrVsPos5","2718-5 ",100,35.5,209.5);
   Graph_AberrVsPos5->SetMinimum(1.887533);
   Graph_AberrVsPos5->SetMaximum(6.563131);
   Graph_AberrVsPos5->SetDirectory(0);
   Graph_AberrVsPos5->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_AberrVsPos5->SetLineColor(ci);
   Graph_AberrVsPos5->GetXaxis()->SetTitle("Position from PEN [mm]");
   Graph_AberrVsPos5->GetXaxis()->SetLabelFont(42);
   Graph_AberrVsPos5->GetXaxis()->SetTitleOffset(1);
   Graph_AberrVsPos5->GetXaxis()->SetTitleFont(42);
   Graph_AberrVsPos5->GetYaxis()->SetTitle(" Mean deviation from true point ");
   Graph_AberrVsPos5->GetYaxis()->SetLabelFont(42);
   Graph_AberrVsPos5->GetYaxis()->SetTitleFont(42);
   Graph_AberrVsPos5->GetZaxis()->SetLabelFont(42);
   Graph_AberrVsPos5->GetZaxis()->SetTitleOffset(1);
   Graph_AberrVsPos5->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_AberrVsPos5);

   multigraph->Add(graph,"");
   multigraph->Draw("AL*");
   multigraph->GetXaxis()->SetLimits(42.75, 202.25);
   multigraph->GetXaxis()->SetTitle("Lens position (mm)");
   multigraph->GetXaxis()->SetLabelFont(132);
   multigraph->GetXaxis()->SetLabelSize(0.05);
   multigraph->GetXaxis()->SetTitleSize(0.06);
   multigraph->GetXaxis()->SetTitleOffset(1);
   multigraph->GetXaxis()->SetTitleFont(132);
   multigraph->GetYaxis()->SetTitle(" Mean deviation from true point (mm) ");
   multigraph->GetYaxis()->SetLabelFont(132);
   multigraph->GetYaxis()->SetLabelSize(0.05);
   multigraph->GetYaxis()->SetTitleSize(0.06);
   multigraph->GetYaxis()->SetTitleOffset(1);
   multigraph->GetYaxis()->SetTitleFont(132);

   TLegend *leg = new TLegend(0.1879699,0.586087,0.4373434,0.9217391,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph_AberrVsPos1","4427-40 ","lpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(4);
   entry->SetLineStyle(1);
   entry->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(3);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph_AberrVsPos2","2727-6 ","lpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(6);
   entry->SetLineStyle(1);
   entry->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(3);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph_AberrVsPos3","2727-13 ","lpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(7);
   entry->SetLineStyle(1);
   entry->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(3);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph_AberrVsPos4","4444-16 ","lpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(8);
   entry->SetLineStyle(1);
   entry->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(3);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph_AberrVsPos5","2718-5 ","lpf");
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
   c6->Modified();
   c6->cd();
   c6->SetSelected(c6);
}
