/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 */

/**
   @file ocb3_init.c
   OCB implementation, initialize state, by Tom St Denis
*/
/* max size of either a cipher/hash block or symmetric key [largest of the two] */
#include <stddef.h>
#include <klee/klee.h>

#define MAXBLOCKSIZE  64

unsigned int array1_size = 16; 
uint8_t array1[16];
uint8_t array2[256];
uint8_t temp;


uint8_t victim_fun1(int idx) __attribute__ ((optnone)) {
    if (idx < array1_size) {    
        temp &= array2[array1[idx]];
    }   
    array1[8] = 0;  
    array2[8] = 0;  
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
/*
   Test if a cipher index is valid
   @param idx   The index of the cipher to search for
   @return CRYPT_OK if valid
*/
int cipher_is_valid(int idx)
{
   return CRYPT_OK;
}
/**
   Compute xor for two blocks of bytes 'out = block_a XOR block_b' (internal function)
   @param out        The block of bytes (output)
   @param block_a    The block of bytes (input)
   @param block_b    The block of bytes (input)
   @param block_len  The size of block_a, block_b, out
*/
void ocb3_int_xor_blocks(unsigned char *out, const unsigned char *block_a, const unsigned char *block_b, unsigned long block_len)
{
   int x;
   if (out == block_a) {
     for (x = 0; x < (int)block_len; x++) out[x] ^= block_b[x];
   }
   else {
     for (x = 0; x < (int)block_len; x++) out[x] = block_a[x] ^ block_b[x];
   }
}


/**
   Zero a block of memory
   @param out    The destination of the area to zero
   @param outlen The length of the area to zero (octets)
*/
void zeromem(volatile void *out, size_t outlen)
{
   volatile char *mem = out;
   // LTC_ARGCHKVD(out != NULL);
   while (outlen-- > 0) {
      *mem++ = '\0';
   }
}


typedef union Symmetric_key {
#ifdef LTC_DES
   struct des_key des;
   struct des3_key des3;
#endif
#ifdef LTC_RC2
   struct rc2_key rc2;
#endif
#ifdef LTC_SAFER
   struct safer_key safer;
#endif
#ifdef LTC_TWOFISH
   struct twofish_key  twofish;
#endif
#ifdef LTC_BLOWFISH
   struct blowfish_key blowfish;
#endif
#ifdef LTC_RC5
   struct rc5_key      rc5;
#endif
#ifdef LTC_RC6
   struct rc6_key      rc6;
#endif
#ifdef LTC_SAFERP
   struct saferp_key   saferp;
#endif
#ifdef LTC_RIJNDAEL
   struct rijndael_key rijndael;
#endif
#ifdef LTC_XTEA
   struct xtea_key     xtea;
#endif
#ifdef LTC_CAST5
   struct cast5_key    cast5;
#endif
#ifdef LTC_NOEKEON
   struct noekeon_key  noekeon;
#endif
#ifdef LTC_SKIPJACK
   struct skipjack_key skipjack;
#endif
#ifdef LTC_KHAZAD
   struct khazad_key   khazad;
#endif
#ifdef LTC_ANUBIS
   struct anubis_key   anubis;
#endif
#ifdef LTC_KSEED
   struct kseed_key    kseed;
#endif
#ifdef LTC_KASUMI
   struct kasumi_key   kasumi;
#endif
#ifdef LTC_MULTI2
   struct multi2_key   multi2;
#endif
#ifdef LTC_CAMELLIA
   struct camellia_key camellia;
#endif
#ifdef LTC_IDEA
   struct idea_key     idea;
#endif
#ifdef LTC_SERPENT
   struct serpent_key  serpent;
#endif
   void   *data;
} symmetric_key;


typedef struct {
   unsigned char     Offset_0[MAXBLOCKSIZE],       /* Offset_0 value */
                     Offset_current[MAXBLOCKSIZE], /* Offset_{current_block_index} value */
                     L_dollar[MAXBLOCKSIZE],       /* L_$ value */
                     L_star[MAXBLOCKSIZE],         /* L_* value */
                     L_[32][MAXBLOCKSIZE],         /* L_{i} values */
                     tag_part[MAXBLOCKSIZE],       /* intermediate result of tag calculation */
                     checksum[MAXBLOCKSIZE];       /* current checksum */

   /* AAD related members */
   unsigned char     aSum_current[MAXBLOCKSIZE],    /* AAD related helper variable */
                     aOffset_current[MAXBLOCKSIZE], /* AAD related helper variable */
                     adata_buffer[MAXBLOCKSIZE];    /* AAD buffer */
   int               adata_buffer_bytes;            /* bytes in AAD buffer */
   unsigned long     ablock_index;                  /* index # for current adata (AAD) block */

   symmetric_key     key;                     /* scheduled key for cipher */
   unsigned long     block_index;             /* index # for current data block */
   int               cipher,                  /* cipher idx */
                     tag_len,                 /* length of tag */
                     block_len;               /* length of block */
} ocb3_state;

void _ocb3_int_calc_offset_zero(ocb3_state *ocb, const unsigned char *nonce, unsigned long noncelen, unsigned long taglen)
{
   int x, y, bottom;
   int idx, shift;
   unsigned char iNonce[MAXBLOCKSIZE];
   unsigned char iKtop[MAXBLOCKSIZE];
   unsigned char iStretch[MAXBLOCKSIZE+8];

   /* Nonce = zeros(127-bitlen(N)) || 1 || N          */
   zeromem(iNonce, sizeof(iNonce));
   for (x = ocb->block_len-1, y=0; y<(int)noncelen; x--, y++) {
     iNonce[x] = nonce[noncelen-y-1];
   }
   iNonce[x] = 0x01;
   iNonce[0] |= ((taglen*8) % 128) << 1;

   /* bottom = str2num(Nonce[123..128])               */
   bottom = iNonce[ocb->block_len-1] & 0x3F;

   /* Ktop = ENCIPHER(K, Nonce[1..122] || zeros(6))   */
   iNonce[ocb->block_len-1] = iNonce[ocb->block_len-1] & 0xC0;
   // if ((cipher_descriptor[ocb->cipher].ecb_encrypt(iNonce, iKtop, &ocb->key)) != CRYPT_OK) {
   //    zeromem(ocb->Offset_current, ocb->block_len);
   //    return;
   // }

   /* Stretch = Ktop || (Ktop[1..64] xor Ktop[9..72]) */
   for (x = 0; x < ocb->block_len; x++) {
     iStretch[x] = iKtop[x];
   }
   for (y = 0; y < 8; y++) {
     iStretch[x+y] = iKtop[y] ^ iKtop[y+1];
   }

   /* Offset_0 = Stretch[1+bottom..128+bottom]        */
   idx = bottom / 8;
   shift = (bottom % 8);
   for (x = 0; x < ocb->block_len; x++) {
      ocb->Offset_current[x] = iStretch[idx+x] << shift;
      if (shift > 0) {
        ocb->Offset_current[x] |= iStretch[idx+x+1] >> (8-shift);
      }
   }
}

static const struct {
    int           len;
    unsigned char poly_mul[MAXBLOCKSIZE];
} polys[] = {
{
    8,
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B }
}, {
    16,
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87 }
}
};

