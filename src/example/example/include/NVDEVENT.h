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
    int                 viNo;               /**<  ͨ���� */
    NVD_ENC_STREAM_TYPE encStreamType;      /**<  ��Ƶ */
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
���ܣ�    ��ȡPF�������
* data1:       id
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_SYS_GET_PF_CONFIG_ACK,
/*
���ܣ�    ��Ӧ��ȡPF�������
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_SYS_SET_PF_CONFIG_REQ,
/*
���ܣ�    ����PF�������
* data1:       
* data2:       unused
* payload_len: sizeof(NVD_PF_PARA)
* payload:     NVD_PF_PARA
*/

    NVD_SYS_SET_PF_CONFIG_ACK,
/*
���ܣ�    ��Ӧ����PF�������
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/
    
    NVD_SYS_GET_NET_2_CONFIG_REQ,
/*
���ܣ�    ��ȡ���������������
* data1:       
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_SYS_GET_NET_2_CONFIG_ACK,
/*
���ܣ�    ��Ӧ���������������
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_NET_2_PARA)
* payload:     NVD_NET_2_PARA
*/

    NVD_SYS_SET_NET_2_CONFIG_REQ,
/*
���ܣ�    �������������������
* data1:       
* data2:       unused
* payload_len: sizeof(NVD_NET_2_PARA)
* payload:     NVD_NET_2_PARA
*/

    NVD_SYS_SET_NET_2_CONFIG_ACK,
/*
���ܣ�    ��Ӧ���������������
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_SYS_GET_NTP_CONFIG_REQ,
/*
���ܣ�    ��ȡNTP��������
* data1:       
* data2:       unused
* payload_len: 0
* payload:     NULL
*/
    
    NVD_SYS_GET_NTP_CONFIG_ACK,
/*
���ܣ�    ��ӦNTP��������
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_NTP_PARA)
* payload:     NVD_NTP_PARA
*/


    NVD_SYS_SET_NTP_CONFIG_REQ,
/*
���ܣ�    ����NTP��������
* data1:       
* data2:       unused
* payload_len: sizeof(NVD_NTP_PARA)
* payload:     NVD_NTP_PARA
*/
    
    NVD_SYS_SET_NTP_CONFIG_ACK,
/*
���ܣ�    ��ӦNTP��������
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_SYS_GET_EMAIL_CONFIG_REQ,
/*
���ܣ�    ��ȡEMAIL��������
* data1:       
* data2:       unused
* payload_len: 0
* payload:     NULL
*/
    
    NVD_SYS_GET_EMAIL_CONFIG_ACK,
/*
���ܣ�    ��ӦEMAIL��������
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_EMAIL_PARA)
* payload:     NVD_EMAIL_PARA
*/


    NVD_SYS_SET_EMAIL_CONFIG_REQ,
/*
���ܣ�    ����EMAIL��������
* data1:       
* data2:       unused
* payload_len: sizeof(NVD_EMAIL_PARA)
* payload:     NVD_NTP_PARA
*/
    
    NVD_SYS_SET_EMAIL_CONFIG_ACK,
/*
���ܣ�    ��ӦEMAIL��������
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/
 

    NVD_SYS_GET_SNMP_CONFIG_REQ,
/*
���ܣ�    ��ȡSNMP��������
* data1:       
* data2:       unused
* payload_len: 0
* payload:     NULL
*/
    
    NVD_SYS_GET_SNMP_CONFIG_ACK,
/*
���ܣ�    ��ӦSNMP��������
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_SNMP_PARA)
* payload:     NVD_SNMP_PARA
*/


    NVD_SYS_SET_SNMP_CONFIG_REQ,
/*
���ܣ�    ����SNMP��������
* data1:       
* data2:       unused
* payload_len: sizeof(NVD_SNMP_PARA)
* payload:     NVD_SNMP_PARA
*/
    
    NVD_SYS_SET_SNMP_CONFIG_ACK,
/*
���ܣ�    ��ӦSNMP��������
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_SYS_TRANS_OPEN_CONFIG_REQ = 0x10100,
/*
���ܣ�    ����͸������
* data1:       id
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_SYS_TRANS_OPEN_CONFIG_ACK,
/*
���ܣ�    �����ȡ͸������
* data1:       
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

/******************************************************************************************/
    NVD_USER = 0x30000,
    NVD_USER_LOGIN_REQ,
/*
���ܣ�    �û���¼�豸
nData1:   NVD_INVALID_HANDLE
nData2:   0
payload_len: sizeof(NVD_USER_PARA)
payload:  NVD_USER_PARA
�ظ���    NVD_USER_LOGIN_ACK
*/

    NVD_USER_LOGIN_ACK,
/*
���ܣ�    �û���¼�ظ�
nData1:   ��ȷ������£����ص�¼ID
nData2:   0:�ɹ�
payload_len: sizeof(NVD_USER_PARA)+sizeof(NVD_LOGIN_INFO)
payload:  NVD_USER_PARA+NVD_LOGIN_INFO
*/

    NVD_USER_LOGOUT_NOTIFY,
/*
���ܣ�    �û��ǳ��豸
nData1:   UserID
*/

    NVD_USER_ADD_REQ,
/*
���ܣ�    �����û�
nData1:   UserID
payload_len: sizeof(NVD_USER_PARA)
payload:  NVD_USER_PARA
�ظ���    NVD_ADD_UAER_ACK
˵����    ֻ�й���Ա������
*/

    NVD_USER_ADD_ACK,
/*
���ܣ�    �����û��ظ�
nData2:   0:�ɹ�
*/

    NVD_USER_DELETE_REQ,
/*
���ܣ�    ɾ���û�
nData1:   UserID
payload_len: sizeof(NVD_USER_PARA)
payload:  NVD_USER_PARA
�ظ���    NVD_DELETE_UAER_ACK
˵����    ֻ�й���Ա������
*/

    NVD_USER_DELETE_ACK,
/*
���ܣ�    ɾ���û��ظ�
nData2:   0:�ɹ�
*/

    NVD_USER_DELETE_NOTIFY,
/*
���ܣ�    ɾ���û���֪ͨ���û�
*/

    NVD_USER_MODIFY_REQ,
/*
���ܣ�    �޸��û��������޸�����
nData1:   UserID
payload_len: sizeof(NVD_USER_PARA)
payload:  NVD_USER_PARA
�ظ���    NVD_MODIFY_UAER_ACK
˵����    ֻ�й���Ա���û��Լ�������
*/

    NVD_USER_MODIFY_ACK,
/*
���ܣ�    �޸��û��ظ�
nData2:   0:�ɹ�
*/

    NVD_USER_QUERY_REQ,
/*
���ܣ�    ��ѯ�û�
nData1:   UserID
�ظ���    NVD_SELECT_USER_ACK
˵����    ֻ�й���Ա���û��Լ�������
*/

    NVD_USER_QUERY_ACK,
/*
���ܣ�    ��ѯ�û��ظ�
nData2:   0:�ɹ�
payload_len: sizeof(NVD_USER_PARA)*�û�����
payload:  NVD_USER_PARA
*/

    NVD_USER_KEEPALIVE_REQ,
/*
���ܣ�    �û���������
nData1:   UserID
*/

    NVD_USER_KEEPALIVE_ACK,
/*
���ܣ�    �û���������
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_DEVICE = 0x40000,
/******************************************************************************************/
    NVD_DEVICE_GET_START_REQ,
/*
���ܣ�    ��ȡ�豸������Ϣ
nData1��  UserID
nData2��  ͨ����     0xFF��ʾȫ����ȡ
�ظ���    NVD_DEVICE_GET_START_ACK
*/

    NVD_DEVICE_GET_START_ACK,
/*
���ܣ�    ��ȡ�豸������Ϣ�ظ�
���ݣ�    
*/

    NVD_DEVICE_SET_START_REQ,
/*
���ܣ�    �����豸������Ϣ
nData1��  UserID
payload��  
�ظ���    NVD_DEVICE_SET_START_ACK
*/

    NVD_DEVICE_SET_START_ACK,
/*
���ܣ�    �����豸������Ϣ�ظ�
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_DEVICE_GET_STATE_INFO_REQ,
/*
���ܣ�    ��ȡ�豸����״̬
nData1:   UserID
nData2:   NVD_STATE_TYPE
�ظ���    NVD_GET_STATE_INFO_ACK
*/

    NVD_DEVICE_GET_STATE_INFO_ACK,
