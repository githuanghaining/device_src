#include "disk_connect.h"
#include "lock.h"
#include "tcp.h"
#include "ly_time.h"
#include "camera_log.h"
#include "atomic.h"
#include "disk_manager.h"
#include "common.h"
#include <pthread.h>


static disk_client_manager_t	dcm;
static int disk_connect_failed_num = 0;
static pthread_mutex_t disk_connect_num_lock;
extern disk_server_t global_disk_schedule_server;

static void init_global_user_cache(int max_user_num,int cache_size)
{
	int i;
	for(i=0;i<DISK_NUM;i++){
		init_user_cache_pool(&(dcm.disk_clients[i].global_user_cache),max_user_num,cache_size);
	}
	lock_init(&disk_connect_num_lock);
}


static int is_backup_disk_server_valid(disk_server_t* ds)
{
	int i;
	for(i=0;i<DISK_NUM;i++){
		if((strcmp(dcm.disk_clients[i].server_ip,ds->server_ip)==0)&&(dcm.disk_clients[i].server_port == ds->server_port)){
			return 0;
		}
	}
	return 1;
}


disk_server_t* get_backup_server()
{
	disk_server_t* ds;
	unsigned char real_disk_num;
	int ret = get_disk_server_list(global_disk_schedule_server.server_ip,global_disk_schedule_server.server_port,&ds,12,&real_disk_num);
	if(ret == -1){
		gerr("get_backup_server failed");
		return NULL;
	}

	if(real_disk_num < 1){
		gerr("get_backup_server real_disk_num %d < 1",real_disk_num);
		return NULL;
	}

	

	int i;
	for(i=0;i<real_disk_num;i++){
		disk_server_t* ds_tmp = ds+i;
		if(is_backup_disk_server_valid(ds_tmp)){
			disk_server_t* bds = (disk_server_t*)malloc(sizeof(disk_server_t));
			if(bds == NULL){
				gerr("get_backup_server malloc failed");
				free(ds);
				return NULL;
			}
			strcpy(bds->server_ip,ds_tmp->server_ip);
			bds->server_port = ds_tmp->server_port;
			gmsg("get_backup_server success,server ip:%s,port:%d",bds->server_ip,bds->server_port);
			free(ds);
			return bds;
		}
	}
	
	gerr("get_backup_server failed, all disk server ip is invalid");
	free(ds);
	return NULL;
}


int request_memory(push_client_t* pc)
{
	if(pc == NULL){
		gerr("request_memory pc is null");
		return -1;
	}

	int i;
	int malloc_success_flag = 1;
	for(i=0;i<DISK_NUM;i++){
		pc->send_cache[i]=NULL;
		pc->send_cache[i] = malloc_user_cache(&(dcm.disk_clients[i].global_user_cache));
		if(pc->send_cache[i] == NULL){
			gerr("userid:%d malloc user cache null",pc->user_id);
			malloc_success_flag = 0;
			break;
		}
		pc->send_cache[i]->user_id = pc->user_id;
	}

	if(malloc_success_flag != 1){
		for(i=0;i<DISK_NUM;i++){
			if(pc->send_cache[i] != NULL)
				free_user_cache(&(dcm.disk_clients[i].global_user_cache),pc->send_cache[i]);
		}
		return -1;
	}

	return 0;
}


