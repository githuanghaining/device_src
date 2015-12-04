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

/* 日志级别 */
typedef enum
{
    msg_pri_error,                    /**< 错误信息,             输出到标准输出，sd卡，网络*/
    msg_pri_log,                      /**< 需要写日志的关键信息, 输出到标准输出，sd卡，网络*/
    msg_pri_debug,                    /**< 调试信息,             输出到标准输出，网络*/
}NVD_MSG_LEVEL;

/* 日志消息 */
#define NVD_LOG_MSG_LEN     512
typedef struct
{
    NVD_TIME      msgTime;
    
    NVD_MSG_LEVEL msgLevel;

    char          modName[NVD_STRING_LEN];

    char          msg[NVD_LOG_MSG_LEN]; /**<  限定最大长度为NVD_LOG_MSG_LEN    */
}NVD_LOG_MESSAGE;


/************************************************************************************/

/**
*日志配置基本结构
*/
typedef struct
{
    int                 isUsed;                 /**<  是否启用 */
    /**
    *日志主机ip地址
    */
    unsigned int        ipAddr;                 /**<  ip地址 */
    /**
    *日志主机端口号
    */
    unsigned int        hostPort;               /**<  端口 */

    int                 isSave2Sd;              /**<  是否保存SD卡 */

    unsigned char       res[60];                /**<  备用 */
}NVD_NET_LOG_PARA;

/************************************************************************************/

typedef struct
{
    unsigned char       mac[6];    //设备物理地址
    unsigned char       res[2];
    char                devSn[NVD_STRING_LEN];     //设备序列号
    char                hwVer[NVD_STRING_LEN];     //硬件版本号
}NVD_FACTORY_PARA;

typedef struct
{
    int                 isIvaLpr;    //是否开启智能分析
    unsigned char       res[256];    //预留
}NVD_ADVANCED_PARA;

/************************************************************************************/

#define NVD_MAX_PF_ID_LENGTH           64
#define NVD_MAX_PF_NAME_LENGTH         32
#define NVD_MAX_PF_PASSWORD_LENGTH     32

typedef struct
{
    unsigned int    cms_ip;         /**<  服务器IP */
    unsigned short  cms_port;       /**<  服务器端口 */
    unsigned char   res[2];         /**<  备用 */
    char            cms_name[NVD_MAX_PF_NAME_LENGTH];    /**<  服务器名字 */
    char            cms_id[NVD_MAX_PF_ID_LENGTH];        /**<  服务器ID */
    int             cms_time_zone;                          /**< 服务器时区调整参数，分钟*/

    unsigned short  board_port;     /**<  设备端口 */
    unsigned char   res1[2];        /**<  备用 */
    char            board_name[NVD_MAX_PF_NAME_LENGTH];  /**<  设备名字 */
    char            board_id[NVD_MAX_PF_ID_LENGTH];      /**<  设备ID */

    char            authUser[NVD_MAX_PF_NAME_LENGTH];    /**<  认证用户名 */
    char            user[NVD_MAX_PF_NAME_LENGTH];        /**<  用户名 */
    char            password[NVD_MAX_PF_PASSWORD_LENGTH];   /**<  密码 */

    unsigned int    reg_interval;    /**<  注册间隔 */
    unsigned int    alive_interval;  /**<  心跳间隔 */

    char            alarm_id[NVD_MAX_PF_ID_LENGTH]; /**<  报警ID */

    char            address[NVD_MAX_PF_NAME_LENGTH]; /**<  设备安装地址 */
    char            addr_longitude[NVD_MAX_PF_NAME_LENGTH]; /**<  经度 */
    char            addr_latitude[NVD_MAX_PF_NAME_LENGTH];  /**<  纬度 */
    char            other_para[128];                        /**<其他参数*/

    unsigned char   res3[128];       /**<  备用 */
}NVD_PF_PARA;

typedef struct
{
    int                 isUsed;                     /**<  是否启用 */
    char                ip[32];                     /**<  服务器地址 */
    char                deviceID[NVD_STRING_LEN];   /**<  设备ID**/
    unsigned int        port;                       /**<  服务器端口 */
    unsigned char       res1[32];                   /**<  备用 */
}NVD_TOLLGATE_PARA;


#endif

