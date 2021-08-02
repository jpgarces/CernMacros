// run it in /root/Delphes-3.4.2

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

#include "/root/Delphes-3.4.2/external/ExRootAnalysis/ExRootTreeReader.h"
#include "/root/Delphes-3.4.2/external/ExRootAnalysis/ExRootResult.h"
#include "/root/MG5_aMC_v2_7_3/ExRootAnalysis/ExRootAnalysis/ExRootClasses.h"

class ExRootTreeReader;
class ExRootResult;
class ExRootLHEFReader;

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

/*double invariant_mass(GenParticle* d1,GenParticle* d2){
  double e2 = TMath::Power(d1->E + d2->E,2);
  double p2 = TMath::Power(d1->Px + d2->Px,2)+TMath::Power(d1->Py + d2->Py,2)+TMath::Power(d1->Pz + d2->Pz,2);
  double m = TMath::Sqrt(e2-p2);
  return m;
  }*/

/*double invariant_mass(GenParticle* *daughter_list){
  Int_t i;
  double e,px,py,pz;
  for(i=0;i<sizeof(daughter_list);i++){
   e += daughter_list[i])->E;
   px += daughter_list[i]->Px;
   py += daughter_list[i]->Py;
   pz += daughter_list[i]->Pz;
  }
  double m = TMath::Sqrt(TMath::Power(e,2)-(TMath::Power(px,2)+TMath::Power(py,2)+TMath::Power(pz,2)));
  return m;
}*/


void gg2taus_cont(){
  //Long64_t entry;

  gSystem->Load("/root/MG5_aMC_v2_7_3/ExRootAnalysis/libExRootAnalysis.so");
  gSystem->Load("libDelphes");
  //gSystem->Load("libPhysics");                                                                     
  //gSystem->Load("libMathCore");                                                                    
  TString inputFile = "/root/bsm_minv0p_pt1_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

  Long64_t allEntries = treeReader->GetEntries();

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle, *tau, *d1, *d2, *d3, *daughter;

  Int_t iTau;

  TFile *outf = new TFile("tau_invm.root","RECREATE");

  TH1F *hist_m = new TH1F("hist_m","Tau reconstructed invariant mass",1000,1.775,1.778); 
  
  for(Int_t entry = 0; entry < allEntries; ++entry){
    //for(Int_t entry = 0; entry < 10; ++entry){
    treeReader->ReadEntry(entry);
    for(Int_t j = 0; j < branchParticle->GetEntriesFast(); ++j){                                          
      particle = (GenParticle*) branchParticle->At(j);
      if (particle->PID==15){
        tau = (GenParticle*) branchParticle->At(j);
	iTau=j;
	//d1 = (GenParticle*) branchParticle->At(tau->D1);
	//d2 = (GenParticle*) branchParticle->At(tau->D2);
	//cout << "d1 E:" << d1->E << "d1 Px: " << d1->Px << "d1 Py: " << d1->Py << "d1 Pz: " << d1->Pz << endl;
	//cout <<	"d2 E:"	<< d2->E << "d2 Px: " << d2->Px	<< "d2 Py: " << d2->Py << "d2 Pz: " << d2->P \
z << endl;
       }
     }
    //Int_t n_daughter=0;
    //GenParticle* daughter_list[3]={d1,d2,d3};
    double e=0,px=0,py=0,pz=0;
    for(Int_t k=tau->D1; k<=tau->D2; ++k){
      daughter=(GenParticle*) branchParticle->At(k);
      if (daughter->M1 == iTau || daughter->M2 == iTau){
	e+=daughter->E;
	px += daughter->Px;                                                                                 py += daughter->Py;                                                                                 pz += daughter->Pz;
	//daughter_list[n_daughter]=(GenParticle*) branchParticle->At(k);
	//n_daughter+=1;
      }
    }
    /* double e=0,px=0,py=0,pz=0;
    for(Int_t i=0;i<sizeof(daughter_list);++i){
      cout << daughter_list[i]->E << endl;
      /*px += daughter_list[i]->Px;
      py += daughter_list[i]->Py;
      pz += daughter_list[i]->Pz;
      }*/
    double m = TMath::Sqrt(TMath::Power(e,2)-(TMath::Power(px,2)+TMath::Power(py,2)+TMath::Power(pz,2)));
    //cout << invariant_mass(d1,d2) << endl;
    hist_m->Fill(m);
  }

  cout << "** Exiting..." << endl;
  outf->Write();
  outf->Close();
  delete treeReader;
  delete chain;
}
