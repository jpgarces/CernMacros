// run it in /root/Delphes-3.4.2 as root -l -q examples/gg2taus.C 

// To Do: include second tau

#ifdef __CLING__
R__LOAD_LIBRARY(/root/Delphes-3.4.2/libDelphes.so)

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
#include "TH1.h"                                 // for histrograming                                
#include "TH2D.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TVirtualPad.h"
#include "TApplication.h"
#include "TBranch.h"
#include "TBranchElement.h"
#include "TFile.h"                     // ROOT, for saving file.                                     
#include  <map>
#include "TTree.h"                     //for Tree file                                               
#include "TROOT.h"

void tau2pions_kin_fstate(){
  gSystem->Load("/root/MG5_aMC_v2_7_3/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");
  
  TString inputFile = "/root/bsm_minv0p_pt1_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *daughter, *daughter_2, *tau_p,*tau_n;

  int iTau_p, iTau_n;

  TFile *outf = new TFile("tau_kin_pions_Eta.root","RECREATE");

  TH1F *taup_1ch10_2ph_ph_eta = new TH1F("taup_1ch10_2ph_ph_pt","Positive tau decay into 1 pi+ and 1 pi0 -> 2 photons",250,-12.0,12.0);

  TH1F *taup_1ch10_epeph_ph_eta = new TH1F("taup_1ch10_epeph_ph_eta","Positive tau decay into 1 pi+ and 1 pi0 -> e+ e- photon",250,-12.0,12.0); 

  TH1F *taun_1ch10_2ph_ph_eta = new TH1F("taun_1ch10_2ph_ph_eta","Negative tau decay into 1 pi- and 1 pi0 -> 2 photons",250,-12.0,12.0);

  TH1F *taun_1ch10_epeph_ph_eta = new TH1F("taun_1ch10_epeph_ph_eta","Negative tau decay into 1 pi- and 1 pi0 -> e+ e- photon",250,-12.0,12.0); 

  TH1F *taun_1ch10_epeph_e_eta = new TH1F("taun_1ch10_epeph_e_eta","Negative tau decay into 1 pi- and 1 pi0 -> 2 photons",250,-12.0,12.0);

  TH1F *taup_1ch10_epeph_e_eta = new TH1F("taup_1ch10_epeph_e_eta","Negative tau decay into 1 pi- and 1 pi0 -> e+ e- photon",250,-12.0,12.0); 

  TH1F *taun_1ch10_epeph_ep_eta = new TH1F("taun_1ch10_epeph_ep_eta","Negative tau decay into 1 pi- and 1 pi0 -> 2 photons",250,-12.0,12.0);

  TH1F *taup_1ch10_epeph_ep_eta = new TH1F("taup_1ch10_epeph_ep_eta","Negative tau decay into 1 pi- and 1 pi0 -> e+ e- photon",250,-12.0,12.0); 
  
  TH1F *hist_ph_all = new TH1F("hist_ph_all","Negative tau decay into 1 pi- and 1 pi0 -> e+ e- photon",250,-12.0,12.0);

  TH1F *hist_e_all = new TH1F("hist_e_all","Negative tau decay into 1 pi- and 1 pi0 -> e+ e- photon",250,-12.0,12.0); 

  TH1F *hist_ep_all = new TH1F("hist_ep_all","Negative tau decay into 1 pi- and 1 pi0 -> e+ e- photon",250,-12.0,12.0);
  
  int pip_count, pim_count, pi0_count, n, nut_count, e_count, ep_count, ph_count, n_ph, n_e, n_ep;

  Double_t ph_l[10];
  Double_t e_l[10];
  Double_t ep_l[10];
  
for(int entry = 0; entry < allEntries; ++entry){
  //for(int entry = 0; entry < 1000; ++entry){
  treeReader->ReadEntry(entry);
  for(int j = 0; j < branchParticle->GetEntriesFast(); ++j){
    particle = (GenParticle*) branchParticle->At(j);
    if (particle->PID==22) hist_ph_all->Fill(particle->Eta);
    if (particle->PID==11) hist_e_all->Fill(particle->Eta);
    if (particle->PID==-11) hist_ep_all->Fill(particle->Eta);
    if (particle->Status!=1){
      if (particle->PID==-15){
	iTau_p=j;
	tau_p=(GenParticle*) branchParticle->At(j);
      }
      if (particle->PID==15){
	iTau_n=j;
	tau_n=(GenParticle*) branchParticle->At(j);
      }
    }
   }
  //cout << "Out of Tau loop" << endl;
	pip_count=0;
	pim_count=0;
	pi0_count=0;
	nut_count=0;
	e_count=0;
	ep_count=0;
	ph_count=0;
	n_ph=0;
	n_e=0;
	n_ep=0;
	for (int t=1; t<10; ++t){
	  ph_l[t]=0;
	  e_l[t]=0;
	  ep_l[t]=0;
	}
	for (int i=tau_p->D1; i<= tau_p->D2; ++i){
          daughter = (GenParticle*) branchParticle->At(i);
	  if (daughter->M1 == iTau_p || daughter->M2 == iTau_p){
	    if (daughter->PID==211){
	      pip_count+=1;
	    }
            if (daughter->PID==111){
	      pi0_count+=1;
	      for (int c=daughter->D1; c<=daughter->D2; ++c){
	        daughter_2=(GenParticle*)branchParticle->At(c);
		if (daughter_2->PID==22 || daughter_2->PID==11 || daughter_2->PID==-11){
		  if (daughter_2->PID==22){
		    ph_count+=1;
		    ph_l[n_ph]=daughter_2->Eta;
		    n_ph+=1;
		  }
		  if (daughter_2->PID==11){
		    e_count+=1;
		    e_l[n_e]=daughter_2->Eta;
		    n_e+=1;
		  }
		  if (daughter_2->PID==-11){
		    ep_count+=1;
		    ep_l[n_ep]=daughter_2->Eta;
		    n_ep+=1;
		  }
		}
	      }
	    }
            if (daughter->PID==-211){
	      pim_count+=1;
	    }
	    if (daughter->PID==-16){
	      nut_count+=1;
	    }
          }
	}
	//cout << "n: " << n << endl;
	if (pim_count==0&&pip_count==1&&nut_count==1&&ph_count==2&&pi0_count==1){
	  taup_1ch10_2ph_ph_eta->Fill(ph_l[0]);
	  taup_1ch10_2ph_ph_eta->Fill(ph_l[1]);
	}else if(pim_count==0&&pip_count==1&&nut_count==1&&e_count==1&&ep_count==1&&ph_count==1&&pi0_count==1&&pi0_count==1){
	  taup_1ch10_epeph_ph_eta->Fill(ph_l[0]);
	  taup_1ch10_epeph_e_eta->Fill(e_l[0]);
	  taup_1ch10_epeph_ep_eta->Fill(ep_l[0]);
	}
	//cout << "Filled Tau_p hists" << endl;
	pip_count=0;
	pim_count=0;
	pi0_count=0;
	nut_count=0;
	e_count=0;
	ep_count=0;
	ph_count=0;
	n_ph=0;
	n_e=0;
	n_ep=0;
	for (int t=1; t<10; ++t){
          ph_l[t]=0;
          e_l[t]=0;
          ep_l[t]=0;
	}
	for (int i=tau_n->D1; i<= tau_n->D2; ++i){
          daughter = (GenParticle*) branchParticle->At(i);
	  if (daughter->M1 == iTau_n || daughter->M2 == iTau_n){
	    if (daughter->PID==211){
	      pip_count+=1;
	    }
            if (daughter->PID==111){
	      pi0_count+=1;
	      for (int c=daughter->D1; c<=daughter->D2; ++c){
	        daughter_2=(GenParticle*) branchParticle->At(c);
		if (daughter_2->PID==22 || daughter_2->PID==11 || daughter_2->PID==-11){
		  if (daughter_2->PID==22){
		    ph_count+=1;
		    ph_l[n_ph]=daughter_2->Eta;
		    n_ph+=1;
		  }
		  if (daughter_2->PID==11){
		    e_count+=1;
		    e_l[n_e]=daughter_2->Eta;
		    n_e+=1;
		  }
	 	  if (daughter_2->PID==-11){
		    ep_count+=1;
		    ep_l[n_ep]=daughter_2->Eta;
		    n_ep+=1;
		  }
		}
	      }
	    }
            if (daughter->PID==-211){
	      pim_count+=1;
	    }
	    if (daughter->PID==16){
	      nut_count+=1;
	    }
          }
	}
	//cout << "Pi minus: " << pim_count << "; Pi plus: " << pip_count << "; Nu tau: " << nut_count << "; Photons: " << ph_count << "; Pi zero: " << pi0_count << endl;
	if (pim_count==1&&pip_count==0&&nut_count==1&&ph_count==2&&pi0_count==1){
	  taun_1ch10_2ph_ph_eta->Fill(ph_l[0]);
	  taun_1ch10_2ph_ph_eta->Fill(ph_l[1]);
	}else if(pim_count==1&&pip_count==0&&nut_count==1&&e_count==1&&ep_count==1&&ph_count==1&&pi0_count==1){
	  taun_1ch10_epeph_ph_eta->Fill(ph_l[0]);
	  taun_1ch10_epeph_e_eta->Fill(e_l[0]);
	  taun_1ch10_epeph_ep_eta->Fill(ep_l[0]);
	}
	//cout << "Filled Tau_n hists" << endl;
  }
  //cout << "Normalizing hists" << endl; 
  taun_1ch10_2ph_ph_eta->Scale(1/(taun_1ch10_2ph_ph_eta->GetEntries()));
  taun_1ch10_epeph_ph_eta->Scale(1/(taun_1ch10_epeph_ph_eta->GetEntries()));
  taup_1ch10_2ph_ph_eta->Scale(1/(taup_1ch10_2ph_ph_eta->GetEntries()));
  taup_1ch10_epeph_ph_eta->Scale(1/(taup_1ch10_epeph_ph_eta->GetEntries()));
  taup_1ch10_epeph_e_eta->Scale(1/(taup_1ch10_epeph_e_eta->GetEntries()));
  taup_1ch10_epeph_ep_eta->Scale(1/(taup_1ch10_epeph_ep_eta->GetEntries()));
  taun_1ch10_epeph_e_eta->Scale(1/(taun_1ch10_epeph_e_eta->GetEntries()));
  taun_1ch10_epeph_ep_eta->Scale(1/(taun_1ch10_epeph_ep_eta->GetEntries()));
  hist_ph_all->Scale(1/(hist_ph_all->GetEntries()));
  hist_e_all->Scale(1/(hist_e_all->GetEntries()));
  hist_ep_all->Scale(1/(hist_ep_all->GetEntries()));
  cout << "** Exiting..." << endl;
  outf->Write();
  outf->Close();
  delete treeReader;
  delete chain;
}