static int change_disk_server(disk_client_t* dc)
{
	int run_count = 0;
	while(1)
	{
		disk_server_t* bds = get_backup_server();
		if(bds == NULL){
			delay_mseconds(100);
			run_count++;
			if(run_count>=200){
				gerr("disk %d change failed,old ip:%s,old port:%d",dc->rs_index,dc->server_ip,dc->server_port);
				return -1;
			}
			continue;
		}

		
		struct shake_hand sk;
		int server_socket = -1;
		
		server_socket = tcp_connect(bds->server_ip,bds->server_port);
		if (-1 == server_socket) {
			gerr("tcp change_disk_server failed.server ip:%s,server port:%d",bds->server_ip, bds->server_port);
			free(bds);
			delay_mseconds(200);
			continue;
		}

		//sk.source=pc->user_id;
		sk.time=real_seconds();
		sk.action=SHAKE_HAND_ACTION_UPLOAD;
		int ret=tcp_send(server_socket, (uint8b_t*)&sk, sizeof(struct shake_hand));
		if(ret!=sizeof(struct shake_hand)){
			gerr("tcp send error.server %s:%d",bds->server_ip, bds->server_port);
			tcp_close(server_socket);
			dc->socket = -1;
			free(bds);
			delay_mseconds(200);
			continue;
		}
		
		ret=tcp_recv(server_socket, (uint8b_t*)&sk, sizeof(struct shake_hand));
		if(ret!=sizeof(struct shake_hand)){
			gerr("tcp recv error.server %s:%d",bds->server_ip, bds->server_port);
			tcp_close(server_socket);
			dc->socket = -1;
			free(bds);
			delay_mseconds(200);
			continue;
		}

		gmsg("disk:%d,change_disk_server success. socket = %d,old ip:%s ===> new ip:%s,old port:%d ===> new port:%d",dc->rs_index, server_socket, 
			dc->server_ip, bds->server_ip,dc->server_port,bds->server_port);

		dc->socket = server_socket;
		dc->server_port = bds->server_port;
		strcpy(dc->server_ip,bds->server_ip);
		free(bds);
		return 0;
	}

	return -1;
	
}

static int reconnect_disk_server(disk_client_t* dc)
{
	while(1)
	{
		struct shake_hand sk;
		int server_socket = -1;
		
		server_socket = tcp_connect(dc->server_ip,dc->server_port);
		if (-1 == server_socket) {
			gdebug("disk:%d,tcp reconnect failed.server ip:%s,server port:%d",dc->rs_index,dc->server_ip, dc->server_port);
			delay_mseconds(2000);
			continue;
		}
		

		//sk.source=pc->user_id;
		sk.time=real_seconds();
		sk.action=SHAKE_HAND_ACTION_UPLOAD;
		int ret=tcp_send(server_socket, (uint8b_t*)&sk, sizeof(struct shake_hand));
		if(ret!=sizeof(struct shake_hand)){
			//gerr("tcp send error.server %s:%d",d->server_ip, d->server_port);
			tcp_close(server_socket);
			dc->socket = -1;
			delay_mseconds(2000);
			continue;
		}
		
		ret=tcp_recv(server_socket, (uint8b_t*)&sk, sizeof(struct shake_hand));
		if(ret!=sizeof(struct shake_hand)){
			//gerr("tcp recv error.server %s:%d",d->server_ip, d->server_port);
			tcp_close(server_socket);
			dc->socket = -1;
			delay_mseconds(2000);
			continue;
		}

		dc->socket = server_socket;
		gmsg("disk:%d,tcp reconnect ok. socket = %d,server ip:%s,server port:%d",dc->rs_index, dc->socket, dc->server_ip, dc->server_port);
		return 0;
	}
	return -1;
}

