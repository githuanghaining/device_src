//#include "CloudOpenAPI.h"
//#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>
#include "rtmpSender.h"
#include <curl/curl.h>
#include "PusherClient.h"
#include "camera_log.h"
#include "Hash_alg.h"
#include "aes128.h"
#include <openssl/aes.h>
#include "cJSON.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "base64.h"
#include "platform_cfg.h"
#include "platform_err.h"

//#define ENABLE_SSL

#ifdef ENABLE_SSL
#define USE_SSL 1
#else
#define USE_SSL 0
#endif

#define DEVICE_TOKEN_SIZE 128

#define DEVICE_APPID_LEN	4
#define DEVICE_SN_LEN	16
#define DEVICE_CID_LEN	16


#define LOG_MSG_SIZE		64
#define LOG_TYPE_DEVICE		0x0301
#define LOG_TYPE_SENDTIME	0x0302

#define RTMP_TYPE_AUDIO_DATA	1
#define RTMP_TYPE_DISK_INFO	2
#define RTMP_TYPE_IMAGE_ADDR	3


#define MAX_MESSAGE_SIZE 256
#define MAX_MESSAGE_B64_BUFFER B64_ENCODE_SIZE(MAX_MESSAGE_SIZE)

typedef enum {
		UDP_P2P_CONNECTION_TYPE		= 0, //
		RTMP_PUBLICLIVE_TYPE     	= 2,
		RTMP_STORAGE_TYPE	     	= 3,
		RTMP_PUBLIC_STORAGE_TYPE      	= 4
}DevConnectionTypeEm;

typedef enum{
		IMAGE_STORAGE_TYPE		=1,
		IMAGE_COVER_TYPE		=2,
		IMAGE_ALARM_TYPE		=3
}ImageTypeEm;

typedef struct rtmp_time
{
		unsigned long  Tstart;
		unsigned long  Tbegain;
		unsigned long  T1;
		unsigned long  Tend;
		unsigned long  Tn_T1;
		unsigned long  Tstart_end;
		unsigned long  Tend_start;
}rtmp_time_t;

rtmp_time_t rtmp_send_time;

typedef void (*RtmpDataCallBack)(void *apData,char* aData,int aDataLen ,char aDataType);

int  HttpPostRTMPURL();
int  HttpRemoveRTMPURL();
float GetPlatformVersion();
int  Disconnect();
int GetDeviceToken(char *aTokenBuffer, unsigned int aBufferLength);
void GetOneSecond_Upload_Count();
int  RespondConfigMsg(int aRespondCode);

//static pthread_mutex_t s_mutex_token = PTHREAD_MUTEX_INITIALIZER;

static int log_flag =0;
static int retry_count =0;
unsigned char aacSeqHeader[2]={0};
long LYRecording_Timestamp = 0;
volatile int rtmpopenflag = 0;
volatile int s_start_cloud_flag = 0;
volatile int LY_PublicLiveFlag = 0;
volatile unsigned long long LY_AlarmStartTime =0;
volatile unsigned long long LY_StartConnectTime =0;
volatile int SDK_ConnectType = -1;
volatile int SDK_PopConfig_flag = 0;
volatile int SDK_Status = 0;

unsigned long C_StartTime = 0;
unsigned int C_FrameRate;
unsigned long C_BitRate;

unsigned long long TLastFrameTime = 0;
unsigned long long TCurFrameTime = 0;
unsigned long long TsysLastTime = 0;
unsigned long long TFrameSendingTime = 0;
unsigned long long TFrameStartTime = 0;

extern char RTMP_Enable_AES128;
extern unsigned int RTMP_C_FrameRate;
extern unsigned int RTMP_C_BitRate;
volatile int RTMP_Upload = 0;

pthread_mutex_t sdk_mutex = PTHREAD_MUTEX_INITIALIZER; /*初始化互斥锁*/
pthread_cond_t sdk_cond = PTHREAD_COND_INITIALIZER;  //初始化条件变量 
static int working = 0;
pthread_t worker_pid;
sem_t sdk_sem;


const char *CenterWebServerAddr = "api.topvdn.com";
const int CenterWebServerPort = 80;
const char *PublicTransferServerAddr = "public.topvdn.cn:1935/live/";

platform_config_t platform_global_config;


static void set_defalut_globle_value()
{
		retry_count = 0;
		C_StartTime = 0;
		C_FrameRate = 0;
		C_BitRate = 0;
		RTMP_C_FrameRate = 0;
		RTMP_C_BitRate = 0;
		LY_AlarmStartTime = 0;	

		rtmp_send_time.Tbegain= 0;
		rtmp_send_time.Tstart= 0;
		rtmp_send_time.T1= 0;
		rtmp_send_time.Tend = 0;
		rtmp_send_time.Tn_T1 = 0;
		rtmp_send_time.Tstart_end = 0;
		rtmp_send_time.Tend_start = 0;
}

void SendLogMessage(const char *msg)
{
		Send_Log(msg,LOG_TYPE_DEVICE);
}

int Get_Device_Meminfo(char *msg)
{
		//        char msg[40]={0};
		char data[30]={0};
		char key[10]={0};
		char value[10]={0};

		int i =4;
		int ret = 0;
		FILE *file;
		file = fopen("/proc/meminfo","r");
		if(file == NULL)
		{
				Send_Log("fopen meminfo failed!",LOG_TYPE_DEVICE);
				return -1;
		}

		while(i--)
		{
				if(fgets(data,30,file) != NULL)
				{
						ret = sscanf(data,"%s%s[^\n]",key,value);
						if(ret !=2){
								memset(data,0,sizeof(data));
								memset(key,0,sizeof(key));
								memset(value,0,sizeof(value));
								Send_Log("fgets Mem return no data !",LOG_TYPE_DEVICE);
								continue;
						}
#if 1
						if(strcmp(key,"MemTotal:") == 0){
								strcat(msg,"Mt:");
								strncat(msg,value,6);
						}else if(strcmp(key,"MemFree:") == 0){
								strcat(msg,",Mf:");
								strncat(msg,value,5);
						}else if(strcmp(key,"Buffers:") == 0){
								strcat(msg,",Bf:");
								strncat(msg,value,5);
						}else if(strcmp(key,"Cached:") == 0){
								strcat(msg,",Ch:");
								strncat(msg,value,5);
						}
#endif
				}
				else
						Send_Log("fgets data==== null!",LOG_TYPE_DEVICE);
		}

		if(file)
		{
				fclose(file);
				file = NULL;	
		}

		return 0;
}

int Get_Allfd(int pid)
{
		DIR * pdir;
		struct dirent * pdirent;  
		//	struct stat f_ftime;   
		int fcnt;/*文件数目统计*/
		char path[25]={0};
		sprintf(path,"/proc/%d/fd/",pid);  
		pdir=opendir(path);  
		if(pdir==NULL)  
		{
				strcat(path," failed!"); 
				Send_Log(path,LOG_TYPE_DEVICE);
				return 0; 
		} 
		fcnt=0; 
		for(pdirent=readdir(pdir);pdirent!=NULL;pdirent=readdir(pdir))
		{   
				if(strcmp(pdirent->d_name,".")==0||strcmp(pdirent->d_name,"..")==0) 
						continue; 
				//if(stat(pdirent->d_name,&f_ftime)!=0) 
				//	return 0;    
				//if(S_ISDIR(f_ftime.st_mode)) 
				//	continue; /*子目录跳过*/  
				fcnt++;  
				//printf("name:%s\n",pdirent->d_name); 
		} 
		//printf("all:%d\n",fcnt);
		closedir(pdir);  
		pdir = NULL;
		pdirent = NULL;

		return fcnt;
}


void *Msg_Handler(void *arg)
{
		//sleep(70);
		char msg[64]={0};
		float version = GetPlatformVersion();
		sprintf(msg,"StartCloudService Version:%.2f",version);
		Send_Log(msg,LOG_TYPE_DEVICE);
		Send_Log((char *)arg,LOG_TYPE_DEVICE);
		log_flag = 1;
		char pid_fp[20];
		int pid = getpid();
		int fpcnt =0, i=0;
		while(log_flag)
		{
				if(rtmpopenflag == 1)
				{
						GetOneSecond_Upload_Count();
				}
				if((i >= 60) || (i == 0))
				{
						i = 0;

						fpcnt = Get_Allfd(pid);
						memset(msg,0,sizeof(msg));
						if(Get_Device_Meminfo(msg) == 0)
						{
								sprintf(pid_fp,",pid:%d,fd:%d",pid,fpcnt);
								strcat(msg,pid_fp);
								Send_Log((const char *)msg,LOG_TYPE_DEVICE);
						}
						//reflash rtmp token
						if(rtmpopenflag == 1)
						{
								char token[DEVICE_TOKEN_SIZE] = {0};
								int token_len = GetDeviceToken(token, sizeof(token));
								if (token_len != -1)
								{
										setToken(token);
								}
						}
				}
				i++;
				sleep(1);
		}

		Send_Log("log msg_pthread exit!",LOG_TYPE_DEVICE);
		//pthread_exit(0);
		return NULL;
}

pthread_t log_tid;
void Create_log_pthread(const char *SN,const int aCid)
{
		static char log[60]={0};
		sprintf(log,"dev sn:%s,cid:%d",SN,aCid);
		//Send_Log(log,0x0301);

		if(log_flag == 0)
		{
				int err;
				//pthread_t tid;
				//pthread_attr_t attr_handle;
				//pthread_attr_init(&attr_handle);
				//pthread_attr_setdetachstate(&attr_handle, PTHREAD_CREATE_DETACHED);
				//err = pthread_create(&tid,&attr_handle,Msg_Handler,NULL);
				err = pthread_create(&log_tid,NULL,Msg_Handler,(void *)log);
				if(err)
				{
						memset(log,0,sizeof(log));
						sprintf("sn:%s,cid:%d,create log pthread failed",SN,aCid);
						Send_Log(log,LOG_TYPE_DEVICE);
						return;
				}

		}
}


static int resolv_name(const char* aHostName, char *apHostip)
{
		struct hostent *host = NULL;
		int retry = 3;
		while (retry--)
		{	
				host = gethostbyname(aHostName);
				if (host) {
						strcpy(apHostip, inet_ntoa(*(struct in_addr*)(host->h_addr_list[0])));
						//printf("resolved web server ip: %s\n", apHostip);
						return 0;
				}
				if (h_errno != TRY_AGAIN) {
						break;
				}
				sleep(1);
		}
		return -1;
}

static void set_defalut_platform_config(const char *aServerAddr)
{
		strcpy(platform_global_config.web_server_ip,aServerAddr);
#ifdef ENABLE_SSL
		platform_global_config.web_server_port = 443;
#else
		platform_global_config.web_server_port = 80;
#endif
		//platform_global_config.web_server_timeout = 5;
		platform_global_config.web_server_timeout = 10;

		strcpy(platform_global_config.rtmp_log_dir,"/media/mmcblk0p1/");
		platform_global_config.rtmp_fun[0] = NULL;
		platform_global_config.rtmp_fun[1] = NULL;
		//strcpy(platform_global_config.rtmp_record_imgAddr,"api.topvdn.com:80");
		platform_global_config.rtmp_record_imgAddr[0] = 0;
		platform_global_config.rtmp_record_imgPort = 0;
		platform_global_config.rtmp_url[0] = 0;
		//strcpy(config->rtmp_url,"rtmp://120.24.88.82/live/999999");

		platform_global_config.cid = 0;
		platform_global_config.hashid[0] = 0;
}

int LastErrorNo(int aErrno, int aIsSet)
{
		static __thread int err = -1;
		if (aIsSet)
				err = aErrno;

		return err;
}


static MessageCallBack messageCallback[2] = {NULL}; 
static char ConfigMessage[1024]={0};

