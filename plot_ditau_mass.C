void plot_ditau_mass(){

 TFile *outf2 = TFile::Open("ditau_mass_lep_nonu.root");
 TFile *outf = TFile::Open("ditau_mass_lep.root"); 
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 TH1F *hist_ditau_eep_mass_nonu = (TH1F*) outf2->Get("hist_ditau_eep_mass_nonu");
 TH1F *hist_ditau_emup_mass_nonu = (TH1F*) outf2->Get("hist_ditau_emup_mass_nonu");
 TH1F *hist_ditau_muep_mass_nonu = (TH1F*) outf2->Get("hist_ditau_muep_mass_nonu");
 TH1F *hist_ditau_mumup_mass_nonu = (TH1F*) outf2->Get("hist_ditau_mumup_mass_nonu");
 
 legend->AddEntry(hist_ditau_eep_mass_nonu,"tau-tau+ -> e-e+ (ignoring neutrinos)");
 legend->AddEntry(hist_ditau_emup_mass_nonu,"tau-tau+ -> e-mu+ (ignoring neutrinos)");
 legend->AddEntry(hist_ditau_muep_mass_nonu,"tau-tau+ -> mu-e+ (ignoring neutrinos)");
 legend->AddEntry(hist_ditau_mumup_mass_nonu,"tau-tau+ -> mu-mu+ (ignoring neutrinos)");

 gStyle->SetOptStat(11);
 hist_ditau_eep_mass_nonu->SetLineColor(3);
 hist_ditau_eep_mass_nonu->SetLineStyle(9);
 hist_ditau_eep_mass_nonu->SetLineWidth(3);
 hist_ditau_eep_mass_nonu->Draw();
 hist_ditau_eep_mass_nonu->GetXaxis()->SetTitle("di-tau mass (GeV)");
 hist_ditau_eep_mass_nonu->GetYaxis()->SetTitle("Counts");
 hist_ditau_eep_mass_nonu->SetTitle("di-Tau mass");
 hist_ditau_eep_mass_nonu->GetXaxis()->CenterTitle(kTRUE);
 hist_ditau_eep_mass_nonu->GetYaxis()->CenterTitle(kTRUE);
 gStyle->SetOptStat(11);
 hist_ditau_emup_mass_nonu->SetLineColor(4);
 hist_ditau_emup_mass_nonu->SetLineStyle(9);
 hist_ditau_emup_mass_nonu->SetLineWidth(3);
 hist_ditau_emup_mass_nonu->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_ditau_muep_mass_nonu->SetLineColor(2);
 hist_ditau_muep_mass_nonu->SetLineStyle(9);
 hist_ditau_muep_mass_nonu->SetLineWidth(3);
 hist_ditau_muep_mass_nonu->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_ditau_mumup_mass_nonu->SetLineColor(1);
 hist_ditau_mumup_mass_nonu->SetLineStyle(9);
 hist_ditau_mumup_mass_nonu->SetLineWidth(3);
 hist_ditau_mumup_mass_nonu->Draw("SAMES");

 TH1F *hist_ditau_eep_mass = (TH1F*) outf->Get("hist_ditau_eep_mass");
 TH1F *hist_ditau_emup_mass = (TH1F*) outf->Get("hist_ditau_emup_mass");
 TH1F *hist_ditau_muep_mass = (TH1F*) outf->Get("hist_ditau_muep_mass");
 TH1F *hist_ditau_mumup_mass = (TH1F*) outf->Get("hist_ditau_mumup_mass");
 
 legend->AddEntry(hist_ditau_eep_mass,"tau-tau+ -> e-e+");
 legend->AddEntry(hist_ditau_emup_mass,"tau-tau+ -> e-mu+");
 legend->AddEntry(hist_ditau_muep_mass,"tau-tau+ -> mu-e+");
 legend->AddEntry(hist_ditau_mumup_mass,"tau-tau+ -> mu-mu+");

 gStyle->SetOptStat(11);
 hist_ditau_eep_mass->SetLineColor(3);
 hist_ditau_eep_mass->SetLineWidth(3);
 hist_ditau_eep_mass->Draw("SAME");
 gStyle->SetOptStat(11);
 hist_ditau_emup_mass->SetLineColor(4);
 hist_ditau_emup_mass->SetLineWidth(3);
 hist_ditau_emup_mass->Draw("SAME");
 gStyle->SetOptStat(11);
 hist_ditau_muep_mass->SetLineColor(2);
 hist_ditau_muep_mass->SetLineWidth(3);
 hist_ditau_muep_mass->Draw("SAME");
 gStyle->SetOptStat(11);
 hist_ditau_mumup_mass->SetLineColor(1);
 hist_ditau_mumup_mass->SetLineWidth(3);
 hist_ditau_mumup_mass->Draw("SAME");

 legend->Draw();
}
