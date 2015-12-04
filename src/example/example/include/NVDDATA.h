////////////////////////////////////////////////////////////////////////// 
///  Copyright (C) 2011
///
/// @file NVDDATA.h
/// @brief   
/// @version   
/// @author  
/// @date  2011-05-12
////////////////////////////////////////////////////////////////////////// 

#ifndef __NVD_DATA_H__
#define __NVD_DATA_H__

#ifndef SMART_IPC_DM8127
#define SMART_IPC_DM8127 //DM8127 IPC专用宏
#endif

typedef enum
{
    NVD_OK                      = 0,                    /**< 成功 */

/**
*内部错误号
*/
    NVD_ERR_THREAD              = 0xF0000000,
    NVD_ERR_DEV_TYPE,

    NVD_ERR_MAIN                = 0xF0000100,
    NVD_ERR_NET,

    NVD_ERR_FILE,
    NVD_ERR_SEM,
    NVD_ERR_MEM,

    NVD_ERR_SYSCFG,

    NVD_ERR_INV_ARG,
    NVD_ERR_XML,
    NVD_ERR_NET_CFG_ARG,

    NVD_ERR_UNSUPPORT_CMD,

    NVD_ERR_CH_NUM,
    NVD_ERR_CH_NAME,

    NVD_ERR_SDK_ADD_STREAM,

    NVD_ERR_JPEG_ID,

    NVD_ERR_VIDEO_HI           = 0xF0000200,
    NVD_ERR_VIDEO_TIME_OSD_TYPE,

    NVD_ERR_VIDEO_INIT_FONT,
    NVD_ERR_VIDEO_CH_NOCREATED,

    NVD_ERR_VIDEO_VIDEO_TYPE,
    NVD_ERR_VIDEO_FORMAT,
    NVD_ERR_VIDEO_IMG_TYPE,
    NVD_ERR_VIDEO_STREAM_TYPE,

    NVD_ERR_VIDEO_BITRATE_MAIN,
    NVD_ERR_VIDEO_QP_MAIN,
    NVD_ERR_VIDEO_FPS_MAIN,
    NVD_ERR_VIDEO_IDR_MAIN,
    NVD_ERR_VIDEO_CBR_MAIN,

    NVD_ERR_VIDEO_FORMAT_SUB,
    NVD_ERR_VIDEO_FORMAT_BOTH,

    NVD_ERR_VIDEO_BITRATE_SUB,
    NVD_ERR_VIDEO_QP_SUB,
    NVD_ERR_VIDEO_FPS_SUB,
    NVD_ERR_VIDEO_IDR_SUB,
    NVD_ERR_VIDEO_CBR_SUB,

    NVD_ERR_VIDEO_BRIGHTNESS,
    NVD_ERR_VIDEO_CONTRAST,
    NVD_ERR_VIDEO_SATURATION,
    NVD_ERR_VIDEO_HUE,

    NVD_ERR_VIDEO_IMAGE_AGC,
    NVD_ERR_VIDEO_IMAGE_SENSE,
    NVD_ERR_VIDEO_IMAGE_ISCTB,
    NVD_ERR_VIDEO_IMAGE_ISMIRROR,
    NVD_ERR_VIDEO_IMAGE_SHUTTERSPEED,
    NVD_ERR_VIDEO_IMAGE_IRIS,
    NVD_ERR_VIDEO_IMAGE_ISAWB,
    NVD_ERR_VIDEO_IMAGE_WBR,
    NVD_ERR_VIDEO_IMAGE_WBG,
    NVD_ERR_VIDEO_IMAGE_WBB,
    NVD_ERR_VIDEO_IMAGE_ISAES,
    NVD_ERR_VIDEO_IMAGE_ISBLC,

    NVD_ERR_AUDIO_TYPE          = 0xF0000300,
    NVD_ERR_AUDIO_SOUND_MODE,
    NVD_ERR_AUDIO_BIT_WIDTH,
    NVD_ERR_AUDIO_SAMPLE_RATE,
    NVD_ERR_AUDIO_ISUSED,
    NVD_ERR_AUDIO_OUT_CTRL,

    NVD_ERR_EEPROM_CHKSUM       = 0xF0000400,

    NVD_ERR_DRIVER_OPEN_FD      = 0xF0000500,
    NVD_ERR_DRIVER_NOOPEN_FD,
    NVD_ERR_DRIVER_READ,
    NVD_ERR_DRIVER_WRITE,

    NVD_ERR_USER_PARAERR        = 0xF0000600,           /**<  用户登陆ID参数错误 */
    NVD_ERR_USER_INFO,                                  /**<  用户用户名或密码错误*/
    NVD_ERR_USER_LOGINED,                               /**<  用户已登录*/
    NVD_ERR_USER_CLIENTOFF,                             /**<  用户未登录*/
    NVD_ERR_USER_MAX,                                   /**<  已达到最大用户连接数*/
    NVD_ERR_USER_LEVEL,                                 /**<  用户权限错误*/
    NVD_ERR_USER_IP_PORT,                               /**<  用户登录的ip的端口错误*/
    NVD_ERR_USER_EXIST,                                 /**<  用户已存在*/
    NVD_ERR_ACCOUNT_MAX,                                /**<  账户已满*/
    NVD_ERR_ACCOUNT_NOTEXIST,                           /**<  账户不存在*/


    NVD_ERR_APP_PARAM           = 0xF0000700,           /**<  参数错误 */
    NVD_ERR_APP_CRTHREAD,                               /**<  创建线程失败 */
    NVD_ERR_APP_OPENPORT,                               /**<  打开本地端口失败 */
    NVD_ERR_APP_NETSEND,                                /**<  网络发送失败 */
    NVD_ERR_APP_NETRECV,                                /**<  网络接收失败 */
    NVD_ERR_APP_NOLOGIN,                                /**<  未登录 */
    NVD_ERR_APP_LOADDEC,                                /**<  加载解码器失败 */
    NVD_ERR_APP_OPENAD,                                 /**<  打开音频设备失败 */
    NVD_ERR_APP_LOADENC,                                /**<  加载编码器失败 */
    NVD_ERR_APP_NOMEMORY,                               /**<  内存不足 */
    NVD_ERR_APP_CRSURFACE,                              /**<  创建播放表面失败 */
    NVD_ERR_APP_DRAWFAILD,                              /**<  绘制失败 */
    NVD_ERR_APP_CRTIMEMAN,                              /**<  构造定时器失败 */
    NVD_ERR_APP_RETURNBACK,                             /**<  命令返回失败 */
    NVD_ERR_APP_OPENFILE,                               /**<  打开文件失败 */
    NVD_ERR_APP_GETENCPARAM,                            /**<  获取编码参数失败 */
    NVD_ERR_APP_CTRLTYPE,                               /**<  控制类型不对 */
    NVD_ERR_APP_LMOPEN,                                 /**<  本地对讲已经打开 */
    NVD_ERR_APP_OTHER,                                  /**<  其他错误 */
    NVD_ERR_APP_TIMEOUT,                                /**<  超时 */
    NVD_ERR_APP_NOBUFFER,                               /**<  缓存不足 */

    NVD_ERR_FILE_OPEN           = 0xF0000800,
    NVD_ERR_FILE_SEEK,
    NVD_ERR_FILE_WRITE,
    NVD_ERR_FILE_READ,
    NVD_ERR_FILE_CLOSE,
    NVD_ERR_FILE_IOCTL,

    NVD_ERR_VER_TYPE            = 0xF0000900,
    NVD_ERR_VER_LABEL,
    NVD_ERR_VER_BUSY,
    NVD_ERR_VER_INDEX,
    NVD_ERR_VER_SIZE,
    NVD_ERR_VER_CRC,
    NVD_ERR_VER_SIGN,

    NVD_ERR_DISPLAY_X_POS       = 0xF0000A00,
    NVD_ERR_DISPLAY_Y_POS,
    NVD_ERR_DISPLAY_ALPHA,
    NVD_ERR_DISPLAY_ISSHOW,
    NVD_ERR_DISPLAY_TYPE,
    NVD_ERR_DISPLAY_SIZE,

    NVD_ERR_TEXT_OSD_X_POS      = 0xF0000B00,
    NVD_ERR_TEXT_OSD_Y_POS,
    NVD_ERR_TEXT_OSD_ALPHA,
    NVD_ERR_TEXT_OSD_ISSHOW,
    NVD_ERR_TEXT_OSD_SIZE,

    NVD_ERR_MASK_X_POS          = 0xF0000C00,
    NVD_ERR_MASK_Y_POS,
    NVD_ERR_MASK_WIDTH,
    NVD_ERR_MASK_HEIGHT,

    NVD_ERR_ALARM_IN_ISUSED     = 0xF0000D00,

    NVD_ERR_ALARM_OUT_ISUSED    = 0xF0000E00,

    NVD_ERR_PTZ_PARA            = 0xF0000F00,
    NVD_ERR_PTZ_PRESET_NUM,
    NVD_ERR_PTZ_TRACK_NUM,
    NVD_ERR_PTZ_CRUISE_NUM,
    NVD_ERR_PTZ_COM_SEND,
    NVD_ERR_PTZ_CRUISE_STATUS,                  /**< 正在巡航，不允许删除 */

    NVD_ERR_RTSP_POINT_NULL     = 0xF0001000,
    NVD_ERR_RTSP_GETHOSTNAME_FAIL,
    NVD_ERR_RTSP_DATASIZE_OVERFLOW,
    NVD_ERR_RTSP_PARSE,
    NVD_ERR_RTSP_BUFFULL,
    NVD_ERR_RTSP_NOTFULL,
    NVD_ERR_RTSP_ERROR,
    NVD_ERR_RTSP_ALLOC,
    NVD_ERR_RTSP_ADD_STREAM,

    NVD_ERR_FH_ADD_STREAM       = 0xF0001100,
    NVD_ERR_FH_DEL_STREAM,

    NVD_ERR_NTP_SET_TIME        = 0xF0001200,    /**<  ntp设置时间错误 */
    NVD_ERR_NTP_GET_TIME,                        /**<  ntp读取时间错误 */
    NVD_ERR_NTP_SOCK,                            /**<  ntp socket 错误 */
    NVD_ERR_NTP_SENDTO,                          /**<  ntp sendto 错误 */
    NVD_ERR_NTP_RECVFROM,                        /**<  ntp recvfrom 错误 */
    NVD_ERR_NTP_GETHOST,                         /**<  ntp gethostbyname错误 */
    NVD_ERR_NTP_HOSTTYPE,                        /**<  hosttype类型错误 */
    
    NVD_ERR_SNMP_ERROR          = 0xF0001300,
    NVD_ERR_SNMP_LENGTH_OVERFLOW,                /**<  snmp 长度溢出 */
    NVD_ERR_SNMP_TYPE_NOT_MATCH,                 /**<  类型不匹配 */
    NVD_ERR_SNMP_COMMUNITY_NOT_MATCH,            /**<  community 不匹配 */
    NVD_ERR_SNMP_BIND_ERROR,                     /**<  socket bind 错误 */

    NVD_ERR_PT                  = 0xF0001400,    /**<  平台参数错误*/
    NVD_ERR_PT_HANDLE_NULL,
    NVD_ERR_PT_XML,
    NVD_ERR_PT_COMMAND,
    NVD_ERR_PT_CONVERT,
    
    NVD_ERR_SD                  = 0xF0001500,
    NVD_ERR_SD_UNUSED,                          /**<  未启用 */
    NVD_ERR_SD_NOSDCARD,                        /**<  未插入SD卡 */
    NVD_ERR_SD_NOT_READY,                       /**<  SD卡不可用 */

    NVD_ERR_TOLLGATE            = 0xF0001600,
    NVD_ERR_TOLLGATE_INVALID,

    NVD_ERR_TCP                 = 0xF0001700,   /**<  TCP通信参数错误 */
    NVD_ERR_TCP_OVERMAXCONNECT,                 /**<  已超过TCP最大可连接数 */
    NVD_ERR_TCP_NOMATCH,                        /**<  设置socket属性失败 */
    NVD_ERR_TCP_REUSEADDR,                      /**<  设置socket属性失败 */
    NVD_ERR_TCP_SNDBUF,                         /**<  设置socket属性失败 */
    NVD_ERR_TCP_RCVBUF,                         /**<  设置socket属性失败 */
    NVD_ERR_TCP_KEEPALIVE,                      /**<  设置socket属性失败 */
    NVD_ERR_TCP_KEEPIDLE,                       /**<  设置socket属性失败 */
    NVD_ERR_TCP_KEEPINTVL,                      /**<  设置socket属性失败 */
    NVD_ERR_TCP_KEEPCNT,                        /**<  设置socket属性失败 */

    NVD_ERR_UDP                 = 0xF0001800,   /**<  UDP通信参数错误 */

    NVD_ERR_IVA                 = 0xF0001900,   /**<  智能模块错误 */
    NVD_ERR_QLY                 = 0xF0002000,   /**<*/

    NVD_ERR_UNI_SEQ             =0xF0002100,    /**< 序列号错误*/
    NVD_ERR_UNI_LEN,                            /**< 数据长度错误*/

    NVD_ERR_PT_UNINITED         =0xF0002200,    /**< NVDPT库未初始化*/
    NVD_ERR_DEVICE_UNINITED,                    /**< NVDDEVICE库未初始化*/
    NVD_ERR_DAEMON              =0xF0002300,    /**< DAEMON守护进程模块错误 */

    NVD_ERR_PLAYBACK            =0xF0002400,    /**< 回放错误*/
	NVD_ERR_PLAYBACK_BUSY,						/**< 正在播放时，不能进行其他操作 */

	NVD_ERR_CAPTURE_NOMOREFILE = 0xF0002500,

    NVD_ERR_ILL
}NVD_ERROR_NUM;


