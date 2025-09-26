#ifdef __CLING__
#pragma cling optimize(0)
#endif
void Mag_Vs_Pos()
{
//=========Macro generated from canvas: c4/ Mag Vs Pos
//=========  (Tue Mar 21 16:34:49 2023) by ROOT version 6.26/06
   TCanvas *c4 = new TCanvas("c4", " Mag Vs Pos",537,53,800,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptTitle(0);
   c4->Range(14.72973,-2.901075,230.2703,17.24468);
   c4->SetFillColor(0);
   c4->SetBorderMode(0);
   c4->SetBorderSize(2);
   c4->SetTickx(1);
   c4->SetTicky(1);
   c4->SetLeftMargin(0.13);
   c4->SetRightMargin(0.13);
   c4->SetTopMargin(0.05);
   c4->SetBottomMargin(0.16);
   c4->SetFrameBorderMode(0);
   c4->SetFrameBorderMode(0);

   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("");
   Double_t off = -0.9;

   Double_t MagVsPos_fx1[30] = {
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
   Double_t MagVsPos_fy1[30] = {
   1.659579,
   1.786104,
   1.943894,
   2.087502,
   2.23033,
   2.377366,
   2.535655,
   2.669227,
   2.815194,
   2.955954,
   3.094,
   3.231191,
   3.383446,
   3.524064,
   3.671395,
   3.766864,
   3.9592,
   4.098386,
   4.252572,
   4.399357,
   4.531583,
   4.668384,
   4.777068,
   4.952086,
   5.108619,
   5.25687,
   5.396096,
   5.534201,
   5.797995,
   5.823143};
   for (int i(0); i < 30; i++){
     MagVsPos_fy1[i]+=off;
   }
   TGraph *graph = new TGraph(30,MagVsPos_fx1,MagVsPos_fy1);
   graph->SetName("MagVsPos");
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

   TH1F *Graph_MagVsPos1 = new TH1F("Graph_MagVsPos1","4427-40 ",100,35.5,209.5);
   Graph_MagVsPos1->SetMinimum(1.243223);
   Graph_MagVsPos1->SetMaximum(6.239499);
   Graph_MagVsPos1->SetDirectory(0);
   Graph_MagVsPos1->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_MagVsPos1->SetLineColor(ci);
   Graph_MagVsPos1->GetXaxis()->SetTitle("Position");
   Graph_MagVsPos1->GetXaxis()->SetLabelFont(42);
   Graph_MagVsPos1->GetXaxis()->SetTitleOffset(1);
   Graph_MagVsPos1->GetXaxis()->SetTitleFont(42);
   Graph_MagVsPos1->GetYaxis()->SetTitle(" Magnitude ");
   Graph_MagVsPos1->GetYaxis()->SetLabelFont(42);
   Graph_MagVsPos1->GetYaxis()->SetTitleFont(42);
   Graph_MagVsPos1->GetZaxis()->SetLabelFont(42);
   Graph_MagVsPos1->GetZaxis()->SetTitleOffset(1);
   Graph_MagVsPos1->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_MagVsPos1);

   multigraph->Add(graph,"");

   Double_t MagVsPos_fx2[30] = {
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
   Double_t MagVsPos_fy2[30] = {
   2.568116,
   3.018844,
   3.418648,
   3.708664,
   4.104337,
   4.471597,
   4.75966,
   5.296472,
   5.547415,
   5.727701,
   6.135184,
   6.796708,
   7.150483,
   7.464745,
   7.777731,
   8.022462,
   8.366746,
   8.481282,
   8.928762,
   9.252468,
   9.554539,
   9.900306,
   10.17471,
   10.49416,
   11.71485,
   11.00981,
   11.35277,
   11.68943,
   11.86519,
   12.2429};

   for (int i(0); i < 30; i++){
     MagVsPos_fy2[i]+=off;
   }

   graph = new TGraph(30,MagVsPos_fx2,MagVsPos_fy2);
   graph->SetName("MagVsPos");
   graph->SetTitle("2727-6 ");
   graph->SetFillStyle(1000);
   graph->SetLineColor(6);
   graph->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(3);
   graph->SetMarkerSize(1.5);

   TH1F *Graph_MagVsPos2 = new TH1F("Graph_MagVsPos2","2727-6 ",100,35.5,209.5);
   Graph_MagVsPos2->SetMinimum(1.600638);
   Graph_MagVsPos2->SetMaximum(13.21038);
   Graph_MagVsPos2->SetDirectory(0);
   Graph_MagVsPos2->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_MagVsPos2->SetLineColor(ci);
   Graph_MagVsPos2->GetXaxis()->SetTitle("Position");
   Graph_MagVsPos2->GetXaxis()->SetLabelFont(42);
   Graph_MagVsPos2->GetXaxis()->SetTitleOffset(1);
   Graph_MagVsPos2->GetXaxis()->SetTitleFont(42);
   Graph_MagVsPos2->GetYaxis()->SetTitle(" Magnitude ");
   Graph_MagVsPos2->GetYaxis()->SetLabelFont(42);
   Graph_MagVsPos2->GetYaxis()->SetTitleFont(42);
   Graph_MagVsPos2->GetZaxis()->SetLabelFont(42);
   Graph_MagVsPos2->GetZaxis()->SetTitleOffset(1);
   Graph_MagVsPos2->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_MagVsPos2);

   multigraph->Add(graph,"");

   Double_t MagVsPos_fx3[30] = {
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
   Double_t MagVsPos_fy3[30] = {
   2.306521,
   2.663985,
   2.961513,
   3.35608,
   3.550115,
   3.866757,
   4.350778,
   4.516768,
   4.809791,
   5.148326,
   5.466374,
   5.857144,
   6.161547,
   6.407873,
   6.669088,
   6.99286,
   7.344608,
   7.570701,
   7.714825,
   8.057711,
   8.357134,
   8.52505,
   8.893585,
   9.14462,
   9.39702,
   9.693314,
   9.895769,
   9.977519,
   10.45249,
   10.62471};
   for (int i(0); i < 30; i++){
     MagVsPos_fy3[i]+=off;
   }
   graph = new TGraph(30,MagVsPos_fx3,MagVsPos_fy3);
   graph->SetName("MagVsPos");
   graph->SetTitle("2727-13 ");
   graph->SetFillStyle(1000);
   graph->SetLineColor(7);
   graph->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(3);
   graph->SetMarkerSize(1.5);

   TH1F *Graph_MagVsPos3 = new TH1F("Graph_MagVsPos3","2727-13 ",100,35.5,209.5);
   Graph_MagVsPos3->SetMinimum(1.474702);
   Graph_MagVsPos3->SetMaximum(11.45653);
   Graph_MagVsPos3->SetDirectory(0);
   Graph_MagVsPos3->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_MagVsPos3->SetLineColor(ci);
   Graph_MagVsPos3->GetXaxis()->SetTitle("Position");
   Graph_MagVsPos3->GetXaxis()->SetLabelFont(42);
   Graph_MagVsPos3->GetXaxis()->SetTitleOffset(1);
   Graph_MagVsPos3->GetXaxis()->SetTitleFont(42);
   Graph_MagVsPos3->GetYaxis()->SetTitle(" Magnitude ");
   Graph_MagVsPos3->GetYaxis()->SetLabelFont(42);
   Graph_MagVsPos3->GetYaxis()->SetTitleFont(42);
   Graph_MagVsPos3->GetZaxis()->SetLabelFont(42);
   Graph_MagVsPos3->GetZaxis()->SetTitleOffset(1);
   Graph_MagVsPos3->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_MagVsPos3);

   multigraph->Add(graph,"");

   Double_t MagVsPos_fx4[30] = {
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
   Double_t MagVsPos_fy4[30] = {
   1.045661,
   1.234216,
   1.434875,
   1.621607,
   1.819446,
   2.027753,
   2.219267,
   2.418398,
   2.623443,
   2.821465,
   3.021671,
   3.218595,
   3.44031,
   3.628869,
   3.852983,
   4.061071,
   4.253419,
   4.507988,
   4.709052,
   4.931427,
   5.142939,
   5.337281,
   5.519402,
   5.731346,
   5.889188,
   6.104524,
   6.258457,
   6.45829,
   6.660802,
   6.807554};
   for (int i(0); i < 30; i++){
     MagVsPos_fy4[i]+=off;
   }
   graph = new TGraph(30,MagVsPos_fx4,MagVsPos_fy4);
   graph->SetName("MagVsPos");
   graph->SetTitle("4444-16 ");
   graph->SetFillStyle(1000);
   graph->SetLineColor(8);
   graph->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(3);
   graph->SetMarkerSize(1.5);

   TH1F *Graph_MagVsPos4 = new TH1F("Graph_MagVsPos4","4444-16 ",100,35.5,209.5);
   Graph_MagVsPos4->SetMinimum(0.4694719);
   Graph_MagVsPos4->SetMaximum(7.383743);
   Graph_MagVsPos4->SetDirectory(0);
   Graph_MagVsPos4->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_MagVsPos4->SetLineColor(ci);
   Graph_MagVsPos4->GetXaxis()->SetTitle("Position");
   Graph_MagVsPos4->GetXaxis()->SetLabelFont(42);
   Graph_MagVsPos4->GetXaxis()->SetTitleOffset(1);
   Graph_MagVsPos4->GetXaxis()->SetTitleFont(42);
   Graph_MagVsPos4->GetYaxis()->SetTitle(" Magnitude ");
   Graph_MagVsPos4->GetYaxis()->SetLabelFont(42);
   Graph_MagVsPos4->GetYaxis()->SetTitleFont(42);
   Graph_MagVsPos4->GetZaxis()->SetLabelFont(42);
   Graph_MagVsPos4->GetZaxis()->SetTitleOffset(1);
   Graph_MagVsPos4->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_MagVsPos4);

   multigraph->Add(graph,"");

   Double_t MagVsPos_fx5[30] = {
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
   Double_t MagVsPos_fy5[30] = {
   3.616929,
   4.112093,
   4.514008,
   5.165052,
   5.694244,
   5.96288,
   6.703196,
   7.009245,
   7.186529,
   7.747603,
   8.318587,
   8.580016,
   9.162312,
   9.399647,
   9.776557,
   10.22338,
   10.54546,
   10.9973,
   11.21427,
   11.80544,
   12.16357,
   12.51147,
   13.05907,
   13.23743,
   13.64206,
   13.96381,
   14.20845,
   14.6936,
   15.14819,
   15.51397};
   for (int i(0); i < 30; i++){
     MagVsPos_fy5[i]+=off;
   }
   graph = new TGraph(30,MagVsPos_fx5,MagVsPos_fy5);
   graph->SetName("MagVsPos");
   graph->SetTitle("2718-5 ");
   graph->SetFillStyle(1000);
   graph->SetLineColor(20);
   graph->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(3);
   graph->SetMarkerSize(1.5);

   TH1F *Graph_MagVsPos5 = new TH1F("Graph_MagVsPos5","2718-5 ",100,35.5,209.5);
   Graph_MagVsPos5->SetMinimum(2.427225);
   Graph_MagVsPos5->SetMaximum(16.70368);
   Graph_MagVsPos5->SetDirectory(0);
   Graph_MagVsPos5->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_MagVsPos5->SetLineColor(ci);
   Graph_MagVsPos5->GetXaxis()->SetTitle("Position");
   Graph_MagVsPos5->GetXaxis()->SetLabelFont(42);
   Graph_MagVsPos5->GetXaxis()->SetTitleOffset(1);
   Graph_MagVsPos5->GetXaxis()->SetTitleFont(42);
   Graph_MagVsPos5->GetYaxis()->SetTitle(" Magnitude ");
   Graph_MagVsPos5->GetYaxis()->SetLabelFont(42);
   Graph_MagVsPos5->GetYaxis()->SetTitleFont(42);
   Graph_MagVsPos5->GetZaxis()->SetLabelFont(42);
   Graph_MagVsPos5->GetZaxis()->SetTitleOffset(1);
   Graph_MagVsPos5->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_MagVsPos5);

   multigraph->Add(graph,"");
   multigraph->Draw("AL*");
   multigraph->GetXaxis()->SetLimits(42.75, 202.25);
   multigraph->GetXaxis()->SetTitle("Lens position (mm)");
   multigraph->GetXaxis()->SetLabelFont(132);
   multigraph->GetXaxis()->SetLabelSize(0.05);
   multigraph->GetXaxis()->SetTitleSize(0.06);
   multigraph->GetXaxis()->SetTitleOffset(1);
   multigraph->GetXaxis()->SetTitleFont(132);
   multigraph->GetYaxis()->SetTitle("Magnitude");
   multigraph->GetYaxis()->SetLabelFont(132);
   multigraph->GetYaxis()->SetLabelSize(0.05);
   multigraph->GetYaxis()->SetTitleSize(0.06);
   multigraph->GetYaxis()->SetTitleOffset(1);
   multigraph->GetYaxis()->SetTitleFont(132);

   TLegend *leg = new TLegend(0.1392405,0.6140351,0.4392405,0.8240351,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph_MagVsPos1","4427-40 ","lpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(4);
   entry->SetLineStyle(1);
   entry->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(3);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph_MagVsPos2","2727-6 ","lpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(6);
   entry->SetLineStyle(1);
   entry->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(3);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph_MagVsPos3","2727-13 ","lpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(7);
   entry->SetLineStyle(1);
   entry->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(3);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph_MagVsPos4","4444-16 ","lpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(8);
   entry->SetLineStyle(1);
   entry->SetLineWidth(4);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(3);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph_MagVsPos5","2718-5 ","lpf");
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
   c4->Modified();
   c4->cd();
   c4->SetSelected(c4);
}
