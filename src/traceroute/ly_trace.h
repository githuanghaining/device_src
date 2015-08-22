#ifndef _LY_TRACE_H
#define _LY_TRACE_H

#define MAX_IP_ADDR		50
#define MAX_DOMAIN		150

#define PROBE_NUMBER	3

typedef struct route_info{
	int 	ttl;															//����
	char 	domain[PROBE_NUMBER][MAX_DOMAIN];								//����
	char 	ip[PROBE_NUMBER][MAX_IP_ADDR];									//IP��ַ
	int     time[PROBE_NUMBER];												//ÿ��̽���ʱ�䣬��λ����
} route_info_t;


/*
ip[in]: Ҫ���ĵ�ַ
ttl_num[out]: ���ص�����
route_info_list: ���ص�·����Ϣ�б�

ʹ�����Ҫע���ͷ�route_info_listռ�õ��ڴ�

*/
void trace_route(char* ip,int* ttl_num, route_info_t** route_info_list);

#endif

