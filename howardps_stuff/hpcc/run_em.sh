#!/bin/bash -l

#export PATH=/usr/projects/artab/users/hpp/ompi-1/test_install_psm2/bin:$PATH
#export PATH=/usr/projects/artab/users/hpp/ompi/test_install_psm2/bin:$PATH
#export PATH=/usr/projects/artab/users/hpp/ompi/test_install_psm2_no_ofi/bin:$PATH
export PATH=/usr/projects/artab/users/hpp/ompi/test_install_psm2_ofi_w_msg/bin:$PATH
export OMPI_MCA_btl=self,vader
export OMPI_MCA_mtl=ofi
#export OMPI_MCA_mtl=psm2

rm hpccoutf.txt
#for N in 56 112 168 224 280 336 392 448 504 560 616 672 728 784 840 896
N=32
#NHOSTS=1
until (( N > 512 ))
do
ITER=1
until (( ITER == 6 ))
do
    echo "Working on ",$N,$ITER
#    prun --system-server-first -np $N -N 28 ./hpcc
#    mpirun  -np $N -N 32 ./hpcc.proto.no_sessions
    mpirun  -np $N -N 32 ./hpcc.master.ofi_w_msg
    sleep 1
#    mv hpccoutf.txt hpccoutf.$N.$ITER.proto.no_sessions.txt
    mv hpccoutf.txt hpccoutf.$N.$ITER.master.ofi_w_msg.txt
#    srun -n $N -N $NHOSTS ./hpcc.master
#    mv hpccoutf.txt hpccoutf.$N.master2.txt
#   sleep 1
    ((ITER +=1))
#    ((NHOSTS +=1))
done
    ((N +=32))
done

