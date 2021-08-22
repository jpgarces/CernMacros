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

void check_RecGen(Int_t pid)
{
  //FILE *f1 = fopen("muon_vcoord_gen.txt","w");
  //FILE *f2 = fopen("muon_vcoord_rec.txt","w");
  //FILE *f3 = fopen("muon_vcoord_track.txt","w");
  gSystem->Load("libDelphes");
  gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");

  TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events.root";

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  /*TFile *f = new TFile("/home/juan/bsm_minv0p_pt1_delphes_events.root");

    TTree *Delphes = (TTree*) f->Get("Delphes");*/

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

  for(Int_t entry = 0; entry < numberOfEntries; ++entry){
   //if (entry>20000) break;
    treeReader->ReadEntry(entry);
    for(Int_t i=0; i < branchParticle->GetEntriesFast(); i++){
     GenParticle *gen = (GenParticle*) branchParticle->At(i);
     if((gen->PID==pid)&&gen->Status==1&&gen->PT>pt_cut&&(gen->Eta)<eta_cut&&gen->Eta>-eta_cut){
     //if(gen->PID==pid&&gen->Status==1&&gen->PT>pt_cut){
       gen_count+=1;
       //fprintf(f1,"%f, %f, %f, %f\n",gen->T,gen->X,gen->Y,gen->Z);
     }
    }
    for(Int_t j=0; j < branchMuon->GetEntriesFast(); j++){
     Muon *muon_rec = (Muon*) branchMuon->At(j);
     GenParticle *gen_p= (GenParticle*) muon_rec->Particle.GetObject();
     //if(gen_p->PID!=13&&gen_p->PID!=-13){
     //cout << gen_p->PID << endl;
       //}
     // fprintf(f2,"%f, %f, %f, %f\n",gen_p->T,gen_p->X,gen_p->Y,gen_p->Z);
     if(gen_p->PID==pid&&gen_p->PT>10&&gen_p->Eta>-2.5&&gen_p->Eta<2.5&&gen_p->Status==1){
       rec_count+=1;
     }
    }
    for(Int_t k=0; k < branchTrack->GetEntriesFast(); k++){
     Track *muon_track = (Track*) branchTrack->At(k);
     GenParticle *gen_track= (GenParticle*) muon_track->Particle.GetObject();
     if((muon_track->PID==pid)&&muon_track->PT>pt_cut&&(muon_track->Eta)<eta_cut&&muon_track->Eta>-eta_cut){
       rec_count_track+=1;
       //fprintf(f3,"%f, %f, %f, %f\n",gen_track->T,gen_track->X,gen_track->Y,gen_track->Z);
     }
    }
   }
 cout<< "Number of generated muons: " << gen_count << endl;
 cout << "Number of reconstructed muons (Muon branch): " << rec_count << endl;
 cout << "Number of reconstructed muons (Track branch): " << rec_count_track << endl;
 /*fclose(f1);
 fclose(f2);
 fclose(f3);*/
}
