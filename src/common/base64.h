#ifndef __BASE64_H__
#define __BASE64_H__

#define B64_ENCODE_SIZE(s) (((((s)+2)*4)/3)+1) //definitely
#define B64_DECODE_SIZE(s) (((s)*3)/4) //could be less

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/**
 * base64编码
 */
char* b64encode(const unsigned char* pData, unsigned int dataSize, char* pEncoded, unsigned int* pEncodedSize);

/**
 * base64解码
 */
unsigned char* b64decode(const char *pData, unsigned int dataSize, unsigned char* pDecoded, unsigned int *pDecodedSize);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__BASE64_H__
