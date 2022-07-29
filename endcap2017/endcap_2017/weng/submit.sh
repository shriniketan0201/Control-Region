./rootcom postAnalyzerWenug Weu_mc
./rootcom postAnalyzerwg WenG_mc_wg
./rootcom postAnalyzerz WenG_mc_zg



./MakeCondorFiles.sh Weu_mc davs://cmsxrootd.hep.wisc.edu:1094//store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017_MiniAODv2/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/crab_job_TTGJets/220129_021831/0000/ WenG_JESPES_TTGJets.root -1 10000 WenG_JESPES_TTGJets egammaEffi.txt_EGM2D_Tight_UL17.root ewk_corr.root

./MakeCondorFiles.sh Weu_mc davs://cmsxrootd.hep.wisc.edu:1094//store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017MiniAODv2/TGJets_TuneCP5_13TeV-amcatnlo-madspin-pythia8/crab_job_TGJets/220317_010930/0000/ WenG_JESPES_TGJets.root -1 10000 WenG_JESPES_TGjets  egammaEffi.txt_EGM2D_Tight_UL17.root ewk_corr.root

./MakeCondorFiles.sh Weu_mc davs://cmsxrootd.hep.wisc.edu:1094//store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017_MiniAODv2/DiPhotonJets_MGG-80toInf_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_job_DiPhotonJets/220129_022659/0000/ WenG_JESPES_Diphoton.root -1 10000 WenG_JESPES_Dipho egammaEffi.txt_EGM2D_Tight_UL17.root ewk_corr.root

./MakeCondorFiles.sh Weu_mc davs://cmsxrootd.hep.wisc.edu:1094//store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017_MiniAODv2/WW_TuneCP5_13TeV-pythia8/crab_job_WW/220129_021845/0000/ WenG_JESPES_WW.root -1 10000 WenG_JESPES_WW egammaEffi.txt_EGM2D_Tight_UL17.root ewk_corr.root

./MakeCondorFiles.sh Weu_mc davs://cmsxrootd.hep.wisc.edu:1094//store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017_MiniAODv2/ZZ_TuneCP5_13TeV-pythia8/crab_job_ZZ/220129_021916/0000/ WenG_JESPES_ZZ.root -1 10000 WenG_JESPES_ZZ egammaEffi.txt_EGM2D_Tight_UL17.root ewk_corr.root

./MakeCondorFiles.sh WenG_mc_zg davs://cmsxrootd.hep.wisc.edu:1094//store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017_MiniAODv2/ZLLGJets_MonoPhoton_PtG-130_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_job_ZLLGJets/220129_021716/0000/ WenG_JESPES_ZLLGJets_2.root -1 10000 WenG_JESPES_ZLL egammaEffi.txt_EGM2D_Tight_UL17.root ewk_corr.root

./MakeCondorFiles.sh Weu_mc davs://cmsxrootd.hep.wisc.edu:1094//store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017_MiniAODv2/WZ_TuneCP5_13TeV-pythia8/crab_job_WZ/220129_021900/0000/ WenG_JESPES_WZ.root -1 10000 WenG_JESPES_WZ egammaEffi.txt_EGM2D_Tight_UL17.root ewk_corr.root

./MakeCondorFiles.sh WenG_mc_wg davs://cmsxrootd.hep.wisc.edu:1094//store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017_MiniAODv2/WGJets_MonoPhoton_PtG-130_TuneCP5_13TeV-madgraph-pythia8/crab_job_WGJets_MonoPhoton_PtG_130/220129_021731/0000/ WenG_JESPES_WG_2.root -1 10000 WenG_JESPES_WG egammaEffi.txt_EGM2D_Tight_UL17.root ewk_corr.root  

# //above sample is LO sample below one is NLO Sample i have been using wrong sample so i have put this comment out just to remember the mistakes which i am doing //this  cost 2 days 

#./MakeCondorFiles.sh WmnG_mc_wg davs://cmsxrootd.hep.wisc.edu:1094//store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017_MiniAODv2/WGToLNuG_01J_5f_PtG_130_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_job_WGToLNuG_01J_5f_PtG_130/220129_021745/0000/ WmnG_JESPES_WG_2_latest.root -1 10000 WmnG_JESPES_WG Efficiencies_muon_generalTracks_Z_Run2017_UL_ID.root Efficiencies_muon_generalTracks_Z_Run2017_UL_ISO.root ewk_corr.root









./Weu_mc /T2_KR_KISTI/store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017MiniAODv2/TGJets_TuneCP5_13TeV-amcatnlo-madspin-pythia8/crab_job_TGJets/220317_010930/0000/ WenG_JESPES_TGJets.root -1 10000
