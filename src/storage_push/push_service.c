#include "push_service.h"
#include "typedef.h"
#include "camera_log.h"
#include "ly_time.h"
#include "tcp.h"
#include "push.h"
#include "cache.h"
#include "common.h"
#include "list.h"
#include "disk_connect.h"
#include "crc32.h"
#include "disk_manager.h"
#include "push.h"
#include <sys/time.h>



#define MAX_USER_NUM				1
#define MAX_USER_CACHE_SIZE			100*1033
#define FLV_HEAD_SIZE				11
#define SPS_HEAD_SIZE				16
#define VIDEO_FRAME_HEAD_SIZE		9
#define FLV_TAG_SIZE				4
#define FLV_SCRIPT_SIZE				23



static push_client_t* pc;
static int first_frame_flag = 1;
static unsigned int start_time = 0;
static unsigned int current_time = 0;

disk_server_t global_disk_schedule_server;


unsigned int getCurrentTime(void) 
{
    struct timeval aika;
    gettimeofday(&aika,NULL);
    unsigned int msecs = aika.tv_sec * 1000;
    msecs += (aika.tv_usec / 1000);
    return msecs;
}

unsigned long long  getRealTime(void) 
{
    struct timeval aika;
    gettimeofday(&aika,NULL);
	unsigned long long tmp_sec = aika.tv_sec;
	unsigned long long tmp_usec = aika.tv_usec;
    unsigned long long msecs = tmp_sec * 1000;
    msecs += (tmp_usec / 1000);
    return msecs;
}


int init_push_client(unsigned int user_id)
{
	pc = (push_client_t *)malloc(sizeof(push_client_t));
	if(pc == NULL) {
		gerr("user id:%d malloc fail.",user_id);
		return -1;
	}
	pc->user_id = user_id;
	pc->sequence_id = 1;
	memset(pc->recv_buff,0,sizeof(pc->recv_buff));
	memset(pc->spsBuf,0,sizeof(pc->spsBuf));
	memset(pc->ppsBuf,0,sizeof(pc->ppsBuf));
	pc->data_length = 0;
	pc->is_sps_pps_sended = 0;
	pc->spslen = 0;
	pc->ppsLen = 0;
	pc->sps_pps_flv_tag = NULL;
	pc->sps_pps_tag_size = 0;
	INIT_LIST_HEAD(&pc->push_client_node_link);
	int ret = request_memory(pc);
	if(ret != 0){
		gerr("user id:%d request memory failed",user_id);
		return -1;
	}

	return 0;
}


int init_push_service(char* ip, int port,unsigned int user_id)
{
	disk_server_t* ds;
	unsigned char real_disk_num;
	int ret = get_disk_server_list(ip,port,&ds,DISK_NUM,&real_disk_num);
	if(ret != 0){
		return -1;
	}

	if(real_disk_num != DISK_NUM){
		gerr("real disk num %d is not %d",real_disk_num,DISK_NUM);
		return -1;
	}

	ret = init_disk_client_manager(ds,MAX_USER_NUM,MAX_USER_CACHE_SIZE);
	if(ret !=0){
		gerr("init_disk_client_manager failed");
		free(ds);
		return -1;
	}	

	ret = init_push_client(user_id);
	if(ret !=0){
		gerr("init_push_client failed");
		free(ds);
		return -1;
	}

	strcpy(global_disk_schedule_server.server_ip,ip);
	global_disk_schedule_server.server_port = port;
	init_crc32_table();
	free(ds);
	return 0;
}

static void create_script_flv_buffer(push_client_t* pct,const char* data,int len)
{ 
	unsigned char* script = pct->script_tag;
	*script++ = 18;
	unsigned int data_len = 12;
	unsigned char* p_data = (unsigned char*)&data_len;
	*script++ = p_data[2];
	*script++ = p_data[1];
	*script++ = p_data[0];
	*script++ = 0;
    *script++ = 0;
    *script++ = 0;
    *script++ = 0;
    *script++ = 0;
    *script++ = 0;
    *script++ = 0;

	unsigned long long current_time = getRealTime();
	p_data = (unsigned char*)&current_time;
	//printf("create_script_flv_buffer current_time:%llu\n",current_time);
	*script++ = p_data[7];
    *script++ = p_data[6];
    *script++ = p_data[5];
    *script++ = p_data[4];
    *script++ = p_data[3];
    *script++ = p_data[2];
    *script++ = p_data[1];
	*script++ = p_data[0];

	uint crc_val = crc_32((unsigned char*)data,len);
	//printf("crc_val:%08x\n",crc_val);
	p_data = (unsigned char*)&crc_val;
	*script++ = p_data[3];
    *script++ = p_data[2];
    *script++ = p_data[1];
	*script++ = p_data[0];

	unsigned int first_tag_size = 23;
	p_data = (unsigned char*)&first_tag_size;
	*script++ = p_data[3];
    *script++ = p_data[2];
    *script++ = p_data[1];
	*script++ = p_data[0];
	
}


