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


void separate_e(){
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");

  TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events_old.root";
  

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *daughter, *tau_n, *tau_p;

  TFile *outf = new TFile("electrons_PT_sm_sep.root","RECREATE");

  TH1F *hist_tau_e_PT = new TH1F("hist_tau_e_PT", "hist_tau_e_PT", 100, 0.0, 100.0);
  TH1F *hist_else_e_PT = new TH1F("hist_else_e_PT", "hist_else_e_PT", 100, 0.0, 100.0);
  
  Int_t iTau_n, iTau_p, count_e=0;
  
  for(int entry = 0; entry < allEntries; ++entry){
    //for(int entry = 0; entry < 1000; ++entry){            
    treeReader->ReadEntry(entry);
    for(int j = 0; j < branchParticle->GetEntriesFast(); ++j){
      particle = (GenParticle*) branchParticle->At(j);
      if (particle->PID==15){
          tau_n = (GenParticle*) branchParticle->At(j);
          iTau_n=j;
          //cout << "Negative tau: " << iTau_n << endl;     
       }
      if (particle->PID==-15){
          tau_p = (GenParticle*) branchParticle->At(j);
          iTau_p=j;
          //cout << "Positive tau: " << iTau_p << endl;                                                                                                                                                  
      }
      if (particle->PID==11&&particle->Status>0){
	count_e+=1;
        if (particle->M1 == iTau_n || particle->M2 == iTau_n){
	   hist_tau_e_PT->Fill(particle->PT);
          //cout << "Tau->electron pT: " << particle->PT << endl;
        }else{
	  hist_else_e_PT->Fill(particle->PT);
	}
      }
    }
  }
  cout << count_e << endl;
  cout << "** Exiting..." << endl;
  //hist_tau_e_PT->Scale(1/count_e);
  //hist_else_e_PT->Scale(1/count_e);
  /*hist_ep_tau_PT->Scale(1/(hist_ep_tau_PT->GetEntries()));
  hist_ep_else_PT->Scale(1/(hist_ep_else_PT->GetEntries()));*/
  outf->Write();
  outf->Close();
  delete treeReader;
  delete chain;
}
