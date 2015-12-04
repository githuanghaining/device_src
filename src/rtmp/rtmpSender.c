#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rtmpcommon.h"
#include "log.h"
#include "rtmpSender.h"
#include "platform_cfg.h"
#include <fcntl.h>

#ifdef SPEEX
#include <speex/speex.h>
#endif
#ifdef PLAYPCM
#include <Encoder.h>
#endif
#ifndef NETPUSH
#ifndef WIN32

void Sys_Sleep(DWORD aMilliseconds)
{
    usleep(aMilliseconds*1000);
}

DWORD Sys_GetTickCount(void) 
{
    struct timeval aika;
    gettimeofday(&aika,NULL);
    unsigned long msecs = aika.tv_sec * 1000;
    msecs += (aika.tv_usec / 1000);
    return msecs;
}

DWORD64 Sys_MicroSeconds(void) 
{
	struct timeval aika;
	gettimeofday(&aika,NULL);
	unsigned long long tmp_sec = aika.tv_sec;
	unsigned long long tmp_usec = aika.tv_usec;
	unsigned long long msecs = tmp_sec * 1000 *1000;
	msecs += tmp_usec;
	return msecs;
}

#endif
#endif


typedef struct RtmpContexStruct
{
	RTMP *pRtmp;
	DWORD64 StartTime;
	DWORD64 First_Iframe_Time;
	int reSend_sps_pps_flag;
	int first_recv_iframe_flag;
	int spslen;
	int ppsLen;
	char spsBuf[100];
	char ppsBuf[100];
	audio_consume_pt fun;
	int recv_audio_flag;
	int stop_audio_thread_flag;
	char rtmp_head[8];
	int audio_data_recv_status;
	int rtmp_head_len;
	int rtmp_body_size;
	int rtmp_body_len;
	char* body;
	char device_type;
	RTMPMetaData  metaData;
	char accessToken[TOKEN_SIZE];
	pthread_mutex_t  RtmpMutex;
} RtmpContex;

typedef struct tag_msginfo {
    unsigned int    peerid;			//�ͻ���PeerID
    unsigned int    session;		//�ͻ��˵�ǰSession
    unsigned short  client_type;		//�ͻ�������
    unsigned short  msg_cmd;		//��־����
    unsigned char   msg[64];		//��־����
}msginfo_t, *pmsginfo_t;



static RtmpContex* global_RtmpContex = NULL;
static char rtmp_url[256];
static int init_rtmp_contex_flag = 0;
extern platform_config_t platform_global_config;
char RTMP_Enable_AES128 =0x00;
unsigned int RTMP_C_BitRate = 0;
unsigned int RTMP_C_FrameRate = 0;


#define HTON16(x)  ((x>>8&0xff)|(x<<8&0xff00))
#define HTON24(x)  ((x>>16&0xff)|(x<<16&0xff0000)|x&0xff00)
#define HTON32(x)  ((x>>24&0xff)|(x>>8&0xff00)|(x<<8&0xff0000)|(x<<24&0xff000000))
#define HEX2BIN(a)      (((a)&0x40)?((a)&0xf)+9:((a)&0xf))

int hex2bin(char *str, char **hex)
{
	char *ptr;
	int i, l = strlen(str);
	if (l & 1)
		return 0;
	*hex = (char *)malloc(l/2);
	ptr = *hex;
	if (!ptr)
		return 0;
	for (i=0; i<l; i+=2)
		*ptr++ = (HEX2BIN(str[i]) << 4) | HEX2BIN(str[i+1]);
	return l/2;
}

char * put_byte( char *output, uint8_t nVal )
{
	output[0] = nVal;
	return output+1;
}
char * put_be16(char *output, uint16_t nVal )
{
	output[1] = nVal & 0xff;
	output[0] = nVal >> 8;
	return output+2;
}
char * put_be24(char *output,uint32_t nVal )
{
	output[2] = nVal & 0xff;
	output[1] = nVal >> 8;
	output[0] = nVal >> 16;
	return output+3;
}
char * put_be32(char *output, uint32_t nVal )
{
	output[3] = nVal & 0xff;
	output[2] = nVal >> 8;
	output[1] = nVal >> 16;
	output[0] = nVal >> 24;
	return output+4;
}
char *  put_be64( char *output, uint64_t nVal )
{
	output=put_be32( output, nVal >> 32 );
	output=put_be32( output, (uint32_t)nVal );
	return output;
}
char * put_amf_string( char *c, const char *str )
{
	uint16_t len = strlen( str );
	c=put_be16( c, len );
	memcpy(c,str,len);
	return c+len;
}
char * put_amf_double( char *c, double d )
{
	*c++ = AMF_NUMBER;	/* type: Number */
	{
		unsigned char *ci, *co;
		ci = (unsigned char *)&d;
		co = (unsigned char *)c;
		co[0] = ci[7];
		co[1] = ci[6];
		co[2] = ci[5];
		co[3] = ci[4];
		co[4] = ci[3];
		co[5] = ci[2];
		co[6] = ci[1];
		co[7] = ci[0];
	}
	return c+8;
}