#define MAX_VIDEO_IN_NUM            8
#define MAX_ALARM_OUT_NUM           4


#define NVD_TEXT_OSD_NUM_PEER       2       /**<  每一路视频最多支持的叠加的osd字符个数 */
#define NVD_MASK_NUM_PEER           4       /**<  每一路视频最多支持的遮挡个数 */
#define NVD_WARD_MAX_DAY            7       /**<  每一路视频最多的布防时间天数 */
#define NVD_WARD_TIME_NUM_PEER      4       /**<  每一路视频每天的布防时间个数 */


#define NVD_MAX_USER_NAME_LEN       16      /**<  用户名最大长度 */
#define NVD_MAX_PASSWORD_LEN        16      /**<  密码最大长度 */
#define NVD_OSD_LEN                 128     /**<  单个OSD显示字符长度 汉字64 */
#define NVD_STRING_LEN              32      /**<  字符串长度 */
#define NVD_UUID_LEN                64      /**<  uuid字符串长度 */
#define NVD_MAX_EMAIL_LEN           128     /**<  Email 内容最大长度*/

#define NVD_INVALID_HANDLE          -1      /**<  无效句柄,用于登录和播放返回 */

#define MAX_VIDEOFRAME_LENGTH       (1024*1024)  /**<  视频单帧最大长度 */
#define MAX_AUDIOFRAME_LENGTH       0x00F00      /**<  音频单帧最大长度 */
#define JPEG_MAX_PACKET_BUFF        0x500000

typedef enum
{
    NVD_LANGUAGE_CHINESE,               /**<  中文 */
    NVD_LANGUAGE_ENGLISH,               /**<  英文 */
    NVD_LANGUAGE_TLL                    /**<  非法范畴 */
}NVD_LANGUAGE_TYPE;

typedef enum
{
    NVD_CATEGORY_IPC,                 /**<  网络枪型摄像机 */
    NVD_CATEGORY_IPC_PTZ,             /**<  一体化网络球型摄像机 */
    NVD_CATEGORY_AUDIO,               /**<  单音频设备 */
    NVD_CATEGORY_ILL                  /**<  非法范畴 */
}NVD_DEV_CATEGORY;

typedef enum
{
    USER_LEVEL_ADMIN = 0,             /**<  管理员用户（可以更改设备设置，可以进行用户操作，ID固定 */
    USER_LEVEL_RESERVE,               /**<  保留用户,用于本地socket通信 */
    USER_LEVEL_NORMAL,                /**<  一般用户 */
}NVD_USER_LEVEL;

typedef enum
{
    NVD_NETMODEL_TCP = 0,             /**<  TCP方式 */
    NVD_NETMODEL_UDP,                 /**<  UDP方式 */
}NVD_NETMODEL;

typedef enum
{
    NVD_VIDEO_TYPE_H264_BASELINE_PROFILE = 0, /**<  H.264编码baseprofile */
    NVD_VIDEO_TYPE_H264_MAIN_PROFILE,         /**<  H.264编码mainprofile */
    NVD_VIDEO_TYPE_H264_HIGH_PROFILE,         /**<  H.264编码highprofile */
    NVD_VIDEO_TYPE_ILL                        /**<  非法类型 */
}NVD_VIDEO_TYPE;

typedef enum
{
    NVD_IVA_TYPE_RESULT = 80,
    NVD_IVA_TYPE_ILL                  /**<  非法类型 */
}NVD_IVA_TYPE;

typedef enum
{
    ENC_FORMAT_SINGLE = 0,            /**<  单码流 */
    ENC_FORMAT_DOUBLE,                /**<  双码流 */
    ENC_FORMAT_ILL                    /**<  非法类型 */
}NVD_ENC_FORMAT;

typedef enum
{
    ENC_STREAM_TYPE_MAIN = 0,         /**<  主流 */
    ENC_STREAM_TYPE_SUB,              /**<  从流 */
    ENC_STREAM_TYPE_IVA,              /**<  智能 */
    ENC_STREAM_TYPE_MAIN_IVA,         /**<  主流&智能 */
    ENC_STREAM_TYPE_SUB_IVA,          /**<  从流&智能 */
    ENC_STREAM_TYPE_ILL               /**<  非法类型 */
}NVD_ENC_STREAM_TYPE;

typedef enum
{
    ENC_ADV_DN_LEVEL_CLEAREST = 0,      /**<  很清晰 */
    ENC_ADV_DN_LEVEL_CLEAR,             /**<  较清晰 */
    ENC_ADV_DN_LEVEL_MEDIUM ,           /**<  适中   */
    ENC_ADV_DN_LEVEL_BLUR,              /**<  较柔和 */
    ENC_ADV_DN_LEVEL_BLUREST,           /**<  很柔和 */
    ENC_ADV_DN_LEVEL_ILL
}NVD_ENC_ADV_DN_LEVEL;

typedef enum
{
    ENC_ADV_DAYTIME = 0,                /**<  白天模式 */
    ENC_ADV_NIGHT,                      /**<  夜晚模式 */
    ENC_ADV_ILL
}NVD_ENC_ADV_MODE;

typedef enum
{
    IMG_AE_MODE_AUTO = 0,               /**<  自动曝光 */
    IMG_AE_MODE_MAN,                    /**<  手动曝光 */
    IMG_AE_MODE_ILL
}NVD_IMG_AE_MODE;

typedef enum
{
    IMG_AWB_MODE_AUTO     = 0,          /**<  自动白平衡 */
    IMG_AWB_MODE_MAN,                   /**<  手动白平衡 */
    IMG_AWB_MODE_MODE_ILL
}NVD_IMG_AWB_MODE;

typedef enum
{
    IMG_CCM_MODE_MID     = 0,           /**<  适中色调 */
    IMG_CCM_MODE_WARM,                  /**<  暖色调 */
    IMG_CCM_MODE_CALM,                  /**<  冷色调 */
    IMG_CCM_MODE_MODE_ILL
}NVD_IMG_CCM_MODE;

typedef enum
{
    IMG_IRIS_MODE_AUTO     = 0,         /**<  自动光圈 */
    IMG_IRIS_MODE_MAN,                  /**<  手动光圈 */
    IMG_IRIS_MODE_MODE_ILL
}NVD_IMG_IRIS_MODE;

typedef enum
{
    IMG_MODE_AUTO = 0,                  /**<  自动模式 */
    IMG_MODE_COLOR,                     /**<  彩色模式 */
    IMG_MODE_BW,                        /**<  黑白模式 */
    IMG_MODE_ILL
}NVD_IMG_COLOR_MODE;

typedef enum
{
    IMG_MIRROR_MODE_OFF     = 0,        /**<  镜像功能关闭 */
    IMG_MIRROR_MODE_VER,                /**<  垂直翻转 */
    IMG_MIRROR_MODE_HOR,                /**<  水平翻转 */
    IMG_MIRROR_MODE_ROTATE,             /**<  旋转*/
    IMG_MIRROR_MODE_MODE_ILL
}NVD_IMG_MIRROR_MODE;

typedef enum
{
    IMG_DENOISE_MODE_AUTO = 0,          /**<  自动去噪 */
    IMG_DENOISE_MODE_MAN,               /**<  手动去噪 */
    IMG_DENOISE_MODE_OFF,               /**<  关闭去噪 */
    IMG_DENOISE_MODE_ILL
}NVD_IMG_DENOISE_MODE;

typedef enum
{
    IMG_ANTIFOG_MODE_OFF     = 0,       /**<  去雾关闭 */
    IMG_ANTIFOG_MODE_ON,                /**<  去雾打开 */
    IMG_ANTIFOG_MODE_MODE_ILL
}NVD_IMG_ANTIFOG_MODE;

typedef enum
{
    IMG_SHADING_MODE_OFF     = 0,       /**<  暗角校正关闭 */
    IMG_SHADING_MODE_ON,                /**<  暗角校正打开 */
    IMG_SHADING_MODE_MODE_ILL
}NVD_IMG_SHADING_MODE;

typedef enum
{
    IMG_SHARPEN_MODE_AUTO = 0,          /**<  边缘锐化自动 */
    IMG_SHARPEN_MODE_MAN,               /**<  边缘锐化手动 */
    IMG_SHARPEN_MODE_OFF,               /**<  边缘锐化关闭 */
    IMG_SHARPEN_MODE_ILL
}NVD_IMG_SHARPEN_MODE;

typedef enum
{
    IMG_WB_MODE_OFF = 0,                /**<  宽动态关 */
    IMG_WB_MODE_ON,                     /**<  宽动态开 */
    IMG_WB_MODE_ILL
}NVD_IMG_WB_MODE;