/*
���ܣ�    ��ȡ�豸����״̬�ظ�
nData1:   0:�ɹ�
payload:  NVD_STATE_INFO
*/

/******************************************************************************************/
    NVD_DEVICE_GET_INFO_REQ = 0x40100,
/*
���ܣ�    ��ȡ�豸��Ϣ
nData1:   UserID
payload_len: 0
�ظ���    NVD_GET_ENC_DEVICE_ACK
*/

    NVD_DEVICE_GET_INFO_ACK,
/*
���ܣ�    ��ȡ�豸��Ϣ�ظ�
nData2:   0:�ɹ�
payload_len: sizeof(NVD_DEV_PARA)
payload�� NVD_DEV_PARA
*/

    NVD_DEVICE_SET_INFO_REQ,
/*
���ܣ�    �����豸��Ϣ
nData1��  UserID
payload_len: sizeof(NVD_DEV_PARA)
payload�� NVD_DEV_PARA
�ظ���    NVD_SET_ENC_DEVICE_ACK
*/

    NVD_DEVICE_SET_INFO_ACK,
/*
���ܣ�    �����豸��Ϣ�ظ�
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_DEVICE_CHECK_TIME_REQ = 0x40700,
/*
���ܣ�    �豸Уʱ����
���ݣ�    
�ظ���    NVD_DEVICE_CHECK_TIME_ACK
˵����   
*/

    NVD_DEVICE_CHECK_TIME_ACK,
/*
���ܣ�    �豸Уʱ�ظ�
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_DEVICE_RESTORE_REQ = 0x40800,
/*
���ܣ�    �����豸�ָ�����������(ֻ�ָ����ã����ָ�IP��ַ)
nData1:   UserID
�ظ���    NVD_DEVICE_RESTORE_ACK
*/

    NVD_DEVICE_RESTORE_ACK,
/*
���ܣ�    �����豸���������ûظ���
nData2:   0:�ɹ�
˵����    ֻ�й���Ա������
*/

    NVD_DEVICE_RESTORE_IP_REQ,
/*
���ܣ�    �����豸�ָ�������IP����(ֻ�ָ�IP��ַ�����ָ�����)
nData1:   UserID
�ظ���    NVD_DEVICE_RESTORE_IP_ACK
*/

    NVD_DEVICE_RESTORE_IP_ACK,
/*
���ܣ�    �����豸������IP���ûظ���
nData2:   0:�ɹ�
˵����    ֻ�й���Ա������
*/

    NVD_DEVICE_RESTORE_ALL_REQ,
/*
���ܣ�    �����豸�ָ�����������(�ָ����У�����IP��ַ������)
nData1:   UserID
�ظ���    NVD_DEVICE_RESTORE_IP_ACK
*/

    NVD_DEVICE_RESTORE_ALL_ACK,
/*
���ܣ�    �����豸���������ûظ���
nData2:   0:�ɹ�
˵����    ֻ�й���Ա������
*/

    NVD_DEVICE_BACKUP_ALL_CONFIG_REQ,
/*
���ܣ�   �������ò��ش�
nData1:  UserID
nData2:  ChannelID
payload: 4���ֽڳ�����ƫ������Ϊ-1ʱ�������ļ�ɾ����ֱ�ӷ��أ����ս������뷢��-1��
�ظ���   NVD_DEVICE_BACKUP_ALL_CONFIG_ACK
˵����   ���ݵ��ļ�ͨ��payload��ɶ�������أ�ÿ����ǰ8���ֽ��ǲ����Ϣ�������ܴ�С��4���ֽڣ�+��ǰƫ������4���ֽڣ�������������
*/

    NVD_DEVICE_BACKUP_ALL_CONFIG_ACK,
/*
���ܣ��������ûظ�
nData1:  UserID
nData2:  0:�ɹ�
payload: ���֮��ÿһС�������ݣ�ɾ���ļ�ʱΪ��
*/

    NVD_DEVICE_RESTORE_ALL_CONFIG_REQ,
/*
���ܣ�   �ָ�����
nData1:  UserID
nData2:  ChannelID
�ظ���   NVD_DEVICE_RESTORE_ALL_CONFIG_ACK
˵����   �ָ����ļ�ͨ��payload��ɶ�������ͣ�ǰ8���ֽ��ǲ����Ϣ�������ܴ�С��4���ֽڣ�+��ǰ��������4���ֽڣ�������������
*/

    NVD_DEVICE_RESTORE_ALL_CONFIG_ACK,
/*
���ܣ�   �ָ����ûظ�
nData2:  0:�ɹ�
*/

/******************************************************************************************/
    NVD_DEVICE_RESET_REQ = 0x40900,
/*
���ܣ�    ��λ�豸
nData1:   UserID
�ظ���    NVD_DEVICE_RESET_ACK
˵����    ֻ�й���Ա������
*/

    NVD_DEVICE_RESET_ACK,
/*
���ܣ�    �����豸��λ�ظ���
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_DEVICE_SAVE_CONFIG_REQ = 0x40A00,
/*
���ܣ�    �����豸��������
nData1:   UserID
�ظ���    NVD_DEVICE_SAVE_CONFIG_ACK
*/

    NVD_DEVICE_SAVE_CONFIG_ACK,
/*
���ܣ�    �����豸��������ظ�
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_VIDEO = 0x50000,
    NVD_VIDEO_GET_ENC_PARAM_REQ,
/*
���ܣ�    ��ȡ�豸�������
nData1:   UserID
nData2:   ͨ����
�ظ���    NVD_VIDEO_GET_ENC_PARAM_ACK
*/

    NVD_VIDEO_GET_ENC_PARAM_ACK,
/*
���ܣ�    ��ȡ�豸��������ظ�
nData2:   0:�ɹ�
payload:  NVD_VIDEO_ENC_PARA
*/

    NVD_VIDEO_SET_ENC_PARAM_REQ,
/*
���ܣ�    �����豸�������
nData1:   UserID
payload:  NVD_VIDEO_ENC_PARA
�ظ���    NVD_VIDEO_SET_ENC_PARAM_ACK
*/

    NVD_VIDEO_SET_ENC_PARAM_ACK,
/*
���ܣ�    ��ȡ�豸��������ظ�
nData2:   0:�ɹ�
*/

    NVD_VIDEO_MAKE_IDR_NOTIFY,
/*
���ܣ�    �����ؼ�֡
nData1:   UserID
nData2:   ͨ����
���ݣ�    NVD_ENC_STREAM_TYPE
*/

    NVD_VIDEO_GET_ENC_ADV_PARAM_REQ,
/*
���ܣ�    ��ȡ�豸����߼�����
nData1:   UserID
nData2:   ͨ����
�ظ���    NVD_VIDEO_GET_ENC_ADV_PARAM_ACK
*/

    NVD_VIDEO_GET_ENC_ADV_PARAM_ACK,
/*
���ܣ�    ��ȡ�豸����߼������ظ�
nData2:   0:�ɹ�
payload:  NVD_VIDEO_ENC_ADV_PARA
*/

    NVD_VIDEO_SET_ENC_ADV_PARAM_REQ,
/*
���ܣ�    �����豸����߼�����
nData1:   UserID
payload:  NVD_VIDEO_ENC_ADV_PARA
�ظ���    NVD_VIDEO_SET_ENC_ADV_PARAM_ACK
*/

    NVD_VIDEO_SET_ENC_ADV_PARAM_ACK,
/*
���ܣ�    �����豸����߼������ظ�
nData2:   0:�ɹ�
*/

    NVD_VIDEO_SET_ENC_ADV_MODE_REQ,
/*
���ܣ�    �����豸����߼�����ģʽ
nData1:   UserID
payload:  NVD_ENC_ADV_MODE_PARA
�ظ���    NVD_VIDEO_SET_ENC_ADV_MODE_ACK
*/

    NVD_VIDEO_SET_ENC_ADV_MODE_ACK,
/*
���ܣ�    �����豸����߼�����ģʽ�ظ�
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_VIDEO_GET_DISPLAY_CFG_REQ = 0x50100,
/*
���ܣ�    ��ȡ�豸��ʾ��Ϣ
nData1:   UserID
nData2:   ͨ����
�ظ���    NVD_VIDEO_GET_DISPLAY_CFG_ACK
*/

    NVD_VIDEO_GET_DISPLAY_CFG_ACK,
