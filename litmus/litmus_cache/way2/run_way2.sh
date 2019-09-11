#!/bin/bash
START=1
SETS=256
WAYS=2
ITER=`expr $SETS \* $WAYS`
for (( i=$START; i <= $ITER; i++ ))
do
    echo "ITERARATION $i"
    python generate_code.py "$i"
    clang-6.0 -g -c test.c -emit-llvm -o test.bc
    /home/wgh/klee/build/bin/klee -search=randomsp -enable-speculative -enable-cachemodel -cache-sets=$SETS -cache-ways=$WAYS test.bc
done 
