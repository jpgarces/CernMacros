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

void Rapidity_corr(){
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

  TFile *outf = new TFile("Rapidity_corr_bsm.root","RECREATE");

  TH2F *hist = new TH2F("hist","Rapidity Corr.",20,-2.5,2.5,20,-2.5,2.5);

  int lep_dec_count, ch_count_1, ch_count_2, n_1, n_2;

  Double_t lead_PT, lep1_PT, lep2_PT, lead_eta, lep1_eta, lep2_eta, ditau_rap, rap_ch;
    
  Double_t daughter_PID[10];

  TLorentzVector tau1, tau2, ch1_1, ch1_2, ch2_1, ch3_1, ch4_1, ch2_2, ch3_2, ch4_2, ch5_2, ch6_2, ch5_1, ch6_1, vec;

  TLorentzVector vec_arr_1[6] = {ch1_1, ch2_1, ch3_1, ch4_1, ch5_1, ch6_1};

  TLorentzVector vec_arr_2[6] = {ch2_1, ch2_2, ch3_2, ch4_2, ch5_2, ch6_2};
  
for(int entry = 0; entry < allEntries; ++entry){
  //for(int entry = 0; entry < 5000; ++entry){
   treeReader->ReadEntry(entry);
   for(int j = 0; j < branchParticle->GetEntriesFast(); ++j){
     particle = (GenParticle*) branchParticle->At(j);
      if (particle->PID==-15){
	iTau_p=j;
	tau_p=(GenParticle*) branchParticle->At(j);
	tau1.SetPxPyPzE(tau_p->Px,tau_p->Py,tau_p->Pz,tau_p->E);
      }
      if (particle->PID==15){
	iTau_n=j;
	tau_n=(GenParticle*) branchParticle->At(j);
	tau2.SetPxPyPzE(tau_n->Px,tau_n->Py,tau_n->Pz,tau_n->E);
      }
    }
   ditau_rap=(tau1 + tau2).Rapidity();
   lep_dec_count=0;
   lep1_PT=0;
   lep2_PT=0;
   ch_count_1=0;
   ch_count_2=0;
   n_1=0;
   n_2=0;
    for (int i=tau_n->D1; i<= tau_n->D2; ++i){
       daughter = (GenParticle*) branchParticle->At(i);
       if (daughter->M1 == iTau_n || daughter->M2 == iTau_n){
	 if (daughter->PID==11&&daughter->Status==1){
	    lep_dec_count+=1;
	    lep2_PT=daughter->PT;
	    lep2_eta=daughter->Eta;
	    ch1_2.SetPxPyPzE(daughter->Px,daughter->Py,daughter->Pz,daughter->E);
	    ch_count_2+=1;
	    vec_arr_2[n_2].SetPxPyPzE(daughter->Px,daughter->Py,daughter->Pz,daughter->E);
	    n_2+=1;
         }
	 if (daughter->PID==13&&daughter->Status==1){
	    lep_dec_count+=1;
	    lep2_PT=daughter->PT;
	    lep2_eta=daughter->Eta;
	    ch1_2.SetPxPyPzE(daughter->Px,daughter->Py,daughter->Pz,daughter->E);
	    ch_count_2+=1;
	    vec_arr_2[n_2].SetPxPyPzE(daughter->Px,daughter->Py,daughter->Pz,daughter->E);
	    n_2+=1;
         }
	 if ((daughter->PID==211||daughter->PID==-211)&&daughter->Status==1){
	    ch_count_2+=1;
	    vec_arr_2[n_2].SetPxPyPzE(daughter->Px,daughter->Py,daughter->Pz,daughter->E);
	    n_2+=1;
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
	    ch1_1.SetPxPyPzE(daughter->Px,daughter->Py,daughter->Pz,daughter->E);
	    ch_count_1+=1;
	    vec_arr_1[n_1].SetPxPyPzE(daughter->Px,daughter->Py,daughter->Pz,daughter->E);
	    n_1+=1;
         }
	 if (daughter->PID==-13&&daughter->Status==1){
	    lep_dec_count+=1;
	    lep1_PT=daughter->PT;
	    lep1_eta=daughter->Eta;
	    ch1_1.SetPxPyPzE(daughter->Px,daughter->Py,daughter->Pz,daughter->E);
	    ch_count_1+=1;
	    vec_arr_1[n_1].SetPxPyPzE(daughter->Px,daughter->Py,daughter->Pz,daughter->E);
	    n_1+=1;
         }
	 if ((daughter->PID==211||daughter->PID==-211)&&daughter->Status==1){
	    ch_count_1+=1;
	    vec_arr_1[n_1].SetPxPyPzE(daughter->Px,daughter->Py,daughter->Pz,daughter->E);
	    n_1+=1;
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
    if (lep_dec_count>=1&&lead_PT>4.0&&TMath::Abs(lead_eta)<=2.5){
      vec.SetPxPyPzE(0,0,0,0);
      for(int i=0; i<n_1; ++i){
	vec+=vec_arr_1[i];
      }
      for(int i=0; i<n_2; ++i){
	vec+=vec_arr_2[i];
      }
      rap_ch=vec.Rapidity();
      hist->Fill(ditau_rap,rap_ch);
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
