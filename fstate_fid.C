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


void fstate_fid(){
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");

  //TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events_old.root";
  
  TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events_NNL.root";
  
  //TString inputFile = "/home/juan/sm_UFO_minv0p_pt1_NNLO_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *daughter, *tau_n, *tau_p;

  TFile *outf = new TFile("fid_PT_sm.root","RECREATE");

  TH1F *hist_lep_PT_fid = new TH1F("hist_lep_PT_fid", "hist_lep_PT_fid", 100, 0.0, 100.0);

  TH1F *hist_pi_PT_fid = new TH1F("hist_pi_PT_fid", "hist_pi_PT_fid", 100, 0.0, 100.0);

  TH1F *hist_3pi_PT_fid = new TH1F("hist_3pi_PT_fid", "hist_3pi_PT_fid", 100, 0.0, 100.0);

  TH1F *hist_sum_PT_fid = new TH1F("hist_sum_PT_fid", "hist_sum_PT_fid", 100, 0.0, 100.0);
  
  int iTau_n, iTau_p, lep_count, pi_count;

  Double_t  lep1_PT, lep1_eta, lep2_PT, lep2_eta, lead_PT, lead_eta;
  
  for(int entry = 0; entry < allEntries; ++entry){
    //for(int entry = 0; entry < 1000; ++entry){             
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
    lep_count=0;
    pi_count=0;
    lep1_PT=0;
    lep2_PT=0;
    for (int i=tau_n->D1; i<= tau_n->D2; ++i){
       daughter = (GenParticle*) branchParticle->At(i);
       if (daughter->M1 == iTau_n || daughter->M2 == iTau_n){
	 if ((daughter->PID==11||daughter->PID==13)&&daughter->Status==1){
	    lep2_PT=daughter->PT;
	    lep2_eta=daughter->Eta;
	    lep_count+=1;
         }
	 if ((daughter->PID==211||daughter->PID==-211)&&daughter->Status==1){
	    pi_count+=1;
         }
       }
     }
    for (int i=tau_p->D1; i<= tau_p->D2; ++i){
       daughter = (GenParticle*) branchParticle->At(i);
       if (daughter->M1 == iTau_p || daughter->M2 == iTau_p){
	 if ((daughter->PID==-11||daughter->PID==-13)&&daughter->Status==1){
	    lep1_PT=daughter->PT;
	    lep1_eta=daughter->Eta;
	    lep_count+=1;
         }
	 if ((daughter->PID==211||daughter->PID==-211)&&daughter->Status==1){
	    pi_count+=1;
         }
       }
     }
    if (lep1_PT>lep2_PT){
      lead_PT=lep1_PT;
      lead_eta=lep1_eta;
    }
    if (lep1_PT<lep2_PT){
      lead_PT=lep2_PT;
      lead_eta=lep2_eta;
    }
    if (lep_count==1&&pi_count==1&&lead_PT>4.0&&TMath::Abs(lead_eta)<=2.5){
      hist_pi_PT_fid->Fill(lead_PT);
      hist_sum_PT_fid->Fill(lead_PT);
    }
    if (lep_count==2&&pi_count==0&&lead_PT>4.0&&TMath::Abs(lead_eta)<=2.5){
      hist_lep_PT_fid->Fill(lead_PT);
      hist_sum_PT_fid->Fill(lead_PT);
    }
    if (lep_count==1&&pi_count==3&&lead_PT>4.0&&TMath::Abs(lead_eta)<=2.5){
      hist_3pi_PT_fid->Fill(lead_PT);
      hist_sum_PT_fid->Fill(lead_PT);
    }
  }
  cout << "** Exiting..." << endl;
  /*hist_e_PT->Scale(1/(hist_e_PT->GetEntries()));
  hist_e_tau_PT->Scale(1/(hist_e_tau_PT->GetEntries()));
  hist_e_else_PT->Scale(1/(hist_e_else_PT->GetEntries()));
  hist_ep_tau_PT->Scale(1/(hist_ep_tau_PT->GetEntries()));
  hist_ep_else_PT->Scale(1/(hist_ep_else_PT->GetEntries()));*/
  outf->Write();
  outf->Close();
  delete treeReader;
  delete chain;
}
