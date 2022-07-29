
./rootcom postAnalyzer_Wmng Wmu_mc
./rootcom postAnalyzerWZ WmnG_mc_WZ
./rootcom postAnalyzerWG WmnG_mc_wg
./rootcom postAnalyzerzg WmnG_mc_zg

#/T2_KR_KISTI/store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017MiniAODv2/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/crab_job_TTGJets/220317_010914/0000/


./MakeCondorFiles.sh Wmu_mc root://cms-t2-se01.sdfarm.kr:1096//store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017MiniAODv2/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/crab_job_TTGJets/220317_010914/0000/ WmnG_JESPES_TTGJets.root -1 10000  WmnG_JESPES_TTGJets Efficiencies_muon_generalTracks_Z_Run2017_UL_ID.root Efficiencies_muon_generalTracks_Z_Run2017_UL_ISO.root ewk_corr.root

./MakeCondorFiles.sh Wmu_mc root://cms-t2-se01.sdfarm.kr:1096//store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017MiniAODv2/TGJets_TuneCP5_13TeV-amcatnlo-madspin-pythia8/crab_job_TGJets/220317_010930/0000/ WmnG_JESPES_TGJets.root -1 10000  WmnG_JESPES_TGJets Efficiencies_muon_generalTracks_Z_Run2017_UL_ID.root Efficiencies_muon_generalTracks_Z_Run2017_UL_ISO.root ewk_corr.root

./MakeCondorFiles.sh Wmu_mc root://cms-t2-se01.sdfarm.kr:1096//store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017MiniAODv2/DiPhotonJets_MGG-80toInf_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_job_DiPhotonJets/220317_011208/0000/ WmnG_JESPES_Diphoton.root -1 10000  WmnG_JESPES_Diphoton Efficiencies_muon_generalTracks_Z_Run2017_UL_ID.root Efficiencies_muon_generalTracks_Z_Run2017_UL_ISO.root ewk_corr.root

./MakeCondorFiles.sh Wmu_mc root://cms-t2-se01.sdfarm.kr:1096//store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017MiniAODv2/WW_TuneCP5_13TeV-pythia8/crab_job_WW/220317_010944/0000/ WmnG_JESPES_WW.root -1 10000 WmnG_JESPES_WW Efficiencies_muon_generalTracks_Z_Run2017_UL_ID.root Efficiencies_muon_generalTracks_Z_Run2017_UL_ISO.root ewk_corr.root

./MakeCondorFiles.sh Wmu_mc root://cms-t2-se01.sdfarm.kr:1096//store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017MiniAODv2/ZZ_TuneCP5_13TeV-pythia8/crab_job_ZZ/220317_011013/0000/ WmnG_JESPES_ZZ.root -1 10000 WmnG_JESPES_ZZ Efficiencies_muon_generalTracks_Z_Run2017_UL_ID.root Efficiencies_muon_generalTracks_Z_Run2017_UL_ISO.root ewk_corr.root

./MakeCondorFiles.sh WmnG_mc_zg root://cms-t2-se01.sdfarm.kr:1096//store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017MiniAODv2/ZLLGJets_MonoPhoton_PtG-130_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_job_ZLLGJets/220317_010802/0000/ WmnG_JESPES_ZLLGJets_2.root -1 10000 WmnG_JESPES_ZLLGJets_2 Efficiencies_muon_generalTracks_Z_Run2017_UL_ID.root Efficiencies_muon_generalTracks_Z_Run2017_UL_ISO.root ewk_corr.root

./MakeCondorFiles.sh WmnG_mc_WZ root://cms-t2-se01.sdfarm.kr:1096//store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017MiniAODv2/WZ_TuneCP5_13TeV-pythia8/crab_job_WZ/220317_010959/0000/ WmnG_JESPES_WZ.root -1 10000 WmnG_JESPES_WZ Efficiencies_muon_generalTracks_Z_Run2017_UL_ID.root Efficiencies_muon_generalTracks_Z_Run2017_UL_ISO.root ewk_corr.root

./MakeCondorFiles.sh WmnG_mc_wg root://cms-t2-se01.sdfarm.kr:1096//store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017MiniAODv2/WGJets_MonoPhoton_PtG-130_TuneCP5_13TeV-madgraph-pythia8/crab_job_WGJets_MonoPhoton_PtG_130/220317_010816/0000/ WmnG_JESPES_WG_2.root -1 10000 WmnG_JESPES_WG Efficiencies_muon_generalTracks_Z_Run2017_UL_ID.root Efficiencies_muon_generalTracks_Z_Run2017_UL_ISO.root ewk_corr.root  

# //above sample is LO sample below one is NLO Sample i have been using wrong sample so i have put this comment out just to remember the mistakes which i am doing //this  cost 2 days 

#./MakeCondorFiles.sh WmnG_mc_wg davs://cmsxrootd.hep.wisc.edu:1094//store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017_MiniAODv2/WGToLNuG_01J_5f_PtG_130_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_job_WGToLNuG_01J_5f_PtG_130/220129_021745/0000/ WmnG_JESPES_WG_2_latest.root -1 10000 WmnG_JESPES_WG Efficiencies_muon_generalTracks_Z_Run2017_UL_ID.root Efficiencies_muon_generalTracks_Z_Run2017_UL_ISO.root ewk_corr.root









