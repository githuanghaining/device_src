//#include "CameraAPI.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "rtmpSender.h"
#include <curl/curl.h>
#include "PusherClient.h"
#include "camera_log.h"
#include "Hash_alg.h"
#include "aes128.h"
#include "platform_cfg.h"
#include <openssl/aes.h>
#include "cJSON.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>


typedef int (*D_MessageCallBack)(void *apData, const char *aMessage);
int rtmpopenflag = 0;
volatile int PublicLiveFlag = 0;
static int log_flag =0;
static int retry_count =0;
platform_config_t platform_global_config;

unsigned long C_StartTime = 0;
unsigned int C_FrameRate;
unsigned long C_BitRate;

extern char RTMP_Enable_AES128;
extern unsigned int RTMP_C_FrameRate;
extern unsigned int RTMP_C_BitRate;

static void set_defalut_platform_config(platform_config_t* config)
{
    strcpy(config->rtmp_url,"rtmp://120.24.88.82/demo/999999");
    strcpy(config->rtmp_log_dir,"/media/mmcblk0p1/");
    strcpy(config->web_server_ip,"120.26.65.144");
    //strcpy(config->web_server_ip,"120.24.86.37");
    config->web_server_port = 8005;
    config->web_server_timeout = 5;
    config->cid = 0;
}

void D_Send_Log(const char *msg)
{
	Send_Log(msg,0x0301);
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
                Send_Log("fopen meminfo failed!",0x0301);
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
				Send_Log("fgets Mem return no data !",0x0301);
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
                        Send_Log("fgets data==== null!",0x0301);
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
		Send_Log(path,0x0301);
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
	sleep(70);
	log_flag = 1;
        Send_Log("start log msg_pthread success",0x0301);
	char msg[60]={0};
	char pid_fp[20];
	int pid = getpid();
	int fpcnt =0;
	while(log_flag)
	{
		fpcnt = Get_Allfd(pid);
		memset(msg,0,sizeof(msg));
		if(Get_Device_Meminfo(msg) == 0)
		{
			sprintf(pid_fp,",pid:%d,fd:%d",pid,fpcnt);
			strcat(msg,pid_fp);
			Send_Log((const char *)msg,0x0301);
		}
		sleep(60);
	}

        Send_Log("log msg_pthread exit!",0x0301);
	pthread_exit(0);
}

void Create_log_pthread(const char *SN,const int aCid)
{
    	char log[60]={0};
    	sprintf(log,"sn:%s,cid:%d,StartCloudService",SN,aCid);
    	Send_Log(log,0x0301);
	
	if(log_flag == 0)
	{
		int err;
        	pthread_t tid;
        	pthread_attr_t attr_handle;
		pthread_attr_init(&attr_handle);
        	pthread_attr_setdetachstate(&attr_handle, PTHREAD_CREATE_DETACHED);
        	err = pthread_create(&tid,&attr_handle,Msg_Handler,NULL);
        	if(err)
        	{
			memset(log,0,sizeof(log));
			sprintf("sn:%s,cid:%d,create log pthread failed",SN,aCid);
                	Send_Log(log,0x0301);
                	return;
        	}

	}
}

