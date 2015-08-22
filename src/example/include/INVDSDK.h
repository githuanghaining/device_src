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

#define          MAX_DEVICE_COUNT       1024      /**<   最多接入IPC个数 */
#define          MAX_PLAYITEM_COUNT     128      /**<   每个IPC最多播放路数 */

/**
*设备连接状态
*/

typedef enum 
{
    NVD_DEVICE_STA_CON = 0,          /**< 连接状态 */
        NVD_DEVICE_STA_DISCON,       /**< 断开连接状态 */
}NVD_DEVICE_STA;

/**
*获取和设置设备配置命令字
*/

typedef enum 
{
    NVD_OPCFGTYPE_GETDEVICEPARAM = 0,        /**<  获取设备参数 */  
        NVD_OPCFGTYPE_SETDEVICEPARAM,        /**<  设置设备参数 */
        NVD_OPCFGTYPE_GETSIPCONFIG,          /**<  获取SIP协议配置 */
        NVD_OPCFGTYPE_SETSIPCONFIG,          /**<  设置SIP协议配置 */
        NVD_OPCFGTYPE_GETVIDEOENCPARAM,      /**<  获取视频编码参数 */
        NVD_OPCFGTYPE_SETVIDEOENCPARAM,      /**<  设置视频编码参数 */
        NVD_OPCFGTYPE_GETAUDIOENCPARAM,      /**<  获取音频编码输入参数 */
        NVD_OPCFGTYPE_SETAUDIOENCPARAM,      /**<  设置音频编码输入参数 */
        NVD_OPCFGTYPE_GETAUDIOOUTPARAM,      /**<  获取音频解码输出参数 */
        NVD_OPCFGTYPE_SETAUDIOOUTPARAM,      /**<  设置音频解码输出参数 */
        NVD_OPCFGTYPE_GETIMAGEPARAM,         /**<  获取图像参数 */
        NVD_OPCFGTYPE_SETIMAGEPARAM,         /**<  设置图像参数 */
        NVD_OPCFGTYPE_SETIMAGEPARAMDAFAULT,  /**<  设置图像参数恢复默认 */
        NVD_OPCFGTYPE_GETALARMINCONFIG,      /**<  获取告警输入配置 */
        NVD_OPCFGTYPE_SETALARMINCONFIG,      /**<  设置告警输入配置 */
        NVD_OPCFGTYPE_GETALARMINVALUE,       /**<  获取告警输入值 */
        NVD_OPCFGTYPE_GETALARMOUTCONFIG,     /**<  获取告警输出配置 */
        NVD_OPCFGTYPE_SETALARMOUTCONFIG,     /**<  设置告警输出配置 */
        NVD_OPCFGTYPE_GETDISPLAYCONFIG,      /**<  获取设备显示配置 */
        NVD_OPCFGTYPE_SETDISPLAYCONFIG,      /**<  设置设备显示配置 */
        NVD_OPCFGTYPE_GETTEXTOSDCONFIG,      /**<  获取设备文本OSD显示配置 */
        NVD_OPCFGTYPE_SETTEXTOSDCONFIG,      /**<  设置设备文本OSD显示配置 */
        NVD_OPCFGTYPE_GETMASKCONFIG,         /**<  获取设备遮挡配置 */
        NVD_OPCFGTYPE_SETMASKCONFIG,         /**<  设置设备遮挡配置 */
        NVD_OPCFGTYPE_GETMDCONFIG,           /**<  获取设备移动侦测配置 */
        NVD_OPCFGTYPE_SETMDCONFIG,           /**<  设置设备移动侦测配置 */
        NVD_OPCFGTYPE_GETPTZCOMPARAM,        /**<  获取设备PTZ控制COM口参数 */
        NVD_OPCFGTYPE_SETPTZCOMPARAM,        /**<  设置设备PTZ控制COM口参数 */
        NVD_OPCFGTYPE_GETNETPARAM,           /**<  获取设备网络参数 */
        NVD_OPCFGTYPE_SETNETPARAM,           /**<  设置设备网络参数 */
        NVD_OPCFGTYPE_GETCOMPARAM,           /**<  获取设备COM口控制参数 */
        NVD_OPCFGTYPE_SETCOMPARAM,           /**<  设置设备COM口控制参数 */                
        NVD_OPCFGTYPE_GETDEFPRESETPARAM,     /**<  获取归位点配置 */
        NVD_OPCFGTYPE_SETDEFPRESETPARAM,     /**<  设置归位点配置 */
        NVD_OPCFGTYPE_GETADVNETPARAM,        /**<  获取高级设备网络参数 */
        NVD_OPCFGTYPE_SETADVNETPARAM,        /**<  设置高级设备网络参数 */
        NVD_OPCFGTYPE_GETNTPSERVERPARAM,     /**<  获取NTP服务器参数 */
        NVD_OPCFGTYPE_SETNTPSERVERPARAM,     /**<  设置NTP服务器参数 */
        NVD_OPCFGTYPE_GETEMAILPARAM,         /**<  获取EMAIL配置参数 */
        NVD_OPCFGTYPE_SETEMAILPARAM,         /**<  设置EMAIL配置参数 */
        NVD_OPCFGTYPE_GETPLATEPARAM,         /**<  获取车牌识别配置参数 */
        NVD_OPCFGTYPE_SETPLATEPARAM,         /**<  设置车牌识别配置参数 */
        NVD_OPCFGTYPE_GETLOGPARAM,           /**<  获取日志配置参数 */
        NVD_OPCFGTYPE_SETLOGPARAM,           /**<  设置日志配置参数 */
        NVD_OPCFGTYPE_GETSNMPPARAM,          /**<  获取SNMP配置参数 */
        NVD_OPCFGTYPE_SETSNMPPARAM,          /**<  设置SNMP配置参数 */
        NVD_OPCFGTYPE_GETODCONFIG,           /**<  获取设备遮挡侦测配置 */
        NVD_OPCFGTYPE_SETODCONFIG,           /**<  设置设备遮挡侦测配置 */
        NVD_OPCFGTYPE_GETSNAPCONFIG,         /**<  获取抓拍参数 */
        NVD_OPCFGTYPE_SETSNAPCONFIG,         /**<  设置抓拍参数 */
        NVD_OPCFGTYPE_GETSTCONFIG,           /**<  获取场景转换侦测参数 */
        NVD_OPCFGTYPE_SETSTCONFIG,           /**<  设置场景转换侦测参数 */
        NVD_OPCFGTYPE_GETVIDEOENCADVPARAM,   /**<  获取视频编码高级参数 */
        NVD_OPCFGTYPE_SETVIDEOENCADVPARAM,   /**<  设置视频编码高级参数 */
        NVD_OPCFGTYPE_SETVIDEOENCADVMODEL,   /**<  设置视频编码高级模式 */
        NVD_OPCFGTYPE_GETROICONFIG,          /**<  获取区域增强配置 */
        NVD_OPCFGTYPE_SETROICONFIG,          /**<  设置区域增强配置 */
        NVD_OPCFGTYPE_GETSDCARDCONFIG,       /**<  获取SD卡配置 */
        NVD_OPCFGTYPE_MOUNTSDCARD,           /**<  挂载SD卡 */
        NVD_OPCFGTYPE_UMOUNTSDCARD,          /**<  卸载SD卡 */
        NVD_OPCFGTYPE_FORMATSDCARD,          /**<  格式化SD卡 */
        NVD_OPCFGTYPE_GETRECCONFIG,          /**<  获取录像配置 */
        NVD_OPCFGTYPE_SETRECCONFIG,          /**<  设置录像配置 */
        NVD_OPCFGTYPE_STARTRECORD,           /**<  开始录像 */
        NVD_OPCFGTYPE_STOPRECORD,            /**<  停止录像 */
        NVD_OPCFGTYPE_GETIMAGEADVPARAM,      /**<  获取图像参数高级配置 */
        NVD_OPCFGTYPE_SETIMAGEADVPARAM,      /**<  设置图像参数高级配置 */
        NVD_OPCFGTYPE_GETIVASTANARDPARAM,    /**<  获取智能检测配置 */
        NVD_OPCFGTYPE_SETIVASTANARDPARAM,    /**<  设置智能检测配置 */
        NVD_OPCFGTYPE_GETIVAADVANCEDPARAM,   /**<  获取智能检测高级配置 */
        NVD_OPCFGTYPE_SETIVAADVANCEDPARAM,   /**<  设置智能检测高级配置 */
        NVD_OPCFGTYPE_GETIVAHLPARAM,         /**<  获取智能身高线基本配置 */
        NVD_OPCFGTYPE_SETIVAHLPARAM,         /**<  设置智能身高线基本配置 */
        NVD_OPCFGTYPE_GETIVACORDONPARAM,     /**<  获取智能警戒线基本配置 */
        NVD_OPCFGTYPE_SETIVACORDONPARAM,     /**<  设置智能警戒线基本配置 */
        NVD_OPCFGTYPE_GETIVAPPLCOUNTPARAM,   /**<  获取智能人流统计基本配置 */
        NVD_OPCFGTYPE_SETIVAPPLCOUNTPARAM,   /**<  设置智能人流统计基本配置 */
        NVD_OPCFGTYPE_GETIVAVEHCOUNTPARAM,   /**<  获取智能车流统计基本配置 */
        NVD_OPCFGTYPE_SETIVAVEHCOUNTPARAM,   /**<  设置智能车流统计基本配置 */
        NVD_OPCFGTYPE_GETFRPARAM,            /**<  获取人脸识别基本配置 */
        NVD_OPCFGTYPE_SETFRPARAM,            /**<  设置人脸识别基本配置 */
        NVD_OPCFGTYPE_GETPTZUNIMODULEPARAM,  /**<  获取一体化机芯配置 */
        NVD_OPCFGTYPE_SETPTZUNIMODULEPARAM,  /**<  设置一体化机芯配置 */
        NVD_OPCFGTYPE_SAVEPTZUNIMODULEPARAM, /**<  保存一体化机芯配置 */
        NVD_OPCFGTYPE_RESETPTZUNIMODULEPARAM,/**<  复位一体化机芯配置 */
        NVD_OPCFGTYPE_BACKUPALLCONFIG,       /**<  备份所有配置（下载下来） */
        NVD_OPCFGTYPE_RESTOREALLCONFIG,      /**<  恢复所有配置（上传上去）*/
}NVD_OPCFGTYPE;
/**
*播放控制命令字
*/
typedef enum
{
    NVD_PLAYCTRL_PAUSE = 0,                  /**<  暂停播放 */
        NVD_PLAYCTRL_RESUME,                 /**<  继续播放 */       
        NVD_PLAYCTRL_GETSPEED,               /**<  获取播放速度 */
        NVD_PLAYCTRL_SETSPEED,               /**<  设置播放速度 */
        NVD_PLAYCTRL_GET_POSITION,           /**<  获取文件播放进度 */
        NVD_PLAYCTRL_SET_POSITION,           /**<  设置文件播放进度 */
        NVD_PLAYCTRL_GET_BETIME,             /**<  获取文件开始时间和结束时间 */
        NVD_PLAYCTRL_GET_CURTIME,            /**<  获取当前播放时间 */
        NVD_PLAYCTRL_SET_PALYTIME,           /**<  设置文件播放时间 */
        NVD_PLAYCTRL_OPEN_AUDIO,             /**<  打开声音 */
        NVD_PLAYCTRL_CLOSE_AUDIO,            /**<  关闭声音 */
        NVD_PLAYCTRL_SET_VOLUME,             /**<  设置音量(0-0xFFFF) */
        NVD_PLAYCTRL_GET_VOLUME,             /**<  获取音量 */
		NVD_PLAYCTRL_SET_PLAYPRIORITY,       /**<  设置播放优先级*/
		NVD_PLAYCTRL_GET_PLAYPRIORITY,       /**<  获取播放优先级*/
}NVD_PLAYCTRL;

