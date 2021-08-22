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

void taus_PT_rapidity(){
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");
  
  TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events_NNL.root";
  
  //TString inputFile = "/home/juan/sm_UFO_minv0p_pt1_NNLO_delphes_events.root";

  //TString inputFile = "/home/juan/sm_bkg_minv0p_pt1_NNLO_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle,*tau_p, *tau_n;

  int iTau_p, iTau_n;

  TFile *outf = new TFile("taus_PT_Rapidity_sm.root","RECREATE");

  TH2F *hist_taus_PT = new TH2F("hist_taus_PT","Lead vs Next-lead Tau P_{T}",150,0.0,15.0,150,0.0,15.0);
  TH2F *hist_taus_rapidity = new TH2F("hist_taus_rapidity","Lead vs Next-lead Tau Rapidity",150,-6.0,6.0,150,-6.0,6.0);
  
  Double_t tau_PT, tau_rapidity;
    
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
   if(tau_p->PT>tau_n->PT){
    hist_taus_PT->Fill(tau_p->PT,tau_n->PT);
    hist_taus_rapidity->Fill(tau_p->Rapidity,tau_n->Rapidity);
   }else{
     hist_taus_PT->Fill(tau_n->PT,tau_p->PT);
     hist_taus_rapidity->Fill(tau_n->Rapidity,tau_p->Rapidity);
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