int  D_StartCloudService(const char* aSN, const int aCid, void *apData, D_MessageCallBack apMessageCallBack)
{
    set_defalut_platform_config(&platform_global_config);
    char SN[25]={0};
    sprintf(SN,"Test%s",aSN);  
    char strconfig[500];
    memset(strconfig, 0, 500);
    if(aCid == 0)
    	sprintf(strconfig,"[Config]\r\nCID=\r\nSN=%s\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nIsSendBroadcast=0\r\nUdpSendInterval=2\r\n[Tracker]\r\nCount=3\r\nIP1=120.24.56.51\r\nPort1=80\r\nIP2=121.40.194.21\r\nPort2=80\r\nIP3=123.57.64.171\r\nPort3=80\r\n",SN);
    else
	sprintf(strconfig,"[Config]\r\nCID=%d\r\nSN=%s\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nIsSendBroadcast=0\r\nUdpSendInterval=2\r\n[Tracker]\r\nCount=3\r\nIP1=120.24.56.51\r\nPort1=80\r\nIP2=121.40.194.21\r\nPort2=80\r\nIP3=123.57.64.171\r\nPort3=80\r\n",aCid,SN);
    
    StartCloudService(strconfig, apData, apMessageCallBack);
  
    Create_log_pthread((const char *)SN,aCid);
    
    sleep(5);
    unsigned long nCid = 0;
    if(aCid == 0)
    {   //register
        //sleep(5);
        char config[256]={0};
	config[0]=0x03;
	config[2]=0x02;
        int nRet = CameraRegist(SN,config,&nCid);
        //cmsprintf("======= cid :%d nRet :%d =======\n",nCid,nRet);
        platform_global_config.cid = nCid;
        //return nCid;
    }
    else
    {   //login
	int count = 5;
        //int Status = 0;
        while(count--)
        {
                char *status = GetStatus();
                cJSON *root = cJSON_Parse(status);
                cJSON *login = cJSON_GetObjectItem(root, "LoginSucc");
                //printf("login ============ %d\n",login->valueint);
                if(login->valueint == 1)
                {
                        nCid = aCid;
                        break;
                }
                else
                {       sleep(1);
                        nCid = 0;
                }
        }
        platform_global_config.cid = nCid;
        //return Status;
    }   

        return nCid;
}
    
void  D_StopCloudService()
{
    Send_Log("D_StopCloudService",0x0301);
    log_flag = 0;
    StopCloudService();
}
    
char* D_GetStatus()
{
    return GetStatus();
}

int   D_PushMessage(unsigned long aID, const char *aMessage, unsigned long aMessageLen)
{
    PushMessage(aID,aMessage,aMessageLen);
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
                                return pTmp;
                                //return pTmp+4;
                        }
    }

    return NULL;
}

char* findIFrameOffset(const char* p_data,int len)
{
    int i;
    for(i=0;i<len;i++){
            char* pTmp = p_data+i;
            if(i+5 >=len)
                return NULL;

                        if(frame_type(pTmp) == 5){
                                //return pTmp+4;
                                return pTmp;
                        }
    }

    return NULL;
}


int   D_PushData(unsigned long aDataLevelPos, const char *aDataBuffer,  unsigned long  aBufferLength, unsigned long aTimestamp, unsigned char apFrameSampleType)
{
	int ret = 0;
	char type = frame_type(aDataBuffer);
	//printf(" type:%d, data src: %x,%x,%x,%x,%x,%x,%x,%x,%x,%x\n",type,*(aDataBuffer),*(aDataBuffer+1),*(aDataBuffer+2),*(aDataBuffer+3),*(aDataBuffer+4),*(aDataBuffer+5),*(aDataBuffer+6),*(aDataBuffer+7),*(aDataBuffer+8),*(aDataBuffer+9));
        if(type==7){                    //first is sps
                int spsLen;
        	int ppsLen;
        	int seiLen;
        	int iframeLen;
	
        	char* pSPS = findSPSOffset(aDataBuffer,aBufferLength);
        	char* pPPS = findPPSOffset(aDataBuffer,aBufferLength);
        	char* pIFrame = findIFrameOffset(aDataBuffer,aBufferLength);
        	int tmpLen = pIFrame-pPPS;
        	char* pSEI = findSEIOffset(pPPS,tmpLen);

        	if(pSEI){
                	spsLen = pPPS - pSPS;
                	ppsLen = pSEI - pPPS;
                	seiLen = pIFrame - pSEI;
                	iframeLen = aBufferLength - spsLen -ppsLen -seiLen;
        	}
        	else
        	{	
                        spsLen = pPPS - pSPS;
                	ppsLen = pIFrame - pPPS;
                	//ppsLen = pSEI - pPPS;
                	iframeLen = aBufferLength - spsLen -ppsLen;
        	}
		
#ifdef ENABLE_AES128
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
		ret = PushData(aDataLevelPos,pSPS,spsLen,aTimestamp,NALU_TYPE_SPS);//7
		ret = PushData(aDataLevelPos,pPPS,ppsLen,aTimestamp,NALU_TYPE_PPS);//8
		ret = PushData(aDataLevelPos,pIFrame,iframeLen,aTimestamp,NALU_TYPE_IDR);//5
        }
	else if(type==1){                       //p frame
                if(aBufferLength>4){
                      ret = PushData(aDataLevelPos,aDataBuffer,aBufferLength,aTimestamp,NALU_TYPE_SLICE);//1
                }
        }
	else 
	{	//else if(apFrameSampleType == NALU_TYPE_AUD)
		ret = PushData(aDataLevelPos,aDataBuffer,aBufferLength,aTimestamp,apFrameSampleType);
		//printf("send aac  ===== length:%ld, time stamp: %ld , frame type: %x , type1 :%x\n",aBufferLength,aTimestamp,apFrameSampleType,type);
	}
	return ret;
}


