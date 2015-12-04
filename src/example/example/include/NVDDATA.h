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
#define SMART_IPC_DM8127 //DM8127 IPCר�ú�
#endif

typedef enum
{
    NVD_OK                      = 0,                    /**< �ɹ� */

/**
*�ڲ������
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

    NVD_ERR_USER_PARAERR        = 0xF0000600,           /**<  �û���½ID�������� */
    NVD_ERR_USER_INFO,                                  /**<  �û��û������������*/
    NVD_ERR_USER_LOGINED,                               /**<  �û��ѵ�¼*/
    NVD_ERR_USER_CLIENTOFF,                             /**<  �û�δ��¼*/
    NVD_ERR_USER_MAX,                                   /**<  �Ѵﵽ����û�������*/
    NVD_ERR_USER_LEVEL,                                 /**<  �û�Ȩ�޴���*/
    NVD_ERR_USER_IP_PORT,                               /**<  �û���¼��ip�Ķ˿ڴ���*/
    NVD_ERR_USER_EXIST,                                 /**<  �û��Ѵ���*/
    NVD_ERR_ACCOUNT_MAX,                                /**<  �˻�����*/
    NVD_ERR_ACCOUNT_NOTEXIST,                           /**<  �˻�������*/


    NVD_ERR_APP_PARAM           = 0xF0000700,           /**<  �������� */
    NVD_ERR_APP_CRTHREAD,                               /**<  �����߳�ʧ�� */
    NVD_ERR_APP_OPENPORT,                               /**<  �򿪱��ض˿�ʧ�� */
    NVD_ERR_APP_NETSEND,                                /**<  ���緢��ʧ�� */
    NVD_ERR_APP_NETRECV,                                /**<  �������ʧ�� */
    NVD_ERR_APP_NOLOGIN,                                /**<  δ��¼ */
    NVD_ERR_APP_LOADDEC,                                /**<  ���ؽ�����ʧ�� */
    NVD_ERR_APP_OPENAD,                                 /**<  ����Ƶ�豸ʧ�� */
    NVD_ERR_APP_LOADENC,                                /**<  ���ر�����ʧ�� */
    NVD_ERR_APP_NOMEMORY,                               /**<  �ڴ治�� */
    NVD_ERR_APP_CRSURFACE,                              /**<  �������ű���ʧ�� */
    NVD_ERR_APP_DRAWFAILD,                              /**<  ����ʧ�� */
    NVD_ERR_APP_CRTIMEMAN,                              /**<  ���춨ʱ��ʧ�� */
    NVD_ERR_APP_RETURNBACK,                             /**<  �����ʧ�� */
    NVD_ERR_APP_OPENFILE,                               /**<  ���ļ�ʧ�� */
    NVD_ERR_APP_GETENCPARAM,                            /**<  ��ȡ�������ʧ�� */
    NVD_ERR_APP_CTRLTYPE,                               /**<  �������Ͳ��� */
    NVD_ERR_APP_LMOPEN,                                 /**<  ���ضԽ��Ѿ��� */
    NVD_ERR_APP_OTHER,                                  /**<  �������� */
    NVD_ERR_APP_TIMEOUT,                                /**<  ��ʱ */
    NVD_ERR_APP_NOBUFFER,                               /**<  ���治�� */

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
    NVD_ERR_PTZ_CRUISE_STATUS,                  /**< ����Ѳ����������ɾ�� */

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

    NVD_ERR_NTP_SET_TIME        = 0xF0001200,    /**<  ntp����ʱ����� */
    NVD_ERR_NTP_GET_TIME,                        /**<  ntp��ȡʱ����� */
    NVD_ERR_NTP_SOCK,                            /**<  ntp socket ���� */
    NVD_ERR_NTP_SENDTO,                          /**<  ntp sendto ���� */
    NVD_ERR_NTP_RECVFROM,                        /**<  ntp recvfrom ���� */
    NVD_ERR_NTP_GETHOST,                         /**<  ntp gethostbyname���� */
    NVD_ERR_NTP_HOSTTYPE,                        /**<  hosttype���ʹ��� */
    
    NVD_ERR_SNMP_ERROR          = 0xF0001300,
    NVD_ERR_SNMP_LENGTH_OVERFLOW,                /**<  snmp ������� */
    NVD_ERR_SNMP_TYPE_NOT_MATCH,                 /**<  ���Ͳ�ƥ�� */
    NVD_ERR_SNMP_COMMUNITY_NOT_MATCH,            /**<  community ��ƥ�� */
    NVD_ERR_SNMP_BIND_ERROR,                     /**<  socket bind ���� */

    NVD_ERR_PT                  = 0xF0001400,    /**<  ƽ̨��������*/
    NVD_ERR_PT_HANDLE_NULL,
    NVD_ERR_PT_XML,
    NVD_ERR_PT_COMMAND,
    NVD_ERR_PT_CONVERT,
    
    NVD_ERR_SD                  = 0xF0001500,
    NVD_ERR_SD_UNUSED,                          /**<  δ���� */
    NVD_ERR_SD_NOSDCARD,                        /**<  δ����SD�� */
    NVD_ERR_SD_NOT_READY,                       /**<  SD�������� */

    NVD_ERR_TOLLGATE            = 0xF0001600,
    NVD_ERR_TOLLGATE_INVALID,

    NVD_ERR_TCP                 = 0xF0001700,   /**<  TCPͨ�Ų������� */
    NVD_ERR_TCP_OVERMAXCONNECT,                 /**<  �ѳ���TCP���������� */
    NVD_ERR_TCP_NOMATCH,                        /**<  ����socket����ʧ�� */
    NVD_ERR_TCP_REUSEADDR,                      /**<  ����socket����ʧ�� */
    NVD_ERR_TCP_SNDBUF,                         /**<  ����socket����ʧ�� */
    NVD_ERR_TCP_RCVBUF,                         /**<  ����socket����ʧ�� */
    NVD_ERR_TCP_KEEPALIVE,                      /**<  ����socket����ʧ�� */
    NVD_ERR_TCP_KEEPIDLE,                       /**<  ����socket����ʧ�� */
    NVD_ERR_TCP_KEEPINTVL,                      /**<  ����socket����ʧ�� */
    NVD_ERR_TCP_KEEPCNT,                        /**<  ����socket����ʧ�� */

    NVD_ERR_UDP                 = 0xF0001800,   /**<  UDPͨ�Ų������� */

    NVD_ERR_IVA                 = 0xF0001900,   /**<  ����ģ����� */
    NVD_ERR_QLY                 = 0xF0002000,   /**<*/

    NVD_ERR_UNI_SEQ             =0xF0002100,    /**< ���кŴ���*/
    NVD_ERR_UNI_LEN,                            /**< ���ݳ��ȴ���*/

    NVD_ERR_PT_UNINITED         =0xF0002200,    /**< NVDPT��δ��ʼ��*/
    NVD_ERR_DEVICE_UNINITED,                    /**< NVDDEVICE��δ��ʼ��*/
    NVD_ERR_DAEMON              =0xF0002300,    /**< DAEMON�ػ�����ģ����� */

    NVD_ERR_PLAYBACK            =0xF0002400,    /**< �طŴ���*/
	NVD_ERR_PLAYBACK_BUSY,						/**< ���ڲ���ʱ�����ܽ����������� */

	NVD_ERR_CAPTURE_NOMOREFILE = 0xF0002500,

    NVD_ERR_ILL
}NVD_ERROR_NUM;


#define MAX_VIDEO_IN_NUM            8
#define MAX_ALARM_OUT_NUM           4


#define NVD_TEXT_OSD_NUM_PEER       2       /**<  ÿһ·��Ƶ���֧�ֵĵ��ӵ�osd�ַ����� */
#define NVD_MASK_NUM_PEER           4       /**<  ÿһ·��Ƶ���֧�ֵ��ڵ����� */
#define NVD_WARD_MAX_DAY            7       /**<  ÿһ·��Ƶ���Ĳ���ʱ������ */
#define NVD_WARD_TIME_NUM_PEER      4       /**<  ÿһ·��Ƶÿ��Ĳ���ʱ����� */


#define NVD_MAX_USER_NAME_LEN       16      /**<  �û�����󳤶� */
#define NVD_MAX_PASSWORD_LEN        16      /**<  ������󳤶� */
#define NVD_OSD_LEN                 128     /**<  ����OSD��ʾ�ַ����� ����64 */
#define NVD_STRING_LEN              32      /**<  �ַ������� */
#define NVD_UUID_LEN                64      /**<  uuid�ַ������� */
#define NVD_MAX_EMAIL_LEN           128     /**<  Email ������󳤶�*/

#define NVD_INVALID_HANDLE          -1      /**<  ��Ч���,���ڵ�¼�Ͳ��ŷ��� */

#define MAX_VIDEOFRAME_LENGTH       (1024*1024)  /**<  ��Ƶ��֡��󳤶� */
#define MAX_AUDIOFRAME_LENGTH       0x00F00      /**<  ��Ƶ��֡��󳤶� */
#define JPEG_MAX_PACKET_BUFF        0x500000

typedef enum
{
    NVD_LANGUAGE_CHINESE,               /**<  ���� */
    NVD_LANGUAGE_ENGLISH,               /**<  Ӣ�� */
    NVD_LANGUAGE_TLL                    /**<  �Ƿ����� */
}NVD_LANGUAGE_TYPE;

typedef enum
{
    NVD_CATEGORY_IPC,                 /**<  ����ǹ������� */
    NVD_CATEGORY_IPC_PTZ,             /**<  һ�廯������������� */
    NVD_CATEGORY_AUDIO,               /**<  ����Ƶ�豸 */
    NVD_CATEGORY_ILL                  /**<  �Ƿ����� */
}NVD_DEV_CATEGORY;

typedef enum
{
    USER_LEVEL_ADMIN = 0,             /**<  ����Ա�û������Ը����豸���ã����Խ����û�������ID�̶� */
    USER_LEVEL_RESERVE,               /**<  �����û�,���ڱ���socketͨ�� */
    USER_LEVEL_NORMAL,                /**<  һ���û� */
}NVD_USER_LEVEL;

