#include "aes128.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/aes.h>

#define AES_KEY_SIZE	128

static unsigned char aes_128_key[16] = {
   0x6A, 0x7C, 0xBB, 0x91,
   0xAF, 0x73, 0x01, 0xA3, 
   0x5A, 0xCF, 0x5B, 0x35, 
   0xA2, 0x5F, 0x98, 0xDF
};

int D_aes_encrypt(unsigned char* in,unsigned int in_len,unsigned char** out ,unsigned int* out_len)
{
	if(in == NULL)
	{
		*out = NULL;
		*out_len = 0;
		return -1;
	}
	
	
	AES_KEY AesKey;
	unsigned char ivec[AES_BLOCK_SIZE];
	int set_data_len = 0;
	if ((in_len%AES_BLOCK_SIZE) == 0)
    {
        set_data_len = in_len;
    }
    else
    {
        set_data_len = ((in_len/AES_BLOCK_SIZE)+1) * AES_BLOCK_SIZE;
    }
    //printf("aes_encrypt in_len:%d , SetDataLen:%d...\n", in_len,set_data_len);   //取16的倍数
	unsigned char* input = (unsigned char*)malloc(set_data_len+1);
	if(input == NULL){
		printf("aes_encrypt input malloc failed\n");
		*out = NULL;
		*out_len = 0;
		return -1;
	}
	memcpy(input,in,in_len);
	

	memset(&AesKey, 0x00, sizeof(AES_KEY));
    if(AES_set_encrypt_key(aes_128_key, AES_KEY_SIZE, &AesKey) < 0)
    {//设置加密密钥
        printf("Unable to set encryption key in AES...\n");
		*out = NULL;
		*out_len = 0;
		free(input);
        return -1;
    }

	memset(ivec,0,sizeof(ivec));
	*out = (unsigned char*)malloc(set_data_len+1);
	if(*out == NULL){
		printf("aes_encrypt malloc failed\n");
		*out = NULL;
		*out_len = 0;
		free(input);
		return -1;
	}
	memset(*out,0,set_data_len+1);
    //加密
    AES_cbc_encrypt(input,*out,set_data_len, &AesKey,ivec, AES_ENCRYPT);
	*out_len = set_data_len;
	free(input);
	return 0;
}

int D_aes_decrypt(unsigned char* in,unsigned int in_len,unsigned char** out ,unsigned int* out_len)
{
	if(in == NULL)
	{
		*out = NULL;
		*out_len = 0;
		return -1;
	}
	

	AES_KEY AesKey;
	unsigned char ivec[AES_BLOCK_SIZE];
	if ((in_len%AES_BLOCK_SIZE) != 0)
    {
        printf("aes_decrypt in_len(%d) AES_BLOCK_SIZE != 0\n",in_len);
		*out = NULL;
		*out_len = 0;
		return -1;
    }

	*out = (unsigned char*)malloc(in_len+1);
	if(*out == NULL){
		printf("aes_decrypt malloc failed\n");
		*out = NULL;
		*out_len = 0;
		return -1;
	}
	memset(*out,0,in_len+1);

	memset(&AesKey, 0x00, sizeof(AES_KEY));
    if(AES_set_decrypt_key(aes_128_key, AES_KEY_SIZE, &AesKey) < 0)
    {//设置解密密钥
        printf("Unable to set decryption key in AES...\n");
		*out = NULL;
		*out_len = 0;
        return -1;
    }

	memset(ivec,0,sizeof(ivec));

	AES_cbc_encrypt(in,*out,in_len,&AesKey,ivec, AES_DECRYPT);
    
    *out_len = in_len;
    
	return 0;
    
}







