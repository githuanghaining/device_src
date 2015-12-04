////////////////////////////////////////////////////////////////////////// 
///  Copyright (C) 2014
///
/// @file NVDIVA.h
/// @brief   
/// @version   
/// @author  
/// @date  2014-05-08
////////////////////////////////////////////////////////////////////////// 

#ifndef __NVD_IVA_H__
#define __NVD_IVA_H__


typedef enum
{
    NVD_IVA_RESULT_YUV420SP = 0,
    NVD_IVA_RESULT_YUV420P,
    NVD_IVA_RESULT_YUV422SP,
    NVD_IVA_RESULT_YUV422P,
    NVD_IVA_RESULT_JPEG,
    NVD_IVA_RESULT_RGB,
    NVD_IVA_RESULT_RAW,
    NVD_IVA_RESULT_PIC_ILL
}NVD_IVA_RESULT_PIC_FORMAT;

/**
*    智能识别结果类型
*/
typedef enum
{
    NVD_IVA_RESULT_LPR = 0,     /**<  车牌识别结果 */
    NVD_IVA_RESULT_FR,          /**<  人脸抓拍结果 */
    NVD_IVA_RESULT_CAPTURE,     /* 抓拍结果*/
    NVD_IVA_RESULT_FTPICS,      /**<  人脸小图结果 */
    NVD_IVA_RESULT_ILL          /**<  未定义 */
}NVD_IVA_RESULT_TYPE;

/**
*    智能识别车牌颜色
*/
typedef enum
{
    NVD_IVA_LC_UNKNOWN = 0,     /**<  未知 */
    NVD_IVA_LC_BLUE,            /**<  蓝色 */
    NVD_IVA_LC_YELLOW,          /**<  黄色 */
    NVD_IVA_LC_WHITE,           /**<  白色 */
    NVD_IVA_LC_BLACK,           /**<  黑色 */
    NVD_IVA_LC_GREEN,           /**<  绿色 */

    NVD_IVA_LC_ILL
}NVD_IVA_LC_COLOR;

/**
*    智能识别车牌类型
*/
typedef enum
{
    NVD_IVA_LT_UNKNOWN = 0,         /**<  未知 */
    NVD_IVA_LT_BLUE,                /**<  蓝牌小汽车 */
    NVD_IVA_LT_BLACK,               /**<  黑牌小汽车 */
    NVD_IVA_LT_YELLOW,              /**<  单排黄牌 */
    NVD_IVA_LT_YELLOW2,             /**<  双排黄牌（大车尾牌，农用车） */
    NVD_IVA_LT_POLICE,              /**<  警车车牌 */
    NVD_IVA_LT_ARMPOL,              /**<  武警车牌 */
    NVD_IVA_LT_INDIVI,              /**<  个性化车牌 */
    NVD_IVA_LT_ARMY,                /**<  单排军车 */
    NVD_IVA_LT_ARMY2,               /**<  双排军车 */
    NVD_IVA_LT_EMBASSY,             /**<  使馆牌 */
    NVD_IVA_LT_HONGKONG,            /**<  香港牌 */

    NVD_IVA_LT_ILL
}NVD_IVA_LT_TYPE;

/**
*    智能识别车身颜色
*/
typedef enum{
    NVD_IVA_BC_WHITE = 0,           /**<  白色 */
    NVD_IVA_BC_SILVER,              /**<  蓝色(银色) */
    NVD_IVA_BC_YELLOW,              /**<  黄色 */
    NVD_IVA_BC_PINK,                /**<  粉色 */
    NVD_IVA_BC_RED,                 /**<  红色 */
    NVD_IVA_BC_GREEN,               /**<  绿色 */
    NVD_IVA_BC_BLUE,                /**<  蓝色 */
    NVD_IVA_BC_BROWN,               /**<  棕色 */
    NVD_IVA_BC_BLACK,               /**<  黑色 */

    NVD_IVA_BC_ILL
}NVD_IVA_BC_COLOR;


//typedef struct
//{
//	unsigned short      left;
//	unsigned short      right;
//	unsigned short      top;
//	unsigned short      bottom;
//}NVD_RECT;
//
//typedef struct
//{
//	int                 isUsed;                /**<  是否启用 */
//
//	unsigned short      xPos;
//	unsigned short      yPos;
//
//	unsigned short      width;                 /**<  窗口宽度 */
//	unsigned short      height;                /**<  窗口高度 */
//}NVD_AREA_RECT;

/**
*智能结果对应的JPEG图片数据
*/
typedef struct
{
	unsigned short      width;                 	/**<  图片宽度 */
	unsigned short      height;                	/**<  图片高度 */
	unsigned int		picLen;					/**<  图片数据长度 */
	unsigned char*		pPicture;				/**<  图片数据 */
}NVD_IVA_JPEG;

/**
*智能小图数据
*/
typedef struct
{
    unsigned short      width;                 	/**<  图片宽度 */
    unsigned short      height;                	/**<  图片高度 */
    unsigned int        picLen;					/**<  图片数据长度 */
    unsigned int        offset;                 /**<  偏移量 */
}NVD_IVA_PIC;

