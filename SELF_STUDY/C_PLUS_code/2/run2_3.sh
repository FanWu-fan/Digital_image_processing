#!/bin/bash
cd build
o1=`cmake ..`
# cmake ..
echo $o1
make clean
# o2=`make`
make
./bin/2_3 ../../image/test.avi
