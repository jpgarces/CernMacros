void plot_tau_angles_pions(){

 TFile *outf = TFile::Open("tau_angles_pions_3ch.root"); 
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 
 TH1F *hist_pim_angles_3ch = (TH1F*) outf->Get("hist_pim_angles_3ch");
 TH1F *hist_nut_angles_3ch = (TH1F*) outf->Get("hist_nut_angles_3ch");
 TH1F *hist_pip_angles_3ch = (TH1F*) outf->Get("hist_pip_angles_3ch");
 //TH1F *hist_ph_angles_3ch = (TH1F*) outf->Get("hist_ph_angles_3ch");
 
 legend->AddEntry(hist_pim_angles_3ch,"Negative pion");
 legend->AddEntry(hist_pip_angles_3ch,"Positive pion");
 legend->AddEntry(hist_nut_angles_3ch,"Tau neutrino");
 //legend->AddEntry(hist_ph_angles_3ch,"Photon");

 gStyle->SetOptStat(11);
 hist_pim_angles_3ch->SetLineColor(3);
 hist_pim_angles_3ch->SetLineWidth(3);
 hist_pim_angles_3ch->GetXaxis()->SetTitle("Angles (deg)");
 hist_pim_angles_3ch->GetYaxis()->SetTitle("Counts");
 hist_pim_angles_3ch->SetTitle("#tau -> 2#pi^{-}#pi^{+}#nu_{#tau}");
 hist_pim_angles_3ch->GetXaxis()->CenterTitle(kTRUE);
 hist_pim_angles_3ch->GetYaxis()->CenterTitle(kTRUE);
 hist_pim_angles_3ch->Draw();
 hist_pim_angles_3ch->SetLineColor(4);
 hist_pim_angles_3ch->SetLineWidth(3);
 hist_pim_angles_3ch->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_pip_angles_3ch->SetLineColor(6);
 hist_pip_angles_3ch->SetLineWidth(3);
 hist_pip_angles_3ch->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_nut_angles_3ch->SetLineColor(1);
 hist_nut_angles_3ch->SetLineWidth(3);
 hist_nut_angles_3ch->Draw("SAMES");
 /*gStyle->SetOptStat(11);
 hist_ph_angles_3ch->SetLineColor(2);
 hist_ph_angles_3ch->SetLineWidth(3);
 hist_ph_angles_3ch->Draw("SAMES");*/

 legend->Draw();
}
