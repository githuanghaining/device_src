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
*    ����ʶ��������
*/
typedef enum
{
    NVD_IVA_RESULT_LPR = 0,     /**<  ����ʶ���� */
    NVD_IVA_RESULT_FR,          /**<  ����ץ�Ľ�� */
    NVD_IVA_RESULT_CAPTURE,     /* ץ�Ľ��*/
    NVD_IVA_RESULT_FTPICS,      /**<  ����Сͼ��� */
    NVD_IVA_RESULT_ILL          /**<  δ���� */
}NVD_IVA_RESULT_TYPE;

/**
*    ����ʶ������ɫ
*/
typedef enum
{
    NVD_IVA_LC_UNKNOWN = 0,     /**<  δ֪ */
    NVD_IVA_LC_BLUE,            /**<  ��ɫ */
    NVD_IVA_LC_YELLOW,          /**<  ��ɫ */
    NVD_IVA_LC_WHITE,           /**<  ��ɫ */
    NVD_IVA_LC_BLACK,           /**<  ��ɫ */
    NVD_IVA_LC_GREEN,           /**<  ��ɫ */

    NVD_IVA_LC_ILL
}NVD_IVA_LC_COLOR;

/**
*    ����ʶ��������
*/
typedef enum
{
    NVD_IVA_LT_UNKNOWN = 0,         /**<  δ֪ */
    NVD_IVA_LT_BLUE,                /**<  ����С���� */
    NVD_IVA_LT_BLACK,               /**<  ����С���� */
    NVD_IVA_LT_YELLOW,              /**<  ���Ż��� */
    NVD_IVA_LT_YELLOW2,             /**<  ˫�Ż��ƣ���β�ƣ�ũ�ó��� */
    NVD_IVA_LT_POLICE,              /**<  �������� */
    NVD_IVA_LT_ARMPOL,              /**<  �侯���� */
    NVD_IVA_LT_INDIVI,              /**<  ���Ի����� */
    NVD_IVA_LT_ARMY,                /**<  ���ž��� */
    NVD_IVA_LT_ARMY2,               /**<  ˫�ž��� */
    NVD_IVA_LT_EMBASSY,             /**<  ʹ���� */
    NVD_IVA_LT_HONGKONG,            /**<  ����� */

    NVD_IVA_LT_ILL
}NVD_IVA_LT_TYPE;