char* D_PopData(unsigned long aDataLevelPos, unsigned long *apFrameSampleLength, unsigned long *apTimestamp, unsigned char *apFrameSampleType)
{
    return PopData(aDataLevelPos,apFrameSampleLength,apTimestamp,apFrameSampleType);
}


int ConnectRTMP(audio_consume_pt RTMPPopDataCallBack)
{
    int ret = -1;
    if (rtmpopenflag == 0) {
		//cmsprintf("SDK:connect to rtmp server\n");
#if 1
		setDeviceType(1);
		//setLogDir(platform_global_config.rtmp_log_dir);
		ret = ConnectToRtmpServer((const char *)platform_global_config.rtmp_url,RTMPPopDataCallBack,1);
#else
		//setLogDir("./");
		setDeviceType(1);
    		char url[50];
    		memset(url,0,50);
    		sprintf(url,"rtmp://120.24.88.92:1935/demo/%d",platform_global_config.cid);
		ret = ConnectToRtmpServer(url,RTMPPopDataCallBack,1);
#endif
        rtmpopenflag = 1;
    }
    return ret;
}

void DisConnectRTMP()
{
    if (rtmpopenflag == 1) {
        rtmpopenflag = 0;
        DisconnectRtmpServer();
    }
    
}

int  D_StartRtmpServer(audio_consume_pt RTMPPopDataCallBack)
{
    return ConnectRTMP(RTMPPopDataCallBack);
}
    