/*
���ܣ�    ��ȡ�豸��Ϣ�ظ�
nData2:   0:�ɹ�
payload   NVD_DISPLAY_PARA
*/

    NVD_VIDEO_SET_DISPLAY_CFG_REQ,
/*
���ܣ�    �����豸��ʾ��Ϣ
nData1:   UserID
payload   NVD_DISPLAY_PARA
�ظ���    NVD_VIDEO_SET_DISPLAY_CFG_ACK
*/

    NVD_VIDEO_SET_DISPLAY_CFG_ACK,
/*
���ܣ�    �����豸��ʾ��Ϣ�ظ�
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_VIDEO_GET_TEXT_OSD_CFG_REQ = 0x50200,
/*
���ܣ�    ��ȡ�豸�ı�OSD��ʾ��Ϣ
nData1:   UserID
nData2:   ͨ����
�ظ���    NVD_VIDEO_GET_TEXT_OSD_CFG_ACK
*/

    NVD_VIDEO_GET_TEXT_OSD_CFG_ACK,
/*
���ܣ�    ��ȡ�豸�ı�OSD��Ϣ�ظ�
nData2:   0:�ɹ�
payload:  NVD_TEXT_OSD_PARA
        payload��NVD_OSD_CFG*4 ���4��
*/

    NVD_VIDEO_SET_TEXT_OSD_CFG_REQ,
/*
���ܣ�    �����豸�ı�OSD��ʾ��Ϣ
nData1:   UserID
nData2:   ͨ����
payload:  NVD_TEXT_OSD_PARA
�ظ���    NVD_VIDEO_SET_TEXT_OSD_CFG_ACK
*/

    NVD_VIDEO_SET_TEXT_OSD_CFG_ACK,
/*
���ܣ�    �����豸�ı�OSD��ʾ��Ϣ�ظ�
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_VIDEO_GET_MASK_CFG_REQ = 0x50300,
/*
���ܣ�    ��ȡ�豸�ڵ���Ϣ
nData1:   UserID
nData2:   ͨ����
�ظ���    NVD_VIDEO_GET_MASK_CFG_ACK
*/

    NVD_VIDEO_GET_MASK_CFG_ACK,
/*
���ܣ�    ��ȡ�豸�ڵ���Ϣ�ظ�
nData2:   0:�ɹ�
payload:  NVD_MASK_PARA
*/

    NVD_VIDEO_SET_MASK_CFG_REQ,
/*
���ܣ�    �����豸�ڵ���Ϣ
nData1:   UserID
nData2:   ͨ����
payload:  NVD_MASK_PARA
�ظ���    NVD_VIDEO_SET_MASK_CFG_ACK
*/

    NVD_VIDEO_SET_MASK_CFG_ACK,
/*
���ܣ�    �����豸�ڵ���Ϣ�ظ�
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_VIDEO_GET_MD_CFG_REQ  = 0x50400,
/*
���ܣ�    ��ȡ�ƶ�������
nData1:   UserID
nData2:   ͨ����
�ظ���    NVD_VIDEO_GET_MD_CFG_ACK
*/

    NVD_VIDEO_GET_MD_CFG_ACK,
/*
���ܣ�    ��ȡ�ƶ��������ظ�
nData2:   0:�ɹ�
payload:  NVD_MD_PARA
*/

    NVD_VIDEO_SET_MD_CFG_REQ,
/*
���ܣ�    �����ƶ�������
nData1:   UserID
nData2:   ͨ����
payload:  NVD_MD_PARA
�ظ���    NVD_VIDEO_SET_MD_CFG_ACK
*/

    NVD_VIDEO_SET_MD_CFG_ACK,
/*
���ܣ�    �����ƶ��������ظ�
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_VIDEO_GET_OD_CFG_REQ  = 0x50500,
/*
���ܣ�    ��ȡ�ڵ�������
nData1:   UserID
nData2:   ͨ����
�ظ���    NVD_VIDEO_GET_OD_CFG_ACK
*/

    NVD_VIDEO_GET_OD_CFG_ACK,
/*
���ܣ�    ��ȡ�ڵ��������ظ�
nData2:   0:�ɹ�
payload:  NVD_OD_PARA
*/

    NVD_VIDEO_SET_OD_CFG_REQ,
/*
���ܣ�    �����ڵ�������
nData1:   UserID
nData2:   ͨ����
payload:  NVD_OD_PARA
�ظ���    NVD_VIDEO_SET_OD_CFG_ACK
*/

    NVD_VIDEO_SET_OD_CFG_ACK,
/*
���ܣ�    �����ڵ��������ظ�
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_VIDEO_GET_SNAP_CFG_REQ  = 0x50600,
/*
���ܣ�    ��ȡץ�Ĳ���
nData1:   UserID
nData2:   ͨ����
�ظ���    NVD_VIDEO_GET_SNAP_CFG_ACK
*/

    NVD_VIDEO_GET_SNAP_CFG_ACK,
/*
���ܣ�    ��ȡץ�Ĳ����ظ�
nData2:   0:�ɹ�
payload:  NVD_SNAP_PARA
*/

    NVD_VIDEO_SET_SNAP_CFG_REQ,
/*
���ܣ�    ����ץ�Ĳ���
nData1:   UserID
nData2:   ͨ����
payload:  NVD_SNAP_PARA
�ظ���    NVD_VIDEO_SET_SNAP_CFG_ACK
*/

    NVD_VIDEO_SET_SNAP_CFG_ACK,
/*
���ܣ�    ����ץ�Ĳ����ظ�
nData2:   0:�ɹ�
*/

    NVD_VIDEO_SNAP_REQ,
/*
���ܣ�    ץ��ͼ��
nData1:   UserID
nData2:   ͨ����
�ظ���    NVD_VIDEO_JPEG_SNAP_ACK
*/

    NVD_VIDEO_SNAP_ACK,
/*
���ܣ�    ץ��ͼ��ظ�
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_VIDEO_GET_ST_CFG_REQ  = 0x50700,
/*
���ܣ�    ��ȡ����ת��������
nData1:   UserID
nData2:   ͨ����
�ظ���    NVD_VIDEO_GET_ST_CFG_ACK
*/

    NVD_VIDEO_GET_ST_CFG_ACK,
/*
���ܣ�    ��ȡ����ת���������ظ�
nData2:   0:�ɹ�
payload:  NVD_ST_PARA
*/

    NVD_VIDEO_SET_ST_CFG_REQ,
/*
���ܣ�    ���ó���ת��������
nData1:   UserID
nData2:   ͨ����
payload:  NVD_ST_PARA
�ظ���    NVD_VIDEO_SET_ST_CFG_ACK
*/

    NVD_VIDEO_SET_ST_CFG_ACK,
/*
���ܣ�    ���ó���ת���������ظ�
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_VIDEO_GET_ROI_CFG_REQ  = 0x50800,
/*
���ܣ�    ��ȡͼ����ǿ����
nData1:   UserID
nData2:   ͨ����
�ظ���    NVD_VIDEO_GET_ROI_CFG_ACK
*/

    NVD_VIDEO_GET_ROI_CFG_ACK,
/*
���ܣ�    ��ȡͼ����ǿ�����ظ�
nData2:   0:�ɹ�
payload:  NVD_ROI_PARA
*/

    NVD_VIDEO_SET_ROI_CFG_REQ,
/*
���ܣ�    ����ͼ����ǿ����
nData1:   UserID
nData2:   ͨ����
payload:  NVD_ROI_PARA
�ظ���    NVD_VIDEO_SET_ROI_CFG_ACK
*/

    NVD_VIDEO_SET_ROI_CFG_ACK,
/*
���ܣ�    ����ͼ����ǿ�����ظ�
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_VIDEO_GET_REC_CFG_REQ  = 0x50900,
/*
���ܣ�    ��ȡ¼�����ò���
nData1:   UserID
nData2:   ͨ����
�ظ���    NVD_SD_GET_REC_CFG_ACK
*/

    NVD_VIDEO_GET_REC_CFG_ACK,
/*
���ܣ�    ��ȡ¼�����ò����ظ�
nData2:   0:�ɹ�
payload:  NVD_REC_PARA
*/

    NVD_VIDEO_SET_REC_CFG_REQ,
