#ifndef _CRC32_H
#define _CRC32_H

typedef unsigned int  uint;
typedef unsigned char uchar;

void init_crc32_table();
uint crc_32(uchar* buf, int len);
#endif
