#define postAnalyzer_cxx
#include "postAnalyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TH1F.h"
#include <iostream>
#include <bitset>
#include <climits>
#include <cstring>
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TStopwatch.h"
#include <algorithm>
#include <vector>
#include <iterator>
#include <list>
#include <set>

using namespace std;
using std::vector;

int main(int argc, const char* argv[])
{
  Long64_t maxEvents = atof(argv[3]);
  if (maxEvents < -1LL)
    {
      std::cout<<"Please enter a valid value for maxEvents (parameter 3)."<<std::endl;
      return 1;
    }
  int reportEvery = atof(argv[4]);
  if (reportEvery < 1)
    {
      std::cout<<"Please enter a valid value for reportEvery (parameter 4)."<<std::endl;
      return 1;
    }
  postAnalyzer t(argv[1],argv[2]);
  t.Loop(maxEvents,reportEvery);
  return 0;
}

void postAnalyzer::Loop(Long64_t maxEvents, int reportEvery){
  if (fChain == 0) return;
  int nTotal;
  nTotal = 0;
  double nPassing;
  nPassing = 0.0;
  double nObs_bin1, nObs_bin2, nObs_bin3, nObs_bin4, nObs_bin5;
  nObs_bin1 = nObs_bin2 = nObs_bin3 = nObs_bin4 = nObs_bin5 = 0.0;
  int nFilters, nHLT, nPhoCand, nWorstChIso, nGoodMu, nRecoil170, nDphiPhoRecoil, nDphiJetsMET, nEleVeto, nMETcut, nMuMETmT, nhem_veto;
  nFilters = nHLT = nPhoCand = nWorstChIso = nGoodMu = nRecoil170 = nDphiPhoRecoil = nDphiJetsMET = nEleVeto = nMETcut = nMuMETmT = nhem_veto =0;
  int mycount = 0;
  int mycount1 = 0;
  int mycount2 = 0;
  std::vector<int> phoCand1;
  phoCand1.clear();

  std::vector<int> jetveto;
  jetveto.clear();
  
  std::vector<Int_t> runlist;
  runlist.clear();
  std::vector<Long64_t> eventlist;
  eventlist.clear();
  std::vector<Int_t> lumilist;
  lumilist.clear();



  bool debug=true;
  Long64_t nentries = fChain->GetEntries();
  std::cout<<"Coming in: "<<std::endl;
  std::cout<<"nentries:"<<nentries<<std::endl;
  //Look at up to maxEvents events, or all if maxEvents == -1.
  Long64_t nentriesToCheck = nentries;
  if (maxEvents != -1LL && nentries > maxEvents)
    nentriesToCheck = maxEvents;
  nTotal = nentriesToCheck;
  Long64_t nbytes = 0, nb = 0;

  std::cout<<"Running over "<<nTotal<<" events."<<std::endl;
  TStopwatch sw;
  sw.Start();
  for (Long64_t jentry=0; jentry<nentriesToCheck;jentry++)
    {
    
      event_.clear();
      event_info.clear();
    
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      //=1.0 for real data
      double event_weight=1.0;
      double EWK_corrected_weight=1.0;
      double NNLO_weight=1.0;

      TLorentzVector ele_4vec, antiele_4vec;
      TLorentzVector dilepton_4vec, dilepton_4vec_temp;

      //Reconstructed event cuts
      phoCand1   = getPhoCand(225,1.4442,1);
      if (!getMetFilter()) continue;
      {
	nFilters++;
	if(HLTPho>>11&1 == 1)
	  {
	    mycount++;
	    nHLT++;
	    if(phoCand1.size() >0)
	      {
		nPhoCand++;
		// event_weight*=(1.013 - 0.0001168*phoEt->at(phoCand1[0]));
		//     if( TMath::Max( ( (*phoYuPFChWorstIso)[phoCand1[0]]  - rho*EAchargedworst((*phoSCEta)[phoCand1[0]]) ), 0.0) < 1.37 )
		//    if(!(phoIEta->at(phoCand1[0])==-24 && phoIPhi->at(phoCand1[0])==141) && !(phoIEta->at(phoCand1[0])==4 && phoIPhi->at(phoCand1[0])==41) && !(phoIEta->at(phoCand1[0])==5 && phoIPhi->at(phoCand1[0])==41) && !(phoIEta->at(phoCand1[0])==1 && phoIPhi->at(phoCand1[0])==81) && !(phoIEta->at(phoCand1[0])==4 && phoIPhi->at(phoCand1[0])==21)) AN
		//   {
		Float_t uncorrectedPhoEt = ((*phoEt)[phoCand1[0]]);
		nWorstChIso++;
		// Float_t uncorrectedPhoEt = ((*phoSCRawE)[phoCand1[0]]/TMath::CosH((*phoSCEta)[phoCand1[0]]));
		// Double_t EWK_percent_adjustment = ewkCorrection->GetBinContent(ewkCorrection->GetXaxis()->FindBin(uncorrectedPhoEt));
		// EWK_corrected_weight = event_weight*(1.0+.01*EWK_percent_adjustment);
		// NNLO_weight = event_weight*EWK_corrected_weight*NNLOCorrection(phoEt->at(phoCand1[0]));

		mycount1++;
		std::vector<int> mulist = muon_veto_tightID(phoCand1[0],30.0);
		std::vector<int> looseMus = muon_veto_looseID(phoCand1[0],0,10.0);
		std::vector<int> looseEles;
		looseEles.clear();
		if(mulist.size() == 1 && looseMus.size() == 1)
		  {
		    nGoodMu++;
		    looseEles = electron_veto_looseID(phoCand1[0],mulist[0],10.0);
		    jetveto = JetVetoDecision(phoCand1[0],mulist[0]);
              
		    TLorentzVector lep_4vec;
		    lep_4vec.SetPtEtaPhiE(muPt->at(mulist[0]),muEta->at(mulist[0]),muPhi->at(mulist[0]),muE->at(mulist[0]));

		    Double_t lepton_pt = lep_4vec.Pt();
		    TLorentzVector met_4vec;
		    met_4vec.SetPtEtaPhiE(pfMET,0.,pfMETPhi,pfMET);
		    TLorentzVector leptoMET_4vec = lep_4vec+met_4vec;
		    Double_t leptoMET = leptoMET_4vec.Pt();
		    Double_t leptoMET_phi = leptoMET_4vec.Phi();

		    if(leptoMET > 200)
		      {
			nRecoil170++;
			fillHistos(0,NNLO_weight,phoCand1[0],jetveto,mulist,leptoMET,leptoMET_phi);
			if(DeltaPhi(phoPhi->at(phoCand1[0]),leptoMET_phi) > 0.5)//0.5 AN
			  {
			    nDphiPhoRecoil++;
			    fillHistos(1,NNLO_weight,phoCand1[0],jetveto,mulist,leptoMET,leptoMET_phi);
			    if(dPhiJetMET_veto(jetveto))
			      {
				nDphiJetsMET++;
				fillHistos(2,NNLO_weight,phoCand1[0],jetveto,mulist,leptoMET,leptoMET_phi);
				if(looseEles.size() == 0)
				  {
				    nEleVeto++;
				    fillHistos(3,NNLO_weight,phoCand1[0],jetveto,mulist,leptoMET,leptoMET_phi);
				    double dPhi_lepMET = DeltaPhi(muPhi->at(mulist[0]),pfMETPhi);
				    double lepMET_MT = sqrt(2*muPt->at(mulist[0])*pfMET*(1-TMath::Cos(dPhi_lepMET)));
				    if(lepMET_MT < 160 && uncorrectedPhoEt/leptoMET < 1.4 && hem_veto()==false)
				      {
					nMuMETmT++;
					fillHistos(4,NNLO_weight,phoCand1[0],jetveto,mulist,leptoMET,leptoMET_phi);
					if(hem_veto()==false){
					  nhem_veto++;
					  runlist.push_back(run);
					  eventlist.push_back(event);
					  lumilist.push_back(lumis);
					} 
				      }
				  }
			      }
			  }
		      }
		  }
		// }
	      }
	  }
      }
      tree->Fill();
    
      if (jentry%reportEvery == 0)
	{
	  std::cout<<"Finished entry "<<jentry<<"/"<<(nentriesToCheck-1)<<std::endl;
	}
    }

  if((nentriesToCheck-1)%reportEvery != 0)
    std::cout<<"Finished entry "<<(nentriesToCheck-1)<<"/"<<(nentriesToCheck-1)<<std::endl;
  sw.Stop();
  std::cout<<"All events checked."<<std::endl;
  //Report
  std::cout << "RealTime : " << sw.RealTime() / 60.0 << " minutes" << std::endl;
  std::cout << "CPUTime  : " << sw.CpuTime()  / 60.0 << " minutes" << std::endl;
  std::cout << std::endl;
  std::cout << "Number of events inspected: " << nTotal << std::endl;
  std::cout<<std::endl;
  cout<<"Events passing all cuts:"<<endl;
  cout<<"run:event:lumis"<<endl;
  for(int i = 0; i < runlist.size(); i++)
    {
      cout<<runlist[i]<<":"<<eventlist[i]<<":"<<lumilist[i]<<endl;
    }
  std::cout<<std::endl;
  cout<<endl;
  cout<<"nFilters: "<<nFilters<<endl;
  cout<<"nHLT: "<<nHLT<<endl;
  cout<<"nPhoCand: "<<nPhoCand<<endl;
  cout<<"nWorstChIso: "<<nWorstChIso<<endl;
  cout<<"nGoodMu: "<<nGoodMu<<endl;
  cout<<"nRecoil170: "<<nRecoil170<<endl;
  cout<<"nDphiPhoRecoil: "<<nDphiPhoRecoil<<endl;
  cout<<"nDphiJetsMET: "<<nDphiJetsMET<<endl;
  cout<<"nEleVeto: "<<nEleVeto<<endl;
  cout<<"nMETcut: "<<nMETcut<<endl;
  cout<<"nMuMETmT: "<<nMuMETmT<<endl;
  cout<<"nhem_veto: "<<nhem_veto<<endl;
  cout<<endl;

  cout<<"count : "<<mycount<<endl;
}