typedef enum
{
    IMG_DIS_MODE_OFF     = 0,           /**<  防抖关闭 */
    IMG_DIS_MODE_ON,                    /**<  防抖打开 */
    IMG_DIS_MODE_MODE_ILL
}NVD_IMG_DIS_MODE;

typedef enum
{
    IMG_BLC_MODE_OFF     = 0,           /**<  背光补偿关闭 */
    IMG_BLC_MODE_ON,                    /**<  背光补偿打开 */
    IMG_BLC_MODE_MODE_ILL
}NVD_IMG_BLC_MODE;


#define QCIF_WIDTH  176
#define QCIF_HEIGHT 144

#define CIF_WIDTH   352
#define CIF_HEIGHT  288

#define HD1_WIDTH   704
#define HD1_HEIGHT  288

#define D1_WIDTH    704
#define D1_HEIGHT   576

#define HD720P_WIDTH   1280           /**<  100万 */
#define HD720P_HEIGHT  720

#define HD900P_WIDTH   1600           /**<  130万 */
#define HD900P_HEIGHT  912

#define HD1080P_WIDTH   1920          /**<  200万 */
#define HD1080P_HEIGHT  1080

#define QVGA_WIDTH  320
#define QVGA_HEIGHT 240

#define VGA_WIDTH  640
#define VGA_HEIGHT 480

#define SVGA_WIDTH  800
#define SVGA_HEIGHT 600

#define XGA_WIDTH  1024
#define XGA_HEIGHT 768

#define SXGA_WIDTH  1280              /**<  130万 */
#define SXGA_HEIGHT 1024

#define UXGA_WIDTH  1600              /**<  200万 */
#define UXGA_HEIGHT 1200

#define HD3M_WIDTH  2048              /**<  300万 */
#define HD3M_HEIGHT 1536

#define HD5M_WIDTH  2592              /**<  500万 */
#define HD5M_HEIGHT 1944


typedef enum
{
    ENC_IMG_TYPE_QCIF = 0x1,          /**<  QCIF (176*144) */
    ENC_IMG_TYPE_CIF  = 0x2,          /**<  CIF (352*288) */
    ENC_IMG_TYPE_HD1  = 0x4,          /**<  HD1 (704*288) */
    ENC_IMG_TYPE_D1   = 0x8,          /**<  D1 (704*576) */
    ENC_IMG_TYPE_HD720P = 0x10,       /**<  720P (1280*720) */
    ENC_IMG_TYPE_HD900P = 0x20,       /**<  900P (1600*912) */
    ENC_IMG_TYPE_HD1080P= 0x40,       /**<  1080P (1920*1080) */

    ENC_IMG_TYPE_QVGA   = 0x80,       /**<  QVGA (320*240) */
    ENC_IMG_TYPE_VGA    = 0x100,      /**<  VGA (640*480) */
    ENC_IMG_TYPE_SVGA   = 0x200,      /**<  SVGA (800*600) */
    ENC_IMG_TYPE_XGA    = 0x400,      /**<  XGA (1024*768) */
    ENC_IMG_TYPE_SXGA   = 0x800,      /**<  SXGA (1280*1024) */
    ENC_IMG_TYPE_UXGA   = 0x1000,     /**<  UXGA (1600*1200) */

    ENC_IMG_TYPE_HD3M     = 0x2000,     /**<  3M (2048*1536) */
    ENC_IMG_TYPE_HD5M     = 0x4000,     /**<  5M (2592*1944) */
    ENC_IMG_TYPE_ILL                  /**<  非法分辨率 */
}NVD_ENC_IMG_TYPE;

typedef enum
{
    NVD_AUDIO_TYPE_ADPCMA = 64,       /**<  ADPCMA 不支持*/
    NVD_AUDIO_TYPE_AMR,               /**<  AMR 不支持*/
    NVD_AUDIO_TYPE_G711A,             /**<  G.711A*/
    NVD_AUDIO_TYPE_G711U,             /**<  G.711U*/
    NVD_AUDIO_TYPE_G726,              /**<  G.726 */
    NVD_AUDIO_TYPE_ILL
}NVD_AUDIO_TYPE;

typedef enum
{
    NVD_AUDIO_SOUND_MODE_MOMO = 0,    /**<  mono*/
    NVD_AUDIO_SOUND_MODE_STEREO,      /**<  stereo*/
    NVD_AUDIO_SOUND_MODE_ILL    
}NVD_AUDIO_SOUND_MODE;

typedef enum
{
    NVD_AUDIO_BIT_WIDTH_8 = 0,        /**<  8bit width */
    NVD_AUDIO_BIT_WIDTH_16,           /**<  16bit width*/
    NVD_AUDIO_BIT_WIDTH_32,           /**<  32bit width*/
    NVD_AUDIO_BIT_WIDTH_ILL
}NVD_AUDIO_BIT_WIDTH;

typedef enum
{
    NVD_AUDIO_SAMPLE_RATE_8000 = 0,   /**<  8K samplerate*/
    NVD_AUDIO_SAMPLE_RATE_11025,      /**<  11.025K samplerate*/
    NVD_AUDIO_SAMPLE_RATE_16000,      /**<  16K samplerate*/
    NVD_AUDIO_SAMPLE_RATE_22050,      /**<  22.050K samplerate*/
    NVD_AUDIO_SAMPLE_RATE_24000,      /**<  24K samplerate*/
    NVD_AUDIO_SAMPLE_RATE_32000,      /**<  32K samplerate*/
    NVD_AUDIO_SAMPLE_RATE_44100,      /**<  44.1K samplerate*/
    NVD_AUDIO_SAMPLE_RATE_48000,      /**<  48K samplerate*/
    NVD_AUDIO_SAMPLE_RATE_ILL
}NVD_AUDIO_SAMPLE_RATE; 

typedef enum
{
	NVD_RECORD_ERROR_MEM_SETUP = 0x01, /**< 内存初始化失败 */
	NVD_RECORD_ERROR_OUTOF_MEM = 0x02, /**< 内存不足 */
	NVD_RECORD_ERROR_THINNER_MEM   = 0x04, /**< 内存不够大 */
	NVD_RECORD_ERROR_WRITE     = 0x08, /**< 文件写入错误 */
	NVD_RECORD_ERROR_READ      = 0x10, /**< 读取文件错误 */
	NVD_RECORD_ERROR_OPEN_FILE = 0x20, /**< 打开文件失败 */
	NVD_RECORD_ERROR_ILL
}NVD_RECORD_ERROR;

typedef enum
{
    NVD_ALARM_TYPE_IN = 0,            /**<  报警输入告警*/
    NVD_ALARM_TYPE_MD,                /**<  移动侦测告警*/
    NVD_ALARM_TYPE_OD,                /**<  遮挡侦测告警*/
    NVD_ALARM_TYPE_ST,                /**<  场景转换侦测告警*/
	NVD_ALARM_TYPE_SD,                /**<  SD卡事件(value见NVD_SD_STATUS)*/
	NVD_ALARM_TYPE_RECORD_ERR,        /**<  SD卡录像错误报警(value见NVD_RECORD_ERROR)*/
    NVD_ALARM_TYPE_ILL
}NVD_ALARM_TYPE; 

typedef struct
{
    NVD_ALARM_TYPE      alarmType;
    int                 chn;
    char                name[NVD_STRING_LEN];  /**<  名称 */
    int                 value;

    unsigned char       res[32];               /**<  备用 */
}NVD_ALARM_REPORT_INFO;

typedef struct
{
    int                 chn;                   /**<  通道 */
    int                 panValue;              /**<  pan值 */
    int                 tiltValue;             /**<  tilt值 */

    unsigned char       res[32];               /**<  备用 */
}NVD_PTZ_REPORT_INFO;

typedef struct
{
    int     year;
    int     month;
    int     day;
    int     hour;
    int     minute;
    int     second;
}NVD_TIME;

typedef struct
{
    unsigned short      left;
    unsigned short      right;
    unsigned short      top;
    unsigned short      bottom;
}NVD_RECT;

typedef struct
{
    int                 isUsed;                /**<  是否启用 */

    unsigned short      xPos;
    unsigned short      yPos;

    unsigned short      width;                 /**<  窗口宽度 */
    unsigned short      height;                /**<  窗口高度 */
}NVD_AREA_RECT;

typedef struct
{
    int                 isUsed;                /**<  是否启用 */

    unsigned char       beginHour;
    unsigned char       beginMinute;
    unsigned char       endHour;
    unsigned char       endMinute;
}NVD_TIME_RECT;

typedef struct
{
    /**
    *第一部分属于联动报警部分，这一部分都是需要发送消息的
    */
    /**
    *0x00: 无响应
    *0x01: 上传中心(需要配置报警主机)
    *0x02: 监视器上警告(不支持)
    *0x04: 声音警告(不支持)
    *0x08: Jpeg抓图并上传EMail(不支持)
    *0x10: 邮件
    */
    unsigned int        type;                              /**<  类型 */

    /**
    *第二部分属于告警输出部分
    */
    unsigned char       alarmOut[MAX_ALARM_OUT_NUM];       /**< 1表示触发该通道, 否则置0 */

    /**
    *第三部分属于联动录像部分
    */
    unsigned char       recordChan[MAX_VIDEO_IN_NUM];      /**< 1表示触发该通道, 否则置0 */

    /**
    *第四部分属于联动ptz部分
    */
    unsigned char       isEnablePreset[MAX_VIDEO_IN_NUM];  /**<  是否调用预置点*/
    unsigned char       presetId[MAX_VIDEO_IN_NUM];        /**<  预置点id*/
    unsigned char       isEnableCruise[MAX_VIDEO_IN_NUM];  /**<  是否调用巡航*/
    unsigned char       cruiseId[MAX_VIDEO_IN_NUM];        /**<  巡航id*/
    unsigned char       isEnableTrack[MAX_VIDEO_IN_NUM];   /**<  是否调用轨迹*/
    unsigned char       trackId[MAX_VIDEO_IN_NUM];         /**<  轨迹id*/
    unsigned char       res[32];                           /**<  备用 */
}NVD_HANDLE_LINKAGE;

typedef struct
{
    unsigned int        ip;                         /**<  小字节序 */
    unsigned int        netmask;                    /**<  小字节序 */
    unsigned int        gateway;                    /**< 小字节序 */
    unsigned char       mac[6];
    unsigned char       isDhcp;                     /**<  目前不支持 填0 */
    unsigned char       res;                        /**<  备用 */

    unsigned int        webPort;                    /**<  设备web端口号 */
    unsigned int        dataUdpPort;                /**<  设备UDP数据流端口号*/
    unsigned int        dataTcpPort;                /**<  设备TCP数据流端口号*/

    unsigned char       res1[52];                   /**<  备用 */

    char                devSn[NVD_STRING_LEN];      /**<  设备序列号 */
    char                hwVer[NVD_STRING_LEN];      /**<  硬件版本号 */
    char                swVer[NVD_STRING_LEN];      /**<  软件版本号 */

    NVD_DEV_CATEGORY    devCategory;                /**<  设备分类 */
    unsigned int        devType;                    /**<  设备类型 */

    unsigned char       res2[64];                   /**<  备用 */
}NVD_SEARCH_PARA;

