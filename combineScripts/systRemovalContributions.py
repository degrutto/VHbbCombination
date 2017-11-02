import  os


#os.system("eval `scramv1 runtime -csh`")




groups = ['theoryMC', 'theorySIG', 'SFsmc', 'mistag', 'btag', 'efflept', 'model', 'lumi', 'res', 'jec', 'stat', 'met', 'SFsdata' ]

#groups = ['SFsdata' ]

#groups = ['theoryMC', 'theorySIG', 'SFsmc', 'mistag', 'btag', 'efflept', 'model', 'lumi', 'res', 'jec', 'stat', 'met' ]



for g in groups:
    if str('SFsdata') in g :
        print 'for rateParams'
        print g
#        os.system("combineTool.py -M ProfileLikelihood -m 125 --signif --pvalue -t -1 --expectSignal=1 vhbb_2016_13TeV_norateParam.txt -n prefit%s   --job-mode lxbatch --task-name lxbatch_mdg_prefit%s  --sub-opts='-q 1nd -G CMS_CERN01_YODA'" % (str(g), str(g)) ) 

        os.system("combineTool.py -M MaxLikelihoodFit -v 2 -m 125  -t -1 --expectSignal=1 --robustFit=1  --stepSize=0.01 --rMin=-5 --rMax=5 vhbb_2016_13TeV_norateParam.txt -n mlfit%s   --job-mode lxbatch --task-name lxbatch_mdg_mlfit%s    --minimizerAlgo=Minuit  --sub-opts='-q 1nd -G CMS_CERN01_YODA'" % ( str(g), str(g)) ) 
        
    else:
         print g
 #        os.system("combineTool.py -M ProfileLikelihood -m 125 --signif --pvalue -t -1 --expectSignal=1 vhbb_2016_13TeV_groups.txt -n prefit%s   --job-mode lxbatch --task-name lxbatch_mdg_prefit%s  --freezeNuisanceGroups %s --sub-opts='-q 1nd -G CMS_CERN01_YODA'" % (str(g), str(g), str(g)) ) 

         os.system("combineTool.py -M MaxLikelihoodFit -v 2 -m 125  -t -1 --expectSignal=1 --robustFit=1  --stepSize=0.01 --rMin=-5 --rMax=5 vhbb_2016_13TeV_groups.txt -n mlfit%s   --job-mode lxbatch --task-name lxbatch_mdg_mlfit%s  --freezeNuisanceGroups %s  --minimizerAlgo=Minuit  --sub-opts='-q 1nd -G CMS_CERN01_YODA'" % (str(g), str(g), str(g)) ) 



#combineTool.py -M ProfileLikelihood -m 125 --signif --pvalue -t -1 --toysFreq --expectSignal=1  vhbb_2016_13TeV.txt -n postfit   --job-mode lxbatch --task-name lxbatch_mdg_postfit --sub-opts='-q 1nd -G CMS_CERN01_YODA' 





