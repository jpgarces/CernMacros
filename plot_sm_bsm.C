void plot_sm_bsm(){

  /*TFile *f1 = TFile::Open("sm_hists.root");
 TFile *f2 = TFile::Open("bsm_hists.root");

 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);

 TH1F *tauLead_pt_sm = (TH1F*) f1->Get("tauLead_pt");
 TH1F *tauLead_pt_bsm = (TH1F*) f2->Get("tauLead_pt");

 legend->AddEntry(tauLead_pt_sm,"SM");
 legend->AddEntry(tauLead_pt_bsm,"BSM");

 tauLead_pt_sm->SetLineColor(3);
 tauLead_pt_sm->SetLineWidth(3);
 tauLead_pt_sm->Draw("HIST");
 //c1->Modified();
 //c1->Update();
 gStyle->SetOptStat(11);
 TPaveStats *stats1 =(TPaveStats*)c1->GetPrimitive("stats");
 stats1->SetName("SM");
 stats1->SetY1NDC(.05);
 stats1->SetY2NDC(.3);
 stats1->SetTextColor(3);
 stats1->SetTextSize(0.03);
 tauLead_pt_sm->GetXaxis()->SetTitle("P_{T} (GeV)");
 tauLead_pt_sm->GetYaxis()->SetTitle("Counts");
 tauLead_pt_sm->SetTitle("Leading Tau P_{T}");
 tauLead_pt_sm->GetXaxis()->CenterTitle(kTRUE);
 tauLead_pt_sm->GetYaxis()->CenterTitle(kTRUE);
 tauLead_pt_bsm->SetLineColor(4);
 tauLead_pt_bsm->SetLineWidth(3);
 tauLead_pt_bsm->Draw("HISTSAMES");
 c1->Update();
 gStyle->SetOptStat(11);
 TPaveStats *stats2 =(TPaveStats*)c1->GetPrimitive("stats");
 stats2->SetName("BSM");
 stats2->SetY1NDC(.05);
 stats2->SetY2NDC(.3);
 stats2->SetTextColor(4);
 stats2->SetTextSize(0.03);

 legend->Draw();*/

  
 TFile *f1 = TFile::Open("sm_hists.root");
 TFile *f2 = TFile::Open("bsm_hists.root");

 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);

 TH1F *di_tau_Mass_sm = (TH1F*) f1->Get("di_tau_Mass");
 TH1F *di_tau_Mass_bsm = (TH1F*) f2->Get("di_tau_Mass");

 legend->AddEntry(di_tau_Mass_sm,"SM electrons from tau decays");
 legend->AddEntry(di_tau_Mass_bsm,"BSM electrons from tau decays");

 di_tau_Mass_sm->SetLineColor(3);
 di_tau_Mass_sm->SetLineWidth(3);
 di_tau_Mass_sm->Draw("HIST");
 //c1->Modified();
 //c1->Update();
 gStyle->SetOptStat(11);
 TPaveStats *stats1 =(TPaveStats*)c1->GetPrimitive("stats");
 stats1->SetName("SM");
 stats1->SetY1NDC(.05);
 stats1->SetY2NDC(.3);
 stats1->SetTextColor(3);
 stats1->SetTextSize(0.03);
 di_tau_Mass_sm->GetXaxis()->SetTitle("Mass (GeV)");
 di_tau_Mass_sm->GetYaxis()->SetTitle("Counts");
 di_tau_Mass_sm->SetTitle("di-Tau Mass");
 di_tau_Mass_sm->GetXaxis()->CenterTitle(kTRUE);
 di_tau_Mass_sm->GetYaxis()->CenterTitle(kTRUE);
 di_tau_Mass_bsm->SetLineColor(4);
 di_tau_Mass_bsm->SetLineWidth(3);
 di_tau_Mass_bsm->Draw("HISTSAMES");
 c1->Update();
 gStyle->SetOptStat(11);
 TPaveStats *stats2 =(TPaveStats*)c1->GetPrimitive("stats");
 stats2->SetName("BSM");
 stats2->SetY1NDC(.05);
 stats2->SetY2NDC(.3);
 stats2->SetTextColor(4);
 stats2->SetTextSize(0.03);

 legend->Draw();
}