void InitNet()
{
#ifdef WIN32
	WORD version;
	WSADATA wsaData;
	version=MAKEWORD(2,2);
	WSAStartup(version,&wsaData);
#endif
}


static void InitGlobalRtmpContex()
{
	if(init_rtmp_contex_flag == 0){
		global_RtmpContex = (RtmpContex*)calloc(1,sizeof(RtmpContex));
		global_RtmpContex->body = NULL;
		global_RtmpContex->pRtmp = NULL;
		pthread_mutex_init(&global_RtmpContex->RtmpMutex,NULL);
		init_rtmp_contex_flag = 1;
	}
}


static void sendUDP(char* ip,int port,char* data,int data_len)
{
	
	struct sockaddr_in addr;
	int sock;

	if ((sock=socket(AF_INET, SOCK_DGRAM, 0))<0)
	{
		return;
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);
	if (addr.sin_addr.s_addr == INADDR_NONE)
	{
		close(sock);
		return;
	}

    socklen_t len = sizeof(addr);
    sendto(sock, data, data_len, 0, (struct sockaddr *)&addr,len);
	close(sock);
}

static void send_msg(char* data)
{
	msginfo_t rtmp_msg;
	rtmp_msg.peerid = platform_global_config.cid;
	rtmp_msg.session = 0;
	rtmp_msg.client_type = 0x0002;
	rtmp_msg.msg_cmd = 0x0201;
	memset(rtmp_msg.msg,0,sizeof(rtmp_msg.msg));
	snprintf(rtmp_msg.msg,sizeof(rtmp_msg.msg)-1,"%s",data);
	sendUDP("120.26.74.53",80,(char*)&rtmp_msg,sizeof(rtmp_msg));
}

void Send_Log(const char *msg, int cmd)
{
        msginfo_t rtmp_msg;
	rtmp_msg.peerid = platform_global_config.cid;
        rtmp_msg.session = 0;
        rtmp_msg.client_type = 0x0001;
	if(cmd == (int)0x0301)
        	rtmp_msg.msg_cmd = 0x0301;
	else if(cmd == (int)0x0302)
        	rtmp_msg.msg_cmd = 0x0302;
        memset(rtmp_msg.msg,0,sizeof(rtmp_msg.msg));
        snprintf(rtmp_msg.msg,sizeof(rtmp_msg.msg)-1,"%s",msg);
        sendUDP("120.26.74.53",80,(char*)&rtmp_msg,sizeof(rtmp_msg));
}


void setToken(unsigned char* token)
{
	InitGlobalRtmpContex();
	pthread_mutex_lock(&global_RtmpContex->RtmpMutex);
	memset(global_RtmpContex->accessToken,0,sizeof(global_RtmpContex->accessToken));
	strncpy(global_RtmpContex->accessToken,token,sizeof(global_RtmpContex->accessToken)-1);
	pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
}

void setDeviceType(unsigned char type)
{
	InitGlobalRtmpContex();
	global_RtmpContex->device_type= type; 
}

void setMetaData(RTMPMetaData meta_data)
{
	InitGlobalRtmpContex();
	global_RtmpContex->metaData= meta_data; 
}

int getJPGServerIP(int fd)
{
        //RtmpContex *rCntx = GetRtmpContexWithFD(fd);
        RtmpContex *rCntx = global_RtmpContex;
	if(NULL == rCntx)
        {
                return -1;
        }
	pthread_mutex_lock(&rCntx->RtmpMutex);
        if(rCntx->pRtmp == NULL){
		pthread_mutex_unlock(&rCntx->RtmpMutex);
                return -1;
        }

        if(RTMP_IsConnected(rCntx->pRtmp)){
                RTMP_getServerIP(rCntx->pRtmp);
		pthread_mutex_unlock(&rCntx->RtmpMutex);
                return 0;
        }
	pthread_mutex_unlock(&rCntx->RtmpMutex);
        return -1;
}


