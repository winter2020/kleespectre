/* crypto/des/des.c */
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <klee/klee.h>

typedef unsigned char DES_cblock[8];
typedef /* const */ unsigned char const_DES_cblock[8];

#define DES_ENCRYPT	1
#define DES_DECRYPT	0
#define ITERATIONS 16
#define HALF_ITERATIONS 8
#define DES_KEY_SZ 	(sizeof(DES_cblock))

#define HPERM_OP(a,t,n,m) ((t)=((((a)<<(16-(n)))^(a))&(m)),\
	(a)=(a)^(t)^(t>>(16-(n))))
#define	ROTATE(a,n)	(((a)>>(n))+((a)<<(32-(n))))

#define PERM_OP(a,b,t,n,m) ((t)=((((a)>>(n))^(b))&(m)),\
	(b)^=(t),\
	(a)^=((t)<<(n)))

#define IP(l,r) \
	{ \
	register DES_LONG tt; \
	PERM_OP(r,l,tt, 4,0x0f0f0f0fL); \
	PERM_OP(l,r,tt,16,0x0000ffffL); \
	PERM_OP(r,l,tt, 2,0x33333333L); \
	PERM_OP(l,r,tt, 8,0x00ff00ffL); \
	PERM_OP(r,l,tt, 1,0x55555555L); \
	}

#define FP(l,r) \
	{ \
	register DES_LONG tt; \
	PERM_OP(l,r,tt, 1,0x55555555L); \
	PERM_OP(r,l,tt, 8,0x00ff00ffL); \
	PERM_OP(l,r,tt, 2,0x33333333L); \
	PERM_OP(r,l,tt,16,0x0000ffffL); \
	PERM_OP(l,r,tt, 4,0x0f0f0f0fL); \
	}



#define c2l(c,l)	(l =((DES_LONG)(*((c)++)))    , \
			 l|=((DES_LONG)(*((c)++)))<< 8L, \
			 l|=((DES_LONG)(*((c)++)))<<16L, \
			 l|=((DES_LONG)(*((c)++)))<<24L)

/* NOTE - c is not incremented as per c2l */
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

#define DES_LONG unsigned long
typedef struct DES_ks
{
	union
	{
		DES_cblock cblock;
/* make sure things are correct size on machines with
 * 8 byte longs */
		DES_LONG deslong[2];
	} ks[16];
} DES_key_schedule;



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






