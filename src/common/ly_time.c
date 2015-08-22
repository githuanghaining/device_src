#include "ly_time.h"
#include <time.h>
#include <sys/select.h>
#include "typedef.h"


uint32b_t monotonic_seconds() {
	int ret = 0;
	struct timespec t;
	ret = clock_gettime(CLOCK_MONOTONIC, &t);
	if(ret != 0) {
		return 0;
	}
	return t.tv_sec;
}
uint64b_t monotonic_mseconds() {
	int ret = 0;
	struct timespec t;
	ret = clock_gettime(CLOCK_MONOTONIC, &t);
	if(ret != 0) {
		return 0;
	}
	return t.tv_sec * 1000 + t.tv_nsec / 1000000;
}

uint32b_t real_seconds() {
	int ret = 0;
	struct timespec t;
	ret = clock_gettime(CLOCK_REALTIME, &t);
	if(ret != 0) {
		return 0;
	}
	return t.tv_sec;
}
uint64b_t read_mseconds() {
	int ret = 0;
	struct timespec t;
	ret = clock_gettime(CLOCK_REALTIME, &t);
	if(ret != 0) {
		return 0;
	}
	return t.tv_sec * 1000 + t.tv_nsec / 1000000;
}
void delay_mseconds(int32b_t ms) {
	int fd = 0;
	struct timeval tv;
	tv.tv_sec = ms / 1000;
	tv.tv_usec = 1000 * (ms % 1000);
	select(fd + 1, NULL, NULL, NULL, &tv);
	return ;
}

int32b_t set_systime(uint32b_t time_secs) {
	int ret = 0;
	struct timespec t;
	t.tv_sec = time_secs;
	t.tv_nsec = 0;
	ret = clock_settime(CLOCK_REALTIME, &t);
	if(ret != 0) 
		return -1;
	
	return 0;

}


