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

void tau_energy_lep(){
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");
  
  TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *daughter, *tau_p,*tau_n;

  int iTau_p, iTau_n;

  TFile *outf = new TFile("tau_energy_e.root","RECREATE");

  TH1F *hist_tau_energy = new TH1F("hist_tau_energy","Tau energy",100,0.0,60.0);
  TH1F *hist_e_energy = new TH1F("hist_e_energy","Electron energy",100,0.0,60.0);
  TH1F *hist_anue_energy = new TH1F("hist_anue_energy","Anti electron neutrino energy",100,0.0,60.0);
  TH1F *hist_nut_energy = new TH1F("hist_nut_energy","Tau neutrino energy",100,0.0,60.0);

  int e_count, anue_count, nut_count, n;

  Double_t energy, e_energy, anue_energy, nut_energy;
    
  Double_t daughter_energy[10];
  
for(int entry = 0; entry < allEntries; ++entry){
  //for(int entry = 0; entry < 5000; ++entry){
   treeReader->ReadEntry(entry);
   for(int j = 0; j < branchParticle->GetEntriesFast(); ++j){
     particle = (GenParticle*) branchParticle->At(j);
      if (particle->PID==-15){
	iTau_p=j;
	tau_p=(GenParticle*) branchParticle->At(j);
      }
      if (particle->PID==15){
	iTau_n=j;
	tau_n=(GenParticle*) branchParticle->At(j);
      }
    }
   e_count=0;
   anue_count=0;
   nut_count=0;
    for (int i=tau_n->D1; i<= tau_n->D2; ++i){
       daughter = (GenParticle*) branchParticle->At(i);
       if (daughter->M1 == iTau_n || daughter->M2 == iTau_n){
	 if (daughter->PID==11&&daughter->Status==1){
	    e_count+=1;
	    e_energy=daughter->E;
         }
	 if (daughter->PID==-12&&daughter->Status==1){
	    anue_count+=1;
	    anue_energy=daughter->E;
         }
	 if (daughter->PID==16&&daughter->Status==1){
	    nut_count+=1;
	    nut_energy=daughter->E;
         }
       }
     }
    /*for (int i=tau_p->D1; i<= tau_p->D2; ++i){
       daughter = (GenParticle*) branchParticle->At(i);
       if (daughter->M1 == iTau_p || daughter->M2 == iTau_p){
	 if (daughter->PID==-11&&daughter->Status==1){
	    ep_count+=1;
         }
	 if (daughter->PID==-13&&daughter->Status==1){
	    mup_count+=1;
         }
	 if (daughter->PID==12&&daughter->Status==1){
	    nue_count+=1;
         }
	 if (daughter->PID==14&&daughter->Status==1){
	    numu_count+=1;
         }
	 if (daughter->PID==-16&&daughter->Status==1){
	    anut_count+=1;
         }
	 if ((daughter->PID==-11 || daughter->PID==12 || daughter->PID==-16 || daughter->PID==-13 || daughter->PID==14)&&daughter->Status==1){
	    daughter_energy[n]=daughter->E;
            n+=1;
         }
       }
       }*/
     if (e_count==1&&anue_count==1&&nut_count==1){
        hist_tau_energy->Fill(tau_n->E);
        hist_e_energy->Fill(e_energy);
	hist_anue_energy->Fill(anue_energy);
	hist_nut_energy->Fill(nut_energy);
     }
  }
  /*hist_taup_ep->Scale(1/(hist_taup_ep->GetEntries()));
  hist_taup_mup->Scale(1/(hist_taup_mup->GetEntries()));
  hist_taum_e->Scale(1/(hist_taum_e->GetEntries()));
  hist_taum_mu->Scale(1/(hist_taum_mu->GetEntries()));*/
  cout << "** Exiting..." << endl;
  outf->Write();
  outf->Close();
  delete treeReader;
  delete chain;
}
