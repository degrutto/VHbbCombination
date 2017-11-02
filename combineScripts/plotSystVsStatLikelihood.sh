wget Https://raw.githubusercontent.com/cms-analysis/CombineHarvester/master/CombineTools/scripts/plot1DScan.py .


combine -M MultiDimFit --algo grid --points 50 --rMin 0.8 --rMax 1.6 vhbb_2016_13TeV_fixes.root  -m 125 -n nominal --robustFit=1 --minimizerAlgo=Minuit 

combine -M MultiDimFit --algo none --rMin 0.8 --rMax 1.6 vhbb_2016_13TeV_fixes.root  -m 125 -n bestfit --saveWorkspace


combine -M MultiDimFit --algo grid --points 50 --rMin 0.8 --rMax 1.6 -m 125 -n stat higgsCombinebestfit.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisances all --freezeNuisances 'rgx{^SF_.*$}'



plot1DScan.py higgsCombinenominal.MultiDimFit.mH125.root --others 'higgsCombinestat.MultiDimFit.mH125.root:Freeze all:2' --breakdown syst,stat