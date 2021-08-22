#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#include "external/ExRootAnalysis/ExRootResult.h"
#else
class ExRootTreeReader;
class ExRootResult;
#endif

void plot_GenRec(){

  gSystem->Load("libDelphes");

  TFile *f = new TFile("/home/juan/bsm_minv0p_pt1_delphes_events_NNL.root");
  TFile *f2 = new TFile("/home/juan/sm_UFO_minv0p_pt1_NNLO_delphes_events.root");
  TFile *f3 = new TFile("/home/juan/sm_bkg_minv0p_pt1_NNLO_delphes_events.root");

  TTree *Delphes_sm = (TTree*) f->Get("Delphes");

  TTree *Delphes_bsm = (TTree*) f2->Get("Delphes");

  TTree *Delphes_bkg = (TTree*) f3->Get("Delphes");

  /*TCanvas *c2 = new TCanvas();
  TLegend *legend2 = new TLegend(0.65,0.7,0.85,0.85);

  //TH1F *hist_Rec_pip_sm = new TH1F("hist_Rec_pip_sm","hist_Rec_pip_sm",300,0.0,20.0);
  TH1F *hist_Gen_pip_sm = new TH1F("hist_Gen_pip_sm","hist_Gen_pip_sm",300,0.0,20.0);
  TH1F *hist_Track_pip_sm = new TH1F("hist_Track_pip_sm","hist_Track_pip_sm",300,0.0,20.0);
  //TH1F *hist_Rec_pip_bsm = new TH1F("hist_Rec_pip_bsm","hist_Rec_pip_bsm",300,0.0,20.0);
  TH1F *hist_Gen_pip_bsm = new TH1F("hist_Gen_pip_bsm","hist_Gen_pip_bsm",300,0.0,20.0);
  TH1F *hist_Track_pip_bsm = new TH1F("hist_Track_pip_bsm","hist_Track_pip_bsm",300,0.0,20.0);
  TH1F *hist_Gen_pip_bkg = new TH1F("hist_Gen_pip_bkg","hist_Gen_pip_bkg",300,0.0,20.0);
  TH1F *hist_Track_pip_bkg = new TH1F("hist_Track_pip_bkg","hist_Track_pip_bkg",300,0.0,20.0);
  hist_Gen_pip_sm->SetLineColor(1);
  //hist_Rec_pip_sm->SetLineColor(2);
  hist_Gen_pip_bkg->SetLineColor(1);
  hist_Track_pip_sm->SetLineColor(3);
  //hist_Rec_pip_sm->SetLineWidth(3);
  hist_Gen_pip_bkg->SetLineWidth(3);
  hist_Gen_pip_sm->SetLineWidth(3);
  hist_Track_pip_sm->SetLineWidth(3);
  hist_Track_pip_bkg->SetLineWidth(3);
  hist_Gen_pip_bsm->SetLineColor(1);
  //hist_Rec_pip_bsm->SetLineColor(2);
  hist_Track_pip_bsm->SetLineColor(3);
  hist_Track_pip_bkg->SetLineColor(3);
  //hist_Rec_pip_bsm->SetLineWidth(3);
  hist_Gen_pip_bsm->SetLineWidth(3);
  hist_Track_pip_bsm->SetLineWidth(3);
  //hist_Rec_pip_bsm->SetLineStyle(2);
  hist_Gen_pip_bsm->SetLineStyle(2);
  hist_Track_pip_bsm->SetLineStyle(2);
  hist_Gen_pip_bkg->SetLineStyle(9);
  hist_Track_pip_bkg->SetLineStyle(9);

  hist_Gen_pip_sm->GetXaxis()->SetTitle("P_{T} (GeV)");
  hist_Gen_pip_sm->GetYaxis()->SetTitle("Counts");
  hist_Gen_pip_sm->SetTitle("-2.5<#eta<2.5");
  hist_Gen_pip_sm->GetXaxis()->CenterTitle(kTRUE);
  hist_Gen_pip_sm->GetYaxis()->CenterTitle(kTRUE);

  //legend2->AddEntry(hist_Rec_pip_sm,"Reconstructed positive pions (SM)");
  legend2->AddEntry(hist_Gen_pip_sm,"Generated positive pions (SM)");
  legend2->AddEntry(hist_Gen_pip_bsm,"Generated positive pions (BSM)");
  legend2->AddEntry(hist_Gen_pip_bkg,"Generated positive pions (Bkg)");
  legend2->AddEntry(hist_Track_pip_sm,"Track positive pions (SM)");
  //legend2->AddEntry(hist_Rec_pip_bsm,"Reconstructed positive pions (BSM)");
  legend2->AddEntry(hist_Track_pip_bsm,"Track positive pions (BSM)");
  legend2->AddEntry(hist_Track_pip_bkg,"Track positive pions (Bkg)");

  Delphes_sm->Draw("Particle.PT>>hist_Gen_pip_sm","Particle.PID==211&&Particle.Eta<2.5&&Particle.Eta>-2.5");
  gStyle->SetOptStat(11);
  TPaveStats *stats1 =(TPaveStats*)c2->GetPrimitive("stats");
  stats1->SetName("Gen SM");
  stats1->SetY1NDC(.05);
  stats1->SetY2NDC(.3);
  stats1->SetTextColor(1);
  stats1->SetTextSize(0.03);
  Delphes_sm->Draw("Track.PT>>hist_Track_pip_sm","Track.PID==211&&Track.Eta>-2.5&&Track.Eta<2.5","SAMES");
  gStyle->SetOptStat(11);
 TPaveStats *stats3 =(TPaveStats*)c2->GetPrimitive("stats");
 stats3->SetName("Track SM");
 stats3->SetY1NDC(.05);
 stats3->SetY2NDC(.3);
 stats3->SetTextColor(3);
 stats3->SetTextSize(0.03);
 Delphes_bkg->Draw("Particle.PT>>hist_Gen_pip_bkg","Particle.PID==211&&Particle.Eta<2.5&&Particle.Eta>-2.5","SAMES");
 gStyle->SetOptStat(11);
  TPaveStats *stats1_bkg =(TPaveStats*)c2->GetPrimitive("stats");
  stats1_bkg->SetName("Gen Bkg");
  stats1_bkg->SetY1NDC(.05);
  stats1_bkg->SetY2NDC(.3);
  stats1_bkg->SetTextColor(1);
  stats1_bkg->SetTextSize(0.03);
  Delphes_bkg->Draw("Track.PT>>hist_Track_pip_bkg","Track.PID==211&&Track.Eta>-2.5&&Track.Eta<2.5","SAMES");
  gStyle->SetOptStat(11);
 TPaveStats *stats2_bkg =(TPaveStats*)c2->GetPrimitive("stats");
 stats2_bkg->SetName("Track Bkg");
 stats2_bkg->SetY1NDC(.05);
 stats2_bkg->SetY2NDC(.3);
 stats2_bkg->SetTextColor(3);
 stats2_bkg->SetTextSize(0.03);

  Delphes_bsm->Draw("Particle.PT>>hist_Gen_pip_bsm","Particle.PID==211&&Particle.Eta<2.5&&Particle.Eta>-2.5","SAMES");
  gStyle->SetOptStat(11);
  TPaveStats *stats1_bsm =(TPaveStats*)c2->GetPrimitive("stats");
  stats1_bsm->SetName("Gen BSM");
  stats1_bsm->SetY1NDC(.05);
  stats1_bsm->SetY2NDC(.3);
  stats1_bsm->SetTextColor(1);
  stats1_bsm->SetTextSize(0.03);
  Delphes_bsm->Draw("Track.PT>>hist_Track_pip_bsm","Track.PID==211&&Track.Eta>-2.5&&Track.Eta<2.5","SAMES");
  gStyle->SetOptStat(11);
 TPaveStats *stats3_bsm =(TPaveStats*)c2->GetPrimitive("stats");
 stats3_bsm->SetName("Track BSM");
 stats3_bsm->SetY1NDC(.05);
 stats3_bsm->SetY2NDC(.3);
 stats3_bsm->SetTextColor(3);
 stats3_bsm->SetTextSize(0.03);
 legend2->Draw();*/

  TCanvas *c2 = new TCanvas();
  TLegend *legend2 = new TLegend(0.65,0.7,0.85,0.85);

  //TH1F *hist_Rec_mu_sm = new TH1F("hist_Rec_mu_sm","hist_Rec_mu_sm",300,0.0,20.0);
  TH1F *hist_Gen_mu_sm = new TH1F("hist_Gen_mu_sm","hist_Gen_mu_sm",300,0.0,20.0);
  TH1F *hist_Track_mu_sm = new TH1F("hist_Track_mu_sm","hist_Track_mu_sm",300,0.0,20.0);
  //TH1F *hist_Rec_mu_bsm = new TH1F("hist_Rec_mu_bsm","hist_Rec_mu_bsm",300,0.0,20.0);
  TH1F *hist_Gen_mu_bsm = new TH1F("hist_Gen_mu_bsm","hist_Gen_mu_bsm",300,0.0,20.0);
  TH1F *hist_Track_mu_bsm = new TH1F("hist_Track_mu_bsm","hist_Track_mu_bsm",300,0.0,20.0);
  TH1F *hist_Gen_mu_bkg = new TH1F("hist_Gen_mu_bkg","hist_Gen_mu_bkg",300,0.0,20.0);
  TH1F *hist_Track_mu_bkg = new TH1F("hist_Track_mu_bkg","hist_Track_mu_bkg",300,0.0,20.0);
  hist_Gen_mu_sm->SetLineColor(1);
  //hist_Rec_mu_sm->SetLineColor(2);
  hist_Gen_mu_bkg->SetLineColor(1);
  hist_Track_mu_sm->SetLineColor(3);
  //hist_Rec_mu_sm->SetLineWidth(3);
  hist_Gen_mu_bkg->SetLineWidth(3);
  hist_Gen_mu_sm->SetLineWidth(3);
  hist_Track_mu_sm->SetLineWidth(3);
  hist_Track_mu_bkg->SetLineWidth(3);
  hist_Gen_mu_bsm->SetLineColor(1);
  //hist_Rec_mu_bsm->SetLineColor(2);
  hist_Track_mu_bsm->SetLineColor(3);
  hist_Track_mu_bkg->SetLineColor(3);
  //hist_Rec_mu_bsm->SetLineWidth(3);
  hist_Gen_mu_bsm->SetLineWidth(3);
  hist_Track_mu_bsm->SetLineWidth(3);
  //hist_Rec_mu_bsm->SetLineStyle(2);
  hist_Gen_mu_bsm->SetLineStyle(2);
  hist_Track_mu_bsm->SetLineStyle(2);
  hist_Gen_mu_bkg->SetLineStyle(9);
  hist_Track_mu_bkg->SetLineStyle(9);

  hist_Gen_mu_sm->GetXaxis()->SetTitle("P_{T} (GeV)");
  hist_Gen_mu_sm->GetYaxis()->SetTitle("Counts");
  hist_Gen_mu_sm->SetTitle("-2.5<#eta<2.5");
  hist_Gen_mu_sm->GetXaxis()->CenterTitle(kTRUE);
  hist_Gen_mu_sm->GetYaxis()->CenterTitle(kTRUE);

  //legend2->AddEntry(hist_Rec_mu_sm,"Reconstructed muons (SM)");
  legend2->AddEntry(hist_Gen_mu_sm,"Generated muons (SM)");
  legend2->AddEntry(hist_Gen_mu_bsm,"Generated muons (BSM)");
  legend2->AddEntry(hist_Gen_mu_bkg,"Generated muons (Bkg)");
  legend2->AddEntry(hist_Track_mu_sm,"Track muons (SM)");
  //legend2->AddEntry(hist_Rec_mu_bsm,"Reconstructed muons (BSM)");
  legend2->AddEntry(hist_Track_mu_bsm,"Track muons (BSM)");
  legend2->AddEntry(hist_Track_mu_bkg,"Track muons (Bkg)");

  Delphes_sm->Draw("Particle.PT>>hist_Gen_mu_sm","Particle.PID==13&&Particle.Eta<2.5&&Particle.Eta>-2.5");
   gStyle->SetOptStat(11);
  TPaveStats *stats1 =(TPaveStats*)c2->GetPrimitive("stats");
  stats1->SetName("Gen SM");
  stats1->SetY1NDC(.05);
  stats1->SetY2NDC(.3);
  stats1->SetTextColor(1);
  stats1->SetTextSize(0.03);
  Delphes_sm->Draw("Track.PT>>hist_Track_mu_sm","Track.PID==13&&Track.Eta>-2.5&&Track.Eta<2.5","SAMES");
   gStyle->SetOptStat(11);
 TPaveStats *stats3 =(TPaveStats*)c2->GetPrimitive("stats");
 stats3->SetName("Track SM");
 stats3->SetY1NDC(.05);
 stats3->SetY2NDC(.3);
 stats3->SetTextColor(3);
 stats3->SetTextSize(0.03);
 /*Delphes_sm->Draw("Muon.PT>>hist_Rec_mu_sm","Muon.Charge==-1","SAMES");
   gStyle->SetOptStat(11);
 TPaveStats *stats2 =(TPaveStats*)c2->GetPrimitive("stats");
 stats2->SetName("Rec SM");
 stats2->SetY1NDC(.05);
 stats2->SetY2NDC(.3);
 stats2->SetTextColor(2);
 stats2->SetTextSize(0.03);*/
 Delphes_bkg->Draw("Particle.PT>>hist_Gen_mu_bkg","Particle.PID==13&&Particle.Eta<2.5&&Particle.Eta>-2.5","SAMES");
   gStyle->SetOptStat(11);
  TPaveStats *stats1_bkg =(TPaveStats*)c2->GetPrimitive("stats");
  stats1_bkg->SetName("Gen Bkg");
  stats1_bkg->SetY1NDC(.05);
  stats1_bkg->SetY2NDC(.3);
  stats1_bkg->SetTextColor(1);
  stats1_bkg->SetTextSize(0.03);
  Delphes_bkg->Draw("Track.PT>>hist_Track_mu_bkg","Track.PID==13&&Track.Eta>-2.5&&Track.Eta<2.5","SAMES");
   gStyle->SetOptStat(11);
 TPaveStats *stats2_bkg =(TPaveStats*)c2->GetPrimitive("stats");
 stats2_bkg->SetName("Track Bkg");
 stats2_bkg->SetY1NDC(.05);
 stats2_bkg->SetY2NDC(.3);
 stats2_bkg->SetTextColor(3);
 stats2_bkg->SetTextSize(0.03);

  Delphes_bsm->Draw("Particle.PT>>hist_Gen_mu_bsm","Particle.PID==13&&Particle.Eta<2.5&&Particle.Eta>-2.5","SAMES");
   gStyle->SetOptStat(11);
  TPaveStats *stats1_bsm =(TPaveStats*)c2->GetPrimitive("stats");
  stats1_bsm->SetName("Gen BSM");
  stats1_bsm->SetY1NDC(.05);
  stats1_bsm->SetY2NDC(.3);
  stats1_bsm->SetTextColor(1);
  stats1_bsm->SetTextSize(0.03);
  /*Delphes_bsm->Draw("Muon.PT>>hist_Rec_mu_bsm","Muon.Charge==-1","SAMES");
   gStyle->SetOptStat(11);
 TPaveStats *stats2_bsm =(TPaveStats*)c2->GetPrimitive("stats");
 stats2_bsm->SetName("Rec BSM");
 stats2_bsm->SetY1NDC(.05);
 stats2_bsm->SetY2NDC(.3);
 stats2_bsm->SetTextColor(2);
 stats2_bsm->SetTextSize(0.03);*/
 Delphes_bsm->Draw("Track.PT>>hist_Track_mu_bsm","Track.PID==13&&Track.Eta>-2.5&&Track.Eta<2.5","SAMES");
   gStyle->SetOptStat(11);
 TPaveStats *stats3_bsm =(TPaveStats*)c2->GetPrimitive("stats");
 stats3_bsm->SetName("Track BSM");
 stats3_bsm->SetY1NDC(.05);
 stats3_bsm->SetY2NDC(.3);
 stats3_bsm->SetTextColor(3);
 stats3_bsm->SetTextSize(0.03);
 legend2->Draw();

  /*TCanvas *c2 = new TCanvas();
  TLegend *legend2 = new TLegend(0.65,0.7,0.85,0.85);

  TH1F *hist_Rec_e = new TH1F("hist_Rec_e","hist_Rec_e",100,0.0,15.0);
  TH1F *hist_Gen_e = new TH1F("hist_Gen_e","hist_Gen_e",100,0.0,15.0);
  hist_Gen_e->SetLineColor(kRed);
  hist_Rec_e->SetLineWidth(3);
  hist_Gen_e->SetLineWidth(3);

  hist_Rec_e->GetXaxis()->SetTitle("P_{T} (GeV)");
  hist_Rec_e->GetYaxis()->SetTitle("Counts");
  hist_Rec_e->SetTitle("Generated vs Reconstructed Muons");
  hist_Rec_e->GetXaxis()->CenterTitle(kTRUE);
  hist_Rec_e->GetYaxis()->CenterTitle(kTRUE);

  legend2->AddEntry(hist_Rec_e,"Reconstructed muons");
  legend2->AddEntry(hist_Gen_e,"Generated muons");

  Delphes->Draw("Track.PT>>hist_Rec_e","Track.PID==11");
  Delphes->Draw("Particle.PT>>hist_Gen_e","Particle.PID==11&&Particle.Eta<2.5&&Particle.Eta>-2.5","SAMES");
  legend2->Draw();*/
  
  /*TCanvas *c1 = new TCanvas();
  TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);

  TH1F *hist_Rec_mu = new TH1F("hist_Rec_mu","hist_Rec_mu",100,0.0,70.0);
  TH1F *hist_Gen_mu = new TH1F("hist_Gen_mu","hist_Gen_mu",100,0.0,70.0);
  hist_Gen_mu->SetLineColor(kRed);
  hist_Rec_mu->SetLineWidth(3);
  hist_Gen_mu->SetLineWidth(3);

  hist_Rec_mu->GetXaxis()->SetTitle("P_{T} (GeV)");
  hist_Rec_mu->GetYaxis()->SetTitle("Counts");
  hist_Rec_mu->SetTitle("Generated vs Reconstructed Muons");
  hist_Rec_mu->GetXaxis()->CenterTitle(kTRUE);
  hist_Rec_mu->GetYaxis()->CenterTitle(kTRUE);

  legend->AddEntry(hist_Rec_mu,"Reconstructed muons");
  legend->AddEntry(hist_Gen_mu,"Generated muons");

  Delphes->Draw("Muon.PT>>hist_Rec_mu","Muon.Charge==-1");
  Delphes->Draw("Particle.PT>>hist_Gen_mu","Particle.PID==13&&Particle.PT>10&&Particle.Eta<2.5&&Particle.Eta>-2.5","SAMES");
  legend->Draw();*/

  /*TCanvas *c1 = new TCanvas();
  TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);

  TH1F *hist_Rec_mu = new TH1F("hist_Rec_mu","hist_Rec_mu",100,0.0,15.0);
  TH1F *hist_Gen_mu = new TH1F("hist_Gen_mu","hist_Gen_mu",100,0.0,15.0);
  hist_Gen_mu->SetLineColor(kRed);
  hist_Rec_mu->SetLineWidth(3);
  hist_Gen_mu->SetLineWidth(3);

  hist_Rec_mu->GetXaxis()->SetTitle("P_{T} (GeV)");
  hist_Rec_mu->GetYaxis()->SetTitle("Counts");
  hist_Rec_mu->SetTitle("Generated vs Reconstructed Muons");
  hist_Rec_mu->GetXaxis()->CenterTitle(kTRUE);
  hist_Rec_mu->GetYaxis()->CenterTitle(kTRUE);

  legend->AddEntry(hist_Rec_mu,"Reconstructed muons");
  legend->AddEntry(hist_Gen_mu,"Generated muons");

  Delphes->Draw("Track.PT>>hist_Rec_mu","Track.PID==13");
  Delphes->Draw("Particle.PT>>hist_Gen_mu","Particle.PID==13&&Particle.Eta<2.5&&Particle.Eta>-2.5","SAMES");
  legend->Draw();*/

  /*TCanvas *c2 = new TCanvas();
  TLegend *legend2 = new TLegend(0.65,0.7,0.85,0.85);

  TH1F *hist_Rec_e = new TH1F("hist_Rec_e","hist_Rec_e",100,0.0,15.0);
  TH1F *hist_Gen_e = new TH1F("hist_Gen_e","hist_Gen_e",100,0.0,15.0);
  hist_Gen_e->SetLineColor(kRed);
  hist_Rec_e->SetLineWidth(3);
  hist_Gen_e->SetLineWidth(3);

  hist_Rec_e->GetXaxis()->SetTitle("P_{T} (GeV)");
  hist_Rec_e->GetYaxis()->SetTitle("Counts");
  hist_Rec_e->SetTitle("Generated vs Reconstructed Electrons");
  hist_Rec_e->GetXaxis()->CenterTitle(kTRUE);
  hist_Rec_e->GetYaxis()->CenterTitle(kTRUE);

  legend2->AddEntry(hist_Rec_e,"Reconstructed electrons");
  legend2->AddEntry(hist_Gen_e,"Generated electrons");

  Delphes->Draw("Track.PT>>hist_Rec_e","Track.PID==11");
  Delphes->Draw("Particle.PT>>hist_Gen_e","Particle.PID==11&&Particle.Eta<2.5&&Particle.Eta>-2.5","SAMES");
  legend2->Draw();*/

  /*TCanvas *c2 = new TCanvas();
  TLegend *legend2 = new TLegend(0.65,0.7,0.85,0.85);

  TH1F *hist_Rec_e_sm = new TH1F("hist_Rec_e_sm","hist_Rec_e_sm",300,0.0,20.0);
  TH1F *hist_Gen_e_sm = new TH1F("hist_Gen_e_sm","hist_Gen_e_sm",300,0.0,20.0);
  TH1F *hist_Track_e_sm = new TH1F("hist_Track_e_sm","hist_Track_e_sm",300,0.0,20.0);
  TH1F *hist_Rec_e_bsm = new TH1F("hist_Rec_e_bsm","hist_Rec_e_bsm",300,0.0,20.0);
  TH1F *hist_Gen_e_bsm = new TH1F("hist_Gen_e_bsm","hist_Gen_e_bsm",300,0.0,20.0);
  TH1F *hist_Track_e_bsm = new TH1F("hist_Track_e_bsm","hist_Track_e_bsm",300,0.0,20.0);
  hist_Gen_e_sm->SetLineColor(1);
  hist_Rec_e_sm->SetLineColor(2);
  hist_Track_e_sm->SetLineColor(3);
  hist_Rec_e_sm->SetLineWidth(3);
  hist_Gen_e_sm->SetLineWidth(3);
  hist_Track_e_sm->SetLineWidth(3);
  hist_Gen_e_bsm->SetLineColor(1);
  hist_Rec_e_bsm->SetLineColor(2);
  hist_Track_e_bsm->SetLineColor(3);
  hist_Rec_e_bsm->SetLineWidth(3);
  hist_Gen_e_bsm->SetLineWidth(3);
  hist_Track_e_bsm->SetLineWidth(3);
  hist_Rec_e_bsm->SetLineStyle(2);
  hist_Gen_e_bsm->SetLineStyle(2);
  hist_Track_e_bsm->SetLineStyle(2);

  hist_Gen_e_sm->GetXaxis()->SetTitle("P_{T} (GeV)");
  hist_Gen_e_sm->GetYaxis()->SetTitle("Counts");
  hist_Gen_e_sm->SetTitle("-2.5<#eta<2.5");
  hist_Gen_e_sm->GetXaxis()->CenterTitle(kTRUE);
  hist_Gen_e_sm->GetYaxis()->CenterTitle(kTRUE);

  legend2->AddEntry(hist_Rec_e_sm,"Reconstructed electrons (SM)");
  legend2->AddEntry(hist_Gen_e_sm,"Generated electrons (SM)");
  legend2->AddEntry(hist_Track_e_sm,"Track electrons (SM)");
  legend2->AddEntry(hist_Rec_e_bsm,"Reconstructed electrons (BSM)");
  legend2->AddEntry(hist_Gen_e_bsm,"Generated electrons (BSM)");
  legend2->AddEntry(hist_Track_e_bsm,"Track electrons (BSM)");

  Delphes_sm->Draw("Particle.PT>>hist_Gen_e_sm","Particle.PID==11&&Particle.Eta<2.5&&Particle.Eta>-2.5");
   gStyle->SetOptStat(11);
  TPaveStats *stats1 =(TPaveStats*)c2->GetPrimitive("stats");
  stats1->SetName("Gen SM");
  stats1->SetY1NDC(.05);
  stats1->SetY2NDC(.3);
  stats1->SetTextColor(1);
  stats1->SetTextSize(0.03);
  Delphes_sm->Draw("Electron.PT>>hist_Rec_e_sm","Electron.Charge==-1","SAMES");
   gStyle->SetOptStat(11);
 TPaveStats *stats2 =(TPaveStats*)c2->GetPrimitive("stats");
 stats2->SetName("Rec SM");
 stats2->SetY1NDC(.05);
 stats2->SetY2NDC(.3);
 stats2->SetTextColor(2);
 stats2->SetTextSize(0.03);
  Delphes_sm->Draw("Track.PT>>hist_Track_e_sm","Track.PID==11&&Track.Eta>-2.5&&Track.Eta<2.5","SAMES");
   gStyle->SetOptStat(11);
 TPaveStats *stats3 =(TPaveStats*)c2->GetPrimitive("stats");
 stats3->SetName("Track SM");
 stats3->SetY1NDC(.05);
 stats3->SetY2NDC(.3);
 stats3->SetTextColor(3);
 stats3->SetTextSize(0.03);

  Delphes_bsm->Draw("Particle.PT>>hist_Gen_e_bsm","Particle.PID==11&&Particle.Eta<2.5&&Particle.Eta>-2.5","SAMES");
   gStyle->SetOptStat(11);
  TPaveStats *stats1_bsm =(TPaveStats*)c2->GetPrimitive("stats");
  stats1_bsm->SetName("Gen BSM");
  stats1_bsm->SetY1NDC(.05);
  stats1_bsm->SetY2NDC(.3);
  stats1_bsm->SetTextColor(1);
  stats1_bsm->SetTextSize(0.03);
  Delphes_bsm->Draw("Electron.PT>>hist_Rec_e_bsm","Electron.Charge==-1","SAMES");
   gStyle->SetOptStat(11);
 TPaveStats *stats2_bsm =(TPaveStats*)c2->GetPrimitive("stats");
 stats2_bsm->SetName("Rec BSM");
 stats2_bsm->SetY1NDC(.05);
 stats2_bsm->SetY2NDC(.3);
 stats2_bsm->SetTextColor(2);
 stats2_bsm->SetTextSize(0.03);
  Delphes_bsm->Draw("Track.PT>>hist_Track_e_bsm","Track.PID==11&&Track.Eta>-2.5&&Track.Eta<2.5","SAMES");
   gStyle->SetOptStat(11);
 TPaveStats *stats3_bsm =(TPaveStats*)c2->GetPrimitive("stats");
 stats3_bsm->SetName("Track BSM");
 stats3_bsm->SetY1NDC(.05);
 stats3_bsm->SetY2NDC(.3);
 stats3_bsm->SetTextColor(3);
 stats3_bsm->SetTextSize(0.03);
  legend2->Draw();*/


  /*TCanvas *c1 = new TCanvas();
  TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);

  TH1F *hist_Rec_mu = new TH1F("hist_Rec_mu","hist_Rec_mu",200,0.0,10.0);
  TH1F *hist_Gen_mu = new TH1F("hist_Gen_mu","hist_Gen_mu",200,0.0,10.0);
  hist_Gen_mu->SetLineColor(kRed);
  hist_Rec_mu->SetLineWidth(3);
  hist_Gen_mu->SetLineWidth(3);

  hist_Rec_mu->GetXaxis()->SetTitle("P_{T} (GeV)");
  hist_Rec_mu->GetYaxis()->SetTitle("Counts");
  hist_Rec_mu->SetTitle("Generated vs Reconstructed Muons");
  hist_Rec_mu->GetXaxis()->CenterTitle(kTRUE);
  hist_Rec_mu->GetYaxis()->CenterTitle(kTRUE);

  legend->AddEntry(hist_Rec_mu,"Reconstructed muons");
  legend->AddEntry(hist_Gen_mu,"Generated muons");

  Delphes->Draw("Muon.PT>>hist_Rec_mu");
  Delphes->Draw("Particle.PT>>hist_Gen_mu","Particle.PID==13&&Particle.Eta<2.5&&Particle.Eta>-2.5","SAMES");
  legend->Draw();

  TCanvas *c2 = new TCanvas();
  TLegend *legend2 = new TLegend(0.65,0.7,0.85,0.85);

  TH1F *hist_Rec_e = new TH1F("hist_Rec_e","hist_Rec_e",200,0.0,10.0);
  TH1F *hist_Gen_e = new TH1F("hist_Gen_e","hist_Gen_e",200,0.0,10.0);
  hist_Gen_e->SetLineColor(kRed);
  hist_Rec_e->SetLineWidth(3);
  hist_Gen_e->SetLineWidth(3);

  hist_Rec_e->GetXaxis()->SetTitle("P_{T} (GeV)");
  hist_Rec_e->GetYaxis()->SetTitle("Counts");
  hist_Rec_e->SetTitle("Generated vs Reconstructed Electrons");
  hist_Rec_e->GetXaxis()->CenterTitle(kTRUE);
  hist_Rec_e->GetYaxis()->CenterTitle(kTRUE);

  legend2->AddEntry(hist_Rec_e,"Reconstructed electrons");
  legend2->AddEntry(hist_Gen_e,"Generated electrons");

  Delphes->Draw("Electron.PT>>hist_Rec_e");
  Delphes->Draw("Particle.PT>>hist_Gen_e","Particle.PID==11&&Particle.Eta<2.5&&Particle.Eta>-2.5","SAMES");
  legend2->Draw();

  TCanvas *c3 = new TCanvas();
  TLegend *legend3 = new TLegend(0.65,0.7,0.85,0.85);

  TH1F *hist_Rec_pip = new TH1F("hist_Rec_pip","hist_Rec_pip",200,0.0,10.0);
  TH1F *hist_Gen_pip = new TH1F("hist_Gen_pip","hist_Gen_pip",200,0.0,10.0);
  hist_Gen_pip->SetLineColor(kRed);
  hist_Rec_pip->SetLineWidth(3);
  hist_Gen_pip->SetLineWidth(3);

  hist_Rec_pip->GetXaxis()->SetTitle("P_{T} (GeV)");
  hist_Rec_pip->GetYaxis()->SetTitle("Counts");
  hist_Rec_pip->SetTitle("Generated vs Reconstructed Positive Pions");
  hist_Rec_pip->GetXaxis()->CenterTitle(kTRUE);
  hist_Rec_pip->GetYaxis()->CenterTitle(kTRUE);

  legend3->AddEntry(hist_Rec_pip,"Reconstructed positive pions");
  legend3->AddEntry(hist_Gen_pip,"Generated positive pions");

  Delphes->Draw("Track.PT>>hist_Rec_pip","Track.PID==211");
  Delphes->Draw("Particle.PT>>hist_Gen_pip","Particle.PID==211&&Particle.Eta<2.5&&Particle.Eta>-2.5","SAMES");
  legend3->Draw();

  TCanvas *c4 = new TCanvas();
  TLegend *legend4 = new TLegend(0.65,0.7,0.85,0.85);

  TH1F *hist_Rec_kp = new TH1F("hist_Rec_kp","hist_Rec_kp",200,0.0,10.0);
  TH1F *hist_Gen_kp = new TH1F("hist_Gen_kp","hist_Gen_kp",200,0.0,10.0);
  hist_Gen_kp->SetLineColor(kRed);
  hist_Rec_kp->SetLineWidth(3);
  hist_Gen_kp->SetLineWidth(3);

  hist_Rec_kp->GetXaxis()->SetTitle("P_{T} (GeV)");
  hist_Rec_kp->GetYaxis()->SetTitle("Counts");
  hist_Rec_kp->SetTitle("Generated vs Reconstructed Positive Kaons");
  hist_Rec_kp->GetXaxis()->CenterTitle(kTRUE);
  hist_Rec_kp->GetYaxis()->CenterTitle(kTRUE);

  legend4->AddEntry(hist_Rec_kp,"Reconstructed positive kaons");
  legend4->AddEntry(hist_Gen_kp,"Generated positive kaons");

  Delphes->Draw("Track.PT>>hist_Rec_kp","Track.PID==321");
  Delphes->Draw("Particle.PT>>hist_Gen_kp","Particle.PID==321&&Particle.Eta<2.5&&Particle.Eta>-2.5","SAMES");
  legend4->Draw();*/
}
