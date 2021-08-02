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

/*
#include "/root/Delphes-3.4.2/external/ExRootAnalysis/ExRootTreeReader.h"
#include "/root/Delphes-3.4.2/external/ExRootAnalysis/ExRootResult.h"
#include "/root/MG5_aMC_v2_7_3/ExRootAnalysis/ExRootAnalysis/ExRootClasses.h"

class ExRootTreeReader;
class ExRootResult;
class ExRootLHEFReader;*/

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

void gg2taus(){
  gSystem->Load("/root/MG5_aMC_v2_7_3/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");
  
  TString inputFile = "/root/bsm_minv0p_pt1_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *tau, *tau_n, *tau_p, *daughter;

  int iTau_p, iTau_n;

  TFile *outf = new TFile("tau_invm.root","RECREATE");

  TH1F *hist_m = new TH1F("hist_m","Tau reconstructed invariant mass",1000,1.775,1.778); 

  //TH1F *hist_m_ep = new TH1F("hist_m_ep","Positive taus reconstructed invariant mass (decay into positron)",1000,1.775,1.778); 

  //TH1F *hist_m_mup = new TH1F("hist_m_mup","Negative taus reconstructed invariant mass (decay into positive muon)",1000,1.775,1.778); 

  //TH1F *hist_m_e = new TH1F("hist_m_e","Positive taus reconstructed invariant mass (decay into electron)",1000,1.775,1.778); 

  //TH1F *hist_m_mu = new TH1F("hist_m_mu","Negative taus reconstructed invariant mass (decays into muon)",1000,1.775,1.778); 

  
  /*int n_lep_decays = 0;

  int n_e_decays=0;
  int n_mu_decays=0;
  int n_ep_decays=0;
  int n_mup_decays=0;*/
  
  for(int entry = 0; entry < allEntries; ++entry){
    //for(int entry = 0; entry < 1000; ++entry){
    treeReader->ReadEntry(entry);
    for(int j = 0; j < branchParticle->GetEntriesFast(); ++j){                                   
      particle = (GenParticle*) branchParticle->At(j);
      if (particle->PID==15){
          tau_n = (GenParticle*) branchParticle->At(j);
	  iTau_n=j;
	  //cout << "Negative tau: " << iTau_n << endl;
       }
      if (particle->PID==-15){
          tau_p = (GenParticle*) branchParticle->At(j);
	  iTau_p=j;
	  //cout << "Positive tau: " << iTau_p << endl;
       }
     }
    double e=0,px=0,py=0,pz=0,m=0;
    int daughter_pids[3]={0,0,0};
    int n=0;
    for(int k=tau_n->D1; k<=tau_n->D2; ++k){
      daughter=(GenParticle*) branchParticle->At(k);
      if (n<3){
        if (daughter->M1 == iTau_n || daughter->M2 == iTau_n){
	  e+=daughter->E;
	  px += daughter->Px;
	  py += daughter->Py;
	  pz += daughter->Pz;
	  daughter_pids[n]=daughter->PID;
	  n+=1;
        }
      }
    }
    int d1_id = daughter_pids[0];
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
    //hist_m->Fill(m);
  }
  /*cout << "Number of tau decays into electrons: " << n_e_decays << endl;
  cout << "Number of tau decays into positrons: " << n_ep_decays << endl;
  cout << "Number of tau decays into muons: " << n_mu_decays << endl;
  cout << "Number of tau decays into positive muons: " << n_mup_decays << endl;
  cout << "Total number of events: " << allEntries << endl;*/
  cout << "** Exiting..." << endl;
  outf->Write();
  outf->Close();
  delete treeReader;
  delete chain;
}
