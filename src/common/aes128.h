#ifndef _AES128_H
#define _AES128_H

#ifndef ENABLE_AES128
#define ENABLE_AES128
#endif
/*

in:要加密的数据
in_len:要加密的数据长度
out:加密后的数据，函数里进行内存分配，外部定义一个unsignd char指针即可，但是用完后记得释放
out_len:加密后的数据长度
*/

int D_aes_encrypt(unsigned char* in,unsigned int in_len,unsigned char** out ,unsigned int* out_len);

/*

in:要解密的数据
in_len:要解密的数据长度
out:解密后的数据，函数里进行内存分配，外部定义一个unsignd char指针即可，但是用完后记得释放
out_len:解密后的数据长度
*/

int D_aes_decrypt(unsigned char* in,unsigned int in_len,unsigned char** out ,unsigned int* out_len);

#endif

