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

void Example5(const char *inputFile)
{
  gSystem->Load("libDelphes");

  // Create chain of root trees
  TChain chain("Delphes");
  chain.Add(inputFile);

  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();
  Int_t it, mom_id;

  // Get pointers to branches used in this analysis
  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);

    if(entry>1000) break;

    cout<<"" <<endl;
    cout<<"--------- New Event ---------" <<endl;
    cout<<"" <<endl;

    // loop over all input particles in the event
    for(Int_t i=0; i < branchParticle->GetEntriesFast(); i++)
    {
     GenParticle *gen = (GenParticle*) branchParticle->At(i);
     if(gen->PID==13&&gen->Status==1){
     it=0;
     cout << "------------ MUON -----------------"<< endl;
       while (gen->M1!=-1&&it<15){
          GenParticle *mom = (GenParticle*) branchParticle->At(gen->M1);
	  mom_id=gen->M1;
	  // if(mom->PID==15){
	    //tmuon_count+=1;
	    //break;
	    //}
          cout<<", St: "<<gen->Status<<", PID: "<<gen->PID<<", M1: "<<gen->M1<<", M2: "<<gen->M2<<", D1: "<<gen->D1<<", D2: "<<gen->D2<<endl;
	  gen = (GenParticle*) branchParticle->At(mom_id);
	  it++;
	  cout<<", St: "<<gen->Status<<", PID: "<<gen->PID<<", M1: "<<gen->M1<<", M2: "<<gen->M2<<", D1: "<<gen->D1<<", D2: "<<gen->D2<<endl;
	  //cout<<gen->M1<<endl;
       }
       cout<<", St: "<<gen->Status<<", PID: "<<gen->PID<<", M1: "<<gen->M1<<", M2: "<<gen->M2<<", D1: "<<gen->D1<<", D2: "<<gen->D2<<endl;
       cout << it << endl;
     }
     /*else{
       cout<<"N: "<<i<<", St: "<<gen->Status<<", PID: "<<gen->PID<<", M1: "<<gen->M1<<", M2: "<<gen->M2<<", D1: "<<gen->D1<<", D2: "<<gen->D2<<endl;
      }*/
    }
  }
}
