# Run2VBSWGamma_ntuple for jes/r uncertainties

cmsrel CMSSW_9_4_13

cd CMSSW_9_4_13/src

cmsenv

git cms-init

git cms-merge-topic cms-egamma:EgammaPostRecoTools

git cms-merge-topic cms-met:METFixEE2017_949_v2

git clone https://github.com/qianminghuang/VBSWA_JESR-94X.git VAJets
