cmsenv



### for ggZH, WH, ZH fit ##########

grep bin vhbb_2016_13TeV.txt | head -n 3 | tail -n 1 | tr ' ' '\n' | sort -u > bins.ad.txt
grep process vhbb_2016_13TeV.txt | head -n 2 | tail -n 1 | tr ' ' '\n' | sort -u > processes.ad.txt


text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO verbose --PO 'map=.*/ggZH:r_ggZH[1,-20,20]' --PO 'map=.*/WH:r_WH[1,-5,5]' --PO 'map=.*/ZH:r_ZH[1,-5,5]' vhbb_2016_13TeV.txt -o pippo_new.root > &log.log&


combine -M MultiDimFit workspace.superCombination.Total.txt.pruned.txt.categories.mu.root  -n "multidimfit.categories"     > result.MultiDimFit.singles.workspace.superCombination.Total.txt.pruned.txt.categories.mu.root.txt

combine -M MultiDimFit pippo.root  -n "multidimfit.categories" > &result_multiDimFit_Andre.txt&

combine -M MultiDimFit pippo_50.root -n multidimfit_singles_50.categories --algo=singles --cl=0.68 --robustFit=1 -v 7  --keepFailures >& log_singles_50.log


combine -M MultiDimFit pippo_new.root -n multidimfit_singles_50.categories --algo=singles --cl=0.68  --stepSize 0.05 --minimizerAlgo=Minuit  --minimizerTolerance=100   >&log_singles_new.log&

combine -M MultiDimFit pippo_new.root -n multidimfit_singles_50.categories --algo=singles   -t -1 --expectSignal=1 -v 3  >&log_singles_new_blind.log&

##[combineTool.py -M MultiDimFit pippo_new.root -n multidimfit_cross_50.categories --algo=cross   -t -1 --expectSignal=1 -v 7 --job-mode=lxbatch   --task-name=cross_mdg  --sub-opts='-q 8nh -G CMS_CERN01_YODA'

combineTool.py  -M MultiDimFit pippo_new.root -n multidimfit_grid_50.categories  --algo=grid3x3 --points=10000  -t -1 --expectSignal=1 --job-mode=lxbatch --split-points=100  --task-name=grid_mdg  --sub-opts='-q 8nh -G CMS_CERN01_YODA'

#######     for 0l, 1l, 2l fit ##########

text2workspace.py vhbb_2016_13TeV.txt -m 125
text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO verbose --PO 'map=ZllHbb_*/*H:r_2l[1,-5,5]' --PO'map=WlnHbb_*/*H:r_1l[1,-5,5]' --PO 'map=ZnnHbb_*/*H:r_0l[1,-5,5]' vhbb_2016_13TeV.txt -o pippo_lept.root > &log_lep.log&       

combine -M ChannelCompatibilityCheck vhbb_2016_13TeV.root -t -1 --expectSignal=1 -v 3 --group WlnHbb --group ZllHbb --group ZnnHbb > & log_ccc.log& 





combine -M ChannelCompatibilityCheck vhbb_2016_13TeV.root  --autoBoundsPOIs   --robustFit=1 --minimizerAlgo=Minuit   -v 3 --group WlnHbb --group ZllHbb --group ZnnHbb > & log_ccc_unblind.log& 


combine -M ChannelCompatibilityCheck vhbb_2016_13TeV.root --robustFit=1 --rMin=-2 -v 1 --group WlnHbb --group ZllHbb --group ZnnHbb --fastScan  --job-mode=lxbatch   --task-name=ccc  --sub-opts='-q 1nd -G CMS_CERN01_YODA'


combine vhbb_2016_13TeV_fixes.root --robustFit=1 --rMin=-2 -v 3 --group WlnHbb --group ZllHbb --group ZnnHbb --fixedSignalStrength 1.19 -M ChannelCompatibilityCheck  --minimizerStrategy 0 --runMinos 0 --job-mode=lxbatch   --task-name=cccNew  --sub-opts='-q 1nd -G CMS_CERN01_YODA'


combine vhbb_2016_13TeV_fixes.root --robustFit=1 --rMin=-2 -v 3 --group WlnHbb --group ZllHbb*high --group ZllHbb*low --group ZnnHbb --fixedSignalStrength 1.19 -M ChannelCompatibilityCheck  --minimizerStrategy 0 --runMinos 0 --job-mode=lxbatch   --task-name=cccNew4  --sub-opts='-q 1nd -G CMS_CERN01_YODA'


combine -M MultiDimFit --rMin=-2 pippo_new.root -n multidimfit_singles_50.categories --algo=singles --cl=0.68 --stepSize 0.05 --robustFit=1 --minimizerAlgoForMinos Minuit2,Migrad > & log_singles_new_fix.log &


############ regular fit ##############

#combine -M MaxLikelihoodFit  --stepSize 0.05 --minimizerAlgo=Minuit --minimizerTolerance=100 vhbb_2016_13TeV.txt > & log_nominal.log &


####### ZH (qq + gg) vs WH fit #########

#before
 text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO verbose --PO 'map=.*/ggZH:r_ZH[1,-20,20]' --PO 'map=.*/WH:r_WH[1,-5,5]' --PO 'map=.*/ZH:r_ZH[1,-5,5]' vhbb_2016_13TeV.txt -o pippo_new_2d.root > &log_2d.log&

#after
combineTool.py  -M MultiDimFit pippo_new_2d.root -n multidimfit_grid_2d.categories  --algo=grid3x3 --points=20000  -t -1 --expectSignal=1 --job-mode=lxbatch --split-points=100  --task-name=grid2d_mdg  --sub-opts='-q 8nh -G CMS_CERN01_YODA'


combineTool.py  -M MultiDimFit pippo_new_2d.root -n multidimfit_grid_2d.categories --fastScan  --algo=grid --points=100000   --job-mode=lxbatch --split-points=1000  --task-name=grid2d_mdg  --sub-opts='-q 1nd -G CMS_CERN01_YODA'

### try grid3x3