/**
*播放速度控制命令字
*/
typedef enum
{
    NVD_PLAYSPEED_8OF1 = 0,                  /**<  8倍速度 */
        NVD_PLAYSPEED_4OF1,                  /**<  4倍速度 */
        NVD_PLAYSPEED_2OF1,                  /**<  2倍速度 */
        NVD_PLAYSPEED_1,                     /**<  正常速度 */
        NVD_PLAYSPEED_1OF2,                  /**<  1/2速度 */
        NVD_PLAYSPEED_1OF4,                  /**<  1/4速度 */
        NVD_PLAYSPEED_1OF8,                  /**<  1/8速度 */
        NVD_PLAYSPEED_FFRAME,                /**<  单帧进  */
        NVD_PLAYSPEED_BFRAME,                /**<  单帧退  */
}NVD_PLAYSPEED;


/**
*播放优先级处理
*/
typedef enum 
{
	NVD_PLAYPRIORITY_REAL=0,                  /**<  实时优先 */
	NVD_PLAYPRIORITY_SMOOTH,                  /**<  流畅优先 */
}NVD_PLAYPRIORITY;

/**
*播放类型
*/
typedef enum 
{
    NVD_PLAYTYPE_REAL = 0,                   /**<  实时视频 */
        NVD_PLAYTYPE_LOCALFILE,              /**<  本地录像 */
        NVD_PLAYTYPE_INPUTREAL,              /**<  实时视频灌流播放 */
        NVD_PLAYTYPE_INPUTRECORD,            /**<  录像灌流播放 */
	NVD_PLAYTYPE_REMOTEFILE,				 /**<  远程回放 */
}NVD_PLAYTYPE;

/**
*数据类型
*/

typedef enum 
{
    NVD_DATATYPE_VIDEO = 0,                  /**<  视频数据 */
		NVD_DATATYPE_AUDIO,                  /**<  音频数据 */       
		NVD_DATATYPE_INTEL,                  /**<  智能数据 */
		NVD_DATATYPE_STATUS,                 /**<  状态数据,返回当前的播放状态,LONG型,-1:读取数据失败,-2:数据读取完毕,-3:缓冲区不足,读取失败 */
}NVD_DATATYPE;

/**
*显示类型
*/

typedef enum 
{
    NVD_SHOWMODEL_NORMAL = 0,                /**< 普通模式,画面全屏显示 */
        NVD_SHOWMODEL_CONST,                 /**< 等比例显示 */
}NVD_SHOWMODEL;

/**
*回放速度设置
*/

typedef enum
{
    NVD_FILEPLAY_SPEED_1OF8 = -3,            /**<  1/8速度 */
		NVD_FILEPLAY_SPEED_1OF4 = -2,        /**<  1/4速度 */
		NVD_FILEPLAY_SPEED_1OF2 = -1,        /**<  1/2速度 */
		NVD_FILEPLAY_SPEED_NORAML = 0,       /**<  正常速度 */
		NVD_FILEPLAY_SPEED_2OF1 = 1,         /**<  2倍速度 */
		NVD_FILEPLAY_SPEED_4OF1 = 2,         /**<  4倍速度 */
		NVD_FILEPLAY_SPEED_8OF1 = 3,         /**<  8倍速度 */
		NVD_FILEPLAY_SPEED_ONEFRAME = 1000,  /**<  单帧播放(每调用一次播放一帧) */
}NVD_FILEPLAY_SPEED;

/**
*播放回调携带信息结构
*/

