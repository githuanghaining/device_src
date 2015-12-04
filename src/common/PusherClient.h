#ifndef __PUSHER_CLIENT_H__
#define __PUSHER_CLIENT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*
在对外的接口函数前 增加了Core_前缀

Todo:
检查汇报的日志时间计算错误问题
播放端弹出慢时 编码方式会出问题
确认linux下时间精度问题：usleep nanosleep setitimer select
*/
#define VERSON                                  24

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

/*
对外发送消息的回调函数(json格式)：
当新绑定了摄像头时            {"Name":"NewBoundCamera"}
当解绑了摄像头时              {"Name":"UnBoundCamera"}
当新被授权了摄像头时          {"Name":"NewAuthCamera"}
当被取消授权了摄像头时        {"Name":"CancelAuthCamera"}
当接受并建立了连接时          {"Name":"ConnectionAcceptted"}
当连接断开时                  {"Name":"ConnectionClosed"}
收到音视频数据时              {"Name":"StartPopData"}
当设备登录成功或者配置变换时   {"Name":"PopConfig","Message":"HexConfigString(256字节 512字符)"}
当设备收到在线消息时          {"Name":"PopMessage","Message":"HexMessageString(变长)","SrcID":"发送方ID"}
当设备收到离线消息时          {"Name":"PopOffLineMessage","Message":"HexMessageString(变长)","SrcID":"发送方ID"}
*/
typedef int (*MessageCallBack)(void *apData, const char *aMessage);

//开始云服务 接收调度命令                      ini格式的配置串      回调参数    开始采集并压缩音视频数据的回调函数
unsigned int    Core_StartCloudService(const char* aConfigString, void *apData, MessageCallBack apMessageCallBack);
//返回值 0:成功 1:失败

//停止云服务
void            Core_StopCloudService();

//获取各种状态信息 
char*           Core_GetStatus();
//返回值 以JSON格式给出的字符串 由外面负责释放

//往该服务塞入音视频采样数据    数据层索引 当前固定为0           音视频采样缓冲区          音视频采样缓冲区长度       32位时间戳单位毫秒  采样类型h264 NALU_TYPE 或者 音频类型
unsigned int    Core_PushData(unsigned int aDataLevelPos, const char *aDataBuffer, unsigned int aBufferLength, unsigned int aTimestamp, unsigned char apFrameSampleType);
//返回值 0:成功 1:失败

//弹出一个音视频采样           数据层索引 当前固定为0                        采样数据长度                 32位时间戳  采样类型h264 NALU_TYPE 或者 音频类型
char*           Core_PopData(unsigned int aDataLevelPos, unsigned int *apFrameSampleLength, unsigned int *apTimestamp, unsigned char *apFrameSampleType);
//返回值 音视频采样缓冲区

//断开连接
unsigned char   Core_Disconnect();
//返回值 最后的状态代码 (ClientStatusEm)

//连接设备                                 设备ID  连接字符串，在目标设备上通过GetConnecttionString获取
unsigned char   Core_ConnectToClient(unsigned int aID, const char *aConnectString, const unsigned char *aParameterBuffer);
//返回值 最后的状态代码 (ClientStatusEm)

//连接服务端  0是待命 1是udp广播 2是rtmp广播 3是录像 4是录像广播      6字节的转发Ip+Port
unsigned char   Core_ConnectToServer(unsigned char aMode, unsigned char *aServerConnectInfo);
//返回值 最后的状态代码 (ClientStatusEm)

//获取连接串 60秒有效     
char*           Core_GetConnecttionString();
//返回值 连接字符串用于传递给需要连接本设备的另一方  缓冲区由外面负责释放

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
