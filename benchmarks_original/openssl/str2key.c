/* crypto/des/str2key.c */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 * 
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 * 
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from 
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 * 
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */

// #include "des_locl.h"
#include <klee/klee.h>
#include <string.h>
typedef unsigned char DES_cblock[8];
#define DES_KEY_SZ 	(sizeof(DES_cblock))
#define DES_LONG unsigned long



#define c2l(c,l)	(l =((DES_LONG)(*((c)++)))    , \
			 l|=((DES_LONG)(*((c)++)))<< 8L, \
			 l|=((DES_LONG)(*((c)++)))<<16L, \
			 l|=((DES_LONG)(*((c)++)))<<24L)

#define c2ln(c,l1,l2,n)	{ \
			c+=n; \
			l1=l2=0; \
			switch (n) { \
			case 8: l2 =((DES_LONG)(*(--(c))))<<24L; \
			case 7: l2|=((DES_LONG)(*(--(c))))<<16L; \
			case 6: l2|=((DES_LONG)(*(--(c))))<< 8L; \
			case 5: l2|=((DES_LONG)(*(--(c))));     \
			case 4: l1 =((DES_LONG)(*(--(c))))<<24L; \
			case 3: l1|=((DES_LONG)(*(--(c))))<<16L; \
			case 2: l1|=((DES_LONG)(*(--(c))))<< 8L; \
			case 1: l1|=((DES_LONG)(*(--(c))));     \
				} \
			}

#define l2c(l,c)	(*((c)++)=(unsigned char)(((l)     )&0xff), \
			 *((c)++)=(unsigned char)(((l)>> 8L)&0xff), \
			 *((c)++)=(unsigned char)(((l)>>16L)&0xff), \
			 *((c)++)=(unsigned char)(((l)>>24L)&0xff))

const unsigned char odd_parity[256]={
  1,  1,  2,  2,  4,  4,  7,  7,  8,  8, 11, 11, 13, 13, 14, 14,
 16, 16, 19, 19, 21, 21, 22, 22, 25, 25, 26, 26, 28, 28, 31, 31,
 32, 32, 35, 35, 37, 37, 38, 38, 41, 41, 42, 42, 44, 44, 47, 47,
 49, 49, 50, 50, 52, 52, 55, 55, 56, 56, 59, 59, 61, 61, 62, 62,
 64, 64, 67, 67, 69, 69, 70, 70, 73, 73, 74, 74, 76, 76, 79, 79,
 81, 81, 82, 82, 84, 84, 87, 87, 88, 88, 91, 91, 93, 93, 94, 94,
 97, 97, 98, 98,100,100,103,103,104,104,107,107,109,109,110,110,
112,112,115,115,117,117,118,118,121,121,122,122,124,124,127,127,
128,128,131,131,133,133,134,134,137,137,138,138,140,140,143,143,
145,145,146,146,148,148,151,151,152,152,155,155,157,157,158,158,
161,161,162,162,164,164,167,167,168,168,171,171,173,173,174,174,
176,176,179,179,181,181,182,182,185,185,186,186,188,188,191,191,
193,193,194,194,196,196,199,199,200,200,203,203,205,205,206,206,
208,208,211,211,213,213,214,214,217,217,218,218,220,220,223,223,
224,224,227,227,229,229,230,230,233,233,234,234,236,236,239,239,
241,241,242,242,244,244,247,247,248,248,251,251,253,253,254,254};

void DES_set_odd_parity(DES_cblock *key)
{
	int i;

	for (i=0; i<DES_KEY_SZ; i++)
		(*key)[i]=odd_parity[(*key)[i]];
}


// void DES_encrypt1(DES_LONG *data, DES_key_schedule *ks, int enc)
// {
// 	register DES_LONG l,r,t,u;
// #ifdef DES_PTR
// 	register const unsigned char *des_SP=(const unsigned char *)DES_SPtrans;
// #endif
// #ifndef DES_UNROLL
// 	register int i;
// #endif
// 	register DES_LONG *s;

// 	r=data[0];
// 	l=data[1];