typedef struct
{
    unsigned int        ip;                         /**<  小字节序 */
    unsigned int        netmask;                    /**<  小字节序 */
    unsigned int        gateway;                    /**<  小字节序 */
    unsigned char       mac[6];
    unsigned char       isDhcp;                     /**<  目前不支持 填0 */
}NVD_NET_PARA;

typedef struct
{
    unsigned int        webPort;                    /**<  设备web端口号 */
    unsigned int        dataUdpPort;                /**<  设备udp数据流端口号 */
    unsigned int        dataTcpPort;                /**<  设备TCP数据流端口号 */
    unsigned int        rtspPort;                   /**<  rtsp服务器端口号 */
    unsigned int        alarmHostIpAddr;            /**<  报警主机ip地址 */
    unsigned int        alarmHostPort;              /**<  报警主机端口号 */
    unsigned int        multicastAddr;              /**<  组播  ip地址 */
    unsigned int        multicastPort;              /**<  组播  ip 端口 */
    unsigned char       uuid[64];                   /**<  uuid */
    unsigned int        dns1;                       /**<  DNS1 */
    unsigned int        dns2;                       /**<  DNS2 */    

    unsigned char       res[252];                   /**<  备用 */
}NVD_NET_2_PARA;

typedef struct
{
    int                 isUsed;                     /**<  是否启用 */
    char                ip[32];                     /**<  服务器ip */
    unsigned int        port;                       /**<  服务器端口 */
    unsigned int        interval;                   /**<  校时间隔 */
    int                 timezone;                   /**<  时区 */
   
    unsigned char       res1[32];                   /**<  备用 */
}NVD_NTP_PARA;

typedef struct
{
    int                 isUsed;                     /**<  是否启用 */
    char                smtpip[32];                 /**<  smtp服务器 */
    unsigned int        smtpport;                   /**<  smtp端口 */
    char                username[NVD_STRING_LEN];   /**<  用户名 */
    char                password[NVD_STRING_LEN];   /**<  密码 */
    char                sendAddr[NVD_STRING_LEN];   /**<  发送地址 */
    char                recvAddr_1[NVD_STRING_LEN]; /**<  接收地址1 */
    char                recvAddr_2[NVD_STRING_LEN]; /**<  接收地址2 */
    char                recvAddr_3[NVD_STRING_LEN]; /**<  接收地址3 */
}NVD_EMAIL_PARA;

typedef struct
{
    int                 isSnmpUsed;                 /**<  是否启用snmp功能 */
    char                snmpReadCommunity[32];      /**<  read community */
    unsigned char       res[256];                   /**<  备用 */
}NVD_SNMP_PARA; 

typedef struct
{
    char                username[NVD_MAX_USER_NAME_LEN];  /**<  用户名 */
    char                password[NVD_MAX_PASSWORD_LEN];   /**<  密码 */
    unsigned int        level;                            /**<  用户级别 */
    unsigned int        privilege;                        /**<  用户权限 */
}NVD_USER_PARA;

typedef struct
{
    NVD_DEV_CATEGORY    devCategory;                /**<  设备分类，属于枪机，球机等 */
    unsigned int        devType;                    /**<  设备类型, 公司每一款产品都有一个唯一的类型编号 */
    char                devName[NVD_STRING_LEN];    /**<  设备名称 */

    unsigned char       videoInNum;                 /**<  视频输入通道个数 */
    unsigned char       videoOutNum;                /**<  视频输出通道个数 */
    unsigned char       audioInNum;                 /**<  音频输入个数 */
    unsigned char       audioOutNum;                /**<  音频输出个数 */
    char                channelName[MAX_VIDEO_IN_NUM][NVD_STRING_LEN];    /**<  通道名称 */

    unsigned char       alarmInNum;
    unsigned char       alarmOutNum;
    unsigned char       comNum;
    unsigned char       res;                        /**<  备用 */
    unsigned int        version;                    /**<  软件版本号 */
    unsigned char       res1[28];                   /**<  备用 */
}NVD_LOGIN_INFO;

typedef struct
{
    char                devSn[NVD_STRING_LEN];      /**<  设备序列号 */
    char                hwVer[NVD_STRING_LEN];      /**<  硬件版本号 */
    char                swVer[NVD_STRING_LEN];      /**<  软件版本号 */

    NVD_DEV_CATEGORY    devCategory;                /**<  设备分类 */
    unsigned int        devType;                    /**<  设备类型 */
    char                devName[NVD_STRING_LEN];    /**<  设备名称            此项可以设置 */
    char                typeName[NVD_STRING_LEN];   /**<  类型名称 */

    unsigned char       videoInNum;                 /**<  视频输入通道个数 */
    unsigned char       videoOutNum;                /**<  视频输出通道个数 */
    unsigned char       audioInNum;                 /**<  音频输入个数 */
    unsigned char       audioOutNum;                /**<  音频输出个数 */ 

    unsigned char       alarmInNum;                 /**<  告警输入个数 */
    unsigned char       alarmOutNum;                /**<  告警输出个数 */
    unsigned char       comNum;                     /**<  串口个数 */
    unsigned char       res[33];
}NVD_DEV_PARA;

typedef struct
{
    int                 viNo;                       /**<  当前参数是哪一个通道的 */

    NVD_VIDEO_TYPE      videoType;
    NVD_ENC_FORMAT      encFormat;                  /**<  单码流or双码流 */

    NVD_ENC_IMG_TYPE    encImgTypeMain;             /**<  主流分辨率格式，4cif or h4cif or cif */
    unsigned int        imgTypeMainMask;            /**<  主流分辨率支持类型的mask */
    NVD_ENC_IMG_TYPE    encImgTypeSub;              /**<  从流分辨率格式，4cif or h4cif or cif */
    unsigned int        imgTypeSubMask;             /**<  从流分辨率支持类型的mask */

    unsigned short      bitrateMain;                /**<  主流视频码率 16-10240*/
    unsigned char       qualityMain;                /**<  主流视频编码质量0-5 */
    unsigned char       fpsMain;                    /**<  主流视频帧率 2-25*/
    unsigned char       idrMain;                    /**<  主流I帧间隔2-250 */
    unsigned char       isCbrMain;                  /**<  CBR/VBR */

    unsigned short      bitrateSub;                 /**<  从流视频码率 16-10240*/
    unsigned char       qualitySub;                 /**<  从流视频编码质量 0-5*/
    unsigned char       fpsSub;                     /**<  从流视频帧率 2-25*/
    unsigned char       idrSub;                     /**<  从流I帧间隔 2-250*/
    unsigned char       isCbrSub;                   /**<  CBR/VBR */

    unsigned char       res[32];
}NVD_VIDEO_ENC_PARA;

typedef struct
{
    int                 viNo;                       /**<  当前参数是哪一个通道的 */
    
    unsigned char       denoiseDay;                 /**<  白天视频降噪 0-255 */
    unsigned char       sharpenDay;                 /**<  白天视频锐化 0-255 */
    
    unsigned char       denoiseNight;               /**<  夜晚视频降噪 0-255 */
    unsigned char       sharpenNight;               /**<  夜晚视频锐化 0-255 */

    unsigned char       res[32];
}NVD_VIDEO_ENC_ADV_PARA;

typedef struct
{
    int                     viNo;                   /**<  当前参数是哪一个通道的 */

    NVD_ENC_ADV_DN_LEVEL    encAdvDnLevel;          /**<  设备视频降噪级别 */
    NVD_ENC_ADV_MODE        encAdvMode;             /**<  设备视频降噪模式 (白天模式/夜晚模式) */

    unsigned char           res[32];
}NVD_ENC_ADV_MODE_PARA;

typedef struct
{
    int                 viNo;                       /**<  当前参数是哪一个通道的 */

    unsigned char       brightness;                 /**<  亮度        0-255 */
    unsigned char       contrast;                   /**<  对比度      0-255 */
    unsigned char       saturation;                 /**<  饱和度      0-255 */
    unsigned char       hue;                        /**<  色调        0-255 */

    unsigned char       res[44];
}NVD_IMAGE_PARA;

typedef struct
{
    int                 viNo;                       /**<  当前参数是哪一个通道的 */

    NVD_IMG_AE_MODE      aeMode;                    /**<  曝光模式*/
    NVD_IMG_AWB_MODE     awbMode;                   /**<  白平衡模式*/
    unsigned int         wbr;                       /**<  手动白平衡模式 r 0-255 */
    unsigned int         wbg;                       /**<  手动白平衡模式 g 0-255 */
    unsigned int         wbb;                       /**<  手动白平衡模式 b 0-255 */

    NVD_IMG_CCM_MODE     colorCCM;                  /**<  色调模式*/

    NVD_IMG_IRIS_MODE    irisMode;                  /**<  光圈控制模式*/
    unsigned int         iris;                      /**<  自动光圈控制0-15 */
    unsigned int         agc;                       /**<  增益模式  0-255 */
    unsigned int         shutterSpeed;              /**<  快门速度 0-15  */
    unsigned int         sense;                     /**<  锐度调节 0-16  */
    NVD_IMG_COLOR_MODE   colorMode;                 /**<  色彩模式*/
    NVD_IMG_MIRROR_MODE  mirrorMode;                /**<  镜像模式*/
    NVD_IMG_DENOISE_MODE denoiseMode;               /**<  去噪模式*/
    NVD_IMG_ANTIFOG_MODE antifogMode;               /**<  去雾模式*/
    NVD_IMG_SHADING_MODE shadingMode;               /**<  暗角校正模式*/
    NVD_IMG_SHARPEN_MODE sharpenMode;               /**<  边缘锐化模式*/
    NVD_IMG_WB_MODE      wbMode;                    /**<  宽动态模式*/
    NVD_IMG_DIS_MODE     disMode;                   /**<  防抖模式 */
    NVD_IMG_BLC_MODE     blcMode;                   /**<  背光补偿模式 */

    unsigned char        res[256];
}NVD_IMAGE_PARA_ADV;


typedef struct
{
    unsigned char       red;
    unsigned char       green;
    unsigned char       blue;
    unsigned char       res;
}RGB_QUAD;

typedef enum
{
    NVD_DISPLAY_YYYY_MM_DD_WEEKDATE_HH_MM_SS,       /**<  0: YYYY-MM-DD 星期X HH:MM:SS*/
    NVD_DISPLAY_DD_MM_YYYY_WEEKDATE_HH_MM_SS,       /**<  1: DD-MM-YYYY WEEKDATE HH:MM:SS       英式 */
    NVD_DISPLAY_MM_DD_YYYY_WEEKDATE_HH_MM_SS,       /**<  2: MM-DD-YYYY WEEKDATE HH:MM:SS       美式 */
    NVD_DISPLAY_YYYY_MM_DD_WEEKDATE_HH_MM_SS_1,     /**<  3: YYYY年MM月DD日 星期X HH时MM分SS秒  */

    NVD_DISPLAY_YYYY_MM_DD_HH_MM_SS,                /**<  4: YYYY-MM-DD  HH:MM:SS */
    NVD_DISPLAY_DD_MM_YYYY_HH_MM_SS,                /**<  5: DD-MM-YYYY  HH:MM:SS               英式 */
    NVD_DISPLAY_MM_DD_YYYY_HH_MM_SS,                /**<  6: MM-DD-YYYY  HH:MM:SS               美式 */
    NVD_DISPLAY_YYYY_MM_DD_HH_MM_SS_1,              /**<  7: YYYY年MM月DD日 HH时MM分SS秒 */
    NVD_DISPLAY_TYPE_TIME_ILL
}NVD_DISPLAY_TYPE_TIME;