const DES_LONG DES_SPtrans[8][64]={
{
/* nibble 0 */
0x02080800L, 0x00080000L, 0x02000002L, 0x02080802L,
0x02000000L, 0x00080802L, 0x00080002L, 0x02000002L,
0x00080802L, 0x02080800L, 0x02080000L, 0x00000802L,
0x02000802L, 0x02000000L, 0x00000000L, 0x00080002L,
0x00080000L, 0x00000002L, 0x02000800L, 0x00080800L,
0x02080802L, 0x02080000L, 0x00000802L, 0x02000800L,
0x00000002L, 0x00000800L, 0x00080800L, 0x02080002L,
0x00000800L, 0x02000802L, 0x02080002L, 0x00000000L,
0x00000000L, 0x02080802L, 0x02000800L, 0x00080002L,
0x02080800L, 0x00080000L, 0x00000802L, 0x02000800L,
0x02080002L, 0x00000800L, 0x00080800L, 0x02000002L,
0x00080802L, 0x00000002L, 0x02000002L, 0x02080000L,
0x02080802L, 0x00080800L, 0x02080000L, 0x02000802L,
0x02000000L, 0x00000802L, 0x00080002L, 0x00000000L,
0x00080000L, 0x02000000L, 0x02000802L, 0x02080800L,
0x00000002L, 0x02080002L, 0x00000800L, 0x00080802L,
},{
/* nibble 1 */
0x40108010L, 0x00000000L, 0x00108000L, 0x40100000L,
0x40000010L, 0x00008010L, 0x40008000L, 0x00108000L,
0x00008000L, 0x40100010L, 0x00000010L, 0x40008000L,
0x00100010L, 0x40108000L, 0x40100000L, 0x00000010L,
0x00100000L, 0x40008010L, 0x40100010L, 0x00008000L,
0x00108010L, 0x40000000L, 0x00000000L, 0x00100010L,
0x40008010L, 0x00108010L, 0x40108000L, 0x40000010L,
0x40000000L, 0x00100000L, 0x00008010L, 0x40108010L,
0x00100010L, 0x40108000L, 0x40008000L, 0x00108010L,
0x40108010L, 0x00100010L, 0x40000010L, 0x00000000L,
0x40000000L, 0x00008010L, 0x00100000L, 0x40100010L,
0x00008000L, 0x40000000L, 0x00108010L, 0x40008010L,
0x40108000L, 0x00008000L, 0x00000000L, 0x40000010L,
0x00000010L, 0x40108010L, 0x00108000L, 0x40100000L,
0x40100010L, 0x00100000L, 0x00008010L, 0x40008000L,
0x40008010L, 0x00000010L, 0x40100000L, 0x00108000L,
},{
/* nibble 2 */
0x04000001L, 0x04040100L, 0x00000100L, 0x04000101L,
0x00040001L, 0x04000000L, 0x04000101L, 0x00040100L,
0x04000100L, 0x00040000L, 0x04040000L, 0x00000001L,
0x04040101L, 0x00000101L, 0x00000001L, 0x04040001L,
0x00000000L, 0x00040001L, 0x04040100L, 0x00000100L,
0x00000101L, 0x04040101L, 0x00040000L, 0x04000001L,
0x04040001L, 0x04000100L, 0x00040101L, 0x04040000L,
0x00040100L, 0x00000000L, 0x04000000L, 0x00040101L,
0x04040100L, 0x00000100L, 0x00000001L, 0x00040000L,
0x00000101L, 0x00040001L, 0x04040000L, 0x04000101L,
0x00000000L, 0x04040100L, 0x00040100L, 0x04040001L,
0x00040001L, 0x04000000L, 0x04040101L, 0x00000001L,
0x00040101L, 0x04000001L, 0x04000000L, 0x04040101L,
0x00040000L, 0x04000100L, 0x04000101L, 0x00040100L,
0x04000100L, 0x00000000L, 0x04040001L, 0x00000101L,
0x04000001L, 0x00040101L, 0x00000100L, 0x04040000L,
},{
/* nibble 3 */
0x00401008L, 0x10001000L, 0x00000008L, 0x10401008L,
0x00000000L, 0x10400000L, 0x10001008L, 0x00400008L,
0x10401000L, 0x10000008L, 0x10000000L, 0x00001008L,
0x10000008L, 0x00401008L, 0x00400000L, 0x10000000L,
0x10400008L, 0x00401000L, 0x00001000L, 0x00000008L,
0x00401000L, 0x10001008L, 0x10400000L, 0x00001000L,
0x00001008L, 0x00000000L, 0x00400008L, 0x10401000L,
0x10001000L, 0x10400008L, 0x10401008L, 0x00400000L,
0x10400008L, 0x00001008L, 0x00400000L, 0x10000008L,
0x00401000L, 0x10001000L, 0x00000008L, 0x10400000L,
0x10001008L, 0x00000000L, 0x00001000L, 0x00400008L,
0x00000000L, 0x10400008L, 0x10401000L, 0x00001000L,
0x10000000L, 0x10401008L, 0x00401008L, 0x00400000L,
0x10401008L, 0x00000008L, 0x10001000L, 0x00401008L,
0x00400008L, 0x00401000L, 0x10400000L, 0x10001008L,
0x00001008L, 0x10000000L, 0x10000008L, 0x10401000L,
},{
/* nibble 4 */
0x08000000L, 0x00010000L, 0x00000400L, 0x08010420L,
0x08010020L, 0x08000400L, 0x00010420L, 0x08010000L,
0x00010000L, 0x00000020L, 0x08000020L, 0x00010400L,
0x08000420L, 0x08010020L, 0x08010400L, 0x00000000L,
0x00010400L, 0x08000000L, 0x00010020L, 0x00000420L,
0x08000400L, 0x00010420L, 0x00000000L, 0x08000020L,
0x00000020L, 0x08000420L, 0x08010420L, 0x00010020L,
0x08010000L, 0x00000400L, 0x00000420L, 0x08010400L,
0x08010400L, 0x08000420L, 0x00010020L, 0x08010000L,
0x00010000L, 0x00000020L, 0x08000020L, 0x08000400L,
0x08000000L, 0x00010400L, 0x08010420L, 0x00000000L,
0x00010420L, 0x08000000L, 0x00000400L, 0x00010020L,
0x08000420L, 0x00000400L, 0x00000000L, 0x08010420L,
0x08010020L, 0x08010400L, 0x00000420L, 0x00010000L,
0x00010400L, 0x08010020L, 0x08000400L, 0x00000420L,
0x00000020L, 0x00010420L, 0x08010000L, 0x08000020L,
},{
/* nibble 5 */
0x80000040L, 0x00200040L, 0x00000000L, 0x80202000L,
0x00200040L, 0x00002000L, 0x80002040L, 0x00200000L,
0x00002040L, 0x80202040L, 0x00202000L, 0x80000000L,
0x80002000L, 0x80000040L, 0x80200000L, 0x00202040L,
0x00200000L, 0x80002040L, 0x80200040L, 0x00000000L,
0x00002000L, 0x00000040L, 0x80202000L, 0x80200040L,
0x80202040L, 0x80200000L, 0x80000000L, 0x00002040L,
0x00000040L, 0x00202000L, 0x00202040L, 0x80002000L,
0x00002040L, 0x80000000L, 0x80002000L, 0x00202040L,
0x80202000L, 0x00200040L, 0x00000000L, 0x80002000L,
0x80000000L, 0x00002000L, 0x80200040L, 0x00200000L,
0x00200040L, 0x80202040L, 0x00202000L, 0x00000040L,
0x80202040L, 0x00202000L, 0x00200000L, 0x80002040L,
0x80000040L, 0x80200000L, 0x00202040L, 0x00000000L,
0x00002000L, 0x80000040L, 0x80002040L, 0x80202000L,
0x80200000L, 0x00002040L, 0x00000040L, 0x80200040L,
},{
/* nibble 6 */
0x00004000L, 0x00000200L, 0x01000200L, 0x01000004L,
0x01004204L, 0x00004004L, 0x00004200L, 0x00000000L,
0x01000000L, 0x01000204L, 0x00000204L, 0x01004000L,
0x00000004L, 0x01004200L, 0x01004000L, 0x00000204L,
0x01000204L, 0x00004000L, 0x00004004L, 0x01004204L,
0x00000000L, 0x01000200L, 0x01000004L, 0x00004200L,
0x01004004L, 0x00004204L, 0x01004200L, 0x00000004L,
0x00004204L, 0x01004004L, 0x00000200L, 0x01000000L,
0x00004204L, 0x01004000L, 0x01004004L, 0x00000204L,
0x00004000L, 0x00000200L, 0x01000000L, 0x01004004L,
0x01000204L, 0x00004204L, 0x00004200L, 0x00000000L,
0x00000200L, 0x01000004L, 0x00000004L, 0x01000200L,
0x00000000L, 0x01000204L, 0x01000200L, 0x00004200L,
0x00000204L, 0x00004000L, 0x01004204L, 0x01000000L,
0x01004200L, 0x00000004L, 0x00004004L, 0x01004204L,
0x01000004L, 0x01004200L, 0x01004000L, 0x00004004L,
},{
/* nibble 7 */
0x20800080L, 0x20820000L, 0x00020080L, 0x00000000L,
0x20020000L, 0x00800080L, 0x20800000L, 0x20820080L,
0x00000080L, 0x20000000L, 0x00820000L, 0x00020080L,
0x00820080L, 0x20020080L, 0x20000080L, 0x20800000L,
0x00020000L, 0x00820080L, 0x00800080L, 0x20020000L,
0x20820080L, 0x20000080L, 0x00000000L, 0x00820000L,
0x20000000L, 0x00800000L, 0x20020080L, 0x20800080L,
0x00800000L, 0x00020000L, 0x20820000L, 0x00000080L,
0x00800000L, 0x00020000L, 0x20000080L, 0x20820080L,
0x00020080L, 0x20000000L, 0x00000000L, 0x00820000L,
0x20800080L, 0x20020080L, 0x20020000L, 0x00800080L,
0x20820000L, 0x00000080L, 0x00800080L, 0x20020000L,
0x20820080L, 0x00800000L, 0x20800000L, 0x20000080L,
0x00820000L, 0x00020080L, 0x20020080L, 0x20800000L,
0x00000080L, 0x20820000L, 0x00820080L, 0x00000000L,
0x20000000L, 0x20800080L, 0x00020000L, 0x00820080L,
}};


#define LOAD_DATA_tmp(a,b,c,d,e,f) LOAD_DATA(a,b,c,d,e,f,g)
#define LOAD_DATA(R,S,u,t,E0,E1,tmp) \
	u=R^s[S  ]; \
	t=R^s[S+1]

