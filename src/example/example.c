#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/types.h>
#include <ifaddrs.h>

#include "cJSON.h"
#include "CloudOpenAPI.h"

static char device_sn[20]={0};
static int publicLiveFlag = 0;
static int isRecording = 0;
static int imageType = 0;
static int rtmpOpenFlag = 0;
static int imagePostFlag =0;
static int popDataFlag = 0;
static int isOpenCapture = 0;
static int configChange = 0;
static int config_Audio = 0;
static int config_Type = 0;
static int config_Bitrate = 300;
pthread_t pushData_pid;
pthread_t popData_pid;
pthread_t picture_pid;
pthread_t rtmp_pid; 

/*接收rtmp音频数据线程*/
void RTMP_DataCallBack(void *apData,char* aData,int aLen, char aType)
{
		if(aType == 1)//接收音频数据
				printf("recv audio data len:%d type:%d\n",aLen,aType);
		else if(aType == 2)//接收报警数据信息
				printf("recv alarm info\n");
} 

/*推送数据线程，数据的采集、处理在这里完成*/
void *PushFunc(void *adata)
{
		int ret = 0;
		char *dataBuffer;             
		unsigned long bufferLength= 0;
		unsigned long long timeStamp = 0;
		unsigned char frameSampleType;
		/*获取数据并处理*/
		/*	.
			.
			.
			*/
		/*将数据推送到网络*/
		printf("push data........\n");
		ret = PushData(0, dataBuffer, bufferLength, timeStamp, frameSampleType); 
}

/*接收数据线程，接收到的数据处理，播放在这里完成*/
void *RecvFunc(void *adata)
{
		char *pFrame;
		unsigned long frameSampleLength= 0;
		unsigned long timeStamp = 0;
		unsigned char frameSampleType;
		/*接收数据*/
		popDataFlag = 1;
		while(popDataFlag)
		{
				pFrame = PopData(0, &frameSampleLength, &timeStamp, &frameSampleType);                       
				/*	.
					.
					.
					*/
		}
		pthread_exit(0);
}
void *PostPictureFunc(void *adata)
{ 
		//发送截图,截图每5分钟更新一张
		int ret = -1; 
		long image_size = 0;
		int updateTime = 300; /*300s*/
		char* image_buffer;
		int postTimeout = 10;/*10s*/
		unsigned long image_timestamp = 0;   
		imagePostFlag = 1;
		while(imagePostFlag)
		{                 
				ret = PostPicture( image_buffer, image_size, image_timestamp,imageType,postTimeout);                         
				sleep(updateTime); 
		}
		pthread_exit(0);
}

void OpenCapture()
{
		int ret = pthread_create(&pushData_pid, NULL, (void *)PushFunc, NULL);
		if(ret != 0) 
				printf("push_thread create failed !\n");
		isOpenCapture = 1;
}

void CloseCapture()
{
		popDataFlag = 0; 
		isOpenCapture = 0;
}

/*为了避免阻塞平台的消息回调，这里开一个线程专门处理连接和断开连接相关操作*/
int rtmpWorking = 1;
void *RtmpWorkingThread(void *arg)
{
		RTMPMetaData rtmpMetadata = {0};
		int ret = -1;
		while(rtmpWorking)
		{
				/*更改配置后需要重新连接rtmp服务，需要将的当前的采集、播放工作停止，停止当前开启的rtmp服务*/
				if(configChange)
				{
						if(isOpenCapture)
						{
								Disconnect();
								CloseCapture();
						}
						if(rtmpOpenFlag)
						{
								ret = ConnectToServer(config_Type,rtmpMetadata);
								if(ret != 0)
								{
										usleep(100);
										continue;
								}
								OpenCapture();                       
						}
						configChange = 0;
				}
				else
				{
						usleep(500);
				}
		}
		if(isOpenCapture)
		{
				Disconnect();
				CloseCapture();
		}
		return NULL;
}

