void plot_dist(){

  /*TFile *outf = TFile::Open("electrons_PT.root"); 
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 //TH1F *taup_1ch10_2ph_ph_pt = (TH1F*) outf->Get("taup_1ch10_2ph_ph_pt");
 //TH1F *taup_1ch10_epeph_ph_pt = (TH1F*) outf->Get("taup_1ch10_epeph_ph_pt");
 //TH1F *taun_1ch10_2ph_ph_pt = (TH1F*) outf->Get("taun_1ch10_2ph_ph_pt");
 //TH1F *taun_1ch10_epeph_ph_pt = (TH1F*) outf->Get("taun_1ch10_epeph_ph_pt");
 TH1F *taun_1ch10_epeph_e_pt = (TH1F*) outf->Get("taun_1ch10_epeph_e_pt");
 TH1F *taup_1ch10_epeph_e_pt = (TH1F*) outf->Get("taup_1ch10_epeph_e_pt");
 //TH1F *taun_1ch10_epeph_ep_pt = (TH1F*) outf->Get("taun_1ch10_epeph_ep_pt");
 //TH1F *taup_1ch10_epeph_ep_pt = (TH1F*) outf->Get("taup_1ch10_epeph_ep_pt");
 //TH1F *hist_ph_all = (TH1F*) outf->Get("hist_ph_all");
 TH1F *hist_e_all = (TH1F*) outf->Get("hist_e_all");
 //TH1F *hist_ep_all = (TH1F*) outf->Get("hist_ep_all");

 //legend->AddEntry(taup_1ch10_2ph_ph_pt,"Positive tau decay into 1 pi+ and 1 pi0 -> 2 photons");
 //legend->AddEntry(taup_1ch10_epeph_ph_pt,"Positive tau decay into 1 pi+ and 1 pi0 -> e+ e- photon");
 //legend->AddEntry(taun_1ch10_2ph_ph_pt,"Negative tau decay into 1 pi- and 1 pi0 -> 2 photons");
 //legend->AddEntry(taun_1ch10_epeph_ph_pt,"Negative tau decay into 1 pi- and 1 pi0 -> e+ e- photon");
 //legend->AddEntry(hist_ph_all,"All photons");
 legend->AddEntry(taun_1ch10_epeph_e_pt,"Negative tau decay into 1 pi- and 1 pi0 -> e+ e- photon");
 legend->AddEntry(taup_1ch10_epeph_e_pt,"Positive tau decay into 1 pi- and 1 pi0 -> e+ e- photon");
 legend->AddEntry(hist_e_all,"All electrons");

 hist_e_all->SetLineColor(3);
 hist_e_all->SetLineWidth(3);
 hist_e_all->Draw("HIST");
 hist_e_all->GetXaxis()->SetTitle("P_{T} (GeV)");
 hist_e_all->GetYaxis()->SetTitle("Normalized Counts");
 hist_e_all->SetTitle("Tau decayss");
 hist_e_all->GetXaxis()->CenterTitle(kTRUE);
 hist_e_all->GetYaxis()->CenterTitle(kTRUE);
 taup_1ch10_epeph_e_pt->SetLineColor(4);
 taup_1ch10_epeph_e_pt->SetLineWidth(3);
 taup_1ch10_epeph_e_pt->Draw("HISTSAME");
 //taup_1ch10_2ph_e_pt->SetLineWidth(3);
 //taup_1ch10_2ph_e_pt->Draw("HISTSAME");
 //taun_1ch10_2ph_e_pt->SetLineColor(2);
 //taun_1ch10_2ph_e_pt->SetLineWidth(3);
 //taun_1ch10_2ph_e_pt->Draw("HISTSAME");
 taun_1ch10_epeph_e_pt->SetLineColor(1);
 taun_1ch10_epeph_e_pt->SetLineWidth(3);
 taun_1ch10_epeph_e_pt->Draw("HISTSAME");
 

 
 legend->Draw();*/
  

  /*TFile *outf = TFile::Open("tau_mass_pions_fstate.root"); 
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 TH1F *hist_taup_1ch10_2ph = (TH1F*) outf->Get("hist_taup_1ch10_2ph");
 TH1F *hist_taup_1ch10_epeph = (TH1F*) outf->Get("hist_taup_1ch10_epeph");
 TH1F *hist_taun_1ch10_2ph = (TH1F*) outf->Get("hist_taun_1ch10_2ph");
 TH1F *hist_taun_1ch10_epeph = (TH1F*) outf->Get("hist_taun_1ch10_epeph");
 TLine *l = new TLine(0.7755,0,0.7755,0.093);

 l->SetLineStyle(2);
 l->SetLineWidth(3);
 legend->AddEntry(hist_taup_1ch10_2ph,"Positive tau decay into 1 pi+ and 1 pi 0 -> 2 photons");
 legend->AddEntry(hist_taup_1ch10_epeph,"Positive tau decay into 1 pi+ and 1 pi0 -> e+ e- photon");
 legend->AddEntry(hist_taun_1ch10_2ph,"Negative tau decay into 1 pi- and 1 pi0 -> 2 photons");
 legend->AddEntry(hist_taun_1ch10_epeph,"Negative tau decay into 1 pi- and 1 pi0 -> e+ e- photon");

 hist_taup_1ch10_epeph->SetLineColor(6);
 hist_taup_1ch10_epeph->SetLineWidth(3);
 hist_taup_1ch10_epeph->Draw("HIST");
 hist_taup_1ch10_epeph->GetXaxis()->SetTitle("Mass (GeV)");
 hist_taup_1ch10_epeph->GetYaxis()->SetTitle("Normalized Counts");
 hist_taup_1ch10_epeph->SetTitle("Tau reconstructud mass from pions");
 hist_taup_1ch10_epeph->GetXaxis()->CenterTitle(kTRUE);
 hist_taup_1ch10_epeph->GetYaxis()->CenterTitle(kTRUE);
 hist_taun_1ch10_epeph->SetLineColor(4);
 hist_taun_1ch10_epeph->SetLineWidth(3);
 hist_taun_1ch10_epeph->Draw("HISTSAME");
 hist_taup_1ch10_2ph->SetLineColor(2);
 hist_taup_1ch10_2ph->SetLineWidth(3);
 hist_taup_1ch10_2ph->Draw("HISTSAME");
 hist_taun_1ch10_2ph->SetLineColor(1);
 hist_taun_1ch10_2ph->SetLineWidth(3);
 hist_taun_1ch10_2ph->Draw("HISTSAME");

 
 legend->Draw();*/

  /*TFile *outf = TFile::Open("tau_mass_leptons.root"); 
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 TH1F *hist_taum_e = (TH1F*) outf->Get("hist_taum_e");
 TH1F *hist_taup_ep = (TH1F*) outf->Get("hist_taup_ep");
 TH1F *hist_taum_mu = (TH1F*) outf->Get("hist_taum_mu");
 TH1F *hist_taup_mup = (TH1F*) outf->Get("hist_taup_mup");
 //TLine *l = new TLine(0.7755,0,0.7755,0.093);

 //l->SetLineStyle(2);
 //l->SetLineWidth(3);
 legend->AddEntry(hist_taum_e,"Positive tau reconstructed mass (positron)");
 legend->AddEntry(hist_taup_ep,"Negative tau reconstructed mass (electron)");
 legend->AddEntry(hist_taum_mu,"Positive tau reconstructed mass (muon)");
 legend->AddEntry(hist_taup_mup,"Negative tau reconstructed mass (positive muon)");
 
 
 hist_taum_e->SetLineColor(6);
 hist_taum_e->SetLineWidth(3);
 hist_taum_e->Draw("HIST");
 hist_taum_e->GetXaxis()->SetTitle("Mass (GeV)");
 hist_taum_e->GetYaxis()->SetTitle("Normalized Counts");
 hist_taum_e->SetTitle("Tau reconstructud mass from leptons");
 hist_taum_e->GetXaxis()->CenterTitle(kTRUE);
 hist_taum_e->GetYaxis()->CenterTitle(kTRUE);
 hist_taup_ep->SetLineColor(2);
 hist_taup_ep->SetLineWidth(3);
 hist_taup_ep->Draw("HISTSAME");
 hist_taum_mu->SetLineColor(1);
 hist_taum_mu->SetLineWidth(3);
 hist_taum_mu->Draw("HISTSAME");
 hist_taup_mup->SetLineColor(4);
 hist_taup_mup->SetLineWidth(3);
 hist_taup_mup->Draw("HISTSAME");
 
 legend->Draw();*/

  
  /*TFile *outf = TFile::Open("tau_mass_pions.root"); 
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 TH1F *hist_taup_1ch = (TH1F*) outf->Get("hist_taup_1ch");
 TH1F *hist_taum_1ch = (TH1F*) outf->Get("hist_taum_1ch");
 TH1F *hist_taup_3ch = (TH1F*) outf->Get("hist_taup_3ch");
 TH1F *hist_taum_3ch = (TH1F*) outf->Get("hist_taum_3ch");
 //TLine *l = new TLine(0.7755,0,0.7755,0.093);

 //l->SetLineStyle(2);
 //l->SetLineWidth(3);
 legend->AddEntry(hist_taup_1ch,"Positive tau reconstructed mass (1 charged pion decay)");
 legend->AddEntry(hist_taum_1ch,"Negative tau reconstructed mass (1 charged pion decay)");
 legend->AddEntry(hist_taup_3ch,"Positive tau reconstructed mass (3 charged pions decay)");
 legend->AddEntry(hist_taum_3ch,"Negative tau reconstructed mass (3 charged pions decay)");
 
 
 hist_taup_1ch->SetLineColor(6);
 hist_taup_1ch->SetLineWidth(3);
 hist_taup_1ch->Draw("HIST");
 hist_taup_1ch->GetXaxis()->SetTitle("Mass (GeV)");
 hist_taup_1ch->GetYaxis()->SetTitle("Normalized Counts");
 hist_taup_1ch->SetTitle("Tau reconstructud mass from pions");
 hist_taup_1ch->GetXaxis()->CenterTitle(kTRUE);
 hist_taup_1ch->GetYaxis()->CenterTitle(kTRUE);
 hist_taum_1ch->SetLineColor(2);
 hist_taum_1ch->SetLineWidth(3);
 hist_taum_1ch->Draw("HISTSAME");
 hist_taup_3ch->SetLineColor(1);
 hist_taup_3ch->SetLineWidth(3);
 hist_taup_3ch->Draw("HISTSAME");
 hist_taum_3ch->SetLineColor(4);
 hist_taum_3ch->SetLineWidth(3);
 hist_taum_3ch->Draw("HISTSAME");
 
 legend->Draw();
 //l->Draw();*/
  
 /*TFile *outf = TFile::Open("rho_mass.root"); 
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 TH1F *hist_rhop_m = (TH1F*) outf->Get("hist_rhop_m");
 TH1F *hist_rhom_m = (TH1F*) outf->Get("hist_rhom_m");
 TH1F *hist_rho0_m = (TH1F*) outf->Get("hist_rho0_m");
 TLine *l = new TLine(0.7755,0,0.7755,0.093);

 l->SetLineStyle(2);
 l->SetLineWidth(3);
 legend->AddEntry(hist_rhop_m,"Positive rho reconstructed mass");
 legend->AddEntry(hist_rhom_m,"Negative rho reconstructed mass");
 legend->AddEntry(hist_rho0_m,"Neutral rho reconstructed mass");
 
 hist_rhop_m->SetLineColor(4);
 hist_rhop_m->SetLineWidth(3);
 hist_rhop_m->Draw("HIST");
 hist_rhop_m->GetXaxis()->SetTitle("Mass (GeV)");
 hist_rhop_m->GetYaxis()->SetTitle("Normalized Counts");
 hist_rhop_m->SetTitle("Rho reconstructud mass from pions");
 hist_rhop_m->GetXaxis()->CenterTitle(kTRUE);
 hist_rhop_m->GetYaxis()->CenterTitle(kTRUE);
 hist_rhom_m->SetLineColor(1);
 hist_rhom_m->SetLineWidth(3);
 hist_rhom_m->Draw("HISTSAME");
 hist_rho0_m->SetLineColor(2);
 hist_rho0_m->SetLineWidth(3);
 hist_rho0_m->Draw("HISTSAME");
 legend->Draw();
 l->Draw();*/

 /*TFile *outf = TFile::Open("rho_Phi.root");
 TFile *outf1 = TFile::Open("pions_Phi.root");
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 TH1F *hist_pip_tau_phi = (TH1F*) outf1->Get("hist_pip_tau_phi");
 TH1F *hist_pim_tau_phi = (TH1F*) outf->Get("hist_pim_tau_phi");
 TH1F *hist_pip_tau_phi_3 = (TH1F*) outf1->Get("hist_pip_tau_phi_3");
 TH1F *hist_pim_tau_phi_3 = (TH1F*) outf->Get("hist_pim_tau_phi_3");
 TH1F *hist_pip_else_phi = (TH1F*) outf1->Get("hist_pip_else_phi");
 TH1F *hist_rhop = (TH1F*) outf->Get("hist_rhop");
 TH1F *hist_rhom = (TH1F*) outf->Get("hist_rhom");
 TH1F *hist_rho0 = (TH1F*) outf->Get("hist_rho0");

 legend->AddEntry(hist_rhop,"Positive pions from rho decays");
 legend->AddEntry(hist_rhom,"Negative pions from rho decays");
 legend->AddEntry(hist_rho0,"Neutral pions not from rho decays");
 
 hist_rhop->SetLineColor(4);
 hist_rhop->SetLineWidth(3);
 hist_rhop->Draw("HIST");
 hist_rhop->GetXaxis()->SetTitle("P_{T} (GeV)");
 hist_rhop->GetYaxis()->SetTitle("Normalized Counts");
 hist_rhop->GetXaxis()->CenterTitle(kTRUE);
 hist_rhop->GetYaxis()->CenterTitle(kTRUE);
 hist_rhom->SetLineColor(1);
 hist_rhom->SetLineWidth(3);
 hist_rhom->Draw("HISTSAME");
 hist_rho0->SetLineColor(2);
 hist_rho0->SetLineWidth(3);
 hist_rho0->Draw("HISTSAME");
 legend->Draw();*/

 /*TFile *outf1 = TFile::Open("electron_Eta.root");
 //TFile *outf2 = TFile::Open("positron_PT.root");
 //TFile *outf3 = TFile::Open("muon_Eta.root");
 TCanvas *c1 = new TCanvas();
 TH1F *hist_e_tau_eta = (TH1F*) outf1->Get("hist_e_tau_eta");
 TH1F *hist_ep_tau_eta = (TH1F*) outf1->Get("hist_ep_tau_eta");
 TH1F *hist_e_else_eta = (TH1F*) outf1->Get("hist_e_else_eta");
 TH1F *hist_ep_else_eta = (TH1F*) outf1->Get("hist_ep_else_eta");
  TH1F *hist_mup_tau_eta = (TH1F*) outf3->Get("hist_mup_tau_eta");
 TH1F *hist_mu_tau_eta = (TH1F*) outf3->Get("hist_mu_tau_eta");
 TH1F *hist_mup_else_eta = (TH1F*) outf3->Get("hist_mup_else_eta")
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);

 legend->AddEntry(hist_e_tau_eta,"Electrons from tau decays");
 legend->AddEntry(hist_ep_tau_eta,"Positrons from tau decays");
 legend->AddEntry(hist_e_else_eta,"Electrons not from tau decays");
 legend->AddEntry(hist_ep_else_eta,"Positrons not from tau decays");
 legend->AddEntry(hist_mu_tau_eta,"Muons from tau decays");
 legend->AddEntry(hist_mup_tau_eta,"Positive muons from tau decays");
 legend->AddEntry(hist_mu_else_eta,"Muons not from tau decays");
 legend->AddEntry(hist_mup_else_eta,"Positive muons not from tau decays");
 
 
 hist_e_else_eta->SetLineColor(1);
 hist_e_else_eta->SetLineWidth(3);
 hist_e_else_eta->Draw("HIST");
 hist_e_else_eta->GetXaxis()->SetTitle("P_{T}");
 hist_e_else_eta->GetYaxis()->SetTitle("Counts");
 hist_e_else_eta->GetXaxis()->CenterTitle(kTRUE);
 hist_e_else_eta->GetYaxis()->CenterTitle(kTRUE);
 gStyle->SetOptStat(11);
 hist_ep_else_eta->SetLineColor(2);
 hist_ep_else_eta->SetLineWidth(3);
 hist_ep_else_eta->Draw("HISTSAMES");
 gStyle->SetOptStat(11);
  hist_e_tau_eta->SetLineColor(3);
 hist_e_tau_eta->SetLineWidth(3);
 hist_e_tau_eta->Draw("HISTSAMES");
 gStyle->SetOptStat(11);
 hist_ep_tau_eta->SetLineColor(4);
 hist_ep_tau_eta->SetLineWidth(3);
 hist_ep_tau_eta->Draw("HISTSAMES");
 //gStyle->SetOptStat(11);
 hist_mup_tau_eta->SetLineColor(95);
 hist_mup_tau_eta->SetLineWidth(3);
 hist_mup_tau_eta->Draw("HIST");
 hist_mup_tau_eta->GetXaxis()->SetTitle("P_{T}");
 hist_mup_tau_eta->GetYaxis()->SetTitle("Counts");
 hist_mup_tau_eta->GetXaxis()->CenterTitle(kTRUE);
 hist_mup_tau_eta->GetYaxis()->CenterTitle(kTRUE);
 gStyle->SetOptStat(11);
 hist_mu_else_eta->SetLineColor(6);
 hist_mu_else_eta->SetLineWidth(3);
 hist_mu_else_eta->Draw("HISTSAMES");
 gStyle->SetOptStat(11);
 hist_mup_else_eta->SetLineColor(7);
 hist_mup_else_eta->SetLineWidth(3);
 hist_mup_else_eta->Draw("HISTSAMES");
 gStyle->SetOptStat(11);
 hist_mu_tau_eta->SetLineColor(209);
 hist_mu_tau_eta->SetLineWidth(3);
 hist_mu_tau_eta->Draw("HISTSAMES");
 legend->Draw();*/


 TFile *outf1 = TFile::Open("pions_Eta.root");
 TFile *outf = TFile::Open("rho_Eta.root");
 TCanvas *c1 = new TCanvas();
 TH1F *hist_pip_tau_eta = (TH1F*) outf1->Get("hist_pip_tau_eta");
 //TH1F *hist_pim_tau_eta = (TH1F*) outf->Get("hist_pim_tau_eta");
 TH1F *hist_pip_tau_eta_3 = (TH1F*) outf1->Get("hist_pip_tau_eta_3");
 //TH1F *hist_pim_tau_eta_3 = (TH1F*) outf->Get("hist_pim_tau_eta_3");
 TH1F *hist_pip_else_eta = (TH1F*) outf1->Get("hist_pip_else_eta");
 //TH1F *hist_pim_else_eta = (TH1F*) outf->Get("hist_pim_else_eta");
 TH1F *hist_rhop = (TH1F*) outf->Get("hist_rhop");
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);

 legend->AddEntry(hist_pip_tau_eta,"Positive pions from tau 1ch-decays");
 //legend->AddEntry(hist_pim_tau_eta,"Negative pions from tau 1ch-decays");
 legend->AddEntry(hist_pip_else_eta,"Positive pions not from tau decays");
 //legend->AddEntry(hist_pim_else_eta,"Negative pions not from tau decays");
 legend->AddEntry(hist_pip_tau_eta_3,"Positive pions from tau 3ch-decays");
 //legend->AddEntry(hist_pim_tau_eta_3,"Negative pions from tau 3ch-decays");
 legend->AddEntry(hist_rhop,"Positive pions from rho decays");

 hist_pip_else_eta->SetLineColor(1);
 hist_pip_else_eta->SetLineWidth(3);
 hist_pip_else_eta->Draw("HIST");
 hist_pip_else_eta->GetXaxis()->SetTitle("#eta");
 hist_pip_else_eta->GetYaxis()->SetTitle("Counts");
 hist_pip_else_eta->GetXaxis()->CenterTitle(kTRUE);
 hist_pip_else_eta->GetYaxis()->CenterTitle(kTRUE);
 gStyle->SetOptStat(11);
 hist_pip_tau_eta->SetLineColor(3);
 hist_pip_tau_eta->SetLineWidth(3);
 hist_pip_tau_eta->Draw("HISTSAMES");
 hist_pip_tau_eta->Draw("HISTSAME");
 hist_pip_tau_eta->GetXaxis()->SetTitle("#eta");
 hist_pip_tau_eta->GetYaxis()->SetTitle("Normalized Counts");
 hist_pip_tau_eta->GetXaxis()->CenterTitle(kTRUE);
 hist_pip_tau_eta->GetYaxis()->CenterTitle(kTRUE);
 gStyle->SetOptStat(11);
 hist_rhop->SetLineColor(4);
 hist_rhop->SetLineWidth(3);
 hist_rhop->Draw("HISTSAMES");
 /*hist_pim_else_eta->SetLineColor(2);
 hist_pim_else_eta->SetLineWidth(3);
 hist_pim_else_eta->Draw("HISTSAME");
 hist_pim_tau_eta->SetLineColor(4);
 hist_pim_tau_eta->SetLineWidth(3);
 hist_pim_tau_eta->Draw("HISTSAME");
 hist_pim_tau_eta_3->SetLineColor(7);
 hist_pim_tau_eta_3->SetLineWidth(3);
 hist_pim_tau_eta_3->Draw("HISTSAME");*/
 gStyle->SetOptStat(11);
 hist_pip_tau_eta_3->SetLineColor(6);
 hist_pip_tau_eta_3->SetLineWidth(3);
 hist_pip_tau_eta_3->Draw("HISTSAMES");
 legend->Draw();
}