typedef struct
{
    int                 viNo;                       /**<  当前参数是哪一个通道的 */

    /**
    *通道名称属性
    */
    int                 isShow_name;                /**<  是否显示 */
    unsigned short      xPos_name;                  /**<  X坐标 中文字的宽 */
    unsigned short      yPos_name;                  /**<  Y坐标 中文字的高 */
    RGB_QUAD            fg_color_name;              /**<  前景颜色 */
    RGB_QUAD            bg_color_name;              /**<  背景颜色 */
    unsigned char       fg_alpha_name;              /**<  前景透明度 0-128 */
    unsigned char       bg_alpha_name;              /**<  背景透明度 0-128 */
    unsigned char       res[2];
    int                 isInvColor_name;            /**<  是否反色 */
    int                 invColorThresh_name;        /**<  反色亮度阙值 0-255 */
    char                channelName[NVD_STRING_LEN];   /**<  通道名称 */
    unsigned char       size_name;                  /**<  字体大小0-5    0为自动 */
    unsigned char       res1[3];

    /**
    *时间属性
    */
    int                 isShow_time;                /**<  是否显示 */
    NVD_DISPLAY_TYPE_TIME   disType_time;
    unsigned short      xPos_time;                  /**<  OSD X坐标 */
    unsigned short      yPos_time;                  /**<  OSD Y坐标 */
    RGB_QUAD            fg_color_time;              /**<  前景颜色 */
    RGB_QUAD            bg_color_time;              /**<  背景颜色 */
    unsigned char       fg_alpha_time;              /**<  前景透明度 0-128 */
    unsigned char       bg_alpha_time;              /**<  背景透明度 0-128 */
    unsigned char       size_time;                  /**<  字体大小0-5    0为自动 */
    unsigned char       res2;

    int                 isInvColor_time;            /**<  是否反色 */
    int                 invColorThresh_time;        /**<  反色亮度阙值 0-255 */
}NVD_DISPLAY_PARA;

typedef struct
{
    int                 isShow;                     /**< 是否显示 */

    unsigned short      xPos;                       /**<  X坐标 */
    unsigned short      yPos;                       /**<  Y坐标 */
    RGB_QUAD            fg_color;                   /**<  前景颜色 */
    RGB_QUAD            bg_color;                   /**<  背景颜色 */
    unsigned char       fg_alpha;                   /**<  前景透明度 0-128 */
    unsigned char       bg_alpha;                   /**<  背景透明度 0-128 */
    unsigned char       res[2];

    int                 isInvColor;                 /**<  是否反色 */
    int                 invColorThresh;             /**<  反色亮度阙值 0-255 */

    char                osdChar[NVD_OSD_LEN];       /**<  字符串 */
    unsigned char       size;                       /**<  字体大小0-5  0为自动 */

    unsigned char       res1[3];
}TEXT_OSD_PARA;

typedef struct
{
    int                 viNo;                       /**<  当前参数是哪一个通道的 */

    TEXT_OSD_PARA       textOsd[NVD_TEXT_OSD_NUM_PEER];

    unsigned char       res[16];
}NVD_TEXT_OSD_PARA;


/************************************************************************************/

#define MASK_WIDTH      1000
#define MASK_HEIGHT     1000
typedef struct
{
    int                 viNo;                           /**<  当前参数是哪一个通道的 */

    NVD_AREA_RECT       area[NVD_MASK_NUM_PEER];        /**<  此区域是相对于1000 X 1000 的一个区域 */
    NVD_TIME_RECT       time[NVD_WARD_MAX_DAY][NVD_WARD_TIME_NUM_PEER];  /**<  布防时间 */

    unsigned char       res[16];
}NVD_MASK_PARA;

#ifdef SMART_IPC_DM8127
#define MD_WIDTH        4
#define MD_HEIGHT       3
#define MD_MAX_LEVEL    2
#else
#define MD_WIDTH        22
#define MD_HEIGHT       18
#define MD_MAX_LEVEL    5
#endif

#define MD_WARNING_DELAY     3                          /**<  告警延时时间 */
typedef struct
{
    int                 viNo;                           /**<  当前参数是哪一个通道的 */
    int                 isUsed;                         /**<  是否启用 */

    NVD_HANDLE_LINKAGE  linkage;                        /**<  联动处理 */

    unsigned char       area[MD_WIDTH*MD_HEIGHT];       /**<  区域，总共有4 X 3个区域 */
                                                        /**<  如果对应区域需要进行侦测，那么相应区域置为1, 否者置为0 */

    NVD_TIME_RECT       time[NVD_WARD_MAX_DAY][NVD_WARD_TIME_NUM_PEER];   /**<  布防时间 */
    char                name[NVD_STRING_LEN];                             /**<  名称 */

    unsigned char       level;                          /**<  移动侦测灵敏度 0-5, 越高越灵敏 MD_MAX_LEVEL */

    unsigned char       res[19];
}NVD_MD_PARA;

#define OD_MAX_LEVEL    5
#define MAX_OD_AREA     4
typedef struct
{
    int                 viNo;          /**<  当前参数是哪一个通道的 */
    int                 isUsed;        /**<  是否启用 */

    NVD_HANDLE_LINKAGE  linkage;        /**<  联动处理 */

    NVD_AREA_RECT       area[MAX_OD_AREA];       /**<  区域，总共有4个区域 */
    NVD_TIME_RECT       time[NVD_WARD_MAX_DAY][NVD_WARD_TIME_NUM_PEER];   /**<  布防时间 */
    char                name[NVD_STRING_LEN];  /**<  名称 */

    unsigned char       level;           /**<  遮挡侦测灵敏度 0-5, 越高越灵敏 OD_MAX_LEVEL */

    unsigned char       res[19];
}NVD_OD_PARA;

#define ST_MAX_LEVEL    5
typedef struct
{
    int                 viNo;          /**<  当前参数是哪一个通道的 */
    int                 isUsed;        /**<  场景转换是否启用 */

    NVD_HANDLE_LINKAGE  linkage;        /**<  联动处理 */

    NVD_TIME_RECT       time[NVD_WARD_MAX_DAY][NVD_WARD_TIME_NUM_PEER];   /**<  布防时间 */
    char                name[NVD_STRING_LEN];  /**<  名称 */

    unsigned char       level;           /**<  场景转换灵敏度 0-5, 越高越灵敏 */

    unsigned char       res[15];
}NVD_ST_PARA;


typedef struct
{
    int                 viNo;           /**<  当前参数是哪一个通道的 */
    int                 isUsed;         /**<  是否启用 */
    int                 interval;       /**<  图片存储间隔 10-3600s */
    int                 quality;        /**<  图片质量 1-99 */
    NVD_TIME_RECT       time[NVD_WARD_MAX_DAY][NVD_WARD_TIME_NUM_PEER];       /**<  图片存储时间段 */

    unsigned char       res[16];
}NVD_SNAP_PARA;

typedef struct
{
    int                 viNo;           /**<  当前参数是哪一个通道的 */
    int                 isUsed;         /**<  是否启用录像 */
    int                 isIFrameOnly;   /**<  是否只保存I帧 */
    NVD_ENC_STREAM_TYPE typeStream;     /**<  保存主流还是从流 */
    int                 mins;           /**<  录像时间长度 (分钟) */
    NVD_TIME_RECT       time[NVD_WARD_MAX_DAY][NVD_WARD_TIME_NUM_PEER];       /**<  录像存储时间段 */

    int                 isOfflineSave;  /**<  是否启用掉线保存录像 */

    unsigned char       res[64];
}NVD_REC_PARA;

typedef enum{
    PLAYBACK_SPEED_HALF = 0,        /* 二分之一倍速回放 */
    PLAYBACK_SPEED_NORMAL,          /* 正常回放 */
    PLAYBACK_SPEED_DOUBLE,          /* 两倍速回放 */
    PLAYBACK_SPEED_FULL,            /* 全速回放 */
    PLAYBACK_SPEED_REWIND,          /* 倒放 */

    PLAYBACK_SPEED_ILL
}NVD_REC_PLAYBACK_SPEED;

typedef struct{
    unsigned int isUsed;            /* 是否启用录像回放 */
    NVD_REC_PLAYBACK_SPEED speed;   /* 录像回放速度 */
    NVD_TIME timeStart;             /* 录像回放起始时间 */
    NVD_TIME timeEnd;               /* 录像回放截止时间 */
    unsigned char res[64];
}NVD_REC_PLATBACK_PARA;

#define NVD_REC_QUERY_RESULT_MAX   60
typedef struct
{
    NVD_TIME timeStart;             /* 录像时间段起始时间 */
    NVD_TIME timeEnd;               /* 录像时间段截止时间 */
    unsigned char fileName[NVD_STRING_LEN];
    unsigned int size;              /* 录像文件大小 (单位:Byte) */
}NVD_REC_QUERY_RESULT;

typedef struct{
    NVD_TIME timeStart;             /* 录像查询起始时间 */
    NVD_TIME timeEnd;               /* 录像查询截止时间 */
    NVD_REC_QUERY_RESULT  queryResult[NVD_REC_QUERY_RESULT_MAX];
    unsigned char res[128];    
}NVD_REC_QUERY_PARA;

typedef struct
{
    unsigned char       qp;       /**<  图像质量[0, 255] */
    unsigned char       res[3];
    NVD_AREA_RECT       area;     /**<  ROI 区域大小 */
    unsigned char       res2[8];
}ROI_AREA;

#define MAX_ROI_NUM    8
typedef struct
{
    int                 viNo;                   /**<  当前参数是哪一个通道的 */

    int                 isUsed;                 /**<  是否启用区域增强 */

    ROI_AREA            roiArea[MAX_ROI_NUM];   /**<  ROI区域属性 */
    
    unsigned char       res[64];
}NVD_ROI_PARA;

/************************************************************************************/

typedef struct
{
    int                 aiNo;              /**<  当前参数是哪一个通道的 */

    int                 isUsed;            /**<  是否启用 */

    NVD_AUDIO_TYPE      type;              /**<  音频编码类型 */
    NVD_AUDIO_SOUND_MODE    soundMode;     /**<  音频单声道，立体声 */
    NVD_AUDIO_BIT_WIDTH     bitWidth;      /**<  音频比特位宽 */
    NVD_AUDIO_SAMPLE_RATE   sampleRate;    /**<  音频采样率 */

    int                 volume;            /**<  音量 0-128 */

    unsigned char       res[28];
}NVD_AUDIO_IN_PARA;

