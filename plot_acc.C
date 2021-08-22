void plot_acc(){

 TFile *f1 = TFile::Open("acceptance_pip_sm.root");
 TFile *f2 = TFile::Open("acceptance_pip_bsm.root");
 //TFile *f3 = TFile::Open("acceptance_bkg.root");
 TCanvas *c1 = new TCanvas();
 TLegend *legend = new TLegend(0.65,0.7,0.85,0.85);
 TLine *l = new TLine(0.0,1.0,12.0,1.0);

 TH1F *hist_acc_sm = (TH1F*) f1->Get("hist_acc");
 TH1F *hist_acc_all_sm = (TH1F*) f1->Get("hist_acc_all");
 TH1F *hist_acc_rec_all_sm = (TH1F*) f1->Get("hist_acc_rec_all");
 TH1F *hist_acc_gen_all_sm = (TH1F*) f1->Get("hist_acc_gen_all");

 TH1F *hist_acc_bsm = (TH1F*) f2->Get("hist_acc");
 TH1F *hist_acc_all_bsm = (TH1F*) f2->Get("hist_acc_all");
 TH1F *hist_acc_rec_all_bsm = (TH1F*) f2->Get("hist_acc_rec_all");
 TH1F *hist_acc_gen_all_bsm = (TH1F*) f2->Get("hist_acc_gen_all");

 TH1F *hist_Rec_sm = (TH1F*) f1->Get("hist_Rec");
 TH1F *hist_Gen_sm = (TH1F*) f1->Get("hist_Gen");

 TH1F *hist_Rec_bsm = (TH1F*) f2->Get("hist_Rec");
 TH1F *hist_Gen_bsm = (TH1F*) f2->Get("hist_Gen");
 
 legend->AddEntry(hist_acc_sm,"Rec/Gen (Eta cut) SM");
 //legend->AddEntry(hist_acc_all_sm,"Rec/Gen (no cuts) SM");
 //legend->AddEntry(hist_acc_rec_all,"Rec_cuts/Rec_no_cuts SM");
 //legend->AddEntry(hist_acc_gen_all,"Gen_cuts/Gen_no_cuts SM");

 legend->AddEntry(hist_acc_bsm,"Rec/Gen (Eta cut) BSM");
 //legend->AddEntry(hist_acc_all_bsm,"Rec/Gen (no cuts) BSM");

 legend->AddEntry(hist_Rec_sm,"Positive Pion P_{T} Rec SM");
 legend->AddEntry(hist_Gen_sm,"Positive Pion P_{T} Gen SM");
 legend->AddEntry(hist_Rec_bsm,"Positive Pion P_{T} Rec BSM");
 legend->AddEntry(hist_Gen_bsm,"Positive Pion P_{T} Gen BSM");
 
 //TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
 //TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.25);

 //pad1->Draw();
 //pad2->Draw();
 
 /*pad2->cd();
 l->SetLineStyle(9);
 l->SetLineWidth(1);
 //hist_sm_bsm_ratio->Divide(tauNL_pt_sm_1ch,tauNL_pt_bsm_1ch,1,1,"B");
 hist_sm_bsm_ratio->Divide(hist_pim_angles_sm_1ch,hist_pim_angles_bsm_1ch);
 hist_sm_bsm_ratio->GetXaxis()->SetTitle("Angle (degrees)");
 hist_sm_bsm_ratio->SetTitle("");
 hist_sm_bsm_ratio->GetXaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetYaxis()->CenterTitle(kTRUE);
 hist_sm_bsm_ratio->GetXaxis()->SetTitleSize(0.15);
 hist_sm_bsm_ratio->GetXaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetLabelSize(0.1);
 hist_sm_bsm_ratio->GetYaxis()->SetNdivisions(5);
 hist_sm_bsm_ratio->SetMarkerStyle(21);
 hist_sm_bsm_ratio->SetMarkerSize(0.5);
 hist_sm_bsm_ratio->SetStats(kFALSE);
 hist_sm_bsm_ratio->Draw("P");
 l->Draw();*/
 
 //pad1->cd();
 hist_acc_sm->SetMarkerStyle(21);
 hist_acc_sm->SetMarkerSize(1);
 hist_acc_sm->SetMarkerColor(1);
 hist_acc_sm->Draw();
 gStyle->SetOptStat(kFALSE);
 /*TPaveStats *stats1 =(TPaveStats*)c1->GetPrimitive("stats");
 stats1->SetName("SM");
 stats1->SetY1NDC(.05);
 stats1->SetY2NDC(.3);
 stats1->SetTextColor(1);
 stats1->SetTextSize(0.03);*/
 hist_acc_sm->GetXaxis()->SetTitle("P_{T} (GeV)");
 //hist_acc_sm->GetXaxis()->SetNdivisions(5);
 hist_acc_sm->GetYaxis()->SetTitle("Counts");
 hist_acc_sm->SetTitle("Positive Pion efficiency");
 hist_acc_sm->GetXaxis()->CenterTitle(kTRUE);
 hist_acc_sm->GetYaxis()->CenterTitle(kTRUE);
 /*hist_acc_all_sm->SetMarkerStyle(21);
 hist_acc_all_sm->SetMarkerSize(1);
 hist_acc_all_sm->SetMarkerColor(2);
 hist_acc_all_sm->Draw("SAMES");
 gStyle->SetOptStat(10);
 TPaveStats *stats2 =(TPaveStats*)c1->GetPrimitive("stats");
 stats2->SetName("BSM");
 stats2->SetY1NDC(.05);
 stats2->SetY2NDC(.3);
 stats2->SetTextColor(2);
 stats2->SetTextSize(0.03);*/

 hist_acc_bsm->SetMarkerStyle(21);
 hist_acc_bsm->SetMarkerSize(1);
 hist_acc_bsm->SetMarkerColor(2);
 hist_acc_bsm->Draw("SAME");
 gStyle->SetOptStat(kFALSE);
 /*TPaveStats *stats1_bsm =(TPaveStats*)c1->GetPrimitive("stats");
 stats1_bsm->SetName("SM");
 stats1_bsm->SetY1NDC(.05);
 stats1_bsm->SetY2NDC(.3);
 stats1_bsm->SetTextColor(2);
 stats1_bsm->SetTextSize(0.03);*/
 /*hist_acc_all_bsm->SetMarkerStyle(21);
 hist_acc_all_bsm->SetMarkerSize(1);
 hist_acc_all_bsm->SetMarkerColor(4);
 hist_acc_all_bsm->Draw("SAMES");
 gStyle->SetOptStat(10);
 TPaveStats *stats2_bsm =(TPaveStats*)c1->GetPrimitive("stats");
 stats2_bsm->SetName("BSM");
 stats2_bsm->SetY1NDC(.05);
 stats2_bsm->SetY2NDC(.3);
 stats2_bsm->SetTextColor(4);
 stats2_bsm->SetTextSize(0.03);*/
 
 legend->Draw();
 l->Draw();

 Float_t rightmax = 1.1*hist_Gen_sm->GetMaximum();
 Float_t scale = gPad -> GetUymax()/rightmax;
 
 hist_Gen_sm->Scale(scale);
 hist_Gen_sm->SetLineColor(1);
 hist_Gen_sm->SetLineStyle(2);
 hist_Gen_sm->SetLineWidth(3);
 //gPad->SetLogy();
 hist_Gen_sm->Draw("HISTSAME");
 hist_Rec_sm->Scale(scale);
 hist_Rec_sm->SetLineColor(1);
 hist_Rec_sm->SetLineWidth(3);
 //gPad->SetLogy();
 hist_Rec_sm->Draw("HISTSAME");
 hist_Gen_bsm->Scale(scale);
 hist_Gen_bsm->SetLineColor(2);
 hist_Gen_bsm->SetLineStyle(2);
 hist_Gen_bsm->SetLineWidth(3);
 hist_Gen_bsm->Draw("HISTSAME");
 hist_Rec_bsm->Scale(scale);
 hist_Rec_bsm->SetLineColor(2);
 hist_Rec_bsm->SetLineWidth(3);
 hist_Rec_bsm->Draw("HISTSAME");
 TGaxis *A2 = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
 //A2->SetTitle("Counts Positive Pions P_{T}");
 A2->SetMaxDigits(3);
 A2->Draw();
}