/*
���ܣ�    ����¼�����ò���
nData1:   UserID
nData2:   ͨ����
payload:  NVD_REC_PARA
�ظ���    NVD_SD_SET_REC_CFG_ACK
*/

    NVD_VIDEO_SET_REC_CFG_ACK,
/*
���ܣ�    ����¼�����ò����ظ�
nData2:   0:�ɹ�
*/

    NVD_VIDEO_REC_MANUAL_START_REQ,
/*
���ܣ�    �ֶ���ʼ¼��
nData1:   UserID
nData2:   ͨ����
�ظ���    NVD_VIDEO_REC_MANUAL_START_ACK
*/

    NVD_VIDEO_REC_MANUAL_START_ACK,
/*
���ܣ�    �ֶ���ʼ¼��ظ�
nData2:   0:�ɹ�
*/

    NVD_VIDEO_REC_MANUAL_STOP_REQ,
/*
���ܣ�    �ֶ�����¼��
nData1:   UserID
nData2:   ͨ����
�ظ���    NVD_VIDEO_REC_MANUAL_STOP_ACK
*/

    NVD_VIDEO_REC_MANUAL_STOP_ACK,
/*
���ܣ�    �ֶ�����¼��ظ�
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_VIDEO_GET_IMAGE_PARAM_REQ  = 0x50a00,
/*
���ܣ�    ��ȡͼ�����
nData1:   UserID
payload:  NVD_IMAGE_PARA
�ظ���    NVD_VIDEO_GET_IMAGE_PARAM_ACK
*/

    NVD_VIDEO_GET_IMAGE_PARAM_ACK,
/*
���ܣ�    ��ȡͼ������ظ�
nData2:   0:�ɹ�
*/

    NVD_VIDEO_SET_IMAGE_PARAM_REQ,
/*
���ܣ�    ����ͼ�����
nData1:   UserID
payload:  NVD_IMAGE_PARA
�ظ���    NVD_VIDEO_SET_IMAGE_PARAM_ACK
*/

    NVD_VIDEO_SET_IMAGE_PARAM_ACK,
/*
���ܣ�    ����ͼ������ظ�
nData2:   0:�ɹ�
*/

    NVD_VIDEO_SET_IMAGE_DEFAULT_REQ,
/*
���ܣ�    ����ͼ��ָ�����
nData1:   UserID
payload:  NVD_IMAGE_PARA
�ظ���    NVD_VIDEO_SET_IMAGE_DEFAULT_ACK
*/

    NVD_VIDEO_SET_IMAGE_DEFAULT_ACK,
/*
���ܣ�    ����ͼ��ָ������ظ�
nData2:   0:�ɹ�
*/

    NVD_VIDEO_GET_IMAGE_PARAM_ADV_REQ,
/*
���ܣ�    ��ȡͼ��߼�����
 nData1:   UserID
 payload:  NVD_IMAGE_PARA_ADV
 �ظ���    NVD_VIDEO_GET_IMAGE_PARAM_ADV_ACK
 */

    NVD_VIDEO_GET_IMAGE_PARAM_ADV_ACK,
/*
 ���ܣ�    ��ȡͼ��߼������ظ�
nData2:   0:�ɹ�
 */

    NVD_VIDEO_SET_IMAGE_PARAM_ADV_REQ,
/*
���ܣ�    ����ͼ��߼�����
nData1:   UserID
payload:  NVD_IMAGE_PARA_ADV
�ظ���    NVD_VIDEO_SET_IMAGE_PARAM_ADV_ACK
*/

    NVD_VIDEO_SET_IMAGE_PARAM_ADV_ACK,
/*
���ܣ�    ����ͼ��߼������ظ�
nData2:   0:�ɹ�
*/

    NVD_VIDEO_SET_IMAGE_DEFAULT_ADV_REQ,
/*
���ܣ�    ����ͼ��ָ��߼�����
nData1:   UserID
payload:  NVD_IMAGE_PARA_ADV
�ظ���    NVD_VIDEO_SET_IMAGE_DEFAULT_ADV_ACK
*/

    NVD_VIDEO_SET_IMAGE_DEFAULT_ADV_ACK,
/*
���ܣ�    ����ͼ��ָ��߼������ظ�
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_AUDIO = 0x60000,
    NVD_AUDIO_IN_GET_CFG_REQ,
/*
���ܣ�    ��ȡ��Ƶ�������
nData1:   UserID
nData2:   ��Ƶ����ͨ����� 0xFF ��ȡȫ��
�ظ���    NVD_AUDIO_IN_GET_CFG_ACK
*/

    NVD_AUDIO_IN_GET_CFG_ACK,
/*
���ܣ�    ��ȡ��Ƶ��������ظ�
nData2:   0:�ɹ�
payload�� NVD_AUDIO_IN_PARA
*/

    NVD_AUDIO_IN_SET_CFG_REQ,
/*
���ܣ�    ������Ƶ�������
nData1:   UserID
payload:  NVD_AUDIO_IN_PARA
�ظ���    NVD_AUDIO_IN_SET_CFG_ACK
*/

    NVD_AUDIO_IN_SET_CFG_ACK,
/*
���ܣ�    ������Ƶ��������ظ�
nData2:   0:�ɹ�
*/

    NVD_AUDIO_OUT_GET_CFG_REQ,
/*
���ܣ�    ��ȡ��Ƶ�������
nData1:   UserID
nData2:   ��Ƶ����ͨ����� 0xFF ��ȡȫ��
�ظ���    NVD_AUDIO_OUT_GET_CFG_ACK
*/

    NVD_AUDIO_OUT_GET_CFG_ACK,
/*
���ܣ�    ��ȡ��Ƶ��������ظ�
nData2:   0:�ɹ�
payload�� NVD_AUDIO_OUT_PARA
*/

    NVD_AUDIO_OUT_SET_CFG_REQ,
/*
���ܣ�    ������Ƶ�������
nData1:   UserID
payload:  NVD_AUDIO_OUT_PARA
�ظ���    NVD_AUDIO_OUT_SET_CFG_ACK
*/

    NVD_AUDIO_OUT_SET_CFG_ACK,
/*
���ܣ�    ������Ƶ��������ظ�
nData2:   0:�ɹ�
*/

    NVD_AUDIO_OUT_OPEN_REQ,
/*
���ܣ�    ������Ƶ�����
nData1:   UserID
nData2:   ͨ����
*/

    NVD_AUDIO_OUT_OPEN_ACK,
/*
���ܣ�    ������Ƶ����򿪻ظ�
nData2:   0:�ɹ�
*/

    NVD_AUDIO_OUT_CLOSE_REQ,
/*
���ܣ�    ������Ƶ����ر�
nData1:   UserID
nData2:   ͨ����
*/

    NVD_AUDIO_OUT_CLOSE_ACK,
/*
���ܣ�    ������Ƶ����ر�
nData2:   0:�ɹ�
*/

    NVD_AUDIO_OUT_SET_VOLUME_REQ,
/*
���ܣ�    ������Ƶ�������
nData1:   UserID
nData2:   ͨ����
*/

    NVD_AUDIO_OUT_SET_VOLUME_ACK,
/*
���ܣ�    ������Ƶ��������ظ�
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_STREAM = 0x70000,
    NVD_STREAM_OPEN_REQ,
/*
���ܣ�    ����
nData1:   UserID
payload:  NVD_PLAY_PARA
�ظ���    NVD_OPEN_STREAM_ACK
*/

    NVD_STREAM_OPEN_ACK,
/*
���ܣ�    �����ظ�
nData1:   streamId
nData2:   0:�ɹ�
*/

    NVD_STREAM_CLOSE_REQ,
/*
���ܣ�    �ر���
nData1:   UserID
nData2:   streamId
�ظ���    NVD_CLOSE_STREAM_ACK
*/

    NVD_STREAM_CLOSE_ACK,
/*
���ܣ�    �ر����ظ�
nData2:   0:�ɹ�
*/

    NVD_STREAM_CHANGE_REQ,
/*
���ܣ�    �л�������
nData1��  UserID
nData2��  streamId
�ظ���    NVD_CHANGE_STREAM_ACK
*/

    NVD_STREAM_CHANGE_ACK,
/*
���ܣ�    �л��������ظ�
nData2:   0:�ɹ�
*/

    NVD_STREAM_UP = 0x70100,
/*
���ܣ�    ʵʱ���ϴ�
nData1:   UserID
payload:  ��
�ظ���    ��
*/

    NVD_STREAM_DOWN,
