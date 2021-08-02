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

void track_diff(const char *inputFile)
{
  gSystem->Load("libDelphes");

  //FILE *f = fopen("diff_muons.txt","w");
  TChain chain("Delphes");
  chain.Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();
  Int_t it, mom_id, tmuon_count=0, muon_count=0, t_sm_muon=0;

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    treeReader->ReadEntry(entry);
    for(Int_t i=0; i < branchParticle->GetEntriesFast(); i++)
    {
     GenParticle *gen = (GenParticle*) branchParticle->At(i);
     if(gen->PID==13&&gen->Status==1){
       it=0;
       Bool_t flag=0;
       while (it<100){
	 if(gen->M1==-1&&gen->M2==-1){
	   if(flag){
	     cout<<"PID: "<<gen->PID<<", M1: "<<gen->M1<<", M2: "<<gen->M2<<endl;
	   }
	   break;
	 }
          GenParticle *mom = (GenParticle*) branchParticle->At(gen->M1);
	  mom_id=gen->M1;
	  if(mom->PID==15){
	    if((gen->M1==30&&entry==333)||(gen->M1==136&&entry==2979)||(gen->M1==193&&entry==12715)||(gen->M1==188&&entry==13073)||(gen->M1==159&&entry==17233)||(gen->M1==75&&entry==18993)||(gen->M1==253&&entry==21403)||(gen->M1==271&&entry==24358)||(gen->M1==54&&entry==28991)||(gen->M1==301&&entry==31804)||(gen->M1==75&&entry==34545)||(gen->M1==237&&entry==35113)||(gen->M1==308&&entry==45726)||(gen->M1==249&&entry==45855)||(gen->M1==210&&entry==47984)||(gen->M1==297&&entry==49012)){
	    if (it==0){
	      flag=1;
	      //cout << "------------ MUON -----------------"<< endl;
	      //fprintf(f,"------------ MUON -----------------\n");
	      //fprintf(f,"%i  %i\n",gen->M1,entry);
	    }
	   }
	  }
	  if(flag){
	    fprintf(f,"PID: %i, M1: %i, M2: %i\n",gen->PID,gen->M1,gen->M2);
	    cout<<"PID: "<<gen->PID<<", M1: "<<gen->M1<<", M2: "<<gen->M2<<endl;
	    }
          gen = (GenParticle*) branchParticle->At(mom_id);
	  it+=1;
       }
       
      }
    
    }
  }
    //fclose(f);
}
