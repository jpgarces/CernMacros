void plot_tau_angles(){

 TFile *f1 = TFile::Open("tau_angles_e_sm.root");
 TFile *f2 = TFile::Open("tau_angles_e_bsm.root");
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 
 TH1F *hist_e_angles_sm = (TH1F*) f1->Get("hist_e_angles");
 TH1F *hist_e_angles_bsm = (TH1F*) f2->Get("hist_e_angles");
 /* TH1F *hist_anue_angles = (TH1F*) outf->Get("hist_anue_angles");
    TH1F *hist_nut_angles = (TH1F*) outf->Get("hist_nut_angles");*/
 
 legend->AddEntry(hist_e_angles_sm,"SM electrons");
 legend->AddEntry(hist_e_angles_bsm,"BSM electrons");
 /*legend->AddEntry(hist_anue_angles,"Anti electron neutrino");
   legend->AddEntry(hist_nut_angles,"Tau neutrino");*/

 gStyle->SetOptStat(11);
 hist_e_angles_sm->SetLineColor(3);
 hist_e_angles_sm->SetLineWidth(3);
 hist_e_angles_sm->GetXaxis()->SetTitle("Angle (deg)");
 hist_e_angles_sm->GetYaxis()->SetTitle("Counts");
 hist_e_angles_sm->SetTitle("Angle of decay products w.r.t Tau direction");
 hist_e_angles_sm->GetXaxis()->CenterTitle(kTRUE);
 hist_e_angles_sm->GetYaxis()->CenterTitle(kTRUE);
 hist_e_angles_sm->Draw();
  gStyle->SetOptStat(11);
 TPaveStats *stats1 =(TPaveStats*)c1->GetPrimitive("stats");
 stats1->SetName("SM");
 stats1->SetY1NDC(.05);
 stats1->SetY2NDC(.3);
 stats1->SetTextColor(3);
 stats1->SetTextSize(0.03);
 hist_e_angles_bsm->SetLineColor(4);
 hist_e_angles_bsm->SetLineWidth(3);
 hist_e_angles_bsm->Draw("HISTSAMES");
 c1->Update();
 gStyle->SetOptStat(11);
 TPaveStats *stats2 =(TPaveStats*)c1->GetPrimitive("stats");
 stats2->SetName("BSM");
 stats2->SetY1NDC(.05);
 stats2->SetY2NDC(.3);
 stats2->SetTextColor(4);
 stats2->SetTextSize(0.03);

 legend->Draw();

 /*gStyle->SetOptStat(11);
 hist_anue_angles->SetLineColor(2);
 hist_anue_angles->SetLineWidth(3);
 hist_anue_angles->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_nut_angles->SetLineColor(1);
 hist_nut_angles->SetLineWidth(3);
 hist_nut_angles->Draw("SAMES");*/

  /*TFile *outf = TFile::Open("tau_angles_e.root"); 
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 
 TH1F *hist_e_angles = (TH1F*) outf->Get("hist_e_angles");
 TH1F *hist_anue_angles = (TH1F*) outf->Get("hist_anue_angles");
 TH1F *hist_nut_angles = (TH1F*) outf->Get("hist_nut_angles");
 
 legend->AddEntry(hist_e_angles,"Electron");
 legend->AddEntry(hist_anue_angles,"Anti electron neutrino");
 legend->AddEntry(hist_nut_angles,"Tau neutrino");

 gStyle->SetOptStat(11);
 hist_e_angles->SetLineColor(3);
 hist_e_angles->SetLineWidth(3);
 hist_e_angles->GetXaxis()->SetTitle("Angle (deg)");
 hist_e_angles->GetYaxis()->SetTitle("Counts");
 hist_e_angles->SetTitle("Angle of decay products w.r.t Tau direction");
 hist_e_angles->GetXaxis()->CenterTitle(kTRUE);
 hist_e_angles->GetYaxis()->CenterTitle(kTRUE);
 hist_e_angles->Draw();
 gStyle->SetOptStat(11);
 hist_anue_angles->SetLineColor(2);
 hist_anue_angles->SetLineWidth(3);
 hist_anue_angles->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_nut_angles->SetLineColor(1);
 hist_nut_angles->SetLineWidth(3);
 hist_nut_angles->Draw("SAMES");

 legend->Draw();*/
}