/*
���ܣ�    �Խ�������
nData1:   UserID
payload:  ��
�ظ���    ��
*/

    NVD_STREAM_COM_UP,
/*
���ܣ�    �������ϴ�
nData1:   UserID
payload:  ��
�ظ���    ��
*/

    NVD_STREAM_ALARM_UP,
/*
���ܣ�    �澯��Ϣ�ϴ�
nData1:   UserID
payload:  ��
�ظ���    ��
*/

    NVD_STREAM_PTZ_INFO_UP,
/*
���ܣ�    ptz��Ϣ�ϴ�
nData1:   UserID
payload:  ��
�ظ���    ��
*/

    NVD_STREAM_OPEN_INFO_UP,
/*
���ܣ�    ͸����Ϣ�ϴ�
nData1:   UserID
payload:  ��
�ظ���    ��
*/
    
    NVD_STREAM_ALARM_CENTER_UP,
/*
���ܣ�    �澯��Ϣ�ϴ����澯����
nData1:      0
payload_len: sizeof(NVD_ALARM_REPORT_INFO)
payload:  NVD_ALARM_REPORT_INFO
�ظ���    ��
*/
    NVD_STREAM_PLAYBACK=0x70200,
    NVD_STREAM_PLAYBACK_OPEN_REQ,
/*
���ܣ�    ����һ���ط�������
nData1:   UserID
payload:  NULL
�ظ���    NVD_STREAM_PLAYBACK_OPEN_ACK
*/
    NVD_STREAM_PLAYBACK_OPEN_ACK,
/*
���ܣ�    �򿪻ط����ظ�
nData1:   PlaybackStreamId
nData2:   0:�ɹ�
*/
    NVD_STREAM_PLAYBACK_CLOSE_REQ,
/*
���ܣ�    �رջط���
nData1:   UserID
nData2:   playbackStreamId
�ظ���    NVD_STREAM_PLAYBACK_CLOSE_ACK
*/
    NVD_STREAM_PLAYBACK_CLOSE_ACK,
/*
���ܣ�    �رջط����ظ�
nData2:   0:�ɹ�
*/ 
    NVD_STREAM_PLAYBACK_PLAY_REQ,
/*
���ܣ�    �򿪻ط�������,Ϊ������׼��
nData1:   UserID
nData2:   playbackStreamId
payload_len: sizeof(NVD_RECORD_PLAYBACK)
payload:  NVD_RECORD_PLAYBACK
�ظ���    NVD_STREAM_PLAYBACK_PLAY_ACK
*/
    NVD_STREAM_PLAYBACK_PLAY_ACK,
/*
���ܣ�    �򿪻ط��������ظ�
nData1:  
nData2:  0:�ɹ�  
*/
    NVD_STREAM_PLAYBACK_STOP_REQ,
/*
���ܣ�    �رջط�������
nData1:   UserID
nData2:   playbackStreamId
�ظ���    NVD_STREAM_PLAYBACK_STOP_ACK
*/
    NVD_STREAM_PLAYBACK_STOP_ACK,
/*
���ܣ�    �رջط��������ظ�
nData1:  playbackStreamId
nData2:  0:�ɹ�  
*/
    NVD_STREAM_PLAYBACK_SEEK_FRAME_REQ,
/*
���ܣ�    ��������Ƶ֡
nData1:   UserID
nData2:   playbackStreamId
payload_len: sizeof(NVD_RECORD_PLAYBACK_SEEK)
payload:  NVD_RECORD_PLAYBACK_SEEK
�ظ���    NVD_STREAM_PLAYBACK_SEEK_FRAME_ACK
*/
    NVD_STREAM_PLAYBACK_SEEK_FRAME_ACK,
/*
���ܣ�    ��������Ƶ֡�ظ�
nData1:  playbackStreamId
nData2:  0:�ɹ�  
*/
    NVD_STREAM_PLAYBACK_GET_PACKET_REQ,
/*
���ܣ�    ��������һ֡����Ƶ����
payload_len: 0
payload:  NULL
�ظ���    ��
*/
    NVD_STREAM_PLAYBACK_GET_PACKET_ACK,
/*
���ܣ�       �ط����ϴ�
nData1:     ��״̬,-1 failed,-2 eof,>0 framesize
payload:    ��
�ظ���       ��
*/
    NVD_STREAM_PLAYBACK_FIND_FILE_REQ,
/*
���ܣ�����һ�β��Ҳ���
nData1:UserID
nData2:playbackStreamId
payload_len:sizeof(NVD_RECORD_FILE_FIND)
payload:NVD_RECORD_FILE_FIND
�ظ���NVD_STREAM_PLAYBACK_FIND_FILE_ACK
*/
    NVD_STREAM_PLAYBACK_FIND_FILE_ACK,
/*
���ܣ�    �������һظ�
nData1:  playbackStreamId
nData2:  0:�ɹ�  
*/
    NVD_STREAM_PLAYBACK_FIND_NEXT_FILE_REQ,//
/*
����:������һ���ļ�
nData1:UserID
nData2:playbackStreamId
*/
    NVD_STREAM_PLAYBACK_FIND_NEXT_FILE_ACK,
/*
����:������һ���ļ��ظ�
nData1:playbackStreamId
nData2: 0�ɹ�,���������ֹͣ����
payload_len:sizeof(NET_RECORDFILE_INFO)
payload:NET_RECORDFILE_INFO
*/
    NVD_STREAM_PLAYBACK_FIND_FILE_CLOSE_REQ,//
/*
����:�ر��ļ�����
nData1:UserID
nData2:playbackStreamId
�ظ�:NVD_STREAM_PLAYBACK_FIND_FILE_CLOSE_ACK
*/
    NVD_STREAM_PLAYBACK_FIND_FILE_CLOSE_ACK,
/*
����:�ر��ļ����һظ�
nData1:playbackStreamId
nData2: 0�ɹ�
*/

/******************************************************************************************/
    NVD_ALARM = 0x80000,
/******************************************************************************************/
    NVD_ALARM_GET_ALARM_IN_CFG_REQ,
/*
���ܣ�    ��ȡ�����������
nData1:   UserID
nData2:   DI���  0xFF ��ȡȫ��
�ظ���    NVD_ALARM_GET_ALARM_IN_CFG_ACK
*/

    NVD_ALARM_GET_ALARM_IN_CFG_ACK,
/*
���ܣ�    ��ȡ������������ظ�
nData2:   0:�ɹ�
payload_len: sizeof(NVD_ALARM_IN_PARA)
payload�� NVD_ALARM_IN_PARA
*/

    NVD_ALARM_SET_ALARM_IN_CFG_REQ,
/*
���ܣ�    ���ñ����������
nData1��  UserID
nData2:   DI���
payload�� NVD_ALARM_IN_PARA
�ظ���    NVD_ALARM_SET_ALARM_IN_CFG_ACK
*/

    NVD_ALARM_SET_ALARM_IN_CFG_ACK,
/*
���ܣ�    ���ñ�����������ظ�
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_ALARM_GET_ALARM_OUT_CFG_REQ,
/*
���ܣ�    ��ȡ�����������
nData1:   UserID
nData2:   DO���
�ظ���    NVD_ALARM_GET_ALARM_OUT_CFG_ACK
*/

    NVD_ALARM_GET_ALARM_OUT_CFG_ACK,
/*
���ܣ�    ��ȡ������������ظ�
nData2:   0:�ɹ�
payload:  NVD_ALARM_OUT_PARA
*/

    NVD_ALARM_SET_ALARM_OUT_CFG_REQ,
/*
���ܣ�    ���ñ����������
nData1:   UserID
nData2:   DO���
payload:  NVD_ALARM_OUT_PARA
�ظ���    NVD_ALARM_SET_ALARM_OUT_CFG_ACK
*/

    NVD_ALARM_SET_ALARM_OUT_CFG_ACK,
/*
���ܣ�    ���ñ�����������ظ�
nData2:   0:�ɹ�
*/

    NVD_ALARM_OUT_OPEN_REQ,
/*
���ܣ�    �ֶ���alarmOut�澯����
nData1:   UserID
nData2:   DO���
payload:  
�ظ���    NVD_ALARM_OUT_OPEN_ACK
*/

    NVD_ALARM_OUT_OPEN_ACK,