typedef struct NVD_PLAYINFO 
{
    LONG                            lPlaySta;      /**<  播放状态 */
    NVD_PLAYTYPE                    ePlayType;     /**<  播放类型 */
    UINT64                          llTotalLen;    /**<  文件总字节数 */
    UINT64                          llRecvLen;     /**<  总接收字节数 */
    UINT64                          llPlayLen;     /**<  总播放字节数 */
    LONG                            lTotalBufLen;  /**<  缓存总字节数 */
    LONG                            lBufLen;       /**<  缓存中残留字节数 */    
    UINT64                          llErrPkg;      /**<  接收错误包次数 */ 
    LONG                            lBitRate;      /**<  瞬时码率 */ 
    LONG                            lAvgBitRate;   /**<  平均码率 */ 
    NVD_TIME                        time;          /**<  当前时间 */
    USHORT                          usWidth;       /**<  视频宽 */
    USHORT                          usHeigth;      /**<  视频高 */
    UINT64                          llDecFrame;    /**<  解码总帧 */
    UINT64                          llDecIFrame;   /**<  解码总I帧 */
    USHORT                          usRate;        /**<  播放/下载录像进度 */
    BYTE                            lpReserve[2];  /**<  预留 */
}NVD_PLAYINFO, *LPNVD_PLAYINFO;


/**
 *  设备状态回调
 *  设备状态: 32位:从最高位开始,如果为1分别表示: 在线 掉线 视频丢失
 *  @param  lLogInHandle      [out]        设备登录句柄
 *  @param  eDeviceSta        [out]        设备状态
 *  @param  lpUser            [out]        用户数据
 *  @return 
 *  @see LPDEVICESTACALLBACK
 */
typedef void (CALLBACK* LPDEVICESTACALLBACK)(LONG lLogInHandle, NVD_DEVICE_STA eDeviceSta, LPVOID lpUser);

/**
 *  播放信息回调
 *  @param  lPlayHandle       [out]        播放句柄
 *  @param  lpPlayInfo        [out]        播放信息结构体指针
 *  @param  lpUser            [out]        用户数据
 *  @return 
 *  @see LPPLAYINFOCALLBACK
 */

typedef void (CALLBACK* LPPLAYINFOCALLBACK)(LONG lPlayHandle, LPNVD_PLAYINFO lpPlayInfo, LPVOID lpUser);

/**
 *  显示回调
 *  视频每播放一帧则触发一次该回调,因此回调中不可做复杂运算
 *  上层可通过GetDC(HWND)获取窗口绘图上下文,进行绘图或显示文字等操作
 *  @param  lPlayHandle       [out]        播放句柄
 *  @param  hDC               [out]        播放窗口绘图设备句柄
 *  @param  lpUser            [out]        用户数据
 *  @return 
 *  @see LPPLAYINFOCALLBACK
 */

typedef void (CALLBACK *LPDRAWFUNCALLBACK)(LONG lPlayHandle, HDC hDC, LPVOID lpUser);

/**
 *  播放数据回调
 *  lDataType:  0:视频  1:音频
 *  @param  lPlayHandle       [out]        播放句柄
 *  @param  eDataType         [out]        数据类型
 *  @param  lDataInfo         [out]        数据头长度
 *  @param  lpBuffer          [out]        数据地址
 *  @param  lBufferSize       [out]        数据长度
 *  @param  lpUser            [out]        用户数据
 *  @return 
 *  @see LPPLAYDATACALLBACK
 */


typedef void (CALLBACK* LPPLAYDATACALLBACK)(LONG lPlayHandle, NVD_DATATYPE eDataType, LONG lDataInfo, BYTE* lpBuffer, LONG lBufferSize, LPVOID lpUser);

/**
 *  YUV数据回调
 *  @param  lPlayHandle         [out]        播放句柄
 *  @param  usWidth             [out]        视频宽度
 *  @param  usHeight            [out]        视频高度
 *  @param  lDataInfo           [out]        数据信息 备用
 *  @param  lpBuffer            [out]        数据地址
 *  @param  lBufferSize         [out]        数据长度
 *  @param  lpUser              [out]        用户数据
 *  @return 
 *  @see LPYUVDATACALLBACK
 */

typedef void (CALLBACK* LPYUVDATACALLBACK)(LONG lPlayHandle, USHORT usWidth, USHORT usHeight, LONG lDataInfo, BYTE* lpBuffer, LONG lBufferSize, LPVOID lpUser);

/**
 *  PCM数据回调
 *  @param  lPlayHandle         [out]        播放句柄
 *  @param  nSampleRate         [out]        采样率
 *  @param  nChannel            [out]        通道数
 *  @param  nBitsPerSample      [out]        每个采样点的比特数
 *  @param  lDataInfo           [out]        数据信息 备用
 *  @param  lpBuffer            [out]        数据地址
 *  @param  lBufferSize         [out]        数据长度
 *  @param  lpUser              [out]        用户数据
 *  @return 
 *  @see LPYUVDATACALLBACK
 */

typedef void (CALLBACK* LPPCMDATACALLBACK)(LONG lPlayHandle, int nSampleRate, int nChannel, int nBitsPerSample, LONG lDataInfo, BYTE* lpBuffer, LONG lBufferSize, LPVOID lpUser);

/**
 *  本地音频数据回调
 *  lDataType:  0:视频  1:音频
 *  @param  lDataInfo         [out]        数据头长度
 *  @param  lpBuffer          [out]        数据地址
 *  @param  lBufferSize       [out]        数据长度
 *  @param  lpUser            [out]        用户数据
 *  @return 
 *  @see LPPLAYDATACALLBACK
 */

typedef void (CALLBACK* LPLOCALAUDIOINDATACALLBACK)(LONG lDataInfo, BYTE* lpBuffer, LONG lBufferSize, LPVOID lpUser);

/**
 *  透明串口数据回调
 *  lDataType:  0:视频  1:音频
 *  @param  lLogInHandle      [out]        登录句柄
 *  @param  lComID            [out]        串口ID
 *  @param  lpBuffer          [out]        数据地址
 *  @param  lBufferSize       [out]        数据长度
 *  @param  lpUser            [out]        用户数据
 *  @return 
 *  @see LPPLAYDATACALLBACK
 */

typedef void (CALLBACK* LPCOMDATACALLBACK)(LONG lLogInHandle, LONG lComID, BYTE* lpBuffer, LONG lBufferSize, LPVOID lpUser);

/**
 *  报警数据回调
 *  lDataType:  0:视频  1:音频
 *  @param  lLogInHandle      [out]        登录句柄
 *  @param  lChannelID        [out]        报警通道ID
 *  @param  eAlarmType        [out]        报警类型
 *  @param  alarmInfo         [out]        报警数据
 *  @param  lpUser            [out]        用户数据
 *  @return 
 *  @see LPPLAYDATACALLBACK
 */

typedef void (CALLBACK* LPALARMDATACALLBACK)(LONG lLogInHandle, LONG lChannelID, NVD_ALARM_TYPE eAlarmType, NVD_ALARM_REPORT_INFO alarmInfo, LPVOID lpUser);

/**
 *  球机当前角度信息回调 
 *  @param  lLogInHandle      [out]        登录句柄
 *  @param  PTZReportInfo     [out]        球机上报信息
 *  @param  lpUser            [out]        用户数据
 *  @return 
 *  @see LPPLAYDATACALLBACK
 */

typedef void (CALLBACK* LPPTZREPORTCALLBACK)(LONG lLogInHandle, NVD_PTZ_REPORT_INFO PTZReportInfo, LPVOID lpUser);

/**
 *  透明信息回调 
 *  @param  lLogInHandle      [out]        登录句柄
 *  @param  IVALPRResult      [out]        车牌信息
 *  @param  lpUser            [out]        用户数据
 *  @return 
 *  @see LPOPENINFOCALLBACK
 */

typedef void (CALLBACK* LPOPENINFOCALLBACK)(LONG lLogInHandle, BYTE* lpBuffer, LONG lBufferSize, LPVOID lpUser);

/**
 *  抓拍图片回调
 *  @param  lLogInHandle      [out]        登录句柄
 *  @param  lpPicInfo         [out]        图片信息
 *  @param  lpBuffer          [out]        图片数据地址
 *  @param  lBufferSize       [out]        图片数据大小
 *  @param  lpUser            [out]        用户数据
 *  @return 
 *  @see LPPLATEINFOCALLBACK
 */

