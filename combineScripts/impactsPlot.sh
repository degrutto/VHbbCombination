#### set up the HiggsCombination package ####
#export SCRAM_ARCH=slc6_amd64_gcc491
#cmsrel CMSSW_7_4_7
#cd CMSSW_7_4_7/src 
#cmsenv
#git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
#cd HiggsAnalysis/CombinedLimit
#scram b -j 8


cmsenv


#text2workspace.py vhbb_2016_13TeV.root -m 125
combineTool.py -M Impacts -d vhbb_2016_13TeV_nobbb.root -m 125 --doInitialFit --robustFit 1   --allPars  --rMax 100 --rMin -100 --job-mode lxbatch --task-name lxbatch_mdg --sub-opts='-q 8nh -G CMS_CERN01_YODA'

combineTool.py -M Impacts -d vhbb_2016_13TeV_nobbb.root -m 125 --robustFit 1 --doFits  --allPars  --rMax 100 --rMin -100 --job-mode lxbatch --task-name lxbatch_mdg --sub-opts='-q 1nd -G CMS_CERN01_YODA'


combine -M MaxLikelihoodFit -m 125 -t -1 --expectSignal=1  --stepSize=0.05 --rMin=-5 --rMax=5 --saveNorm --saveShapes --plots -v 3 vhbb_2016_13TeV.root

combineTool.py -M Impacts -d vhbb_2016_13TeV.root -m 125 --allPars -o impacts.json
cp ../WH/zeroR.txt .
more zeroR.txt >> impact_blind.json ; tail -n+12 impacts.json >> impact_blind.json
plotImpacts.py -i impact_blind.json  -o impacts_blind


