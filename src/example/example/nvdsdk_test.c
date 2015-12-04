#ifdef _WIN32
#include <windows.h>
#elif defined(__linux__)
#include <stdio.h>
//#include <iostream.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <arpa/inet.h>
#endif

#include "NVDDATA.h"
#include "NVDIVA.h"
#include "NVDDATA_TOOLS.h"
#include "INVDSDK.h"

//using namespace std;



//FILE* lpFile_1 = fopen("1.266", "wb");
FILE* lpFile_1 = NULL;


void PlayDataCall1(LONG lPlayHandle, NVD_DATATYPE eDataType, LONG lDataInfo, BYTE* lpBuffer, LONG lBufferSize, LPVOID lpUser)
{
    printf("================= data buffsize:%u==============\n", lBufferSize-lDataInfo);
    
    //fwrite(lpBuffer+lDataInfo, 1, lBufferSize-lDataInfo, lpFile_1);
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
						char buf[bufLen];
						if (buf == NULL)
						{
							return;
						}
						memcpy(buf, &stReport, iReportHeadLen);
						memcpy(buf+iReportHeadLen, stReport.ivaData, stReport.ivaLen);

						//m_host->ReportEvent2(buf,bufLen);

						//delete []buf;
						//buf = NULL;
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
						char buf[bufLen];
						if (buf == NULL)
						{
							return;
						}
						memcpy(buf, &stReport, iReportHeadLen);
						memcpy(buf+iReportHeadLen, stReport.ivaData, stReport.ivaLen);

						//m_host->ReportEvent2(buf,bufLen);

						//delete []buf;
						//buf = NULL;
					}
					break;
				case NVD_IVA_RESULT_FTPICS://人脸小图
					{
						NVD_IVA_FTPIC_RESULTS* lpr=(NVD_IVA_FTPIC_RESULTS* )(lpBuffer+lDataInfo+sizeof(int));
						printf("2time: %s;sizeof(NVD_IVA_FTPIC_RESULTS)=%u ; lpr->nNumResult: %d", lpr->tTime, sizeof(NVD_IVA_FTPIC_RESULTS), lpr->nNumResult);

						unsigned int i,picLen = 0;
						for (i=0;i<lpr->nNumResult;i++)
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
						char buf[bufLen];
						if (buf == NULL)
						{
							return;
						}
						memcpy(buf, &stReport, iReportHeadLen);
						memcpy(buf+iReportHeadLen, stReport.ivaData, stReport.ivaLen);

						//m_host->ReportEvent2(buf,bufLen);

						//delete []buf;
						//buf = NULL;
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

void Alarm(LONG lLogInHandle, LONG lChannelID, NVD_ALARM_TYPE eAlarmType, LPVOID lpAlarmInfo, LPVOID lpUser)
{
    printf("HELLO_ALARM\n");
    NVD_ALARM_REPORT_INFO* lpInfo = (NVD_ALARM_REPORT_INFO*)lpAlarmInfo;
    
    printf("%d  %d  AlarmType:%d, AlarmName:%s\n", lLogInHandle, lChannelID, lpInfo->alarmType, lpInfo->name);
}


void* ThreadFun1(void *arg)
{
    int i = 0;

    while(1)
    {

        NVD_LOGIN_INFO Info;
        memset(&Info, 0, sizeof(NVD_LOGIN_INFO));
        int lLogInHandle = NVD_LogIn2("192.168.20.49", 12560, "admin", "123456", NVD_NETMODEL_TCP, 2000, &Info);
        if(lLogInHandle < 0)
        {
            printf("====================================num 1 login err!---i=%d------lLogInHandle=%u-------\n", i,lLogInHandle);
            continue;
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

        //NVD_SetPlateInfoCallBack(lLogInHandle, PlateInfoCall, NULL);

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
        	printf(" get video enc para ok!\n");
            
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


int main()
{
    printf("Init result=%d\n", NVD_Init());

    lpFile_1 = fopen("1.266", "wb");
    if(lpFile_1 == NULL)
	printf("fopen 1.266 failed! \n");
	
    pthread_t m_tid1;

    pthread_create(&m_tid1,NULL, ThreadFun1, NULL);

//    char cUserChoose = 'r';
    
//    cin>>cUserChoose;

    printf("main exit 1111!\n");
    
    pthread_join(m_tid1,NULL);

    printf("main exit 2222!\n");

    NVD_Fini();

//    fflush(lpFile_1);
    
//    fclose(lpFile_1);

    return 0;
}

