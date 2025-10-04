#include "OpticSystemTransport.h"
#include "TRandom.h"
#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TProfile.h"
#include "TCanvas.h"

double Simulation(double size = 200., double lensposition = 0., double sensorpos = 0.) {

    bool debug = false;
    TFile *graphs = new TFile("graphs.root", "UPDATE");
    FILE *input = fopen("lens_sensor_position_input.txt", "r");

    std::vector<double> lenspositions_v, sensorpositions_v;
    double col_1 = 0, col_2 = 0;
    while (fscanf(input, "%lf %lf", &col_1, &col_2) == 2) {
        lenspositions_v.push_back(col_1);
        sensorpositions_v.push_back(col_2);
    }

    Double_t lens_th_30 = 6.5, lens_Surf_R1 = 45.61, lens_th_20 = 5.0, lens_th = 0;
    Double_t d_1_2 = lens_th_30/2 + lens_th_30/2 + 6.5;
    Double_t lens_ApRad = 30./2.;
    Double_t Flange_Thick = 22, WLS_Zpos = 0.;
    Double_t d_ThGEMtoFlange = 50, PEN_to_Flange = d_ThGEMtoFlange;
    Double_t w_pos = d_ThGEMtoFlange + Flange_Thick/2;
    Double_t distr_fact = 0.5, MPPC_QE = 0.4, Acr_tr = 0.9;
    double PEN_QE = 0.25, mesh_t = 0.8;
    Double_t dt_Ar = 1200, dt_CF4 = 100;
    Double_t dt = dt_Ar * TMath::Sqrt(10) * 1e-3, tr_size = 1.;
    Double_t dx_mean = 0, WLS_size = 200;

    Double_t silica_idx = 1.458;
    Double_t EJ_220_idx = 1.6;//source: table 2 https://arxiv.org/pdf/2407.19465
    Double_t cube_length = 100; //size of cube

    Disc w(w_pos, 8.3, 50., silica_idx, 1);
    Disc air(cube_length, 8.3, 50., silica_idx, 1);
    double pmt_pos = w_pos + 5;
    Disc pmt(pmt_pos, 2., 12.5, 1.458, 1);

    std::vector<Aperture*> a1_store;
    std::vector<Lens*> lens_store, lens_store_2;
    for (size_t i = 0; i < lenspositions_v.size(); i++) {
        lens_store.push_back(new Lens(lenspositions_v.at(i), lens_th_30, lens_Surf_R1, lens_ApRad, 1.833, 3));
        lens_store_2.push_back(new Lens(lenspositions_v.at(i) + d_1_2, lens_th_30, lens_Surf_R1, lens_ApRad, 1.833, 3));
        a1_store.push_back(new Aperture(lenspositions_v.at(i) - lens_th_30/2 - 3, 1., 14., 2));
    }
    for (size_t i = 0; i < lens_store.size(); i++) {
        lens_store.at(i)->SetDebug(debug);
        lens_store_2.at(i)->SetDebug(debug);
        a1_store.at(i)->SetDebug(debug);
    }
    w.SetDebug(debug);

    TRandom r;
    std::vector<Double_t> xOnPEN, yOnPEN;
    std::vector<double> PhtPerBin, eff_mag, lens_acc, mag_store, aberr_store;
    
    TH2D *h1_2d = new TH2D("h1_PEN_dist", "1. Primary photons produced forward ; X (mm); Y(mm)", 200, -65, 65, 200, -65, 65);
    TH3D *h1_3d = new TH3D("3d_h1_PEN_dist", "1. Primary photons produced forward ; X (mm); Y(mm); Z(mm)", 200, -65, 65, 200, -65, 65, 200, -65, 65);
    TH2D *hpmt_2d = new TH2D("h_PMT_dist", " Photon distribution on the Photocathode of PMT ; X (mm); Y (mm)", 200, -30, 30, 200, -30, 30);
    TH2D *h2x = new TH2D("h2x", "  ", 100, -size-2, size+2, 100, -20, 20);
    TH2D *h2y = new TH2D("h2y", ";Position at PEN (mm);Position at MPPC (mm)", 100, -WLS_size/2., WLS_size/2., 100, -WLS_size/2./5., WLS_size/2./5.);
    TProfile *hpx = new TProfile("hpx", "  ", 100, -size-2, size+2, -20, 20, "S");
    TProfile *hpy = new TProfile("hpy", "  ", 100, -WLS_size/2., WLS_size/2., -WLS_size/2./5., WLS_size/2./5., "S");
    TH2D *hsensornolens = new TH2D("hsensornolens", "4. Photons detected by MPPC without lens ", 16, -8., 8., 16, -8., 8.);
    TH2D *hsensorlens = new TH2D("hsensorlens", "3. Photons detected by MPPC; X position on MPPC (mm); Y position on MPPC (mm) ", 16, -8., 8., 16, -8., 8.);
    TH2D *hlens = new TH2D("hlens", "2. Photons distribution on the first lens; X Position on lens (mm); Y Position on lens (mm) ", 100, -lens_ApRad-10, lens_ApRad+10, 100, -lens_ApRad-10, lens_ApRad+10);
    TH2D *hwindow = new TH2D("hwindow", "  ", 100, -50., 50., 100, -50., 50.);
    TH2D *hwindow2 = new TH2D("hwindow2", "  ", 100, -50., 50., 100, -50., 50.);
    TH1D *haberr = new TH1D("haberr", "", 1000, 0., size/10.);
    TH1D *htest = new TH1D("htest", "", 1000, -8, 8);
    TH3D *hdxr = new TH3D("hdxr", "", 100, 0., 25., 100, -size, size, 100, -size/5., size/5.);
    TH3D *testspherical = new TH3D("testspherical", "", 100, -1., 1., 100, -1., 1., 100, -1., 1.);
    TH2D *hRICy = new TH2D("hRICy", ";Fractional Pupil Coordonate (at lens); Displacement at lens (mm) ", 100, -1.1, 1.1, 100, -5, 5);
    TH2D *hRICx = new TH2D("hRICx", ";Fractional Pupil Coordonate (at lens); Displacement at lens (mm)", 100, -1.1, 1.1, 100, -5, 5);

    double D = 100., d1 = w_pos;
    int ntot = 0;
    double NDecay = 100., MIP_e = 2.2e5, part_propag = 100;
    //Muons 2.2 MeV per cm or 0.22 MeV per mm.
    //protons 4.5 MeV per cm or 0.45 MeV per mm
    //Alpha 5.3 MeV per cm or 0.53 MeV per mm// attention genereated with copilot AI
    //Electron 2.0 MeV per cm or 0.20 MeV per // attention genereated with copilot AI
    if (part_propag > 100) cout << " Pay attentio, the particle propagates more than 100 mm, the length of the cube" << std::endl;
    
    double InEnergy = MIP_e * part_propag;
    cout << " Input Energy (eV) " << InEnergy << endl;
    double pht_per_eV = 0.01, prim_pht = InEnergy * pht_per_eV;
    int PhtAtThGEM = NDecay * prim_pht;
    cout << " Initial conditions: " << PhtAtThGEM << "  NDecay " << NDecay << "  Primary photons per decay " << prim_pht << endl;
    double photAtLens = 0;

    for (size_t pos = 0; pos < lens_store.size(); pos++) {
        double lensposition_2 = lens_store_2[pos]->GetLensPos();
        lensposition = lens_store.at(pos)->GetLensPos();
        lens_th = lens_store.at(pos)->GetThickness();
        lens_ApRad = lens_store.at(pos)->GetApRad();
        lensposition_2 = lens_store_2.at(pos)->GetLensPos();
        sensorpos = sensorpositions_v.at(pos) + WLS_Zpos;
        cout << " Lens 1 position " << lensposition << " Sensor position " << sensorpos <<  " lens thickenss " << lens_th << "  Lens Aperture Radius " << lens_ApRad << endl;

        xOnPEN.clear(); yOnPEN.clear();
        hsensorlens->Reset("ICESM");
        h1_2d->Reset("ICESM");
        hsensornolens->Reset("ICESM");
        hwindow2->Reset("ICESM");
        hlens->Reset("ICESM");
        hdxr->Reset("ICESM");
        h2y->Reset("ICESM");
        hpy->Reset("ICESM");
        hpx->Reset("ICESM");
        h2x->Reset("ICESM");
        photAtLens = 0;
        hwindow->Reset("ICESM");
        hRICy->Reset("ICESM");
        hRICx->Reset("ICESM");
        dx_mean = 0;

      
        ntot = PhtAtThGEM;
        double z = 0;
        for (size_t i = 0; i < PhtAtThGEM/2; i++) {
            double x = r.Uniform(-part_propag/2, part_propag/2);
            double y = x;
            z = 0;//x + 40. / (PhtAtThGEM / 2);

            xOnPEN.push_back(x);
            yOnPEN.push_back(y);
            h1_2d->Fill(x,y);
            h1_3d->Fill(x,y,z);
            double costheta = r.Uniform(0.,1.), phi = r.Uniform(0.,2*3.141592);
            double sintheta = TMath::Sqrt(1.-(costheta*costheta));
            double vx = sintheta*TMath::Cos(phi), vy = sintheta*TMath::Sin(phi), vz = costheta;
            // testspherical->Fill(vx, vy, vz);
            Ray ray(x, y, z, vx, vy, vz, 1.);
            double thx = vx/vz, thy = vy/vz;

            if (TMath::Sqrt((x+thx*d1)*(x+thx*d1)+(y+thy*d1)*(y+thy*d1)) < D/2.) hwindow2->Fill(x+thx*d1,y+thy*d1);
            if (TMath::Abs(x+thx*sensorpos)<8. &&  TMath::Abs(y+thy*sensorpos)<8.) hsensornolens->Fill(x+thx*sensorpos,y+thy*sensorpos);
            if (TMath::Sqrt(pow(x+thx*(lensposition+(lens_th/2)),2) + pow(y+thy*(lensposition+(lens_th/2)),2)) < lens_ApRad) photAtLens++;
            // if (!w.Transport(ray)) continue;
            // ray.Transport(w_pos);
            // hwindow->Fill(ray.GetX(), ray.GetY());
            // if (pmt.Transport(ray)) {
            //     ray.Transport(pmt_pos);
            //     if (r.Uniform() < PEN_QE) hpmt_2d->Fill(ray.GetX(), ray.GetY());
            // }
            if (!a1_store.at(pos)->Transport(ray)) continue;
            ray.Transport(a1_store.at(pos)->GetPos());
            if (!lens_store.at(pos)->Transport(ray)) continue;
            hlens->Fill(ray.GetX(), ray.GetY());
            double Ratlens = TMath::Sqrt(ray.GetX()*ray.GetX()+ray.GetY()*ray.GetY());
            ray.Transport(lensposition);
            Double_t FY = (2*(ray.GetY() + lens_ApRad) / (2*lens_ApRad))-1;
            Double_t FX = (2*(ray.GetX() + lens_ApRad) / (2*lens_ApRad))-1;
            if (!lens_store_2.at(pos)->Transport(ray)) continue;
            ray.Transport(sensorpos);

            Double_t DY = ray.GetY(), DX = ray.GetX();
            if (-1<y && y<1) hRICy->Fill(FY, DY);
            if (-1<x && x<1 && FX>0) {
                hRICx->Fill(FX, DX);
                dx_mean += DX;
            }
            Bool_t eff_con = r.Uniform() < MPPC_QE && r.Uniform() < Acr_tr;
            if (fabs(ray.GetX())<8. && fabs(ray.GetY())<8. && eff_con) {
                hsensorlens->Fill(ray.GetX(), ray.GetY());
                htest->Fill(ray.GetX());
                hdxr->Fill(Ratlens, x, ray.GetX());
                h2x->Fill(x, ray.GetX());
                hpx->Fill(x, ray.GetX());
                h2y->Fill(y, ray.GetY());
                hpy->Fill(y, ray.GetY());
            }
        }

        double bin_content = 0;
        for (int i = 6; i < 12; i++) bin_content += hsensorlens->GetBinContent(i, i);
        h2x->FitSlicesX(); h2y->FitSlicesX();
        TH1D *h2xmean = (TH1D*)gROOT->FindObject("h2x_1");
        TH1D *h2ymean = (TH1D*)gROOT->FindObject("h2y_1");
        h2xmean->Fit("pol1", "", "", -7., 7.);
        h2ymean->Fit("pol1", "", "", -7., 7.);
        double aberr = 0.01;
        cout << "PAY ATTENTION I HAVE MUTILATED THE aberr TO 0.1 " << endl;
        
        PhtPerBin.push_back(bin_content / 6 / NDecay);
        eff_mag.push_back((double)hsensorlens->GetEntries()/(double)ntot * 1/(MPPC_QE*Acr_tr));
        lens_acc.push_back(hlens->GetEntries()/ntot);
        hpx->Fit("pol1", "", "same");
        
        mag_store.push_back(TMath::Abs(h2ymean->GetFunction("pol1")->GetParameter(1)));
        aberr_store.push_back(aberr);
        std::cout << " The max number of photons per channel: " << bin_content / 16 / NDecay << std::endl;
        std::cout << " eff * mag " << ((double)hsensorlens->GetEntries()/(double)ntot) * 1/(MPPC_QE*Acr_tr) << " lensposition " << lensposition <<std::endl;
        std::cout << " Photons reaching the lens " << hlens->GetEntries() << " ratio " << hlens->GetEntries()/ntot << " lens/pen "  << hlens->GetEntries()/xOnPEN.size() << std::endl;
    }
    
    TCanvas *c = new TCanvas("c", "Overview", 1200, 800);
    c->Divide(2, 3);
    c->cd(1); h2x->Draw("colz"); hpx->Fit("pol1", "", "same"); for(int i=0; i<100; i++ ) haberr->Fill(hpy->GetBinError(i+1));
    c->cd(2); h2y->Draw("colz"); for(int i=0; i<100; i++ ) haberr->Fill(hpy->GetBinError(i+1));
    c->cd(3); hsensorlens->Scale(1/NDecay); hsensorlens->Draw("colz");
    c->cd(4); hsensornolens->Scale(1/NDecay); hsensornolens->Draw("colz");
    c->cd(5); hlens->Scale(1/NDecay); hlens->Scale(1/NDecay); hlens->Draw("colz");
    c->cd(6); hdxr->Draw("box");
    c->Update();


    TCanvas *c_Img = new TCanvas("c_img", "Images", 1200, 800);
    c_Img->Divide(2, 2);
    c_Img->cd(1); h1_2d->Draw("colz");
    c_Img->cd(2); hlens->Draw("colz");
    c_Img->cd(3); hsensorlens->Draw("colz");
    c_Img->cd(4); hsensornolens->Draw("colz");
    c_Img->Update();

    // TCanvas *c_Img_3D = new TCanvas("c_3d", "Ima", 1200, 800);
    // h1_3d->Draw("box");
    // c_Img_3D->Update();

    double scale = 1. / (hpx->GetFunction("pol1")->GetParameter(1));
    std::cout << "\n\n";
    std::cout << " --------------For "<< NDecay<<" identical primary tracks ----------------- " << std::endl;
    std::cout << " Total photons generated in the scintillator (along the track) " << ntot << endl;
    std::cout << " Photons emitted at forward" << xOnPEN.size() << " Fraction " << (double)xOnPEN.size()/ntot << endl;
    std::cout << " Photons reaching the lens " << hlens->GetEntries() << " ratio " << hlens->GetEntries()/ntot << " lens/pen " << hlens->GetEntries()/xOnPEN.size() << std::endl;
    std::cout << " Fraction of photons reaching the sensor " << std::endl;
    std::cout << "       With lens " << (double)hsensorlens->GetEntries()/(double)ntot << std::endl;
    std::cout << "       With no lense " << (double)hsensornolens->GetEntries()/(double)ntot << std::endl;
    std::cout << " Including the MPPC QE,  With Lense: " << (double)hsensorlens->GetEntries() << endl;
    std::cout << " ------------------------------------------------------------------- " << std::endl;
    if (hRICx->GetEntries()!=0) std::cout << "Lens Performance " << dx_mean/hRICx->GetEntries() <<"  Lens pos " << lensposition <<  " mm.  SensorPos " << sensorpos << std::endl;
    if (mag_store.size() != 0) std::cout << "Magnitude " << mag_store.at(0) <<std::endl;
    std::vector<double> acc_mag_lens;
    for (size_t i = 0; i < mag_store.size(); i++) acc_mag_lens.push_back(lens_acc.at(i)*mag_store.at(i));
    TCanvas *c_LensAccMag_pos = new TCanvas("Acc_mag_pos ", "", 600, 600);
    double f = lens_store.at(0)->GetFocalLength(), f2 = lens_store_2.at(0)->GetFocalLength();
    double lens_th_2 = 0, lens_ApRad_2 = 0;
    for (size_t i = 0; i < lens_store.size(); i++) { delete lens_store.at(i); }
    return 0;

}