static int handle_disk_server_exception(disk_client_t* dc)
{
	#if 0
	int ret,ret1;
	ret = reconnect_disk_server(dc);
	if(ret !=0){
		ret1 =  change_disk_server(dc);
		if(ret1 != 0)
			return -1;
		return 0;
	}
	#else
	lock_up(&disk_connect_num_lock);
	disk_connect_failed_num++;
	lock_down(&disk_connect_num_lock);

	int run_count = 0;
	int disk_reconnect_flag = 0;

	//5秒内判断是重连还是换盘
	while(1){
		if(run_count>=25){
			break;
		}

		//如果5秒内磁盘连接断开数大于2，则认为是本地网络出现问题，如果本地网络很好，不太可能同时出现2个盘坏掉
		lock_up(&disk_connect_num_lock);
		if(disk_connect_failed_num >2){
			disk_reconnect_flag = 1;
			//printf("disk :%d ,begin to reconnect,disk_connect_failed_num:%d,run_count:%d\n",dc->rs_index,disk_connect_failed_num,run_count);
			lock_down(&disk_connect_num_lock);
			break;
		}
		lock_down(&disk_connect_num_lock);
		delay_mseconds(200);
		run_count++;
	}


	//printf("disk :%d ,disk_reconnect_flag:%d,disk_connect_failed_num:%d\n",dc->rs_index,disk_reconnect_flag,disk_connect_failed_num);
	int ret;
	if(disk_reconnect_flag){
		reconnect_disk_server(dc);
		lock_up(&disk_connect_num_lock);
		disk_connect_failed_num--;
		lock_down(&disk_connect_num_lock);
		//printf("disk :%d ,reconnect success,disk_connect_failed_num:%d\n",dc->rs_index,disk_connect_failed_num);
		return 1;
	}
	else
	{
		ret = change_disk_server(dc);
		if(ret !=0){
			reconnect_disk_server(dc);
			lock_up(&disk_connect_num_lock);
			disk_connect_failed_num--;
			lock_down(&disk_connect_num_lock);
			return 1;
		}
		lock_up(&disk_connect_num_lock);
		disk_connect_failed_num--;
		lock_down(&disk_connect_num_lock);
		return 0;
	}
	
	#endif
	
	return -1;
}
static int send_data(disk_client_t * dc,user_cache_t* uc)
{
	
	int write_offset = atomic_get(&uc->write_offset);

	/*static int flag = 0;
	if(flag)
	{
		if(write_offset == 0){
			uc->read_offset = 0;
			handle_change_disk_server(dc);
			exit(0);
		}
	}

	flag = 1;*/

	/*if(write_offset == 263415){
		uc->read_offset = write_offset;
		handle_change_disk_server(dc);
		exit(0);
	}*/

	/*static int flag = 0;

	if(flag)
	{
		if(write_offset == 11363&& dc->rs_index == 1){
			uc->read_offset = write_offset;
			handle_change_disk_server(dc);
			exit(0);
		}
	}
	
	if(write_offset == 11363 && dc->rs_index == 1){
		if(flag == 0){
			flag = 1;
		}
	}*/
	

	/*if(write_offset == 226227){
		uc->read_offset = 11363;
		handle_change_disk_server(dc);
		exit(0);
	}*/

	/*static int flag = 0;

	if(flag)
	{
		if(write_offset == 11363&& dc->rs_index == 1){
			uc->read_offset = 226227;
			handle_change_disk_server(dc);
			exit(0);
		}
	}
	
	if(write_offset == 263415 && dc->rs_index == 1){
		if(flag == 0){
			flag = 1;
		}
	}*/
	
	
	if(uc->read_offset == write_offset)
		return 0;

	int socket_fd = dc->socket;
	int send_length,already_sended_length;
	if(uc->read_offset < write_offset){
		send_length= tcp_send2(socket_fd,uc->buffer+uc->read_offset,write_offset-uc->read_offset,&already_sended_length);
		//gdebug("111 disk:%d user_id:%d send data,read offset:%d , write offset:%d,buffer size:%d,send_length:%d",dc->rs_index,uc->user_id,uc->read_offset,uc->write_offset,uc->buffer_size,send_length);
		if(send_length > 0){
			uc->read_offset += send_length;
			uc->read_offset = (uc->read_offset)%(uc->buffer_size);
		}
		else if(send_length == -1)
		{
			gerr("111 disk:%d user_id:%d send data error,read offset:%d , write offset:%d,buffer size:%d,already_sended_length:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,uc->buffer_size,already_sended_length);
			tcp_close(socket_fd);
			return -1;
		}
		else if(send_length == -2)
		{
			gerr("111 disk:%d user_id:%d send data timeout,read offset:%d , write offset:%d,buffer size:%d,already_sended_length:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,uc->buffer_size,already_sended_length);
			tcp_close(socket_fd);
			return -1;
		}
		return 0;
	}
	else
	{
		send_length= tcp_send2(socket_fd,uc->buffer+uc->read_offset,uc->buffer_size-uc->read_offset,&already_sended_length);
		//gdebug("222 disk:%d user_id:%d send data,read offset:%d , write offset:%d,buffer size:%d,send_length:%d",dc->rs_index,uc->user_id,uc->read_offset,uc->write_offset,uc->buffer_size,send_length);
		if(send_length > 0){
			uc->read_offset += send_length;
			uc->read_offset = (uc->read_offset)%(uc->buffer_size);
		}
		else if(send_length == -1)
		{
			gerr("222 disk:%d user_id:%d send data error,read offset:%d , write offset:%d,buffer size:%d,already_sended_length:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,uc->buffer_size,already_sended_length);
			tcp_close(socket_fd);
			return -1;
		}
		else if(send_length == -2)
		{
			gerr("222 disk:%d user_id:%d send data timeout,read offset:%d , write offset:%d,buffer size:%d,already_sended_length:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,uc->buffer_size,already_sended_length);
			tcp_close(socket_fd);
			return -1;
		}

		if(write_offset != 0){
			send_length = tcp_send2(socket_fd,uc->buffer+uc->read_offset,write_offset,&already_sended_length);
			if(send_length > 0){
				uc->read_offset += send_length;
				uc->read_offset = (uc->read_offset)%(uc->buffer_size);
			}
			else if(send_length == -1)
			{
				gerr("333 disk:%d user_id:%d send data error,read offset:%d , write offset:%d,buffer size:%d,already_sended_length:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,uc->buffer_size,already_sended_length);
				tcp_close(socket_fd);
				return -1;
			}
			else if(send_length == -2)
			{
				gerr("333 disk:%d user_id:%d send data timeout,read offset:%d , write offset:%d,buffer size:%d,already_sended_length:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,uc->buffer_size,already_sended_length);
				tcp_close(socket_fd);
				return -1;
			}
		}
		
		return 0;
	}
}


static int find_backward(user_cache_t* uc,int start_pos,int end_pos,unsigned int timestamp,unsigned int* diff_timestamp,int* count)
{
	*count = 0;
	int tmp_pos = end_pos;
	segement_t* sg;
	while(tmp_pos>=start_pos){
		sg = (segement_t*)(uc->buffer+tmp_pos);				
		if(sg->timestamp == timestamp)
		{
			uc->read_offset = tmp_pos;
			tmp_pos = tmp_pos - sizeof(segement_t);	
			(*count) = (*count) + 1;
			continue;
		}
	
		*diff_timestamp = sg->timestamp;
		return 1;
		
	}

	*diff_timestamp = timestamp;
	return 0;
}

static void handle_user_cache(disk_client_t * dc,user_cache_t* uc)
{
	segement_t* sg;
	unsigned int current_timstamp;
	unsigned int diff_timestamp;
	int count=0;

	int write_offset = atomic_get(&uc->write_offset);
	write_offset = (write_offset)%(uc->buffer_size);
	
	if(uc->read_offset == write_offset){
		if(uc->read_offset == 0){
			sg = (segement_t*)(uc->buffer+uc->buffer_size-sizeof(segement_t));
			current_timstamp = sg->timestamp;
			gmsg("1111 disk :%d use id:%d handle_change_disk_server read_offset:%d,write_offset:%d,current_timstamp:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,current_timstamp);
			if(find_backward(uc,sizeof(segement_t),uc->buffer_size-sizeof(segement_t),current_timstamp,&diff_timestamp,&count) == 1){
				gmsg("11111 disk :%d use id:%d  find_backward read_offset:%d,write_offset:%d,count:%d,diff_timestamp:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,count,diff_timestamp);				
			}
			else
			{
				gmsg("11111 disk :%d use id:%d  find_backward failed read_offset:%d,write_offset:%d,count:%d,diff_timestamp:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,count,diff_timestamp);
			}
		}
		else if(uc->read_offset == uc->buffer_size - sizeof(segement_t)){
			sg = (segement_t*)(uc->buffer+uc->read_offset-sizeof(segement_t));
			current_timstamp = sg->timestamp;
			gmsg("2222 disk :%d use id:%d handle_change_disk_server read_offset:%d,write_offset:%d,current_timstamp:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,current_timstamp);
			if(find_backward(uc,0,uc->read_offset-sizeof(segement_t),current_timstamp,&diff_timestamp,&count) == 1){
				gmsg("2222 disk :%d use id:%d  find_backward read_offset:%d,write_offset:%d,count:%d,diff_timestamp:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,count,diff_timestamp);				
			}
			else
			{
				gmsg("2222 disk :%d use id:%d  find_backward failed read_offset:%d,write_offset:%d,count:%d,diff_timestamp:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,count,diff_timestamp);
			}
		}
		else
		{
			sg = (segement_t*)(uc->buffer+uc->read_offset-sizeof(segement_t));
			current_timstamp = sg->timestamp;
			gmsg("3333 disk :%d use id:%d handle_change_disk_server read_offset:%d,write_offset:%d,current_timstamp:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,current_timstamp);
			if(find_backward(uc,0,uc->read_offset-sizeof(segement_t),current_timstamp,&diff_timestamp,&count) == 1){
				gmsg("33333 first find disk :%d use id:%d  handle_change_disk_server read_offset:%d,write_offset:%d,count:%d,diff_timestamp:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,count,diff_timestamp);				
			}
			else
			{
				if(find_backward(uc,write_offset+sizeof(segement_t),uc->buffer_size-sizeof(segement_t),current_timstamp,&diff_timestamp,&count) == 1){
					gmsg("333 second find disk :%d use id:%d  find_backward read_offset:%d,write_offset:%d,count:%d,diff_timestamp:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,count,diff_timestamp);				
				}
				else
				{
					gmsg("33333 second find disk :%d use id:%d  find_backward failed read_offset:%d,write_offset:%d,count:%d,diff_timestamp:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,count,diff_timestamp);				
				}
			}
		}
		
	}
	else if(uc->read_offset < write_offset){
		
		sg = (segement_t*)(uc->buffer+uc->read_offset);
		current_timstamp = sg->timestamp;
		gmsg("4444 disk :%d use id:%d handle_change_disk_server read_offset:%d,write_offset:%d,current_timstamp:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,current_timstamp);
		if(find_backward(uc,0,uc->read_offset,current_timstamp,&diff_timestamp,&count) == 1){
			gmsg("4444 first find disk :%d use id:%d  handle_change_disk_server read_offset:%d,write_offset:%d,count:%d,diff_timestamp:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,count,diff_timestamp);				
		}
		else
		{
			if(find_backward(uc,write_offset+sizeof(segement_t),uc->buffer_size-sizeof(segement_t),current_timstamp,&diff_timestamp,&count) == 1){
				gmsg("4444 second find disk :%d use id:%d  find_backward read_offset:%d,write_offset:%d,count:%d,diff_timestamp:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,count,diff_timestamp);				
			}
			else
			{
				gmsg("4444 second find disk :%d use id:%d  find_backward failed read_offset:%d,write_offset:%d,count:%d,diff_timestamp:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,count,diff_timestamp);
			}
		}
	}
	else
	{
		sg = (segement_t*)(uc->buffer+uc->read_offset);
		current_timstamp = sg->timestamp;
		gmsg("55555 disk :%d use id:%d handle_change_disk_server read_offset:%d,write_offset:%d,current_timstamp:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,current_timstamp);
		if(find_backward(uc,write_offset+sizeof(segement_t),uc->read_offset,current_timstamp,&diff_timestamp,&count) == 1){
			gmsg("5555 disk :%d use id:%d  find_backward read_offset:%d,write_offset:%d,count:%d,diff_timestamp:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,count,diff_timestamp);				
		}
		else
		{
			gmsg("5555 disk :%d use id:%d  find_backward failed read_offset:%d,write_offset:%d,count:%d,diff_timestamp:%d",dc->rs_index,uc->user_id,uc->read_offset,write_offset,count,diff_timestamp);
		}
	}
}

static void handle_change_disk_server(disk_client_t * dc)
{
	user_cache_t* uc;
	list_for_each_entry(uc,&(dc->global_user_cache.used_cache_link),user_cache_pool_link){
		if(uc == NULL)
			continue;
		handle_user_cache(dc,uc);
	}
}

static void handle_reconnect_disk_server(disk_client_t * dc)
{
	user_cache_t* uc;
	list_for_each_entry(uc,&(dc->global_user_cache.used_cache_link),user_cache_pool_link){
		if(uc == NULL)
			continue;
		
		uc->read_offset = atomic_get(&uc->write_offset);
	}
}


static void modify_read_pos(disk_client_t * dc,int handle_mode)
{
	#if 1
	if(handle_mode == 1){//change disk server
		handle_change_disk_server(dc);
	}
	else if(handle_mode == 2){//reconnect disk server
		handle_reconnect_disk_server(dc);
	}
	#else
	handle_reconnect_disk_server(dc);
	#endif
}

void * handle_push_data(void *arg) 
{
	disk_client_t * dc = (disk_client_t*)arg;
	int send_status_flag = 1;
	while(1)
	{
		int used_user_cache_count = dc->global_user_cache.used_cache_count;
		if(used_user_cache_count == 0){
			//gdebug("disk %d thread wait user....",dc->rs_index);
			delay_mseconds(200);
			continue;
		}

		lock_up(&(dc->global_user_cache.lock));
		user_cache_t* uc;
		list_for_each_entry(uc,&(dc->global_user_cache.used_cache_link),user_cache_pool_link){
			if(uc == NULL)
				break;

			int ret = send_data(dc,uc);
			if(ret == -1){
				dc->socket = -1;
				send_status_flag = 0;
				break;
			}
		}
		lock_down(&(dc->global_user_cache.lock));

		if(send_status_flag == 0){
			int ret = handle_disk_server_exception(dc);
			if(ret == 0){// change disk server
				modify_read_pos(dc,1);
			}else if(ret == 1){//reconect disk server
				modify_read_pos(dc,2);
			}
			send_status_flag = 1;
		}

		delay_mseconds(200);
	}
	
}


int  init_disk_send_thread()
{
	int i;
	for(i=0;i<DISK_NUM;i++){
		pthread_t tid_push;
		int ret = pthread_create(&tid_push, NULL, handle_push_data, &(dcm.disk_clients[i]));
		if(ret != 0) {
			gerr("pthread create failure:%d", errno);
			return -1;
		}
	}
	return 0;
}

void uninit_disk_send_thread()
{
	
}



int init_disk_client_manager(disk_server_t*	ds,int max_user_num,int cache_size)
{
	int i;
	for(i=0;i<DISK_NUM;i++){
		strcpy(dcm.disk_clients[i].server_ip,ds[i].server_ip);
		dcm.disk_clients[i].server_port = ds[i].server_port;
		dcm.disk_clients[i].socket = -1;
		dcm.disk_clients[i].user_count = max_user_num;
		dcm.disk_clients[i].rs_index = i+1;
	}

	struct shake_hand sk;
	int server_socket = -1;

	int connected_num=0;
	
	for(i=0;i<DISK_NUM;i++){
		
		server_socket = tcp_connect(dcm.disk_clients[i].server_ip,dcm.disk_clients[i].server_port);
		if (-1 == server_socket) {
			gerr("tcp connet server %s:%d failed.", dcm.disk_clients[i].server_ip, dcm.disk_clients[i].server_port);
			continue;
		}
		
		//gmsg("tcp connect ok. socket = %d,server %s:%d", d->socket,d->server_ip, d->server_port);

		//sk.source=pc->user_id;
		sk.time=real_seconds();
		sk.action=SHAKE_HAND_ACTION_UPLOAD;
		int ret=tcp_send(server_socket, (uint8b_t*)&sk, sizeof(struct shake_hand));
		if(ret!=sizeof(struct shake_hand)){
			gerr("tcp send error.server %s:%d",dcm.disk_clients[i].server_ip, dcm.disk_clients[i].server_port);
			tcp_close(server_socket);
			continue;
		}
		//gdebug("tcp send shake hand request done.");

		//
		ret=tcp_recv(server_socket, (uint8b_t*)&sk, sizeof(struct shake_hand));
		if(ret!=sizeof(struct shake_hand)){
			gerr("tcp recv error.server %s:%d",dcm.disk_clients[i].server_ip, dcm.disk_clients[i].server_port);
			tcp_close(server_socket);
			continue;
		}
		dcm.disk_clients[i].socket = server_socket;
		connected_num++;
		gmsg("disk:%d,tcp connect ok. socket = %d,server ip:%s,server port:%d",dcm.disk_clients[i].rs_index, dcm.disk_clients[i].socket, dcm.disk_clients[i].server_ip, dcm.disk_clients[i].server_port);
	}

	if(connected_num == DISK_NUM)
	{
		gmsg("connect all disk server success");
		init_global_user_cache(max_user_num,cache_size);
		init_disk_send_thread();
		return 0;
	}

	for(i=0;i<DISK_NUM;i++){
		if(dcm.disk_clients[i].socket != -1)
		{
			tcp_close(dcm.disk_clients[i].socket);
		}
	}

	gmsg("connect all disk server failed,connected_num:%d",connected_num);
	return -1;
}

void uninit_disk_client_manager()
{

}