void postAnalyzer::BookHistos(const char* file2)
{
  fileName = new TFile(file2, "RECREATE");
  tree = new TTree("ADD","ADD");
  tree->Branch("event_","std::vector<unsigned int>",&event_);
  tree->Branch("event_info","std::vector<double>",&event_info);
  fileName->cd();
  
  Float_t PtBins[6]={225.,250., 300., 400., 600., 1000.0};
  Float_t MetBins[6]={200.,250., 300., 400., 600., 1000.0};
  Float_t dPhiJetMETBins[14]={0.0,0.25,0.50,0.75,1.00,1.25,1.50,1.75,2.00,2.25,2.50,2.75,3.00,3.142};

  //h_phoIEtaIPhi = new TH2F("h_phoIEtaIPhi","Photon p_{T} > 175 GeV, E^{miss}_{T} > 140 GeV",360,0.5,360.5,186,-85.5,100.5);h_phoIEtaIPhi->Sumw2();

  // h_dPhijetmet_min = new TH1F("h_dPhijetmet_min","h_dPhijetmet_min",40,0,3.2);h_dPhijetmet_min->Sumw2();
  //       h_dPhijetmet_min_first4 = new TH1F("h_dPhijetmet_min_first4","h_dPhijetmet_min_first4",40,0,3.2);h_dPhijetmet_min_first4->Sumw2();
  // h_HT = new TH1F("h_HT","h_HT",50,0,1000);h_HT->Sumw2();
  // h_HTMET = new TH2F("h_HTMET","h_HTMET",100,0,1000,86,140,1000);h_HTMET->Sumw2();
  // h_njetMET = new TH2F("h_njetMET","h_njetMET",20,0,20,86,140,1000);h_njetMET->Sumw2();

  //Set up the histos to be filled with method fillHistos
  for(int i=0; i<10; i++)
    {
      char ptbins[100];
      sprintf(ptbins, "_%d", i);
      std::string histname(ptbins);
      h_nVtx[i] = new TH1F(("nVtx"+histname).c_str(), "nVtx",40,0,40);h_nVtx[i]->Sumw2();
      h_photon_Et_range[i] = new TH1F(("Photon_Et_range"+histname).c_str(), "Photon_Et",5,PtBins);h_photon_Et_range[i]->Sumw2();
      h_photon_SCEta[i] = new TH1F(("h_photon_SCEta"+histname).c_str(), "h_photon_SCEta",15,-5.0,5.0);h_photon_SCEta[i]->Sumw2();
      h_photon_SCPhi[i] = new TH1F(("h_photon_SCPhi"+histname).c_str(), "h_photon_SCPhi", 15,0,3.15);h_photon_SCPhi[i]->Sumw2();
      h_pfMET[i] = new TH1F(("pfMET"+histname).c_str(), "pfMET",15,0.,700.);h_pfMET[i]->Sumw2();
      h_nJet[i] = new TH1F(("nJet"+histname).c_str(), "nJet",15,0,15);h_nJet[i]->Sumw2();
      h_leadingJetPt[i] = new TH1F(("leadingJetPt"+histname).c_str(),"leadingJetPt",15,0,300);h_leadingJetPt[i]->Sumw2();
      h_leadingJetEta[i] = new TH1F(("h_leadingJetEta"+histname).c_str(),"h_leadingJetEta",15,-5.0,5.0);h_leadingJetEta[i]->Sumw2();
      h_PTMET[i] = new TH1F(("PTMET"+histname).c_str(),"P_{T}/Missing E_{T}",15,0,2);h_PTMET[i]->Sumw2();
      h_leptonPt[i] = new TH1F(("h_leptonPt"+histname).c_str(),"h_leptonPt",15,30.,400.);h_leptonPt[i]->Sumw2();
      h_leptonEta[i] = new TH1F(("h_leptonEta"+histname).c_str(),"h_leptonEta",15,-5.0,5.0);h_leptonEta[i]->Sumw2();
      h_leptonPhi[i] = new TH1F(("h_leptonPhi"+histname).c_str(),"h_leptonPhi",15,0.,3.15);h_leptonPhi[i]->Sumw2();
      //mark 
      h_JetPt[i] = new TH1F(("h_JetPt"+histname).c_str(),"h_JetPt",15,30.,400.);h_JetPt[i]->Sumw2();
      h_JetEta[i] = new TH1F(("h_JetEta"+histname).c_str(),"h_JetEta",15,-5.0,5.0);h_JetEta[i]->Sumw2();
      h_JetPhi[i] = new TH1F(("h_JetPhi"+histname).c_str(),"h_JetPhi",15,0.,3.15);h_JetPhi[i]->Sumw2();
      h_photonic_recoil[i] = new TH1F(("h_photonic_recoil"+histname).c_str(),"h_photonic_recoil",5,MetBins);h_photonic_recoil[i]->Sumw2();
      h_dPhi_phoRecoil[i] = new TH1F(("h_dPhi_phoRecoil"+histname).c_str(),"h_dPhi_phoRecoil",15,2.0,3.15);h_dPhi_phoRecoil[i]->Sumw2();
      h_phoPT_over_photonicRecoil[i] = new TH1F(("h_phoPT_over_photonicRecoil"+histname).c_str(),"h_phoPT_over_photonicRecoil",15,0.,2.);h_phoPT_over_photonicRecoil[i]->Sumw2();
    h_leptonPt_over_pfMET[i] = new TH1F(("h_leptonPt_over_pfMET"+histname).c_str(),"h_leptonPt_over_pfMET",20,0.,3.);h_leptonPt_over_pfMET[i]->Sumw2();
    h_lepMET_MT[i] = new TH1F(("h_lepMET_MT"+histname).c_str(),"h_lepMET_MT",15,0.,400.);h_lepMET_MT[i]->Sumw2();
    h_min_dphijetmet[i] = new TH1F(("h_min_dphijetmet"+histname).c_str(),"h_min_dphijetmet",13,dPhiJetMETBins);h_min_dphijetmet[i]->Sumw2();
    h_min_dphijetrecoil[i] = new TH1F(("h_min_dphijetrecoil"+histname).c_str(),"h_min_dphijetrecoil",10,0.,3.15);h_min_dphijetrecoil[i]->Sumw2();
    h_dPhi_lepMET[i] = new TH1F(("h_dPhi_lepMET"+histname).c_str(),"h_dPhi_lepMET",15,0.,3.15);h_dPhi_lepMET[i]->Sumw2();
    h_dPhi_phoRecoil_fullrange[i] = new TH1F(("h_dPhi_phoRecoil_fullrange"+histname).c_str(),"h_dPhi_phoRecoil_fullrange",20,0.,3.15);h_dPhi_phoRecoil_fullrange[i]->Sumw2();
    h_pfMETsumEt[i] = new TH1F(("pfMETsumEt"+histname).c_str(),"pfMETsumEt",5,MetBins);
    h_METoverSqrtSumEt_extended[i] = new TH1F(("METoverSqrtSumEt_extended"+histname).c_str(),"METoverSqrtSumEt",30,0,30);
    h_METoverSqrtSumEt[i] = new TH1F(("METoverSqrtSumEt"+histname).c_str(),"METoverSqrtSumEt",30,0,10);
  }
}