typedef struct
{
    int                 aoNo;              /**<  当前参数是哪一个通道的 */

    int                 isUsed;            /**<  是否启用 */

    NVD_AUDIO_TYPE      type;              /**<  音频编码类型 */
    NVD_AUDIO_SOUND_MODE    soundMode;     /**<  音频单声道，立体声 */
    NVD_AUDIO_BIT_WIDTH     bitWidth;      /**<  音频比特位宽 */
    NVD_AUDIO_SAMPLE_RATE   sampleRate;    /**<  音频采样率 */

    int                 volume;            /**<  音量 0-128 */

    unsigned char       res[28];
}NVD_AUDIO_OUT_PARA;

/************************************************************************************/

/* 媒体头的结构 */
typedef struct
{
    unsigned int syncflag:8;            /**<  同步头   */
    unsigned int headerType:4;          /**<  媒体头信息类型, Max type=15  */
    unsigned int dataSize:20;           /**<  整个帧的大小,   Max size=1M-1  */

    unsigned int algorithm:7;           /**<  媒体压缩格式 0-63为视频, 0:海思的h264, 64-79为音频, 80为车牌识别结果,81为人脸识别结果 ...*/
    unsigned int mediaType:3;           /**<  如为视频,0-P frame, 1-I frame; 如为音频,则表示0-mono,1-stereo  */
    unsigned int resolution:6;          /**<  如为视频,则表示分辨率;如为音频,则表示采样率  */
    unsigned int fps:8;                 /**<  如为视频,则表示帧率;如为音频,则表示位宽  */
    unsigned int idr:8;                 /**<  如为视频,则表示I帧间隔;如为音频,则保留 */

    unsigned int timeSec;               /**<  当前帧时间(单位1秒);表示从公元1970年1月1日0时0分0秒算起至今的UTC时间所经过的秒数  */

    unsigned int extInfo;               /**<  扩展信息  */

    unsigned int checksum;              /**<  校验和    */
}NVD_MEDIA_HEAD;

/* JPEG抓拍图片的结构 */
typedef struct
{
    unsigned int syncflag:8;            /**<  同步头   */
    unsigned int headerType:4;          /**<  媒体头信息类型, Max type=15  */
    unsigned int resolution:6;          /**<  分辨率*/
    unsigned int quality:14;            /**<  图像质量(0~99)*/
    unsigned int dataSize;              /**<  整个帧的大小*/

    unsigned int timeSec;               /**<  抓拍图片时间(单位1秒);表示从公元1970年1月1日0时0分0秒算起至今的UTC时间所经过的秒数  */

    /**<  extInfo  扩展信息:
              1:当有抓拍命令时，利用该位判断动作是由谁发出来的,
                     0为远端配置前端抓拍，1为ocx界面前端抓拍.
                注意:抓拍命令返回时，需要填充timeSec，作为jpeg的标志
                     (保存处，以及返回值两处对应起来)
    */
    unsigned int extInfo;               

    unsigned int checksum;              /**<  校验和    */
}NVD_JPEG_HEAD;


/************************************************************************************/

/**
*alarm in
*/
typedef struct
{
    int                 alarmInNo;              /**<  当前参数是哪一个通道的 */
    int                 isUsed;                 /**<  是否启用 */

    NVD_HANDLE_LINKAGE  linkage;                /**<  联动处理 */
    NVD_TIME_RECT       time[NVD_WARD_MAX_DAY][NVD_WARD_TIME_NUM_PEER];  /**<  布防时间 */
    char                name[NVD_STRING_LEN];   /**<  名称 */

    unsigned char       alarmInType;            /**<  告警类型, 0-常闭, 1-常开 */

    unsigned char       res[19];
}NVD_ALARM_IN_PARA;

/**
*alarm out
*/
typedef struct
{
    int                 alarmOutNo;             /**<  当前参数是哪一个通道的 */
    int                 isUsed;                 /**<  是否启用 */

    NVD_TIME_RECT       time[NVD_WARD_MAX_DAY][NVD_WARD_TIME_NUM_PEER];  /**<  布防时间 */
    char                name[NVD_STRING_LEN];   /**<  名称 */

    unsigned char       alarmOutDelay;
    /**<  输出信号状态维持时间 0-5秒，1-10秒，2-30秒，3-1分钟，4-2分钟，5-5分钟，6-10分钟，7-手动，0xff-为无限（需手动关闭） */

    unsigned char       res[19];
}NVD_ALARM_OUT_PARA;

/************************************************************************************/
/**
*com
*/
typedef enum
{
    NVD_PTZ_PROTOCOL_PELCO_D,
    NVD_PTZ_PROTOCOL_PELCO_P,
    NVD_PTZ_PROTOCOL_VT,
    PROTOCOL_ILL
}NVD_PTZ_PROTOCOL;    

typedef enum
{
    NVD_PTZ_B2400,
    NVD_PTZ_B4800,
    NVD_PTZ_B9600,
    NVD_PTZ_B19200,
    NVD_PTZ_B38400,
    NVD_PTZ_B57600,
    NVD_PTZ_B115200,
    BAUDRATE_ILL
}NVD_PTZ_BAUDRATE;

typedef enum
{
    NVD_PTZ_5_DATABITS,
    NVD_PTZ_6_DATABITS,
    NVD_PTZ_7_DATABITS,
    NVD_PTZ_8_DATABITS,
    DATABITS_ILL
}NVD_PTZ_DATABITS;

typedef enum
{
    NVD_PTZ_NO_PARITY,      /**<  no check */
    NVD_PTZ_ODD_PARITY,     /**<  odd check */
    NVD_PTZ_EVEN_PARITY,    /**<  even check */
    PARITY_ILL
}NVD_PTZ_PARITY;

typedef enum
{
    NVD_PTZ_1_STOPBITS,     /**<  1 stop bits */
    NVD_PTZ_2_STOPBITS,     /**<  2 stop bits */
    STOPBITS_ILL
}NVD_PTZ_STOPBITS;

typedef enum
{
    NVD_PTZ_NO_FLOWCRTL,    /**<  no flow control */
    NVD_PTZ_HW_FLOWCRTL,    /**<  hardware flow control */
    NVD_PTZ_SW_FLOWCRTL,    /**<  software flow control */
    FLOWCRTL_ILL
}NVD_PTZ_FLOWCRTL;

typedef struct
{
    NVD_PTZ_BAUDRATE baudRate;
    NVD_PTZ_DATABITS dataBit;
    NVD_PTZ_PARITY   parity;
    NVD_PTZ_STOPBITS stopBit;
    NVD_PTZ_FLOWCRTL flowCtrl;
}NVD_COM_INFO;

/**
*透明串口
*/
typedef struct
{
    int                 comNo;         /**<  当前参数是哪一个通道的 */
    int                 isUsed;        /**<  是否启用 */

    NVD_COM_INFO        comInfo;

    unsigned char       res[16];
}NVD_COM_PARA;

/************************************************************************************/
/**
*ptz
*/
typedef struct
{
    int                 viNo;          /**<  当前参数是哪一个通道的 */
    int                 isUsed;        /**<  是否启用 */

    NVD_PTZ_PROTOCOL    protocol;

    NVD_COM_INFO        comInfo;

    unsigned char       addr;
    unsigned char       comNo;         /**<  使用的是哪一个串口,有可能当前设备有多个串口 */

    unsigned char       res[18];
}NVD_PTZ_COM_PARA;

/**
*PTZ控制命令字 
*/
typedef enum
{
    /**
    *basic,基本命令
    */
    NVD_PTZ_UP = 0,               /**<  上 data1:tilt speed, 1~8 level */
    NVD_PTZ_DOWN,                 /**<  下 data1:tilt speed, 1~8 level */
    NVD_PTZ_LEFT,                 /**<  左 data1:pan speed, 1~8 level */
    NVD_PTZ_RIGHT,                /**<  右 data1:pan speed, 1~8 level */
    NVD_PTZ_LEFTUP,               /**<  左上data1:pan speed, 1~8 level; data2:tilt speed, 1~8 level */
    NVD_PTZ_RIGHTUP,              /**<  右上data1:pan speed, 1~8 level; data2:tilt speed, 1~8 level */
    NVD_PTZ_LEFTDOWN,             /**<  左下data1:pan speed, 1~8 level; data2:tilt speed, 1~8 level */
    NVD_PTZ_RIGHTDOWN,            /**<  右下data1:pan speed, 1~8 level; data2:tilt speed, 1~8 level */
    NVD_PTZ_AUTO_SCAN,            /**<  自动扫描 */
    NVD_PTZ_MANUAL_SCAN,          /**<  手动扫描 */
    NVD_PTZ_CAMERA_ON,
    NVD_PTZ_CAMERA_OFF,
    NVD_PTZ_IRIS_CLOSE,           /**<  光圈小 */
    NVD_PTZ_IRIS_OPEN,            /**<  光圈大 */ 
    NVD_PTZ_FOCUS_NEAR,           /**<  对焦近 */
    NVD_PTZ_FOCUS_FAR,            /**<  对焦远 */
    NVD_PTZ_ZOOM_WIDE,            /**<  变倍小 */
    NVD_PTZ_ZOOM_TELE,            /**<  变倍大 */

    NVD_PTZ_STOP,                 /**<  停止命令 */

    NVD_PTZ_AUXILIARY_1 = 0x80,   /**<  辅助1， data1, 0:close, 1:open*/
    NVD_PTZ_AUXILIARY_2,          /**<  辅助2， data1, 0:close, 1:open*/
    NVD_PTZ_AUXILIARY_3,          /**<  辅助3， data1, 0:close, 1:open*/
    NVD_PTZ_AUXILIARY_4,          /**<  辅助4， data1, 0:close, 1:open*/
    NVD_PTZ_AUXILIARY_5,          /**<  辅助5， data1, 0:close, 1:open*/
    NVD_PTZ_AUXILIARY_6,          /**<  辅助6， data1, 0:close, 1:open*/
    NVD_PTZ_AUXILIARY_7,          /**<  辅助7， data1, 0:close, 1:open*/
    NVD_PTZ_AUXILIARY_8,          /**<  辅助8， data1, 0:close, 1:open*/

    NVD_DIGITAL_PTZ_UP = 0x100,   /**<  上 data1:tilt speed, 1~8 level */
    NVD_DIGITAL_PTZ_DOWN,         /**<  下 data1:tilt speed, 1~8 level */
    NVD_DIGITAL_PTZ_LEFT,         /**<  左 data1:pan speed, 1~8 level */
    NVD_DIGITAL_PTZ_RIGHT,        /**<  右 data1:pan speed, 1~8 level */
    NVD_DIGITAL_PTZ_LEFTUP,       /**<  左上data1:pan speed, 1~8 level; data2:tilt speed, 1~8 level */
    NVD_DIGITAL_PTZ_RIGHTUP,      /**<  右上data1:pan speed, 1~8 level; data2:tilt speed, 1~8 level */
    NVD_DIGITAL_PTZ_LEFTDOWN,     /**<  左下data1:pan speed, 1~8 level; data2:tilt speed, 1~8 level */
    NVD_DIGITAL_PTZ_RIGHTDOWN,    /**<  右下data1:pan speed, 1~8 level; data2:tilt speed, 1~8 level */

    NVD_DIGITAL_PTZ_ZOOM_WIDE,    /**<  变倍小 */
    NVD_DIGITAL_PTZ_ZOOM_TELE,    /**<  变倍大 */

    NVD_DIGITAL_PTZ_STOP,         /**<  停止命令 */

    NVD_PTZ_ILL
}NVD_PTZ_CTRL_CMD;