int ReConnectToRtmpServer(RtmpContex* apRtmpContex,const char* aUrl)
{
	RTMP_Init(apRtmpContex->pRtmp);//��ʼ��rtmp����
	apRtmpContex->pRtmp->Link.timeout=5;//�������ӳ�ʱ����λ�룬Ĭ��30��
	apRtmpContex->pRtmp->device_type = apRtmpContex->device_type;
	strncpy(apRtmpContex->pRtmp->accessToken,apRtmpContex->accessToken,sizeof(apRtmpContex->pRtmp->accessToken)-1);
	apRtmpContex->pRtmp->metaData = apRtmpContex->metaData;

	RTMP_SetupURL(apRtmpContex->pRtmp, aUrl);//����url
	RTMP_EnableWrite(apRtmpContex->pRtmp);//���ÿ�д״̬
	if (!RTMP_Connect(apRtmpContex->pRtmp,NULL))
	{
		RTMP_Close(apRtmpContex->pRtmp);
		return -1;
	}
	if (!RTMP_ConnectStream(apRtmpContex->pRtmp,0)) 
	{
		RTMP_Close(apRtmpContex->pRtmp);
		return -1;
	}
	//printf("ReConnectToRtmpServer:%s Succ",aUrl);
	apRtmpContex->StartTime = Sys_MicroSeconds();
	return 0;
}


void setLogDir(char* log_dir)
{
	RTMP_Set_Log_Dir(log_dir);
}


pthread_t audio_recv_thread;
static int tcp_recv_noblock1(int fd, char* buffer, int len) {
	int ret = 0;
	char* p = buffer;
	int left = len;

	int flags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL,  flags| O_NONBLOCK);
	ret = recv(fd, p, left, 0);
	if(ret == -1){
		 if(errno == EAGAIN || errno == EWOULDBLOCK)
		 {
		 	fcntl(fd, F_SETFL,  flags);
		 	return 0;
		 }
		 else 
  	 	 {
  			return -1;
  		 }
	}
	else if(ret == 0){
		return -1;
	}
	else
	{
		fcntl(fd, F_SETFL,  flags);
		return ret;
	}
}


static void parseBodyAndType(char* buffer,int* body_size,char* type)
{
	//printf("%02x %02x %02x %02x %02x %02x %02x %02x \n",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5],buffer[6],buffer[7]);
	*body_size = 0;
	unsigned char* p_data = (unsigned char*)body_size;
	p_data[2] = buffer[4];
	p_data[1] = buffer[5];
	p_data[0] = buffer[6];
	*type = buffer[7];
}

/*

������Ƶ����״̬
0 ��ʼ״̬
1 ���յ�rtmpͷ��
2 ������Ƶ���ݣ�ֱ������
3 ���շ���Ƶ���ݣ�ֱ������
*/


static void reset_audio_thread_flag()
{
	global_RtmpContex->rtmp_head_len = 0;
	global_RtmpContex->rtmp_body_len = 0;
	global_RtmpContex->audio_data_recv_status = 0;
	if(global_RtmpContex->body)
	{
		free(global_RtmpContex->body);
		global_RtmpContex->body = NULL;
	}
}