//Fill the sequential histos at a particular spot in the sequence
void postAnalyzer::fillHistos(int histoNumber, double event_weight,int index,std::vector<int> jets,std::vector<int> leplist,Double_t leptoMET,Double_t leptoMET_phi)
{
    Float_t uncorrectedPhoEt = ((*phoEt)[index]);
    h_photon_Et_range[histoNumber]->Fill(uncorrectedPhoEt,event_weight);
    h_photon_SCEta[histoNumber]->Fill(phoSCEta->at(index),event_weight);
    h_photon_SCPhi[histoNumber]->Fill(phoSCPhi->at(index),event_weight);
    h_pfMET[histoNumber]->Fill(pfMET,event_weight);
    h_PTMET[histoNumber]->Fill(uncorrectedPhoEt/pfMET,event_weight);
    h_nJet[histoNumber]->Fill(jets.size(),event_weight);
for(int ii = 0; ii < jets.size();ii++){
    h_JetPt[histoNumber]->Fill(jetPt->at(jets[ii]),event_weight);
    h_JetEta[histoNumber]->Fill(jetEta->at(jets[ii]),event_weight);
    h_JetPhi[histoNumber]->Fill(jetPhi->at(jets[ii]),event_weight);
}
    if(jets.size()>0){
      h_leadingJetPt[histoNumber]->Fill(jetPt->at(jets[0]),event_weight);
      h_leadingJetEta[histoNumber]->Fill(jetEta->at(jets[0]),event_weight);
      int max_njets = jets.size();
      if(jets.size() > 4)
        max_njets = 4;
      double min_dphijetmet = TMath::Pi();
      double min_dphijetrecoil = TMath::Pi();
      for(int i = 0; i < max_njets; i++)
      {
        double dphijetmet = DeltaPhi(jetPhi->at(jets[i]),pfMETPhi);
        if(dphijetmet < min_dphijetmet)
          min_dphijetmet = dphijetmet;
        double dphijetrecoil = DeltaPhi(jetPhi->at(jets[i]),leptoMET_phi);
        if(dphijetrecoil < min_dphijetrecoil)
          min_dphijetrecoil = dphijetrecoil;
      }
      h_min_dphijetmet[histoNumber]->Fill(min_dphijetmet,event_weight);
      h_min_dphijetrecoil[histoNumber]->Fill(min_dphijetrecoil,event_weight);
    }
    h_leptonPt[histoNumber]->Fill(muPt->at(leplist[0]),event_weight);
    h_leptonEta[histoNumber]->Fill(muEta->at(leplist[0]),event_weight);
    h_leptonPhi[histoNumber]->Fill(muPhi->at(leplist[0]),event_weight);
    h_photonic_recoil[histoNumber]->Fill(leptoMET,event_weight);
    double dPhi_phoRecoil = DeltaPhi(phoPhi->at(index),leptoMET_phi);
    h_dPhi_phoRecoil[histoNumber]->Fill(dPhi_phoRecoil,event_weight);
    h_dPhi_phoRecoil_fullrange[histoNumber]->Fill(dPhi_phoRecoil,event_weight);
    h_phoPT_over_photonicRecoil[histoNumber]->Fill(uncorrectedPhoEt/leptoMET,event_weight);
    h_leptonPt_over_pfMET[histoNumber]->Fill(muPt->at(leplist[0])/pfMET,event_weight);
    double dPhi_lepMET = DeltaPhi(muPhi->at(leplist[0]),pfMETPhi);
    h_dPhi_lepMET[histoNumber]->Fill(dPhi_lepMET,event_weight);
    h_lepMET_MT[histoNumber]->Fill(sqrt(2*muPt->at(leplist[0])*pfMET*(1-TMath::Cos(dPhi_lepMET))),event_weight);
    h_pfMETsumEt[histoNumber]->Fill(pfMETsumEt,event_weight);
    h_METoverSqrtSumEt_extended[histoNumber]->Fill(pfMET/sqrt(pfMETsumEt),event_weight);
    h_METoverSqrtSumEt[histoNumber]->Fill(pfMET/sqrt(pfMETsumEt),event_weight);
}