/**
*    ����ʶ������ɫ
*/
typedef enum{
    NVD_IVA_BC_WHITE = 0,           /**<  ��ɫ */
    NVD_IVA_BC_SILVER,              /**<  ��ɫ(��ɫ) */
    NVD_IVA_BC_YELLOW,              /**<  ��ɫ */
    NVD_IVA_BC_PINK,                /**<  ��ɫ */
    NVD_IVA_BC_RED,                 /**<  ��ɫ */
    NVD_IVA_BC_GREEN,               /**<  ��ɫ */
    NVD_IVA_BC_BLUE,                /**<  ��ɫ */
    NVD_IVA_BC_BROWN,               /**<  ��ɫ */
    NVD_IVA_BC_BLACK,               /**<  ��ɫ */

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
//	int                 isUsed;                /**<  �Ƿ����� */
//
//	unsigned short      xPos;
//	unsigned short      yPos;
//
//	unsigned short      width;                 /**<  ���ڿ�� */
//	unsigned short      height;                /**<  ���ڸ߶� */
//}NVD_AREA_RECT;

/**
*���ܽ����Ӧ��JPEGͼƬ����
*/
typedef struct
{
	unsigned short      width;                 	/**<  ͼƬ��� */
	unsigned short      height;                	/**<  ͼƬ�߶� */
	unsigned int		picLen;					/**<  ͼƬ���ݳ��� */
	unsigned char*		pPicture;				/**<  ͼƬ���� */
}NVD_IVA_JPEG;

/**
*����Сͼ����
*/
typedef struct
{
    unsigned short      width;                 	/**<  ͼƬ��� */
    unsigned short      height;                	/**<  ͼƬ�߶� */
    unsigned int        picLen;					/**<  ͼƬ���ݳ��� */
    unsigned int        offset;                 /**<  ƫ���� */
}NVD_IVA_PIC;

/**
*������Ƶ��������ʶ�����û����ṹ
*/
typedef struct
{
	int         isUsed;         /**<  �Ƿ����ó���ʶ�� */
	NVD_AREA_RECT rect[8];  /**<  ʶ���������8�� */
	int nMinPlateWidth;         /**<  ������С���ƿ�ȣ�������Ϊ��λ */
	int nMaxPlateWidth;         /**<  ��������ƿ�ȣ�������Ϊ��λ */
	int isOutputSingleFrame;    /**<  �Ƿ���Ƶͼ����ͬһ�����Ķ��ͼ��ֻ���һ�ν�� */
	int isTwoRowYellow;         /**<  �Ƿ�����ʶ��˫�ŻƳ��� */
	int nMergeFrames;         /**<  �ں�֡�� */
	char szProvince[4];         /**<  Ĭ��ʡ�� */

	int enableLogo;             /**<  �Ƿ����ó���ʶ�� */
	int enableWindow;           /**<  �Ƿ����ó�ǰ��ʶ�� */

	char res[248];
}NVD_IVA_LPR_PARA;

/**
*������Ƶ��������ʶ���������ṹ
*/
typedef struct
{
	char license[16];           /**<  ���ƺ��� */
	char color[8];              /**<  ������ɫ */
	NVD_IVA_LC_COLOR nColor;    /**<  ������ɫ */
	NVD_IVA_LT_TYPE nType;      /**<  �������� */
	int nConfidence;            /**<  ���ƿ��Ŷ� */
	int nBright;                /**<  �������� */
	int nDirection;             /**<  �����˶�����unknown, 1 left, 2 right, 3 up , 4 down */
	NVD_RECT    rect;           /**<  ����λ�� */
	NVD_IVA_BC_COLOR bodyColor; /**<  ������ɫ */
	int bodyBright;             /**<  ���������� */
	int secondColor;            /**<  �ڶ�������ɫ */
	float firstRate;            /**<  ��һ��ɫ���� */
	float secondRate;           /**<  �ڶ���ɫ���� */

	NVD_RECT lcLogo;            /**<  ����λ��  */
	NVD_RECT lcWindow;          /**<  ��ǰ��λ�� */
	char charScore[16];         /**<  ����  */
	int charNum;                /**<  ����  */
}NVD_IVA_LPR_RESULT;

#define NVD_IVA_LPR_RESULT_NUM_MAX    20
typedef struct
{
	char				tTime[20];				/**<  ����ʱ�䣬��ʽ��YYYYMMDD HHMMSS.000 �����������λ�Ǻ��� */
	int 				nNumResult;             /**<  ���������Ĭ��10 */
	NVD_IVA_LPR_RESULT 	pPlateResult[NVD_IVA_LPR_RESULT_NUM_MAX];    /**<  ����ʶ���� */
	NVD_IVA_JPEG		pPicture;		/**<  �����Ӧ��JPEGͼƬ���� */
}NVD_IVA_LPR_RESULTS;


/**
*������Ƶ��������ץ�����û����ṹ
*/

typedef struct
{
	int isUsed;         /**<  �Ƿ����� */
	int nMinFace;       /**<  ץ����С����ȣ�Ĭ��60 */
	int nMaxFace;       /**<  ץ���������ȣ�Ĭ��400 */
	NVD_AREA_RECT roi[8];  /**<  ץ���������8�� */

	char res[64];
}NVD_IVA_FR_PARA;


/**
*������Ƶ��������ץ�Ľ�������ṹ
*/
typedef struct
{
	NVD_RECT location;      /**<  ����λ�� */
	int confidence;         /**<  ���Ŷ� */
    int                 trackID;                /**<  ����ID  */
    int                 flag;                   /**<  �Ƿ��״γ���  */
                                                /**< 1 ��ʾ������Ϊ��һ�γ��֣���Ҫ��ҳ��ͼ��ѡ��ʾ����  */
                                                /**< 0 ��ʾ������Ϊ���ٵ�����������Сͼ����ʾ  */
    char                res[16];                /**< Ԥ��*/
}NVD_IVA_FR_RESULT;

#define NVD_IVA_FR_RESULT_NUM_MAX    30
typedef struct
{
	char				tTime[20];				/**<  ����ʱ�䣬��ʽ��YYYYMMDD HHMMSS.000 �����������λ�Ǻ��� */
	int nNumResult;         /**<  ���������Ĭ��30 */
	NVD_IVA_FR_RESULT pFaceResult[NVD_IVA_FR_RESULT_NUM_MAX];   /**<  ����ץ�Ľ�� */
	NVD_IVA_JPEG		pPicture;		/**<  �����Ӧ��JPEGͼƬ���� */
}NVD_IVA_FR_RESULTS;

typedef struct
{
	char				tTime[20];				/**<  ����ʱ�䣬��ʽ��YYYYMMDD HHMMSS.000 �����������λ�Ǻ��� */
    int					nNumResult;         	/**<  ���������Ĭ��30 */
    int                 nFormat;                /**<  ͼƬ��ʽNVD_IVA_RESULT_PIC_FORMAT */
    NVD_IVA_FR_RESULT	pFaceResult[NVD_IVA_FR_RESULT_NUM_MAX];   /**<  ����ʶ���� */
    NVD_IVA_PIC 		pPictures[NVD_IVA_FR_RESULT_NUM_MAX];     /**<  ͼƬ��� */
}NVD_IVA_FTPIC_RESULTS;


/**
*���ܽ���ϱ��ṹ��
*/
typedef struct
{
	char				deviceInfo[256];		/**<  �����豸��Ϣ����XML����������
												//�豸�汾��Ϣ���汾��
												//�豸�������������������IP��MAC��ַ
												//�豸��ŵ������������豸���̱�š��豸���к�
												<device>
													<ver>1.0.5</ver>
													<ip>192.168.1.100</ip>
													<mac>FF:FF:FF:FF:FF:FF</mac>
													<vendor>netposa</vendor>
													<license>301412000057</license>
												</device>
												*/
	int					ivaType;				/**<  �����������ͣ���Ӧ��NVD_IVA_RESULT_TYPE������ */
	unsigned int		ivaLen;					/**<  �������ݳ��� */
	unsigned char*		ivaData;				/**<  �����������ݣ���Ӧһ��NVD_IVA_LPR_RESULTS����NVD_IVA_FR_RESULTS��NVD_IVA_FTPIC_RESULTS */
}NVD_IVA_REPORT;

#endif

