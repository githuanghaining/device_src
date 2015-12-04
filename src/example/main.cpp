#ifdef _WIN32
#include <windows.h>
#elif defined(__linux__)
#include <stdio.h>
#include <iostream>
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
#endif

#include "NVDDATA.h"
#include "NVDIVA.h"
#include "NVDDATA_TOOLS.h"
#include "INVDSDK.h"
#include "cJSON.h"
#include "CloudOpenAPI.h"

#include "utils.h"
#include "imgza.h"

using namespace std;

#define SIG_VALUE_EXIT 0
#define SIG_VALUE_CONNECT 1

#define SAVE_H264_ENABLE 0
#define SAVE_AAC_ENABLE 0
#define SAVE_PICTURE_ENABLE 0
#define TIMESTAMP_STEP_5min 30
#define TIMESTAMP_STEP_4min 24

#define IMG_MAX_SIZE (1.5*1024*1024)

typedef struct camera_config
{
		char cid[50];
		char SNNumber[200];
}camera_config_t;

camera_config_t global_cofig;

static int lPlayHandle = -1;
static int lLogInHandle = -1;

unsigned long  StartTime = 0;
unsigned long  AlarmStartTime = 0;
static int alarm_flag = 0;
static int alarm_start_flag =0;

static char *img_buffer =NULL;

static int Config_Audio = 0;
static int Config_Type = 0;
static int Config_Bitrate = -1;
static int ConfigChange = 0;

static int image_type = 0;
static int Alarm_enable = 1;
static int is_recording = 0;
static int rtmp_open_flag = 0;
static int publicLiveFlag = 0;
volatile int mjpeg_push_flag = 0;
static int play_audio_enable = 1;
static int push_audio_enable = 0;
static int popdata_flag = 0;
static int push_data_flag = 0;
static int IsOpenCapture = 0;

static int exit_flag = 0;

FILE* lpFile_1 = fopen("test.h264", "wb");
FILE* lpFile_2 = fopen("audio.aac", "wb");

void Sys_Sleep1(unsigned long aMilliseconds)
{
		usleep(aMilliseconds*1000);
}

unsigned long Sys_GetTickCount1(void)
{
		struct timeval aika;
		gettimeofday(&aika,NULL);
		unsigned long msecs = aika.tv_sec * 1000;
		msecs += (aika.tv_usec / 1000);
		return msecs;
}

unsigned long long Sys_MicroSeconds(void)
{
		struct timeval aika;
		gettimeofday(&aika,NULL);
		unsigned long long tmp_sec = aika.tv_sec;
		unsigned long long tmp_usec = aika.tv_usec;
		unsigned long long msecs = tmp_sec * 1000 *1000;
		msecs += tmp_usec;
		return msecs;
}



void DeviceStateCall(LONG lLogInHandle, NVD_DEVICE_STA eDeviceSta, LPVOID lpUser)
{
		printf("======================================\n");
		printf("========== DeviceStateCall ===========\n");
		printf("======================================\n");
}

void PlayDataCall1(LONG lPlayHandle, NVD_DATATYPE eDataType, LONG lDataInfo, BYTE* lpBuffer, LONG lBufferSize, LPVOID lpUser)
{
		//    return;

		//printf("head len:%d,data:%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x\n",lDataInfo,*(lpBuffer+lDataInfo),*(lpBuffer+lDataInfo+1),*(lpBuffer+lDataInfo+2),*(lpBuffer+lDataInfo+3),*(lpBuffer+lDataInfo+4),*(lpBuffer+lDataInfo+5),*(lpBuffer+lDataInfo+6),*(lpBuffer+lDataInfo+7),*(lpBuffer+lDataInfo+8),*(lpBuffer+lDataInfo+9),*(lpBuffer+lDataInfo+10),*(lpBuffer+lDataInfo+11),*(lpBuffer+lDataInfo+12),*(lpBuffer+lDataInfo+13),*(lpBuffer+lDataInfo+14),*(lpBuffer+lDataInfo+15),*(lpBuffer+lDataInfo+16),*(lpBuffer+lDataInfo+17),*(lpBuffer+lDataInfo+18),*(lpBuffer+lDataInfo+19),*(lpBuffer+lDataInfo+20),*(lpBuffer+lDataInfo+21),*(lpBuffer+lDataInfo+22),*(lpBuffer+lDataInfo+23),*(lpBuffer+lDataInfo+24));

		//  if( push_data_flag == 1 )
		//{
		int ret = -1;
		unsigned long  subTime;
		unsigned char *pBuffer;
		int frameType = eDataType;
		if(StartTime==0)  
				StartTime = Sys_GetTickCount1();
		subTime = Sys_GetTickCount1() - StartTime;

		unsigned long long piTime = Sys_MicroSeconds();
		//printf("get time:%llu\n",piTime);

		if(push_audio_enable)
		{
				//printf("eDataType ====  %d\n",eDataType);
				if(eDataType == 1)
						frameType = 129;

				//ret = PushData(0, (char *)(lpBuffer+lDataInfo), lBufferSize-lDataInfo, subTime, frameType);
				ret = PushData(0, (char *)(lpBuffer+lDataInfo), lBufferSize-lDataInfo, piTime, frameType);
				if(ret != 0)
				{
						int err = GetLastErrorNo();
						printf("D_PushData ret === %d, err:%d\n",ret,err);
				}
		}
		else if(eDataType == 0)	//video data
		{
				//ret = PushData(0, (char *)(lpBuffer+lDataInfo), lBufferSize-lDataInfo, subTime, eDataType);
				//printf("......  start ......\n");
				ret = PushData(0, (char *)(lpBuffer+lDataInfo), lBufferSize-lDataInfo, piTime, eDataType);
				//printf("D_PushData ret === %d\n",ret);
				if(ret != 0)
				{
						int err = GetLastErrorNo();
						printf("D_PushData ret === %d, err:%d\n",ret,err);
				}
#if 1
				if(alarm_start_flag == 1)
				{
						if(AlarmStartTime != 0)
						{
								alarm_start_flag = 0;
								printf("D_SendGetDiskList start ..........\n");
								int ret = QueryAlarmRecordInfo();
								printf("D_SendGetDiskList ret =%d\n",ret);
						}
				}

#endif
				//fwrite(lpBuffer+lDataInfo, 1, lBufferSize-lDataInfo, lpFile_1);
				//fflush(lpFile_2);

		}
		else if(eDataType == 1)
		{
				//PushData(0, (const char *)(lpBuffer+lDataInfo), lBufferSize-lDataInfo, subTime, 129);
				//fwrite(lpBuffer+lDataInfo, 1, lBufferSize-lDataInfo, lpFile_2);
				//fflush(lpFile_2);
				//	printf("audio disable, head len:%d,data:%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x\n",lDataInfo,*(lpBuffer+lDataInfo),*(lpBuffer+lDataInfo+1),*(lpBuffer+lDataInfo+2),*(lpBuffer+lDataInfo+3),*(lpBuffer+lDataInfo+4),*(lpBuffer+lDataInfo+5),*(lpBuffer+lDataInfo+6),*(lpBuffer+lDataInfo+7),*(lpBuffer+lDataInfo+8),*(lpBuffer+lDataInfo+9),*(lpBuffer+lDataInfo+10),*(lpBuffer+lDataInfo+11),*(lpBuffer+lDataInfo+12),*(lpBuffer+lDataInfo+13),*(lpBuffer+lDataInfo+14),*(lpBuffer+lDataInfo+15),*(lpBuffer+lDataInfo+16),*(lpBuffer+lDataInfo+17),*(lpBuffer+lDataInfo+18),*(lpBuffer+lDataInfo+19),*(lpBuffer+lDataInfo+20),*(lpBuffer+lDataInfo+21),*(lpBuffer+lDataInfo+22),*(lpBuffer+lDataInfo+23),*(lpBuffer+lDataInfo+24));
		}
		//}
}

void IvaDataCall1(LONG lPlayHandle, NVD_DATATYPE eDataType, LONG lDataInfo, BYTE* lpBuffer, LONG lBufferSize, LPVOID lpUser)
{
		printf("=================iva buffsize:%u==============\n", lBufferSize-lDataInfo);

		{  
				if (NVD_DATATYPE_INTEL == eDataType)
				{

						NVD_MEDIA_HEAD head;
						memcpy(&head, lpBuffer, lDataInfo);
						//NPLogInfo((_T("VideotrecIPPoStreamInChannel::NVD_DATATYPE_INTEL head.algorithm=%d"),head.algorithm));
						if (80 == head.algorithm )
						{
								int datatype=*(int*)(lpBuffer+lDataInfo);
								//NVD_IVA_LPR_RESULTS* lpr=(NVD_IVA_LPR_RESULTS* )(lpBuffer+lDataInfo+sizeof(int));
								//DWORD bufLen = sizeof(NVD_IVA_LPR_RESULTS)+lpr->pPicture.picLen;
								//NPLogInfo((_T("VideotrecIPPoStreamInChannel::NVD_DATATYPE_INTEL buflen=%d,datatype=%d"),bufLen,datatype ));

								int iReportHeadLen = 164+sizeof(int)*2;
								NVD_IVA_REPORT stReport;
								//ZeroMemory(&stReport, sizeof(NVD_IVA_REPORT));
								stReport.ivaType = datatype;
								//MakeReportDevInfo(&stReport);

								switch(datatype)
								{
										case NVD_IVA_RESULT_LPR://车辆信息
												{
														NVD_IVA_LPR_RESULTS* lpr=(NVD_IVA_LPR_RESULTS* )(lpBuffer+lDataInfo+sizeof(int));
														printf("0time: %s; lpr->nNumResult: %d", lpr->tTime, lpr->nNumResult);
														stReport.ivaLen = sizeof(NVD_IVA_LPR_RESULTS)+lpr->pPicture.picLen;
														stReport.ivaData = lpBuffer+lDataInfo+sizeof(int);
														DWORD bufLen = iReportHeadLen+stReport.ivaLen;
														if(bufLen > 5000000)
														{
																//
																//NPLogInfo((_T("VideotrecIPPoStreamInChannel::NVD_DATATYPE_INTEL buflen too long!! buflen=%d,datatype=%d"),bufLen,datatype ));
																return;
														}
														//NPLogInfo((_T("VideotrecIPPoStreamInChannel::NVD_DATATYPE_INTEL buflen=%d,datatype=%d"),bufLen,datatype ));
														char *buf=new char[bufLen];
														if (buf == NULL)
														{
																return;
														}
														memcpy(buf, &stReport, iReportHeadLen);
														memcpy(buf+iReportHeadLen, stReport.ivaData, stReport.ivaLen);

														//m_host->ReportEvent2(buf,bufLen);

														delete []buf;
														buf = NULL;
												}
												break;
										case NVD_IVA_RESULT_FR://人脸
												{
														NVD_IVA_FR_RESULTS* lpr=(NVD_IVA_FR_RESULTS* )(lpBuffer+lDataInfo+sizeof(int));
														printf("1time: %s; lpr->nNumResult: %d", lpr->tTime, lpr->nNumResult);
														stReport.ivaLen = sizeof(NVD_IVA_FR_RESULTS)+lpr->pPicture.picLen;
														stReport.ivaData = lpBuffer+lDataInfo+sizeof(int);
														DWORD bufLen = iReportHeadLen+stReport.ivaLen;

														if(bufLen > 5000000)
														{
																//
																//NPLogInfo((_T("VideotrecIPPoStreamInChannel::NVD_DATATYPE_INTEL buflen too long!! buflen=%d,datatype=%d"),bufLen,datatype ));
																return;
														}
														//NPLogInfo((_T("VideotrecIPPoStreamInChannel::NVD_DATATYPE_INTEL buflen=%d,datatype=%d"),bufLen,datatype ));
														char *buf=new char[bufLen];
														if (buf == NULL)
														{
																return;
														}
														memcpy(buf, &stReport, iReportHeadLen);
														memcpy(buf+iReportHeadLen, stReport.ivaData, stReport.ivaLen);

														//m_host->ReportEvent2(buf,bufLen);

														delete []buf;
														buf = NULL;
												}
												break;
										case NVD_IVA_RESULT_FTPICS://人脸小图
												{
														NVD_IVA_FTPIC_RESULTS* lpr=(NVD_IVA_FTPIC_RESULTS* )(lpBuffer+lDataInfo+sizeof(int));
														printf("2time: %s;sizeof(NVD_IVA_FTPIC_RESULTS)=%u ; lpr->nNumResult: %d", lpr->tTime, sizeof(NVD_IVA_FTPIC_RESULTS), lpr->nNumResult);

														unsigned int picLen = 0;
														for (int i=0;i<lpr->nNumResult;i++)
														{
																picLen+= lpr->pPictures[i].picLen;
														}

														stReport.ivaLen = sizeof(NVD_IVA_FTPIC_RESULTS)+picLen;
														stReport.ivaData = lpBuffer+lDataInfo+sizeof(int);
														DWORD bufLen = iReportHeadLen+stReport.ivaLen;

														if(bufLen > 5000000)
														{
																//
																//NPLogInfo((_T("VideotrecIPPoStreamInChannel::NVD_DATATYPE_INTEL buflen too long!! buflen=%d,datatype=%d"),bufLen,datatype ));
																return;
														}
														//NPLogInfo((_T("VideotrecIPPoStreamInChannel::NVD_DATATYPE_INTEL buflen=%d,datatype=%d"),bufLen,datatype ));
														char *buf=new char[bufLen];
														if (buf == NULL)
														{
																return;
														}
														memcpy(buf, &stReport, iReportHeadLen);
														memcpy(buf+iReportHeadLen, stReport.ivaData, stReport.ivaLen);

														//m_host->ReportEvent2(buf,bufLen);

														delete []buf;
														buf = NULL;
												}
												break;
								}
						}
				}
		}    
}