void postAnalyzer::scaleHistos(int histoNumber, double scale_factor)
{
  // h_photon_Et[histoNumber]->Scale(scale_factor);
  // h_photon_Et_range[histoNumber]->Scale(scale_factor);
  // h_photon_eta[histoNumber]->Scale(scale_factor);
  // h_photon_SCEta[histoNumber]->Scale(scale_factor);
  // h_photon_phi[histoNumber]->Scale(scale_factor);
  // h_photon_SCPhi[histoNumber]->Scale(scale_factor);
  // h_pfMET[histoNumber]->Scale(scale_factor);
  // h_pfMET_300[histoNumber]->Scale(scale_factor);
  // h_dPhi[histoNumber]->Scale(scale_factor);
  // h_nJet[histoNumber]->Scale(scale_factor);
  // h_PTMET[histoNumber]->Scale(scale_factor);
}

//Gives the (minimum) separation in phi between the specified phi values
//Must return a positive value
double postAnalyzer::DeltaPhi(double phi1, double phi2)
{
  double pi = TMath::Pi();
  double dphi = fabs(phi1-phi2);
  if(dphi>pi)
    dphi = 2.0*pi - dphi;
  return dphi;
}


//---------------------------------------------------
// get a photon candiate based on pt eta and isolation
//----------------------------------------------------

