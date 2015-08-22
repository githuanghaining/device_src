#ifndef __CAMERA_API_H__
#define __CAMERA_API_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif
    
    /*
     
     Todo:
     rs解码有时候会出错
		确认linux下时间精度问题：usleep nanosleep setitimer select
		状态串里面增加推荐延迟和推荐码流参数
		通过弹出包的时间戳计算卡顿情况
		卡顿过后就不要往回找了
		GF256 在系数为0和1时的处理方式需要确认
     */
    
    //对外发送消息的回调函数：
    //当该服务接收到调度服务器的开始推送命令时 会发出消息通知外壳调用PushData函数塞数据 json格式：{"Name":"StartPushData"}
    //当需要停止塞数据时 json格式：{"Name":"StopPushData"}
    //当该服务接收到时 对方发送的媒体数据时，会发出消息通知外壳调用PopData函数收数据 json格式：{"Name":"StartPopData"}
    //当需要需要停止收数据时 json格式：{"Name":"StopPopData"}
#if 1   
 
    //StatusBuffer[CLIENT_STATUS_BUFFER_LENGTH]; //0字节代表nat类型 1字节代表当前工作状态 2字节代表是否需要心跳返回 3字节代表是否需要编码 4字节代表启动模式 0是待命 1是udp广播 2是rtmp广播 3是录像 4是录像广播
		//当前状态
		typedef enum {
			CLIENT_STATUS_CODE_READY              =     1,      //初始状态
			CLIENT_STATUS_CODE_REQUEST_RELAY      =     2,      //正在请求转发
			CLIENT_STATUS_CODE_CONNECTING_LIVE    =     3,      //正在连接中
			CLIENT_STATUS_CODE_LIVEING            =     4,      //正在直播
			CLIENT_STATUS_CODE_STOPING            =     5,      //停止过程中 
			CLIENT_STATUS_CODE_ERROR              =     255     //异常状态
		} ClientStatusEm;

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
			AAC_TYPE_INFO = 128,
			AAC_TYPE_SAMPLE = 129
		} FrameSampleTypeEm;
 
#endif  

    // 私有直播消息回调函数
    typedef int (*D_MessageCallBack)(void *apData, const char *aMessage);
    //RTMP消息回调函数 
    //typedef void (*audio_consume_pt)(char* audio_data,int len);
    //type 1 is audio data,type 2 is disk list
    typedef void (*audio_consume_pt)(int type,char* data,int len);
 
    //开始云服务 接收调度命令         ini格式的配置串       开始采集并压缩音视频数据的回调函数
    int  D_StartCloudService(const char* aSN,const int aCid,void *apData, D_MessageCallBack apMessageCallBack);
    //void  D_StartCloudService(const char* aConfigString,void *apData, D_MessageCallBack apMessageCallBack);
    
    //停止云服务
    void  D_StopCloudService();
    
    //获取以JSON格式给出的各种状态信息 返回的字符串由外面负责释放
    char* D_GetStatus();
    
    //推送消息             摄像头ID 往手机推送时为0       二进制消息缓冲区          缓冲区长度 最大256
    int   D_PushMessage(unsigned long aID, const char *aMessage, unsigned long aMessageLen);
    
    //往该服务塞入音视频采样数据  数据层索引 当前固定为0    音视频采样缓冲区          音视频采样缓冲区长度    32位时间戳单位毫秒  采样类型h264 NALU_TYPE 或者 音频类型
    int   D_PushData(unsigned long aDataLevelPos, const char *aDataBuffer, unsigned long aBufferLength, unsigned long aTimestamp, unsigned char apFrameSampleType);
    
    //弹出一个音视频采样缓冲区 数据层索引 当前固定为0           采样数据长度              32位时间戳  采 样类型h264 NALU_TYPE 或者 音频类型
    char* D_PopData(unsigned long aDataLevelPos, unsigned long *apFrameSampleLength, unsigned long *apTimestamp, unsigned char *apFrameSampleType);
    
    //摄像机注册                摄像机序列号20字节
    int   D_CameraRegist(const char *aSN, unsigned long *apCameraID);
    
    //开启rtmp服务
    int  D_StartRtmpServer(audio_consume_pt RTMPPopDataCallBack);
    
    //关闭rtmp服务
    void  D_StopRtmpServer();

    //连接
    //0是待命 1是udp广播 2是rtmp广播 3是录像 4是录像广播
    //aAreaID --- 录像存储区域的ID，只要是录像就必须设置aAreaID，0--非录像；1--深圳； 2--杭州；3--北京 
//    int D_StartConnectToServer(char aMode);
    int D_StartConnectToServer(char aMode, unsigned char aAreaID);
	
    //断开连接
    int D_Disconnect();
    
    //往rtmp服务塞入音视频采样数据 音视频采样缓冲区       音视频采样缓冲区长度          32位时间戳单位毫秒    采样类型h264 NALU_TYPE 或者 音频类型
    void D_SendRTMPData(char * aDataBuffer,unsigned long aBufferLength, unsigned long aTimestamp,unsigned char apFrameSampleType);
    
    int  D_HttpPostPicture(int timestamp,char* image_buffer, long image_size, int is_recording_flag,unsigned char aAreaID);
    
    //void  D_HttpPostRTMPURL();
    void  D_HttpPostRTMPURL(char aMode, unsigned char aScaleID);
 
    void  D_HttpRemoveRTMPURL();

    int  D_SetRtmpConnectMessage(char *rtmpMessgae,char aMode, unsigned char aAreaID);    
    //void  D_SetRtmpConnectMessage(char *rtmpMessgae);

    //int D_GetDiskList(const char* aUrl,unsigned char* buffer,int* size);
    int D_SendGetDiskList();  
 
    void D_Send_Log(const char *msg);
 
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* End of #ifndef __CAMERA_API_H__ */
