void plot_ditau_PT(){

 TFile *outf2 = TFile::Open("ditau_PT_lep_nonu.root");
 TFile *outf = TFile::Open("ditau_PT_lep.root"); 
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 TH1F *hist_ditau_eep_PT_nonu = (TH1F*) outf2->Get("hist_ditau_eep_PT_nonu");
 TH1F *hist_ditau_emup_PT_nonu = (TH1F*) outf2->Get("hist_ditau_emup_PT_nonu");
 TH1F *hist_ditau_muep_PT_nonu = (TH1F*) outf2->Get("hist_ditau_muep_PT_nonu");
 TH1F *hist_ditau_mumup_PT_nonu = (TH1F*) outf2->Get("hist_ditau_mumup_PT_nonu");
 
 legend->AddEntry(hist_ditau_eep_PT_nonu,"tau-tau+ -> e-e+ (ignoring neutrinos)");
 legend->AddEntry(hist_ditau_emup_PT_nonu,"tau-tau+ -> e-mu+ (ignoring neutrinos)");
 legend->AddEntry(hist_ditau_muep_PT_nonu,"tau-tau+ -> mu-e+ (ignoring neutrinos)");
 legend->AddEntry(hist_ditau_mumup_PT_nonu,"tau-tau+ -> mu-mu+ (ignoring neutrinos)");

 gStyle->SetOptStat(11);
 hist_ditau_eep_PT_nonu->SetLineColor(3);
 hist_ditau_eep_PT_nonu->SetLineStyle(9);
 hist_ditau_eep_PT_nonu->SetLineWidth(3);
 hist_ditau_eep_PT_nonu->Draw();
 hist_ditau_eep_PT_nonu->GetXaxis()->SetTitle("di-tau P_{T} (GeV)");
 hist_ditau_eep_PT_nonu->GetYaxis()->SetTitle("Counts");
 hist_ditau_eep_PT_nonu->SetTitle("di-Tau PT");
 hist_ditau_eep_PT_nonu->GetXaxis()->CenterTitle(kTRUE);
 hist_ditau_eep_PT_nonu->GetYaxis()->CenterTitle(kTRUE);
 gStyle->SetOptStat(11);
 hist_ditau_emup_PT_nonu->SetLineColor(4);
 hist_ditau_emup_PT_nonu->SetLineStyle(9);
 hist_ditau_emup_PT_nonu->SetLineWidth(3);
 hist_ditau_emup_PT_nonu->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_ditau_muep_PT_nonu->SetLineColor(2);
 hist_ditau_muep_PT_nonu->SetLineStyle(9);
 hist_ditau_muep_PT_nonu->SetLineWidth(3);
 hist_ditau_muep_PT_nonu->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_ditau_mumup_PT_nonu->SetLineColor(1);
 hist_ditau_mumup_PT_nonu->SetLineStyle(9);
 hist_ditau_mumup_PT_nonu->SetLineWidth(3);
 hist_ditau_mumup_PT_nonu->Draw("SAMES");

 TH1F *hist_ditau_eep_PT = (TH1F*) outf->Get("hist_ditau_eep_PT");
 TH1F *hist_ditau_emup_PT = (TH1F*) outf->Get("hist_ditau_emup_PT");
 TH1F *hist_ditau_muep_PT = (TH1F*) outf->Get("hist_ditau_muep_PT");
 TH1F *hist_ditau_mumup_PT = (TH1F*) outf->Get("hist_ditau_mumup_PT");
 
 legend->AddEntry(hist_ditau_eep_PT,"tau-tau+ -> e-e+");
 legend->AddEntry(hist_ditau_emup_PT,"tau-tau+ -> e-mu+");
 legend->AddEntry(hist_ditau_muep_PT,"tau-tau+ -> mu-e+");
 legend->AddEntry(hist_ditau_mumup_PT,"tau-tau+ -> mu-mu+");

 gStyle->SetOptStat(11);
 hist_ditau_eep_PT->SetLineColor(3);
 hist_ditau_eep_PT->SetLineWidth(3);
 hist_ditau_eep_PT->Draw("SAME");
 gStyle->SetOptStat(11);
 hist_ditau_emup_PT->SetLineColor(4);
 hist_ditau_emup_PT->SetLineWidth(3);
 hist_ditau_emup_PT->Draw("SAME");
 gStyle->SetOptStat(11);
 hist_ditau_muep_PT->SetLineColor(2);
 hist_ditau_muep_PT->SetLineWidth(3);
 hist_ditau_muep_PT->Draw("SAME");
 gStyle->SetOptStat(11);
 hist_ditau_mumup_PT->SetLineColor(1);
 hist_ditau_mumup_PT->SetLineWidth(3);
 hist_ditau_mumup_PT->Draw("SAME");

 legend->Draw();
}
