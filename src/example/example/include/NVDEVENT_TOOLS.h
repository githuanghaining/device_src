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

#define NVD_DEFAULT_UDP_DATA_PORT          11560       //ȱʡ��udp���ݶ˿ں�
#define NVD_DEFAULT_TCP_DATA_PORT          12560       //ȱʡ��tcp���ݶ˿ں�
#define NVD_DEFAULT_BROAD_SEARCH_PORT      10100


#define NVD_CMD_PREFIX              0x55aa55aa
#define NVD_CMD_VERSION             0x030409           //�汾��
#define NVD_CMD_HEADER_LEN          32
#define NVD_MAX_CMD_PAYLOAD_LEN     1400

#define NVD_GET_CMD_TYPE(cmd)       (cmd&0xFFFF0000)


#define NVD_SU_LOGID    0xa5a5a5a5

#define NVD_CFG_MAX_PTZ_UNI_MODULE_NUM  100     //�������������
#define NVD_CFG_MAX_PTZ_UNI_MODULE_LEN  20      //  һ�廯��о������Ϣ��󳤶� 


/* ȫ��ʹ��С�ֽ��� */
typedef struct
{
    unsigned int    prefix;        //��������ǰ׺0x55aa55aa
    unsigned int    version;       //����汾��
    unsigned int    commandId;     //����ID
    unsigned int    event;         //��������
    unsigned int    data1;         //Я������1 ���¼ID
    unsigned int    data2;         //Я������2
    unsigned short  payload_len;   //�غɳ���
    unsigned char   res[2];        //����
    unsigned int    checksum;      //У���
    unsigned char   payload[NVD_MAX_CMD_PAYLOAD_LEN];   //�غ�����
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
    unsigned short  crc16;              /* �汾�ļ���У���*/
    unsigned short  signature;          /* 0x4e43 "CN" 2.0֮ǰ�İ汾, 0x4e57 "WN" 2.0֮��İ汾 */
    unsigned int    sections;           /* �汾�Ĵ�С(�Ѿ�������)*/
    unsigned int    lowest;             /* lowest address */
    unsigned int    highest;            /* highest address */
    char            version[NVD_VER_STR_LEN];
    unsigned int    tTime;              /* �汾�ļ�������ʱ��*/
    unsigned int    uncmpsize;          /* ѹ��ǰ�汾�Ĵ�С */
    unsigned short  uncmpcrc16;         /* ѹ��ǰ�汾��У��� */
    unsigned short  vertype;
    unsigned int    position;           /*��ʾ�汾��FLASH�е�λ�ã������汾ʱΪ0*/
    unsigned int    mainversion;        /*1����ʾ�ð汾Ϊ����ʹ�ð汾��0��ʾ�Ǳ��ð汾�������汾ʱ��λΪ0*/
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
���ܣ�    �ϲ��򵥰巢�ͻ�ȡ������Ϣ����
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_BURN_GET_FACTORY_ACK,
/*
���ܣ�    �ϲ��򵥰巢�ͻ�ȡ������Ϣ��Ӧ
* data1:       NVD_SU_LOGID
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_FACTORY_PARA)
* payload:     NVD_FACTORY_PARA
*/

    NVD_BURN_SET_FACTORY_REQ,
/*
���ܣ�    �����ϱ����豸��Ϣ���ó�����Ϣ����
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: 2*sizeof(NVD_FACTORY_PARA)
* payload:     NVD_FACTORY_PARA + NVD_FACTORY_PARA
* ���ڳ�����д�����Ҫ��payload�з�������NVD_FACTORY_PARA�ṹ�壬�µ���ǰ��ԭ�����ں�
*              ����ֻ�����ϵ���ԭ�������ã����ڵ������ָ������Ƿ��Ƿ�������ģ�
*              payload_lenΪ 2 * sizeof(NVD_FACTORY_PARA)���㲥����;
*/

    NVD_BURN_SET_FACTORY_ACK,
/*
���ܣ�    �ϲ��򵥰巢�����ó�����Ϣ��Ӧ
* data1:       NVD_SU_LOGID
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_BURN_GET_ADVANCED_REQ,
/*
���ܣ�    �ϲ��򵥰巢�ͻ�߼�������Ϣ����
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_BURN_GET_ADVANCED_ACK,
/*
���ܣ�    �ϲ��򵥰巢�ͻ�ȡ�߼�������Ӧ
* data1:       NVD_SU_LOGID
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_FACTORY_PARA)+sizeof(NVD_ADVANCED_PARA)
* payload:     NVD_FACTORY_PARA+NVD_ADVANCED_PARA
*/

    NVD_BURN_SET_ADVANCED_REQ,
/*
���ܣ�    �����ϱ����豸��Ϣ���ø߼���������
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: sizeof(NVD_ADVANCED_PARA) + sizeof(NVD_FACTORY_PARA)
* payload:     NVD_FACTORY_PARA + NVD_ADVANCED_PARA
* ���ڳ�����д�����Ҫ��payload�з��� NVD_ADVANCED_PARA + NVD_FACTORY_PARA�ṹ��
*              ����ֻ�����ϵ���ԭ�������ã����ڵ������ָ������Ƿ��Ƿ�������ģ�
*              payload_lenΪ sizeof(NVD_ADVANCED_PARA) + sizeof(NVD_FACTORY_PARA)���㲥����;
*/

    NVD_BURN_SET_ADVANCED_ACK,
/*
���ܣ�    �ϲ��򵥰巢�����ø߼�������Ӧ
* data1:       NVD_SU_LOGID
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

/******************************************************************************************/
    NVD_SYS                     = 0x10000,
    NVD_SYS_GET_SEARCH_REQ,
/*
���ܣ�    �ϲ��򵥰巢����������㲥����,����̽��
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_SYS_GET_SEARCH_ACK,
/*
���ܣ�    �豸��Ӧ����������ϲ���������������Ϣ���㲥��
* data1:       unused
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_SEARCH_PARA)
* payload:     NVD_SEARCH_PARA
*/

    NVD_SYS_SET_SEARCH_REQ,
/*
���ܣ�    �ϲ��򵥰巢��������������㲥����
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: 2*sizeof(NVD_SEARCH_PARA)
* payload:     NVD_SEARCH_PARA*2
* �������������Ҫ��payload�з�������NVD_SEARCH_PARA�ṹ�壬�µ���ǰ��ԭ�����ں�
*              ����ֻ�����ϵ���ԭ�������ã����ڵ������ָ������Ƿ��Ƿ�������ģ�
*              payload_lenΪ 2 * sizeof(NVD_SEARCH_PARA)���㲥����;
*/

    NVD_SYS_SET_SEARCH_ACK,
/*
���ܣ�    �豸��Ӧ��������������ϲ���������������Ϣ���㲥��
* data1:       unused
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_SYS_GET_NET_CONFIG_REQ,
/*
���ܣ�    �ϲ��򵥰��ȡ������������
* data1:       id
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_SYS_GET_NET_CONFIG_ACK,
/*
���ܣ�    �ϲ��򵥰��ȡ��������������Ӧ
* data1:       id
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(NVD_NET_PARA)
* payload:     NVD_NET_PARA
*/

    NVD_SYS_SET_NET_CONFIG_REQ,
/*
���ܣ�    �����ϱ����豸��Ϣ�����豸�������
* data1:       NVD_SU_LOGID/����������¼ID
* data2:       unused
* payload_len: sizeof(NVD_NET_PARA)
* payload:     NVD_NET_PARA
*/

    NVD_SYS_SET_NET_CONFIG_ACK,
/*
���ܣ�    �豸��Ӧ����������ϲ���������������Ϣ��
* data1:       unused
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

/******************************************************************************************/
    NVD_VER             = 0x20000,
    NVD_VER_GET_VER_REQ,
/*
���ܣ�    ��ȡ�豸�汾
* data1:       NVD_SU_LOGID
* data2:       NVD_VER_TYPE
* payload_len: 0
* payload:     NULL
*/

    NVD_VER_GET_VER_ACK,
/*
���ܣ�    ��ȡ�豸�汾�ظ�
* data1:       unused
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(nvd_ver_head)
* payload:     nvd_ver_head / NULL
*/

    NVD_VER_DELETE_VER_REQ,
/*
���ܣ�    ɾ���豸�汾 ������ɾAPP
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: 0
* payload:     NULL
*/

    NVD_VER_DELETE_VER_ACK,
/*
���ܣ�    ɾ���豸�汾�ظ�
* data1:       unused
* data2:       NVD_ERROR_NUM
* payload_len: 0
* payload:     NULL
*/

    NVD_VER_UPDATE_VER_REQ,
/*
���ܣ�    ���³�ʼ������
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: sizeof(nvd_ver_head)
* payload:     nvd_ver_head
*/

    NVD_VER_UPDATE_VER_ACK,
/*
���ܣ�    ���³�ʼ���ظ�
* data1:       unused
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(nvd_ver_err_str)
* payload:     nvd_ver_err_str  //�ɵ�����д���������ֻ��ʾ
*/

    NVD_VER_UPDATE_VER_TRANS_REQ,
/*
���ܣ�    �����豸�汾������������
* data1:       NVD_SU_LOGID
* data2:       ����ţ���0��ʼ�����һ������ NVD_VER_LAST_VER_PACKET_INDEX
* payload_len: sizeof(package)
* payload:     package
*/

    NVD_VER_UPDATE_VER_TRANS_ACK,
/*
���ܣ�    �����豸�汾�������ݻظ�
* data1:       unused
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(package index)
* payload:     package index
*/

    NVD_VER_UPDATE_CRC_VER_REQ,
/*
���ܣ�    CRC��ȫ���³�ʼ������
* data1:       NVD_SU_LOGID
* data2:       unused
* payload_len: sizeof(nvd_ver_head)
* payload:     nvd_ver_head
*/

    NVD_VER_UPDATE_CRC_VER_ACK,
/*
���ܣ�    CRC��ȫ���³�ʼ���ظ�
* data1:       unused
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(nvd_ver_err_str)
* payload:     nvd_ver_err_str  //�ɵ�����д���������ֻ��ʾ
*/

    NVD_VER_UPDATE_CRC_VER_TRANS_REQ,
/*
���ܣ�    CRC��ȫ�����豸�汾������������
* data1:       NVD_SU_LOGID
* data2:       ����ţ���0��ʼ�����һ������ NVD_VER_LAST_VER_PACKET_INDEX
* payload_len: sizeof(package)
* payload:     package
*/

    NVD_VER_UPDATE_CRC_VER_TRANS_ACK,
/*
���ܣ�    CRC��ȫ�����豸�汾�������ݻظ�
* data1:       unused
* data2:       NVD_ERROR_NUM
* payload_len: sizeof(package index)
* payload:     package index
*/

/******************************************************************************************/
    NVD_EVENT_TOOLS_ILL
}NVD_EVENT_TOOLS;

#endif

