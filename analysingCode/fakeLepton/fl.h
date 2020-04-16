#include "TCanvas.h"
#include "TFile.h"
#include "TH2.h"
#include "TMath.h"
#include "TROOT.h"
#include "TString.h"
#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TTreeReaderValue.h>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "TTree.h"
using namespace std;

class histFill
{
	public:
		//TFile * fout;
		TTree * t;
		TH2D* h;
		//TH1F* h2;
		void setHist(void);
		void setCut(void);
		void readTree(TFile * inputfile);
		void fill(void);	
		double scf;

		//channel (muon or electron) and type (data or mc)
		TString type;
		TString channel;
		bool cut;	

		//branch
		double 	scalef;
		int 	nevent;
		int 	run;
		int 	ls;
		double 	theWeight;
		int 	lep;

		int 	jet1hf_orig;
		int 	jet1pf_orig;
		double  jet1pt_orig;
		double  jet1eta_orig;
		double  jet1phi_orig;
		double  jet1e_orig;
		double	jet1csv_orig;
		double 	jet1icsv_orig;
		double	drj1a_orig;
		double	drj1l_orig;

		int		jet2hf_orig;
		int 	jet2pf_orig;
		double  jet2pt_orig;
		double  jet2eta_orig;
		double  jet2phi_orig;
		double  jet2e_orig;
		double  jet2csv_orig;
		double  jet2icsv_orig;
		double  drj2a_orig;
		double  drj2l_orig;

		int		nlooseeles;
		int		nloosemus;
		int		ngoodeles;
		int		ngoodmus;

		double	ptlep1;
		double	etalep1;
		int		HLT_Ele1;
		int		HLT_Ele2;
		int		HLT_Mu1;
		int		HLT_Mu2;
		int		HLT_Mu3;

		double	lumiWeight;
		double	pileupWeight;
		double	MET_et;
		double	mtVlepJECnew;
	
		Long64_t entries;
 		Double_t LUMI=-35.857;

		int n_pt_bin;
		int n_eta_bin;

	private:
		clock_t startTime,endTime;


};

void histFill::setCut(void){
	if(channel == "muon") {
		cut = HLT_Mu2 == 1 &&lep == 13 &&ngoodmus == 1 &&ngoodeles == 0 &&mtVlepJECnew < 20 &&MET_et < 30 &&((jet1pt_orig > 20 && drj1l_orig > 0.3) || (jet2pt_orig > 20 && drj2l_orig > 0.3));
	}

	else {
		cut = HLT_Ele2 == 1 &&lep == 11 &&ngoodmus == 0 &&ngoodeles == 1 &&mtVlepJECnew < 20 &&MET_et < 30 &&((jet1pt_orig > 30 && drj1l_orig > 0.3) || (jet2pt_orig > 30 && drj2l_orig > 0.3))
	}
}

void histFill::setHist(void){
	cout<<channel<<"	"<<type<<endl;
	if(channel == "muon") {
		//cout<<"muon cut"<<endl;
		//-------hist bin
		n_pt_bin   = 3;
		n_eta_bin  = 5;
		double pt_bin[4]  = {25, 30, 40, 50};
		double eta_bin[6] = {0, 0.5, 1.0, 1.5, 2.0, 2.5};
		h = new TH2D( type, type ,n_eta_bin, eta_bin, n_pt_bin, pt_bin);
		//h2 = new TH1F("t","t",n_pt_bin,pt_bin);
	}

	else {
		//-------hist bin
		n_pt_bin   = 2;
		n_eta_bin  = 5;
		double pt_bin[3]  = {30, 40, 50};
		double eta_bin[6] = {0, 0.5, 1.0, 1.5, 2.0, 2.5};
		h = new TH2D( type, type ,n_eta_bin, eta_bin, n_pt_bin, pt_bin);
		//h2 = new TH1F("t","t",n_pt_bin,pt_bin);
	}
}

