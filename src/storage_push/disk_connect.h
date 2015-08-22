#ifndef _DISK_CONNECT_H_
#define _DISK_CONNECT_H_

#include "list.h"
#include "cache.h"
#include "typedef.h"
#include "push.h"

int init_disk_client_manager(disk_server_t* ds,int max_user_num,int cache_size);
void uninit_disk_client_manager();
int request_memory(push_client_t* pc);
int init_disk_send_thread();
void uninit_disk_send_thread();


#endif