int PopMessageCallBack(void *apData, const char *aMessage)
{
		//	pthread_mutex_lock(&sdk_mutex);
		memset(ConfigMessage,0,sizeof(ConfigMessage));
		memcpy(ConfigMessage,aMessage,strlen(aMessage));
		sem_post(&sdk_sem);
		//	pthread_cond_signal(&sdk_cond);
		//	pthread_mutex_unlock(&sdk_mutex);

		//printf("========= PopMessageCallBack ==========\n");
		return  0;
}


void *PopMsgCallBackHandler(void *arg)
{
		int ret = 0,i=0;
		while(1)
		{
				//pthread_mutex_lock(&sdk_mutex);
				//pthread_cond_wait(&sdk_cond, &sdk_mutex);
				//printf("......... sem_wait ........\n");
				sem_wait(&sdk_sem);
				//printf("......... sem_wait up ........\n");
				if(working == 0)
				{
						//	pthread_mutex_unlock(&sdk_mutex);
						break;
				}
				char Message[1024]={0};
				memcpy(Message, ConfigMessage, sizeof(ConfigMessage));
				//pthread_mutex_unlock(&sdk_mutex);

				cJSON *root = cJSON_Parse(Message);
				cJSON *name = cJSON_GetObjectItem(root, "Name");
				cJSON *messgae = cJSON_GetObjectItem(root, "Message");
				printf("====popmessage===== %s , status:%d\n",name->valuestring,getDeviceStatus());
				if (memcmp("ConnectionAcceptted", name->valuestring, strlen(name->valuestring)) == 0)
				{
						//printf("..................... Sdk ConnectionAcceptted ....................\n");
						SDK_ConnectType = UDP_P2P_CONNECTION_TYPE;
						LY_StartConnectTime = 0;
						if(rtmpopenflag)
						{	
								cJSON_Delete(root);
								//pthread_mutex_unlock(&sdk_mutex);
								continue;
						}	
				}
				else if (memcmp("ConnectionClosed", name->valuestring, strlen(name->valuestring)) == 0)
				{
						//printf("..................... Sdk ConnectionClosed ....................\n");
						SDK_ConnectType = -1;
						LY_StartConnectTime = 0;
						if(rtmpopenflag)
						{	
								cJSON_Delete(root);
								//pthread_mutex_unlock(&sdk_mutex);
								continue;
						}	
				}
				else if (memcmp("PopConfig", name->valuestring, strlen(name->valuestring)) == 0)
				{
#if 1
						unsigned char * rtmpmessage = (unsigned char *)messgae->valuestring;
						unsigned char config[256];
						int result;
						for (i=0; i<256; i++) {
								sscanf((const char*)rtmpmessage+i*2,"%02X",&result);
								config[i] = result & 0xFF;
						}
						int nStatus = config[4];
						if(SDK_Status == nStatus)
						{
								for(i=0; i<10; i++)
								{
										ret = RespondConfigMsg(0);
										if(ret == 0)
												break;
								}
						}
						SDK_Status = nStatus;
#endif
						SDK_PopConfig_flag = 1;
				}
				cJSON_Delete(root);

				if (messageCallback[0]) {
						messageCallback[0]((void*)messageCallback[1],Message);
				}


		}
		//printf("================== PopMsgCallBackHandler exit  ===============\n");

		return NULL;
}

int init_workers(const char *aSN, unsigned long aCid)
{
		if(working)
				return 0;
		int err;	
		char log[64]={0};
		err = sem_init(&sdk_sem,0,0);
		if(err != 0)
		{
				printf("sdk sem init Fail\n");
				return -1;
		}
		working = 1;
		err = pthread_create(&worker_pid, NULL, PopMsgCallBackHandler, NULL);
		if(err)
		{
				memset(log,0,sizeof(log));
				sprintf("sn:%s,cid:%lu,create working pthread failed",aSN,aCid);
				Send_Log(log,LOG_TYPE_DEVICE);
				return -1;
		}
		return 0;
}

void uninit_workers()
{
		if(working)
		{
				working = 0;
#if 0
				pthread_mutex_lock(&sdk_mutex);
				pthread_cond_signal(&sdk_cond);
				pthread_mutex_unlock(&sdk_mutex);

				//	pthread_cancel(worker_pid);
				pthread_join(worker_pid,0);
				pthread_mutex_destroy(&sdk_mutex);
				pthread_cond_destroy(&sdk_cond);
#else
				sem_post(&sdk_sem);
				usleep(10000);
				pthread_cancel(worker_pid);
				pthread_join(worker_pid,0);
				sem_destroy(&sdk_sem);
#endif
		}

}

int  StartCloudService(const char *aAppID, const char* aDeviceSN, const char* aCid, void *apData, MessageCallBack apMessageCallBack)
{
		int err = -1;
		if((NULL == aAppID)||(NULL == aDeviceSN)||(NULL == aCid))
		{
				err = LYR_InvalidParameter;
				goto failed;
		}

		if(s_start_cloud_flag == 1)
		{
				err = LYR_Unknown;
				goto failed;
		}

		int appIDlen = strlen(aAppID);
		int devSNlen = strlen(aDeviceSN);
		int cidlen = strlen(aCid);
		printf("appid len:%d, sn len:%d, cid len:%d\n",appIDlen,devSNlen,cidlen);
		if((appIDlen != DEVICE_APPID_LEN) || (cidlen != DEVICE_CID_LEN) || (devSNlen > DEVICE_SN_LEN))
		{	
				err = LYR_LengthExceeded;
				goto failed;
		}

		SDK_PopConfig_flag = 0;
		rtmpopenflag = 0;

		messageCallback[0] = apMessageCallBack;
		messageCallback[1] = (MessageCallBack)apData;
		char msg[64]={0};
		char SN[25]={0};
		sprintf(SN,"%s%s",aAppID,aDeviceSN);  
		unsigned long Cid = GetDwordID((char *)aCid);
		if(Cid == 0)
		{
				sprintf(msg,"g_cid f sn:%s hid:%s cid:%ld",SN,aCid,Cid);
				Send_Log(msg,LOG_TYPE_DEVICE);
				err = LYR_InvalidCID;
				goto failed;
		}

		char hostip[64] = {0};
		if (resolv_name(CenterWebServerAddr, hostip) != 0) {
				printf("DNS resolve failed\n");
				memset(msg,0,sizeof(msg));
				sprintf(msg,"DNS failed cid:%ld,%s",Cid,CenterWebServerAddr);
				Send_Log(msg,LOG_TYPE_DEVICE);

				err = LYR_DNSResolveFailed;
				goto failed;
		}

#if 1
		err = init_workers(SN, Cid);
		if(err != 0)
		{
				printf(" ... init_workers failed ....\n");
				err = LYR_Unknown;
				goto failed;
		}		
#endif

		set_defalut_platform_config(hostip);
		char strconfig[500];
		memset(strconfig, 0, 500);
		sprintf(strconfig,"[Config]\r\nCID=%lu\r\nSN=%s%s\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nIsSendBroadcast=0\r\nUdpSendInterval=2\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80\r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n",Cid,aAppID,aDeviceSN);

		int nRet = Core_StartCloudService(strconfig, apData, PopMessageCallBack);
		if(nRet == 0)
		{
				init_ssl();
				s_start_cloud_flag = 1;
				Create_log_pthread((const char *)SN,Cid);
				platform_global_config.cid = Cid;
				strcpy(platform_global_config.hashid, aCid);
				//printf("device hashid :%s len:%d\n",platform_global_config.hashid,strlen(platform_global_config.hashid));
				LastErrorNo(LYR_OK,1);
				return LYR_OK;	
		} 

		//send login failed log message
		memset(msg,0,sizeof(msg));
		sprintf(msg,"Start r:%d sn:%s hid:%s cid:%ld",nRet,SN,aCid,Cid);
		Send_Log(msg,LOG_TYPE_DEVICE);

		err = nRet;		

failed:
		LastErrorNo(err,1);	
		return -1;
}


int  StartCloudService2(const char* aConfigString, void *apData, MessageCallBack apMessageCallBack)
{
		int err = -1;
		if(NULL == aConfigString)
		{
				err = LYR_InvalidParameter;
				goto failed;
		}

		if(s_start_cloud_flag == 1)
		{
				err = LYR_Unknown;
				goto failed;
		}

		SDK_PopConfig_flag = 0;
		rtmpopenflag = 0;

		messageCallback[0] = apMessageCallBack;
		messageCallback[1] = (MessageCallBack)apData;

		int nRet = 0;
		char hashid[30]={0};
		char devSN[32]={0};
		char ServerAddr[32]={0};
		char msg[64] = {0};

		//ret = sscanf(aString,"%*[^\n]\nCID=%16[^\r]%*[^\n]\nSN=%32[^\r]%*[^\n]\nLoginAddress=%30[^\r]\r\n%*s",cid,devsn,ServerAddr);
		char *devCid_str = strstr(aConfigString,"\r\nCID=");
		if((devCid_str == NULL))
		{
				err = LYR_InvalidCID;
				goto failed;
		}
		nRet = sscanf(devCid_str,"%*[^\n]\nCID=%30[^\r\n]",hashid);

		char *devSN_str = strstr(aConfigString,"\r\nSN=");
		if((devSN_str == NULL))
		{
				err = LYR_InvalidDevSN;
				goto failed;
		}
		nRet = sscanf(devSN_str,"%*[^\n]\nSN=%30[^\r\n]",devSN);

		if((strlen(hashid) != DEVICE_CID_LEN) || (strlen(devSN) > (DEVICE_SN_LEN + DEVICE_APPID_LEN)))
		{
				err = LYR_LengthExceeded;
				goto failed;
		}

		char *ServerAddr_str = strstr(aConfigString,"\r\nLoginAddress=");
		if(ServerAddr_str)
				nRet = sscanf(ServerAddr_str,"%*[^\n]\nLoginAddress=%32[^\r\n]",ServerAddr);

		char *cid_start_offset = strstr(aConfigString,"CID=");
		char *cid_end_offset = strstr(cid_start_offset,"\r\n");
		//printf("cid start:\n%s\n",cid_start_offset);
		//printf("cid end:\n%s\n",cid_end_offset);
		printf("ret:%d hashid:%s, devsn:%s, ServerAddr:%s\n",nRet,hashid,devSN,ServerAddr);

		unsigned long Cid = GetDwordID(hashid);
		if(Cid == 0)
		{
				sprintf(msg,"g_cid f sn:%s hid:%s cid:%ld",devSN,hashid,Cid);
				Send_Log(msg,LOG_TYPE_DEVICE);
				err = LYR_InvalidCID;
				goto failed;
		}	

		char strconfig[500]={0};
		char new_cid_str[50]={0};
		sprintf(new_cid_str,"CID=%lu",Cid);
		strncpy(strconfig,aConfigString,cid_start_offset-aConfigString);
		strcat(strconfig,new_cid_str);
		strcat(strconfig,cid_end_offset);

		if(ServerAddr_str)
				set_defalut_platform_config(ServerAddr);
		else
		{
				char hostip[64] = {0};
				if (resolv_name(CenterWebServerAddr, hostip) != 0) {
						printf("DNS resolve failed\n");
						memset(msg,0,sizeof(msg));
						sprintf(msg,"DNS failed cid:%ld,%s",Cid,CenterWebServerAddr);
						Send_Log(msg,LOG_TYPE_DEVICE);
						err = LYR_DNSResolveFailed;
						goto failed;
				}

				set_defalut_platform_config(hostip);
		}

		err = init_workers(devSN, Cid);
		if(err != 0)
		{
				err = LYR_Unknown;
				goto failed;
		}		

		nRet = Core_StartCloudService(strconfig, apData, PopMessageCallBack);
		if(nRet == 0)
		{
				init_ssl();
				s_start_cloud_flag = 1;
				Create_log_pthread(devSN,Cid);
				platform_global_config.cid = Cid;
				strcpy(platform_global_config.hashid, hashid);
				//printf("device hashid :%s len:%d\n",platform_global_config.hashid,strlen(platform_global_config.hashid));	
				LastErrorNo(LYR_OK,1);
				return LYR_OK;	
		}

		// send login failed log message
		memset(msg,0,sizeof(msg));
		sprintf(msg,"Start r:%d sn:%s hid:%s cid:%ld",nRet,devSN,hashid,Cid);
		Send_Log(msg,LOG_TYPE_DEVICE);
		err = nRet;

failed:
		LastErrorNo(err,1);	
		return -1;
}

