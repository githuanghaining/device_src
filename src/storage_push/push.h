#ifndef __PUSH_H__
#define __PUSH_H__


#include "cache.h"
#include "common.h"
#include "list.h"

/**/


#define DISK_NUM	8

#define BUFFER_SIZE 512*1024

/**/

typedef struct push_client{
	uint32b_t user_id;
	char recv_buff[BUFFER_SIZE];
	int	 data_length;
	char spsBuf[100];
	char ppsBuf[100];
	int spslen;
	int ppsLen;
	int is_sps_pps_sended;
	char* sps_pps_flv_tag;
	int sps_pps_tag_size;
	unsigned char script_tag[27];
	user_cache_t*	send_cache[DISK_NUM];	
	struct list_head push_client_node_link;
	unsigned int sequence_id;
}push_client_t;

typedef struct push_client_node{
	int count;
	struct list_head push_client_link;
}push_client_node_t;

typedef struct push_client_hash{
	int blocks;
	int count;
	struct push_client_node * nodes;
}push_client_hash_t;



int init_push_client_hash(push_client_hash_t * pch, int blocks);

void uninit_index_packet_hash(push_client_hash_t * pch);


/**
 * \brief 数据缓存区建立
 *
 * \param[in] ch	推送数据客户端哈希表
 * \param[in] user_id 用户id
 *
 * \return	返回推送客户端
 * \retval NULL 		建立失败
 * \retval !NULL		建立成功
 */
push_client_t * find_push_client(push_client_hash_t * ch, uint32b_t user_id);


/**
 * \brief 延迟等待
 *
 * \param[in] 	ms 以毫秒为单位的睡眠等待
 * \param[out] 	无
 *
 * \return 无
 */
push_client_t * malloc_push_client(uint32b_t user_id);
int insert_push_client(push_client_hash_t * pch, push_client_t * pc);
int delete_push_client(push_client_hash_t * pch, push_client_t * pc);



int put_segement_packet(push_client_t * pc, message_content_t * msg);




#endif // __PUSH_H__

