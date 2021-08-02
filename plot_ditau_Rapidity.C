void plot_ditau_Rapidity(){

 TFile *outf2 = TFile::Open("ditau_Rapidity_lep_nonu.root");
 TFile *outf = TFile::Open("ditau_Rapidity_lep.root"); 
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 TH1F *hist_ditau_eep_Rapidity_nonu = (TH1F*) outf2->Get("hist_ditau_eep_Rapidity_nonu");
 TH1F *hist_ditau_emup_Rapidity_nonu = (TH1F*) outf2->Get("hist_ditau_emup_Rapidity_nonu");
 TH1F *hist_ditau_muep_Rapidity_nonu = (TH1F*) outf2->Get("hist_ditau_muep_Rapidity_nonu");
 TH1F *hist_ditau_mumup_Rapidity_nonu = (TH1F*) outf2->Get("hist_ditau_mumup_Rapidity_nonu");
 
 legend->AddEntry(hist_ditau_eep_Rapidity_nonu,"tau-tau+ -> e-e+ (ignoring neutrinos)");
 legend->AddEntry(hist_ditau_emup_Rapidity_nonu,"tau-tau+ -> e-mu+ (ignoring neutrinos)");
 legend->AddEntry(hist_ditau_muep_Rapidity_nonu,"tau-tau+ -> mu-e+ (ignoring neutrinos)");
 legend->AddEntry(hist_ditau_mumup_Rapidity_nonu,"tau-tau+ -> mu-mu+ (ignoring neutrinos)");

 gStyle->SetOptStat(11);
 hist_ditau_eep_Rapidity_nonu->SetLineColor(3);
 hist_ditau_eep_Rapidity_nonu->SetLineStyle(9);
 hist_ditau_eep_Rapidity_nonu->SetLineWidth(3);
 hist_ditau_eep_Rapidity_nonu->Draw();
 hist_ditau_eep_Rapidity_nonu->GetXaxis()->SetTitle("di-tau Rapidity");
 hist_ditau_eep_Rapidity_nonu->GetYaxis()->SetTitle("Counts");
 hist_ditau_eep_Rapidity_nonu->SetTitle("di-Tau Rapidity");
 hist_ditau_eep_Rapidity_nonu->GetXaxis()->CenterTitle(kTRUE);
 hist_ditau_eep_Rapidity_nonu->GetYaxis()->CenterTitle(kTRUE);
 gStyle->SetOptStat(11);
 hist_ditau_emup_Rapidity_nonu->SetLineColor(4);
 hist_ditau_emup_Rapidity_nonu->SetLineStyle(9);
 hist_ditau_emup_Rapidity_nonu->SetLineWidth(3);
 hist_ditau_emup_Rapidity_nonu->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_ditau_muep_Rapidity_nonu->SetLineColor(2);
 hist_ditau_muep_Rapidity_nonu->SetLineStyle(9);
 hist_ditau_muep_Rapidity_nonu->SetLineWidth(3);
 hist_ditau_muep_Rapidity_nonu->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_ditau_mumup_Rapidity_nonu->SetLineColor(1);
 hist_ditau_mumup_Rapidity_nonu->SetLineStyle(9);
 hist_ditau_mumup_Rapidity_nonu->SetLineWidth(3);
 hist_ditau_mumup_Rapidity_nonu->Draw("SAMES");

 TH1F *hist_ditau_eep_Rapidity = (TH1F*) outf->Get("hist_ditau_eep_Rapidity");
 TH1F *hist_ditau_emup_Rapidity = (TH1F*) outf->Get("hist_ditau_emup_Rapidity");
 TH1F *hist_ditau_muep_Rapidity = (TH1F*) outf->Get("hist_ditau_muep_Rapidity");
 TH1F *hist_ditau_mumup_Rapidity = (TH1F*) outf->Get("hist_ditau_mumup_Rapidity");
 
 legend->AddEntry(hist_ditau_eep_Rapidity,"tau-tau+ -> e-e+");
 legend->AddEntry(hist_ditau_emup_Rapidity,"tau-tau+ -> e-mu+");
 legend->AddEntry(hist_ditau_muep_Rapidity,"tau-tau+ -> mu-e+");
 legend->AddEntry(hist_ditau_mumup_Rapidity,"tau-tau+ -> mu-mu+");

 gStyle->SetOptStat(11);
 hist_ditau_eep_Rapidity->SetLineColor(3);
 hist_ditau_eep_Rapidity->SetLineWidth(3);
 hist_ditau_eep_Rapidity->Draw("SAME");
 gStyle->SetOptStat(11);
 hist_ditau_emup_Rapidity->SetLineColor(4);
 hist_ditau_emup_Rapidity->SetLineWidth(3);
 hist_ditau_emup_Rapidity->Draw("SAME");
 gStyle->SetOptStat(11);
 hist_ditau_muep_Rapidity->SetLineColor(2);
 hist_ditau_muep_Rapidity->SetLineWidth(3);
 hist_ditau_muep_Rapidity->Draw("SAME");
 gStyle->SetOptStat(11);
 hist_ditau_mumup_Rapidity->SetLineColor(1);
 hist_ditau_mumup_Rapidity->SetLineWidth(3);
 hist_ditau_mumup_Rapidity->Draw("SAME");

 legend->Draw();
}