std::vector<int> postAnalyzer::getPhoCand(double phoPtCut, double phoEtaCut, Short_t isoBit){

  std::vector<int> tmpCand;
  tmpCand.clear();
  for(int p=0;p<nPho;p++)
    {
      Float_t uncorrectedPhoEt = ((*phoEt)[p]);
      //      bool kinematic = uncorrectedPhoEt > phoPtCut  && fabs((*phoSCEta)[p])<phoEtaCut;
      bool kinematic = uncorrectedPhoEt > phoPtCut && fabs((*phoSCEta)[p])>1.566 && fabs((*phoSCEta)[p])<2.5;

      bool photonId = (
		       ((*phoHoverE)[p]                <  0.0109    ) &&
		       ((*phoSigmaIEtaIEtaFull5x5)[p]  <  0.026 ) &&
		       ((*phohasPixelSeed)[p]              ==  0      )&& 
		       ( TMath::Max( ( (*phoPFChWorstIso)[p]  - rho*EAchargedworst((*phoSCEta)[p]) ), 0.0) <4.98 )  &&
		       ( TMath::Max( ( (*phoPFNeuIso)[p] - rho*EAneutral((*phoSCEta)[p]) ), 0.0) < (5.24 + (0.0072 * uncorrectedPhoEt) + (0.000017 * pow(uncorrectedPhoEt, 2.0))) )  &&
		       ( TMath::Max( ( (*phoPFPhoIso)[p] - rho*EAphoton((*phoSCEta)[p])  ), 0.0) < (1.20 + (0.0019 * uncorrectedPhoEt)) )
		       );
      
      
      bool noncoll = fabs((*phoSeedTime)[p]) < 3. && (*phoMIPTotEnergy)[p] < 4.9;// && (*phoSigmaIEtaIEtaFull5x5)[p] > 0.001 && (*phoSigmaIPhiIPhiFull5x5)[p] > 0.001;
      
      if(photonId && kinematic && noncoll)
	{
	  tmpCand.push_back(p);
	}                                                                                                                                                              
    }                                                                                                                                                                
  
  //Loop over photons                                                                                                                                                             
  return tmpCand;


}






