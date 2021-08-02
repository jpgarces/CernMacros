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

void tau_angles_pions_3ch(){
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");
  
  TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *daughter, *tau_p,*tau_n, *pi0daughter1, *pi0daughter2;

  int iTau_p, iTau_n;

  TFile *outf = new TFile("tau_angles_pions_3ch.root","RECREATE");

  TH1F *hist_nut_angles_3ch = new TH1F("hist_nut_angles_3ch","Tau neutrino angles",150,0.0,180.0);
  TH1F *hist_nut_angles_3ch10 = new TH1F("hist_nut_angles_3ch10","Tau neutrino angles",150,0.0,180.0);
  TH1F *hist_nut_angles_3ch20 = new TH1F("hist_nut_angles_3ch20","Tau neutrino angles",150,0.0,180.0);
  
  TH1F *hist_ph_angles_3ch10 = new TH1F("hist_ph_angles_3ch10","Photon angles",150,0.0,180.0);
  TH1F *hist_ph_angles_3ch20 = new TH1F("hist_ph_angles_3ch20","Photon angles",150,0.0,180.0);

  TH1F *hist_pim_angles_3ch = new TH1F("hist_pim_angles_3ch","Negative pion angles",150,0.0,180.0);
  TH1F *hist_pim_angles_3ch10 = new TH1F("hist_pim_angles_3ch10","Negative pion angles",150,0.0,180.0);
  TH1F *hist_pim_angles_3ch20 = new TH1F("hist_pim_angles_3ch20","Negative pion angles",150,0.0,180.0);

  TH1F *hist_pip_angles_3ch = new TH1F("hist_pip_angles_3ch","Positive pion angles",150,0.0,180.0);
  TH1F *hist_pip_angles_3ch10 = new TH1F("hist_pip_angles_3ch10","Positive pion angles",150,0.0,180.0);
  TH1F *hist_pip_angles_3ch20 = new TH1F("hist_pip_angles_3ch20","Positive pion angles",150,0.0,180.0);


  TVector3 pim_pvec, pi0_pvec, ph_pvec, nut_pvec, pip_pvec;

  int pim_count, pi0_count, ph_count, nut_count, n, pip_count, k;

  TVector3 ph_pvec_arr[4];

  TVector3 pim_pvec_arr[2];
  
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
   TVector3 taun_pvec(tau_n->Px,tau_n->Py,tau_n->Pz);
   pim_count=0;
   pi0_count=0;
   nut_count=0;
   ph_count=0;
   pip_count=0;
   n=0;
   k=0;
    for (int i=tau_n->D1; i<= tau_n->D2; ++i){
       daughter = (GenParticle*) branchParticle->At(i);
       if (daughter->M1 == iTau_n || daughter->M2 == iTau_n){
	 if (daughter->PID==-211&&daughter->Status==1){
	   pim_count+=1;
	   if(k<2){
	     pim_pvec_arr[k].SetX(daughter->Px);
	     pim_pvec_arr[k].SetY(daughter->Py);
	     pim_pvec_arr[k].SetZ(daughter->Pz);
	   }
	   k+=1;
         }
	 if (daughter->PID==111){
	    pi0_count+=1;
	    pi0daughter1 = (GenParticle*) branchParticle->At(daughter->D1);
	    pi0daughter2 = (GenParticle*) branchParticle->At(daughter->D2);
	    if(pi0daughter1->PID==22&&pi0daughter2->PID==22){
	      ph_count+=2;
	      if(n<4){
	       ph_pvec_arr[n].SetX(pi0daughter1->Px);
	       ph_pvec_arr[n].SetY(pi0daughter1->Py);
	       ph_pvec_arr[n].SetZ(pi0daughter1->Pz);
	       ph_pvec_arr[n+1].SetX(pi0daughter2->Px);
	       ph_pvec_arr[n+1].SetY(pi0daughter2->Py);
	       ph_pvec_arr[n+1].SetZ(pi0daughter2->Pz);
	      }
	      n+=2;
	    }
         }
	 if (daughter->PID==211&&daughter->Status==1){
	    pip_count+=1;
	    pip_pvec.SetX(daughter->Px);
	    pip_pvec.SetY(daughter->Py);
	    pip_pvec.SetZ(daughter->Pz);
         }
	 if (daughter->PID==16&&daughter->Status==1){
	    nut_count+=1;
	    nut_pvec.SetX(daughter->Px);
	    nut_pvec.SetY(daughter->Py);
	    nut_pvec.SetZ(daughter->Pz);
         }
       }
     }
    
     if (pim_count==2&&pip_count==1&&pi0_count==0&&ph_count==0&&nut_count==1){
        hist_pim_angles_3ch->Fill(pim_pvec_arr[0].Angle(taun_pvec)*57.2958);
        hist_pim_angles_3ch->Fill(pim_pvec_arr[1].Angle(taun_pvec)*57.2958);
	hist_pip_angles_3ch->Fill(pip_pvec.Angle(taun_pvec)*57.2958);
	hist_nut_angles_3ch->Fill(nut_pvec.Angle(taun_pvec)*57.2958);
     }
     if (pim_count==2&&pip_count==1&&pi0_count==1&&ph_count==2&&nut_count==1){
        hist_pim_angles_3ch10->Fill(pim_pvec_arr[0].Angle(taun_pvec)*57.2958);
        hist_pim_angles_3ch10->Fill(pim_pvec_arr[1].Angle(taun_pvec)*57.2958);
	hist_nut_angles_3ch10->Fill(nut_pvec.Angle(taun_pvec)*57.2958);
	hist_ph_angles_3ch10->Fill(ph_pvec_arr[0].Angle(taun_pvec)*57.2958);
	hist_ph_angles_3ch10->Fill(ph_pvec_arr[1].Angle(taun_pvec)*57.2958);
	hist_pip_angles_3ch10->Fill(pip_pvec.Angle(taun_pvec)*57.2958);
     }
     if (pim_count==2&&pip_count==1&&pi0_count==2&&ph_count==4&&nut_count==1){
        hist_pim_angles_3ch20->Fill(pim_pvec_arr[0].Angle(taun_pvec)*57.2958);
        hist_pim_angles_3ch20->Fill(pim_pvec_arr[1].Angle(taun_pvec)*57.2958);
	hist_nut_angles_3ch20->Fill(nut_pvec.Angle(taun_pvec)*57.2958);
	hist_ph_angles_3ch20->Fill(ph_pvec_arr[0].Angle(taun_pvec)*57.2958);
	hist_ph_angles_3ch20->Fill(ph_pvec_arr[1].Angle(taun_pvec)*57.2958);
	hist_ph_angles_3ch20->Fill(ph_pvec_arr[2].Angle(taun_pvec)*57.2958);
	hist_ph_angles_3ch20->Fill(ph_pvec_arr[3].Angle(taun_pvec)*57.2958);
	hist_pip_angles_3ch20->Fill(pip_pvec.Angle(taun_pvec)*57.2958);
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