void  StopCloudService()
{		
		if(s_start_cloud_flag)
		{
				Send_Log("StopCloudService",LOG_TYPE_DEVICE);
				if(rtmpopenflag == 1)
						Disconnect();

				Core_StopCloudService();
				pthread_cancel(log_tid);
				pthread_join(log_tid,0);
		}
		uninit_workers();	

		log_flag = 0;
		SDK_PopConfig_flag = 0;
		s_start_cloud_flag = 0;
		LastErrorNo(LYR_OK,1);	
}


float GetPlatformVersion()
{
		float fversion = 0.0;
		char *status = Core_GetStatus();

		if(status == NULL)
		{
				LastErrorNo(LYR_Unknown,1);	
				return -1;
		}

		cJSON *root = cJSON_Parse(status);
		do {
				if (root == NULL) {
						break;
				}
				cJSON *version = cJSON_GetObjectItem(root, "ver");
				if (version == NULL) {
						break;
				}

				fversion = atof(version->valuestring);

				//printf("======== ver_str:%s , fversion = %d\n",version->valuestring,fversion);

		} while(0);


		if (root) {
				cJSON_Delete(root);
		}
		if(status != NULL)
				free(status);

		LastErrorNo(LYR_OK,1);	
		return fversion;
}

int GetDeviceToken(char *aTokenBuffer, unsigned int aBufferLength)
{
		size_t length = -1;

		char *status = NULL;
		status = Core_GetStatus();
		//printf("status:%s\n",status);
		if (status == NULL) {
				LastErrorNo(LYR_InvalidToken,1);	
				return length;
		}
		cJSON *root = cJSON_Parse(status);
		do {
				if (root == NULL) {
						break;
				}
				cJSON *token = cJSON_GetObjectItem(root, "ToKen");
				if (token == NULL) {
						break;
				}
				length = strlen(token->valuestring);
				if (aTokenBuffer && aBufferLength > length) {
						strcpy(aTokenBuffer, token->valuestring);
				}
		} while(0);

		if (root) {
				cJSON_Delete(root);
		}
		//printf("======== token:%s , len = %d\n",aToken,TokenLength);
		free(status);

		LastErrorNo(LYR_OK,1);	
		return length;
}

char* GetDeviceStatus()
{
		char *status = NULL;
		status = Core_GetStatus();
		//printf("status:%s\n",status);
		cJSON *root = cJSON_Parse(status);

		cJSON *version = cJSON_GetObjectItem(root, "ver");
		cJSON *loginsucc = cJSON_GetObjectItem(root, "LoginSucc");
		cJSON *isOnLine = cJSON_GetObjectItem(root, "IsOnline");
		cJSON *sendLostCount = cJSON_GetObjectItem(root, "SendLostCount");
		cJSON *devStatus = cJSON_GetObjectItem(root, "Status");

		float fversion = 0.0;
		int login = 0;
		int online = 0;
		int sendLost = 0;
		int status_value = 0;


		if (devStatus != NULL) {
				status_value = devStatus->valueint;
		}


		if (version != NULL) {
				fversion = atof(version->valuestring);
		}

		if (loginsucc != NULL) {
				login = loginsucc->valueint;
		}

		if (isOnLine != NULL) {
				online = isOnLine->valueint;
		}
		if (sendLostCount != NULL) {
				sendLost = sendLostCount->valueint;
		}

#if 1
		if(sendLost > 100)
				sendLost = 100;
		if(RTMP_Upload > 100)
				RTMP_Upload = 100;

		static char status_json[500]={0};
		memset(status_json,0,sizeof(status_json));
		if(version == NULL)
				sprintf(status_json,"{\"Version\":%s,\"LoginSucc\":%d,\"IsOnline\":%d,\"Status\":%d,\"UDPSendLostCount\":%d,\"RtmpSendLostCount\":%d}","0.0",login,online,status_value,sendLost,RTMP_Upload);
		else if(version->valuestring == NULL)
				sprintf(status_json,"{\"Version\":%s,\"LoginSucc\":%d,\"IsOnline\":%d,\"Status\":%d,\"UDPSendLostCount\":%d,\"RtmpSendLostCount\":%d}","0.0",login,online,status_value,sendLost,RTMP_Upload);
		else
				sprintf(status_json,"{\"Version\":%s,\"LoginSucc\":%d,\"IsOnline\":%d,\"Status\":%d,\"UDPSendLostCount\":%d,\"RtmpSendLostCount\":%d}",version->valuestring,login,online,status_value,sendLost,RTMP_Upload);
#else
		/*json root out */
		cJSON * root_out = cJSON_CreateObject();
		cJSON_AddNumberToObject(root_out,"Version",fversion);
		cJSON_AddNumberToObject(root_out,"LoginSucc",login);
		cJSON_AddNumberToObject(root_out,"IsOnline",online);
		cJSON_AddNumberToObject(root_out,"SendLostCount",sendLost);

		//cJSON_AddStringToObject(root_out, "version", aData);
		/*json output.*/
		static char *status_json=cJSON_PrintUnformatted(root_out);
		if (NULL == status_json) {
				cJSON_Delete(root_out);
		}

		if (root_out) {
				cJSON_Delete(root_out);
		}
#endif

		if (root) {
				cJSON_Delete(root);
		}

		if(status)
				free(status);

		LastErrorNo(LYR_OK,1);	
		return status_json;
}


int getDeviceStatus()
{
		char *status = NULL;
		status = Core_GetStatus();
		//printf("status:%s\n",status);
		cJSON *root = cJSON_Parse(status);

		cJSON *devStatus = cJSON_GetObjectItem(root, "Status");

		int value = 0;
		if (devStatus != NULL) {
				//value = atoi(devStatus->valuestring);
				value = devStatus->valueint;
		}
		if (root) {
				cJSON_Delete(root);
		}

		if(status)	
				free(status);

		return value;
}


static int frame_type(const char* p_data)
{
		char* pTmp = p_data;
		if((*pTmp == 0)&&(*(pTmp+1)==0)&&(*(pTmp+2)==0)&&(*(pTmp+3)==1)){
				char type = (*(pTmp+4)) & 0x1f;

				if(type == 7){
						return 7;
				}else if(type == 8){
						return 8;
				}
				else if(type == 6){
						return 6;
				}
				else if(type == 5){
						return 5;
				}
				else if(type == 1){
						return 1;
				}
				else
						return -1;
		}
		else if((*pTmp == 0)&&(*(pTmp+1)==0)&&(*(pTmp+2)==1))
		{
				//printf("===== data : %x\n",*(pTmp+3));
				char type = (*(pTmp+3)) & 0x1f;
				if(type == 5)
						return 15;
				else
						return -1;
		}

		return -1;
}

char* findSPSOffset(const char* p_data,int len)
{
		int i;
		for(i=0;i<len;i++){
				char* pTmp = p_data+i;
				if(i+5 >=len)
						return NULL;

				if(frame_type(pTmp) == 7){
						//printf("sps\n");
						return pTmp;
						//return pTmp+4;
				}
		}

		return NULL;
}

char* findPPSOffset(const char* p_data,int len)
{
		int i;
		for(i=0;i<len;i++){
				char* pTmp = p_data+i;
				if(i+5 >=len)
						return NULL;

				if(frame_type(pTmp) == 8){
						//printf("pps\n");
						return pTmp;
						//return pTmp+4;
				}
		}

		return NULL;
}

char* findSEIOffset(const char* p_data,int len)
{
		int i;
		for(i=0;i<len;i++){
				char* pTmp = p_data+i;
				if(i+5 >=len)
						return NULL;

				if(frame_type(pTmp) == 6){
						//printf("sei\n");
						return pTmp;
						//return pTmp+4;
				}
		}

		return NULL;
}

char* findIFrameOffset(const char* p_data,int len, int *eItype)
{
		int i;
		for(i=0;i<len;i++){
				char* pTmp = p_data+i;
				if(i+5 >=len)
						return NULL;

				int type = frame_type(pTmp);
				if(type == 5){
						//printf("iframe\n");
						//return pTmp+4;
						*eItype = 5;
						return pTmp;
				}
				else if(type == 15){
						*eItype = 15;//
						return pTmp;
				}

		}

		return NULL;
}

char* findPFrameOffset(const char* p_data,int len)
{
		int i;
		for(i=0;i<len;i++){
				char* pTmp = p_data+i;
				if(i+5 >=len)
						return NULL;

				if(frame_type(pTmp) == 1){
						//printf("pframe\n");
						//return pTmp+4;
						return pTmp;
				}
		}

		return NULL;
}

char* findFrameOffset(const char* p_data,int len, unsigned char *aType)
{
		int i;
		*aType = 0;
		for(i=0;i<len;i++){
				char* pTmp = p_data+i;
				if(i+5 >=len)
						return NULL;

				int type = frame_type(pTmp);
				if(type != -1){
						*aType = type;
						//return pTmp+4;
						return pTmp;
				}
		}

		return NULL;
}

