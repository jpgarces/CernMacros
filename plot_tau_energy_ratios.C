void plot_tau_energy_ratios(){

 TFile *outf = TFile::Open("tau_energy_e.root"); 
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 
 c1->Divide(1,2,0,0);

 c1->cd(1);

 TH1F *hist_tau_energy = (TH1F*) outf->Get("hist_tau_energy");
 TH1F *hist_e_energy = (TH1F*) outf->Get("hist_e_energy");
 TH1F *hist_anue_energy = (TH1F*) outf->Get("hist_anue_energy");
 TH1F *hist_nut_energy = (TH1F*) outf->Get("hist_nut_energy");
 TH1F *hist_eanue_ratio = new TH1F("hist_eanue_ratio ","hist_eanue_ratio ",100,0.0,60.0);
 
 legend->AddEntry(hist_tau_energy,"Tau energy");
 legend->AddEntry(hist_e_energy,"Electron energy");
 legend->AddEntry(hist_anue_energy,"Anti electron neutrino");
 legend->AddEntry(hist_nut_energy,"Tau neutrino");

 gStyle->SetOptStat(11);
 hist_tau_energy->SetLineColor(3);
 hist_tau_energy->SetLineWidth(3);
 hist_tau_energy->GetXaxis()->SetTitle("Energy (GeV)");
 hist_tau_energy->GetYaxis()->SetTitle("Counts");
 hist_tau_energy->SetTitle("Tau energy");
 hist_tau_energy->GetXaxis()->CenterTitle(kTRUE);
 hist_tau_energy->GetYaxis()->CenterTitle(kTRUE);
 hist_tau_energy->Draw();
 gStyle->SetOptStat(11);
 hist_e_energy->SetLineColor(4);
 hist_e_energy->SetLineWidth(3);
 hist_e_energy->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_anue_energy->SetLineColor(2);
 hist_anue_energy->SetLineWidth(3);
 hist_anue_energy->Draw("SAMES");
 gStyle->SetOptStat(11);
 hist_nut_energy->SetLineColor(1);
 hist_nut_energy->SetLineWidth(3);
 hist_nut_energy->Draw("SAMES");
 legend->Draw();

 c1->cd(2);
 hist_eanue_ratio->Divide(hist_e_energy,hist_anue_energy,1,1,"B");
 hist_eanue_ratio->Draw();
}