static void create_sps_pps_flv_buffer(push_client_t* pct,const char* sps_data,int sps_len,const char* pps_data,int pps_len,unsigned int time)
{
	char* dst = pct->sps_pps_flv_tag;
	char* tmp;
	//sps
	*dst++ = 0x09;
	int flv_data_size = SPS_HEAD_SIZE+sps_len+pps_len;
	tmp = (char*)&flv_data_size;
	*dst++ = tmp[2];
	*dst++ = tmp[1];
	*dst++ = tmp[0];
	tmp = (char*)&time;
	*dst++ = tmp[2];
	*dst++ = tmp[1];
	*dst++ = tmp[0];
	*dst++ = 0x00;
	*dst++ = 0x00;
	*dst++ = 0x00;
	*dst++ = 0x00;
	*dst++ = 0x17;
	*dst++ = 0x00;
	*dst++ = 0x00;
	*dst++ = 0x00;
	*dst++ = 0x00;
	*dst++ = 0x01;
	*dst++ = sps_data[1];
	*dst++ = sps_data[2];
	*dst++ = sps_data[3];
	*dst++ = 0x03;
	*dst++ = 0xe1;
	tmp = (char*)&sps_len;
	*dst++ = tmp[1];
	*dst++ = tmp[0];
	memcpy(dst,sps_data, sps_len);

	//pps
	dst = dst+sps_len;
	*dst++ = 0x01;
	tmp =(char*)&pps_len;
	*dst++ = tmp[1];
	*dst++ = tmp[0];
	memcpy(dst,pps_data, pps_len);

	//tag size
	dst = dst+pps_len;
	int flv_tag_size = sps_len+pps_len+FLV_HEAD_SIZE+SPS_HEAD_SIZE;
	tmp = (char*)&flv_tag_size;
	*dst++ = tmp[3];
	*dst++ = tmp[2];
	*dst++ = tmp[1];
	*dst++ = tmp[0];
}


static void create_I_frame_flv_buffer(push_client_t* pct,const char* data,int len,unsigned int time)
{
	create_sps_pps_flv_buffer(pct,pct->spsBuf,pct->spslen,pct->ppsBuf,pct->ppsLen,time);
	create_script_flv_buffer(pct,pct->sps_pps_flv_tag,pc->sps_pps_tag_size);
	int target_len = FLV_SCRIPT_SIZE+pc->sps_pps_tag_size+FLV_HEAD_SIZE+VIDEO_FRAME_HEAD_SIZE+len+FLV_TAG_SIZE;
	
	if(pct->data_length+target_len <= BUFFER_SIZE){
		memcpy(pct->recv_buff+pct->data_length,pct->script_tag,sizeof(pct->script_tag));
		pct->data_length +=sizeof(pct->script_tag);
		memcpy(pct->recv_buff+pct->data_length,pct->sps_pps_flv_tag,pct->sps_pps_tag_size);
		pct->data_length +=pct->sps_pps_tag_size;
		
		char* dst = pct->recv_buff+ pct->data_length;
		char* tmp;
		*dst++ = 0x09;
		int flv_data_size = VIDEO_FRAME_HEAD_SIZE+len;
		tmp = (char*)&flv_data_size;
		*dst++ = tmp[2];
		*dst++ = tmp[1];
		*dst++ = tmp[0];
		tmp = (char*)&time;
		*dst++ = tmp[2];
		*dst++ = tmp[1];
		*dst++ = tmp[0];
		*dst++ = 0x00;
		*dst++ = 0x00;
		*dst++ = 0x00;
		*dst++ = 0x00;
		*dst++ = 0x17;
		*dst++ = 0x01;
		*dst++ = 0x00;
		*dst++ = 0x00;
		*dst++ = 0x00;
		tmp = (char*)&len;
		*dst++ = tmp[3];
		*dst++ = tmp[2];
		*dst++ = tmp[1];
		*dst++ = tmp[0];
		memcpy(dst,data, len);
		dst = dst+len;
		
		int flv_tag_size = FLV_HEAD_SIZE+VIDEO_FRAME_HEAD_SIZE+len;
		tmp = (char*)&flv_tag_size;
		*dst++ = tmp[3];
		*dst++ = tmp[2];
		*dst++ = tmp[1];
		*dst++ = tmp[0];
		pct->data_length += (flv_tag_size+FLV_TAG_SIZE);
	}
	else
	{
		gerr("pct->data_length:%d +target_len:%d > BUFFER_SIZE",pct->data_length,target_len);
	}
		
}

