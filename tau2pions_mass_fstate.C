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

void tau2pions_mass_fstate(){
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

  TFile *outf = new TFile("tau_mass_pions_fstate.root","RECREATE");

  TH1F *hist_taup_1ch10_2ph = new TH1F("hist_taup_1ch10_2ph","Positive tau decay into 1 pi+ and 1 pi0 -> 2 photons",500,1.7767,1.7773);

  TH1F *hist_taup_1ch10_epeph = new TH1F("hist_taup_1ch10_epeph","Positive tau decay into 1 pi+ and 1 pi0 -> e+ e- photon",500,1.7767,1.7773); 

  TH1F *hist_taun_1ch10_2ph = new TH1F("hist_taun_1ch10_2ph","Negative tau decay into 1 pi- and 1 pi0 -> 2 photons",500,1.7767,1.7773);

  TH1F *hist_taun_1ch10_epeph = new TH1F("hist_taun_1ch10_epeph","Negative tau decay into 1 pi- and 1 pi0 -> e+ e- photon",500,1.7767,1.7773); 

  
  int pip_count, pim_count, pi0_count, n, nut_count, e_count, ep_count, ph_count;

  Double_t m,e,px,py,pz;

  Double_t daughter_e[10];
  Double_t daughter_px[10];
  Double_t daughter_py[10];
  Double_t daughter_pz[10];
	
  
for(int entry = 0; entry < allEntries; ++entry){
  //for(int entry = 0; entry < 1000; ++entry){
  treeReader->ReadEntry(entry);
  for(int j = 0; j < branchParticle->GetEntriesFast(); ++j){
    particle = (GenParticle*) branchParticle->At(j);
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
	for (int t=0;t<10;++t){
	  daughter_e[t]=0;
	  daughter_px[t]=0;
	  daughter_py[t]=0;
	  daughter_pz[t]=0;
	}
	n=0;
	for (int i=tau_p->D1; i<= tau_p->D2; ++i){
          daughter = (GenParticle*) branchParticle->At(i);
	  if (daughter->M1 == iTau_p || daughter->M2 == iTau_p){
	    if (daughter->PID==211 || daughter->PID==-211 || daughter->PID==-16){
	      daughter_e[n]=daughter->E;
              daughter_px[n]=daughter->Px;
              daughter_py[n]=daughter->Py;
              daughter_pz[n]=daughter->Pz;
              n+=1;
	    }
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
		  }
		  if (daughter_2->PID==11){
		    e_count+=1;
		  }
		  if (daughter_2->PID==-11){
		    ep_count+=1;
		  }
		  daughter_e[n]=daughter_2->E;
                  daughter_px[n]=daughter_2->Px;
                  daughter_py[n]=daughter_2->Py;
                  daughter_pz[n]=daughter_2->Pz;
		  n+=1;
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
	e=0;px=0;py=0;pz=0;
        for (int l=0;l<10;++l){
            e+=daughter_e[l];
	    px+=daughter_px[l];
            py+=daughter_py[l];
	    pz+=daughter_pz[l];
	}
	m = TMath::Sqrt(TMath::Power(e,2)-(TMath::Power(px,2)+TMath::Power(py,2)+TMath::Power(pz,2)));  
	if (pim_count==0&&pip_count==1&&nut_count==1&&ph_count==2&&pi0_count==1){
	  hist_taup_1ch10_2ph->Fill(m);
	}else if(pim_count==0&&pip_count==1&&nut_count==1&&e_count==1&&ep_count==1&&ph_count==1&&pi0_count==1&&pi0_count==1){
	  hist_taup_1ch10_epeph->Fill(m);
	}
	//cout << "Filled Tau_p hists" << endl;
	pip_count=0;
	pim_count=0;
	pi0_count=0;
	nut_count=0;
	e_count=0;
	ep_count=0;
	ph_count=0;
	for (int t=0;t<10;++t){
	  daughter_e[t]=0;
	  daughter_px[t]=0;
	  daughter_py[t]=0;
	  daughter_pz[t]=0;
	}
	n=0;
	for (int i=tau_n->D1; i<= tau_n->D2; ++i){
          daughter = (GenParticle*) branchParticle->At(i);
	  if (daughter->M1 == iTau_n || daughter->M2 == iTau_n){
	    if (daughter->PID==211 || daughter->PID==-211 || daughter->PID==16){
	      daughter_e[n]=daughter->E;
              daughter_px[n]=daughter->Px;
              daughter_py[n]=daughter->Py;
              daughter_pz[n]=daughter->Pz;
              n+=1;
	    }
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
		  }
		  if (daughter_2->PID==11){
		    e_count+=1;
		  }
	 	  if (daughter_2->PID==-11){
		    ep_count+=1;
		  }
		  daughter_e[n]=daughter_2->E;
                  daughter_px[n]=daughter_2->Px;
                  daughter_py[n]=daughter_2->Py;
                  daughter_pz[n]=daughter_2->Pz;
	          n+=1;
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
	e=0;px=0;py=0;pz=0;
        for (int l=0;l<10;++l){
            e+=daughter_e[l];
	    px+=daughter_px[l];
            py+=daughter_py[l];
	    pz+=daughter_pz[l];
	}
	m = TMath::Sqrt(TMath::Power(e,2)-(TMath::Power(px,2)+TMath::Power(py,2)+TMath::Power(pz,2)));
	//cout << "Pi minus: " << pim_count << "; Pi plus: " << pip_count << "; Nu tau: " << nut_count << "; Photons: " << ph_count << "; Pi zero: " << pi0_count << endl;
	if (pim_count==1&&pip_count==0&&nut_count==1&&ph_count==2&&pi0_count==1){
	  hist_taun_1ch10_2ph->Fill(m);
	}else if(pim_count==1&&pip_count==0&&nut_count==1&&e_count==1&&ep_count==1&&ph_count==1&&pi0_count==1){
	  hist_taun_1ch10_epeph->Fill(m);
	}
	//cout << "Filled Tau_n hists" << endl;
  }
  //cout << "Normalizing hists" << endl; 
  hist_taun_1ch10_2ph->Scale(1/(hist_taun_1ch10_2ph->GetEntries()));
  hist_taun_1ch10_epeph->Scale(1/(hist_taun_1ch10_epeph->GetEntries()));
  hist_taup_1ch10_2ph->Scale(1/(hist_taup_1ch10_2ph->GetEntries()));
  hist_taup_1ch10_epeph->Scale(1/(hist_taup_1ch10_epeph->GetEntries()));
  cout << "** Exiting..." << endl;
  outf->Write();
  outf->Close();
  delete treeReader;
  delete chain;
}
