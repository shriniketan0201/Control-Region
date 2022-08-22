#include <fstream>
#include <vector>
#include <iomanip>
#include "TFile.h"
#include "TH2.h"
#include "TH2F.h"
#include "TGraph2D.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TString.h"
#include "THStack.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TColor.h"

void plot(string histname_string, Double_t leg_xoffset, Double_t leg_yoffset, TString xaxis_title, TString plotname)
{
    TString histname = TString(histname_string+"_5");
  TString histname_JESUp = TString(histname_string+"_11");
  TString histname_JESDown = TString(histname_string+"_17");
  TString histname_PESUp = TString(histname_string+"_23");
  TString histname_PESDown = TString(histname_string+"_29");
  



  std::vector<TH1F*> histo_vector;
  histo_vector.clear();
  
  Float_t int_lumi = 41530.0;
  Float_t scale_factor = 0.94;
  
  double photon_scale_factor_unc = 0.06;
  double electron_scale_factor_unc = 0.02;
  double jes_unc = 0.0031;
  double pes_unc = 0.0615;
  double qcdscale_unc = 0.052;
  double pdf_unc = 0.026;
  double unbinned_unc_sumsquares = photon_scale_factor_unc*photon_scale_factor_unc + electron_scale_factor_unc*electron_scale_factor_unc + qcdscale_unc*qcdscale_unc + pdf_unc*pdf_unc;
  double all_unc_sumsquares = unbinned_unc_sumsquares + jes_unc*jes_unc + pes_unc*pes_unc;
  // double sumsquares_scale_factor_unc = photon_scale_factor_unc*photon_scale_factor_unc + electron_scale_factor_unc*electron_scale_factor_unc;
  
  double total_background = 0.0;
  double background_unc_sumsquares = 0.0;
  
  TCanvas *c = new TCanvas("c", "canvas",700,640);
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  float t_m = 0.08; //top margin
  float b_m = 0.4; //botton margin
  float l_m = 0.09; //left margin
  float r_m = 0.05; //right margin
  c->SetTopMargin(t_m);
  c->SetBottomMargin(b_m);
  c->SetLeftMargin(l_m);
  c->SetRightMargin(r_m);
  c->SetFrameFillStyle(0);
  c->SetFrameBorderMode(0);
  c->SetFrameFillStyle(0);
  c->SetFrameBorderMode(0);
  c->cd();

  TFile *f_data = new TFile("Data_all.root");
  TH1F* histo_data = (TH1F*)f_data->Get(histname);
  const int nBins = histo_data->GetXaxis()->GetNbins();
  Float_t int_data = histo_data->Integral()+histo_data->GetBinContent(0)+histo_data->GetBinContent(nBins+1);
  histo_data->SetLineWidth(3);
  histo_data->SetLineColor(kWhite);
  histo_data->SetMarkerStyle(kFullSquare);
  histo_data->SetMarkerColor(kWhite);
  histo_vector.push_back(histo_data);
  
  //Now that nBins has been specified, initialize binned MET shift repositories to the appropriate length
  std::vector<double> jesup_shift;
  jesup_shift.clear();
  std::vector<double> jesdown_shift;
  jesdown_shift.clear();
  std::vector<double> pesup_shift;
  pesup_shift.clear();
  std::vector<double> pesdown_shift;
  pesdown_shift.clear();
  std::vector<double> renup_shift;
  renup_shift.clear();
  std::vector<double> rendown_shift;
  rendown_shift.clear();
  std::vector<double> facup_shift;
  facup_shift.clear();
  std::vector<double> facdown_shift;
  facdown_shift.clear();
  std::vector<double> pdfup_shift;
  pdfup_shift.clear();
  std::vector<double> pdfdown_shift;
  pdfdown_shift.clear();
  for(int i = 1; i <= nBins; i++){
    jesup_shift.push_back(0);
    jesdown_shift.push_back(0);
    pesup_shift.push_back(0);
    pesdown_shift.push_back(0);
    renup_shift.push_back(0);
    rendown_shift.push_back(0);
    facup_shift.push_back(0);
    facdown_shift.push_back(0);
    pdfup_shift.push_back(0);
    pdfdown_shift.push_back(0);
  }
  
  TFile* f_WG = new TFile("WenG_JESPES_WG.root");
  TH1F* histo_WG = (TH1F*)f_WG->Get(histname);
  TH1F* histo_WG_JESUp = (TH1F*)f_WG->Get(histname_JESUp);
  TH1F* histo_WG_JESDown = (TH1F*)f_WG->Get(histname_JESDown);
  TH1F* histo_WG_PESUp = (TH1F*)f_WG->Get(histname_PESUp);
  TH1F* histo_WG_PESDown = (TH1F*)f_WG->Get(histname_PESDown);
  histo_WG->SetStats(0);
  histo_WG->Scale(int_lumi*scale_factor*8.093e-01/3609634.0);
  histo_WG_JESUp->Scale(int_lumi*scale_factor*8.093e-01/3609634.0);
  histo_WG_JESDown->Scale(int_lumi*scale_factor*8.093e-01/3609634.0);
  histo_WG_PESUp->Scale(int_lumi*scale_factor*8.093e-01/3609634.0);
  histo_WG_PESDown->Scale(int_lumi*scale_factor*8.093e-01/3609634.0);
  Float_t int_WG = histo_WG->Integral()+histo_WG->GetBinContent(0)+histo_WG->GetBinContent(nBins+1);
  Float_t int_WG_JESUp = histo_WG_JESUp->Integral()+histo_WG_JESUp->GetBinContent(0)+histo_WG_JESUp->GetBinContent(nBins+1);
  Float_t int_WG_JESDown = histo_WG_JESDown->Integral()+histo_WG_JESDown->GetBinContent(0)+histo_WG_JESDown->GetBinContent(nBins+1);
  Float_t int_WG_PESUp = histo_WG_PESUp->Integral()+histo_WG_PESUp->GetBinContent(0)+histo_WG_PESUp->GetBinContent(nBins+1);
  Float_t int_WG_PESDown = histo_WG_PESDown->Integral()+histo_WG_PESDown->GetBinContent(0)+histo_WG_PESDown->GetBinContent(nBins+1);
  double jeserr_WG = (fabs(int_WG_JESUp-int_WG)+fabs(int_WG_JESDown-int_WG))/2.0;
  double peserr_WG = (fabs(int_WG_PESUp-int_WG)+fabs(int_WG_PESDown-int_WG))/2.0;
  TH1F* histo_WG_RenUp;
  TH1F* histo_WG_RenDown;
  TH1F* histo_WG_FacUp;
  TH1F* histo_WG_FacDown;
  TH1F* histo_WG_PDFUp;
  TH1F* histo_WG_PDFDown;
  double renerr_WG = 0.0;
  double facerr_WG = 0.0;
  double pdferr_WG = 0.0;
  //  if(histname == "Photon_Et_range_5"){
  /*    TFile* f_pdfscale_WG = new TFile("histos_WenG_pdfscale_WGJets.root");
    histo_WG_RenUp = (TH1F*)f_pdfscale_WG->Get("h_WenG_pdfscale_WGJets_renUp");
    histo_WG_RenDown = (TH1F*)f_pdfscale_WG->Get("h_WenG_pdfscale_WGJets_renDown");
    histo_WG_FacUp = (TH1F*)f_pdfscale_WG->Get("h_WenG_pdfscale_WGJets_facUp");
    histo_WG_FacDown = (TH1F*)f_pdfscale_WG->Get("h_WenG_pdfscale_WGJets_facDown");
    histo_WG_PDFUp = (TH1F*)f_pdfscale_WG->Get("h_WenG_pdfscale_WGJets_pdfUp");
    histo_WG_PDFDown = (TH1F*)f_pdfscale_WG->Get("h_WenG_pdfscale_WGJets_pdfDown");

    Float_t int_WG_RenUp = histo_WG_RenUp->Integral()+histo_WG_RenUp->GetBinContent(0)+histo_WG_RenUp->GetBinContent(nBins+1);
    Float_t int_WG_RenDown = histo_WG_RenDown->Integral()+histo_WG_RenDown->GetBinContent(0)+histo_WG_RenDown->GetBinContent(nBins+1);
    Float_t int_WG_FacUp = histo_WG_FacUp->Integral()+histo_WG_FacUp->GetBinContent(0)+histo_WG_FacUp->GetBinContent(nBins+1);
    Float_t int_WG_FacDown = histo_WG_FacDown->Integral()+histo_WG_FacDown->GetBinContent(0)+histo_WG_FacDown->GetBinContent(nBins+1);
    Float_t int_WG_PDFUp = histo_WG_PDFUp->Integral()+histo_WG_PDFUp->GetBinContent(0)+histo_WG_PDFUp->GetBinContent(nBins+1);
    Float_t int_WG_PDFDown = histo_WG_PDFDown->Integral()+histo_WG_PDFDown->GetBinContent(0)+histo_WG_PDFDown->GetBinContent(nBins+1);
    renerr_WG = (fabs(int_WG_RenUp-int_WG)+fabs(int_WG_RenDown-int_WG))/2.0;
    facerr_WG = (fabs(int_WG_FacUp-int_WG)+fabs(int_WG_FacDown-int_WG))/2.0;
    pdferr_WG = (fabs(int_WG_PDFUp-int_WG)+fabs(int_WG_PDFDown-int_WG))/2.0;
}
*/
  for(int i = 1; i <= nBins; i++){
    double int_bin = histo_WG->GetBinContent(i);
    double jesup = histo_WG_JESUp->GetBinContent(i);
    double jesdown = histo_WG_JESDown->GetBinContent(i);
    double pesup = histo_WG_PESUp->GetBinContent(i);
    double pesdown = histo_WG_PESDown->GetBinContent(i);
    jesup_shift[i-1] += jesup-int_bin;
    jesdown_shift[i-1] += jesdown-int_bin;
    pesup_shift[i-1] += pesup-int_bin;
    pesdown_shift[i-1] += pesdown-int_bin;
    
    double err_bin = 0.0;
    if(int_bin > 0)
      err_bin = int_bin*sqrt(((8.093e-01*int_lumi*scale_factor-int_bin)/(3609634.0*int_bin))+(.07*.07));
    histo_WG->SetBinError(i,err_bin);
  }
  Float_t err_WG = 0.0;
  if(int_WG > 0.0){
    err_WG = sqrt(int_WG*int_WG*((electron_scale_factor_unc*electron_scale_factor_unc)+(photon_scale_factor_unc*photon_scale_factor_unc)+(.07*.07)+(8.093e-01*int_lumi*scale_factor-int_WG)/(3609634.0*int_WG))+(jeserr_WG*jeserr_WG)+(peserr_WG*peserr_WG)+(renerr_WG*renerr_WG)+(facerr_WG*facerr_WG)+(pdferr_WG*pdferr_WG));
        if(histname == "Photon_Et_range_5"){
    
      cout<<"WenG percentage errors:"<<endl;
      cout<<"stat err = "<<sqrt(((8.093e-01*int_lumi*scale_factor-int_WG)/(3609634.0*int_WG)))<<endl;
      cout<<"jes err = "<<jeserr_WG/int_WG<<endl;
      cout<<"pes err = "<<peserr_WG/int_WG<<endl;
      cout<<"ren err = "<<renerr_WG/int_WG<<endl;
      cout<<"fac err = "<<facerr_WG/int_WG<<endl;
      cout<<"pdf err = "<<pdferr_WG/int_WG<<endl;
      cout<<"pho scale factor err = "<<photon_scale_factor_unc<<endl;
      cout<<"ele scale factor err = "<<electron_scale_factor_unc<<endl;
      cout<<"NNLO xsec err = "<<0.07<<endl;
      cout<<"Total systematic = "<<sqrt(pow(jeserr_WG,2)+pow(peserr_WG,2)+pow(renerr_WG,2)+pow(facerr_WG,2)+pow(pdferr_WG,2)+pow(photon_scale_factor_unc*int_WG,2)+pow(electron_scale_factor_unc*int_WG,2)+pow(0.07*int_WG,2))/int_WG<<endl;
    }
  }
  total_background += int_WG;
  background_unc_sumsquares += err_WG*err_WG;
  histo_WG->SetFillColor(kAzure+10);
  // histo_WG->SetFillColor(TColor::GetColor("#FF6633"));
  histo_vector.push_back(histo_WG);
  
     TFile *f_jetfake = new TFile("QCD_all.root");
  //  TFile *f_jetfake = new TFile("/nfs_scratch/sacharya/UL_studies/CMSSW_10_6_20/src/CR_Studies/nlo_samples/wenug_update/egamma_2016/qcd/sdogra_new/qcd_all.root");
  TH1F* histo_jetfake = (TH1F*)f_jetfake->Get(histname);
  Float_t int_QCD = histo_jetfake->Integral()+histo_jetfake->GetBinContent(0)+histo_jetfake->GetBinContent(nBins+1);
  Float_t err_QCD = 0.10*int_QCD;
  for(int i = 1; i <= nBins; i++){
    double int_bin_jetfake = histo_jetfake->GetBinContent(i);
    histo_jetfake->SetBinError(i,0.10*int_bin_jetfake);
  }
  total_background += int_QCD;
  background_unc_sumsquares += err_QCD*err_QCD;
  histo_jetfake->SetFillColor(kBlue-4);
  histo_vector.push_back(histo_jetfake);
    

  TFile *f_elefake = new TFile("Wenu_all.root");
  TH1F* histo_elefake = (TH1F*)((TH1F*)f_elefake->Get(histname))->Clone("histo_elefake");
  histo_elefake->SetBinContent(nBins, histo_elefake->GetBinContent(nBins)+histo_elefake->GetBinContent(nBins+1));
  histo_elefake->ClearUnderflowAndOverflow();
  //  histo_elefake->Scale(0.03031);
  //  histo_elefake->Scale(0.050);
  Float_t int_elefake = histo_elefake->Integral();
  for(int i = 1; i <= nBins; i++){
    double int_bin_elefake = histo_elefake->GetBinContent(i);
    //    histo_elefake->SetBinError(i, sqrt(int_bin_elefake*0.03031));
    histo_elefake->SetBinError(i, sqrt(int_bin_elefake*0.050));
  }
  //  Float_t syst_elefake = (0.00220/0.03031)*int_elefake;
   Float_t syst_elefake = (0.003/0.050)*int_elefake;
   //  Float_t stat_elefake = sqrt(int_elefake*0.03031);
  Float_t stat_elefake = sqrt(int_elefake*0.050);
  Float_t err_elefake = sqrt(syst_elefake*syst_elefake + stat_elefake*stat_elefake);
  total_background += int_elefake;
  background_unc_sumsquares += err_elefake*err_elefake;
  // histo_elefake->SetFillColor(kBlue-8);
  histo_elefake->SetFillColor(kYellow);
  histo_vector.push_back(histo_elefake);

  
  TFile *f_ZllG = new TFile("WenG_JESPES_ZLLGJets_2.root");
  TH1F* histo_ZllG = (TH1F*)f_ZllG->Get(histname);
  TH1F* histo_ZllG_JESUp = (TH1F*)f_ZllG->Get(histname_JESUp);
  TH1F* histo_ZllG_JESDown = (TH1F*)f_ZllG->Get(histname_JESDown);
  TH1F* histo_ZllG_PESUp = (TH1F*)f_ZllG->Get(histname_PESUp);
  TH1F* histo_ZllG_PESDown = (TH1F*)f_ZllG->Get(histname_PESDown);
  histo_ZllG->SetStats(0);
  histo_ZllG->Scale(int_lumi*scale_factor*2.059e-01/544413);
  histo_ZllG_JESUp->Scale(int_lumi*scale_factor*2.059e-01/544413);
  histo_ZllG_JESDown->Scale(int_lumi*scale_factor*2.059e-01/544413);
  histo_ZllG_PESUp->Scale(int_lumi*scale_factor*2.059e-01/544413);
  histo_ZllG_PESDown->Scale(int_lumi*scale_factor*2.059e-01/544413);
  Float_t int_ZllG = histo_ZllG->Integral()+histo_ZllG->GetBinContent(0)+histo_ZllG->GetBinContent(nBins+1);
  Float_t int_ZllG_JESUp = histo_ZllG_JESUp->Integral()+histo_ZllG_JESUp->GetBinContent(0)+histo_ZllG_JESUp->GetBinContent(nBins+1);
  Float_t int_ZllG_JESDown = histo_ZllG_JESDown->Integral()+histo_ZllG_JESDown->GetBinContent(0)+histo_ZllG_JESDown->GetBinContent(nBins+1);
  Float_t int_ZllG_PESUp = histo_ZllG_PESUp->Integral()+histo_ZllG_PESUp->GetBinContent(0)+histo_ZllG_PESUp->GetBinContent(nBins+1);
  Float_t int_ZllG_PESDown = histo_ZllG_PESDown->Integral()+histo_ZllG_PESDown->GetBinContent(0)+histo_ZllG_PESDown->GetBinContent(nBins+1);
  double jeserr_ZllG = (fabs(int_ZllG_JESUp-int_ZllG)+fabs(int_ZllG_JESDown-int_ZllG))/2.0;
  double peserr_ZllG = (fabs(int_ZllG_PESUp-int_ZllG)+fabs(int_ZllG_PESDown-int_ZllG))/2.0;
  TH1F* histo_ZllG_RenUp;
  TH1F* histo_ZllG_RenDown;
  TH1F* histo_ZllG_FacUp;
  TH1F* histo_ZllG_FacDown;
  TH1F* histo_ZllG_PDFUp;
  TH1F* histo_ZllG_PDFDown;
  double renerr_ZllG = 0.0;
  double facerr_ZllG = 0.0;
  double pdferr_ZllG = 0.0;
  if(histname == "Photon_Et_range_5"){
    /*    TFile* f_pdfscale_ZllG = new TFile("histos_WenG_pdfscale_ZLLGJets.root");
    histo_ZllG_RenUp = (TH1F*)f_pdfscale_ZllG->Get("h_WenG_pdfscale_ZLLGJets_renUp");
    histo_ZllG_RenDown = (TH1F*)f_pdfscale_ZllG->Get("h_WenG_pdfscale_ZLLGJets_renDown");
    histo_ZllG_FacUp = (TH1F*)f_pdfscale_ZllG->Get("h_WenG_pdfscale_ZLLGJets_facUp");
    histo_ZllG_FacDown = (TH1F*)f_pdfscale_ZllG->Get("h_WenG_pdfscale_ZLLGJets_facDown");
    histo_ZllG_PDFUp = (TH1F*)f_pdfscale_ZllG->Get("h_WenG_pdfscale_ZLLGJets_pdfUp");
    histo_ZllG_PDFDown = (TH1F*)f_pdfscale_ZllG->Get("h_WenG_pdfscale_ZLLGJets_pdfDown");

    Float_t int_ZllG_RenUp = histo_ZllG_RenUp->Integral()+histo_ZllG_RenUp->GetBinContent(0)+histo_ZllG_RenUp->GetBinContent(nBins+1);
    Float_t int_ZllG_RenDown = histo_ZllG_RenDown->Integral()+histo_ZllG_RenDown->GetBinContent(0)+histo_ZllG_RenDown->GetBinContent(nBins+1);
    Float_t int_ZllG_FacUp = histo_ZllG_FacUp->Integral()+histo_ZllG_FacUp->GetBinContent(0)+histo_ZllG_FacUp->GetBinContent(nBins+1);
    Float_t int_ZllG_FacDown = histo_ZllG_FacDown->Integral()+histo_ZllG_FacDown->GetBinContent(0)+histo_ZllG_FacDown->GetBinContent(nBins+1);
    Float_t int_ZllG_PDFUp = histo_ZllG_PDFUp->Integral()+histo_ZllG_PDFUp->GetBinContent(0)+histo_ZllG_PDFUp->GetBinContent(nBins+1);
    Float_t int_ZllG_PDFDown = histo_ZllG_PDFDown->Integral()+histo_ZllG_PDFDown->GetBinContent(0)+histo_ZllG_PDFDown->GetBinContent(nBins+1);
    renerr_ZllG = (fabs(int_ZllG_RenUp-int_ZllG)+fabs(int_ZllG_RenDown-int_ZllG))/2.0;
    facerr_ZllG = (fabs(int_ZllG_FacUp-int_ZllG)+fabs(int_ZllG_FacDown-int_ZllG))/2.0;
    pdferr_ZllG = (fabs(int_ZllG_PDFUp-int_ZllG)+fabs(int_ZllG_PDFDown-int_ZllG))/2.0;
    */  }
  for(int i = 1; i <= nBins; i++){
    double int_bin = histo_ZllG->GetBinContent(i);
    double jesup = histo_ZllG_JESUp->GetBinContent(i);
    double jesdown = histo_ZllG_JESDown->GetBinContent(i);
    double pesup = histo_ZllG_PESUp->GetBinContent(i);
    double pesdown = histo_ZllG_PESDown->GetBinContent(i);
    jesup_shift[i-1] += jesup-int_bin;
    jesdown_shift[i-1] += jesdown-int_bin;
    pesup_shift[i-1] += pesup-int_bin;
    pesdown_shift[i-1] += pesdown-int_bin;
    /*   if(histname == "Photon_Et_range_5"){
      double renup = histo_ZllG_RenUp->GetBinContent(i);
      double rendown = histo_ZllG_RenDown->GetBinContent(i);
      double facup = histo_ZllG_FacUp->GetBinContent(i);
      double facdown = histo_ZllG_FacDown->GetBinContent(i);
      double pdfup = histo_ZllG_PDFUp->GetBinContent(i);
      double pdfdown = histo_ZllG_PDFDown->GetBinContent(i);
      renup_shift[i-1] += renup-int_bin;
      rendown_shift[i-1] += rendown-int_bin;
      facup_shift[i-1] += facup-int_bin;
      facdown_shift[i-1] += facdown-int_bin;
      pdfup_shift[i-1] += pdfup-int_bin;
      pdfdown_shift[i-1] += pdfdown-int_bin;
  }*/
    // cout<<"ZllG: bin="<<i<<",int_bin="<<int_bin<<",jesup="<<jesup<<",jesdown="<<jesdown<<",pesup="<<pesup<<",pesdown="<<pesdown<<endl;
    
    double err_bin = 0.0;
    if(int_bin > 0)
      err_bin = int_bin*sqrt(((2.059e-01*1.3*int_lumi*scale_factor-int_bin)/(544413*int_bin))+all_unc_sumsquares+(.11*.11));
    histo_ZllG->SetBinError(i,err_bin);
  }
  Float_t err_ZllG = 0.0;
  if(int_ZllG > 0.0)
    err_ZllG = sqrt(int_ZllG*int_ZllG*((electron_scale_factor_unc*electron_scale_factor_unc)+(photon_scale_factor_unc*photon_scale_factor_unc)+(.11*.11)+(2.059e-01*int_lumi*scale_factor-int_ZllG)/(544413*int_ZllG))+(jeserr_ZllG*jeserr_ZllG)+(peserr_ZllG*peserr_ZllG)+(renerr_ZllG*renerr_ZllG)+(facerr_ZllG*facerr_ZllG)+(pdferr_ZllG*pdferr_ZllG));
  total_background += int_ZllG;
  background_unc_sumsquares += err_ZllG*err_ZllG;
  // histo_ZllG->SetFillColor(kSpring-8);
  histo_ZllG->SetFillColor(kSpring-9);
  histo_vector.push_back(histo_ZllG);
    
  TFile *f_TTG = new TFile("WenG_JESPES_TTGJets.root");
  TH1F* histo_TTG = (TH1F*)f_TTG->Get(histname);
  TH1F* histo_TTG_JESUp = (TH1F*)f_TTG->Get(histname_JESUp);
  TH1F* histo_TTG_JESDown = (TH1F*)f_TTG->Get(histname_JESDown);
  TH1F* histo_TTG_PESUp = (TH1F*)f_TTG->Get(histname_PESUp);
  TH1F* histo_TTG_PESDown = (TH1F*)f_TTG->Get(histname_PESDown);
  histo_TTG->SetStats(0);
  histo_TTG->Scale(int_lumi*scale_factor*3.779e+00/3534208);
  histo_TTG_JESUp->Scale(int_lumi*scale_factor*3.779e+00/3534208);
  histo_TTG_JESDown->Scale(int_lumi*scale_factor*3.779e+00/3534208);
  histo_TTG_PESUp->Scale(int_lumi*scale_factor*3.779e+00/3534208);
  histo_TTG_PESDown->Scale(int_lumi*scale_factor*3.779e+00/3534208);
  Float_t int_TTG = histo_TTG->Integral()+histo_TTG->GetBinContent(0)+histo_TTG->GetBinContent(nBins+1);
  Float_t int_TTG_JESUp = histo_TTG_JESUp->Integral()+histo_TTG_JESUp->GetBinContent(0)+histo_TTG_JESUp->GetBinContent(nBins+1);
  Float_t int_TTG_JESDown = histo_TTG_JESDown->Integral()+histo_TTG_JESDown->GetBinContent(0)+histo_TTG_JESDown->GetBinContent(nBins+1);
  Float_t int_TTG_PESUp = histo_TTG_PESUp->Integral()+histo_TTG_PESUp->GetBinContent(0)+histo_TTG_PESUp->GetBinContent(nBins+1);
  Float_t int_TTG_PESDown = histo_TTG_PESDown->Integral()+histo_TTG_PESDown->GetBinContent(0)+histo_TTG_PESDown->GetBinContent(nBins+1);
  double jeserr_TTG = (fabs(int_TTG_JESUp-int_TTG)+fabs(int_TTG_JESDown-int_TTG))/2.0;
  double peserr_TTG = (fabs(int_TTG_PESUp-int_TTG)+fabs(int_TTG_PESDown-int_TTG))/2.0;
  for(int i = 1; i <= nBins; i++){
    double int_bin = histo_TTG->GetBinContent(i);
    double jesup = histo_TTG_JESUp->GetBinContent(i);
    double jesdown = histo_TTG_JESDown->GetBinContent(i);
    double pesup = histo_TTG_PESUp->GetBinContent(i);
    double pesdown = histo_TTG_PESDown->GetBinContent(i);
    jesup_shift[i-1] += jesup-int_bin;
    jesdown_shift[i-1] += jesdown-int_bin;
    pesup_shift[i-1] += pesup-int_bin;
    pesdown_shift[i-1] += pesdown-int_bin;
    // cout<<"TTG: bin="<<i<<",int_bin="<<int_bin<<",jesup="<<jesup<<",jesdown="<<jesdown<<",pesup="<<pesup<<",pesdown="<<pesdown<<endl;
    
    double err_bin = 0.0;
    if(int_bin > 0)
      err_bin = int_bin*sqrt((3.779e+00*int_lumi*scale_factor-int_bin)/(3534208*int_bin));
    histo_TTG->SetBinError(i,err_bin);
  }
  Float_t err_TTG = 0.0;
  if(int_TTG > 0.0)
    err_TTG = sqrt(int_TTG*int_TTG*((electron_scale_factor_unc*electron_scale_factor_unc)+(photon_scale_factor_unc*photon_scale_factor_unc)+(3.779e+00*int_lumi*scale_factor-int_TTG)/(3534208*int_TTG))+(jeserr_TTG*jeserr_TTG)+(peserr_TTG*peserr_TTG));
  total_background += int_TTG;
  background_unc_sumsquares += err_TTG*err_TTG;
  // histo_TTG->SetFillColor(kOrange);
  histo_TTG->SetFillColor(kOrange-3);
  histo_vector.push_back(histo_TTG);
  
  TFile *f_TG = new TFile("WenG_JESPES_TGJets.root");
  TH1F* histo_TG = (TH1F*)f_TG->Get(histname);
  TH1F* histo_TG_JESUp = (TH1F*)f_TG->Get(histname_JESUp);
  TH1F* histo_TG_JESDown = (TH1F*)f_TG->Get(histname_JESDown);
  TH1F* histo_TG_PESUp = (TH1F*)f_TG->Get(histname_PESUp);
  TH1F* histo_TG_PESDown = (TH1F*)f_TG->Get(histname_PESDown);
  histo_TG->SetStats(0);
  histo_TG->Scale(int_lumi*scale_factor*2.997/1965000);
  histo_TG_JESUp->Scale(int_lumi*scale_factor*2.997/1965000);
  histo_TG_JESDown->Scale(int_lumi*scale_factor*2.997/1965000);
  histo_TG_PESUp->Scale(int_lumi*scale_factor*2.997/1965000);
  histo_TG_PESDown->Scale(int_lumi*scale_factor*2.997/1965000);
  Float_t int_TG = histo_TG->Integral()+histo_TG->GetBinContent(0)+histo_TG->GetBinContent(nBins+1);
  Float_t int_TG_JESUp = histo_TG_JESUp->Integral()+histo_TG_JESUp->GetBinContent(0)+histo_TG_JESUp->GetBinContent(nBins+1);
  Float_t int_TG_JESDown = histo_TG_JESDown->Integral()+histo_TG_JESDown->GetBinContent(0)+histo_TG_JESDown->GetBinContent(nBins+1);
  Float_t int_TG_PESUp = histo_TG_PESUp->Integral()+histo_TG_PESUp->GetBinContent(0)+histo_TG_PESUp->GetBinContent(nBins+1);
  Float_t int_TG_PESDown = histo_TG_PESDown->Integral()+histo_TG_PESDown->GetBinContent(0)+histo_TG_PESDown->GetBinContent(nBins+1);
  double jeserr_TG = (fabs(int_TG_JESUp-int_TG)+fabs(int_TG_JESDown-int_TG))/2.0;
  double peserr_TG = (fabs(int_TG_PESUp-int_TG)+fabs(int_TG_PESDown-int_TG))/2.0;
  for(int i = 1; i <= nBins; i++){
    double int_bin = histo_TG->GetBinContent(i);
    double jesup = histo_TG_JESUp->GetBinContent(i);
    double jesdown = histo_TG_JESDown->GetBinContent(i);
    double pesup = histo_TG_PESUp->GetBinContent(i);
    double pesdown = histo_TG_PESDown->GetBinContent(i);
    jesup_shift[i-1] += jesup-int_bin;
    jesdown_shift[i-1] += jesdown-int_bin;
    pesup_shift[i-1] += pesup-int_bin;
    pesdown_shift[i-1] += pesdown-int_bin;
    // cout<<"TG: bin="<<i<<",int_bin="<<int_bin<<",jesup="<<jesup<<",jesdown="<<jesdown<<",pesup="<<pesup<<",pesdown="<<pesdown<<endl;
    
    double err_bin = 0.0;
    if(int_bin > 0)
      err_bin = int_bin*sqrt((2.997*int_lumi*scale_factor-int_bin)/(1965000*int_bin));
    histo_TG->SetBinError(i,err_bin);
  }
  Float_t err_TG = 0.0;
  if(int_TG > 0.0)
    err_TG = sqrt(int_TG*int_TG*((electron_scale_factor_unc*electron_scale_factor_unc)+(photon_scale_factor_unc*photon_scale_factor_unc)+(2.997*int_lumi*scale_factor-int_TG)/(1965000*int_TG))+(jeserr_TG*jeserr_TG)+(peserr_TG*peserr_TG));
  total_background += int_TG;
  background_unc_sumsquares += err_TG*err_TG;
  histo_TG->SetFillColor(kRed-4);
  histo_vector.push_back(histo_TG);
  // histo_TG->SetFillColor(kBlue-2);

  
  
  TFile* f_diphoton = new TFile("WenG_JESPES_Dipho.root");
  TH1F* histo_diphoton = (TH1F*)f_diphoton->Get(histname);
  TH1F* histo_diphoton_JESUp = (TH1F*)f_diphoton->Get(histname_JESUp);
  TH1F* histo_diphoton_JESDown = (TH1F*)f_diphoton->Get(histname_JESDown);
  TH1F* histo_diphoton_PESUp = (TH1F*)f_diphoton->Get(histname_PESUp);
  TH1F* histo_diphoton_PESDown = (TH1F*)f_diphoton->Get(histname_PESDown);
  histo_diphoton->SetStats(0);
  histo_diphoton->Scale(int_lumi*scale_factor*1.273e+02/4828755 );
  histo_diphoton_JESUp->Scale(int_lumi*scale_factor*1.273e+02/4828755 );
  histo_diphoton_JESDown->Scale(int_lumi*scale_factor*1.273e+02/4828755 );
  histo_diphoton_PESUp->Scale(int_lumi*scale_factor*1.273e+02/4828755 );
  histo_diphoton_PESDown->Scale(int_lumi*scale_factor*1.273e+02/4828755 );
  Float_t int_diphoton = histo_diphoton->Integral()+histo_diphoton->GetBinContent(0)+histo_diphoton->GetBinContent(nBins+1);
  Float_t int_diphoton_JESUp = histo_diphoton_JESUp->Integral()+histo_diphoton_JESUp->GetBinContent(0)+histo_diphoton_JESUp->GetBinContent(nBins+1);
  Float_t int_diphoton_JESDown = histo_diphoton_JESDown->Integral()+histo_diphoton_JESDown->GetBinContent(0)+histo_diphoton_JESDown->GetBinContent(nBins+1);
  Float_t int_diphoton_PESUp = histo_diphoton_PESUp->Integral()+histo_diphoton_PESUp->GetBinContent(0)+histo_diphoton_PESUp->GetBinContent(nBins+1);
  Float_t int_diphoton_PESDown = histo_diphoton_PESDown->Integral()+histo_diphoton_PESDown->GetBinContent(0)+histo_diphoton_PESDown->GetBinContent(nBins+1);
  double jeserr_diphoton = (fabs(int_diphoton_JESUp-int_diphoton)+fabs(int_diphoton_JESDown-int_diphoton))/2.0;
  double peserr_diphoton = (fabs(int_diphoton_PESUp-int_diphoton)+fabs(int_diphoton_PESDown-int_diphoton))/2.0;
  for(int i = 1; i <= nBins; i++){
    double int_bin = histo_diphoton->GetBinContent(i);
    double jesup = histo_diphoton_JESUp->GetBinContent(i);
    double jesdown = histo_diphoton_JESDown->GetBinContent(i);
    double pesup = histo_diphoton_PESUp->GetBinContent(i);
    double pesdown = histo_diphoton_PESDown->GetBinContent(i);
    jesup_shift[i-1] += jesup-int_bin;
    jesdown_shift[i-1] += jesdown-int_bin;
    pesup_shift[i-1] += pesup-int_bin;
    pesdown_shift[i-1] += pesdown-int_bin;
    // cout<<"diphoton: bin="<<i<<",int_bin="<<int_bin<<",jesup="<<jesup<<",jesdown="<<jesdown<<",pesup="<<pesup<<",pesdown="<<pesdown<<endl;
    
    double err_bin = 0.0;
    if(int_bin > 0)
      err_bin = int_bin*sqrt((1.273e+02*int_lumi*scale_factor-int_bin)/(4828755 *int_bin));
    histo_diphoton->SetBinError(i,err_bin);
  }
  Float_t err_diphoton = 0.0;
  if(int_diphoton > 0.0)
    err_diphoton = sqrt(int_diphoton*int_diphoton*((photon_scale_factor_unc*photon_scale_factor_unc)+(1.273e+02*int_lumi*scale_factor-int_diphoton)/(4828755 *int_diphoton))+(jeserr_diphoton*jeserr_diphoton)+(peserr_diphoton*peserr_diphoton));
  total_background += int_diphoton;
  background_unc_sumsquares += err_diphoton*err_diphoton;
  histo_diphoton->SetFillColor(kMagenta+1);
  histo_vector.push_back(histo_diphoton);
  
  TFile *f_WZ = new TFile("WenG_JESPES_WZ.root");
  TH1F* histo_WZ = (TH1F*)f_WZ->Get(histname);
  TH1F* histo_WZ_JESUp = (TH1F*)f_WZ->Get(histname_JESUp);
  TH1F* histo_WZ_JESDown = (TH1F*)f_WZ->Get(histname_JESDown);
  TH1F* histo_WZ_PESUp = (TH1F*)f_WZ->Get(histname_PESUp);
  TH1F* histo_WZ_PESDown = (TH1F*)f_WZ->Get(histname_PESDown);
  histo_WZ->SetStats(0);
  histo_WZ->Scale(int_lumi*scale_factor*2.756e+01/7889000);
  histo_WZ_JESUp->Scale(int_lumi*scale_factor*2.756e+01/7889000);
  histo_WZ_JESDown->Scale(int_lumi*scale_factor*2.756e+01/7889000);
  histo_WZ_PESUp->Scale(int_lumi*scale_factor*2.756e+01/7889000);
  histo_WZ_PESDown->Scale(int_lumi*scale_factor*2.756e+01/7889000);
  Float_t int_WZ = histo_WZ->Integral()+histo_WZ->GetBinContent(0)+histo_WZ->GetBinContent(nBins+1);
  Float_t int_WZ_JESUp = histo_WZ_JESUp->Integral()+histo_WZ_JESUp->GetBinContent(0)+histo_WZ_JESUp->GetBinContent(nBins+1);
  Float_t int_WZ_JESDown = histo_WZ_JESDown->Integral()+histo_WZ_JESDown->GetBinContent(0)+histo_WZ_JESDown->GetBinContent(nBins+1);
  Float_t int_WZ_PESUp = histo_WZ_PESUp->Integral()+histo_WZ_PESUp->GetBinContent(0)+histo_WZ_PESUp->GetBinContent(nBins+1);
  Float_t int_WZ_PESDown = histo_WZ_PESDown->Integral()+histo_WZ_PESDown->GetBinContent(0)+histo_WZ_PESDown->GetBinContent(nBins+1);
  double jeserr_WZ = (fabs(int_WZ_JESUp-int_WZ)+fabs(int_WZ_JESDown-int_WZ))/2.0;
  double peserr_WZ = (fabs(int_WZ_PESUp-int_WZ)+fabs(int_WZ_PESDown-int_WZ))/2.0;
  for(int i = 1; i <= nBins; i++){
    double int_bin = histo_WZ->GetBinContent(i);
    double jesup = histo_WZ_JESUp->GetBinContent(i);
    double jesdown = histo_WZ_JESDown->GetBinContent(i);
    double pesup = histo_WZ_PESUp->GetBinContent(i);
    double pesdown = histo_WZ_PESDown->GetBinContent(i);
    jesup_shift[i-1] += jesup-int_bin;
    jesdown_shift[i-1] += jesdown-int_bin;
    pesup_shift[i-1] += pesup-int_bin;
    pesdown_shift[i-1] += pesdown-int_bin;
    // cout<<"WZ: bin="<<i<<",int_bin="<<int_bin<<",jesup="<<jesup<<",jesdown="<<jesdown<<",pesup="<<pesup<<",pesdown="<<pesdown<<endl;
    
    double err_bin = 0.0;
    if(int_bin > 0)
      err_bin = int_bin*sqrt((2.756e+01*int_lumi*scale_factor-int_bin)/(7889000*int_bin));
    histo_WZ->SetBinError(i,err_bin);
  }
  Float_t err_WZ = 0.0;
  if(int_WZ > 0.0)
    err_WZ = sqrt(int_WZ*int_WZ*((electron_scale_factor_unc*electron_scale_factor_unc)+(photon_scale_factor_unc*photon_scale_factor_unc)+(2.756e+01*int_lumi*scale_factor-int_WZ)/(7889000*int_WZ))+(jeserr_WZ*jeserr_WZ)+(peserr_WZ*peserr_WZ));
  total_background += int_WZ;
  background_unc_sumsquares += err_WZ*err_WZ;
  // histo_WZ->SetFillColor(kBlue-4);
  histo_WZ->SetFillColor(kRed-5);
  histo_vector.push_back(histo_WZ);
 

  TFile *f_WW = new TFile("WenG_JESPES_WW.root");
  TH1F* histo_WW = (TH1F*)((TH1F*)f_WW->Get(histname))->Clone("histo_WW");
  histo_WW->SetBinContent(nBins, histo_WW->GetBinContent(nBins)+histo_WW->GetBinContent(nBins+1));
  histo_WW->ClearUnderflowAndOverflow();
  TH1F* histo_WW_JESUp = (TH1F*)((TH1F*)f_WW->Get(histname_JESUp))->Clone("histo_WW_JESUp");
  histo_WW_JESUp->SetBinContent(nBins, histo_WW_JESUp->GetBinContent(nBins)+histo_WW_JESUp->GetBinContent(nBins+1));
  histo_WW_JESUp->ClearUnderflowAndOverflow();
  TH1F* histo_WW_JESDown = (TH1F*)((TH1F*)f_WW->Get(histname_JESDown))->Clone("histo_WW_JESDown");
  histo_WW_JESDown->SetBinContent(nBins, histo_WW_JESDown->GetBinContent(nBins)+histo_WW_JESDown->GetBinContent(nBins+1));
  histo_WW_JESDown->ClearUnderflowAndOverflow();
  TH1F* histo_WW_PESUp = (TH1F*)((TH1F*)f_WW->Get(histname_PESUp))->Clone("histo_WW_PESUp");
  histo_WW_PESUp->SetBinContent(nBins, histo_WW_PESUp->GetBinContent(nBins)+histo_WW_PESUp->GetBinContent(nBins+1));
  histo_WW_PESUp->ClearUnderflowAndOverflow();
  TH1F* histo_WW_PESDown = (TH1F*)((TH1F*)f_WW->Get(histname_PESDown))->Clone("histo_WW_PESDown");
  histo_WW_PESDown->SetBinContent(nBins, histo_WW_PESDown->GetBinContent(nBins)+histo_WW_PESDown->GetBinContent(nBins+1));
  histo_WW_PESDown->ClearUnderflowAndOverflow();
  histo_WW->SetStats(0);
  histo_WW->Scale(int_lumi*scale_factor*7.588e+01/15634000);
  histo_WW_JESUp->Scale(int_lumi*scale_factor*7.588e+01/15634000);
  histo_WW_JESDown->Scale(int_lumi*scale_factor*7.588e+01/15634000);
  histo_WW_PESUp->Scale(int_lumi*scale_factor*7.588e+01/15634000);
  histo_WW_PESDown->Scale(int_lumi*scale_factor*7.588e+01/15634000);
  Float_t int_WW = histo_WW->Integral();
  Float_t int_WW_JESUp = histo_WW_JESUp->Integral();
  Float_t int_WW_JESDown = histo_WW_JESDown->Integral();
  Float_t int_WW_PESUp = histo_WW_PESUp->Integral();
  Float_t int_WW_PESDown = histo_WW_PESDown->Integral();
  double jeserr_WW = (fabs(int_WW_JESUp-int_WW)+fabs(int_WW_JESDown-int_WW))/2.0;
  double peserr_WW = (fabs(int_WW_PESUp-int_WW)+fabs(int_WW_PESDown-int_WW))/2.0;
  for(int i = 1; i <= nBins; i++){
    double int_bin = histo_WW->GetBinContent(i);
    double jesup = histo_WW_JESUp->GetBinContent(i);
    double jesdown = histo_WW_JESDown->GetBinContent(i);
    double pesup = histo_WW_PESUp->GetBinContent(i);
    double pesdown = histo_WW_PESDown->GetBinContent(i);
    jesup_shift[i-1] += jesup-int_bin;
    jesdown_shift[i-1] += jesdown-int_bin;
    pesup_shift[i-1] += pesup-int_bin;
    pesdown_shift[i-1] += pesdown-int_bin;
    // cout<<"WW: bin="<<i<<",int_bin="<<int_bin<<",jesup="<<jesup<<",jesdown="<<jesdown<<",pesup="<<pesup<<",pesdown="<<pesdown<<endl;
    
    double err_bin = 0.0;
    if(int_bin > 0)
      err_bin = int_bin*sqrt((7.588e+01*int_lumi*scale_factor-int_bin)/(15634000*int_bin));
    histo_WW->SetBinError(i,err_bin);
  }
  Float_t err_WW = 0.0;
  if(int_WW > 0.0)
    err_WW = sqrt(int_WW*int_WW*((electron_scale_factor_unc*electron_scale_factor_unc)+(photon_scale_factor_unc*photon_scale_factor_unc)+(7.588e+01*int_lumi*scale_factor-int_WW)/(15634000*int_WW))+(jeserr_WW*jeserr_WW)+(peserr_WW*peserr_WW));
  total_background += int_WW;
  background_unc_sumsquares += err_WW*err_WW;
  // histo_WW->SetFillColor(kRed-10);
  histo_WW->SetFillColor(kRed-5);
  histo_vector.push_back(histo_WW);
    
 
  if (histname == "Photon_Et_range_5")
    
    {
      TFile* f_WenG_histos = new TFile("WenG_histos.root","RECREATE");
      f_WenG_histos->cd();
      histo_data->Write();
      histo_jetfake->Write();
      histo_WG->Write();
      histo_ZllG->Write();
      histo_TTG->Write();
      histo_TG->Write();
      histo_diphoton->Write();
      histo_WZ->Write();
      f_WenG_histos->Close();
    }
  
  if (histname == "Photon_Et_range_5" || histname == "h_photonic_recoil_5"){
  
    for(int i = 1; i <= nBins; i++){
      double binWidth = histo_data->GetBinWidth(i);
      histo_data->SetBinContent(i,histo_data->GetBinContent(i)/binWidth);
      histo_data->SetBinError(i,histo_data->GetBinError(i)/binWidth);
      histo_WG->SetBinContent(i,histo_WG->GetBinContent(i)/binWidth);
      histo_WG->SetBinError(i,histo_WG->GetBinError(i)/binWidth);
      histo_TG->SetBinContent(i,histo_TG->GetBinContent(i)/binWidth);
      histo_TG->SetBinError(i,histo_TG->GetBinError(i)/binWidth);
      histo_jetfake->SetBinContent(i,histo_jetfake->GetBinContent(i)/binWidth);
      histo_jetfake->SetBinError(i,histo_jetfake->GetBinError(i)/binWidth);
      histo_elefake->SetBinContent(i,histo_elefake->GetBinContent(i)/binWidth);
      histo_elefake->SetBinError(i,histo_elefake->GetBinError(i)/binWidth);
      histo_WZ->SetBinContent(i,histo_WZ->GetBinContent(i)/binWidth);
      histo_WZ->SetBinError(i,histo_WZ->GetBinError(i)/binWidth);
      histo_WW->SetBinContent(i,histo_WW->GetBinContent(i)/binWidth);
      histo_WW->SetBinError(i,histo_WW->GetBinError(i)/binWidth);
      histo_ZllG->SetBinContent(i,histo_ZllG->GetBinContent(i)/binWidth);
      histo_ZllG->SetBinError(i,histo_ZllG->GetBinError(i)/binWidth);
      histo_TTG->SetBinContent(i,histo_TTG->GetBinContent(i)/binWidth);
      histo_TTG->SetBinError(i,histo_TTG->GetBinError(i)/binWidth);
      histo_diphoton->SetBinContent(i,histo_diphoton->GetBinContent(i)/binWidth);
      histo_diphoton->SetBinError(i,histo_diphoton->GetBinError(i)/binWidth);
    }
  }
  TPad *pad1 = new TPad("pad1","pad1",0.01,0.26,0.99,0.99);
  pad1->Draw(); pad1->cd();
  pad1->SetFillColor(0); pad1->SetFrameBorderMode(0); pad1->SetBorderMode(0);
  pad1->SetBottomMargin(0.);
  
  TH1F *histo_allbackgrounds = (TH1F*)histo_WG->Clone("histo_allbackgrounds");
  histo_allbackgrounds->Add(histo_TG);
  histo_allbackgrounds->Add(histo_elefake);
  histo_allbackgrounds->Add(histo_WZ);
  histo_allbackgrounds->Add(histo_WW);
  histo_allbackgrounds->Add(histo_ZllG);
  histo_allbackgrounds->Add(histo_diphoton);
  histo_allbackgrounds->Add(histo_jetfake);
  histo_allbackgrounds->Add(histo_TTG);
  for(int i = 1; i <= nBins; i++){
    double background = histo_allbackgrounds->GetBinContent(i);
    // Add statistical errors
    double sum_binerrors_squared = 0.0;
    sum_binerrors_squared += pow(histo_WG->GetBinError(i),2);
    sum_binerrors_squared += pow(histo_TG->GetBinError(i),2);
    sum_binerrors_squared += pow(histo_jetfake->GetBinError(i),2);
    sum_binerrors_squared += pow(histo_WZ->GetBinError(i),2);
    sum_binerrors_squared += pow(histo_ZllG->GetBinError(i),2);
    sum_binerrors_squared += pow(histo_TTG->GetBinError(i),2);
    sum_binerrors_squared += pow(histo_diphoton->GetBinError(i),2);
    double binerror = sqrt(sum_binerrors_squared); // Include just the statistical error
    double jeserr = (fabs(jesup_shift[i-1])+fabs(jesdown_shift[i-1]))/2.0;
    double peserr = (fabs(pesup_shift[i-1])+fabs(pesdown_shift[i-1]))/2.0;
    double renerr = (fabs(renup_shift[i-1])+fabs(rendown_shift[i-1]))/2.0;
    double facerr = (fabs(facup_shift[i-1])+fabs(facdown_shift[i-1]))/2.0;
    double pdferr = (fabs(pdfup_shift[i-1])+fabs(pdfdown_shift[i-1]))/2.0;
    if (histname == "Photon_Et_range_5" || histname == "h_photonic_recoil_5"){
    
      double binWidth = histo_data->GetBinWidth(i);
      jeserr /= binWidth;
      peserr /= binWidth;
      renerr /= binWidth;
      facerr /= binWidth;
      pdferr /= binWidth;
    }
    binerror = sqrt(sum_binerrors_squared+pow(background*photon_scale_factor_unc,2)+pow(background*electron_scale_factor_unc,2)+pow(jeserr,2)+pow(peserr,2)+pow(renerr,2)+pow(facerr,2)+pow(pdferr,2));
    histo_allbackgrounds->SetBinError(i,binerror);
  }
  histo_allbackgrounds->SetFillColorAlpha(kGray+1,0.6);
  histo_vector.push_back(histo_allbackgrounds);
  
  TH1F *histo_allbackgrounds_outline = (TH1F*)histo_allbackgrounds->Clone("histo_allbackgrounds_outline");
  histo_allbackgrounds_outline->SetFillColorAlpha(kWhite,0.0);
  histo_allbackgrounds_outline->SetLineWidth(1);
  histo_vector.push_back(histo_allbackgrounds_outline);
  histo_WZ->Add(histo_WW);
  histo_TTG->Add(histo_TG);
    
  THStack *stackHisto = new THStack("stackHisto","Title");
  stackHisto->Add(histo_ZllG);
  stackHisto->Add(histo_WZ);
  //nngamma 
  stackHisto->Add(histo_diphoton);
  stackHisto->Add(histo_elefake);
  stackHisto->Add(histo_jetfake);
  stackHisto->Add(histo_TTG);
  stackHisto->Add(histo_WG);
  stackHisto->SetTitle("");
  
  for(int i = 0; i < int(histo_vector.size()); i++){
    histo_vector[i]->SetStats(0);
    histo_vector[i]->SetTitle("");
    histo_vector[i]->GetXaxis()->SetTitle(xaxis_title);
    histo_vector[i]->GetXaxis()->SetLabelFont(42);
    histo_vector[i]->GetXaxis()->SetLabelSize(0.06);
    histo_vector[i]->GetXaxis()->SetTitleFont(42);
    histo_vector[i]->GetXaxis()->SetTitleSize(0.06);
    histo_vector[i]->GetYaxis()->SetTitle("Events / bin");
        if (histname == "Photon_Et_range_5" || histname == "h_photonic_recoil_5")
    //  if (histname == "Photon_Et_range_4" || histname == "h_photonic_recoil_4")
      histo_vector[i]->GetYaxis()->SetTitle("Events / GeV");
    histo_vector[i]->GetYaxis()->SetLabelFont(42);
    histo_vector[i]->GetYaxis()->SetLabelSize(0.06);
    histo_vector[i]->GetYaxis()->SetTitleFont(42);
    histo_vector[i]->GetYaxis()->SetTitleSize(0.06);
    histo_vector[i]->GetYaxis()->SetTitleOffset(0.9);
    histo_vector[i]->SetLineColor(kBlack);
  }
  
  //Accommodate both the data and background plots
  double ymax_data = 0.0;
  double ymax_background = 0.0;
  for(int i = 1; i <= nBins; i++){
    double y_data = histo_data->GetBinContent(i);
    double y_error_data = histo_data->GetBinError(i);
    double y_high_data = y_data+y_error_data;
    if(y_high_data > ymax_data)
      ymax_data = y_high_data;
    double y_background = histo_allbackgrounds->GetBinContent(i);
    double y_error_background = histo_allbackgrounds->GetBinError(i);
    double y_high_background = y_background+y_error_background;
    if(y_high_background > ymax_background)
      ymax_background = y_high_background;
  }
  
  double ymin = 0.0003;
  double ymax = 1.3*ymax_data;
  if(ymax_background > ymax_data)
    ymax = 1.3*ymax_background;
  if (histname == "Photon_Et_range_5" || histname == "h_photonic_recoil_5"){
  
    pad1->SetLogy();
    ymax *= 5;
  }
  // else if (histname == "nJet_5"){
  //   ymax = 2.0;
  // }
  histo_data->GetYaxis()->SetRangeUser(ymin,ymax);
  //  if(histname == "nJet_5")
  //    histo_data->GetXaxis()->SetRangeUser(0,10);
  histo_data->Draw();
  stackHisto->Draw("HIST SAME");
  histo_allbackgrounds->Draw("E2 SAME");
  histo_allbackgrounds_outline->Draw("HIST SAME");
  histo_data->SetLineColor(kBlack);
  histo_data->SetMarkerColor(kBlack);
  histo_data->Draw("E0 P0 SAME");
  gPad->RedrawAxis();
  
  //Central location of leg defined to be location of leg in phoPt plot
  TLegend* leg = new TLegend(0.5+leg_xoffset,0.46075+leg_yoffset,0.885387+leg_xoffset,0.862969+leg_yoffset,"");
  leg->AddEntry(histo_data,"Data");
  leg->AddEntry(histo_WG,"W#gamma#rightarrowl#nu#gamma","F");
  leg->AddEntry(histo_TTG,"tt#gamma","F");
  leg->AddEntry(histo_TG,"t#gamma","F");
  leg->AddEntry(histo_elefake,"e#rightarrow#gamma MisID","F");
  leg->AddEntry(histo_jetfake,"jet#rightarrow#gamma MisID","F");
  leg->AddEntry(histo_diphoton,"#gamma#gamma","F");
  leg->AddEntry(histo_WZ,"VV#gamma","F");
  //nn
  leg->AddEntry(histo_ZllG,"Z(ll)#gamma","F");
  leg->SetFillColor(kWhite);
  leg->SetShadowColor(0);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.040);
  leg->Draw();
  
  float lumiTextSize = 0.6;
  float lumiTextOffset = 0.2;
  float cmsTextSize = 0.75;
  TLatex *texS = new TLatex(0.60023,0.917173,"41.53 fb^{-1} (13 TeV)");
  texS->SetNDC();
  texS->SetTextFont(42);
  texS->SetTextSize(lumiTextSize*t_m);
  texS->Draw();
  TLatex *texS1 = new TLatex(0.13592,0.817173,"#bf{CMS} #it{Preliminary}");
  texS1->SetNDC();
  texS1->SetTextFont(42);
  texS1->SetTextSize(cmsTextSize*t_m);
  texS1->Draw();
  
  c->cd();
  TPad *pad2 = new TPad("pad2","pad2",0.01,0.01,0.99,0.26);
  pad2->Draw(); pad2->cd();
  pad2->SetFillColor(0); pad2->SetFrameBorderMode(0); pad2->SetBorderMode(0);
  pad2->SetTopMargin(0.0);
  pad2->SetBottomMargin(0.35);
  
  double max_ratio = 3.5;
  
  TH1F* Ratio = (TH1F*)histo_data->Clone("Ratio");
  TH1F* Ratio_background = (TH1F*)histo_allbackgrounds->Clone("Ratio_background");
  for(int i = 1; i <= nBins; i++){
    double y_data = histo_data->GetBinContent(i);
    double y_error_data = histo_data->GetBinError(i);
    double y_background = histo_allbackgrounds->GetBinContent(i);
    double y_error_background = histo_allbackgrounds->GetBinError(i);
    double Ratiocontent = 0.0;
    double Ratioerror = max_ratio;
    double Ratioerror_background = max_ratio;
    if(y_background > 0.){
      Ratiocontent = y_data/y_background;
      Ratioerror_background = y_error_background/y_background;
      if(y_error_data > 0.)
        Ratioerror = y_error_data/y_background;
    }
    else if(y_data > 0.){
      Ratiocontent = 3.*max_ratio;
    }
    Ratio->SetBinContent(i,Ratiocontent);
    Ratio->SetBinError(i,Ratioerror);
    Ratio_background->SetBinContent(i,1);
    Ratio_background->SetBinError(i,Ratioerror_background);
  }
  
  //  Ratio_background->GetYaxis()->SetRangeUser(0.0,max_ratio-0.01);
  Ratio_background->GetYaxis()->SetRangeUser(0.0,2.1-0.01);
  Ratio_background->GetYaxis()->SetTitle("Data/SM");
  Ratio_background->GetYaxis()->CenterTitle();
  Ratio_background->GetYaxis()->SetLabelSize(0.14);
  Ratio_background->GetYaxis()->SetTitleSize(0.15);
  Ratio_background->GetYaxis()->SetLabelFont(42);
  Ratio_background->GetYaxis()->SetTitleFont(42);
  Ratio_background->GetYaxis()->SetTitleOffset(0.30);
  Ratio_background->GetYaxis()->SetNdivisions(305);
  Ratio_background->GetXaxis()->SetTitle(xaxis_title);
  Ratio_background->GetXaxis()->SetLabelSize(0.16);
  Ratio_background->GetXaxis()->SetTitleSize(0.18);
  Ratio_background->GetXaxis()->SetLabelFont(42);
  Ratio_background->GetXaxis()->SetTitleFont(42);
  Ratio_background->GetXaxis()->SetTitleOffset(0.9);
  Ratio_background->GetXaxis()->SetTickLength(0.05);
  Ratio_background->SetStats(0);
  Ratio->SetMarkerStyle(0);
  double xmin = histo_data->GetXaxis()->GetBinLowEdge(1);
  double xmax = histo_data->GetXaxis()->GetBinUpEdge(nBins);
  TLine* line = new TLine(xmin,1.,xmax,1.);
  line->SetLineStyle(2);
  line->SetLineColor(kBlack);
  gStyle->SetLineStyleString(11,"3 12");
  TLine* line0 = new TLine(xmin,0.5,xmax,0.5);
  line0->SetLineStyle(11);
  line0->SetLineColor(kBlack);
  Ratio_background->Draw("E2");
  line->Draw("SAME");
  line0->Draw("SAME");
  for(int i = 1; i <= (2*max_ratio-3); i++){
    double y_coord = 1.0 + 0.5*i;
    TLine* line_i = new TLine(xmin,y_coord,xmax,y_coord);
    line_i->SetLineStyle(11);
    line_i->SetLineColor(kBlack);
    line_i->Draw("SAME");
  }
  Ratio->Draw("E0 P0 SAME");

  double background_unc = sqrt(background_unc_sumsquares);
  
  if (histname == "Photon_Et_range_5"){
  
    cout<<"WenG region"<<endl;
    cout<<"------------------------------------"<<endl;
    cout<<"Electron faking photon: "<<int_elefake<<" +- "<<err_elefake<<endl;
    cout<<"Z(ll)+Gamma: "<<int_ZllG<<" +- "<<err_ZllG<<endl;
    cout<<"tt+Gamma: "<<int_TTG<<" +- "<<err_TTG<<endl;
    cout<<"t+Gamma: "<<int_TG<<" +- "<<err_TG<<endl;
    cout<<"Diphoton: "<<int_diphoton<<" +- "<<err_diphoton<<endl;
    cout<<"QCD fakes: "<<int_QCD<<" +- "<<err_QCD<<endl;
    cout<<"W+gamma: "<<int_WG<<" +- "<<err_WG<<endl;
    cout<<"WZ: "<<int_WZ<<" +- "<<err_WZ<<endl;
    cout<<"WW: "<<int_WW<<" +- "<<err_WW<<endl;
    cout<<"Total background: "<<total_background<<" +- "<<background_unc<<endl;
    cout<<"------------------------------------"<<endl;
    cout<<"Data: "<<int_data<<endl;
    cout<<"------------------------------------"<<endl;
  }

  c->SaveAs(TString("weng_elefake"+plotname+".png"));
  //  c->SaveAs(TString("weng_"+plotname+".pdf"));
  delete(c);
}

