#ifndef __PUSHER_CLIENT_H__
#define __PUSHER_CLIENT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*
�ڶ���Ľӿں���ǰ ������Core_ǰ׺

Todo:
���㱨����־ʱ������������
���Ŷ˵�����ʱ ���뷽ʽ�������
ȷ��linux��ʱ�侫�����⣺usleep nanosleep setitimer select
*/
#define VERSON                                  24

//StatusBuffer[CLIENT_STATUS_BUFFER_LENGTH]; //0�ֽڴ���nat���� 1�ֽڴ���ǰ����״̬ 2�ֽڴ����Ƿ���Ҫ�������� 3�ֽڴ����Ƿ���Ҫ���� 4�ֽڴ�������ģʽ 0�Ǵ��� 1��udp�㲥 2��rtmp�㲥 3��¼�� 4��¼��㲥
//��ǰ״̬
typedef enum {
	CLIENT_STATUS_CODE_READY              =     1,      //��ʼ״̬
	CLIENT_STATUS_CODE_REQUEST_RELAY      =     2,      //��������ת��
	CLIENT_STATUS_CODE_CONNECTING         =     3,      //����������
	CLIENT_STATUS_CODE_WORKING            =     4,      //����ֱ��
	CLIENT_STATUS_CODE_STOPING            =     5,      //ֹͣ������ 
	CLIENT_STATUS_CODE_ERROR              =     255     //�쳣״̬
} ClientStatusEm;

typedef enum {
	WORK_MODE_STANDBY       = 0,      //����
	WORK_MODE_UDP_BROD      = 1,      //udp�㲥
	WORK_MODE_RTMP_BROD     = 2,      //rtmp�㲥
	WORK_MODE_RELAY_STORAGE = 3,      //ͨ��ת��¼��
	WORK_MODE_STORAGE_BROD  = 4       //¼��㲥
} WorkModeEm;

//����nat����
typedef enum {
	NAT_TYPE_INTERNET  = 1, //�����Ĺ���IP
	NAT_TYPE_UNKOWN    = 2, //δ֪����
	NAT_TYPE_SYNMETRIC = 3, //�Գ�����
	NAT_TYPE_CONE      = 4  //׶��
} NatTypeEm;

//����֡����
typedef enum {
	NALU_TYPE_SLICE = 1,
	NALU_TYPE_DPA = 2,
	NALU_TYPE_DPB = 3,
	NALU_TYPE_DPC = 4,
	NALU_TYPE_IDR = 5,
	NALU_TYPE_SEI = 6,
	NALU_TYPE_SPS = 7,
	NALU_TYPE_PPS = 8,
	NALU_TYPE_AUD = 9,
	NALU_TYPE_EOSEQ = 10,
	NALU_TYPE_EOSTREAM = 11,
	NALU_TYPE_FILL = 12,
	NALU_TYPE_PREFIX = 14,
	NALU_TYPE_SUB_SPS = 15,
	NALU_TYPE_SLC_EXT = 20,
	NALU_TYPE_VDRD = 24,
	OPUS_TYPE_SAMPLE = 127,
	AAC_TYPE_INFO = 128,
	AAC_TYPE_SAMPLE = 129
} FrameSampleTypeEm;

/*
���ⷢ����Ϣ�Ļص�����(json��ʽ)��
���°�������ͷʱ            {"Name":"NewBoundCamera"}
�����������ͷʱ              {"Name":"UnBoundCamera"}
���±���Ȩ������ͷʱ          {"Name":"NewAuthCamera"}
����ȡ����Ȩ������ͷʱ        {"Name":"CancelAuthCamera"}
�����ܲ�����������ʱ          {"Name":"ConnectionAcceptted"}
�����ӶϿ�ʱ                  {"Name":"ConnectionClosed"}
�յ�����Ƶ����ʱ              {"Name":"StartPopData"}
���豸��¼�ɹ��������ñ任ʱ   {"Name":"PopConfig","Message":"HexConfigString(256�ֽ� 512�ַ�)"}
���豸�յ�������Ϣʱ          {"Name":"PopMessage","Message":"HexMessageString(�䳤)","SrcID":"���ͷ�ID"}
���豸�յ�������Ϣʱ          {"Name":"PopOffLineMessage","Message":"HexMessageString(�䳤)","SrcID":"���ͷ�ID"}
*/
typedef int (*MessageCallBack)(void *apData, const char *aMessage);

//��ʼ�Ʒ��� ���յ�������                      ini��ʽ�����ô�      �ص�����    ��ʼ�ɼ���ѹ������Ƶ���ݵĻص�����
unsigned int    Core_StartCloudService(const char* aConfigString, void *apData, MessageCallBack apMessageCallBack);
//����ֵ 0:�ɹ� 1:ʧ��

//ֹͣ�Ʒ���
void            Core_StopCloudService();

//��ȡ����״̬��Ϣ 
char*           Core_GetStatus();
//����ֵ ��JSON��ʽ�������ַ��� �����渺���ͷ�

//���÷�����������Ƶ��������    ���ݲ����� ��ǰ�̶�Ϊ0           ����Ƶ����������          ����Ƶ��������������       32λʱ�����λ����  ��������h264 NALU_TYPE ���� ��Ƶ����
unsigned int    Core_PushData(unsigned int aDataLevelPos, const char *aDataBuffer, unsigned int aBufferLength, unsigned int aTimestamp, unsigned char apFrameSampleType);
//����ֵ 0:�ɹ� 1:ʧ��

//����һ������Ƶ����           ���ݲ����� ��ǰ�̶�Ϊ0                        �������ݳ���                 32λʱ���  ��������h264 NALU_TYPE ���� ��Ƶ����
char*           Core_PopData(unsigned int aDataLevelPos, unsigned int *apFrameSampleLength, unsigned int *apTimestamp, unsigned char *apFrameSampleType);
//����ֵ ����Ƶ����������

//�Ͽ�����
unsigned char   Core_Disconnect();
//����ֵ ����״̬���� (ClientStatusEm)

//�����豸                                 �豸ID  �����ַ�������Ŀ���豸��ͨ��GetConnecttionString��ȡ
unsigned char   Core_ConnectToClient(unsigned int aID, const char *aConnectString, const unsigned char *aParameterBuffer);
//����ֵ ����״̬���� (ClientStatusEm)

//���ӷ����  0�Ǵ��� 1��udp�㲥 2��rtmp�㲥 3��¼�� 4��¼��㲥      6�ֽڵ�ת��Ip+Port
unsigned char   Core_ConnectToServer(unsigned char aMode, unsigned char *aServerConnectInfo);
//����ֵ ����״̬���� (ClientStatusEm)

//��ȡ���Ӵ� 60����Ч     
char*           Core_GetConnecttionString();
//����ֵ �����ַ������ڴ��ݸ���Ҫ���ӱ��豸����һ��  �����������渺���ͷ�

//�����Ǵ洢����ר�� ��Ӧ�ù�����������
void            InitEncoder8();

int             Encoder8FillAllData(unsigned char** aBufffer);

unsigned char*  Encoder8Encode(unsigned int aGroupIndex);

void            InitDecoder8();

//ע�� Ӧ���ȼ���ȫ���ķǱ���� Ȼ���ټ��ر����
int             Decoder8LoadDataRow(unsigned int aGroupIndex, unsigned char* aBufffer);

unsigned char** Decoder8Decode();

void            UnInitDecoder8();

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* End of #ifndef __PUSHER_CLIENT_H__ */
