/*=========================================================================
  Copyright (C) 2011, Videotrec Industrial Co., Ltd
                         All Rights Reserved.

  Name        : NVDEVENT.h
  Description :
  Version     :
  Author      : 
  Create Date : 2013-11-07
  =========================================================================*/

#ifndef __NVD_EVENT_H__
#define __NVD_EVENT_H__

#include "NVDDATA.h"

typedef struct
{
    int                 viNo;               /**<  通道号 */
    NVD_ENC_STREAM_TYPE encStreamType;      /**<  视频 */
    NVD_NETMODEL        netModel;
}NVD_PLAY_PARA;


/************************************************************************************/

typedef enum
{
/******************************************************************************************/
/*
    NVD_SYS = 0x10000,
*/
    NVD_SYS_GET_PF_CONFIG_REQ = 0x10009,
/*
功能：    获取PF相关配置
* data1:       id
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_SYS_GET_PF_CONFIG_ACK,
/*
功能：    响应获取PF相关配置
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_SYS_SET_PF_CONFIG_REQ,
/*
功能：    设置PF相关配置
* data1:       
* data2:       unused
* payload_len: sizeof(NVD_PF_PARA)
* payload:     NVD_PF_PARA
*/

    NVD_SYS_SET_PF_CONFIG_ACK,
/*
功能：    响应设置PF相关配置
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/
    
    NVD_SYS_GET_NET_2_CONFIG_REQ,
/*
功能：    获取其它网络相关配置
* data1:       
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_SYS_GET_NET_2_CONFIG_ACK,
/*
功能：    响应其它网络相关配置
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_NET_2_PARA)
* payload:     NVD_NET_2_PARA
*/

    NVD_SYS_SET_NET_2_CONFIG_REQ,
/*
功能：    设置其它网络相关配置
* data1:       
* data2:       unused
* payload_len: sizeof(NVD_NET_2_PARA)
* payload:     NVD_NET_2_PARA
*/

    NVD_SYS_SET_NET_2_CONFIG_ACK,
/*
功能：    响应其它网络相关配置
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_SYS_GET_NTP_CONFIG_REQ,
/*
功能：    获取NTP参数配置
* data1:       
* data2:       unused
* payload_len: 0
* payload:     NULL
*/
    
    NVD_SYS_GET_NTP_CONFIG_ACK,
/*
功能：    响应NTP参数配置
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_NTP_PARA)
* payload:     NVD_NTP_PARA
*/


    NVD_SYS_SET_NTP_CONFIG_REQ,
/*
功能：    设置NTP参数配置
* data1:       
* data2:       unused
* payload_len: sizeof(NVD_NTP_PARA)
* payload:     NVD_NTP_PARA
*/
    
    NVD_SYS_SET_NTP_CONFIG_ACK,
/*
功能：    响应NTP参数配置
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_SYS_GET_EMAIL_CONFIG_REQ,
/*
功能：    获取EMAIL参数配置
* data1:       
* data2:       unused
* payload_len: 0
* payload:     NULL
*/
    
    NVD_SYS_GET_EMAIL_CONFIG_ACK,
/*
功能：    响应EMAIL参数配置
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_EMAIL_PARA)
* payload:     NVD_EMAIL_PARA
*/


    NVD_SYS_SET_EMAIL_CONFIG_REQ,
/*
功能：    设置EMAIL参数配置
* data1:       
* data2:       unused
* payload_len: sizeof(NVD_EMAIL_PARA)
* payload:     NVD_NTP_PARA
*/
    
    NVD_SYS_SET_EMAIL_CONFIG_ACK,
/*
功能：    响应EMAIL参数配置
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/
 

    NVD_SYS_GET_SNMP_CONFIG_REQ,
/*
功能：    获取SNMP参数配置
* data1:       
* data2:       unused
* payload_len: 0
* payload:     NULL
*/
    
    NVD_SYS_GET_SNMP_CONFIG_ACK,
/*
功能：    响应SNMP参数配置
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_SNMP_PARA)
* payload:     NVD_SNMP_PARA
*/


    NVD_SYS_SET_SNMP_CONFIG_REQ,
/*
功能：    设置SNMP参数配置
* data1:       
* data2:       unused
* payload_len: sizeof(NVD_SNMP_PARA)
* payload:     NVD_SNMP_PARA
*/
    
    NVD_SYS_SET_SNMP_CONFIG_ACK,
/*
功能：    响应SNMP参数配置
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_SYS_TRANS_OPEN_CONFIG_REQ = 0x10100,
/*
功能：    传输透明数据
* data1:       id
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_SYS_TRANS_OPEN_CONFIG_ACK,
/*
功能：    传输获取透明数据
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

/******************************************************************************************/
    NVD_USER = 0x30000,
    NVD_USER_LOGIN_REQ,
/*
功能：    用户登录设备
nData1:   NVD_INVALID_HANDLE
nData2:   0
payload_len: sizeof(NVD_USER_PARA)
payload:  NVD_USER_PARA
回复：    NVD_USER_LOGIN_ACK
*/

    NVD_USER_LOGIN_ACK,
/*
功能：    用户登录回复
nData1:   正确的情况下，返回登录ID
nData2:   0:成功
payload_len: sizeof(NVD_USER_PARA)+sizeof(NVD_LOGIN_INFO)
payload:  NVD_USER_PARA+NVD_LOGIN_INFO
*/

    NVD_USER_LOGOUT_NOTIFY,
/*
功能：    用户登出设备
nData1:   UserID
*/

    NVD_USER_ADD_REQ,
/*
功能：    增加用户
nData1:   UserID
payload_len: sizeof(NVD_USER_PARA)
payload:  NVD_USER_PARA
回复：    NVD_ADD_UAER_ACK
说明：    只有管理员可以做
*/

    NVD_USER_ADD_ACK,
/*
功能：    增加用户回复
nData2:   0:成功
*/

    NVD_USER_DELETE_REQ,
/*
功能：    删除用户
nData1:   UserID
payload_len: sizeof(NVD_USER_PARA)
payload:  NVD_USER_PARA
回复：    NVD_DELETE_UAER_ACK
说明：    只有管理员可以做
*/

    NVD_USER_DELETE_ACK,
/*
功能：    删除用户回复
nData2:   0:成功
*/

    NVD_USER_DELETE_NOTIFY,
/*
功能：    删除用户后通知该用户
*/

    NVD_USER_MODIFY_REQ,
/*
功能：    修改用户，包括修改密码
nData1:   UserID
payload_len: sizeof(NVD_USER_PARA)
payload:  NVD_USER_PARA
回复：    NVD_MODIFY_UAER_ACK
说明：    只有管理员和用户自己可以做
*/

    NVD_USER_MODIFY_ACK,
/*
功能：    修改用户回复
nData2:   0:成功
*/

    NVD_USER_QUERY_REQ,
/*
功能：    查询用户
nData1:   UserID
回复：    NVD_SELECT_USER_ACK
说明：    只有管理员和用户自己可以做
*/

    NVD_USER_QUERY_ACK,
/*
功能：    查询用户回复
nData2:   0:成功
payload_len: sizeof(NVD_USER_PARA)*用户个数
payload:  NVD_USER_PARA
*/

    NVD_USER_KEEPALIVE_REQ,
/*
功能：    用户保活请求
nData1:   UserID
*/

    NVD_USER_KEEPALIVE_ACK,
/*
功能：    用户保活请求
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_DEVICE = 0x40000,
/******************************************************************************************/
    NVD_DEVICE_GET_START_REQ,
/*
功能：    获取设备启动信息
nData1：  UserID
nData2：  通道号     0xFF表示全部获取
回复：    NVD_DEVICE_GET_START_ACK
*/

    NVD_DEVICE_GET_START_ACK,
/*
功能：    获取设备启动信息回复
数据：    
*/

    NVD_DEVICE_SET_START_REQ,
/*
功能：    设置设备启动信息
nData1：  UserID
payload：  
回复：    NVD_DEVICE_SET_START_ACK
*/

    NVD_DEVICE_SET_START_ACK,
/*
功能：    设置设备启动信息回复
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_DEVICE_GET_STATE_INFO_REQ,
/*
功能：    获取设备运行状态
nData1:   UserID
nData2:   NVD_STATE_TYPE
回复：    NVD_GET_STATE_INFO_ACK
*/

    NVD_DEVICE_GET_STATE_INFO_ACK,
/*
功能：    获取设备运行状态回复
nData1:   0:成功
payload:  NVD_STATE_INFO
*/

/******************************************************************************************/
    NVD_DEVICE_GET_INFO_REQ = 0x40100,
/*
功能：    获取设备信息
nData1:   UserID
payload_len: 0
回复：    NVD_GET_ENC_DEVICE_ACK
*/

    NVD_DEVICE_GET_INFO_ACK,
/*
功能：    获取设备信息回复
nData2:   0:成功
payload_len: sizeof(NVD_DEV_PARA)
payload： NVD_DEV_PARA
*/

    NVD_DEVICE_SET_INFO_REQ,
/*
功能：    设置设备信息
nData1：  UserID
payload_len: sizeof(NVD_DEV_PARA)
payload： NVD_DEV_PARA
回复：    NVD_SET_ENC_DEVICE_ACK
*/

    NVD_DEVICE_SET_INFO_ACK,
/*
功能：    设置设备信息回复
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_DEVICE_CHECK_TIME_REQ = 0x40700,
/*
功能：    设备校时请求
数据：    
回复：    NVD_DEVICE_CHECK_TIME_ACK
说明：   
*/

    NVD_DEVICE_CHECK_TIME_ACK,
/*
功能：    设备校时回复
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_DEVICE_RESTORE_REQ = 0x40800,
/*
功能：    设置设备恢复到出厂设置(只恢复配置，不恢复IP地址)
nData1:   UserID
回复：    NVD_DEVICE_RESTORE_ACK
*/

    NVD_DEVICE_RESTORE_ACK,
/*
功能：    设置设备到出厂设置回复。
nData2:   0:成功
说明：    只有管理员可以做
*/

    NVD_DEVICE_RESTORE_IP_REQ,
/*
功能：    设置设备恢复到出厂IP设置(只恢复IP地址，不恢复配置)
nData1:   UserID
回复：    NVD_DEVICE_RESTORE_IP_ACK
*/

    NVD_DEVICE_RESTORE_IP_ACK,
/*
功能：    设置设备到出厂IP设置回复。
nData2:   0:成功
说明：    只有管理员可以做
*/

    NVD_DEVICE_RESTORE_ALL_REQ,
/*
功能：    设置设备恢复到出厂设置(恢复所有，包括IP地址和配置)
nData1:   UserID
回复：    NVD_DEVICE_RESTORE_IP_ACK
*/

    NVD_DEVICE_RESTORE_ALL_ACK,
/*
功能：    设置设备到出厂设置回复。
nData2:   0:成功
说明：    只有管理员可以做
*/

    NVD_DEVICE_BACKUP_ALL_CONFIG_REQ,
/*
功能：   备份配置并回传
nData1:  UserID
nData2:  ChannelID
payload: 4个字节长数据偏移量（为-1时将备份文件删除后直接返回，接收结束后请发送-1）
回复：   NVD_DEVICE_BACKUP_ALL_CONFIG_ACK
说明：   备份的文件通过payload拆成多个包返回，每个包前8个字节是拆包信息，数据总大小（4个字节）+当前偏移量（4个字节），后面是数据
*/

    NVD_DEVICE_BACKUP_ALL_CONFIG_ACK,
/*
功能：备份配置回复
nData1:  UserID
nData2:  0:成功
payload: 拆包之后每一小包的数据，删除文件时为空
*/

    NVD_DEVICE_RESTORE_ALL_CONFIG_REQ,
/*
功能：   恢复配置
nData1:  UserID
nData2:  ChannelID
回复：   NVD_DEVICE_RESTORE_ALL_CONFIG_ACK
说明：   恢复的文件通过payload拆成多个包发送，前8个字节是拆包信息，数据总大小（4个字节）+当前包索引（4个字节），后面是数据
*/

    NVD_DEVICE_RESTORE_ALL_CONFIG_ACK,
/*
功能：   恢复配置回复
nData2:  0:成功
*/

/******************************************************************************************/
    NVD_DEVICE_RESET_REQ = 0x40900,
/*
功能：    复位设备
nData1:   UserID
回复：    NVD_DEVICE_RESET_ACK
说明：    只有管理员可以做
*/

    NVD_DEVICE_RESET_ACK,
/*
功能：    设置设备复位回复。
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_DEVICE_SAVE_CONFIG_REQ = 0x40A00,
/*
功能：    保存设备参数命令
nData1:   UserID
回复：    NVD_DEVICE_SAVE_CONFIG_ACK
*/

    NVD_DEVICE_SAVE_CONFIG_ACK,
/*
功能：    保存设备参数命令回复
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_VIDEO = 0x50000,
    NVD_VIDEO_GET_ENC_PARAM_REQ,
/*
功能：    获取设备编码参数
nData1:   UserID
nData2:   通道号
回复：    NVD_VIDEO_GET_ENC_PARAM_ACK
*/

    NVD_VIDEO_GET_ENC_PARAM_ACK,
/*
功能：    获取设备编码参数回复
nData2:   0:成功
payload:  NVD_VIDEO_ENC_PARA
*/

    NVD_VIDEO_SET_ENC_PARAM_REQ,
/*
功能：    设置设备编码参数
nData1:   UserID
payload:  NVD_VIDEO_ENC_PARA
回复：    NVD_VIDEO_SET_ENC_PARAM_ACK
*/

    NVD_VIDEO_SET_ENC_PARAM_ACK,
/*
功能：    获取设备编码参数回复
nData2:   0:成功
*/

    NVD_VIDEO_MAKE_IDR_NOTIFY,
/*
功能：    触发关键帧
nData1:   UserID
nData2:   通道号
数据：    NVD_ENC_STREAM_TYPE
*/

    NVD_VIDEO_GET_ENC_ADV_PARAM_REQ,
/*
功能：    获取设备编码高级参数
nData1:   UserID
nData2:   通道号
回复：    NVD_VIDEO_GET_ENC_ADV_PARAM_ACK
*/

    NVD_VIDEO_GET_ENC_ADV_PARAM_ACK,
/*
功能：    获取设备编码高级参数回复
nData2:   0:成功
payload:  NVD_VIDEO_ENC_ADV_PARA
*/

    NVD_VIDEO_SET_ENC_ADV_PARAM_REQ,
/*
功能：    设置设备编码高级参数
nData1:   UserID
payload:  NVD_VIDEO_ENC_ADV_PARA
回复：    NVD_VIDEO_SET_ENC_ADV_PARAM_ACK
*/

    NVD_VIDEO_SET_ENC_ADV_PARAM_ACK,
/*
功能：    设置设备编码高级参数回复
nData2:   0:成功
*/

    NVD_VIDEO_SET_ENC_ADV_MODE_REQ,
/*
功能：    设置设备编码高级参数模式
nData1:   UserID
payload:  NVD_ENC_ADV_MODE_PARA
回复：    NVD_VIDEO_SET_ENC_ADV_MODE_ACK
*/

    NVD_VIDEO_SET_ENC_ADV_MODE_ACK,
/*
功能：    设置设备编码高级参数模式回复
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_VIDEO_GET_DISPLAY_CFG_REQ = 0x50100,
/*
功能：    获取设备显示信息
nData1:   UserID
nData2:   通道号
回复：    NVD_VIDEO_GET_DISPLAY_CFG_ACK
*/

    NVD_VIDEO_GET_DISPLAY_CFG_ACK,
/*
功能：    获取设备信息回复
nData2:   0:成功
payload   NVD_DISPLAY_PARA
*/

    NVD_VIDEO_SET_DISPLAY_CFG_REQ,
/*
功能：    设置设备显示信息
nData1:   UserID
payload   NVD_DISPLAY_PARA
回复：    NVD_VIDEO_SET_DISPLAY_CFG_ACK
*/

    NVD_VIDEO_SET_DISPLAY_CFG_ACK,
/*
功能：    设置设备显示信息回复
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_VIDEO_GET_TEXT_OSD_CFG_REQ = 0x50200,
/*
功能：    获取设备文本OSD显示信息
nData1:   UserID
nData2:   通道号
回复：    NVD_VIDEO_GET_TEXT_OSD_CFG_ACK
*/

    NVD_VIDEO_GET_TEXT_OSD_CFG_ACK,
/*
功能：    获取设备文本OSD信息回复
nData2:   0:成功
payload:  NVD_TEXT_OSD_PARA
        payload：NVD_OSD_CFG*4 最多4个
*/

    NVD_VIDEO_SET_TEXT_OSD_CFG_REQ,
/*
功能：    设置设备文本OSD显示信息
nData1:   UserID
nData2:   通道号
payload:  NVD_TEXT_OSD_PARA
回复：    NVD_VIDEO_SET_TEXT_OSD_CFG_ACK
*/

    NVD_VIDEO_SET_TEXT_OSD_CFG_ACK,
/*
功能：    设置设备文本OSD显示信息回复
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_VIDEO_GET_MASK_CFG_REQ = 0x50300,
/*
功能：    获取设备遮挡信息
nData1:   UserID
nData2:   通道号
回复：    NVD_VIDEO_GET_MASK_CFG_ACK
*/

    NVD_VIDEO_GET_MASK_CFG_ACK,
/*
功能：    获取设备遮挡信息回复
nData2:   0:成功
payload:  NVD_MASK_PARA
*/

    NVD_VIDEO_SET_MASK_CFG_REQ,
/*
功能：    设置设备遮挡信息
nData1:   UserID
nData2:   通道号
payload:  NVD_MASK_PARA
回复：    NVD_VIDEO_SET_MASK_CFG_ACK
*/

    NVD_VIDEO_SET_MASK_CFG_ACK,
/*
功能：    设置设备遮挡信息回复
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_VIDEO_GET_MD_CFG_REQ  = 0x50400,
/*
功能：    获取移动侦测参数
nData1:   UserID
nData2:   通道号
回复：    NVD_VIDEO_GET_MD_CFG_ACK
*/

    NVD_VIDEO_GET_MD_CFG_ACK,
/*
功能：    获取移动侦测参数回复
nData2:   0:成功
payload:  NVD_MD_PARA
*/

    NVD_VIDEO_SET_MD_CFG_REQ,
/*
功能：    设置移动侦测参数
nData1:   UserID
nData2:   通道号
payload:  NVD_MD_PARA
回复：    NVD_VIDEO_SET_MD_CFG_ACK
*/

    NVD_VIDEO_SET_MD_CFG_ACK,
/*
功能：    设置移动侦测参数回复
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_VIDEO_GET_OD_CFG_REQ  = 0x50500,
/*
功能：    获取遮挡侦测参数
nData1:   UserID
nData2:   通道号
回复：    NVD_VIDEO_GET_OD_CFG_ACK
*/

    NVD_VIDEO_GET_OD_CFG_ACK,
/*
功能：    获取遮挡侦测参数回复
nData2:   0:成功
payload:  NVD_OD_PARA
*/

    NVD_VIDEO_SET_OD_CFG_REQ,
/*
功能：    设置遮挡侦测参数
nData1:   UserID
nData2:   通道号
payload:  NVD_OD_PARA
回复：    NVD_VIDEO_SET_OD_CFG_ACK
*/

    NVD_VIDEO_SET_OD_CFG_ACK,
/*
功能：    设置遮挡侦测参数回复
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_VIDEO_GET_SNAP_CFG_REQ  = 0x50600,
/*
功能：    获取抓拍参数
nData1:   UserID
nData2:   通道号
回复：    NVD_VIDEO_GET_SNAP_CFG_ACK
*/

    NVD_VIDEO_GET_SNAP_CFG_ACK,
/*
功能：    获取抓拍参数回复
nData2:   0:成功
payload:  NVD_SNAP_PARA
*/

    NVD_VIDEO_SET_SNAP_CFG_REQ,
/*
功能：    设置抓拍参数
nData1:   UserID
nData2:   通道号
payload:  NVD_SNAP_PARA
回复：    NVD_VIDEO_SET_SNAP_CFG_ACK
*/

    NVD_VIDEO_SET_SNAP_CFG_ACK,
/*
功能：    设置抓拍参数回复
nData2:   0:成功
*/

    NVD_VIDEO_SNAP_REQ,
/*
功能：    抓拍图像
nData1:   UserID
nData2:   通道号
回复：    NVD_VIDEO_JPEG_SNAP_ACK
*/

    NVD_VIDEO_SNAP_ACK,
/*
功能：    抓拍图像回复
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_VIDEO_GET_ST_CFG_REQ  = 0x50700,
/*
功能：    获取场景转换侦测参数
nData1:   UserID
nData2:   通道号
回复：    NVD_VIDEO_GET_ST_CFG_ACK
*/

    NVD_VIDEO_GET_ST_CFG_ACK,
/*
功能：    获取场景转换侦测参数回复
nData2:   0:成功
payload:  NVD_ST_PARA
*/

    NVD_VIDEO_SET_ST_CFG_REQ,
/*
功能：    设置场景转换侦测参数
nData1:   UserID
nData2:   通道号
payload:  NVD_ST_PARA
回复：    NVD_VIDEO_SET_ST_CFG_ACK
*/

    NVD_VIDEO_SET_ST_CFG_ACK,
/*
功能：    设置场景转换侦测参数回复
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_VIDEO_GET_ROI_CFG_REQ  = 0x50800,
/*
功能：    获取图像增强参数
nData1:   UserID
nData2:   通道号
回复：    NVD_VIDEO_GET_ROI_CFG_ACK
*/

    NVD_VIDEO_GET_ROI_CFG_ACK,
/*
功能：    获取图像增强参数回复
nData2:   0:成功
payload:  NVD_ROI_PARA
*/

    NVD_VIDEO_SET_ROI_CFG_REQ,
/*
功能：    设置图像增强参数
nData1:   UserID
nData2:   通道号
payload:  NVD_ROI_PARA
回复：    NVD_VIDEO_SET_ROI_CFG_ACK
*/

    NVD_VIDEO_SET_ROI_CFG_ACK,
/*
功能：    设置图像增强参数回复
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_VIDEO_GET_REC_CFG_REQ  = 0x50900,
/*
功能：    获取录像设置参数
nData1:   UserID
nData2:   通道号
回复：    NVD_SD_GET_REC_CFG_ACK
*/

    NVD_VIDEO_GET_REC_CFG_ACK,
/*
功能：    获取录像设置参数回复
nData2:   0:成功
payload:  NVD_REC_PARA
*/

    NVD_VIDEO_SET_REC_CFG_REQ,
/*
功能：    设置录像设置参数
nData1:   UserID
nData2:   通道号
payload:  NVD_REC_PARA
回复：    NVD_SD_SET_REC_CFG_ACK
*/

    NVD_VIDEO_SET_REC_CFG_ACK,
/*
功能：    设置录像设置参数回复
nData2:   0:成功
*/

    NVD_VIDEO_REC_MANUAL_START_REQ,
/*
功能：    手动开始录像
nData1:   UserID
nData2:   通道号
回复：    NVD_VIDEO_REC_MANUAL_START_ACK
*/

    NVD_VIDEO_REC_MANUAL_START_ACK,
/*
功能：    手动开始录像回复
nData2:   0:成功
*/

    NVD_VIDEO_REC_MANUAL_STOP_REQ,
/*
功能：    手动结束录像
nData1:   UserID
nData2:   通道号
回复：    NVD_VIDEO_REC_MANUAL_STOP_ACK
*/

    NVD_VIDEO_REC_MANUAL_STOP_ACK,
/*
功能：    手动结束录像回复
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_VIDEO_GET_IMAGE_PARAM_REQ  = 0x50a00,
/*
功能：    获取图像参数
nData1:   UserID
payload:  NVD_IMAGE_PARA
回复：    NVD_VIDEO_GET_IMAGE_PARAM_ACK
*/

    NVD_VIDEO_GET_IMAGE_PARAM_ACK,
/*
功能：    获取图像参数回复
nData2:   0:成功
*/

    NVD_VIDEO_SET_IMAGE_PARAM_REQ,
/*
功能：    设置图像参数
nData1:   UserID
payload:  NVD_IMAGE_PARA
回复：    NVD_VIDEO_SET_IMAGE_PARAM_ACK
*/

    NVD_VIDEO_SET_IMAGE_PARAM_ACK,
/*
功能：    设置图像参数回复
nData2:   0:成功
*/

    NVD_VIDEO_SET_IMAGE_DEFAULT_REQ,
/*
功能：    设置图像恢复参数
nData1:   UserID
payload:  NVD_IMAGE_PARA
回复：    NVD_VIDEO_SET_IMAGE_DEFAULT_ACK
*/

    NVD_VIDEO_SET_IMAGE_DEFAULT_ACK,
/*
功能：    设置图像恢复参数回复
nData2:   0:成功
*/

    NVD_VIDEO_GET_IMAGE_PARAM_ADV_REQ,
/*
功能：    获取图像高级参数
 nData1:   UserID
 payload:  NVD_IMAGE_PARA_ADV
 回复：    NVD_VIDEO_GET_IMAGE_PARAM_ADV_ACK
 */

    NVD_VIDEO_GET_IMAGE_PARAM_ADV_ACK,
/*
 功能：    获取图像高级参数回复
nData2:   0:成功
 */

    NVD_VIDEO_SET_IMAGE_PARAM_ADV_REQ,
/*
功能：    设置图像高级参数
nData1:   UserID
payload:  NVD_IMAGE_PARA_ADV
回复：    NVD_VIDEO_SET_IMAGE_PARAM_ADV_ACK
*/

    NVD_VIDEO_SET_IMAGE_PARAM_ADV_ACK,
/*
功能：    设置图像高级参数回复
nData2:   0:成功
*/

    NVD_VIDEO_SET_IMAGE_DEFAULT_ADV_REQ,
/*
功能：    设置图像恢复高级参数
nData1:   UserID
payload:  NVD_IMAGE_PARA_ADV
回复：    NVD_VIDEO_SET_IMAGE_DEFAULT_ADV_ACK
*/

    NVD_VIDEO_SET_IMAGE_DEFAULT_ADV_ACK,
/*
功能：    设置图像恢复高级参数回复
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_AUDIO = 0x60000,
    NVD_AUDIO_IN_GET_CFG_REQ,
/*
功能：    获取音频输入参数
nData1:   UserID
nData2:   音频解码通道序号 0xFF 获取全部
回复：    NVD_AUDIO_IN_GET_CFG_ACK
*/

    NVD_AUDIO_IN_GET_CFG_ACK,
/*
功能：    获取音频输入参数回复
nData2:   0:成功
payload： NVD_AUDIO_IN_PARA
*/

    NVD_AUDIO_IN_SET_CFG_REQ,
/*
功能：    设置音频输入参数
nData1:   UserID
payload:  NVD_AUDIO_IN_PARA
回复：    NVD_AUDIO_IN_SET_CFG_ACK
*/

    NVD_AUDIO_IN_SET_CFG_ACK,
/*
功能：    设置音频输入参数回复
nData2:   0:成功
*/

    NVD_AUDIO_OUT_GET_CFG_REQ,
/*
功能：    获取音频输出参数
nData1:   UserID
nData2:   音频解码通道序号 0xFF 获取全部
回复：    NVD_AUDIO_OUT_GET_CFG_ACK
*/

    NVD_AUDIO_OUT_GET_CFG_ACK,
/*
功能：    获取音频输出参数回复
nData2:   0:成功
payload： NVD_AUDIO_OUT_PARA
*/

    NVD_AUDIO_OUT_SET_CFG_REQ,
/*
功能：    设置音频输出参数
nData1:   UserID
payload:  NVD_AUDIO_OUT_PARA
回复：    NVD_AUDIO_OUT_SET_CFG_ACK
*/

    NVD_AUDIO_OUT_SET_CFG_ACK,
/*
功能：    设置音频输出参数回复
nData2:   0:成功
*/

    NVD_AUDIO_OUT_OPEN_REQ,
/*
功能：    设置音频输出打开
nData1:   UserID
nData2:   通道号
*/

    NVD_AUDIO_OUT_OPEN_ACK,
/*
功能：    设置音频输出打开回复
nData2:   0:成功
*/

    NVD_AUDIO_OUT_CLOSE_REQ,
/*
功能：    设置音频输出关闭
nData1:   UserID
nData2:   通道号
*/

    NVD_AUDIO_OUT_CLOSE_ACK,
/*
功能：    设置音频输出关闭
nData2:   0:成功
*/

    NVD_AUDIO_OUT_SET_VOLUME_REQ,
/*
功能：    设置音频输出音量
nData1:   UserID
nData2:   通道号
*/

    NVD_AUDIO_OUT_SET_VOLUME_ACK,
/*
功能：    设置音频输出音量回复
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_STREAM = 0x70000,
    NVD_STREAM_OPEN_REQ,
/*
功能：    打开流
nData1:   UserID
payload:  NVD_PLAY_PARA
回复：    NVD_OPEN_STREAM_ACK
*/

    NVD_STREAM_OPEN_ACK,
/*
功能：    打开流回复
nData1:   streamId
nData2:   0:成功
*/

    NVD_STREAM_CLOSE_REQ,
/*
功能：    关闭流
nData1:   UserID
nData2:   streamId
回复：    NVD_CLOSE_STREAM_ACK
*/

    NVD_STREAM_CLOSE_ACK,
/*
功能：    关闭流回复
nData2:   0:成功
*/

    NVD_STREAM_CHANGE_REQ,
/*
功能：    切换主从流
nData1：  UserID
nData2：  streamId
回复：    NVD_CHANGE_STREAM_ACK
*/

    NVD_STREAM_CHANGE_ACK,
/*
功能：    切换主从流回复
nData2:   0:成功
*/

    NVD_STREAM_UP = 0x70100,
/*
功能：    实时流上传
nData1:   UserID
payload:  流
回复：    无
*/

    NVD_STREAM_DOWN,
/*
功能：    对讲流下载
nData1:   UserID
payload:  流
回复：    无
*/

    NVD_STREAM_COM_UP,
/*
功能：    串口流上传
nData1:   UserID
payload:  流
回复：    无
*/

    NVD_STREAM_ALARM_UP,
/*
功能：    告警信息上传
nData1:   UserID
payload:  流
回复：    无
*/

    NVD_STREAM_PTZ_INFO_UP,
/*
功能：    ptz信息上传
nData1:   UserID
payload:  流
回复：    无
*/

    NVD_STREAM_OPEN_INFO_UP,
/*
功能：    透明信息上传
nData1:   UserID
payload:  流
回复：    无
*/
    
    NVD_STREAM_ALARM_CENTER_UP,
/*
功能：    告警信息上传到告警中心
nData1:      0
payload_len: sizeof(NVD_ALARM_REPORT_INFO)
payload:  NVD_ALARM_REPORT_INFO
回复：    无
*/
    NVD_STREAM_PLAYBACK=0x70200,
    NVD_STREAM_PLAYBACK_OPEN_REQ,
/*
功能：    建立一个回放流链接
nData1:   UserID
payload:  NULL
回复：    NVD_STREAM_PLAYBACK_OPEN_ACK
*/
    NVD_STREAM_PLAYBACK_OPEN_ACK,
/*
功能：    打开回放流回复
nData1:   PlaybackStreamId
nData2:   0:成功
*/
    NVD_STREAM_PLAYBACK_CLOSE_REQ,
/*
功能：    关闭回放流
nData1:   UserID
nData2:   playbackStreamId
回复：    NVD_STREAM_PLAYBACK_CLOSE_ACK
*/
    NVD_STREAM_PLAYBACK_CLOSE_ACK,
/*
功能：    关闭回放流回复
nData2:   0:成功
*/ 
    NVD_STREAM_PLAYBACK_PLAY_REQ,
/*
功能：    打开回放下载流,为下载做准备
nData1:   UserID
nData2:   playbackStreamId
payload_len: sizeof(NVD_RECORD_PLAYBACK)
payload:  NVD_RECORD_PLAYBACK
回复：    NVD_STREAM_PLAYBACK_PLAY_ACK
*/
    NVD_STREAM_PLAYBACK_PLAY_ACK,
/*
功能：    打开回放下载流回复
nData1:  
nData2:  0:成功  
*/
    NVD_STREAM_PLAYBACK_STOP_REQ,
/*
功能：    关闭回放下载流
nData1:   UserID
nData2:   playbackStreamId
回复：    NVD_STREAM_PLAYBACK_STOP_ACK
*/
    NVD_STREAM_PLAYBACK_STOP_ACK,
/*
功能：    关闭回放下载流回复
nData1:  playbackStreamId
nData2:  0:成功  
*/
    NVD_STREAM_PLAYBACK_SEEK_FRAME_REQ,
/*
功能：    搜索音视频帧
nData1:   UserID
nData2:   playbackStreamId
payload_len: sizeof(NVD_RECORD_PLAYBACK_SEEK)
payload:  NVD_RECORD_PLAYBACK_SEEK
回复：    NVD_STREAM_PLAYBACK_SEEK_FRAME_ACK
*/
    NVD_STREAM_PLAYBACK_SEEK_FRAME_ACK,
/*
功能：    搜索音视频帧回复
nData1:  playbackStreamId
nData2:  0:成功  
*/
    NVD_STREAM_PLAYBACK_GET_PACKET_REQ,
/*
功能：    请求下载一帧音视频数据
payload_len: 0
payload:  NULL
回复：    无
*/
    NVD_STREAM_PLAYBACK_GET_PACKET_ACK,
/*
功能：       回放流上传
nData1:     流状态,-1 failed,-2 eof,>0 framesize
payload:    流
回复：       无
*/
    NVD_STREAM_PLAYBACK_FIND_FILE_REQ,
/*
功能：开启一次查找操作
nData1:UserID
nData2:playbackStreamId
payload_len:sizeof(NVD_RECORD_FILE_FIND)
payload:NVD_RECORD_FILE_FIND
回复：NVD_STREAM_PLAYBACK_FIND_FILE_ACK
*/
    NVD_STREAM_PLAYBACK_FIND_FILE_ACK,
/*
功能：    开启查找回复
nData1:  playbackStreamId
nData2:  0:成功  
*/
    NVD_STREAM_PLAYBACK_FIND_NEXT_FILE_REQ,//
/*
功能:查找下一个文件
nData1:UserID
nData2:playbackStreamId
*/
    NVD_STREAM_PLAYBACK_FIND_NEXT_FILE_ACK,
/*
功能:查找下一个文件回复
nData1:playbackStreamId
nData2: 0成功,其他情况均停止查找
payload_len:sizeof(NET_RECORDFILE_INFO)
payload:NET_RECORDFILE_INFO
*/
    NVD_STREAM_PLAYBACK_FIND_FILE_CLOSE_REQ,//
/*
功能:关闭文件查找
nData1:UserID
nData2:playbackStreamId
回复:NVD_STREAM_PLAYBACK_FIND_FILE_CLOSE_ACK
*/
    NVD_STREAM_PLAYBACK_FIND_FILE_CLOSE_ACK,
/*
功能:关闭文件查找回复
nData1:playbackStreamId
nData2: 0成功
*/

/******************************************************************************************/
    NVD_ALARM = 0x80000,
/******************************************************************************************/
    NVD_ALARM_GET_ALARM_IN_CFG_REQ,
/*
功能：    获取报警输入参数
nData1:   UserID
nData2:   DI序号  0xFF 获取全部
回复：    NVD_ALARM_GET_ALARM_IN_CFG_ACK
*/

    NVD_ALARM_GET_ALARM_IN_CFG_ACK,
/*
功能：    获取报警输入参数回复
nData2:   0:成功
payload_len: sizeof(NVD_ALARM_IN_PARA)
payload： NVD_ALARM_IN_PARA
*/

    NVD_ALARM_SET_ALARM_IN_CFG_REQ,
/*
功能：    设置报警输入参数
nData1：  UserID
nData2:   DI序号
payload： NVD_ALARM_IN_PARA
回复：    NVD_ALARM_SET_ALARM_IN_CFG_ACK
*/

    NVD_ALARM_SET_ALARM_IN_CFG_ACK,
/*
功能：    设置报警输入参数回复
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_ALARM_GET_ALARM_OUT_CFG_REQ,
/*
功能：    获取报警输出参数
nData1:   UserID
nData2:   DO序号
回复：    NVD_ALARM_GET_ALARM_OUT_CFG_ACK
*/

    NVD_ALARM_GET_ALARM_OUT_CFG_ACK,
/*
功能：    获取报警输出参数回复
nData2:   0:成功
payload:  NVD_ALARM_OUT_PARA
*/

    NVD_ALARM_SET_ALARM_OUT_CFG_REQ,
/*
功能：    设置报警输出参数
nData1:   UserID
nData2:   DO序号
payload:  NVD_ALARM_OUT_PARA
回复：    NVD_ALARM_SET_ALARM_OUT_CFG_ACK
*/

    NVD_ALARM_SET_ALARM_OUT_CFG_ACK,
/*
功能：    设置报警输出参数回复
nData2:   0:成功
*/

    NVD_ALARM_OUT_OPEN_REQ,
/*
功能：    手动打开alarmOut告警请求
nData1:   UserID
nData2:   DO序号
payload:  
回复：    NVD_ALARM_OUT_OPEN_ACK
*/

    NVD_ALARM_OUT_OPEN_ACK,
/*
功能：    手动打开alarmOut告警响应
nData2:   0:成功
*/

    NVD_ALARM_OUT_CLOSE_REQ,
/*
功能：    手动关闭alarmOut告警请求
nData1:   UserID
nData2:   DO序号
payload:  
回复：    NVD_ALARM_OUT_CLOSE_ACK
*/

    NVD_ALARM_OUT_CLOSE_ACK,
/*
功能：    手动关闭alarmOut告警响应
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_COM = 0x90000,
    NVD_COM_GET_CFG_REQ,
/*
功能：    获取透明串口参数
nData1:   UserID
nData2:   通道通道号，口序号 0xFF表示全部获取
回复：    NVD_COM_GET_CFG_ACK
*/

    NVD_COM_GET_CFG_ACK,
/*
功能：    获取透明串口参数回复
nData2:   0:成功
payload： NVD_COM_PARA
*/

    NVD_COM_SET_CFG_REQ,
/*
功能：    设置透明串口参数
nData1:   UserID
payload:  NVD_COM_PARA
回复：    NVD_COM_SET_CFG_ACK
*/

    NVD_COM_SET_CFG_ACK,
/*
功能：    设置透明串口参数回复
nData2:   0:成功
*/

    NVD_COM_SEND_DATA_REQ,
/*
功能：    发送透明数据
nData1:   UserID
nData2:   串口序号
playload: buffer
payload_len:  buf len
回复：    NVD_COM_SEND_DATA_ACK
*/

    NVD_COM_SEND_DATA_ACK,
/*
功能：    发送透明数据回复
nData2:   0:成功
payload： 0
*/

/******************************************************************************************/
    NVD_PTZ = 0xA0000,
    NVD_PTZ_GET_COM_CFG_REQ,
/*
功能：    获取ptz 非透明串口参数 非透明串口
nData1:   UserID
nData2:   通道通道号，口序号 0xFF表示全部获取
回复：    NVD_PTZ_GET_COM_CFG_ACK
*/

    NVD_PTZ_GET_COM_CFG_ACK,
/*
功能：    获取ptz 非透明串口参数回复
nData2:   0:成功
payload： NVD_PTZ_COM_PARA
*/

    NVD_PTZ_SET_COM_CFG_REQ,
/*
功能：    设置ptz 非透明串口参数
nData1:   UserID
payload:  NVD_PTZ_COM_PARA
回复：    NVD_PTZ_SET_COM_CFG_ACK
*/

    NVD_PTZ_SET_COM_CFG_ACK,
/*
功能：    设置ptz 非透明串口参数回复
nData2:   0:成功
*/

    NVD_PTZ_SEND_COM_DATA_REQ,
/*
功能：    向ptz 非透明串口发送数据
nData1:   UserID
payload:  NVD_PTZ_CTRL_DATA
回复：    NVD_PTZ_SEND_COM_DATA_ACK
*/

    NVD_PTZ_SEND_COM_DATA_ACK,
/*
功能：    向ptz 非透明串口发送数据
nData2:   0:成功
*/

    NVD_PTZ_GET_PRESET_REQ,
/*
功能：    获取ptz 预置位 参数
nData1:   UserID
nData2:   串口序号 0xFF表示全部获取
回复：    NVD_PTZ_GET_PRESET_ACK
*/

    NVD_PTZ_GET_PRESET_ACK,
/*
功能：    获取ptz 预置位 参数回复
nData2:   0:成功
payload： NVD_PTZ_PRESET_PARA
*/

    NVD_PTZ_CTRL_PRESET_REQ,
/*
功能：    控制ptz 预置位 参数
nData1:   UserID
payload:  NVD_PTZ_CTRL_PRESET_PARA ************注意和获取的结构体不一样*************
回复：    NVD_PTZ_CTRL_PRESET_ACK
*/

    NVD_PTZ_CTRL_PRESET_ACK,
/*
功能：    控制ptz 预置位 参数回复
nData2:   0:成功
*/

    NVD_PTZ_GET_TRACK_REQ,
/*
功能：    获取ptz 轨迹 参数
nData1:   UserID
nData2:   串口序号 0xFF表示全部获取
回复：    NVD_PTZ_GET_TRACK_ACK
*/

    NVD_PTZ_GET_TRACK_ACK,
/*
功能：    获取ptz 轨迹 参数回复
nData2:   0:成功
payload： NVD_PTZ_TRACK_PARA
*/

    NVD_PTZ_CTRL_TRACK_REQ,
/*
功能：    控制ptz 轨迹 参数
nData1:   UserID
payload:  NVD_PTZ_CTRL_TRACK_PARA ************注意和获取的结构体不一样*************
回复：    NVD_PTZ_CTRL_TRACK_ACK
*/

    NVD_PTZ_CTRL_TRACK_ACK,
/*
功能：    控制ptz 轨迹 参数回复
nData2:   0:成功
*/

    NVD_PTZ_GET_CRUISE_REQ,
/*
功能：    获取ptz 巡航 参数
nData1:   UserID
nData2:   串口序号 0xFF表示全部获取
回复：    NVD_PTZ_GET_CRUISE_ACK
*/

    NVD_PTZ_GET_CRUISE_ACK,
/*
功能：    获取ptz 巡航 参数回复
nData2:   0:成功
payload： NVD_PTZ_CRUISE_PARA
*/

    NVD_PTZ_CTRL_CRUISE_REQ,
/*
功能：    控制ptz 巡航
nData1:   UserID
payload:  NVD_PTZ_CTRL_CRUISE_PARA ************注意和获取的结构体不一样*************
回复：    NVD_PTZ_SET_CRUISE_ACK
*/

    NVD_PTZ_CTRL_CRUISE_ACK,
/*
功能：    控制ptz 巡航回复
nData2:   0:成功
*/

    NVD_PTZ_GET_CRUISE_POINT_CFG_REQ,
/*
功能：    获取ptz 巡航点 参数
nData1:   UserID
nData2:   串口序号 0xFF表示全部获取
回复：    NVD_PTZ_GET_CRUISE_POINT_CFG_ACK
*/

    NVD_PTZ_GET_CRUISE_POINT_CFG_ACK,
/*
功能：    获取ptz 巡航点 参数
nData2:   0:成功
payload： NVD_PTZ_CRUISE_POINT_PARA
*/

    NVD_PTZ_SET_CRUISE_POINT_CFG_REQ,
/*
功能：    设置ptz 巡航点 参数
nData1:   UserID
payload:  NVD_PTZ_CRUISE_POINT_PARA
回复：    NVD_PTZ_SET_CRUISE_POINT_CFG_ACK
*/

    NVD_PTZ_SET_CRUISE_POINT_CFG_ACK,
/*
功能：    设置ptz 巡航点 参数
nData2:   0:成功
*/

    NVD_PTZ_GET_DEFAULT_PRESET_CFG_REQ,
/*
功能：    获取ptz 自动归位 参数
nData1:   UserID
nData2:   0xFF表示全部获取
回复：    NVD_PTZ_GET_DEFAULT_PRESET_CFG_ACK
*/

    NVD_PTZ_GET_DEFAULT_PRESET_CFG_ACK,
/*
功能：    获取ptz 自动归位 参数
nData2:   0:成功
payload： NVD_PTZ_DEFAULT_PRESET_PARA
*/

    NVD_PTZ_SET_DEFAULT_PRESET_CFG_REQ,
/*
功能：    设置ptz 自动归位 参数
nData1:   UserID
payload:  NVD_PTZ_DEFAULT_PRESET_PARA
回复：    NVD_PTZ_SET_DEFAULT_PRESET_CFG_ACK
*/

    NVD_PTZ_SET_DEFAULT_PRESET_CFG_ACK,
/*
功能：    设置ptz 自动归位 参数
nData2:   0:成功
*/

    NVD_PTZ_CTRL_RESTORE_AND_RESET_REQ = 0xA0100,
/*
功能：    控制ptz 单片机，机芯复位, 复位的时候，同时恢复配置
nData1:   UserID
payload:  int flag, 1:单片机复位，2:一体化机芯复位, 3:一体化机芯和单片机同时复位
回复：    NVD_PTZ_CTRL_RESTORE_AND_RESET_ACK
*/

    NVD_PTZ_CTRL_RESTORE_AND_RESET_ACK,
/*
功能：    控制ptz 单片机，机芯复位
nData2:   0:成功
*/

    NVD_PTZ_CTRL_3D_LOCATE_REQ,
/*
功能：    控制ptz 3D定位 请求
nData1:   UserID
payload:  NVD_PTZ_3D_LOCATE_DATA
回复：    NVD_PTZ_SEND_3D_LOCATE_DATA_ACK
*/

    NVD_PTZ_CTRL_3D_LOCATE_ACK,
/*
功能：    控制ptz 3D定位 回应
nData2:   0:成功
*/

    NVD_PTZ_GET_UNI_MODULE_CFG_REQ  = 0xA0200,
/*
功能：    获取一体化机芯配置请求
nData1:   UserID
nData2:   viNo=0
payload:  NVD_PTZ_UNI_MODULE_DATA,只需要填上seq,从0开始编号
回复：    NVD_PTZ_GET_UNI_MODULE_CFG_ACK
*/

    NVD_PTZ_GET_UNI_MODULE_CFG_ACK,
/*
功能：    获取一体化机芯配置回应 每次回复一条对应序列号的数据
nData2:   0:成功
payload： NVD_PTZ_UNI_MODULE_DATA
*/

    NVD_PTZ_SET_UNI_MODULE_CFG_REQ,
/*
功能：    设置一体化机芯配置请求 每次设置一条对应序列号的数据
nData1:   UserID
nData2:   viNo=0
payload:  NVD_PTZ_UNI_MODULE_DATA
回复：    NVD_PTZ_SET_UNI_MODULE_CFG_ACK
*/

    NVD_PTZ_SET_UNI_MODULE_CFG_ACK,
/*
功能：    设置一体化机芯配置回应
nData2:   0:成功
*/

    NVD_PTZ_SAVE_UNI_MODULE_CFG_REQ,
/*
功能：    保存一体化机芯配置请求
nData1:   UserID
nData2:   viNo=0
payload:  0
回复：    NVD_PTZ_SAVE_UNI_MODULE_CFG_ACK
*/

    NVD_PTZ_SAVE_UNI_MODULE_CFG_ACK,
/*
功能：    保存一体化机芯配置 回应
nData2:   0:成功
*/


/******************************************************************************************/
    NVD_KEYBOARD = 0xB0000,
    NVD_KEYBOARD_SEND_CMD_REQ,
/*
功能：    模拟键盘发送命令请求
nData1:   UserID
nData2:   通道通道号
payload： NVD_KEYBOARD_CTRL_DATA
回复：    NVD_KEYBOARD_SEND_CMD_ACK
*/

    NVD_KEYBOARD_SEND_CMD_ACK,
/*
功能：    模拟键盘发送命令回复
nData2:   0:成功
payload： 无
*/

/******************************************************************************************/
    NVD_LOG = 0xC0000,
    NVD_LOG_GET_CONFIG_REQ,
/*
功能：    获取网络日志相关配置
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_LOG_GET_CONFIG_ACK,
/*
功能：    响应获取网络日志相关配置
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_NET_LOG_PARA)
* payload:     NVD_NET_LOG_PARA
*/

    NVD_LOG_SET_CONFIG_REQ,
/*
功能：    设置网络日志相关配置
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: sizeof(NVD_NET_LOG_PARA)
* payload:     NVD_NET_LOG_PARA
*/

    NVD_LOG_SET_CONFIG_ACK,
/*
功能：    响应设置网络日志相关配置
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_LOG_KEEPALIVE_REQ,
/*
功能：    日志保活请求，有IPC发起
* nData1:      0
* payload_len: 0
* payload:     NULL
*/

    NVD_LOG_KEEPALIVE_ACK,
/*
功能：    日志保活请求
* nData2:      0:成功
* payload_len: 0
* payload:     NULL
*/

    NVD_LOG_INFO_UP,
/*
功能：    log信息上传
* nData1:      0
* payload_len: 日志的长度
* payload:     日志内容,采用NVD_LOG_MESSAGE
* 回复：    无
*/

/******************************************************************************************/
    NVD_IVA = 0xD0000,
    NVD_IVA_GET_LPR_CONFIG_REQ,
/*
功能：    获取智能车牌识别相关配置
* data1:
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_LPR_CONFIG_ACK,
/*
功能：    响应智能车牌识别相关配置
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_IVA_LPR_PARA)
* payload:     NVD_IVA_LPR_PARA
*/

    NVD_IVA_SET_LPR_CONFIG_REQ,
/*
功能：    设置智能车牌识别相关配置
* data1:
* data2:       unused
* payload_len: sizeof(NVD_IVA_LPR_PARA)
* payload:     NVD_IVA_LPR_PARA
*/

    NVD_IVA_SET_LPR_CONFIG_ACK,
/*
功能：    响应智能车牌识别相关配置
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_FR_CONFIG_REQ,
/*
功能：    获取智能人脸识别相关配置
* data1:
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_FR_CONFIG_ACK,
/*
功能：    响应智能人脸识别相关配置
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_IVA_FR_PARA)
* payload:     NVD_IVA_FR_PARA
*/

    NVD_IVA_SET_FR_CONFIG_REQ,
/*
功能：    设置智能人脸识别相关配置
* data1:
* data2:       unused
* payload_len: sizeof(NVD_IVA_FR_PARA)
* payload:     NVD_IVA_FR_PARA
*/

    NVD_IVA_SET_FR_CONFIG_ACK,
/*
功能：    响应智能人脸识别相关配置
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/


    NVD_IVA_GET_STANDARD_CONFIG_REQ = 0xD0100,
/*
功能：    获取智能基本参数配置
* data1:
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_STANDARD_CONFIG_ACK,
/*
功能：    响应智能基本参数配置
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_IVA_STANDARD_PARA)
* payload:     NVD_IVA_STANDARD_PARA
*/

    NVD_IVA_SET_STANDARD_CONFIG_REQ,
/*
功能：    设置智能基本参数配置
* data1:
* data2:       unused
* payload_len: sizeof(NVD_IVA_STANDARD_PARA)
* payload:     NVD_IVA_STANDARD_PARA
*/

    NVD_IVA_SET_STANDARD_CONFIG_ACK,
/*
功能：    响应智能基本参数配置
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_ADVANCED_CONFIG_REQ,
/*
功能：    获取智能高级参数配置
* data1:
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_ADVANCED_CONFIG_ACK,
/*
功能：    响应智能高级参数配置
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_IVA_ADVANCED_PARA)
* payload:     NVD_IVA_ADVANCED_PARA
*/

    NVD_IVA_SET_ADVANCED_CONFIG_REQ,
/*
功能：    设置智能高级参数配置
* data1:
* data2:       unused
* payload_len: sizeof(NVD_IVA_ADVANCED_PARA)
* payload:     NVD_IVA_ADVANCED_PARA
*/

    NVD_IVA_SET_ADVANCED_CONFIG_ACK,
/*
功能：    响应智能高级参数配置
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_CORDON_CONFIG_REQ,
/*
功能：    获取智能警戒线配置
* data1:
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_CORDON_CONFIG_ACK,
/*
功能：    响应智能警戒线配置
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_IVA_CORDON_PARA)
* payload:     NVD_IVA_CORDON_PARA
*/

    NVD_IVA_SET_CORDON_CONFIG_REQ,
/*
功能：    设置智能警戒线配置
* data1:
* data2:       unused
* payload_len: sizeof(NVD_IVA_CORDON_PARA)
* payload:     NVD_IVA_CORDON_PARA
*/

    NVD_IVA_SET_CORDON_CONFIG_ACK,
/*
功能：    响应智能警戒线配置
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_PPL_COUNTER_CONFIG_REQ,
/*
功能：    获取智能人流统计配置
* data1:
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_PPL_COUNTER_CONFIG_ACK,
/*
功能：    响应智能人流统计配置
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_IVA_PPL_COUNTER_PARA)
* payload:     NVD_IVA_PPL_COUNTER_PARA
*/

    NVD_IVA_SET_PPL_COUNTER_CONFIG_REQ,
/*
功能：    设置智能人流统计配置
* data1:
* data2:       unused
* payload_len: sizeof(NVD_IVA_PPL_COUNTER_PARA)
* payload:     NVD_IVA_PPL_COUNTER_PARA
*/

    NVD_IVA_SET_PPL_COUNTER_CONFIG_ACK,
/*
功能：    响应智能人流统计配置
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_VEH_COUNTER_CONFIG_REQ,
/*
功能：    获取智能车流统计配置
* data1:
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_VEH_COUNTER_CONFIG_ACK,
/*
功能：    响应智能车流统计配置
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_IVA_VEH_COUNTER_PARA)
* payload:     NVD_IVA_VEH_COUNTER_PARA
*/

    NVD_IVA_SET_VEH_COUNTER_CONFIG_REQ,
/*
功能：    设置智能车流统计配置
* data1:
* data2:       unused
* payload_len: sizeof(NVD_IVA_VEH_COUNTER_PARA)
* payload:     NVD_IVA_VEH_COUNTER_PARA
*/

    NVD_IVA_SET_VEH_COUNTER_CONFIG_ACK,
/*
功能：    响应智能车流统计配置
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_HL_CONFIG_REQ,
/*
功能：    获取智能身高线配置
* data1:
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_HL_CONFIG_ACK,
/*
功能：    响应智能身高线配置
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_IVA_HL_PARA)
* payload:     NVD_IVA_HL_PARA
*/

    NVD_IVA_SET_HL_CONFIG_REQ,
/*
功能：    设置智能身高线配置
* data1:
* data2:       unused
* payload_len: sizeof(NVD_IVA_HL_PARA)
* payload:     NVD_IVA_HL_PARA
*/

    NVD_IVA_SET_HL_CONFIG_ACK,
/*
功能：    响应智能身高线配置
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

/******************************************************************************************/
    NVD_SD = 0xE0000,
    NVD_SD_GET_INFO_REQ,
/*
功能：  获取SD卡相关配置
ndata1: UserID
ndata2: 通道号
回复：  NVD_SD_GET_INFO_ACK
*/

    NVD_SD_GET_INFO_ACK,
/*
功能:        获取SD卡相关配置回复
ndata2:      NVD_ERROR_NUM
payload_len: sizeof(NVD_SD_PARA)
payload:     NVD_SD_PARA
*/

    NVD_SD_UMOUNT_REQ,
/*
功能：    卸载SD卡
nData1:   UserID
nData2:   通道号
回复：    NVD_SD_UMOUNT_ACK
*/

    NVD_SD_UMOUNT_ACK,
/*
功能：    卸载SD卡回复
nData2:   0:成功
*/

    NVD_SD_FORMAT_REQ,
/*
功能：    格式化SD卡
nData1:   UserID
nData2:   通道号
回复：    NVD_SD_FORMAT_ACK
*/

    NVD_SD_FORMAT_ACK,
/*
功能：    格式化SD卡回复
nData2:   0:成功
*/

    NVD_SD_QUERY_DIR_REQ,
/*
功能：          查询SD卡中目录
ndata1:         UserID
ndata2:         unused
payload_len:    目录路径的长度
payload:        需要查询的目录路径，如: /sd/pic

回复：  NVD_SD_QUERY_DIR_ACK
*/

    NVD_SD_QUERY_DIR_ACK,
/*
功能：          查询SD卡中目录回复
ndata1:         unused
ndata2:         NVD_ERROR_NUM
payload_len:    长度
payload:        目录下的文件名或目录名(以':'符号分隔)
*/
    
    NVD_SD_MOUNT_REQ,
/*
功能：    卸载SD卡
nData1:   UserID
nData2:   通道号
回复：    NVD_SD_MOUNT_ACK
*/

    NVD_SD_MOUNT_ACK,
/*
功能：    卸载SD卡回复
nData2:   0:成功
*/


/******************************************************************************************/
    NVD_JPEG = 0xF0000,
    NVD_JPEG_GET_PIC_REQ,
/*
功能：    获取JPEG图片请求
nData1:   UserID
payload:  NVD_JPEG_HEAD
回复：    NVD_JPEG_GET_PIC_ACK
*/

    NVD_JPEG_GET_PIC_ACK,
/*
功能：    获取JPEG图片请求回复
nData1:   JPEGId
nData2:   0:成功
*/

/******************************************************************************************/
    NVD_CAPTURE = 0x100000,
    NVD_CAPTURE_FIND_REQ,
/*
功能：    查询前端抓拍图片请求
nData1:   UserID
nData2:   通道号
payload:  NVD_FIND_PICTURE_PARAM
回复：    NVD_CAPTURE_QUERY_ACK
*/

    NVD_CAPTURE_FIND_ACK,
/*
功能：    查询前端抓拍图片请求回复
nData1:   UserID
nData2:   0:成功
payload:  查询上下文
*/

	NVD_CAPTURE_FIND_NEXT_REQ,
/*
功能：	  查询下一批(多张)图片请求
nData1:   UserID
nData2:   通道号
payload:  查询上下文
回复：	  NVD_CAPTURE_QUERY_ACK
*/

	NVD_CAPTURE_FIND_NEXT_ACK,
/*
功能：	  查询下一批(多张)图片请求回复
nData1:   UserID
nData2:   0:成功
payload:  前四字节为查询到的图片数量
*/

    NVD_CAPTURE_CLOSE_FIND_REQ,
/*
功能:     关闭查询前端抓拍图片请求
nData1:   UserID
*/

    NVD_CAPTURE_CLOSE_FIND_ACK,
/*
功能：	  关闭查询前端抓拍图片回复
nData1:   UserID
nData2:   0:成功
*/

    NVD_CAPTURE_GET_PICTURE_REQ,
/*
功能:    获取前端抓拍图片请求
nData1:  UserID
payload: 图片文件名
*/

	NVD_CAPTURE_GET_PICTURE_ACK,
/*
功能:	 获取前端抓拍图片请求回复
nData1:  UserID
nData2:  0:成功
payload: 前四字节为图片数据大小
*/


    NVD_EVENT_ILL
}NVD_EVENT;

#endif