void  D_StopRtmpServer()
{
    DisConnectRTMP();
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


unsigned long  T1= 0;
unsigned long  Tend = 0;
unsigned long  Tn_T1 = 0;
unsigned long  Tstart_end = 0;
unsigned long  Tend_start = 0;


void D_SendRTMPData(char * aDataBuffer,unsigned long aBufferLength, unsigned long aTimestamp,unsigned char apFrameSampleType)
{
    if (rtmpopenflag == 0)
        return;

    unsigned long  Tstart = 0;

    RTMP_Enable_AES128 = 0x00;
    Count_BitRate_FrameRate(aBufferLength,apFrameSampleType);

    aTimestamp = aTimestamp%0xFFFFFE;
    if(apFrameSampleType == NALU_TYPE_AUD)
    {
        SendOpus(aDataBuffer, aBufferLength,aTimestamp);
    }
    else if(apFrameSampleType == AAC_TYPE_INFO)
    {
		SendAacInfo(aDataBuffer, aBufferLength,aTimestamp);
		//printf("send aac info ===== length:%ld, time stamp: %ld\n",aBufferLength,aTimestamp);
    }
    else if(apFrameSampleType == AAC_TYPE_SAMPLE)
    {
		SendAAC(aDataBuffer, aBufferLength,aTimestamp);
		//printf("send aac sample ===== length:%ld, time stamp: %ld\n",aBufferLength,aTimestamp);
    }
    else
    {
	 	int ret = 0;
        	char type = frame_type(aDataBuffer);
        	if(type==7){                    //first is sps
			int spsLen;
                	int ppsLen;
                	int seiLen;
                	int iframeLen;

                	char* pSPS = findSPSOffset(aDataBuffer,aBufferLength);
                	char* pPPS = findPPSOffset(aDataBuffer,aBufferLength);
                	char* pIFrame = findIFrameOffset(aDataBuffer,aBufferLength);
                	int tmpLen = pIFrame-pPPS;
                	char* pSEI = findSEIOffset(pPPS,tmpLen);

                	if(pSEI){
                        	spsLen = pPPS - pSPS -4;
                        	ppsLen = pSEI - pPPS -4;
                        	seiLen = pIFrame - pSEI -4;
                        	iframeLen = aBufferLength - spsLen -ppsLen -seiLen -16;
                	}
                	else
                	{
                        	spsLen = pPPS - pSPS -4;
                		ppsLen = pIFrame - pPPS -4;
                        	//ppsLen = pSEI - pPPS -4;
                        	iframeLen = aBufferLength - spsLen -ppsLen -12;
                	}
			
#ifdef ENABLE_AES128
			if(PublicLiveFlag == 0)		//is not publicLive
			{
				RTMP_Enable_AES128 = 0x01;
				if(pIFrame)
        			{
            				unsigned char* encrypt_out;
            				unsigned int encrypt_len;

        				int ret = D_aes_encrypt((unsigned char*)(pIFrame+4+1),(unsigned int)(iframeLen-1 - (iframeLen-1)%16),&encrypt_out,&encrypt_len);

        				memcpy(pIFrame+4+1,encrypt_out,encrypt_len);
            				free(encrypt_out);
				}
        		}
#endif
			Tstart = Sys_GetTickCount();
			if(T1 == 0 || T1 > Tstart)	
				T1 = Tstart;
			else
				Tend_start += (Tstart - Tend);


			//printf("D_aes_encrypt end .........sps:%d, pps:%d, iframe:%d\n",spsLen,ppsLen,iframeLen);
			SendNal(pSPS+4,spsLen,aTimestamp);
        		SendNal(pPPS+4,ppsLen,aTimestamp);
			SendNal(pIFrame+4,iframeLen,aTimestamp);
			//printf("D_aes_encrypt end iframe:%x %x %x %x %x %x %x %x %x %x\n",*(pIFrame+4),*(pIFrame+4+1),*(pIFrame+4+2),*(pIFrame+4+3),*(pIFrame+4+4),*(pIFrame+4+5),*(pIFrame+4+6),*(pIFrame+4+7),*(pIFrame+4+8),*(pIFrame+4+9));
    		}
        	else if(type==1)
		{   
	                //p frame	
			if(aBufferLength>4)
			{
				Tstart = Sys_GetTickCount();
				if(T1 == 0 || T1 > Tstart)	
					T1 = Tstart;
				else
					Tend_start += (Tstart - Tend);

                		SendNal(aDataBuffer+4,aBufferLength-4,aTimestamp);
                	}
        	}
		else
		{
			Tstart = Sys_GetTickCount();
			if(T1 == 0 || T1 > Tstart)	
				T1 = Tstart;
			else
				Tend_start += (Tstart - Tend);
                	
			SendNal(aDataBuffer+4,aBufferLength-4,aTimestamp);
		}
	
        	Tend = Sys_GetTickCount();
		//printf("tend:%ld, t1:%ld\n",Tend,T1);
		Tn_T1 = Tend - T1;
		Tstart_end += (Tend - Tstart); 

		if(Tn_T1 >= 5000)
		{
			//printf(" === tn_t1:%ld, tstart_tend:%ld, tend_tstart:%ld\n",Tn_T1,Tstart_end,Tend_start);
			//send_log();
			char info[50]={0};
        		sprintf(info,"T5_T1:%ld, Ts_Te:%ld, Tpe_Tns:%ld",Tn_T1,Tstart_end,Tend_start);
        		Send_Log((const char *)info,0x0302);
			T1 = 0;
			Tend = 0;
			Tn_T1 = 0;
			Tstart_end = 0;
			Tend_start = 0;
		}

	}
}


int D_StartConnectToServer(char aMode, unsigned char aAreaID)
{
	//return StartConnectToServer(aMode,aAreaID);
	if(aMode == 0x02)
	{
		PublicLiveFlag = 1;
		//aAreaID:0x00 --- (0x00)small-scale; aAreaID:0x01--- (0xe0)large-scale
		if(aAreaID == 0x00)
			return StartConnectToServer(aMode,0x00);
		else
			return StartConnectToServer(aMode,0xe0);
	}
	else
		return StartConnectToServer(aMode,aAreaID);

}

int  D_Disconnect()
{
	PublicLiveFlag = 0;
	return Disconnect();
}

int D_SendGetDiskList()
{
	return sendGetDiskListCommand();
}

int http_post_file(char* ip,int port,int cid, int timestamp,int is_recording,char* image_buffer, long image_size)
{
    CURL *curl = NULL;
    CURLcode res;
    
    struct curl_httppost *post=NULL;
    struct curl_httppost *last=NULL;
    
    //http_msg("======http_post_file start=========");
    if(image_buffer == NULL || ip == NULL)
    {
        //http_msg("image_buffer == NULL || ip == NULL");
        Send_Log("image_buffer == NULL || ip == NULL",0x0301);
	return -1;
    }
    
    char hashID[50];
    memset(hashID,0,50);
    GetDwordHash(cid,hashID);
    char hash[50];
    memset(hash,0,50);
    int i;
    for(i=0;i<8;i++)
    {
        sprintf(hash+i*2,"%02X",(unsigned char )hashID[i]);
    }
//    printf("hashid :%s\n",hash);
    
    char post_url[500];
    memset(post_url,0,sizeof(post_url));
    sprintf(post_url,"http://%s:%d/API/cameras/%s/images/upload",ip,port,hash);
   
    //printf("post pic:%s\n",post_url);
 
    char timestamp_str[30];
    memset(timestamp_str,0,sizeof(timestamp_str));
    sprintf(timestamp_str,"%d",timestamp);
    
    char is_recording_str[10];
    memset(is_recording_str,0,sizeof(is_recording_str));
    if(is_recording == 1)
        sprintf(is_recording_str,"1");
    else
        sprintf(is_recording_str,"0");
    
    char filename[200];
    memset(filename,0,sizeof(filename));
    sprintf(filename,"%d_%d.jpg",cid,timestamp);
    
    /* Add simple file section */
    
    if(curl_formadd(&post, &last, CURLFORM_COPYNAME, "is_recording",CURLFORM_PTRCONTENTS,is_recording_str,CURLFORM_CONTENTSLENGTH,strlen(is_recording_str), CURLFORM_END) != 0)
    {
        //http_msg("curl_formadd is_recording error");
	Send_Log("curl_formadd is_recording error",0x0301);
        curl_formfree(post);
        return -1;
    }
    
    if(curl_formadd(&post, &last, CURLFORM_COPYNAME, "timestamp",CURLFORM_PTRCONTENTS,timestamp_str,CURLFORM_CONTENTSLENGTH,strlen(timestamp_str), CURLFORM_END) != 0)
    {
        //http_msg("curl_formadd timestamp error");
	Send_Log("curl_formadd timestamp error",0x0301);
        curl_formfree(post);
        return -1;
    }
    
    if( curl_formadd(&post, &last, CURLFORM_COPYNAME, "pic",CURLFORM_BUFFER, filename,CURLFORM_BUFFERPTR,image_buffer,CURLFORM_BUFFERLENGTH,image_size, CURLFORM_END) != 0)
    {
        //http_msg("curl_formadd pic error");
	Send_Log("curl_formadd pic error",0x0301);
        curl_formfree(post);
        return -1;
    }
    
    curl = curl_easy_init();
    if(curl == NULL)
    {
        //http_msg("curl_easy_init() error");
	Send_Log("curl_easy_init() error",0x0301);
        curl_formfree(post);
        return -1;
    }
    
    curl_easy_setopt(curl, CURLOPT_HEADER, 0);
    curl_easy_setopt(curl, CURLOPT_URL, post_url); /*Set URL*/
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, platform_global_config.web_server_timeout);
    
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
    {
        //http_msg("curl_easy_perform[%d] error", res);
        char err[50]={0};
	sprintf(err,"curl_easy_perform:%d,size:%d error",res,image_size);
	Send_Log((const char *)err,0x0301);
        curl_easy_cleanup(curl);
        curl_formfree(post);
        return -1;
    }
    
    //http_msg("http post success:filename:%s,ip:%s,port:%d,image_size:%d,is_recording:%d",filename,ip,port,image_size,is_recording);
    curl_easy_cleanup(curl);
    curl_formfree(post);
    return 0;
}
    
