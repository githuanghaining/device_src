#ifndef LOCK_H_
#define LOCK_H_

#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <strings.h>

void lock_init(pthread_mutex_t *lock);

void lock_uninit(pthread_mutex_t *lock);

void lock_up(pthread_mutex_t *lock);

void lock_down(pthread_mutex_t *lock);


#endif

