#### set up the HiggsCombination package ####
export SCRAM_ARCH=slc6_amd64_gcc491
cmsrel CMSSW_7_4_7
cd CMSSW_7_4_7/src 
cmsenv
git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
cd HiggsAnalysis/CombinedLimit
scram b -j 8

#download also the combineHarvester
git clone via https:
bash <(curl -s https://raw.githubusercontent.com/cms-analysis/CombineHarvester/master/CombineTools/scripts/sparse-checkout-https.sh)
scram b -j 8

cmsenv

### copy files from Zll, Znn and Wln Hbb ####


### Zll,Znn,WH
##WlnH_19042017/  ZllH/           ZnnH/           ZnnH_20042017/  

cp ZllH_fix/vhbb_*  .
cp ZnnH/vhbb_*  .
cp WlnH/vhbb*  .




combineCards.py ZnnHbb=vhbb_znnhbb_2016_13TeV.txt  ZllHbb=vhbb_zllhbb_2016_13TeV.txt  WlnHbb=vhbb_wlnhbb_2016_13TeV.txt  > ! vhbb_2016_13TeV.txt

combineTool.py -M Asymptotic -t -1 vhbb_2016_13TeV.txt -n asympt --job-mode lxbatch --task-name lxbatch_mdg_asymp --sub-opts='-q 1nd -G CMS_CERN01_YODA'

combineTool.py -M ProfileLikelihood -m 125 --signif --pvalue -t -1 --expectSignal=1 vhbb_2016_13TeV.txt -n prefit   --job-mode lxbatch --task-name lxbatch_mdg_prefit --sub-opts='-q 1nd -G CMS_CERN01_YODA'

combineTool.py -M ProfileLikelihood -m 125 --signif --pvalue -t -1 --toysFreq --expectSignal=1  vhbb_2016_13TeV.txt -n postfit   --job-mode lxbatch --task-name lxbatch_mdg_postfit --sub-opts='-q 1nd -G CMS_CERN01_YODA' 

combineTool.py -M MaxLikelihoodFit -m 125 -t -1 --expectSignal=1   --robustFit=1  --stepSize=0.05 --rMin=-5 --rMax=5 --saveNorm -v 3 vhbb_2016_13TeV.txt  -n mlfitblind   --job-mode lxbatch --task-name lxbatch_mdg_mlfitblind --sub-opts='-q 1nd -G CMS_CERN01_YODA' 

combineTool.py -M MaxLikelihoodFit   -v 3 -m 125 --rMin=-3 --rMax=3  --stepSize=0.01   --expectSignal=1 --robustFit=1  --saveNorm --saveShapes --saveWithUncertainties  --minimizerTolerance=10.0 --minimizerAlgoForMinos Minuit2,Migrad vhbb_2016_13TeV.txt -n mlfitunblind   --job-mode lxbatch --task-name lxbatch_mdg_mlfitunblind --sub-opts='-q 1nd -G CMS_CERN01_YODA'


combineTool.py -M MaxLikelihoodFit   -v 3 -m 125 --rMin=-5 --rMax=5  --stepSize=0.05   --expectSignal=1 --robustFit=1  --saveNorm --saveShapes --saveWithUncertainties  --minimizerTolerance=10.0 --minimizerAlgoForMinos Minuit2,Migrad vhbb_2016_13TeV.txt -n mlfitunblindr5   --job-mode lxbatch --task-name lxbatch_mdg_mlfitunblindr5 --sub-opts='-q 1nd -G CMS_CERN01_YODA'

combineTool.py -M MaxLikelihoodFit   -v 3 -m 125 --rMin=-5 --rMax=5  --stepSize=0.05   --expectSignal=1 --robustFit=1  --saveNorm --saveShapes --saveWithUncertainties  --minimizerTolerance=10.0  vhbb_2016_13TeV.txt -n mlfitunblindr5test   --job-mode lxbatch --task-name lxbatch_mdg_mlfitunblindr5test --sub-opts='-q 1nd -G CMS_CERN01_YODA'


combineTool.py -M MaxLikelihoodFit   -v 3 -m 125  --robustFit=1  --saveNorm --saveShapes --saveWithUncertainties    vhbb_2016_13TeV.txt -n mlfitunblindsimple   --job-mode lxbatch --task-name lxbatch_mdg_mlfitunblindsimple --sub-opts='-q 1nd -G CMS_CERN01_YODA'




combineTool.py -M MaxLikelihoodFit   -v 3 -m 125 --rMin=-5 --rMax=5  --stepSize=0.01   --expectSignal=1 --robustFit=1  --saveNorm --saveShapes --saveWithUncertainties   vhbb_2016_13TeV.txt -n mlfitunblindr5testv2   --job-mode lxbatch --task-name lxbatch_mdg_mlfitunblindr5testv2 --sub-opts='-q 1nd -G CMS_CERN01_YODA'


combineTool.py -M MaxLikelihoodFit -m 125 -v 3 --expectSignal=1 --robustFit=1  --minimizerAlgo=Minuit --saveNorm --saveShapes  --saveWithUncertainties  vhbb_2016_13TeV.txt -n mlfitunblindrUltraSimple --job-mode lxbatch --task-name lxbatch_mdg_mlfitunblindUltraSimple --sub-opts='-q 1nd -G CMS_CERN01_YODA'

combineTool.py -M MaxLikelihoodFit -m 125 -v 3 --expectSignal=1 --robustFit=1  --minimizerAlgo=Minuit --saveNorm --saveShapes    vhbb_2016_13TeV.txt -n mlfitunblindrUltraSimpleNoUnc --job-mode lxbatch --task-name lxbatch_mdg_mlfitunblindUltraSimpleNoUnc --sub-opts='-q 1nd -G CMS_CERN01_YODA'

combineTool.py -M MaxLikelihoodFit -m 125 -v 3 --expectSignal=1 --robustFit=1  --minimizerAlgo=Minuit --saveNorm --saveShapes    vhbb_2016_13TeV.txt --minimizerTolerance=10.0 -n mlfitunblindrUltraSimpleNoUncTol10 --job-mode lxbatch --task-name lxbatch_mdg_mlfitunblindUltraSimpleNoUncTol10 --sub-opts='-q 1nd -G CMS_CERN01_YODA'

combineTool.py -M MaxLikelihoodFit -m 125 -v 3 --expectSignal=1 --robustFit=1  --minimizerAlgo=Minuit --saveNorm --saveShapes  --saveWithUncertainties    vhbb_2016_13TeV.txt --minimizerTolerance=10.0 -n mlfitunblindrUltraSimpleTol10 --job-mode lxbatch --task-name lxbatch_mdg_mlfitunblindUltraSimpleTol10 --sub-opts='-q 1nd -G CMS_CERN01_YODA'