#include "check_time.h"
#include<sys/time.h>

int main()
{
	printf("begin to check time............\n");
	struct  timeval    tv;
    struct  timezone   tz;
    gettimeofday(&tv,&tz);
	tz.tz_minuteswest = -480;
	tz.tz_dsttime = 0;
	settimeofday(&tv,&tz);
	sync_time();
	printf("check time success\n");
	printf("tv_sec:%d\n",tv.tv_sec);
    printf("tv_usec:%d\n",tv.tv_usec);
    printf("tz_minuteswest:%d\n",tz.tz_minuteswest);
    printf("tz_dsttime:%d\n",tz.tz_dsttime);
	
}