int  D_HttpPostPicture(int timestamp,char* image_buffer, long image_size, int is_recording_flag,unsigned char aAreaID)
{
    if(is_recording_flag)
    {
	char server_ip[50]={0};
	switch((int)aAreaID)
	{
		case 1:
			//shenzhen
    			strcpy(server_ip,"120.24.86.37");
			break;
		case 2:
			//hangzhou
    			strcpy(server_ip,"121.40.195.115");
			break;
		case 3:
			//beijing
    			strcpy(server_ip,"182.92.161.108");
			break;
		defualt:
			//area id error
			sprintf(server_ip,"post record picture,area id[%x] err",aAreaID);
    			Send_Log(server_ip,0x0301);
			break;
	}
    	return http_post_file(server_ip,platform_global_config.web_server_port,platform_global_config.cid,timestamp, is_recording_flag,image_buffer,image_size);
    }
    else
    {
    	return http_post_file(platform_global_config.web_server_ip,platform_global_config.web_server_port,platform_global_config.cid,timestamp, is_recording_flag,image_buffer,image_size);
    }
}

int httppost(char* ip,int port,char *hashID,char *rtmpUrl,int isremove)
{
    CURL *curl = NULL;
    CURLcode res;
    
    struct curl_httppost *post=NULL;
    struct curl_httppost *last=NULL;
    
    if( ip == NULL)
    {
        Send_Log("httppost ip = null",0x0301);
        return -1;
    }
    
    char post_url[500];
    memset(post_url,0,sizeof(post_url));
    if (isremove == 1)
        sprintf(post_url,"http://%s:%d/API/rtmp/%s/addr/remove",ip,port,hashID);
    else
        sprintf(post_url,"http://%s:%d/API/rtmp/addr",ip,port);
    
    /* Add simple file section */
    
    //printf("======param ========= :%s %s %d %s %d\n",post_url,hashID,strlen(hashID),rtmpUrl,strlen(rtmpUrl));
    
    if (isremove == 0)
    {
        if(curl_formadd(&post, &last, CURLFORM_COPYNAME, "hash_cid",CURLFORM_PTRCONTENTS,hashID,CURLFORM_CONTENTSLENGTH,strlen(hashID), CURLFORM_END) != 0)
        {
            Send_Log("curl_formadd hash_cid error\n",0x0301);
            curl_formfree(post);
            return -1;
        }
        
        if(curl_formadd(&post, &last, CURLFORM_COPYNAME, "addr",CURLFORM_PTRCONTENTS,rtmpUrl,CURLFORM_CONTENTSLENGTH,strlen(rtmpUrl), CURLFORM_END) != 0)
        {
            Send_Log("curl_formadd addr error\n",0x0301);
            curl_formfree(post);
            return -1;
        }
    }
    
    
    curl = curl_easy_init();
    if(curl == NULL)
    {
        Send_Log("curl_easy_init() error\n",0x0301);
        curl_formfree(post);
        return -1;
    }
    
    curl_easy_setopt(curl, CURLOPT_HEADER, 0);
    curl_easy_setopt(curl, CURLOPT_URL, post_url); /*Set URL*/
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, platform_global_config.web_server_timeout);
    
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
    {
        char err[50]={0};
	sprintf(err,"post url curl_easy_perform:%d,err",res);
	Send_Log((const char *)err,0x0301);
        curl_easy_cleanup(curl);
        curl_formfree(post);
        return -1;
    }
    
    //printf("http post success:ip:%s,port:%d,hashID:%s,url:%s\n",ip,port,hashID,rtmpUrl);
    curl_easy_cleanup(curl);
    curl_formfree(post);
    return 0;
}
    
