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

void rho2pions(){
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");
  
  TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *rho_0, *rho_n, *rho_p, *daughter;

  int iRho_p, iRho_n, iRho_0;

  TFile *outf = new TFile("rho_Eta.root","RECREATE");

  TH1F *hist_rhop = new TH1F("hist_rhop","Positive rho decay",100,-12.0,12.0); 

  TH1F *hist_rhom = new TH1F("hist_rhom","Negative rho decay",100,-12.0,12.0); 

  TH1F *hist_rho0 = new TH1F("hist_rho0","Neutral rho decay",100,-12.0,12.0); 


  int pip_count, pim_count, pi0_count, rhop_pi0pip=0, rhon_pi0pim=0, rho0_pimpip=0, rhop_else=0, rhon_else=0, rho0_else=0;
  for(int entry = 0; entry < allEntries; ++entry){
    //for(int entry = 0; entry < 1000; ++entry){
   treeReader->ReadEntry(entry);
   for(int j = 0; j < branchParticle->GetEntriesFast(); ++j){
     particle = (GenParticle*) branchParticle->At(j);
     if (particle->Status!=1){
      if (particle->PID==213){
	rho_p = (GenParticle*) branchParticle->At(j);
	iRho_p=j;
	pip_count=0;
	pim_count=0;
	pi0_count=0;
	for (int i=particle->D1; i<= particle->D2; ++i){
          daughter = (GenParticle*) branchParticle->At(i);
	  if (daughter->M1 == iRho_p || daughter->M2 == iRho_p){
            if (daughter->PID==211){
	      pip_count+=1;
	    }
            if (daughter->PID==111){
	      pi0_count+=1;
	    }
            if (daughter->PID==-211){
	      pim_count+=1;
	    }
	  }                                                                                                                                                                                              
        }
	if (pip_count==1&&pim_count==0){
	  rhop_pi0pip+=1;
	  hist_rhop->Fill(daughter->Eta);
	}else{
          rhop_else+=1;
	}
      }
      if (particle->PID==-213){
	rho_n = (GenParticle*) branchParticle->At(j);
	iRho_n=j;
	pip_count=0;
	pim_count=0;
	pi0_count=0;
	for (int i=particle->D1; i<= particle->D2; ++i){
          daughter = (GenParticle*) branchParticle->At(i);
	  if (daughter->M1 == iRho_n || daughter->M2 == iRho_n){
            if (daughter->PID==211){
	      pip_count+=1;
	    }
            if (daughter->PID==111){
	      pi0_count+=1;
	    }
            if (daughter->PID==-211){
	      pim_count+=1;
	    }
          }                                                                                                                                                                                              
        }
	if (pim_count==1&&pip_count==0){
	  rhon_pi0pim+=1;
	  hist_rhom->Fill(daughter->Eta);
	}else{
	  rhon_else+=1;
	}
       }
      if (particle->PID==113){
	rho_0 = (GenParticle*) branchParticle->At(j);
	iRho_0=j;
	pip_count=0;
	pim_count=0;
	pi0_count=0;
	for (int i=particle->D1; i<= particle->D2; ++i){
          daughter = (GenParticle*) branchParticle->At(i);
	  if (daughter->M1 == iRho_0 || daughter->M2 == iRho_0){
            if (daughter->PID==211){
	      pip_count+=1;
	    }
            if (daughter->PID==111){
	      pi0_count+=1;
	    }
            if (daughter->PID==-211){
	      pim_count+=1;
	    }
          }                                                                                                                                                                                              
        }
	if (pim_count==1&&pip_count==1){
	  rho0_pimpip+=1;
	  hist_rho0->Fill(daughter->Eta);
	}else{
	  rho0_else+=1;
	  //cout << pip_count << pi0_count << pim_count << endl;
	}
       }
      }
     }
    /* double e=0,px=0,py=0,pz=0,m=0;
    int daughter_pids[10]={0,0,0,0,0,0,0,0,0,0};
    int n=0;
    for(int k=tau_n->D1; k<=tau_n->D2; ++k){
      daughter=(GenParticle*) branchParticle->At(k);
      if (n<10){
        if (daughter->M1 == iTau_n || daughter->M2 == iTau_n){
	  //cout << "---- START DAUGHTERS ----" << endl;
	  e+=daughter->E;
	  px += daughter->Px;
	  py += daughter->Py;
	  pz += daughter->Pz;
	  daughter_pids[n]=daughter->PID;
	  if (daughter_pids[n]==113 || daughter_pids[n]==213 || daughter_pids[n]==-213){
	    cout << daughter_pids[n] << endl;
	  }
	  //cout << "-----END-----" << endl;
	  n+=1;
        }
      }
      }*/
    /*int d1_id = daughter_pids[0];
    int d2_id = daughter_pids[1];
    int d3_id = daughter_pids[2];
    //cout <<entry<< ": "<< d1_id << " " << d2_id << " " << d3_id << endl;
    if (d1_id==13&&d2_id==-14&&d3_id==16 || d1_id==-14&&d2_id==13&&d3_id==16 || d1_id==-14&&d2_id==16&&d3_id==13 || d1_id==16&&d2_id==13&&d3_id==-14 || d1_id==16&&d2_id==-14&&d3_id==13 || d1_id==13&&d2_id==16&&d3_id==-14){
      //n_lep_decays+=1;
      //n_mu_decays+=1;
      m = TMath::Sqrt(TMath::Power(e,2)-(TMath::Power(px,2)+TMath::Power(py,2)+TMath::Power(pz,2)));
      //hist_m_mu->Fill(m);
      hist_m->Fill(m);
    }
    if (d1_id==11&&d2_id==-12&&d3_id==16 || d1_id==-12&&d2_id==11&&d3_id==16 || d1_id==-12&&d2_id==16&&d3_id==11 || d1_id==16&&d2_id==11&&d3_id==-12 || d1_id==16&&d2_id==-12&&d3_id==11 || d1_id==11&&d2_id==16&&d3_id==-12){
      //n_lep_decays+=1;
      //n_e_decays+=1;
      m = TMath::Sqrt(TMath::Power(e,2)-(TMath::Power(px,2)+TMath::Power(py,2)+TMath::Power(pz,2)));
      //hist_m_e->Fill(m);
      hist_m->Fill(m);
    }
    //m = TMath::Sqrt(TMath::Power(e,2)-(TMath::Power(px,2)+TMath::Power(py,2)+TMath::Power(pz,2)));
    n=0;
    daughter_pids[0]=0;
    daughter_pids[1]=0;
    daughter_pids[2]=0;
    e=0;px=0;py=0;pz=0;m=0;
    for(int k=tau_p->D1; k<=tau_p->D2; ++k){
      daughter=(GenParticle*) branchParticle->At(k);
      if (n<3){
        if (daughter->M1 == iTau_p || daughter->M2 == iTau_p){
	  e+=daughter->E;
	  px += daughter->Px;
	  py += daughter->Py;
	  pz += daughter->Pz;
	  daughter_pids[n]=daughter->PID;
	  n+=1;
        }
      }
    }
    d1_id = daughter_pids[0];
    d2_id = daughter_pids[1];
    d3_id = daughter_pids[2];
    //cout <<entry<< ": "<< d1_id << " " << d2_id << " " << d3_id << endl; 
    if (d1_id==-11&&d2_id==12&&d3_id==-16 || d1_id==12&&d2_id==-11&&d3_id==-16 || d1_id==12&&d2_id==-16&&d3_id==-11 || d1_id==-16&&d2_id==-11&&d3_id==12 || d1_id==-16&&d2_id==12&&d3_id==-11 || d1_id==-11&&d2_id==-16&&d3_id==12){
      //n_lep_decays+=1;
      //n_ep_decays+=1;
      m = TMath::Sqrt(TMath::Power(e,2)-(TMath::Power(px,2)+TMath::Power(py,2)+TMath::Power(pz,2)));
      //hist_m_ep->Fill(m);
      hist_m->Fill(m);
      }
    if (d1_id==-13&&d2_id==14&&d3_id==-16 || d1_id==14&&d2_id==-13&&d3_id==-16 || d1_id==14&&d2_id==-16&&d3_id==-13 || d1_id==-16&&d2_id==-13&&d3_id==14 || d1_id==-16&&d2_id==14&&d3_id==-13 || d1_id==-13&&d2_id==-16&&d3_id==14){
      //n_lep_decays+=1;
      //n_mup_decays+=1;
      m = TMath::Sqrt(TMath::Power(e,2)-(TMath::Power(px,2)+TMath::Power(py,2)+TMath::Power(pz,2)));
      //hist_m_mup->Fill(m);
      hist_m->Fill(m);
    }
    //m = TMath::Sqrt(TMath::Power(e,2)-(TMath::Power(px,2)+TMath::Power(py,2)+TMath::Power(pz,2)));
    //hist_m->Fill(m);*/
    }
  /*cout << "Number of tau decays into electrons: " << n_e_decays << endl;
  cout << "Number of tau decays into positrons: " << n_ep_decays << endl;
  cout << "Number of tau decays into muons: " << n_mu_decays << endl;
  cout << "Number of tau decays into positive muons: " << n_mup_decays << endl;*/
  /*cout << "Total number of tau decays into rhos: " << rho_counter_n + rho_counter_p << endl;
  cout << "Total number of decays into rhos not coming from taus: " << rho_counter_else << endl;
  cout << "Total number of events: " << allEntries << endl;*/
  /*cout << "Number of positive rhos decaying into one positive pion and neutral pions: " << rhop_pi0pip << endl;
  cout << "Number of positive rhos decaying NOT into one positive pion and neutral pions: " << rhop_else << endl;
  cout << "Number of negative rhos decaying into one negative pion and neutral pions: " << rhon_pi0pim << endl;
  cout << "Number of negative rhos decaying NOT into one negative pion and neutral pions: " << rhon_else << endl;
  cout << "Number of neutral rhos decaying into one negative and one positive pion: " << rho0_pimpip << endl;
  cout << "Number of neutral rhos decaying NOT into one negative and one positive pion: " << rho0_else << endl;*/
  /*hist_rhop->Scale(1/(hist_rhop->GetEntries()));
  hist_rhom->Scale(1/(hist_rhom->GetEntries()));
  hist_rho0->Scale(1/(hist_rho0->GetEntries()));*/
  cout << "** Exiting..." << endl;
  outf->Write();
  outf->Close();
  delete treeReader;
  delete chain;
}
