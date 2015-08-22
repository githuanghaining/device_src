#ifndef __COMMON_H__
#define __COMMON_H__

#include "typedef.h"
#include "list.h"
#include <pthread.h>

#define HASH_SIZE 10
#define TIMESTAMP_STEP			30
#define SVMQ_MAX_SIZE (1024 * 1024 * 128)
#define SVMQ_UPLOAD_MSG_TYPE	9527
#define MAX_IP_LENGTH	256
#define DISK_NUM		8


#pragma pack(1)
typedef struct message_content {
	uint32b_t user_id;
	uint32b_t data_length;
	char data[1024 * 1024 * 4];
} message_content_t;
#pragma pack()

#pragma pack(1)
typedef struct message {
	long msg_type;
	message_content_t content;
} message_t;
#pragma pack()

typedef struct user_cache{
	unsigned char* 	buffer;
	int	  	buffer_size;
	int		read_offset;
	int 	write_offset;
	uint32b_t user_id;
	struct list_head	user_cache_pool_link;
}user_cache_t;

typedef struct user_cache_pool{
	unsigned char* buffer;
	int buffer_size;

	int used_cache_count;
	struct list_head used_cache_link;

	int free_cache_count;
	struct list_head free_cache_link;

	pthread_mutex_t lock;
}user_cache_pool_t;



typedef struct disk_server{
	int8b_t server_ip[MAX_IP_LENGTH];
	int32b_t server_port;
}disk_server_t;

typedef struct backup_disk_server{
	int8b_t server_ip[MAX_IP_LENGTH];
	int32b_t server_port;
	struct list_head backup_disk_server_list_link;
}backup_disk_server_t;


typedef struct disk_client {
	int8b_t server_ip[MAX_IP_LENGTH];
	int32b_t server_port;
	int32b_t socket;
	int rs_index;
	int user_count;
	user_cache_pool_t global_user_cache;

}disk_client_t;

typedef struct disk_client_manager{
	disk_client_t disk_clients[DISK_NUM];
}disk_client_manager_t;

#endif