void *recv_audio(void)
{
	while(!global_RtmpContex->stop_audio_thread_flag){
		//pthread_t tid = pthread_self();
		//printf("audio start ..........tid= %d\n",tid);
		pthread_mutex_lock(&global_RtmpContex->RtmpMutex);

		if(global_RtmpContex->pRtmp == NULL){
			pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
			sleep(1);
			continue;
		}
		if(!RTMP_IsConnected(global_RtmpContex->pRtmp)){
			pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
			sleep(1);
			continue;
		}
		pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);

		#if 0
		char buffer[1024];
		pthread_mutex_lock(&pRtmpContex->RtmpMutex);
		int nRead = tcp_recv_noblock(pRtmpContex->pRtmp->m_sb.sb_socket,buffer,1024);
		pthread_mutex_unlock(&pRtmpContex->RtmpMutex);
		printf("lock nRead:%d\n",nRead);
		if(nRead == 0){
			usleep(40000);
			printf("no audio data...........\n");
			continue;
		}
		int i;
		for(i=0;i<nRead;i++){
			printf("%02x ",buffer[i]);
		}
		printf("\n");
		usleep(40000);
		continue;
		#endif
		//printf("======= begain =========\n");	
	
		if(global_RtmpContex->audio_data_recv_status == 0){
			pthread_mutex_lock(&global_RtmpContex->RtmpMutex);
			if(global_RtmpContex->pRtmp == NULL){
				reset_audio_thread_flag();
				pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
				continue;
			}
			int nRead = tcp_recv_noblock1(global_RtmpContex->pRtmp->m_sb.sb_socket,global_RtmpContex->rtmp_head+global_RtmpContex->rtmp_head_len,8-global_RtmpContex->rtmp_head_len);
			pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
			if(nRead == -1)
			{
				reset_audio_thread_flag();
				continue;
			}

			if(nRead == 0){
				usleep(40000);
				continue;
			}
			
			global_RtmpContex->rtmp_head_len += nRead;
			if(global_RtmpContex->rtmp_head_len == 8){
				global_RtmpContex->audio_data_recv_status = 1;
				global_RtmpContex->rtmp_head_len = 0;
			}

			
		}

	
		if(global_RtmpContex->audio_data_recv_status == 1){

			int body_size;
			char type;
			parseBodyAndType(global_RtmpContex->rtmp_head,&body_size,&type);

			//�����쳣������Ϊ��Ƶ�ĳ��Ȳ�̫���ܴ���30KB���������쳣�����˴���ڴ�ʧ�ܵ��³������
			if(body_size > 30*1024){
				body_size = 30*1024;
			}
			
			if(type != 8)
			{
				body_size +=4;
				global_RtmpContex->audio_data_recv_status = 3;
			}
			else
				global_RtmpContex->audio_data_recv_status = 2;

			global_RtmpContex->rtmp_body_size = body_size;
			if(global_RtmpContex->body == NULL){
				global_RtmpContex->body = (char*)calloc(1,global_RtmpContex->rtmp_body_size);
			}
			//printf("111111111111 type:%d, body_size:%d\n",type,body_size);
		}


		if(global_RtmpContex->audio_data_recv_status == 2){
			pthread_mutex_lock(&global_RtmpContex->RtmpMutex);
			if(global_RtmpContex->pRtmp == NULL){
				reset_audio_thread_flag();
				pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
				continue;
			}
			int nRead = tcp_recv_noblock1(global_RtmpContex->pRtmp->m_sb.sb_socket,global_RtmpContex->body+global_RtmpContex->rtmp_body_len,global_RtmpContex->rtmp_body_size-global_RtmpContex->rtmp_body_len);
			//printf("222222 read:%d,pRtmpContex->rtmp_body_len:%d pRtmpContex->rtmp_body_size:%d \n",nRead,global_RtmpContex->rtmp_body_len,global_RtmpContex->rtmp_body_size);
			pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
			if(nRead == -1)
			{
				reset_audio_thread_flag();
				continue;
			}

			if(nRead == 0){
				usleep(40000);
				continue;
			}
			
			global_RtmpContex->rtmp_body_len += nRead;

			//printf("222222222 rtmp_body_len:%d,rtmp_body_size:%d\n",global_RtmpContex->rtmp_body_len,global_RtmpContex->rtmp_body_size);
			if(global_RtmpContex->rtmp_body_len == global_RtmpContex->rtmp_body_size){
				if(global_RtmpContex->fun){
					global_RtmpContex->fun(1,global_RtmpContex->body,global_RtmpContex->rtmp_body_size);
				}
				reset_audio_thread_flag();
			}

			
		}

		if(global_RtmpContex->audio_data_recv_status == 3){
			//printf(" 333333333 status ======= 3\n");
			pthread_mutex_lock(&global_RtmpContex->RtmpMutex);
			if(global_RtmpContex->pRtmp == NULL){
				reset_audio_thread_flag();
				pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
				continue;
			}
			int nRead = tcp_recv_noblock1(global_RtmpContex->pRtmp->m_sb.sb_socket,global_RtmpContex->body+global_RtmpContex->rtmp_body_len,global_RtmpContex->rtmp_body_size-global_RtmpContex->rtmp_body_len);
			pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
			if(nRead == -1)
			{
				reset_audio_thread_flag();
				continue;
			}

			if(nRead == 0){
				usleep(40000);
				continue;
			}
			
			global_RtmpContex->rtmp_body_len += nRead;
			if(global_RtmpContex->rtmp_body_len == global_RtmpContex->rtmp_body_size){
				if(global_RtmpContex->fun){
					if(global_RtmpContex->rtmp_body_size > 6)
						if(*(global_RtmpContex->body+4) == 0x00 && *(global_RtmpContex->body+5) == 0x29)        //disk info
							global_RtmpContex->fun(2,global_RtmpContex->body+6,global_RtmpContex->rtmp_body_size-6);
						else if(*(global_RtmpContex->body+4) == 0x00 && *(global_RtmpContex->body+5) == 0x47)   //jpeg server addr
							global_RtmpContex->fun(3,global_RtmpContex->body+6,global_RtmpContex->rtmp_body_size-6);
							
				}
				reset_audio_thread_flag();
			}

			
		}
		
	}

	pthread_exit(0);
	return NULL;
}


int sendGetDiskListCommand()
{
	pthread_mutex_lock(&global_RtmpContex->RtmpMutex);
	if(global_RtmpContex->pRtmp == NULL){
		pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
		return -1;
	}

	if(RTMP_IsConnected(global_RtmpContex->pRtmp)){
		RTMP_getDiskList(global_RtmpContex->pRtmp);
		pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
		return 0;
	}

	pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
	return -1;
}