void  D_HttpPostRTMPURL(char aMode, unsigned char aScaleID)
{
    char hashID[50];
    memset(hashID,0,50);
    GetDwordHash(platform_global_config.cid,hashID);
    char hash[50];
    memset(hash,0,50);
    int i,nRet;
    for(i=0;i<8;i++)
    {
        sprintf(hash+i*2,"%02X",(unsigned char )hashID[i]);
    }
    if(aMode == 0x02 && aScaleID == 0x01)
    {
    	char url[60];
    	memset(url,0,60);
    	sprintf(url,"rtmp://rtmp.public.topvdn.cn:1935/demo/%d",platform_global_config.cid);
    	nRet = httppost(platform_global_config.web_server_ip,platform_global_config.web_server_port,hash,url,0);
    }
    else
    	nRet = httppost(platform_global_config.web_server_ip,platform_global_config.web_server_port,hash,platform_global_config.rtmp_url,0);
    //cmsprintf("SDK:D_HttpPostRTMPURL httppost return:%d\n",nRet);

}

void  D_HttpRemoveRTMPURL()
{
    char hashID[50];
    memset(hashID,0,50);
    GetDwordHash(platform_global_config.cid,hashID);
    char hash[50];
    memset(hash,0,50);
    int i;
    for(i=0;i<8;i++)
    {
        sprintf(hash+i*2,"%02X",(unsigned char )hashID[i]);
    }
    int nRet = httppost(platform_global_config.web_server_ip,platform_global_config.web_server_port,hash,platform_global_config.rtmp_url,1);
    //cmsprintf("SDK:D_HttpRemoveRTMPURL  httppost return:%d\n",nRet);

}

