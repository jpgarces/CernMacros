#ifdef __CLING__
R__LOAD_LIBRARY(/home/juan/Delphes-3.5.0/libDelphes.so)

#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#include "external/ExRootAnalysis/ExRootResult.h"
   
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


//------------------------------------------------------------------------------

void acceptance()
{
      gSystem->Load("/home/juan/MG5_aMC_v2.6.7/MG5_aMC_v2_6_7/ExRootAnalysis/libExRootAnalysis.so");
      gSystem->Load("libDelphes");
  
      //TString inputFile = "/home/juan/bsm_minv0p_pt1_delphes_events_NNL.root";
  
      TString inputFile = "/home/juan/sm_UFO_minv0p_pt1_NNLO_delphes_events.root";

      //TString inputFile = "/home/juan/sm_bkg_minv0p_pt1_NNLO_delphes_events.root";

      TFile *outf = new TFile("acceptance_mu_bsm.root","RECREATE");

      TChain *chain = new TChain("Delphes");
      chain->Add(inputFile);

      ExRootTreeReader *treeReader = new ExRootTreeReader(chain);

      Long64_t allEntries = treeReader->GetEntries();

      TClonesArray *branchParticle = treeReader->UseBranch("Particle");
      TClonesArray *branchTrack = treeReader->UseBranch("Track");

      TH1F *hist_Rec = new TH1F("hist_Rec", "Reconstructed charged particles", 20, 0.0, 12.0);
	TH1F *hist_Gen = new TH1F("hist_Gen", "Generated charged particles (with cuts)", 20, 0.0, 12.0);
	TH1F *hist_Rec_all = new TH1F("hist_Rec_all", "All charged particles", 20, 0.0, 12.0);
	TH1F *hist_Gen_all = new TH1F("hist_Gen_all", "All generated charged particles", 20, 0.0, 12.0);

	TH1F *hist_acc = new TH1F("hist_acc", "Rec/Gen (with cuts)", 20, 0.0, 12.0);
	TH1F *hist_acc_all = new TH1F("hist_acc_all", "Rec/Gen (no cuts)", 20, 0.0, 12.0);
	TH1F *hist_acc_rec_all = new TH1F("hist_acc_rec_all", "Rec_cuts/Rec_no_cuts", 20, 0.0, 12.0);
	TH1F *hist_acc_gen_all = new TH1F("hist_acc_gen_all", "Gen_cuts/Gen_no_cuts", 20, 0.0, 12.0);

      Double_t cut1_rec=0, cut2_rec=0, cut3_rec=0, cut4_rec=0, cut5_rec=0, cut6_rec=0, cut7_rec=0, cut8_rec=0;

      Double_t cut1_gen=0, cut2_gen=0, cut3_gen=0, cut4_gen=0, cut5_gen=0, cut6_gen=0, cut7_gen=0, cut8_gen=0;

	//Double_t minPtAcc = 1.0;	// 1 GeV
	//Double_t maxCtAcc = 1.0;	// 45 degrees

	// Loop over all events
	for (Int_t entry = 0; entry < allEntries; ++entry)
	{
		treeReader->ReadEntry(entry);

		// If event contains at least 1 track
		if (branchTrack->GetEntries() > 0)
		{
			// Loop on tracks
			for (Int_t it = 0; it < branchTrack->GetEntries(); it++)
			{
			      Track* trk = (Track*)branchTrack->At(it);

			        if (trk->PID==13){
				    hist_Rec_all->Fill(trk->PT);
				}
	        
				if ((TMath::Abs(trk->Eta)<2.5)&&trk->PID==13)hist_Rec->Fill(trk->PT); // pt for central tracks
				//if (trk->PID==211){
				/*if (trk->PT<=0.1){
				  cut1_rec+=1;
				}else if(TMath::Abs(trk->Eta)<=1.5&&trk->PT>0.1&&trk->PT<=1.0){
				  cut2_rec+=1;
				  //}else if(TMath::Abs(trk->Eta)<=1.5&&trk->PT>1.0&&trk->PT<=100){
				  // cut3_rec+=1;
				}else if(TMath::Abs(trk->Eta)<=1.5&&trk->PT>1.0){
				  cut4_rec+=1;
				}else if(TMath::Abs(trk->Eta)>1.5&&TMath::Abs(trk->Eta)<=2.5&&trk->PT>0.1&&trk->PT<=1.0){
				  cut5_rec+=1;
				  //}else if(TMath::Abs(trk->Eta)>1.5&&TMath::Abs(trk->Eta)<=2.5&&trk->PT>1.0&&trk->PT<=100){
				  // cut6_rec+=1;
				}else if(TMath::Abs(trk->Eta)>1.5&&TMath::Abs(trk->Eta)<=2.5&&trk->PT>1.0){
				  cut7_rec+=1;
				}else if(TMath::Abs(trk->Eta)>2.5){
				  cut8_rec+=1;
				  }*/
				/*if (trk->PT<=10.0){
				  cut1_rec+=1;
				}else if(TMath::Abs(trk->Eta)<=1.5&&trk->PT>10.0){
				  cut2_rec+=1;
				}else if(TMath::Abs(trk->Eta)>1.5&&TMath::Abs(trk->Eta)<=2.5&&trk->PT>10.0){
				  cut3_rec+=1;
				}else if(TMath::Abs(trk->Eta)>2.5){
				  cut4_rec+=1;
				  }*/
				//}		
      			}  

			// If event contains at least 1 generated charged
			//
			if (branchParticle->GetEntries() > 0)
			{
				// Loop on generated particles
				for (Int_t it = 0; it < branchParticle->GetEntries(); it++) {
				     GenParticle* gpart = (GenParticle*)branchParticle->At(it);
					//
					// Plot charged particle parameters
					// Only final state particles (Status = 1)
				     if (gpart->Status==1&&gpart->PID==13) {
					  hist_Gen_all->Fill(gpart->PT);
					  if (TMath::Abs(gpart->Eta)<2.5)hist_Gen->Fill(gpart->PT); 
				       /*if (gpart->PT<=0.1){
				           cut1_gen+=1;
				        }else if(TMath::Abs(gpart->Eta)<=1.5&&gpart->PT>0.1&&gpart->PT<=1.0){
				           cut2_gen+=1;
				  //        }else if(TMath::Abs(gpart->Eta)<=1.5&&gpart->PT>1.0&&gpart->PT<=100){
				  //        cut3_gen+=1;
				        }else if(TMath::Abs(gpart->Eta)<=1.5&&gpart->PT>1.0){
				           cut4_gen+=1;
				        }else if(TMath::Abs(gpart->Eta)>1.5&&TMath::Abs(gpart->Eta)<=2.5&&gpart->PT>0.1&&gpart->PT<=1.0){
				           cut5_gen+=1;
				  //        }else if(TMath::Abs(gpart->Eta)>1.5&&TMath::Abs(gpart->Eta)<=2.5&&gpart->PT>1.0&&gpart->PT<=100){
				  //        cut6_gen+=1;
				        }else if(TMath::Abs(gpart->Eta)>1.5&&TMath::Abs(gpart->Eta)<=2.5&&gpart->PT>1.0){
				           cut7_gen+=1;
				        }else if(TMath::Abs(gpart->Eta)>2.5){
				           cut8_gen+=1;
					   }*/
				       /*if (gpart->PT<=10.0){
				        cut1_gen+=1;
				       }else if(TMath::Abs(gpart->Eta)<=1.5&&gpart->PT>10.0){
				        cut2_gen+=1;
				       }else if(TMath::Abs(gpart->Eta)>1.5&&TMath::Abs(gpart->Eta)<=2.5&&gpart->PT>10.0){
				        cut3_gen+=1;
				       }else if(TMath::Abs(gpart->Eta)>2.5){
				        cut4_gen+=1;
					}*/
				    }
				}
			}
		}
	}
	// Acceptance plots
	hist_acc->Divide(hist_Rec,hist_Gen,1,1,"B");
	hist_acc_all->Divide(hist_Rec_all,hist_Gen_all,1,1,"B");
	hist_acc_rec_all->Divide(hist_Rec,hist_Rec_all,1,1,"B");
	hist_acc_gen_all->Divide(hist_Gen,hist_Gen_all,1,1,"B");
	outf->Write();
        outf->Close();
	/*cout <<       cut1_rec/cut1_gen << endl;
	cout << cut2_rec/cut2_gen << endl;
	cout << cut3_rec/cut3_gen << endl;
	cout << cut4_rec/cut4_gen << endl;*/
	/*cout << cut5_rec/cut5_gen << endl;	
	//cout << cut6_rec/cut6_gen << endl;
	cout << cut7_rec/cut7_gen << endl;	
	cout << cut8_rec/cut8_gen << endl;*/
}
