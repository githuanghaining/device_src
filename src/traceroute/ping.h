#ifndef __PING_H__
#define __PING_H__

/*
ip_addr[in]:  ip地址，可以是域名

time[out]: 返回ping的时间，单位毫秒

timeout[in]:  超时时间，单位毫秒

成功返回1，失败返回0
*/
int ping( char *ip_addr, int* time,int timeout);
#endif