void PlateInfoCall(LONG lLogInHandle, NVD_IVA_LPR_RESULT lpResult, LPVOID lpUser)
{
		printf("HELLO_PlateInfoCall\n");

		printf("=================bodyBright:%d=================\n", lpResult.bodyBright);
		printf("=================bodyColor:%d=================\n", lpResult.bodyColor);
		printf("=================color:%s=================\n", lpResult.color);
		printf("=================firstRate:%f=================\n", lpResult.firstRate);
		printf("=================license:%s=================\n", lpResult.license);
		printf("=================nBright:%d=================\n", lpResult.nBright);
		printf("=================nColor:%d=================\n", lpResult.nColor);
		printf("=================nConfidence:%d=================\n", lpResult.nConfidence);
		printf("=================nDirection:%d=================\n", lpResult.nDirection);
		printf("=================nType:%d=================\n", lpResult.nType);
		printf("=================rect.bottom:%d=================\n", lpResult.rect.bottom);
		printf("=================rect.left:%d=================\n", lpResult.rect.left);
		printf("=================rect.right:%d=================\n", lpResult.rect.right);
		printf("=================rect.top:%d=================\n", lpResult.rect.top);
		printf("=================secondColor:%d=================\n", lpResult.secondColor);
		printf("=================secondRate:%f=================\n", lpResult.secondRate);



}

void PTZReportCallBack1 (LONG lLogInHandle, NVD_PTZ_REPORT_INFO lpPTZReportInfo, LPVOID lpUser)
{
		printf("HELLO_PTZ\n");

		printf("=================panValue:%d=================\n", lpPTZReportInfo.panValue);
		printf("=================tiltValue:%d=================\n", lpPTZReportInfo.tiltValue);
}

//void Alarm(LONG lLogInHandle, LONG lChannelID, NVD_ALARM_TYPE eAlarmType, LPVOID lpAlarmInfo, LPVOID lpUser)
void Alarm(LONG lLogInHandle, LONG lChannelID, NVD_ALARM_TYPE eAlarmType, NVD_ALARM_REPORT_INFO lpAlarmInfo, LPVOID lpUser)
{
		printf("HELLO_ALARM\n");
		//NVD_ALARM_REPORT_INFO* lpInfo = (NVD_ALARM_REPORT_INFO*)lpAlarmInfo; 
		//printf("%d  %d  AlarmType:%d, AlarmName:%s\n", lLogInHandle, lChannelID, lpInfo->alarmType, lpInfo->name);
		printf("%d  %d  AlarmType:%d, AlarmName:%s\n", lLogInHandle, lChannelID, lpAlarmInfo.alarmType, lpAlarmInfo.name);
}


