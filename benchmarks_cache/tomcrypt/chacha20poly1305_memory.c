/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 */
#include <string.h>
#include <klee/klee.h>


typedef unsigned long long ulong64;
typedef unsigned ulong32;

#ifndef XMEMSET
#define XMEMSET  memset
#endif
#ifndef XMEMCPY
#define XMEMCPY  memcpy
#endif

unsigned int array1_size = 16; 
uint8_t array1[16];
uint8_t array2[256];
uint8_t temp = 0;


uint8_t victim_fun1(int idx) __attribute__ ((optnone)) {
    if (idx < array1_size) {    
        temp &= array2[array1[idx]];
    }   
    array1[8] = 0; 
    array2[8] = 0; 
    return temp;
}

uint8_t victim_fun2(int idx) __attribute__ ((optnone)) {
    int temp = 0;
    if (idx < array1_size) {    
        temp &= array2[array1[idx]];
    }   
    return temp;
}

uint8_t victim_fun3(int idx) __attribute__ ((optnone)) {
    int temp = 0;
    if (idx < array1_size) {    
        temp &= array2[array1[idx]];
    }   
    return temp;
}


#define  CHACHA20POLY1305_ENCRYPT 0
#define  CHACHA20POLY1305_DECRYPT 1
/* error codes [will be expanded in future releases] */
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

   CRYPT_MEM,              /* Out of memory */

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

typedef struct {
   ulong32 r[5];
   ulong32 h[5];
   ulong32 pad[4];
   unsigned long leftover;
   unsigned char buffer[16];
   int final;
} poly1305_state;

typedef struct {
   ulong32 input[16];
   unsigned char kstream[64];
   unsigned long ksleft;
   unsigned long ivlen;
   int rounds;
} chacha_state;

typedef struct {
   poly1305_state poly;
   chacha_state chacha;
   ulong64 aadlen;
   ulong64 ctlen;
   int aadflg;
} chacha20poly1305_state;

#define STORE32L(x, y)                                                                     \
       (y)[3] = (unsigned char)(((x)>>24)&255); (y)[2] = (unsigned char)(((x)>>16)&255);   \
       (y)[1] = (unsigned char)(((x)>>8)&255); (y)[0] = (unsigned char)((x)&255);

#define LOAD32L(x, y)                            \
       x = ((ulong32)((y)[3] & 255)<<24) | \
           ((ulong32)((y)[2] & 255)<<16) | \
           ((ulong32)((y)[1] & 255)<<8)  | \
           ((ulong32)((y)[0] & 255)); 