int ConnectToRtmpServer(const char* aUrl,audio_consume_pt fun,int recv_audio_flag)
{
	RTMP_LogLevel lvl=RTMP_LOGDEBUG;

	InitGlobalRtmpContex();
	
	memset(rtmp_url,0,sizeof(rtmp_url));
	global_RtmpContex->fun = fun;
	global_RtmpContex->recv_audio_flag = recv_audio_flag;
	global_RtmpContex->first_recv_iframe_flag= 1;
	global_RtmpContex->reSend_sps_pps_flag= 0;
	global_RtmpContex->First_Iframe_Time = 0;
	global_RtmpContex->stop_audio_thread_flag = 0;
	global_RtmpContex->audio_data_recv_status = 0;
	global_RtmpContex->rtmp_head_len= 0;
	global_RtmpContex->rtmp_body_size = 0;
	global_RtmpContex->rtmp_body_len = 0;
	if(global_RtmpContex->body != NULL){
		free(global_RtmpContex->body);
		global_RtmpContex->body = NULL;
	}
	strncpy(rtmp_url,aUrl,sizeof(rtmp_url)-1);
	
	InitNet();
	RTMP_LogSetLevel(lvl);//������Ϣ�ȼ�

	if(global_RtmpContex->pRtmp != NULL){
		RTMP_Close(global_RtmpContex->pRtmp);
		RTMP_Free(global_RtmpContex->pRtmp);
		global_RtmpContex->pRtmp = NULL;
	}
	global_RtmpContex->pRtmp=RTMP_Alloc();//����rtmp�ռ�
	RTMP_Init(global_RtmpContex->pRtmp);//��ʼ��rtmp����
	global_RtmpContex->pRtmp->Link.timeout=5;//�������ӳ�ʱ����λ�룬Ĭ��30��
	global_RtmpContex->pRtmp->device_type = global_RtmpContex->device_type;

	pthread_mutex_lock(&global_RtmpContex->RtmpMutex);
	strncpy(global_RtmpContex->pRtmp->accessToken,global_RtmpContex->accessToken,sizeof(global_RtmpContex->pRtmp->accessToken)-1);
	global_RtmpContex->pRtmp->metaData = global_RtmpContex->metaData;
	pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
	
	//modify by suwei
	//int connect_count = 3600;
	int connect_count = 6;
	int i=0;
	char msg_buffer[64]={0};
	memset(msg_buffer,0,sizeof(msg_buffer));
	snprintf(msg_buffer,sizeof(msg_buffer)-1,"cn url:%s",aUrl);
	send_msg(msg_buffer);

	while(i<connect_count){
		//printf("ConnectToRtmpServer bengin ====================\n");
		RTMP_SetupURL(global_RtmpContex->pRtmp, aUrl);//����url
		RTMP_EnableWrite(global_RtmpContex->pRtmp);//���ÿ�д״̬

		//printf("RTMP_Connect bengin ====================  retry num:%d,retry count:%d\n",i,connect_count);
		if (!RTMP_Connect(global_RtmpContex->pRtmp,NULL))
		{
			RTMP_Close(global_RtmpContex->pRtmp);
			i++;
			sleep(1);
			//printf("RTMP_Connect failed, close socket,url:%s ======================\n",aUrl);
			continue;
		}
		
		//printf("RTMP_ConnectStream bengin ====================\n");
		if (!RTMP_ConnectStream(global_RtmpContex->pRtmp,0)) 
		{
			RTMP_Close(global_RtmpContex->pRtmp);
			i++;
			sleep(1);
			//printf("RTMP_ConnectStream failed,close socket,url:%s ================\n",aUrl);
			continue;
		}
		break;
	}

	if(i>=connect_count){
		//char msg_buffer[64]={0};
		memset(msg_buffer,0,sizeof(msg_buffer));
		snprintf(msg_buffer,sizeof(msg_buffer)-1,"fc %s,local:%s failed",global_RtmpContex->pRtmp->server_ip,global_RtmpContex->pRtmp->local_ip);
		send_msg(msg_buffer);
		return -1;
	}

	printf("ConnectToRtmpServer:%s Succ\n",aUrl);
	global_RtmpContex->StartTime = Sys_MicroSeconds();

	if(global_RtmpContex->recv_audio_flag){
		int ret = pthread_create(&audio_recv_thread, NULL, (void *)recv_audio, NULL);
   		if(ret != 0) 
   		{
			send_msg("audio recv thread create failed");
   		}          
  
	}

	//printf("rtmp  first connect \n");
	//char msg_buffer[64]={0};
	memset(msg_buffer,0,sizeof(msg_buffer));
	snprintf(msg_buffer,sizeof(msg_buffer)-1,"fc %s,local:%s success",global_RtmpContex->pRtmp->server_ip,global_RtmpContex->pRtmp->local_ip);
	send_msg(msg_buffer);
	return 0;
	//end modify by suwei

	#if 0
	RTMP_EnableWrite(pRtmpContex->pRtmp);//���ÿ�д״̬
	if (!RTMP_Connect(pRtmpContex->pRtmp,NULL))
	{
		free(pRtmpContex);
		return NULL;
	}
	if (!RTMP_ConnectStream(pRtmpContex->pRtmp,0)) 
	{
		free(pRtmpContex);
		return NULL;
	}
	printf("ConnectToRtmpServer:%s Succ",aUrl);
	pRtmpContex->StartTime = Sys_GetTickCount();
	return pRtmpContex;
	#endif
}

