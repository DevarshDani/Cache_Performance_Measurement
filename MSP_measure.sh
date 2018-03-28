#! /bin/bash
#source ./.bashrc

cd /home2/accts11/Project

# compiling for Branch Misprediction
echo 'compiling MSP.c file'
cc -o3 MSP.c -o MSP -I/opt/papi/5.6.0/include -L/opt/papi/5.6.0/lib64 -lpapi

echo 'First iteration'

echo 'Matrix size 512'
./MSP 512

echo 'Matrix size 1024'
./MSP 1024


echo '2nd iteration'

echo 'Matrix size 512'
./MSP 512

echo 'Matrix size 1024'
./MSP 1024

echo '3rd iteration'

echo 'Matrix size 512'
./MSP 512

echo 'Matrix size 1024'
./MSP 1024

exit 