typedef int  (CALLBACK *LPPICTUREINFOCALLBACK)(LONG lLogInHandle, LPVOID lpPicInfo, BYTE* lpBuffer, LONG lBufferSize, LPVOID lpUser);

/**
 *  模块初始化
 *  操作前请务必调用
 *  @param
 *  @return 0:成功   其他:失败
 *  @see NVD_Init
 */

NVDSDK_API LONG __stdcall NVD_Init();
 
/**
 *  模块反初始化
 *  调用此接口会关闭所有应用,并登出设备
 *  @param
 *  @return 
 *  @see NVD_Fini
 */
 
NVDSDK_API void __stdcall NVD_Fini();

/**
 *  登陆设备
 *  所有涉及登录句柄的操作前调用  如果已经登录则返回以前的登录句柄
 *  @param  sDeviceIP         [in]        设备IP
 *  @param  wDevicePort       [in]        设备端口
 *  @param  sUserName         [in]        用户名
 *  @param  sPassword         [in]        密码
 *  @param  eNetModel         [in]        网络类型
 *  @param  dwNetTimeOut      [in]        网络超时时间(ms)
 *  @param  lpLogInInfo       [out]       返回设备信息
 *  @return 登录句柄  >=0:成功   其他:失败
 *  @see NVD_LogIn
 */

NVDSDK_API LONG __stdcall NVD_LogIn(char* sDeviceIP, WORD wDevicePort, char* sUserName, char* sPassword, NVD_NETMODEL eNetModel, NVD_LOGIN_INFO* lpLogInInfo);
NVDSDK_API LONG __stdcall NVD_LogIn2(char* sDeviceIP, WORD wDevicePort, char* sUserName, char* sPassword, NVD_NETMODEL eNetModel, DWORD dwNetTimeOut, NVD_LOGIN_INFO* lpLogInInfo);

/**
 *  设置设备状态回调
 *  @param  lLogInHandle      [in]        播放句柄
 *  @param  lpCall            [in]        视频宽度
 *  @param  lpUser            [in]        视频高度
 *  @return 0:成功   其他:失败
 *  @see NVD_SetDeviceStaCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetDeviceStaCallBack(LONG lLogInHandle, LPDEVICESTACALLBACK lpCall, LPVOID lpUser);

/**
 *  登出设备
 *  调用此接口会停止该设备上所有应用,并登出设备
 *  @param  lLogInHandle       [in]        登陆句柄
 *  @return 
 *  @see NVD_SetDeviceStaCallBack
 */

NVDSDK_API void __stdcall NVD_LogOut(LONG lLogInHandle);

/**
 *  获取设备配置
 *  获取全部配置时通道号请填0xFF,如果不涉及则填写0xEE
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  eOPCfgType           [in]        获取类型
 *  @param  lChannelID           [in]        通道号
 *  @param  lpBuffer             [in]        返回数据存储区
 *  @param  lBufferSize          [in]        缓存区大小
 *  @param  lReturnSize          [in]        返回数据大小
 *  @return 0:成功   其他:失败
 *  @see NVD_GetDeviceCfg
 */


NVDSDK_API LONG __stdcall NVD_GetDeviceCfg(LONG lLogInHandle, NVD_OPCFGTYPE eOPCfgType, LONG lChannelID, LPVOID lpBuffer, LONG lBufferSize, LONG* lpReturnSize);

/**
 *  设置设备配置
 *  将配置复制到所有通道通道号请填0xFF,如果不涉及则填写0xEE
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  eOPCfgType           [in]        获取类型
 *  @param  lChannelID           [in]        通道号
 *  @param  lpBuffer             [in]        数据存储区
 *  @param  lBufferSize          [in]        缓存区大小
 *  @return 0:成功   其他:失败
 *  @see NVD_SetDeviceCfg
 */

NVDSDK_API LONG __stdcall NVD_SetDeviceCfg(LONG lLogInHandle, NVD_OPCFGTYPE eOPCfgType, LONG lChannelID, LPVOID lpBuffer, LONG lBufferSize);

/**
 *  播放实时视频
 *  播放句柄将用于后续播放控制
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  lChannelID           [in]        获取类型
 *  @param  eStreamType          [in]        通道号
 *  @param  eNetModel            [in]        网络模式
 *  @param  hPlayWnd             [in]        播放窗口句柄
 *  @return 播放句柄  >=0:成功   其他:失败
 *  @see NVD_RealPlay
 */


NVDSDK_API LONG __stdcall NVD_RealPlay(LONG lLogInHandle, LONG lChannelID, NVD_ENC_STREAM_TYPE eStreamType, NVD_NETMODEL eNetModel, HWND hPlayWnd);

/**
 *  播放本地录像
 *  播放句柄将用于后续播放控制
 *  @param  sFilePath           [in]        录像路径
 *  @param  hPlayWnd            [in]        播放窗口
 *  @return 播放句柄  >=0:成功   其他:失败
 *  @see NVD_RealPlay
 */

NVDSDK_API LONG __stdcall NVD_PlayBackLocal(char* sFilePath, HWND hPlayWnd);

/**
 *  打开录像回放句柄
 *  该句柄用于后续录像文件查找、回放、回放控制、关闭等操作
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  eNetModel            [in]        网络模式
 *  @return 播放句柄  >=0:成功   其他:失败
 *  @see NVD_RealPlay,NVD_PlayBackLocal
 */
NVDSDK_API LONG __stdcall NVD_OpenPlayback(LONG lLogInHandle, NVD_NETMODEL eNetModel);

/**
 *  关闭录像回放句柄
 *  释放资源
 *  @param  lPlaybackHandle      [in]        录像回放句柄
 *  @return   0:成功   其他:失败
 *  @see NVD_Close
 */
NVDSDK_API LONG __stdcall NVD_ClosePlayback(LONG lPlaybackHandle);

/**
 *  打开一个查找上下文
 *  打开查找上下文后，方可进行查找操作
 *  @param  lPlaybackHandle      [in]        录像回放句柄
 *  @param  lChannel             [in]        录像通道号
 *  @param  dwType               [in]        录像类型，目前赋值为0xffffffff
 *  @param  startTime            [in]        录像开始时间
 *  @param  stopTime             [in]        录像停止时间
 *  @param  dwTimeout            [in]        查找超时时间，单位：ms. @brief 由于IPC端循环录像可能删除文件，该查找时间估计应尽量的贴切，不要过长；经过该超时时间后，IPC端可能会单方清除查找上下文
 *  @return 0:成功   其他:失败
 *  @see ...
 */
NVDSDK_API LONG __stdcall NVD_PlaybackFindFile(LONG lPlaybackHandle,LONG lChannel,DWORD dwType,NET_TIME* startTime,NET_TIME* stopTime,DWORD dwTimeout);

/**
 *  查找下一个文件
 *  打开查找上下文后，方可进行本操作
 *  @param  lPlaybackHandle      [in]        录像回放句柄
 *  @param  fileinfo             [out]       查找成功时，输出录像文件信息
 *  @return 0:成功   其他:失败(此时应停止查找)
 *  @see ...
 */
NVDSDK_API LONG __stdcall NVD_PlaybackFindNextFile(LONG lPlaybackHandle,LPNET_RECORDFILE_INFO fileinfo);

/**
 *  关闭查找上下文
 *  文件查找完毕后，即可停止查找，不会影响后续文件/时间段播放
 *  @param  lPlaybackHandle      [in]        录像回放句柄
 *  @return 0:成功   其他:失败
 *  @see ...
 */
NVDSDK_API LONG __stdcall NVD_PlaybackCloseFindFile(LONG lPlaybackHandle);

/**
 *  按文件名回放
 *  
 *  @param  lPlaybackHandle      [in]        录像回放句柄
 *  @param  sFilePath            [in]        录像文件名
 *  @param  hPlayWnd			 [in]		 播放窗口句柄
 *  @param  dwTimeout            [in]        播放超时时间，单位：ms.（从开始播放到停止播放之间的估计时间）
 *  @return 0:成功   其他:失败
 *  @see ...
 */