int   P2pPushData(unsigned long aDataLevelPos, const char *aDataBuffer,  unsigned long  aBufferLength, unsigned long aTimestamp, unsigned char apFrameSampleType)
{
		int ret = 0;
		char type = frame_type(aDataBuffer);
		//printf(" type:%d, data src: %x,%x,%x,%x,%x,%x,%x,%x,%x,%x\n",type,*(aDataBuffer),*(aDataBuffer+1),*(aDataBuffer+2),*(aDataBuffer+3),*(aDataBuffer+4),*(aDataBuffer+5),*(aDataBuffer+6),*(aDataBuffer+7),*(aDataBuffer+8),*(aDataBuffer+9));
		if(type==7){                    //first is sps
				int spsLen = aBufferLength;
				int ppsLen = 0;
				int seiLen = 0;
				int iframeLen = 0;
				int iType = 0;

				char* pSPS = findSPSOffset(aDataBuffer,aBufferLength);
				char* pPPS = findPPSOffset(aDataBuffer,aBufferLength);
				char* pIFrame = findIFrameOffset(aDataBuffer,aBufferLength,&iType);
				int tmpLen = pIFrame-pPPS;
				char* pSEI = findSEIOffset(pPPS,tmpLen);
#if 0
				if(pSPS == NULL)
						printf("pSPS ============= NULL\n");
				if(pPPS == NULL)
						printf("pPPs ============= NULL\n");
				if(pIFrame == NULL)
						printf("pIFrame ============= NULL\n");
				if(pSEI == NULL)
						printf("pSEI ============= NULL\n");
#endif
				if(pSEI){
						if(pPPS)
						{
								spsLen = pPPS - pSPS;
								ppsLen = pSEI - pPPS;
						}
						if(pIFrame)
						{
								seiLen = pIFrame - pSEI;
								iframeLen = aBufferLength - spsLen -ppsLen -seiLen;
						}
				}
				else
				{	
						if(pPPS)
						{
								spsLen = pPPS - pSPS;
								ppsLen = aBufferLength - spsLen;
						}
						if(pIFrame)
						{
								ppsLen = pIFrame - pPPS;
								//ppsLen = pSEI - pPPS;
								iframeLen = aBufferLength - spsLen -ppsLen;
						}
				}

#ifdef ENABLE_AES128
				//printf("D_aes_encrypt start .........sps:%d, pps:%d, iframe:%d\n",spsLen,ppsLen,iframeLen);
				if(pIFrame)
				{
						unsigned char* encrypt_out;
						unsigned int encrypt_len;

						//printf("iframe: %x %x %x %x %x %x %x\n",*pIFrame,*(pIFrame+1),*(pIFrame+2),*(pIFrame+3),*(pIFrame+4),*(pIFrame+5),*(pIFrame+6));
						int ret = D_aes_encrypt((unsigned char*)(pIFrame+1),(unsigned int)(iframeLen-1 - (iframeLen-1)%16),&encrypt_out,&encrypt_len);
						if(ret != -1)
						{
								memcpy(pIFrame+1,encrypt_out,encrypt_len);
								free(encrypt_out);
						}
				}
#endif
				//printf("D_aes_encrypt end .........sps:%d, pps:%d, iframe:%d\n",spsLen,ppsLen,iframeLen);
				if(pSPS)
						ret = Core_PushData(aDataLevelPos,pSPS,spsLen,aTimestamp,NALU_TYPE_SPS);//7
				if(pPPS)
						ret = Core_PushData(aDataLevelPos,pPPS,ppsLen,aTimestamp,NALU_TYPE_PPS);//8
				if(pIFrame)
						ret = Core_PushData(aDataLevelPos,pIFrame,iframeLen,aTimestamp,NALU_TYPE_IDR);//5
		}
		else if(type == 8)
		{
				//send pps
				//printf("send rtmp pps frame\n");
				ret = Core_PushData(aDataLevelPos,aDataBuffer,aBufferLength,aTimestamp,NALU_TYPE_PPS);
		}
		else if(type == 5)
		{
				//send iFrame
				//printf("send rtmp I frame\n");
				int iframeLen = aBufferLength;
				int iType;
				char* pIFrame = findIFrameOffset(aDataBuffer,aBufferLength,&iType);
#ifdef ENABLE_AES128
				if(LY_PublicLiveFlag == 0)		//is not publicLive
				{
						RTMP_Enable_AES128 = 0x01;
						if(pIFrame)
						{
								unsigned char* encrypt_out;
								unsigned int encrypt_len;
								int ret = D_aes_encrypt((unsigned char*)(pIFrame+1),(unsigned int)(iframeLen-1 - (iframeLen-1)%16),&encrypt_out,&encrypt_len);

								memcpy(pIFrame+1,encrypt_out,encrypt_len);
								free(encrypt_out);
						}
				}
#endif

				if(pIFrame)
						ret = Core_PushData(aDataLevelPos,pIFrame,iframeLen,aTimestamp,NALU_TYPE_IDR);//5
		}
		else if(type==1){                       //p frame
				if(aBufferLength>4){
						ret = Core_PushData(aDataLevelPos,aDataBuffer,aBufferLength,aTimestamp,NALU_TYPE_SLICE);//1
				}
		}
		else 
		{	//else if(apFrameSampleType == NALU_TYPE_AUD)
				ret = Core_PushData(aDataLevelPos,aDataBuffer,aBufferLength,aTimestamp,apFrameSampleType);
				//printf("send aac  ===== length:%ld, time stamp: %ld , frame type: %x , type1 :%x\n",aBufferLength,aTimestamp,apFrameSampleType,type);
		}
		return ret;
}


char* PopData(unsigned long aDataLevelPos, unsigned long *apFrameSampleLength, unsigned long *apTimestamp, unsigned char *apFrameSampleType)
{
		return Core_PopData(aDataLevelPos,apFrameSampleLength,apTimestamp,apFrameSampleType);
}

int QueryAlarmRecordInfo()
{
		return sendGetDiskListCommand();
}


unsigned char recvAudioSpecificConfig[2]={0};
unsigned char aacFrame[2048]={0};

static int getADTSHeader(char *packet, int packetLen)
{
		int profile = 2;  //AAC LC
		int freqIdx = 3;  //11025:10 < 44.1KHz
		int chanCfg = 1;  //mono
		int frameLengthFlag = 0;
		int dependsOnCoreCoder = 0;
		int extensionFlag = 0;

		//printf("getADTSHeader profile:%d, freqIdx:%d, chanCfg:%d\n",profile,freqIdx,chanCfg);
#if 0
		profile = (aacSeqHeader[0] & 0xf8)  >> 3 ;			//取前5bit
		freqIdx = ((aacSeqHeader[0] & 0x07) << 1)|(aacSeqHeader[1] >> 7);//取后4bit
		chanCfg = (aacSeqHeader[1] >> 3) & 0x0f;			//取后4bit
		frameLengthFlag = (aacSeqHeader[1] >> 2) & 0x01;		//取后1bit
		dependsOnCoreCoder = (aacSeqHeader[1] >> 1) & 0x01;		//取后1bit
		extensionFlag = aacSeqHeader[1] & 0x01;				//最后1bit
#else	
		profile = (recvAudioSpecificConfig[0] & 0xf8)  >> 3 ;			//取前5bit
		freqIdx = ((recvAudioSpecificConfig[0] & 0x07) << 1)|(recvAudioSpecificConfig[1] >> 7);//取后4bit
		chanCfg = (recvAudioSpecificConfig[1] >> 3) & 0x0f;			//取后4bit
		frameLengthFlag = (recvAudioSpecificConfig[1] >> 2) & 0x01;		//取后1bit
		dependsOnCoreCoder = (recvAudioSpecificConfig[1] >> 1) & 0x01;		//取后1bit
		extensionFlag = recvAudioSpecificConfig[1] & 0x01;				//最后1bit
#endif
		//printf("getADTSHeader profile:%d, freqIdx:%d, chanCfg:%d, frameLengthFlag:%d, depend:%d, extenflag:%d\n",profile,freqIdx,chanCfg,frameLengthFlag,dependsOnCoreCoder,extensionFlag);

		// fill in ADTS data
		unsigned int num_data_block = packetLen/1024;
		unsigned int frame_length = packetLen +7; 
#if 1
		//char aacheadtype[7] = {0xff,0xf1,0x68,0x80,0x16,0x62,0x64};
		char aacheadtype[7] = {0xff,0xf1,0x68,0x40,0x16,0x00,0xfc};
		memset(aacFrame,0,sizeof(aacFrame));
		memcpy(aacFrame,aacheadtype,7);

		/* frame size over last 2 bits */
		aacFrame[3] |= (frame_length & 0x1800) >> 11;// the upper 2 bit
		/* frame size continued over full byte */
		aacFrame[4] = (frame_length & 0x1FF8) >> 3;// the middle 8 bit
		/* frame size continued first 3 bits */
		aacFrame[5] = 0x00;
		aacFrame[5] |= (frame_length & 0x7) << 5;
		aacFrame[5] |= 0x1F;
#else
		memset(aacFrame,0,sizeof(aacFrame));
		aacFrame[0] = (unsigned char)0xFF;
		aacFrame[1] = (unsigned char)0xF1;//0xF9
		aacFrame[2] = (unsigned char)(((profile-1)<<6) + (freqIdx<<2) +(chanCfg>>2));
		aacFrame[3] = (unsigned char)(((chanCfg & 0x03)<<6) + (frame_length >> 11));
		aacFrame[4] = (unsigned char)((frame_length & 0x7FF) >> 3);
		aacFrame[5] = (unsigned char)(((frame_length & 0x07)<<5) + 0x1F);
		aacFrame[6] = (unsigned char)0xFC;

		//aacFrame[5] = (unsigned char)((frame_length << 5) & 0xE0);
		//aacFrame[5] |= ((0x7FF >> 6) & 0x1F);  
		//aacFrame[6] = (unsigned char)0xFC;
		//aacFrame[6] |= (num_data_block & 0x03);
#endif
		if(packetLen <= (sizeof(aacFrame)-7))
				memcpy(aacFrame+7,packet,packetLen);
		else
				return 0;

		return frame_length;
} 

static int getADTSHead(char *Adts_header, int packetLen)
{
		if(Adts_header == NULL)
				return -1;

		int profile = 2;  //AAC LC
		int freqIdx = 3;  //11025:10 < 44.1KHz
		int chanCfg = 1;  //mono
		int frameLengthFlag = 0;
		int dependsOnCoreCoder = 0;
		int extensionFlag = 0;

		//printf("getADTSHeader profile:%d, freqIdx:%d, chanCfg:%d\n",profile,freqIdx,chanCfg);
#if 0
		profile = (aacSeqHeader[0] & 0xf8)  >> 3 ;			//取前5bit
		freqIdx = ((aacSeqHeader[0] & 0x07) << 1)|(aacSeqHeader[1] >> 7);//取后4bit
		chanCfg = (aacSeqHeader[1] >> 3) & 0x0f;			//取后4bit
		frameLengthFlag = (aacSeqHeader[1] >> 2) & 0x01;		//取后1bit
		dependsOnCoreCoder = (aacSeqHeader[1] >> 1) & 0x01;		//取后1bit
		extensionFlag = aacSeqHeader[1] & 0x01;				//最后1bit
#else	
		profile = (recvAudioSpecificConfig[0] & 0xf8)  >> 3 ;			//取前5bit
		freqIdx = ((recvAudioSpecificConfig[0] & 0x07) << 1)|(recvAudioSpecificConfig[1] >> 7);//取后4bit
		chanCfg = (recvAudioSpecificConfig[1] >> 3) & 0x0f;			//取后4bit
		frameLengthFlag = (recvAudioSpecificConfig[1] >> 2) & 0x01;		//取后1bit
		dependsOnCoreCoder = (recvAudioSpecificConfig[1] >> 1) & 0x01;		//取后1bit
		extensionFlag = recvAudioSpecificConfig[1] & 0x01;				//最后1bit
#endif
		//printf("getADTSHeader profile:%d, freqIdx:%d, chanCfg:%d, frameLengthFlag:%d, depend:%d, extenflag:%d\n",profile,freqIdx,chanCfg,frameLengthFlag,dependsOnCoreCoder,extensionFlag);

		// fill in ADTS data
		unsigned int num_data_block = (packetLen+7) / 1024;
		unsigned int frame_length = packetLen + 7; 
#if 1
		//char aacheadtype[7] = {0xff,0xf1,0x68,0x80,0x16,0x62,0x64};
		char aacheadtype[7] = {0xff,0xf1,0x68,0x40,0x16,0x00,0xfc};
		memcpy(Adts_header, aacheadtype,7);

		/* frame size over last 2 bits */
		Adts_header[3] |= (frame_length & 0x1800) >> 11;// the upper 2 bit
		/* frame size continued over full byte */
		Adts_header[4] = (frame_length & 0x1FF8) >> 3;// the middle 8 bit
		/* frame size continued first 3 bits */
		Adts_header[5] = 0x00;
		Adts_header[5] |= (frame_length & 0x7) << 5;
		Adts_header[5] |= 0x1F;
#else
		Adts_header[0] = (unsigned char)0xFF;
		Adts_header[1] = (unsigned char)0xF1;//0xF9
		Adts_header[2] = (unsigned char)(((profile-1)<<6) + (freqIdx<<2) +(chanCfg>>2));
		Adts_header[3] = (unsigned char)(((chanCfg & 0x03)<<6) + (frame_length >> 11));
		Adts_header[4] = (unsigned char)((frame_length & 0x7FF) >> 3);
		Adts_header[5] = (unsigned char)(((frame_length & 0x07)<<5) + 0x1F);
		Adts_header[6] = (unsigned char)0xFC;

		//Adts_header[5] = (unsigned char)((frame_length << 5) & 0xE0);
		//Adts_header[5] |= ((0x7FF >> 6) & 0x1F);  
		//Adts_header[6] = (unsigned char)0xFC;
		//Adts_header[6] |= (num_data_block & 0x03);
#endif

		return 0;
} 


