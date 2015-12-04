////////////////////////////////////////////////////////////////////////// 
///  Copyright (C) 2011
///
/// @file INVDSDK.h
/// @brief   
/// @version   
/// @author  
/// @date  2011-05-12
////////////////////////////////////////////////////////////////////////// 
 
#ifndef _NVDSDK_H_DEFINE
#define _NVDSDK_H_DEFINE

#include "NVDDATA.h"

#if defined(_WIN32) //windows

#define NVDSDK_API  extern "C"__declspec(dllexport)
typedef  unsigned _int64 UINT64;

#elif defined(__linux__)

#define NVDSDK_API     extern "C"
typedef     unsigned int    DWORD;
typedef     unsigned short  WORD;
typedef     unsigned short  USHORT;
typedef     int             LONG;
typedef     unsigned char   BYTE;
#define     BOOL            int
typedef     unsigned int    UINT;
typedef     void*           LPVOID;
typedef     void*           HANDLE;
typedef     unsigned int*   LPDWORD; 
typedef     unsigned long long UINT64;

#ifndef     TRUE
#define     TRUE    1
#endif
#ifndef     FALSE
#define     FALSE   0
#endif
#ifndef     NULL
#define     NULL    0
#endif

#define __stdcall
#define CALLBACK

#ifndef __PLAYRECT_defined
#define __PLAYRECT_defined
typedef struct __PLAYRECT
{
    int x;
    int y;
    int uWidth;
    int uHeight;
}PLAYRECT;
#endif

#ifndef __HWND_defined
#define __HWND_defined
typedef void* HWND; 
#else 
typedef void* HWND; 
#endif

#ifndef __HDC_defined
#define __HDC_defined
typedef struct __DC
{
    void*   surface;        //SDL Surface
    HWND    hWnd;           //HDC window handle
}DC;
typedef DC* HDC;
#else
typedef void* HDC;
#endif

#endif

#define          MAX_DEVICE_COUNT       1024      /**<   ������IPC���� */
#define          MAX_PLAYITEM_COUNT     128      /**<   ÿ��IPC��ಥ��·�� */

/**
*�豸����״̬
*/

typedef enum 
{
    NVD_DEVICE_STA_CON = 0,          /**< ����״̬ */
        NVD_DEVICE_STA_DISCON,       /**< �Ͽ�����״̬ */
}NVD_DEVICE_STA;

/**
*��ȡ�������豸����������
*/

typedef enum 
{
    NVD_OPCFGTYPE_GETDEVICEPARAM = 0,        /**<  ��ȡ�豸���� */  
        NVD_OPCFGTYPE_SETDEVICEPARAM,        /**<  �����豸���� */
        NVD_OPCFGTYPE_GETSIPCONFIG,          /**<  ��ȡSIPЭ������ */
        NVD_OPCFGTYPE_SETSIPCONFIG,          /**<  ����SIPЭ������ */
        NVD_OPCFGTYPE_GETVIDEOENCPARAM,      /**<  ��ȡ��Ƶ������� */
        NVD_OPCFGTYPE_SETVIDEOENCPARAM,      /**<  ������Ƶ������� */
        NVD_OPCFGTYPE_GETAUDIOENCPARAM,      /**<  ��ȡ��Ƶ����������� */
        NVD_OPCFGTYPE_SETAUDIOENCPARAM,      /**<  ������Ƶ����������� */
        NVD_OPCFGTYPE_GETAUDIOOUTPARAM,      /**<  ��ȡ��Ƶ����������� */
        NVD_OPCFGTYPE_SETAUDIOOUTPARAM,      /**<  ������Ƶ����������� */
        NVD_OPCFGTYPE_GETIMAGEPARAM,         /**<  ��ȡͼ����� */
        NVD_OPCFGTYPE_SETIMAGEPARAM,         /**<  ����ͼ����� */
        NVD_OPCFGTYPE_SETIMAGEPARAMDAFAULT,  /**<  ����ͼ������ָ�Ĭ�� */
        NVD_OPCFGTYPE_GETALARMINCONFIG,      /**<  ��ȡ�澯�������� */
        NVD_OPCFGTYPE_SETALARMINCONFIG,      /**<  ���ø澯�������� */
        NVD_OPCFGTYPE_GETALARMINVALUE,       /**<  ��ȡ�澯����ֵ */
        NVD_OPCFGTYPE_GETALARMOUTCONFIG,     /**<  ��ȡ�澯������� */
        NVD_OPCFGTYPE_SETALARMOUTCONFIG,     /**<  ���ø澯������� */
        NVD_OPCFGTYPE_GETDISPLAYCONFIG,      /**<  ��ȡ�豸��ʾ���� */
        NVD_OPCFGTYPE_SETDISPLAYCONFIG,      /**<  �����豸��ʾ���� */
        NVD_OPCFGTYPE_GETTEXTOSDCONFIG,      /**<  ��ȡ�豸�ı�OSD��ʾ���� */
        NVD_OPCFGTYPE_SETTEXTOSDCONFIG,      /**<  �����豸�ı�OSD��ʾ���� */
        NVD_OPCFGTYPE_GETMASKCONFIG,         /**<  ��ȡ�豸�ڵ����� */
        NVD_OPCFGTYPE_SETMASKCONFIG,         /**<  �����豸�ڵ����� */
        NVD_OPCFGTYPE_GETMDCONFIG,           /**<  ��ȡ�豸�ƶ�������� */
        NVD_OPCFGTYPE_SETMDCONFIG,           /**<  �����豸�ƶ�������� */
        NVD_OPCFGTYPE_GETPTZCOMPARAM,        /**<  ��ȡ�豸PTZ����COM�ڲ��� */
        NVD_OPCFGTYPE_SETPTZCOMPARAM,        /**<  �����豸PTZ����COM�ڲ��� */
        NVD_OPCFGTYPE_GETNETPARAM,           /**<  ��ȡ�豸������� */
        NVD_OPCFGTYPE_SETNETPARAM,           /**<  �����豸������� */
        NVD_OPCFGTYPE_GETCOMPARAM,           /**<  ��ȡ�豸COM�ڿ��Ʋ��� */
        NVD_OPCFGTYPE_SETCOMPARAM,           /**<  �����豸COM�ڿ��Ʋ��� */                
        NVD_OPCFGTYPE_GETDEFPRESETPARAM,     /**<  ��ȡ��λ������ */
        NVD_OPCFGTYPE_SETDEFPRESETPARAM,     /**<  ���ù�λ������ */
        NVD_OPCFGTYPE_GETADVNETPARAM,        /**<  ��ȡ�߼��豸������� */
        NVD_OPCFGTYPE_SETADVNETPARAM,        /**<  ���ø߼��豸������� */
        NVD_OPCFGTYPE_GETNTPSERVERPARAM,     /**<  ��ȡNTP���������� */
        NVD_OPCFGTYPE_SETNTPSERVERPARAM,     /**<  ����NTP���������� */
        NVD_OPCFGTYPE_GETEMAILPARAM,         /**<  ��ȡEMAIL���ò��� */
        NVD_OPCFGTYPE_SETEMAILPARAM,         /**<  ����EMAIL���ò��� */
        NVD_OPCFGTYPE_GETPLATEPARAM,         /**<  ��ȡ����ʶ�����ò��� */
        NVD_OPCFGTYPE_SETPLATEPARAM,         /**<  ���ó���ʶ�����ò��� */
        NVD_OPCFGTYPE_GETLOGPARAM,           /**<  ��ȡ��־���ò��� */
        NVD_OPCFGTYPE_SETLOGPARAM,           /**<  ������־���ò��� */
        NVD_OPCFGTYPE_GETSNMPPARAM,          /**<  ��ȡSNMP���ò��� */
        NVD_OPCFGTYPE_SETSNMPPARAM,          /**<  ����SNMP���ò��� */
        NVD_OPCFGTYPE_GETODCONFIG,           /**<  ��ȡ�豸�ڵ�������� */
        NVD_OPCFGTYPE_SETODCONFIG,           /**<  �����豸�ڵ�������� */
        NVD_OPCFGTYPE_GETSNAPCONFIG,         /**<  ��ȡץ�Ĳ��� */
        NVD_OPCFGTYPE_SETSNAPCONFIG,         /**<  ����ץ�Ĳ��� */
        NVD_OPCFGTYPE_GETSTCONFIG,           /**<  ��ȡ����ת�������� */
        NVD_OPCFGTYPE_SETSTCONFIG,           /**<  ���ó���ת�������� */
        NVD_OPCFGTYPE_GETVIDEOENCADVPARAM,   /**<  ��ȡ��Ƶ����߼����� */
        NVD_OPCFGTYPE_SETVIDEOENCADVPARAM,   /**<  ������Ƶ����߼����� */
        NVD_OPCFGTYPE_SETVIDEOENCADVMODEL,   /**<  ������Ƶ����߼�ģʽ */
        NVD_OPCFGTYPE_GETROICONFIG,          /**<  ��ȡ������ǿ���� */
        NVD_OPCFGTYPE_SETROICONFIG,          /**<  ����������ǿ���� */
        NVD_OPCFGTYPE_GETSDCARDCONFIG,       /**<  ��ȡSD������ */
        NVD_OPCFGTYPE_MOUNTSDCARD,           /**<  ����SD�� */
        NVD_OPCFGTYPE_UMOUNTSDCARD,          /**<  ж��SD�� */
        NVD_OPCFGTYPE_FORMATSDCARD,          /**<  ��ʽ��SD�� */
        NVD_OPCFGTYPE_GETRECCONFIG,          /**<  ��ȡ¼������ */
        NVD_OPCFGTYPE_SETRECCONFIG,          /**<  ����¼������ */
        NVD_OPCFGTYPE_STARTRECORD,           /**<  ��ʼ¼�� */
        NVD_OPCFGTYPE_STOPRECORD,            /**<  ֹͣ¼�� */
        NVD_OPCFGTYPE_GETIMAGEADVPARAM,      /**<  ��ȡͼ������߼����� */
        NVD_OPCFGTYPE_SETIMAGEADVPARAM,      /**<  ����ͼ������߼����� */
        NVD_OPCFGTYPE_GETIVASTANARDPARAM,    /**<  ��ȡ���ܼ������ */
        NVD_OPCFGTYPE_SETIVASTANARDPARAM,    /**<  �������ܼ������ */
        NVD_OPCFGTYPE_GETIVAADVANCEDPARAM,   /**<  ��ȡ���ܼ��߼����� */
        NVD_OPCFGTYPE_SETIVAADVANCEDPARAM,   /**<  �������ܼ��߼����� */
        NVD_OPCFGTYPE_GETIVAHLPARAM,         /**<  ��ȡ��������߻������� */
        NVD_OPCFGTYPE_SETIVAHLPARAM,         /**<  ������������߻������� */
        NVD_OPCFGTYPE_GETIVACORDONPARAM,     /**<  ��ȡ���ܾ����߻������� */
        NVD_OPCFGTYPE_SETIVACORDONPARAM,     /**<  �������ܾ����߻������� */
        NVD_OPCFGTYPE_GETIVAPPLCOUNTPARAM,   /**<  ��ȡ��������ͳ�ƻ������� */
        NVD_OPCFGTYPE_SETIVAPPLCOUNTPARAM,   /**<  ������������ͳ�ƻ������� */
        NVD_OPCFGTYPE_GETIVAVEHCOUNTPARAM,   /**<  ��ȡ���ܳ���ͳ�ƻ������� */
        NVD_OPCFGTYPE_SETIVAVEHCOUNTPARAM,   /**<  �������ܳ���ͳ�ƻ������� */
        NVD_OPCFGTYPE_GETFRPARAM,            /**<  ��ȡ����ʶ��������� */
        NVD_OPCFGTYPE_SETFRPARAM,            /**<  ��������ʶ��������� */
        NVD_OPCFGTYPE_GETPTZUNIMODULEPARAM,  /**<  ��ȡһ�廯��о���� */
        NVD_OPCFGTYPE_SETPTZUNIMODULEPARAM,  /**<  ����һ�廯��о���� */
        NVD_OPCFGTYPE_SAVEPTZUNIMODULEPARAM, /**<  ����һ�廯��о���� */
        NVD_OPCFGTYPE_RESETPTZUNIMODULEPARAM,/**<  ��λһ�廯��о���� */
        NVD_OPCFGTYPE_BACKUPALLCONFIG,       /**<  �����������ã����������� */
        NVD_OPCFGTYPE_RESTOREALLCONFIG,      /**<  �ָ��������ã��ϴ���ȥ��*/
}NVD_OPCFGTYPE;
/**
*���ſ���������
*/
typedef enum
{
    NVD_PLAYCTRL_PAUSE = 0,                  /**<  ��ͣ���� */
        NVD_PLAYCTRL_RESUME,                 /**<  �������� */       
        NVD_PLAYCTRL_GETSPEED,               /**<  ��ȡ�����ٶ� */
        NVD_PLAYCTRL_SETSPEED,               /**<  ���ò����ٶ� */
        NVD_PLAYCTRL_GET_POSITION,           /**<  ��ȡ�ļ����Ž��� */
        NVD_PLAYCTRL_SET_POSITION,           /**<  �����ļ����Ž��� */
        NVD_PLAYCTRL_GET_BETIME,             /**<  ��ȡ�ļ���ʼʱ��ͽ���ʱ�� */
        NVD_PLAYCTRL_GET_CURTIME,            /**<  ��ȡ��ǰ����ʱ�� */
        NVD_PLAYCTRL_SET_PALYTIME,           /**<  �����ļ�����ʱ�� */
        NVD_PLAYCTRL_OPEN_AUDIO,             /**<  ������ */
        NVD_PLAYCTRL_CLOSE_AUDIO,            /**<  �ر����� */
        NVD_PLAYCTRL_SET_VOLUME,             /**<  ��������(0-0xFFFF) */
        NVD_PLAYCTRL_GET_VOLUME,             /**<  ��ȡ���� */
		NVD_PLAYCTRL_SET_PLAYPRIORITY,       /**<  ���ò������ȼ�*/
		NVD_PLAYCTRL_GET_PLAYPRIORITY,       /**<  ��ȡ�������ȼ�*/
}NVD_PLAYCTRL;

