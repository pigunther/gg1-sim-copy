#!/bin/bash

queueLen=$1
model=$2
service=$3

rm -rf result.dat

for lambda in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9
do
  ./execute.py $lambda 1 100000 $queueLen $model --runMode static >> result.dat
done

python plot.py $queueLen $model $service