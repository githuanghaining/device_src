#ifndef __RTMP_SENDER_H__
#define __RTMP_SENDER_H__

#include "rtmp_sys.h"
#ifdef NETPUSH
#include "../Src/System.h"
#else
#ifdef WIN32
#include "../Src/System.h"
#else
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <ctype.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <pthread.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>
#include "rtmpcommon.h"
#define SOCKET_ERROR -1
#endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif

extern char RTMP_Enable_AES128;
extern unsigned int RTMP_C_BitRate;
extern unsigned int RTMP_C_FrameRate;

//type 1 is audio data,type 2 is disk list
typedef void (*audio_consume_pt)(int type,char* data,int len);

void setCameraToken(DWORD cid, DWORD deadline_time, unsigned char* token);
void setMobileToken(DWORD cid, DWORD user_id ,cid_list_t clt, DWORD deadline_time, unsigned char* token);
void setDeviceType(unsigned char type);			//camera device type is 1,mobile device type is 2
void setRecordFlag(unsigned char flag);			//0 is only live,1 is live&record

int ConnectToRtmpServer(const char* aUrl,audio_consume_pt fun,int recv_audio_flag);

int sendGetDiskListCommand();
    
void DisconnectRtmpServer();

void setLogDir(char* log_dir);

//void Send_Log(const char *msg);
//cmd: 0x0301 meminfo;  0x0302 time info   
void Send_Log(const char *msg, int cmd);

int SendAacInfo(const char *aAacInfoBuf, DWORD aAacInfoBufLen,DWORD time);

int SendNal(const char *aNalBuf, DWORD aNalBufLen,DWORD time);

int SendAAC(const char *aAacBuf, DWORD aAacBufLen,DWORD time);

int SendOpus(const char *aOpusBuf, DWORD aOpusBufLen,DWORD time);

void InitNet();

#ifndef NETPUSH
#ifndef WIN32
DWORD Sys_GetTickCount(void);
#endif
#endif

#ifdef __cplusplus
};
#endif

#endif
