#ifdef __CLING__
R__LOAD_LIBRARY(/home/juan/Delphes-3.5.0/libDelphes.so)

#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#include "external/ExRootAnalysis/ExRootResult.h"
   
#else
class ExRootTreeReader;
class ExRootResult;
class ExRootLHEFReader;
#endif

#include <iostream>
#include <cmath>
#include <array>
#include <vector>
#include <TArrayC.h>
#include <string>
#include "TH1.h"                                                               
#include "TH2D.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TVirtualPad.h"
#include "TApplication.h"
#include "TBranch.h"
#include "TBranchElement.h"
#include "TFile.h"                                                          
#include  <map>
#include "TTree.h"                                                                    
#include "TROOT.h"


void fstate_e_mu_bkg(){
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");

  TString inputFile = "/home/juan/sm_bkg_minv0p_pt1_NNLO_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *daughter, *tau_n, *tau_p;

  TFile *outf = new TFile("e_mu_PT_bkg.root","RECREATE");

  TH1F *hist_e_PT = new TH1F("hist_e_PT", "hist_e_PT", 200, 0.0, 100.0);
  TH1F *hist_mu_PT = new TH1F("hist_mu_PT", "hist_mu_PT", 200, 0.0, 100.0);
  
  
  int iTau_n, iTau_p, e_count, mu_count, ep_count, mup_count;

  Double_t e_PT, mu_PT;
  
for(int entry = 0; entry < allEntries; ++entry){
  //for(int entry = 0; entry < 1000; ++entry){             
  treeReader->ReadEntry(entry);
  e_count=0;
  mu_count=0;
  ep_count=0;
  mup_count=0;
  for(int j = 0; j < branchParticle->GetEntriesFast(); ++j){
    particle = (GenParticle*) branchParticle->At(j);
    if (particle->PID==11&&particle->Status==1){
      e_count+=1;
      e_PT=particle->PT;
    }
    if (particle->PID==13&&particle->Status==1){
      mu_count+=1;
      mu_PT=particle->PT;
    }
    if (particle->PID==-11&&particle->Status==1){
      ep_count+=1;
    }
    if (particle->PID==-13&&particle->Status==1){
      mup_count+=1;
    }
 }
 if (e_count==1&&ep_count==1){
   hist_e_PT->Fill(e_PT);
 }
 if (mu_count==1&&mup_count==1){
   hist_mu_PT->Fill(mu_PT);
 }
}
  cout << "** Exiting..." << endl;
  /*hist_e_PT->Scale(1/(hist_e_PT->GetEntries()));
  hist_e_tau_PT->Scale(1/(hist_e_tau_PT->GetEntries()));
  hist_e_else_PT->Scale(1/(hist_e_else_PT->GetEntries()));
  hist_ep_tau_PT->Scale(1/(hist_ep_tau_PT->GetEntries()));
  hist_ep_else_PT->Scale(1/(hist_ep_else_PT->GetEntries()));*/
  outf->Write();
  outf->Close();
  delete treeReader;
  delete chain;
}