void SetRtmpDataCallBack(void *apData, RtmpDataCallBack aRtmpDataCallBack)
{
		platform_global_config.rtmp_fun[0] = (char *)aRtmpDataCallBack;
		platform_global_config.rtmp_fun[1] = (char *)apData;
}

void RTMP_PopDataCall(int aDataType,char* aDataBuffer,int aDataLength)
{
		//printf("rtmp recv data type :%d\n",aDataType);
		if((aDataBuffer == NULL) || (aDataLength < 4))
				return ;
		int i,ret = -1;
		switch(aDataType)
		{
				case RTMP_TYPE_AUDIO_DATA:
						if((aDataBuffer[0] == 0xaf) && (aDataBuffer[1] == 0x00) && (aDataLength == 4))
						{	// 0xaf 0x00 aac info
								//printf("....sdk-------recv rtmp aac info------\n");
								recvAudioSpecificConfig[0] = aDataBuffer[2];
								recvAudioSpecificConfig[1] = aDataBuffer[3];
						}
						else if((aDataBuffer[0] == 0xaf) && (aDataBuffer[1] == 0x01))
						{	// x0af 0x01 aac data
								if(platform_global_config.rtmp_fun[0] != NULL)
								{
										//printf("....sdk-------recv rtmp aac data ------\n");
#if 0
										int aac_length = getADTSHeader((char *)(data+2), len-2);
										((D_RtmpAudioCallBack)platform_global_config.rtmp_fun[0])((void *)platform_global_config.rtmp_fun[1],(const char *)aacFrame,aac_length);
#else
										int packetLen = aDataLength-2;
										char *frameBuffer = (char *)malloc(packetLen+7);
										if(frameBuffer == NULL)
										{
												printf("alloc aac buffer failed!\n");
												return;
										}
										memset(frameBuffer,0,packetLen+7);
										if(getADTSHead(frameBuffer, packetLen) == -1)
												return;
										memcpy(frameBuffer+7,aDataBuffer+2,packetLen);
										((RtmpDataCallBack)platform_global_config.rtmp_fun[0])((void *)platform_global_config.rtmp_fun[1],(const char *)frameBuffer,packetLen+7,RTMP_TYPE_AUDIO_DATA);
										if(frameBuffer)
												free(frameBuffer);
#endif
								}
						}
						break;

				case RTMP_TYPE_DISK_INFO:
						((RtmpDataCallBack)platform_global_config.rtmp_fun[0])((void *)platform_global_config.rtmp_fun[1],(const char *)aDataBuffer,aDataLength,RTMP_TYPE_DISK_INFO);
						break;

				case RTMP_TYPE_IMAGE_ADDR:
						memset(platform_global_config.rtmp_record_imgAddr,0,sizeof(platform_global_config.rtmp_record_imgAddr));
						//memcpy(platform_global_config.rtmp_record_imgAddr, aDataBuffer, aDataLength);
						sscanf(aDataBuffer, "%[^:]:%d", platform_global_config.rtmp_record_imgAddr, &platform_global_config.rtmp_record_imgPort);
						char msg[LOG_MSG_SIZE]={0};
						//platform_global_config.rtmp_record_imgPort = 80;
						sprintf(msg,"G_img srv ip:%s, port:%d",platform_global_config.rtmp_record_imgAddr,platform_global_config.rtmp_record_imgPort);
						Send_Log((const char *)msg,LOG_TYPE_DEVICE);
						//printf("get image server ip :%s , port:%d\n",platform_global_config.rtmp_record_imgAddr,platform_global_config.rtmp_record_imgPort);
						break;

				default:
						break; 
		}
}

int ConnectRTMP(RTMPMetaData aMetaData)
{
		int ret = -1;
#if 1
		setDeviceType(1);
		char token[DEVICE_TOKEN_SIZE] = {0};
		int token_len = GetDeviceToken(token, sizeof(token));
		if (token_len == -1)
		{
				return -1;
		}
		setToken(token);
		setMetaData(aMetaData);
		//setLogDir(platform_global_config.rtmp_log_dir);
		//platform_global_config.rtmp_fun[0] = (char *)aRtmpAudioCall;
		ret = ConnectToRtmpServer((const char *)platform_global_config.rtmp_url,RTMP_PopDataCall,1);
		//ret = ConnectToRtmpServer((const char *)platform_global_config.rtmp_url,RTMPPopDataCallBack,1);
#else
		//setLogDir("./");
		setDeviceType(1);
		char token[DEVICE_TOKEN_SIZE] = {0};
		int token_len = GetDeviceToken(token, sizeof(token));
		if (token_len == -1)
		{
				return -1;
		}
		setToken(token);
		setMetaData(aMetaData);
		char url[50];
		memset(url,0,50);
		sprintf(url,"rtmp://203.195.158.144:1935/live/%d",platform_global_config.cid);
		//sprintf(url,"rtmp://123.56.155.168:1935/live/%d",platform_global_config.cid);
		//sprintf(url,"rtmp://54.183.239.230:1935/live/%d",platform_global_config.cid);
		//platform_global_config.rtmp_fun[0] = (char *)aRtmpAudioCall;
		ret = ConnectToRtmpServer(url,RTMP_PopDataCall,1);
		//ret = ConnectToRtmpServer("rtmp://192.168.2.197:1936/demo/1001",RTMP_PopDataCall,1);
#endif
		return ret;
}

int StartRtmpServer(RTMPMetaData aMetaData)
{
		set_defalut_globle_value();
		return ConnectRTMP(aMetaData);
}

void  StopRtmpServer()
{
		DisconnectRtmpServer();
}


void Count_BitRate_FrameRate(unsigned long aBufferLength, unsigned char apFrameSampleType)
{
		if(apFrameSampleType == NALU_TYPE_AUD || apFrameSampleType == AAC_TYPE_INFO || apFrameSampleType == AAC_TYPE_SAMPLE)
				;
		//printf("audio frame\n");
		else
		{
				C_FrameRate++;		
		}

		C_BitRate += aBufferLength;

		unsigned long  subTime = 0;
		unsigned long  curTime = Sys_GetTickCount();
		if(C_StartTime == 0 || C_StartTime > curTime)
		{
				C_StartTime = curTime;
				return;
		}

		subTime = curTime - C_StartTime;
		if(subTime >= 2000)
		{
				//printf("subTime:%ld ,vframe: %d,tatol bit:%ld,kb:%d \n",subTime,C_FrameRate/2,C_BitRate/2,C_BitRate/1024/2);
				C_StartTime = curTime;
				RTMP_C_FrameRate = C_FrameRate/2;
				RTMP_C_BitRate = C_BitRate/1024/2;
				C_FrameRate = 0;
				C_BitRate = 0;
		}
}

void GetOneSecond_Upload_Count()
{
#if 0
		//一帧数据发送时间超出1秒
		if(rtmp_send_time.T1 != 0)
		{
				if(rtmp_send_time.Tend == 0)
						RTMP_Upload = 100;
				else if(rtmp_send_time.Tend_start != 0)
						RTMP_Upload = ((double)rtmp_send_time.Tstart_end/(double)rtmp_send_time.Tend_start*2)*100;
				else
						printf("GetOneSecond_Upload_Count error! \n");
		}
		printf(".....Tsend: %d , Tfree: %d , RTMP_Upload === %d ....\n",rtmp_send_time.Tstart_end,rtmp_send_time.Tend_start,RTMP_Upload);
#else
		unsigned long long CurTime = Sys_MicroSeconds();
		//double time = (double)(TCurFrameTime - TLastFrameTime)/(double)(CurTime - TsysLastTime);
		double value = (double)(TFrameSendingTime)/(double)(CurTime - TsysLastTime);
		if((value == 0) || (value > 1))
		{
				TFrameStartTime = CurTime;
				RTMP_Upload = 100;
		}
		else if((value*100) < 50)
		{
				RTMP_Upload = 0;
		}
		else
				RTMP_Upload = (value*100 - 50)*2;
		//RTMP_Upload = (double)(TCurFrameTime - TLastFrameTime)/(double)(CurTime - TsysLastTime);

		//printf("TLastFrameTime:%llu, TCurFrameTime:%llu, TsysLastTime:%llu, CurTime:%llu,total: %llu , sending:%llu  value:%2f\n",TLastFrameTime,TCurFrameTime,TsysLastTime,CurTime,(CurTime - TsysLastTime),TFrameSendingTime,value);
		TLastFrameTime = TCurFrameTime;
		TsysLastTime = CurTime;
		TFrameSendingTime = 0;
#endif
}


void GetOneFrame_Sending_StartTime(unsigned long long aTimestamp)
{
		if(TsysLastTime == 0)
				TsysLastTime = Sys_MicroSeconds();
		if(TLastFrameTime == 0)
				TLastFrameTime = aTimestamp;
		TCurFrameTime = aTimestamp;

		TFrameStartTime = Sys_MicroSeconds();

		rtmp_send_time.Tstart = 0;
		rtmp_send_time.Tstart = Sys_GetTickCount();
		if(rtmp_send_time.T1 == 0 || rtmp_send_time.T1 > rtmp_send_time.Tstart)
				rtmp_send_time.T1 = rtmp_send_time.Tstart;
		else
				rtmp_send_time.Tend_start += (rtmp_send_time.Tstart - rtmp_send_time.Tend);
}

void GetOneFrame_Sending_EndTime(unsigned long long aTimestamp, int aResult)
{
		rtmp_send_time.Tend = Sys_GetTickCount();
		//printf("tend:%ld, t1:%ld\n",Tend,T1);
		rtmp_send_time.Tn_T1 = rtmp_send_time.Tend - rtmp_send_time.T1;
		if((aResult==0) || (aResult == 2))
		{
				TFrameSendingTime += (Sys_MicroSeconds() - TFrameStartTime);
				rtmp_send_time.Tstart_end += (rtmp_send_time.Tend - rtmp_send_time.Tstart);
		}

		if(rtmp_send_time.Tbegain == 0)
		{
				rtmp_send_time.Tbegain = rtmp_send_time.Tstart;
		}

		if(rtmp_send_time.Tn_T1 >= 5000)
		{
				//printf(" === Tn_T1:%ld, Tsend:%ld, Tfree:%ld\n",rtmp_send_time.Tn_T1,rtmp_send_time.Tstart_end,rtmp_send_time.Tend_start);
				//send_log();
				char info[50]={0};
				sprintf(info,"T5_T1:%ld, Tsend:%ld, Tfree:%ld",rtmp_send_time.Tn_T1,rtmp_send_time.Tstart_end,rtmp_send_time.Tend_start);
				Send_Log((const char *)info,LOG_TYPE_SENDTIME);
#if 0
				//if((rtmp_send_time.Tend-rtmp_send_time.Tbegain) >= )
				if((double)rtmp_send_time.Tstart_end/(double)rtmp_send_time.Tend_start >= 0.5)                          
				{
						printf("========== send msg to app ==========:%lf\n",(double)rtmp_send_time.Tstart_end/(double)rtmp_send_time.Tend_start);
						PushMessage(0, "12345", 5);
				}                       
#endif
				rtmp_send_time.T1 = 0;
				rtmp_send_time.Tend = 0;
				rtmp_send_time.Tn_T1 = 0;
				rtmp_send_time.Tstart_end = 0;
				rtmp_send_time.Tend_start = 0;
		}
}

