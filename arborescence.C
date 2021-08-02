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

void arborescence(const char *inputFile)
{
  gSystem->Load("libDelphes");

  // Create chain of root trees
  TChain chain("Delphes");
  chain.Add(inputFile);

  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();

  // Get pointers to branches used in this analysis
  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  Int_t tmuon_count=0, muon_count=0, it, mom_id;

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);

    //if(entry>100) break;

    // loop over all input particles in the event
    for(Int_t i=0; i < branchParticle->GetEntriesFast(); i++)
    {
     GenParticle *gen = (GenParticle*) branchParticle->At(i);
     if (gen->PID==13&&gen->Status==1){
       //cout<<"" <<endl;
       //cout<<"--------- New Event with Muon---------" <<endl;
       //cout<<"" <<endl;
       muon_count+=1;
       it=0;
       while (gen->M1>0&&it<15){
          GenParticle *mom = (GenParticle*) branchParticle->At(gen->M1);
	  mom_id=gen->M1;
	  if(mom->PID==15){
	    tmuon_count+=1;
	    break;
	  }
	    //cout<< "Muon" << endl;
            //cout<<"N: "<<i<<", St: "<<gen->Status<<", PID: "<<gen->PID<<", M1: "<<gen->M1<<", M2: "<<gen->M2<<", D1: "<<gen->D1<<", D2: "<<gen->D2<<endl;
	    //cout << "Mother 1" << endl;
	    //cout<<"N: "<<i<<", St: "<<mom->Status<<", PID: "<<mom->PID<<", M1: "<<mom->M1<<", M2: "<<mom->M2<<", D1: "<<mom->D1<<", D2: "<<mom->D2<<endl;
	    //if (mom->M1>0){
	    //GenParticle *g_mom = (GenParticle*) branchParticle->At(mom->M1);
	      //cout << "Mother 1" << endl;
	      //cout<<"N: "<<i<<", St: "<<mom->Status<<", PID: "<<mom->PID<<", M1: "<<mom->M1<<", M2: "<<mom->M2<<", D1: "<<mom->D1<<", D2: "<<mom->D2<<endl;
	      //cout << "Grand Mother 1" << endl;
	      // cout<<"N: "<<i<<", St: "<<g_mom->Status<<", PID: "<<g_mom->PID<<", M1: "<<g_mom->M1<<", M2: "<<g_mom->M2<<", D1: "<<g_mom->D1<<", D2: "<<g_mom->D2<<endl;
	    // }
	    //if (mom->M2>0){
	    //GenParticle *g_mom = (GenParticle*) branchParticle->At(mom->M2);
	      //cout << "Mother 2" << endl;
	      //cout<<"N: "<<i<<", St: "<<mom->Status<<", PID: "<<mom->PID<<", M1: "<<mom->M1<<", M2: "<<mom->M2<<", D1: "<<mom->D1<<", D2: "<<mom->D2<<endl;
	      //cout << "Grand Mother 2" << endl;
	      //cout<<"N: "<<i<<", St: "<<g_mom->Status<<", PID: "<<g_mom->PID<<", M1: "<<g_mom->M1<<", M2: "<<g_mom->M2<<", D1: "<<g_mom->D1<<", D2: "<<g_mom->D2<<endl;
	  cout << mom->PID << endl;
	  GenParticle *gen = (GenParticle*) branchParticle->At(mom_id);
	  it++;
	  //cout<<gen->M1<<endl;
       }
       cout << it << endl;
	  //if (gen->M2>0){
	  //GenParticle *mom = (GenParticle*) branchParticle->At(gen->M2);
	  //if(mom->PID!=15){
	    //cout << "Mother 2" << endl;
	    //cout<<"N: "<<i<<", St: "<<mom->Status<<", PID: "<<mom->PID<<", M1: "<<mom->M1<<", M2: "<<mom->M2<<", D1: "<<mom->D1<<", D2: "<<mom->D2<<endl;
	  //}
      } 
    }
  }
  cout << "Total number of muons connected to tau decay: " << tmuon_count << endl;
  cout << "Total number of muons in sample: " << muon_count << endl;
  cout << "Total number of events: " << numberOfEntries << endl;
  
}
