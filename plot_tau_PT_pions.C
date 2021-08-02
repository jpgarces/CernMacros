void plot_tau_PT_pions(){

 TFile *outf = TFile::Open("tau_PT_pions_3ch.root"); 
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 
 TH1F *hist_tau_PT_3ch = (TH1F*) outf->Get("hist_tau_PT_3ch");
 TH1F *hist_pim_PT_3ch = (TH1F*) outf->Get("hist_pim_PT_3ch");
 TH1F *hist_nut_PT_3ch = (TH1F*) outf->Get("hist_nut_PT_3ch");
 TH1F *hist_pip_PT_3ch = (TH1F*) outf->Get("hist_pip_PT_3ch");
 //TH1F *hist_ph_PT_3ch = (TH1F*) outf->Get("hist_ph_PT_3ch");
 
 legend->AddEntry(hist_tau_PT_3ch,"Tau");
 legend->AddEntry(hist_pim_PT_3ch,"Negative pion");
 legend->AddEntry(hist_pip_PT_3ch,"Positive pion");
 legend->AddEntry(hist_nut_PT_3ch,"Tau neutrino");
 //legend->AddEntry(hist_ph_PT_3ch,"Photon");

 gStyle->SetOptStat(11);
 hist_tau_PT_3ch->SetLineColor(3);
 hist_tau_PT_3ch->SetLineWidth(3);
 hist_tau_PT_3ch->GetXaxis()->SetTitle("P_{T} (GeV)");
 hist_tau_PT_3ch->GetYaxis()->SetTitle("Counts");
 hist_tau_PT_3ch->SetTitle("#tau -> #pi^{-}#nu_{#tau} -> #pi^{-}#nu_{#tau}");
 hist_tau_PT_3ch->GetXaxis()->CenterTitle(kTRUE);
 hist_tau_PT_3ch->GetYaxis()->CenterTitle(kTRUE);
 hist_tau_PT_3ch->Draw();
 gStyle->SetOptStat(11);
 hist_pim_PT_3ch->SetLineColor(4);
 hist_pim_PT_3ch->SetLineWidth(3);
 hist_pim_PT_3ch->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_pip_PT_3ch->SetLineColor(6);
 hist_pip_PT_3ch->SetLineWidth(3);
 hist_pip_PT_3ch->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_nut_PT_3ch->SetLineColor(1);
 hist_nut_PT_3ch->SetLineWidth(3);
 hist_nut_PT_3ch->Draw("SAMES");
 /*gStyle->SetOptStat(11);
 hist_ph_PT_3ch->SetLineColor(2);
 hist_ph_PT_3ch->SetLineWidth(3);
 hist_ph_PT_3ch->Draw("SAMES");*/

 legend->Draw();

 TCanvas *c2 = new TCanvas();
 TLegend *legend2 = new TLegend(0.65,0.7,0.85,0.85);
 
 TH1F *hist_tau_PT_3ch10 = (TH1F*) outf->Get("hist_tau_PT_3ch10");
 TH1F *hist_pim_PT_3ch10 = (TH1F*) outf->Get("hist_pim_PT_3ch10");
 TH1F *hist_nut_PT_3ch10 = (TH1F*) outf->Get("hist_nut_PT_3ch10");
 TH1F *hist_pip_PT_3ch10 = (TH1F*) outf->Get("hist_pip_PT_3ch10");
 TH1F *hist_ph_PT_3ch10 = (TH1F*) outf->Get("hist_ph_PT_3ch10");
 
 legend2->AddEntry(hist_tau_PT_3ch10,"Tau");
 legend2->AddEntry(hist_pim_PT_3ch10,"Negative pion");
 legend2->AddEntry(hist_pip_PT_3ch10,"Positive pion");
 legend2->AddEntry(hist_nut_PT_3ch10,"Tau neutrino");
 legend2->AddEntry(hist_ph_PT_3ch10,"Photon");

 gStyle->SetOptStat(11);
 hist_tau_PT_3ch10->SetLineColor(3);
 hist_tau_PT_3ch10->SetLineWidth(3);
 hist_tau_PT_3ch10->GetXaxis()->SetTitle("P_{T} (GeV)");
 hist_tau_PT_3ch10->GetYaxis()->SetTitle("Counts");
 hist_tau_PT_3ch10->SetTitle("#tau -> #pi^{-}#pi^{0}#nu_{#tau} -> #pi^{-}2#gamma#nu_{#tau}");
 hist_tau_PT_3ch10->GetXaxis()->CenterTitle(kTRUE);
 hist_tau_PT_3ch10->GetYaxis()->CenterTitle(kTRUE);
 hist_tau_PT_3ch10->Draw();
 gStyle->SetOptStat(11);
 hist_pim_PT_3ch10->SetLineColor(4);
 hist_pim_PT_3ch10->SetLineWidth(3);
 hist_pim_PT_3ch10->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_pip_PT_3ch10->SetLineColor(6);
 hist_pip_PT_3ch10->SetLineWidth(3);
 hist_pip_PT_3ch10->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_nut_PT_3ch10->SetLineColor(1);
 hist_nut_PT_3ch10->SetLineWidth(3);
 hist_nut_PT_3ch10->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_ph_PT_3ch10->SetLineColor(2);
 hist_ph_PT_3ch10->SetLineWidth(3);
 hist_ph_PT_3ch10->Draw("SAMES");

 legend2->Draw();

 TCanvas *c3 = new TCanvas();
 TLegend *legend3 = new TLegend(0.65,0.7,0.85,0.85);
 
 TH1F *hist_tau_PT_3ch20 = (TH1F*) outf->Get("hist_tau_PT_3ch20");
 TH1F *hist_pim_PT_3ch20 = (TH1F*) outf->Get("hist_pim_PT_3ch20");
 TH1F *hist_nut_PT_3ch20 = (TH1F*) outf->Get("hist_nut_PT_3ch20");
 TH1F *hist_pip_PT_3ch20 = (TH1F*) outf->Get("hist_pip_PT_3ch20");
 TH1F *hist_ph_PT_3ch20 = (TH1F*) outf->Get("hist_ph_PT_3ch20");
 
 legend3->AddEntry(hist_tau_PT_3ch20,"Tau");
 legend3->AddEntry(hist_pim_PT_3ch20,"Negative pion");
 legend3->AddEntry(hist_pip_PT_3ch20,"Positive pion");
 legend3->AddEntry(hist_nut_PT_3ch20,"Tau neutrino");
 legend3->AddEntry(hist_ph_PT_3ch20,"Photon");

 gStyle->SetOptStat(11);
 hist_tau_PT_3ch20->SetLineColor(3);
 hist_tau_PT_3ch20->SetLineWidth(3);
 hist_tau_PT_3ch20->GetXaxis()->SetTitle("P_{T} (GeV)");
 hist_tau_PT_3ch20->GetYaxis()->SetTitle("Counts");
 hist_tau_PT_3ch20->SetTitle("#tau -> #pi^{-}2#pi^{0}#nu_{#tau} -> #pi^{-}4#gamma#nu_{#tau}");
 hist_tau_PT_3ch20->GetXaxis()->CenterTitle(kTRUE);
 hist_tau_PT_3ch20->GetYaxis()->CenterTitle(kTRUE);
 hist_tau_PT_3ch20->Draw();
 gStyle->SetOptStat(11);
 hist_pim_PT_3ch20->SetLineColor(4);
 hist_pim_PT_3ch20->SetLineWidth(3);
 hist_pim_PT_3ch20->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_pip_PT_3ch20->SetLineColor(6);
 hist_pip_PT_3ch20->SetLineWidth(3);
 hist_pip_PT_3ch20->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_nut_PT_3ch20->SetLineColor(1);
 hist_nut_PT_3ch20->SetLineWidth(3);
 hist_nut_PT_3ch20->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_ph_PT_3ch20->SetLineColor(2);
 hist_ph_PT_3ch20->SetLineWidth(3);
 hist_ph_PT_3ch20->Draw("SAMES");

 legend3->Draw();
}