#define D_ENCRYPT(LL,R,S) {\
	LOAD_DATA_tmp(R,S,u,t,E0,E1); \
	t=ROTATE(t,4); \
	LL^=\
		DES_SPtrans[0][(u>> 2L)&0x3f]^ \
		DES_SPtrans[2][(u>>10L)&0x3f]^ \
		DES_SPtrans[4][(u>>18L)&0x3f]^ \
		DES_SPtrans[6][(u>>26L)&0x3f]^ \
		DES_SPtrans[1][(t>> 2L)&0x3f]^ \
		DES_SPtrans[3][(t>>10L)&0x3f]^ \
		DES_SPtrans[5][(t>>18L)&0x3f]^ \
		DES_SPtrans[7][(t>>26L)&0x3f]; }

void usage(void);
void doencryption(void);
int uufwrite(unsigned char *data, int size, unsigned int num, FILE *fp);
void uufwriteEnd(FILE *fp);
int uufread(unsigned char *out,int size,unsigned int num,FILE *fp);
int uuencode(unsigned char *in,int num,unsigned char *out);
int uudecode(unsigned char *in,int num,unsigned char *out);
void DES_3cbc_encrypt(DES_cblock *input,DES_cblock *output,long length,
	DES_key_schedule sk1,DES_key_schedule sk2,
	DES_cblock *ivec1,DES_cblock *ivec2,int enc);
#ifdef OPENSSL_SYS_VMS
#define EXIT(a) exit(a&0x10000000L)
#else
#define EXIT(a) exit(a)
#endif

