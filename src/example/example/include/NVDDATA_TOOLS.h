////////////////////////////////////////////////////////////////////////// 
///  Copyright (C) 2011
///
/// @file NVDDATA_TOOLS.h
/// @brief   
/// @version   
/// @author  
/// @date  2011-05-12
////////////////////////////////////////////////////////////////////////// 

#ifndef __NVD_DATA_TOOLS_H__
#define __NVD_DATA_TOOLS_H__

#include "NVDDATA.h"
#include "NVDIVA.h"
/************************************************************************************/

/* ��־���� */
typedef enum
{
    msg_pri_error,                    /**< ������Ϣ,             �������׼�����sd��������*/
    msg_pri_log,                      /**< ��Ҫд��־�Ĺؼ���Ϣ, �������׼�����sd��������*/
    msg_pri_debug,                    /**< ������Ϣ,             �������׼���������*/
}NVD_MSG_LEVEL;

/* ��־��Ϣ */
#define NVD_LOG_MSG_LEN     512
typedef struct
{
    NVD_TIME      msgTime;
    
    NVD_MSG_LEVEL msgLevel;

    char          modName[NVD_STRING_LEN];

    char          msg[NVD_LOG_MSG_LEN]; /**<  �޶���󳤶�ΪNVD_LOG_MSG_LEN    */
}NVD_LOG_MESSAGE;


/************************************************************************************/

/**
*��־���û����ṹ
*/
typedef struct
{
    int                 isUsed;                 /**<  �Ƿ����� */
    /**
    *��־����ip��ַ
    */
    unsigned int        ipAddr;                 /**<  ip��ַ */
    /**
    *��־�����˿ں�
    */
    unsigned int        hostPort;               /**<  �˿� */

    int                 isSave2Sd;              /**<  �Ƿ񱣴�SD�� */

    unsigned char       res[60];                /**<  ���� */
}NVD_NET_LOG_PARA;

/************************************************************************************/

typedef struct
{
    unsigned char       mac[6];    //�豸�����ַ
    unsigned char       res[2];
    char                devSn[NVD_STRING_LEN];     //�豸���к�
    char                hwVer[NVD_STRING_LEN];     //Ӳ���汾��
}NVD_FACTORY_PARA;

typedef struct
{
    int                 isIvaLpr;    //�Ƿ������ܷ���
    unsigned char       res[256];    //Ԥ��
}NVD_ADVANCED_PARA;

/************************************************************************************/

#define NVD_MAX_PF_ID_LENGTH           64
#define NVD_MAX_PF_NAME_LENGTH         32
#define NVD_MAX_PF_PASSWORD_LENGTH     32

typedef struct
{
    unsigned int    cms_ip;         /**<  ������IP */
    unsigned short  cms_port;       /**<  �������˿� */
    unsigned char   res[2];         /**<  ���� */
    char            cms_name[NVD_MAX_PF_NAME_LENGTH];    /**<  ���������� */
    char            cms_id[NVD_MAX_PF_ID_LENGTH];        /**<  ������ID */
    int             cms_time_zone;                          /**< ������ʱ����������������*/

    unsigned short  board_port;     /**<  �豸�˿� */
    unsigned char   res1[2];        /**<  ���� */
    char            board_name[NVD_MAX_PF_NAME_LENGTH];  /**<  �豸���� */
    char            board_id[NVD_MAX_PF_ID_LENGTH];      /**<  �豸ID */

    char            authUser[NVD_MAX_PF_NAME_LENGTH];    /**<  ��֤�û��� */
    char            user[NVD_MAX_PF_NAME_LENGTH];        /**<  �û��� */
    char            password[NVD_MAX_PF_PASSWORD_LENGTH];   /**<  ���� */

    unsigned int    reg_interval;    /**<  ע���� */
    unsigned int    alive_interval;  /**<  ������� */

    char            alarm_id[NVD_MAX_PF_ID_LENGTH]; /**<  ����ID */

    char            address[NVD_MAX_PF_NAME_LENGTH]; /**<  �豸��װ��ַ */
    char            addr_longitude[NVD_MAX_PF_NAME_LENGTH]; /**<  ���� */
    char            addr_latitude[NVD_MAX_PF_NAME_LENGTH];  /**<  γ�� */
    char            other_para[128];                        /**<��������*/

    unsigned char   res3[128];       /**<  ���� */
}NVD_PF_PARA;

typedef struct
{
    int                 isUsed;                     /**<  �Ƿ����� */
    char                ip[32];                     /**<  ��������ַ */
    char                deviceID[NVD_STRING_LEN];   /**<  �豸ID**/
    unsigned int        port;                       /**<  �������˿� */
    unsigned char       res1[32];                   /**<  ���� */
}NVD_TOLLGATE_PARA;


#endif