typedef enum
{
    NVD_NETMODEL_TCP = 0,             /**<  TCP��ʽ */
    NVD_NETMODEL_UDP,                 /**<  UDP��ʽ */
}NVD_NETMODEL;

typedef enum
{
    NVD_VIDEO_TYPE_H264_BASELINE_PROFILE = 0, /**<  H.264����baseprofile */
    NVD_VIDEO_TYPE_H264_MAIN_PROFILE,         /**<  H.264����mainprofile */
    NVD_VIDEO_TYPE_H264_HIGH_PROFILE,         /**<  H.264����highprofile */
    NVD_VIDEO_TYPE_ILL                        /**<  �Ƿ����� */
}NVD_VIDEO_TYPE;

typedef enum
{
    NVD_IVA_TYPE_RESULT = 80,
    NVD_IVA_TYPE_ILL                  /**<  �Ƿ����� */
}NVD_IVA_TYPE;

typedef enum
{
    ENC_FORMAT_SINGLE = 0,            /**<  ������ */
    ENC_FORMAT_DOUBLE,                /**<  ˫���� */
    ENC_FORMAT_ILL                    /**<  �Ƿ����� */
}NVD_ENC_FORMAT;

typedef enum
{
    ENC_STREAM_TYPE_MAIN = 0,         /**<  ���� */
    ENC_STREAM_TYPE_SUB,              /**<  ���� */
    ENC_STREAM_TYPE_IVA,              /**<  ���� */
    ENC_STREAM_TYPE_MAIN_IVA,         /**<  ����&���� */
    ENC_STREAM_TYPE_SUB_IVA,          /**<  ����&���� */
    ENC_STREAM_TYPE_ILL               /**<  �Ƿ����� */
}NVD_ENC_STREAM_TYPE;

typedef enum
{
    ENC_ADV_DN_LEVEL_CLEAREST = 0,      /**<  ������ */
    ENC_ADV_DN_LEVEL_CLEAR,             /**<  ������ */
    ENC_ADV_DN_LEVEL_MEDIUM ,           /**<  ����   */
    ENC_ADV_DN_LEVEL_BLUR,              /**<  ����� */
    ENC_ADV_DN_LEVEL_BLUREST,           /**<  ����� */
    ENC_ADV_DN_LEVEL_ILL
}NVD_ENC_ADV_DN_LEVEL;

typedef enum
{
    ENC_ADV_DAYTIME = 0,                /**<  ����ģʽ */
    ENC_ADV_NIGHT,                      /**<  ҹ��ģʽ */
    ENC_ADV_ILL
}NVD_ENC_ADV_MODE;

typedef enum
{
    IMG_AE_MODE_AUTO = 0,               /**<  �Զ��ع� */
    IMG_AE_MODE_MAN,                    /**<  �ֶ��ع� */
    IMG_AE_MODE_ILL
}NVD_IMG_AE_MODE;

typedef enum
{
    IMG_AWB_MODE_AUTO     = 0,          /**<  �Զ���ƽ�� */
    IMG_AWB_MODE_MAN,                   /**<  �ֶ���ƽ�� */
    IMG_AWB_MODE_MODE_ILL
}NVD_IMG_AWB_MODE;

typedef enum
{
    IMG_CCM_MODE_MID     = 0,           /**<  ����ɫ�� */
    IMG_CCM_MODE_WARM,                  /**<  ůɫ�� */
    IMG_CCM_MODE_CALM,                  /**<  ��ɫ�� */
    IMG_CCM_MODE_MODE_ILL
}NVD_IMG_CCM_MODE;

typedef enum
{
    IMG_IRIS_MODE_AUTO     = 0,         /**<  �Զ���Ȧ */
    IMG_IRIS_MODE_MAN,                  /**<  �ֶ���Ȧ */
    IMG_IRIS_MODE_MODE_ILL
}NVD_IMG_IRIS_MODE;

typedef enum
{
    IMG_MODE_AUTO = 0,                  /**<  �Զ�ģʽ */
    IMG_MODE_COLOR,                     /**<  ��ɫģʽ */
    IMG_MODE_BW,                        /**<  �ڰ�ģʽ */
    IMG_MODE_ILL
}NVD_IMG_COLOR_MODE;

typedef enum
{
    IMG_MIRROR_MODE_OFF     = 0,        /**<  �����ܹر� */
    IMG_MIRROR_MODE_VER,                /**<  ��ֱ��ת */
    IMG_MIRROR_MODE_HOR,                /**<  ˮƽ��ת */
    IMG_MIRROR_MODE_ROTATE,             /**<  ��ת*/
    IMG_MIRROR_MODE_MODE_ILL
}NVD_IMG_MIRROR_MODE;

typedef enum
{
    IMG_DENOISE_MODE_AUTO = 0,          /**<  �Զ�ȥ�� */
    IMG_DENOISE_MODE_MAN,               /**<  �ֶ�ȥ�� */
    IMG_DENOISE_MODE_OFF,               /**<  �ر�ȥ�� */
    IMG_DENOISE_MODE_ILL
}NVD_IMG_DENOISE_MODE;

typedef enum
{
    IMG_ANTIFOG_MODE_OFF     = 0,       /**<  ȥ��ر� */
    IMG_ANTIFOG_MODE_ON,                /**<  ȥ��� */
    IMG_ANTIFOG_MODE_MODE_ILL
}NVD_IMG_ANTIFOG_MODE;

typedef enum
{
    IMG_SHADING_MODE_OFF     = 0,       /**<  ����У���ر� */
    IMG_SHADING_MODE_ON,                /**<  ����У���� */
    IMG_SHADING_MODE_MODE_ILL
}NVD_IMG_SHADING_MODE;

typedef enum
{
    IMG_SHARPEN_MODE_AUTO = 0,          /**<  ��Ե���Զ� */
    IMG_SHARPEN_MODE_MAN,               /**<  ��Ե���ֶ� */
    IMG_SHARPEN_MODE_OFF,               /**<  ��Ե�񻯹ر� */
    IMG_SHARPEN_MODE_ILL
}NVD_IMG_SHARPEN_MODE;

typedef enum
{
    IMG_WB_MODE_OFF = 0,                /**<  ��̬�� */
    IMG_WB_MODE_ON,                     /**<  ��̬�� */
    IMG_WB_MODE_ILL
}NVD_IMG_WB_MODE;

typedef enum
{
    IMG_DIS_MODE_OFF     = 0,           /**<  �����ر� */
    IMG_DIS_MODE_ON,                    /**<  ������ */
    IMG_DIS_MODE_MODE_ILL
}NVD_IMG_DIS_MODE;

typedef enum
{
    IMG_BLC_MODE_OFF     = 0,           /**<  ���ⲹ���ر� */
    IMG_BLC_MODE_ON,                    /**<  ���ⲹ���� */
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

#define HD720P_WIDTH   1280           /**<  100�� */
#define HD720P_HEIGHT  720

#define HD900P_WIDTH   1600           /**<  130�� */
#define HD900P_HEIGHT  912

#define HD1080P_WIDTH   1920          /**<  200�� */
#define HD1080P_HEIGHT  1080

#define QVGA_WIDTH  320
#define QVGA_HEIGHT 240

#define VGA_WIDTH  640
#define VGA_HEIGHT 480

#define SVGA_WIDTH  800
#define SVGA_HEIGHT 600

#define XGA_WIDTH  1024
#define XGA_HEIGHT 768

#define SXGA_WIDTH  1280              /**<  130�� */
#define SXGA_HEIGHT 1024

#define UXGA_WIDTH  1600              /**<  200�� */
#define UXGA_HEIGHT 1200

#define HD3M_WIDTH  2048              /**<  300�� */
#define HD3M_HEIGHT 1536

#define HD5M_WIDTH  2592              /**<  500�� */
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
    ENC_IMG_TYPE_ILL                  /**<  �Ƿ��ֱ��� */
}NVD_ENC_IMG_TYPE;

typedef enum
{
    NVD_AUDIO_TYPE_ADPCMA = 64,       /**<  ADPCMA ��֧��*/
    NVD_AUDIO_TYPE_AMR,               /**<  AMR ��֧��*/
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
	NVD_RECORD_ERROR_MEM_SETUP = 0x01, /**< �ڴ��ʼ��ʧ�� */
	NVD_RECORD_ERROR_OUTOF_MEM = 0x02, /**< �ڴ治�� */
	NVD_RECORD_ERROR_THINNER_MEM   = 0x04, /**< �ڴ治���� */
	NVD_RECORD_ERROR_WRITE     = 0x08, /**< �ļ�д����� */
	NVD_RECORD_ERROR_READ      = 0x10, /**< ��ȡ�ļ����� */
	NVD_RECORD_ERROR_OPEN_FILE = 0x20, /**< ���ļ�ʧ�� */
	NVD_RECORD_ERROR_ILL
}NVD_RECORD_ERROR;

typedef enum
{
    NVD_ALARM_TYPE_IN = 0,            /**<  ��������澯*/
    NVD_ALARM_TYPE_MD,                /**<  �ƶ����澯*/
    NVD_ALARM_TYPE_OD,                /**<  �ڵ����澯*/
    NVD_ALARM_TYPE_ST,                /**<  ����ת�����澯*/
	NVD_ALARM_TYPE_SD,                /**<  SD���¼�(value��NVD_SD_STATUS)*/
	NVD_ALARM_TYPE_RECORD_ERR,        /**<  SD��¼����󱨾�(value��NVD_RECORD_ERROR)*/
    NVD_ALARM_TYPE_ILL
}NVD_ALARM_TYPE; 

typedef struct
{
    NVD_ALARM_TYPE      alarmType;
    int                 chn;
    char                name[NVD_STRING_LEN];  /**<  ���� */
    int                 value;

    unsigned char       res[32];               /**<  ���� */
}NVD_ALARM_REPORT_INFO;