/* internal only */
void _poly1305_block(poly1305_state *st, const unsigned char *in, unsigned long inlen) 
{
   const unsigned long hibit = (st->final) ? 0 : (1UL << 24); /* 1 << 128 */
   ulong32 r0,r1,r2,r3,r4;
   ulong32 s1,s2,s3,s4;
   ulong32 h0,h1,h2,h3,h4;
   ulong32 tmp;
   ulong64 d0,d1,d2,d3,d4;
   ulong32 c;

   r0 = st->r[0];
   r1 = st->r[1];
   r2 = st->r[2];
   r3 = st->r[3];
   r4 = st->r[4];

   s1 = r1 * 5;
   s2 = r2 * 5;
   s3 = r3 * 5;
   s4 = r4 * 5;

   h0 = st->h[0];
   h1 = st->h[1];
   h2 = st->h[2];
   h3 = st->h[3];
   h4 = st->h[4];

   while (inlen >= 16) {
      /* h += in[i] */
      LOAD32L(tmp, in+ 0); h0 += (tmp     ) & 0x3ffffff;
      LOAD32L(tmp, in+ 3); h1 += (tmp >> 2) & 0x3ffffff;
      LOAD32L(tmp, in+ 6); h2 += (tmp >> 4) & 0x3ffffff;
      LOAD32L(tmp, in+ 9); h3 += (tmp >> 6) & 0x3ffffff;
      LOAD32L(tmp, in+12); h4 += (tmp >> 8) | hibit;

      /* h *= r */
      d0 = ((ulong64)h0 * r0) + ((ulong64)h1 * s4) + ((ulong64)h2 * s3) + ((ulong64)h3 * s2) + ((ulong64)h4 * s1);
      d1 = ((ulong64)h0 * r1) + ((ulong64)h1 * r0) + ((ulong64)h2 * s4) + ((ulong64)h3 * s3) + ((ulong64)h4 * s2);
      d2 = ((ulong64)h0 * r2) + ((ulong64)h1 * r1) + ((ulong64)h2 * r0) + ((ulong64)h3 * s4) + ((ulong64)h4 * s3);
      d3 = ((ulong64)h0 * r3) + ((ulong64)h1 * r2) + ((ulong64)h2 * r1) + ((ulong64)h3 * r0) + ((ulong64)h4 * s4);
      d4 = ((ulong64)h0 * r4) + ((ulong64)h1 * r3) + ((ulong64)h2 * r2) + ((ulong64)h3 * r1) + ((ulong64)h4 * r0);

      /* (partial) h %= p */
                    c = (ulong32)(d0 >> 26); h0 = (ulong32)d0 & 0x3ffffff;
      d1 += c;      c = (ulong32)(d1 >> 26); h1 = (ulong32)d1 & 0x3ffffff;
      d2 += c;      c = (ulong32)(d2 >> 26); h2 = (ulong32)d2 & 0x3ffffff;
      d3 += c;      c = (ulong32)(d3 >> 26); h3 = (ulong32)d3 & 0x3ffffff;
      d4 += c;      c = (ulong32)(d4 >> 26); h4 = (ulong32)d4 & 0x3ffffff;
      h0 += c * 5;  c =          (h0 >> 26); h0 =          h0 & 0x3ffffff;
      h1 += c;

      in += 16;
      inlen -= 16;
   }

   st->h[0] = h0;
   st->h[1] = h1;
   st->h[2] = h2;
   st->h[3] = h3;
   st->h[4] = h4;
}

/**
  Process data through POLY1305
  @param st      The POLY1305 state
  @param in      The data to send through HMAC
  @param inlen   The length of the data to HMAC (octets)
  @return CRYPT_OK if successful
*/
int poly1305_process(poly1305_state *st, const unsigned char *in, unsigned long inlen) 
{
   unsigned long i;

   if (inlen == 0) return CRYPT_OK; /* nothing to do */
   // LTC_ARGCHK(st != NULL);
   // LTC_ARGCHK(in != NULL);

   /* handle leftover */
   if (st->leftover) {
      unsigned long want = (16 - st->leftover);
      if (want > inlen) want = inlen;
      for (i = 0; i < want; i++) st->buffer[st->leftover + i] = in[i];
      inlen -= want;
      in += want;
      st->leftover += want;
      if (st->leftover < 16) return CRYPT_OK;
      _poly1305_block(st, st->buffer, 16);
      st->leftover = 0;
   }

   /* process full blocks */
   if (inlen >= 16) {
      unsigned long want = (inlen & ~(16 - 1));
      _poly1305_block(st, in, want);
      in += want;
      inlen -= want;
   }

   /* store leftover */
   if (inlen) {
      for (i = 0; i < inlen; i++) st->buffer[st->leftover + i] = in[i];
      st->leftover += inlen;
   }
   return CRYPT_OK;
}