std::vector<int> postAnalyzer::getPhoCand1(double phoEtaCut, Short_t isoBit){

  std::vector<int> tmpCand;
  tmpCand.clear();
  return tmpCand;
}


std::vector<int> postAnalyzer::getQcdden(double phoPtCut, double phoEtaCut, Short_t isoBit){
  std::vector<int> tmpCand;
  tmpCand.clear();
  return tmpCand;
}

// Effective area to be needed in PF Iso for photon ID
// https://indico.cern.ch/event/455258/contribution/0/attachments/1173322/1695132/SP15_253rd.pdf -- slide-5

Double_t postAnalyzer::EAchargedworst(Double_t eta){
  Float_t EffectiveArea = 0.0;

  if(fabs(eta) >= 1.566   && fabs(eta) < 2.0 ) EffectiveArea = 0.055;
  if(fabs(eta) >= 2.0   && fabs(eta) < 2.5 ) EffectiveArea = 0.048;

  return EffectiveArea;
}
Double_t postAnalyzer::EAneutral(Double_t eta){
  Float_t EffectiveArea = 0.0;
  if(fabs(eta) >= 1.566   && fabs(eta) < 2.0 ) EffectiveArea = 0.019;
  if(fabs(eta) >= 2.0   && fabs(eta) < 2.5 ) EffectiveArea = 0.018;
  return EffectiveArea;
}
Double_t postAnalyzer::EAphoton(Double_t eta){
  Float_t EffectiveArea = 0.0;
  if(fabs(eta) >= 1.566   && fabs(eta) < 2.0 ) EffectiveArea = 0.057;
  if(fabs(eta) >= 2.0   && fabs(eta) < 2.5 ) EffectiveArea = 0.069;
  return EffectiveArea;
}




