#ifndef _AES128_H
#define _AES128_H

#ifndef ENABLE_AES128
#define ENABLE_AES128
#endif
/*

in:Ҫ���ܵ�����
in_len:Ҫ���ܵ����ݳ���
out:���ܺ�����ݣ�����������ڴ���䣬�ⲿ����һ��unsignd charָ�뼴�ɣ����������ǵ��ͷ�
out_len:���ܺ�����ݳ���
*/

int D_aes_encrypt(unsigned char* in,unsigned int in_len,unsigned char** out ,unsigned int* out_len);

/*

in:Ҫ���ܵ�����
in_len:Ҫ���ܵ����ݳ���
out:���ܺ�����ݣ�����������ڴ���䣬�ⲿ����һ��unsignd charָ�뼴�ɣ����������ǵ��ͷ�
out_len:���ܺ�����ݳ���
*/

int D_aes_decrypt(unsigned char* in,unsigned int in_len,unsigned char** out ,unsigned int* out_len);

#endif