/**
   Terminate a POLY1305 session
   @param st      The POLY1305 state
   @param mac     [out] The destination of the POLY1305 authentication tag
   @param maclen  [in/out]  The max size and resulting size of the POLY1305 authentication tag
   @return CRYPT_OK if successful
*/
int poly1305_done(poly1305_state *st, unsigned char *mac, unsigned long *maclen)
{
   ulong32 h0,h1,h2,h3,h4,c;
   ulong32 g0,g1,g2,g3,g4;
   ulong64 f;
   ulong32 mask;

   // LTC_ARGCHK(st     != NULL);
   // LTC_ARGCHK(mac    != NULL);
   // LTC_ARGCHK(maclen != NULL);
   // LTC_ARGCHK(*maclen >= 16);

   /* process the remaining block */
   if (st->leftover) {
      unsigned long i = st->leftover;
      st->buffer[i++] = 1;
      for (; i < 16; i++) st->buffer[i] = 0;
      st->final = 1;
      _poly1305_block(st, st->buffer, 16);
   }

   /* fully carry h */
   h0 = st->h[0];
   h1 = st->h[1];
   h2 = st->h[2];
   h3 = st->h[3];
   h4 = st->h[4];

                c = h1 >> 26; h1 = h1 & 0x3ffffff;
   h2 +=     c; c = h2 >> 26; h2 = h2 & 0x3ffffff;
   h3 +=     c; c = h3 >> 26; h3 = h3 & 0x3ffffff;
   h4 +=     c; c = h4 >> 26; h4 = h4 & 0x3ffffff;
   h0 += c * 5; c = h0 >> 26; h0 = h0 & 0x3ffffff;
   h1 +=     c;

   /* compute h + -p */
   g0 = h0 + 5; c = g0 >> 26; g0 &= 0x3ffffff;
   g1 = h1 + c; c = g1 >> 26; g1 &= 0x3ffffff;
   g2 = h2 + c; c = g2 >> 26; g2 &= 0x3ffffff;
   g3 = h3 + c; c = g3 >> 26; g3 &= 0x3ffffff;
   g4 = h4 + c - (1UL << 26);

   /* select h if h < p, or h + -p if h >= p */
   mask = (g4 >> 31) - 1;
   g0 &= mask;
   g1 &= mask;
   g2 &= mask;
   g3 &= mask;
   g4 &= mask;
   mask = ~mask;
   h0 = (h0 & mask) | g0;
   h1 = (h1 & mask) | g1;
   h2 = (h2 & mask) | g2;
   h3 = (h3 & mask) | g3;
   h4 = (h4 & mask) | g4;

   /* h = h % (2^128) */
   h0 = ((h0      ) | (h1 << 26)) & 0xffffffff;
   h1 = ((h1 >>  6) | (h2 << 20)) & 0xffffffff;
   h2 = ((h2 >> 12) | (h3 << 14)) & 0xffffffff;
   h3 = ((h3 >> 18) | (h4 <<  8)) & 0xffffffff;

   /* mac = (h + pad) % (2^128) */
   f = (ulong64)h0 + st->pad[0]            ; h0 = (ulong32)f;
   f = (ulong64)h1 + st->pad[1] + (f >> 32); h1 = (ulong32)f;
   f = (ulong64)h2 + st->pad[2] + (f >> 32); h2 = (ulong32)f;
   f = (ulong64)h3 + st->pad[3] + (f >> 32); h3 = (ulong32)f;

   STORE32L(h0, mac +  0);
   STORE32L(h1, mac +  4);
   STORE32L(h2, mac +  8);
   STORE32L(h3, mac + 12);

   /* zero out the state */
   st->h[0] = 0;
   st->h[1] = 0;
   st->h[2] = 0;
   st->h[3] = 0;
   st->h[4] = 0;
   st->r[0] = 0;
   st->r[1] = 0;
   st->r[2] = 0;
   st->r[3] = 0;
   st->r[4] = 0;
   st->pad[0] = 0;
   st->pad[1] = 0;
   st->pad[2] = 0;
   st->pad[3] = 0;

   *maclen = 16;
   return CRYPT_OK;
}


static const char * const sigma = "expand 32-byte k";
static const char * const tau   = "expand 16-byte k";