/*
���ܣ�    �ֶ���alarmOut�澯��Ӧ
nData2:   0:�ɹ�
*/

    NVD_ALARM_OUT_CLOSE_REQ,
/*
���ܣ�    �ֶ��ر�alarmOut�澯����
nData1:   UserID
nData2:   DO���
payload:  
�ظ���    NVD_ALARM_OUT_CLOSE_ACK
*/

    NVD_ALARM_OUT_CLOSE_ACK,
/*
���ܣ�    �ֶ��ر�alarmOut�澯��Ӧ
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_COM = 0x90000,
    NVD_COM_GET_CFG_REQ,
/*
���ܣ�    ��ȡ͸�����ڲ���
nData1:   UserID
nData2:   ͨ��ͨ���ţ������ 0xFF��ʾȫ����ȡ
�ظ���    NVD_COM_GET_CFG_ACK
*/

    NVD_COM_GET_CFG_ACK,
/*
���ܣ�    ��ȡ͸�����ڲ����ظ�
nData2:   0:�ɹ�
payload�� NVD_COM_PARA
*/

    NVD_COM_SET_CFG_REQ,
/*
���ܣ�    ����͸�����ڲ���
nData1:   UserID
payload:  NVD_COM_PARA
�ظ���    NVD_COM_SET_CFG_ACK
*/

    NVD_COM_SET_CFG_ACK,
/*
���ܣ�    ����͸�����ڲ����ظ�
nData2:   0:�ɹ�
*/

    NVD_COM_SEND_DATA_REQ,
/*
���ܣ�    ����͸������
nData1:   UserID
nData2:   �������
playload: buffer
payload_len:  buf len
�ظ���    NVD_COM_SEND_DATA_ACK
*/

    NVD_COM_SEND_DATA_ACK,
/*
���ܣ�    ����͸�����ݻظ�
nData2:   0:�ɹ�
payload�� 0
*/

/******************************************************************************************/
    NVD_PTZ = 0xA0000,
    NVD_PTZ_GET_COM_CFG_REQ,
/*
���ܣ�    ��ȡptz ��͸�����ڲ��� ��͸������
nData1:   UserID
nData2:   ͨ��ͨ���ţ������ 0xFF��ʾȫ����ȡ
�ظ���    NVD_PTZ_GET_COM_CFG_ACK
*/

    NVD_PTZ_GET_COM_CFG_ACK,
/*
���ܣ�    ��ȡptz ��͸�����ڲ����ظ�
nData2:   0:�ɹ�
payload�� NVD_PTZ_COM_PARA
*/

    NVD_PTZ_SET_COM_CFG_REQ,
/*
���ܣ�    ����ptz ��͸�����ڲ���
nData1:   UserID
payload:  NVD_PTZ_COM_PARA
�ظ���    NVD_PTZ_SET_COM_CFG_ACK
*/

    NVD_PTZ_SET_COM_CFG_ACK,
/*
���ܣ�    ����ptz ��͸�����ڲ����ظ�
nData2:   0:�ɹ�
*/

    NVD_PTZ_SEND_COM_DATA_REQ,
/*
���ܣ�    ��ptz ��͸�����ڷ�������
nData1:   UserID
payload:  NVD_PTZ_CTRL_DATA
�ظ���    NVD_PTZ_SEND_COM_DATA_ACK
*/

    NVD_PTZ_SEND_COM_DATA_ACK,
/*
���ܣ�    ��ptz ��͸�����ڷ�������
nData2:   0:�ɹ�
*/

    NVD_PTZ_GET_PRESET_REQ,
/*
���ܣ�    ��ȡptz Ԥ��λ ����
nData1:   UserID
nData2:   ������� 0xFF��ʾȫ����ȡ
�ظ���    NVD_PTZ_GET_PRESET_ACK
*/

    NVD_PTZ_GET_PRESET_ACK,
/*
���ܣ�    ��ȡptz Ԥ��λ �����ظ�
nData2:   0:�ɹ�
payload�� NVD_PTZ_PRESET_PARA
*/

    NVD_PTZ_CTRL_PRESET_REQ,
/*
���ܣ�    ����ptz Ԥ��λ ����
nData1:   UserID
payload:  NVD_PTZ_CTRL_PRESET_PARA ************ע��ͻ�ȡ�Ľṹ�岻һ��*************
�ظ���    NVD_PTZ_CTRL_PRESET_ACK
*/

    NVD_PTZ_CTRL_PRESET_ACK,
/*
���ܣ�    ����ptz Ԥ��λ �����ظ�
nData2:   0:�ɹ�
*/

    NVD_PTZ_GET_TRACK_REQ,
/*
���ܣ�    ��ȡptz �켣 ����
nData1:   UserID
nData2:   ������� 0xFF��ʾȫ����ȡ
�ظ���    NVD_PTZ_GET_TRACK_ACK
*/

    NVD_PTZ_GET_TRACK_ACK,
/*
���ܣ�    ��ȡptz �켣 �����ظ�
nData2:   0:�ɹ�
payload�� NVD_PTZ_TRACK_PARA
*/

    NVD_PTZ_CTRL_TRACK_REQ,
/*
���ܣ�    ����ptz �켣 ����
nData1:   UserID
payload:  NVD_PTZ_CTRL_TRACK_PARA ************ע��ͻ�ȡ�Ľṹ�岻һ��*************
�ظ���    NVD_PTZ_CTRL_TRACK_ACK
*/

    NVD_PTZ_CTRL_TRACK_ACK,
/*
���ܣ�    ����ptz �켣 �����ظ�
nData2:   0:�ɹ�
*/

    NVD_PTZ_GET_CRUISE_REQ,
/*
���ܣ�    ��ȡptz Ѳ�� ����
nData1:   UserID
nData2:   ������� 0xFF��ʾȫ����ȡ
�ظ���    NVD_PTZ_GET_CRUISE_ACK
*/

    NVD_PTZ_GET_CRUISE_ACK,
/*
���ܣ�    ��ȡptz Ѳ�� �����ظ�
nData2:   0:�ɹ�
payload�� NVD_PTZ_CRUISE_PARA
*/

    NVD_PTZ_CTRL_CRUISE_REQ,
/*
���ܣ�    ����ptz Ѳ��
nData1:   UserID
payload:  NVD_PTZ_CTRL_CRUISE_PARA ************ע��ͻ�ȡ�Ľṹ�岻һ��*************
�ظ���    NVD_PTZ_SET_CRUISE_ACK
*/

    NVD_PTZ_CTRL_CRUISE_ACK,
/*
���ܣ�    ����ptz Ѳ���ظ�
nData2:   0:�ɹ�
*/

    NVD_PTZ_GET_CRUISE_POINT_CFG_REQ,
/*
���ܣ�    ��ȡptz Ѳ���� ����
nData1:   UserID
nData2:   ������� 0xFF��ʾȫ����ȡ
�ظ���    NVD_PTZ_GET_CRUISE_POINT_CFG_ACK
*/

    NVD_PTZ_GET_CRUISE_POINT_CFG_ACK,
/*
���ܣ�    ��ȡptz Ѳ���� ����
nData2:   0:�ɹ�
payload�� NVD_PTZ_CRUISE_POINT_PARA
*/

    NVD_PTZ_SET_CRUISE_POINT_CFG_REQ,
/*
���ܣ�    ����ptz Ѳ���� ����
nData1:   UserID
payload:  NVD_PTZ_CRUISE_POINT_PARA
�ظ���    NVD_PTZ_SET_CRUISE_POINT_CFG_ACK
*/

    NVD_PTZ_SET_CRUISE_POINT_CFG_ACK,
/*
���ܣ�    ����ptz Ѳ���� ����
nData2:   0:�ɹ�
*/

    NVD_PTZ_GET_DEFAULT_PRESET_CFG_REQ,
/*
���ܣ�    ��ȡptz �Զ���λ ����
nData1:   UserID
nData2:   0xFF��ʾȫ����ȡ
�ظ���    NVD_PTZ_GET_DEFAULT_PRESET_CFG_ACK
*/

    NVD_PTZ_GET_DEFAULT_PRESET_CFG_ACK,
/*
���ܣ�    ��ȡptz �Զ���λ ����
nData2:   0:�ɹ�
payload�� NVD_PTZ_DEFAULT_PRESET_PARA
*/

    NVD_PTZ_SET_DEFAULT_PRESET_CFG_REQ,
