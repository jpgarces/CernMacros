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

void not_tau_rec_mass_lep(){
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");
  
  TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *daughter, *mom1, *mom2;

  TFile *outf = new TFile("not_tau_mass_e.root","RECREATE");

  TFile *e_f = TFile::Open("electron_PT.root");
  TFile *nue_f = TFile::Open("nue_PT.root");
  TFile *nut_f = TFile::Open("nut_PT.root");

  TH1F *hist_not_tau_mass = new TH1F("hist_not_tau_mass","Mass from leptonic products not from tau decay",500,1.0,2.5); 

  int e_count, nue_count, num_count, nut_count, n, e_entries, nue_entries, nut_entries;

  Double_t m,e,px,py,pz;

  Double_t daughter_e[10];
  Double_t daughter_px[10];
  Double_t daughter_py[10];
  Double_t daughter_pz[10];

  TH1F *e_hist = (TH1F*) e_f->Get("hist_e_else_pt");
  TH1F *nue_hist = (TH1F*) nue_f->Get("hist_nue_else_pt");
  TH1F *nut_hist = (TH1F*) nut_f->Get("hist_nut_else_pt");

  e_entries=e_hist->GetEntries();
  nue_entries=nue_hist->GetEntries();
  nut_entries=nut->GetEntries();

for(int entry = 0; entry < allEntries; ++entry){
 //for(int entry = 0; entry < 5000; ++entry){
 treeReader->ReadEntry(entry);
 for(int j = 0; j < branchParticle->GetEntriesFast(); ++j){
   particle = (GenParticle*) branchParticle->At(j);
   mom1 = (GenParticle*) branchParticle->At(particle->M1);
   mom2 = (GenParticle*) branchParticle->At(particle->M2);
     
   e_count=0;
   nue_count=0;
   nut_count=0;
   /*for (int t=0;t<10;++t){
      daughter_e[t]=0;
      daughter_px[t]=0;
      daughter_py[t]=0;
      daughter_pz[t]=0;
      }*/
    n=0;
    if (mom1->PID!=15&&mom1->PID!=-15&&mom2->PID!=15&&mom2->PID!=-15){
     if (daughter->PID==11&&daughter->Status==1){
       e_count+=1;
     }
     if (daughter->PID==-12&&daughter->Status==1){
       nue_count+=1;
     }
     if (daughter->PID==16&&daughter->Status==1){
       nut_count+=1;
     }
	 /*if ((daughter->PID==11 || daughter->PID==-12 || daughter->PID==16)&&daughter->Status==1){
	    hist_e_mass->Fill(daughter->Mass);
	    daughter_e[n]=daughter->E;
            daughter_px[n]=daughter->Px;
            daughter_py[n]=daughter->Py;
            daughter_pz[n]=daughter->Pz;
            n+=1;
	    }*/
    }
  }
   /*e=0;px=0;py=0;pz=0;
     for (int l=0;l<10;++l){
       e+=daughter_e[l];
       px+=daughter_px[l];
       py+=daughter_py[l];
       pz+=daughter_pz[l];
     }
     m = TMath::Sqrt(TMath::Power(e,2)-(TMath::Power(px,2)+TMath::Power(py,2)+TMath::Power(pz,2)));  
     if (e_count==1&&nue_count==1&&nut_count==1){
        hist_tau_mass_e->Fill(m);
	}*/
  }
  /*hist_taup_ep->Scale(1/(hist_taup_ep->GetEntries()));
  hist_taup_mup->Scale(1/(hist_taup_mup->GetEntries()));
  hist_taum_e->Scale(1/(hist_taum_e->GetEntries()));
  hist_taum_mu->Scale(1/(hist_taum_mu->GetEntries()));*/
  cout << "Number of electrons not from tau: " << e_count << endl;
  cout << "Number of electron neutrinos not from tau: " << e_count << endl;
  cout << "Number of tau neutrinos: " << e_count << endl; 
  cout << "** Exiting..." << endl;
  outf->Write();
  outf->Close();
  delete treeReader;
  delete chain;
}