/**
   Initialize an ChaCha context (only the key)
   @param st        [out] The destination of the ChaCha state
   @param key       The secret key
   @param keylen    The length of the secret key (octets)
   @param rounds    Number of rounds (e.g. 20 for ChaCha20)
   @return CRYPT_OK if successful
*/
int chacha_setup(chacha_state *st, const unsigned char *key, unsigned long keylen, int rounds)
{
   const char *constants;

   // LTC_ARGCHK(st  != NULL);
   // LTC_ARGCHK(key != NULL);
   // LTC_ARGCHK(keylen == 32 || keylen == 16);

   if (rounds == 0) rounds = 20;

   LOAD32L(st->input[4], key + 0);
   LOAD32L(st->input[5], key + 4);
   LOAD32L(st->input[6], key + 8);
   LOAD32L(st->input[7], key + 12);
   if (keylen == 32) { /* 256bit */
      key += 16;
      constants = sigma;
   } else { /* 128bit */
      constants = tau;
   }
   LOAD32L(st->input[8],  key + 0);
   LOAD32L(st->input[9],  key + 4);
   LOAD32L(st->input[10], key + 8);
   LOAD32L(st->input[11], key + 12);
   LOAD32L(st->input[0],  constants + 0);
   LOAD32L(st->input[1],  constants + 4);
   LOAD32L(st->input[2],  constants + 8);
   LOAD32L(st->input[3],  constants + 12);
   st->rounds = rounds; /* e.g. 20 for chacha20 */
   st->ivlen = 0; /* will be set later by chacha_ivctr(32|64) */
   return CRYPT_OK;
}

#define ROL(x, y) ( (((ulong32)(x)<<(ulong32)((y)&31)) | (((ulong32)(x)&0xFFFFFFFFUL)>>(ulong32)((32-((y)&31))&31))) & 0xFFFFFFFFUL)
#define ROR(x, y) ( ((((ulong32)(x)&0xFFFFFFFFUL)>>(ulong32)((y)&31)) | ((ulong32)(x)<<(ulong32)((32-((y)&31))&31))) & 0xFFFFFFFFUL)
#define ROLc(x, y) ( (((ulong32)(x)<<(ulong32)((y)&31)) | (((ulong32)(x)&0xFFFFFFFFUL)>>(ulong32)((32-((y)&31))&31))) & 0xFFFFFFFFUL)
#define RORc(x, y) ( ((((ulong32)(x)&0xFFFFFFFFUL)>>(ulong32)((y)&31)) | ((ulong32)(x)<<(ulong32)((32-((y)&31))&31))) & 0xFFFFFFFFUL)

#define QUARTERROUND(a,b,c,d) \
  x[a] += x[b]; x[d] = ROL(x[d] ^ x[a], 16); \
  x[c] += x[d]; x[b] = ROL(x[b] ^ x[c], 12); \
  x[a] += x[b]; x[d] = ROL(x[d] ^ x[a],  8); \
  x[c] += x[d]; x[b] = ROL(x[b] ^ x[c],  7);

void _chacha_block(unsigned char *output, const ulong32 *input, int rounds) 
{
   ulong32 x[16];
   int i;
   XMEMCPY(x, input, sizeof(x));
   for (i = rounds; i > 0; i -= 2) {
      QUARTERROUND(0, 4, 8,12)
      QUARTERROUND(1, 5, 9,13)
      QUARTERROUND(2, 6,10,14)
      QUARTERROUND(3, 7,11,15)
      QUARTERROUND(0, 5,10,15)
      QUARTERROUND(1, 6,11,12)
      QUARTERROUND(2, 7, 8,13)
      QUARTERROUND(3, 4, 9,14)
   }
   for (i = 0; i < 16; ++i) {
     x[i] += input[i];
     STORE32L(x[i], output + 4 * i);
   }
}