/*
���ܣ�    ����ptz �Զ���λ ����
nData1:   UserID
payload:  NVD_PTZ_DEFAULT_PRESET_PARA
�ظ���    NVD_PTZ_SET_DEFAULT_PRESET_CFG_ACK
*/

    NVD_PTZ_SET_DEFAULT_PRESET_CFG_ACK,
/*
���ܣ�    ����ptz �Զ���λ ����
nData2:   0:�ɹ�
*/

    NVD_PTZ_CTRL_RESTORE_AND_RESET_REQ = 0xA0100,
/*
���ܣ�    ����ptz ��Ƭ������о��λ, ��λ��ʱ��ͬʱ�ָ�����
nData1:   UserID
payload:  int flag, 1:��Ƭ����λ��2:һ�廯��о��λ, 3:һ�廯��о�͵�Ƭ��ͬʱ��λ
�ظ���    NVD_PTZ_CTRL_RESTORE_AND_RESET_ACK
*/

    NVD_PTZ_CTRL_RESTORE_AND_RESET_ACK,
/*
���ܣ�    ����ptz ��Ƭ������о��λ
nData2:   0:�ɹ�
*/

    NVD_PTZ_CTRL_3D_LOCATE_REQ,
/*
���ܣ�    ����ptz 3D��λ ����
nData1:   UserID
payload:  NVD_PTZ_3D_LOCATE_DATA
�ظ���    NVD_PTZ_SEND_3D_LOCATE_DATA_ACK
*/

    NVD_PTZ_CTRL_3D_LOCATE_ACK,
/*
���ܣ�    ����ptz 3D��λ ��Ӧ
nData2:   0:�ɹ�
*/

    NVD_PTZ_GET_UNI_MODULE_CFG_REQ  = 0xA0200,
/*
���ܣ�    ��ȡһ�廯��о��������
nData1:   UserID
nData2:   viNo=0
payload:  NVD_PTZ_UNI_MODULE_DATA,ֻ��Ҫ����seq,��0��ʼ���
�ظ���    NVD_PTZ_GET_UNI_MODULE_CFG_ACK
*/

    NVD_PTZ_GET_UNI_MODULE_CFG_ACK,
/*
���ܣ�    ��ȡһ�廯��о���û�Ӧ ÿ�λظ�һ����Ӧ���кŵ�����
nData2:   0:�ɹ�
payload�� NVD_PTZ_UNI_MODULE_DATA
*/

    NVD_PTZ_SET_UNI_MODULE_CFG_REQ,
/*
���ܣ�    ����һ�廯��о�������� ÿ������һ����Ӧ���кŵ�����
nData1:   UserID
nData2:   viNo=0
payload:  NVD_PTZ_UNI_MODULE_DATA
�ظ���    NVD_PTZ_SET_UNI_MODULE_CFG_ACK
*/

    NVD_PTZ_SET_UNI_MODULE_CFG_ACK,
/*
���ܣ�    ����һ�廯��о���û�Ӧ
nData2:   0:�ɹ�
*/

    NVD_PTZ_SAVE_UNI_MODULE_CFG_REQ,
/*
���ܣ�    ����һ�廯��о��������
nData1:   UserID
nData2:   viNo=0
payload:  0
�ظ���    NVD_PTZ_SAVE_UNI_MODULE_CFG_ACK
*/

    NVD_PTZ_SAVE_UNI_MODULE_CFG_ACK,
/*
���ܣ�    ����һ�廯��о���� ��Ӧ
nData2:   0:�ɹ�
*/


/******************************************************************************************/
    NVD_KEYBOARD = 0xB0000,
    NVD_KEYBOARD_SEND_CMD_REQ,
/*
���ܣ�    ģ����̷�����������
nData1:   UserID
nData2:   ͨ��ͨ����
payload�� NVD_KEYBOARD_CTRL_DATA
�ظ���    NVD_KEYBOARD_SEND_CMD_ACK
*/

    NVD_KEYBOARD_SEND_CMD_ACK,
/*
���ܣ�    ģ����̷�������ظ�
nData2:   0:�ɹ�
payload�� ��
*/

/******************************************************************************************/
    NVD_LOG = 0xC0000,
    NVD_LOG_GET_CONFIG_REQ,
/*
���ܣ�    ��ȡ������־�������
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_LOG_GET_CONFIG_ACK,
/*
���ܣ�    ��Ӧ��ȡ������־�������
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_NET_LOG_PARA)
* payload:     NVD_NET_LOG_PARA
*/

    NVD_LOG_SET_CONFIG_REQ,
/*
���ܣ�    ����������־�������
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: sizeof(NVD_NET_LOG_PARA)
* payload:     NVD_NET_LOG_PARA
*/

    NVD_LOG_SET_CONFIG_ACK,
/*
���ܣ�    ��Ӧ����������־�������
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_LOG_KEEPALIVE_REQ,
/*
���ܣ�    ��־����������IPC����
* nData1:      0
* payload_len: 0
* payload:     NULL
*/

    NVD_LOG_KEEPALIVE_ACK,
/*
���ܣ�    ��־��������
* nData2:      0:�ɹ�
* payload_len: 0
* payload:     NULL
*/

    NVD_LOG_INFO_UP,
/*
���ܣ�    log��Ϣ�ϴ�
* nData1:      0
* payload_len: ��־�ĳ���
* payload:     ��־����,����NVD_LOG_MESSAGE
* �ظ���    ��
*/

/******************************************************************************************/
    NVD_IVA = 0xD0000,
    NVD_IVA_GET_LPR_CONFIG_REQ,
/*
���ܣ�    ��ȡ���ܳ���ʶ���������
* data1:
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_LPR_CONFIG_ACK,
/*
���ܣ�    ��Ӧ���ܳ���ʶ���������
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_IVA_LPR_PARA)
* payload:     NVD_IVA_LPR_PARA
*/

    NVD_IVA_SET_LPR_CONFIG_REQ,
/*
���ܣ�    �������ܳ���ʶ���������
* data1:
* data2:       unused
* payload_len: sizeof(NVD_IVA_LPR_PARA)
* payload:     NVD_IVA_LPR_PARA
*/

    NVD_IVA_SET_LPR_CONFIG_ACK,
/*
���ܣ�    ��Ӧ���ܳ���ʶ���������
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_FR_CONFIG_REQ,
/*
���ܣ�    ��ȡ��������ʶ���������
* data1:
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_FR_CONFIG_ACK,
/*
���ܣ�    ��Ӧ��������ʶ���������
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_IVA_FR_PARA)
* payload:     NVD_IVA_FR_PARA
*/

    NVD_IVA_SET_FR_CONFIG_REQ,
/*
���ܣ�    ������������ʶ���������
* data1:
* data2:       unused
* payload_len: sizeof(NVD_IVA_FR_PARA)
* payload:     NVD_IVA_FR_PARA
*/

    NVD_IVA_SET_FR_CONFIG_ACK,
/*
���ܣ�    ��Ӧ��������ʶ���������
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/


    NVD_IVA_GET_STANDARD_CONFIG_REQ = 0xD0100,
/*
���ܣ�    ��ȡ���ܻ�����������
* data1:
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_STANDARD_CONFIG_ACK,
/*
���ܣ�    ��Ӧ���ܻ�����������
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_IVA_STANDARD_PARA)
* payload:     NVD_IVA_STANDARD_PARA
*/

    NVD_IVA_SET_STANDARD_CONFIG_REQ,
/*
���ܣ�    �������ܻ�����������
* data1:
* data2:       unused
* payload_len: sizeof(NVD_IVA_STANDARD_PARA)
* payload:     NVD_IVA_STANDARD_PARA
*/

    NVD_IVA_SET_STANDARD_CONFIG_ACK,
/*
���ܣ�    ��Ӧ���ܻ�����������
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_ADVANCED_CONFIG_REQ,
/*
���ܣ�    ��ȡ���ܸ߼���������
* data1:
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_ADVANCED_CONFIG_ACK,
/*
���ܣ�    ��Ӧ���ܸ߼���������
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_IVA_ADVANCED_PARA)
* payload:     NVD_IVA_ADVANCED_PARA
*/

    NVD_IVA_SET_ADVANCED_CONFIG_REQ,
/*
���ܣ�    �������ܸ߼���������
* data1:
* data2:       unused
* payload_len: sizeof(NVD_IVA_ADVANCED_PARA)
* payload:     NVD_IVA_ADVANCED_PARA
*/

    NVD_IVA_SET_ADVANCED_CONFIG_ACK,
