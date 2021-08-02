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

void tau2pions_mass(){
  gSystem->Load("/root/MG5_aMC_v2_7_3/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");
  
  TString inputFile = "/root/bsm_minv0p_pt1_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *daughter, *tau_p,*tau_n;

  int iTau_p, iTau_n;

  TFile *outf = new TFile("tau_mass_pions.root","RECREATE");

  TH1F *hist_taup_1ch = new TH1F("hist_taup_1ch","Positive tau decay into 1 charged pion",500,1.7767,1.7773); 

  TH1F *hist_taum_1ch = new TH1F("hist_taum_1ch","Negative tau decay into 1 charged pion",500,1.7767,1.7773);

  TH1F *hist_taup_3ch = new TH1F("hist_taup_3ch","Positive tau decay into 3 charged pions",500,1.7767,1.7773); 

  TH1F *hist_taum_3ch = new TH1F("hist_taum_3ch","Negative tau decay into 3 charged pions",500,1.7767,1.7773); 

  int pip_count, pim_count, pi0_count, n, nut_count;

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
     //if (particle->Status!=1){
      if (particle->PID==-15){
	iTau_p=j;
	tau_p=(GenParticle*) branchParticle->At(j);
      }
      if (particle->PID==15){
	iTau_n=j;
	tau_n=(GenParticle*) branchParticle->At(j);
      }
    }
	pip_count=0;
	pim_count=0;
	pi0_count=0;
	nut_count=0;
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
	    if (daughter->PID==211 || daughter->PID==111 || daughter->PID==-211 || daughter->PID==-16){
	      daughter_e[n]=daughter->E;
              daughter_px[n]=daughter->Px;
              daughter_py[n]=daughter->Py;
              daughter_pz[n]=daughter->Pz;
              n+=1;
	    }
	    if (daughter->PID==211){
	      pip_count+=1;
	      n+=1;
	    }
            if (daughter->PID==111){
	      pi0_count+=1;
	      n+=1;
	    }
            if (daughter->PID==-211){
	      pim_count+=1;
	      n+=1;
	    }
	    if (daughter->PID==-16){
	      nut_count+=1;
	      n+=1;
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
	if (pim_count==0&&pip_count==1&&nut_count==1){
	  hist_taup_1ch->Fill(m);
        }else if(pim_count==1&&pip_count==2&&nut_count==1){
	  hist_taup_3ch->Fill(m);
	}
     
	pip_count=0;
	pim_count=0;
	pi0_count=0;
	nut_count=0;
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
	    if (daughter->PID==211 || daughter->PID==111 || daughter->PID==-211 || daughter->PID==16){
	      daughter_e[n]=daughter->E;
              daughter_px[n]=daughter->Px;
              daughter_py[n]=daughter->Py;
              daughter_pz[n]=daughter->Pz;
              n+=1;
	    }
	    if (daughter->PID==211){
	      pip_count+=1;
	      n+=1;
	    }
            if (daughter->PID==111){
	      pi0_count+=1;
	      n+=1;
	    }
            if (daughter->PID==-211){
	      pim_count+=1;
	      n+=1;
	    }
	    if (daughter->PID==16){
	      nut_count+=1;
	      n+=1;
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
	if (pim_count==1&&pip_count==0&&nut_count==1){
	  hist_taum_1ch->Fill(m);
        }else if(pim_count==2&&pip_count==1&&nut_count==1){
	  hist_taum_3ch->Fill(m);
	}
  }
  hist_taup_1ch->Scale(1/(hist_taup_1ch->GetEntries()));
  hist_taum_1ch->Scale(1/(hist_taum_1ch->GetEntries()));
  hist_taup_3ch->Scale(1/(hist_taup_3ch->GetEntries()));
  hist_taum_3ch->Scale(1/(hist_taum_3ch->GetEntries()));
  cout << "** Exiting..." << endl;
  outf->Write();
  outf->Close();
  delete treeReader;
  delete chain;
}
