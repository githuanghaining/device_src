/*=========================================================================
  Copyright (C) 2011, Videotrec Industrial Co., Ltd
                         All Rights Reserved.

  Name        : NVDEVENT_TOOLS.h
  Description :
  Version     :
  Author      : 
  Create Date : 2013-11-07
  =========================================================================*/

#ifndef __NVD_EVENT_TOOLS_H__
#define __NVD_EVENT_TOOLS_H__

/************************************************************************************/

#define NVD_DEFAULT_UDP_DATA_PORT          11560       //缺省的udp数据端口号
#define NVD_DEFAULT_TCP_DATA_PORT          12560       //缺省的tcp数据端口号
#define NVD_DEFAULT_BROAD_SEARCH_PORT      10100


#define NVD_CMD_PREFIX              0x55aa55aa
#define NVD_CMD_VERSION             0x030409           //版本号
#define NVD_CMD_HEADER_LEN          32
#define NVD_MAX_CMD_PAYLOAD_LEN     1400

#define NVD_GET_CMD_TYPE(cmd)       (cmd&0xFFFF0000)


#define NVD_SU_LOGID    0xa5a5a5a5

#define NVD_CFG_MAX_PTZ_UNI_MODULE_NUM  100     //最大配置序列数
#define NVD_CFG_MAX_PTZ_UNI_MODULE_LEN  20      //  一体化机芯单条消息最大长度 


/* 全部使用小字节序 */
typedef struct
{
    unsigned int    prefix;        //网络命令前缀0x55aa55aa
    unsigned int    version;       //软件版本号
    unsigned int    commandId;     //命令ID
    unsigned int    event;         //网络命令
    unsigned int    data1;         //携带数据1 填登录ID
    unsigned int    data2;         //携带数据2
    unsigned short  payload_len;   //载荷长度
    unsigned char   res[2];        //保留
    unsigned int    checksum;      //校验和
    unsigned char   payload[NVD_MAX_CMD_PAYLOAD_LEN];   //载荷数据
}NVD_HEAD;

/************************************************************************************/

typedef enum
{
    NVD_VER_APP     = 0,
    NVD_VER_APP1,
    NVD_VER_BOOT,
    NVD_MAX_VER_TYPE
}NVD_VER_TYPE;

#define NVD_VER_STR_LEN                 32
#define NVD_VER_SIGNATURE               0x4e57

typedef struct
{
    unsigned short  crc16;              /* 版本文件的校验和*/
    unsigned short  signature;          /* 0x4e43 "CN" 2.0之前的版本, 0x4e57 "WN" 2.0之后的版本 */
    unsigned int    sections;           /* 版本的大小(已经补齐了)*/
    unsigned int    lowest;             /* lowest address */
    unsigned int    highest;            /* highest address */
    char            version[NVD_VER_STR_LEN];
    unsigned int    tTime;              /* 版本文件制作的时间*/
    unsigned int    uncmpsize;          /* 压缩前版本的大小 */
    unsigned short  uncmpcrc16;         /* 压缩前版本的校验和 */
    unsigned short  vertype;
    unsigned int    position;           /*表示版本在FLASH中的位置，制作版本时为0*/
    unsigned int    mainversion;        /*1：表示该版本为正在使用版本，0表示是备用版本。制作版本时该位为0*/
    char            acReserve[60];
}nvd_ver_head;

#define NVD_VER_FIRST_VER_PACKET_INDEX  0
#define NVD_VER_LAST_VER_PACKET_INDEX   0xFFFFFFFF

/************************************************************************************/

