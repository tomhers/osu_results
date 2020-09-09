#!/bin/bash -l

#export PATH=/usr/projects/artab/users/hpp/ompi-1/test_install_psm2/bin:$PATH
export PATH=/usr/projects/artab/users/hpp/ompi/test_install_psm2/bin:$PATH
export OMPI_MCA_btl=self,vader
export OMPI_MCA_mtl=ofi

N=32
until (( N > 512 ))
do
ITER=1
until (( ITER == 6 ))
do
#      latency=`grep "On naturally ordered ring" hpccoutf.$N.$ITER.master.txt | awk '{ print $6 }'`
#     latency=`grep "On randomly  ordered ring" hpccoutf.$N.$ITER.master.psm2.txt | awk '{ print $6 }'`
#     latency=`grep "On randomly  ordered ring" hpccoutf.$N.$ITER.proto.txt | awk '{ print $6 }'`
#     latency=`grep "On naturally ordered ring" hpccoutf.$N.$ITER.proto.txt | awk '{ print $6 }'`
#    latency=`grep "On randomly  ordered ring" hpccoutf.$N.$ITER.proto.no_sessions.txt | awk '{ print $6 }'`
     latency=`grep "On randomly  ordered ring" hpccoutf.$N.$ITER.master.psm2.txt | awk '{ print $6 }'`
#     latency=`grep "On naturally ordered ring" hpccoutf.$N.$ITER.master.ofi_w_msg.txt | awk '{ print $6 }'`
    echo $N,$latency
    ((ITER +=1))
done
    ((N +=32))
done

