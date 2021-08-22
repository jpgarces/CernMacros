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

void count_gen_tracks(Int_t pid){
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
  TClonesArray *branchTrack = treeReader->UseBranch("Track");

  GenParticle *particle;

  Track *trk;

  //TFile *outf = new TFile("gen_vs_track_e_bsm.root","RECREATE");
  
  Double_t count_e, count_e_trk;

  TH1F *hist_gen_trk = new TH1F("hist_gen_trk","Gen vs. Tracks",100,0.0,2.0);

  Int_t count_eq=0, count_gen_g=0, count_trk_g=0;
  
  
  for(int entry = 0; entry < allEntries; ++entry){
    //if (entry>100) break;
    treeReader->ReadEntry(entry);
    count_e=0;
    for(int j = 0; j < branchParticle->GetEntriesFast(); ++j){                                   
      particle = (GenParticle*) branchParticle->At(j);
      if (particle->PID==pid&&TMath::Abs(particle->Eta)<2.5&&particle->PT>0.1){
	count_e+=1;
      }
    }
    count_e_trk=0;
    for(int i = 0; i < branchTrack->GetEntriesFast(); ++i){                                   
      trk = (Track*) branchTrack->At(i);
      if (trk->PID==pid){
	count_e_trk+=1;
      }
    }
    //cout << "Tracks: " << count_e_trk << " , Gen: " << count_e << endl;
    hist_gen_trk->Fill(count_e_trk/count_e);
    if(count_e_trk>count_e){
      cout << "Tracks: " << count_e_trk << " , Gen: " << count_e << endl;
      count_trk_g+=1;
    }else if(count_e_trk==count_e){
      count_eq+=1;
    }else{
      count_gen_g+=1;
    }
  }

  //outf->Write();
  //outf->Close();
  cout << "------------------- " << pid << " -------------------------" << endl;
  cout << "Number of events with greater number of generated particles than tracks: " << count_gen_g << endl;
  cout << "Number of events with equal number generated particles and tracks: " << count_eq << endl;
  cout << "Number of events with morelower number of generated particles than tracks: " << count_trk_g << endl;
  delete treeReader;
  delete chain;
}
