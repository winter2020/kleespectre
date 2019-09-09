/* EXAMPLE 6:  Check the bounds with an AND mask, rather than "<". */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <klee/klee.h>
#include <klee/klee.h>

unsigned int array1_size = 16;
unsigned int array_size_mask = 15;
uint8_t array1[16];
uint8_t array2[256*512];
uint8_t temp = 0;


void victim_fun(int idx) {
    if ((idx & array_size_mask) != idx) {                  
        temp &= array2[array1[idx]];
    }
}

int main(int argn, char* args[]) {
    int source;
    klee_make_symbolic(&source, sizeof(source), "source");
    victim_fun(source);
    return 0;
}