/**
*�����ٶȿ���������
*/
typedef enum
{
    NVD_PLAYSPEED_8OF1 = 0,                  /**<  8���ٶ� */
        NVD_PLAYSPEED_4OF1,                  /**<  4���ٶ� */
        NVD_PLAYSPEED_2OF1,                  /**<  2���ٶ� */
        NVD_PLAYSPEED_1,                     /**<  �����ٶ� */
        NVD_PLAYSPEED_1OF2,                  /**<  1/2�ٶ� */
        NVD_PLAYSPEED_1OF4,                  /**<  1/4�ٶ� */
        NVD_PLAYSPEED_1OF8,                  /**<  1/8�ٶ� */
        NVD_PLAYSPEED_FFRAME,                /**<  ��֡��  */
        NVD_PLAYSPEED_BFRAME,                /**<  ��֡��  */
}NVD_PLAYSPEED;


/**
*�������ȼ�����
*/
typedef enum 
{
	NVD_PLAYPRIORITY_REAL=0,                  /**<  ʵʱ���� */
	NVD_PLAYPRIORITY_SMOOTH,                  /**<  �������� */
}NVD_PLAYPRIORITY;

/**
*��������
*/
typedef enum 
{
    NVD_PLAYTYPE_REAL = 0,                   /**<  ʵʱ��Ƶ */
        NVD_PLAYTYPE_LOCALFILE,              /**<  ����¼�� */
        NVD_PLAYTYPE_INPUTREAL,              /**<  ʵʱ��Ƶ�������� */
        NVD_PLAYTYPE_INPUTRECORD,            /**<  ¼��������� */
	NVD_PLAYTYPE_REMOTEFILE,				 /**<  Զ�̻ط� */
}NVD_PLAYTYPE;

/**
*��������
*/

typedef enum 
{
    NVD_DATATYPE_VIDEO = 0,                  /**<  ��Ƶ���� */
		NVD_DATATYPE_AUDIO,                  /**<  ��Ƶ���� */       
		NVD_DATATYPE_INTEL,                  /**<  �������� */
		NVD_DATATYPE_STATUS,                 /**<  ״̬����,���ص�ǰ�Ĳ���״̬,LONG��,-1:��ȡ����ʧ��,-2:���ݶ�ȡ���,-3:����������,��ȡʧ�� */
}NVD_DATATYPE;

/**
*��ʾ����
*/

