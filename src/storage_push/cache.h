/**
 * \file 	cache.h
 * \brief	系统缓存
 * 用户索引 用户延迟索引 用户数据包 用户延迟数据包 用户预分配内存实现。
 * \author	liuyong 120031860@qq.com
 *
 */


#ifndef __CACHE_H__
#define __CACHE_H__

#include "common.h"
#include "list.h"


#define SEGEMENT_DATA_LENGTH 1024

#pragma pack(1)
typedef struct segement {
	uint32b_t user_id;
	uint8b_t rs_index;
	uint32b_t timestamp;
	uint8b_t data[SEGEMENT_DATA_LENGTH];
} segement_t;
#pragma pack()

int  init_user_cache_pool(user_cache_pool_t* ucp,int max_user_num,int size);
user_cache_t* malloc_user_cache(user_cache_pool_t* ucp);
void free_user_cache(user_cache_pool_t* ucp,user_cache_t* uc);
void uninit_user_cache_pool(user_cache_pool_t* ucp);

void  add_segement_data(user_cache_t* uc,segement_t* sg);


#endif // __CACHE_H__

