cmsrel CMSSW_10_2_18

cd CMSSW_10_2_18/src

cmsenv

git cms-init

git cms-merge-topic cms-egamma:EgammaPostRecoTools

git-cms-addpkg RecoEgamma/PhotonIdentification

git cms-addpkg RecoMET/METFilters

svn checkout https://github.com/JINGFFF/test/trunk/17/VAJets