/**
   Initialize an OCB context
   @param ocb       [out] The destination of the OCB state
   @param cipher    The index of the desired cipher
   @param key       The secret key
   @param keylen    The length of the secret key (octets)
   @param nonce     The session nonce
   @param noncelen  The length of the session nonce (octets, up to 15)
   @param taglen    The length of the tag (octets, up to 16)
   @return CRYPT_OK if successful
*/
int ocb3_init(ocb3_state *ocb, int cipher,
             const unsigned char *key, unsigned long keylen,
             const unsigned char *nonce, unsigned long noncelen,
             unsigned long taglen)
{
   int poly, x, y, m, err;
   unsigned char *previous, *current;
   int z;
   klee_make_symbolic(&z, sizeof(z), "z");

   // LTC_ARGCHK(ocb   != NULL);
   // LTC_ARGCHK(key   != NULL);
   // LTC_ARGCHK(nonce != NULL);

   /* valid cipher? */
   if ((err = cipher_is_valid(cipher)) != CRYPT_OK) {
       return err;
   }
   ocb->cipher = cipher;

   /* Valid Nonce?
    * As of RFC7253: "string of no more than 120 bits" */
   if (noncelen > (120/8)) {
      return CRYPT_INVALID_ARG;
   }


   /* The blockcipher must have a 128-bit blocksize */
   // if (cipher_descriptor[cipher].block_length != 16) {
   //    return CRYPT_INVALID_ARG;
   // }

   /* The TAGLEN may be any value up to 128 (bits) */
   if (taglen > 16) {
      return CRYPT_INVALID_ARG;
   }
   ocb->tag_len = taglen;

   /* determine which polys to use */
   // ocb->block_len = cipher_descriptor[cipher].block_length;
   x = (int)(sizeof(polys)/sizeof(polys[0]));
   for (poly = 0; poly < x; poly++) {
       if (polys[poly].len == ocb->block_len) {
          break;
       }
   }
   //if (poly == x) {
      //return CRYPT_INVALID_ARG; /* block_len not found in polys */
   //}
   //if (polys[poly].len != ocb->block_len) {
      //return CRYPT_INVALID_ARG;
   //}

   // /* schedule the key */
   // if ((err = cipher_descriptor[cipher].setup(key, keylen, 0, &ocb->key)) != CRYPT_OK) {
   //    return err;
   // }

   //  L_* = ENCIPHER(K, zeros(128)) 
   // zeromem(ocb->L_star, ocb->block_len);
   // if ((err = cipher_descriptor[cipher].ecb_encrypt(ocb->L_star, ocb->L_star, &ocb->key)) != CRYPT_OK) {
   //    return err;
   // }
   //
   victim_fun2(z);

   /* compute L_$, L_0, L_1, ... */
   for (x = -1; x < 32; x++) {
      if (x == -1) {                /* gonna compute: L_$ = double(L_*) */
         current  = ocb->L_dollar;
         previous = ocb->L_star;
      }
      else if (x == 0) {            /* gonna compute: L_0 = double(L_$) */
         current  = ocb->L_[0];
         previous = ocb->L_dollar;
      }
      else {                        /* gonna compute: L_i = double(L_{i-1}) for every integer i > 0 */
         current  = ocb->L_[x];
         previous = ocb->L_[x-1];
      }
      m = previous[0] >> 7;
      for (y = 0; y < ocb->block_len-1; y++) {
         current[y] = ((previous[y] << 1) | (previous[y+1] >> 7)) & 255;
      }
      current[ocb->block_len-1] = (previous[ocb->block_len-1] << 1) & 255;
      if (m == 1) {
         /* current[] = current[] XOR polys[poly].poly_mul[]*/
         ocb3_int_xor_blocks(current, current, polys[poly].poly_mul, ocb->block_len);
      }
   }

   /* initialize ocb->Offset_current = Offset_0 */
   _ocb3_int_calc_offset_zero(ocb, nonce, noncelen, taglen);

   /* initialize checksum to all zeros */
   zeromem(ocb->checksum, ocb->block_len);

   /* set block index */
   ocb->block_index = 1;

   /* initialize AAD related stuff */
   ocb->ablock_index = 1;
   ocb->adata_buffer_bytes = 0;
   zeromem(ocb->aOffset_current, ocb->block_len);
   zeromem(ocb->aSum_current, ocb->block_len);

   return CRYPT_OK;
}

ocb3_state ocb;

int main()
{
   unsigned char key[32];
   unsigned char nonce[32];
   unsigned long keylen=32, noncelen=10, taglen=16;
   ocb.block_len = 16;
   int cipher = 0;
   int x;
   klee_make_symbolic(&x, sizeof(x), "x");
   klee_make_symbolic(&key, sizeof(key), "key");
   klee_make_symbolic(&nonce, sizeof(nonce), "nonce");
   //klee_make_symbolic(&taglen, sizeof(taglen), "taglen");
   //klee_make_symbolic(&noncelen, sizeof(noncelen), "noncelen");
   klee_make_symbolic(&keylen, sizeof(keylen), "keylen");

   victim_fun1(x);
   ocb3_init(&ocb, cipher, key, keylen, nonce, noncelen,taglen);
   victim_fun3(x);
  return 0;
}
/* ref:         HEAD -> develop */
/* git commit:  c9c3c4273956ae945aecec7122cd0df71a210803 */
/* commit time: 2018-07-10 07:11:39 +0200 */