void histFill::readTree(TFile * inputfile){
	t = (TTree*)inputfile->Get("demo");
	t->SetBranchAddress("scalef",&scalef);
	t->SetBranchAddress("nevent",&nevent);
	t->SetBranchAddress("run",&run);
	t->SetBranchAddress("ls",&ls);
	t->SetBranchAddress("theWeight",&theWeight);
	t->SetBranchAddress("lep",&lep);
	t->SetBranchAddress("jet1hf_orig",&jet1hf_orig);
	t->SetBranchAddress("jet1pf_orig",&jet1pf_orig);
	t->SetBranchAddress("jet1pt_orig",&jet1pt_orig);
	t->SetBranchAddress("jet1eta_orig",&jet1eta_orig);
	t->SetBranchAddress("jet1phi_orig",&jet1phi_orig);
	t->SetBranchAddress("jet1e_orig",&jet1e_orig);
	t->SetBranchAddress("jet1csv_orig",&jet1csv_orig);
	t->SetBranchAddress("jet1icsv_orig",&jet1icsv_orig);
	t->SetBranchAddress("drj1a_orig",&drj1a_orig);
	t->SetBranchAddress("drj1l_orig",&drj1l_orig);
	t->SetBranchAddress("jet2hf_orig",&jet2hf_orig);
	t->SetBranchAddress("jet2pf_orig",&jet2pf_orig);
	t->SetBranchAddress("jet2pt_orig",&jet2pt_orig);
	t->SetBranchAddress("jet2eta_orig",&jet2eta_orig);
	t->SetBranchAddress("jet2phi_orig",&jet2phi_orig);
	t->SetBranchAddress("jet2e_orig",&jet2e_orig);
	t->SetBranchAddress("jet2csv_orig",&jet2csv_orig);
	t->SetBranchAddress("jet2icsv_orig",&jet2icsv_orig);
	t->SetBranchAddress("drj2a_orig",&drj2a_orig);
	t->SetBranchAddress("drj2l_orig",&drj2l_orig);

	t->SetBranchAddress("nlooseeles",&nlooseeles);
	t->SetBranchAddress("nloosemus",&nloosemus);
	t->SetBranchAddress("ngoodeles",&ngoodeles);
	t->SetBranchAddress("ngoodmus",&ngoodmus);
	t->SetBranchAddress("ptlep1",&ptlep1);
	t->SetBranchAddress("etalep1",&etalep1);
	t->SetBranchAddress("HLT_Ele1",&HLT_Ele1);
	t->SetBranchAddress("HLT_Ele2",&HLT_Ele2);
	t->SetBranchAddress("HLT_Mu1",&HLT_Mu1);
	t->SetBranchAddress("HLT_Mu2",&HLT_Mu2);
	t->SetBranchAddress("HLT_Mu3",&HLT_Mu3);

	t->SetBranchAddress("MET_et",&MET_et);
	t->SetBranchAddress("mtVlepJECnew",&mtVlepJECnew);

	t->SetBranchAddress("lumiWeight",&lumiWeight);
	t->SetBranchAddress("pileupWeight",&pileupWeight);

	entries	= t->GetEntries();

}

void histFill::fill(void){
	for(int i=0; i < entries; i++){
		//if(i>50000) break;

		if (i % 100 == 0) {
			cout << "Analyzing event " << i <<"  "<<setw(6)<<i*100./entries<<"%"<<"\r" <<flush;
		}

		t->GetEntry(i);
		if(type.Contains("data")) scf = 1;
		else scf = scalef * lumiWeight * pileupWeight;
		setCut();
		//cout << cut<<endl;
		if(cut){
			//cout<<i<<"   pass   "<<ptlep1<<" "<<etalep1<<endl;
			h->Fill(fabs(etalep1), ptlep1, scf);
		//	h2->Fill(ptlep1);
		}
		//cout<< i <<" "<<ptlep1<<endl;
	}
	cout<<endl;
	//TFile* out = new TFile(type+".root", "RECREATE");
	//h2->Write();
	//h->Write();
	//out->Close();

}
