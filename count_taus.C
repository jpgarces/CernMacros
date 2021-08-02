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

void count_taus(){
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");

  //FILE *f = fopen("test1.txt","w");
  
  TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *tau, *tau_n, *tau_p, *daughter;

  int iTau_p, iTau_n, muon_count=0, it, mom_id;

  
  int phtau_count=0, rmntau_count=0, tau_count=0;
  
  
  for(int entry = 0; entry < allEntries; ++entry){
    //if (entry>100) break;
    treeReader->ReadEntry(entry);
    for(int j = 0; j < branchParticle->GetEntriesFast(); ++j){                                   
      particle = (GenParticle*) branchParticle->At(j);
      if (particle->PID==15){
          tau_n = (GenParticle*) branchParticle->At(j);
	  iTau_n=j;
      }
      /*if (particle->PID==-15){
          tau_p = (GenParticle*) branchParticle->At(j);
	  iTau_p=j;
	  }*/
     }
       tau_count+=1;
       it=0;
       //cout << "------------ New Decay -----------------"<< endl;
       while (it<100){
	 if(tau_n->M1==-1&&tau_n->M2==-1){
	   //cout<<"PID: "<<tau_n->PID<<", M1: "<<tau_n->M1<<", M2: "<<tau_n->M2<< ", D2: " << tau_n->D2<<endl;
	   break;
	 }
          GenParticle *mom = (GenParticle*) branchParticle->At(tau_n->M1);
	  mom_id=tau_n->M1;
	  //cout<<"PID: "<<tau_n->PID<<", M1: "<<tau_n->M1<<", M2: "<<tau_n->M2<< ", D1:" << tau_n->D1 << ", D2: " << tau_n->D2 << endl;
          tau_n = (GenParticle*) branchParticle->At(mom_id);
	  if (mom->PID!=15){
	    if (mom->PID=22){
	      phtau_count+=1;
	      break;
	    }else{
	      rmntau_count+=1;
	      break;
	    }
	  }
	  it+=1;
        }
      }
      cout << "Total number of taus: "<< tau_count << endl;
      cout << "Number of taus from photons: "<< phtau_count << endl;
      cout << "Number of taus from remnants (not photons): "<< rmntau_count << endl;
  delete treeReader;
  delete chain;
  //fclose(f);
}
