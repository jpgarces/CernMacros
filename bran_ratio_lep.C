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


void bran_ratio_lep(){
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");
  
  //TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events_NNL.root";

  TString inputFile = "/home/juan/sm_UFO_minv0p_pt1_NNLO_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *tau, *tau_n, *tau_p, *daughter;

  int iTau_p, iTau_n;

  int n_lep_decays = 0;

  int n_e_decays=0;
  int n_mu_decays=0;
  int n_ep_decays=0;
  int n_mup_decays=0;
  
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
     }
    int daughter_pids[3]={0,0,0};
    int n=0;
    for(int k=tau_n->D1; k<=tau_n->D2; ++k){
      daughter=(GenParticle*) branchParticle->At(k);
      if (n<3){
        if (daughter->M1 == iTau_n || daughter->M2 == iTau_n){
	  daughter_pids[n]=daughter->PID;
	  n+=1;
        }
      }
    }
    int d1_id = daughter_pids[0];
    int d2_id = daughter_pids[1];
    int d3_id = daughter_pids[2];
    //cout <<entry<< ": "<< d1_id << " " << d2_id << " " << d3_id << endl;
    if (d1_id==13&&d2_id==-14&&d3_id==16 || d1_id==-14&&d2_id==13&&d3_id==16 || d1_id==-14&&d2_id==16&&d3_id==13 || d1_id==16&&d2_id==13&&d3_id==-14 || d1_id==16&&d2_id==-14&&d3_id==13 || d1_id==13&&d2_id==16&&d3_id==-14){
      n_lep_decays+=1;
      n_mu_decays+=1;
    }
    if (d1_id==11&&d2_id==-12&&d3_id==16 || d1_id==-12&&d2_id==11&&d3_id==16 || d1_id==-12&&d2_id==16&&d3_id==11 || d1_id==16&&d2_id==11&&d3_id==-12 || d1_id==16&&d2_id==-12&&d3_id==11 || d1_id==11&&d2_id==16&&d3_id==-12){
      n_lep_decays+=1;
      n_e_decays+=1;
    }
    n=0;
    daughter_pids[0]=0;
    daughter_pids[1]=0;
    daughter_pids[2]=0;
    for(int k=tau_p->D1; k<=tau_p->D2; ++k){
      daughter=(GenParticle*) branchParticle->At(k);
      if (n<3){
        if (daughter->M1 == iTau_p || daughter->M2 == iTau_p){
	  daughter_pids[n]=daughter->PID;
	  n+=1;
        }
      }
    }
    d1_id = daughter_pids[0];
    d2_id = daughter_pids[1];
    d3_id = daughter_pids[2];
    //cout <<entry<< ": "<< d1_id << " " << d2_id << " " << d3_id << endl; 
    if (d1_id==-11&&d2_id==12&&d3_id==-16 || d1_id==12&&d2_id==-11&&d3_id==-16 || d1_id==12&&d2_id==-16&&d3_id==-11 || d1_id==-16&&d2_id==-11&&d3_id==12 || d1_id==-16&&d2_id==12&&d3_id==-11 || d1_id==-11&&d2_id==-16&&d3_id==12){
      n_lep_decays+=1;
      n_ep_decays+=1;
    }
    if (d1_id==-13&&d2_id==14&&d3_id==-16 || d1_id==14&&d2_id==-13&&d3_id==-16 || d1_id==14&&d2_id==-16&&d3_id==-13 || d1_id==-16&&d2_id==-13&&d3_id==14 || d1_id==-16&&d2_id==14&&d3_id==-13 || d1_id==-13&&d2_id==-16&&d3_id==14){
      n_lep_decays+=1;
      n_mup_decays+=1;
    }
  }
  cout << "Number of tau decays into electrons: " << n_e_decays << " -> " << n_e_decays*100/200000.0 << "%" <<  endl;
  cout << "Number of tau decays into positrons: " << n_ep_decays << " -> " << n_ep_decays*100/200000.0 << "%" << endl;
  cout << "Number of tau decays into muons: " << n_mu_decays  << " -> " << n_mu_decays*100/200000.0 << "%" << endl;
  cout << "Number of tau decays into positive muons: " << n_mup_decays << " -> " << n_mup_decays*100/200000.0 << "%" <<endl;
  cout << "Total number of events: " << allEntries << endl;
  cout << "** Exiting..." << endl;
  delete treeReader;
  delete chain;
}
