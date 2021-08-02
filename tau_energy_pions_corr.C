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

void tau_energy_pions_corr(){
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");
  
  TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *daughter, *tau_p, *tau_n, *pi0daughter1, *pi0daughter2;

  int iTau_p, iTau_n;

  TFile *outf = new TFile("tau_energy_pions_corr.root","RECREATE");

  TH2F *hist_pippim_energy = new TH2F("hist_pippim_energy","Charged pions",150,0.0,8.0,150,0.0,8.0);
  TH2F *hist_phph_energy = new TH2F("hist_phph_energy","Charged pions",150,0.0,8.0,150,0.0,8.0);

  int pim_count, pi0_count, ph_count, nut_count, n, pip_count, k;

  Double_t energy, pim_energy, ph1_energy, ph2_energy, nut_energy, pip_energy;

  Double_t ph_energy_arr[6], pim_energy_arr[2];
    
  
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
   pim_count=0;
   pi0_count=0;
   nut_count=0;
   ph_count=0;
   pip_count=0;
   n=0;
   k=0;
   for(int t=0;t<6;++t){
     ph_energy_arr[t]=0;
   }
   for(int t=0;t<2;++t){
     pim_energy_arr[t]=0;
   }
    for (int i=tau_n->D1; i<= tau_n->D2; ++i){
       daughter = (GenParticle*) branchParticle->At(i);
       if (daughter->M1 == iTau_n || daughter->M2 == iTau_n){
	 if (daughter->PID==-211&&daughter->Status==1){
	    pim_count+=1;
	    pim_energy_arr[k]=daughter->E;
	    k+=1;
         }
	 if (daughter->PID==111){
	    pi0_count+=1;
	    pi0daughter1 = (GenParticle*) branchParticle->At(daughter->D1);
	    pi0daughter2 = (GenParticle*) branchParticle->At(daughter->D2);
	    if(pi0daughter1->PID==22&&pi0daughter2->PID==22){
	      ph_count+=2;
	      ph_energy_arr[n]=pi0daughter1->E;
	      ph_energy_arr[n+1]=pi0daughter2->E;
	      n+=2;
	    }
	 }
	 if (daughter->PID==211&&daughter->Status==1){
	    pip_count+=1;
	    pip_energy=daughter->E;
	 }
	 if (daughter->PID==16&&daughter->Status==1){
	    nut_count+=1;
	    nut_energy=daughter->E;
         }
       }
     }
    if (pim_count==2&&pip_count==1&&pi0_count==0&&ph_count==0&&nut_count==1){
      hist_pippim_energy->Fill((pim_energy_arr[0]+pim_energy_arr[1])/2.0,pip_energy);
    }

    if (pim_count==2&&pip_count==1&&pi0_count==1&&ph_count==2&&nut_count==1){
      hist_phph_energy->Fill(ph_energy_arr[0],ph_energy_arr[1]);
    }

    /*if (pim_count==2&&pip_count==1&&pi0_count==0&&ph_count==0&&nut_count==1){
        hist_tau_energy_3ch->Fill(tau_n->E);
        hist_pim_energy_3ch->Fill(pim_energy_arr[0]);
        hist_pim_energy_3ch->Fill(pim_energy_arr[1]);
        hist_pip_energy_3ch->Fill(pip_energy);
	hist_nut_energy_3ch->Fill(nut_energy);
     }
     if (pim_count==2&&pip_count==1&&pi0_count==1&&ph_count==2&&nut_count==1){
        hist_tau_energy_3ch10->Fill(tau_n->E);
	hist_pim_energy_3ch10->Fill(pim_energy_arr[0]);
        hist_pim_energy_3ch10->Fill(pim_energy_arr[1]);
        hist_pip_energy_3ch10->Fill(pip_energy);
	hist_nut_energy_3ch10->Fill(nut_energy);
	hist_ph_energy_3ch10->Fill(ph_energy_arr[0]);
	hist_ph_energy_3ch10->Fill(ph_energy_arr[1]);
     }
     if (pim_count==2&&pip_count==1&&pi0_count==2&&ph_count==4&&nut_count==1){
        hist_tau_energy_3ch20->Fill(tau_n->E);
	hist_pim_energy_3ch20->Fill(pim_energy_arr[0]);
        hist_pim_energy_3ch20->Fill(pim_energy_arr[1]);
        hist_pip_energy_3ch20->Fill(pip_energy);
	hist_nut_energy_3ch20->Fill(nut_energy);
	hist_ph_energy_3ch20->Fill(ph_energy_arr[0]);
	hist_ph_energy_3ch20->Fill(ph_energy_arr[1]);
	hist_ph_energy_3ch20->Fill(ph_energy_arr[2]);
	hist_ph_energy_3ch20->Fill(ph_energy_arr[3]);
	}*/
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
