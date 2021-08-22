// run it in /root/Delphes-3.4.2 as root -l -q examples/gg2taus2chpions.C 

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

void count_tau_jets(){
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");
  
  //TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events_NNL.root";
  
  //TString inputFile = "/home/juan/sm_UFO_minv0p_pt1_NNLO_delphes_events.root";

  TString inputFile = "/home/juan/sm_bkg_minv0p_pt1_NNLO_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");
  TClonesArray *branchJet = treeReader->UseBranch("Jet");

  GenParticle *particle, *tau, *tau_n, *tau_p, *daughter;

  Jet *jet;

  int iTau_p, iTau_n, muon_count=0, it, mom_id, n_taun_jet=0, n_taup_jet=0;

  
  int phtau_count=0, rmntau_count=0, tau_count=0, miss_tag=0, n_evnt_jet=0;
  
  
  for(int entry = 0; entry < allEntries; ++entry){
    //if (entry>100) break;
    treeReader->ReadEntry(entry);
    for(int j = 0; j < branchParticle->GetEntriesFast(); ++j){                                   
      particle = (GenParticle*) branchParticle->At(j);
      if (particle->PID==15){
          tau_n = (GenParticle*) branchParticle->At(j);
	  iTau_n=j;
      }
      /*if (particle->PID==-15){
          tau_p = (GenParticle*) branchParticle->At(j);
	  iTau_p=j;
	  }*/
     }
     tau_count+=1;
     if ( branchJet->GetEntriesFast()!=0){
       n_evnt_jet+=1;
       //cout << "Number of jets: " << branchJet->GetEntriesFast() << endl;
     }
     for(int i = 0; i < branchJet->GetEntriesFast(); ++i){                                   
      jet = (Jet*) branchJet->At(i);
      if (jet->TauTag==1&&jet->Charge==-1){
	n_taun_jet+=1;
      }
      if (jet->TauTag==1&&jet->Charge==1){
	n_taup_jet+=1;
      }
      
      /*if (Jet->TauTag==0){
	  miss_tag+=1;
	  }*/
     }
  }
     cout << "Total number of taus: "<< tau_count << endl;
     cout << "Number of jets tagged as tauN: "<< n_taun_jet << endl;
     cout << "Number of jets tagged as tauP: "<< n_taup_jet << endl;
     cout << "Number of events with at least one jet: "<< n_evnt_jet << endl;
     
  delete treeReader;
  delete chain;
}