/*
���ܣ�    ��Ӧ���ܸ߼���������
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_CORDON_CONFIG_REQ,
/*
���ܣ�    ��ȡ���ܾ���������
* data1:
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_CORDON_CONFIG_ACK,
/*
���ܣ�    ��Ӧ���ܾ���������
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_IVA_CORDON_PARA)
* payload:     NVD_IVA_CORDON_PARA
*/

    NVD_IVA_SET_CORDON_CONFIG_REQ,
/*
���ܣ�    �������ܾ���������
* data1:
* data2:       unused
* payload_len: sizeof(NVD_IVA_CORDON_PARA)
* payload:     NVD_IVA_CORDON_PARA
*/

    NVD_IVA_SET_CORDON_CONFIG_ACK,
/*
���ܣ�    ��Ӧ���ܾ���������
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_PPL_COUNTER_CONFIG_REQ,
/*
���ܣ�    ��ȡ��������ͳ������
* data1:
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_PPL_COUNTER_CONFIG_ACK,
/*
���ܣ�    ��Ӧ��������ͳ������
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_IVA_PPL_COUNTER_PARA)
* payload:     NVD_IVA_PPL_COUNTER_PARA
*/

    NVD_IVA_SET_PPL_COUNTER_CONFIG_REQ,
/*
���ܣ�    ������������ͳ������
* data1:
* data2:       unused
* payload_len: sizeof(NVD_IVA_PPL_COUNTER_PARA)
* payload:     NVD_IVA_PPL_COUNTER_PARA
*/

    NVD_IVA_SET_PPL_COUNTER_CONFIG_ACK,
/*
���ܣ�    ��Ӧ��������ͳ������
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_VEH_COUNTER_CONFIG_REQ,
/*
���ܣ�    ��ȡ���ܳ���ͳ������
* data1:
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_VEH_COUNTER_CONFIG_ACK,
/*
���ܣ�    ��Ӧ���ܳ���ͳ������
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_IVA_VEH_COUNTER_PARA)
* payload:     NVD_IVA_VEH_COUNTER_PARA
*/

    NVD_IVA_SET_VEH_COUNTER_CONFIG_REQ,
/*
���ܣ�    �������ܳ���ͳ������
* data1:
* data2:       unused
* payload_len: sizeof(NVD_IVA_VEH_COUNTER_PARA)
* payload:     NVD_IVA_VEH_COUNTER_PARA
*/

    NVD_IVA_SET_VEH_COUNTER_CONFIG_ACK,
/*
���ܣ�    ��Ӧ���ܳ���ͳ������
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_HL_CONFIG_REQ,
/*
���ܣ�    ��ȡ�������������
* data1:
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_IVA_GET_HL_CONFIG_ACK,
/*
���ܣ�    ��Ӧ�������������
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_IVA_HL_PARA)
* payload:     NVD_IVA_HL_PARA
*/

    NVD_IVA_SET_HL_CONFIG_REQ,
/*
���ܣ�    �����������������
* data1:
* data2:       unused
* payload_len: sizeof(NVD_IVA_HL_PARA)
* payload:     NVD_IVA_HL_PARA
*/

    NVD_IVA_SET_HL_CONFIG_ACK,
/*
���ܣ�    ��Ӧ�������������
* data1:
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

/******************************************************************************************/
    NVD_SD = 0xE0000,
    NVD_SD_GET_INFO_REQ,
/*
���ܣ�  ��ȡSD���������
ndata1: UserID
ndata2: ͨ����
�ظ���  NVD_SD_GET_INFO_ACK
*/

    NVD_SD_GET_INFO_ACK,
/*
����:        ��ȡSD��������ûظ�
ndata2:      NVD_ERROR_NUM
payload_len: sizeof(NVD_SD_PARA)
payload:     NVD_SD_PARA
*/

    NVD_SD_UMOUNT_REQ,
/*
���ܣ�    ж��SD��
nData1:   UserID
nData2:   ͨ����
�ظ���    NVD_SD_UMOUNT_ACK
*/

    NVD_SD_UMOUNT_ACK,
/*
���ܣ�    ж��SD���ظ�
nData2:   0:�ɹ�
*/

    NVD_SD_FORMAT_REQ,
/*
���ܣ�    ��ʽ��SD��
nData1:   UserID
nData2:   ͨ����
�ظ���    NVD_SD_FORMAT_ACK
*/

    NVD_SD_FORMAT_ACK,
/*
���ܣ�    ��ʽ��SD���ظ�
nData2:   0:�ɹ�
*/

    NVD_SD_QUERY_DIR_REQ,
/*
���ܣ�          ��ѯSD����Ŀ¼
ndata1:         UserID
ndata2:         unused
payload_len:    Ŀ¼·���ĳ���
payload:        ��Ҫ��ѯ��Ŀ¼·������: /sd/pic

�ظ���  NVD_SD_QUERY_DIR_ACK
*/

    NVD_SD_QUERY_DIR_ACK,
/*
���ܣ�          ��ѯSD����Ŀ¼�ظ�
ndata1:         unused
ndata2:         NVD_ERROR_NUM
payload_len:    ����
payload:        Ŀ¼�µ��ļ�����Ŀ¼��(��':'���ŷָ�)
*/
    
    NVD_SD_MOUNT_REQ,
/*
���ܣ�    ж��SD��
nData1:   UserID
nData2:   ͨ����
�ظ���    NVD_SD_MOUNT_ACK
*/

    NVD_SD_MOUNT_ACK,
/*
���ܣ�    ж��SD���ظ�
nData2:   0:�ɹ�
*/


/******************************************************************************************/
    NVD_JPEG = 0xF0000,
    NVD_JPEG_GET_PIC_REQ,
/*
���ܣ�    ��ȡJPEGͼƬ����
nData1:   UserID
payload:  NVD_JPEG_HEAD
�ظ���    NVD_JPEG_GET_PIC_ACK
*/

    NVD_JPEG_GET_PIC_ACK,
/*
���ܣ�    ��ȡJPEGͼƬ����ظ�
nData1:   JPEGId
nData2:   0:�ɹ�
*/

/******************************************************************************************/
    NVD_CAPTURE = 0x100000,
    NVD_CAPTURE_FIND_REQ,
/*
���ܣ�    ��ѯǰ��ץ��ͼƬ����
nData1:   UserID
nData2:   ͨ����
payload:  NVD_FIND_PICTURE_PARAM
�ظ���    NVD_CAPTURE_QUERY_ACK
*/

    NVD_CAPTURE_FIND_ACK,
/*
���ܣ�    ��ѯǰ��ץ��ͼƬ����ظ�
nData1:   UserID
nData2:   0:�ɹ�
payload:  ��ѯ������
*/

	NVD_CAPTURE_FIND_NEXT_REQ,
/*
���ܣ�	  ��ѯ��һ��(����)ͼƬ����
nData1:   UserID
nData2:   ͨ����
payload:  ��ѯ������
�ظ���	  NVD_CAPTURE_QUERY_ACK
*/

	NVD_CAPTURE_FIND_NEXT_ACK,
/*
���ܣ�	  ��ѯ��һ��(����)ͼƬ����ظ�
nData1:   UserID
nData2:   0:�ɹ�
payload:  ǰ���ֽ�Ϊ��ѯ����ͼƬ����
*/

    NVD_CAPTURE_CLOSE_FIND_REQ,
/*
����:     �رղ�ѯǰ��ץ��ͼƬ����
nData1:   UserID
*/

    NVD_CAPTURE_CLOSE_FIND_ACK,
/*
���ܣ�	  �رղ�ѯǰ��ץ��ͼƬ�ظ�
nData1:   UserID
nData2:   0:�ɹ�
*/

    NVD_CAPTURE_GET_PICTURE_REQ,
/*
����:    ��ȡǰ��ץ��ͼƬ����
nData1:  UserID
payload: ͼƬ�ļ���
*/

	NVD_CAPTURE_GET_PICTURE_ACK,
/*
����:	 ��ȡǰ��ץ��ͼƬ����ظ�
nData1:  UserID
nData2:  0:�ɹ�
payload: ǰ���ֽ�ΪͼƬ���ݴ�С
*/


    NVD_EVENT_ILL
}NVD_EVENT;

#endif