/**
   Encrypt (or decrypt) bytes of ciphertext (or plaintext) with ChaCha
   @param st      The ChaCha state
   @param in      The plaintext (or ciphertext)
   @param inlen   The length of the input (octets)
   @param out     [out] The ciphertext (or plaintext), length inlen
   @return CRYPT_OK if successful
*/
int chacha_crypt(chacha_state *st, const unsigned char *in, unsigned long inlen, unsigned char *out) 
{
   unsigned char buf[64];
   unsigned long i, j;

   if (inlen == 0) return CRYPT_OK; /* nothing to do */

   // LTC_ARGCHK(st        != NULL);
   // LTC_ARGCHK(in        != NULL);
   // LTC_ARGCHK(out       != NULL);
   // LTC_ARGCHK(st->ivlen != 0);

   if (st->ksleft > 0) {
      j = st->ksleft < inlen ? st->ksleft :inlen;
      for (i = 0; i < j; ++i, st->ksleft--) out[i] = in[i] ^ st->kstream[64 - st->ksleft];
      inlen -= j;
      if (inlen == 0) return CRYPT_OK;
      out += j;
      in  += j;
   }
   for (;;) {
     _chacha_block(buf, st->input, st->rounds);
     if (st->ivlen == 8) {
       /* IV-64bit, increment 64bit counter */
       if (0 == ++st->input[12] && 0 == ++st->input[13]) return CRYPT_OVERFLOW;
     }
     else {
       /* IV-96bit, increment 32bit counter */
       if (0 == ++st->input[12]) return CRYPT_OVERFLOW;
     }
     if (inlen <= 64) {
       for (i = 0; i < inlen; ++i) out[i] = in[i] ^ buf[i];
       st->ksleft = 64 - inlen;
       for (i = inlen; i < 64; ++i) st->kstream[i] = buf[i];
       return CRYPT_OK;
     }
     for (i = 0; i < 64; ++i) out[i] = in[i] ^ buf[i];
     inlen -= 64;
     out += 64;
     in  += 64;
   }
}









/**
   Decrypt bytes of ciphertext with ChaCha20Poly1305
   @param st      The ChaCha20Poly1305 state
   @param in      The ciphertext
   @param inlen   The length of the input (octets)
   @param out     [out] The plaintext (length inlen)
   @return CRYPT_OK if successful
*/
int chacha20poly1305_decrypt(chacha20poly1305_state *st, const unsigned char *in, unsigned long inlen, unsigned char *out)  
{
   unsigned char padzero[16] = { 0 };
   unsigned long padlen;
   int err;

   padzero[0] =0; padzero[1] =0; padzero[2] =0; padzero[3] =0;
   if (inlen == 0) return CRYPT_OK; /* nothing to do */
   // LTC_ARGCHK(st != NULL);

   if (st->aadflg) {
      padlen = 16 - (unsigned long)(st->aadlen % 16);
      if (padlen < 16) {
        if ((err = poly1305_process(&st->poly, padzero, padlen)) != CRYPT_OK) return err;
      }
      st->aadflg = 0; /* no more AAD */
   }
   if (st->aadflg) st->aadflg = 0; /* no more AAD */
   if ((err = poly1305_process(&st->poly, in, inlen)) != CRYPT_OK)         return err;
   if ((err = chacha_crypt(&st->chacha, in, inlen, out)) != CRYPT_OK)      return err;
   st->ctlen += (ulong64)inlen;
   return CRYPT_OK;
}



