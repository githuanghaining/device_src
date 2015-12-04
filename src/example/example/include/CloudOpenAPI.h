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
/*******************************************************************************************************
//SKD新接口,该版本兼容新接口和旧接口，新接口和旧接口功能一致只，使用只需要选择其中一个即可;
//官网文档以新的接口为准，往后对外统一以新接口为标准
*******************************************************************************************************/
    //平台消息回调函数
    typedef int (*MessageCallBack)(void* apData, const char* aMessage);
    //RTMP数据回调函数(包含：音频数据和报警录像信息) 
    typedef void (*RtmpDataCallBack)(void* apData, char* aDataBuffer, int aDataLength, char aDataType);
 
 	//注册rtmp数据回调(包含：音频数据和报警录像信息),; aDataType: 1 音频数据; 2:报警录像信息
    void SetRtmpDataCallBack(void *apData, RtmpDataCallBack aRtmpDataCallBack); 
 

    //开始云服务 接收调度命令    平台消息回调函数
    int StartCloudService(const char* aAppID, const char* aDeviceSN, const char* aCid, void* apData, MessageCallBack apMessageCallBack);
    //return: 0---success ; -1 --failed 

	//用户自定义配置登录云平台,ini格式的配置串（可使用指定服务器IP地址登录，需指明地址字段：LoginAddress=(IPAddress),ip地址由羚羊云提供）
	//如:aCid:AFEG7J8D5D2; aAppID: YG7s ; DeviceSN:193886dhk8; IPAddress:220.168.38.182
    //config:[Config]\r\nCID=AFEG7J8D5D2\r\nSN=YG7s193886dhk8\r\nLoginAddress=220.168.38.182\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nIsSendBroadcast=0\r\nUdpSendInterval=2\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80\r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n
    int  StartCloudService2(const char* aConfigString, void* apData, MessageCallBack apMessageCallBack);
    //return: 0---success ; -1 --failed 
    
    //停止云服务
    void StopCloudService();

    //获取设备状态
    //版本号version,登录状态login,在线状态online,丢包情况SendLostCount(每个数据包代表1k数据量)
    char* GetDeviceStatus();

    //获取当前云平台版本号(platform version)
    float GetPlatformVersion();
 
    //获取设备的token，设备token用于客户端或者后台系统访问操作该设备，用于安全校验
    int GetDeviceToken(char *apTokenBuffer, unsigned int aBufferLength);
    //return -1 -- failed; token length ----success(56字符)
 
    //往该服务塞入音视频采样数据  数据层索引 当前固定为0   音视频采样缓冲区  音视频采样缓冲区长度    64位时间戳单位微秒（绝对时间戳）  采样类型h264 NALU_TYPE 或者 音频类型
    int PushData(unsigned long aDataLevelPos, const char *aDataBuffer, unsigned long aBufferLength, unsigned long long aTimeStamp, unsigned char apFrameSampleType);
    //return: 0---success ; other --failed 
    
    //弹出一个音视频采样缓冲区 数据层索引 当前固定为0    采样数据长度   32位时间戳（相对时间戳）  采样类型 h264 NALU_TYPE 或者 音频类型
    char* PopData(unsigned long aDataLevelPos, unsigned long* apFrameSampleLength, unsigned long* apTimestamp, unsigned char* apFrameSampleType);
    //return: DataBuffer ---success ; NULL --failed 
    
    //type	int	截图的类型 1: 录像截图，2:封面截图，3:告警截图; aTimeOut:缺省默认超时10s 
    int PostPicture(char* aDataBuffer, unsigned long aBufferLength, int aTimeStamp, int aImageType, int aTimeOut);
    //return: 0---success ; other --failed 

	//消息透传通道，设备端发送消息到客户端，256字节长度二进制消息体；
	//aNotifyThirdPartyPlatform ：该消息是否通知第三方后台系统（1：通知；0：不通知）
    int PushMessage(const char* aMessage, unsigned long aMessageLength, int aNotifyThirdPartyPlatform);
    //return: 0---success ; -1 --failed 
     
    //连接
    //开启rtmp服务;aMetaData:rtmp元数据信息
    // aMode :0是待命 1是udp广播 2是rtmp广播(公众) 3是录像(云存储) 4是录像广播(公众+云存储)
    int ConnectToServer(char aMode, RTMPMetaData aMetaData);
    //return: 0 ---success , -1 --- failed
	
    //断开连接
    //关闭rtmp服务
    int Disconnect();
    //return: 0---success ; -1 --failed 
    
    //上传设备配置参数,256字节的平台配置串
    int SetDeviceConfig(const char* aConfig, unsigned int aConfigLength);
    //return: 0---success ; -1 --failed 

    //上传设备自定义额外数据信息（摄像头的属性等），数据对平台透明，平台只是进行保存。
    int SetDeviceInfo(const char* aDataInfo, unsigned int aDataLength);	
    //return: 0---success ; -1 --failed 

	//请求录像报警播放信息,录像数据信息将会在rtmp数据回调函数中给出
	//用于客户端播放器实时播放报警录像所需信息
    int QueryAlarmRecordInfo();
    //return: 0---success ; -1 --failed 
	
	//获取上一次操作状态值
	//int GetLastOperationErrorNo();
	int GetLastErrorNo();
 	//return: error no
 	
	//上报日志接口，可适当的上传一些必要的日志信息到云服务器
    void SendLogMessage(const char* aMessage);

	//使用Cid转换出HashID,老设备从旧平台过度到新平台时期使用
    int  ConvertCidToHashID(unsigned long aSrcCid, char* apHashID, int HashIdLength);
    //return: 0---success ; -1 --failed 
 

