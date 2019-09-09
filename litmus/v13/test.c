/* EXAMPLE 13:  Do the safety check into an inline function */
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

inline static int is_x_safe(size_t x) {
    if (x < array1_size) 
        return 1;
    return 0;
}

void victim_fun(int idx) {
    if (is_x_safe(idx)) {                  
        temp &= array2[array1[idx] * 512];
    }
}

int main(int argn, char* args[]) {
    int source;
    klee_make_symbolic(&source, sizeof(source), "source");
    victim_fun(source);
    return 0;
}

