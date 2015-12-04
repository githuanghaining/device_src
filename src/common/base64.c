#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* b64encode(const unsigned char* pData, unsigned int dataSize, char* pEncoded, unsigned int* pEncodedSize)
{
    if (pData == NULL || dataSize == 0) {
        return NULL;
    }

    static const char encoding[64] = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
        'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f',
        'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
        'w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/'
    };

    unsigned int size = (((dataSize + 2) * 4) / 3) + 1;
    if (pEncoded == NULL || pEncodedSize == NULL || *pEncodedSize < size) {
        pEncoded = NULL;
        if (pEncodedSize) {
            *pEncodedSize = size;
        }
    }

    char* s = pEncoded;
    if (s == NULL) {
        s = (char*)malloc(size); /* N.B. caller is responsible for free'ing s */
        if (s == NULL) {
            return NULL;
        }
    }

    const unsigned char* src = pData;
    char* dest = s;
    unsigned int numGroups = dataSize / 3;
    unsigned int i;

    for (i = 0; i < numGroups; i++) {
        *dest++ = encoding[src[0] >> 2];
        *dest++ = encoding[((src[0] & 0x03) << 4) | (src[1] >> 4)];
        *dest++ = encoding[((src[1] & 0x0F) << 2) | (src[2] >> 6)];
        *dest++ = encoding[src[2] & 0x3F];
        src += 3;
    }

    if (dataSize % 3 == 1) {
        *dest++ = encoding[src[0] >> 2];
        *dest++ = encoding[((src[0] & 0x03) << 4)];
        *dest++ = '=';
        *dest++ = '=';
    } else if (dataSize % 3 == 2) {
        *dest++ = encoding[src[0] >> 2];
        *dest++ = encoding[((src[0] & 0x03) << 4) | (src[1] >> 4)];
        *dest++ = encoding[((src[1] & 0x0F) << 2)];
        *dest++ = '=';
    }
    *dest = '\0';
    return s;
}

static int convertBase64 (const char data, unsigned char *value)
{
    static const unsigned char decodingarr64[128] = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0x3e, 0xff, 0xff, 0xff, 0x3f,
        0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b,
        0x3c, 0x3d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
        0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e,
        0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
        0x17, 0x18, 0x19, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20,
        0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
        0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30,
        0x31, 0x32, 0x33, 0xff, 0xff, 0xff, 0xff, 0xff,
    };
    unsigned char index = (unsigned char)data;
    if ((index & 0x80) != 0) return 0;

    if (decodingarr64[index] == 0xff) return 0;
    *value = decodingarr64[index];
    return 1;
}

unsigned char* b64decode(const char *pData, unsigned int dataSize, unsigned char* pDecoded, unsigned int *pDecodedSize)
{
    unsigned char *ret;
    int internal_buffer = 0;
    unsigned int size, ix, groups;
    unsigned char jx;
    if (pData == NULL || dataSize == 0) {
        return NULL;
    }

    if ((dataSize % 4) != 0) {
        // must be multiples of 4 characters
        return NULL;
    }
    size = (dataSize * 3) / 4;
    for (ix=1; ix<4; ix++) {
        if (pData[dataSize-ix] != '=') {
            break;
        }
        size--;
    }
    if (pDecoded == NULL || pDecodedSize == NULL || *pDecodedSize < size) {
        pDecoded = NULL;
        if (pDecodedSize) {
            *pDecodedSize = size;
        }
    }

    groups = dataSize / 4;
    ret = pDecoded;
    if (ret == NULL) {
        ret = (unsigned char *)malloc(size);
        if (ret == NULL) {
            return NULL;
        }
        internal_buffer = 1;
    }
    for (ix = 0; ix < groups; ix++) {
        unsigned char value[4];
        for (jx = 0; jx < 4; jx++) {
            if (pData[jx] == '=') {
                if (ix != (groups - 1)) {
                    if (internal_buffer) {
                        free(ret);
                    }
                    return NULL;
                }
                size--;
                value[jx] = 0;
            } else if (!convertBase64(pData[jx], &value[jx])) {
                if (internal_buffer) {
                    free(ret);
                }
                return NULL;
            }
        }
        ret[(ix * 3)] = value[0] << 2 | ((value[1] >> 4) & 0x3);
        ret[(ix * 3) + 1] = (value[1] << 4) | (value[2] >> 2 & 0xf);
        ret[(ix * 3) + 2] = ((value[2] & 0x3) << 6) | value[3];
        pData += 4;
    }
    return ret;
}

#if 0 //TEST
static void print_hex(unsigned char* b, int l)
{
    int i;
    for (i=0; i<l; i++) {
        printf("0x%02x ", *b++);
    }
    printf("\n");
}

int main(void)
{
    unsigned char rand[] = {0x14, 0x67, 0x49, 0x02, 0x52, 0xf2, 0x24, 0x18};
    printf("raw: ");
    print_hex(rand, sizeof(rand));
#if 1
    char encode[14];
    unsigned char decode[8];
    unsigned int dsize;

    dsize = sizeof(encode);
    if (b64encode(rand, sizeof(rand), encode, &dsize)) {
        printf("encode: %s\n", encode);
        dsize = sizeof(decode);
        if (b64decode(encode, strlen(encode), decode, &dsize)) {
            printf("decode: ");
            print_hex(decode, dsize);
        }
    }
#else
    char* encode = NULL;
    unsigned char* decode = NULL;
    unsigned int dsize = 0;

    encode = b64encode(rand, sizeof(rand), encode, &dsize);
    if (encode) {
        printf("encode: %s\n", encode);
        dsize = 0;
        decode = b64decode(encode, strlen(encode), decode, &dsize);
        if (decode) {
            printf("decode: ");
            print_hex(decode, dsize);
            free(decode);
        }
        free(encode);
    }
#endif
    return 0;
}
#endif