void weng_plotter_test()
{
  std::vector<string> histnames;
  histnames.clear();
  std::vector<Double_t> leg_xoffsets;
  leg_xoffsets.clear();
  std::vector<Double_t> leg_yoffsets;
  leg_yoffsets.clear();
  std::vector<TString> xaxis_titles;
  xaxis_titles.clear();
  std::vector<TString> plotnames;
  plotnames.clear();

  //  histnames.push_back(TString("_4"));
  //  leg_xoffsets.push_back(0.);
  //  leg_yoffsets.push_back(0.);
  //  xaxis_titles.push_back(TString(""));
  //  plotnames.push_back(TString(""));

  histnames.push_back("Photon_Et_range");
  leg_xoffsets.push_back(0.);
  leg_yoffsets.push_back(0.);
  xaxis_titles.push_back(TString("Photon #it{p}_{T} [GeV]"));
  plotnames.push_back(TString("phoPt"));

  histnames.push_back("h_photon_SCEta");
  leg_xoffsets.push_back(0.);
  leg_yoffsets.push_back(0.);
  xaxis_titles.push_back(TString("Photon #eta"));
  plotnames.push_back(TString("phoEta"));

  histnames.push_back("h_photon_SCPhi");
  leg_xoffsets.push_back(0.);
  leg_yoffsets.push_back(0.);
  xaxis_titles.push_back(TString("Photon #phi"));
  plotnames.push_back(TString("phoPhi"));

  histnames.push_back("pfMET");
  leg_xoffsets.push_back(0.);
  leg_yoffsets.push_back(0.);
  xaxis_titles.push_back(TString("pfMET [GeV]"));
  plotnames.push_back(TString("pfMET"));

  histnames.push_back("nJet");
  leg_xoffsets.push_back(0.);
  leg_yoffsets.push_back(0.);
  xaxis_titles.push_back(TString("Number of Jets"));
  plotnames.push_back(TString("nJet"));

  histnames.push_back("h_photonic_recoil");
  leg_xoffsets.push_back(0.);
  leg_yoffsets.push_back(0.);
  xaxis_titles.push_back(TString("Recoil [GeV]"));
  plotnames.push_back(TString("recoil"));

  histnames.push_back("h_dPhi_phoRecoil");
  leg_xoffsets.push_back(0.);
  leg_yoffsets.push_back(0.);
  xaxis_titles.push_back(TString("#Delta#phi(Photon,Recoil)"));
  plotnames.push_back(TString("dPhiPhoRecoil"));

  histnames.push_back("h_leptonPt");
  leg_xoffsets.push_back(0.);
  leg_yoffsets.push_back(0.);
  xaxis_titles.push_back(TString("Electron #it{p}_{T} [GeV]"));
  plotnames.push_back(TString("elePt"));

  histnames.push_back("h_leptonEta");
  leg_xoffsets.push_back(0.15);
  leg_yoffsets.push_back(0.);
  xaxis_titles.push_back(TString("Electron #eta"));
  plotnames.push_back(TString("eleEta"));

  histnames.push_back("h_leptonPhi");
  leg_xoffsets.push_back(0.);
  leg_yoffsets.push_back(0.);
  xaxis_titles.push_back(TString("Electron #phi"));
  plotnames.push_back(TString("elePhi"));

  histnames.push_back("h_phoPT_over_photonicRecoil");
  leg_xoffsets.push_back(0.);
  leg_yoffsets.push_back(0.);
  xaxis_titles.push_back(TString("Photon #it{p}_{T} / Recoil"));
  plotnames.push_back(TString("phoPtOverRecoil"));

  histnames.push_back("h_leptonPt_over_pfMET");
  leg_xoffsets.push_back(0.);
  leg_yoffsets.push_back(0.);
  xaxis_titles.push_back(TString("Electron #it{p}_{T} / pfMET"));
  plotnames.push_back(TString("elePtOverpfMET"));

  histnames.push_back("h_lepMET_MT");
  leg_xoffsets.push_back(0.);
  leg_yoffsets.push_back(0.);
  xaxis_titles.push_back(TString("Electron + pfMET m_{T} [GeV]"));
  plotnames.push_back(TString("eleMETmT"));

  histnames.push_back("h_min_dphijetmet");
  leg_xoffsets.push_back(0.);
  leg_yoffsets.push_back(0.);
  xaxis_titles.push_back(TString("Min. #Delta#phi(jets,MET)"));
  plotnames.push_back(TString("dPhiJetsMET"));

  histnames.push_back("h_min_dphijetrecoil");
  leg_xoffsets.push_back(0.);
  leg_yoffsets.push_back(0.);
  xaxis_titles.push_back(TString("Min. #Delta#phi(jets,Recoil)"));
  plotnames.push_back(TString("dphiJetsRecoil"));

  histnames.push_back("h_dPhi_lepMET");
  leg_xoffsets.push_back(0.);
  leg_yoffsets.push_back(0.);
  xaxis_titles.push_back(TString("#Delta#phi(Electron,MET)"));
  plotnames.push_back(TString("dPhiEleMET"));
  histnames.push_back("leadingJetPt");
  leg_xoffsets.push_back(0.);
  leg_yoffsets.push_back(0.);
  xaxis_titles.push_back(TString("JetPt"));
  plotnames.push_back(TString("jetPt"));

  for(int i = 0; i < histnames.size(); i++){
    plot(histnames[i],leg_xoffsets[i],leg_yoffsets[i],xaxis_titles[i],plotnames[i]);
  }
}
