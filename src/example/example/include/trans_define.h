#ifndef __TRANS_DEFINE_H__
#define __TRANS_DEFINE_H__
#define TRANS_MAX_DATA_LEN (1024)

/*
����͸���ӿڶ���
*/
//������
enum {
	UNKNOWN=0,
	GET_IMAGE_PARA_ADV_EXT,	//��ȡͼ��߼�����
	SET_IMAGE_PARA_ADV_EXT,	//����ͼ��߼�����
	RESTORE_IMAGE_PARA_ADV_EXT_DEFAULT,	//�ָ�ͼ��߼�����Ĭ��ֵ
	GET_VIM_SERVER_PARA,//��ȡ���ڷ���������
	SET_VIM_SERVER_PARA,//���ÿ��ڷ���������
	CAPTURE_PICTURE,	//ץ��
	GET_IVA_FACE_PARA,//��ȡ����ʶ�����
	SET_IVA_FACE_PARA,//��������ʶ�����
	GET_IMAGE_DEFAULT_PARA_ADV_EXT,//��ȡͼ��߼�����Ĭ��ֵ
	GET_ONVIF_AUTHENTICATION, //��ȡONVIF�û���֤����
	SET_ONVIF_AUTHENTICATION, //����ONVIF�û���֤����
	GET_DEFOG_PARA,//��ȡ͸�����
	SET_DEFOG_PARA, //����͸�����
	GET_CAPTURE_PARA, //��ȡǰ��ץ�Ĳ���
	SET_CATPURE_PARA, //����ǰ��ץ�Ĳ���
	GET_RECORD_PARA,        /**<  ��ȡ¼������ */
	SET_RECORD_PARA,        /**<  ����¼������ */
	GET_SCHEDULE_PARA,		/**<  ��ȡ�ƻ�¼����� */
	SET_SCHEDULE_PARA,		/**<  ���üƻ�¼����� */
};

///͸���������ݽṹ��
typedef struct _trans_data  
{
	int cmd;
	int datalen;
	char data[TRANS_MAX_DATA_LEN];
} TRANS_DATA;

//typedef struct
//{
//	int 	gain_mode,	gain_max; 		//< �ٷֱ�
//	int 	backlighting_mode, backlighting_strength; //< �ٷֱ�
//	int 	iris_mode, iris_min, iris_max;  //< �ٷֱ�
//
//
//	int 	exposure_mode, exposure_min, exposure_max, exposure_step; //< ��΢��Ϊ��λ
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
	/// IMAGE ͼ����� 
	int sharp; //< ���

	/// VIDEO ��Ƶ���� 
	int mirror; //< ���� 
	int rotate; //< ��ת 
	int frequency; //< ��Ƶ��ʽ

	/// AE �Զ��ع�
	int ae_mode; //< �ع�ģʽ
	int framerate_sensor; //< �ɼ�֡��
	int framerate_min_gain;//<��֡ת��
	int framerate_min; //< ��С֡��
	int target_brightness; //< Ŀ������
	int target_thrld; //< Ŀ��ƫ�� �ٷֱ�
	int exposure_fix; //< �ع�ʱ��
	int exposure_min, exposure_max, exposure_step; //< ��С�ع� ����ع� �عⲽ��
	int gain_min; //< ��С������
	int gain_max; //< ������档�ٷֱ�
	int exroi_mode; //< ��Ȥģʽ
	int backlighting_strength; //< ǿ������ �ٷֱ� 0Ϊ�Զ��� 
	int exroi_blocks; //< ��Ȥ�ܿ��� 9/16
	int exroi_buf[16]; //< ��Ȥ���� ��0��ʼ 0~F
	int wdr_strength; //< ��̬

	///////////////////////////////////////////////////////
	///��Ȧ���ƾ����趨(��Ȧ��Χ)
	int light_added; //< ��������
	int light_added_gain; //< ����ת��
	int iris_type; //< ��Ȧ���� ���� �ͺ�
	int iris_mode; //< ��Ȧģʽ 0/�Զ�ģʽ 1/�ֹ�ģʽ
	int iris_min, iris_max;  //< ��Ȧ��С ��Ȧ���
	int iris_step; //< �Զ���Ȧ������
	int light_added_step; //< ��ҹģʽת��������
	int light_bright; //< ���ƹ�����
	int day_night_mode; //< ��ҹģʽ
	int filter_second; //< ��ҹģʽת��ʱ��	

	//////////////////////////////////////////////////////////////////
	/// ͼ����������Ե��ǿ���� 
	int noise_mode; //< ����ģʽ
	int ee_strength;  //< ��Եǿ�� 
	int noise_tnf_size ; //< �����˶� ʱ��
	int noise_tnf_strength; //< ʱ��ǿ�� ʱ��:
	int noise_snf_size; //< ������С ����
	int noise_snf_strength; //< ����ǿ�� ���� 
	int noise_reserved[16]; 
}NVD_IMAGE_PARA_ADV_EXT;
//���ڷ���������
typedef struct vim
{
	int use;//�Ƿ�����
	char VIMIp[16];
	int VIMPort;
	char channelID[32];
}VIMCfgInfo;