void* ThreadFun1(void *arg)
{
		int i = 0;

		while(1)
		{

				NVD_LOGIN_INFO Info;
				memset(&Info, 0, sizeof(NVD_LOGIN_INFO));
				int lLogInHandle = NVD_LogIn2("192.168.2.101", 12560, "admin", "123456", NVD_NETMODEL_TCP, 2000, &Info);
				if(lLogInHandle < 0)
				{
						printf("====================================num 1 login err!---i=%d------lLogInHandle=%u-------\n", i,lLogInHandle);
						continue;
				}
				else
				{
						printf("====================================num 1 login  succese !---i=%d------lLogInHandle=%u-------\n", i,lLogInHandle);
						printf("=================================== dev name :%s , type : %d ============================\n",Info.devName,Info.devType);
						printf("-----------------------------------------------------------------------\n");
				}


				//lLogInHandle-登录句柄;0-获取类型;ENC_STREAM_TYPE_MAIN-主流;NVD_NETMODEL_TCP-TCP方式;0-播放窗口句柄
				//lPlayHandle-播放句柄  >=0:成功   其他:失败 
				int lPlayHandle = NVD_RealPlay(lLogInHandle, 0, ENC_STREAM_TYPE_MAIN, NVD_NETMODEL_TCP, 0);
				if(lPlayHandle < 0)
				{
						printf("===========================num 1 play err!---i=%d------lPlayHandle=%u!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", i,lPlayHandle);
						NVD_LogOut(lLogInHandle);
						continue;
				}

				//设置显示回调;return  0:成功   其他:失败;PlayDataCall1-数据回调;0-显示回调用户数据 
				NVD_SetPlayDataCallBack(lPlayHandle, PlayDataCall1, NULL);

				//ENC_STREAM_TYPE_IVA-智能
				int lIvaHandle = NVD_RealPlay(lLogInHandle, 0, ENC_STREAM_TYPE_IVA, NVD_NETMODEL_TCP, 0);
				if(lIvaHandle < 0)
				{
						printf("===========================num 1 iva err!---i=%d------lIvaHandle=%u!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", i,lIvaHandle);
						NVD_LogOut(lLogInHandle);
						continue;
				}

				NVD_SetPlayDataCallBack(lIvaHandle, IvaDataCall1, NULL);

				//        NVD_SetPlateInfoCallBack(lLogInHandle, PlateInfoCall, NULL);

#if 0
				NVD_SetPTZReportCallBack(lLogInHandle,  PTZReportCallBack1, NULL);
				NVD_SetAlarmDataCallBack(lLogInHandle, Alarm, NULL);

				NVD_KEYBOARD_CTRL_DATA KeyBoard_Ctrl_Data;
				memset(&KeyBoard_Ctrl_Data, 0, sizeof(NVD_KEYBOARD_CTRL_DATA));

				KeyBoard_Ctrl_Data.cmd = NVD_KEYBOARD_TELT_UP;
				int lKeyHandle = NVD_KeyBoardCtrl(lLogInHandle, 0, KeyBoard_Ctrl_Data);
				if(lKeyHandle < 0)
				{
						printf("===========================num 1 KEYBOARD_UP err!---i=%d------lKeyHandle=%u!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", i,lKeyHandle);
						NVD_LogOut(lLogInHandle);
						continue;
				}
				sleep(1);

				KeyBoard_Ctrl_Data.cmd = NVD_KEYBOARD_WIDE_DOWN;
				lKeyHandle = NVD_KeyBoardCtrl(lLogInHandle, 0, KeyBoard_Ctrl_Data);
				if(lKeyHandle < 0)
				{
						printf("===========================num 1 KEYBOARD_DOWN err!---i=%d------lKeyHandle=%u!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", i,lKeyHandle);
						NVD_LogOut(lLogInHandle);
						continue;
				}
				sleep(1);

				KeyBoard_Ctrl_Data.cmd = NVD_KEYBOARD_FAR_LEFT;
				lKeyHandle = NVD_KeyBoardCtrl(lLogInHandle, 0, KeyBoard_Ctrl_Data);
				if(lKeyHandle < 0)
				{
						printf("===========================num 1 KEYBOARD_LEFT err!---i=%d------lKeyHandle=%u!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", i,lKeyHandle);
						NVD_LogOut(lLogInHandle);
						continue;
				}
				sleep(1);

				KeyBoard_Ctrl_Data.cmd = NVD_KEYBOARD_NEAR_RIGHT;
				lKeyHandle = NVD_KeyBoardCtrl(lLogInHandle, 0, KeyBoard_Ctrl_Data);
				if(lKeyHandle < 0)
				{
						printf("===========================num 1 KEYBOARD_RIGHT err!---i=%d------lKeyHandle=%u!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", i,lKeyHandle);
						NVD_LogOut(lLogInHandle);
						continue;
				}
				sleep(1);
#endif        

#if 0        

				NVD_SetAlarmDataCallBack(lLogInHandle, Alarm, NULL);

				NVD_PTZCtrl(lPlayHandle, NVD_PTZ_UP, 7);

				sleep(2);

				NVD_PTZCtrl(lPlayHandle, NVD_PTZ_STOP, 0);

				usleep(10000);

				NVD_PTZCtrl(lPlayHandle, NVD_PTZ_DOWN, 7);

				sleep(2);

				NVD_PTZCtrl(lPlayHandle, NVD_PTZ_STOP, 0);

				usleep(300000);

				NVD_PTZCtrl(lPlayHandle, NVD_PTZ_RIGHT, 7);

				sleep(2);

				NVD_PTZCtrl(lPlayHandle, NVD_PTZ_STOP, 0);

				usleep(300000);

				NVD_PTZCtrl(lPlayHandle, NVD_PTZ_LEFT, 7);

				sleep(2);

				NVD_PTZCtrl(lPlayHandle, NVD_PTZ_STOP, 0);

				sleep(2);



#endif
#if 1


				/*====================================================================================

				  参数设置区

				  =====================================================================================*/
				//1
				NVD_DEV_PARA Info_Get_DEV_PARA;
				LONG lBufferSize_DEV_PARA = sizeof(NVD_DEV_PARA);
				LONG lpReturnSize_DEV_PARA;


				//3
				NVD_VIDEO_ENC_PARA Info_Get_VIDEO_ENC_PARA;
				LONG lBufferSize_VIDEO_ENC_PARA = sizeof(NVD_VIDEO_ENC_PARA);
				LONG lpReturnSize_VIDEO_ENC_PARA;
				//4

				NVD_AUDIO_IN_PARA Info_Get_AUDIO_IN_PARA;
				LONG lBufferSize_AUDIO_IN_PARA = sizeof(NVD_AUDIO_IN_PARA);
				LONG lpReturnSize_AUDIO_IN_PARA;

				//5
				NVD_AUDIO_OUT_PARA Info_Get_AUDIO_OUT_PARA;
				LONG lBufferSize_AUDIO_OUT_PARA = sizeof(NVD_AUDIO_OUT_PARA);
				LONG lpReturnSize_AUDIO_OUT_PARA;

				//6
				NVD_IMAGE_PARA Info_Get_IMAGE_PARA;
				LONG lBufferSize_IMAGE_PARA = sizeof(NVD_IMAGE_PARA);
				LONG lpReturnSize_IMAGE_PARA;

				//7
				NVD_ALARM_IN_PARA Info_Get_ALARM_IN_PARA;
				LONG lBufferSize_ALARM_IN_PARA = sizeof(NVD_ALARM_IN_PARA);
				LONG lpReturnSize_ALARM_IN_PARA;

				//8
				NVD_ALARM_OUT_PARA Info_Get_ALARM_OUT_PARA;
				LONG lBufferSize_ALARM_OUT_PARA = sizeof(NVD_ALARM_OUT_PARA);
				LONG lpReturnSize_ALARM_OUT_PARA;

				//9
				NVD_DISPLAY_PARA Info_Get_DISPLAY_PARA;
				LONG lBufferSize_DISPLAY_PARA = sizeof(NVD_DISPLAY_PARA);
				LONG lpReturnSize_DISPLAY_PARA;

				//10        
				NVD_TEXT_OSD_PARA Info_Get_TEXT_OSD_PARA;
				LONG lBufferSize_TEXT_OSD_PARA = sizeof(NVD_TEXT_OSD_PARA);
				LONG lpReturnSize_TEXT_OSD_PARA;

				//11    
				NVD_MASK_PARA Info_Get_MASK_PARA;
				LONG lBufferSize_MASK_PARA = sizeof(NVD_MASK_PARA);
				LONG lpReturnSize_MASK_PARA;

				//12    
				NVD_MD_PARA Info_Get_MD_PARA;
				LONG lBufferSize_MD_PARA = sizeof(NVD_MD_PARA);
				LONG lpReturnSize_MD_PARA;

				//13    
				NVD_PTZ_COM_PARA Info_Get_PTZ_COM_PARA;
				LONG lBufferSize_PTZ_COM_PARA = sizeof(NVD_PTZ_COM_PARA);
				LONG lpReturnSize_PTZ_COM_PARA;

				//14    
				NVD_NET_PARA Info_Get_NET_PARA;
				LONG lBufferSize_NET_PARA = sizeof(NVD_NET_PARA);
				LONG lpReturnSize_NET_PARA;        

				//15    
				NVD_COM_PARA Info_Get_COM_PARA;
				LONG lBufferSize_COM_PARA = sizeof(NVD_COM_PARA);
				LONG lpReturnSize_COM_PARA;        

				//16    
				NVD_PTZ_DEFAULT_PRESET_PARA Info_Get_PTZ_DEFAULT_PRESET_PARA;
				LONG lBufferSize_PTZ_DEFAULT_PRESET_PARA = sizeof(NVD_PTZ_DEFAULT_PRESET_PARA);
				LONG lpReturnSize_PTZ_DEFAULT_PRESET_PARA;    

				//17    
				NVD_NET_2_PARA Info_Get_NET_2_PARA;
				LONG lBufferSize_NET_2_PARA = sizeof(NVD_NET_2_PARA);
				LONG lpReturnSize_NET_2_PARA;

				//18    
				NVD_NTP_PARA Info_Get_NTP_PARA;
				LONG lBufferSize_NTP_PARA = sizeof(NVD_NTP_PARA);
				LONG lpReturnSize_NTP_PARA;

				//19    
				NVD_EMAIL_PARA Info_Get_EMAIL_PARA;
				LONG lBufferSize_EMAIL_PARA = sizeof(NVD_EMAIL_PARA);
				LONG lpReturnSize_EMAIL_PARA;

				//20    
				NVD_IVA_LPR_PARA Info_Get_IVA_LPR_PARA;
				LONG lBufferSize_IVA_LPR_PARA = sizeof(NVD_IVA_LPR_PARA);
				LONG lpReturnSize_IVA_LPR_PARA;

				//21    
				NVD_NET_LOG_PARA Info_Get_NET_LOG_PARA;
				LONG lBufferSize_NET_LOG_PARA = sizeof(NVD_NET_LOG_PARA);
				LONG lpReturnSize_NET_LOG_PARA;


				//22    
				NVD_SNMP_PARA Info_Get_SNMP_PARA;
				LONG lBufferSize_SNMP_PARA = sizeof(NVD_SNMP_PARA);
				LONG lpReturnSize_SNMP_PARA;







				/*======================================================================================

				  获取信息的代码区

				  =======================================================================================*/
				//1 GET_DEV_PARA
				memset(&Info_Get_DEV_PARA, 0, sizeof(NVD_DEV_PARA));
				int lGetDeviceCfgHandle_DEV_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETDEVICEPARAM, 0, &Info_Get_DEV_PARA, lBufferSize_DEV_PARA, &lpReturnSize_DEV_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_DEV_PARA)
				{
						printf(" get dev para ok!\n");
				}
				else
				{      
						printf("========================num 1 get DEV_PARA error!---i=%d-------lGetDeviceCfgHandle_DEV_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_DEV_PARA);
				}



				//3 GET_VIDEO_ENC_PARA
				memset(&Info_Get_VIDEO_ENC_PARA, 0, sizeof(NVD_VIDEO_ENC_PARA));
				int lGetDeviceCfgHandle_VIDEO_ENC_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETVIDEOENCPARAM, 0, &Info_Get_VIDEO_ENC_PARA, lBufferSize_VIDEO_ENC_PARA, &lpReturnSize_VIDEO_ENC_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_VIDEO_ENC_PARA)
				{       
						printf("=================================\n"); 
						printf("     get video enc para ok!\n");
						printf("Info_Get_VIDEO_ENC_PARA->viNo === %d\n",Info_Get_VIDEO_ENC_PARA.viNo);

				}
				else
				{      
						printf("========================num 1 get VIDEO_ENC_PARA error!---i=%d-------lGetDeviceCfgHandle_VIDEO_ENC_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_VIDEO_ENC_PARA);
				}


				//4 GET_AUDIO_IN_PARA
				memset(&Info_Get_AUDIO_IN_PARA, 0, sizeof(NVD_AUDIO_IN_PARA));
				int lGetDeviceCfgHandle_AUDIO_IN_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETAUDIOENCPARAM, 0, &Info_Get_AUDIO_IN_PARA, lBufferSize_AUDIO_IN_PARA, &lpReturnSize_AUDIO_IN_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_AUDIO_IN_PARA)
				{        
						printf(" get audio in para ok!\n");

				}
				else
				{      
						printf("========================num 1 get AUDIO_IN_PARA error!---i=%d-------lGetDeviceCfgHandle_AUDIO_IN_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_AUDIO_IN_PARA);
				}


				//5 GET_AUDIO_OUT_PARA
				memset(&Info_Get_AUDIO_OUT_PARA, 0, sizeof(NVD_AUDIO_OUT_PARA));
				int lGetDeviceCfgHandle_AUDIO_OUT_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETAUDIOOUTPARAM, 0, &Info_Get_AUDIO_OUT_PARA, lBufferSize_AUDIO_OUT_PARA, &lpReturnSize_AUDIO_OUT_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_AUDIO_OUT_PARA)
				{            
						printf(" get audio out para ok!\n");

				}
				else
				{
						printf("========================num 1 get AUDIO_OUT_PARA error!---i=%d-------lGetDeviceCfgHandle_AUDIO_OUT_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_AUDIO_OUT_PARA);
				}


				//6 GET_IMAGE_PARA
				memset(&Info_Get_IMAGE_PARA, 0, sizeof(NVD_IMAGE_PARA));
				int lGetDeviceCfgHandle_IMAGE_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETIMAGEPARAM, 0, &Info_Get_IMAGE_PARA, lBufferSize_IMAGE_PARA, &lpReturnSize_IMAGE_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_IMAGE_PARA)
				{
						printf(" get image para ok!\n");

				}
				else
				{      
						printf("========================num 1 get _IMAGE_PARA error!---i=%d-------lGetDeviceCfgHandle_IMAGE_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_IMAGE_PARA);
				}


				//7 GET_ALARM_IN_PARA
				memset(&Info_Get_ALARM_IN_PARA, 0, sizeof(NVD_ALARM_IN_PARA));
				int lGetDeviceCfgHandle_ALARM_IN_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETALARMINCONFIG, 0, &Info_Get_ALARM_IN_PARA, lBufferSize_ALARM_IN_PARA, &lpReturnSize_ALARM_IN_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_ALARM_IN_PARA)
				{
						printf(" get alarm in para ok!\n");

				}
				else
				{
						printf("========================num 1 get _ALARM_IN_PARA error!---i=%d-------lGetDeviceCfgHandle_ALARM_IN_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_ALARM_IN_PARA);
				}

				//8 GET_ALARM_OUT_PARA
				memset(&Info_Get_ALARM_OUT_PARA, 0, sizeof(NVD_ALARM_OUT_PARA));
				int lGetDeviceCfgHandle_ALARM_OUT_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETALARMOUTCONFIG, 0, &Info_Get_ALARM_OUT_PARA, lBufferSize_ALARM_OUT_PARA, &lpReturnSize_ALARM_OUT_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_ALARM_OUT_PARA)
				{
						printf(" get alarm out para ok!\n");

				}
				else
				{      
						printf("========================num 1 get ALARM_OUT_PARA error!---i=%d-------lGetDeviceCfgHandle_ALARM_OUT_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_ALARM_OUT_PARA);
				}


				//9 GET_DISPLAY_PARA    
				memset(&Info_Get_DISPLAY_PARA, 0, sizeof(NVD_DISPLAY_PARA));
				int lGetDeviceCfgHandle_DISPLAY_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETDISPLAYCONFIG, 0, &Info_Get_DISPLAY_PARA, lBufferSize_DISPLAY_PARA, &lpReturnSize_DISPLAY_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_DISPLAY_PARA)
				{
						printf(" get display para ok!\n");

				}
				else
				{      
						printf("========================num 1 get DISPLAY_PARA error!---i=%d-------lGetDeviceCfgHandle_DISPLAY_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_DISPLAY_PARA);
				}


				//10 GET_TEXT_OSD_PARA
				memset(&Info_Get_TEXT_OSD_PARA, 0, sizeof(NVD_TEXT_OSD_PARA));
				int lGetDeviceCfgHandle_TEXT_OSD_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETTEXTOSDCONFIG, 0, &Info_Get_TEXT_OSD_PARA, lBufferSize_TEXT_OSD_PARA, &lpReturnSize_TEXT_OSD_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_TEXT_OSD_PARA)
				{
						printf(" get text OSD para ok!\n");

				}
				else
				{      
						printf("========================num 1 get TEXT_OSD_PARA error!---i=%d-------lGetDeviceCfgHandle_TEXT_OSD_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_TEXT_OSD_PARA);
				}


				//11 GET_MASK_PARA
				memset(&Info_Get_MASK_PARA, 0, sizeof(NVD_MASK_PARA));
				int lGetDeviceCfgHandle_MASK_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETMASKCONFIG, 0, &Info_Get_MASK_PARA, lBufferSize_MASK_PARA, &lpReturnSize_MASK_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_MASK_PARA)
				{
						printf(" get mask para ok!\n");

				}
				else
				{      
						printf("========================num 1 get MASK_PARA error!---i=%d-------lGetDeviceCfgHandle_MASK_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_MASK_PARA);
				}


				//12 GET_MD_PARA
				memset(&Info_Get_MD_PARA, 0, sizeof(NVD_MD_PARA));
				int lGetDeviceCfgHandle_MD_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETMDCONFIG, 0, &Info_Get_MD_PARA, lBufferSize_MD_PARA, &lpReturnSize_MD_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_MD_PARA)
				{
						printf(" get MD para ok!\n");

				}
				else
				{      
						printf("========================num 1 get MD_PARA error!---i=%d-------lGetDeviceCfgHandle_MD_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_MD_PARA);
				}


				//13 GET_PTZ_COM_PARA
				memset(&Info_Get_PTZ_COM_PARA, 0, sizeof(NVD_PTZ_COM_PARA));
				int lGetDeviceCfgHandle_PTZ_COM_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETPTZCOMPARAM, 0, &Info_Get_PTZ_COM_PARA, lBufferSize_PTZ_COM_PARA, &lpReturnSize_PTZ_COM_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_PTZ_COM_PARA)
				{
						printf(" get ptz com para ok!\n");

				}
				else
				{      
						printf("========================num 1 get PTZ_COM_PARA error!---i=%d-------lGetDeviceCfgHandle_PTZ_COM_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_PTZ_COM_PARA);
				}


				//14 GET_NET_PARA
				memset(&Info_Get_NET_PARA, 0, sizeof(NVD_NET_PARA));
				int lGetDeviceCfgHandle_NET_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETNETPARAM, 0, &Info_Get_NET_PARA, lBufferSize_NET_PARA, &lpReturnSize_NET_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_NET_PARA)
				{
						printf(" get net para ok!\n");

				}
				else
				{      
						printf("========================num 1 get NET_PARA error!---i=%d-------lGetDeviceCfgHandle_NET_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_NET_PARA);
				}


				//15 GET_COM_PARA
				memset(&Info_Get_COM_PARA, 0, sizeof(NVD_COM_PARA));
				int lGetDeviceCfgHandle_COM_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETCOMPARAM, 0, &Info_Get_COM_PARA, lBufferSize_COM_PARA, &lpReturnSize_COM_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_COM_PARA)
				{
						printf(" get com para ok!\n");

				}
				else
				{      
						printf("========================num 1 get COM_PARA error!---i=%d-------lGetDeviceCfgHandle_COM_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_COM_PARA);
				}


				//16 GET_PTZ_DEFAULT_PRESET_PARA
				memset(&Info_Get_PTZ_DEFAULT_PRESET_PARA, 0, sizeof(NVD_PTZ_DEFAULT_PRESET_PARA));
				int lGetDeviceCfgHandle_PTZ_DEFAULT_PRESET_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETDEFPRESETPARAM, 0, &Info_Get_PTZ_DEFAULT_PRESET_PARA, lBufferSize_PTZ_DEFAULT_PRESET_PARA, &lpReturnSize_PTZ_DEFAULT_PRESET_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_PTZ_DEFAULT_PRESET_PARA)
				{
						printf(" get ptz default para ok!\n");

				}
				else
				{      
						printf("========================num 1 get PTZ_DEFAULT_PRESET_PARA error!---i=%d-------lGetDeviceCfgHandle_PTZ_DEFAULT_PRESET_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_PTZ_DEFAULT_PRESET_PARA);
				}


				//17 GET_NET_2_PARA
				memset(&Info_Get_NET_2_PARA, 0, sizeof(NVD_NET_2_PARA));
				int lGetDeviceCfgHandle_NET_2_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETADVNETPARAM, 0, &Info_Get_NET_2_PARA, lBufferSize_NET_2_PARA, &lpReturnSize_NET_2_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_NET_2_PARA)
				{
						printf(" get net 2 para ok!\n");

				}
				else
				{      
						printf("========================num 1 get NET_2_PARA error!---i=%d-------lGetDeviceCfgHandle_NET_2_PARA=%u!!!!!!!!!!!!\n", i, lGetDeviceCfgHandle_NET_2_PARA);
				}

				//18 GET_NTP_PARA
				memset(&Info_Get_NTP_PARA, 0, sizeof(NVD_NTP_PARA));
				int lGetDeviceCfgHandle_NTP_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETNTPSERVERPARAM, 0, &Info_Get_NTP_PARA, lBufferSize_NTP_PARA, &lpReturnSize_NTP_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_NTP_PARA)
				{
						printf(" get ntp para ok!\n");

				}
				else
				{      
						printf("========================num 1 get NTP_PARA error!---i=%d-------lGetDeviceCfgHandle_NTP_PARA=%u!!!!!!!!!!!!\n", i, lGetDeviceCfgHandle_NTP_PARA);
				}

				//19 GET_EMAIL_PARA

				memset(&Info_Get_EMAIL_PARA, 0, sizeof(NVD_EMAIL_PARA));
				int lGetDeviceCfgHandle_EMAIL_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETEMAILPARAM, 0, &Info_Get_EMAIL_PARA, lBufferSize_EMAIL_PARA, &lpReturnSize_EMAIL_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_EMAIL_PARA)
				{
						printf(" get email para ok!\n");

				}
				else
				{      
						printf("========================num 1 get EMAIL_PARA error!---i=%d-------lGetDeviceCfgHandle_EMAIL_PARA=%u!!!!!!!!!!!!\n", i, lGetDeviceCfgHandle_EMAIL_PARA);
				}

				//20 GET_IVA_LPR_PARA

				memset(&Info_Get_IVA_LPR_PARA, 0, sizeof(NVD_IVA_LPR_PARA));
				int lGetDeviceCfgHandle_IVA_LPR_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETPLATEPARAM, 0, &Info_Get_IVA_LPR_PARA, lBufferSize_IVA_LPR_PARA, &lpReturnSize_IVA_LPR_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_IVA_LPR_PARA)
				{
						printf(" get iva lpr para ok!\n");

				}
				else
				{      
						printf("========================num 1 get IVA_LPR_PARA error!---i=%d-------lGetDeviceCfgHandle_IVA_LPR_PARA=%u!!!!!!!!!!!!\n", i, lGetDeviceCfgHandle_IVA_LPR_PARA);
				}

				//21 GET_NET_LOG_PARA

				memset(&Info_Get_NET_LOG_PARA, 0, sizeof(NVD_NET_LOG_PARA));
				int lGetDeviceCfgHandle_NET_LOG_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETLOGPARAM, 0, &Info_Get_NET_LOG_PARA, lBufferSize_NET_LOG_PARA, &lpReturnSize_NET_LOG_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_NET_LOG_PARA)
				{
						printf(" get net log para ok!\n");

				}
				else
				{      
						printf("========================num 1 get NET_LOG_PARA error!---i=%d-------lGetDeviceCfgHandle_NET_LOG_PARA=%u!!!!!!!!!!!!\n", i, lGetDeviceCfgHandle_NET_LOG_PARA);
				}

				//22 GET_SNMP_PARA

				memset(&Info_Get_SNMP_PARA, 0, sizeof(NVD_SNMP_PARA));
				int lGetDeviceCfgHandle_SNMP_PARA = NVD_GetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_GETSNMPPARAM, 0, &Info_Get_SNMP_PARA, lBufferSize_SNMP_PARA, &lpReturnSize_SNMP_PARA);
				if(NVD_OK == lGetDeviceCfgHandle_SNMP_PARA)
				{
						printf(" get snmp para ok!\n");

				}
				else
				{      
						printf("========================num 1 get SNMP_PARA error!---i=%d-------lGetDeviceCfgHandle_SNMP_PARA=%u!!!!!!!!!!!!\n", i, lGetDeviceCfgHandle_SNMP_PARA);
				}





				/*=======================================================================================

				  设置信息的代码区

				  ========================================================================================*/