static void create_P_frame_flv_buffer(push_client_t* pct,const char* data,int len,unsigned int time)
{
	if(pct->data_length + len <= BUFFER_SIZE){
		char* dst = pct->recv_buff+ pct->data_length;
		char* tmp;
		*dst++ = 0x09;
		int flv_data_size = VIDEO_FRAME_HEAD_SIZE+len;
		tmp = (char*)&flv_data_size;
		*dst++ = tmp[2];
		*dst++ = tmp[1];
		*dst++ = tmp[0];
		tmp = (char*)&time;
		*dst++ = tmp[2];
		*dst++ = tmp[1];
		*dst++ = tmp[0];
		*dst++ = 0x00;
		*dst++ = 0x00;
		*dst++ = 0x00;
		*dst++ = 0x00;
		*dst++ = 0x27;
		*dst++ = 0x01;
		*dst++ = 0x00;
		*dst++ = 0x00;
		*dst++ = 0x00;
		tmp = (char*)&len;
		*dst++ = tmp[3];
		*dst++ = tmp[2];
		*dst++ = tmp[1];
		*dst++ = tmp[0];
		memcpy(dst,data, len);
		dst = dst+len;
		int flv_tag_size = FLV_HEAD_SIZE+VIDEO_FRAME_HEAD_SIZE+len;
		tmp = (char*)&flv_tag_size;
		*dst++ = tmp[3];
		*dst++ = tmp[2];
		*dst++ = tmp[1];
		*dst++ = tmp[0];
		pct->data_length += (flv_tag_size+FLV_TAG_SIZE);
	}
}




void init_sps_pps_tag_buffer()
{
	int sps_pps_tag_size = pc->spslen+pc->ppsLen+FLV_HEAD_SIZE+SPS_HEAD_SIZE+FLV_TAG_SIZE;
	pc->sps_pps_flv_tag = (char*)malloc(sps_pps_tag_size);
	memset(pc->sps_pps_flv_tag,0,sps_pps_tag_size);
	pc->sps_pps_tag_size = sps_pps_tag_size;
}

void push_data(const char* data,int len,FrameType type)
{
	unsigned int diff_time;
	if(type == SPS){
		if(pc->is_sps_pps_sended == 0){
			memcpy(pc->spsBuf,data,len);
			pc->spslen = len;
		}
	}
	else if(type == PPS){
		if(pc->is_sps_pps_sended == 0){
			memcpy(pc->ppsBuf,data,len);
			pc->ppsLen= len;
			pc->is_sps_pps_sended = 1;
			init_sps_pps_tag_buffer();
		}
	}
	else if(type == I_FRAME){
		if(pc->is_sps_pps_sended == 1){
			if(first_frame_flag == 1){
				start_time = getCurrentTime();
				current_time = start_time;
				first_frame_flag = 0;
				diff_time = current_time - start_time;
			}
			else
			{
				current_time = getCurrentTime();
				diff_time = current_time - start_time;
			}
			create_I_frame_flv_buffer(pc,data,len,diff_time);
		}
	}
	else if(type == P_FRAME){
		if(pc->is_sps_pps_sended == 1){
			current_time = getCurrentTime();
			diff_time = current_time - start_time;
			create_P_frame_flv_buffer(pc,data,len,diff_time);
		}
	}
	
	if(pc->data_length < SEGEMENT_DATA_LENGTH*DISK_NUM)
	{
		//gdebug("put_segement_packet ,userid:%d, pc->data_length :%d < 1024,continue to recv",pc->user_id,pc->data_length);
		return;
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

	int left_len = pc->data_length - read_len;
	memmove(pc->recv_buff, pc->recv_buff+ read_len, left_len);
	pc->data_length = left_len;
}