typedef enum 
{
    NVD_SHOWMODEL_NORMAL = 0,                /**< ��ͨģʽ,����ȫ����ʾ */
        NVD_SHOWMODEL_CONST,                 /**< �ȱ�����ʾ */
}NVD_SHOWMODEL;

/**
*�ط��ٶ�����
*/

typedef enum
{
    NVD_FILEPLAY_SPEED_1OF8 = -3,            /**<  1/8�ٶ� */
		NVD_FILEPLAY_SPEED_1OF4 = -2,        /**<  1/4�ٶ� */
		NVD_FILEPLAY_SPEED_1OF2 = -1,        /**<  1/2�ٶ� */
		NVD_FILEPLAY_SPEED_NORAML = 0,       /**<  �����ٶ� */
		NVD_FILEPLAY_SPEED_2OF1 = 1,         /**<  2���ٶ� */
		NVD_FILEPLAY_SPEED_4OF1 = 2,         /**<  4���ٶ� */
		NVD_FILEPLAY_SPEED_8OF1 = 3,         /**<  8���ٶ� */
		NVD_FILEPLAY_SPEED_ONEFRAME = 1000,  /**<  ��֡����(ÿ����һ�β���һ֡) */
}NVD_FILEPLAY_SPEED;

/**
*���Żص�Я����Ϣ�ṹ
*/

typedef struct NVD_PLAYINFO 
{
    LONG                            lPlaySta;      /**<  ����״̬ */
    NVD_PLAYTYPE                    ePlayType;     /**<  �������� */
    UINT64                          llTotalLen;    /**<  �ļ����ֽ��� */
    UINT64                          llRecvLen;     /**<  �ܽ����ֽ��� */
    UINT64                          llPlayLen;     /**<  �ܲ����ֽ��� */
    LONG                            lTotalBufLen;  /**<  �������ֽ��� */
    LONG                            lBufLen;       /**<  �����в����ֽ��� */    
    UINT64                          llErrPkg;      /**<  ���մ�������� */ 
    LONG                            lBitRate;      /**<  ˲ʱ���� */ 
    LONG                            lAvgBitRate;   /**<  ƽ������ */ 
    NVD_TIME                        time;          /**<  ��ǰʱ�� */
    USHORT                          usWidth;       /**<  ��Ƶ�� */
    USHORT                          usHeigth;      /**<  ��Ƶ�� */
    UINT64                          llDecFrame;    /**<  ������֡ */
    UINT64                          llDecIFrame;   /**<  ������I֡ */
    USHORT                          usRate;        /**<  ����/����¼����� */
    BYTE                            lpReserve[2];  /**<  Ԥ�� */
}NVD_PLAYINFO, *LPNVD_PLAYINFO;


/**
 *  �豸״̬�ص�
 *  �豸״̬: 32λ:�����λ��ʼ,���Ϊ1�ֱ��ʾ: ���� ���� ��Ƶ��ʧ
 *  @param  lLogInHandle      [out]        �豸��¼���
 *  @param  eDeviceSta        [out]        �豸״̬
 *  @param  lpUser            [out]        �û�����
 *  @return 
 *  @see LPDEVICESTACALLBACK
 */
typedef void (CALLBACK* LPDEVICESTACALLBACK)(LONG lLogInHandle, NVD_DEVICE_STA eDeviceSta, LPVOID lpUser);

/**
 *  ������Ϣ�ص�
 *  @param  lPlayHandle       [out]        ���ž��
 *  @param  lpPlayInfo        [out]        ������Ϣ�ṹ��ָ��
 *  @param  lpUser            [out]        �û�����
 *  @return 
 *  @see LPPLAYINFOCALLBACK
 */

typedef void (CALLBACK* LPPLAYINFOCALLBACK)(LONG lPlayHandle, LPNVD_PLAYINFO lpPlayInfo, LPVOID lpUser);

/**
 *  ��ʾ�ص�
 *  ��Ƶÿ����һ֡�򴥷�һ�θûص�,��˻ص��в�������������
 *  �ϲ��ͨ��GetDC(HWND)��ȡ���ڻ�ͼ������,���л�ͼ����ʾ���ֵȲ���
 *  @param  lPlayHandle       [out]        ���ž��
 *  @param  hDC               [out]        ���Ŵ��ڻ�ͼ�豸���
 *  @param  lpUser            [out]        �û�����
 *  @return 
 *  @see LPPLAYINFOCALLBACK
 */

typedef void (CALLBACK *LPDRAWFUNCALLBACK)(LONG lPlayHandle, HDC hDC, LPVOID lpUser);

/**
 *  �������ݻص�
 *  lDataType:  0:��Ƶ  1:��Ƶ
 *  @param  lPlayHandle       [out]        ���ž��
 *  @param  eDataType         [out]        ��������
 *  @param  lDataInfo         [out]        ����ͷ����
 *  @param  lpBuffer          [out]        ���ݵ�ַ
 *  @param  lBufferSize       [out]        ���ݳ���
 *  @param  lpUser            [out]        �û�����
 *  @return 
 *  @see LPPLAYDATACALLBACK
 */


typedef void (CALLBACK* LPPLAYDATACALLBACK)(LONG lPlayHandle, NVD_DATATYPE eDataType, LONG lDataInfo, BYTE* lpBuffer, LONG lBufferSize, LPVOID lpUser);

/**
 *  YUV���ݻص�
 *  @param  lPlayHandle         [out]        ���ž��
 *  @param  usWidth             [out]        ��Ƶ���
 *  @param  usHeight            [out]        ��Ƶ�߶�
 *  @param  lDataInfo           [out]        ������Ϣ ����
 *  @param  lpBuffer            [out]        ���ݵ�ַ
 *  @param  lBufferSize         [out]        ���ݳ���
 *  @param  lpUser              [out]        �û�����
 *  @return 
 *  @see LPYUVDATACALLBACK
 */

typedef void (CALLBACK* LPYUVDATACALLBACK)(LONG lPlayHandle, USHORT usWidth, USHORT usHeight, LONG lDataInfo, BYTE* lpBuffer, LONG lBufferSize, LPVOID lpUser);

/**
 *  PCM���ݻص�
 *  @param  lPlayHandle         [out]        ���ž��
 *  @param  nSampleRate         [out]        ������
 *  @param  nChannel            [out]        ͨ����
 *  @param  nBitsPerSample      [out]        ÿ��������ı�����
 *  @param  lDataInfo           [out]        ������Ϣ ����
 *  @param  lpBuffer            [out]        ���ݵ�ַ
 *  @param  lBufferSize         [out]        ���ݳ���
 *  @param  lpUser              [out]        �û�����
 *  @return 
 *  @see LPYUVDATACALLBACK
 */

typedef void (CALLBACK* LPPCMDATACALLBACK)(LONG lPlayHandle, int nSampleRate, int nChannel, int nBitsPerSample, LONG lDataInfo, BYTE* lpBuffer, LONG lBufferSize, LPVOID lpUser);

/**
 *  ������Ƶ���ݻص�
 *  lDataType:  0:��Ƶ  1:��Ƶ
 *  @param  lDataInfo         [out]        ����ͷ����
 *  @param  lpBuffer          [out]        ���ݵ�ַ
 *  @param  lBufferSize       [out]        ���ݳ���
 *  @param  lpUser            [out]        �û�����
 *  @return 
 *  @see LPPLAYDATACALLBACK
 */

typedef void (CALLBACK* LPLOCALAUDIOINDATACALLBACK)(LONG lDataInfo, BYTE* lpBuffer, LONG lBufferSize, LPVOID lpUser);

/**
 *  ͸���������ݻص�
 *  lDataType:  0:��Ƶ  1:��Ƶ
 *  @param  lLogInHandle      [out]        ��¼���
 *  @param  lComID            [out]        ����ID
 *  @param  lpBuffer          [out]        ���ݵ�ַ
 *  @param  lBufferSize       [out]        ���ݳ���
 *  @param  lpUser            [out]        �û�����
 *  @return 
 *  @see LPPLAYDATACALLBACK
 */

typedef void (CALLBACK* LPCOMDATACALLBACK)(LONG lLogInHandle, LONG lComID, BYTE* lpBuffer, LONG lBufferSize, LPVOID lpUser);

/**
 *  �������ݻص�
 *  lDataType:  0:��Ƶ  1:��Ƶ
 *  @param  lLogInHandle      [out]        ��¼���
 *  @param  lChannelID        [out]        ����ͨ��ID
 *  @param  eAlarmType        [out]        ��������
 *  @param  alarmInfo         [out]        ��������
 *  @param  lpUser            [out]        �û�����
 *  @return 
 *  @see LPPLAYDATACALLBACK
 */

