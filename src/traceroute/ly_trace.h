#ifndef _LY_TRACE_H
#define _LY_TRACE_H

#define MAX_IP_ADDR		50
#define MAX_DOMAIN		150

#define PROBE_NUMBER	3

typedef struct route_info{
	int 	ttl;															//跳数
	char 	domain[PROBE_NUMBER][MAX_DOMAIN];								//域名
	char 	ip[PROBE_NUMBER][MAX_IP_ADDR];									//IP地址
	int     time[PROBE_NUMBER];												//每次探测的时间，单位毫秒
} route_info_t;


/*
ip[in]: 要检查的地址
ttl_num[out]: 返回的跳数
route_info_list: 返回的路由信息列表

使用完后要注意释放route_info_list占用的内存

*/
void trace_route(char* ip,int* ttl_num, route_info_t** route_info_list);

#endif