int  D_SetRtmpConnectMessage(char *rtmpMessgae,char aMode, unsigned char aAreaID)
{
    unsigned char * rtmpmessage = rtmpMessgae;
    
    int i;
    unsigned char data[6];
    int result;
    for (i=0; i<6; i++) {
        sscanf(rtmpmessage+i*2,"%02X",&result);
        data[i] = result & 0xFF;
    }
   
/* 
    for(i=0;i<6;i++)
    {
        printf("%02X ",data[i]);
    }
    printf("\n");
*/
    Send_Log(data,0x0301);
#if  1 

    if(retry_count > 10)
	return -1;

    if(platform_global_config.cid == 0)
    {
	printf("D_SetRtmpConnectMessage cid = %d\n",platform_global_config.cid);
	retry_count++;
	D_Disconnect();
	sleep(2);
	D_StartConnectToServer(aMode, aAreaID);
        return 0;
    }

    if((data[0]==0x00) && (data[1]==0x00) && (data[2]==0x00) && (data[3]==0x00))
    {
	Send_Log("get rtmp server ip is 0.0.0.0",0x0301);
	retry_count++;
	D_Disconnect();
	sleep(5);
	D_StartConnectToServer(aMode, aAreaID);	
	return 0;
    }
#endif
    unsigned int ip = *(unsigned int *)rtmpmessage;
    char strIP[16];
    memset(strIP,0,16);
    //cmsprintf("....:%d.%d.%d.%d \n",data[3],data[2],data[1],data[0]);
    unsigned short port = *(unsigned short *)(data+4);
    
    //cmsprintf("strIP:%s,  port:%d \n",strIP,port);
    
    char url[60];
    memset(url,0,60);
//    sprintf(url,"rtmp://120.24.88.92/demo/%d",1003145);
//    sprintf(url,"rtmp://rtmp.public.topvdn.cn:1935/demo/%d",platform_global_config.cid);
//    sprintf(url,"rtmp://120.24.88.92:1935/demo/%d",platform_global_config.cid);
    sprintf(url,"rtmp://%d.%d.%d.%d:1935/demo/%d",data[3],data[2],data[1],data[0],platform_global_config.cid);
//    global_cofig.rtmp_open_flag = 1;
    strcpy(platform_global_config.rtmp_url,url);
   
    return 1;
}
