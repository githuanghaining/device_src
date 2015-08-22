#ifndef __TRANS_DEFINE_H__
#define __TRANS_DEFINE_H__
#define TRANS_MAX_DATA_LEN (1024)

/*
网络透传接口定义
*/
//命令字
enum {
	UNKNOWN=0,
	GET_IMAGE_PARA_ADV_EXT,	//获取图像高级参数
	SET_IMAGE_PARA_ADV_EXT,	//设置图像高级参数
	RESTORE_IMAGE_PARA_ADV_EXT_DEFAULT,	//恢复图像高级参数默认值
	GET_VIM_SERVER_PARA,//获取卡口服务器配置
	SET_VIM_SERVER_PARA,//设置卡口服务器配置
	CAPTURE_PICTURE,	//抓拍
	GET_IVA_FACE_PARA,//获取人脸识别参数
	SET_IVA_FACE_PARA,//设置人脸识别参数
	GET_IMAGE_DEFAULT_PARA_ADV_EXT,//获取图像高级参数默认值
	GET_ONVIF_AUTHENTICATION, //获取ONVIF用户验证配置
	SET_ONVIF_AUTHENTICATION, //设置ONVIF用户验证配置
	GET_DEFOG_PARA,//获取透雾参数
	SET_DEFOG_PARA, //设置透雾参数
	GET_CAPTURE_PARA, //获取前端抓拍参数
	SET_CATPURE_PARA, //设置前端抓拍参数
	GET_RECORD_PARA,        /**<  获取录像配置 */
	SET_RECORD_PARA,        /**<  设置录像配置 */
	GET_SCHEDULE_PARA,		/**<  获取计划录像参数 */
	SET_SCHEDULE_PARA,		/**<  设置计划录像参数 */
};

///透明传输数据结构体
typedef struct _trans_data  
{
	int cmd;
	int datalen;
	char data[TRANS_MAX_DATA_LEN];
} TRANS_DATA;

//typedef struct
//{
//	int 	gain_mode,	gain_max; 		//< 百分比
//	int 	backlighting_mode, backlighting_strength; //< 百分比
//	int 	iris_mode, iris_min, iris_max;  //< 百分比
//
//
//	int 	exposure_mode, exposure_min, exposure_max, exposure_step; //< 以微秒为单位
//	int 	sharpe_mode, sharpe_strength, sharpe_gains, sharpe_algs;
//	int 	noise_mode, noise_strength, noise_gains,noise_algs;
//	int 	exroi_mode, exroi_blocks;
//
//	char	sharpe_buf[16];
//	char 	noise_buf[16];
//	char 	exroi_buf[16];
//}NVD_IMAGE_PARA_ADV_EXT;

typedef struct {
	///////////////////////////////////////////////////////////
	/// IMAGE 图像调节 
	int sharp; //< 锐度

	/// VIDEO 视频调整 
	int mirror; //< 镜像 
	int rotate; //< 旋转 
	int frequency; //< 视频制式

	/// AE 自动曝光
	int ae_mode; //< 曝光模式
	int framerate_sensor; //< 采集帧率
	int framerate_min_gain;//<降帧转化
	int framerate_min; //< 最小帧率
	int target_brightness; //< 目标亮度
	int target_thrld; //< 目标偏移 百分比
	int exposure_fix; //< 曝光时间
	int exposure_min, exposure_max, exposure_step; //< 最小曝光 最大曝光 曝光步长
	int gain_min; //< 最小过增益
	int gain_max; //< 最大增益。百分比
	int exroi_mode; //< 兴趣模式
	int backlighting_strength; //< 强光抑制 百分比 0为自动。 
	int exroi_blocks; //< 兴趣总块数 9/16
	int exroi_buf[16]; //< 兴趣块数 从0开始 0~F
	int wdr_strength; //< 宽动态

	///////////////////////////////////////////////////////
	///光圈控制景深设定(光圈范围)
	int light_added; //< 补光类型
	int light_added_gain; //< 补光转换
	int iris_type; //< 光圈类型 厂家 型号
	int iris_mode; //< 光圈模式 0/自动模式 1/手工模式
	int iris_min, iris_max;  //< 光圈最小 光圈最大
	int iris_step; //< 自动光圈灵敏度
	int light_added_step; //< 日夜模式转换灵敏度
	int light_bright; //< 补灯光亮度
	int day_night_mode; //< 日夜模式
	int filter_second; //< 日夜模式转换时间	

	//////////////////////////////////////////////////////////////////
	/// 图像噪声及边缘增强部分 
	int noise_mode; //< 噪声模式
	int ee_strength;  //< 边缘强度 
	int noise_tnf_size ; //< 噪声运动 时域
	int noise_tnf_strength; //< 时域强度 时域:
	int noise_snf_size; //< 噪声大小 空域
	int noise_snf_strength; //< 空域强度 空域 
	int noise_reserved[16]; 
}NVD_IMAGE_PARA_ADV_EXT;
//卡口服务器参数
typedef struct vim
{
	int use;//是否启用
	char VIMIp[16];
	int VIMPort;
	char channelID[32];
}VIMCfgInfo;

