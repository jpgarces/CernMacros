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

void tau_decays(){
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");

  //FILE *f = fopen("test1.txt","w");
  
  TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *tau, *tau_n, *tau_p, *daughter;

  int iTau_p, iTau_n, muon_count=0;

  
  int ch_nk_1=0;
  int ch_pk_1=0;
  int ch_pip_1=0;
  int ch_pim_1=0;
  int ch_pip_3=0;
  int ch_pim_3=0;
  int ch_e_1=0;
  int ch_ep_1=0;
  int ch_mu_1=0;
  int ch_mup_1=0;
  
  //for(int entry = 0; entry < allEntries; ++entry){
    //if (entry>100) break;
    int entry=333;
    treeReader->ReadEntry(entry);
    for(int j = 0; j < branchParticle->GetEntriesFast(); ++j){                                   
      particle = (GenParticle*) branchParticle->At(j);
      if (particle->PID==15){
          tau_n = (GenParticle*) branchParticle->At(j);
	  iTau_n=j;
      }
      if (particle->PID==-15){
          tau_p = (GenParticle*) branchParticle->At(j);
	  iTau_p=j;
      }
     }
    cout << iTau_n << endl;
    cout << iTau_p << endl;
    int daughter_pids_n[10]={0,0,0,0,0,0,0,0,0,0};
    int n=0;
    cout << tau_n->D1 << endl;
    cout << tau_n->D2 << endl;
    for(int k=tau_n->D1; k<=tau_n->D2; ++k){
    //for(int k=0; k<branchParticle->GetEntriesFast(); ++k){
      daughter=(GenParticle*) branchParticle->At(k);
      //if (n<10){
      //if (daughter->M1 == iTau_n || daughter->M2 == iTau_n){
      cout << daughter->PID << endl;
      if (daughter->M1 == iTau_n){
	  //daughter_pids_n[n]=daughter->PID;
	  n+=1;
	  if(daughter->PID==13){
	    muon_count+=1;
	    //fprintf(f,"%i  %i\n",daughter->M1,entry);
	    //cout << daughter->M1 << endl;
	  }
        }
	//}
    }
    if (n>9){
      cout << n << endl;
    }
    /*int n_ch_nk=0;
    int n_ch_pim=0;
    int n_ch_e=0;
    int n_ch_mu=0;
    int n_dec=0;
    for(int l = 0; l<10; ++l){
      if (daughter_pids_n[l]==-321 || daughter_pids_n[l]==321) n_ch_nk+=1;
      if (daughter_pids_n[l]==-211 || daughter_pids_n[l]==211) n_ch_pim+=1;
      if (daughter_pids_n[l]==11) n_ch_e+=1;
      if (daughter_pids_n[l]==13) n_ch_mu+=1;
      if(daughter_pids_n[l]!=0){
	n_dec+=1;
      }
    }

    if (n_dec>6){
      cout<<n_dec<<endl;
    }

    int daughter_pids_p[10]={0,0,0,0,0,0,0,0,0,0};
    n=0;
    for(int k=tau_p->D1; k<=tau_p->D2; ++k){
      daughter=(GenParticle*) branchParticle->At(k);
      if (n<10){
        if (daughter->M1 == iTau_p || daughter->M2 == iTau_p){
	  daughter_pids_p[n]=daughter->PID;
	  n+=1;
        }
      }
    }
    
    int n_ch_pk=0;
    int n_ch_pip=0;
    int n_ch_ep=0;
    int n_ch_mup=0;
    for(int l = 0; l<10; ++l){
      if (daughter_pids_p[l]==-321 || daughter_pids_p[l]==321) n_ch_pk+=1;
      if (daughter_pids_p[l]==-211 || daughter_pids_p[l]==211) n_ch_pip+=1;
      if (daughter_pids_p[l]==-11) n_ch_ep+=1;
      if (daughter_pids_p[l]==-13) n_ch_mup+=1;
    }
    
    if (n_ch_nk==1) ch_nk_1+=1;
    if (n_ch_pim==1) ch_pim_1+=1;
    if (n_ch_e==1) ch_e_1+=1;
    if (n_ch_mu>=1) ch_mu_1+=1;

    if (n_ch_pk==1) ch_pk_1+=1;
    if (n_ch_pip==1) ch_pip_1+=1;
    if (n_ch_ep==1) ch_ep_1+=1;
    if (n_ch_mup==1) ch_mup_1+=1;

    if (n_ch_pim==3) ch_pim_3+=1;
    if (n_ch_pip==3) ch_pip_3+=1;*/

    //}
  /* cout << "Number of tau decays into 1 negative Kaon: " << ch_nk_1 << " -> " << ch_nk_1/500.0 << "%" <<  endl;
  cout << "Number of tau decays into 1 positive Kaon: " << ch_pk_1 << " -> " << ch_pk_1/500.0 << "%"<< endl;
  cout << "Number of tau decays into 1 negative Pion: " << ch_pim_1 << " -> " << ch_pim_1/500.0 << "%"<< endl;
  cout << "Number of tau decays into 1 positive Pion: " << ch_pip_1 << " -> " << ch_pip_1/500.0 << "%"<< endl;
  cout << "Number of tau decays into 2 negative and 1 positive Pions: " << ch_pim_3 << " -> " << ch_pim_3/500.0 << "%" << endl;
  cout << "Number of tau decays into 2 positive and 1 negative Pions: " << ch_pip_3 << " -> " << ch_pim_3/500.0 << "%"<< endl;
  cout << "Number of tau decays into 1 Electron: " << ch_e_1 << " -> " << ch_e_1/500.0 << "%" << endl;
  cout << "Number of tau decays into 1 Positron: " << ch_ep_1 << " -> " << ch_ep_1/500.0 << "%" << endl;
  cout << "Number of tau decays into 1 Muon: " << ch_mu_1 << " -> " << ch_mu_1/500.0 << "%" << endl;
  cout << "Number of tau decays into 1 positive Muon: " << ch_mup_1 << " -> " << ch_mup_1/500.0 << "%" << endl;
  int total_decays = ch_nk_1+ch_pk_1+ch_pim_1+ch_pip_1+ch_pim_3+ch_pip_3+ch_e_1+ch_ep_1+ch_mu_1+ch_mup_1;
  cout << "Total number of decays: " << total_decays << endl;
  cout << "Total number of events: " << allEntries << endl;
  cout << "Total number of muons: " << muon_count << endl;
  cout << "** Exiting..." << endl;*/
  cout << muon_count << endl;
  delete treeReader;
  delete chain;
  //fclose(f);
}