/**
*控球基本结构
*/
typedef struct
{
    NVD_PTZ_CTRL_CMD        cmd;            /**<  控制命令字 */

    /**
    *控制数据
    */
    unsigned char           data1;          /**<  参照NVD_PTZ_CMD，未说明即为0 */
    unsigned char           data2;          /**<  参照NVD_PTZ_CMD，未说明即为0 */

    unsigned char           res[18];        /**<  备用 */
}NVD_PTZ_CTRL_DATA;

/**************************************************************/
#define NVD_MAX_PRESET_SET     32
#define NVD_MAX_PRESET_GRP     4
#define NVD_MAX_PRESET_NUM     NVD_MAX_PRESET_SET*NVD_MAX_PRESET_GRP
typedef struct
{
    int                     isUsed;         /**<  是否启用 */
    char                    presetName[NVD_STRING_LEN];     /**<  预置点名字 */
}PTZ_PRESET_PARA;

/*
 * 预置位组
 * res[0]值为0时获取第一组，为1时第二组，以此类推
 */
typedef struct
{
    int                     viNo;           /**<  当前参数是哪一个通道的 */

    PTZ_PRESET_PARA         presetPara[NVD_MAX_PRESET_SET];

    unsigned char           res[16];        /**<  备用 */
}NVD_PTZ_PRESET_PARA;

typedef enum
{
    PTZ_ADD_PRESET,        /**<  增加预置点 */
    PTZ_DEL_PRESET,        /**<  删除预置点 */
    PTZ_MODIFY_PRESET,     /**<  修改预置点 */
    PTZ_GOTO_PRESET,       /**<  执行预置点 */

    PTZ_PRESET_ILL
}NVD_PTZ_PRESET_CMD;

/**
*预置点结构 
*/
typedef struct
{
    NVD_PTZ_PRESET_CMD      cmd;            /**<  控制命令字 */

    int                     presetId;       /**<  预置点编号 */
    char                    presetName[NVD_STRING_LEN];     /**<  预置点名字 */

    unsigned char           res[16];        /**<  备用 */
}NVD_PTZ_CTRL_PRESET_PARA;

/**************************************************************/
#define NVD_MAX_TRACK_NUM     32

typedef struct
{
    int                     isUsed;        /**<  是否启用 */
    char                    trackName[NVD_STRING_LEN];     /**<  轨迹名字 */
}PTZ_TRACK_PARA;

typedef struct
{
    int                     viNo;          /**<  当前参数是哪一个通道的 */

    PTZ_TRACK_PARA          trackPara[NVD_MAX_TRACK_NUM];

    unsigned char           res[16];        /**<  备用 */
}NVD_PTZ_TRACK_PARA;

typedef enum
{
    PTZ_ADD_TRACK,          /**<  增加轨迹 */
    PTZ_DEL_TRACK,          /**<  删除轨迹 */
    PTZ_START_MEM_TRACK,    /**<  开始记录轨迹 (如果之前这个轨迹配置过，那么直接覆盖) */
    PTZ_STOP_MEM_TRACK,     /**<  停止记录轨迹 */
    PTZ_START_RUN_TRACK,    /**<  开始运行轨迹 */
    PTZ_STOP_RUN_TRACK,     /**<  停止运行轨迹 */

    PTZ_TRACK_ILL
}NVD_PTZ_TRACK_CMD;

/**
*轨迹结构
*/
typedef struct
{
    NVD_PTZ_TRACK_CMD       cmd;            /**<  控制命令字 */

    int                     trackId;        /**<  轨迹编号 */
    char                    trackName[NVD_STRING_LEN];     /**<  轨迹名字 */

    unsigned char           res[16];        /**<  备用 */
}NVD_PTZ_CTRL_TRACK_PARA;

/**************************************************************/
#define NVD_MAX_CRUISE_NUM          16
#define NVD_MAX_CRUISE_POINT_NUM    16
typedef struct
{
    int                     isUsed;         /**<  当前参数是否使用 */
    char                    cruiseName[NVD_STRING_LEN];     /**<  巡航路径名字 */

    unsigned char           res[16];        /**<  备用 */
}PTZ_CRUISE_PARA;

typedef struct
{
    int                     viNo;           /**<  当前参数是哪一个通道的 */

    PTZ_CRUISE_PARA         cruisePara[NVD_MAX_CRUISE_NUM]; /**<  具体的巡航路径 */

    unsigned char           res[16];        /**<  备用 */
}NVD_PTZ_CRUISE_PARA;

typedef enum
{
    PTZ_ADD_CRUISE,        /**<  增加巡航 */
    PTZ_DEL_CRUISE,        /**<  删除巡航 */
    PTZ_START_CRUISE,      /**<  开始巡航 */
    PTZ_STOP_CRUISE,       /**<  停止巡航 */

    PTZ_CRUISE_ILL
}NVD_PTZ_CRUISE_CMD;

/**
*轨迹结构
*/
typedef struct
{
    NVD_PTZ_CRUISE_CMD      cmd;            /**<  控制命令字 */
 
    int                     cruiseId;       /**<  巡航路径编号 */
    char                    cruiseName[NVD_STRING_LEN];     /**<  巡航名字 */

    unsigned char           res[16];        /**<  备用 */
}NVD_PTZ_CTRL_CRUISE_PARA;

/*************************************/

/**
*对于修改巡航路径具体信息的操作，单独使用结构体。
*当给设备发获取的时候，根据巡航路径号发送要修改的巡航路径的具体信息，发送NVD_PTZ_CRUISE_POINT_PARA
*当给设备发设置的时候，上层应该下发NVD_PTZ_CRUISE_POINT_PARA，具体要修改的路径号，填在cruiseId中
*/
typedef struct
{
    int                     isUsed;         /**<  当前参数是否使用 */

    int                     presetId;       /**<  在巡航点上对应的预置点号 */
    char                    presetName[NVD_STRING_LEN];     /**<  预置点名字 */

    unsigned char           dwell;          /**<  在巡航点上对应的停顿时间 */
    unsigned char           res[3];         /**<  备用 */
}CRUISE_POINT_PARA;

typedef struct
{
    int                     cruiseId;         /**<  当前参数是哪一个巡航路径的 */
    char                    cruiseName[NVD_STRING_LEN];     /**<  巡航路径名字 */

    CRUISE_POINT_PARA       pointPara[NVD_MAX_CRUISE_POINT_NUM];
}NVD_PTZ_CRUISE_POINT_PARA;

/**************************************************************/

/**
*自动归位预置点结构
*/
typedef struct
{
    int                     viNo;           /**<  当前参数是哪一个通道的 */
    int                     isUsed;         /**<  是否启用 */

    int                     presetId;       /**<  预置点编号 */
    char                    presetName[NVD_STRING_LEN];     /**<  预置点名字 */
    unsigned int            resetTime;      /**<  自动归位的时间 */

    unsigned char           res[16];        /**<  备用 */
}NVD_PTZ_DEFAULT_PRESET_PARA;

/**************************************************************/

/**
*3D局部快速放大,球机3D定位
*/
typedef struct
{
    unsigned short          allWidth;       /**<  整个播放窗口的宽度 */
    unsigned short          allHeight;      /**<  整个播放窗口的高度 */
    unsigned short          xPos;           /**<  框选窗口的左上角x轴坐标 */
    unsigned short          yPos;           /**<  框选窗口的左上角y轴坐标 */
    unsigned short          width;          /**<  框选窗口的宽度 */
    unsigned short          height;         /**<  框选窗口的高度 */

    unsigned char           res[16];        /**<  备用 */
}NVD_PTZ_3D_LOCATE_DATA;

/**************************************************************/

/**
*UniModule 一体化机芯参数
*/
#define NVD_MAX_PTZ_UNI_MODULE_LEN  20      /**<  一体化机芯单条消息最大长度 */
typedef struct
{
    int                     isUsed;         /**<  是否有效 */
    int                     seq;            /**<  当前参数是第几个序列 */

    int                     len;            /**<  当前buf的有效长度 */

    unsigned char           buf[NVD_MAX_PTZ_UNI_MODULE_LEN];        /**<  具体数据 */
}NVD_PTZ_UNI_MODULE_DATA;
/**************************************************************/


/**
*模拟键盘控制命令字 
*/
typedef enum
{
    NVD_KEYBOARD_MENU = 0,       /**<  菜单 */
    NVD_KEYBOARD_TELT_UP,        /**<  上 */
    NVD_KEYBOARD_WIDE_DOWN,      /**<  下 */
    NVD_KEYBOARD_FAR_LEFT,       /**<  左 */
    NVD_KEYBOARD_NEAR_RIGHT,     /**<  右 */

    NVD_KEYBOARD_ILL
}NVD_KEYBOARD_CTRL_CMD;

/**
*模拟键盘基本结构
*/
typedef struct
{
    NVD_KEYBOARD_CTRL_CMD   cmd;        /**<  控制命令字 */

    /**
    *保留
    */
    unsigned char           res[20];    /**<  备用 */
}NVD_KEYBOARD_CTRL_DATA;

/************************************************************************************/

typedef enum
{
    NVD_SD_STATUS_INSERTED			= 0x01,     /**<  SD卡插入*/
	NVD_SD_STATUS_WRITE_PROTECTED	= 0x02,		/**<  SD卡写保护开关打开*/
	NVD_SD_STATUS_MOUNTED			= 0x04,		/**<  SD卡已挂载*/
    NVD_SD_STATUS_FORMATTING		= 0x08,     /**<  SD卡正在格式化*/
	NVD_SD_STATUS_READONLY			= 0x10,		/**<  SD卡文件系统挂载为只读(异常拔卡等导致SD卡文件系统错误时,会出现没有打开写保护开关但是SD卡挂载为只读情况)*/
    NVD_SD_STATUS_ILL
}NVD_SD_STATUS;

