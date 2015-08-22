#include <stdio.h>
#include "crc32.h"

static uint   CRC32[256];
static char   init = 0;

//初始化表
void init_crc32_table()
{
    int   i,j;
    uint   crc;
    for(i = 0;i < 256;i++)
    {
         crc = i;
        for(j = 0;j < 8;j++)
        {
            if(crc & 1)
            {
                 crc = (crc >> 1) ^ 0xEDB88320;
            }
            else
            {
                 crc = crc >> 1;
            }
        }
         CRC32[i] = crc;
    }
    init = 1;
}

//crc32实现函数
uint crc_32( uchar *buf, int len)
{
    uint ret = 0xFFFFFFFF;
    int   i;
    if(init == 0)
    {
         init_crc32_table();
    }
    
    for(i = 0; i < len;i++)
    {
         ret = CRC32[((ret & 0xFF) ^ buf[i])] ^ (ret >> 8);
    }
    ret = ~ret;
    return ret;
}