typedef void (CALLBACK* LPALARMDATACALLBACK)(LONG lLogInHandle, LONG lChannelID, NVD_ALARM_TYPE eAlarmType, NVD_ALARM_REPORT_INFO alarmInfo, LPVOID lpUser);

/**
 *  �����ǰ�Ƕ���Ϣ�ص� 
 *  @param  lLogInHandle      [out]        ��¼���
 *  @param  PTZReportInfo     [out]        ����ϱ���Ϣ
 *  @param  lpUser            [out]        �û�����
 *  @return 
 *  @see LPPLAYDATACALLBACK
 */

typedef void (CALLBACK* LPPTZREPORTCALLBACK)(LONG lLogInHandle, NVD_PTZ_REPORT_INFO PTZReportInfo, LPVOID lpUser);

/**
 *  ͸����Ϣ�ص� 
 *  @param  lLogInHandle      [out]        ��¼���
 *  @param  IVALPRResult      [out]        ������Ϣ
 *  @param  lpUser            [out]        �û�����
 *  @return 
 *  @see LPOPENINFOCALLBACK
 */

typedef void (CALLBACK* LPOPENINFOCALLBACK)(LONG lLogInHandle, BYTE* lpBuffer, LONG lBufferSize, LPVOID lpUser);

/**
 *  ץ��ͼƬ�ص�
 *  @param  lLogInHandle      [out]        ��¼���
 *  @param  lpPicInfo         [out]        ͼƬ��Ϣ
 *  @param  lpBuffer          [out]        ͼƬ���ݵ�ַ
 *  @param  lBufferSize       [out]        ͼƬ���ݴ�С
 *  @param  lpUser            [out]        �û�����
 *  @return 
 *  @see LPPLATEINFOCALLBACK
 */

typedef int  (CALLBACK *LPPICTUREINFOCALLBACK)(LONG lLogInHandle, LPVOID lpPicInfo, BYTE* lpBuffer, LONG lBufferSize, LPVOID lpUser);

/**
 *  ģ���ʼ��
 *  ����ǰ����ص���
 *  @param
 *  @return 0:�ɹ�   ����:ʧ��
 *  @see NVD_Init
 */

NVDSDK_API LONG __stdcall NVD_Init();
 
/**
 *  ģ�鷴��ʼ��
 *  ���ô˽ӿڻ�ر�����Ӧ��,���ǳ��豸
 *  @param
 *  @return 
 *  @see NVD_Fini
 */
 
NVDSDK_API void __stdcall NVD_Fini();

/**
 *  ��½�豸
 *  �����漰��¼����Ĳ���ǰ����  ����Ѿ���¼�򷵻���ǰ�ĵ�¼���
 *  @param  sDeviceIP         [in]        �豸IP
 *  @param  wDevicePort       [in]        �豸�˿�
 *  @param  sUserName         [in]        �û���
 *  @param  sPassword         [in]        ����
 *  @param  eNetModel         [in]        ��������
 *  @param  dwNetTimeOut      [in]        ���糬ʱʱ��(ms)
 *  @param  lpLogInInfo       [out]       �����豸��Ϣ
 *  @return ��¼���  >=0:�ɹ�   ����:ʧ��
 *  @see NVD_LogIn
 */

NVDSDK_API LONG __stdcall NVD_LogIn(char* sDeviceIP, WORD wDevicePort, char* sUserName, char* sPassword, NVD_NETMODEL eNetModel, NVD_LOGIN_INFO* lpLogInInfo);
NVDSDK_API LONG __stdcall NVD_LogIn2(char* sDeviceIP, WORD wDevicePort, char* sUserName, char* sPassword, NVD_NETMODEL eNetModel, DWORD dwNetTimeOut, NVD_LOGIN_INFO* lpLogInInfo);

/**
 *  �����豸״̬�ص�
 *  @param  lLogInHandle      [in]        ���ž��
 *  @param  lpCall            [in]        ��Ƶ���
 *  @param  lpUser            [in]        ��Ƶ�߶�
 *  @return 0:�ɹ�   ����:ʧ��
 *  @see NVD_SetDeviceStaCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetDeviceStaCallBack(LONG lLogInHandle, LPDEVICESTACALLBACK lpCall, LPVOID lpUser);

/**
 *  �ǳ��豸
 *  ���ô˽ӿڻ�ֹͣ���豸������Ӧ��,���ǳ��豸
 *  @param  lLogInHandle       [in]        ��½���
 *  @return 
 *  @see NVD_SetDeviceStaCallBack
 */

NVDSDK_API void __stdcall NVD_LogOut(LONG lLogInHandle);

/**
 *  ��ȡ�豸����
 *  ��ȡȫ������ʱͨ��������0xFF,������漰����д0xEE
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  eOPCfgType           [in]        ��ȡ����
 *  @param  lChannelID           [in]        ͨ����
 *  @param  lpBuffer             [in]        �������ݴ洢��
 *  @param  lBufferSize          [in]        ��������С
 *  @param  lReturnSize          [in]        �������ݴ�С
 *  @return 0:�ɹ�   ����:ʧ��
 *  @see NVD_GetDeviceCfg
 */


NVDSDK_API LONG __stdcall NVD_GetDeviceCfg(LONG lLogInHandle, NVD_OPCFGTYPE eOPCfgType, LONG lChannelID, LPVOID lpBuffer, LONG lBufferSize, LONG* lpReturnSize);

/**
 *  �����豸����
 *  �����ø��Ƶ�����ͨ��ͨ��������0xFF,������漰����д0xEE
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  eOPCfgType           [in]        ��ȡ����
 *  @param  lChannelID           [in]        ͨ����
 *  @param  lpBuffer             [in]        ���ݴ洢��
 *  @param  lBufferSize          [in]        ��������С
 *  @return 0:�ɹ�   ����:ʧ��
 *  @see NVD_SetDeviceCfg
 */

NVDSDK_API LONG __stdcall NVD_SetDeviceCfg(LONG lLogInHandle, NVD_OPCFGTYPE eOPCfgType, LONG lChannelID, LPVOID lpBuffer, LONG lBufferSize);

/**
 *  ����ʵʱ��Ƶ
 *  ���ž�������ں������ſ���
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  lChannelID           [in]        ��ȡ����
 *  @param  eStreamType          [in]        ͨ����
 *  @param  eNetModel            [in]        ����ģʽ
 *  @param  hPlayWnd             [in]        ���Ŵ��ھ��
 *  @return ���ž��  >=0:�ɹ�   ����:ʧ��
 *  @see NVD_RealPlay
 */


NVDSDK_API LONG __stdcall NVD_RealPlay(LONG lLogInHandle, LONG lChannelID, NVD_ENC_STREAM_TYPE eStreamType, NVD_NETMODEL eNetModel, HWND hPlayWnd);

/**
 *  ���ű���¼��
 *  ���ž�������ں������ſ���
 *  @param  sFilePath           [in]        ¼��·��
 *  @param  hPlayWnd            [in]        ���Ŵ���
 *  @return ���ž��  >=0:�ɹ�   ����:ʧ��
 *  @see NVD_RealPlay
 */

NVDSDK_API LONG __stdcall NVD_PlayBackLocal(char* sFilePath, HWND hPlayWnd);

/**
 *  ��¼��طž��
 *  �þ�����ں���¼���ļ����ҡ��طš��طſ��ơ��رյȲ���
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  eNetModel            [in]        ����ģʽ
 *  @return ���ž��  >=0:�ɹ�   ����:ʧ��
 *  @see NVD_RealPlay,NVD_PlayBackLocal
 */
NVDSDK_API LONG __stdcall NVD_OpenPlayback(LONG lLogInHandle, NVD_NETMODEL eNetModel);

/**
 *  �ر�¼��طž��
 *  �ͷ���Դ
 *  @param  lPlaybackHandle      [in]        ¼��طž��
 *  @return   0:�ɹ�   ����:ʧ��
 *  @see NVD_Close
 */
NVDSDK_API LONG __stdcall NVD_ClosePlayback(LONG lPlaybackHandle);