std::vector<int> postAnalyzer::electron_veto_tightID(int pho_index, float elePtCut)
{
  std::vector<int> ele_cands;
  ele_cands.clear();
  for(int i = 0; i < nEle; i++)
    {
      //Electron passes Loose Electron ID cuts
            if(eleIDbit->at(i)>>2&1==1)

	{
	  //Electron passes pt cut
	  //	  	  if(elePt->at(i) > elePtCut)
		    if(elePt->at(i) > elePtCut && abs(eleEta->at(i)) < 2.5 )
	    {
	      //Electron does not overlap photon
	      if(dR(eleEta->at(i),elePhi->at(i),phoEta->at(pho_index),phoPhi->at(pho_index)) > 0.5)
		{
		  ele_cands.push_back(i);
		}
	    }
	}
    }
  return ele_cands;
}

std::vector<int> postAnalyzer::muon_veto_tightID(int pho_index, float muPtCut)
{
  // bool veto_passed = true; //pass veto if no good muon found
  std::vector<int> mu_cands;
  mu_cands.clear();
  for(int i = 0; i < nMu; i++)
    {
      //Muon passes Tight Muon ID
      //      if(muIDbit->at(i)>>3&1==1)
	if(muIDbit->at(i)>>3&1==1 && muIDbit->at(i)>>9&1==1)
	{
	  //Muon passes pt cut
	  	  if(muPt->at(i) > muPtCut && abs(muEta->at(i)) < 2.4 )
	  //if(muPt->at(i) > muPtCut)
	    {
	      //Muon does not overlap photon
	      if(dR(muEta->at(i),muPhi->at(i),phoEta->at(pho_index),phoPhi->at(pho_index)) > 0.5)
		{
		  mu_cands.push_back(i);
		}
	    }
	}
    }
  return mu_cands;
}

//Returns true if veto passed
//Veto failed if an electron is found that passes Loose Electron ID and elePtcut, and does not overlap the candidate photon within dR of 0.5
//Always true if no electrons with |SC eta| < 2.5, since ID always fails for |SC eta| > 2.

std::vector<int> postAnalyzer::electron_veto_looseID(int pho_index, int mu_index, float elePtCut)
{
  std::vector<int> ele_cands;
  ele_cands.clear();
  for(int i = 0; i < nEle; i++)
    {
      //Electron passes Loose Electron ID cuts
      if(eleIDbit->at(i)>>0&1==1)
	{
	  //Electron passes pt cut
	  //	  if(elePt->at(i) > elePtCut)
		      if(elePt->at(i) > elePtCut && abs(eleEta->at(i)) < 2.5 )

	    {
	      //       if(dR(eleEta->at(i),elePhi->at(i),phoEta->at(pho_index),phoPhi->at(pho_index)) > 0.5)
	      //Electron does not overlap photon
	      if(dR(eleEta->at(i),elePhi->at(i),phoEta->at(pho_index),phoPhi->at(pho_index)) > 0.5 && dR(eleEta->at(i),elePhi->at(i),muEta->at(mu_index),muPhi->at(mu_index)) > 0.5)
		{
		  ele_cands.push_back(i);
		}
	    }
	}
    }
  return ele_cands;
}



//Veto failed if a muon is found that passes Loose Muon ID, Loose Muon Isolation, and muPtcut, and does not overlap the candidate photon within dR of 0.5
std::vector<int> postAnalyzer::muon_veto_looseID(int pho_index, int ele_index, float muPtCut)
{
  std::vector<int> mu_cands;
  mu_cands.clear();

  for(int i = 0; i < nMu; i++)
    {
      //      if(muIDbit->at(i)>>0&1==1)
	if(muIDbit->at(i)>>0&1==1 && muIDbit->at(i)>>7&1==1)
	{
	  //Muon passes pt cut
	  	  if(muPt->at(i) > muPtCut && abs(muEta->at(i)) < 2.4 )
	  //if(muPt->at(i) > muPtCut)
	    {
	      //Muon does not overlap photon
	      if(dR(muEta->at(i),muPhi->at(i),phoEta->at(pho_index),phoPhi->at(pho_index)) > 0.5)
		{
		  mu_cands.push_back(i);
		}
	    }
	}
    }
  return mu_cands;
}


