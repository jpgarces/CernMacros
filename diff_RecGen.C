/*
Prints complete input particle arborescence for the first 10 events. Useful for debugging purposes.
root -l examples/Example5.C'("delphes_output.root",PID)'
*/

#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#include "external/ExRootAnalysis/ExRootResult.h"
#else
class ExRootTreeReader;
class ExRootResult;
#endif


//------------------------------------------------------------------------------

void diff_RecGen(Int_t pid)
{
  gSystem->Load("libDelphes");
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");

  TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);
  Long64_t numberOfEntries = treeReader->GetEntries();
  Int_t it, mom_id, tmuon_count=0, muon_count=0, t_sm_muon=0,n,m;

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");
  TClonesArray *branchTrack = treeReader->UseBranch("Track");
  TClonesArray *branchMuon = treeReader->UseBranch("Muon");
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");

  Int_t rec_count = 0, rec_count_track=0;

  Double_t pt_cut=10.0;
  Double_t eta_cut=2.5;
  Int_t gen_count=0;
  Int_t j, k, diff=0, diff_track=0;

  for(Int_t entry = 0; entry < numberOfEntries; ++entry){
   //if (entry>20000) break;
    treeReader->ReadEntry(entry);
    j=0;
    k=0;
    for(Int_t i=0; i < branchParticle->GetEntriesFast(); i++){
     GenParticle *gen = (GenParticle*) branchParticle->At(i);
     if(gen->PID==pid&&gen->Status==1&&gen->PT>pt_cut&&(gen->Eta)<eta_cut&&gen->Eta>-eta_cut){
       gen_count+=1;
       if(j<branchMuon->GetEntriesFast()){
        Muon *muon_rec = (Muon*) branchMuon->At(j);
        GenParticle *gen_p= (GenParticle*) muon_rec->Particle.GetObject();
	if(gen_p->PID==pid){
	  rec_count+=1;
	  if(gen_p->X==gen->X&&gen_p->Y==gen->Y&&gen_p->Z==gen->Z){
	    //cout << "Entry: "<< entry << ", i: " << i << endl;
	    j+=1;
	  }
	  else{
	   diff+=1;
	   cout << "Entry: " << entry << ", i: " << i << ", j: " << j << endl;
	  }
	}
       }else{
	 diff+=1;
	 cout << "Entry: " << entry << ", i: " << i << ", j: " << j << endl;
       }
       /*if(k<branchTrack->GetEntriesFast()){
        Track *muon_track = (Track*) branchTrack->At(k);
        GenParticle *gen_track= (GenParticle*) muon_track->Particle.GetObject();
	//if(muon_track->PID==pid){
	//rec_count_track+=1;
	  if(gen_track->X==gen->X&&gen_track->Y==gen->Y&&gen_track->Z==gen->Z){
	  //cout << "Entry: "<< entry << ", i: " << i << endl;
	   k+=1;
	  }
	  else{
	   diff_track+=1;
	  }
	  //}
       }else{
	 diff_track+=1;
       }
       }*/
      }
    }
    /*for(Int_t k=0; k < branchTrack->GetEntriesFast(); k++){
     Track *muon_track = (Track*) branchTrack->At(k);
     GenParticle *gen_track= (GenParticle*) muon_track->Particle.GetObject();
     if((muon_track->PID==pid||muon_track->PID==-pid)&&muon_track->PT>pt_cut&&(muon_track->Eta)<eta_cut&&muon_track->Eta>-eta_cut){
       rec_count_track+=1;
     }
     }*/
 }
 cout<< "Number of generated (negative) muons: " << gen_count << endl;
 cout << "Number of reconstructed (negative) muons (Muon branch): " << rec_count << endl;
 cout << "Number of reconstructed (negative) muons (Track branch): " << rec_count_track << endl;
 cout << "Gen - Rec (Muon branch): " << diff << endl;
 cout << "Gen - Rec (Track branch): " << diff_track << endl;
}