/**
   Encrypt bytes of ciphertext with ChaCha20Poly1305
   @param st      The ChaCha20Poly1305 state
   @param in      The plaintext
   @param inlen   The length of the input (octets)
   @param out     [out] The ciphertext (length inlen)
   @return CRYPT_OK if successful
*/
int chacha20poly1305_encrypt(chacha20poly1305_state *st, const unsigned char *in, unsigned long inlen, unsigned char *out) 
{
   unsigned char padzero[32] = { 0 };
   unsigned long padlen;
   int err;

   padzero[0] =0; padzero[1] =0; padzero[2] =0; padzero[3] =0;

   if (inlen == 0) return CRYPT_OK; /* nothing to do */
   // LTC_ARGCHK(st != NULL);

   if ((err = chacha_crypt(&st->chacha, in, inlen, out)) != CRYPT_OK)         return err;
   if (st->aadflg) {
      padlen = 16 - (unsigned long)(st->aadlen % 16);
      if (padlen < 16) {
        if ((err = poly1305_process(&st->poly, padzero, padlen)) != CRYPT_OK) return err;
      }
      st->aadflg = 0; /* no more AAD */
   }
   if ((err = poly1305_process(&st->poly, out, inlen)) != CRYPT_OK)           return err;
   st->ctlen += (ulong64)inlen;
   return CRYPT_OK;
}


/**
  Add AAD to the ChaCha20Poly1305 state
  @param st     The ChaCha20Poly1305 state
  @param in     The additional authentication data to add to the ChaCha20Poly1305 state
  @param inlen  The length of the ChaCha20Poly1305 data.
  @return CRYPT_OK on success
 */
int chacha20poly1305_add_aad(chacha20poly1305_state *st, const unsigned char *in, unsigned long inlen)
{
   int err;

   if (inlen == 0) return CRYPT_OK; /* nothing to do */
   // LTC_ARGCHK(st != NULL);

   if (st->aadflg == 0) return CRYPT_ERROR;
   if ((err = poly1305_process(&st->poly, in, inlen)) != CRYPT_OK) return err;
   st->aadlen += (ulong64)inlen;
   return CRYPT_OK;
}

/**
   Initialize an POLY1305 context.
   @param st       The POLY1305 state
   @param key      The secret key
   @param keylen   The length of the secret key (octets)
   @return CRYPT_OK if successful
*/
int poly1305_init(poly1305_state *st, const unsigned char *key, unsigned long keylen)
{
   // LTC_ARGCHK(st  != NULL);
   // LTC_ARGCHK(key != NULL);
   // LTC_ARGCHK(keylen == 32);

   /* r &= 0xffffffc0ffffffc0ffffffc0fffffff */
   LOAD32L(st->r[0], key +  0); st->r[0] = (st->r[0]     ) & 0x3ffffff;
   LOAD32L(st->r[1], key +  3); st->r[1] = (st->r[1] >> 2) & 0x3ffff03;
   LOAD32L(st->r[2], key +  6); st->r[2] = (st->r[2] >> 4) & 0x3ffc0ff;
   LOAD32L(st->r[3], key +  9); st->r[3] = (st->r[3] >> 6) & 0x3f03fff;
   LOAD32L(st->r[4], key + 12); st->r[4] = (st->r[4] >> 8) & 0x00fffff;

   /* h = 0 */
   st->h[0] = 0;
   st->h[1] = 0;
   st->h[2] = 0;
   st->h[3] = 0;
   st->h[4] = 0;

   /* save pad for later */
   LOAD32L(st->pad[0], key + 16);
   LOAD32L(st->pad[1], key + 20);
   LOAD32L(st->pad[2], key + 24);
   LOAD32L(st->pad[3], key + 28);

   st->leftover = 0;
   st->final = 0;
   return CRYPT_OK;
}
/**
   Initialize an ChaCha20Poly1305 context (only the key)
   @param st        [out] The destination of the ChaCha20Poly1305 state
   @param key       The secret key
   @param keylen    The length of the secret key (octets)
   @return CRYPT_OK if successful
*/
int chacha20poly1305_init(chacha20poly1305_state *st, const unsigned char *key, unsigned long keylen)
{
   return chacha_setup(&st->chacha, key, keylen, 20);
}
/**
  Set IV + counter data to the ChaCha state
  @param st      The ChaCha20 state
  @param iv      The IV data to add
  @param ivlen   The length of the IV (must be 12)
  @param counter 32bit (unsigned) initial counter value
  @return CRYPT_OK on success
 */
