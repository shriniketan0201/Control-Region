// Effective area to be needed in PF Iso for photon ID                                                                                                                                                                                                                  

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