#define BUFSIZE (245*64)
#define VERIFY  1
#define KEYSIZ	8
#define KEYSIZB 1024 /* should hit tty line limit first :-) */
char key[KEYSIZB+1];
int do_encrypt,longk=0;
FILE *DES_IN,*DES_OUT,*CKSUM_OUT;
char uuname[200];
unsigned char uubuf[50];
int uubufnum=0;
#define INUUBUFN	(45*100)
#define OUTUUBUF	(65*100)
unsigned char b[OUTUUBUF];
unsigned char bb[300];
DES_cblock cksum={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
char cksumname[200]="";

int vflag,cflag,eflag,dflag,kflag,bflag,fflag,sflag,uflag,flag3,hflag,error;

unsigned char cleanse_ctr = 0;
void OPENSSL_cleanse(void *ptr, size_t len)
{
    unsigned char *p = ptr;
    size_t loop = len;
    while(loop--)
        {
        *(p++) = cleanse_ctr;
        cleanse_ctr += (17 + (unsigned char)((int)p & 0xF));
        }
    if(memchr(ptr, cleanse_ctr, len))
        cleanse_ctr += 63;
}

void DES_encrypt1(DES_LONG *data, DES_key_schedule *ks, int enc)
	{
	register DES_LONG l,r,t,u;
#ifdef DES_PTR
	register const unsigned char *des_SP=(const unsigned char *)DES_SPtrans;
#endif
#ifndef DES_UNROLL
	register int i;
#endif
	register DES_LONG *s;

	r=data[0];
	l=data[1];

	IP(r,l);
	/* Things have been modified so that the initial rotate is
	 * done outside the loop.  This required the
	 * DES_SPtrans values in sp.h to be rotated 1 bit to the right.
	 * One perl script later and things have a 5% speed up on a sparc2.
	 * Thanks to Richard Outerbridge <71755.204@CompuServe.COM>
	 * for pointing this out. */
	/* clear the top bits on machines with 8byte longs */
	/* shift left by 2 */
	r=ROTATE(r,29)&0xffffffffL;
	l=ROTATE(l,29)&0xffffffffL;

	s=ks->ks->deslong;
	/* I don't know if it is worth the effort of loop unrolling the
	 * inner loop */
	if (enc)
		{
#ifdef DES_UNROLL
		D_ENCRYPT(l,r, 0); /*  1 */
		D_ENCRYPT(r,l, 2); /*  2 */
		D_ENCRYPT(l,r, 4); /*  3 */
		D_ENCRYPT(r,l, 6); /*  4 */
		D_ENCRYPT(l,r, 8); /*  5 */
		D_ENCRYPT(r,l,10); /*  6 */
		D_ENCRYPT(l,r,12); /*  7 */
		D_ENCRYPT(r,l,14); /*  8 */
		D_ENCRYPT(l,r,16); /*  9 */
		D_ENCRYPT(r,l,18); /*  10 */
		D_ENCRYPT(l,r,20); /*  11 */
		D_ENCRYPT(r,l,22); /*  12 */
		D_ENCRYPT(l,r,24); /*  13 */
		D_ENCRYPT(r,l,26); /*  14 */
		D_ENCRYPT(l,r,28); /*  15 */
		D_ENCRYPT(r,l,30); /*  16 */
#else
		for (i=0; i<32; i+=8)
			{
			D_ENCRYPT(l,r,i+0); /*  1 */
			D_ENCRYPT(r,l,i+2); /*  2 */
			D_ENCRYPT(l,r,i+4); /*  3 */
			D_ENCRYPT(r,l,i+6); /*  4 */
			}
#endif
		}
	else
		{
#ifdef DES_UNROLL
		D_ENCRYPT(l,r,30); /* 16 */
		D_ENCRYPT(r,l,28); /* 15 */
		D_ENCRYPT(l,r,26); /* 14 */
		D_ENCRYPT(r,l,24); /* 13 */
		D_ENCRYPT(l,r,22); /* 12 */
		D_ENCRYPT(r,l,20); /* 11 */
		D_ENCRYPT(l,r,18); /* 10 */
		D_ENCRYPT(r,l,16); /*  9 */
		D_ENCRYPT(l,r,14); /*  8 */
		D_ENCRYPT(r,l,12); /*  7 */
		D_ENCRYPT(l,r,10); /*  6 */
		D_ENCRYPT(r,l, 8); /*  5 */
		D_ENCRYPT(l,r, 6); /*  4 */
		D_ENCRYPT(r,l, 4); /*  3 */
		D_ENCRYPT(l,r, 2); /*  2 */
		D_ENCRYPT(r,l, 0); /*  1 */
#else
		for (i=30; i>0; i-=8)
			{
			D_ENCRYPT(l,r,i-0); /* 16 */
			D_ENCRYPT(r,l,i-2); /* 15 */
			D_ENCRYPT(l,r,i-4); /* 14 */
			D_ENCRYPT(r,l,i-6); /* 13 */
			}
#endif
		}

	/* rotate and clear the top bits on machines with 8byte longs */
	l=ROTATE(l,3)&0xffffffffL;
	r=ROTATE(r,3)&0xffffffffL;

	FP(r,l);
	data[0]=l;
	data[1]=r;
	l=r=t=u=0;
	}

DES_LONG DES_cbc_cksum(const unsigned char *in, DES_cblock *output,
		       long length, DES_key_schedule *schedule,
		       const_DES_cblock *ivec)
	{
	register DES_LONG tout0,tout1,tin0,tin1;
	register long l=length;
	DES_LONG tin[2];
	unsigned char *out = &(*output)[0];
	const unsigned char *iv = &(*ivec)[0];

	c2l(iv,tout0);
	c2l(iv,tout1);
	for (; l>0; l-=8)
		{
		if (l >= 8)
			{
			c2l(in,tin0);
			c2l(in,tin1);
			}
		else
			c2ln(in,tin0,tin1,l);
			
		tin0^=tout0; tin[0]=tin0;
		tin1^=tout1; tin[1]=tin1;
		DES_encrypt1((DES_LONG *)tin,schedule,DES_ENCRYPT);
		/* fix 15/10/91 eay - thanks to keithr@sco.COM */
		tout0=tin[0];
		tout1=tin[1];
		}
	if (out != NULL)
		{
		l2c(tout0,out);
		l2c(tout1,out);
		}
	tout0=tin0=tin1=tin[0]=tin[1]=0;
	/*
	  Transform the data in tout1 so that it will
	  match the return value that the MIT Kerberos
	  mit_des_cbc_cksum API returns.
	*/
	tout1 = ((tout1 >> 24L) & 0x000000FF)
	      | ((tout1 >> 8L)  & 0x0000FF00)
	      | ((tout1 << 8L)  & 0x00FF0000)
	      | ((tout1 << 24L) & 0xFF000000);
	return(tout1);
	}


#define NUM_WEAK_KEY	16
static DES_cblock weak_keys[NUM_WEAK_KEY]={
	/* weak keys */
	{0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},
	{0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE},
	{0x1F,0x1F,0x1F,0x1F,0x0E,0x0E,0x0E,0x0E},
	{0xE0,0xE0,0xE0,0xE0,0xF1,0xF1,0xF1,0xF1},
	/* semi-weak keys */
	{0x01,0xFE,0x01,0xFE,0x01,0xFE,0x01,0xFE},
	{0xFE,0x01,0xFE,0x01,0xFE,0x01,0xFE,0x01},
	{0x1F,0xE0,0x1F,0xE0,0x0E,0xF1,0x0E,0xF1},
	{0xE0,0x1F,0xE0,0x1F,0xF1,0x0E,0xF1,0x0E},
	{0x01,0xE0,0x01,0xE0,0x01,0xF1,0x01,0xF1},
	{0xE0,0x01,0xE0,0x01,0xF1,0x01,0xF1,0x01},
	{0x1F,0xFE,0x1F,0xFE,0x0E,0xFE,0x0E,0xFE},
	{0xFE,0x1F,0xFE,0x1F,0xFE,0x0E,0xFE,0x0E},
	{0x01,0x1F,0x01,0x1F,0x01,0x0E,0x01,0x0E},
	{0x1F,0x01,0x1F,0x01,0x0E,0x01,0x0E,0x01},
	{0xE0,0xFE,0xE0,0xFE,0xF1,0xFE,0xF1,0xFE},
	{0xFE,0xE0,0xFE,0xE0,0xFE,0xF1,0xFE,0xF1}};

int DES_is_weak_key(const_DES_cblock *key)
	{
	int i;

	for (i=0; i<NUM_WEAK_KEY; i++)
		/* Added == 0 to comparison, I obviously don't run
		 * this section very often :-(, thanks to
		 * engineering@MorningStar.Com for the fix
		 * eay 93/06/29
		 * Another problem, I was comparing only the first 4
		 * bytes, 97/03/18 */
		if (memcmp(weak_keys[i],key,sizeof(DES_cblock)) == 0) return(1);
	return(0);
	}

/* NOW DEFINED IN des_local.h
 * See ecb_encrypt.c for a pseudo description of these macros. 
 * #define PERM_OP(a,b,t,n,m) ((t)=((((a)>>(n))^(b))&(m)),\
 * 	(b)^=(t),\
 * 	(a)=((a)^((t)<<(n))))
 */



static const DES_LONG des_skb[8][64]={
	{
	/* for C bits (numbered as per FIPS 46) 1 2 3 4 5 6 */
	0x00000000L,0x00000010L,0x20000000L,0x20000010L,
	0x00010000L,0x00010010L,0x20010000L,0x20010010L,
	0x00000800L,0x00000810L,0x20000800L,0x20000810L,
	0x00010800L,0x00010810L,0x20010800L,0x20010810L,
	0x00000020L,0x00000030L,0x20000020L,0x20000030L,
	0x00010020L,0x00010030L,0x20010020L,0x20010030L,
	0x00000820L,0x00000830L,0x20000820L,0x20000830L,
	0x00010820L,0x00010830L,0x20010820L,0x20010830L,
	0x00080000L,0x00080010L,0x20080000L,0x20080010L,
	0x00090000L,0x00090010L,0x20090000L,0x20090010L,
	0x00080800L,0x00080810L,0x20080800L,0x20080810L,
	0x00090800L,0x00090810L,0x20090800L,0x20090810L,
	0x00080020L,0x00080030L,0x20080020L,0x20080030L,
	0x00090020L,0x00090030L,0x20090020L,0x20090030L,
	0x00080820L,0x00080830L,0x20080820L,0x20080830L,
	0x00090820L,0x00090830L,0x20090820L,0x20090830L,
	},{
	/* for C bits (numbered as per FIPS 46) 7 8 10 11 12 13 */
	0x00000000L,0x02000000L,0x00002000L,0x02002000L,
	0x00200000L,0x02200000L,0x00202000L,0x02202000L,
	0x00000004L,0x02000004L,0x00002004L,0x02002004L,
	0x00200004L,0x02200004L,0x00202004L,0x02202004L,
	0x00000400L,0x02000400L,0x00002400L,0x02002400L,
	0x00200400L,0x02200400L,0x00202400L,0x02202400L,
	0x00000404L,0x02000404L,0x00002404L,0x02002404L,
	0x00200404L,0x02200404L,0x00202404L,0x02202404L,
	0x10000000L,0x12000000L,0x10002000L,0x12002000L,
	0x10200000L,0x12200000L,0x10202000L,0x12202000L,
	0x10000004L,0x12000004L,0x10002004L,0x12002004L,
	0x10200004L,0x12200004L,0x10202004L,0x12202004L,
	0x10000400L,0x12000400L,0x10002400L,0x12002400L,
	0x10200400L,0x12200400L,0x10202400L,0x12202400L,
	0x10000404L,0x12000404L,0x10002404L,0x12002404L,
	0x10200404L,0x12200404L,0x10202404L,0x12202404L,
	},{
	/* for C bits (numbered as per FIPS 46) 14 15 16 17 19 20 */
	0x00000000L,0x00000001L,0x00040000L,0x00040001L,
	0x01000000L,0x01000001L,0x01040000L,0x01040001L,
	0x00000002L,0x00000003L,0x00040002L,0x00040003L,
	0x01000002L,0x01000003L,0x01040002L,0x01040003L,
	0x00000200L,0x00000201L,0x00040200L,0x00040201L,
	0x01000200L,0x01000201L,0x01040200L,0x01040201L,
	0x00000202L,0x00000203L,0x00040202L,0x00040203L,
	0x01000202L,0x01000203L,0x01040202L,0x01040203L,
	0x08000000L,0x08000001L,0x08040000L,0x08040001L,
	0x09000000L,0x09000001L,0x09040000L,0x09040001L,
	0x08000002L,0x08000003L,0x08040002L,0x08040003L,
	0x09000002L,0x09000003L,0x09040002L,0x09040003L,
	0x08000200L,0x08000201L,0x08040200L,0x08040201L,
	0x09000200L,0x09000201L,0x09040200L,0x09040201L,
	0x08000202L,0x08000203L,0x08040202L,0x08040203L,
	0x09000202L,0x09000203L,0x09040202L,0x09040203L,
	},{
	/* for C bits (numbered as per FIPS 46) 21 23 24 26 27 28 */
	0x00000000L,0x00100000L,0x00000100L,0x00100100L,
	0x00000008L,0x00100008L,0x00000108L,0x00100108L,
	0x00001000L,0x00101000L,0x00001100L,0x00101100L,
	0x00001008L,0x00101008L,0x00001108L,0x00101108L,
	0x04000000L,0x04100000L,0x04000100L,0x04100100L,
	0x04000008L,0x04100008L,0x04000108L,0x04100108L,
	0x04001000L,0x04101000L,0x04001100L,0x04101100L,
	0x04001008L,0x04101008L,0x04001108L,0x04101108L,
	0x00020000L,0x00120000L,0x00020100L,0x00120100L,
	0x00020008L,0x00120008L,0x00020108L,0x00120108L,
	0x00021000L,0x00121000L,0x00021100L,0x00121100L,
	0x00021008L,0x00121008L,0x00021108L,0x00121108L,
	0x04020000L,0x04120000L,0x04020100L,0x04120100L,
	0x04020008L,0x04120008L,0x04020108L,0x04120108L,
	0x04021000L,0x04121000L,0x04021100L,0x04121100L,
	0x04021008L,0x04121008L,0x04021108L,0x04121108L,
	},{
	/* for D bits (numbered as per FIPS 46) 1 2 3 4 5 6 */
	0x00000000L,0x10000000L,0x00010000L,0x10010000L,
	0x00000004L,0x10000004L,0x00010004L,0x10010004L,
	0x20000000L,0x30000000L,0x20010000L,0x30010000L,
	0x20000004L,0x30000004L,0x20010004L,0x30010004L,
	0x00100000L,0x10100000L,0x00110000L,0x10110000L,
	0x00100004L,0x10100004L,0x00110004L,0x10110004L,
	0x20100000L,0x30100000L,0x20110000L,0x30110000L,
	0x20100004L,0x30100004L,0x20110004L,0x30110004L,
	0x00001000L,0x10001000L,0x00011000L,0x10011000L,
	0x00001004L,0x10001004L,0x00011004L,0x10011004L,
	0x20001000L,0x30001000L,0x20011000L,0x30011000L,
	0x20001004L,0x30001004L,0x20011004L,0x30011004L,
	0x00101000L,0x10101000L,0x00111000L,0x10111000L,
	0x00101004L,0x10101004L,0x00111004L,0x10111004L,
	0x20101000L,0x30101000L,0x20111000L,0x30111000L,
	0x20101004L,0x30101004L,0x20111004L,0x30111004L,
	},{
	/* for D bits (numbered as per FIPS 46) 8 9 11 12 13 14 */
	0x00000000L,0x08000000L,0x00000008L,0x08000008L,
	0x00000400L,0x08000400L,0x00000408L,0x08000408L,
	0x00020000L,0x08020000L,0x00020008L,0x08020008L,
	0x00020400L,0x08020400L,0x00020408L,0x08020408L,
	0x00000001L,0x08000001L,0x00000009L,0x08000009L,
	0x00000401L,0x08000401L,0x00000409L,0x08000409L,
	0x00020001L,0x08020001L,0x00020009L,0x08020009L,
	0x00020401L,0x08020401L,0x00020409L,0x08020409L,
	0x02000000L,0x0A000000L,0x02000008L,0x0A000008L,
	0x02000400L,0x0A000400L,0x02000408L,0x0A000408L,
	0x02020000L,0x0A020000L,0x02020008L,0x0A020008L,
	0x02020400L,0x0A020400L,0x02020408L,0x0A020408L,
	0x02000001L,0x0A000001L,0x02000009L,0x0A000009L,
	0x02000401L,0x0A000401L,0x02000409L,0x0A000409L,
	0x02020001L,0x0A020001L,0x02020009L,0x0A020009L,
	0x02020401L,0x0A020401L,0x02020409L,0x0A020409L,
	},{
	/* for D bits (numbered as per FIPS 46) 16 17 18 19 20 21 */
	0x00000000L,0x00000100L,0x00080000L,0x00080100L,
	0x01000000L,0x01000100L,0x01080000L,0x01080100L,
	0x00000010L,0x00000110L,0x00080010L,0x00080110L,
	0x01000010L,0x01000110L,0x01080010L,0x01080110L,
	0x00200000L,0x00200100L,0x00280000L,0x00280100L,
	0x01200000L,0x01200100L,0x01280000L,0x01280100L,
	0x00200010L,0x00200110L,0x00280010L,0x00280110L,
	0x01200010L,0x01200110L,0x01280010L,0x01280110L,
	0x00000200L,0x00000300L,0x00080200L,0x00080300L,
	0x01000200L,0x01000300L,0x01080200L,0x01080300L,
	0x00000210L,0x00000310L,0x00080210L,0x00080310L,
	0x01000210L,0x01000310L,0x01080210L,0x01080310L,
	0x00200200L,0x00200300L,0x00280200L,0x00280300L,
	0x01200200L,0x01200300L,0x01280200L,0x01280300L,
	0x00200210L,0x00200310L,0x00280210L,0x00280310L,
	0x01200210L,0x01200310L,0x01280210L,0x01280310L,
	},{
	/* for D bits (numbered as per FIPS 46) 22 23 24 25 27 28 */
	0x00000000L,0x04000000L,0x00040000L,0x04040000L,
	0x00000002L,0x04000002L,0x00040002L,0x04040002L,
	0x00002000L,0x04002000L,0x00042000L,0x04042000L,
	0x00002002L,0x04002002L,0x00042002L,0x04042002L,
	0x00000020L,0x04000020L,0x00040020L,0x04040020L,
	0x00000022L,0x04000022L,0x00040022L,0x04040022L,
	0x00002020L,0x04002020L,0x00042020L,0x04042020L,
	0x00002022L,0x04002022L,0x00042022L,0x04042022L,
	0x00000800L,0x04000800L,0x00040800L,0x04040800L,
	0x00000802L,0x04000802L,0x00040802L,0x04040802L,
	0x00002800L,0x04002800L,0x00042800L,0x04042800L,
	0x00002802L,0x04002802L,0x00042802L,0x04042802L,
	0x00000820L,0x04000820L,0x00040820L,0x04040820L,
	0x00000822L,0x04000822L,0x00040822L,0x04040822L,
	0x00002820L,0x04002820L,0x00042820L,0x04042820L,
	0x00002822L,0x04002822L,0x00042822L,0x04042822L,
	}};




void DES_set_key_unchecked(const_DES_cblock *key, DES_key_schedule *schedule)
	{
	static int shifts2[16]={0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0};
	register DES_LONG c,d,t,s,t2;
	register const unsigned char *in;
	register DES_LONG *k;
	register int i;

#ifdef OPENBSD_DEV_CRYPTO
	memcpy(schedule->key,key,sizeof schedule->key);
	schedule->session=NULL;
#endif
	k = &schedule->ks->deslong[0];
	in = &(*key)[0];

	c2l(in,c);
	c2l(in,d);

	/* do PC1 in 47 simple operations :-)
	 * Thanks to John Fletcher (john_fletcher@lccmail.ocf.llnl.gov)
	 * for the inspiration. :-) */
	PERM_OP (d,c,t,4,0x0f0f0f0fL);
	HPERM_OP(c,t,-2,0xcccc0000L);
	HPERM_OP(d,t,-2,0xcccc0000L);
	PERM_OP (d,c,t,1,0x55555555L);
	PERM_OP (c,d,t,8,0x00ff00ffL);
	PERM_OP (d,c,t,1,0x55555555L);
	d=	(((d&0x000000ffL)<<16L)| (d&0x0000ff00L)     |
		 ((d&0x00ff0000L)>>16L)|((c&0xf0000000L)>>4L));
	c&=0x0fffffffL;

	for (i=0; i<ITERATIONS; i++)
		{
		if (shifts2[i])
			{ c=((c>>2L)|(c<<26L)); d=((d>>2L)|(d<<26L)); }
		else
			{ c=((c>>1L)|(c<<27L)); d=((d>>1L)|(d<<27L)); }
		c&=0x0fffffffL;
		d&=0x0fffffffL;
		/* could be a few less shifts but I am to lazy at this
		 * point in time to investigate */
		s=	des_skb[0][ (c    )&0x3f                ]|
			des_skb[1][((c>> 6L)&0x03)|((c>> 7L)&0x3c)]|
			des_skb[2][((c>>13L)&0x0f)|((c>>14L)&0x30)]|
			des_skb[3][((c>>20L)&0x01)|((c>>21L)&0x06) |
						  ((c>>22L)&0x38)];
		t=	des_skb[4][ (d    )&0x3f                ]|
			des_skb[5][((d>> 7L)&0x03)|((d>> 8L)&0x3c)]|
			des_skb[6][ (d>>15L)&0x3f                ]|
			des_skb[7][((d>>21L)&0x0f)|((d>>22L)&0x30)];

		/* table contained 0213 4657 */
		t2=((t<<16L)|(s&0x0000ffffL))&0xffffffffL;
		*(k++)=ROTATE(t2,30)&0xffffffffL;

		t2=((s>>16L)|(t&0xffff0000L));
		*(k++)=ROTATE(t2,26)&0xffffffffL;
		}
	}

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

int DES_check_key_parity(const_DES_cblock *key)
	{
	int i;

	for (i=0; i<DES_KEY_SZ; i++)
		{
		if ((*key)[i] != odd_parity[(*key)[i]])
			return(0);
		}
	return(1);
	}
/* return 0 if key parity is odd (correct),
 * return -1 if key parity error,
 * return -2 if illegal weak key.
 */
int DES_set_key_checked(const_DES_cblock *key, DES_key_schedule *schedule)
	{
	if (!DES_check_key_parity(key))
		return(-1);
	if (DES_is_weak_key(key))
		return(-2);
	DES_set_key_unchecked(key, schedule);
	return 0;
	}

int DES_set_key(const_DES_cblock *key, DES_key_schedule *schedule)
{

	DES_set_key_unchecked(key, schedule);
	return 0;
}



void DES_set_odd_parity(DES_cblock *key)
{
	int i;

	for (i=0; i<DES_KEY_SZ; i++)
		(*key)[i]=odd_parity[(*key)[i]];
}

void DES_string_to_2keys(const char *str, DES_cblock *key1, DES_cblock *key2)
	{
	DES_key_schedule ks;
	int i,length;
	register unsigned char j;

	// memset(key1,0,8);
	// memset(key2,0,8);
	length=strlen(str);
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

#ifdef EXPERIMENTAL_STR_TO_STRONG_KEY
	if(DES_is_weak_key(key1))
	    (*key1)[7] ^= 0xF0;
	DES_set_key(key1,&ks);
#else
	DES_set_key_unchecked(key1,&ks);
#endif

	DES_cbc_cksum((const unsigned char*)str,key1,length,&ks,key1);

#ifdef EXPERIMENTAL_STR_TO_STRONG_KEY
	if(DES_is_weak_key(key2))
	    (*key2)[7] ^= 0xF0;
	DES_set_key(key2,&ks);
#else
	DES_set_key_unchecked(key2,&ks);
#endif

	DES_cbc_cksum((const unsigned char*)str,key2,length,&ks,key2);
	OPENSSL_cleanse(&ks,sizeof(ks));
	DES_set_odd_parity(key1);
	DES_set_odd_parity(key2);
}


void DES_string_to_key(const char *str, DES_cblock *key)
{
	DES_key_schedule ks;
	int i,length;
	register unsigned char j;

	memset(key,0,8);
	length=strlen(str);
#ifdef OLD_STR_TO_KEY
	for (i=0; i<length; i++)
		(*key)[i%8]^=(str[i]<<1);
#else /* MIT COMPATIBLE */
	for (i=0; i<length; i++)
	{
		j=str[i];
		if ((i%16) < 8)
			(*key)[i%8]^=(j<<1);
		else
		{
			/* Reverse the bit order 05/05/92 eay */
			j=((j<<4)&0xf0)|((j>>4)&0x0f);
			j=((j<<2)&0xcc)|((j>>2)&0x33);
			j=((j<<1)&0xaa)|((j>>1)&0x55);
			(*key)[7-(i%8)]^=j;
		}
	}
#endif
	DES_set_odd_parity(key);
#ifdef EXPERIMENTAL_STR_TO_STRONG_KEY
	if(DES_is_weak_key(key))
		(*key)[7] ^= 0xF0;
	DES_set_key(key,&ks);
#else
	DES_set_key_unchecked(key,&ks);
#endif
	DES_cbc_cksum((const unsigned char*)str,key,length,&ks,key);
	OPENSSL_cleanse(&ks,sizeof(ks));
	DES_set_odd_parity(key);
}

void doencryption(void) __attribute__((annotate("specuAnaly")))
{
#ifdef _LIBC
	extern unsigned long time();
#endif

	register int i;
	DES_key_schedule ks,ks2;
	DES_cblock iv,iv2;
	char *p;
	int num=0,j,k,l,rem,ll,len,last,ex=0;
	DES_cblock kk,k2;
    int y;
    klee_make_symbolic(&key, sizeof(key), "key");
    klee_make_symbolic(&kk, sizeof(kk), "kk");
    klee_make_symbolic(&k2, sizeof(k2), "k2");
    klee_make_symbolic(&y, sizeof(y), "y");


	FILE *O;
	int Exit=0;
#ifndef OPENSSL_SYS_MSDOS
	static unsigned char buf[BUFSIZE+8],obuf[BUFSIZE+8];
#else
	static unsigned char *buf=NULL,*obuf=NULL;

    //klee_make_symbolic(&ks, sizeof(ks), "ks");
    //klee_make_symbolic(&ks2, sizeof(ks2), "ks2");
    //klee_make_symbolic(&iv, sizeof(iv), "iv");
    //klee_make_symbolic(&iv2, sizeof(iv2), "iv2");
    //klee_make_symbolic(&kk, sizeof(kk), "kk");
    //klee_make_symbolic(&k2, sizeof(k2), "k2");
    //klee_make_symbolic(&O, sizeof(O), "O");
    //klee_make_symbolic(&hflag, sizeof(hflag), "hflag");


	if (buf == NULL)
	{
		if (    (( buf=OPENSSL_malloc(BUFSIZE+8)) == NULL) ||
			((obuf=OPENSSL_malloc(BUFSIZE+8)) == NULL))
		{
			fputs("Not enough memory\n",stderr);
			Exit=10;
			return;
		}
	}
#endif

    victim_fun2(y);
	if (hflag)
	{
		j=(flag3?16:8);
		p=key;
		for (i=0; i<j; i++)
		{
			k=0;
			if ((*p <= '9') && (*p >= '0'))
				k=(*p-'0')<<4;
			else if ((*p <= 'f') && (*p >= 'a'))
				k=(*p-'a'+10)<<4;
			else if ((*p <= 'F') && (*p >= 'A'))
				k=(*p-'A'+10)<<4;
			else
			{
				fputs("Bad hex key\n",stderr);
				Exit=9;
				return;
			}
			p++;
			if ((*p <= '9') && (*p >= '0'))
				k|=(*p-'0');
			else if ((*p <= 'f') && (*p >= 'a'))
				k|=(*p-'a'+10);
			else if ((*p <= 'F') && (*p >= 'A'))
				k|=(*p-'A'+10);
			else
			{
				fputs("Bad hex key\n",stderr);
				Exit=9;
				return;
			}
			p++;
			if (i < 8)
				kk[i]=k;
			else
				k2[i-8]=k;
		}
		DES_set_key_unchecked(&k2,&ks2);
		OPENSSL_cleanse(k2,sizeof(k2));
	}
	else if (longk || flag3)
	{
		if (flag3)
		{
			DES_string_to_2keys(key,&kk,&k2);
			DES_set_key_unchecked(&k2,&ks2);
			OPENSSL_cleanse(k2,sizeof(k2));
		}
		else
			DES_string_to_key(key,&kk);
	}
	else
		for (i=0; i<KEYSIZ; i++)
		{
			l=0;
			k=key[i];
			for (j=0; j<8; j++)
			{
				if (k&1) l++;
				k>>=1;
			}
			if (l & 1)
				kk[i]=key[i]&0x7f;
			else
				kk[i]=key[i]|0x80;
		}

	// DES_set_key_unchecked(&kk,&ks);
	// OPENSSL_cleanse(key,sizeof(key));
	// OPENSSL_cleanse(kk,sizeof(kk));
	// /* woops - A bug that does not showup under unix :-( */
	// memset(iv,0,sizeof(iv));
	// memset(iv2,0,sizeof(iv2));

	// l=1;
	// rem=0;
	// /* first read */
	// if (eflag || (!dflag && cflag))
	// {
	// 	for (;;)
	// 	{
	// 		num=l=fread(&(buf[rem]),1,BUFSIZE,DES_IN);
	// 		l+=rem;
	// 		num+=rem;
	// 		if (l < 0)
	// 		{
	// 			perror("read error");
	// 			Exit=6;
	// 			goto problems;
	// 		}

	// 		rem=l%8;
	// 		len=l-rem;
	// 		if (feof(DES_IN))
	// 		{
	// 			for (i=7-rem; i>0; i--)
	// 				RAND_pseudo_bytes(buf + l++, 1);
	// 			buf[l++]=rem;
	// 			ex=1;
	// 			len+=rem;
	// 		}
	// 		else
	// 			l-=rem;

	// 		if (cflag)
	// 		{
	// 			DES_cbc_cksum(buf,&cksum,
	// 				(long)len,&ks,&cksum);
	// 			if (!eflag)
	// 			{
	// 				if (feof(DES_IN)) break;
	// 				else continue;
	// 			}
	// 		}

	// 		if (bflag && !flag3)
	// 			for (i=0; i<l; i+=8)
	// 				DES_ecb_encrypt(
	// 					(DES_cblock *)&(buf[i]),
	// 					(DES_cblock *)&(obuf[i]),
	// 					&ks,do_encrypt);
	// 			else if (flag3 && bflag)
	// 				for (i=0; i<l; i+=8)
	// 					DES_ecb2_encrypt(
	// 						(DES_cblock *)&(buf[i]),
	// 						(DES_cblock *)&(obuf[i]),
	// 						&ks,&ks2,do_encrypt);
	// 				else if (flag3 && !bflag)
	// 				{
	// 					char tmpbuf[8];

	// 					if (rem) memcpy(tmpbuf,&(buf[l]),
	// 						(unsigned int)rem);
	// 						DES_3cbc_encrypt(
	// 							(DES_cblock *)buf,(DES_cblock *)obuf,
	// 							(long)l,ks,ks2,&iv,
	// 							&iv2,do_encrypt);
	// 					if (rem) memcpy(&(buf[l]),tmpbuf,
	// 						(unsigned int)rem);
	// 				}
	// 			else
	// 			{
	// 				DES_cbc_encrypt(
	// 					buf,obuf,
	// 					(long)l,&ks,&iv,do_encrypt);
	// 				if (l >= 8) memcpy(iv,&(obuf[l-8]),8);
	// 			}
	// 			if (rem) memcpy(buf,&(buf[l]),(unsigned int)rem);

	// 			i=0;
	// 			while (i < l)
	// 			{
	// 				if (uflag)
	// 					j=uufwrite(obuf,1,(unsigned int)l-i,
	// 						DES_OUT);
	// 				else
	// 					j=fwrite(obuf,1,(unsigned int)l-i,
	// 						DES_OUT);
	// 				if (j == -1)
	// 				{
	// 					perror("Write error");
	// 					Exit=7;
	// 					goto problems;
	// 				}
	// 				i+=j;
	// 			}
	// 			if (feof(DES_IN))
	// 			{
	// 				if (uflag) uufwriteEnd(DES_OUT);
	// 				break;
	// 			}
	// 	}
	// }
	// else /* decrypt */
	// {
	// 	ex=1;
	// 	for (;;)
	// 	{
	// 		if (ex) {
	// 			if (uflag)
	// 				l=uufread(buf,1,BUFSIZE,DES_IN);
	// 			else
	// 				l=fread(buf,1,BUFSIZE,DES_IN);
	// 			ex=0;
	// 			rem=l%8;
	// 			l-=rem;
	// 		}
	// 		if (l < 0)
	// 		{
	// 			perror("read error");
	// 			Exit=6;
	// 			goto problems;
	// 		}

	// 		if (bflag && !flag3)
	// 			for (i=0; i<l; i+=8)
	// 				DES_ecb_encrypt(
	// 					(DES_cblock *)&(buf[i]),
	// 					(DES_cblock *)&(obuf[i]),
	// 					&ks,do_encrypt);
	// 		else if (flag3 && bflag)
	// 			for (i=0; i<l; i+=8)
	// 				DES_ecb2_encrypt(
	// 					(DES_cblock *)&(buf[i]),
	// 					(DES_cblock *)&(obuf[i]),
	// 					&ks,&ks2,do_encrypt);
	// 		else if (flag3 && !bflag)
	// 		{
	// 			DES_3cbc_encrypt(
	// 				(DES_cblock *)buf,(DES_cblock *)obuf,
	// 				(long)l,ks,ks2,&iv,
	// 				&iv2,do_encrypt);
	// 		}
	// 		else
	// 		{
	// 			DES_cbc_encrypt(
	// 				buf,obuf,
	// 				(long)l,&ks,&iv,do_encrypt);
	// 			if (l >= 8) memcpy(iv,&(buf[l-8]),8);
	// 		}

	// 		if (uflag)
	// 			ll=uufread(&(buf[rem]),1,BUFSIZE,DES_IN);
	// 		else
	// 			ll=fread(&(buf[rem]),1,BUFSIZE,DES_IN);
	// 		ll+=rem;
	// 		rem=ll%8;
	// 		ll-=rem;
	// 		if (feof(DES_IN) && (ll == 0))
	// 		{
	// 			last=obuf[l-1];

	// 			if ((last > 7) || (last < 0))
	// 			{
	// 				fputs("The file was not decrypted correctly.\n",
	// 					stderr);
	// 				Exit=8;
	// 				last=0;
	// 			}
	// 			l=l-8+last;
	// 		}
	// 		i=0;
	// 		if (cflag) 
	// 			DES_cbc_cksum(obuf, (DES_cblock *)cksum,(long)l/8*8,&ks, (DES_cblock *)cksum);
	// 		while (i != l)
	// 		{
	// 			j=fwrite(obuf,1,(unsigned int)l-i,DES_OUT);
	// 			if (j == -1)
	// 			{
	// 				perror("Write error");
	// 				Exit=7;
	// 				goto problems;
	// 			}
	// 			i+=j;
	// 		}
	// 		l=ll;
	// 		if ((l == 0) && feof(DES_IN)) break;
	// 	}
	// }
	// if (cflag)
	// {
	// 	l=0;
	// 	if (cksumname[0] != '\0')
	// 	{
	// 		if ((O=fopen(cksumname,"w")) != NULL)
	// 		{
	// 			CKSUM_OUT=O;
	// 			l=1;
	// 		}
	// 	}
	// 	for (i=0; i<8; i++)
	// 		fprintf(CKSUM_OUT,"%02X",cksum[i]);
	// 	fprintf(CKSUM_OUT,"\n");
	// 	if (l) fclose(CKSUM_OUT);
	// }
	// problems:
	// OPENSSL_cleanse(buf,sizeof(buf));
	// OPENSSL_cleanse(obuf,sizeof(obuf));
	// OPENSSL_cleanse(&ks,sizeof(ks));
	// OPENSSL_cleanse(&ks2,sizeof(ks2));
	// OPENSSL_cleanse(iv,sizeof(iv));
	// OPENSSL_cleanse(iv2,sizeof(iv2));
	// OPENSSL_cleanse(kk,sizeof(kk));
	// OPENSSL_cleanse(k2,sizeof(k2));
	// OPENSSL_cleanse(uubuf,sizeof(uubuf));
	// OPENSSL_cleanse(b,sizeof(b));
	// OPENSSL_cleanse(bb,sizeof(bb));
	// OPENSSL_cleanse(cksum,sizeof(cksum));
	// if (Exit) EXIT(Exit);
}
int main() {
    int x;
    klee_make_symbolic(&x, sizeof(x), "x");
    victim_fun1(x);
    doencryption();
    victim_fun3(x);

    return 0;
}

