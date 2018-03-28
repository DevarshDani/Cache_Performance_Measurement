#! /bin/bash
#source ./.bashrc

cd /home2/accts11/Project

# compiling for L1
echo 'compiling L1_MR.c file'
cc -o3 L1_MR_data.c -o L1_MR_data -I/opt/papi/5.6.0/include -L/opt/papi/5.6.0/lib64 -lpapi

echo 'First iteration'

echo 'Matrix size 512'
./L1_MR_data 512

echo 'Matrix size 1024'
./L1_MR_data 1024


echo '2nd iteration'

echo 'Matrix size 512'
./L1_MR_data 512

echo 'Matrix size 1024'
./L1_MR_data 1024

echo '3rd iteration'

echo 'Matrix size 512'
./L1_MR_data 512

echo 'Matrix size 1024'
./L1_MR_data 1024

exit 
