void plot_tau_angles(){

 TFile *outf = TFile::Open("tau_angles_e.root"); 
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

 legend->Draw();
}