/**
 *  ��һ������������
 *  �򿪲��������ĺ󣬷��ɽ��в��Ҳ���
 *  @param  lPlaybackHandle      [in]        ¼��طž��
 *  @param  lChannel             [in]        ¼��ͨ����
 *  @param  dwType               [in]        ¼�����ͣ�Ŀǰ��ֵΪ0xffffffff
 *  @param  startTime            [in]        ¼��ʼʱ��
 *  @param  stopTime             [in]        ¼��ֹͣʱ��
 *  @param  dwTimeout            [in]        ���ҳ�ʱʱ�䣬��λ��ms. @brief ����IPC��ѭ��¼�����ɾ���ļ����ò���ʱ�����Ӧ���������У���Ҫ�����������ó�ʱʱ���IPC�˿��ܻᵥ���������������
 *  @return 0:�ɹ�   ����:ʧ��
 *  @see ...
 */
NVDSDK_API LONG __stdcall NVD_PlaybackFindFile(LONG lPlaybackHandle,LONG lChannel,DWORD dwType,NET_TIME* startTime,NET_TIME* stopTime,DWORD dwTimeout);

/**
 *  ������һ���ļ�
 *  �򿪲��������ĺ󣬷��ɽ��б�����
 *  @param  lPlaybackHandle      [in]        ¼��طž��
 *  @param  fileinfo             [out]       ���ҳɹ�ʱ�����¼���ļ���Ϣ
 *  @return 0:�ɹ�   ����:ʧ��(��ʱӦֹͣ����)
 *  @see ...
 */
NVDSDK_API LONG __stdcall NVD_PlaybackFindNextFile(LONG lPlaybackHandle,LPNET_RECORDFILE_INFO fileinfo);

/**
 *  �رղ���������
 *  �ļ�������Ϻ󣬼���ֹͣ���ң�����Ӱ������ļ�/ʱ��β���
 *  @param  lPlaybackHandle      [in]        ¼��طž��
 *  @return 0:�ɹ�   ����:ʧ��
 *  @see ...
 */
NVDSDK_API LONG __stdcall NVD_PlaybackCloseFindFile(LONG lPlaybackHandle);

/**
 *  ���ļ����ط�
 *  
 *  @param  lPlaybackHandle      [in]        ¼��طž��
 *  @param  sFilePath            [in]        ¼���ļ���
 *  @param  hPlayWnd			 [in]		 ���Ŵ��ھ��
 *  @param  dwTimeout            [in]        ���ų�ʱʱ�䣬��λ��ms.���ӿ�ʼ���ŵ�ֹͣ����֮��Ĺ���ʱ�䣩
 *  @return 0:�ɹ�   ����:ʧ��
 *  @see ...
 */
NVDSDK_API LONG __stdcall NVD_PlaybackByName(LONG lPlaybackHandle, const char* sFilePath, HWND hPlayWnd, DWORD dwTimeout);

/**
 *  ��ʱ��λط�
 *  
 *  @param  lPlaybackHandle      [in]        ¼��طž��
 *  @param  lChannel             [in]        ¼��ͨ����
 *  @param  dwType               [in]        ¼�����ͣ�Ŀǰ��ֵΪ0xffffffff
 *  @param  startTime            [in]        ¼��ʼʱ��
 *  @param  stopTime             [in]        ¼��ֹͣʱ��
 *  @param  hPlayWnd			 [in]		 ���Ŵ��ھ��
 *  @param  dwTimeout            [in]        ���ų�ʱʱ�䣬��λ��ms.���ӿ�ʼ���ŵ�ֹͣ����֮��Ĺ���ʱ�䣩
 *  @return 0:�ɹ�   ����:ʧ��
 *  @see ...
 */
NVDSDK_API LONG __stdcall NVD_PlaybackByTime(LONG lPlaybackHandle, LONG lChannel,DWORD dwType, NET_TIME* startTime, NET_TIME* stopTime, HWND hPlayWnd, DWORD dwTimeout);

/**
 *  ֹͣ����
 *  ����������ֻ��ֹͣ���Ŷ���
 *  @param  lPlaybackHandle      [in]        ¼��طž��
 *  @return 0:�ɹ�   ����:ʧ��
 *  @see NVD_Close
 */
NVDSDK_API LONG __stdcall NVD_PlaybackStopPlay(LONG lPlaybackHandle);

/**
 *  �򿪹�������
 *  �˴��Ĳ���������ָ  ʵʱ��Ƶ�������� ���� ¼���������
 *  @param  eType               [in]        ��������
 *  @param  hPlayWnd            [in]        ���Ŵ���
 *  @return lPlayHandle  >=0:�ɹ�   ����:ʧ��
 *  @see NVD_OpenInputPlay
 */

NVDSDK_API LONG __stdcall NVD_OpenInputPlay(NVD_PLAYTYPE ePlayType, HWND hPlayWnd);

/**
 *  ��������
 *  @param  lPlayHandle        [in]        ���ž��
 *  @param  eDataType          [in]        ��������
 *  @param  lDataInfo          [in]        ����ͷ����
 *  @param  lpBuffer           [in]        ���ݵ�ַ
 *  @param  lpBufferSize       [in]        ���ݳ���
 *  @return �ɹ����볤��
 *  @see NVD_InputData
 */

NVDSDK_API LONG __stdcall NVD_InputData(LONG lPlayHandle, NVD_DATATYPE eDataType, LONG lDataInfo, BYTE* lpBuffer, LONG lBufferSize);

/**
 *  ֹͣ����
 *  ���ô˽ӿں������µ�¼�豸
 *  @param  lPlayHandle        [in]        ���ž��
 *  @return 
 *  @see NVD_Close
 */

NVDSDK_API void __stdcall NVD_Close(LONG lPlayHandle);

/**
 *  ������ʾ����
 *  ���ô˽ӿں������µ�¼�豸
 *  @param  lPlayHandle        [in]        ���ž��
 *  @param  eShowModel         [in]        ��ʾ����
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_SetShowMdoel
 */

NVDSDK_API LONG __stdcall NVD_SetShowMdoel(LONG lPlayHandle, NVD_SHOWMODEL eShowModel);

/**
 *  ��ʼ����¼��
 *  ·��δ����,SDK���Զ�����
 *  @param  lPlayHandle        [in]        ���ž��
 *  @param  sFileName          [in]        �ļ�����·��,������׺��  
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_StartRecord
 */

NVDSDK_API LONG __stdcall NVD_StartRecord(LONG lPlayHandle, char* sFileName);

/**
 *  ֹͣ����¼��
 *  @param  lPlayHandle        [in]        ���ž��
 *  @return  
 *  @see NVD_StopRecord
 */

NVDSDK_API void __stdcall NVD_StopRecord(LONG lPlayHandle);

/**
 *  ����ץͼ
 *  ����¼��jpg��bmpͼ,SDK���ݺ�׺���Զ��ж� 
 *  @param  lPlayHandle        [in]        ���ž��
 *  @param  sFileName          [in]        �ļ�����·��,����׺��  
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_CapPicture
 */

NVDSDK_API LONG __stdcall NVD_CapPicture(LONG lPlayHandle, char* sFileName);

/**
 *  ���ſ���
 *  @param  lPlayHandle              [in]        ���ž��
 *  @param  ePlayCtrl                [in]        ����������
 *  @param  lpCtrlData               [in]        �������ݴ洢��
 *  @param  lCtrlDataSize            [in]        �������ݳ���
 *  @param  lpReturnData             [in]        ���Ʒ������ݴ洢��
 *  @param  lReturnDataSize          [in]        ���Ʒ������ݻ�������С
 *  @param  lpReturnSize             [out]       �������ݴ�С
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_PlayCtrl
 */

NVDSDK_API LONG __stdcall NVD_PlayCtrl(LONG lPlayHandle, NVD_PLAYCTRL ePlayCtrl, LPVOID lpCtrlData, LONG lCtrlDataSize, LPVOID lpReturnData, LONG lReturnDataSize, LONG* lpReturnSize);