//int SendRtmpPacket(char * aDataBuffer,unsigned long aBufferLength, unsigned long aTimestamp,unsigned char aFrameType)
int SendRtmpPacket(char * aDataBuffer,unsigned long aBufferLength, unsigned long long aTimestamp,unsigned char aFrameType)
{
		int nRet = -1;
		//printf("frame type ==== %d\n",aFrameType);
		if(aFrameType == 7)
		{       //first is sps
				int spsLen = aBufferLength -4;
				int ppsLen;
				int seiLen;
				int iframeLen;
				int iType = 0;				
				int iFrame_nal_len = 0;

				char* pSPS = findSPSOffset(aDataBuffer,aBufferLength);
				char* pPPS = findPPSOffset(aDataBuffer,aBufferLength);
				char* pIFrame = findIFrameOffset(aDataBuffer,aBufferLength,&iType);
				int tmpLen = pIFrame-pPPS;
				char* pSEI = findSEIOffset(pPPS,tmpLen);
				if(iType == 5)
						iFrame_nal_len = 4;
				else
						iFrame_nal_len = 3;
				//printf("iFrame_nal_len ===== %d\n",iFrame_nal_len);

				if(pSEI){
						if(pPPS)
								spsLen = pPPS - pSPS -4;
						ppsLen = pSEI - pPPS -4;
						if(pIFrame)
						{
								seiLen = pIFrame - pSEI -4;
								iframeLen = aBufferLength - spsLen -ppsLen -seiLen -12 -iFrame_nal_len;
						}
				}
				else
				{
						if(pPPS)
						{
								spsLen = pPPS - pSPS -4;
								ppsLen = aBufferLength - spsLen -8;
						}
						if(pIFrame)
						{
								ppsLen = pIFrame - pPPS -4;
								//ppsLen = pSEI - pPPS -4;
								iframeLen = aBufferLength - spsLen -ppsLen -8 -iFrame_nal_len;
						}
				}

#ifdef ENABLE_AES128
				if(LY_PublicLiveFlag == 0)		//is not publicLive
				{
						RTMP_Enable_AES128 = 0x01;
						if(pIFrame)
						{
								unsigned char* encrypt_out;
								unsigned int encrypt_len;

								int ret = D_aes_encrypt((unsigned char*)(pIFrame+iFrame_nal_len+1),(unsigned int)(iframeLen-1 - (iframeLen-1)%16),&encrypt_out,&encrypt_len);

								memcpy(pIFrame+iFrame_nal_len+1,encrypt_out,encrypt_len);
								free(encrypt_out);
						}
				}
#endif

				//printf("D_aes_encrypt end .........sps:%d, pps:%d, iframe:%d\n",spsLen,ppsLen,iframeLen);
				if(pSPS)
						nRet = SendNal(pSPS+4,spsLen,aTimestamp);
				if(pPPS)
						nRet = SendNal(pPPS+4,ppsLen,aTimestamp);
				if(pIFrame)
						nRet = SendNal(pIFrame+iFrame_nal_len,iframeLen,aTimestamp);
				//printf("D_aes_encrypt end iframe:%x %x %x %x %x %x %x %x %x %x\n",*(pIFrame+4),*(pIFrame+4+1),*(pIFrame+4+2),*(pIFrame+4+3),*(pIFrame+4+4),*(pIFrame+4+5),*(pIFrame+4+6),*(pIFrame+4+7),*(pIFrame+4+8),*(pIFrame+4+9));
		}
		else if(aFrameType == 8)
		{
				//send pps
				//printf("send rtmp pps frame\n");
				nRet = SendNal(aDataBuffer+4,aBufferLength-4,aTimestamp);
		}
		else if(aFrameType == 5)
		{
				//send iFrame
				//printf("send rtmp I frame\n");
				int iFrame_nal_len = 0;
				int iType;
				char* pIFrame = findIFrameOffset(aDataBuffer,aBufferLength,&iType);
				if(iType == 5)
						iFrame_nal_len = 4;
				else
						iFrame_nal_len = 3;
				int iframeLen = aBufferLength-iFrame_nal_len;
#ifdef ENABLE_AES128
				if(LY_PublicLiveFlag == 0)		//is not publicLive
				{
						RTMP_Enable_AES128 = 0x01;
						if(pIFrame)
						{
								unsigned char* encrypt_out;
								unsigned int encrypt_len;
								int ret = D_aes_encrypt((unsigned char*)(pIFrame+iFrame_nal_len+1),(unsigned int)(iframeLen-1 - (iframeLen-1)%16),&encrypt_out,&encrypt_len);

								memcpy(pIFrame+iFrame_nal_len+1,encrypt_out,encrypt_len);
								free(encrypt_out);
						}
				}
#endif

				if(pIFrame)
						nRet = SendNal(pIFrame+iFrame_nal_len,iframeLen,aTimestamp);
		}
		else if(aFrameType == 1)
		{   
				//p frame	
				if(aBufferLength>4)
				{
						nRet = SendNal(aDataBuffer+4,aBufferLength-4,aTimestamp);
				}
		}
		else if(aFrameType == 6)
		{
				printf("frame type 6 , drop!\n");
				nRet = LYR_FrameTypeNotSupported;	
				//frame start type: 00 00 00 01 06
		}
		else
		{   
				nRet = SendNal(aDataBuffer+4,aBufferLength-4,aTimestamp);
		}

		return nRet;
}


//int SendRTMPData(char * aDataBuffer,unsigned long aBufferLength, unsigned long aTimestamp,unsigned char apFrameSampleType)
int SendRTMPData(char * aDataBuffer,unsigned long aBufferLength, unsigned long long aTimestamp,unsigned char apFrameSampleType)
{
		int nRet = -1;
		unsigned long  Tstart = 0;

		RTMP_Enable_AES128 = 0x00;
		Count_BitRate_FrameRate(aBufferLength,apFrameSampleType);

		//aTimestamp = aTimestamp%0xFFFFFE;
		if(apFrameSampleType == NALU_TYPE_AUD)
		{
				nRet = SendOpus(aDataBuffer, aBufferLength,aTimestamp);
		}
		else if(apFrameSampleType == AAC_TYPE_INFO)
		{
				nRet = SendAacInfo(aDataBuffer, aBufferLength,aTimestamp);
				//printf("send aac info ===== length:%ld, time stamp: %ld\n",aBufferLength,aTimestamp);
		}
		else if(apFrameSampleType == AAC_TYPE_SAMPLE)
		{
				nRet = SendAAC(aDataBuffer, aBufferLength,aTimestamp);
				//printf("send aac sample ===== length:%ld, time stamp: %ld\n",aBufferLength,aTimestamp);
		}
		else
		{
				GetOneFrame_Sending_StartTime(aTimestamp);
				int ret = 0;
				unsigned char type = frame_type(aDataBuffer);
				if(type == 6)
				{
						char* pFrame = findFrameOffset(aDataBuffer+4,aBufferLength-4,&type);
						if(type > 0)
						{
								if(pFrame){
										int seiFrame_len = pFrame - aDataBuffer;
										printf("s total:%d len:%d, data:%x %x %x %x %x \n",aBufferLength,seiFrame_len,*aDataBuffer,*(aDataBuffer+1),*(aDataBuffer+2),*(aDataBuffer+3),*(aDataBuffer+4));
										//SendNal(aDataBuffer+4,seiFrame_len-4,aTimestamp);             //sei frame
										//nRet = SendNal(pFrame+4,aBufferLength-seiFrame_len-4,aTimestamp);       //p frame
										nRet = SendRtmpPacket(pFrame+4, aBufferLength-seiFrame_len-4, aTimestamp, type);	
										printf("p len:%d, data:%x %x %x %x %x \n",aBufferLength-seiFrame_len,*pFrame,*(pFrame+1),*(pFrame+2),*(pFrame+3),*(pFrame+4));
								}
						}
						else
						{
								printf("==== frame 6 %x, drop! ====\n",type);
								nRet = LYR_FrameTypeNotSupported;	
						}	
				}
				else
						nRet = SendRtmpPacket(aDataBuffer, aBufferLength, aTimestamp, type);	

				GetOneFrame_Sending_EndTime(aTimestamp, nRet);

		}


		return nRet;
}

static int GetAacHeadInfo(char *aPayload, long aDataLength)
{
		int profile = ((aPayload[2]&0xc0)>>6)+1;
		int sample_rate = (aPayload[2]&0x3c)>>2;
		int channel = ((aPayload[2]&0x1)<<2)|((aPayload[3]&0xc0)>>6);
		int config1 = (profile<<3)|((sample_rate&0xe)>>1);
		int config2 = ((sample_rate&0x1)<<7)|(channel<<3);

		aacSeqHeader[0] = config1&0xFF;
		aacSeqHeader[1] = config2&0xFF;

		//printf("...profile:%d, sample_rate:%d, channel:%d, config1:%d, config2:%d,aac header1:%x,aac header2:%x\n",profile,sample_rate,channel,config1,config2,aacSeqHeader[0],aacSeqHeader[1]);
		return 0;
}

static void GetAudioSpecificConfig(char *aAdtsHeader, long aDataLength, unsigned char *apAudioSpecificConfig)
{
		int profile = (((unsigned char)aAdtsHeader[2]&0xc0)>>6)+1;
		int sample_rate = ((unsigned char)aAdtsHeader[2]&0x3c)>>2;
		int channel = (((unsigned char)aAdtsHeader[2]&0x1)<<2)|(((unsigned char)aAdtsHeader[3]&0xc0)>>6);
		int config1 = (profile<<3)|((sample_rate&0xe)>>1);
		int config2 = ((sample_rate&0x1)<<7)|(channel<<3);

		apAudioSpecificConfig[0] = (unsigned char)config1&0xFF;
		apAudioSpecificConfig[1] = (unsigned char)config2&0xFF;

		//printf("...profile:%d, sample_rate:%d, channel:%d, config1:%d, config2:%d,aac header1:%x,aac header2:%x\n",profile,sample_rate,channel,config1,config2,apAudioSpecificConfig[0],apAudioSpecificConfig[1]);

}

int RtmpPushData(char * aDataBuffer,unsigned long aBufferLength, unsigned long long aTimestamp,unsigned char apFrameSampleType)
{
		int nRet = -1;
		if(apFrameSampleType == AAC_TYPE_SAMPLE)
		{
				char AudioSpecificConfig[2]={0};
				GetAudioSpecificConfig((char *)aDataBuffer, aBufferLength, AudioSpecificConfig);
				nRet = SendRTMPData((char *)AudioSpecificConfig, 2, aTimestamp, AAC_TYPE_INFO);
				nRet = SendRTMPData((char *)(aDataBuffer+7), aBufferLength-7, aTimestamp, AAC_TYPE_SAMPLE);
		}
		else
				nRet = SendRTMPData((char *)aDataBuffer, aBufferLength, aTimestamp, apFrameSampleType);

		return nRet;
}


//int  PushData(unsigned long aDataLevelPos, const char *aDataBuffer, unsigned long aBufferLength, unsigned long aTimestamp, unsigned char apFrameSampleType)
int  PushData(unsigned long aDataLevelPos, const char *aDataBuffer, unsigned long aBufferLength, unsigned long long aTimestamp, unsigned char apFrameSampleType)
{
		int nRet = 0;
		if(rtmpopenflag == 0) //p2p
		{
				if(SDK_ConnectType != UDP_P2P_CONNECTION_TYPE)
				{
						LastErrorNo(LYR_InvalidDevMode,1);
						return -1;
				}

				if(LY_StartConnectTime == 0)
						LY_StartConnectTime = aTimestamp;

				unsigned long Timestamp = (aTimestamp - LY_StartConnectTime)/1000;
				nRet =  P2pPushData(aDataLevelPos, aDataBuffer, aBufferLength, Timestamp, apFrameSampleType);
		}
		else            //rtmp
		{
				nRet =  RtmpPushData(aDataBuffer, aBufferLength, aTimestamp, apFrameSampleType);
		}

		int err = -1;
		if(nRet != LYR_OK)
		{
				err = (nRet==LYR_FrameTypeNotSupported) ? LYR_FrameTypeNotSupported:LYR_OperationTimeout;
#if 0
				if(nRet != LYR_FrameTypeNotSupported)
						err = LYR_OperationTimeout;
				else
						err = nRet;	
#endif	
				LastErrorNo(err,1);
				return -1;
		}

		LastErrorNo(LYR_OK,1);
		return nRet;
}