//ONVIF用户验证
typedef struct 
{
	int authenticate; //0关闭验证，1开启验证

}ONVIF_AUTHENTICATION;

//人脸识别透传参数
typedef struct
{
	int total; //人脸总数
}NVD_IVA_FACE_EXT;

#ifdef _WIN32
/*
* 抓拍图片上传结果结构
*/
typedef struct
{
	char				tTime[20];              /* 抓拍时间*/
	int					streamId;				/* 0表示主码流，表示子码流*/
	unsigned long       ulLoginHandle;          /* 抓拍源信息*/
	NVD_IVA_JPEG        pPicture;               /* 抓拍图片数据*/
}NVD_IVA_CAPTURE_RESULT;


//智能透雾设置
typedef struct
{
	int 				isUsed;         		/**<  是否启用 */
	int 				nDarkParam;       		/**<  去雾强度0-255 */
	NVD_AREA_RECT     	roi[8];  				/**<  感兴趣区域 (未使用) */

	char res[64];
}NP_IVA_DEFOG_PARA;

//前端抓拍
typedef struct
{
	///定时
	int		tEnable; //是否开启
	int		tPeroid; //定时间隔（秒）

	///联动
	//联动配置位于报警事件的配置里

	///SD卡
	int		sdSave; //是否保存到SD卡
	int		sdSpaceLimit; //最大使用空间限制（M）
	int		sdClearData; //当占用空间达到上限之后是否删除数据，删除最早的一小时数据

	///FTP
	int		ftpEnable; //是否开启FTP上传
	char	ftpIP[64]; //FTP服务器IP地址
	int		ftpPort; //FTP命令端口
	char	ftpUser[64]; //FTP登录用户
	char	ftpPass[64]; //FTP登录密码
	char	ftpPath[256]; //FTP上传路径，留空或者'/'表示FTP根目录
	int		ftpMode; //FTP模式，0表示主动模式（PORT），1表示被动模式（PASV）
	int		jpegQuality;//图片质量

}NVD_CAPTURE_PARA;
#endif //if _WIN32

typedef struct tagNVD_RECORD_PARA
{
    int     enableRecord;          /**<  是否启用录像 */
    long    lChannel;              /**<  录像通道 */
    int     enableLoopRecord;      /**<  循环覆盖录像 */
    int     enablePreRecord;       /**<  是否预录 */
    unsigned int   dwPreRecordTime;/**<  预录时间(ms) */
    unsigned int   dwDelayTime;    /**<  录像延时时间(ms),普通报警录像使用 */
    unsigned int   dwPackTime;     /**<  打包时间(ms),计划录像使用 */
    unsigned int   dwPercentageOfRecordSize;    /**< 录像占用空间百分比 */
}NVD_RECORD_PARA,*LPNVD_RECORD_PARA;

typedef struct tagNVD_SCHEDULE_PARA
{
    NVD_TIME_RECT       schedules[NVD_WARD_MAX_DAY][NVD_WARD_TIME_NUM_PEER];       /**<  计划录像时间段 */
}NVD_SCHEDULE_PARA,*LPNVD_SCHEDULE_PARA;

#endif