void DisconnectRtmpServer()
{
	global_RtmpContex->stop_audio_thread_flag = 1;
	pthread_mutex_lock(&global_RtmpContex->RtmpMutex);
	if(global_RtmpContex->pRtmp != NULL){
		RTMP_Close(global_RtmpContex->pRtmp);
		RTMP_Free(global_RtmpContex->pRtmp);
		global_RtmpContex->pRtmp = NULL;
		printf("DisconnectRtmpServer ---------------- 11111\n");
		pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
		int r = pthread_cancel(audio_recv_thread);
		printf("pthread_cancel: %d\n", r);
		pthread_join(audio_recv_thread,0);
		printf("DisconnectRtmpServer ---------------- 222222\n");
		send_msg("DisconnectRtmpServer");
		printf("DisconnectRtmpServer ---------------- 333333\n");
	} else
	pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
}


static int SendSpsAndPpsPacket(RtmpContex* apRtmpContex,const char* aBodyBuffer, int aBodyBufferLength, int aType, unsigned int aTimeStamp)
{
	RTMPPacket packet;//������
	RTMPPacket_Reset(&packet);//����packet״̬
	RTMPPacket_Alloc(&packet,aBodyBufferLength+1);//��packet�������ݿռ�
	packet.m_packetType = aType;
	packet.m_nBodySize = aBodyBufferLength;
	packet.m_nTimeStamp = aTimeStamp;
	packet.m_nChannel = 0x04; //ͨ��
	packet.m_headerType = RTMP_PACKET_SIZE_LARGE; 
	packet.m_nInfoField2 = apRtmpContex->pRtmp->m_stream_id;
	memcpy(packet.m_body, aBodyBuffer, aBodyBufferLength);
	RTMP_SendPacket(apRtmpContex->pRtmp,&packet,0);
	RTMPPacket_Free(&packet);
	return 0;
}

static int ReSendSPSPPS(RtmpContex* apRtmpContex,unsigned int aTimeStamp)
{
	int buflen;
	char* buf;
	buflen = apRtmpContex->spslen + apRtmpContex->ppsLen + 16;
	buf = (char*)malloc(buflen);
	buf[0] = 0x17;
	buf[1] = 0x00;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0x00;
	buf[5] = 0x01;
	buf[6] = apRtmpContex->spsBuf[1];
	buf[7] = apRtmpContex->spsBuf[2];
	buf[8] = apRtmpContex->spsBuf[3];
	buf[9] = 0x03;
	buf[10] = 0xe1;
	put_be16(buf+11,apRtmpContex->spslen);
	memcpy(buf+13,apRtmpContex->spsBuf,apRtmpContex->spslen);
	buf[13+apRtmpContex->spslen] = 0x01;
	put_be16(buf+13+apRtmpContex->spslen+1,apRtmpContex->ppsLen);
	memcpy(buf+13+apRtmpContex->spslen+1+2,apRtmpContex->ppsBuf,apRtmpContex->ppsLen);
	SendSpsAndPpsPacket(apRtmpContex, buf, buflen, 9, aTimeStamp);	
	free(buf);
	return 0;
}



