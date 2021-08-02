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

void tau_PT_pions_1ch(){
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");
  
  TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *daughter, *tau_p, *tau_n, *pi0daughter1, *pi0daughter2;

  int iTau_p, iTau_n;

  TFile *outf = new TFile("tau_PT_pions_1ch.root","RECREATE");

  TH1F *hist_tau_PT_1ch = new TH1F("hist_tau_PT_1ch","Tau PT",100,0.0,40.0);
  TH1F *hist_tau_PT_1ch10 = new TH1F("hist_tau_PT_1ch10","Tau PT",100,0.0,40.0);
  TH1F *hist_tau_PT_1ch20 = new TH1F("hist_tau_PT_1ch20","Tau PT",100,0.0,40.0);

  TH1F *hist_nut_PT_1ch = new TH1F("hist_nut_PT_1ch","Tau neutrino PT",100,0.0,40.0);
  TH1F *hist_nut_PT_1ch10 = new TH1F("hist_nut_PT_1ch10","Tau neutrino PT",100,0.0,40.0);
  TH1F *hist_nut_PT_1ch20 = new TH1F("hist_nut_PT_1ch20","Tau neutrino PT",100,0.0,40.0);
  
  TH1F *hist_ph_PT_1ch10 = new TH1F("hist_ph_PT_1ch10","Photon PT",100,0.0,40.0);
  TH1F *hist_ph_PT_1ch20 = new TH1F("hist_ph_PT_1ch20","Photon PT",100,0.0,40.0);

  TH1F *hist_pim_PT_1ch = new TH1F("hist_pim_PT_1ch","Negative pion PT",100,0.0,40.0);
  TH1F *hist_pim_PT_1ch10 = new TH1F("hist_pim_PT_1ch10","Negative pion PT",100,0.0,40.0);
  TH1F *hist_pim_PT_1ch20 = new TH1F("hist_pim_PT_1ch20","Negative pion PT",100,0.0,40.0);

  int pim_count, pi0_count, ph_count, nut_count, n;

  Double_t PT, pim_PT, ph1_PT, ph2_PT, nut_PT;

  Double_t ph_PT_arr[6];
    
  
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
   pim_count=0;
   pi0_count=0;
   nut_count=0;
   ph_count=0;
   n=0;
   for(int t=0;t<6;++t){
     ph_PT_arr[t]=0;
   }
    for (int i=tau_n->D1; i<= tau_n->D2; ++i){
       daughter = (GenParticle*) branchParticle->At(i);
       if (daughter->M1 == iTau_n || daughter->M2 == iTau_n){
	 if (daughter->PID==-211&&daughter->Status==1){
	    pim_count+=1;
	    pim_PT=daughter->PT;
         }
	 if (daughter->PID==111){
	    pi0_count+=1;
	    pi0daughter1 = (GenParticle*) branchParticle->At(daughter->D1);
	    pi0daughter2 = (GenParticle*) branchParticle->At(daughter->D2);
	    if(pi0daughter1->PID==22&&pi0daughter2->PID==22){
	      ph_count+=2;
	      ph_PT_arr[n]=pi0daughter1->PT;
	      ph_PT_arr[n+1]=pi0daughter1->PT;
	      n+=2;
	    }
         }
	 if (daughter->PID==16&&daughter->Status==1){
	    nut_count+=1;
	    nut_PT=daughter->PT;
         }
       }
     }
     if (pim_count==1&&pi0_count==0&&ph_count==0&&nut_count==1){
        hist_tau_PT_1ch->Fill(tau_n->PT);
        hist_pim_PT_1ch->Fill(pim_PT);
	hist_nut_PT_1ch->Fill(nut_PT);
     }
     if (pim_count==1&&pi0_count==1&&ph_count==2&&nut_count==1){
        hist_tau_PT_1ch10->Fill(tau_n->PT);
        hist_pim_PT_1ch10->Fill(pim_PT);
	hist_nut_PT_1ch10->Fill(nut_PT);
	hist_ph_PT_1ch10->Fill(ph_PT_arr[0]);
	hist_ph_PT_1ch10->Fill(ph_PT_arr[1]);
     }
     if (pim_count==1&&pi0_count==2&&ph_count==4&&nut_count==1){
        hist_tau_PT_1ch20->Fill(tau_n->PT);
        hist_pim_PT_1ch20->Fill(pim_PT);
	hist_nut_PT_1ch20->Fill(nut_PT);
	hist_ph_PT_1ch20->Fill(ph_PT_arr[0]);
	hist_ph_PT_1ch20->Fill(ph_PT_arr[1]);
	hist_ph_PT_1ch20->Fill(ph_PT_arr[2]);
	hist_ph_PT_1ch20->Fill(ph_PT_arr[3]);
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
