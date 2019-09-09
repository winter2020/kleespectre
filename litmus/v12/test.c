/* EXAMPLE 12:  Make the index be the sum of two input parameters. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <klee/klee.h>
#include <klee/klee.h>

unsigned int array1_size = 16;
uint8_t array1[16];
uint8_t array2[256 * 512];
uint8_t temp = 0;


void victim_fun(int x, int y) {
    if ((x + y) < array1_size) {                  
        temp &= array2[array1[x + y] * 512];
    }
}

int main(int argn, char* args[]) {
    int source;
    klee_make_symbolic(&source, sizeof(source), "source");
    victim_fun(source, source);
    return 0;
}