int chacha_ivctr32(chacha_state *st, const unsigned char *iv, unsigned long ivlen, ulong32 counter)
{
   // LTC_ARGCHK(st != NULL);
   // LTC_ARGCHK(iv != NULL);
   //  96bit IV + 32bit counter 
   // LTC_ARGCHK(ivlen == 12);

   st->input[12] = counter;
   LOAD32L(st->input[13], iv + 0);
   LOAD32L(st->input[14], iv + 4);
   LOAD32L(st->input[15], iv + 8);
   st->ksleft = 0;
   st->ivlen = ivlen;
   return CRYPT_OK;
}

/**
  Set IV + counter data to the ChaCha state
  @param st      The ChaCha20 state
  @param iv      The IV data to add
  @param ivlen   The length of the IV (must be 8)
  @param counter 64bit (unsigned) initial counter value
  @return CRYPT_OK on success
 */
int chacha_ivctr64(chacha_state *st, const unsigned char *iv, unsigned long ivlen, ulong64 counter)
{
   // LTC_ARGCHK(st != NULL);
   // LTC_ARGCHK(iv != NULL);
   /* 64bit IV + 64bit counter */
   // LTC_ARGCHK(ivlen == 8);

   st->input[12] = (ulong32)(counter & 0xFFFFFFFF);
   st->input[13] = (ulong32)(counter >> 32);
   LOAD32L(st->input[14], iv + 0);
   LOAD32L(st->input[15], iv + 4);
   st->ksleft = 0;
   st->ivlen = ivlen;
   return CRYPT_OK;
}

/**
  Generate a stream of random bytes via ChaCha
  @param st      The ChaCha20 state
  @param out     [out] The output buffer
  @param outlen  The output length
  @return CRYPT_OK on success
 */
int chacha_keystream(chacha_state *st, unsigned char *out, unsigned long outlen)
{
   if (outlen == 0) return CRYPT_OK; /* nothing to do */
   // LTC_ARGCHK(out != NULL);
   XMEMSET(out, 0, outlen);
   return chacha_crypt(st, out, outlen, out);
}

/**
  Set IV + counter data to the ChaCha20Poly1305 state and reset the context
  @param st     The ChaCha20Poly1305 state
  @param iv     The IV data to add
  @param ivlen  The length of the IV (must be 12 or 8)
  @return CRYPT_OK on success
 */
int chacha20poly1305_setiv(chacha20poly1305_state *st, const unsigned char *iv, unsigned long ivlen) 
{
   chacha_state tmp_st;
   int i, err;
   unsigned char polykey[32];

   // LTC_ARGCHK(st != NULL);
   // LTC_ARGCHK(iv != NULL);
   // LTC_ARGCHK(ivlen == 12 || ivlen == 8);

   /* set IV for chacha20 */
   if (ivlen == 12) {
      /* IV 96bit */
      if ((err = chacha_ivctr32(&st->chacha, iv, ivlen, 1)) != CRYPT_OK) return err;
   }
   else {
      /* IV 64bit */
      if ((err = chacha_ivctr64(&st->chacha, iv, ivlen, 1)) != CRYPT_OK) return err;
   }

   /* copy chacha20 key to temporary state */
   for(i = 0; i < 12; i++) tmp_st.input[i] = st->chacha.input[i];
   tmp_st.rounds = 20;
   /* set IV */
   if (ivlen == 12) {
      /* IV 32bit */
      if ((err = chacha_ivctr32(&tmp_st, iv, ivlen, 0)) != CRYPT_OK) return err;
   }
   else {
      /* IV 64bit */
      if ((err = chacha_ivctr64(&tmp_st, iv, ivlen, 0)) != CRYPT_OK) return err;
   }
   /* (re)generate new poly1305 key */
   if ((err = chacha_keystream(&tmp_st, polykey, 32)) != CRYPT_OK) return err;
   /* (re)initialise poly1305 */
   if ((err = poly1305_init(&st->poly, polykey, 32)) != CRYPT_OK) return err;
   st->ctlen  = 0;
   st->aadlen = 0;
   st->aadflg = 1;

   return CRYPT_OK;
}




