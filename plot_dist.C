
void plot_dist(){

 TFile *f1 = TFile::Open("fid_PT_sm.root");
 TCanvas *c1 = new TCanvas("c1","c1",500,400);
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 TLine *l = new TLine(0.0,1.0,20.0,1.0);

 TH1F *hist_lep_PT = (TH1F*) f1->Get("hist_lep_PT_fid");
 TH1F *hist_pi_PT= (TH1F*) f1->Get("hist_pi_PT_fid");
 TH1F *hist_3pi_PT= (TH1F*) f1->Get("hist_3pi_PT_fid");
 TH1F *hist_sum_PT= (TH1F*) f1->Get("hist_sum_PT_fid");
 
 legend->AddEntry(hist_lep_PT,"#tau_{l}#tau_{1ch}, 1ch=lepton");
 legend->AddEntry(hist_pi_PT,"#tau_{l}#tau_{1ch}, 1ch=#pi");
 legend->AddEntry(hist_3pi_PT,"#tau_{l}#tau_{3ch}");
 legend->AddEntry(hist_sum_PT,"sum");

 gPad->SetLogy();
 hist_lep_PT->SetLineColor(1);
 hist_lep_PT->SetLineWidth(3);
 //hist_lep_PT->SetMarkerStyle(20);
 //hist_lep_PT->SetMarkerColor(1);
 //hist_lep_PT->SetMarkerSize(1);
 hist_lep_PT->GetYaxis()->SetMaxDigits(3);
 //hist_lep_PT->Scale(5.0/0.0015);
 hist_lep_PT->Draw("HIST");
 gStyle->SetOptStat(10);
 TPaveStats *stats1 =(TPaveStats*)c1->GetPrimitive("stats");
 stats1->SetName("SM");
 stats1->SetY1NDC(.05);
 stats1->SetY2NDC(.3);
 stats1->SetTextColor(1);
 stats1->SetTextSize(0.025);
 hist_lep_PT->GetXaxis()->SetTitle("p_{T}^{lead lepton} (GeV)");
 //hist_lep_PT->GetXaxis()->SetNdivisions(0);
 hist_lep_PT->GetYaxis()->SetTitle("Counts");
 hist_lep_PT->GetXaxis()->SetRangeUser(4.0,20.0);
 hist_lep_PT->GetYaxis()->SetRangeUser(1,1000);
 //hist_lep_PT->GetYaxis()->SetRangeUser(0,450.0);
 hist_lep_PT->GetXaxis()->SetMaxDigits(3);
 //hist_lep_PT->SetTitle(" P_{T}");
 //hist_lep_PT->SetTitleSize(25);
 hist_lep_PT->GetXaxis()->CenterTitle(kTRUE);
 hist_lep_PT->GetYaxis()->CenterTitle(kTRUE);
 hist_pi_PT->SetLineColor(2);
 hist_pi_PT->SetLineWidth(3);
 //hist_pi_PT->SetMarkerStyle(23);
 //hist_pi_PT->SetMarkerSize(1);
 //hist_pi_PT->SetMarkerColor(2);
 //hist_pi_PT->Scale(5.0/0.0016);
 hist_pi_PT->Draw("HISTSAMES");
 gStyle->SetOptStat(10);
 TPaveStats *stats2 =(TPaveStats*)c1->GetPrimitive("stats");
 stats2->SetName("BSM");
 stats2->SetY1NDC(.05);
 stats2->SetY2NDC(.3);
 stats2->SetTextColor(2);
 stats2->SetTextSize(0.025);
 hist_3pi_PT->SetLineColor(3);
 hist_3pi_PT->SetLineWidth(3);
 //hist_3pi_PT->SetMarkerStyle(23);
 //hist_3pi_PT->SetMarkerSize(1);
 //hist_3pi_PT->SetMarkerColor(3);
 //hist_3pi_PT->Scale(5.0/0.0016);
 hist_3pi_PT->Draw("HISTSAMES");
 gStyle->SetOptStat(10);
 TPaveStats *stats3 =(TPaveStats*)c1->GetPrimitive("stats");
 stats3->SetName("Bkg");
 stats3->SetY1NDC(.05);
 stats3->SetY2NDC(.3);
 stats3->SetTextColor(3);
 stats3->SetTextSize(0.025);
 hist_sum_PT->SetLineColor(4);
 hist_sum_PT->SetLineWidth(3);
 //hist_sum_PT->SetMarkerStyle(23);
 //hist_sum_PT->SetMarkerSize(1);
 //hist_sum_PT->SetMarkerColor(3);
 //hist_sum_PT->Scale(5.0/0.0016);
 hist_sum_PT->Draw("HISTSAMES");
 gStyle->SetOptStat(10);
 TPaveStats *stats4 =(TPaveStats*)c1->GetPrimitive("stats");
 stats4->SetName("Bkg");
 stats4->SetY1NDC(.05);
 stats4->SetY2NDC(.3);
 stats4->SetTextColor(4);
 stats4->SetTextSize(0.025);
 
 legend->Draw();
  
  /*TFile *f1 = TFile::Open("e_mu_PT_sm.root");
 TFile *f2 = TFile::Open("e_mu_PT_bsm.root");
 TFile *f3 = TFile::Open("e_mu_PT_bkg.root");
 TCanvas *c1 = new TCanvas("c1","c1",500,400);
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 TLine *l = new TLine(0.0,1.0,20.0,1.0);

 TH1F *hist_mu_PT_sm = (TH1F*) f1->Get("hist_mu_PT");
 TH1F *hist_mu_PT_bsm= (TH1F*) f2->Get("hist_mu_PT");
 TH1F *hist_mu_PT_bkg= (TH1F*) f3->Get("hist_mu_PT");
 TH1F *hist_sm_bsm_ratio = new TH1F("hist_sm_bsm_ratio ","hist_sm_bsm_ratio ",200,0.0,100.0);
 
 legend->AddEntry(hist_mu_PT_sm,"SM");
 legend->AddEntry(hist_mu_PT_bsm,"SM+BSM");
 legend->AddEntry(hist_mu_PT_bkg,"Bkg");

 TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
 TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.25);

 pad1->Draw();
 pad2->Draw();
 
 pad2->cd();
 //l->SetLineStyle(9);
 l->SetLineWidth(1);
 l->SetLineColor(kRed);
 hist_sm_bsm_ratio->Divide(hist_mu_PT_bsm,hist_mu_PT_sm,1,1,"B");
 //hist_sm_bsm_ratio->Divide(hist_mu_PT_sm,hist_mu_PT_bsm);
 hist_sm_bsm_ratio->GetXaxis()->SetTitle("P_{T} (GeV)");
 hist_sm_bsm_ratio->SetTitle("");
 hist_sm_bsm_ratio->GetXaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetYaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetXaxis()->SetTitleSize(0.15);
 hist_sm_bsm_ratio->GetXaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetNdivisions(5);
 hist_sm_bsm_ratio->GetYaxis()->SetTitle("SM+BSM/SM");
 hist_sm_bsm_ratio->GetYaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->SetMarkerStyle(21);
 hist_sm_bsm_ratio->SetMarkerSize(0.4);
 hist_sm_bsm_ratio->SetStats(kFALSE);
 hist_sm_bsm_ratio->GetYaxis()->SetRangeUser(0,2);
 hist_sm_bsm_ratio->GetXaxis()->SetRangeUser(0,20.0);
 hist_sm_bsm_ratio->Draw("P");
 l->Draw();
 
 pad1->cd();
 //gPad->SetLogy();
 hist_mu_PT_sm->SetLineColor(1);
 hist_mu_PT_sm->SetLineWidth(3);
 //hist_mu_PT_sm->SetMarkerStyle(20);
 //hist_mu_PT_sm->SetMarkerColor(1);
 //hist_mu_PT_sm->SetMarkerSize(1);
 hist_mu_PT_sm->GetYaxis()->SetMaxDigits(3);
 //hist_mu_PT_sm->Scale(5.0/0.0015);
 hist_mu_PT_sm->Draw("HIST");
 gStyle->SetOptStat(10);
 TPaveStats *stats1 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats1->SetName("SM");
 stats1->SetY1NDC(.05);
 stats1->SetY2NDC(.3);
 stats1->SetTextColor(1);
 stats1->SetTextSize(0.025);
 //hist_mu_PT_sm->GetXaxis()->SetTitle("P_{T} (GeV)");
 hist_mu_PT_sm->GetXaxis()->SetNdivisions(0);
 hist_mu_PT_sm->GetYaxis()->SetTitle("Counts");
 hist_mu_PT_sm->GetXaxis()->SetRangeUser(0,20.0);
 hist_mu_PT_sm->GetYaxis()->SetRangeUser(0,70000.0);
 hist_mu_PT_sm->GetXaxis()->SetMaxDigits(3);
 hist_mu_PT_sm->SetTitle("Muon P_{T}");
 hist_mu_PT_sm->SetTitleSize(25);
 //hist_mu_PT_sm->GetXaxis()->CenterTitle(kTRUE);
 hist_mu_PT_sm->GetYaxis()->CenterTitle(kTRUE);
 hist_mu_PT_bsm->SetLineColor(2);
 hist_mu_PT_bsm->SetLineWidth(3);
 //hist_mu_PT_bsm->SetMarkerStyle(23);
 //hist_mu_PT_bsm->SetMarkerSize(1);
 //hist_mu_PT_bsm->SetMarkerColor(2);
 //hist_mu_PT_bsm->Scale(5.0/0.0016);
 hist_mu_PT_bsm->Draw("HISTSAMES");
 gStyle->SetOptStat(10);
 TPaveStats *stats2 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats2->SetName("BSM");
 stats2->SetY1NDC(.05);
 stats2->SetY2NDC(.3);
 stats2->SetTextColor(2);
 stats2->SetTextSize(0.025);
 hist_mu_PT_bkg->SetLineColor(kBlue);
 hist_mu_PT_bkg->SetLineWidth(3);
 //hist_mu_PT_bkg->SetMarkerStyle(23);
 //hist_mu_PT_bkg->SetMarkerSize(1);
 //hist_mu_PT_bkg->SetMarkerColor(3);
 //hist_mu_PT_bkg->Scale(5.0/0.0016);
 hist_mu_PT_bkg->Draw("HISTSAMES");
 gStyle->SetOptStat(10);
 TPaveStats *stats3 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats3->SetName("Bkg");
 stats3->SetY1NDC(.05);
 stats3->SetY2NDC(.3);
 stats3->SetTextColor(kBlue);
 stats3->SetTextSize(0.025);
 
 legend->Draw();*/

  /*TFile *f1 = TFile::Open("e_mu_PT_cut_sm.root");
 TFile *f2 = TFile::Open("e_mu_PT_cut_bsm.root");
 TFile *f3 = TFile::Open("e_mu_PT_cut_bkg.root");
 TCanvas *c1 = new TCanvas("c1","c1",500,400);
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 TLine *l = new TLine(0.0,1.0,20.0,1.0);

 TH1F *hist_mu_PT_sm = (TH1F*) f1->Get("hist_mu_PT_fid");
 TH1F *hist_mu_PT_bsm= (TH1F*) f2->Get("hist_mu_PT_fid");
 TH1F *hist_mu_PT_bkg= (TH1F*) f3->Get("hist_mu_PT_fid");
 TH1F *hist_sm_bsm_ratio = new TH1F("hist_sm_bsm_ratio ","hist_sm_bsm_ratio ",200,0.0,100.0);
 
 legend->AddEntry(hist_mu_PT_sm,"SM");
 legend->AddEntry(hist_mu_PT_bsm,"SM+BSM");
 legend->AddEntry(hist_mu_PT_bkg,"Bkg");

 TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
 TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.25);

 pad1->Draw();
 pad2->Draw();
 
 pad2->cd();
 //l->SetLineStyle(9);
 l->SetLineWidth(1);
 l->SetLineColor(kRed);
 hist_sm_bsm_ratio->Divide(hist_mu_PT_bsm,hist_mu_PT_sm,1,1,"B");
 //hist_sm_bsm_ratio->Divide(hist_mu_PT_sm,hist_mu_PT_bsm);
 hist_sm_bsm_ratio->GetXaxis()->SetTitle("P_{T} (GeV)");
 hist_sm_bsm_ratio->SetTitle("");
 hist_sm_bsm_ratio->GetXaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetYaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetXaxis()->SetTitleSize(0.15);
 hist_sm_bsm_ratio->GetXaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetNdivisions(5);
 hist_sm_bsm_ratio->GetYaxis()->SetTitle("SM+BSM/SM");
 hist_sm_bsm_ratio->GetYaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->SetMarkerStyle(21);
 hist_sm_bsm_ratio->SetMarkerSize(0.4);
 hist_sm_bsm_ratio->SetStats(kFALSE);
 hist_sm_bsm_ratio->GetYaxis()->SetRangeUser(0,6);
 hist_sm_bsm_ratio->GetXaxis()->SetRangeUser(0,20.0);
 hist_sm_bsm_ratio->Draw("P");
 l->Draw();
 
 pad1->cd();
 //gPad->SetLogy();
 hist_mu_PT_sm->SetLineColor(1);
 hist_mu_PT_sm->SetLineWidth(3);
 //hist_mu_PT_sm->SetMarkerStyle(20);
 //hist_mu_PT_sm->SetMarkerColor(1);
 //hist_mu_PT_sm->SetMarkerSize(1);
 hist_mu_PT_sm->GetYaxis()->SetMaxDigits(3);
 //hist_mu_PT_sm->Scale(5.0/0.0015);
 hist_mu_PT_sm->Draw("HIST");
 gStyle->SetOptStat(10);
 TPaveStats *stats1 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats1->SetName("SM");
 stats1->SetY1NDC(.05);
 stats1->SetY2NDC(.3);
 stats1->SetTextColor(1);
 stats1->SetTextSize(0.025);
 //hist_mu_PT_sm->GetXaxis()->SetTitle("P_{T} (GeV)");
 hist_mu_PT_sm->GetXaxis()->SetNdivisions(0);
 hist_mu_PT_sm->GetYaxis()->SetTitle("Counts");
 hist_mu_PT_sm->GetXaxis()->SetRangeUser(0,20.0);
 hist_mu_PT_sm->GetYaxis()->SetRangeUser(0,450.0);
 hist_mu_PT_sm->GetXaxis()->SetMaxDigits(3);
 hist_mu_PT_sm->SetTitle("Muon P_{T}");
 hist_mu_PT_sm->SetTitleSize(25);
 //hist_mu_PT_sm->GetXaxis()->CenterTitle(kTRUE);
 hist_mu_PT_sm->GetYaxis()->CenterTitle(kTRUE);
 hist_mu_PT_bsm->SetLineColor(2);
 hist_mu_PT_bsm->SetLineWidth(3);
 //hist_mu_PT_bsm->SetMarkerStyle(23);
 //hist_mu_PT_bsm->SetMarkerSize(1);
 //hist_mu_PT_bsm->SetMarkerColor(2);
 //hist_mu_PT_bsm->Scale(5.0/0.0016);
 hist_mu_PT_bsm->Draw("HISTSAMES");
 gStyle->SetOptStat(10);
 TPaveStats *stats2 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats2->SetName("BSM");
 stats2->SetY1NDC(.05);
 stats2->SetY2NDC(.3);
 stats2->SetTextColor(2);
 stats2->SetTextSize(0.025);
 hist_mu_PT_bkg->SetLineColor(kBlue);
 hist_mu_PT_bkg->SetLineWidth(3);
 //hist_mu_PT_bkg->SetMarkerStyle(23);
 //hist_mu_PT_bkg->SetMarkerSize(1);
 //hist_mu_PT_bkg->SetMarkerColor(3);
 //hist_mu_PT_bkg->Scale(5.0/0.0016);
 hist_mu_PT_bkg->Draw("HISTSAMES");
 gStyle->SetOptStat(10);
 TPaveStats *stats3 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats3->SetName("Bkg");
 stats3->SetY1NDC(.05);
 stats3->SetY2NDC(.3);
 stats3->SetTextColor(kBlue);
 stats3->SetTextSize(0.025);
 
 legend->Draw();*/

  /*TFile *f1 = TFile::Open("Rapidity_corr_bsm.root");
  TCanvas *c1 = new TCanvas("c1","c1",500,400);
  TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);

  TH1F *hist = (TH1F*) f1->Get("hist");

  gPad->SetLogz();
  //gStyle->SetOptStat(kFALSE);
  //hist->GetXaxis()->SetRangeUser(-6.0,6.0);
  //hist->GetYaxis()->SetRangeUser(-6.0,6.0);
  hist->GetXaxis()->SetTitle("y_{#tau#tau}");
  hist->GetYaxis()->SetTitle("y_{ch}");
  hist->GetXaxis()->CenterTitle(kTRUE);
  hist->GetYaxis()->CenterTitle(kTRUE);
  hist->Draw("colz");*/

  /*TFile *f1 = TFile::Open("taus_PT_Rapidity_bsm.root");
  TCanvas *c1 = new TCanvas("c1","c1",500,400);
  TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);

  TH1F *hist = (TH1F*) f1->Get("hist_taus_rapidity");

  //gPad->SetLogz();
  gStyle->SetOptStat(kFALSE);
  //hist->GetXaxis()->SetRangeUser(-6.0,6.0);
  //hist->GetYaxis()->SetRangeUser(-6.0,6.0);
  hist->GetXaxis()->SetTitle("Lead-Tau Rapidity");
  hist->GetYaxis()->SetTitle("Next-Lead Tau Rapidity");
  hist->GetXaxis()->CenterTitle(kTRUE);
  hist->GetYaxis()->CenterTitle(kTRUE);
  hist->Draw("colz");*/

  /*TFile *f1 = TFile::Open("PT_corr_sm.root");
  TCanvas *c1 = new TCanvas("c1","c1",500,400);
  TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);

  TH1F *hist = (TH1F*) f1->Get("hist");

  gPad->SetLogz();
  hist->GetXaxis()->SetRangeUser(4,20);
  hist->GetYaxis()->SetRangeUser(4,20);
  hist->GetXaxis()->SetTitle("p_{T}^{#tau} (GeV)");
  hist->GetYaxis()->SetTitle("p_{T}^{lead lepton} (GeV)");
  hist->GetXaxis()->CenterTitle(kTRUE);
  hist->GetYaxis()->CenterTitle(kTRUE);
  hist->Draw("colz");*/

  /*TFile *f1 = TFile::Open("electrons_PT_sm.root");
 TFile *f2 = TFile::Open("electrons_PT_bsm.root");
 TFile *f3 = TFile::Open("electrons_PT_bkg.root");
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 TLine *l = new TLine(0.0,1.0,100.0,1.0);

 TH1F *hist_e_PT_sm = (TH1F*) f1->Get("hist_e_PT");
 TH1F *hist_e_PT_bsm= (TH1F*) f2->Get("hist_e_PT");
 TH1F *hist_e_PT_bkg= (TH1F*) f3->Get("hist_e_bkg_PT");
 TH1F *hist_sm_bsm_ratio = new TH1F("hist_sm_bsm_ratio ","hist_sm_bsm_ratio ",200,0.0,100.0);
 
 legend->AddEntry(hist_e_PT_sm,"SM");
 legend->AddEntry(hist_e_PT_bsm,"SM+BSM");
 legend->AddEntry(hist_e_PT_bkg,"Bkg");

 TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
 TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.25);

 pad1->Draw();
 pad2->Draw();
 
 pad2->cd();
 //l->SetLineStyle(9);
 l->SetLineWidth(1);
 l->SetLineColor(kRed);
 hist_sm_bsm_ratio->Divide(hist_e_PT_bsm,hist_e_PT_sm,1,1,"B");
 //hist_sm_bsm_ratio->Divide(hist_e_PT_sm,hist_e_PT_bsm);
 hist_sm_bsm_ratio->GetXaxis()->SetTitle("P_{T} (GeV)");
 hist_sm_bsm_ratio->SetTitle("");
 hist_sm_bsm_ratio->GetXaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetYaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetXaxis()->SetTitleSize(0.15);
 hist_sm_bsm_ratio->GetXaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetNdivisions(5);
 hist_sm_bsm_ratio->GetYaxis()->SetTitle("SM+BSM/SM");
 hist_sm_bsm_ratio->GetYaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->SetMarkerStyle(21);
 hist_sm_bsm_ratio->SetMarkerSize(0.4);
 hist_sm_bsm_ratio->SetStats(kFALSE);
 hist_sm_bsm_ratio->GetYaxis()->SetRangeUser(0,2);
 hist_sm_bsm_ratio->Draw("P");
 l->Draw();
 
 pad1->cd();
 //gPad->SetLogy();
 hist_e_PT_sm->SetLineColor(1);
 hist_e_PT_sm->SetLineWidth(3);
 //hist_e_PT_sm->SetMarkerStyle(20);
 //hist_e_PT_sm->SetMarkerColor(1);
 //hist_e_PT_sm->SetMarkerSize(1);
 hist_e_PT_sm->GetYaxis()->SetMaxDigits(3);
 //hist_e_PT_sm->Scale(5.0/0.0015);
 hist_e_PT_sm->Draw("HIST");
 gStyle->SetOptStat(10);
 TPaveStats *stats1 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats1->SetName("SM");
 stats1->SetY1NDC(.05);
 stats1->SetY2NDC(.3);
 stats1->SetTextColor(1);
 stats1->SetTextSize(0.025);
 //hist_e_PT_sm->GetXaxis()->SetTitle("P_{T} (GeV)");
 // hist_e_PT_sm->GetXaxis()->SetNdivisions(0);
 hist_e_PT_sm->GetYaxis()->SetTitle("Counts");
 hist_e_PT_sm->SetTitle("Electron P_{T}");
 hist_e_PT_sm->SetTitleSize(25);
 //hist_e_PT_sm->GetXaxis()->CenterTitle(kTRUE);
 hist_e_PT_sm->GetYaxis()->CenterTitle(kTRUE);
 hist_e_PT_bsm->SetLineColor(2);
 hist_e_PT_bsm->SetLineWidth(3);
 //hist_e_PT_bsm->SetMarkerStyle(23);
 //hist_e_PT_bsm->SetMarkerSize(1);
 //hist_e_PT_bsm->SetMarkerColor(2);
 //hist_e_PT_bsm->Scale(5.0/0.0016);
 hist_e_PT_bsm->Draw("HISTSAMES");
 gStyle->SetOptStat(10);
 TPaveStats *stats2 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats2->SetName("BSM");
 stats2->SetY1NDC(.05);
 stats2->SetY2NDC(.3);
 stats2->SetTextColor(2);
 stats2->SetTextSize(0.025);
 hist_e_PT_bkg->SetLineColor(kBlue);
 hist_e_PT_bkg->SetLineWidth(3);
 //hist_e_PT_bkg->SetMarkerStyle(23);
 //hist_e_PT_bkg->SetMarkerSize(1);
 //hist_e_PT_bkg->SetMarkerColor(3);
 //hist_e_PT_bkg->Scale(5.0/0.0016);
 hist_e_PT_bkg->Draw("HISTSAMES");
 gStyle->SetOptStat(10);
 TPaveStats *stats3 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats3->SetName("Bkg");
 stats3->SetY1NDC(.05);
 stats3->SetY2NDC(.3);
 stats3->SetTextColor(kBlue);
 stats3->SetTextSize(0.025);
 
 
 legend->Draw();*/

  /*TFile *f1 = TFile::Open("ppions_PT_sm_sep.root");
 TFile *f2 = TFile::Open("ppions_PT_sm.root");
 //TFile *f2 = TFile::Open("electrons_PT_sm_norm_old.root");
 TCanvas *c1 = new TCanvas("c1","c1",500,400);
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);

 TH1F *hist_tau_pip_PT = (TH1F*) f1->Get("hist_tau_pip_PT");
 TH1F *hist_else_pip_PT = (TH1F*) f1->Get("hist_else_pip_PT");
 TH1F *hist_pip_PT = (TH1F*) f2->Get("hist_pip_PT");
 
 legend->AddEntry(hist_tau_pip_PT,"#pi^{+} from #tau (MPI=ISR=on)");
 legend->AddEntry(hist_else_pip_PT,"#pi^{+} not from #tau (MPI=ISR=on)");
 legend->AddEntry(hist_pip_PT,"#pi^{+} from #tau (MPI=ISR=off)");

 gPad->SetLogy();
 hist_tau_pip_PT->SetMarkerStyle(20);
 hist_tau_pip_PT->SetMarkerColor(1);
 hist_tau_pip_PT->SetMarkerSize(1);
 //hist_tau_pip_PT->SetLineColor(1);
 //hist_tau_pip_PT->SetLineWidth(3);
 hist_tau_pip_PT->GetYaxis()->SetMaxDigits(3);
 hist_tau_pip_PT->GetXaxis()->SetTitle("P_{T} (GeV)");
 hist_tau_pip_PT->GetYaxis()->SetTitle("Counts");
 hist_tau_pip_PT->SetTitle("Positive Pion P_{T}");
 hist_tau_pip_PT->GetXaxis()->CenterTitle(kTRUE);
 hist_tau_pip_PT->GetYaxis()->CenterTitle(kTRUE);
 hist_tau_pip_PT->Draw("P");
 gStyle->SetOptStat(10);
 TPaveStats *stats1 =(TPaveStats*)c1->GetPrimitive("stats");
 stats1->SetName("SM1");
 stats1->SetY1NDC(.05);
 stats1->SetY2NDC(.3);
 stats1->SetTextColor(1);
 stats1->SetTextSize(0.025);
 //hist_else_pip_PT->SetLineWidth(3);
 //hist_else_pip_PT->SetLineColor(2);
 hist_else_pip_PT->SetMarkerStyle(23);
 hist_else_pip_PT->SetMarkerSize(1);
 hist_else_pip_PT->SetMarkerColor(2);
 hist_else_pip_PT->Draw("PSAMES");
 gStyle->SetOptStat(10);
 TPaveStats *stats2 =(TPaveStats*)c1->GetPrimitive("stats");
 stats2->SetName("SM");
 stats2->SetY1NDC(.05);
 stats2->SetY2NDC(.3);
 stats2->SetTextColor(2);
 stats2->SetTextSize(0.025);
 //hist_pip_PT->SetLineWidth(3);
 //hist_pip_PT->SetLineColor(kBlue);
 hist_pip_PT->SetMarkerStyle(21);
 hist_pip_PT->SetMarkerSize(1);
 hist_pip_PT->SetMarkerColor(kBlue);
 hist_pip_PT->Draw("PSAMES");
 gStyle->SetOptStat(10);
 TPaveStats *stats3 =(TPaveStats*)c1->GetPrimitive("stats");
 stats3->SetName("SM2");
 stats3->SetY1NDC(.05);
 stats3->SetY2NDC(.3);
 stats3->SetTextColor(kBlue);
 stats3->SetTextSize(0.025); 
 
 legend->Draw();*/

  /*TFile *f1 = TFile::Open("ppions_rapidity_sm_norm.root");
 TFile *f2 = TFile::Open("ppions_rapidity_sm_norm_old.root");
 TCanvas *c1 = new TCanvas("c1","c1",500,400);
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 //TLine *l = new TLine(0.0,1.0,100.0,1.0);

 TH1F *hist_pip_rapidity = (TH1F*) f1->Get("hist_pip_rapidity");
 TH1F *hist_pip_rapidity_old = (TH1F*) f2->Get("hist_pip_rapidity");
 //TH1F *hist_sm_bsm_ratio = new TH1F("hist_sm_bsm_ratio ","hist_sm_bsm_ratio ",100,0.0,100.0);
 
 legend->AddEntry(hist_pip_rapidity,"SM (MPI=ISR=OFF)");
 legend->AddEntry(hist_pip_rapidity_old,"SM (MPI=ISR=ON)");

 //TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
 //TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.25);

 //pad1->Draw();
 //pad2->Draw();
 
 //pad2->cd();
 //l->SetLineStyle(9);*/
 /*l->SetLineWidth(1);
 l->SetLineColor(kRed);
 hist_sm_bsm_ratio->Divide(tau_mass_bsm,tau_mass_sm,1,1,"B");
 //hist_sm_bsm_ratio->Divide(tau_mass_sm,tau_mass_bsm);
 hist_sm_bsm_ratio->GetXaxis()->SetTitle("Mass (GeV)");
 hist_sm_bsm_ratio->SetTitle("");
 hist_sm_bsm_ratio->GetXaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetYaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetXaxis()->SetTitleSize(0.15);
 hist_sm_bsm_ratio->GetXaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetNdivisions(5);
 hist_sm_bsm_ratio->SetMarkerStyle(21);
 hist_sm_bsm_ratio->SetMarkerSize(0.8);
 hist_sm_bsm_ratio->SetStats(kFALSE);
 hist_sm_bsm_ratio->GetYaxis()->SetRangeUser(0,2);
 hist_sm_bsm_ratio->Draw("P");
 l->Draw();*/
 
 /*//pad1->cd();
 //gPad->SetLogy();
 //hist_pip_rapidity->SetLineColor(1);
 //hist_pip_rapidity->SetLineWidth(3);
 hist_pip_rapidity->SetMarkerStyle(20);
 hist_pip_rapidity->SetMarkerColor(1);
 hist_pip_rapidity->SetMarkerSize(1);
 hist_pip_rapidity->GetYaxis()->SetMaxDigits(3);
 //hist_pip_rapidity->Scale(5.0/0.0015);
  hist_pip_rapidity->GetXaxis()->SetTitle("Rapidity");
 hist_pip_rapidity->GetYaxis()->SetTitle("Normalized counts");
 hist_pip_rapidity->SetTitle("Positive Pion Rapidity");
 // hist_pip_rapidity->SetTitleSize(25);
 hist_pip_rapidity->GetXaxis()->CenterTitle(kTRUE);
 hist_pip_rapidity->GetYaxis()->CenterTitle(kTRUE);
 hist_pip_rapidity->Draw("P");
 gStyle->SetOptStat(10);
 TPaveStats *stats1 =(TPaveStats*)c1->GetPrimitive("stats");
 stats1->SetName("SM1");
 stats1->SetY1NDC(.05);
 stats1->SetY2NDC(.3);
 stats1->SetTextColor(1);
 stats1->SetTextSize(0.025);
 //hist_pip_rapidity_old->SetLineColor(2);
 //hist_pip_rapidity_old->SetLineWidth(3);
 hist_pip_rapidity_old->SetMarkerStyle(23);
 hist_pip_rapidity_old->SetMarkerSize(1);
 hist_pip_rapidity_old->SetMarkerColor(2);
 //hist_pip_rapidity_old->Scale(5.0/0.0016);
 hist_pip_rapidity_old->Draw("PSAMES");
 gStyle->SetOptStat(10);
 TPaveStats *stats2 =(TPaveStats*)c1->GetPrimitive("stats");
 stats2->SetName("SM2");
 stats2->SetY1NDC(.05);
 stats2->SetY2NDC(.3);
 stats2->SetTextColor(2);
 stats2->SetTextSize(0.025);
 
 legend->Draw();*/
  
 /*TFile *f1 = TFile::Open("sm_hists.root");
 TFile *f2 = TFile::Open("bsm_hists.root");
 TCanvas *c1 = new TCanvas("c1","c1",500,400);
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 TLine *l = new TLine(-4.0,1.0,4.0,1.0);

 TH1F *tau_phi_sm = (TH1F*) f1->Get("tau_Phi");
 TH1F *tau_phi_bsm= (TH1F*) f2->Get("tau_Phi");
 TH1F *hist_sm_bsm_ratio = new TH1F("hist_sm_bsm_ratio ","hist_sm_bsm_ratio ",100,-4.0,4.0);
 
 legend->AddEntry(tau_phi_sm,"SM");
 legend->AddEntry(tau_phi_bsm,"BSM");

 TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
 TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.25);

 pad1->Draw();
 pad2->Draw();
 
 pad2->cd();
 //l->SetLineStyle(9);
 l->SetLineWidth(1);
 l->SetLineColor(kRed);
 hist_sm_bsm_ratio->Divide(tau_phi_bsm,tau_phi_sm,1,1,"B");
 //hist_sm_bsm_ratio->Divide(tau_phi_sm,tau_phi_bsm);
 hist_sm_bsm_ratio->GetXaxis()->SetTitle("#phi");
 hist_sm_bsm_ratio->GetYaxis()->SetTitle("(SM+BSM)/SM");
 hist_sm_bsm_ratio->GetXaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetYaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetXaxis()->SetTitleSize(0.15);
 hist_sm_bsm_ratio->GetXaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetNdivisions(5);
 hist_sm_bsm_ratio->SetMarkerStyle(21);
 hist_sm_bsm_ratio->SetMarkerSize(0.8);
 hist_sm_bsm_ratio->SetStats(kFALSE);
 hist_sm_bsm_ratio->GetYaxis()->SetRangeUser(0,2);
 hist_sm_bsm_ratio->Draw("P");
 l->Draw();
 
 pad1->cd();
 //gPad->SetLogy();
 //tau_phi_sm->SetLineColor(3);
 // tau_phi_sm->SetLineWidth(3);
 tau_phi_sm->SetMarkerStyle(20);
 tau_phi_sm->SetMarkerColor(1);
 tau_phi_sm->SetMarkerSize(1);
 tau_phi_sm->GetYaxis()->SetMaxDigits(3);
 tau_phi_sm->Scale(5.0/0.0015);
 tau_phi_sm->Draw("P");
 gStyle->SetOptStat(10);
 TPaveStats *stats1 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats1->SetName("SM");
 stats1->SetY1NDC(.05);
 stats1->SetY2NDC(.3);
 stats1->SetTextColor(1);
 stats1->SetTextSize(0.025);
 //tau_phi_sm->GetXaxis()->SetTitle("P_{T} (GeV)");
 tau_phi_sm->GetXaxis()->SetNdivisions(0);
 tau_phi_sm->GetXaxis()->SetNdivisions(0);
 tau_phi_sm->GetYaxis()->SetTitle("d#sigma/d#phi [pb]");
 tau_phi_sm->SetTitle("Tau Phi");
 tau_phi_sm->SetTitleSize(25);
 //tau_phi_sm->GetXaxis()->CenterTitle(kTRUE);
 tau_phi_sm->GetYaxis()->CenterTitle(kTRUE);
 //tau_phi_bsm->SetLineColor(4);
 //tau_phi_bsm->SetLineWidth(3);
 tau_phi_bsm->SetMarkerStyle(23);
 tau_phi_bsm->SetMarkerSize(1);
 tau_phi_bsm->SetMarkerColor(2);
 tau_phi_bsm->Scale(5.0/0.0016);
 tau_phi_bsm->Draw("PSAMES");
 gStyle->SetOptStat(10);
 TPaveStats *stats2 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats2->SetName("BSM");
 stats2->SetY1NDC(.05);
 stats2->SetY2NDC(.3);
 stats2->SetTextColor(2);
 stats2->SetTextSize(0.025);
 
 legend->Draw();*/

  /*TFile *f1 = TFile::Open("tau_angles_pions_1ch_sm.root");
 TFile *f2 = TFile::Open("tau_angles_pions_1ch_bsm.root");
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 TLine *l = new TLine(0.0,1.0,180.0,1.0);

 TH1F *hist_pim_angles_sm_1ch = (TH1F*) f1->Get("hist_pim_angles_1ch");
 TH1F *hist_pim_angles_bsm_1ch = (TH1F*) f2->Get("hist_pim_angles_1ch");
 TH1F *hist_sm_bsm_ratio = new TH1F("hist_sm_bsm_ratio","hist_sm_bsm_ratio",150,0.0,180.0);
 
 legend->AddEntry(hist_pim_angles_sm_1ch,"SM #pi^{-}");
 legend->AddEntry(hist_pim_angles_bsm_1ch,"BSM #pi^{-}");

 TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
 TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.25);

 pad1->Draw();
 pad2->Draw();
 
 pad2->cd();
 l->SetLineStyle(9);
 l->SetLineWidth(1);
 //hist_sm_bsm_ratio->Divide(tauNL_pt_sm_1ch,tauNL_pt_bsm_1ch,1,1,"B");
 hist_sm_bsm_ratio->Divide(hist_pim_angles_sm_1ch,hist_pim_angles_bsm_1ch);
 hist_sm_bsm_ratio->GetXaxis()->SetTitle("Angle (degrees)");
 hist_sm_bsm_ratio->SetTitle("");
 hist_sm_bsm_ratio->GetXaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetYaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetXaxis()->SetTitleSize(0.15);
 hist_sm_bsm_ratio->GetXaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetNdivisions(5);
 hist_sm_bsm_ratio->SetMarkerStyle(21);
 hist_sm_bsm_ratio->SetMarkerSize(0.5);
 hist_sm_bsm_ratio->SetStats(kFALSE);
 hist_sm_bsm_ratio->Draw("P");
 l->Draw();
 
 pad1->cd();
 hist_pim_angles_sm_1ch->SetLineColor(3);
 hist_pim_angles_sm_1ch->SetLineWidth(3);
 hist_pim_angles_sm_1ch->Draw("HIST");
 gStyle->SetOptStat(11);
 TPaveStats *stats1 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats1->SetName("SM");
 stats1->SetY1NDC(.05);
 stats1->SetY2NDC(.3);
 stats1->SetTextColor(3);
 stats1->SetTextSize(0.03);
 //hist_pim_angles_sm_1ch->GetXaxis()->SetTitle("P_{T} (GeV)");
 hist_pim_angles_sm_1ch->GetXaxis()->SetNdivisions(0);
 hist_pim_angles_sm_1ch->GetYaxis()->SetTitle("Counts");
 hist_pim_angles_sm_1ch->SetTitle("Angle w.r.t tau direction");
 //hist_pim_angles_sm_1ch->GetXaxis()->CenterTitle(kTRUE);
 hist_pim_angles_sm_1ch->GetYaxis()->CenterTitle(kTRUE);
 hist_pim_angles_bsm_1ch->SetLineColor(4);
 hist_pim_angles_bsm_1ch->SetLineWidth(3);
 hist_pim_angles_bsm_1ch->Draw("HISTSAMES");
 gStyle->SetOptStat(11);
 TPaveStats *stats2 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats2->SetName("BSM");
 stats2->SetY1NDC(.05);
 stats2->SetY2NDC(.3);
 stats2->SetTextColor(4);
 stats2->SetTextSize(0.03);
 
 legend->Draw();*/

  /*TFile *f1 = TFile::Open("sm_hists.root");
 TFile *f2 = TFile::Open("bsm_hists.root");
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 TLine *l = new TLine(0.0,1.0,20.0,1.0);

 TH1F *tauNL_pt_sm = (TH1F*) f1->Get("tauNL_pt");
 TH1F *tauNL_pt_bsm = (TH1F*) f2->Get("tauNL_pt");
 TH1F *hist_sm_bsm_ratio = new TH1F("hist_sm_bsm_ratio ","hist_sm_bsm_ratio ",300,0.0,20.0);
 
 legend->AddEntry(tauNL_pt_sm,"SM");
 legend->AddEntry(tauNL_pt_bsm,"BSM");

 TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
 TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.25);

 pad1->Draw();
 pad2->Draw();
 
 pad2->cd();
 l->SetLineStyle(9);
 l->SetLineWidth(1);
 //hist_sm_bsm_ratio->Divide(tauNL_pt_sm,tauNL_pt_bsm,1,1,"B");
 hist_sm_bsm_ratio->Divide(tauNL_pt_sm,tauNL_pt_bsm);
 hist_sm_bsm_ratio->GetXaxis()->SetTitle("P_{T} (GeV)");
 hist_sm_bsm_ratio->SetTitle("");
 hist_sm_bsm_ratio->GetXaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetYaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetXaxis()->SetTitleSize(0.15);
 hist_sm_bsm_ratio->GetXaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetNdivisions(5);
 hist_sm_bsm_ratio->SetMarkerStyle(21);
 hist_sm_bsm_ratio->SetMarkerSize(0.5);
 hist_sm_bsm_ratio->SetStats(kFALSE);
 hist_sm_bsm_ratio->Draw("P");
 l->Draw();
 
 pad1->cd();
 tauNL_pt_sm->SetLineColor(3);
 tauNL_pt_sm->SetLineWidth(3);
 tauNL_pt_sm->Draw("HIST");
 gStyle->SetOptStat(11);
 TPaveStats *stats1 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats1->SetName("SM");
 stats1->SetY1NDC(.05);
 stats1->SetY2NDC(.3);
 stats1->SetTextColor(3);
 stats1->SetTextSize(0.03);
 //tauNL_pt_sm->GetXaxis()->SetTitle("P_{T} (GeV)");
 tauNL_pt_sm->GetXaxis()->SetNdivisions(0);
 tauNL_pt_sm->GetYaxis()->SetTitle("Counts");
 tauNL_pt_sm->SetTitle("Next-lead Tau P_{T}");
 //tauNL_pt_sm->GetXaxis()->CenterTitle(kTRUE);
 tauNL_pt_sm->GetYaxis()->CenterTitle(kTRUE);
 tauNL_pt_bsm->SetLineColor(4);
 tauNL_pt_bsm->SetLineWidth(3);
 tauNL_pt_bsm->Draw("HISTSAMES");
 gStyle->SetOptStat(11);
 TPaveStats *stats2 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats2->SetName("BSM");
 stats2->SetY1NDC(.05);
 stats2->SetY2NDC(.3);
 stats2->SetTextColor(4);
 stats2->SetTextSize(0.03);
 
 legend->Draw();*/
  
  /*TFile *f1 = TFile::Open("sm_hists.root");
 TFile *f2 = TFile::Open("bsm_hists.root");
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 TLine *l = new TLine(0.0,1.0,100.0,1.0);

 TH1F *di_tau_mass_sm = (TH1F*) f1->Get("di_tau_Mass");
 TH1F *di_tau_mass_bsm = (TH1F*) f2->Get("di_tau_Mass");
 TH1F *hist_sm_bsm_ratio = new TH1F("hist_sm_bsm_ratio ","hist_sm_bsm_ratio ",100,0.0,100.0);
 
 legend->AddEntry(di_tau_mass_sm,"SM");
 legend->AddEntry(di_tau_mass_bsm,"BSM");

 TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
 TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.25);

 pad1->Draw();
 pad2->Draw();
 
 pad2->cd();
 //l->SetLineStyle(9);
 l->SetLineWidth(1);
 l->SetLineColor(kRed);
 hist_sm_bsm_ratio->Divide(di_tau_mass_bsm,di_tau_mass_sm,1,1,"B");
 //hist_sm_bsm_ratio->Divide(di_tau_mass_sm,di_tau_mass_bsm);
 hist_sm_bsm_ratio->GetXaxis()->SetTitle("Mass");
 hist_sm_bsm_ratio->SetTitle("");
 hist_sm_bsm_ratio->GetXaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetYaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetXaxis()->SetTitleSize(0.15);
 hist_sm_bsm_ratio->GetXaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetNdivisions(5);
 hist_sm_bsm_ratio->SetMarkerStyle(21);
 hist_sm_bsm_ratio->SetMarkerSize(0.8);
 hist_sm_bsm_ratio->SetStats(kFALSE);
 hist_sm_bsm_ratio->Draw("P");
 l->Draw();
 
 pad1->cd();
 gPad->SetLogy();
 //di_tau_mass_sm->SetLineColor(3);
 // di_tau_mass_sm->SetLineWidth(3);
 di_tau_mass_sm->SetMarkerStyle(20);
 di_tau_mass_sm->SetMarkerColor(1);
 di_tau_mass_sm->SetMarkerSize(1);
 di_tau_mass_sm->Draw("P");
 gStyle->SetOptStat(11);
 TPaveStats *stats1 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats1->SetName("SM");
 stats1->SetY1NDC(.05);
 stats1->SetY2NDC(.3);
 stats1->SetTextColor(1);
 stats1->SetTextSize(0.03);
 //di_tau_mass_sm->GetXaxis()->SetTitle("P_{T} (GeV)");
 di_tau_mass_sm->GetXaxis()->SetNdivisions(0);
 di_tau_mass_sm->GetYaxis()->SetTitle("Counts");
 di_tau_mass_sm->SetTitle("di-Tau Mass");
 //di_tau_mass_sm->GetXaxis()->CenterTitle(kTRUE);
 di_tau_mass_sm->GetYaxis()->CenterTitle(kTRUE);
 //di_tau_mass_bsm->SetLineColor(4);
 //di_tau_mass_bsm->SetLineWidth(3);
 di_tau_mass_bsm->SetMarkerStyle(23);
 di_tau_mass_bsm->SetMarkerSize(1);
 di_tau_mass_bsm->SetMarkerColor(2);
 di_tau_mass_bsm->Draw("PSAMES");
 gStyle->SetOptStat(11);
 TPaveStats *stats2 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats2->SetName("BSM");
 stats2->SetY1NDC(.05);
 stats2->SetY2NDC(.3);
 stats2->SetTextColor(2);
 stats2->SetTextSize(0.03);
 
 legend->Draw();*/
  
  /*TFile *f1 = TFile::Open("electrons_rapidity_sm.root");
 TFile *f2 = TFile::Open("electrons_rapidity_bsm.root");
 //TFile *f3 = TFile::Open("electrons_rapidity_bkg.root"); 
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 TLine *l = new TLine(-5.0,1.0,5.0,1.0);

 //c1->Divide(1,2,0,0);

 //c1->cd(1);

 TH1F *hist_e_tau_rapidity_sm = (TH1F*) f1->Get("hist_e_tau_rapidity");
 TH1F *hist_e_tau_rapidity_bsm = (TH1F*) f2->Get("hist_e_tau_rapidity");
 //TH1F *hist_e_bkg_rapidity = (TH1F*) f3->Get("hist_e_bkg_rapidity");
 TH1F *hist_sm_bsm_ratio = new TH1F("hist_sm_bsm_ratio ","hist_sm_bsm_ratio ",100,-5.0,5.0);
 
 legend->AddEntry(hist_e_tau_rapidity_sm,"SM electrons from tau decays");
 legend->AddEntry(hist_e_tau_rapidity_bsm,"BSM electrons from tau decays");
 //legend->AddEntry(hist_e_bkg_rapidity,"Bkg electrons from tau decays");

 TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
 TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.25);

 pad1->Draw();
 pad2->Draw();
 
 pad1->cd();
 //gPad->SetLogy();
 //hist_e_tau_rapidity_sm->SetLineColor(3);
 //hist_e_tau_rapidity_sm->SetLineWidth(3);
 hist_e_tau_rapidity_sm->SetMarkerStyle(20);
 hist_e_tau_rapidity_sm->SetMarkerColor(1);
 hist_e_tau_rapidity_sm->SetMarkerSize(1);
 hist_e_tau_rapidity_sm->GetYaxis()->SetMaxDigits(3);
 hist_e_tau_rapidity_sm->Scale(5.0/0.0015);
 //hist_e_tau_rapidity_sm->SetMinimum(0.0);
 hist_e_tau_rapidity_sm->Draw("P");
 //hist_e_tau_rapidity_sm->GetYaxis()->SetRangeUser(1,1e9);
 gStyle->SetOptStat(10);
 TPaveStats *stats1 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats1->SetName("SM");
 stats1->SetY1NDC(.05);
 stats1->SetY2NDC(.3);
 stats1->SetTextColor(1);
 stats1->SetTextSize(0.03);
 //hist_e_tau_rapidity_sm->GetXaxis()->SetTitle("P_{T} (GeV)");
 hist_e_tau_rapidity_sm->GetXaxis()->SetNdivisions(0);
 hist_e_tau_rapidity_sm->GetYaxis()->SetTitle("d#sigma/dy [pb]");
 hist_e_tau_rapidity_sm->SetTitle("Tau decay into electron");
 //hist_e_tau_rapidity_sm->GetXaxis()->CenterTitle(kTRUE);
 hist_e_tau_rapidity_sm->GetYaxis()->CenterTitle(kTRUE);
 //hist_e_tau_rapidity_sm->SetLineColor(4);
 //hist_e_tau_rapidity_sm->SetLineWidth(3);
 hist_e_tau_rapidity_bsm->SetMarkerStyle(23);
 hist_e_tau_rapidity_bsm->SetMarkerColor(2);
 hist_e_tau_rapidity_bsm->SetMarkerSize(1);
 hist_e_tau_rapidity_bsm->Scale(5.0/0.0016);
 hist_e_tau_rapidity_bsm->Draw("PSAMES");
 gStyle->SetOptStat(10);
 TPaveStats *stats2 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats2->SetName("BSM");
 stats2->SetY1NDC(.05);
 stats2->SetY2NDC(.3);
 stats2->SetTextColor(2);
 stats2->SetTextSize(0.03);*/

 /*//hist_e_bkg_rapidity->SetLineColor(1);
 //hist_e_bkg_rapidity->SetLineWidth(3);
 hist_e_bkg_rapidity->SetMarkerStyle(21);
 hist_e_bkg_rapidity->SetMarkerColor(3);
 hist_e_bkg_rapidity->SetMarkerSize(1);
 hist_e_bkg_rapidity->Draw("PSAMES");
 gStyle->SetOptStat(10);
 TPaveStats *stats3 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats3->SetName("Bkg");
 stats3->SetY1NDC(.05);
 stats3->SetY2NDC(.3);
 stats3->SetTextColor(3);
 stats3->SetTextSize(0.03);*/

 /*legend->Draw();

 pad2->cd();
 //l->SetLineStyle(9);
 l->SetLineWidth(1);
 l->SetLineColor(kRed);
 hist_sm_bsm_ratio->Divide(hist_e_tau_rapidity_sm,hist_e_tau_rapidity_bsm,1,1,"B");
 //hist_sm_bsm_ratio->Divide(hist_e_tau_rapidity_sm,hist_e_tau_rapidity_bsm);
 hist_sm_bsm_ratio->GetXaxis()->SetTitle("Rapidity");
 hist_sm_bsm_ratio->SetTitle("");
 hist_sm_bsm_ratio->GetXaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetYaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetXaxis()->SetTitleSize(0.1);
 hist_sm_bsm_ratio->GetXaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetNdivisions(5);
 hist_sm_bsm_ratio->SetMarkerStyle(21);
 hist_sm_bsm_ratio->SetMarkerSize(0.8);
 hist_sm_bsm_ratio->SetStats(kFALSE);
 hist_sm_bsm_ratio->GetYaxis()->SetRangeUser(0,2);
 hist_sm_bsm_ratio->Draw("P");
 l->Draw();*/


  /*TFile *f1 = TFile::Open("electrons_rapidity_sm.root");
 TFile *f2 = TFile::Open("electrons_rapidity_bsm.root");
 TFile *f3 = TFile::Open("electrons_rapidity_bkg.root"); 
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 TLine *l = new TLine(0.0,1.0,20.0,1.0);

 //c1->Divide(1,2,0,0);

 //c1->cd(1);

 TH1F *hist_mu_tau_PT_sm = (TH1F*) f1->Get("hist_mu_tau_PT_sm");
 TH1F *hist_mu_tau_PT_bsm = (TH1F*) f2->Get("hist_mu_tau_PT_bsm");
 TH1F *hist_mu_bkg_PT = (TH1F*) f3->Get("hist_mu_bkg_PT");
 TH1F *hist_sm_bsm_ratio = new TH1F("hist_sm_bsm_ratio ","hist_sm_bsm_ratio ",300,0.0,20.0);
 
 legend->AddEntry(hist_mu_tau_PT_sm,"SM electrons from tau decays");
 legend->AddEntry(hist_mu_tau_PT_bsm,"BSM electrons from tau decays");
 legend->AddEntry(hist_mu_bkg_PT,"Bkg electrons from tau decays");

 TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
 TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.25);

 pad1->Draw();
 pad2->Draw();
 
 pad2->cd();
 l->SetLineStyle(9);
 l->SetLineWidth(1);
 //hist_sm_bsm_ratio->Divide(hist_mu_tau_PT_sm,hist_mu_tau_PT_bsm,1,1,"B");
 hist_sm_bsm_ratio->Divide(hist_mu_tau_PT_sm,hist_mu_tau_PT_bsm);
 hist_sm_bsm_ratio->GetXaxis()->SetTitle("P_{T} (GeV)");
 hist_sm_bsm_ratio->SetTitle("");
 hist_sm_bsm_ratio->GetXaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetYaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetXaxis()->SetTitleSize(0.15);
 hist_sm_bsm_ratio->GetXaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetNdivisions(5);
 hist_sm_bsm_ratio->SetMarkerStyle(21);
 hist_sm_bsm_ratio->SetMarkerSize(0.5);
 hist_sm_bsm_ratio->SetStats(kFALSE);
 hist_sm_bsm_ratio->Draw("P");
 l->Draw();
 
 pad1->cd();
 hist_mu_tau_PT_sm->SetLineColor(3);
 hist_mu_tau_PT_sm->SetLineWidth(3);
 hist_mu_tau_PT_sm->Draw("HIST");
 gStyle->SetOptStat(01);
 TPaveStats *stats1 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats1->SetName("SM");
 stats1->SetY1NDC(.05);
 stats1->SetY2NDC(.3);
 stats1->SetTextColor(3);
 stats1->SetTextSize(0.03);
 //hist_mu_tau_PT_sm->GetXaxis()->SetTitle("P_{T} (GeV)");
 hist_mu_tau_PT_sm->GetXaxis()->SetNdivisions(0);
 hist_mu_tau_PT_sm->GetYaxis()->SetTitle("Counts");
 hist_mu_tau_PT_sm->SetTitle("Tau decay into muon");
 //hist_mu_tau_PT_sm->GetXaxis()->CenterTitle(kTRUE);
 hist_mu_tau_PT_sm->GetYaxis()->CenterTitle(kTRUE);
 hist_mu_tau_PT_bsm->SetLineColor(4);
 hist_mu_tau_PT_bsm->SetLineWidth(3);
 hist_mu_tau_PT_bsm->Draw("HISTSAMES");
 gStyle->SetOptStat(01);
 TPaveStats *stats2 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats2->SetName("BSM");
 stats2->SetY1NDC(.05);
 stats2->SetY2NDC(.3);
 stats2->SetTextColor(4);
 stats2->SetTextSize(0.03);
 hist_mu_bkg_PT->SetLineColor(1);
 hist_mu_bkg_PT->SetLineWidth(3);
 hist_mu_bkg_PT->Draw("HISTSAMES");
 gStyle->SetOptStat(11);
 TPaveStats *stats3 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats3->SetName("Bkg");
 stats3->SetY1NDC(.05);
 stats3->SetY2NDC(.3);
 stats3->SetTextColor(1);
 stats3->SetTextSize(0.03);
 
 legend->Draw();*/

  /*TFile *f1 = TFile::Open("electrons_PT_sm.root");
 TFile *f2 = TFile::Open("electrons_PT_bsm.root");
 TFile *f3 = TFile::Open("electrons_PT_bkg.root"); 
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 TLine *l = new TLine(0.0,1.0,20.0,1.0);

 //c1->Divide(1,2,0,0);

 //c1->cd(1);

 TH1F *hist_e_tau_PT_sm = (TH1F*) f1->Get("hist_e_tau_PT_sm");
 TH1F *hist_e_tau_PT_bsm = (TH1F*) f2->Get("hist_e_tau_PT_bsm");
 TH1F *hist_e_bkg_PT = (TH1F*) f3->Get("hist_e_bkg_PT");
 TH1F *hist_sm_bsm_ratio = new TH1F("hist_sm_bsm_ratio ","hist_sm_bsm_ratio ",300,0.0,20.0);
 
 legend->AddEntry(hist_e_tau_PT_sm,"SM electrons from tau decays");
 legend->AddEntry(hist_e_tau_PT_bsm,"BSM electrons from tau decays");
 legend->AddEntry(hist_e_bkg_PT,"Bkg electrons from tau decays");

 TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
 TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.25);

 pad1->Draw();
 pad2->Draw();
 
 pad2->cd();
 l->SetLineStyle(9);
 l->SetLineWidth(1);
 //hist_sm_bsm_ratio->Divide(hist_e_tau_PT_sm,hist_e_tau_PT_bsm,1,1,"B");
 hist_sm_bsm_ratio->Divide(hist_e_tau_PT_sm,hist_e_tau_PT_bsm);
 hist_sm_bsm_ratio->GetXaxis()->SetTitle("P_{T} (GeV)");
 hist_sm_bsm_ratio->SetTitle("");
 hist_sm_bsm_ratio->GetXaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetYaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetXaxis()->SetTitleSize(0.15);
 hist_sm_bsm_ratio->GetXaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetNdivisions(5);
 hist_sm_bsm_ratio->SetMarkerStyle(21);
 hist_sm_bsm_ratio->SetMarkerSize(0.5);
 hist_sm_bsm_ratio->SetStats(kFALSE);
 hist_sm_bsm_ratio->Draw("P");
 l->Draw();
 
 pad1->cd();
 hist_e_tau_PT_sm->SetLineColor(3);
 hist_e_tau_PT_sm->SetLineWidth(3);
 hist_e_tau_PT_sm->Draw("HIST");
 gStyle->SetOptStat(11);
 TPaveStats *stats1 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats1->SetName("SM");
 stats1->SetY1NDC(.05);
 stats1->SetY2NDC(.3);
 stats1->SetTextColor(3);
 stats1->SetTextSize(0.03);
 //hist_e_tau_PT_sm->GetXaxis()->SetTitle("P_{T} (GeV)");
 hist_e_tau_PT_sm->GetXaxis()->SetNdivisions(0);
 hist_e_tau_PT_sm->GetYaxis()->SetTitle("Counts");
 hist_e_tau_PT_sm->SetTitle("Tau decay into electron");
 //hist_e_tau_PT_sm->GetXaxis()->CenterTitle(kTRUE);
 hist_e_tau_PT_sm->GetYaxis()->CenterTitle(kTRUE);
 hist_e_tau_PT_bsm->SetLineColor(4);
 hist_e_tau_PT_bsm->SetLineWidth(3);
 hist_e_tau_PT_bsm->Draw("HISTSAMES");
 gStyle->SetOptStat(11);
 TPaveStats *stats2 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats2->SetName("BSM");
 stats2->SetY1NDC(.05);
 stats2->SetY2NDC(.3);
 stats2->SetTextColor(4);
 stats2->SetTextSize(0.03);
 hist_e_bkg_PT->SetLineColor(1);
 hist_e_bkg_PT->SetLineWidth(3);
 hist_e_bkg_PT->Draw("HISTSAMES");
 gStyle->SetOptStat(11);
 TPaveStats *stats3 =(TPaveStats*)pad1->GetPrimitive("stats");
 stats3->SetName("Bkg");
 stats3->SetY1NDC(.05);
 stats3->SetY2NDC(.3);
 stats3->SetTextColor(1);
 stats3->SetTextSize(0.03);
 
 legend->Draw();*/



 

  /*TFile *f1 = TFile::Open("muons_PT_sm.root");
 TFile *f2 = TFile::Open("muons_PT_bsm.root");
 TFile *f3 = TFile::Open("muons_PT_bkg.root"); 
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);

 TH1F *hist_mu_tau_PT_sm = (TH1F*) f1->Get("hist_mu_tau_PT_sm");
 TH1F *hist_mu_tau_PT_bsm = (TH1F*) f2->Get("hist_mu_tau_PT_bsm");
 TH1F *hist_mu_bkg_PT = (TH1F*) f3->Get("hist_mu_bkg_PT");
 
 legend->AddEntry(hist_mu_tau_PT_sm,"SM muons from tau decays");
 legend->AddEntry(hist_mu_tau_PT_bsm,"BSM muons from tau decays");
 legend->AddEntry(hist_mu_bkg_PT,"Bkg muons from tau decays");
 

 hist_mu_tau_PT_sm->SetLineColor(3);
 hist_mu_tau_PT_sm->SetLineWidth(3);
 hist_mu_tau_PT_sm->Draw("HIST");
 hist_mu_tau_PT_sm->GetXaxis()->SetTitle("P_{T} (GeV)");
 hist_mu_tau_PT_sm->GetYaxis()->SetTitle("Counts");
 hist_mu_tau_PT_sm->SetTitle("Tau decays");
 hist_mu_tau_PT_sm->GetXaxis()->CenterTitle(kTRUE);
 hist_mu_tau_PT_sm->GetYaxis()->CenterTitle(kTRUE);
 hist_mu_tau_PT_bsm->SetLineColor(4);
 hist_mu_tau_PT_bsm->SetLineWidth(3);
 hist_mu_tau_PT_bsm->Draw("HISTSAMES");
 hist_mu_bkg_PT->SetLineColor(1);
 hist_mu_bkg_PT->SetLineWidth(3);
 hist_mu_bkg_PT->Draw("HISTSAMES");
 

 
 legend->Draw();*/

  
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
 TH1F *hist_e_all
 = (TH1F*) outf->Get("hist_e_all");
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

 /*TFile *outf1 = TFile::Open("electron_Rapidity.root");
 //TFile *outf2 = TFile::Open("positron_PT.root");
 //TFile *outf3 = TFile::Open("muon_Rapidity.root");
 TCanvas *c1 = new TCanvas();
 TH1F *hist_e_tau_rapidity = (TH1F*) outf1->Get("hist_e_tau_eta");
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


 /*TFile *outf1 = TFile::Open("pions_Eta.root");
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
 hist_pim_else_eta->SetLineColor(2);
 hist_pim_else_eta->SetLineWidth(3);
 hist_pim_else_eta->Draw("HISTSAME");
 hist_pim_tau_eta->SetLineColor(4);
 hist_pim_tau_eta->SetLineWidth(3);
 hist_pim_tau_eta->Draw("HISTSAME");
 hist_pim_tau_eta_3->SetLineColor(7);
 hist_pim_tau_eta_3->SetLineWidth(3);
 hist_pim_tau_eta_3->Draw("HISTSAME");
 gStyle->SetOptStat(11);
 hist_pip_tau_eta_3->SetLineColor(6);
 hist_pip_tau_eta_3->SetLineWidth(3);
 hist_pip_tau_eta_3->Draw("HISTSAMES");
 legend->Draw();*/
}
