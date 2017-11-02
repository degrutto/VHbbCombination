import os
import math





groups = ['theoryMC', 'theorySIG', 'SFsmc', 'mistag', 'btag', 'efflept', 'model', 'lumi', 'res', 'jec', 'stat', 'met', 'SFsdata' ]

#groups = ['theoryMC', 'theorySIG', 'mistag', 'btag', 'efflept', 'model', 'lumi', 'res', 'jec', 'stat', 'met', 'SFsdata' ]


nominal = +0.292907 +0.287089 
#nominal = +0.287089 

for g in groups:
#    print g  
    os.system("more job_lxbatch_mdg_mlfit%s_0_46*.log | grep 'Best fit r' | awk '{print $5 }' > mlfit%s.log"  % ( g,  g ) )
    with open("mlfit%s.log" % g, 'r' ) as f:
        err2 = f.readline().split('/')
        err = float(err2[1]) - float(err2[0])
        #print err2, err2[1], err2[0], err
         
#        sig = float(f.readline()[:+8])
# #       print g, sig
        effect = 1 - round (  ( float (err/float(nominal))) , 3)
        print g , ' ',  effect
            
        
        
