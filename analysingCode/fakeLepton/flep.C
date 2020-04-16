#include "fl.h"

int main(int argc, char** argv)
{
	//tight data
	histFill tight_data;
	tight_data.channel = argv[1];
	tight_data.type = "tight_data";
	tight_data.setHist();

	ifstream infile1("tight_data.txt");
	string buffer1;
	TString infilename1;

	while(getline (infile1, buffer1)){
		infilename1 = buffer1;
		TFile* file1 = TFile::Open(infilename1);

		tight_data.readTree(file1);
		tight_data.fill();
	}


	//control data
	histFill control_data;
	control_data.channel = argv[1];
	control_data.type = "control_data";
	control_data.setHist();

	ifstream infile2("control_data.txt");
	string buffer2;
	TString infilename2;

	while(getline (infile2, buffer2)){
		infilename2 = buffer2;
		TFile* file2 = TFile::Open(infilename2); 

		control_data.readTree(file2);
		control_data.fill();
	}

	//tight wz
 	histFill tight_wz;
	tight_wz.channel = argv[1];
	tight_wz.type = "tight_wz";
 	tight_wz.setHist();

	ifstream infile3("tight_wz.txt");
	string buffer3;
	TString infilename3;

	while(getline (infile3, buffer3)){
		infilename3 = buffer3;
		TFile* file3 = TFile::Open(infilename3);

		tight_wz.readTree(file3);
		tight_wz.fill();
	}

	//control wz
	histFill control_wz;
	control_wz.channel = argv[1];
	control_wz.type = "control_wz";
	control_wz.setHist();

	ifstream infile4("control_wz.txt");
	string buffer4;
	TString infilename4;

 	while(getline (infile4, buffer4)){
		infilename4 = buffer4;
 		TFile* file4 = TFile::Open(infilename4);

		control_wz.readTree(file4);
		control_wz.fill();
	}

	//calculate the fake rate
	TFile* output = new TFile("fake_"+tight_data.channel + ".root", "RECREATE");

	TH2D* fakerate;
 	TH2D* fenzi;
	TH2D* fenmu;
	TH2D* weight;

	fenzi = (TH2D*)tight_data.h->Clone();
	fenzi->Add(tight_wz.h,-35.857);
	fenzi->SetName("numerator");
	fenzi->SetTitle("numerator");

	fenmu = (TH2D*)tight_data.h->Clone();
	fenmu->Add(control_data.h);
	fenmu->Add(tight_wz.h,-35.857);
	fenmu->Add(control_wz.h,-35.857);
	fenmu->SetName("denominator");
	fenmu->SetTitle("denominator");

	fakerate = (TH2D*)fenzi->Clone();
	fakerate->Divide(fenmu);
	fakerate->SetName("fakerate");
	fakerate->GetXaxis()->SetTitle("|#eta|");
	fakerate->GetYaxis()->SetTitle("p_{T}(GeV)");
	fakerate->SetTitle("fake_rate");

	weight = (TH2D*)fakerate->Clone();
	weight->SetName("weight");
	weight->GetXaxis()->SetTitle("|#eta|");
	weight->GetYaxis()->SetTitle("p_{T}(GeV)");
	weight->SetTitle("fake_lepton_weight");

	for (int i = 0; i < tight_data.n_pt_bin; i++) {
		for (int j = 0; j < tight_data.n_eta_bin; j++) {
			Double_t tmp     = fakerate->GetBinContent(j + 1, tight_data.n_pt_bin - i);
			Double_t wgt_tmp = tmp / (1 - tmp);
			weight->SetBinContent(j + 1, tight_data.n_pt_bin - i, wgt_tmp);
			cout<<tmp<<"   ";
		}
		cout<<endl;
	}
	cout<<endl;

	output->cd();
	tight_data.h->Write();
	control_data.h->Write();
	tight_wz.h->Write();
	control_wz.h->Write();
	fenzi->Write();
	fenmu->Write();
	fakerate->Write();
	weight->Write();
	output->Close();

}