typedef struct
{
    int                 chn;                   /**<  ͨ�� */
    int                 panValue;              /**<  panֵ */
    int                 tiltValue;             /**<  tiltֵ */

    unsigned char       res[32];               /**<  ���� */
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
    int                 isUsed;                /**<  �Ƿ����� */

    unsigned short      xPos;
    unsigned short      yPos;

    unsigned short      width;                 /**<  ���ڿ�� */
    unsigned short      height;                /**<  ���ڸ߶� */
}NVD_AREA_RECT;

typedef struct
{
    int                 isUsed;                /**<  �Ƿ����� */

    unsigned char       beginHour;
    unsigned char       beginMinute;
    unsigned char       endHour;
    unsigned char       endMinute;
}NVD_TIME_RECT;

typedef struct
{
    /**
    *��һ�������������������֣���һ���ֶ�����Ҫ������Ϣ��
    */
    /**
    *0x00: ����Ӧ
    *0x01: �ϴ�����(��Ҫ���ñ�������)
    *0x02: �������Ͼ���(��֧��)
    *0x04: ��������(��֧��)
    *0x08: Jpegץͼ���ϴ�EMail(��֧��)
    *0x10: �ʼ�
    */
    unsigned int        type;                              /**<  ���� */

    /**
    *�ڶ��������ڸ澯�������
    */
    unsigned char       alarmOut[MAX_ALARM_OUT_NUM];       /**< 1��ʾ������ͨ��, ������0 */

    /**
    *����������������¼�񲿷�
    */
    unsigned char       recordChan[MAX_VIDEO_IN_NUM];      /**< 1��ʾ������ͨ��, ������0 */

    /**
    *���Ĳ�����������ptz����
    */
    unsigned char       isEnablePreset[MAX_VIDEO_IN_NUM];  /**<  �Ƿ����Ԥ�õ�*/
    unsigned char       presetId[MAX_VIDEO_IN_NUM];        /**<  Ԥ�õ�id*/
    unsigned char       isEnableCruise[MAX_VIDEO_IN_NUM];  /**<  �Ƿ����Ѳ��*/
    unsigned char       cruiseId[MAX_VIDEO_IN_NUM];        /**<  Ѳ��id*/
    unsigned char       isEnableTrack[MAX_VIDEO_IN_NUM];   /**<  �Ƿ���ù켣*/
    unsigned char       trackId[MAX_VIDEO_IN_NUM];         /**<  �켣id*/
    unsigned char       res[32];                           /**<  ���� */
}NVD_HANDLE_LINKAGE;

typedef struct
{
    unsigned int        ip;                         /**<  С�ֽ��� */
    unsigned int        netmask;                    /**<  С�ֽ��� */
    unsigned int        gateway;                    /**< С�ֽ��� */
    unsigned char       mac[6];
    unsigned char       isDhcp;                     /**<  Ŀǰ��֧�� ��0 */
    unsigned char       res;                        /**<  ���� */

    unsigned int        webPort;                    /**<  �豸web�˿ں� */
    unsigned int        dataUdpPort;                /**<  �豸UDP�������˿ں�*/
    unsigned int        dataTcpPort;                /**<  �豸TCP�������˿ں�*/

    unsigned char       res1[52];                   /**<  ���� */

    char                devSn[NVD_STRING_LEN];      /**<  �豸���к� */
    char                hwVer[NVD_STRING_LEN];      /**<  Ӳ���汾�� */
    char                swVer[NVD_STRING_LEN];      /**<  ����汾�� */

    NVD_DEV_CATEGORY    devCategory;                /**<  �豸���� */
    unsigned int        devType;                    /**<  �豸���� */

    unsigned char       res2[64];                   /**<  ���� */
}NVD_SEARCH_PARA;

typedef struct
{
    unsigned int        ip;                         /**<  С�ֽ��� */
    unsigned int        netmask;                    /**<  С�ֽ��� */
    unsigned int        gateway;                    /**<  С�ֽ��� */
    unsigned char       mac[6];
    unsigned char       isDhcp;                     /**<  Ŀǰ��֧�� ��0 */
}NVD_NET_PARA;

typedef struct
{
    unsigned int        webPort;                    /**<  �豸web�˿ں� */
    unsigned int        dataUdpPort;                /**<  �豸udp�������˿ں� */
    unsigned int        dataTcpPort;                /**<  �豸TCP�������˿ں� */
    unsigned int        rtspPort;                   /**<  rtsp�������˿ں� */
    unsigned int        alarmHostIpAddr;            /**<  ��������ip��ַ */
    unsigned int        alarmHostPort;              /**<  ���������˿ں� */
    unsigned int        multicastAddr;              /**<  �鲥  ip��ַ */
    unsigned int        multicastPort;              /**<  �鲥  ip �˿� */
    unsigned char       uuid[64];                   /**<  uuid */
    unsigned int        dns1;                       /**<  DNS1 */
    unsigned int        dns2;                       /**<  DNS2 */    

    unsigned char       res[252];                   /**<  ���� */
}NVD_NET_2_PARA;

typedef struct
{
    int                 isUsed;                     /**<  �Ƿ����� */
    char                ip[32];                     /**<  ������ip */
    unsigned int        port;                       /**<  �������˿� */
    unsigned int        interval;                   /**<  Уʱ��� */
    int                 timezone;                   /**<  ʱ�� */
   
    unsigned char       res1[32];                   /**<  ���� */
}NVD_NTP_PARA;

typedef struct
{
    int                 isUsed;                     /**<  �Ƿ����� */
    char                smtpip[32];                 /**<  smtp������ */
    unsigned int        smtpport;                   /**<  smtp�˿� */
    char                username[NVD_STRING_LEN];   /**<  �û��� */
    char                password[NVD_STRING_LEN];   /**<  ���� */
    char                sendAddr[NVD_STRING_LEN];   /**<  ���͵�ַ */
    char                recvAddr_1[NVD_STRING_LEN]; /**<  ���յ�ַ1 */
    char                recvAddr_2[NVD_STRING_LEN]; /**<  ���յ�ַ2 */
    char                recvAddr_3[NVD_STRING_LEN]; /**<  ���յ�ַ3 */
}NVD_EMAIL_PARA;

typedef struct
{
    int                 isSnmpUsed;                 /**<  �Ƿ�����snmp���� */
    char                snmpReadCommunity[32];      /**<  read community */
    unsigned char       res[256];                   /**<  ���� */
}NVD_SNMP_PARA; 

typedef struct
{
    char                username[NVD_MAX_USER_NAME_LEN];  /**<  �û��� */
    char                password[NVD_MAX_PASSWORD_LEN];   /**<  ���� */
    unsigned int        level;                            /**<  �û����� */
    unsigned int        privilege;                        /**<  �û�Ȩ�� */
}NVD_USER_PARA;

typedef struct
{
    NVD_DEV_CATEGORY    devCategory;                /**<  �豸���࣬����ǹ��������� */
    unsigned int        devType;                    /**<  �豸����, ��˾ÿһ���Ʒ����һ��Ψһ�����ͱ�� */
    char                devName[NVD_STRING_LEN];    /**<  �豸���� */

    unsigned char       videoInNum;                 /**<  ��Ƶ����ͨ������ */
    unsigned char       videoOutNum;                /**<  ��Ƶ���ͨ������ */
    unsigned char       audioInNum;                 /**<  ��Ƶ������� */
    unsigned char       audioOutNum;                /**<  ��Ƶ������� */
    char                channelName[MAX_VIDEO_IN_NUM][NVD_STRING_LEN];    /**<  ͨ������ */

    unsigned char       alarmInNum;
    unsigned char       alarmOutNum;
    unsigned char       comNum;
    unsigned char       res;                        /**<  ���� */
    unsigned int        version;                    /**<  ����汾�� */
    unsigned char       res1[28];                   /**<  ���� */
}NVD_LOGIN_INFO;

typedef struct
{
    char                devSn[NVD_STRING_LEN];      /**<  �豸���к� */
    char                hwVer[NVD_STRING_LEN];      /**<  Ӳ���汾�� */
    char                swVer[NVD_STRING_LEN];      /**<  ����汾�� */

    NVD_DEV_CATEGORY    devCategory;                /**<  �豸���� */
    unsigned int        devType;                    /**<  �豸���� */
    char                devName[NVD_STRING_LEN];    /**<  �豸����            ����������� */
    char                typeName[NVD_STRING_LEN];   /**<  �������� */

    unsigned char       videoInNum;                 /**<  ��Ƶ����ͨ������ */
    unsigned char       videoOutNum;                /**<  ��Ƶ���ͨ������ */
    unsigned char       audioInNum;                 /**<  ��Ƶ������� */
    unsigned char       audioOutNum;                /**<  ��Ƶ������� */ 

    unsigned char       alarmInNum;                 /**<  �澯������� */
    unsigned char       alarmOutNum;                /**<  �澯������� */
    unsigned char       comNum;                     /**<  ���ڸ��� */
    unsigned char       res[33];
}NVD_DEV_PARA;

typedef struct
{
    int                 viNo;                       /**<  ��ǰ��������һ��ͨ���� */

    NVD_VIDEO_TYPE      videoType;
    NVD_ENC_FORMAT      encFormat;                  /**<  ������or˫���� */

    NVD_ENC_IMG_TYPE    encImgTypeMain;             /**<  �����ֱ��ʸ�ʽ��4cif or h4cif or cif */
    unsigned int        imgTypeMainMask;            /**<  �����ֱ���֧�����͵�mask */
    NVD_ENC_IMG_TYPE    encImgTypeSub;              /**<  �����ֱ��ʸ�ʽ��4cif or h4cif or cif */
    unsigned int        imgTypeSubMask;             /**<  �����ֱ���֧�����͵�mask */

    unsigned short      bitrateMain;                /**<  ������Ƶ���� 16-10240*/
    unsigned char       qualityMain;                /**<  ������Ƶ��������0-5 */
    unsigned char       fpsMain;                    /**<  ������Ƶ֡�� 2-25*/
    unsigned char       idrMain;                    /**<  ����I֡���2-250 */
    unsigned char       isCbrMain;                  /**<  CBR/VBR */

    unsigned short      bitrateSub;                 /**<  ������Ƶ���� 16-10240*/
    unsigned char       qualitySub;                 /**<  ������Ƶ�������� 0-5*/
    unsigned char       fpsSub;                     /**<  ������Ƶ֡�� 2-25*/
    unsigned char       idrSub;                     /**<  ����I֡��� 2-250*/
    unsigned char       isCbrSub;                   /**<  CBR/VBR */

    unsigned char       res[32];
}NVD_VIDEO_ENC_PARA;

