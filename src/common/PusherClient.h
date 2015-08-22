#ifndef __PUSHER_CLIENT_H__
#define __PUSHER_CLIENT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*
��������־�㱨���һ������
֧���˺�̨��Ϣ����

Todo:
���㱨����־ʱ������������
���Ŷ˵�����ʱ ���뷽ʽ�������
ȷ��linux��ʱ�侫�����⣺usleep nanosleep setitimer select
*/
#define VERSON                                  84

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

//���ⷢ����Ϣ�Ļص�������
//���÷�����յ����ȷ������Ŀ�ʼ��������ʱ �ᷢ����Ϣ֪ͨ��ǵ���PushData���������� json��ʽ��{"Name":"StartPushData"}
//����Ҫֹͣ������ʱ json��ʽ��{"Name":"StopPushData"}
//���÷�����յ�ʱ �Է����͵�ý������ʱ���ᷢ����Ϣ֪ͨ��ǵ���PopData���������� json��ʽ��{"Name":"StartPopData"}
//����Ҫ��Ҫֹͣ������ʱ json��ʽ��{"Name":"StopPopData"}
typedef int (*MessageCallBack)(void *apData, const char *aMessage);

//��ʼ�Ʒ��� ���յ�������         ini��ʽ�����ô�       ��ʼ�ɼ���ѹ������Ƶ���ݵĻص�����
void            StartCloudService(const char* aConfigString, void *apData, MessageCallBack apMessageCallBack);

//ֹͣ�Ʒ���
void            StopCloudService();

//��ȡ��JSON��ʽ�����ĸ���״̬��Ϣ ���ص��ַ��������渺���ͷ�
char*           GetStatus(); 

//������Ϣ             ����ͷID ���ֻ�����ʱΪ0       ��������Ϣ������       ���������� ���256
int             PushMessage(unsigned int aID, const char *aMessage, unsigned int aMessageLen);

//���÷�����������Ƶ��������  ���ݲ����� ��ǰ�̶�Ϊ0    ����Ƶ����������          ����Ƶ��������������    32λʱ�����λ����  ��������h264 NALU_TYPE ���� ��Ƶ����
int             PushData(unsigned int aDataLevelPos, const char *aDataBuffer, unsigned int aBufferLength, unsigned int aTimestamp, unsigned char apFrameSampleType);

//����һ������Ƶ���������� ���ݲ����� ��ǰ�̶�Ϊ0           �������ݳ���              32λʱ���  �� ������h264 NALU_TYPE ���� ��Ƶ����
char*           PopData(unsigned int aDataLevelPos, unsigned int *apFrameSampleLength, unsigned int *apTimestamp, unsigned char *apFrameSampleType);

//�Ͽ�����
int             Disconnect();

//�������ֻ�ר��
//�������     ��������к�20�ֽ�             ����ͷID
unsigned char   CameraBound(const char *aSN, unsigned int *apID);

//����������              ����ͷID
unsigned char   CameraUnBound(unsigned int aID);

//��������ͷ                       ����ͷID
void            ConnectMediaSource(unsigned int aID);

//����������ͷר��
//�����ע��               ��������к�20�ֽ�        ��ʼ����256�ֽ�                  ����ͷID
unsigned char   CameraRegist(const char *aSN, const char* aConfig, unsigned int *apCameraID);

                //0�Ǵ��� 1��udp�㲥 2��rtmp�㲥 3��¼�� 4��¼��㲥
int             StartConnectToServer(unsigned char aMode, unsigned char aAreaID);

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
