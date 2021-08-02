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

void particle_history(const char *inputFile, Int_t pid)
{
  FILE *f = fopen("kpdecays.txt","w");
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
    //cout << "------------ New Event -----------------"<< endl;
    fprintf(f,"------------ New Event -----------------\n");
    for(Int_t i=0; i < branchParticle->GetEntriesFast(); i++)
    {
     GenParticle *gen = (GenParticle*) branchParticle->At(i);
     //if(gen->PID==pid&&gen->Status==1){
      if(gen->PID==pid){
       it=0;
       Bool_t flag=0;
       //cout << "------------ New Decay -----------------"<< endl;
       fprintf(f,"------------ New Decay -----------------\n");
       n=0;
       m=0;
       while (it<100){
	 if(gen->M1==-1&&gen->M2==-1){
	   //cout<<"PID: "<<gen->PID<<", M1: "<<gen->M1<<", M2: "<<gen->M2<< ", D2: " << gen->D2<<endl;
	   fprintf(f,"PID: %i, M1: %i, M2: %i, D2: %i\n",gen->PID,gen->M1,gen->M2,gen->D2);
	   break;
	 }
          GenParticle *mom = (GenParticle*) branchParticle->At(gen->M1);
	  if(mom->PID==15||mom->PID==-15){
	    n+=1;
	    m+=1;
	    if(it==0){
	      if(n==1){
	        //cout<<"------- Decay directly from Tau ------"<<endl;
		fprintf(f,"------- Decay directly from Tau ------\n");
		n+=1;
	      }
	    }else {
	      if(m==1){
	        //cout<<"------- Decay indirectly from Tau (intermediate decays present) ------"<<endl;
		fprintf(f,"------- Decay indirectly from Tau (intermediate decays present) ------\n");
		m+=1;
	      }
	    }
	  }
	  mom_id=gen->M1;
	  //cout<<"PID: "<<gen->PID<<", M1: "<<gen->M1<<", M2: "<<gen->M2<< ", D1:" << gen->D1 << ", D2: " << gen->D2 << endl;
	  fprintf(f,"PID: %i, M1: %i, M2: %i, D2: %i\n",gen->PID,gen->M1,gen->M2,gen->D2);
          gen = (GenParticle*) branchParticle->At(mom_id);
	  it+=1;
       }
      }
    }
   }
 fclose(f);
}
