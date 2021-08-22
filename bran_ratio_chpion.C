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


void bran_ratio_chpion(){
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");
  
  TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events_NNL.root";

  //TString inputFile = "/home/juan/sm_UFO_minv0p_pt1_NNLO_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *tau, *tau_n, *tau_p, *daughter;

  int iTau_p, iTau_n;

  
  int ch_pi_1_n=0;
  int ch_pi_3_n=0;
  int ch_pi_1_p=0;
  int ch_pi_3_p=0;
  
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
    int n_pi0_n=0;
    //cout << "-----START---- " << endl;
    for(int k=tau_n->D1; k<=tau_n->D2; ++k){
      daughter=(GenParticle*) branchParticle->At(k);
      if (n<10){
        if (daughter->M1 == iTau_n || daughter->M2 == iTau_n){
	  daughter_pids_n[n]=daughter->PID;
	  //cout << daughter->PID << endl;
	  n+=1;
        }
      }
    }
    //cout << "------END-----" << endl;
    int n_ch_pi_nt=0;
    for(int l = 0; l<10; ++l){
      if (daughter_pids_n[l]==-211 || daughter_pids_n[l]==211) n_ch_pi_nt+=1;
      if (daughter_pids_n[l]==111) n_pi0_n+=1;
      //if (daughter_pids_n[l]!=-211&&daughter_pids_n[l]!=211&&daughter_pids_n[l]!=111&&daughter_pids_n[l]!=22&&daughter_pids_n[l]!=21&&daughter_pids_n[l]!=11&&daughter_pids_n[l]!=-11&&daughter_pids_n[l]!=12&&daughter_pids_n[l]!=-12&&daughter_pids_n[l]!=13&&daughter_pids_n[l]!=-13&&daughter_pids_n[l]!=14&&daughter_pids_n[l]!=-14&&daughter_pids_n[l]!=16&&daughter_pids_n[l]!=-16&&daughter_pids_n[l]!=0){
      //cout << daughter_pids_n[l] << endl;
      //}
    }
    //if (n_pi0_n>3){
    //cout << "Number of neutral pions = " << n_pi0_n << endl;
    //}
    if (n_ch_pi_nt==1&&n_pi0_n<=3&&n==(n_ch_pi_nt+n_pi0_n+1)) ch_pi_1_n+=1;
    if (n_ch_pi_nt==3&&n_pi0_n<=3&&n==(n_ch_pi_nt+n_pi0_n+1)) ch_pi_3_n+=1;
    
    int n_pi0_p=0;
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
    
    int n_ch_pi_pt=0;
    for(int l = 0; l<10; ++l){
      if (daughter_pids_p[l]==-211 || daughter_pids_p[l]==211) n_ch_pi_pt+=1;
      if (daughter_pids_p[l]==111) n_pi0_p+=1;
      //if (daughter_pids_p[l]!=-211&&daughter_pids_p[l]!=211&&daughter_pids_p[l]!=111&&daughter_pids_p[l]!=22&&daughter_pids_p[l]!=21&&daughter_pids_p[l]!=11&&daughter_pids_p[l]!=-11&&daughter_pids_p[l]!=12&&daughter_pids_p[l]!=-12&&daughter_pids_p[l]!=13&&daughter_pids_p[l]!=-13&&daughter_pids_p[l]!=14&&daughter_pids_p[l]!=-14&&daughter_pids_p[l]!=16&&daughter_pids_p[l]!=-16&&daughter_pids_p[l]!=0){
      //cout << daughter_pids_p[l] << endl;
      //}
    }

    //if (n_pi0_p>3){
    //cout << "Number of neutral pions = " << n_pi0_p << endl;
    //}
    
    if (n_ch_pi_pt==1&&n_pi0_p<=3&&n==(n_ch_pi_pt+n_pi0_p+1)) ch_pi_1_p+=1;
    if (n_ch_pi_pt==3&&n_pi0_p<=3&&n==(n_ch_pi_pt+n_pi0_p+1)) ch_pi_3_p+=1;
   }
  cout << "Number of tau decays into 1 negative pion and up to 3 neutral pions: " << ch_pi_1_n << " -> " << ch_pi_1_n*100/200000.0 << "%" <<  endl;
  cout << "Number of tau decays into 2 negative pions, 1 positive pion and up to 3 neutral pions: " << ch_pi_3_n << " -> " << ch_pi_3_n*100/200000.0 << "%" << endl;
  cout << "Number of tau decays into 1 positive pion and up to 3 neutral pions: " << ch_pi_1_p << " -> " << ch_pi_1_p*100/200000.0 << "%" << endl;
  cout << "Number of tau decays into 2 positive pions, 1 negative pion and up to 3 neutral pions: " << ch_pi_3_p << " -> " << ch_pi_3_p*100/200000.0 << "%" << endl;
  cout << "Total number of events: " << allEntries << endl;
  cout << "** Exiting..." << endl;
  delete treeReader;
  delete chain;
}