/*消息回调函数*/
int PopMessage(void *apData, const char *aMessage)
{
		cJSON *root = cJSON_Parse(aMessage);
		cJSON *name = cJSON_GetObjectItem(root, "name");
		cJSON *message = cJSON_GetObjectItem(root, "message");
		int ret =0; 
		if (memcmp("ConnectionAcceptted", name->valuestring, strlen(name->valuestring)) == 0)
		{
				if(!rtmpOpenFlag)
				{
						/*发送数据指令，开启推送数据工作线程*/  
						OpenCapture();
				}
		}
		else if (memcmp("ConnectionClosed", name->valuestring, strlen(name->valuestring)) == 0)
		{
				if(!rtmpOpenFlag)
				{
						/*停止推送数据*/
						CloseCapture();
						/*停止接收数据*/
						popDataFlag = 0;
				}
		}
		else if (memcmp("StartPopData", name->valuestring, strlen(name->valuestring)) == 0)
		{
				/*接收数据指令，开启接收数据工作线程*/    
				ret = pthread_create(&popData_pid, NULL, (void *)RecvFunc, NULL);
				if(ret != 0) 
						printf("pop_thread create failed !\n");
		}
		else if (memcmp("PopMessage", name->valuestring, strlen(name->valuestring)) == 0)
		{
				//消息透传
				int len = strlen(message->valuestring);
				printf(" ... message : %s, len: %d\n",message->valuestring,len);
				printf("........................ popMessage ...................\n");
		}
		else if (memcmp("PopConfig", name->valuestring, strlen(name->valuestring)) == 0)
		{
				printf("message->valuestring === %s\n",message->valuestring);
				unsigned char * cfgMessage = message->valuestring;
				int i;
				unsigned char config[256];
				int result;
				for (i=0; i<256; i++) {
						sscanf(cfgMessage+i*2,"%02X",&result);
						config[i] = result & 0xFF;
				}
				int bitrate = config[0];// bitrate 1---1m;2---500k;3---300k;
				int audio = config[1];  // audio enable 0---off; 1----on;
				int nType = config[4];
				config_Audio = audio;
				config_Bitrate = bitrate;
				if(config_Type == nType)
				{
						printf("========== the same config type ==========\n");
						cJSON_Delete(root);
						return 0;
				}
				if(nType == 4)
				{
						//公众+录像 ；rtmp流
						publicLiveFlag = 1;
						isRecording = 1;
						rtmpOpenFlag = 1;
						imageType = 1;
				}
				else if(nType == 3)
				{
						//录像，rtmp流
						publicLiveFlag = 0;
						isRecording = 1;
						rtmpOpenFlag = 1;
						imageType = 1;
				}
				else if(nType == 2)
				{
						//公众，rtmp流
						publicLiveFlag = 1;
						isRecording = 0;
						rtmpOpenFlag = 1;
						imageType = 2;
				}
				else if(nType == 0)
				{
						//待命状态,等待私有连接
						publicLiveFlag = 0;
						isRecording = 0;
						rtmpOpenFlag = 0;
						imageType = 2;
				}
				config_Type = nType;
				configChange = 1;
		}
		cJSON_Delete(root);
		return 0;
}

int main(int argc, char **argv)
{     
		//注意：必须要忽略SIGPIPE信号 
		signal(SIGPIPE,SIG_IGN);
		if(argc != 3)
		{
				printf("Usage:./main [Device_SN(serial number)] [CID(platform cid)]\n");
				return 0;
		}     

		int ret = -1;    
		const char *app_id = "Test";
		memset(device_sn, 0, 20);
		strcpy(device_sn,argv[1]);
		const char *cid = argv[2];
		isRecording = 0;
		isOpenCapture = 0;
		imageType = 2;	

		//1.开启云平台
		while(1)
		{              
				ret = StartCloudService(app_id,device_sn,cid,NULL,PopMessage);
				if(ret == 0)
						break;
				else
				{
						int err = GetLastErrorNo();
						printf("StartCloudService  ret = %d, err= %d\n",ret,err);
						sleep(1);
				}
		}
		if(ret == 0)
		{
				char token[128]={0};
				int len = GetDeviceToken(token, sizeof(token));
				printf("token :%s, len:%d\n",token,len);
				SetRtmpDataCallBack(NULL,RTMP_DataCallBack);
				printf("=========start mjpeg push==========\n");
				ret = pthread_create(&picture_pid, NULL, (void *)PostPictureFunc, NULL);
				if(ret != 0)
						printf("push picture thread create failed!.....\n");
				ret = pthread_create(&rtmp_pid,NULL,(void *)RtmpWorkingThread,NULL);
				if(ret != 0)
						printf("..... rtmp working thread create failed! .....\n");                       
		}
		while (1) 
		{
				sleep(10);
				//发送消息给app端
				unsigned char msg[]={0x01,0x02,0x03,0x04,0x05,0x06};
				ret = PushMessage(msg, 6, 0);
				printf("push message ret   ======== %d\n",ret);    
		}
		//停止上传截图              
		imagePostFlag = 0; 
		pthread_cancel(picture_pid);
		pthread_join(picture_pid, NULL);        
		//停止rtmp工作线程
		rtmpWorking = 0; 
		pthread_cancel(rtmp_pid);
		pthread_join(rtmp_pid, NULL);        
		//3.关闭云平台
		StopCloudService();
		return ret;
}
