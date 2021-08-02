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

  TFile *f = new TFile("/home/juan/bsm_minv0p_pt1_delphes_events.root");

  TTree *Delphes = (TTree*) f->Get("Delphes");

  TCanvas *c1 = new TCanvas();
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

  Delphes->Draw("Muon.PT>>hist_Rec_mu");
  Delphes->Draw("Particle.PT>>hist_Gen_mu","Particle.PID==13&&Particle.PT>10&&Particle.Eta<2.5&&Particle.Eta>-2.5","SAMES");
  legend->Draw();

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
  legend->Draw();

  TCanvas *c2 = new TCanvas();
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
