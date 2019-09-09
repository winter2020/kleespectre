/* EXAMPLE 4:  Add a left shift by one on the index. */

#include <stdio.h>
#include <stdlib.h>
#include <klee/klee.h>
#include <klee/klee.h>
#include <stdint.h>

unsigned int array1_size = 16;
uint8_t array1[16];
uint8_t array2[256 * 512];
uint8_t temp = 0;


void victim_fun(int idx) {
    if (idx < array1_size) {                  
        temp &= array2[array1[idx << 1] * 512];
    }
}

int main(int argn, char* args[]) {
    int source;
    klee_make_symbolic(&source, sizeof(source), "source");
    victim_fun(source);
    return 0;
}

