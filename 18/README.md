cmsrel CMSSW_10_2_18

cd CMSSW_10_2_18/src

cmsenv

git cms-init

git cms-merge-topic cms-egamma:EgammaPostRecoTools

git cms-merge-topic cms-egamma:PhotonIDValueMapSpeedup1029 

git cms-merge-topic cms-egamma:slava77-btvDictFix_10210 

git cms-addpkg EgammaAnalysis/ElectronTools

rm EgammaAnalysis/ElectronTools/data -rf

git clone git@github.com:cms-data/EgammaAnalysis-ElectronTools.git EgammaAnalysis/ElectronTools/data

git cms-addpkg RecoMET/METFilters

svn checkout https://github.com/JINGFFF/test/trunk/18/VAJets