NVDSDK_API LONG __stdcall NVD_PlaybackByName(LONG lPlaybackHandle, const char* sFilePath, HWND hPlayWnd, DWORD dwTimeout);

/**
 *  按时间段回放
 *  
 *  @param  lPlaybackHandle      [in]        录像回放句柄
 *  @param  lChannel             [in]        录像通道号
 *  @param  dwType               [in]        录像类型，目前赋值为0xffffffff
 *  @param  startTime            [in]        录像开始时间
 *  @param  stopTime             [in]        录像停止时间
 *  @param  hPlayWnd			 [in]		 播放窗口句柄
 *  @param  dwTimeout            [in]        播放超时时间，单位：ms.（从开始播放到停止播放之间的估计时间）
 *  @return 0:成功   其他:失败
 *  @see ...
 */
NVDSDK_API LONG __stdcall NVD_PlaybackByTime(LONG lPlaybackHandle, LONG lChannel,DWORD dwType, NET_TIME* startTime, NET_TIME* stopTime, HWND hPlayWnd, DWORD dwTimeout);

/**
 *  停止播放
 *  本操作仅仅只是停止播放而已
 *  @param  lPlaybackHandle      [in]        录像回放句柄
 *  @return 0:成功   其他:失败
 *  @see NVD_Close
 */
NVDSDK_API LONG __stdcall NVD_PlaybackStopPlay(LONG lPlaybackHandle);

/**
 *  打开灌流播放
 *  此处的播放类型是指  实时视频灌流播放 或者 录像灌流播放
 *  @param  eType               [in]        播放类型
 *  @param  hPlayWnd            [in]        播放窗口
 *  @return lPlayHandle  >=0:成功   其他:失败
 *  @see NVD_OpenInputPlay
 */

NVDSDK_API LONG __stdcall NVD_OpenInputPlay(NVD_PLAYTYPE ePlayType, HWND hPlayWnd);

/**
 *  输入码流
 *  @param  lPlayHandle        [in]        播放句柄
 *  @param  eDataType          [in]        数据类型
 *  @param  lDataInfo          [in]        数据头长度
 *  @param  lpBuffer           [in]        数据地址
 *  @param  lpBufferSize       [in]        数据长度
 *  @return 成功输入长度
 *  @see NVD_InputData
 */

NVDSDK_API LONG __stdcall NVD_InputData(LONG lPlayHandle, NVD_DATATYPE eDataType, LONG lDataInfo, BYTE* lpBuffer, LONG lBufferSize);

/**
 *  停止播放
 *  调用此接口后需重新登录设备
 *  @param  lPlayHandle        [in]        播放句柄
 *  @return 
 *  @see NVD_Close
 */

NVDSDK_API void __stdcall NVD_Close(LONG lPlayHandle);

/**
 *  设置显示类型
 *  调用此接口后需重新登录设备
 *  @param  lPlayHandle        [in]        播放句柄
 *  @param  eShowModel         [in]        显示类型
 *  @return  0:成功   其他:失败
 *  @see NVD_SetShowMdoel
 */

NVDSDK_API LONG __stdcall NVD_SetShowMdoel(LONG lPlayHandle, NVD_SHOWMODEL eShowModel);

/**
 *  开始本地录像
 *  路径未创建,SDK会自动创建
 *  @param  lPlayHandle        [in]        播放句柄
 *  @param  sFileName          [in]        文件完整路径,不含后缀名  
 *  @return  0:成功   其他:失败
 *  @see NVD_StartRecord
 */

NVDSDK_API LONG __stdcall NVD_StartRecord(LONG lPlayHandle, char* sFileName);

/**
 *  停止本地录像
 *  @param  lPlayHandle        [in]        播放句柄
 *  @return  
 *  @see NVD_StopRecord
 */

NVDSDK_API void __stdcall NVD_StopRecord(LONG lPlayHandle);

/**
 *  本地抓图
 *  可以录制jpg和bmp图,SDK根据后缀名自动判断 
 *  @param  lPlayHandle        [in]        播放句柄
 *  @param  sFileName          [in]        文件完整路径,含后缀名  
 *  @return  0:成功   其他:失败
 *  @see NVD_CapPicture
 */

NVDSDK_API LONG __stdcall NVD_CapPicture(LONG lPlayHandle, char* sFileName);

/**
 *  播放控制
 *  @param  lPlayHandle              [in]        播放句柄
 *  @param  ePlayCtrl                [in]        控制命令字
 *  @param  lpCtrlData               [in]        控制数据存储区
 *  @param  lCtrlDataSize            [in]        控制数据长度
 *  @param  lpReturnData             [in]        控制返回数据存储区
 *  @param  lReturnDataSize          [in]        控制返回数据缓冲区大小
 *  @param  lpReturnSize             [out]       返回数据大小
 *  @return  0:成功   其他:失败
 *  @see NVD_PlayCtrl
 */

NVDSDK_API LONG __stdcall NVD_PlayCtrl(LONG lPlayHandle, NVD_PLAYCTRL ePlayCtrl, LPVOID lpCtrlData, LONG lCtrlDataSize, LPVOID lpReturnData, LONG lReturnDataSize, LONG* lpReturnSize);

/**
 *  设置播放信息回调
 *  @param  lPlayHandle           [in]        播放句柄
 *  @param  lpCall                [in]        播放信息回调
 *  @param  lpUser                [in]        播放信息回调用户数据
 *  @return  0:成功   其他:失败
 *  @see NVD_SetPlayInfoCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetPlayInfoCallBack(LONG lPlayHandle, LPPLAYINFOCALLBACK lpCall, LPVOID lpUser);

/**
 *  设置显示回调
 *  @param  lPlayHandle           [in]        播放句柄
 *  @param  lpCall                [in]        显示回调
 *  @param  lpUser                [in]        显示回调用户数据
 *  @return  0:成功   其他:失败
 *  @see NVD_SetDrawFunCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetDrawFunCallBack(LONG lPlayHandle, LPDRAWFUNCALLBACK lpCall, LPVOID lpUser);

/**
 *  设置显示回调
 *  @param  lPlayHandle           [in]        播放句柄
 *  @param  eDataType             [in]        回调数据类型
 *  @param  lpCall                [in]        数据回调
 *  @param  lpUser                [in]        显示回调用户数据
 *  @return  0:成功   其他:失败
 *  @see NVD_SetPlayDataCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetPlayDataCallBack(LONG lPlayHandle, LPPLAYDATACALLBACK lpCall, LPVOID lpUser);

/**
 *  设置视频播放数据回调
 *  @param  lPlayHandle           [in]        播放句柄
 *  @param  lpCall                [in]        数据回调
 *  @param  lpUser                [in]        数据回调用户数据
 *  @return  0:成功   其他:失败
 *  @see NVD_SetYUVDataCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetYUVDataCallBack(LONG lPlayHandle, LPYUVDATACALLBACK lpCall, LPVOID lpUser);

/**
 *  设置音频播放数据回调
 *  @param  lPlayHandle           [in]        播放句柄
 *  @param  lpCall                [in]        数据回调
 *  @param  lpUser                [in]        数据回调用户数据
 *  @return  0:成功   其他:失败
 *  @see NVD_SetPCMDataCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetPCMDataCallBack(LONG lPlayHandle, LPPCMDATACALLBACK lpCall, LPVOID lpUser);

/**
 *  打开PC声音采集
 *  @param  lLogInHandle         [in]        登录句柄
 *  @return  0:成功   其他:失败
 *  @see NVD_OpenMIC
 */

NVDSDK_API LONG __stdcall NVD_OpenLocalAudioIn(NVD_AUDIO_TYPE eAudioType);

/**
 *  关闭PC声音采集
 *  @param  lLogInHandle         [in]        登录句柄
 *  @return  0:成功   其他:失败
 *  @see NVD_CloseMIC
 */