/**
 *  ���ò�����Ϣ�ص�
 *  @param  lPlayHandle           [in]        ���ž��
 *  @param  lpCall                [in]        ������Ϣ�ص�
 *  @param  lpUser                [in]        ������Ϣ�ص��û�����
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_SetPlayInfoCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetPlayInfoCallBack(LONG lPlayHandle, LPPLAYINFOCALLBACK lpCall, LPVOID lpUser);

/**
 *  ������ʾ�ص�
 *  @param  lPlayHandle           [in]        ���ž��
 *  @param  lpCall                [in]        ��ʾ�ص�
 *  @param  lpUser                [in]        ��ʾ�ص��û�����
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_SetDrawFunCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetDrawFunCallBack(LONG lPlayHandle, LPDRAWFUNCALLBACK lpCall, LPVOID lpUser);

/**
 *  ������ʾ�ص�
 *  @param  lPlayHandle           [in]        ���ž��
 *  @param  eDataType             [in]        �ص���������
 *  @param  lpCall                [in]        ���ݻص�
 *  @param  lpUser                [in]        ��ʾ�ص��û�����
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_SetPlayDataCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetPlayDataCallBack(LONG lPlayHandle, LPPLAYDATACALLBACK lpCall, LPVOID lpUser);

/**
 *  ������Ƶ�������ݻص�
 *  @param  lPlayHandle           [in]        ���ž��
 *  @param  lpCall                [in]        ���ݻص�
 *  @param  lpUser                [in]        ���ݻص��û�����
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_SetYUVDataCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetYUVDataCallBack(LONG lPlayHandle, LPYUVDATACALLBACK lpCall, LPVOID lpUser);

/**
 *  ������Ƶ�������ݻص�
 *  @param  lPlayHandle           [in]        ���ž��
 *  @param  lpCall                [in]        ���ݻص�
 *  @param  lpUser                [in]        ���ݻص��û�����
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_SetPCMDataCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetPCMDataCallBack(LONG lPlayHandle, LPPCMDATACALLBACK lpCall, LPVOID lpUser);

/**
 *  ��PC�����ɼ�
 *  @param  lLogInHandle         [in]        ��¼���
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_OpenMIC
 */

NVDSDK_API LONG __stdcall NVD_OpenLocalAudioIn(NVD_AUDIO_TYPE eAudioType);

/**
 *  �ر�PC�����ɼ�
 *  @param  lLogInHandle         [in]        ��¼���
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_CloseMIC
 */

NVDSDK_API LONG __stdcall NVD_CloseLocalAudioIn();

/**
 *  ���豸�������
 *  @param  lLogInHandle         [in]        ��¼���
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_OpenMIC
 */

NVDSDK_API LONG __stdcall NVD_OpenDeviceAudioOut(LONG lLogInHandle);

/**
 *  �ر��豸�������
 *  @param  lLogInHandle         [in]        ��¼���
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_CloseMIC
 */

NVDSDK_API LONG __stdcall NVD_CloseDeviceAudioOut(LONG lLogInHandle);

/**
 *  ����MIC���ݻص�
 *  @param  lLogInHandle          [in]        ��¼���
 *  @param  lpCall                [in]        ���ݻص�
 *  @param  lpUser                [in]        ���ݻص��û�����
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_SetLocalAudioInDataCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetLocalAudioInDataCallBack(LPLOCALAUDIOINDATACALLBACK lpCall, LPVOID lpUser);

/**
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  lpBuffer             [in]        ���ݵ�ַ
 *  @param  lBufferSize          [in]        ���ݳ���
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_SetMICVOL
 */

NVDSDK_API LONG __stdcall NVD_SendAudioDataToDevice(LONG lLogInHandle, BYTE* lpBuffer, LONG lBufferSize);

/**
 *  ���ô������ݻص�
 *  @param  lLogInHandle          [in]        ��¼���
 *  @param  lpCall                [in]        ���ݻص�
 *  @param  lpUser                [in]        ���ݻص��û�����
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_SetCOMDataCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetComDataCallBack(LONG lLogInHandle, LPCOMDATACALLBACK lpCall, LPVOID lpUser);

/**
 *  ��͸�����ڷ�������
 *  @param  lLogInHandle          [in]        ��¼���
 *  @param  lComID                [in]        �������
 *  @param  lpBuffer              [in]        ���ݵ�ַ
 *  @param  lBufferSize           [in]        ���ݳ���
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_SetCOMDataCallBack
 */

NVDSDK_API LONG __stdcall NVD_SendComData(LONG lLogInHandle, LONG lComID, BYTE* lpBuffer, LONG lBufferSize);

/**
 *  ���ñ������ݻص�
 *  @param  lLogInHandle          [in]        ��¼���
 *  @param  lpCall                [in]        ���ݻص�
 *  @param  lpUser                [in]        ���ݻص��û�����
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_SetAlarmDataCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetAlarmDataCallBack(LONG lLogInHandle, LPALARMDATACALLBACK lpCall, LPVOID lpUser);

/**
 *  ����PTZ�������ݻص�
 *  @param  lLogInHandle          [in]        ��¼���
 *  @param  lpCall                [in]        ���ݻص�
 *  @param  lpUser                [in]        ���ݻص��û�����
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_SetPTZReportCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetPTZReportCallBack(LONG lLogInHandle, LPPTZREPORTCALLBACK lpCall, LPVOID lpUser);

/**
 *  ���ڲ����������
 *  @param  lPlayHandle           [in]        ���ž��
 *  @param  eCtrlType             [in]        ��������
 *  @param  lData                 [in]        ��������
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_PTZCtrl
 */

NVDSDK_API LONG __stdcall NVD_PTZCtrl(LONG lPlayHandle, NVD_PTZ_CTRL_CMD eCtrlType, LONG lData);

/**
 *  ���3D��λ
 *  @param  lPlayHandle           [in]        ���ž��
 *  @param  Ptz3dLocatePara       [in]        ��ѡ�ṹ
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_PTZ_3D_LOCATE
 */
NVDSDK_API LONG __stdcall NVD_PTZ_3D_LOCATE(LONG lPlayHandle, NVD_PTZ_3D_LOCATE_DATA Ptz3dLocateData);

/**
 *  ���ڲ������Ԥ��λ��ѯ
 *  �˺������ڿ�������Զ�Ѱ��,ֻ���ӵ�д˹��ܵ����
 *  @param  lPlayHandle           [in]        ʵʱ��Ƶ���ž��
 *  @param  lpPresetPara          [in]        Ԥ��λ���ؽṹ
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_PTZQueryPreset
 */

NVDSDK_API LONG __stdcall NVD_PTZQueryPreset(LONG lPlayHandle, NVD_PTZ_PRESET_PARA* lpPresetPara);

/**
 *  ���ڲ������Ԥ��λ����
 *  @param  lPlayHandle            [in]        ʵʱ��Ƶ���ž��
 *  @param  lpCtrlPresetPara       [in]        Ԥ��λ�ṹ
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_PTZCtrlPreset
 */

NVDSDK_API LONG __stdcall NVD_PTZCtrlPreset(LONG lPlayHandle, NVD_PTZ_CTRL_PRESET_PARA* lpCtrlPresetPara);

/**
 *  ���ڲ������Ѳ����ѯ
 *  �˺������ڿ�������Զ�Ѱ��,ֻ���ӵ�д˹��ܵ����
 *  @param  lPlayHandle            [in]        ʵʱ��Ƶ���ž��
 *  @param  lpCruisePara           [in]        Ѳ�����ؽṹ
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_PTZQueryCruise
 */

NVDSDK_API LONG __stdcall NVD_PTZQueryCruise(LONG lPlayHandle, NVD_PTZ_CRUISE_PARA* lpCruisePara);

/**
 *  ���ڲ������Ѳ������
 *  �˺������ڿ�������Զ�Ѱ��,ֻ���ӵ�д˹��ܵ����
 *  @param  lPlayHandle                 [in]        ʵʱ��Ƶ���ž��
 *  @param  lpCtrlCruisePara            [in]        Ԥ��λ�ṹ
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_PTZCtrlCruise
 */

NVDSDK_API LONG __stdcall NVD_PTZCtrlCruise(LONG lPlayHandle, NVD_PTZ_CTRL_CRUISE_PARA* lpCtrlCruisePara);

/**
 *  ���ڲ������Ѳ�����û�ȡ
 *  �˺������ڿ�������Զ�Ѱ��,ֻ���ӵ�д˹��ܵ����
 *  @param  lPlayHandle                 [in]        ʵʱ��Ƶ���ž��
 *  @param  lCruiseID                   [in]        Ѳ��ID
 *  @param  lpCruisePointPara           [out]       Ѳ�����ýṹ
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_PTZGetCruisePoint
 */

NVDSDK_API LONG __stdcall NVD_PTZGetCruisePoint(LONG lPlayHandle, LONG lCruiseID, NVD_PTZ_CRUISE_POINT_PARA* lpCruisePointPara);

