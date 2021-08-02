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

void tau2leptons_mass_fstate(){
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

  /* TFile *outf = new TFile("tau_mass_leptons_fstate.root","RECREATE");

  TH1F *hist_taup_ep = new TH1F("hist_taup_ep","Positive tau decay into a positron",500,1.7767,1.7773); 

  TH1F *hist_taum_e = new TH1F("hist_taum_e","Negative tau decay into an electron",500,1.7767,1.7773);

  TH1F *hist_taup_mup = new TH1F("hist_taup_mup","Positive tau decay into a positive muon",500,1.7767,1.7773); 

  TH1F *hist_taum_mu = new TH1F("hist_taum_mu","Negative tau decay into a muon",500,1.7767,1.7773); 

  int e_count, ep_count, mu_count, mup_count, nue_count, num_count, nut_count, n;

  Double_t m,e,px,py,pz;

  Double_t daughter_e[10];
  Double_t daughter_px[10];
  Double_t daughter_py[10];
  Double_t daughter_pz[10];*/
  
  
  for(int entry = 0; entry < allEntries; ++entry){
  //for(int entry = 0; entry < 5000; ++entry){
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
   /*ep_count=0;
	mup_count=0;
	nue_count=0;
	num_count=0;
	nut_count=0;
	for (int t=0;t<10;++t){
	  daughter_e[t]=0;
	  daughter_px[t]=0;
	  daughter_py[t]=0;
	  daughter_pz[t]=0;
	}
	n=0;*/
	for (int i=tau_n->D1; i<= tau_n->D2; ++i){
          daughter = (GenParticle*) branchParticle->At(i);
	  if (daughter->M1 == iTau_n || daughter->M2 == iTau_n){
	    if (daughter->PID==111){
	      //if (daughter->Status!=1){
      	        cout << daughter->PID << ": " << daughter->D1 << endl;
		//}
	    }
	  }
	}
	    /* if (daughter->PID==-11 || daughter->PID==12 || daughter->PID==-16){
	      daughter_e[n]=daughter->E;
              daughter_px[n]=daughter->Px;
              daughter_py[n]=daughter->Py;
              daughter_pz[n]=daughter->Pz;
              n+=1;
	    }
	    if (daughter->PID==-11){
	      ep_count+=1;
	      n+=1;
	    }
            if (daughter->PID==-13){
	      mup_count+=1;
	      n+=1;
	    }
            if (daughter->PID==12){
	      nue_count+=1;
	      n+=1;
	    }
	    if (daughter->PID==14){
	      num_count+=1;
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
	if (ep_count==1&&nue_count==1&&nut_count==1){
	  hist_taup_ep->Fill(m);
        }else if(mup_count==1&&num_count==1&&nut_count==1){
	  hist_taup_mup->Fill(m);
	}
	e_count=0;
	mu_count=0;
	nue_count=0;
	num_count=0;
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
	    if (daughter->PID==11 || daughter->PID==13 || daughter->PID==-12 || daughter->PID==-14|| daughter->PID==16){
	      daughter_e[n]=daughter->E;
              daughter_px[n]=daughter->Px;
              daughter_py[n]=daughter->Py;
              daughter_pz[n]=daughter->Pz;
              n+=1;
	    }
	    if (daughter->PID==11){
	      e_count+=1;
	      n+=1;
	    }
            if (daughter->PID==13){
	      mu_count+=1;
	      n+=1;
	    }
            if (daughter->PID==-12){
	      nue_count+=1;
	      n+=1;
	    }
	    if (daughter->PID==-14){
	      num_count+=1;
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
	if (e_count==1&&nue_count==1&&nut_count==1){
	  hist_taum_e->Fill(m);
        }else if(mu_count==1&&num_count==1&&nut_count==1){
	  hist_taum_mu->Fill(m);
	  }*/
  }
  /*hist_taup_ep->Scale(1/(hist_taup_ep->GetEntries()));
  hist_taup_mup->Scale(1/(hist_taup_mup->GetEntries()));
  hist_taum_e->Scale(1/(hist_taum_e->GetEntries()));
  hist_taum_mu->Scale(1/(hist_taum_mu->GetEntries()));
  cout << "** Exiting..." << endl;
  outf->Write();
  outf->Close();*/
  delete treeReader;
  delete chain;
}
