#ifndef __CAMERA_API_H__
#define __CAMERA_API_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif
    
    
    //对外发送消息的回调函数：
    //当该服务接收到调度服务器的开始推送命令时 会发出消息通知外壳调用PushData函数塞数据 json格式：{"Name":"ConnectionAcceptted"}
    //当需要停止塞数据时 停止收数据 json格式：{"Name":"ConnectionClosed"}
    //当该服务接收到时 对方发送的媒体数据时，会发出消息通知外壳调用PopData函数收数据 json格式：{"Name":"StartPopData"}
    // 当设备登录成功或者配置变换时   {"Name":"PopConfig","Message":"HexConfigString(256字节 512字符)"}
    //当设备收到在线消息时          {"Name":"PopMessage","Message":"HexMessageString(变长)","SrcID":"发送方ID"}
    //当设备收到离线消息时          {"Name":"PopOffLineMessage","Message":"HexMessageString(变长)","SrcID":"发送方ID"} 
#if 1   
 
		//当前状态
		typedef enum {
			CLIENT_STATUS_CODE_READY              =     1,      //初始状态
			CLIENT_STATUS_CODE_REQUEST_RELAY      =     2,      //正在请求转发
			CLIENT_STATUS_CODE_CONNECTING_LIVE    =     3,      //正在连接中
			CLIENT_STATUS_CODE_LIVEING            =     4,      //正在直播
			CLIENT_STATUS_CODE_STOPING            =     5,      //停止过程中 
			CLIENT_STATUS_CODE_ERROR              =     255     //异常状态
		} ClientStatusEm;

    
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
			AAC_TYPE_INFO = 128,
			AAC_TYPE_SAMPLE = 129
		} FrameSampleTypeEm;

	//RTMP Metadata 
	typedef struct _RTMPMetaData
        {
                double  duration;
                double  width;
                double  height;
                double  videodatarate;
                double  framerate;
                double  videocodecid;
                double  audiodatarate;
                double  audiosamplerate;
                double  audiosamplesize;
                double  stereo;                         //0 for false
                double  audiocodecid;
        }RTMPMetaData;

#endif  

    // 私有直播消息回调函数
    typedef int (*MessageCallBack)(void* apData, const char* aMessage);
    //RTMP消息回调函数 
    typedef void (*RtmpDataCallBack)(void* apData, char* aDataBuffer, int aDataLength, char aDataType);
    //typedef void (*RtmpDataCallBack)(void* apData, char* aDataBuffer, int aDataLength);
 
 		//注册rtmp音频数据回调
    void SetRtmpDataCallBack(void *apData, RtmpDataCallBack aRtmpCallBack); 
 

    //开始云服务 接收调度命令         ini格式的配置串       开始采集并压缩音视频数据的回调函数
    //return: 0---success ; other --failed 
    int StartCloudService(const char* aAppID, const char* aDeviceSN, const char* aCid, void* apData, MessageCallBack apMessageCallBack);

		//用户自定义配置登录云平台（可使用指定服务器IP地址登录，需指明地址字段：LoginAddress=(IPAddress)）
    //config:[Config]\r\nCID=(aCID)\r\nSN=(aAppIda+DeviceSN)\r\nLoginAddress=(IPAddress)\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nIsSendBroadcast=0\r\nUdpSendInterval=2\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80\r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n
    int  StartCloudService2(const char* aConfigString, void* apData, MessageCallBack apMessageCallBack);
    
    //停止云服务
    void StopCloudService();

    //获取设备状态:版本号version,登录状态login,在线状态online,丢包情况packet lost count
    char* GetDeviceStatus();

    //获取当前云平台版本号(platform version)
    float GetPlatformVersion();
 
    //获取设备的token，每次启动云服务都会获得新的token， token过期需要重新启动云服务
    //return -1 -- failed; token length ----success(56字符)
    int GetDeviceToken(char *apTokenBuffer, unsigned int aBufferLength);
 
    //往该服务塞入音视频采样数据  数据层索引 当前固定为0    音视频采样缓冲区          音视频采样缓冲区长度    32位时间戳单位毫秒  采样类型h264 NALU_TYPE 或者 音频类型
    //int PushData(unsigned long aDataLevelPos, const char *aDataBuffer, unsigned long aBufferLength, unsigned long aTimeStamp, unsigned char apFrameSampleType);
    int PushData(unsigned long aDataLevelPos, const char *aDataBuffer, unsigned long aBufferLength, unsigned long long aTimeStamp, unsigned char apFrameSampleType);
    
    int PushRTMPData(char* aDataBuffer, unsigned long aBufferLength, unsigned long long aTimestamp, unsigned char apFrameSampleType);
    
    //弹出一个音视频采样缓冲区 数据层索引 当前固定为0           采样数据长度              32位时间戳  采 样类型h264 NALU_TYPE 或者 音频类型
    char* PopData(unsigned long aDataLevelPos, unsigned long* apFrameSampleLength, unsigned long* apTimestamp, unsigned char* apFrameSampleType);
    
    //type	int	截图的类型 1: 录像截图，2:封面截图，3:告警截图 
    int PostPicture(char* aDataBuffer, unsigned long aBufferLength, int aTimeStamp, int aImageType, int aTimeOut);

    int PushMessage(const char* aMessage, unsigned long aMessageLength, int aNotifyThirdPlatform);
     
    //连接
    //开启rtmp服务;return: 0 ---success , other --- failed
    // aMode :0是待命 1是udp广播 2是rtmp广播 3是录像 4是录像广播
    int ConnectToServer(char aMode, RTMPMetaData aMetaData);
	
    //断开连接
    //关闭rtmp服务
    int Disconnect();
    
    //上传设备配置参数,256字节的平台配置串
    int SetDeviceConfig(const char* aConfig, unsigned int aConfigLength);

    //上传设备自定义额外数据信息（摄像头的属性等），数据对平台透明，平台只是进行保存。
    int SetDeviceInfo(const char* aDataInfo, unsigned int aDataLength);	

		//获取录像报警播放信息
    int QueryAlarmPlayInfo();
 
    void SendLogMessage(const char* aMessage);
    int  ConvertCidToHashID(unsigned long aSrcCid, char* apHashID, int HashIdLength);
 
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* End of #ifndef __CAMERA_API_H__ */