/**
 *  ���ڲ������Ѳ����������
 *  �˺������ڿ�������Զ�Ѱ��,ֻ���ӵ�д˹��ܵ����
 *  @param  lPlayHandle                 [in]        ʵʱ��Ƶ���ž��
 *  @param  lpCruisePointPara           [in]        Ѳ�����ýṹ
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_PTZSetCruisePoint
 */

NVDSDK_API LONG __stdcall NVD_PTZSetCruisePoint(LONG lPlayHandle, NVD_PTZ_CRUISE_POINT_PARA* lpCruisePointPara);

/**
 *  ֱ���������
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  lChannelID           [in]        ͨ����
 *  @param  eCtrlType            [in]        ��������
 *  @param  lData                [in]        ��������(�ٶ�) 
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_PTZCtrl_EX
 */

NVDSDK_API LONG __stdcall NVD_PTZCtrl_EX(LONG lLogInHandle, LONG lChannelID, NVD_PTZ_CTRL_CMD eCtrlType, LONG lData);

/**
 *  ���3D��λ
 *  @param  lPlayHandle           [in]        ���ž��
 *  @param  Ptz3dLocatePara       [in]        ��ѡ�ṹ
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_PTZ_3D_LOCATE
 */
NVDSDK_API LONG __stdcall NVD_PTZ_3D_LOCATE_EX(LONG lLogInHandle, LONG lChannelID, NVD_PTZ_3D_LOCATE_DATA Ptz3dLocateData);

/**
 *  ֱ�����Ԥ��λ��ѯ
 *  �˺������ڿ�������Զ�Ѱ��,ֻ���ӵ�д˹��ܵ����
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  lChannelID           [in]        ͨ����
 *  @param  lpPresetPara         [in]        Ԥ��λ���ؽṹ
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_PTZQueryPreset_EX
 */

NVDSDK_API LONG __stdcall NVD_PTZQueryPreset_EX(LONG lLogInHandle, LONG lChannelID, NVD_PTZ_PRESET_PARA* lpPresetPara);

/**
 *  ֱ�����Ԥ��λ����
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  lChannelID           [in]        ��Ƶ��λID
 *  @param  lpCtrlPresetPara     [in]        Ԥ��λ�ṹ
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_PTZCtrlPreset_EX
 */

NVDSDK_API LONG __stdcall NVD_PTZCtrlPreset_EX(LONG lLogInHandle, LONG lChannelID, NVD_PTZ_CTRL_PRESET_PARA* lpCtrlPresetPara);

/**
 *  ֱ�����Ѳ����ѯ
 *  �˺������ڿ�������Զ�Ѱ��,ֻ���ӵ�д˹��ܵ����
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  lChannelID           [in]        ��Ƶ��λID
 *  @param  lpCruisePara         [in]        Ѳ�����ؽṹ
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_PTZQueryCruise_EX
 */

NVDSDK_API LONG __stdcall NVD_PTZQueryCruise_EX(LONG lLogInHandle, LONG lChannelID, NVD_PTZ_CRUISE_PARA* lpCruisePara);

/**
 *  ֱ�����Ѳ������
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  lChannelID           [in]        ��Ƶ��λID
 *  @param  lpCtrlCruisePara     [in]        Ԥ��λ�ṹ
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_PTZCtrlCruise_EX
 */

NVDSDK_API LONG __stdcall NVD_PTZCtrlCruise_EX(LONG lLogInHandle, LONG lChannelID, NVD_PTZ_CTRL_CRUISE_PARA* lpCtrlCruisePara);

/**
 *  ֱ�����Ѳ������
 *  �˺������ڿ�������Զ�Ѱ��,ֻ���ӵ�д˹��ܵ����
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  lChannelID           [in]        ��Ƶ��λID
 *  @param  lCruiseID            [in]        Ѳ��ID
 *  @param  lpCruisePointPara    [in]        Ѳ�����ýṹ
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_PTZGetCruisePoint_EX
 */

NVDSDK_API LONG __stdcall NVD_PTZGetCruisePoint_EX(LONG lLogInHandle, LONG lChannelID, LONG lCruiseID, NVD_PTZ_CRUISE_POINT_PARA* lpCruisePointPara);

/**
 *  ֱ�����Ѳ����������
 *  �˺������ڿ�������Զ�Ѱ��,ֻ���ӵ�д˹��ܵ����
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  lChannelID           [in]        ��Ƶ��λID
 *  @param  lpCruisePointPara    [in]        Ѳ�����ýṹ
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_PTZSetCruisePoint_EX
 */

NVDSDK_API LONG __stdcall NVD_PTZSetCruisePoint_EX(LONG lLogInHandle, LONG lChannelID, NVD_PTZ_CRUISE_POINT_PARA* lpCruisePointPara);

/**
 *  �������ݴ���
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  lComIndex            [in]        ���ڱ��
 *  @param  lpBuffer             [in]        ���͵�����
 *  @param  lBufferSize          [in]        ���͵����ݳ���   
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_TransportCom
 */

NVDSDK_API LONG __stdcall NVD_TransportCom(LONG lLogInHandle, LONG lComIndex, BYTE* lpBuffer, LONG lBufferSize);

/**
 *  ˢ����ʾ
 *  �˽ӿڿ�����ͼ����ͣ�Ҳ��Ŵ��ڱ�ˢ��ʱʹ��
 *  @param  lPlayHandle         [in]        ���ž��
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_RefreshShow
 */

NVDSDK_API LONG __stdcall NVD_RefreshShow(LONG lPlayHandle);

/**
 *  ��������
 *  ���ô˽ӿں󴥷���Ӧ����ͨ���ı���
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  lAlarmChannelID      [in]        ����ͨ��
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_CheckTime
 */

NVDSDK_API LONG __stdcall NVD_StartAlarm(LONG lLogInHandle, LONG lAlarmChannelID);

/**
 *  ֹͣ����
 *  ���ô˽ӿں�ֹͣ��Ӧ����ͨ���ı���
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  lAlarmChannelID      [in]        ����ͨ��
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_CheckTime
 */

NVDSDK_API LONG __stdcall NVD_StopAlarm(LONG lLogInHandle, LONG lAlarmChannelID);

/**
 *  ǿ���豸����I֡
 *  �˽ӿ��в���Ƶ������,����ϵͳ������
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  lChannelID           [in]        ͨ����
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_MakeIFrame
 */

NVDSDK_API LONG __stdcall NVD_MakeIFrame(LONG lLogInHandle, LONG lChannelID);

/**
 *  �������õ�����
 *  ���ô˽ӿں󱣴���������
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  Time                 [in]        ���õ�ʱ��
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_CheckTime
 */

NVDSDK_API LONG __stdcall NVD_CheckTime(LONG lLogInHandle, NVD_TIME Time);

/**
 *  �������õ�����
 *  ���ô˽ӿں󱣴���������
 *  @param  lLogInHandle         [in]        ��¼���
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_SaveDeviceCfg
 */

NVDSDK_API LONG __stdcall NVD_SaveDeviceCfg(LONG lLogInHandle);

/**
 *  �����豸
 *  ���ô˽ӿں������µ�¼�豸
 *  @param  lLogInHandle         [in]        ��¼���
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_Reset
 */

NVDSDK_API LONG __stdcall NVD_Reset(LONG lLogInHandle);

/**
 *  �豸�ָ�����
 *  ���ô˽ӿں������µ�¼�豸
 *  @param  lLogInHandle         [in]        ��¼���
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_RestoreCfg
 */

NVDSDK_API LONG __stdcall NVD_RestoreCfg(LONG lLogInHandle);

/**
 *  �豸�ָ�IP
 *  ���ô˽ӿں������µ�¼�豸
 *  @param  lLogInHandle         [in]        ��¼���
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_RestoreIP
 */

NVDSDK_API LONG __stdcall NVD_RestoreIP(LONG lLogInHandle);

/**
 *  ģ����̿��ƽӿ�
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  lChannelID           [in]        ͨ����
 *  @param  CtrlData             [in]        ���̿��ƽṹ
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_KeyBoardCtrl
 */

NVDSDK_API LONG __stdcall NVD_KeyBoardCtrl(LONG lLogInHandle, LONG lChannelID, NVD_KEYBOARD_CTRL_DATA CtrlData);