typedef enum
{
/******************************************************************************************/
    NVD_BURN = 0x00000,
    NVD_BURN_GET_FACTORY_REQ,
/*
功能：    上层向单板发送获取出厂信息命令
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_BURN_GET_FACTORY_ACK,
/*
功能：    上层向单板发送获取出厂信息回应
* data1:       NVD_SU_LOGID
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_FACTORY_PARA)
* payload:     NVD_FACTORY_PARA
*/

    NVD_BURN_SET_FACTORY_REQ,
/*
功能：    根据上报的设备信息设置出厂信息命令
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: 2*sizeof(NVD_FACTORY_PARA)
* payload:     NVD_FACTORY_PARA + NVD_FACTORY_PARA
* 对于出厂烧写软件需要在payload中发送两个NVD_FACTORY_PARA结构体，新的在前，原来的在后
*              内容只需填上单板原出厂配置，用于单板区分该命令是否是发给自身的，
*              payload_len为 2 * sizeof(NVD_FACTORY_PARA)，广播发送;
*/

    NVD_BURN_SET_FACTORY_ACK,
/*
功能：    上层向单板发送设置出厂信息回应
* data1:       NVD_SU_LOGID
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_BURN_GET_ADVANCED_REQ,
/*
功能：    上层向单板发送获高级参数信息命令
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_BURN_GET_ADVANCED_ACK,
/*
功能：    上层向单板发送获取高级参数回应
* data1:       NVD_SU_LOGID
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_FACTORY_PARA)+sizeof(NVD_ADVANCED_PARA)
* payload:     NVD_FACTORY_PARA+NVD_ADVANCED_PARA
*/

    NVD_BURN_SET_ADVANCED_REQ,
/*
功能：    根据上报的设备信息设置高级参数命令
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: sizeof(NVD_ADVANCED_PARA) + sizeof(NVD_FACTORY_PARA)
* payload:     NVD_FACTORY_PARA + NVD_ADVANCED_PARA
* 对于出厂烧写软件需要在payload中发送 NVD_ADVANCED_PARA + NVD_FACTORY_PARA结构体
*              内容只需填上单板原出厂配置，用于单板区分该命令是否是发给自身的，
*              payload_len为 sizeof(NVD_ADVANCED_PARA) + sizeof(NVD_FACTORY_PARA)，广播发送;
*/

    NVD_BURN_SET_ADVANCED_ACK,
/*
功能：    上层向单板发送设置高级参数回应
* data1:       NVD_SU_LOGID
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

/******************************************************************************************/
    NVD_SYS                     = 0x10000,
    NVD_SYS_GET_SEARCH_REQ,
/*
功能：    上层向单板发送搜索命令。广播搜索,单播探测
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_SYS_GET_SEARCH_ACK,
/*
功能：    设备响应搜索命令，向上层软件发送自身的信息。广播答复
* data1:       unused
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_SEARCH_PARA)
* payload:     NVD_SEARCH_PARA
*/

    NVD_SYS_SET_SEARCH_REQ,
/*
功能：    上层向单板发送设置搜索命令。广播发送
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: 2*sizeof(NVD_SEARCH_PARA)
* payload:     NVD_SEARCH_PARA*2
* 对于搜索软件需要在payload中发送两个NVD_SEARCH_PARA结构体，新的在前，原来的在后
*              内容只需填上单板原网络配置，用于单板区分该命令是否是发给自身的，
*              payload_len为 2 * sizeof(NVD_SEARCH_PARA)，广播发送;
*/

    NVD_SYS_SET_SEARCH_ACK,
/*
功能：    设备响应设置搜索命令，向上层软件发送自身的信息。广播答复
* data1:       unused
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_SYS_GET_NET_CONFIG_REQ,
/*
功能：    上层向单板获取网络设置请求
* data1:       id
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_SYS_GET_NET_CONFIG_ACK,
/*
功能：    上层向单板获取网络设置请求响应
* data1:       id
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_NET_PARA)
* payload:     NVD_NET_PARA
*/

    NVD_SYS_SET_NET_CONFIG_REQ,
/*
功能：    根据上报的设备信息设置设备网络参数
* data1:       NVD_SU_LOGID/或者其他登录ID
* data2:       unused
* payload_len: sizeof(NVD_NET_PARA)
* payload:     NVD_NET_PARA
*/

    NVD_SYS_SET_NET_CONFIG_ACK,
/*
功能：    设备响应搜索命令，向上层软件发送自身的信息。
* data1:       unused
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

/******************************************************************************************/
    NVD_VER             = 0x20000,
    NVD_VER_GET_VER_REQ,
/*
功能：    获取设备版本
* data1:       NVD_SU_LOGID
* data2:       NVD_VER_TYPE
* payload_len: 0
* payload:     NULL
*/

    NVD_VER_GET_VER_ACK,
/*
功能：    获取设备版本回复
* data1:       unused
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(nvd_ver_head)
* payload:     nvd_ver_head / NULL
*/

    NVD_VER_DELETE_VER_REQ,
/*
功能：    删除设备版本 仅限于删APP
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_VER_DELETE_VER_ACK,
/*
功能：    删除设备版本回复
* data1:       unused
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_VER_UPDATE_VER_REQ,
/*
功能：    更新初始化请求
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: sizeof(nvd_ver_head)
* payload:     nvd_ver_head
*/

    NVD_VER_UPDATE_VER_ACK,
/*
功能：    更新初始化回复
* data1:       unused
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(nvd_ver_err_str)
* payload:     nvd_ver_err_str  //由单板填写，更新软件只显示
*/

    NVD_VER_UPDATE_VER_TRANS_REQ,
/*
功能：    更新设备版本发送数据请求
* data1:       NVD_SU_LOGID
* data2:       包序号，从0开始，最后一个包填 NVD_VER_LAST_VER_PACKET_INDEX
* payload_len: sizeof(package)
* payload:     package
*/

    NVD_VER_UPDATE_VER_TRANS_ACK,
/*
功能：    更新设备版本发送数据回复
* data1:       unused
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(package index)
* payload:     package index
*/

    NVD_VER_UPDATE_CRC_VER_REQ,
/*
功能：    CRC安全更新初始化请求
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: sizeof(nvd_ver_head)
* payload:     nvd_ver_head
*/

    NVD_VER_UPDATE_CRC_VER_ACK,
/*
功能：    CRC安全更新初始化回复
* data1:       unused
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(nvd_ver_err_str)
* payload:     nvd_ver_err_str  //由单板填写，更新软件只显示
*/

    NVD_VER_UPDATE_CRC_VER_TRANS_REQ,
/*
功能：    CRC安全更新设备版本发送数据请求
* data1:       NVD_SU_LOGID
* data2:       包序号，从0开始，最后一个包填 NVD_VER_LAST_VER_PACKET_INDEX
* payload_len: sizeof(package)
* payload:     package
*/

    NVD_VER_UPDATE_CRC_VER_TRANS_ACK,
/*
功能：    CRC安全更新设备版本发送数据回复
* data1:       unused
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(package index)
* payload:     package index
*/

/******************************************************************************************/
    NVD_EVENT_TOOLS_ILL
}NVD_EVENT_TOOLS;

#endif