NVDSDK_API LONG __stdcall NVD_CloseLocalAudioIn();

/**
 *  打开设备声音输出
 *  @param  lLogInHandle         [in]        登录句柄
 *  @return  0:成功   其他:失败
 *  @see NVD_OpenMIC
 */

NVDSDK_API LONG __stdcall NVD_OpenDeviceAudioOut(LONG lLogInHandle);

/**
 *  关闭设备声音输出
 *  @param  lLogInHandle         [in]        登录句柄
 *  @return  0:成功   其他:失败
 *  @see NVD_CloseMIC
 */

NVDSDK_API LONG __stdcall NVD_CloseDeviceAudioOut(LONG lLogInHandle);

/**
 *  设置MIC数据回调
 *  @param  lLogInHandle          [in]        登录句柄
 *  @param  lpCall                [in]        数据回调
 *  @param  lpUser                [in]        数据回调用户数据
 *  @return  0:成功   其他:失败
 *  @see NVD_SetLocalAudioInDataCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetLocalAudioInDataCallBack(LPLOCALAUDIOINDATACALLBACK lpCall, LPVOID lpUser);

/**
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  lpBuffer             [in]        数据地址
 *  @param  lBufferSize          [in]        数据长度
 *  @return  0:成功   其他:失败
 *  @see NVD_SetMICVOL
 */

NVDSDK_API LONG __stdcall NVD_SendAudioDataToDevice(LONG lLogInHandle, BYTE* lpBuffer, LONG lBufferSize);

/**
 *  设置串口数据回调
 *  @param  lLogInHandle          [in]        登录句柄
 *  @param  lpCall                [in]        数据回调
 *  @param  lpUser                [in]        数据回调用户数据
 *  @return  0:成功   其他:失败
 *  @see NVD_SetCOMDataCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetComDataCallBack(LONG lLogInHandle, LPCOMDATACALLBACK lpCall, LPVOID lpUser);

/**
 *  向透明串口发送数据
 *  @param  lLogInHandle          [in]        登录句柄
 *  @param  lComID                [in]        串口序号
 *  @param  lpBuffer              [in]        数据地址
 *  @param  lBufferSize           [in]        数据长度
 *  @return  0:成功   其他:失败
 *  @see NVD_SetCOMDataCallBack
 */

NVDSDK_API LONG __stdcall NVD_SendComData(LONG lLogInHandle, LONG lComID, BYTE* lpBuffer, LONG lBufferSize);

/**
 *  设置报警数据回调
 *  @param  lLogInHandle          [in]        登录句柄
 *  @param  lpCall                [in]        数据回调
 *  @param  lpUser                [in]        数据回调用户数据
 *  @return  0:成功   其他:失败
 *  @see NVD_SetAlarmDataCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetAlarmDataCallBack(LONG lLogInHandle, LPALARMDATACALLBACK lpCall, LPVOID lpUser);

/**
 *  设置PTZ控制数据回调
 *  @param  lLogInHandle          [in]        登录句柄
 *  @param  lpCall                [in]        数据回调
 *  @param  lpUser                [in]        数据回调用户数据
 *  @return  0:成功   其他:失败
 *  @see NVD_SetPTZReportCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetPTZReportCallBack(LONG lLogInHandle, LPPTZREPORTCALLBACK lpCall, LPVOID lpUser);

/**
 *  基于播放球机控制
 *  @param  lPlayHandle           [in]        播放句柄
 *  @param  eCtrlType             [in]        控制类型
 *  @param  lData                 [in]        控制数据
 *  @return  0:成功   其他:失败
 *  @see NVD_PTZCtrl
 */

NVDSDK_API LONG __stdcall NVD_PTZCtrl(LONG lPlayHandle, NVD_PTZ_CTRL_CMD eCtrlType, LONG lData);

/**
 *  球机3D定位
 *  @param  lPlayHandle           [in]        播放句柄
 *  @param  Ptz3dLocatePara       [in]        框选结构
 *  @return  0:成功   其他:失败
 *  @see NVD_PTZ_3D_LOCATE
 */
NVDSDK_API LONG __stdcall NVD_PTZ_3D_LOCATE(LONG lPlayHandle, NVD_PTZ_3D_LOCATE_DATA Ptz3dLocateData);

/**
 *  基于播放球机预置位查询
 *  此函数用于控制球机自动寻像,只针对拥有此功能的球机
 *  @param  lPlayHandle           [in]        实时视频播放句柄
 *  @param  lpPresetPara          [in]        预置位返回结构
 *  @return  0:成功   其他:失败
 *  @see NVD_PTZQueryPreset
 */

NVDSDK_API LONG __stdcall NVD_PTZQueryPreset(LONG lPlayHandle, NVD_PTZ_PRESET_PARA* lpPresetPara);

/**
 *  基于播放球机预置位控制
 *  @param  lPlayHandle            [in]        实时视频播放句柄
 *  @param  lpCtrlPresetPara       [in]        预置位结构
 *  @return  0:成功   其他:失败
 *  @see NVD_PTZCtrlPreset
 */

NVDSDK_API LONG __stdcall NVD_PTZCtrlPreset(LONG lPlayHandle, NVD_PTZ_CTRL_PRESET_PARA* lpCtrlPresetPara);

/**
 *  基于播放球机巡航查询
 *  此函数用于控制球机自动寻像,只针对拥有此功能的球机
 *  @param  lPlayHandle            [in]        实时视频播放句柄
 *  @param  lpCruisePara           [in]        巡航返回结构
 *  @return  0:成功   其他:失败
 *  @see NVD_PTZQueryCruise
 */

NVDSDK_API LONG __stdcall NVD_PTZQueryCruise(LONG lPlayHandle, NVD_PTZ_CRUISE_PARA* lpCruisePara);

/**
 *  基于播放球机巡航控制
 *  此函数用于控制球机自动寻像,只针对拥有此功能的球机
 *  @param  lPlayHandle                 [in]        实时视频播放句柄
 *  @param  lpCtrlCruisePara            [in]        预置位结构
 *  @return  0:成功   其他:失败
 *  @see NVD_PTZCtrlCruise
 */

NVDSDK_API LONG __stdcall NVD_PTZCtrlCruise(LONG lPlayHandle, NVD_PTZ_CTRL_CRUISE_PARA* lpCtrlCruisePara);

/**
 *  基于播放球机巡航配置获取
 *  此函数用于控制球机自动寻像,只针对拥有此功能的球机
 *  @param  lPlayHandle                 [in]        实时视频播放句柄
 *  @param  lCruiseID                   [in]        巡航ID
 *  @param  lpCruisePointPara           [out]       巡航配置结构
 *  @return  0:成功   其他:失败
 *  @see NVD_PTZGetCruisePoint
 */

NVDSDK_API LONG __stdcall NVD_PTZGetCruisePoint(LONG lPlayHandle, LONG lCruiseID, NVD_PTZ_CRUISE_POINT_PARA* lpCruisePointPara);

/**
 *  基于播放球机巡航配置设置
 *  此函数用于控制球机自动寻像,只针对拥有此功能的球机
 *  @param  lPlayHandle                 [in]        实时视频播放句柄
 *  @param  lpCruisePointPara           [in]        巡航配置结构
 *  @return  0:成功   其他:失败
 *  @see NVD_PTZSetCruisePoint
 */

NVDSDK_API LONG __stdcall NVD_PTZSetCruisePoint(LONG lPlayHandle, NVD_PTZ_CRUISE_POINT_PARA* lpCruisePointPara);

/**
 *  直接球机控制
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  lChannelID           [in]        通道号
 *  @param  eCtrlType            [in]        控制类型
 *  @param  lData                [in]        控制数据(速度) 
 *  @return  0:成功   其他:失败
 *  @see NVD_PTZCtrl_EX
 */

