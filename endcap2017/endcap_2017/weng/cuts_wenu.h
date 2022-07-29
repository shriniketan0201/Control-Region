std::vector<int> postAnalyzer::getPhoCand(double phoPtCut, double phoEtaCut, Short_t isoBit){
  std::vector<int> tmpCand;
  tmpCand.clear();
  for(int p=0;p<nPho;p++)
    {
      Float_t uncorrectedPhoEt = ((*phoEt)[p]);
      //      bool kinematic = uncorrectedPhoEt > phoPtCut  && fabs((*phoSCEta)[p])<phoEtaCut;
      bool kinematic = uncorrectedPhoEt > phoPtCut  && fabs((*phoSCEta)[p])>1.566 && fabs((*phoSCEta)[p])<2.5;

      bool photonId = (
                       ((*phoHoverE)[p]                <  0.0109    ) &&
                       ((*phoSigmaIEtaIEtaFull5x5)[p]  <  0.026 ) &&
                       ((*phohasPixelSeed)[p]              ==  1      )&&
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



std::vector<int> postAnalyzer::electron_veto_tightID(int pho_index, float elePtCut)
{
  std::vector<int> ele_cands;
  ele_cands.clear();
  for(int i = 0; i < nEle; i++)
    {
      if(eleIDbit->at(i)>>2&1==1)
        {
	  if(elePt->at(i) > elePtCut && abs(eleEta->at(i)) < 2.5 )
            {
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
  std::vector<int> mu_cands;
  mu_cands.clear();
  for(int i = 0; i < nMu; i++)
    {
      if(muIDbit->at(i)>>3&1==1 && muIDbit->at(i)>>9&1==1)        
	{
	  if(muPt->at(i) > muPtCut && abs(muEta->at(i)) < 2.4 )        
	    {
              if(dR(muEta->at(i),muPhi->at(i),phoEta->at(pho_index),phoPhi->at(pho_index)) > 0.5)
                {
                  mu_cands.push_back(i);
                }
            }
        }
    }
  return mu_cands;
}

std::vector<int> postAnalyzer::electron_veto_looseID(int pho_index, int mu_index, float elePtCut)
{
  std::vector<int> ele_cands;
  ele_cands.clear();
  for(int i = 0; i < nEle; i++)
    {
      if(eleIDbit->at(i)>>0&1==1)
	
	{
	  if(elePt->at(i) > elePtCut && abs(eleEta->at(i)) < 2.5 )
            {
	      
              if(dR(eleEta->at(i),elePhi->at(i),phoEta->at(pho_index),phoPhi->at(pho_index)) > 0.5)
                {
                  ele_cands.push_back(i);
                }
            }
        }
    }
  return ele_cands;
}



std::vector<int> postAnalyzer::muon_veto_looseID(int pho_index, int ele_index, float muPtCut)
{
  std::vector<int> mu_cands;
  mu_cands.clear();
  for(int i = 0; i < nMu; i++)
    {
      if(muIDbit->at(i)>>0&1==1 && muIDbit->at(i)>>7&1==1)
	{
	  if(muPt->at(i) > muPtCut && abs(muEta->at(i)) < 2.4 )        
	    {
	      if(dR(muEta->at(i),muPhi->at(i),phoEta->at(pho_index),phoPhi->at(pho_index)) > 0.5 && dR(muEta->at(i),muPhi->at(i),eleEta->at(ele_index),elePhi->at(ele_index)) > 0.5)
		{
		  mu_cands.push_back(i);
		}
	    }
	}
    }
  return mu_cands;
  
}
std::vector<int> postAnalyzer::JetVetoDecision(int pho_index, int ele_index) {

  bool jetVeto=true;
  std::vector<int> jetindex;
  float value =0.0;

  for(int i = 0; i < nJet; i++)
    {
      if(0.0 < abs(jetEta->at(i)) && abs(jetEta->at(i)) <2.5)
        value =0.86;
      if(2.5 <= abs(jetEta->at(i)) && abs(jetEta->at(i)) <2.75)
        value =-0.10;
      if(2.75 <= abs(jetEta->at(i)) && abs(jetEta->at(i)) <3.0)
        value =-0.05;
      if(3.00 <= abs(jetEta->at(i)) && abs(jetEta->at(i)) <5.0)
        value =-0.01;
      
      double deltar = 0.0 ;
      double deltar_ele = 0.0;
      
      deltar= dR(jetEta->at(i),jetPhi->at(i),phoEta->at(pho_index),phoPhi->at(pho_index));
      deltar_ele = dR(jetEta->at(i),jetPhi->at(i),eleEta->at(ele_index),elePhi->at(ele_index));
      //std::cout<<"Delta R between photon and jet="<<dR<< "jet pt"<<pfJet_pt[i]<<std::endl; \
      
      if(deltar>0.4 && deltar_ele > 0.4 && jetPt->at(i) >30.0 && (jetID->at(i) >>1&1==1) && abs(jetEta->at(i))<5.0) 
        {
          jetindex.push_back(i);
        }

      
    }
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
  
  bool passes = false;
  int njetsMax = jets.size();
  
  if(njetsMax > 4)
    njetsMax = 4;
  int j = 0;
  for(; j < njetsMax; j++)
    {
      
      if(DeltaPhi(jetPhi->at(jets[j]),pfMETPhi) < 0.5)
        break;
    }
  if(j==njetsMax)
    passes = true;
  
  return passes;
}

double postAnalyzer::FakeRatePt(Float_t phoPt, int syst_number)
{


  /*  Float_t bin1[11] = {0.303537,0.304514,0.299726,0.297962,0.31297,0.304277,0.299551,0.309215,0.29773,0.307996,0.299078};
  Float_t bin2[11] = {0.298028,0.298402,0.298061,0.287888,0.306639,0.299296,0.293234,0.30409,0.292122,0.302939,0.293118};
  Float_t bin3[11] = {0.406485,0.404428,0.388505,0.38985,0.42444,0.403011,0.394846,0.417009,0.396109,0.416827,0.396143};
  Float_t bin4[11] = {0.610214,0.611106,0.621412,0.569974,0.63718,0.601306,0.619642,0.629268,0.592484,0.647198,0.573231};
  Float_t bin5[11] = {0.87848,1.12126,0.879364,0.83731,0.934397,0.841015,1.31338,0.94448,0.804299,1.14847,0.608489};
  */
  
  //fake rate egamma2016ID                                                                                                                                               
  Float_t bin1[11] = {0.127912,0.12656,0.130018,0.127249,0.127514,0.128716,0.125946,0.12986,0.125779,0.130247,0.125577};
  Float_t bin2[11] = {0.130086,0.127354,0.128756,0.129742,0.128357,0.130537,0.127225,0.132657,0.127301,0.132837,0.127336};
  Float_t bin3[11] = {0.168888,0.165167,0.173507,0.167206,0.169793,0.169516,0.16279,0.172816,0.164628,0.174577,0.163199};
  Float_t bin4[11] = {0.246274,0.249355,0.254842,0.253525,0.210587,0.241324,0.236697,0.25269,0.239962,0.266137,0.226412};
  Float_t bin5[11] = {0.381658,0.453696,0.298467,0.371258,0.242856,0.394216,0.375365,0.411912,0.355592,0.535912,0.227404};


  
  double weight = 1.0;
  if(phoPt <= 225.0)
    weight = 0;
  else if(225.0 < phoPt && phoPt <= 250.0)
    weight = bin1[syst_number];
  else if(250.0 < phoPt && phoPt <= 300.0)
    weight = bin2[syst_number];
  else if(300.0 < phoPt && phoPt <= 400.0)
    weight = bin3[syst_number];
  else if(400.0 < phoPt && phoPt <= 600.0)
    weight = bin4[syst_number];
  else if(600.0 < phoPt )
    weight = bin5[syst_number];
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

