#ifndef __PING_H__
#define __PING_H__

/*
ip_addr[in]:  ip��ַ������������

time[out]: ����ping��ʱ�䣬��λ����

timeout[in]:  ��ʱʱ�䣬��λ����

�ɹ�����1��ʧ�ܷ���0
*/
int ping( char *ip_addr, int* time,int timeout);
#endif
