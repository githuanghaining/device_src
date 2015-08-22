#include "cache.h"
#include "typedef.h"
#include "camera_log.h"
#include "time.h"
#include "common.h"
#include "lock.h"
#include "atomic.h"
#include <errno.h>

int init_user_cache_pool(user_cache_pool_t* ucp,int max_user_num,int size)
{
	ucp->buffer_size = max_user_num*size;
	ucp->buffer = (unsigned char*)malloc(ucp->buffer_size);
	if(ucp->buffer == NULL)
	{
		gerr("init_user_cache_pool malloc buffer error");
		return -1;
	}

	ucp->used_cache_count = 0;
	INIT_LIST_HEAD(&ucp->used_cache_link);

	ucp->free_cache_count = max_user_num;
	INIT_LIST_HEAD(&ucp->free_cache_link);

	lock_init(&ucp->lock);
	int i;

	unsigned char* tmp = ucp->buffer;
	for(i=0;i<max_user_num;i++){
		user_cache_t* uc = (user_cache_t*)malloc(sizeof(user_cache_t));
		if(uc == NULL){
			gerr("init_user_cache_pool malloc user_cache error");
			return -1;
		}
		uc->buffer = tmp+i*size;
		uc->buffer_size = size;
		uc->read_offset = 0;
		uc->write_offset = 0;
		INIT_LIST_HEAD(&uc->user_cache_pool_link);
		list_add_tail(&uc->user_cache_pool_link,&ucp->free_cache_link);
	}
	return 0;
	
}
user_cache_t* malloc_user_cache(user_cache_pool_t* ucp)
{
	lock_up(&ucp->lock);
	if(ucp->free_cache_count <= 0){
		gerr("malloc_user_cache failed,free_cache_count=%d",ucp->free_cache_count);
		lock_down(&ucp->lock);
		return NULL;
	}

	user_cache_t* uc = list_entry(ucp->free_cache_link.next,user_cache_t,user_cache_pool_link);
	list_del(&uc->user_cache_pool_link);
	ucp->free_cache_count--;

	list_add_tail(&uc->user_cache_pool_link,&ucp->used_cache_link);
	ucp->used_cache_count++;
	lock_down(&ucp->lock);
	return uc;	
}
void free_user_cache(user_cache_pool_t* ucp,user_cache_t* uc)
{
	if(uc==NULL)
		return;
	lock_up(&ucp->lock);
	list_del(&uc->user_cache_pool_link);
	ucp->used_cache_count--;

	list_add_tail(&uc->user_cache_pool_link,&ucp->free_cache_link);
	ucp->free_cache_count++;
	lock_down(&ucp->lock);
	
}
void uninit_user_cache_pool(user_cache_pool_t* ucp)
{

}

void add_segement_data(user_cache_t* uc,segement_t* sg)
{
	unsigned char* tmp = (unsigned char*)sg;
	int seg_size = sizeof(segement_t);
	
	int left_size = uc->buffer_size - uc->write_offset;
	if(seg_size <= left_size){
		memcpy(uc->buffer+uc->write_offset,tmp,seg_size);
		
		atomic_add(&uc->write_offset,seg_size);
		if(uc->write_offset >=uc->buffer_size){
			atomic_sub(&uc->write_offset,uc->buffer_size);
		}
	}
	else
	{
		gerr("user id:%d rs_index:%d timestamp:%d buffer size is not 1033 multiple",uc->user_id,sg->rs_index,sg->timestamp);
	}
}


