#ifndef __PUSHER_CLIENT_H__
#define __PUSHER_CLIENT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*
修正了日志汇报里的一个错误
支持了后台消息推送

Todo:
检查汇报的日志时间计算错误问题
播放端弹出慢时 编码方式会出问题
确认linux下时间精度问题：usleep nanosleep setitimer select
*/
#define VERSON                                  84

//StatusBuffer[CLIENT_STATUS_BUFFER_LENGTH]; //0字节代表nat类型 1字节代表当前工作状态 2字节代表是否需要心跳返回 3字节代表是否需要编码 4字节代表启动模式 0是待命 1是udp广播 2是rtmp广播 3是录像 4是录像广播
//当前状态
typedef enum {
	CLIENT_STATUS_CODE_READY              =     1,      //初始状态
	CLIENT_STATUS_CODE_REQUEST_RELAY      =     2,      //正在请求转发
	CLIENT_STATUS_CODE_CONNECTING         =     3,      //正在连接中
	CLIENT_STATUS_CODE_WORKING            =     4,      //正在直播
	CLIENT_STATUS_CODE_STOPING            =     5,      //停止过程中 
	CLIENT_STATUS_CODE_ERROR              =     255     //异常状态
} ClientStatusEm;

typedef enum {
	WORK_MODE_STANDBY       = 0,      //待命
	WORK_MODE_UDP_BROD      = 1,      //udp广播
	WORK_MODE_RTMP_BROD     = 2,      //rtmp广播
	WORK_MODE_RELAY_STORAGE = 3,      //通过转发录像
	WORK_MODE_STORAGE_BROD  = 4       //录像广播
} WorkModeEm;

//网关nat类型
typedef enum {
	NAT_TYPE_INTERNET  = 1, //独立的公网IP
	NAT_TYPE_UNKOWN    = 2, //未知类型
	NAT_TYPE_SYNMETRIC = 3, //对称类型
	NAT_TYPE_CONE      = 4  //锥形
} NatTypeEm;

//数据帧类型
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

//对外发送消息的回调函数：
//当该服务接收到调度服务器的开始推送命令时 会发出消息通知外壳调用PushData函数塞数据 json格式：{"Name":"StartPushData"}
//当需要停止塞数据时 json格式：{"Name":"StopPushData"}
//当该服务接收到时 对方发送的媒体数据时，会发出消息通知外壳调用PopData函数收数据 json格式：{"Name":"StartPopData"}
//当需要需要停止收数据时 json格式：{"Name":"StopPopData"}
typedef int (*MessageCallBack)(void *apData, const char *aMessage);

//开始云服务 接收调度命令         ini格式的配置串       开始采集并压缩音视频数据的回调函数
void            StartCloudService(const char* aConfigString, void *apData, MessageCallBack apMessageCallBack);

//停止云服务
void            StopCloudService();

//获取以JSON格式给出的各种状态信息 返回的字符串由外面负责释放
char*           GetStatus(); 

//推送消息             摄像头ID 往手机推送时为0       二进制消息缓冲区       缓冲区长度 最大256
int             PushMessage(unsigned int aID, const char *aMessage, unsigned int aMessageLen);

//往该服务塞入音视频采样数据  数据层索引 当前固定为0    音视频采样缓冲区          音视频采样缓冲区长度    32位时间戳单位毫秒  采样类型h264 NALU_TYPE 或者 音频类型
int             PushData(unsigned int aDataLevelPos, const char *aDataBuffer, unsigned int aBufferLength, unsigned int aTimestamp, unsigned char apFrameSampleType);

//弹出一个音视频采样缓冲区 数据层索引 当前固定为0           采样数据长度              32位时间戳  采 样类型h264 NALU_TYPE 或者 音频类型
char*           PopData(unsigned int aDataLevelPos, unsigned int *apFrameSampleLength, unsigned int *apTimestamp, unsigned char *apFrameSampleType);

//断开连接
int             Disconnect();

//以下是手机专用
//摄像机绑定     摄像机序列号20字节             摄像头ID
unsigned char   CameraBound(const char *aSN, unsigned int *apID);

//摄像机解除绑定              摄像头ID
unsigned char   CameraUnBound(unsigned int aID);

//连接摄像头                       摄像头ID
void            ConnectMediaSource(unsigned int aID);

//以下是摄像头专用
//摄像机注册               摄像机序列号20字节        初始配置256字节                  摄像头ID
unsigned char   CameraRegist(const char *aSN, const char* aConfig, unsigned int *apCameraID);

                //0是待命 1是udp广播 2是rtmp广播 3是录像 4是录像广播
int             StartConnectToServer(unsigned char aMode, unsigned char aAreaID);

//以下是存储解码专用 不应该公开给第三方
void            InitEncoder8();

int             Encoder8FillAllData(unsigned char** aBufffer);

unsigned char*  Encoder8Encode(unsigned int aGroupIndex);

void            InitDecoder8();

//注意 应该先加载全部的非编码包 然后再加载编码包
int             Decoder8LoadDataRow(unsigned int aGroupIndex, unsigned char* aBufffer);

unsigned char** Decoder8Decode();

void            UnInitDecoder8();

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* End of #ifndef __PUSHER_CLIENT_H__ */
