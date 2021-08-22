#ifdef __CLING__
R__LOAD_LIBRARY(/home/juan/Delphes-3.5.0/libDelphes.so)

#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#include "external/ExRootAnalysis/ExRootResult.h"
#include "/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/ExRootAnalysis/ExRootTreeReader.h"
#include "/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/ExRootAnalysis/ExRootLHEFReader.h"
#include "/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/ExRootAnalysis/ExRootClasses.h"

   
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

  
const Int_t kMaxfParticles = 10000;

//void analysis(const char *inputFile, const char *outputFile)
void analysis()
{
  gSystem->Load("libDelphes");
  gSystem->Load("ExRootAnalysis/lib/libExRootAnalysis.so");
  gSystem->Load("libPhysics"); 
  gSystem->Load("libMathCore"); 
  TChain *chain = new TChain("Delphes");
  //chain->Add("/home/juan/bsm_minv0p_pt1_delphes_events_NNL.root");
  chain->Add("/home/juan/sm_UFO_minv0p_pt1_NNLO_delphes_events.root");

 ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

 cout << "sono qui " <<endl;

 Long64_t numberOfEntries = treeReader->GetEntries();
 
 // Get pointers to branches used in this analysis
 TClonesArray *branchParticle = treeReader->UseBranch("Particle");
 

 GenParticle *particle;
 
 TObject *object;

 TLorentzVector momentum;
    cout << "sono qui " <<endl;
  // Book histograms
  TH1 *histTauPT = new TH1F("tau_pt", "tau P_{T}", 100, 0.0, 100.0);
  TH1 *histTauLeadPT = new TH1F("tauLead_pt", "tau P_{T}", 100, 0.0, 100.0);
  TH1 *histTauNLPT = new TH1F("tauNL_pt", "tau P_{T}", 100, 0.0, 100.0);
  TH1 *histTauEta = new TH1F("tau_Eta", "tau Eta", 100, -5.0, 5.0);

  TH1 *histTauPhi = new TH1F("tau_Phi", "tau Phi", 100, -4.0, 4.0);
  TH1 *histTauRapidity = new TH1F("tau_Rapidity", "tau Rapidity", 100, -5.0, 5.0);

  TH1 *histDiTauMass = new TH1F("di_tau_Mass", "tau Mass system", 100, 0, 100.0);
  TH1 *histDiTauRapidity = new TH1F("di_tau_Rapidity", "tau Rapidity system", 100, -5.0, 5.0);

  TH1 *histTauNLeadEta = new TH1F("NLeadtau_Eta", "NLeadtau Eta", 100, -5.0, 5.0);
  TH1 *histTauLeadEta = new TH1F("Leadtau_Eta", "Leadtau Eta", 100, -5.0, 5.0);

  TH1 *histDiTauPt = new TH1F("di_tau_Pt", "tau Pt system", 100, 0, 2);




  
  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    treeReader->ReadEntry(entry);
    GenParticle *tauP, *tauN;
    double maxpt=0;
    int indexmaxpt = -1;
    double taup_pt, taun_pt, taun_eta, taup_eta;
    TLorentzVector taup_m, taun_m;
    for(Int_t i = 0; i < branchParticle->GetEntriesFast(); ++i)

    {
     
      particle = (GenParticle*) branchParticle->At(i);
      //      particle = (GenParticle*) electron->Particle.GetObject();
      //      particle = (GenParticle*) muon->Particle.GetObject();
      
      if (particle->PID ==-15) {
	  tauN = (GenParticle *) branchParticle->At(i);
	  taun_m.SetPxPyPzE(tauN->Px,tauN->Py,tauN->Pz,tauN->E);
      }
      if (particle->PID ==15) {
	  tauP = (GenParticle *) branchParticle->At(i); 
	  taup_m.SetPxPyPzE(tauP->Px,tauP->Py,tauP->Pz,tauP->E);
      }
    }

   
   taup_pt=tauP->PT;
   taun_pt=tauN->PT;
   taup_eta=tauP->Eta;
   taun_eta=tauN->Eta; 
  
  
   histTauPT->Fill(tauN->PT);
   histTauPT->Fill(tauP->PT);
   histTauPhi->Fill(tauN->Phi);
   histTauPhi->Fill(tauP->Phi);
   histTauEta->Fill(tauN->Eta);
   histTauEta->Fill(tauP->Eta);
   histTauRapidity->Fill(tauN->Rapidity);
   histTauRapidity->Fill(tauP->Rapidity);
    
    
    histDiTauPt->Fill((taup_m + taun_m).Pt());
    histDiTauMass->Fill((taup_m + taun_m).M());
    histDiTauRapidity->Fill((taup_m + taun_m).Rapidity());
    if (taup_pt>taun_pt){
      histTauLeadPT->Fill(taup_pt);
      histTauNLPT->Fill(taun_pt);
      histTauNLeadEta->Fill(taun_eta);
      histTauLeadEta->Fill(taup_eta);
    }
    else {
      histTauLeadPT->Fill(taun_pt);
      histTauNLPT->Fill(taup_pt);
      histTauNLeadEta->Fill(taup_eta);
      histTauLeadEta->Fill(taun_eta);
    }
    
  }
  TFile f("bsm_hists.root","RECREATE");
  // Show resulting histograms
  histTauPT->Write();
  histTauLeadPT->Write();
  histTauNLPT->Write();
  histTauLeadEta->Write();
  histTauNLeadEta->Write();
  histTauEta->Write();
  histTauPhi->Write();
  histTauRapidity->Write();
  histDiTauMass->Write();
  histDiTauRapidity->Write();
  histDiTauPt->Write();
  
   

// Closing the ROOT file.
   f.Close();
}
