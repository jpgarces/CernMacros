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


void fstate_electrons_bkg(){
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");

  TString inputFile = "/home/juan/sm_bkg_minv0p_pt1_NNLO_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *daughter, *tau_n, *tau_p;

  TFile *outf = new TFile("electrons_rapidity_bkg.root","RECREATE");

  TH1F *hist_e_bkg_rapidity = new TH1F("hist_e_bkg_rapidity", "hist_e_bkg_rapidity",100, -10.0, 10.0);

  TH1F *hist_ep_bkg_rapidity = new TH1F("hist_ep_bkg_rapidity", "hist_ep_bkg_rapidity", 100, -10.0, 10.0);

  
  
  int iTau_n, iTau_p;
  
  for(int entry = 0; entry < allEntries; ++entry){
    //for(int entry = 0; entry < 1000; ++entry){                                                                                                                                                          
    treeReader->ReadEntry(entry);
    for(int j = 0; j < branchParticle->GetEntriesFast(); ++j){
      particle = (GenParticle*) branchParticle->At(j);
      if (particle->PID==11&&particle->Status==1){
           hist_e_bkg_rapidity->Fill(particle->Rapidity);
          //cout << "Tau->electron pT: " << particle->rapidity << endl;
      }
      if (particle->PID==-11&&particle->Status==1){
           hist_ep_bkg_rapidity->Fill(particle->Rapidity);
          //cout << "Tau->electron pT: " << particle->rapidity << endl;
      }
   }
  }
  cout << "** Exiting..." << endl;
  /*hist_e_bkg_rapidity->Scale(1/(hist_e_bkg_rapidity->GetEntries()));
  hist_e_else_rapidity->Scale(1/(hist_e_else_rapidity->GetEntries()));
  hist_ep_bkg_rapidity->Scale(1/(hist_ep_bkg_rapidity->GetEntries()));
  hist_ep_else_rapidity->Scale(1/(hist_ep_else_rapidity->GetEntries()));*/
  outf->Write();
  outf->Close();
  delete treeReader;
  delete chain;
}
