void plot_tau_angles_pions(){

 TFile *f1 = TFile::Open("tau_angles_pions_1ch_sm.root");
 TFile *f2 = TFile::Open("tau_angles_pions_1ch_bsm.root");
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 
 TH1F *hist_pim_angles_1ch_sm = (TH1F*) f1->Get("hist_pim_angles_1ch");
 TH1F *hist_pim_angles_1ch_bsm = (TH1F*) f2->Get("hist_pim_angles_1ch");
 /*TH1F *hist_nut_angles_1ch = (TH1F*) outf->Get("hist_nut_angles_1ch");
 TH1F *hist_pip_angles_1ch = (TH1F*) outf->Get("hist_pip_angles_1ch");
 //TH1F *hist_ph_angles_1ch = (TH1F*) outf->Get("hist_ph_angles_1ch");*/
 
 legend->AddEntry(hist_pim_angles_1ch_sm,"SM negative pions");
 legend->AddEntry(hist_pim_angles_1ch_bsm,"BSM negative pions");
 /*legend->AddEntry(hist_pip_angles_1ch,"Positive pion");
 legend->AddEntry(hist_nut_angles_1ch,"Tau neutrino");
 //legend->AddEntry(hist_ph_angles_1ch,"Photon");*/

 gStyle->SetOptStat(11);
 hist_pim_angles_1ch_sm->SetLineColor(3);
 hist_pim_angles_1ch_sm->SetLineWidth(3);
 hist_pim_angles_1ch_sm->GetXaxis()->SetTitle("Angles (deg)");
 hist_pim_angles_1ch_sm->GetYaxis()->SetTitle("Counts");
 //hist_pim_angles_1ch_sm->SetTitle("#tau -> 2#pi^{-}#pi^{+}#nu_{#tau}");
 hist_pim_angles_1ch_sm->SetTitle("#tau -> #pi^{-}#nu_{#tau}");
 hist_pim_angles_1ch_sm->GetXaxis()->CenterTitle(kTRUE);
 hist_pim_angles_1ch_sm->GetYaxis()->CenterTitle(kTRUE);
 hist_pim_angles_1ch_sm->Draw();
 gStyle->SetOptStat(11);
 TPaveStats *stats1 =(TPaveStats*)c1->GetPrimitive("stats");
 stats1->SetName("SM");
 stats1->SetY1NDC(.05);
 stats1->SetY2NDC(.3);
 stats1->SetTextColor(3);
 stats1->SetTextSize(0.03);
 hist_pim_angles_1ch_bsm->SetLineColor(4);
 hist_pim_angles_1ch_bsm->SetLineWidth(3);
 hist_pim_angles_1ch_bsm->Draw("SAMES");
 c1->Update();
 gStyle->SetOptStat(11);
 TPaveStats *stats2 =(TPaveStats*)c1->GetPrimitive("stats");
 stats2->SetName("BSM");
 stats2->SetY1NDC(.05);
 stats2->SetY2NDC(.3);
 stats2->SetTextColor(4);
 stats2->SetTextSize(0.03);
 


 /*gStyle->SetOptStat(11);
 hist_pip_angles_1ch->SetLineColor(6);
 hist_pip_angles_1ch->SetLineWidth(3);
 hist_pip_angles_1ch->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_nut_angles_1ch->SetLineColor(1);
 hist_nut_angles_1ch->SetLineWidth(3);
 hist_nut_angles_1ch->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_ph_angles_1ch->SetLineColor(2);
 hist_ph_angles_1ch->SetLineWidth(3);
 hist_ph_angles_1ch->Draw("SAMES");*/

 legend->Draw();
}