// 	IP(r,l);
// 	/* Things have been modified so that the initial rotate is
// 	 * done outside the loop.  This required the
// 	 * DES_SPtrans values in sp.h to be rotated 1 bit to the right.
// 	 * One perl script later and things have a 5% speed up on a sparc2.
// 	 * Thanks to Richard Outerbridge <71755.204@CompuServe.COM>
// 	 * for pointing this out. */
// 	/* clear the top bits on machines with 8byte longs */
// 	/* shift left by 2 */
// 	r=ROTATE(r,29)&0xffffffffL;
// 	l=ROTATE(l,29)&0xffffffffL;

// 	s=ks->ks->deslong;
// 	/* I don't know if it is worth the effort of loop unrolling the
// 	 * inner loop */
// 	if (enc)
// 		{
// #ifdef DES_UNROLL
// 		D_ENCRYPT(l,r, 0); /*  1 */
// 		D_ENCRYPT(r,l, 2); /*  2 */
// 		D_ENCRYPT(l,r, 4); /*  3 */
// 		D_ENCRYPT(r,l, 6); /*  4 */
// 		D_ENCRYPT(l,r, 8); /*  5 */
// 		D_ENCRYPT(r,l,10); /*  6 */
// 		D_ENCRYPT(l,r,12); /*  7 */
// 		D_ENCRYPT(r,l,14); /*  8 */
// 		D_ENCRYPT(l,r,16); /*  9 */
// 		D_ENCRYPT(r,l,18); /*  10 */
// 		D_ENCRYPT(l,r,20); /*  11 */
// 		D_ENCRYPT(r,l,22); /*  12 */
// 		D_ENCRYPT(l,r,24); /*  13 */
// 		D_ENCRYPT(r,l,26); /*  14 */
// 		D_ENCRYPT(l,r,28); /*  15 */
// 		D_ENCRYPT(r,l,30); /*  16 */
// #else
// 		for (i=0; i<32; i+=8)
// 			{
// 			D_ENCRYPT(l,r,i+0); /*  1 */
// 			D_ENCRYPT(r,l,i+2); /*  2 */
// 			D_ENCRYPT(l,r,i+4); /*  3 */
// 			D_ENCRYPT(r,l,i+6); /*  4 */
// 			}
// #endif
// 		}
// 	else
// 		{
// #ifdef DES_UNROLL
// 		D_ENCRYPT(l,r,30); /* 16 */
// 		D_ENCRYPT(r,l,28); /* 15 */
// 		D_ENCRYPT(l,r,26); /* 14 */
// 		D_ENCRYPT(r,l,24); /* 13 */
// 		D_ENCRYPT(l,r,22); /* 12 */
// 		D_ENCRYPT(r,l,20); /* 11 */
// 		D_ENCRYPT(l,r,18); /* 10 */
// 		D_ENCRYPT(r,l,16); /*  9 */
// 		D_ENCRYPT(l,r,14); /*  8 */
// 		D_ENCRYPT(r,l,12); /*  7 */
// 		D_ENCRYPT(l,r,10); /*  6 */
// 		D_ENCRYPT(r,l, 8); /*  5 */
// 		D_ENCRYPT(l,r, 6); /*  4 */
// 		D_ENCRYPT(r,l, 4); /*  3 */
// 		D_ENCRYPT(l,r, 2); /*  2 */
// 		D_ENCRYPT(r,l, 0); /*  1 */
// #else
// 		for (i=30; i>0; i-=8)
// 			{
// 			D_ENCRYPT(l,r,i-0); /* 16 */
// 			D_ENCRYPT(r,l,i-2); /* 15 */
// 			D_ENCRYPT(l,r,i-4); /* 14 */
// 			D_ENCRYPT(r,l,i-6); /* 13 */
// 			}
// #endif
// 		}

// 	/* rotate and clear the top bits on machines with 8byte longs */
// 	l=ROTATE(l,3)&0xffffffffL;
// 	r=ROTATE(r,3)&0xffffffffL;

// 	FP(r,l);
// 	data[0]=l;
// 	data[1]=r;
// 	l=r=t=u=0;
// }


// DES_LONG DES_cbc_cksum(const unsigned char *in, DES_cblock *output,
// 		       long length, DES_key_schedule *schedule,
// 		       const_DES_cblock *ivec)
// 	{
// 	register DES_LONG tout0,tout1,tin0,tin1;
// 	register long l=length;
// 	DES_LONG tin[2];
// 	unsigned char *out = &(*output)[0];
// 	const unsigned char *iv = &(*ivec)[0];

