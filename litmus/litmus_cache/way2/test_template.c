#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <klee/klee.h>

unsigned int array1_size = 16;
uint8_t array1[16];
uint8_t array2[256 * 64];
uint8_t array3[512 * 64];
uint8_t temp = 0;


uint8_t victim_fun(int idx)  __attribute__ ((optnone)) 
{
    printf("array2 = %p\n", array2);
    printf("array3 = %p\n", array3);
    if (idx < array1_size) {                  
        temp &= array2[array1[idx]];
    }
    return temp;
}

int main() {
    int x;
    int i;

    klee_make_symbolic(&x, sizeof(x), "x");
    victim_fun(x);
#define ITER 512
    for (i = 0; i < ITER; i++) {
        temp &= array3[i*64];
    }
    return 0;
}

