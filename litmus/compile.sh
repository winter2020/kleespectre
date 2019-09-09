#!/bin/bash

for d in $(find . -maxdepth 1 ! -name . -type d) 
do 
    #echo $d
    cd $d 
    pwd
    rm *.bc
    #sed -i '5i#include <klee/klee.h>' test.c
    clang-6.0 test.c -g -c -emit-llvm -o test.bc
    #objdump -S test > test.asm
    #objdump -S test_slh > test_slh.asm
    cd ..
done 


#-x86-speculative-load-hardening-lfence
