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

void fstate_pions(){
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");
  
  TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *daughter, *tau_n, *tau_p;

  TFile *outf = new TFile("pions_Rapidity.root","RECREATE");

  TH1F *hist_pip_tau_Rapidity = new TH1F("hist_pip_tau_Rapidity", "hist_pip_tau_Rapidity", 100, -12.0, 12.0);

  TH1F *hist_pi0_tau_Rapidity = new TH1F("hist_pi0_tau_Rapidity", "hist_pi0_tau_Rapidity", 100, -12.0, 12.0);

  TH1F *hist_pim_tau_Rapidity = new TH1F("hist_pim_tau_Rapidity", "hist_pim_tau_Rapidity", 100, -12.0, 12.0);

  TH1F *hist_pip_tau_Rapidity_3 = new TH1F("hist_pip_tau_Rapidity_3", "hist_pip_tau_Rapidity_3", 100, -12.0, 12.0);

  TH1F *hist_pi0_tau_Rapidity_3 = new TH1F("hist_pi0_tau_Rapidity_3", "hist_pi0_tau_Rapidity_3", 100, -12.0, 12.0);

  TH1F *hist_pim_tau_Rapidity_3 = new TH1F("hist_pim_tau_Rapidity_3", "hist_pim_tau_Rapidity_3", 100, -12.0, 12.0);
  
  TH1F *hist_pip_else_Rapidity = new TH1F("hist_pip_else_Rapidity", "hist_pip_else_Rapidity", 100, -12.0, 12.0);

  TH1F *hist_pi0_else_Rapidity = new TH1F("hist_pi0_else_Rapidity", "hist_pi0_else_Rapidity", 100, -12.0, 12.0);

  TH1F *hist_pim_else_Rapidity = new TH1F("hist_pim_else_Rapidity", "hist_pim_else_Rapidity", 100, -12.0, 12.0);
  
  
  int iTau_n, iTau_p, n, pip_counter_taum, pi0_counter_taum, pim_counter_taum,pip_counter_taup, pi0_counter_taup, pim_counter_taup,pip_counter_else, pi0_counter_else, pim_counter_else;

  Double_t pip_Rapidity, pi0_Rapidity, pim_Rapidity;

  
for(int entry = 0; entry < allEntries; ++entry){
  //for(int entry = 0; entry < 1000; ++entry){                                                    
  treeReader->ReadEntry(entry);
  for(int j = 0; j < branchParticle->GetEntriesFast(); ++j){
    particle = (GenParticle*) branchParticle->At(j);
    if (particle->Status!=1){
      if (particle->PID==15){
	//tau_n = (GenParticle*) branchParticle->At(j);
          iTau_n=j;
          //cout << "Negative tau: " << iTau_n << endl;                                                                                                                                                   
       }
      if (particle->PID==-15){
	//tau_p = (GenParticle*) branchParticle->At(j);
          iTau_p=j;
          //cout << "Positive tau: " << iTau_p << endl;                                                                                                                                                   
       }
      
      pip_counter_taum=0;
      pi0_counter_taum=0;
      pim_counter_taum=0;
      pip_counter_taup=0;
      pi0_counter_taup=0;
      pim_counter_taup=0;
      pip_counter_else=0;
      pi0_counter_else=0;
      pim_counter_else=0;
      //pi0_counter=0;
      //pip_counter=0;
      //pim_counter=0;
      Double_t pi0_Rapidity_lm[5]={-99,-99,-99,-99,-99};
      Double_t pip_Rapidity_lm[5]={-99,-99,-99,-99,-99};
      Double_t pim_Rapidity_lm[5]={-99,-99,-99,-99,-99};
      Double_t pi0_Rapidity_lp[5]={-99,-99,-99,-99,-99};
      Double_t pip_Rapidity_lp[5]={-99,-99,-99,-99,-99};
      Double_t pim_Rapidity_lp[5]={-99,-99,-99,-99,-99};
      for (int i=particle->D1;i<=particle->D2;++i){
	daughter = (GenParticle*) branchParticle->At(i);
	if (daughter->PID==111&&daughter->Status==1){
	  if (daughter->M1 == iTau_n || daughter->M2 == iTau_n){
	    pi0_Rapidity_lm[pi0_counter_taum]=daughter->Rapidity;
	    pi0_counter_taum+=1;
          }else if (daughter->M1 == iTau_p || daughter->M2 == iTau_p){
	    pi0_Rapidity_lp[pi0_counter_taup]=daughter->Rapidity;
	    pi0_counter_taup+=1;
          }else{
	    pi0_counter_else+=1;
	    hist_pi0_else_Rapidity->Fill(daughter->Rapidity);
	  }
	}
	if (daughter->PID==211&&daughter->Status==1){
	  if (daughter->M1 == iTau_n || daughter->M2 == iTau_n){
	    pip_Rapidity_lm[pip_counter_taum]=daughter->Rapidity;
	    pip_counter_taum+=1;
          }else if (daughter->M1 == iTau_p || daughter->M2 == iTau_p){
	    pip_Rapidity_lp[pip_counter_taup]=daughter->Rapidity;
	    pip_counter_taup+=1;
          }else{
	    pip_counter_else+=1;
	    hist_pip_else_Rapidity->Fill(daughter->Rapidity);
	  }
	}
	if (daughter->PID==-211&&daughter->Status==1){
	  if (daughter->M1 == iTau_n || daughter->M2 == iTau_n){
	    pim_Rapidity_lm[pim_counter_taum]=daughter->Rapidity;
	    pim_counter_taum+=1;
          }else if (daughter->M1 == iTau_p || daughter->M2 == iTau_p){
	    pim_Rapidity_lp[pim_counter_taup]=daughter->Rapidity;
	    pim_counter_taup+=1;
          }else{
	    pim_counter_else+=1;
	    hist_pim_else_Rapidity->Fill(daughter->Rapidity);
	  }
	}
      }     
      if (pip_counter_taum==0&&pim_counter_taum==1){
        hist_pim_tau_Rapidity->Fill(pim_Rapidity_lm[0]);
	for (int i=0; i<pi0_counter_taum;++i){
	  hist_pi0_tau_Rapidity->Fill(pi0_Rapidity_lm[i]);
	}
      }
      if (pip_counter_taup==1&&pim_counter_taup==0){
        hist_pip_tau_Rapidity->Fill(pip_Rapidity_lp[0]);
	for (int i=0; i<pi0_counter_taup;++i){
	  hist_pi0_tau_Rapidity->Fill(pi0_Rapidity_lp[i]);
	}
      }
      if (pip_counter_taum==1&&pim_counter_taum==2){
        hist_pim_tau_Rapidity_3->Fill(pim_Rapidity_lm[0]);
	hist_pim_tau_Rapidity_3->Fill(pim_Rapidity_lm[1]);
	hist_pip_tau_Rapidity_3->Fill(pip_Rapidity_lm[0]);
	for (int i=0; i<pi0_counter_taum;++i){
	  hist_pi0_tau_Rapidity_3->Fill(pi0_Rapidity_lm[i]);
	}
      }
      if (pip_counter_taup==2&&pim_counter_taup==1){
        hist_pip_tau_Rapidity_3->Fill(pip_Rapidity_lp[0]);
	hist_pip_tau_Rapidity_3->Fill(pip_Rapidity_lp[1]);
	hist_pim_tau_Rapidity_3->Fill(pim_Rapidity_lp[0]);
	for (int i=0; i<pi0_counter_taup;++i){
	  hist_pi0_tau_Rapidity_3->Fill(pi0_Rapidity_lp[i]);
	}
      }
    }
   }
  }
  cout << "** Exiting..." << endl;
  /*hist_pip_tau_Rapidity->Scale(1/(hist_pip_tau_Rapidity->GetEntries()));
  hist_pi0_tau_Rapidity->Scale(1/(hist_pi0_tau_Rapidity->GetEntries()));
  hist_pim_tau_Rapidity->Scale(1/(hist_pim_tau_Rapidity->GetEntries()));
  hist_pip_tau_Rapidity_3->Scale(1/(hist_pip_tau_Rapidity_3->GetEntries()));
  hist_pi0_tau_Rapidity_3->Scale(1/(hist_pi0_tau_Rapidity_3->GetEntries()));
  hist_pim_tau_Rapidity_3->Scale(1/(hist_pim_tau_Rapidity_3->GetEntries()));
  hist_pip_else_Rapidity->Scale(1/(hist_pip_else_Rapidity->GetEntries()));
  hist_pi0_else_Rapidity->Scale(1/(hist_pi0_else_Rapidity->GetEntries()));
  hist_pim_else_Rapidity->Scale(1/(hist_pim_else_Rapidity->GetEntries()));*/
  outf->Write();
  outf->Close();
  delete treeReader;
  delete chain;
}
