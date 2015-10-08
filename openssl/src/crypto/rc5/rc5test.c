/* crypto/rc5/rc5test.c */
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

/*
 * This has been a quickly hacked 'ideatest.c'.  When I add tests for other
 * RC5 modes, more of the code will be uncommented.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../e_os.h"

#ifdef OPENSSL_NO_RC5
int main(int argc, char *argv[])
{
    printf("No RC5 support\n");
    return (0);
}
#else
# include <openssl/rc5.h>

static unsigned char RC5key[5][16] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x91, 0x5f, 0x46, 0x19, 0xbe, 0x41, 0xb2, 0x51,
     0x63, 0x55, 0xa5, 0x01, 0x10, 0xa9, 0xce, 0x91},
    {0x78, 0x33, 0x48, 0xe7, 0x5a, 0xeb, 0x0f, 0x2f,
     0xd7, 0xb1, 0x69, 0xbb, 0x8d, 0xc1, 0x67, 0x87},
    {0xdc, 0x49, 0xdb, 0x13, 0x75, 0xa5, 0x58, 0x4f,
     0x64, 0x85, 0xb4, 0x13, 0xb5, 0xf1, 0x2b, 0xaf},
    {0x52, 0x69, 0xf1, 0x49, 0xd4, 0x1b, 0xa0, 0x15,
     0x24, 0x97, 0x57, 0x4d, 0x7f, 0x15, 0x31, 0x25},
};

static unsigned char RC5plain[5][8] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x21, 0xA5, 0xDB, 0xEE, 0x15, 0x4B, 0x8F, 0x6D},
    {0xF7, 0xC0, 0x13, 0xAC, 0x5B, 0x2B, 0x89, 0x52},
    {0x2F, 0x42, 0xB3, 0xB7, 0x03, 0x69, 0xFC, 0x92},
    {0x65, 0xC1, 0x78, 0xB2, 0x84, 0xD1, 0x97, 0xCC},
};

static unsigned char RC5cipher[5][8] = {
    {0x21, 0xA5, 0xDB, 0xEE, 0x15, 0x4B, 0x8F, 0x6D},
    {0xF7, 0xC0, 0x13, 0xAC, 0x5B, 0x2B, 0x89, 0x52},
    {0x2F, 0x42, 0xB3, 0xB7, 0x03, 0x69, 0xFC, 0x92},
    {0x65, 0xC1, 0x78, 0xB2, 0x84, 0xD1, 0x97, 0xCC},
    {0xEB, 0x44, 0xE4, 0x15, 0xDA, 0x31, 0x98, 0x24},
};

# define RC5_CBC_NUM 27
static unsigned char rc5_cbc_cipher[RC5_CBC_NUM][8] = {
    {0x7a, 0x7b, 0xba, 0x4d, 0x79, 0x11, 0x1d, 0x1e},
    {0x79, 0x7b, 0xba, 0x4d, 0x78, 0x11, 0x1d, 0x1e},
    {0x7a, 0x7b, 0xba, 0x4d, 0x79, 0x11, 0x1d, 0x1f},
    {0x7a, 0x7b, 0xba, 0x4d, 0x79, 0x11, 0x1d, 0x1f},
    {0x8b, 0x9d, 0xed, 0x91, 0xce, 0x77, 0x94, 0xa6},
    {0x2f, 0x75, 0x9f, 0xe7, 0xad, 0x86, 0xa3, 0x78},
    {0xdc, 0xa2, 0x69, 0x4b, 0xf4, 0x0e, 0x07, 0x88},
    {0xdc, 0xa2, 0x69, 0x4b, 0xf4, 0x0e, 0x07, 0x88},
    {0xdc, 0xfe, 0x09, 0x85, 0x77, 0xec, 0xa5, 0xff},
    {0x96, 0x46, 0xfb, 0x77, 0x63, 0x8f, 0x9c, 0xa8},
    {0xb2, 0xb3, 0x20, 0x9d, 0xb6, 0x59, 0x4d, 0xa4},
    {0x54, 0x5f, 0x7f, 0x32, 0xa5, 0xfc, 0x38, 0x36},
    {0x82, 0x85, 0xe7, 0xc1, 0xb5, 0xbc, 0x74, 0x02},
    {0xfc, 0x58, 0x6f, 0x92, 0xf7, 0x08, 0x09, 0x34},
    {0xcf, 0x27, 0x0e, 0xf9, 0x71, 0x7f, 0xf7, 0xc4},
    {0xe4, 0x93, 0xf1, 0xc1, 0xbb, 0x4d, 0x6e, 0x8c},
    {0x5c, 0x4c, 0x04, 0x1e, 0x0f, 0x21, 0x7a, 0xc3},
    {0x92, 0x1f, 0x12, 0x48, 0x53, 0x73, 0xb4, 0xf7},
    {0x5b, 0xa0, 0xca, 0x6b, 0xbe, 0x7f, 0x5f, 0xad},
    {0xc5, 0x33, 0x77, 0x1c, 0xd0, 0x11, 0x0e, 0x63},
    {0x29, 0x4d, 0xdb, 0x46, 0xb3, 0x27, 0x8d, 0x60},
    {0xda, 0xd6, 0xbd, 0xa9, 0xdf, 0xe8, 0xf7, 0xe8},
    {0x97, 0xe0, 0x78, 0x78, 0x37, 0xed, 0x31, 0x7f},
    {0x78, 0x75, 0xdb, 0xf6, 0x73, 0x8c, 0x64, 0x78},
    {0x8f, 0x34, 0xc3, 0xc6, 0x81, 0xc9, 0x96, 0x95},
    {0x7c, 0xb3, 0xf1, 0xdf, 0x34, 0xf9, 0x48, 0x11},
    {0x7f, 0xd1, 0xa0, 0x23, 0xa5, 0xbb, 0xa2, 0x17},
};

static unsigned char rc5_cbc_key[RC5_CBC_NUM][17] = {
    {1, 0x00},
    {1, 0x00},
    {1, 0x00},
    {1, 0x00},
    {1, 0x00},
    {1, 0x11},
    {1, 0x00},
    {4, 0x00, 0x00, 0x00, 0x00},
    {1, 0x00},
    {1, 0x00},
    {1, 0x00},
    {1, 0x00},
    {4, 0x01, 0x02, 0x03, 0x04},
    {4, 0x01, 0x02, 0x03, 0x04},
    {4, 0x01, 0x02, 0x03, 0x04},
    {8, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
    {8, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
    {8, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
    {8, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
    {16, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
     0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80},
    {16, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
     0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80},
    {16, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
     0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80},
    {5, 0x01, 0x02, 0x03, 0x04, 0x05},
    {5, 0x01, 0x02, 0x03, 0x04, 0x05},
    {5, 0x01, 0x02, 0x03, 0x04, 0x05},
    {5, 0x01, 0x02, 0x03, 0x04, 0x05},
    {5, 0x01, 0x02, 0x03, 0x04, 0x05},
};

static unsigned char rc5_cbc_plain[RC5_CBC_NUM][8] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01},
    {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80},
    {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80},
    {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80},
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80},
    {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80},
    {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80},
    {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80},
    {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80},
    {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80},
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x01},
};

static int rc5_cbc_rounds[RC5_CBC_NUM] = {
    0, 0, 0, 0, 0, 1, 2, 2,
    8, 8, 12, 16, 8, 12, 16, 12,
    8, 12, 16, 8, 12, 16, 12, 8,
    8, 8, 8,
};

static unsigned char rc5_cbc_iv[RC5_CBC_NUM][8] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
    {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
    {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
    {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
    {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
    {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
    {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
    {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x78, 0x75, 0xdb, 0xf6, 0x73, 0x8c, 0x64, 0x78},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x7c, 0xb3, 0xf1, 0xdf, 0x34, 0xf9, 0x48, 0x11},
};

int main(int argc, char *argv[])
{
    int i, n, err = 0;
    RC5_32_KEY key;
    unsigned char buf[8], buf2[8], ivb[8];

    for (n = 0; n < 5; n++) {
        RC5_32_set_key(&key, 16, &(RC5key[n][0]), 12);

        RC5_32_ecb_encrypt(&(RC5plain[n][0]), buf, &key, RC5_ENCRYPT);
        if (memcmp(&(RC5cipher[n][0]), buf, 8) != 0) {
            printf("ecb RC5 error encrypting (%d)\n", n + 1);
            printf("got     :");
            for (i = 0; i < 8; i++)
                printf("%02X ", buf[i]);
            printf("\n");
            printf("expected:");
            for (i = 0; i < 8; i++)
                printf("%02X ", RC5cipher[n][i]);
            err = 20;
            printf("\n");
        }

        RC5_32_ecb_encrypt(buf, buf2, &key, RC5_DECRYPT);
        if (memcmp(&(RC5plain[n][0]), buf2, 8) != 0) {
            printf("ecb RC5 error decrypting (%d)\n", n + 1);
            printf("got     :");
            for (i = 0; i < 8; i++)
                printf("%02X ", buf2[i]);
            printf("\n");
            printf("expected:");
            for (i = 0; i < 8; i++)
                printf("%02X ", RC5plain[n][i]);
            printf("\n");
            err = 3;
        }
    }
    if (err == 0)
        printf("ecb RC5 ok\n");

    for (n = 0; n < RC5_CBC_NUM; n++) {
        i = rc5_cbc_rounds[n];
        if (i < 8)
            continue;

        RC5_32_set_key(&key, rc5_cbc_key[n][0], &(rc5_cbc_key[n][1]), i);

        memcpy(ivb, &(rc5_cbc_iv[n][0]), 8);
        RC5_32_cbc_encrypt(&(rc5_cbc_plain[n][0]), buf, 8,
                           &key, &(ivb[0]), RC5_ENCRYPT);

        if (memcmp(&(rc5_cbc_cipher[n][0]), buf, 8) != 0) {
            printf("cbc RC5 error encrypting (%d)\n", n + 1);
            printf("got     :");
            for (i = 0; i < 8; i++)
                printf("%02X ", buf[i]);
            printf("\n");
            printf("expected:");
            for (i = 0; i < 8; i++)
                printf("%02X ", rc5_cbc_cipher[n][i]);
            err = 30;
            printf("\n");
        }

        memcpy(ivb, &(rc5_cbc_iv[n][0]), 8);
        RC5_32_cbc_encrypt(buf, buf2, 8, &key, &(ivb[0]), RC5_DECRYPT);
        if (memcmp(&(rc5_cbc_plain[n][0]), buf2, 8) != 0) {
            printf("cbc RC5 error decrypting (%d)\n", n + 1);
            printf("got     :");
            for (i = 0; i < 8; i++)
                printf("%02X ", buf2[i]);
            printf("\n");
            printf("expected:");
            for (i = 0; i < 8; i++)
                printf("%02X ", rc5_cbc_plain[n][i]);
            printf("\n");
            err = 3;
        }
    }
    if (err == 0)
        printf("cbc RC5 ok\n");

    EXIT(err);
    return (err);
}

# ifdef undef
static int cfb64_test(unsigned char *cfb_cipher)
{
    IDEA_KEY_SCHEDULE eks, dks;
    int err = 0, i, n;

    idea_set_encrypt_key(cfb_key, &eks);
    idea_set_decrypt_key(&eks, &dks);
    memcpy(cfb_tmp, cfb_iv, 8);
    n = 0;
    idea_cfb64_encrypt(plain, cfb_buf1, (long)12, &eks,
                       cfb_tmp, &n, IDEA_ENCRYPT);
    idea_cfb64_encrypt(&(plain[12]), &(cfb_buf1[12]),
                       (long)CFB_TEST_SIZE - 12, &eks,
                       cfb_tmp, &n, IDEA_ENCRYPT);
    if (memcmp(cfb_cipher, cfb_buf1, CFB_TEST_SIZE) != 0) {
        err = 1;
        printf("idea_cfb64_encrypt encrypt error\n");
        for (i = 0; i < CFB_TEST_SIZE; i += 8)
            printf("%s\n", pt(&(cfb_buf1[i])));
    }
    memcpy(cfb_tmp, cfb_iv, 8);
    n = 0;
    idea_cfb64_encrypt(cfb_buf1, cfb_buf2, (long)17, &eks,
                       cfb_tmp, &n, IDEA_DECRYPT);
    idea_cfb64_encrypt(&(cfb_buf1[17]), &(cfb_buf2[17]),
                       (long)CFB_TEST_SIZE - 17, &dks,
                       cfb_tmp, &n, IDEA_DECRYPT);
    if (memcmp(plain, cfb_buf2, CFB_TEST_SIZE) != 0) {
        err = 1;
        printf("idea_cfb_encrypt decrypt error\n");
        for (i = 0; i < 24; i += 8)
            printf("%s\n", pt(&(cfb_buf2[i])));
    }
    return (err);
}

static char *pt(unsigned char *p)
{
    static char bufs[10][20];
    static int bnum = 0;
    char *ret;
    int i;
    static char *f = "0123456789ABCDEF";

    ret = &(bufs[bnum++][0]);
    bnum %= 10;
    for (i = 0; i < 8; i++) {
        ret[i * 2] = f[(p[i] >> 4) & 0xf];
        ret[i * 2 + 1] = f[p[i] & 0xf];
    }
    ret[16] = '\0';
    return (ret);
}

# endif
#endif
