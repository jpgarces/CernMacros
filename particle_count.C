/*
Prints complete input particle arborescence for the first 10 events. Useful for debugging purposes.
root -l examples/Example5.C'("delphes_output.root")'
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

void particle_count(const char *inputFile,Int_t pid)
{
  gSystem->Load("libDelphes");

  //FILE *f = fopen("test2.txt","w");
  TChain chain("Delphes");
  chain.Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();
  Int_t it, mom_id, tpart_count=0, part_count=0, t_sm_part=0;

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

for(Int_t entry = 0; entry < numberOfEntries; ++entry){
  //int entry = 333;
    treeReader->ReadEntry(entry);

    //if(entry>100) break;
    
    for(Int_t i=0; i < branchParticle->GetEntriesFast(); i++)
    {
     GenParticle *gen = (GenParticle*) branchParticle->At(i);
     //cout << "N: " << i <<  ", PID: " << gen->PID << ", M1: " << gen->M1 << ", M2: " << gen->M2 << ", D1:" << gen->D1 << ", D2: " << gen->D2 << endl;
     //if(gen->PID==pid&&gen->Status==1){
     if(gen->PID==pid){
       part_count+=1;
       it=0;
       while (it<100){
	 if(gen->M1==-1&&gen->M2==-1){
	   break;
	 }
	  mom_id=gen->M1;
	  GenParticle *mom = (GenParticle*) branchParticle->At(mom_id);
	  if(mom->PID==15||mom->PID==-15){
	    if(it==0){
	      tpart_count+=1;
              //fprintf(f,"%i  %i\n",gen->M1,entry);
	    }else{
	      t_sm_part+=1;
	    }
	    break;
	  }
	  gen = (GenParticle*) branchParticle->At(mom_id);
	  it+=1;
       }
      }
    }
  }
  cout << "Total number of " << pid << " connected to tau decay: " << tpart_count << endl;
  cout << "Total number of " << pid << " connected to tau decay through an intermediate particle: " << t_sm_part << endl;
  cout << "Total number of " << pid << " in sample: " << part_count << endl;
  cout << "Total number of events: " << numberOfEntries << endl;
  //fclose(f);
}
