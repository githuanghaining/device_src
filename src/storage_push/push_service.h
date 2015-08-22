#ifndef __PUSH_SERVICE_H__
#define __PUSH_SERVICE_H__

#ifdef __cplusplus
extern "C"{
#endif


typedef enum {
	SPS				=		1,   
	PPS				=		2,
	I_FRAME     	=     	3,      
	P_FRAME    		=     	4,  
	AUDIO			=		5,
	NONE            =       255
}FrameType;

/*
��ʼ�����ͷ���
����:ipΪ���ͷ�������ַ,portΪ���ͷ������˿�
����ֵ:��ʼ���ɹ�����0��ʧ�ܷ���-1
*/
int init_push_service(char* ip, int port,unsigned int user_id);

void push_data(const char* data,int len,FrameType type);


#ifdef __cplusplus
}
#endif
#endif 


