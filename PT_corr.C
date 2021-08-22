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

void PT_corr(){
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");
  
  //TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events_NNL.root";
  
  TString inputFile = "/home/juan/sm_UFO_minv0p_pt1_NNLO_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *daughter, *tau_p,*tau_n;

  int iTau_p, iTau_n;

  TFile *outf = new TFile("PT_corr_bsm.root","RECREATE");

  TH2F *hist = new TH2F("hist","Tau P_{T} vs e^{-}/mu^{-} P_{T}",20,0.0,20.0,20,0.0,20.0);

  int lep_dec_count, n;

  Double_t lead_PT, lep1_PT, lep2_PT, tau1_PT, tau2_PT, lead_eta, lep1_eta, lep2_eta, tau_PT;
    
  Double_t daughter_PID[10];
  
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
   tau1_PT=tau_p->PT;
   tau2_PT=tau_n->PT;
   lep_dec_count=0;
   lep1_PT=0;
   lep2_PT=0;
    for (int i=tau_n->D1; i<= tau_n->D2; ++i){
       daughter = (GenParticle*) branchParticle->At(i);
       if (daughter->M1 == iTau_n || daughter->M2 == iTau_n){
	 if (daughter->PID==11&&daughter->Status==1){
	    lep_dec_count+=1;
	    lep2_PT=daughter->PT;
	    lep2_eta=daughter->Eta;
         }
	 if (daughter->PID==13&&daughter->Status==1){
	    lep_dec_count+=1;
	    lep2_PT=daughter->PT;
	    lep2_eta=daughter->Eta;
         }
       }
     }
    for (int i=tau_p->D1; i<= tau_p->D2; ++i){
       daughter = (GenParticle*) branchParticle->At(i);
       if (daughter->M1 == iTau_p || daughter->M2 == iTau_p){
	 if (daughter->PID==-11&&daughter->Status==1){
	    lep_dec_count+=1;
	    lep1_PT=daughter->PT;
	    lep1_eta=daughter->Eta;
         }
	 if (daughter->PID==-13&&daughter->Status==1){
	    lep_dec_count+=1;
	    lep1_PT=daughter->PT;
	    lep1_eta=daughter->Eta;
         }
       }
     }
    if (lep1_PT>lep2_PT){
      lead_PT=lep1_PT;
      lead_eta=lep1_eta;
      tau_PT=tau1_PT;
    }
    if (lep1_PT<lep2_PT){
      lead_PT=lep2_PT;
      lead_eta=lep2_eta;
      tau_PT=tau2_PT;
    }
    if (lep_dec_count>=1&&lead_PT>4.0&&TMath::Abs(lead_eta)<=2.5){
      hist->Fill(tau_PT,lead_PT);
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
