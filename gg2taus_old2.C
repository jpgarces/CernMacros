#ifdef __CLING__
R__LOAD_LIBRARY(/root/Delphes-3.4.2/libDelphes.so)

#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#include "external/ExRootAnalysis/ExRootResult.h"

//#include "/root/Delphes-3.4.2/classes/DelphesClasses.h"
//#include "/root/Delphes-3.4.2/external/ExRootAnalysis/ExRootTreeReader.h"
//#include "/root/Delphes-3.4.2/external/ExRootAnalysis/ExRootResult.h"
//R__LOAD_LIBRARY(/root/MG5_aMC_v2_7_3/ExRootAnalysis/libExRootAnalysis.so)
//#include "/root/MG5_aMC_v2_7_3/ExRootAnalysis/ExRootAnalysis/ExRootClasses.h"


#else
class ExRootTreeReader;
class ExRootResult;
class ExRootLHEFReader;
#endif 

//#include "/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/HEPTools/hepmc/include/HepMC/GenParticle.h"

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


void gg2taus(){

  Long64_t entry;
  
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

  GenParticle *particle;

  Int_t j;

  
  
 // Loop over all events
  for(entry = 0; entry < allEntries; ++entry){
    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);
    if(entry%500 == 0) cout << "Event number: "<< entry <<endl;
    // Loop over all hard partons in event
     for(j = 0; j < branchParticle->GetEntriesFast(); ++j)
     {
       //particle = (GenParticle*) branchParticle->At(j);
       particle = (GenParticle*) branchParticle->At(j);
       if (particle->PID==15){
	  cout << "Tau index: " << particle->PID << endl;
	}
      }
  }
  
  
  cout << "** Exiting..." << endl;

  delete treeReader;
  delete chain;
}
