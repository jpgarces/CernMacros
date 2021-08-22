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


void fstate_muons_bkg(){
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");

  TString inputFile = "/home/juan/sm_bkg_minv0p_pt1_NNLO_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *daughter, *tau_n, *tau_p;

  TFile *outf = new TFile("muons_PT_bkg.root","RECREATE");

  TH1F *hist_mu_bkg_PT = new TH1F("hist_mu_bkg_PT", "hist_mu_bkg_PT", 200, 0.0, 20.0);

  TH1F *hist_mup_bkg_PT = new TH1F("hist_mup_bkg_PT", "hist_mup_bkg_PT", 200, 0.0, 20.0);

  
  
  int iTau_n, iTau_p;
  
  for(int entry = 0; entry < allEntries; ++entry){
    //for(int entry = 0; entry < 1000; ++entry){                                                                                                                                                          
    treeReader->ReadEntry(entry);
    for(int j = 0; j < branchParticle->GetEntriesFast(); ++j){
      particle = (GenParticle*) branchParticle->At(j);
      if (particle->PID==13&&particle->Status==1){
           hist_mu_bkg_PT->Fill(particle->PT);
          //cout << "Tau->electron pT: " << particle->PT << endl;
      }
      if (particle->PID==-13&&particle->Status==1){
           hist_mup_bkg_PT->Fill(particle->PT);
          //cout << "Tau->electron pT: " << particle->PT << endl;
      }
   }
  }
  cout << "** Exiting..." << endl;
  /*hist_mu_bkg_PT->Scale(1/(hist_mu_bkg_PT->GetEntries()));
  hist_mu_else_PT->Scale(1/(hist_mu_else_PT->GetEntries()));
  hist_mup_bkg_PT->Scale(1/(hist_mup_bkg_PT->GetEntries()));
  hist_mup_else_PT->Scale(1/(hist_mup_else_PT->GetEntries()));*/
  outf->Write();
  outf->Close();
  delete treeReader;
  delete chain;
}