typedef struct
{
    int                 viNo;                       /**<  ��ǰ��������һ��ͨ���� */
    
    unsigned char       denoiseDay;                 /**<  ������Ƶ���� 0-255 */
    unsigned char       sharpenDay;                 /**<  ������Ƶ�� 0-255 */
    
    unsigned char       denoiseNight;               /**<  ҹ����Ƶ���� 0-255 */
    unsigned char       sharpenNight;               /**<  ҹ����Ƶ�� 0-255 */

    unsigned char       res[32];
}NVD_VIDEO_ENC_ADV_PARA;

typedef struct
{
    int                     viNo;                   /**<  ��ǰ��������һ��ͨ���� */

    NVD_ENC_ADV_DN_LEVEL    encAdvDnLevel;          /**<  �豸��Ƶ���뼶�� */
    NVD_ENC_ADV_MODE        encAdvMode;             /**<  �豸��Ƶ����ģʽ (����ģʽ/ҹ��ģʽ) */

    unsigned char           res[32];
}NVD_ENC_ADV_MODE_PARA;

typedef struct
{
    int                 viNo;                       /**<  ��ǰ��������һ��ͨ���� */

    unsigned char       brightness;                 /**<  ����        0-255 */
    unsigned char       contrast;                   /**<  �Աȶ�      0-255 */
    unsigned char       saturation;                 /**<  ���Ͷ�      0-255 */
    unsigned char       hue;                        /**<  ɫ��        0-255 */

    unsigned char       res[44];
}NVD_IMAGE_PARA;

typedef struct
{
    int                 viNo;                       /**<  ��ǰ��������һ��ͨ���� */

    NVD_IMG_AE_MODE      aeMode;                    /**<  �ع�ģʽ*/
    NVD_IMG_AWB_MODE     awbMode;                   /**<  ��ƽ��ģʽ*/
    unsigned int         wbr;                       /**<  �ֶ���ƽ��ģʽ r 0-255 */
    unsigned int         wbg;                       /**<  �ֶ���ƽ��ģʽ g 0-255 */
    unsigned int         wbb;                       /**<  �ֶ���ƽ��ģʽ b 0-255 */

    NVD_IMG_CCM_MODE     colorCCM;                  /**<  ɫ��ģʽ*/

    NVD_IMG_IRIS_MODE    irisMode;                  /**<  ��Ȧ����ģʽ*/
    unsigned int         iris;                      /**<  �Զ���Ȧ����0-15 */
    unsigned int         agc;                       /**<  ����ģʽ  0-255 */
    unsigned int         shutterSpeed;              /**<  �����ٶ� 0-15  */
    unsigned int         sense;                     /**<  ��ȵ��� 0-16  */
    NVD_IMG_COLOR_MODE   colorMode;                 /**<  ɫ��ģʽ*/
    NVD_IMG_MIRROR_MODE  mirrorMode;                /**<  ����ģʽ*/
    NVD_IMG_DENOISE_MODE denoiseMode;               /**<  ȥ��ģʽ*/
    NVD_IMG_ANTIFOG_MODE antifogMode;               /**<  ȥ��ģʽ*/
    NVD_IMG_SHADING_MODE shadingMode;               /**<  ����У��ģʽ*/
    NVD_IMG_SHARPEN_MODE sharpenMode;               /**<  ��Ե��ģʽ*/
    NVD_IMG_WB_MODE      wbMode;                    /**<  ��̬ģʽ*/
    NVD_IMG_DIS_MODE     disMode;                   /**<  ����ģʽ */
    NVD_IMG_BLC_MODE     blcMode;                   /**<  ���ⲹ��ģʽ */

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
    NVD_DISPLAY_YYYY_MM_DD_WEEKDATE_HH_MM_SS,       /**<  0: YYYY-MM-DD ����X HH:MM:SS*/
    NVD_DISPLAY_DD_MM_YYYY_WEEKDATE_HH_MM_SS,       /**<  1: DD-MM-YYYY WEEKDATE HH:MM:SS       Ӣʽ */
    NVD_DISPLAY_MM_DD_YYYY_WEEKDATE_HH_MM_SS,       /**<  2: MM-DD-YYYY WEEKDATE HH:MM:SS       ��ʽ */
    NVD_DISPLAY_YYYY_MM_DD_WEEKDATE_HH_MM_SS_1,     /**<  3: YYYY��MM��DD�� ����X HHʱMM��SS��  */

    NVD_DISPLAY_YYYY_MM_DD_HH_MM_SS,                /**<  4: YYYY-MM-DD  HH:MM:SS */
    NVD_DISPLAY_DD_MM_YYYY_HH_MM_SS,                /**<  5: DD-MM-YYYY  HH:MM:SS               Ӣʽ */
    NVD_DISPLAY_MM_DD_YYYY_HH_MM_SS,                /**<  6: MM-DD-YYYY  HH:MM:SS               ��ʽ */
    NVD_DISPLAY_YYYY_MM_DD_HH_MM_SS_1,              /**<  7: YYYY��MM��DD�� HHʱMM��SS�� */
    NVD_DISPLAY_TYPE_TIME_ILL
}NVD_DISPLAY_TYPE_TIME;

typedef struct
{
    int                 viNo;                       /**<  ��ǰ��������һ��ͨ���� */

    /**
    *ͨ����������
    */
    int                 isShow_name;                /**<  �Ƿ���ʾ */
    unsigned short      xPos_name;                  /**<  X���� �����ֵĿ� */
    unsigned short      yPos_name;                  /**<  Y���� �����ֵĸ� */
    RGB_QUAD            fg_color_name;              /**<  ǰ����ɫ */
    RGB_QUAD            bg_color_name;              /**<  ������ɫ */
    unsigned char       fg_alpha_name;              /**<  ǰ��͸���� 0-128 */
    unsigned char       bg_alpha_name;              /**<  ����͸���� 0-128 */
    unsigned char       res[2];
    int                 isInvColor_name;            /**<  �Ƿ�ɫ */
    int                 invColorThresh_name;        /**<  ��ɫ������ֵ 0-255 */
    char                channelName[NVD_STRING_LEN];   /**<  ͨ������ */
    unsigned char       size_name;                  /**<  �����С0-5    0Ϊ�Զ� */
    unsigned char       res1[3];

    /**
    *ʱ������
    */
    int                 isShow_time;                /**<  �Ƿ���ʾ */
    NVD_DISPLAY_TYPE_TIME   disType_time;
    unsigned short      xPos_time;                  /**<  OSD X���� */
    unsigned short      yPos_time;                  /**<  OSD Y���� */
    RGB_QUAD            fg_color_time;              /**<  ǰ����ɫ */
    RGB_QUAD            bg_color_time;              /**<  ������ɫ */
    unsigned char       fg_alpha_time;              /**<  ǰ��͸���� 0-128 */
    unsigned char       bg_alpha_time;              /**<  ����͸���� 0-128 */
    unsigned char       size_time;                  /**<  �����С0-5    0Ϊ�Զ� */
    unsigned char       res2;

    int                 isInvColor_time;            /**<  �Ƿ�ɫ */
    int                 invColorThresh_time;        /**<  ��ɫ������ֵ 0-255 */
}NVD_DISPLAY_PARA;

typedef struct
{
    int                 isShow;                     /**< �Ƿ���ʾ */

    unsigned short      xPos;                       /**<  X���� */
    unsigned short      yPos;                       /**<  Y���� */
    RGB_QUAD            fg_color;                   /**<  ǰ����ɫ */
    RGB_QUAD            bg_color;                   /**<  ������ɫ */
    unsigned char       fg_alpha;                   /**<  ǰ��͸���� 0-128 */
    unsigned char       bg_alpha;                   /**<  ����͸���� 0-128 */
    unsigned char       res[2];

    int                 isInvColor;                 /**<  �Ƿ�ɫ */
    int                 invColorThresh;             /**<  ��ɫ������ֵ 0-255 */

    char                osdChar[NVD_OSD_LEN];       /**<  �ַ��� */
    unsigned char       size;                       /**<  �����С0-5  0Ϊ�Զ� */

    unsigned char       res1[3];
}TEXT_OSD_PARA;

typedef struct
{
    int                 viNo;                       /**<  ��ǰ��������һ��ͨ���� */

    TEXT_OSD_PARA       textOsd[NVD_TEXT_OSD_NUM_PEER];

    unsigned char       res[16];
}NVD_TEXT_OSD_PARA;


/************************************************************************************/