/**
 *  ����͸����Ϣ�ص�
 *  @param  lLogInHandle          [in]        ��¼���
 *  @param  lpCall                [in]        ���ݻص�
 *  @param  lpUser                [in]        ���ݻص��û�����
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_SetPlateInfoCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetOpenInfoCallBack(LONG lLogInHandle, LPOPENINFOCALLBACK lpCall, LPVOID lpUser);

/**
 *  ������ʾ����
 *  @param  lPlayHandle           [in]        ���ž��
 *  @param  rect                  [in]        ��ʾ����
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_SetShowRect
 */

NVDSDK_API LONG __stdcall NVD_SetShowRect(LONG lPlayHandle, NVD_RECT rect);

/**
 *  ���ÿ���ͼƬ�ص�
 *  @param  lLogInHandl           [in]        ��¼���
 *  @param  lChannelID            [in]        ץ��ͨ��ID
 *  @param  lpCall                [in]        �ص�����
 *  @param  lpUser                [in]        �û�����
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_SetShowRect
 */
NVDSDK_API LONG __stdcall NVD_SetPictureCallBack(LONG lLogInHandle, LONG lChannelID, LPPICTUREINFOCALLBACK lpCall, LPVOID lpUser);

/**
 *  ʵʱץ��(�����ڲ���)
 *  @param  lLogInHandl           [in]        ��¼���
 *  @param  lChannelID            [in]        ץ��ͨ��ID
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_SetShowRect
 */
NVDSDK_API LONG __stdcall NVD_CapPictureEX(LONG lLogInHandle, LONG lChannelID);

/**
 *  ��ȡĿ¼
 *  @param  lLogInHandl           [in]        ��¼���
 *  @param  strParentDir          [in]        ��Ŀ¼
 *  @param  strDir                [out]       ��ȡ����Ŀ¼������ݵ�ַ
 *  @param  lDirSize              [out]       ��ȡĿ¼��С
 *  @return  0:�ɹ�   ����:ʧ��
 *  @see NVD_SetShowRect
 */
NVDSDK_API LONG __stdcall NVD_GetDirectory(LONG lLogInHandle, char* strParentDir, char* strDir, LONG lDirSize);

/**
 *  ����͸������
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  lpInBuffer           [in]        ���뻺��
 *  @param  lInBufferSize        [in]        ���뻺���С
 *  @param  lpOutBuffer          [in]        �������
 *  @param  lOutBufferSize       [in]        ��������С
 *  @param  lpOutBufferSize      [in]        ʵ����������С
 *  @return 0:�ɹ�   ����:ʧ��
 *  @see NVD_TransOpenCfg
 */

NVDSDK_API LONG __stdcall NVD_TransOpenCfg(LONG lLogInHandle, LPVOID lpInBuffer, LONG lInBufferSize, LPVOID lpOutBuffer, LONG lOutBufferSize, LONG* lpReturnBufferSize);

/**
 *  Զ��ץ��
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  bSaveInCard          [in]        �Ƿ����洢��
 *  @param  lpOutHead            [in]        ץ�������Ϣͷ
 *  @return 0:�ɹ�   ����:ʧ��
 *  @see NVD_SNAPPicture
 */

NVDSDK_API LONG __stdcall NVD_SNAPPicture(LONG lLogInHandle, LONG lChannelID, BOOL bSaveInCard, NVD_JPEG_HEAD* lpOutHead);


/**
 *  ��ȡԶ��ץ������
 *  @param  lLogInHandle         [in]        ��¼���
 *  @param  Head                 [in]        ץ��ͷ(ͨ��NVD_SNAPPicture�еķ��ز���lpOutHead�еı����õ�)
 *  @param  lBufferSize          [in]        ��ȡͼƬ�Ĵ�С(ͨ��NVD_SNAPPicture�еķ��ز���lpOutHead�еı����õ�)
 *  @param  lpBuffer             [out]       ��ȡ����ͼƬ���ڴ˻�����
 *  @param  lpReturnSize         [out]       ��ȡ����ͼƬ��С
 *  @return 0:�ɹ�   ����:ʧ��
 *  @see NVD_GetSNAPPicture
 */

NVDSDK_API LONG __stdcall NVD_GetSNAPPicture(LONG lLogInHandle, NVD_JPEG_HEAD Head, BYTE* lpBuffer, LONG lBufferSize, LONG* lpReturnSize);

/**
 * ��ѯǰ��ץ��ͼƬ
 * @param  lLogInHandle         [in]        ��¼���
 * @param  lChannelID           [in]        ץ��ͨ��ID
 * @param  lpFindParam          [in]        ��ѯͼƬ����
 * @param  lppFindHandle        [out]       ��ѯͼƬ���
 * @return 0:�ɹ�  ����:ʧ��
 */
NVDSDK_API LONG __stdcall NVD_FindPicture(LONG lLoginHandle, LONG lChannelID, NVD_FIND_PICTURE_PARAM* lpFindParam, void** lppFindHandle);

/**
 * ��ѯ��һ��ǰ��ץ��ͼƬ
 * @param  lppFindHandle        [in]        ��ѯͼƬ���
 * @param  lpFindData           [out]       ��ѯͼƬ���
 * @return 0:�ɹ�  ����:ʧ��
 */
NVDSDK_API LONG __stdcall NVD_FindNextPicture(void* lpFindHandle, NVD_FIND_PICTURE* lpFindData);

/**
 * �رղ�ѯǰ��ץ��ͼƬ
 * @param  lppFindHandle        [in]        ��ѯͼƬ���
 * @return 0:�ɹ�  ����:ʧ��
 */
NVDSDK_API LONG __stdcall NVD_CloseFindPicture(void* lpFindHandle);

/**
 * ��ȡǰ��ץ��ͼƬ����
 * @param  lpFindHandle         [in]        ��ѯͼƬ���
 * @param  lpszFileName         [in]        ǰ��ͼƬ��
 * @param  lpszSavedFileName    [in]        ���ر����ļ�·��
 * @return 0:�ɹ�  ����:ʧ��
 */
NVDSDK_API LONG __stdcall NVD_GetPicture(void* lpFindHandle, const char* lpszFileName, const char* lpszSavedFileName);

/**
 * ��ȡǰ��ץ��ͼƬ����
 * @param  lpFindHandle         [in]        ��ѯͼƬ���
 * @param  lpszFileName         [in]        ǰ��ͼƬ��
 * @param  lpszSavedFileName    [in]        ��ȡͼƬ���ݻ���
 * @param  dwBufLen             [in]        ͼƬ�������ݴ�С
 * @param  lpdwRetLen           [out]       ʵ���յ������ݴ�С������Ϊ��
 * @return 0:�ɹ�  ����:ʧ��
 */
NVDSDK_API LONG __stdcall NVD_GetPictureEx(void* lpFindHandle, const char* lpszFileName, void* lpSavedFileBuf, DWORD dwBufLen, DWORD* lpdwRetLen);

/**
 * ��ѯ��ǰ�û�
 * @param  lLogInHandle         [in]        ��¼���
 * @param  pUserInfo            [out]       ����ע����û���Ϣ
 * @param  pUserCount           [out]       ����ע����û�����
 * @return 0:�ɹ�  ����: ������
 */
NVDSDK_API LONG __stdcall NVD_GetUsers(LONG lLoginHandle, NVD_USER_PARA* pUserInfo, int* pUserCount);

/**
 * ע���û�
 * @param  lLogInHandle         [in]        ��¼���
 * @param  pUserInfo            [out]       ע����û���Ϣ
 * @return 0:�ɹ�  ����: ������
 */
NVDSDK_API LONG __stdcall NVD_AddUser(LONG lLoginHandle, const NVD_USER_PARA* pUserInfo);

/**
 * ɾ���û�
 * @param  lLogInHandle         [in]        ��¼���
 * @param  pUserInfo            [out]       Ҫɾ�����û���
 * @return 0:�ɹ�  ����: ������
 */
NVDSDK_API LONG __stdcall NVD_DeleteUser(LONG lLoginHandle, const char* pUsername);

/**
 * �޸��û���Ϣ
 * @param  lLogInHandle         [in]        ��¼���
 * @param  pUserInfo            [in]        Ҫ�޸ĵ��û���Ϣ
 * @param  pOldPass             [in]        ԭ����
 * @return 0:�ɹ�  ����: ������
 */
NVDSDK_API LONG __stdcall NVD_ModifyUser(LONG lLoginHandle, const NVD_USER_PARA* pUserInfo, const char* pOldPass);


#endif//end of _NVDSDK_H_DEFINE