int SetRtmpConnectUrl(unsigned char *aRtmpInfo)
{
		//printf("get rtmp ip: %d %d %d %d %d %d \n",data[0],data[1],data[2],data[3],data[4],data[5]);
		if((aRtmpInfo[0]==0x00) && (aRtmpInfo[1]==0x00) && (aRtmpInfo[2]==0x00) && (aRtmpInfo[3]==0x00))
		{
				Send_Log("get rtmp server ip is 0.0.0.0",LOG_TYPE_DEVICE);
				//cmsprintf("========= ========= get rtmp addr is 000000 =========== \n");
				return -1;
		}

		unsigned short port = *(unsigned short *)(aRtmpInfo+4);
		char url[60];
		memset(url,0,60);
		sprintf(url,"rtmp://%d.%d.%d.%d:%d/live/%d",aRtmpInfo[3],aRtmpInfo[2],aRtmpInfo[1],aRtmpInfo[0],port,platform_global_config.cid);
		strcpy(platform_global_config.rtmp_url,url);
		//printf("rtmp url port:%d :%s\n",port,platform_global_config.rtmp_url);

		return 0;
}


int ConnectToServer(char aMode, RTMPMetaData aMetadata)
{
		if((s_start_cloud_flag == 0) || (rtmpopenflag == 1))
		{
				LastErrorNo(LYR_InvalidDevMode,1);
				return -1;
		}	

		if(getDeviceStatus() != 1)
		{
				LastErrorNo(LYR_InvalidDevMode,1);
				return -1;
		}

		int i=0;
		int nRet = -1;
		LYRecording_Timestamp = 0;
		if((aMode == RTMP_PUBLICLIVE_TYPE) || (aMode == RTMP_PUBLIC_STORAGE_TYPE))
				LY_PublicLiveFlag = 1;

		unsigned char ServerConnectInfo[32]={0};
		//printf("===== amode ==== %d\n",aMode);
		unsigned char ret = Core_ConnectToServer(aMode, ServerConnectInfo);
		if(ret != 4)
		{
				printf("ConnectToServer Core_ConnectToServer ret=%d \n",ret);
				LastErrorNo(LYR_Unknown,1);
				return -1;
		}

		if(SDK_PopConfig_flag)
		{
				for(i=0; i<10; i++)
				{
						nRet = RespondConfigMsg(0);
						if(nRet == 0)
								break;
				}
				if(nRet == 0)
						SDK_PopConfig_flag = 0;
				else
						goto failed;
		}

		nRet =  SetRtmpConnectUrl(ServerConnectInfo);
		if(nRet == -1)
		{
				printf("ConnectToServer SetRtmpConnectUrl ret=%d \n",nRet);
				usleep(10000);
				goto failed;
		}

		if(LY_PublicLiveFlag)
		{
				for(i=0;i<10;i++)
				{
						nRet =  HttpPostRTMPURL();
						if(nRet == 0)
								break;
						else
								usleep(500);
				}
				printf("ConnectToServer HttpPostRTMPURL ret=%d \n",nRet);
				if(nRet != 0)
						goto failed;

		}

		nRet = StartRtmpServer(aMetadata);
		if(nRet == 0)
		{
				rtmpopenflag = 1;
				if((aMode == RTMP_STORAGE_TYPE) || (aMode == RTMP_PUBLIC_STORAGE_TYPE))
				{
						//printf("========== send get image server addr ==========\n");
						getJPGServerIP(0);
				}
				printf("ConnectToServer StartRtmpServer ret=%d \n",nRet);
				LastErrorNo(LYR_OK,1);
				return 0;
		}

failed:
		Disconnect();
		LastErrorNo(LYR_OperationTimeout,1);
		return -1;
}


int  Disconnect()
{
		int ret = -1, i=0;

		if(LY_PublicLiveFlag)
		{
				ret = HttpRemoveRTMPURL();
				printf("DisConnectToServer HttpRemoveRTMPURL ret=%d \n",ret);	
		}

		LY_PublicLiveFlag = 0;
		LYRecording_Timestamp = 0;

		if (rtmpopenflag == 1) {
				//rtmpopenflag = 0;
				printf("DisConnectToServer StopRtmpServer 111111 \n");
				StopRtmpServer();
				printf("DisConnectToServer StopRtmpServer 222222\n");
		}
		ret = Core_Disconnect();
		printf("DisConnectToServer Core_Disconnect ret=%d  status:%d\n",ret,getDeviceStatus());
#if 1
		if(SDK_PopConfig_flag && rtmpopenflag && (SDK_Status == 0))
		{
				for(i=0; i<10; i++)
				{
						ret = RespondConfigMsg(0);
						if(ret == 0)
								break;
				}
				if(ret == 0)
						SDK_PopConfig_flag = 0;

		}
#endif
		RTMP_Upload = 0;
		rtmpopenflag = 0;
end:
		LastErrorNo(LYR_OK,1);
		return 0;
}


int  PostPicture(char* aDataBuffer, long aBufferLength, int aTimeStamp, int aImageType, int aTimeOut)
{
		if(aDataBuffer == NULL)
		{
				LastErrorNo(LYR_InvalidParameter,1);	
				return -1;
		}

		int ret = -1;
		char token[DEVICE_TOKEN_SIZE] = {0};
		int token_len = GetDeviceToken(token, sizeof(token));
		if (token_len == -1)
				return -1;

		//printf("post image type: %d\n", aImageType); 

		//recording 
		if((aImageType == IMAGE_STORAGE_TYPE) || (aImageType == IMAGE_ALARM_TYPE))//1
		{
				int i=0;
				char server_ip[50]={0};

				if(aImageType == IMAGE_ALARM_TYPE)
						ret =  http_post_image(platform_global_config.web_server_ip, platform_global_config.web_server_port, USE_SSL, token, platform_global_config.hashid, aTimeStamp, aImageType, aDataBuffer, aBufferLength);

				//post public image
				if(LY_PublicLiveFlag)
				{
						//printf("post device updata pic url:%s\n",post_url);
						ret =  http_post_image(platform_global_config.web_server_ip, platform_global_config.web_server_port, USE_SSL, token, platform_global_config.hashid, aTimeStamp, IMAGE_COVER_TYPE, aDataBuffer, aBufferLength);
						if((aTimeStamp - LYRecording_Timestamp) >= 300)
						{
								LYRecording_Timestamp = (long)aTimeStamp;
						}
						else
								goto end;
				}


				//post recording image
				for(i=0; i<5; i++)
				{
						//printf("post device recording pic url:%s\n",post_url);
						ret =  http_post_image(platform_global_config.rtmp_record_imgAddr, platform_global_config.rtmp_record_imgPort, USE_SSL, token, platform_global_config.hashid, aTimeStamp, IMAGE_STORAGE_TYPE, aDataBuffer, aBufferLength);
						if(ret == 0)
								break;
						else
								sleep(1);
				}
		}
		else
		{
				//printf("post device updata pic url:%s\n",post_url);
				ret = http_post_image(platform_global_config.web_server_ip, platform_global_config.web_server_port, USE_SSL, token, platform_global_config.hashid, aTimeStamp, aImageType, aDataBuffer, aBufferLength);
		}

end:
		LastErrorNo(ret, 1);	

		char msg[64]={0};
		if(ret == 200)
		{
				sprintf(msg,"post picture ok id:%s",platform_global_config.hashid);
				//Send_Log((const char *)msg,LOG_TYPE_DEVICE);
				return 0;
		}
		else
		{
				sprintf(msg,"post picture failed(%d) id:%s",ret,platform_global_config.hashid);
				Send_Log((const char *)msg,LOG_TYPE_DEVICE);
				return -1;
		}
}

int HttpPostRTMPURL()
{
		char token[DEVICE_TOKEN_SIZE] = {0};
		int token_len = GetDeviceToken(token, sizeof(token));
		if (token_len == -1)
				return -1;

		int nRet = -1;
		char url[60];
		memset(url,0,60);
		int flag = platform_global_config.cid % 10;
		sprintf(url,"rtmp://rtmp%d.%s%d",flag,PublicTransferServerAddr,platform_global_config.cid);

		char *Rtmp_json = NULL;
		cJSON * root = NULL;
		/* Add simple file section */    
		/*json root*/
		root=cJSON_CreateObject();
		/*json of rtmp url.*/
		cJSON_AddStringToObject(root, "cid", platform_global_config.hashid);
		cJSON_AddStringToObject(root, "rtmp", url);
		cJSON_AddStringToObject(root, "type", "camera");

		/*json output.*/
		Rtmp_json = cJSON_PrintUnformatted(root);

		char msg[62]={0};
		memset(msg,0,62);
		unsigned char post_url[300] = {0};
		//sprintf(post_url,"/API/cameras/public/addr");
		strcpy(post_url,"/API/cameras/public/addr");
		nRet = http_post_jsonData(platform_global_config.web_server_ip, platform_global_config.web_server_port, USE_SSL, token, post_url, Rtmp_json, strlen(Rtmp_json));
		//nRet = http_post_jsonData("192.168.2.221",  443, USE_SSL, token, post_url, Rtmp_json, strlen(Rtmp_json));
		//printf("public rtmp:%s\n",url);
		//printf("SDK:D_HttpPostRTMPURL httppost return:%d\n",nRet);
		cJSON_Delete(root);
		free(Rtmp_json);
		Rtmp_json = NULL;

		sprintf(msg,"post rtmp url (%d) id:%s",nRet,platform_global_config.hashid);
		Send_Log((const char *)msg,LOG_TYPE_DEVICE);

		LastErrorNo(nRet,1);	
		if(nRet == 200)
				return 0;
		else
				return -1;
}

int HttpRemoveRTMPURL()
{
		char token[DEVICE_TOKEN_SIZE] = {0};
		int token_len = GetDeviceToken(token, sizeof(token));
		if (token_len == -1)
				return -1;

		char msg[62]={0};
		memset(msg,0,62);
		unsigned char post_url[300] = {0};
		sprintf(post_url,"/API/cameras/public/%s/addr/remove",platform_global_config.hashid);
		int nRet = http_post_jsonData(platform_global_config.web_server_ip, platform_global_config.web_server_port, USE_SSL, token, post_url, NULL, 0);

		sprintf(msg,"remove rtmp url (%d) id:%s",nRet,platform_global_config.hashid);
		Send_Log((const char *)msg,LOG_TYPE_DEVICE);

		LastErrorNo(nRet,1);	
		if(nRet == 200)
				return 0;
		else
				return -1;

}


int getMessageJson(char *aMessage, int aNotifyThirdPartyPlatform, char *apJson, unsigned int aJson_size)
{
		char *out = NULL;
		int out_len = 0;

		/*json root*/
		cJSON * root=cJSON_CreateObject();
		/*json of timestamp.*/
		//cJSON_AddItemToObject(root, "report", json_report);
		cJSON_AddStringToObject(root, "from", platform_global_config.hashid);
		cJSON_AddStringToObject(root, "msg", aMessage);
		cJSON_AddNumberToObject(root, "callback", aNotifyThirdPartyPlatform ? 1:0);
		// callback是整数不是字符串

		/*json output.*/
		out=cJSON_PrintUnformatted(root);
		out_len=strlen(out);
		if (apJson != NULL && aJson_size >= out_len) {
				memcpy(apJson, out, out_len);
				cJSON_Delete(root);
				free(out);
				out = NULL;
				return 0;
		}

		cJSON_Delete(root);
		free(out);
		out = NULL;
		return -1;
}