#define MASK_WIDTH      1000
#define MASK_HEIGHT     1000
typedef struct
{
    int                 viNo;                           /**<  ��ǰ��������һ��ͨ���� */

    NVD_AREA_RECT       area[NVD_MASK_NUM_PEER];        /**<  �������������1000 X 1000 ��һ������ */
    NVD_TIME_RECT       time[NVD_WARD_MAX_DAY][NVD_WARD_TIME_NUM_PEER];  /**<  ����ʱ�� */

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

#define MD_WARNING_DELAY     3                          /**<  �澯��ʱʱ�� */
typedef struct
{
    int                 viNo;                           /**<  ��ǰ��������һ��ͨ���� */
    int                 isUsed;                         /**<  �Ƿ����� */

    NVD_HANDLE_LINKAGE  linkage;                        /**<  �������� */

    unsigned char       area[MD_WIDTH*MD_HEIGHT];       /**<  �����ܹ���4 X 3������ */
                                                        /**<  �����Ӧ������Ҫ������⣬��ô��Ӧ������Ϊ1, ������Ϊ0 */

    NVD_TIME_RECT       time[NVD_WARD_MAX_DAY][NVD_WARD_TIME_NUM_PEER];   /**<  ����ʱ�� */
    char                name[NVD_STRING_LEN];                             /**<  ���� */

    unsigned char       level;                          /**<  �ƶ���������� 0-5, Խ��Խ���� MD_MAX_LEVEL */

    unsigned char       res[19];
}NVD_MD_PARA;

#define OD_MAX_LEVEL    5
#define MAX_OD_AREA     4
typedef struct
{
    int                 viNo;          /**<  ��ǰ��������һ��ͨ���� */
    int                 isUsed;        /**<  �Ƿ����� */

    NVD_HANDLE_LINKAGE  linkage;        /**<  �������� */

    NVD_AREA_RECT       area[MAX_OD_AREA];       /**<  �����ܹ���4������ */
    NVD_TIME_RECT       time[NVD_WARD_MAX_DAY][NVD_WARD_TIME_NUM_PEER];   /**<  ����ʱ�� */
    char                name[NVD_STRING_LEN];  /**<  ���� */

    unsigned char       level;           /**<  �ڵ���������� 0-5, Խ��Խ���� OD_MAX_LEVEL */

    unsigned char       res[19];
}NVD_OD_PARA;

#define ST_MAX_LEVEL    5
typedef struct
{
    int                 viNo;          /**<  ��ǰ��������һ��ͨ���� */
    int                 isUsed;        /**<  ����ת���Ƿ����� */

    NVD_HANDLE_LINKAGE  linkage;        /**<  �������� */

    NVD_TIME_RECT       time[NVD_WARD_MAX_DAY][NVD_WARD_TIME_NUM_PEER];   /**<  ����ʱ�� */
    char                name[NVD_STRING_LEN];  /**<  ���� */

    unsigned char       level;           /**<  ����ת�������� 0-5, Խ��Խ���� */

    unsigned char       res[15];
}NVD_ST_PARA;


typedef struct
{
    int                 viNo;           /**<  ��ǰ��������һ��ͨ���� */
    int                 isUsed;         /**<  �Ƿ����� */
    int                 interval;       /**<  ͼƬ�洢��� 10-3600s */
    int                 quality;        /**<  ͼƬ���� 1-99 */
    NVD_TIME_RECT       time[NVD_WARD_MAX_DAY][NVD_WARD_TIME_NUM_PEER];       /**<  ͼƬ�洢ʱ��� */

    unsigned char       res[16];
}NVD_SNAP_PARA;

typedef struct
{
    int                 viNo;           /**<  ��ǰ��������һ��ͨ���� */
    int                 isUsed;         /**<  �Ƿ�����¼�� */
    int                 isIFrameOnly;   /**<  �Ƿ�ֻ����I֡ */
    NVD_ENC_STREAM_TYPE typeStream;     /**<  �����������Ǵ��� */
    int                 mins;           /**<  ¼��ʱ�䳤�� (����) */
    NVD_TIME_RECT       time[NVD_WARD_MAX_DAY][NVD_WARD_TIME_NUM_PEER];       /**<  ¼��洢ʱ��� */

    int                 isOfflineSave;  /**<  �Ƿ����õ��߱���¼�� */

    unsigned char       res[64];
}NVD_REC_PARA;

typedef enum{
    PLAYBACK_SPEED_HALF = 0,        /* ����֮һ���ٻط� */
    PLAYBACK_SPEED_NORMAL,          /* �����ط� */
    PLAYBACK_SPEED_DOUBLE,          /* �����ٻط� */
    PLAYBACK_SPEED_FULL,            /* ȫ�ٻط� */
    PLAYBACK_SPEED_REWIND,          /* ���� */

    PLAYBACK_SPEED_ILL
}NVD_REC_PLAYBACK_SPEED;

typedef struct{
    unsigned int isUsed;            /* �Ƿ�����¼��ط� */
    NVD_REC_PLAYBACK_SPEED speed;   /* ¼��ط��ٶ� */
    NVD_TIME timeStart;             /* ¼��ط���ʼʱ�� */
    NVD_TIME timeEnd;               /* ¼��طŽ�ֹʱ�� */
    unsigned char res[64];
}NVD_REC_PLATBACK_PARA;

#define NVD_REC_QUERY_RESULT_MAX   60
typedef struct
{
    NVD_TIME timeStart;             /* ¼��ʱ�����ʼʱ�� */
    NVD_TIME timeEnd;               /* ¼��ʱ��ν�ֹʱ�� */
    unsigned char fileName[NVD_STRING_LEN];
    unsigned int size;              /* ¼���ļ���С (��λ:Byte) */
}NVD_REC_QUERY_RESULT;

typedef struct{
    NVD_TIME timeStart;             /* ¼���ѯ��ʼʱ�� */
    NVD_TIME timeEnd;               /* ¼���ѯ��ֹʱ�� */
    NVD_REC_QUERY_RESULT  queryResult[NVD_REC_QUERY_RESULT_MAX];
    unsigned char res[128];    
}NVD_REC_QUERY_PARA;

typedef struct
{
    unsigned char       qp;       /**<  ͼ������[0, 255] */
    unsigned char       res[3];
    NVD_AREA_RECT       area;     /**<  ROI �����С */
    unsigned char       res2[8];
}ROI_AREA;

#define MAX_ROI_NUM    8
typedef struct
{
    int                 viNo;                   /**<  ��ǰ��������һ��ͨ���� */

    int                 isUsed;                 /**<  �Ƿ�����������ǿ */

    ROI_AREA            roiArea[MAX_ROI_NUM];   /**<  ROI�������� */
    
    unsigned char       res[64];
}NVD_ROI_PARA;

/************************************************************************************/

typedef struct
{
    int                 aiNo;              /**<  ��ǰ��������һ��ͨ���� */

    int                 isUsed;            /**<  �Ƿ����� */

    NVD_AUDIO_TYPE      type;              /**<  ��Ƶ�������� */
    NVD_AUDIO_SOUND_MODE    soundMode;     /**<  ��Ƶ�������������� */
    NVD_AUDIO_BIT_WIDTH     bitWidth;      /**<  ��Ƶ����λ�� */
    NVD_AUDIO_SAMPLE_RATE   sampleRate;    /**<  ��Ƶ������ */

    int                 volume;            /**<  ���� 0-128 */

    unsigned char       res[28];
}NVD_AUDIO_IN_PARA;

typedef struct
{
    int                 aoNo;              /**<  ��ǰ��������һ��ͨ���� */

    int                 isUsed;            /**<  �Ƿ����� */

    NVD_AUDIO_TYPE      type;              /**<  ��Ƶ�������� */
    NVD_AUDIO_SOUND_MODE    soundMode;     /**<  ��Ƶ�������������� */
    NVD_AUDIO_BIT_WIDTH     bitWidth;      /**<  ��Ƶ����λ�� */
    NVD_AUDIO_SAMPLE_RATE   sampleRate;    /**<  ��Ƶ������ */

    int                 volume;            /**<  ���� 0-128 */

    unsigned char       res[28];
}NVD_AUDIO_OUT_PARA;

/************************************************************************************/

/* ý��ͷ�Ľṹ */
typedef struct
{
    unsigned int syncflag:8;            /**<  ͬ��ͷ   */
    unsigned int headerType:4;          /**<  ý��ͷ��Ϣ����, Max type=15  */
    unsigned int dataSize:20;           /**<  ����֡�Ĵ�С,   Max size=1M-1  */

    unsigned int algorithm:7;           /**<  ý��ѹ����ʽ 0-63Ϊ��Ƶ, 0:��˼��h264, 64-79Ϊ��Ƶ, 80Ϊ����ʶ����,81Ϊ����ʶ���� ...*/
    unsigned int mediaType:3;           /**<  ��Ϊ��Ƶ,0-P frame, 1-I frame; ��Ϊ��Ƶ,���ʾ0-mono,1-stereo  */
    unsigned int resolution:6;          /**<  ��Ϊ��Ƶ,���ʾ�ֱ���;��Ϊ��Ƶ,���ʾ������  */
    unsigned int fps:8;                 /**<  ��Ϊ��Ƶ,���ʾ֡��;��Ϊ��Ƶ,���ʾλ��  */
    unsigned int idr:8;                 /**<  ��Ϊ��Ƶ,���ʾI֡���;��Ϊ��Ƶ,���� */

    unsigned int timeSec;               /**<  ��ǰ֡ʱ��(��λ1��);��ʾ�ӹ�Ԫ1970��1��1��0ʱ0��0�����������UTCʱ��������������  */

    unsigned int extInfo;               /**<  ��չ��Ϣ  */

    unsigned int checksum;              /**<  У���    */
}NVD_MEDIA_HEAD;

/* JPEGץ��ͼƬ�Ľṹ */
typedef struct
{
    unsigned int syncflag:8;            /**<  ͬ��ͷ   */
    unsigned int headerType:4;          /**<  ý��ͷ��Ϣ����, Max type=15  */
    unsigned int resolution:6;          /**<  �ֱ���*/
    unsigned int quality:14;            /**<  ͼ������(0~99)*/
    unsigned int dataSize;              /**<  ����֡�Ĵ�С*/

    unsigned int timeSec;               /**<  ץ��ͼƬʱ��(��λ1��);��ʾ�ӹ�Ԫ1970��1��1��0ʱ0��0�����������UTCʱ��������������  */

    /**<  extInfo  ��չ��Ϣ:
              1:����ץ������ʱ�����ø�λ�ж϶�������˭��������,
                     0ΪԶ������ǰ��ץ�ģ�1Ϊocx����ǰ��ץ��.
                ע��:ץ�������ʱ����Ҫ���timeSec����Ϊjpeg�ı�־
                     (���洦���Լ�����ֵ������Ӧ����)
    */
    unsigned int extInfo;               

    unsigned int checksum;              /**<  У���    */
}NVD_JPEG_HEAD;


/************************************************************************************/

/**
*alarm in
*/
typedef struct
{
    int                 alarmInNo;              /**<  ��ǰ��������һ��ͨ���� */
    int                 isUsed;                 /**<  �Ƿ����� */

    NVD_HANDLE_LINKAGE  linkage;                /**<  �������� */
    NVD_TIME_RECT       time[NVD_WARD_MAX_DAY][NVD_WARD_TIME_NUM_PEER];  /**<  ����ʱ�� */
    char                name[NVD_STRING_LEN];   /**<  ���� */

    unsigned char       alarmInType;            /**<  �澯����, 0-����, 1-���� */

    unsigned char       res[19];
}NVD_ALARM_IN_PARA;

/**
*alarm out
*/
typedef struct
{
    int                 alarmOutNo;             /**<  ��ǰ��������һ��ͨ���� */
    int                 isUsed;                 /**<  �Ƿ����� */

    NVD_TIME_RECT       time[NVD_WARD_MAX_DAY][NVD_WARD_TIME_NUM_PEER];  /**<  ����ʱ�� */
    char                name[NVD_STRING_LEN];   /**<  ���� */

    unsigned char       alarmOutDelay;
    /**<  ����ź�״̬ά��ʱ�� 0-5�룬1-10�룬2-30�룬3-1���ӣ�4-2���ӣ�5-5���ӣ�6-10���ӣ�7-�ֶ���0xff-Ϊ���ޣ����ֶ��رգ� */

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
*͸������
*/
typedef struct
{
    int                 comNo;         /**<  ��ǰ��������һ��ͨ���� */
    int                 isUsed;        /**<  �Ƿ����� */

    NVD_COM_INFO        comInfo;

    unsigned char       res[16];
}NVD_COM_PARA;

/************************************************************************************/
/**
*ptz
*/
typedef struct
{
    int                 viNo;          /**<  ��ǰ��������һ��ͨ���� */
    int                 isUsed;        /**<  �Ƿ����� */

    NVD_PTZ_PROTOCOL    protocol;

    NVD_COM_INFO        comInfo;

    unsigned char       addr;
    unsigned char       comNo;         /**<  ʹ�õ�����һ������,�п��ܵ�ǰ�豸�ж������ */

    unsigned char       res[18];
}NVD_PTZ_COM_PARA;

/**
*PTZ���������� 
*/
typedef enum
{
    /**
    *basic,��������
    */
    NVD_PTZ_UP = 0,               /**<  �� data1:tilt speed, 1~8 level */
    NVD_PTZ_DOWN,                 /**<  �� data1:tilt speed, 1~8 level */
    NVD_PTZ_LEFT,                 /**<  �� data1:pan speed, 1~8 level */
    NVD_PTZ_RIGHT,                /**<  �� data1:pan speed, 1~8 level */
    NVD_PTZ_LEFTUP,               /**<  ����data1:pan speed, 1~8 level; data2:tilt speed, 1~8 level */
    NVD_PTZ_RIGHTUP,              /**<  ����data1:pan speed, 1~8 level; data2:tilt speed, 1~8 level */
    NVD_PTZ_LEFTDOWN,             /**<  ����data1:pan speed, 1~8 level; data2:tilt speed, 1~8 level */
    NVD_PTZ_RIGHTDOWN,            /**<  ����data1:pan speed, 1~8 level; data2:tilt speed, 1~8 level */
    NVD_PTZ_AUTO_SCAN,            /**<  �Զ�ɨ�� */
    NVD_PTZ_MANUAL_SCAN,          /**<  �ֶ�ɨ�� */
    NVD_PTZ_CAMERA_ON,
    NVD_PTZ_CAMERA_OFF,
    NVD_PTZ_IRIS_CLOSE,           /**<  ��ȦС */
    NVD_PTZ_IRIS_OPEN,            /**<  ��Ȧ�� */ 
    NVD_PTZ_FOCUS_NEAR,           /**<  �Խ��� */
    NVD_PTZ_FOCUS_FAR,            /**<  �Խ�Զ */
    NVD_PTZ_ZOOM_WIDE,            /**<  �䱶С */
    NVD_PTZ_ZOOM_TELE,            /**<  �䱶�� */

    NVD_PTZ_STOP,                 /**<  ֹͣ���� */

    NVD_PTZ_AUXILIARY_1 = 0x80,   /**<  ����1�� data1, 0:close, 1:open*/
    NVD_PTZ_AUXILIARY_2,          /**<  ����2�� data1, 0:close, 1:open*/
    NVD_PTZ_AUXILIARY_3,          /**<  ����3�� data1, 0:close, 1:open*/
    NVD_PTZ_AUXILIARY_4,          /**<  ����4�� data1, 0:close, 1:open*/
    NVD_PTZ_AUXILIARY_5,          /**<  ����5�� data1, 0:close, 1:open*/
    NVD_PTZ_AUXILIARY_6,          /**<  ����6�� data1, 0:close, 1:open*/
    NVD_PTZ_AUXILIARY_7,          /**<  ����7�� data1, 0:close, 1:open*/
    NVD_PTZ_AUXILIARY_8,          /**<  ����8�� data1, 0:close, 1:open*/

    NVD_DIGITAL_PTZ_UP = 0x100,   /**<  �� data1:tilt speed, 1~8 level */
    NVD_DIGITAL_PTZ_DOWN,         /**<  �� data1:tilt speed, 1~8 level */
    NVD_DIGITAL_PTZ_LEFT,         /**<  �� data1:pan speed, 1~8 level */
    NVD_DIGITAL_PTZ_RIGHT,        /**<  �� data1:pan speed, 1~8 level */
    NVD_DIGITAL_PTZ_LEFTUP,       /**<  ����data1:pan speed, 1~8 level; data2:tilt speed, 1~8 level */
    NVD_DIGITAL_PTZ_RIGHTUP,      /**<  ����data1:pan speed, 1~8 level; data2:tilt speed, 1~8 level */
    NVD_DIGITAL_PTZ_LEFTDOWN,     /**<  ����data1:pan speed, 1~8 level; data2:tilt speed, 1~8 level */
    NVD_DIGITAL_PTZ_RIGHTDOWN,    /**<  ����data1:pan speed, 1~8 level; data2:tilt speed, 1~8 level */

    NVD_DIGITAL_PTZ_ZOOM_WIDE,    /**<  �䱶С */
    NVD_DIGITAL_PTZ_ZOOM_TELE,    /**<  �䱶�� */

    NVD_DIGITAL_PTZ_STOP,         /**<  ֹͣ���� */

    NVD_PTZ_ILL
}NVD_PTZ_CTRL_CMD;

/**
*��������ṹ
*/
typedef struct
{
    NVD_PTZ_CTRL_CMD        cmd;            /**<  ���������� */

    /**
    *��������
    */
    unsigned char           data1;          /**<  ����NVD_PTZ_CMD��δ˵����Ϊ0 */
    unsigned char           data2;          /**<  ����NVD_PTZ_CMD��δ˵����Ϊ0 */

    unsigned char           res[18];        /**<  ���� */
}NVD_PTZ_CTRL_DATA;

/**************************************************************/
#define NVD_MAX_PRESET_SET     32
#define NVD_MAX_PRESET_GRP     4
#define NVD_MAX_PRESET_NUM     NVD_MAX_PRESET_SET*NVD_MAX_PRESET_GRP
typedef struct
{
    int                     isUsed;         /**<  �Ƿ����� */
    char                    presetName[NVD_STRING_LEN];     /**<  Ԥ�õ����� */
}PTZ_PRESET_PARA;

/*
 * Ԥ��λ��
 * res[0]ֵΪ0ʱ��ȡ��һ�飬Ϊ1ʱ�ڶ��飬�Դ�����
 */
typedef struct
{
    int                     viNo;           /**<  ��ǰ��������һ��ͨ���� */

    PTZ_PRESET_PARA         presetPara[NVD_MAX_PRESET_SET];

    unsigned char           res[16];        /**<  ���� */
}NVD_PTZ_PRESET_PARA;

typedef enum
{
    PTZ_ADD_PRESET,        /**<  ����Ԥ�õ� */
    PTZ_DEL_PRESET,        /**<  ɾ��Ԥ�õ� */
    PTZ_MODIFY_PRESET,     /**<  �޸�Ԥ�õ� */
    PTZ_GOTO_PRESET,       /**<  ִ��Ԥ�õ� */

    PTZ_PRESET_ILL
}NVD_PTZ_PRESET_CMD;

/**
*Ԥ�õ�ṹ 
*/
typedef struct
{
    NVD_PTZ_PRESET_CMD      cmd;            /**<  ���������� */

    int                     presetId;       /**<  Ԥ�õ��� */
    char                    presetName[NVD_STRING_LEN];     /**<  Ԥ�õ����� */

    unsigned char           res[16];        /**<  ���� */
}NVD_PTZ_CTRL_PRESET_PARA;

/**************************************************************/
#define NVD_MAX_TRACK_NUM     32

typedef struct
{
    int                     isUsed;        /**<  �Ƿ����� */
    char                    trackName[NVD_STRING_LEN];     /**<  �켣���� */
}PTZ_TRACK_PARA;

typedef struct
{
    int                     viNo;          /**<  ��ǰ��������һ��ͨ���� */

    PTZ_TRACK_PARA          trackPara[NVD_MAX_TRACK_NUM];

    unsigned char           res[16];        /**<  ���� */
}NVD_PTZ_TRACK_PARA;

typedef enum
{
    PTZ_ADD_TRACK,          /**<  ���ӹ켣 */
    PTZ_DEL_TRACK,          /**<  ɾ���켣 */
    PTZ_START_MEM_TRACK,    /**<  ��ʼ��¼�켣 (���֮ǰ����켣���ù�����ôֱ�Ӹ���) */
    PTZ_STOP_MEM_TRACK,     /**<  ֹͣ��¼�켣 */
    PTZ_START_RUN_TRACK,    /**<  ��ʼ���й켣 */
    PTZ_STOP_RUN_TRACK,     /**<  ֹͣ���й켣 */

    PTZ_TRACK_ILL
}NVD_PTZ_TRACK_CMD;

/**
*�켣�ṹ
*/
typedef struct
{
    NVD_PTZ_TRACK_CMD       cmd;            /**<  ���������� */

    int                     trackId;        /**<  �켣��� */
    char                    trackName[NVD_STRING_LEN];     /**<  �켣���� */

    unsigned char           res[16];        /**<  ���� */
}NVD_PTZ_CTRL_TRACK_PARA;

/**************************************************************/
#define NVD_MAX_CRUISE_NUM          16
#define NVD_MAX_CRUISE_POINT_NUM    16
typedef struct
{
    int                     isUsed;         /**<  ��ǰ�����Ƿ�ʹ�� */
    char                    cruiseName[NVD_STRING_LEN];     /**<  Ѳ��·������ */

    unsigned char           res[16];        /**<  ���� */
}PTZ_CRUISE_PARA;

typedef struct
{
    int                     viNo;           /**<  ��ǰ��������һ��ͨ���� */

    PTZ_CRUISE_PARA         cruisePara[NVD_MAX_CRUISE_NUM]; /**<  �����Ѳ��·�� */

    unsigned char           res[16];        /**<  ���� */
}NVD_PTZ_CRUISE_PARA;

typedef enum
{
    PTZ_ADD_CRUISE,        /**<  ����Ѳ�� */
    PTZ_DEL_CRUISE,        /**<  ɾ��Ѳ�� */
    PTZ_START_CRUISE,      /**<  ��ʼѲ�� */
    PTZ_STOP_CRUISE,       /**<  ֹͣѲ�� */

    PTZ_CRUISE_ILL
}NVD_PTZ_CRUISE_CMD;

/**
*�켣�ṹ
*/
typedef struct
{
    NVD_PTZ_CRUISE_CMD      cmd;            /**<  ���������� */
 
    int                     cruiseId;       /**<  Ѳ��·����� */
    char                    cruiseName[NVD_STRING_LEN];     /**<  Ѳ������ */

    unsigned char           res[16];        /**<  ���� */
}NVD_PTZ_CTRL_CRUISE_PARA;

/*************************************/

/**
*�����޸�Ѳ��·��������Ϣ�Ĳ���������ʹ�ýṹ�塣
*�����豸����ȡ��ʱ�򣬸���Ѳ��·���ŷ���Ҫ�޸ĵ�Ѳ��·���ľ�����Ϣ������NVD_PTZ_CRUISE_POINT_PARA
*�����豸�����õ�ʱ���ϲ�Ӧ���·�NVD_PTZ_CRUISE_POINT_PARA������Ҫ�޸ĵ�·���ţ�����cruiseId��
*/
typedef struct
{
    int                     isUsed;         /**<  ��ǰ�����Ƿ�ʹ�� */

    int                     presetId;       /**<  ��Ѳ�����϶�Ӧ��Ԥ�õ�� */
    char                    presetName[NVD_STRING_LEN];     /**<  Ԥ�õ����� */

    unsigned char           dwell;          /**<  ��Ѳ�����϶�Ӧ��ͣ��ʱ�� */
    unsigned char           res[3];         /**<  ���� */
}CRUISE_POINT_PARA;

typedef struct
{
    int                     cruiseId;         /**<  ��ǰ��������һ��Ѳ��·���� */
    char                    cruiseName[NVD_STRING_LEN];     /**<  Ѳ��·������ */

    CRUISE_POINT_PARA       pointPara[NVD_MAX_CRUISE_POINT_NUM];
}NVD_PTZ_CRUISE_POINT_PARA;

/**************************************************************/

/**
*�Զ���λԤ�õ�ṹ
*/
typedef struct
{
    int                     viNo;           /**<  ��ǰ��������һ��ͨ���� */
    int                     isUsed;         /**<  �Ƿ����� */

    int                     presetId;       /**<  Ԥ�õ��� */
    char                    presetName[NVD_STRING_LEN];     /**<  Ԥ�õ����� */
    unsigned int            resetTime;      /**<  �Զ���λ��ʱ�� */

    unsigned char           res[16];        /**<  ���� */
}NVD_PTZ_DEFAULT_PRESET_PARA;

/**************************************************************/

/**
*3D�ֲ����ٷŴ�,���3D��λ
*/
typedef struct
{
    unsigned short          allWidth;       /**<  �������Ŵ��ڵĿ�� */
    unsigned short          allHeight;      /**<  �������Ŵ��ڵĸ߶� */
    unsigned short          xPos;           /**<  ��ѡ���ڵ����Ͻ�x������ */
    unsigned short          yPos;           /**<  ��ѡ���ڵ����Ͻ�y������ */
    unsigned short          width;          /**<  ��ѡ���ڵĿ�� */
    unsigned short          height;         /**<  ��ѡ���ڵĸ߶� */

    unsigned char           res[16];        /**<  ���� */
}NVD_PTZ_3D_LOCATE_DATA;

/**************************************************************/

/**
*UniModule һ�廯��о����
*/
#define NVD_MAX_PTZ_UNI_MODULE_LEN  20      /**<  һ�廯��о������Ϣ��󳤶� */
typedef struct
{
    int                     isUsed;         /**<  �Ƿ���Ч */
    int                     seq;            /**<  ��ǰ�����ǵڼ������� */

    int                     len;            /**<  ��ǰbuf����Ч���� */

    unsigned char           buf[NVD_MAX_PTZ_UNI_MODULE_LEN];        /**<  �������� */
}NVD_PTZ_UNI_MODULE_DATA;
/**************************************************************/


/**
*ģ����̿��������� 
*/
typedef enum
{
    NVD_KEYBOARD_MENU = 0,       /**<  �˵� */
    NVD_KEYBOARD_TELT_UP,        /**<  �� */
    NVD_KEYBOARD_WIDE_DOWN,      /**<  �� */
    NVD_KEYBOARD_FAR_LEFT,       /**<  �� */
    NVD_KEYBOARD_NEAR_RIGHT,     /**<  �� */

    NVD_KEYBOARD_ILL
}NVD_KEYBOARD_CTRL_CMD;

/**
*ģ����̻����ṹ
*/
typedef struct
{
    NVD_KEYBOARD_CTRL_CMD   cmd;        /**<  ���������� */

    /**
    *����
    */
    unsigned char           res[20];    /**<  ���� */
}NVD_KEYBOARD_CTRL_DATA;

/************************************************************************************/

typedef enum
{
    NVD_SD_STATUS_INSERTED			= 0x01,     /**<  SD������*/
	NVD_SD_STATUS_WRITE_PROTECTED	= 0x02,		/**<  SD��д�������ش�*/
	NVD_SD_STATUS_MOUNTED			= 0x04,		/**<  SD���ѹ���*/
    NVD_SD_STATUS_FORMATTING		= 0x08,     /**<  SD�����ڸ�ʽ��*/
	NVD_SD_STATUS_READONLY			= 0x10,		/**<  SD���ļ�ϵͳ����Ϊֻ��(�쳣�ο��ȵ���SD���ļ�ϵͳ����ʱ,�����û�д�д�������ص���SD������Ϊֻ�����)*/
    NVD_SD_STATUS_ILL
}NVD_SD_STATUS;

/**
*SD�����û����ṹ
*/
typedef struct
{
    int                 status;                   /**<  SD��״̬*/
    char				res[4];                   /**<  ���� */

#if defined( _MSC_VER) && (_MSC_VER<1500)
	unsigned __int64	nTotalSpace;              /**<  SD��������(Byte) */
	unsigned __int64	nFreeSpace;               /**<  ��������(Byte) */
	   
	unsigned __int64	nTotalRecordUsedSize;	  /**<  ��ǰ¼���Ѿ�ʹ�ÿռ�(Byte) */
	unsigned __int64	nTotalCaptureUsedSize;	  /**<  ��ǰץ���Ѿ�ʹ�ÿռ�(Byte) */
#else
    unsigned long long	nTotalSpace;              /**<  SD��������(Byte) */
    unsigned long long	nFreeSpace;               /**<  ��������(Byte) */

	unsigned long long	nTotalRecordUsedSize;	  /**<  ��ǰ¼���Ѿ�ʹ�ÿռ�(Byte) */
	unsigned long long	nTotalCaptureUsedSize;	  /**<  ��ǰץ���Ѿ�ʹ�ÿռ�(Byte) */
#endif

}NVD_SD_PARA;
/************************************************************************************/
/**
*���ܻ����������ýṹ��
*/
typedef struct
{
    unsigned char isUsed;                       /**< �Ƿ����� */
    unsigned char interval;                     /**< ���(֡)[0,5] */
    unsigned char sensitivity;                  /**< ������[0,100] */
    unsigned char sceneType;                    /**< ����ģʽ: 0:���⣬1:���� */
    unsigned char processingQuality;            /**< ��������[0,3] : 0 - Low, 1 - Med, 2 - High, 3 - Use original video scale */

    unsigned char pplEnabled;                   /**< �Ƿ����� : 0 - disabled, 1 - enabled  */
    unsigned char minPplWdPercent;              /**< ��С���[0,100](����ڵ�ǰ�ֱ��ʵİٷֱ�) */
    unsigned char minPplHtPercent;              /**< ��С�߶�[0,100](����ڵ�ǰ�ֱ��ʵİٷֱ�) */
    unsigned char maxPplWdPercent;              /**< �����[0,100](����ڵ�ǰ�ֱ��ʵİٷֱ�) */
    unsigned char maxPplHtPercent;              /**< ���߶�[0,100](����ڵ�ǰ�ֱ��ʵİٷֱ�) */

    unsigned char vehEnabled;                   /**< �Ƿ��⳵�� : 0 - disabled, 1 - enabled  */
    unsigned char minVehWdPercent;              /**< ��С���[0,100](����ڵ�ǰ�ֱ��ʵİٷֱ�) */
    unsigned char minVehHtPercent;              /**< ��С�߶�[0,100](����ڵ�ǰ�ֱ��ʵİٷֱ�) */
    unsigned char maxVehWdPercent;              /**< �����[0,100](����ڵ�ǰ�ֱ��ʵİٷֱ�) */
    unsigned char maxVehHtPercent;              /**< ���߶�[0,100](����ڵ�ǰ�ֱ��ʵİٷֱ�) */
    
    unsigned char objEnabled;                   /**< �Ƿ������� : 0 - disabled, 1 - enabled  */
    unsigned char minObjWdPercent;              /**< ��С���[0,100](����ڵ�ǰ�ֱ��ʵİٷֱ�) */
    unsigned char minObjHtPercent;              /**< ��С�߶�[0,100](����ڵ�ǰ�ֱ��ʵİٷֱ�) */
    unsigned char maxObjWdPercent;              /**< �����[0,100](����ڵ�ǰ�ֱ��ʵİٷֱ�) */
    unsigned char maxObjHtPercent;              /**< ���߶�[0,100](����ڵ�ǰ�ֱ��ʵİٷֱ�) */

    unsigned char othEnabled;                   /**< �Ƿ����������� : 0 - disabled, 1 - enabled  */
    unsigned char minOthWdPercent;              /**< ��С���[0,100](����ڵ�ǰ�ֱ��ʵİٷֱ�) */
    unsigned char minOthHtPercent;              /**< ��С�߶�[0,100](����ڵ�ǰ�ֱ��ʵİٷֱ�) */
    unsigned char maxOthWdPercent;              /**< �����[0,100](����ڵ�ǰ�ֱ��ʵİٷֱ�) */
    unsigned char maxOthHtPercent;              /**< ���߶�[0,100](����ڵ�ǰ�ֱ��ʵİٷֱ�) */

    unsigned char res[127];

}NVD_IVA_STANDARD_PARA;

/**
*���ܸ߼��������ýṹ��
*/
typedef struct
{
    unsigned short initLearnTime;               /**< ��ʼѧϰʱ��(��) Initial learning time in sec */
    unsigned char initLearnType;                /**< ��ʼѧϰ����, 0:û������ѧϰ,1:����ѧϰ */

    unsigned char conBGLearnEnable;             /**< �Ƿ����ѧϰ: 0 - disabled, 1 - enabled */
    unsigned short conBGLearnTime;              /**< ����ѧϰʱ��(����)*/
    unsigned char conBGSpeed;                   /**< ����ѧϰ�ٶ�[0,3] : 0 (slow) .. 3 (fast) */
    unsigned char conBGObjInSceEnable;          /**< �Ƿ�̬����ѧϰ : 0 - disabled, 1 - enabled */
    unsigned short conBGObjInScene;             /**< ��̬����ѧϰʱ��(��) */

    unsigned char  enableSuddenChangeBGl;       /**< �Ƿ��ⱳ��˲��仯�ͱ���ѧϰ : 0 - disabled, 1 - enabled */
    unsigned char  suddenChangeThreshold;       /**< ˲��仯���������[0,100] */

    unsigned char  colorCheck;                  /**< �Ƿ�ʶ��������ɫ : 0 - disabled, 1 - enabled */
    unsigned char  shapeApperance;              /**< �Ƿ�ʶ��������״ : 0 - disabled, 1 - enabled */
    unsigned char  motionCheck;                 /**< �Ƿ��������˶�״̬ : 0 - disabled, 1 - enabled */
    unsigned char  contrastCheck;               /**< �Ƿ�Ա����� : 0 - disabled, 1 - enabled */

    unsigned char  trackerType;                 /**< �Ƿ���� : 0 - disabled, 1 - enabled */
    unsigned char  shadowSuppress;              /**< ��Ӱ����ǿ��[0,100] */
    unsigned short initialTime;                 /**< ����ȷ��ʱ��(����) */
    
    unsigned char   enbObjEntryExit;            /**< �Ƿ�ʹ�����������ʧ�¼� : 0 - disabled, 1 - enabled */
    unsigned char   enbSingleEventPerObj;       /**< �Ƿ񵥸�����ֻ���������¼� Single event per object: 0 - disabled, 1 - enabled */
    unsigned short timeDiffBetTwoEvents;        /**< �¼����(��) Time between events: 0.. */

    unsigned char res[128];

}NVD_IVA_ADVANCED_PARA;


#define NVD_MAX_HEIGHT_LINE_NUM     3   /**<  ������������ */
#define NVD_MAX_HEIGHT_POS_NUM      5   /**<  ÿ����������ο��� */
#define NVD_MAX_HL_TXT_LEN          64  /**<  ����߱�ʾ�ַ���󳤶� */
typedef struct
{
    unsigned short posX;    /**<  x���� */
    unsigned short posY;    /**<  y���� */
}NVD_IVA_POS_COORD;

/**
*��������߻������ýṹ
*/
typedef struct
{
    unsigned int isUsed;                                                        /**< �Ƿ�������������� */
    NVD_IVA_POS_COORD pos[NVD_MAX_HEIGHT_LINE_NUM][NVD_MAX_HEIGHT_POS_NUM];     /**< ���������:�����1�������2����׼�� */
    unsigned char txtHl[NVD_MAX_HEIGHT_LINE_NUM][NVD_MAX_HL_TXT_LEN];           /**< ����߱�ʾ�ַ��� */
    
    char res[44];
}NVD_IVA_HL_PARA;

/**
*���ܾ����߻������ýṹ
*/
typedef struct{
    int enableCordon;           /**< �Ƿ����þ�����*/
    NVD_IVA_POS_COORD posStart; /**< ��ʼ���� */
    NVD_IVA_POS_COORD posEnd;   /**< �������� */
    
    unsigned char res[64];
}NVD_IVA_CORDON_PARA;

/**
*��������ͳ�ƻ������ýṹ
*/
typedef struct{
    unsigned int enablePplCounter;      /**< �Ƿ���������ͳ�� */
    NVD_IVA_POS_COORD posStart;         /**< ��ʼ���� */
    NVD_IVA_POS_COORD posEnd;           /**< �������� */

    unsigned char res[64];
}NVD_IVA_PPL_COUNTER_PARA;

/**
*���ܳ���ͳ�ƻ������ýṹ
*/
typedef struct{
    unsigned int enableVehCounter;      /**< �Ƿ����ó���ͳ�� */
    NVD_IVA_POS_COORD posStart;         /**< ��ʼ���� */
    NVD_IVA_POS_COORD posEnd;           /**< �������� */

    unsigned char res[64];
}NVD_IVA_VEH_COUNTER_PARA;

/**
*¼������
*/
/**
@brief ¼������ģʽ
*/
typedef enum
{
    NVD_RECORD_PLAYBACK_MODE_BY_NAME     = 0,   /**<  ���ļ�����������*/
    NVD_RECORD_PLAYBACK_MODE_BY_TIME,           /**<  ��ʱ��ν�������*/
    NVD_RECORD_PLAYBACK_MODE_ILL,
}NVD_RECORD_PLAYBACK_MODE;
/**
*@brief ¼��ʱ��ṹ
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
 @brief ¼���ļ���Ϣ
*/
typedef struct tagNET_RECORDFILE_INFO
{
    char szFileName[100];           /**<  �ļ��� */
    NET_TIME startTime;             /**<  �ļ��Ŀ�ʼʱ�� */
    NET_TIME stopTime;              /**<  �ļ��Ľ���ʱ�� */
    unsigned int dwFileSize;        /**<  �ļ��Ĵ�С */
}NET_RECORDFILE_INFO, *LPNET_RECORDFILE_INFO;
/**
* @brief ����¼�����ز���
*/
typedef struct tagNVD_RECORD_PLAYBACK
{
    NVD_RECORD_PLAYBACK_MODE mode;  /**<  �ļ�����ģʽ */
    char szFileName[100];           /**<  ���ļ�����������ʱ���ø�ֵ */
    unsigned char   byChannel;      /**<  ��ʱ��ν�������ʱ����ֵ��Ч */
    unsigned char   byReserve[3];
    unsigned int    dwType;         /**<  ��ʱ��ν�������ʱ����ֵ��Ч */
    NET_TIME        startTime;      /**<  ��ʱ��ν�������ʱ����ֵ��Ч */
    NET_TIME        stopTime;       /**<  ��ʱ��ν�������ʱ����ֵ��Ч */
    unsigned int    dwTimeout;      /**<  ms,��ʱʱ�䣨�ӿ�ʼ���ص��������ص�Ԥ��ʱ��Σ����������ʱ��Σ�IPC�˿��ܻᵥ���������أ� */
}NVD_RECORD_PLAYBACK,*LPNVD_RECORD_PLAYBACK;

/**
* @brief ����Ƶ֡����
*/
typedef struct tagNVD_RECORD_PLAYBACK_SEEK
{
    unsigned int dwTime;            /**<  1970/1/1 00:00:00��������� */
}NVD_RECORD_PLAYBACK_SEEK,*LPNVD_RECORD_PLAYBACK_SEEK;
/**
*@brief ¼���ļ���������
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
* ǰ��ץ��ͼƬ���Ҳ���
*/
typedef struct
{
    unsigned char  byFileType;      // ���ҵ�ͼƬ����: 0-��ʱץ�� 1-�ƶ����ץ�� 2-����ץ�� 3-����ת�� 4-��Ƶ�ڵ� 0xff-ȫ������
    unsigned char  byRes1[3];       // �����ֽ�
    NVD_TIME       ntStartTime;     // ����ͼƬ�Ŀ�ʼʱ��
    NVD_TIME       ntStopTime;      // ����ͼƬ�Ľ���ʱ��
    unsigned char  byRes2[16];      // �����ֽ�
}NVD_FIND_PICTURE_PARAM;

/**
* ǰ��ץ��ͼƬ���ҽ��
*/
typedef struct
{
    char           sFileName[64];    // ͼƬ�ļ���
    NVD_TIME       ntTime;           // ͼƬ��ʱ��
    unsigned int   dwFileSize;       // ͼƬ���ݴ�С
    unsigned char  byRes[6];         // �����ֽ�
}NVD_FIND_PICTURE;

#endif