std::vector<int> postAnalyzer::JetVetoDecision(int pho_index, int mu_index) {

  bool jetVeto=true;
  std::vector<int> jetindex;
  float value =0.0;

  for(int i = 0; i < nJet; i++)
    {


      if(0.0 < abs(jetEta->at(i)) && abs(jetEta->at(i)) <2.5)
        value =0.86;//-0.8;
      if(2.5 <= abs(jetEta->at(i)) && abs(jetEta->at(i)) <2.75)
        value =-0.10;//-0.95;
      if(2.75 <= abs(jetEta->at(i)) && abs(jetEta->at(i)) <3.0)
        value =-0.05;//-0.97;
      if(3.00 <= abs(jetEta->at(i)) && abs(jetEta->at(i)) <5.0)
        value =-0.01;//-0.99;


      //      std::cout<<"Jet size: "<<nJet<<std::endl;
      double deltar = 0.0 ;
      double deltar_mu = 0.0 ;
      //      std::cout<<"Jet no:"<<i<<"coming here pujetid: "<<pfJet_pt[i]<<std::endl;
      //if(OverlapWithMuon(jetEta->at(i),jetPhi->at(i)))     continue;
      //      std::cout<<"Jet no:"<<i<<"coming here OverlapWithMuon: "<<pfJet_pt[i]<<std::endl;
      //      if(OverlapWithElectron(jetEta->at(i),jetPhi->at(i)))   continue;
      deltar= dR(jetEta->at(i),jetPhi->at(i),phoEta->at(pho_index),phoPhi->at(pho_index));
      deltar_mu = dR(jetEta->at(i),jetPhi->at(i),muEta->at(mu_index),muPhi->at(mu_index));
      if((deltar>0.4) && (deltar_mu > 0.4) && (jetPt->at(i) >30.0) && (jetID->at(i) >>1&1==1) && abs(jetEta->at(i))<5.0)
        {
          jetindex.push_back(i);
        }

      
    }


  //  std::cout<<"Jet size: "<< jetindex.size()<<std::endl;
  //if(jetindex.size()>1)jetVeto = false;
  return jetindex;

}



bool postAnalyzer::OverlapWithMuon(double eta, double phi){

  return false;


}



bool postAnalyzer::OverlapWithElectron(double eta, double phi){
  return false;

}


double postAnalyzer::dR(double eta1, double phi1, double eta2, double phi2)
{
  double deltaeta = abs(eta1 - eta2);
  double deltaphi = DeltaPhi(phi1, phi2);
  double deltar = sqrt(deltaeta*deltaeta + deltaphi*deltaphi);
  return deltar;
}





bool postAnalyzer::dPhiJetMET_veto(std::vector<int> jets)
{
  //pass veto if no jet is found within DeltaPhi(jet,MET) < 0.5
  bool passes = false;
  int njetsMax = jets.size();
  //Only look at first four jets
  if(njetsMax > 4)
    njetsMax = 4;
  int j = 0;
  for(; j < njetsMax; j++)
    {
      //fail veto if a jet is found with DeltaPhi(jet,MET) < 0.5
      if(DeltaPhi(jetPhi->at(jets[j]),pfMETPhi) < 0.5)
	break;
    }
  if(j==njetsMax)
    passes = true;

  return passes;
}
double postAnalyzer::FakeRatePt(Float_t phoPt, int syst_number)
{
  double weight = 1.0;
  return weight;
}


bool postAnalyzer::getMetFilter(){
  bool decision = true;
  if(metFilters>>0 & 1) decision = false;
  if(metFilters>>1 & 1) decision = false;
  if(metFilters>>2 & 1) decision = false;
  if(metFilters>>3 & 1) decision = false;
  if(metFilters>>4 & 1) decision = false;
  if(metFilters>>5 & 1) decision = false;
  if(metFilters>>7 & 1) decision = false;
  if(metFilters>>8 & 1) decision = false;
  return decision;
}


bool postAnalyzer::hem_veto(){
  bool veto_event = false;
  for(int iJets=0; iJets<nJet ; iJets++)
    {
      if (jetEta->at(iJets)> -3.2 && jetEta->at(iJets)<-1.3 && jetPhi->at(iJets)>-1.57 && jetPhi->at(iJets)<-0.87)
	veto_event = true;
    }
  return veto_event;
}