int  SendMessage(const char *aPostURL,const char *aMessage, unsigned int aMessageLength, int aNotifyThirdPartyPlatform)
{
		int ret = -1;
		/*printf("msg= %d %d %d %d %d %d, len=%d\n",aMessage[0],aMessage[1],aMessage[2],aMessage[3],aMessage[4],aMessage[5],aMessageLength);*/
		char token[DEVICE_TOKEN_SIZE] = {0};
		int token_len = GetDeviceToken(token, sizeof(token));
		if (token_len == -1)
				return -1;

		char message[MAX_MESSAGE_B64_BUFFER];
		unsigned int length = sizeof(message);
		if (aMessageLength > MAX_MESSAGE_SIZE) {
				aMessageLength = MAX_MESSAGE_SIZE;
		}
		if (NULL == b64encode((const unsigned char*)aMessage, aMessageLength, message, &length)) {
				Send_Log("push msg b64ecode failed",LOG_TYPE_DEVICE);
				LastErrorNo(LYR_Unknown,1);	
				return -1;
		}
		char msg_json[512]={0};
		ret = getMessageJson(message, aNotifyThirdPartyPlatform, msg_json, (unsigned int)sizeof(msg_json));
		if(ret != 0) {
				LastErrorNo(LYR_Unknown,1);	
				return ret;
		}

		//printf("msg json:%s, len:%d\n",msg_json,strlen(msg_json));

		ret = http_post_jsonData(platform_global_config.web_server_ip, platform_global_config.web_server_port, USE_SSL, token, aPostURL,  msg_json, strlen(msg_json));
		LastErrorNo(ret,1);	

		char msg[64]={0};
		if(ret == 200)
		{
				sprintf(msg,"push message ok id:%s",platform_global_config.hashid);
				//Send_Log((const char *)msg,LOG_TYPE_DEVICE);
				return 0;
		}
		else
		{
				sprintf(msg,"push message failed id:%s",platform_global_config.hashid);
				//Send_Log((const char *)msg,LOG_TYPE_DEVICE);
				return -1;
		}
}

int  PushMessage(const char *aMessage, unsigned int aMessageLength, int aNotifyThirdPartyPlatform)
{
		char post_url[500];
		memset(post_url,0,sizeof(post_url));
		strcpy(post_url,"/API/message/cameras/touser");
		//http://121.41.118.167:8006/API/message/cameras/touser   
		return SendMessage(post_url, aMessage, aMessageLength, aNotifyThirdPartyPlatform);
}

int  RespondConfigMsg(int aRespondCode)
{
		int ret = -1;
		/*printf("msg= %d %d %d %d %d %d, len=%d\n",aMessage[0],aMessage[1],aMessage[2],aMessage[3],aMessage[4],aMessage[5],aMessageLength);*/
		char token[DEVICE_TOKEN_SIZE] = {0};
		int token_len = GetDeviceToken(token, sizeof(token));
		if (token_len == -1)
				return -1;

		char msg_json[512]={0};
		sprintf(msg_json,"{\"code\": %d}",aRespondCode);

		char post_url[500];
		memset(post_url,0,sizeof(post_url));
		sprintf(post_url,"/API/cameras/%s/config/confirm",platform_global_config.hashid);

		ret = http_post_jsonData(platform_global_config.web_server_ip, platform_global_config.web_server_port, USE_SSL, token, post_url,  msg_json, strlen(msg_json));
		printf("RespondConfigMsg msg json :%s,  err: %d\n", msg_json, ret);

		char msg[64]={0};
		sprintf(msg,"respond config msg(%d) id:%s",ret,platform_global_config.hashid);
		Send_Log((const char *)msg,LOG_TYPE_DEVICE);

		LastErrorNo(ret,1);	
		if(ret == 200)
				return 0;
		else
				return -1;
}


int  SetDeviceConfig(const char *aConfig, unsigned int aConfigLength)
{
		int ret = -1;
		/*printf("msg= %d %d %d %d %d %d, len=%d\n",aMessage[0],aMessage[1],aMessage[2],aMessage[3],aMessage[4],aMessage[5],aMessageLen);*/
		char token[DEVICE_TOKEN_SIZE] = {0};
		int token_len = GetDeviceToken(token, sizeof(token));
		if (token_len == -1)
				return -1;

		char config[MAX_MESSAGE_B64_BUFFER];
		unsigned int length = sizeof(config);
		if (aConfigLength > MAX_MESSAGE_SIZE) {
				aConfigLength = MAX_MESSAGE_SIZE;
		}
		if (NULL == b64encode((const unsigned char*)aConfig, aConfigLength, config, &length)) {
				Send_Log("set_dev_cfg b64ecode failed",LOG_TYPE_DEVICE);
				LastErrorNo(LYR_Unknown,1);	
				return -1;
		}

		/*json root*/
		cJSON * root=cJSON_CreateObject();
		/*json of timestamp.*/
		cJSON_AddStringToObject(root, "cid", platform_global_config.hashid);
		cJSON_AddStringToObject(root, "config", config);

		/*json output.*/
		char *cfg_json=cJSON_PrintUnformatted(root);
		if (NULL == cfg_json) {
				cJSON_Delete(root);
				LastErrorNo(LYR_Unknown,1);	
				return -1;
		}

		//printf("msg json:%s, len:%d\n",msg_json,strlen(msg_json));
		char post_url[500];
		memset(post_url,0,sizeof(post_url));
		strcpy(post_url,"/API/cameras/configs");
		//http://121.41.118.167:8006/API/message/cameras/touser   

		ret = http_post_jsonData(platform_global_config.web_server_ip, platform_global_config.web_server_port, USE_SSL, token, post_url,  cfg_json, strlen(cfg_json));
		//ret = http_post_jsonData("192.168.2.221", 443, USE_SSL, token, post_url,  cfg_json, strlen(cfg_json));

		if (cfg_json) {
				cJSON_Delete(root);
				free(cfg_json);
				cfg_json = NULL;
		}

		char msg[64]={0};
		sprintf(msg,"set device config(%d) id:%s",ret,platform_global_config.hashid);
		Send_Log((const char *)msg,LOG_TYPE_DEVICE);

		LastErrorNo(ret,1);	
		if(ret == 200)
				return 0;
		else
				return -1;
}

int  SetDeviceInfo(const char *aDataInfo, unsigned int aDataLength)
{
		int ret = -1;
		char token[DEVICE_TOKEN_SIZE] = {0};
		int token_len = GetDeviceToken(token, sizeof(token));
		if (token_len == -1)
				return -1;

#if 0
		char config[MAX_MESSAGE_B64_BUFFER];
		unsigned int length = sizeof(config);
		if (aDataLength > MAX_MESSAGE_SIZE) {
				aDataLength = MAX_MESSAGE_SIZE;
		}
		if (NULL == b64encode((const unsigned char*)aDataInfo, aDataLength, config, &length)) {
				Send_Log("set_dev_cfg b64ecode failed",0x0301);
				return -1;
		}
#endif

		/*json root*/
		cJSON * root=cJSON_CreateObject();
#if 0
		/*json of extra data.*/
		cJSON_AddStringToObject(root, "extra", config);
#else
		cJSON_AddStringToObject(root, "extra", aDataInfo);
#endif

		/*json output.*/
		char *cfg_json=cJSON_PrintUnformatted(root);
		if (NULL == cfg_json) {
				cJSON_Delete(root);
				LastErrorNo(LYR_Unknown,1);	
				return -1;
		}


		//printf("msg json:%s, len:%d\n",msg_json,strlen(msg_json));
		char post_url[500];
		memset(post_url,0,sizeof(post_url));
		sprintf(post_url,"/API/cameras/%s/extra",platform_global_config.hashid);

		ret = http_post_jsonData(platform_global_config.web_server_ip,platform_global_config.web_server_port, USE_SSL, token, post_url,  cfg_json, strlen(cfg_json));
		//ret = http_post_jsonData("192.168.2.221", 443, USE_SSL, token, post_url,  cfg_json, strlen(cfg_json));

		if (cfg_json) {
				cJSON_Delete(root);
				free(cfg_json);
				cfg_json = NULL;
		}

		char msg[64]={0};
		sprintf(msg,"set device info(%d) id:%s",ret,platform_global_config.hashid);
		Send_Log((const char *)msg,LOG_TYPE_DEVICE);

		LastErrorNo(ret,1);	
		if(ret == 200)
				return 0;
		else
				return -1;
}


int  ConvertCidToHashID(unsigned long aSrcCid, char *apHashID,int HashIdLength)
{
		if((aSrcCid == 0) || (apHashID == NULL))
				return -1;

		char hashID[50];
		memset(hashID,0,50);
		GetDwordHash(aSrcCid, hashID);
		char hash[50];
		memset(hash,0,50);
		int i;
		for(i=0;i<8;i++)
		{
				sprintf(hash+i*2,"%02X",(unsigned char )hashID[i]);
		}
		printf("hashid :%s, len:%d\n",hash,strlen(hash));
		int len = strlen(hash);


		if(HashIdLength < len)
				return -1;

		strncpy(apHashID,hash,len);

		return len;
}

/*******************************/
//该版本兼容新接口和旧接口
//以下为老接口的定义
/*******************************/

int D_StartCloudService(const char*app_id, const char* aSN, const char *aHashID,void *apData, MessageCallBack apMessageCallBack)
{
		return StartCloudService(app_id, aSN, aHashID, apData, apMessageCallBack);
}

int  D_StartCloudService2(const char* aConfigString, void *apData, MessageCallBack apMessageCallBack)
{
		return StartCloudService2(aConfigString, apData, apMessageCallBack);
}

void  D_StopCloudService()
{
		StopCloudService();
}
char* D_GetStatus()
{
		return GetDeviceStatus();
}

float D_GetPlatformVersion()
{
		return GetPlatformVersion();
}
int D_GetDeviceToken(char *aToken, unsigned int sizeOfToken)
{
		return GetDeviceToken(aToken, sizeOfToken);
}

int GetLastErrorNo()
{
		return LastErrorNo(0,0);
}

int D_PushData(unsigned long aDataLevelPos, const char *aDataBuffer, unsigned long aBufferLength, unsigned long long aTimestamp, unsigned char apFrameSampleType)
{
		return PushData(aDataLevelPos, aDataBuffer,aBufferLength,aTimestamp,apFrameSampleType);
}

char* D_PopData(unsigned long aDataLevelPos, unsigned long *apFrameSampleLength, unsigned long *apTimestamp, unsigned char *apFrameSampleType)
{
		return PopData(aDataLevelPos, apFrameSampleLength, apTimestamp, apFrameSampleType);
}

int  D_HttpPostPicture(int timestamp,char* image_buffer, long image_size, int image_type)
{
		return PostPicture(image_buffer, image_size, timestamp, image_type, 10);
}

int D_PushMessage(const char *aMessage, unsigned long aMessageLen, int is_callServer)
{
		return PushMessage(aMessage, aMessageLen, is_callServer);
}

int D_StartConnectToServer(char aMode, RTMPMetaData aMetaData)
{
		return ConnectToServer(aMode, aMetaData);
}

void D_SetRtmpAudioCallBack(void *apData,RtmpDataCallBack aRtmpAudioCall)
{
		SetRtmpDataCallBack(apData, aRtmpAudioCall); 
}

int D_Disconnect()
{
		return Disconnect();
}

int D_SetDeviceConfig(const char *aConfig, unsigned int aConfigLen)
{
		return SetDeviceConfig(aConfig, aConfigLen);
}

int D_SetDeviceExtraFields(const char *aData, unsigned int aDataLen)
{
		return SetDeviceInfo(aData, aDataLen);	
}

int D_QueryAlarmRecordInfo()
{
		return QueryAlarmRecordInfo();
}

void D_Send_Log(const char *msg)
{
		SendLogMessage(msg);
}
int  D_GetDevHashID(unsigned long aSrcCid, char *apHashBuffer,int HashIdLength)
{
		return ConvertCidToHashID(aSrcCid, apHashBuffer, HashIdLength);
}