/**
*智能视频分析车牌识别配置基本结构
*/
typedef struct
{
	int         isUsed;         /**<  是否启用车牌识别 */
	NVD_AREA_RECT rect[8];  /**<  识别区域，最大8个 */
	int nMinPlateWidth;         /**<  检测的最小车牌宽度，以像素为单位 */
	int nMaxPlateWidth;         /**<  检测的最大车牌宽度，以像素为单位 */
	int isOutputSingleFrame;    /**<  是否视频图像中同一个车的多幅图像只输出一次结果 */
	int isTwoRowYellow;         /**<  是否允许识别双排黄车牌 */
	int nMergeFrames;         /**<  融合帧数 */
	char szProvince[4];         /**<  默认省名 */

	int enableLogo;             /**<  是否启用车标识别 */
	int enableWindow;           /**<  是否启用车前窗识别 */

	char res[248];
}NVD_IVA_LPR_PARA;

/**
*智能视频分析车牌识别结果基本结构
*/
typedef struct
{
	char license[16];           /**<  车牌号码 */
	char color[8];              /**<  车牌颜色 */
	NVD_IVA_LC_COLOR nColor;    /**<  车牌颜色 */
	NVD_IVA_LT_TYPE nType;      /**<  车牌类型 */
	int nConfidence;            /**<  整牌可信度 */
	int nBright;                /**<  亮度评价 */
	int nDirection;             /**<  车牌运动方向，unknown, 1 left, 2 right, 3 up , 4 down */
	NVD_RECT    rect;           /**<  车牌位置 */
	NVD_IVA_BC_COLOR bodyColor; /**<  车身颜色 */
	int bodyBright;             /**<  车身明暗度 */
	int secondColor;            /**<  第二车身颜色 */
	float firstRate;            /**<  第一颜色比例 */
	float secondRate;           /**<  第二颜色比例 */

	NVD_RECT lcLogo;            /**<  车标位置  */
	NVD_RECT lcWindow;          /**<  车前窗位置 */
	char charScore[16];         /**<  忽略  */
	int charNum;                /**<  忽略  */
}NVD_IVA_LPR_RESULT;

#define NVD_IVA_LPR_RESULT_NUM_MAX    20
typedef struct
{
	char				tTime[20];				/**<  发生时间，格式：YYYYMMDD HHMMSS.000 其中最后面三位是毫秒 */
	int 				nNumResult;             /**<  结果个数，默认10 */
	NVD_IVA_LPR_RESULT 	pPlateResult[NVD_IVA_LPR_RESULT_NUM_MAX];    /**<  车牌识别结果 */
	NVD_IVA_JPEG		pPicture;		/**<  结果对应的JPEG图片数据 */
}NVD_IVA_LPR_RESULTS;


/**
*智能视频分析人脸抓拍配置基本结构
*/

typedef struct
{
	int isUsed;         /**<  是否启用 */
	int nMinFace;       /**<  抓拍最小脸宽度，默认60 */
	int nMaxFace;       /**<  抓拍最大脸宽度，默认400 */
	NVD_AREA_RECT roi[8];  /**<  抓拍区域，最大8个 */

	char res[64];
}NVD_IVA_FR_PARA;


/**
*智能视频分析人脸抓拍结果基本结构
*/
typedef struct
{
	NVD_RECT location;      /**<  人脸位置 */
	int confidence;         /**<  可信度 */
    int                 trackID;                /**<  跟踪ID  */
    int                 flag;                   /**<  是否首次出现  */
                                                /**< 1 表示此人脸为第一次出现，需要网页大图框选显示出来  */
                                                /**< 0 表示此人脸为跟踪的人脸，用于小图的显示  */
    char                res[16];                /**< 预留*/
}NVD_IVA_FR_RESULT;

#define NVD_IVA_FR_RESULT_NUM_MAX    30
typedef struct
{
	char				tTime[20];				/**<  发生时间，格式：YYYYMMDD HHMMSS.000 其中最后面三位是毫秒 */
	int nNumResult;         /**<  结果个数，默认30 */
	NVD_IVA_FR_RESULT pFaceResult[NVD_IVA_FR_RESULT_NUM_MAX];   /**<  人脸抓拍结果 */
	NVD_IVA_JPEG		pPicture;		/**<  结果对应的JPEG图片数据 */
}NVD_IVA_FR_RESULTS;

typedef struct
{
	char				tTime[20];				/**<  发生时间，格式：YYYYMMDD HHMMSS.000 其中最后面三位是毫秒 */
    int					nNumResult;         	/**<  结果个数，默认30 */
    int                 nFormat;                /**<  图片格式NVD_IVA_RESULT_PIC_FORMAT */
    NVD_IVA_FR_RESULT	pFaceResult[NVD_IVA_FR_RESULT_NUM_MAX];   /**<  人脸识别结果 */
    NVD_IVA_PIC 		pPictures[NVD_IVA_FR_RESULT_NUM_MAX];     /**<  图片结果 */
}NVD_IVA_FTPIC_RESULTS;


/**
*智能结果上报结构体
*/
typedef struct
{
	char				deviceInfo[256];		/**<  智能设备信息，用XML描述，例如
												//设备版本信息：版本号
												//设备网络参数的描述，包括IP、MAC地址
												//设备编号的描述，包括设备厂商编号、设备序列号
												<device>
													<ver>1.0.5</ver>
													<ip>192.168.1.100</ip>
													<mac>FF:FF:FF:FF:FF:FF</mac>
													<vendor>netposa</vendor>
													<license>301412000057</license>
												</device>
												*/
	int					ivaType;				/**<  智能数据类型，对应于NVD_IVA_RESULT_TYPE的描述 */
	unsigned int		ivaLen;					/**<  智能数据长度 */
	unsigned char*		ivaData;				/**<  智能数据内容，对应一个NVD_IVA_LPR_RESULTS或者NVD_IVA_FR_RESULTS、NVD_IVA_FTPIC_RESULTS */
}NVD_IVA_REPORT;

#endif