// 	c2l(iv,tout0);
// 	c2l(iv,tout1);
// 	for (; l>0; l-=8)
// 		{
// 		if (l >= 8)
// 			{
// 			c2l(in,tin0);
// 			c2l(in,tin1);
// 			}
// 		else
// 			c2ln(in,tin0,tin1,l);
			
// 		tin0^=tout0; tin[0]=tin0;
// 		tin1^=tout1; tin[1]=tin1;
// 		DES_encrypt1((DES_LONG *)tin,schedule,DES_ENCRYPT);
// 		/* fix 15/10/91 eay - thanks to keithr@sco.COM */
// 		tout0=tin[0];
// 		tout1=tin[1];
// 		}
// 	if (out != NULL)
// 		{
// 		l2c(tout0,out);
// 		l2c(tout1,out);
// 		}
// 	tout0=tin0=tin1=tin[0]=tin[1]=0;
// 	/*
// 	  Transform the data in tout1 so that it will
// 	  match the return value that the MIT Kerberos
// 	  mit_des_cbc_cksum API returns.
// 	*/
// 	tout1 = ((tout1 >> 24L) & 0x000000FF)
// 	      | ((tout1 >> 8L)  & 0x0000FF00)
// 	      | ((tout1 << 8L)  & 0x00FF0000)
// 	      | ((tout1 << 24L) & 0xFF000000);
// 	return(tout1);
// 	}


void DES_string_to_2keys(const char *str, DES_cblock *key1, DES_cblock *key2)
	{
	// DES_key_schedule ks;
	int i,length=16;
	register unsigned char j;

	// memset(key1,0,8);
	// memset(key2,0,8);
	//length=strlen(str);
    //klee_make_symbolic(&length, sizeof(length), "length");
#ifdef OLD_STR_TO_KEY
	if (length <= 8)
		{
		for (i=0; i<length; i++)
			{
			(*key2)[i]=(*key1)[i]=(str[i]<<1);
			}
		}
	else
		{
		for (i=0; i<length; i++)
			{
			if ((i/8)&1)
				(*key2)[i%8]^=(str[i]<<1);
			else
				(*key1)[i%8]^=(str[i]<<1);
			}
		}
#else /* MIT COMPATIBLE */
	for (i=0; i<length; i++)
	{
		j=str[i];
		if ((i%32) < 16)
			{
			if ((i%16) < 8)
				(*key1)[i%8]^=(j<<1);
			else
				(*key2)[i%8]^=(j<<1);
			}
		else
			{
			j=((j<<4)&0xf0)|((j>>4)&0x0f);
			j=((j<<2)&0xcc)|((j>>2)&0x33);
			j=((j<<1)&0xaa)|((j>>1)&0x55);
			if ((i%16) < 8)
				(*key1)[7-(i%8)]^=j;
			else
				(*key2)[7-(i%8)]^=j;
			}
	}
	if (length <= 8) memcpy(key2,key1,8);
#endif

	DES_set_odd_parity(key1);
	DES_set_odd_parity(key2);

// #ifdef EXPERIMENTAL_STR_TO_STRONG_KEY
// 	if(DES_is_weak_key(key1))
// 	    (*key1)[7] ^= 0xF0;
// 	DES_set_key(key1,&ks);
// #else
// 	DES_set_key_unchecked(key1,&ks);
// #endif

// 	DES_cbc_cksum((const unsigned char*)str,key1,length,&ks,key1);

// #ifdef EXPERIMENTAL_STR_TO_STRONG_KEY
// 	if(DES_is_weak_key(key2))
// 	    (*key2)[7] ^= 0xF0;
// 	DES_set_key(key2,&ks);
// #else
// 	DES_set_key_unchecked(key2,&ks);
// #endif

// 	DES_cbc_cksum((const unsigned char*)str,key2,length,&ks,key2);
// 	OPENSSL_cleanse(&ks,sizeof(ks));
// 	DES_set_odd_parity(key1);
// 	DES_set_odd_parity(key2);
}


unsigned char buff[29*64];
DES_cblock k1, k2;
int main()
{	
	
    DES_cblock *key1 = &k1;
    DES_cblock *key2 = &k1;
    char *str= "";

    //klee_make_symbolic(&key1, sizeof(key1), "key1");
    //klee_make_symbolic(&key2, sizeof(key2), "key2");
    klee_make_symbolic(&str, sizeof(str), "str");

	DES_string_to_2keys(str, key1, key2);
    return 0;
}