#if 0

				//1 SET_DEV_PARA
				strcpy(Info_Get_DEV_PARA.devName, "jia");

				int lSetDeviceCfgHandle_DEV_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETDEVICEPARAM, 0, &Info_Get_DEV_PARA, lBufferSize_DEV_PARA);
				if(NVD_OK == lSetDeviceCfgHandle_DEV_PARA)
				{
						//printf("set DEV_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set DEV_PARA error!---i=%d-------lSetDeviceCfgHandle_DEV_PARA=%u!!!!!!!!!!!!\n",i,lSetDeviceCfgHandle_DEV_PARA);
				}


				//3 SET_VIDEO_ENC_PARA
#if 0
				Info_Get_VIDEO_ENC_PARA.bitrateMain = 2000;
				Info_Get_VIDEO_ENC_PARA.bitrateSub = 300;
				Info_Get_VIDEO_ENC_PARA.encFormat = ENC_FORMAT_DOUBLE;
				Info_Get_VIDEO_ENC_PARA.encImgTypeMain = ENC_IMG_TYPE_HD1;
				Info_Get_VIDEO_ENC_PARA.encImgTypeSub = ENC_IMG_TYPE_CIF;
				Info_Get_VIDEO_ENC_PARA.fpsMain = 20;
				Info_Get_VIDEO_ENC_PARA.fpsSub = 20;
				Info_Get_VIDEO_ENC_PARA.idrMain = 50;
				Info_Get_VIDEO_ENC_PARA.idrSub = 50;

				int lSetDeviceCfgHandle_VIDEO_ENC_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETVIDEOENCPARAM, 0, &Info_Get_VIDEO_ENC_PARA, lBufferSize_VIDEO_ENC_PARA);
				if(NVD_OK == lSetDeviceCfgHandle_VIDEO_ENC_PARA)
				{
						//printf("set VIDEO_ENC_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set VIDEO_ENC_PARA error!---i=%d-------lSetDeviceCfgHandle_VIDEO_ENC_PARA=%u!!!!!!!!!!!!\n",i,lSetDeviceCfgHandle_VIDEO_ENC_PARA);
				}
#endif
				//4 SET_AUDIO_IN_PARA
				Info_Get_AUDIO_IN_PARA.isUsed = 0;

				int lSetDeviceCfgHandle_AUDIO_IN_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETAUDIOENCPARAM, 0, &Info_Get_AUDIO_IN_PARA, lBufferSize_AUDIO_IN_PARA);
				if(NVD_OK == lSetDeviceCfgHandle_AUDIO_IN_PARA)
				{
						//printf("set AUDIO_IN_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set AUDIO_IN_PARA error!---i=%d-------lSetDeviceCfgHandle_AUDIO_IN_PARA=%u!!!!!!!!!!!!\n",i,lSetDeviceCfgHandle_AUDIO_IN_PARA);
				}

				//5 SET_AUDIO_OUT_PARA

				Info_Get_AUDIO_OUT_PARA.isUsed = 0;

				int lSetDeviceCfgHandle_AUDIO_OUT_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETAUDIOOUTPARAM, 0, &Info_Get_AUDIO_OUT_PARA, lBufferSize_AUDIO_OUT_PARA);
				if(NVD_OK == lSetDeviceCfgHandle_AUDIO_OUT_PARA)
				{
						//printf("set AUDIO_OUT_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set AUDIO_OUT_PARA error!---i=%d-------lSetDeviceCfgHandle_AUDIO_OUT_PARA=%u!!!!!!!!!!!!\n",i,lSetDeviceCfgHandle_AUDIO_OUT_PARA);
				}

				//6 SET_IMAGE_PARA
				Info_Get_IMAGE_PARA.brightness = 63;
				Info_Get_IMAGE_PARA.contrast = 63;
				Info_Get_IMAGE_PARA.saturation = 63;
				Info_Get_IMAGE_PARA.hue = 63;

				int lSetDeviceCfgHandle_IMAGE_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETIMAGEPARAM, 0, &Info_Get_IMAGE_PARA, lBufferSize_IMAGE_PARA);
				if(NVD_OK == lSetDeviceCfgHandle_IMAGE_PARA)
				{
						//printf("set _IMAGE_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set _IMAGE_PARA error!---i=%d-------lGetDeviceCfgHandle_IMAGE_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_IMAGE_PARA);
				}

				//7 SET_ALARM_IN_PARA
				Info_Get_ALARM_IN_PARA.isUsed = 0;
				Info_Get_ALARM_IN_PARA.name[0] = (char)100;
				Info_Get_ALARM_IN_PARA.alarmInType = 0;
				Info_Get_ALARM_IN_PARA.time[0][0].beginHour = 12;
				Info_Get_ALARM_IN_PARA.time[0][0].beginMinute = 00;
				Info_Get_ALARM_IN_PARA.time[0][0].endHour = 13;
				Info_Get_ALARM_IN_PARA.time[0][0].endMinute = 00;

				int lSetDeviceCfgHandle_ALARM_IN_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETALARMINCONFIG, 0, &Info_Get_ALARM_IN_PARA, lBufferSize_ALARM_IN_PARA);

				if(NVD_OK == lSetDeviceCfgHandle_ALARM_IN_PARA)
				{
						//printf("set ALARM_IN_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set ALARM_IN_PARA error!---i=%d-------lGetDeviceCfgHandle_ALARM_IN_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_ALARM_IN_PARA);
				}

				//8 SET_ALARM_OUT_PARA
				Info_Get_ALARM_OUT_PARA.alarmOutDelay = 3;
				Info_Get_ALARM_OUT_PARA.alarmOutNo = 0;
				Info_Get_ALARM_OUT_PARA.isUsed = 0;
				Info_Get_ALARM_OUT_PARA.name[0] = 'h';
				Info_Get_ALARM_OUT_PARA.time[0][0].isUsed = 1;
				Info_Get_ALARM_OUT_PARA.time[0][0].beginHour = 6;
				Info_Get_ALARM_OUT_PARA.time[0][0].beginMinute = 10;
				Info_Get_ALARM_OUT_PARA.time[0][0].endHour = 8;
				Info_Get_ALARM_OUT_PARA.time[0][0].endMinute = 10;

				int lSetDeviceCfgHandle_ALARM_OUT_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETALARMOUTCONFIG, 0, &Info_Get_ALARM_OUT_PARA, lBufferSize_ALARM_OUT_PARA);    
				if(NVD_OK == lSetDeviceCfgHandle_ALARM_OUT_PARA)
				{
						//printf("set ALARM_OUT_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set ALARM_OUT_PARA error!---i=%d-------lGetDeviceCfgHandle_ALARM_OUT_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_ALARM_OUT_PARA);
				}

				//9 SET_DISPLAY_PARA        
				Info_Get_DISPLAY_PARA.channelName[0] = 'q'; 
				Info_Get_DISPLAY_PARA.disType_time = NVD_DISPLAY_YYYY_MM_DD_WEEKDATE_HH_MM_SS_1;
				Info_Get_DISPLAY_PARA.isShow_name = 1;
				Info_Get_DISPLAY_PARA.isShow_time = 1;
				Info_Get_DISPLAY_PARA.size_name = 5;
				Info_Get_DISPLAY_PARA.size_time = 5;
				Info_Get_DISPLAY_PARA.viNo = 0;
				Info_Get_DISPLAY_PARA.xPos_name = 10;
				Info_Get_DISPLAY_PARA.xPos_time = 30;
				Info_Get_DISPLAY_PARA.yPos_name = 10;
				Info_Get_DISPLAY_PARA.yPos_time = 30;

				int lSetDeviceCfgHandle_DISPLAY_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETDISPLAYCONFIG, 0, &Info_Get_DISPLAY_PARA, lBufferSize_DISPLAY_PARA);
				if(NVD_OK == lSetDeviceCfgHandle_DISPLAY_PARA)
				{
						//printf("set ALARM_OUT_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set DISPLAY_PARA error!---i=%d-------lGetDeviceCfgHandle_DISPLAY_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_DISPLAY_PARA);
				}

				//10 SET_TEXT_OSD_PARA   

#if 0
				Info_Get_TEXT_OSD_PARA.textOsd[0].alpha = 100;
				Info_Get_TEXT_OSD_PARA.textOsd[0].color.blue = 100;
				Info_Get_TEXT_OSD_PARA.textOsd[0].color.green = 100;
				Info_Get_TEXT_OSD_PARA.textOsd[0].color.red = 100;
				Info_Get_TEXT_OSD_PARA.textOsd[0].color.res = 10;
				Info_Get_TEXT_OSD_PARA.textOsd[0].isShow = 1;
				strcpy(Info_Get_TEXT_OSD_PARA.textOsd[0].osdChar,"jia");
				Info_Get_TEXT_OSD_PARA.textOsd[0].size = 4;
				Info_Get_TEXT_OSD_PARA.textOsd[0].xPos = 40;
				Info_Get_TEXT_OSD_PARA.textOsd[0].yPos = 40;
				Info_Get_TEXT_OSD_PARA.textOsd[1].alpha = 100;
				Info_Get_TEXT_OSD_PARA.textOsd[1].color.blue = 100;
				Info_Get_TEXT_OSD_PARA.textOsd[1].color.green = 100;
				Info_Get_TEXT_OSD_PARA.textOsd[1].color.red = 100;
				Info_Get_TEXT_OSD_PARA.textOsd[1].color.res = 10;
				Info_Get_TEXT_OSD_PARA.textOsd[1].isShow = 1;
				strcpy(Info_Get_TEXT_OSD_PARA.textOsd[1].osdChar,"jia");
				Info_Get_TEXT_OSD_PARA.textOsd[1].size = 4;
				Info_Get_TEXT_OSD_PARA.textOsd[1].xPos = 40;
				Info_Get_TEXT_OSD_PARA.textOsd[1].yPos = 40;
				Info_Get_TEXT_OSD_PARA.viNo = 0;