NVDSDK_API LONG __stdcall NVD_PTZCtrl_EX(LONG lLogInHandle, LONG lChannelID, NVD_PTZ_CTRL_CMD eCtrlType, LONG lData);

/**
 *  球机3D定位
 *  @param  lPlayHandle           [in]        播放句柄
 *  @param  Ptz3dLocatePara       [in]        框选结构
 *  @return  0:成功   其他:失败
 *  @see NVD_PTZ_3D_LOCATE
 */
NVDSDK_API LONG __stdcall NVD_PTZ_3D_LOCATE_EX(LONG lLogInHandle, LONG lChannelID, NVD_PTZ_3D_LOCATE_DATA Ptz3dLocateData);

/**
 *  直接球机预置位查询
 *  此函数用于控制球机自动寻像,只针对拥有此功能的球机
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  lChannelID           [in]        通道号
 *  @param  lpPresetPara         [in]        预置位返回结构
 *  @return  0:成功   其他:失败
 *  @see NVD_PTZQueryPreset_EX
 */

NVDSDK_API LONG __stdcall NVD_PTZQueryPreset_EX(LONG lLogInHandle, LONG lChannelID, NVD_PTZ_PRESET_PARA* lpPresetPara);

/**
 *  直接球机预置位控制
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  lChannelID           [in]        视频点位ID
 *  @param  lpCtrlPresetPara     [in]        预置位结构
 *  @return  0:成功   其他:失败
 *  @see NVD_PTZCtrlPreset_EX
 */

NVDSDK_API LONG __stdcall NVD_PTZCtrlPreset_EX(LONG lLogInHandle, LONG lChannelID, NVD_PTZ_CTRL_PRESET_PARA* lpCtrlPresetPara);

/**
 *  直接球机巡航查询
 *  此函数用于控制球机自动寻像,只针对拥有此功能的球机
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  lChannelID           [in]        视频点位ID
 *  @param  lpCruisePara         [in]        巡航返回结构
 *  @return  0:成功   其他:失败
 *  @see NVD_PTZQueryCruise_EX
 */

NVDSDK_API LONG __stdcall NVD_PTZQueryCruise_EX(LONG lLogInHandle, LONG lChannelID, NVD_PTZ_CRUISE_PARA* lpCruisePara);

/**
 *  直接球机巡航控制
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  lChannelID           [in]        视频点位ID
 *  @param  lpCtrlCruisePara     [in]        预置位结构
 *  @return  0:成功   其他:失败
 *  @see NVD_PTZCtrlCruise_EX
 */

NVDSDK_API LONG __stdcall NVD_PTZCtrlCruise_EX(LONG lLogInHandle, LONG lChannelID, NVD_PTZ_CTRL_CRUISE_PARA* lpCtrlCruisePara);

/**
 *  直接球机巡航控制
 *  此函数用于控制球机自动寻像,只针对拥有此功能的球机
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  lChannelID           [in]        视频点位ID
 *  @param  lCruiseID            [in]        巡航ID
 *  @param  lpCruisePointPara    [in]        巡航配置结构
 *  @return  0:成功   其他:失败
 *  @see NVD_PTZGetCruisePoint_EX
 */

NVDSDK_API LONG __stdcall NVD_PTZGetCruisePoint_EX(LONG lLogInHandle, LONG lChannelID, LONG lCruiseID, NVD_PTZ_CRUISE_POINT_PARA* lpCruisePointPara);

/**
 *  直接球机巡航配置设置
 *  此函数用于控制球机自动寻像,只针对拥有此功能的球机
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  lChannelID           [in]        视频点位ID
 *  @param  lpCruisePointPara    [in]        巡航配置结构
 *  @return  0:成功   其他:失败
 *  @see NVD_PTZSetCruisePoint_EX
 */

NVDSDK_API LONG __stdcall NVD_PTZSetCruisePoint_EX(LONG lLogInHandle, LONG lChannelID, NVD_PTZ_CRUISE_POINT_PARA* lpCruisePointPara);

/**
 *  串口数据传输
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  lComIndex            [in]        串口编号
 *  @param  lpBuffer             [in]        发送的数据
 *  @param  lBufferSize          [in]        发送的数据长度   
 *  @return  0:成功   其他:失败
 *  @see NVD_TransportCom
 */

NVDSDK_API LONG __stdcall NVD_TransportCom(LONG lLogInHandle, LONG lComIndex, BYTE* lpBuffer, LONG lBufferSize);

/**
 *  刷新显示
 *  此接口可以在图像暂停且播放窗口被刷新时使用
 *  @param  lPlayHandle         [in]        播放句柄
 *  @return  0:成功   其他:失败
 *  @see NVD_RefreshShow
 */

NVDSDK_API LONG __stdcall NVD_RefreshShow(LONG lPlayHandle);

/**
 *  触发报警
 *  调用此接口后触发相应报警通道的报警
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  lAlarmChannelID      [in]        报警通道
 *  @return  0:成功   其他:失败
 *  @see NVD_CheckTime
 */

NVDSDK_API LONG __stdcall NVD_StartAlarm(LONG lLogInHandle, LONG lAlarmChannelID);

/**
 *  停止报警
 *  调用此接口后停止相应报警通道的报警
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  lAlarmChannelID      [in]        报警通道
 *  @return  0:成功   其他:失败
 *  @see NVD_CheckTime
 */

NVDSDK_API LONG __stdcall NVD_StopAlarm(LONG lLogInHandle, LONG lAlarmChannelID);

/**
 *  强制设备发送I帧
 *  此接口切不可频繁调用,增加系统数据量
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  lChannelID           [in]        通道号
 *  @return  0:成功   其他:失败
 *  @see NVD_MakeIFrame
 */

NVDSDK_API LONG __stdcall NVD_MakeIFrame(LONG lLogInHandle, LONG lChannelID);

/**
 *  保存设置的数据
 *  调用此接口后保存设置数据
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  Time                 [in]        设置的时间
 *  @return  0:成功   其他:失败
 *  @see NVD_CheckTime
 */

NVDSDK_API LONG __stdcall NVD_CheckTime(LONG lLogInHandle, NVD_TIME Time);

/**
 *  保存设置的数据
 *  调用此接口后保存设置数据
 *  @param  lLogInHandle         [in]        登录句柄
 *  @return  0:成功   其他:失败
 *  @see NVD_SaveDeviceCfg
 */

NVDSDK_API LONG __stdcall NVD_SaveDeviceCfg(LONG lLogInHandle);

/**
 *  重启设备
 *  调用此接口后需重新登录设备
 *  @param  lLogInHandle         [in]        登录句柄
 *  @return  0:成功   其他:失败
 *  @see NVD_Reset
 */

NVDSDK_API LONG __stdcall NVD_Reset(LONG lLogInHandle);

/**
 *  设备恢复配置
 *  调用此接口后需重新登录设备
 *  @param  lLogInHandle         [in]        登录句柄
 *  @return  0:成功   其他:失败
 *  @see NVD_RestoreCfg
 */

NVDSDK_API LONG __stdcall NVD_RestoreCfg(LONG lLogInHandle);

/**
 *  设备恢复IP
 *  调用此接口后需重新登录设备
 *  @param  lLogInHandle         [in]        登录句柄
 *  @return  0:成功   其他:失败
 *  @see NVD_RestoreIP
 */

NVDSDK_API LONG __stdcall NVD_RestoreIP(LONG lLogInHandle);

/**
 *  模拟键盘控制接口
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  lChannelID           [in]        通道号
 *  @param  CtrlData             [in]        键盘控制结构
 *  @return  0:成功   其他:失败
 *  @see NVD_KeyBoardCtrl
 */

NVDSDK_API LONG __stdcall NVD_KeyBoardCtrl(LONG lLogInHandle, LONG lChannelID, NVD_KEYBOARD_CTRL_DATA CtrlData);

