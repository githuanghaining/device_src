#include "push.h"
#include "camera_log.h"
#include "cache.h"
#include "lock.h"
#include "ly_time.h"
#include "tcp.h"
#include "disk_connect.h"
#include "crc32.h"
#include <string.h>


static uint32b_t source_hash_value(uint32b_t blocks, uint32b_t source) {
	return source % blocks;
}


int init_push_client_hash(push_client_hash_t * pch, int blocks) {
	pch->blocks = blocks;
	pch->count = 0;
	pch->nodes = (push_client_node_t *)malloc(sizeof(push_client_node_t) * blocks);
	if(pch->nodes == NULL) {
		gerr("malloc fail.");
		return -1;
	}
	int i = 0;
	for(i = 0; i < blocks; i++) {
		pch->nodes[i].count = 0;
		INIT_LIST_HEAD(&pch->nodes[i].push_client_link);
	}

	return 0;
}

void uninit_index_packet_hash(push_client_hash_t * pch) {
	free(pch->nodes);
}


push_client_t * find_push_client(push_client_hash_t * pch, uint32b_t user_id) {
	int hash_value = source_hash_value(pch->blocks, user_id);
	push_client_t * pc = NULL;
	list_for_each_entry(pc, &pch->nodes[hash_value].push_client_link, push_client_node_link) {
		if(user_id == pc->user_id) {
			return pc;
		}
	}

	return NULL;
}


push_client_t * malloc_push_client(uint32b_t user_id) {
	push_client_t * pc = (push_client_t *)malloc(sizeof(push_client_t));
	if(pc == NULL) {
		gerr("user id:%d malloc fail.",user_id);
		return NULL;
	}
	pc->user_id = user_id;
	pc->sequence_id = 1;
	memset(pc->recv_buff,0,sizeof(pc->recv_buff));
	pc->data_length = 0;
	INIT_LIST_HEAD(&pc->push_client_node_link);
	int ret = request_memory(pc);
	if(ret != 0){
		gerr("user id:%d request memory failed",user_id);
		return NULL;
	}
	return pc;
}

int insert_push_client(push_client_hash_t * pch, push_client_t * pc) {
	int hash_value = source_hash_value(pch->blocks, pc->user_id);
	list_add_tail(&pc->push_client_node_link, &pch->nodes[hash_value].push_client_link);
	pch->nodes[hash_value].count++;
	pch->count++;
	return 0;
}

int delete_push_client(push_client_hash_t * pch, push_client_t * pc) {
	int hash_value = source_hash_value(pch->blocks, pc->user_id);
	push_client_t * pos = NULL;
	push_client_t * n = NULL;
	list_for_each_entry_safe(pos, n, &pch->nodes[hash_value].push_client_link, push_client_node_link) {
		if(pc->user_id == pos->user_id) {
			list_del(&pc->push_client_node_link);
			pch->nodes[hash_value].count--;
			pch->count--;
			return 0;
		}
	}
	
	return -1;
}


int put_segement_packet(push_client_t * pc, message_content_t * msg) {

	if(pc->data_length + msg->data_length <= BUFFER_SIZE){
		memcpy(pc->recv_buff+ pc->data_length, msg->data, msg->data_length);
		pc->data_length += msg->data_length;
	}
	else
		gerr("put_segement_packet ,recv buffer full,userid:%d,pc->data_length:%d,msg->data_lengt:%d",pc->user_id,pc->data_length,msg->data_length);

	#if 1
	if(pc->data_length < SEGEMENT_DATA_LENGTH*DISK_NUM)
	{
		//gdebug("put_segement_packet ,userid:%d, pc->data_length :%d < 1024,continue to recv",pc->user_id,pc->data_length);
		return -1;
	}

	uint32b_t slice_time_align = (real_seconds() / TIMESTAMP_STEP) * TIMESTAMP_STEP;
	int read_len = 0;
	while(pc->data_length - read_len >= SEGEMENT_DATA_LENGTH*DISK_NUM){

		char* data = pc->recv_buff  +read_len;
		int i;
		for(i=0;i<DISK_NUM;i++){
			segement_t sg;
			sg.user_id = pc->user_id;
			sg.rs_index = i+1;
			sg.timestamp = slice_time_align;
			memcpy(sg.data,data+i*SEGEMENT_DATA_LENGTH,SEGEMENT_DATA_LENGTH);
			add_segement_data(pc->send_cache[i],&sg);
			read_len +=SEGEMENT_DATA_LENGTH;
		}
	}
	#else
	if(pc->data_length < 1016*DISK_NUM)
	{
		//gdebug("put_segement_packet ,userid:%d, pc->data_length :%d < 1024,continue to recv",pc->user_id,pc->data_length);
		return -1;
	}

	uint32b_t slice_time_align = (real_seconds() / TIMESTAMP_STEP) * TIMESTAMP_STEP;
	int read_len = 0;
	while(pc->data_length - read_len >= 1016*DISK_NUM){

		char* data = pc->recv_buff  +read_len;
		int i;
		for(i=0;i<DISK_NUM;i++){
			segement_t sg;
			sg.user_id = pc->user_id;
			sg.rs_index = i+1;
			sg.timestamp = slice_time_align;
			memcpy(sg.data,(unsigned char*)(&pc->sequence_id),4);
			memcpy(sg.data+4,data+i*1016,1016);
			unsigned int crc_value = crc_32(sg.data+4,1016);
			unsigned char* src = (unsigned char*)&crc_value;
			memcpy(sg.data+1020,src,4);
			add_segement_data(pc->send_cache[i],&sg);
			read_len +=1016;
			pc->sequence_id++;
		}
	}
	#endif

	
	int left_len = pc->data_length - read_len;
	memmove(pc->recv_buff, pc->recv_buff+ read_len, left_len);
	pc->data_length = left_len;
	
	return 0;
	
}


