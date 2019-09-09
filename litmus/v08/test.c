/* EXAMPLE 8:  Use a ?: operator to check bounds. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <klee/klee.h>
#include <klee/klee.h>

unsigned int array1_size = 16;
uint8_t array1[16];
uint8_t array2[256 * 512];
uint8_t temp = 0;


void victim_fun(int idx) {
    temp &= array2[array1[idx < (array1_size-1)? (idx + 1) : 0] * 512];
}

int main(int argn, char* args[]) {
    int source;
    klee_make_symbolic(&source, sizeof(source), "source");
    victim_fun(source);
    return 0;
}