/**
 *  设置透明信息回调
 *  @param  lLogInHandle          [in]        登录句柄
 *  @param  lpCall                [in]        数据回调
 *  @param  lpUser                [in]        数据回调用户数据
 *  @return  0:成功   其他:失败
 *  @see NVD_SetPlateInfoCallBack
 */

NVDSDK_API LONG __stdcall NVD_SetOpenInfoCallBack(LONG lLogInHandle, LPOPENINFOCALLBACK lpCall, LPVOID lpUser);

/**
 *  设置显示矩形
 *  @param  lPlayHandle           [in]        播放句柄
 *  @param  rect                  [in]        显示矩形
 *  @return  0:成功   其他:失败
 *  @see NVD_SetShowRect
 */

NVDSDK_API LONG __stdcall NVD_SetShowRect(LONG lPlayHandle, NVD_RECT rect);

/**
 *  设置卡口图片回调
 *  @param  lLogInHandl           [in]        登录句柄
 *  @param  lChannelID            [in]        抓拍通道ID
 *  @param  lpCall                [in]        回调函数
 *  @param  lpUser                [in]        用户数据
 *  @return  0:成功   其他:失败
 *  @see NVD_SetShowRect
 */
NVDSDK_API LONG __stdcall NVD_SetPictureCallBack(LONG lLogInHandle, LONG lChannelID, LPPICTUREINFOCALLBACK lpCall, LPVOID lpUser);

/**
 *  实时抓拍(不基于播放)
 *  @param  lLogInHandl           [in]        登录句柄
 *  @param  lChannelID            [in]        抓拍通道ID
 *  @return  0:成功   其他:失败
 *  @see NVD_SetShowRect
 */
NVDSDK_API LONG __stdcall NVD_CapPictureEX(LONG lLogInHandle, LONG lChannelID);

/**
 *  获取目录
 *  @param  lLogInHandl           [in]        登录句柄
 *  @param  strParentDir          [in]        父目录
 *  @param  strDir                [out]       获取到的目录存放数据地址
 *  @param  lDirSize              [out]       获取目录大小
 *  @return  0:成功   其他:失败
 *  @see NVD_SetShowRect
 */
NVDSDK_API LONG __stdcall NVD_GetDirectory(LONG lLogInHandle, char* strParentDir, char* strDir, LONG lDirSize);

/**
 *  传输透明数据
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  lpInBuffer           [in]        输入缓存
 *  @param  lInBufferSize        [in]        输入缓存大小
 *  @param  lpOutBuffer          [in]        输出缓存
 *  @param  lOutBufferSize       [in]        输出缓存大小
 *  @param  lpOutBufferSize      [in]        实际输出缓存大小
 *  @return 0:成功   其他:失败
 *  @see NVD_TransOpenCfg
 */

NVDSDK_API LONG __stdcall NVD_TransOpenCfg(LONG lLogInHandle, LPVOID lpInBuffer, LONG lInBufferSize, LPVOID lpOutBuffer, LONG lOutBufferSize, LONG* lpReturnBufferSize);

/**
 *  远端抓拍
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  bSaveInCard          [in]        是否存入存储卡
 *  @param  lpOutHead            [in]        抓拍输出信息头
 *  @return 0:成功   其他:失败
 *  @see NVD_SNAPPicture
 */

NVDSDK_API LONG __stdcall NVD_SNAPPicture(LONG lLogInHandle, LONG lChannelID, BOOL bSaveInCard, NVD_JPEG_HEAD* lpOutHead);


/**
 *  获取远端抓拍数据
 *  @param  lLogInHandle         [in]        登录句柄
 *  @param  Head                 [in]        抓拍头(通过NVD_SNAPPicture中的返回参数lpOutHead中的变量得到)
 *  @param  lBufferSize          [in]        获取图片的大小(通过NVD_SNAPPicture中的返回参数lpOutHead中的变量得到)
 *  @param  lpBuffer             [out]       获取到的图片存在此缓存中
 *  @param  lpReturnSize         [out]       获取到的图片大小
 *  @return 0:成功   其他:失败
 *  @see NVD_GetSNAPPicture
 */

NVDSDK_API LONG __stdcall NVD_GetSNAPPicture(LONG lLogInHandle, NVD_JPEG_HEAD Head, BYTE* lpBuffer, LONG lBufferSize, LONG* lpReturnSize);

/**
 * 查询前端抓拍图片
 * @param  lLogInHandle         [in]        登录句柄
 * @param  lChannelID           [in]        抓拍通道ID
 * @param  lpFindParam          [in]        查询图片参数
 * @param  lppFindHandle        [out]       查询图片句柄
 * @return 0:成功  其它:失败
 */
NVDSDK_API LONG __stdcall NVD_FindPicture(LONG lLoginHandle, LONG lChannelID, NVD_FIND_PICTURE_PARAM* lpFindParam, void** lppFindHandle);

/**
 * 查询下一张前端抓拍图片
 * @param  lppFindHandle        [in]        查询图片句柄
 * @param  lpFindData           [out]       查询图片结果
 * @return 0:成功  其它:失败
 */
NVDSDK_API LONG __stdcall NVD_FindNextPicture(void* lpFindHandle, NVD_FIND_PICTURE* lpFindData);

/**
 * 关闭查询前端抓拍图片
 * @param  lppFindHandle        [in]        查询图片句柄
 * @return 0:成功  其它:失败
 */
NVDSDK_API LONG __stdcall NVD_CloseFindPicture(void* lpFindHandle);

/**
 * 获取前端抓拍图片数据
 * @param  lpFindHandle         [in]        查询图片句柄
 * @param  lpszFileName         [in]        前端图片名
 * @param  lpszSavedFileName    [in]        本地保存文件路径
 * @return 0:成功  其它:失败
 */
NVDSDK_API LONG __stdcall NVD_GetPicture(void* lpFindHandle, const char* lpszFileName, const char* lpszSavedFileName);

/**
 * 获取前端抓拍图片数据
 * @param  lpFindHandle         [in]        查询图片句柄
 * @param  lpszFileName         [in]        前端图片名
 * @param  lpszSavedFileName    [in]        获取图片数据缓存
 * @param  dwBufLen             [in]        图片缓存数据大小
 * @param  lpdwRetLen           [out]       实际收到的数据大小，不能为空
 * @return 0:成功  其它:失败
 */
NVDSDK_API LONG __stdcall NVD_GetPictureEx(void* lpFindHandle, const char* lpszFileName, void* lpSavedFileBuf, DWORD dwBufLen, DWORD* lpdwRetLen);

/**
 * 查询当前用户
 * @param  lLogInHandle         [in]        登录句柄
 * @param  pUserInfo            [out]       返回注册的用户信息
 * @param  pUserCount           [out]       返回注册的用户个数
 * @return 0:成功  其它: 错误码
 */
NVDSDK_API LONG __stdcall NVD_GetUsers(LONG lLoginHandle, NVD_USER_PARA* pUserInfo, int* pUserCount);

/**
 * 注册用户
 * @param  lLogInHandle         [in]        登录句柄
 * @param  pUserInfo            [out]       注册的用户信息
 * @return 0:成功  其它: 错误码
 */
NVDSDK_API LONG __stdcall NVD_AddUser(LONG lLoginHandle, const NVD_USER_PARA* pUserInfo);

/**
 * 删除用户
 * @param  lLogInHandle         [in]        登录句柄
 * @param  pUserInfo            [out]       要删除的用户名
 * @return 0:成功  其它: 错误码
 */
NVDSDK_API LONG __stdcall NVD_DeleteUser(LONG lLoginHandle, const char* pUsername);

/**
 * 修改用户信息
 * @param  lLogInHandle         [in]        登录句柄
 * @param  pUserInfo            [in]        要修改的用户信息
 * @param  pOldPass             [in]        原密码
 * @return 0:成功  其它: 错误码
 */
NVDSDK_API LONG __stdcall NVD_ModifyUser(LONG lLoginHandle, const NVD_USER_PARA* pUserInfo, const char* pOldPass);


#endif//end of _NVDSDK_H_DEFINE