/**
  Process an entire GCM packet in one call.
  @param key               The secret key
  @param keylen            The length of the secret key
  @param iv                The initialization vector
  @param ivlen             The length of the initialization vector
  @param aad               The additional authentication data (header)
  @param aadlen            The length of the aad
  @param in                The plaintext
  @param inlen             The length of the plaintext (ciphertext length is the same)
  @param out               The ciphertext
  @param tag               [out] The MAC tag
  @param taglen            [in/out] The MAC tag length
  @param direction         Encrypt or Decrypt mode (CHACHA20POLY1305_ENCRYPT or CHACHA20POLY1305_DECRYPT)
  @return CRYPT_OK on success
 */

unsigned char in[16], out[16];
unsigned long inlen = 16;
unsigned char buff[411*64];


int chacha20poly1305_memory(const unsigned char *key, unsigned long keylen,
                            const unsigned char *iv,  unsigned long ivlen,
                            const unsigned char *aad, unsigned long aadlen,
                            // const unsigned char *in,  unsigned long inlen,
                                  // unsigned char *out,
                                  unsigned char *tag, unsigned long *taglen,
                            int direction)
{

  unsigned char dummy =0;

   chacha20poly1305_state st;
   int err;
   int y;

   // LTC_ARGCHK(key != NULL);
   // LTC_ARGCHK(iv  != NULL);
   // LTC_ARGCHK(in  != NULL);
   // LTC_ARGCHK(out != NULL);
   // LTC_ARGCHK(tag != NULL);
   klee_make_symbolic(&y, sizeof(y), "y");
   chacha20poly1305_init(&st, key, keylen);
   chacha20poly1305_setiv(&st, iv, ivlen);
  
   if (aad && aadlen > 0) {
      chacha20poly1305_add_aad(&st, aad, aadlen);
   }

    victim_fun2(y);
   if (direction == CHACHA20POLY1305_ENCRYPT) {
      err = chacha20poly1305_encrypt(&st, in, inlen, out);
   }
   else if (direction == CHACHA20POLY1305_DECRYPT) {
      err = chacha20poly1305_decrypt(&st, in, inlen, out);
   }

//    else {
//       err = CRYPT_INVALID_ARG;
//       goto LBL_ERR;
//    }
//    err = chacha20poly1305_done(&st, tag, taglen);
// LBL_ERR:
// #ifdef LTC_CLEAN_STACK
//    zeromem(&st, sizeof(chacha20poly1305_state));
// #endif
   return err;
}

int main() {
    unsigned char key[16];
    unsigned char iv[16];
    unsigned char aad[16];
    unsigned char tag[16];
    int direction;
    unsigned long taglen;
    int x;
    
    klee_make_symbolic(&x, sizeof(x), "x");
    klee_make_symbolic(&key, sizeof(key), "key");
    klee_make_symbolic(&iv, sizeof(iv), "iv");
    klee_make_symbolic(&aad, sizeof(aad), "aad");
    klee_make_symbolic(&tag, sizeof(tag), "tag");
    klee_make_symbolic(&direction, sizeof(direction), "direction");
    victim_fun1(x);
    chacha20poly1305_memory(key, 16, iv, 16, aad, 16, tag, &taglen, direction);
    victim_fun3(x);
    return 0;
}


/* ref:         HEAD -> develop */
/* git commit:  c9c3c4273956ae945aecec7122cd0df71a210803 */
/* commit time: 2018-07-10 07:11:39 +0200 */
