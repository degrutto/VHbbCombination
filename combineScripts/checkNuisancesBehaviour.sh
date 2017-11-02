python $CMSSW_BASE/HiggsAnalysis/CombinedLimit/test/diffNuisances.py mlfit.root -g outputfile.root

python $CMSSW_BASE/HiggsAnalysis/CombinedLimit/test/diffNuisances.py mlfit.root -f html > ! nuisance.html

more nuisance.html | grep "</strong> </td><td> <strong>" > ! strong_nuisanances.txt