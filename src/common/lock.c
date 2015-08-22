#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <strings.h>

#include "lock.h"


void lock_init(pthread_mutex_t *lock){
	pthread_mutex_init(lock, NULL);
	return ;
}

void lock_uninit(pthread_mutex_t *lock){
	pthread_mutex_destroy(lock);
	return ;
}

void lock_up(pthread_mutex_t *lock){
	pthread_mutex_lock(lock);
	return ;
}

void lock_down(pthread_mutex_t *lock){
	pthread_mutex_unlock(lock);
	return ;
}

