#ifndef _DISK_MANAGER_H_
#define _DISK_MANAGER_H_
#include "common.h"

int get_disk_server_list(char* ip,int port,disk_server_t** ds,uint8b_t disk_num, uint8b_t* real_disk_num);
#endif