//ONVIF�û���֤
typedef struct 
{
	int authenticate; //0�ر���֤��1������֤

}ONVIF_AUTHENTICATION;

//����ʶ��͸������
typedef struct
{
	int total; //��������
}NVD_IVA_FACE_EXT;

#ifdef _WIN32
/*
* ץ��ͼƬ�ϴ�����ṹ
*/
typedef struct
{
	char				tTime[20];              /* ץ��ʱ��*/
	int					streamId;				/* 0��ʾ����������ʾ������*/
	unsigned long       ulLoginHandle;          /* ץ��Դ��Ϣ*/
	NVD_IVA_JPEG        pPicture;               /* ץ��ͼƬ����*/
}NVD_IVA_CAPTURE_RESULT;


//����͸������
typedef struct
{
	int 				isUsed;         		/**<  �Ƿ����� */
	int 				nDarkParam;       		/**<  ȥ��ǿ��0-255 */
	NVD_AREA_RECT     	roi[8];  				/**<  ����Ȥ���� (δʹ��) */

	char res[64];
}NP_IVA_DEFOG_PARA;

//ǰ��ץ��
typedef struct
{
	///��ʱ
	int		tEnable; //�Ƿ���
	int		tPeroid; //��ʱ������룩

	///����
	//��������λ�ڱ����¼���������

	///SD��
	int		sdSave; //�Ƿ񱣴浽SD��
	int		sdSpaceLimit; //���ʹ�ÿռ����ƣ�M��
	int		sdClearData; //��ռ�ÿռ�ﵽ����֮���Ƿ�ɾ�����ݣ�ɾ�������һСʱ����

	///FTP
	int		ftpEnable; //�Ƿ���FTP�ϴ�
	char	ftpIP[64]; //FTP������IP��ַ
	int		ftpPort; //FTP����˿�
	char	ftpUser[64]; //FTP��¼�û�
	char	ftpPass[64]; //FTP��¼����
	char	ftpPath[256]; //FTP�ϴ�·�������ջ���'/'��ʾFTP��Ŀ¼
	int		ftpMode; //FTPģʽ��0��ʾ����ģʽ��PORT����1��ʾ����ģʽ��PASV��
	int		jpegQuality;//ͼƬ����

}NVD_CAPTURE_PARA;
#endif //if _WIN32

typedef struct tagNVD_RECORD_PARA
{
    int     enableRecord;          /**<  �Ƿ�����¼�� */
    long    lChannel;              /**<  ¼��ͨ�� */
    int     enableLoopRecord;      /**<  ѭ������¼�� */
    int     enablePreRecord;       /**<  �Ƿ�Ԥ¼ */
    unsigned int   dwPreRecordTime;/**<  Ԥ¼ʱ��(ms) */
    unsigned int   dwDelayTime;    /**<  ¼����ʱʱ��(ms),��ͨ����¼��ʹ�� */
    unsigned int   dwPackTime;     /**<  ���ʱ��(ms),�ƻ�¼��ʹ�� */
    unsigned int   dwPercentageOfRecordSize;    /**< ¼��ռ�ÿռ�ٷֱ� */
}NVD_RECORD_PARA,*LPNVD_RECORD_PARA;

typedef struct tagNVD_SCHEDULE_PARA
{
    NVD_TIME_RECT       schedules[NVD_WARD_MAX_DAY][NVD_WARD_TIME_NUM_PEER];       /**<  �ƻ�¼��ʱ��� */
}NVD_SCHEDULE_PARA,*LPNVD_SCHEDULE_PARA;

#endif