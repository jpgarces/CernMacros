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

void ditau_nonu_mass_lep(){
   gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");
  
  TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *daughter, *tau_p,*tau_n;

  int iTau_p, iTau_n;

  TFile *outf = new TFile("ditau_mass_lep_nonu.root","RECREATE");

  TH1F *hist_ditau_eep_mass_nonu = new TH1F("hist_ditau_eep_mass_nonu","di-Tau mass from electron/positron decays ignoring neutrinos",100,0.0,40.0);
  TH1F *hist_ditau_emup_mass_nonu = new TH1F("hist_ditau_emup_mass_nonu","di-Tau mass from electron/positive-muon decays ignoring neutrinos",100,0.0,40.0);
  TH1F *hist_ditau_muep_mass_nonu = new TH1F("hist_ditau_muep_mass_nonu","di-Tau mass from muon/positron decays ignoring neutrinos",100,0.0,40.0);
  TH1F *hist_ditau_mumup_mass_nonu = new TH1F("hist_ditau_mumup_mass_nonu","di-Tau mass from muon/positive-muon decays ignoring neutrinos",100,0.0,40.0);


  int e_count, anue_count, nut_count, n, nue_count, ep_count,anut_count, mu_count, anumu_count, numu_count, mup_count;

  Double_t m,e,px,py,pz;

  Double_t daughter_e[10];
  Double_t daughter_px[10];
  Double_t daughter_py[10];
  Double_t daughter_pz[10];
  
  
for(int entry = 0; entry < allEntries; ++entry){
  //for(int entry = 0; entry < 5000; ++entry){
   treeReader->ReadEntry(entry);
   for(int j = 0; j < branchParticle->GetEntriesFast(); ++j){
     particle = (GenParticle*) branchParticle->At(j);
      if (particle->PID==-15){
	iTau_p=j;
	tau_p=(GenParticle*) branchParticle->At(j);
      }
      if (particle->PID==15){
	iTau_n=j;
	tau_n=(GenParticle*) branchParticle->At(j);
      }
    }
   e_count=0;
   anue_count=0;
   nut_count=0;
   ep_count=0;
   nue_count=0;
   anut_count=0;
   mu_count=0;
   anumu_count=0;
   mup_count=0;
   numu_count=0;
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
	 if (daughter->PID==11&&daughter->Status==1){
	    e_count+=1;
         }
	 if (daughter->PID==13&&daughter->Status==1){
	    mu_count+=1;
         }
	 if (daughter->PID==-12&&daughter->Status==1){
	    anue_count+=1;
         }
	 if (daughter->PID==-14&&daughter->Status==1){
	    anumu_count+=1;
         }
	 if (daughter->PID==16&&daughter->Status==1){
	    nut_count+=1;
         }
	 if ((daughter->PID==11 || daughter->PID==13)&&daughter->Status==1){
	    daughter_e[n]=daughter->E;
            daughter_px[n]=daughter->Px;
            daughter_py[n]=daughter->Py;
            daughter_pz[n]=daughter->Pz;
            n+=1;
         }
       }
     }
    for (int i=tau_p->D1; i<= tau_p->D2; ++i){
       daughter = (GenParticle*) branchParticle->At(i);
       if (daughter->M1 == iTau_p || daughter->M2 == iTau_p){
	 if (daughter->PID==-11&&daughter->Status==1){
	    ep_count+=1;
         }
	 if (daughter->PID==-13&&daughter->Status==1){
	    mup_count+=1;
         }
	 if (daughter->PID==12&&daughter->Status==1){
	    nue_count+=1;
         }
	 if (daughter->PID==14&&daughter->Status==1){
	    numu_count+=1;
         }
	 if (daughter->PID==-16&&daughter->Status==1){
	    anut_count+=1;
         }
	 if ((daughter->PID==-11 || daughter->PID==-13)&&daughter->Status==1){
	    daughter_e[n]=daughter->E;
            daughter_px[n]=daughter->Px;
            daughter_py[n]=daughter->Py;
            daughter_pz[n]=daughter->Pz;
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
     if (e_count==1&&anue_count==1&&nut_count==1&&ep_count==1&&nue_count==1&&anut_count==1){
        hist_ditau_eep_mass_nonu->Fill(m);
     }
     if (e_count==1&&anue_count==1&&nut_count==1&&mup_count==1&&numu_count==1&&anut_count==1){
        hist_ditau_emup_mass_nonu->Fill(m);
     }
     if (mu_count==1&&anumu_count==1&&nut_count==1&&ep_count==1&&nue_count==1&&anut_count==1){
        hist_ditau_muep_mass_nonu->Fill(m);
     }
     if (mu_count==1&&anumu_count==1&&nut_count==1&&mup_count==1&&numu_count==1&&anut_count==1){
        hist_ditau_mumup_mass_nonu->Fill(m);
     }
  }
  /*hist_taup_ep->Scale(1/(hist_taup_ep->GetEntries()));
  hist_taup_mup->Scale(1/(hist_taup_mup->GetEntries()));
  hist_taum_e->Scale(1/(hist_taum_e->GetEntries()));
  hist_taum_mu->Scale(1/(hist_taum_mu->GetEntries()));*/
  cout << "** Exiting..." << endl;
  outf->Write();
  outf->Close();
  delete treeReader;
  delete chain;
}