//static int SendRtmpPacket(RtmpContex* apRtmpContex,const char* aBodyBuffer, int aBodyBufferLength, int aType, unsigned int aTimeStamp,int frame_type)
static int SendRtmpPacket(RtmpContex* apRtmpContex,const char* aBodyBuffer, int aBodyBufferLength, int aType, DWORD64 aTimeStamp,int frame_type)
{
	int nRet = -1;
	if(!RTMP_IsConnected(apRtmpContex->pRtmp)){
		if(ReConnectToRtmpServer(apRtmpContex,(const char *)rtmp_url) !=0)
		{
			char msg_buffer[64]={0};
			snprintf(msg_buffer,sizeof(msg_buffer)-1,"rc %s,local:%s failed",global_RtmpContex->pRtmp->server_ip,global_RtmpContex->pRtmp->local_ip);
			send_msg(msg_buffer);
			return 2;	//network status
		}
		else
		{
			char msg_buffer[64]={0};
			snprintf(msg_buffer,sizeof(msg_buffer)-1,"rc %s,local:%s success",global_RtmpContex->pRtmp->server_ip,global_RtmpContex->pRtmp->local_ip);
			send_msg(msg_buffer);
		}
		
		global_RtmpContex->reSend_sps_pps_flag= 1;
	}

	//make sure first frame is IFrame
	if(global_RtmpContex->First_Iframe_Time == 0){
		printf("rtmp send First_Iframe_Time == 0 \n");
		return -1;
	}

	//discard too old frame 
	if(aTimeStamp < global_RtmpContex->StartTime){
		if((global_RtmpContex->StartTime-aTimeStamp) >= 2000*1000)
		{
			char msg[64]={0};
			sprintf(msg,"Ts - Tc : %u",(global_RtmpContex->StartTime-aTimeStamp)/1000);
			//printf("discard old frame first time:%llu, absolute time:%llu, start time:%llu, info:%s\n",
			//	global_RtmpContex->First_Iframe_Time,aTimeStamp,global_RtmpContex->StartTime,msg);
			//send_msg(msg);
			return -1;
		}
	}

	unsigned int curTimestamp = (aTimeStamp - global_RtmpContex->First_Iframe_Time)/1000;
	curTimestamp = curTimestamp%0xFFFFFE;
	if(global_RtmpContex->reSend_sps_pps_flag)
	{
		//when reconnect,make sure fisrt frame is IFrame
		if(frame_type != 2)
		{
			//printf("send rtmp frame_type != 2 \n");
			return -1;
		}	

		global_RtmpContex->reSend_sps_pps_flag = 0;	
		printf("reconnect success ,resend sps pps curTimestamp:%u\n",curTimestamp);
		nRet = ReSendSPSPPS(apRtmpContex,curTimestamp);
		char msg_buffer[64]={0};
		snprintf(msg_buffer,sizeof(msg_buffer)-1,"rc tm:%llu st:%llu %lu",aTimeStamp,global_RtmpContex->StartTime,curTimestamp);
		send_msg(msg_buffer);
	}
	else
	{
		//send sps before send IFrame
		if(frame_type == 2)
			ReSendSPSPPS(apRtmpContex,curTimestamp);
	}


	//printf("first time:%llu, absolute time:%llu, start time:%llu,relative time:%u, type:%d, len:%d\n",
	//	global_RtmpContex->First_Iframe_Time,aTimeStamp,global_RtmpContex->StartTime,curTimestamp,frame_type,aBodyBufferLength);

	RTMPPacket packet;//������
	RTMPPacket_Reset(&packet);//����packet״̬
	RTMPPacket_Alloc(&packet,aBodyBufferLength+1);//��packet�������ݿռ�
	packet.m_packetType = aType;
	packet.m_nBodySize = aBodyBufferLength;
	packet.m_nTimeStamp = curTimestamp;
	packet.m_nChannel = 0x04; //ͨ��
	packet.m_headerType = RTMP_PACKET_SIZE_LARGE; 
	packet.m_nInfoField2 = apRtmpContex->pRtmp->m_stream_id;
	memcpy(packet.m_body, aBodyBuffer, aBodyBufferLength);
	if(RTMP_IsConnected(apRtmpContex->pRtmp)) {
		int ret = RTMP_SendPacket(apRtmpContex->pRtmp,&packet,0);
		if(ret == 0){
			RTMP_Close(apRtmpContex->pRtmp);
			RTMP_Log(RTMP_LOGINFO, "RTMP_SendPacket failed");
			char msg_buffer[64]={0};
			snprintf(msg_buffer,sizeof(msg_buffer)-1,"send %s,local:%s failed",global_RtmpContex->pRtmp->server_ip,global_RtmpContex->pRtmp->local_ip);
			send_msg(msg_buffer);
			nRet = 2;		//network status
		}
		else
		{
			
			nRet = 0;
		}
	}
	else
		nRet = 2;		//network status
	
	RTMPPacket_Free(&packet);
	return nRet;
}