/***************************************************************************************
 //老接口
****************************************************************************************/

 // 私有直播消息回调函数 
    typedef int (*D_MessageCallBack)(void *apData, const char *aMessage);
    //RTMP消息回调函数 
    typedef void (*D_RtmpAudioCallBack)(void *apData, char* aAudioData,int aDataLen, char aDataType);

        //注册rtmp音频数据回调
    void D_SetRtmpAudioCallBack(void *apData,D_RtmpAudioCallBack aRtmpAudioCall);


    //开始云服务 接收调度命令         ini格式的配置串       开始采集并压缩音视频数据的回调函数
    //return: 0---success ; other --failed 
    int D_StartCloudService(const char*app_id, const char* aSN, const char *aHashID,void *apData, D_MessageCallBack apMessageCallBack);

    //config:[Config]\r\nCID=%lu\r\nSN=%s%s\r\nLoginAddress=%s\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nIsSendBroadcast=0\r\nUdpSendInterval=2\r\n
    int  D_StartCloudService2(const char* aConfigString, void *apData, D_MessageCallBack apMessageCallBack);

    //停止云服务
    void  D_StopCloudService();
    //get device status:version,login,online,packet lost count
    char* D_GetStatus();

    //get platform version
    float D_GetPlatformVersion();

    //获取设备的token，每次启动云服务都会获得新的token， token过期需要重新启动云服务
    //return -1 -- failed; token length ----success(56字符)
    int D_GetDeviceToken(char *aToken, unsigned int sizeOfToken);

    //往该服务塞入音视频采样数据  数据层索引 当前固定为0    音视频采样缓冲区          音视频采样缓冲区长度    32位时间戳单位毫秒  采样类型h264
    int   D_PushData(unsigned long aDataLevelPos, const char *aDataBuffer, unsigned long aBufferLength, unsigned long long aTimestamp, unsigned char apFrameSampleType);

    //弹出一个音视频采样缓冲区 数据层索引 当前固定为0           采样数据长度              32位时间戳  采 样类型h264 NALU_TYPE 或者 音频类型
    char* D_PopData(unsigned long aDataLevelPos, unsigned long *apFrameSampleLength, unsigned long *apTimestamp, unsigned char *apFrameSampleType);

    //type  int 截图的类型 1: 录像截图，2:封面截图，3:告警截图 
    int  D_HttpPostPicture(int timestamp,char* image_buffer, long image_size, int image_type);

    int D_PushMessage(const char *aMessage, unsigned long aMessageLen, int is_callServer);

    //连接
    //开启rtmp服务;return: 0 ---success , other --- failed
    // Mode :0是待命 1是udp广播 2是rtmp广播 3是录像 4是录像广播
    int D_StartConnectToServer(char aMode, RTMPMetaData aMetaData);

    //断开连接
    //关闭rtmp服务
    int D_Disconnect();

    //上传设备配置参数,256字节的平台配置串
    int D_SetDeviceConfig(const char *aConfig, unsigned int aConfigLen);

    //上传设备自定义额外数据信息（摄像头的属性等），数据对平台透明，平台只是进行保存。
    int D_SetDeviceExtraFields(const char *aData, unsigned int aDataLen);

    int D_QueryAlarmRecordInfo();

    void D_Send_Log(const char *msg);
    int  D_GetDevHashID(unsigned long aSrcCid, char *apHashBuffer,int HashIdLength);
 
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* End of #ifndef __CAMERA_API_H__ */
