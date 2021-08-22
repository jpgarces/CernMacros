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

void particle_history_bkg(const char *inputFile, Int_t pid)
{
  gSystem->Load("libDelphes");

  TChain chain("Delphes");
  chain.Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();
  Int_t it, mom_id, tmuon_count=0, muon_count=0, t_sm_muon=0,n,m;

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

 for(Int_t entry = 0; entry < numberOfEntries; ++entry){
   if (entry>20000) break;
    //int entry = 333;
    treeReader->ReadEntry(entry);
    cout << "------------ New Event -----------------"<< endl;
    for(Int_t i=0; i < branchParticle->GetEntriesFast(); i++)
    {
     GenParticle *gen = (GenParticle*) branchParticle->At(i);
     //if(gen->PID==pid&&gen->Status==1){
      if(gen->PID==pid){
       it=0;
       Bool_t flag=0;
       cout << "------------ New Decay -----------------"<< endl;
       n=0;
       m=0;
       while (it<100){
	 if(gen->M1==-1&&gen->M2==-1){
	   cout<<"PID: "<<gen->PID<<", M1: "<<gen->M1<<", M2: "<<gen->M2<< ", D2: " << gen->D2<<endl;
	   break;
	 }
          GenParticle *mom = (GenParticle*) branchParticle->At(gen->M1);
	  if(mom->PID==22){
	    n+=1;
	    m+=1;
	    if(it==0){
	      if(n==1){
	        cout<<"------- Decay directly from photon ------"<<endl;
		n+=1;
	      }
	    }else {
	      if(m==1){
	        cout<<"------- Decay indirectly from photon (intermediate decays present) ------"<<endl;
	      }
	    }
	  }
	  mom_id=gen->M1;
	  cout<<"PID: "<<gen->PID<<", M1: "<<gen->M1<<", M2: "<<gen->M2<< ", D1:" << gen->D1 << ", D2: " << gen->D2 << endl;
          gen = (GenParticle*) branchParticle->At(mom_id);
	  it+=1;
       }
      }
    }
   }
}
