// run it in /root/Delphes-3.4.2 as root -l -q examples/gg2taus2chpions.C 

#ifdef __CLING__
R__LOAD_LIBRARY(/root/Delphes-3.4.2/libDelphes.so)

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

void gg2taus2chkaon(){
  gSystem->Load("/root/MG5_aMC_v2_7_3/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");
  
  TString inputFile = "/root/bsm_minv0p_pt1_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *tau, *tau_n, *tau_p, *daughter;

  int iTau_p, iTau_n;

  
  int ch_nk_1=0;
  int ch_pk_1=0;
  
  for(int entry = 0; entry < allEntries; ++entry){
  //for(int entry = 29000; entry < 30000; ++entry){
    treeReader->ReadEntry(entry);
    for(int j = 0; j < branchParticle->GetEntriesFast(); ++j){                                   
      particle = (GenParticle*) branchParticle->At(j);
      if (particle->PID==15){
          tau_n = (GenParticle*) branchParticle->At(j);
	  iTau_n=j;
      }
      if (particle->PID==-15){
          tau_p = (GenParticle*) branchParticle->At(j);
	  iTau_p=j;
      }
     }
    int daughter_pids_n[10]={0,0,0,0,0,0,0,0,0,0};
    int n=0;
    for(int k=tau_n->D1; k<=tau_n->D2; ++k){
      daughter=(GenParticle*) branchParticle->At(k);
      if (n<10){
        if (daughter->M1 == iTau_n || daughter->M2 == iTau_n){
	  daughter_pids_n[n]=daughter->PID;
	  n+=1;
        }
      }
    }
    int n_ch_nk=0;
    for(int l = 0; l<10; ++l){
      if (daughter_pids_n[l]==-321) n_ch_nk+=1;
    }
    int daughter_pids_p[10]={0,0,0,0,0,0,0,0,0,0};
    n=0;
    for(int k=tau_p->D1; k<=tau_p->D2; ++k){
      daughter=(GenParticle*) branchParticle->At(k);
      if (n<10){
        if (daughter->M1 == iTau_p || daughter->M2 == iTau_p){
	  daughter_pids_p[n]=daughter->PID;
	  n+=1;
        }
      }
    }
    
    int n_ch_pk=0;
    for(int l = 0; l<10; ++l){
      if (daughter_pids_p[l]==321) n_ch_pk+=1;
    }
    
    if (n_ch_nk==1) ch_nk_1+=1;
    if (n_ch_pk==1) ch_pk_1+=1;
   }
  cout << "Number of tau decays into 1 negative Kaon: " << ch_nk_1 << endl;
  cout << "Number of tau decays into 1 positive Kaon: " << ch_pk_1 << endl;
  cout << "Total number of events: " << allEntries << endl;
  cout << "** Exiting..." << endl;
  delete treeReader;
  delete chain;
}