#endif        
				int lSetDeviceCfgHandle_TEXT_OSD_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETTEXTOSDCONFIG, 0, &Info_Get_TEXT_OSD_PARA, lBufferSize_TEXT_OSD_PARA);
				if(NVD_OK == lSetDeviceCfgHandle_TEXT_OSD_PARA)
				{
						//printf("set TEXT_OSD_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set TEXT_OSD_PARA error!---i=%d-------lGetDeviceCfgHandle_TEXT_OSD_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_TEXT_OSD_PARA);
				}

				//11 SET_MASK_PARA
				Info_Get_MASK_PARA.viNo = 0;
				Info_Get_MASK_PARA.area[0].isUsed = 0;
				Info_Get_MASK_PARA.area[0].xPos = 0;
				Info_Get_MASK_PARA.area[0].yPos = 0;
				Info_Get_MASK_PARA.area[0].width = 10;
				Info_Get_MASK_PARA.area[0].height = 10;
				Info_Get_MASK_PARA.area[1].isUsed = 1;
				Info_Get_MASK_PARA.area[1].xPos = 10;
				Info_Get_MASK_PARA.area[1].yPos = 10;
				Info_Get_MASK_PARA.area[1].width = 20;
				Info_Get_MASK_PARA.area[1].height = 20;
				Info_Get_MASK_PARA.time[0][0].isUsed = 1;
				Info_Get_MASK_PARA.time[0][0].beginHour = 6;
				Info_Get_MASK_PARA.time[0][0].beginMinute = 10;
				Info_Get_MASK_PARA.time[0][0].endHour = 8;
				Info_Get_MASK_PARA.time[0][0].endMinute =20;

				int lSetDeviceCfgHandle_MASK_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETMASKCONFIG, 0, &Info_Get_MASK_PARA, lBufferSize_MASK_PARA);
				if(NVD_OK == lSetDeviceCfgHandle_MASK_PARA)
				{
						//printf("set MASK_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set MASK_PARA error!---i=%d-------lGetDeviceCfgHandle_MASK_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_MASK_PARA);
				}

				//12 SET_MD_PARA
				Info_Get_MD_PARA.isUsed = 0;
				strcpy(Info_Get_MD_PARA.name,"jia");
				Info_Get_MD_PARA.level = 5;
				for(int j = 0; j < 22*18; j++)
				{
						Info_Get_MD_PARA.area[j] = 1;
				}

				int lSetDeviceCfgHandle_MD_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETMDCONFIG, 0, &Info_Get_MD_PARA, lBufferSize_MD_PARA);
				if(NVD_OK ==lSetDeviceCfgHandle_MD_PARA)
				{
						//printf("set MD_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set MD_PARA error!---i=%d-------lGetDeviceCfgHandle_MD_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_MD_PARA);
				}

				//13 SET_PTZ_COM_PARA
				Info_Get_PTZ_COM_PARA.isUsed = 0;
				Info_Get_PTZ_COM_PARA.viNo = 0;
				Info_Get_PTZ_COM_PARA.addr = 2;
				Info_Get_PTZ_COM_PARA.comNo = 0;
				Info_Get_PTZ_COM_PARA.protocol = NVD_PTZ_PROTOCOL_PELCO_P;
				Info_Get_PTZ_COM_PARA.comInfo.baudRate = NVD_PTZ_B4800;
				Info_Get_PTZ_COM_PARA.comInfo.dataBit = NVD_PTZ_5_DATABITS;
				Info_Get_PTZ_COM_PARA.comInfo.flowCtrl = NVD_PTZ_SW_FLOWCRTL;
				Info_Get_PTZ_COM_PARA.comInfo.parity = NVD_PTZ_EVEN_PARITY;
				Info_Get_PTZ_COM_PARA.comInfo.stopBit = NVD_PTZ_2_STOPBITS;

				int lSetDeviceCfgHandle_PTZ_COM_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETPTZCOMPARAM, 0, &Info_Get_PTZ_COM_PARA, lBufferSize_PTZ_COM_PARA);
				if(NVD_OK == lSetDeviceCfgHandle_PTZ_COM_PARA)
				{
						//printf("set PTZ_COM_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set PTZ_COM_PARA error!---i=%d-------lGetDeviceCfgHandle_PTZ_COM_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_PTZ_COM_PARA);
				}
#if 0
				//14 SET_NET_PARA
				Info_Get_NET_PARA.isDhcp = 0;
				//        inet_aton("192.168.1.63",Info_Get_NET_PARA.ip);
				//        inet_aton("192.168.1.1",Info_Get_NET_PARA.gateway);
				//        inet_aton("255.255.255.0",Info_Get_NET_PARA.netmask);

				int lSetDeviceCfgHandle_NET_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETNETPARAM, 0, &Info_Get_NET_PARA, lBufferSize_NET_PARA);
				if(NVD_OK == lSetDeviceCfgHandle_NET_PARA)
				{
						//printf("set NET_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set NET_PARA error!---i=%d-------lGetDeviceCfgHandle_NET_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_NET_PARA);
				}
#endif

				//15 SET_COM_PARA
				Info_Get_COM_PARA.isUsed = 0;
				Info_Get_COM_PARA.comNo = 0;
				Info_Get_COM_PARA.comInfo.baudRate = NVD_PTZ_B4800;
				Info_Get_COM_PARA.comInfo.dataBit = NVD_PTZ_5_DATABITS;
				Info_Get_COM_PARA.comInfo.flowCtrl = NVD_PTZ_HW_FLOWCRTL;
				Info_Get_COM_PARA.comInfo.parity = NVD_PTZ_ODD_PARITY;
				Info_Get_COM_PARA.comInfo.stopBit = NVD_PTZ_2_STOPBITS;

				int lSetDeviceCfgHandle_COM_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETCOMPARAM, 0, &Info_Get_COM_PARA, lBufferSize_COM_PARA);
				if(NVD_OK == lSetDeviceCfgHandle_COM_PARA)
				{
						//printf("set COM_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set COM_PARA error!---i=%d-------lGetDeviceCfgHandle_COM_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_COM_PARA);
				}

#if 0
				//16 SET_PTZ_DEFAULT_PRESET_PARA
				Info_Get_PTZ_DEFAULT_PRESET_PARA.isUsed = 1;
				Info_Get_PTZ_DEFAULT_PRESET_PARA.presetId =
						Info_Get_PTZ_DEFAULT_PRESET_PARA
						Info_Get_PTZ_DEFAULT_PRESET_PARA
						Info_Get_PTZ_DEFAULT_PRESET_PARA
						Info_Get_PTZ_DEFAULT_PRESET_PARA
						Info_Get_PTZ_DEFAULT_PRESET_PARA

						int lSetDeviceCfgHandle_PTZ_DEFAULT_PRESET_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETCOMPARAM, 0, &Info_Get_PTZ_DEFAULT_PRESET_PARA, lBufferSize_PTZ_DEFAULT_PRESET_PARA);
				if(NVD_OK == lSetDeviceCfgHandle_PTZ_DEFAULT_PRESET_PARA)
				{
						//printf("set PTZ_DEFAULT_PRESET_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set PTZ_DEFAULT_PRESET_PARA error!---i=%d-------lGetDeviceCfgHandle_PTZ_DEFAULT_PRESET_PARA=%u!!!!!!!!!!!!\n",i,lGetDeviceCfgHandle_PTZ_DEFAULT_PRESET_PARA);
				}

#endif

				//17 SET_NET_2_PARA
#if 0
				Info_Get_NET_2_PARA.alarmHostIpAddr = 
						Info_Get_NET_2_PARA
						Info_Get_NET_2_PARA
						Info_Get_NET_2_PARA
						Info_Get_NET_2_PARA
						Info_Get_NET_2_PARA
						Info_Get_NET_2_PARA
#endif
						int lSetDeviceCfgHandle_NET_2_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETADVNETPARAM, 0, &Info_Get_NET_2_PARA, lBufferSize_NET_2_PARA);
				if(NVD_OK == lSetDeviceCfgHandle_NET_2_PARA)
				{
						//printf("set NET_2_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set NET_2_PARA error!---i=%d-------lGetDeviceCfgHandle_NET_2_PARA=%u!!!!!!!!!!!!\n", i, lGetDeviceCfgHandle_NET_2_PARA);
				}

				//18 SET_NTP_PARA

				Info_Get_NTP_PARA.interval = 5;

				int lSetDeviceCfgHandle_NTP_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETNTPSERVERPARAM, 0, &Info_Get_NTP_PARA, lBufferSize_NTP_PARA);
				if(NVD_OK == lSetDeviceCfgHandle_NTP_PARA)
				{
						//printf("set NTP_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set NTP_PARA error!---i=%d-------lGetDeviceCfgHandle_NTP_PARA=%u!!!!!!!!!!!!\n", i, lGetDeviceCfgHandle_NTP_PARA);
				}

				//19 SET_EMAIL_PARA

				Info_Get_EMAIL_PARA.isUsed = 1;

				int lSetDeviceCfgHandle_EMAIL_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETEMAILPARAM, 0, &Info_Get_EMAIL_PARA, lBufferSize_EMAIL_PARA);
				if(NVD_OK == lSetDeviceCfgHandle_EMAIL_PARA)
				{
						//printf("set EMAIL_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set EMAIL_PARA error!---i=%d-------lGetDeviceCfgHandle_EMAIL_PARA=%u!!!!!!!!!!!!\n", i, lGetDeviceCfgHandle_EMAIL_PARA);
				}


				//20 SET_IVA_LPR_PARA

#if 0
				Info_Get_IVA_LPR_PARA
#endif

						int lSetDeviceCfgHandle_IVA_LPR_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETPLATEPARAM, 0, &Info_Get_IVA_LPR_PARA, lBufferSize_IVA_LPR_PARA);
				if(NVD_OK == lSetDeviceCfgHandle_IVA_LPR_PARA)
				{
						//printf("set IVA_LPR_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set IVA_LPR_PARA error!---i=%d-------lGetDeviceCfgHandle_IVA_LPR_PARA=%u!!!!!!!!!!!!\n", i, lGetDeviceCfgHandle_IVA_LPR_PARA);
				}

				//21 SET_NET_LOG_PARA

				Info_Get_NET_LOG_PARA.isUsed = 1;

				int lSetDeviceCfgHandle_NET_LOG_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETLOGPARAM, 0, &Info_Get_NET_LOG_PARA, lBufferSize_NET_LOG_PARA);
				if(NVD_OK == lSetDeviceCfgHandle_NET_LOG_PARA)
				{
						//printf("set NET_LOG_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set NET_LOG_PARA error!---i=%d-------lGetDeviceCfgHandle_NET_LOG_PARA=%u!!!!!!!!!!!!\n", i, lGetDeviceCfgHandle_NET_LOG_PARA);
				}


				//22 SET_SNMP_PARA

				Info_Get_SNMP_PARA.isSnmpUsed = 1;

				int lSetDeviceCfgHandle_SNMP_PARA = NVD_SetDeviceCfg(lLogInHandle, NVD_OPCFGTYPE_SETSNMPPARAM, 0, &Info_Get_SNMP_PARA, lBufferSize_SNMP_PARA);
				if(NVD_OK == lSetDeviceCfgHandle_SNMP_PARA)
				{
						//printf("set SNMP_PARA success\n");
				}
				else
				{      
						printf("========================num 1 set SNMP_PARA error!---i=%d-------lGetDeviceCfgHandle_SNMP_PARA=%u!!!!!!!!!!!!\n", i, lGetDeviceCfgHandle_SNMP_PARA);
				}

#endif

				//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#endif
				sleep(10);

				NVD_LogOut(lLogInHandle);

				i++;
		}

		pthread_exit(NULL);
}


