#!/bin/sh
cat>Job_${6}.sh<<EOF
#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh 
cd /cvmfs/cms.cern.ch/slc7_amd64_gcc820/cms/cmssw/CMSSW_10_6_26/src
eval `scramv1 runtime -sh`
cd \${_CONDOR_SCRATCH_DIR}
./${1} ${2} ${3} ${4} ${5}
EOF

chmod 775 Job_${6}.sh

cat>condor_${6}<<EOF
accounting_group=group_cms                                                                   
use_x509userproxy = True                                                                     
x509userproxy = /tmp/x509up_u556951229
executable = ./Job_${6}.sh
notification         = never
whenToTransferOutput = On_Exit
shouldTransferFiles  = yes
getenv = true 
request_memory       = 1992
transfer_input_files = ${1}, ${7}, ${8}, ${9}
output               = \$(Cluster)_\$(Process)_${6}.out 
error                = \$(Cluster)_\$(Process)_${6}.err
Log                  = \$(Cluster)_\$(Process)_${6}.log
Queue
EOF

condor_submit condor_${6}