/**
*SD卡配置基本结构
*/
typedef struct
{
    int                 status;                   /**<  SD卡状态*/
    char				res[4];                   /**<  保留 */

#if defined( _MSC_VER) && (_MSC_VER<1500)
	unsigned __int64	nTotalSpace;              /**<  SD卡总容量(Byte) */
	unsigned __int64	nFreeSpace;               /**<  空余容量(Byte) */
	   
	unsigned __int64	nTotalRecordUsedSize;	  /**<  当前录像已经使用空间(Byte) */
	unsigned __int64	nTotalCaptureUsedSize;	  /**<  当前抓拍已经使用空间(Byte) */
#else
    unsigned long long	nTotalSpace;              /**<  SD卡总容量(Byte) */
    unsigned long long	nFreeSpace;               /**<  空余容量(Byte) */

	unsigned long long	nTotalRecordUsedSize;	  /**<  当前录像已经使用空间(Byte) */
	unsigned long long	nTotalCaptureUsedSize;	  /**<  当前抓拍已经使用空间(Byte) */
#endif

}NVD_SD_PARA;
/************************************************************************************/
/**
*智能基本参数配置结构体
*/
typedef struct
{
    unsigned char isUsed;                       /**< 是否启用 */
    unsigned char interval;                     /**< 间隔(帧)[0,5] */
    unsigned char sensitivity;                  /**< 灵敏度[0,100] */
    unsigned char sceneType;                    /**< 场景模式: 0:室外，1:室内 */
    unsigned char processingQuality;            /**< 运行质量[0,3] : 0 - Low, 1 - Med, 2 - High, 3 - Use original video scale */

    unsigned char pplEnabled;                   /**< 是否检测人 : 0 - disabled, 1 - enabled  */
    unsigned char minPplWdPercent;              /**< 最小宽度[0,100](相对于当前分辨率的百分比) */
    unsigned char minPplHtPercent;              /**< 最小高度[0,100](相对于当前分辨率的百分比) */
    unsigned char maxPplWdPercent;              /**< 最大宽度[0,100](相对于当前分辨率的百分比) */
    unsigned char maxPplHtPercent;              /**< 最大高度[0,100](相对于当前分辨率的百分比) */

    unsigned char vehEnabled;                   /**< 是否检测车辆 : 0 - disabled, 1 - enabled  */
    unsigned char minVehWdPercent;              /**< 最小宽度[0,100](相对于当前分辨率的百分比) */
    unsigned char minVehHtPercent;              /**< 最小高度[0,100](相对于当前分辨率的百分比) */
    unsigned char maxVehWdPercent;              /**< 最大宽度[0,100](相对于当前分辨率的百分比) */
    unsigned char maxVehHtPercent;              /**< 最大高度[0,100](相对于当前分辨率的百分比) */
    
    unsigned char objEnabled;                   /**< 是否检测物体 : 0 - disabled, 1 - enabled  */
    unsigned char minObjWdPercent;              /**< 最小宽度[0,100](相对于当前分辨率的百分比) */
    unsigned char minObjHtPercent;              /**< 最小高度[0,100](相对于当前分辨率的百分比) */
    unsigned char maxObjWdPercent;              /**< 最大宽度[0,100](相对于当前分辨率的百分比) */
    unsigned char maxObjHtPercent;              /**< 最大高度[0,100](相对于当前分辨率的百分比) */

    unsigned char othEnabled;                   /**< 是否检测其它物体 : 0 - disabled, 1 - enabled  */
    unsigned char minOthWdPercent;              /**< 最小宽度[0,100](相对于当前分辨率的百分比) */
    unsigned char minOthHtPercent;              /**< 最小高度[0,100](相对于当前分辨率的百分比) */
    unsigned char maxOthWdPercent;              /**< 最大宽度[0,100](相对于当前分辨率的百分比) */
    unsigned char maxOthHtPercent;              /**< 最大高度[0,100](相对于当前分辨率的百分比) */

    unsigned char res[127];

}NVD_IVA_STANDARD_PARA;

/**
*智能高级参数配置结构体
*/
typedef struct
{
    unsigned short initLearnTime;               /**< 初始学习时间(秒) Initial learning time in sec */
    unsigned char initLearnType;                /**< 初始学习类型, 0:没物体下学习,1:立刻学习 */

    unsigned char conBGLearnEnable;             /**< 是否持续学习: 0 - disabled, 1 - enabled */
    unsigned short conBGLearnTime;              /**< 持续学习时间(毫秒)*/
    unsigned char conBGSpeed;                   /**< 持续学习速度[0,3] : 0 (slow) .. 3 (fast) */
    unsigned char conBGObjInSceEnable;          /**< 是否静态物体学习 : 0 - disabled, 1 - enabled */
    unsigned short conBGObjInScene;             /**< 静态物体学习时间(秒) */

    unsigned char  enableSuddenChangeBGl;       /**< 是否检测背景瞬间变化和背景学习 : 0 - disabled, 1 - enabled */
    unsigned char  suddenChangeThreshold;       /**< 瞬间变化检测灵敏度[0,100] */

    unsigned char  colorCheck;                  /**< 是否识别物体颜色 : 0 - disabled, 1 - enabled */
    unsigned char  shapeApperance;              /**< 是否识别物体形状 : 0 - disabled, 1 - enabled */
    unsigned char  motionCheck;                 /**< 是否检测物体运动状态 : 0 - disabled, 1 - enabled */
    unsigned char  contrastCheck;               /**< 是否对比物体 : 0 - disabled, 1 - enabled */

    unsigned char  trackerType;                 /**< 是否跟踪 : 0 - disabled, 1 - enabled */
    unsigned char  shadowSuppress;              /**< 阴影抑制强度[0,100] */
    unsigned short initialTime;                 /**< 物体确认时间(毫秒) */
    
    unsigned char   enbObjEntryExit;            /**< 是否使能物体出现消失事件 : 0 - disabled, 1 - enabled */
    unsigned char   enbSingleEventPerObj;       /**< 是否单个物体只关联单个事件 Single event per object: 0 - disabled, 1 - enabled */
    unsigned short timeDiffBetTwoEvents;        /**< 事件间隔(秒) Time between events: 0.. */

    unsigned char res[128];

}NVD_IVA_ADVANCED_PARA;


#define NVD_MAX_HEIGHT_LINE_NUM     3   /**<  身高线最大条数 */
#define NVD_MAX_HEIGHT_POS_NUM      5   /**<  每条身高线最多参考点 */
#define NVD_MAX_HL_TXT_LEN          64  /**<  身高线标示字符最大长度 */
typedef struct
{
    unsigned short posX;    /**<  x坐标 */
    unsigned short posY;    /**<  y坐标 */
}NVD_IVA_POS_COORD;

/**
*智能身高线基本配置结构
*/
typedef struct
{
    unsigned int isUsed;                                                        /**< 是否启用身高线坐标 */
    NVD_IVA_POS_COORD pos[NVD_MAX_HEIGHT_LINE_NUM][NVD_MAX_HEIGHT_POS_NUM];     /**< 身高线坐标:身高线1，身高线2，基准线 */
    unsigned char txtHl[NVD_MAX_HEIGHT_LINE_NUM][NVD_MAX_HL_TXT_LEN];           /**< 身高线标示字符串 */
    
    char res[44];
}NVD_IVA_HL_PARA;

/**
*智能警戒线基本配置结构
*/
typedef struct{
    int enableCordon;           /**< 是否启用警戒线*/
    NVD_IVA_POS_COORD posStart; /**< 起始坐标 */
    NVD_IVA_POS_COORD posEnd;   /**< 结束坐标 */
    
    unsigned char res[64];
}NVD_IVA_CORDON_PARA;

/**
*智能人流统计基本配置结构
*/
typedef struct{
    unsigned int enablePplCounter;      /**< 是否启用人流统计 */
    NVD_IVA_POS_COORD posStart;         /**< 起始坐标 */
    NVD_IVA_POS_COORD posEnd;           /**< 结束坐标 */

    unsigned char res[64];
}NVD_IVA_PPL_COUNTER_PARA;

/**
*智能车流统计基本配置结构
*/
typedef struct{
    unsigned int enableVehCounter;      /**< 是否启用车流统计 */
    NVD_IVA_POS_COORD posStart;         /**< 起始坐标 */
    NVD_IVA_POS_COORD posEnd;           /**< 结束坐标 */

    unsigned char res[64];
}NVD_IVA_VEH_COUNTER_PARA;

/**
*录像下载
*/
/**
@brief 录像下载模式
*/
typedef enum
{
    NVD_RECORD_PLAYBACK_MODE_BY_NAME     = 0,   /**<  以文件名进行下载*/
    NVD_RECORD_PLAYBACK_MODE_BY_TIME,           /**<  以时间段进行下载*/
    NVD_RECORD_PLAYBACK_MODE_ILL,
}NVD_RECORD_PLAYBACK_MODE;
/**
*@brief 录像时间结构
*/
typedef struct tagNET_TIME
{
     unsigned short wYear;
     unsigned char  byMonth;
     unsigned char  byDay;
     unsigned char  byHour;
     unsigned char  byMinute;
     unsigned char  bySecond;
     unsigned char  byRes;
}NET_TIME,*LPNET_TIME;
/**
 @brief 录像文件信息
*/
typedef struct tagNET_RECORDFILE_INFO
{
    char szFileName[100];           /**<  文件名 */
    NET_TIME startTime;             /**<  文件的开始时间 */
    NET_TIME stopTime;              /**<  文件的结束时间 */
    unsigned int dwFileSize;        /**<  文件的大小 */
}NET_RECORDFILE_INFO, *LPNET_RECORDFILE_INFO;
/**
* @brief 开启录像下载参数
*/
typedef struct tagNVD_RECORD_PLAYBACK
{
    NVD_RECORD_PLAYBACK_MODE mode;  /**<  文件下载模式 */
    char szFileName[100];           /**<  以文件名进行下载时，用该值 */
    unsigned char   byChannel;      /**<  以时间段进行下载时，该值有效 */
    unsigned char   byReserve[3];
    unsigned int    dwType;         /**<  以时间段进行下载时，该值有效 */
    NET_TIME        startTime;      /**<  以时间段进行下载时，该值有效 */
    NET_TIME        stopTime;       /**<  以时间段进行下载时，该值有效 */
    unsigned int    dwTimeout;      /**<  ms,超时时间（从开始下载到结束下载的预计时间段，如果超过该时间段，IPC端可能会单方结束下载） */
}NVD_RECORD_PLAYBACK,*LPNVD_RECORD_PLAYBACK;

/**
* @brief 音视频帧搜索
*/
typedef struct tagNVD_RECORD_PLAYBACK_SEEK
{
    unsigned int dwTime;            /**<  1970/1/1 00:00:00至今的秒数 */
}NVD_RECORD_PLAYBACK_SEEK,*LPNVD_RECORD_PLAYBACK_SEEK;
/**
*@brief 录像文件查找条件
*/
typedef struct tagNVD_RECORD_FILE_FIND
{
    unsigned char   byChannel;
    unsigned char   byReserve[3];
    unsigned int    dwType;
    NET_TIME        startTime;
    NET_TIME        stopTime;
    unsigned int    dwTimeout;//ms
}NVD_RECORD_FILE_FIND,*LPNVD_RECORD_FILE_FIND;

/**
* 前端抓拍图片查找参数
*/
typedef struct
{
    unsigned char  byFileType;      // 查找的图片类型: 0-定时抓拍 1-移动侦测抓拍 2-报警抓拍 3-场景转换 4-视频遮挡 0xff-全部类型
    unsigned char  byRes1[3];       // 保留字节
    NVD_TIME       ntStartTime;     // 查找图片的开始时间
    NVD_TIME       ntStopTime;      // 查找图片的结束时间
    unsigned char  byRes2[16];      // 保留字节
}NVD_FIND_PICTURE_PARAM;

/**
* 前端抓拍图片查找结果
*/
typedef struct
{
    char           sFileName[64];    // 图片文件名
    NVD_TIME       ntTime;           // 图片的时间
    unsigned int   dwFileSize;       // 图片数据大小
    unsigned char  byRes[6];         // 保留字节
}NVD_FIND_PICTURE;

#endif