//int SendNal(const char *aNalBuf, DWORD aNalBufLen,DWORD time)
int SendNal(const char *aNalBuf, DWORD aNalBufLen,DWORD64 time)
{
	int nRet = -1;
	char frame_type = aNalBuf[0] & 0x1f;
	//printf("send nal type === %d\n",frame_type);
	if(frame_type==6) //SEI
	{
	}
	else if(frame_type==7)//SPS
	{
		global_RtmpContex->spslen = aNalBufLen;
		memcpy(global_RtmpContex->spsBuf, aNalBuf,global_RtmpContex->spslen);
		nRet = 0;
	}
	else if(frame_type==8)//PPS
	{
		global_RtmpContex->ppsLen = aNalBufLen;
		memcpy(global_RtmpContex->ppsBuf, aNalBuf, global_RtmpContex->ppsLen);
		nRet = 0;
	}
	else
	{
		
		int buflen;
		if(frame_type == 5)
			buflen = aNalBufLen+18;
		else
			buflen = aNalBufLen+9;
		pthread_mutex_lock(&global_RtmpContex->RtmpMutex);
		if(global_RtmpContex->pRtmp == NULL){
			pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
			return -1;
		}
		char* buf = (char*)malloc(buflen);
		if(frame_type==5)
		{
			//printf("...aes128:%d, frame rate:%d, bitrate kb:%d\n",RTMP_Enable_AES128,RTMP_C_FrameRate,RTMP_C_BitRate);
			buf[0]=0x17;
			buf[1]=0x01;
			buf[2]=0x00;
			buf[3]=0x00;
			buf[4]=0x00;

			buf[5]=0x00;
			buf[6]=0x00;
			buf[7]=0x00;
			buf[8]=0x05;
		
			buf[9]=0x06;
			buf[10]=RTMP_Enable_AES128;
			buf[11]=RTMP_C_FrameRate&0xFF;
			buf[12]=RTMP_C_BitRate&0XFF;
			buf[13]=(RTMP_C_BitRate >> 8)&0xFF;
			put_be32((char *)buf+14,aNalBufLen);
			memcpy(buf+18,aNalBuf,aNalBufLen);		//����ǰ׺��Ϣ������)

			//printf("...rtmp aes:%x, frame rate:%x, bit low:%x, hight:%x\n",buf[10],buf[11],buf[12],buf[13]);
		}
		else
		{
			buf[0]=0x27;
			buf[1]=0x01;
			buf[2]=0x00;
			buf[3]=0x00;
			buf[4]=0x00;
			put_be32((char *)buf+5,aNalBufLen);
			memcpy(buf+9,aNalBuf,aNalBufLen);		//����ǰ׺��Ϣ������)
		}
		
		if(frame_type==5){
			if(global_RtmpContex->first_recv_iframe_flag)
			{
				global_RtmpContex->First_Iframe_Time = time;	
				global_RtmpContex->first_recv_iframe_flag = 0;	
			}
			nRet = SendRtmpPacket(global_RtmpContex,buf, buflen, 9, time,2);		//Iframe
		}
		else
			nRet = SendRtmpPacket(global_RtmpContex,buf, buflen, 9, time,3);		//Pframe
		
		free(buf);
		pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
	}
	return nRet;
}

//int SendAacInfo(const char *aAacInfoBuf, DWORD aAacInfoBufLen,DWORD time)
int SendAacInfo(const char *aAacInfoBuf, DWORD aAacInfoBufLen,DWORD64 time)
{
	int nRet = -1;
	char* buf = (char*)malloc(aAacInfoBufLen+2);
	pthread_mutex_lock(&global_RtmpContex->RtmpMutex);
	if(global_RtmpContex->pRtmp == NULL){
		pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
		return -1;
	}
	buf[0] = 0xaf;
	buf[1] = 0x00;
	memcpy(buf+2,aAacInfoBuf,aAacInfoBufLen);
	nRet = SendRtmpPacket(global_RtmpContex,buf, aAacInfoBufLen+2, 8,time,4);     //aac info type is 4
	free(buf);
	pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
	return nRet;
}


//int SendAAC(const char *aAacBuf, DWORD aAacBufLen,DWORD time)
int SendAAC(const char *aAacBuf, DWORD aAacBufLen,DWORD64 time)
{
	int nRet = -1;
	char* buf = (char*)malloc(aAacBufLen+2);
	pthread_mutex_lock(&global_RtmpContex->RtmpMutex);
	if(global_RtmpContex->pRtmp == NULL){
		pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
		return -1;
	}
	buf[0] = 0xaf;
	buf[1] = 0x01;
	memcpy(buf+2,aAacBuf,aAacBufLen);
	nRet = SendRtmpPacket(global_RtmpContex,buf, aAacBufLen+2, 8,time,5);
	free(buf);
	pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
	return nRet;
}

//int SendOpus(const char *aOpusBuf, DWORD aOpusBufLen,DWORD time)
int SendOpus(const char *aOpusBuf, DWORD aOpusBufLen,DWORD64 time)
{
	int nRet = -1;
    	char* buf = (char*)malloc(aOpusBufLen+1);
    	pthread_mutex_lock(&global_RtmpContex->RtmpMutex);
	if(global_RtmpContex->pRtmp == NULL){
		pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
		return -1;
	}
	buf[0] = 0xff;        
	memcpy(buf+1,aOpusBuf,aOpusBufLen);
    	nRet = SendRtmpPacket(global_RtmpContex,buf, aOpusBufLen+1, 8,time,5);
	free(buf);
    	pthread_mutex_unlock(&global_RtmpContex->RtmpMutex);
    	return nRet;
}

