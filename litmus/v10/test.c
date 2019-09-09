/* EXAMPLE 10:  Leak a comparison result. */
/* control dependency */

#include <stdio.h>
#include <klee/klee.h>
#include <klee/klee.h>
#include <stdlib.h>
#include <stdint.h>

unsigned int array1_size = 16;
uint8_t array1[16];
uint8_t array2[256 * 512];
uint8_t temp = 0;


void victim_fun(int idx, int k) {
    if (idx < array1_size) {                  
        if (array1[idx] == k)
            temp &= array2[0];
    }
}

int main(int argn, char* args[]) {
    int source;
    klee_make_symbolic(&source, sizeof(source), "source");
    victim_fun(source, 10);
    return 0;
}