void Set_Device_Para(LONG aLogInHandle,int type)
{

		printf("Set_Device_Para aLogInHandle:%d\n",aLogInHandle);
		//3 NVD_VIDEO_ENC_PARA
		NVD_VIDEO_ENC_PARA Info_Get_VIDEO_ENC_PARA;
		LONG lBufferSize_VIDEO_ENC_PARA = sizeof(NVD_VIDEO_ENC_PARA);
		LONG lpReturnSize_VIDEO_ENC_PARA;

#if 1
		//3 GET_VIDEO_ENC_PARA
		memset(&Info_Get_VIDEO_ENC_PARA, 0, sizeof(NVD_VIDEO_ENC_PARA));
		int lGetDeviceCfgHandle_VIDEO_ENC_PARA = NVD_GetDeviceCfg(aLogInHandle, NVD_OPCFGTYPE_GETVIDEOENCPARAM, 0, &Info_Get_VIDEO_ENC_PARA, lBufferSize_VIDEO_ENC_PARA, &lpReturnSize_VIDEO_ENC_PARA);
		printf("================ before  set video encode  para =================\n"); 
		if(NVD_OK == lGetDeviceCfgHandle_VIDEO_ENC_PARA)
		{       
				printf("     get video enc para ok!\n");
				printf("Info_Get_VIDEO_ENC_PARA->viNo === %d\n",Info_Get_VIDEO_ENC_PARA.viNo);
				printf("Info_Get_VIDEO_ENC_PARA->videoType === %d\n",Info_Get_VIDEO_ENC_PARA.videoType);
				printf("Info_Get_VIDEO_ENC_PARA->encFormat === %d\n",Info_Get_VIDEO_ENC_PARA.encFormat);
				printf("Info_Get_VIDEO_ENC_PARA->bitrateMain === %d\n",Info_Get_VIDEO_ENC_PARA.bitrateMain);
				printf("Info_Get_VIDEO_ENC_PARA->bitrateSub === %d\n",Info_Get_VIDEO_ENC_PARA.bitrateSub);
				printf("Info_Get_VIDEO_ENC_PARA->qualityMain === %d\n",Info_Get_VIDEO_ENC_PARA.qualityMain);
				printf("Info_Get_VIDEO_ENC_PARA->qualitySub === %d\n",Info_Get_VIDEO_ENC_PARA.qualitySub);
				printf("Info_Get_VIDEO_ENC_PARA->encImgTypeMain === %d\n",Info_Get_VIDEO_ENC_PARA.encImgTypeMain);
				printf("Info_Get_VIDEO_ENC_PARA->encImgTypeSub === %d\n",Info_Get_VIDEO_ENC_PARA.encImgTypeSub);
				printf("Info_Get_VIDEO_ENC_PARA->imgTypeMainMask === %d\n",Info_Get_VIDEO_ENC_PARA.imgTypeMainMask);
				printf("Info_Get_VIDEO_ENC_PARA->imgTypeSubMask === %d\n",Info_Get_VIDEO_ENC_PARA.imgTypeSubMask);
				printf("Info_Get_VIDEO_ENC_PARA->fpsMain === %d\n",Info_Get_VIDEO_ENC_PARA.fpsMain);
				printf("Info_Get_VIDEO_ENC_PARA->fpsSub === %d\n",Info_Get_VIDEO_ENC_PARA.fpsSub);
				printf("Info_Get_VIDEO_ENC_PARA->idrMain === %d\n",Info_Get_VIDEO_ENC_PARA.idrMain);
				printf("Info_Get_VIDEO_ENC_PARA->idrSub === %d\n",Info_Get_VIDEO_ENC_PARA.idrSub);
		}
		else
		{      
				printf("========================num 1 get VIDEO_ENC_PARA error!---------lGetDeviceCfgHandle_VIDEO_ENC_PARA=%ld!!!!!!!!!!!!\n",lGetDeviceCfgHandle_VIDEO_ENC_PARA);
		}
#endif
		//3 SET_VIDEO_ENC_PARA
#if 1

		switch(type)
		{
				case 1:
						//Info_Get_VIDEO_ENC_PARA.viNo = 0;
						//Info_Get_VIDEO_ENC_PARA.videoType = NVD_VIDEO_TYPE_H264_HIGH_PROFILE;
						Info_Get_VIDEO_ENC_PARA.encFormat = ENC_FORMAT_DOUBLE;//ENC_FORMAT_DOUBLE 双码流  //ENC_FORMAT_SINGLE
						Info_Get_VIDEO_ENC_PARA.bitrateMain = 2048;
						Info_Get_VIDEO_ENC_PARA.bitrateSub = 500;
						//Info_Get_VIDEO_ENC_PARA.qualityMain = 0;
						//Info_Get_VIDEO_ENC_PARA.qualitySub = 0;
						Info_Get_VIDEO_ENC_PARA.encImgTypeMain = ENC_IMG_TYPE_HD1080P;		//ENC_IMG_TYPE_HD1080P
						Info_Get_VIDEO_ENC_PARA.encImgTypeSub = ENC_IMG_TYPE_D1;		//ENC_IMG_TYPE_D1 or ENC_IMG_TYPE_CIF
						Info_Get_VIDEO_ENC_PARA.imgTypeMainMask = ENC_IMG_TYPE_HD1080P;
						Info_Get_VIDEO_ENC_PARA.imgTypeSubMask = ENC_IMG_TYPE_D1;
						Info_Get_VIDEO_ENC_PARA.fpsMain = 25;
						Info_Get_VIDEO_ENC_PARA.fpsSub = 25;
						Info_Get_VIDEO_ENC_PARA.idrMain = 50;
						Info_Get_VIDEO_ENC_PARA.idrSub = 50;
						break;
				case 2:
						//Info_Get_VIDEO_ENC_PARA.viNo = 0;
						//Info_Get_VIDEO_ENC_PARA.videoType = NVD_VIDEO_TYPE_H264_HIGH_PROFILE;
						Info_Get_VIDEO_ENC_PARA.encFormat = ENC_FORMAT_DOUBLE;//ENC_FORMAT_DOUBLE 双码流  //ENC_FORMAT_SINGLE
						Info_Get_VIDEO_ENC_PARA.bitrateMain = 1228;	//1.2m
						Info_Get_VIDEO_ENC_PARA.bitrateSub = 300;
						//Info_Get_VIDEO_ENC_PARA.qualityMain = 0;
						//Info_Get_VIDEO_ENC_PARA.qualitySub = 0;
						Info_Get_VIDEO_ENC_PARA.encImgTypeMain = ENC_IMG_TYPE_HD1080P;		//ENC_IMG_TYPE_HD1080P
						Info_Get_VIDEO_ENC_PARA.encImgTypeSub = ENC_IMG_TYPE_D1;		//ENC_IMG_TYPE_D1 or ENC_IMG_TYPE_CIF
						Info_Get_VIDEO_ENC_PARA.imgTypeMainMask = ENC_IMG_TYPE_HD1080P;
						Info_Get_VIDEO_ENC_PARA.imgTypeSubMask = ENC_IMG_TYPE_D1;
						Info_Get_VIDEO_ENC_PARA.fpsMain = 20;
						Info_Get_VIDEO_ENC_PARA.fpsSub = 15;
						Info_Get_VIDEO_ENC_PARA.idrMain = 50;
						Info_Get_VIDEO_ENC_PARA.idrSub = 50;

						break;
				case 3:
						//Info_Get_VIDEO_ENC_PARA.viNo = 0;
						//Info_Get_VIDEO_ENC_PARA.videoType = NVD_VIDEO_TYPE_H264_HIGH_PROFILE;
						Info_Get_VIDEO_ENC_PARA.encFormat = ENC_FORMAT_DOUBLE;//ENC_FORMAT_DOUBLE 双码流  //ENC_FORMAT_SINGLE
						Info_Get_VIDEO_ENC_PARA.bitrateMain = 600;
						Info_Get_VIDEO_ENC_PARA.bitrateSub = 500;
						//Info_Get_VIDEO_ENC_PARA.qualityMain = 0;
						//Info_Get_VIDEO_ENC_PARA.qualitySub = 0;
						Info_Get_VIDEO_ENC_PARA.encImgTypeMain = ENC_IMG_TYPE_HD720P;		//ENC_IMG_TYPE_HD1080P//ENC_IMG_TYPE_HD720P
						Info_Get_VIDEO_ENC_PARA.encImgTypeSub = ENC_IMG_TYPE_D1;		//ENC_IMG_TYPE_D1 or ENC_IMG_TYPE_CIF
						Info_Get_VIDEO_ENC_PARA.imgTypeMainMask = ENC_IMG_TYPE_HD720P;
						Info_Get_VIDEO_ENC_PARA.imgTypeSubMask = ENC_IMG_TYPE_D1;
						Info_Get_VIDEO_ENC_PARA.fpsMain = 20;
						Info_Get_VIDEO_ENC_PARA.fpsSub = 15;
						Info_Get_VIDEO_ENC_PARA.idrMain = 50;
						Info_Get_VIDEO_ENC_PARA.idrSub = 50;
						break;
				default:
						break;
		}

		int lSetDeviceCfgHandle_VIDEO_ENC_PARA = NVD_SetDeviceCfg(aLogInHandle, NVD_OPCFGTYPE_SETVIDEOENCPARAM, 0, &Info_Get_VIDEO_ENC_PARA, lBufferSize_VIDEO_ENC_PARA);
		if(NVD_OK == lSetDeviceCfgHandle_VIDEO_ENC_PARA)
		{
				printf("....................set VIDEO_ENC_PARA success..................\n");
		}
		else
		{      
				printf("========================num 1 set VIDEO_ENC_PARA error!---------lSetDeviceCfgHandle_VIDEO_ENC_PARA=%u!!!!!!!!!!!!\n",lSetDeviceCfgHandle_VIDEO_ENC_PARA);
		}
		//3 GET_VIDEO_ENC_PARA
		memset(&Info_Get_VIDEO_ENC_PARA, 0, sizeof(NVD_VIDEO_ENC_PARA));
		int rGetDeviceCfgHandle_VIDEO_ENC_PARA = NVD_GetDeviceCfg(aLogInHandle, NVD_OPCFGTYPE_GETVIDEOENCPARAM, 0, &Info_Get_VIDEO_ENC_PARA, lBufferSize_VIDEO_ENC_PARA, &lpReturnSize_VIDEO_ENC_PARA);
		printf("================ after  set video encode para =================\n"); 
		if(NVD_OK == rGetDeviceCfgHandle_VIDEO_ENC_PARA)
		{       
				printf("     get video enc para ok!\n");
				printf("Info_Get_VIDEO_ENC_PARA->viNo === %d\n",Info_Get_VIDEO_ENC_PARA.viNo);
				printf("Info_Get_VIDEO_ENC_PARA->videoType === %d\n",Info_Get_VIDEO_ENC_PARA.videoType);
				printf("Info_Get_VIDEO_ENC_PARA->encFormat === %d\n",Info_Get_VIDEO_ENC_PARA.encFormat);
				printf("Info_Get_VIDEO_ENC_PARA->bitrateMain === %d\n",Info_Get_VIDEO_ENC_PARA.bitrateMain);
				printf("Info_Get_VIDEO_ENC_PARA->bitrateSub === %d\n",Info_Get_VIDEO_ENC_PARA.bitrateSub);
				printf("Info_Get_VIDEO_ENC_PARA->qualityMain === %d\n",Info_Get_VIDEO_ENC_PARA.qualityMain);
				printf("Info_Get_VIDEO_ENC_PARA->qualitySub === %d\n",Info_Get_VIDEO_ENC_PARA.qualitySub);
				printf("Info_Get_VIDEO_ENC_PARA->encImgTypeMain === %d\n",Info_Get_VIDEO_ENC_PARA.encImgTypeMain);
				printf("Info_Get_VIDEO_ENC_PARA->encImgTypeSub === %d\n",Info_Get_VIDEO_ENC_PARA.encImgTypeSub);
				printf("Info_Get_VIDEO_ENC_PARA->imgTypeMainMask === %d\n",Info_Get_VIDEO_ENC_PARA.imgTypeMainMask);
				printf("Info_Get_VIDEO_ENC_PARA->imgTypeSubMask === %d\n",Info_Get_VIDEO_ENC_PARA.imgTypeSubMask);
				printf("Info_Get_VIDEO_ENC_PARA->fpsMain === %d\n",Info_Get_VIDEO_ENC_PARA.fpsMain);
				printf("Info_Get_VIDEO_ENC_PARA->fpsSub === %d\n",Info_Get_VIDEO_ENC_PARA.fpsSub);
				printf("Info_Get_VIDEO_ENC_PARA->idrMain === %d\n",Info_Get_VIDEO_ENC_PARA.idrMain);
				printf("Info_Get_VIDEO_ENC_PARA->idrSub === %d\n",Info_Get_VIDEO_ENC_PARA.idrSub);
		}
		else
		{      
				printf("========================num 1 get VIDEO_ENC_PARA error!---------lGetDeviceCfgHandle_VIDEO_ENC_PARA=%u!!!!!!!!!!!!\n",lGetDeviceCfgHandle_VIDEO_ENC_PARA);
		}
#endif


#if 0 
		//lLogInHandle-登录句柄;0-获取类型;ENC_STREAM_TYPE_MAIN-主流;NVD_NETMODEL_TCP-TCP方式;0-播放窗口句柄
		//lPlayHandle-播放句柄  >=0:成功   其他:失败 
		int lPlayHandle = NVD_RealPlay(lLogInHandle, 0, ENC_STREAM_TYPE_MAIN, NVD_NETMODEL_TCP, 0);
		if(lPlayHandle < 0)
		{
				printf("===========================num 1 play err!---i=%d------lPlayHandle=%u!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", i,lPlayHandle);
				goto out;
		}

		//设置显示回调;return  0:成功   其他:失败;PlayDataCall1-数据回调;0-显示回调用户数据 
		NVD_SetPlayDataCallBack(lPlayHandle, PlayDataCall1, NULL);

		//ENC_STREAM_TYPE_IVA-智能
		int lIvaHandle = NVD_RealPlay(lLogInHandle, 0, ENC_STREAM_TYPE_IVA, NVD_NETMODEL_TCP, 0);
		if(lIvaHandle < 0)
		{
				printf("===========================num 1 iva err!---i=%d------lIvaHandle=%u!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", i,lIvaHandle);
				goto out;
		}

		NVD_SetPlayDataCallBack(lIvaHandle, IvaDataCall1, NULL);

		//        NVD_SetPlateInfoCallBack(lLogInHandle, PlateInfoCall, NULL);
#else

#endif
}


static int IsLANIP(unsigned int nIP)
{
		// filter LAN IP's
		// -------------------------------------------
		// 0.*
		// 10.0.0.0 - 10.255.255.255  class A
		// 172.16.0.0 - 172.31.255.255  class B
		// 192.168.0.0 - 192.168.255.255 class C

		unsigned char nFirst = (unsigned char)nIP;
		unsigned char nSecond = (unsigned char)(nIP >> 8);

		if (nFirst==192 && nSecond==168) // check this 1st, because those LANs IPs are mostly spreaded
				return 1;

		if (nFirst==172 && nSecond>=16 && nSecond<=31)
				return 1;

		if (nFirst==0 || nFirst==10)
				return 1;

		if(nFirst==127)
				return 1;

		if(nFirst==169 && nSecond==254)
				return 1;

		return 0;
}

static void get_local_ip(char* local_ip)
{
		struct sockaddr_in *sin = NULL;
		struct ifaddrs *ifa = NULL, *ifList;

		if (getifaddrs(&ifList) < 0)
				return;

		for (ifa = ifList; ifa != NULL; ifa = ifa->ifa_next)
		{
				if(ifa->ifa_addr->sa_family == AF_INET)
				{
						if(strcmp(ifa->ifa_name,"lo")==0){
								continue;
						}

						sin = (struct sockaddr_in *)ifa->ifa_addr;
						if(IsLANIP(sin->sin_addr.s_addr)){
								strcpy(local_ip,inet_ntoa(sin->sin_addr));
								break;
						}
				}
		}
		freeifaddrs(ifList);
}


