/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 */

// #include "tomcrypt_private.h"

/**
   @file base16_encode.c
   Base16/Hex encode a string, Steffen Jaeckel
*/

#include <klee/klee.h>

// #ifdef LTC_BASE16
/* error codes [will be expanded in future releases] */
// #define CRYPT_BUFFER_OVERFLOW 6
// #define CRYPT_OVERFLOW 19
// #define CRYPT_OK 0
enum {
   CRYPT_OK=0,             /* Result OK */
   CRYPT_ERROR,            /* Generic Error */
   CRYPT_NOP,              /* Not a failure but no operation was performed */

   CRYPT_INVALID_KEYSIZE,  /* Invalid key size given */
   CRYPT_INVALID_ROUNDS,   /* Invalid number of rounds */
   CRYPT_FAIL_TESTVECTOR,  /* Algorithm failed test vectors */

   CRYPT_BUFFER_OVERFLOW,  /* Not enough space for output */
   CRYPT_INVALID_PACKET,   /* Invalid input packet given */

   CRYPT_INVALID_PRNGSIZE, /* Invalid number of bits for a PRNG */
   CRYPT_ERROR_READPRNG,   /* Could not read enough from PRNG */

   CRYPT_INVALID_CIPHER,   /* Invalid cipher specified */
   CRYPT_INVALID_HASH,     /* Invalid hash specified */
   CRYPT_INVALID_PRNG,     /* Invalid PRNG specified */

   CRYPT_MEM,              /* Out of memory  */

   CRYPT_PK_TYPE_MISMATCH, /* Not equivalent types of PK keys */
   CRYPT_PK_NOT_PRIVATE,   /* Requires a private PK key */

   CRYPT_INVALID_ARG,      /* Generic invalid argument */
   CRYPT_FILE_NOTFOUND,    /* File Not Found */

   CRYPT_PK_INVALID_TYPE,  /* Invalid type of PK key */

   CRYPT_OVERFLOW,         /* An overflow of a value was detected/prevented */

   CRYPT_PK_ASN1_ERROR,    /* An error occurred while en- or decoding ASN.1 data */

   CRYPT_INPUT_TOO_LONG,   /* The input was longer than expected. */

   CRYPT_PK_INVALID_SIZE,  /* Invalid size input for PK parameters */

   CRYPT_INVALID_PRIME_SIZE,/* Invalid size of prime requested */
   CRYPT_PK_INVALID_PADDING, /* Invalid padding on input */

   CRYPT_HASH_OVERFLOW      /* Hash applied to too many bits */
};
/**
   Base16 encode a buffer
   @param in       The input buffer to encode
   @param inlen    The length of the input buffer
   @param out      [out] The destination of the Base16 encoded data
   @param outlen   [in/out] The max size and resulting size of the encoded data
   @param options  Output 'a-f' on 0 and 'A-F' otherwise.
   @return CRYPT_OK if successful
*/

unsigned int array1_size = 16; 
uint8_t array1[16];
uint8_t array2[256];
uint8_t temp;


uint8_t victim_fun1(int idx) __attribute__ ((optnone)) {
    if (idx < array1_size) {    
        temp &= array2[array1[idx]];
    }   
    array2[8] = 2;
    array1[8] = 2;
    return temp;
}

uint8_t victim_fun2(int idx) __attribute__ ((optnone)) {
    if (idx < array1_size) {    
        temp &= array2[array1[idx]];
    }   
    return temp;
}

uint8_t victim_fun3(int idx) __attribute__ ((optnone)) {
    if (idx < array1_size) {    
        temp &= array2[array1[idx]];
    }   
    return temp;
}


unsigned char buff[508*64] __attribute__((aligned(64)));
static char alphabets1[] __attribute__((aligned(64)))= "0123456789abcdef";
static char alphabets2[] __attribute__((aligned(64)))= "0123456789ABCDEF";
static char alphabets3[47+64] __attribute__((aligned(64)))= "placeHolder";

int base16_encode(const unsigned char *in,  unsigned long  inlen,
                                 char *out, unsigned long *outlen,
                        unsigned int   options)
{
   unsigned long i, x;
   char *alphabet;
   int y;

   // LTC_ARGCHK(in     != NULL);
   // LTC_ARGCHK(out    != NULL);
   // LTC_ARGCHK(outlen != NULL);

   /* check the sizes */
   x = inlen * 2 + 1;

   klee_make_symbolic(&y, sizeof(y), "y");

   if (x < inlen) return CRYPT_OVERFLOW;

   if (*outlen < x) {
      *outlen = x;
      return CRYPT_BUFFER_OVERFLOW;
   }
   x--;
   *outlen = x; /* returning the length without terminating NUL */
    victim_fun2(y);
   if (options == 0) {
          for (i = 0; i < x; i += 2) 
         {
            out[i]   = alphabets1[(in[i/2] >> 4) & 0x0f];
            out[i+1] = alphabets1[in[i/2] & 0x0f];
         }
   } else {
          for (i = 0; i < x; i += 2) 
         {
            out[i]   = alphabets2[(in[i/2] >> 4) & 0x0f];
            out[i+1] = alphabets2[in[i/2] & 0x0f];
         }
   }

   out[x] =  alphabets3[110]; //'\0';
   return CRYPT_OK;
}

int main()
{
   unsigned char in[16]={0}; 
   char out[256] = {0};
   unsigned long len = 16;
   unsigned long outlen;
   unsigned int options;
   int x;

   klee_make_symbolic(&in, sizeof(in), "in");
   //klee_make_symbolic(&len, sizeof(len), "len");
   klee_make_symbolic(&options, sizeof(options), "options");
   klee_make_symbolic(&x, sizeof(x), "x");
   victim_fun1(x);  
   base16_encode(in, len, out, &outlen, options);
   victim_fun3(x);  
   return 0;
  
}


// #endif

/* ref:         HEAD -> develop */
/* git commit:  c9c3c4273956ae945aecec7122cd0df71a210803 */
/* commit time: 2018-07-10 07:11:39 +0200 */
