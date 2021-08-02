// run it in /root/Delphes-3.4.2 as root -l -q examples/gg2taus.C 

// To Do: include second tau

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

void rho2pions_mass(){

  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  
  gSystem->Load("libDelphes");
  
  TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *daughter;

  int iRho_p, iRho_n, iRho_0;

  TFile *outf = new TFile("rho_mass.root","RECREATE");

  TH1F *hist_rhop_m = new TH1F("hist_rhop_m","Positive rho decay",100,0.0,2.0); 

  TH1F *hist_rhom_m = new TH1F("hist_rhom_m","Negative rho decay",100,0.0,2.0); 

  TH1F *hist_rho0_m = new TH1F("hist_rho0_m","Neutral rho decay",100,0.0,2.0); 


  int pip_count, pim_count, pi0_count, n;

  Double_t m,e,px,py,pz;

  Double_t daughter_e[10];
  Double_t daughter_px[10];
  Double_t daughter_py[10];
  Double_t daughter_pz[10];
	
  
 for(int entry = 0; entry < allEntries; ++entry){
   if (entry>100) break;
   treeReader->ReadEntry(entry);
   for(int j = 0; j < branchParticle->GetEntriesFast(); ++j){
     particle = (GenParticle*) branchParticle->At(j);
     if (particle->Status!=1){
      if (particle->PID==213){
	cout << "--------- New rho -----------"<< endl;
	iRho_p=j;
	pip_count=0;
	pim_count=0;
	pi0_count=0;
	for (int t=0;t<10;++t){
	  daughter_e[t]=0;
	  daughter_px[t]=0;
	  daughter_py[t]=0;
	  daughter_pz[t]=0;
	}
	n=0;
	for (int i=particle->D1; i<= particle->D2; ++i){
          daughter = (GenParticle*) branchParticle->At(i);
	  if (daughter->M1 == iRho_p || daughter->M2 == iRho_p){
            if (daughter->PID==211){
	      pip_count+=1;
	      daughter_e[n]=daughter->E;
	      daughter_px[n]=daughter->Px;
	      daughter_py[n]=daughter->Py;
	      daughter_pz[n]=daughter->Pz;
	      cout << daughter->PID << endl;
	      n+=1;
	    }
            if (daughter->PID==111){
	      pi0_count+=1;
	      daughter_e[n]=daughter->E;
	      daughter_px[n]=daughter->Px;
	      daughter_py[n]=daughter->Py;
	      daughter_pz[n]=daughter->Pz;
	      n+=1;
	      cout << daughter->PID << endl;
	    }
            if (daughter->PID==-211){
	      pim_count+=1;
	      daughter_e[n]=daughter->E;
	      daughter_px[n]=daughter->Px;
	      daughter_py[n]=daughter->Py;
	      daughter_pz[n]=daughter->Pz;
	      n+=1;
	      cout << daughter->PID << endl;
	    }
          }                                                                                                                                                                                              
        }
	e=0;px=0;py=0;pz=0;
	if (pim_count==0&&pip_count==1){
	  for (int l=0;l<10;++l){
	    e+=daughter_e[l];
	    px+=daughter_px[l];
	    py+=daughter_py[l];
	    pz+=daughter_pz[l];
	  }
	  m = TMath::Sqrt(TMath::Power(e,2)-(TMath::Power(px,2)+TMath::Power(py,2)+TMath::Power(pz,2))); 
	  hist_rhop_m->Fill(m);
	}
      }
      /*
      if (particle->PID==-213){
	iRho_n=j;
	pip_count=0;
	pim_count=0;
	pi0_count=0;
	for (int t=0;t<10;++t){
	  daughter_e[t]=0;
	  daughter_px[t]=0;
	  daughter_py[t]=0;
	  daughter_pz[t]=0;
	}
	n=0;
	for (int i=particle->D1; i<= particle->D2; ++i){
          daughter = (GenParticle*) branchParticle->At(i);
	  if (daughter->M1 == iRho_n || daughter->M2 == iRho_n){
            if (daughter->PID==211){
	      pip_count+=1;
	      daughter_e[n]=daughter->E;
	      daughter_px[n]=daughter->Px;
	      daughter_py[n]=daughter->Py;
	      daughter_pz[n]=daughter->Pz;
	      n+=1;
	    }
            if (daughter->PID==111){
	      pi0_count+=1;
	      daughter_e[n]=daughter->E;
	      daughter_px[n]=daughter->Px;
	      daughter_py[n]=daughter->Py;
	      daughter_pz[n]=daughter->Pz;
	      n+=1;
	    }
            if (daughter->PID==-211){
	      pim_count+=1;
	      daughter_e[n]=daughter->E;
	      daughter_px[n]=daughter->Px;
	      daughter_py[n]=daughter->Py;
	      daughter_pz[n]=daughter->Pz;
	      n+=1;
	    }
          }                                                                                                                                                                                              
        }
	e=0;px=0;py=0;pz=0;
	if (pim_count==1&&pip_count==0){
	  for (int l=0;l<10;++l){
	    e+=daughter_e[l];
	    px+=daughter_px[l];
	    py+=daughter_py[l];
	    pz+=daughter_pz[l];
	  }
	  m = TMath::Sqrt(TMath::Power(e,2)-(TMath::Power(px,2)+TMath::Power(py,2)+TMath::Power(pz,2))); 
	  hist_rhom_m->Fill(m);
	}
      }
      if (particle->PID==113){
	iRho_0=j;
	pip_count=0;
	pim_count=0;
	pi0_count=0;
	for (int t=0;t<10;++t){
	  daughter_e[t]=0;
	  daughter_px[t]=0;
	  daughter_py[t]=0;
	  daughter_pz[t]=0;
	}
	n=0;
	for (int i=particle->D1; i<= particle->D2; ++i){
          daughter = (GenParticle*) branchParticle->At(i);
	  if (daughter->M1 == iRho_0 || daughter->M2 == iRho_0){
            if (daughter->PID==211){
	      pip_count+=1;
	      daughter_e[n]=daughter->E;
	      daughter_px[n]=daughter->Px;
	      daughter_py[n]=daughter->Py;
	      daughter_pz[n]=daughter->Pz;
	      n+=1;
	    }
            if (daughter->PID==111){
	      pi0_count+=1;
	      daughter_e[n]=daughter->E;
	      daughter_px[n]=daughter->Px;
	      daughter_py[n]=daughter->Py;
	      daughter_pz[n]=daughter->Pz;
	      n+=1;
	    }
            if (daughter->PID==-211){
	      pim_count+=1;
	      daughter_e[n]=daughter->E;
	      daughter_px[n]=daughter->Px;
	      daughter_py[n]=daughter->Py;
	      daughter_pz[n]=daughter->Pz;
	      n+=1;
	    }
	    }                                                                                                                                                                                            
        }
	e=0;px=0;py=0;pz=0;
	if (pim_count==1&&pip_count==1){
	  for (int l=0;l<10;++l){
	    e+=daughter_e[l];
	    px+=daughter_px[l];
	    py+=daughter_py[l];
	    pz+=daughter_pz[l];
	  }
	  m = TMath::Sqrt(TMath::Power(e,2)-(TMath::Power(px,2)+TMath::Power(py,2)+TMath::Power(pz,2))); 
	  hist_rho0_m->Fill(m);
	}
       }
      */
      }
     }
    }
  /*hist_rhop_m->Scale(1/(hist_rhop_m->GetEntries()));
  hist_rhom_m->Scale(1/(hist_rhom_m->GetEntries()));
  hist_rho0_m->Scale(1/(hist_rho0_m->GetEntries()));*/
  cout << "** Exiting..." << endl;
  //outf->Write();
  outf->Close();
  delete treeReader;
  delete chain;
}