int NVD_Login(void)
{
		char local_ip[64]={0};
		get_local_ip(local_ip);
		printf("local ip :%s\n",local_ip);

		NVD_LOGIN_INFO Info;
		memset(&Info, 0, sizeof(NVD_LOGIN_INFO));
		//int LogInHandle = NVD_LogIn2(local_ip, 12560, "admin", "123456", NVD_NETMODEL_TCP, 2000, &Info);
		int LogInHandle = NVD_LogIn2("127.0.0.1", 12560, "admin", "123456", NVD_NETMODEL_TCP, 10000, &Info);
		if(LogInHandle >= 0)
		{
				printf("=================lLogInHandle=%d-------\n", LogInHandle);
				printf("=================================== dev name :%s , type : %d ============================\n",Info.devName,Info.devType);
		}


		return LogInHandle;
}

int Open_Media_Play(LONG aLogInHandle)
{
#if 1
		printf("Open_Media_Play, lLogInHandle:%d\n",aLogInHandle);
		//LogInHandle-登录句柄;0-获取类型;ENC_STREAM_TYPE_MAIN-主流;NVD_NETMODEL_TCP-TCP方式;0-播放窗口句柄
		//PlayHandle-播放句柄  >=0:成功   其他:失败 
		int PlayHandle = NVD_RealPlay(aLogInHandle, 0, ENC_STREAM_TYPE_MAIN, NVD_NETMODEL_TCP, 0);
		if(PlayHandle < 0)
		{
				printf("===== nvd realplay failed--lPlayHandle=%x,  logInHandle=%d !!!!\n", PlayHandle,aLogInHandle);
				//if(aLogInHandle > 0)
				//	NVD_LogOut(aLogInHandle);

				lLogInHandle = NVD_Login();
				if(lLogInHandle < 0)
				{
						printf("============= nvd relogin failed :%x ==========\n",lLogInHandle);
						return -1;              
				}

				return PlayHandle;
		}

		//设置显示回调;return  0:成功   其他:失败;PlayDataCall1-数据回调;0-显示回调用户数据 
		NVD_SetPlayDataCallBack(PlayHandle, PlayDataCall1, NULL);


		return PlayHandle;
#else
		push_data_flag = 1;

		return 0;
#endif

}

int Stop_Media_Play(int PlayHandle)
{
		printf("=========== Stop_Media_Play ==========\n");
#if 1
		if(PlayHandle < 0)
				return 0;

		return NVD_PlaybackStopPlay(PlayHandle);
#else
		push_data_flag = 0;
		return 0;
#endif
}

//800*450; 1024*576
static int dst_pic_width = 512;
static int dst_pic_height = 288;
int Get_Picture(LONG alLogInHandle, LONG alChannelID, BYTE* alpBuffer, LONG* alpReturnSize, unsigned long *aTime)
{
		NVD_JPEG_HEAD Info_JPEG_HEAD;

		int ret = -1;
		ret = NVD_SNAPPicture(alLogInHandle, alChannelID, 0, &Info_JPEG_HEAD);
		if(ret != 0)
				return ret;

		ret = NVD_GetSNAPPicture(alLogInHandle, Info_JPEG_HEAD, alpBuffer, Info_JPEG_HEAD.dataSize, alpReturnSize);
		*aTime = Info_JPEG_HEAD.timeSec;
		//printf(".........head picture quality:%d,  size:%d,  time:%d\n",Info_JPEG_HEAD.quality,Info_JPEG_HEAD.dataSize,Info_JPEG_HEAD.timeSec);

#if 1	
		int dec_size = 0,resize = 0;
		int src_width,src_height;
		char *dec_data =NULL;
		char *rgb_data =NULL;
		ret = decompress_jpeg_from_buffer((char*)alpBuffer, (size_t)*alpReturnSize, &dec_data, (size_t *)&dec_size, &src_width, &src_height);
		//printf("decompress 2222222 ret:%d, dec size=%d, width:%d, height:%d\n",ret,dec_size,src_width,src_height);
		if((dec_data == NULL) || (ret !=0))
		{
				printf("=== decompress_jpeg_from_buffer failed! ===\n");
				return -1;
		}

		ret = rgb_resample((unsigned char *)dec_data, src_width, src_height, (unsigned char **)&rgb_data, (size_t*)&resize, dst_pic_width, dst_pic_height, 0);
		//ret = resize_rgb_double_linear(dec_data, src_width, src_height, &rgb_data, (size_t *)&resize, dst_pic_width, dst_pic_height);
		//ret = resize_rgb_nearest(dec_data, src_width, src_height, &rgb_data, (size_t*)&resize, dst_pic_width, dst_pic_height);
		//printf("decompress 3333333 ret:%d, resize=%d\n",ret,resize);
		if(dec_data)
				free(dec_data);
		if((rgb_data == NULL) || (ret != 0))
		{
				printf("=== resize_rgb_double_linear failed! ===\n");
				return -1;
		}

		memset(alpBuffer,0,*alpReturnSize);
		ret = compress_rgb_to_jpeg_buffer((char **)&alpBuffer, (size_t *)alpReturnSize, rgb_data, dst_pic_width, dst_pic_height);
		if(rgb_data)
				free(rgb_data);
		//printf("decompress 4444444 ret:%d, dst size =%d\n",ret,*alpReturnSize);

#endif
		return ret;
}

//capture audio data
//NVD_AUDIO_TYPE 
//NVD_AUDIO_TYPE_G711A,             /**<  G.711A*/
//NVD_AUDIO_TYPE_G711U,             /**<  G.711U*/
//NVD_AUDIO_TYPE_G726,              /**<  G.726 */
//NVD_AUDIO_TYPE_ILL
int Open_Audio_In(NVD_AUDIO_TYPE aAudioType)
{
		return NVD_OpenLocalAudioIn(aAudioType);
}

int Close_Audio_In(void)
{
		return NVD_CloseLocalAudioIn();
}

// 设置MIC数据回调
// NVD_SetLocalAudioInDataCallBack(LPLOCALAUDIOINDATACALLBACK lpCall, LPVOID lpUser);


//play audio data
int Open_Audio_Out(LONG alLogInHandle)
{
		return NVD_OpenDeviceAudioOut(alLogInHandle);
}

int Close_Audio_Out(LONG alLogInHandle)
{
		return NVD_CloseDeviceAudioOut(alLogInHandle);
}

//NVD_SendAudioDataToDevice(LONG lLogInHandle, BYTE* lpBuffer, LONG lBufferSize);
int Open_Alarm(LONG alLogInHandle)
{
		return NVD_SetAlarmDataCallBack(alLogInHandle, Alarm, NULL);
}

int Send_Alarm_Msg2(unsigned char *buffer, int disk_size)
{
		printf("=================start=================\n");
		char msg[256]={0};
		int ret = 0;
		//int disk_size = 0;
		//alarm time
		msg[0] = AlarmStartTime & 0xff;
		msg[1] = (AlarmStartTime>>8) & 0xff;
		msg[2] = (AlarmStartTime>>16) & 0xff;
		msg[3] = (AlarmStartTime>>24) & 0xff;
		memcpy(msg+4,buffer,disk_size);
		int i =0;
		printf("disk info:\n");
		for(i=0;i<disk_size;i++)
				printf(" %d",buffer[i]);
		printf("\n");
		sleep(40);
		printf("ret:%d time:%ld ,size:%d,msg0:%d\n",ret,AlarmStartTime,disk_size,msg[0]);
		ret = PushMessage((char *)msg, disk_size+4,0);
		int err = GetLastErrorNo();
		printf("ret:%d , err:%d\n",ret,err);
		printf("=================end=================\n");
		return ret;
}


void RTMP_Pop_Audio_Data(void *apdata, char* data,int len,char aDataType)
{
		if(aDataType == 1)
		{
				printf("recv rtmp  data len:%d, %x %x %x %x \n",len,*data,*(data+1),*(data+2),*(data+3) );
				//int frame_length = ((((unsigned int)data[3]&0x03))<<11) | (((unsigned int)data[4]&0xff)<<3) | ((data[5]&0xe0)>>5);
				//int buffer_fullness = (((unsigned int)data[5]&0x1f)<<6)|((data[6]&0xfc) >> 2);
				//printf("rtmp data:%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x, len:%d,num_in:%d,len2:%d ness:%d\n",data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],data[9],data[10],data[11],data[12],data[13],data[14],data[15],data[16],data[17],data[18],data[19],data[20],len,data[6]&0x03,frame_length,buffer_fullness);
		}
		else if(aDataType == 2)
				Send_Alarm_Msg2((unsigned char *)data, len);

		//printf("data:%s\n",data);
		//if(play_audio_enable)
		//	NVD_SendAudioDataToDevice(lLogInHandle, (BYTE *)data, len);
}

pthread_t picture_pid;
void *Push_Picture(void *arg)
{
		int i = 0,ret =-1;
		unsigned long lastTime = 0;
		unsigned long currentTime = 0;
		unsigned long ImgTime = 0;
		struct timeval tv;


#if SAVE_PICTURE_ENABLE
		FILE * tfp=NULL;
		int i=0;
		char sFileName[50];
#endif
		LONG tjlen, terr;

		if(img_buffer == NULL)
				img_buffer = (char *)malloc(IMG_MAX_SIZE);

		if(img_buffer == NULL)
		{
				printf("malloc img_buffer failed!\n");
				return NULL;	
		}
		ret = Get_Picture(lLogInHandle, 1, (BYTE *)img_buffer, &tjlen,&ImgTime);
		printf("Get_Picture time:%d, len:%d, ret:%d\n",ImgTime,tjlen,ret);
		AlarmStartTime = ImgTime;

		int time_step = 0;
		time_step = TIMESTAMP_STEP_4min*10;

		mjpeg_push_flag = 1;
		while(mjpeg_push_flag)
		{
				gettimeofday(&tv,NULL);
				currentTime= tv.tv_sec;

				if((currentTime % time_step == 0) || (lastTime == 0))
				{
						if(currentTime != lastTime)
						{
								for(i=0;i<5;i++)
								{
										ret = Get_Picture(lLogInHandle, 0, (BYTE *)img_buffer, &tjlen,&ImgTime);
										AlarmStartTime = ImgTime;
										//printf("Get_Picture time:%d, len:%d, ret:%d type:%d\n",ImgTime,tjlen,ret,image_type);

#if 1
										if(ret == 0)
										{
												ret = PostPicture(img_buffer, (long)tjlen, currentTime, image_type, 10);
												int err = GetLastErrorNo();
												printf("get last error no:%d\n",err);
												if(ret == 0)
														break;
												else
												{
														printf("D_HttpPostPicture failed err:%d\n",err);
												}
										}
										else
												printf("capture picture failed!\n");
#endif
										usleep(500);
								}
								lastTime = currentTime;
						}
				}
				else
						usleep(100);	

		}

		printf("post picture thread exit\n");
}

void openCapture();
void closeCapture();
/*为了避免阻塞平台的消息回调，这里开一个线程专门处理连接和断开连接相关操作*/
pthread_t rtmp_pid;
int RtmpWorking = 1;
void *RtmpWorkingThread(void *arg)
{
		RTMPMetaData rtmpMetadata = {0};
		int ret = -1;
		while(RtmpWorking)
		{
				/*更改配置后需要重新连接rtmp服务，需要将的当前的采集、播放工作停止，停止当前开启的rtmp服务*/
				if(ConfigChange)
				{
						if(IsOpenCapture)
						{
								Disconnect();
								closeCapture();
						}
						if(rtmp_open_flag)
						{
								ret = ConnectToServer(Config_Type,rtmpMetadata);
								if(ret != 0)
								{
										usleep(100);
										continue;
								}
								openCapture();                       
						}
						ConfigChange = 0;
				}
				else
				{
						usleep(500);
				}
		}
		if(IsOpenCapture)
		{
				Disconnect();
				closeCapture();
		}
		return NULL;
}


pthread_t popdata_pid;
void *popData(void *arg)
{
		printf("pop data ......\n");
		unsigned long apFrameSampleLength =0;
		unsigned long apTimestamp =0;
		unsigned char apFrameSampleType = 0xff;
		char *buffer = NULL;

		popdata_flag = 1;
		while(popdata_flag)
		{
				printf("................. pop data ................\n");
				buffer =  PopData(0, &apFrameSampleLength, &apTimestamp, &apFrameSampleType);
				if(buffer != NULL)
				{
						printf("length === %ld, time stamp === %ld, sample type = %x\n",apFrameSampleLength,apTimestamp,apFrameSampleType);
						//printf("data:%x,%x,%x,%x,%x,%x,%x,%x,%x,%x\n",*buffer,*(buffer+1),*(buffer+2),*(buffer+3),*(buffer+4),*(buffer+5),*(buffer+6),*(buffer+7),*(buffer+8),*(buffer+9));

						if(play_audio_enable)
								;
						//MediaAacPlaySend(tMediaInst, buffer, apFrameSampleLength);
				}
				else
						printf("pop data ============ null\n");
		}

		printf("................ pop pthread exit ...............\n");
		pthread_exit(0);
}

void openCapture()
{
		int ret =0;
		//1.start video
		printf("init media...........\n");
		if(IsOpenCapture)
				return;
#if 1
		lPlayHandle = Open_Media_Play(lLogInHandle);
		if(lPlayHandle < 0)
		{
				printf("start open media play failed..............\n");
				return;
		}
#else
		Open_Media_Play(lLogInHandle);
#endif        

		IsOpenCapture = 1;
		printf("after open media play.............\n");
}        

