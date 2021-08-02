void plot_tau_PT(){

 TFile *outf = TFile::Open("tau_PT_e.root"); 
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 
 TH1F *hist_tau_PT = (TH1F*) outf->Get("hist_tau_PT");
 TH1F *hist_e_PT = (TH1F*) outf->Get("hist_e_PT");
 TH1F *hist_anue_PT = (TH1F*) outf->Get("hist_anue_PT");
 TH1F *hist_nut_PT = (TH1F*) outf->Get("hist_nut_PT");
 
 legend->AddEntry(hist_tau_PT,"Tau");
 legend->AddEntry(hist_e_PT,"Electron");
 legend->AddEntry(hist_anue_PT,"Anti electron neutrino");
 legend->AddEntry(hist_nut_PT,"Tau neutrino");

 gStyle->SetOptStat(11);
 hist_tau_PT->SetLineColor(3);
 hist_tau_PT->SetLineWidth(3);
 hist_tau_PT->GetXaxis()->SetTitle("P_{T} (GeV)");
 hist_tau_PT->GetYaxis()->SetTitle("Counts");
 hist_tau_PT->SetTitle("Tau P_{T}");
 hist_tau_PT->GetXaxis()->CenterTitle(kTRUE);
 hist_tau_PT->GetYaxis()->CenterTitle(kTRUE);
 hist_tau_PT->Draw();
 gStyle->SetOptStat(11);
 hist_e_PT->SetLineColor(4);
 hist_e_PT->SetLineWidth(3);
 hist_e_PT->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_anue_PT->SetLineColor(2);
 hist_anue_PT->SetLineWidth(3);
 hist_anue_PT->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_nut_PT->SetLineColor(1);
 hist_nut_PT->SetLineWidth(3);
 hist_nut_PT->Draw("SAMES");

 legend->Draw();
}