void closeCapture()
{
		printf("close capture ......\n");
		if(IsOpenCapture == 0)
				return;		

		alarm_flag = 0;
		alarm_start_flag = 0;

		//2.stop popdata
		popdata_flag = 0;

		//3.stop audio
		if(play_audio_enable != 0)
		{
				printf("StopPushData close audio\n");
				//MediaAacPlay(tMediaInst, 0);
		}
#if 1
		//4.stop media capture
		if(Stop_Media_Play(lPlayHandle) == 0)
		{
				lPlayHandle = -1;
				printf(" stop media play ok...............\n");
		}
		else
				printf(" stop media play failed...............\n");
#endif       
		IsOpenCapture = 0;
		printf("close capture ...finished...\n");
}                       


int PopMessgae(void *apData, const char *aMessage)
{
		printf("popmessage call back!!!!\n");
		int ret = 0;
		cJSON *root = cJSON_Parse(aMessage);
		cJSON *name = cJSON_GetObjectItem(root, "Name");
		cJSON *messgae = cJSON_GetObjectItem(root, "Message");
		printf("====popmessage===== %s , len = %d\n",name->valuestring, strlen(aMessage));
		//printf("===========msg:%s\n",aMessage);
		if (memcmp("ConnectionAcceptted", name->valuestring, strlen(name->valuestring)) == 0)
		{
				printf(".................. ConnectionAcceptted .....................\n");
				if(!rtmp_open_flag)
				{
						/*发送数据指令，开启推送数据工作线程*/ 
						alarm_start_flag = 0;
						openCapture();
				}
		}
		else if (memcmp("ConnectionClosed", name->valuestring, strlen(name->valuestring)) == 0)
		{
				printf("..................... ConnectionClosed ....................\n");
				if(!rtmp_open_flag)
				{
						/*停止推送数据*/
						closeCapture();
						/*停止接收数据*/
						popdata_flag = 0;
				}
		}
		else if (memcmp("StartPopData", name->valuestring, strlen(name->valuestring)) == 0)
		{
				printf("..................... StartPopData ....................\n");
				//4.start popdata
				ret = pthread_create(&popdata_pid, NULL, popData, NULL);
				if(ret != 0)
				{
						printf("pop data thread create failed======\n");
				}
		}
#if 1
		else if (memcmp("PopMessage", name->valuestring, strlen(name->valuestring)) == 0)
		{
				printf(" ... message : %s\n",messgae->valuestring);
				printf("........................ PopMessage ...................\n");
				if(strncmp(messgae->valuestring,"2015080300000001",16)==0)
				{
						printf("............ do restart system ...........\n");
						if(NVD_Reset(lLogInHandle)==0)
								printf("............. restart system success ..........\n");
				}
				else if(strncmp(messgae->valuestring,"3031",4)==0)
				{
#if 0
						int ret = PushMessage(0,"12345",5);
						printf("ret === %d\n",ret);	
#else
						printf("............ alarm start ...........\n");
						publicLiveFlag = 0;
						is_recording = 1;
						rtmp_open_flag = 1;
						alarm_flag = 1;
#endif
				}
		}
#endif
		else if (memcmp("PopConfig", name->valuestring, strlen(name->valuestring)) == 0)
		{
				printf(".............. config .............\n");
				if(messgae == NULL)
				{
						printf("messgae =================== null \n");
						cJSON_Delete(root);
						return 0;
				}
#if 1

				printf("messgae->valuestring === %s\n",messgae->valuestring);
				unsigned char * rtmpmessage = (unsigned char *)messgae->valuestring;

				int i;
				unsigned char config[256];
				int result;
				for (i=0; i<256; i++) {
						sscanf((const char*)rtmpmessage+i*2,"%02X",&result);
						config[i] = result & 0xFF;
				}

				int bitrate = config[0];// bitrate 1---1m;2---500k;3---300k;
				int audio = config[1];  // audio enable 0---off; 1----on;
				int nType = config[4];

				if(Config_Bitrate != bitrate )
						Set_Device_Para(lLogInHandle,bitrate);

				if(audio == Config_Audio)
						;
				else if(audio == 1)
				{
						push_audio_enable = audio;
						//NVD_AUDIO_TYPE_G711A,             /**<  G.711A*/
						////NVD_AUDIO_TYPE_G711U,             /**<  G.711U*/
						////NVD_AUDIO_TYPE_G726,              /**<  G.726 */
						//Open_Audio_In(NVD_AUDIO_TYPE_G711A);
				}
				else if(audio == 0)
				{
						push_audio_enable = audio;
						//Close_Audio_In();
				}

				Config_Audio = audio;

				if(Config_Type == nType)
				{
						if(nType == 0 || rtmp_open_flag == 1)
						{
								printf("========== the same config ==========\n");
								Config_Bitrate = bitrate;
								cJSON_Delete(root);
								return 0;
						}
				}

				if(nType == 4)
				{
						//公众 录像
						publicLiveFlag = 1;
						is_recording = 1;
						rtmp_open_flag = 1;
						image_type = 1;
				}
				else if(nType == 3)
				{
						//录像
						publicLiveFlag = 0;
						is_recording = 1;
						rtmp_open_flag = 1;
						image_type = 1;
				}
				else if(nType == 2)
				{
						//公众
						publicLiveFlag = 1;
						is_recording = 0;
						rtmp_open_flag = 1;
						image_type = 2;
				}
				else if(nType == 0)
				{
						//待命
						publicLiveFlag = 0;
						is_recording = 0;
						rtmp_open_flag = 0;
						image_type = 2;
				}
				Config_Bitrate = bitrate;
				Config_Type = nType;
				ConfigChange = 1;

#endif
				printf("................. config end ...............\n");
		}
		cJSON_Delete(root);
		return 0;
}                                                                        


static void set_defalut_config(camera_config_t* config)
{
		memset(config->cid,0,sizeof(config->cid));
		strcpy(config->SNNumber,"ti00000000");
}

static void load_config(camera_config_t* config)
{
		int ret;
		FILE* file = fopen("./camera_config.ini","r");
		if(file == NULL)
		{
				set_defalut_config(config);
				printf("load cofing error,file open failed\n");
				return;
		}

		char buffer[500];
		char key[200];
		char value[300];
		memset(buffer,0,sizeof(buffer));
		memset(key,0,sizeof(key));
		memset(value,0,sizeof(value));
		while(fgets(buffer,500,file) != NULL)
		{
				ret = sscanf(buffer,"%[^=]=%s",key,value);
				if(ret !=2){
						memset(buffer,0,sizeof(buffer));
						memset(key,0,sizeof(key));
						memset(value,0,sizeof(value));
						continue;
				}

				if(strcmp(key,"cid")== 0){
						memset(config->cid,0,sizeof(config->cid));
						strcpy(config->cid,value);
				}else if(strcmp(key,"SNNumber")== 0){
						memset(config->SNNumber,0,sizeof(config->SNNumber));
						strcpy(config->SNNumber,value);
				}

				memset(buffer,0,sizeof(buffer));
				memset(key,0,sizeof(key));
				memset(value,0,sizeof(value));
		}

		if(file)
				fclose(file);
}

int main(int argc, char *argv[])
{
		//注意：必须要忽略SIGPIPE信号 
		signal(SIGPIPE,SIG_IGN);

		load_config(&global_cofig); 
		printf("test camera SN: %s; hashid:%s \n",global_cofig.SNNumber,global_cofig.cid);

		while(1)
		{
				int nRet = NVD_Init();
				if(nRet != 0)
				{
						printf(".... nvd Init failed....\n");
						sleep(1);
						continue;
				}

				lLogInHandle = NVD_Login();	
				if(lLogInHandle < 0)
				{
						printf("============= nvd login failed:%x  ==========\n",lLogInHandle);
						sleep(1);
						continue;
				}
				else
				{
						printf("======= nvd login ok  handle:%d=========\n",lLogInHandle);
						break;
				}
		}

		//设置设备状态回调
		NVD_SetDeviceStaCallBack(lLogInHandle, DeviceStateCall, NULL);

		if(Alarm_enable)
				Open_Alarm(lLogInHandle);

		img_buffer = (char *)malloc(IMG_MAX_SIZE);

		/*--------------------------------------------------------
		 ****           Start lingyang service
		 ***---------------------------------------------------------*/

		int err = 0;
		alarm_start_flag = 0;
		is_recording = 0;
		IsOpenCapture = 0;
		image_type = 2;	
		const char *app_id = "Test";
		//const char *app_id = "YjNG";
		//const char *app_id = "MVbC";
#if 0
		StartCloudService(app_id,global_cofig.SNNumber,global_cofig.cid,NULL,PopMessgae);
		err = GetLastErrorNo();
		printf("StartCloudService errno :%d\n",err);
		usleep(1000);
		StopCloudService();
		err = GetLastErrorNo();
		printf("StopCloudService errno :%d\n",err);
		usleep(1000);
#endif
		while(1)
		{
#if 0
				long id = 1003147;
				char *ip = "223.202.103.158";
				char config[256]={0};
				//sprintf(config,"[Config]\r\nCID=%lu\r\nSN=%s%s\r\nLoginAddress=%s\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nIsSendBroadcast=0\r\nUdpSendInterval=2\r\n",id,app_id,global_cofig.SNNumber,ip);
				//sprintf(config,"[Config]\r\nCID=%s\r\nSN=%s%s\r\nLoginAddress=%s\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nIsSendBroadcast=0\r\nUdpSendInterval=2\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80\r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n",global_cofig.cid,app_id,global_cofig.SNNumber,ip);
				//sprintf(config,"[Config]\r\nCID=hahsjsksksldjsnd\r\nSN=mshiksdsdsmkdsjiasjixknnkndnn\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nIsSendBroadcast=0\r\nUdpSendInterval=2\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80\r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n");
				sprintf(config,"[Config]\r\nCID=%s\r\nSN=%s%s\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nIsSendBroadcast=0\r\nUdpSendInterval=2\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80\r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n",global_cofig.cid,app_id,global_cofig.SNNumber,ip);

				int ret = StartCloudService2(config, NULL, PopMessgae);
#else
				int ret = StartCloudService(app_id,global_cofig.SNNumber,global_cofig.cid,NULL,PopMessgae);

#endif

				if(ret == 0)
				{
						err = GetLastErrorNo();
						printf("D_StartCloudService ok errno :%d\n",err);
						SendLogMessage("StartCloudService");
						char token[128] = {0};
						int len = GetDeviceToken(token,128);
						printf("token ======= %s , len=%d\n",token,strlen(token));
						SetRtmpDataCallBack(NULL,RTMP_Pop_Audio_Data);
						printf("=========start mjpeg push==========\n");
						ret = pthread_create(&picture_pid, NULL, Push_Picture, NULL);
						if(ret != 0)
								printf("push picture thread create failed!.....\n");
						ret = pthread_create(&rtmp_pid,NULL,RtmpWorkingThread,NULL);
						if(ret != 0)
								printf("..... rtmp working thread create failed! .....\n"); 
						break;
				}
				else
				{
						err = GetLastErrorNo();
						printf("======== D_StartCloudService failed ======ret :%d, errno:%d\n",ret,err);
						usleep(500);
				}
		}

		int pid = getpid();
		float version = GetPlatformVersion();
		printf("version : %f\n",version);
		unsigned char data[]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
		int len = SetDeviceInfo("123456789",8);
		printf("set data ret ==== %d\n",len);
		//
		char hashID[50]={0};
		len = ConvertCidToHashID(1003147, hashID,50);
		printf("hashid :%s, len:%d\n",hashID,len);


#if 0
		sleep(5);
		alarm_flag = 1;
		rtmp_open_flag = 1;
		image_type = 3;
		Cfg_State = 3;
#endif

#if 0
		while(ncid == 0)
		{
				StopCloudService();
				sleep(2);
				ncid = StartCloudService(global_cofig.SNNumber,0,NULL,PopMessgae);
		}
#endif

		//    	pthread_t m_tid1;

		//  	pthread_create(&m_tid1,NULL, ThreadFun2, NULL);
		//pthread_create(&m_tid1,NULL, ThreadFun1, NULL);

		//    char cUserChoose = 'r';

		//    cin>>cUserChoose;

		int r=0;
		int count=0;
		//static unsigned char msg[] = {0x05, 0x06};  
		char *msg = "{\"name\":\"abc\"}";  
		while(!exit_flag)
		{
#if 0
				while(r == 0)
				{
						r = PushMessage((const char *)msg,strlen(msg)+1,0);
						count++;
						printf("ret === %d, count:%d\n",r,count);
						sleep(1);
				}
#endif
				sleep(1);
				//send_alarm_msg();
#if 1
				char *p = GetDeviceStatus();
				long socket_buf = GetSocketSendCountQueue();
				printf("state len: %d :%s, buffer:%ld\n", strlen(p),p,socket_buf);
#endif
		}

		printf("main exit 1111!\n");

		exit_flag = 1;

		//停止上传截图              
		mjpeg_push_flag = 0; 
		pthread_cancel(picture_pid);
		pthread_join(picture_pid, NULL);        
		//停止rtmp工作线程
		RtmpWorking = 0; 
		pthread_cancel(rtmp_pid);
		pthread_join(rtmp_pid, NULL);        
		//3.关闭云平台
		StopCloudService();

		NVD_LogOut(lLogInHandle);

		NVD_Fini();

		if(img_buffer)
				free(img_buffer);

		printf("main exit 2222!\n");

		fflush(lpFile_1);

		fclose(lpFile_1);

		return 0;
}

