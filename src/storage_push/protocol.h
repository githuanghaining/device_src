//-----------------Command----------------------
#define DISKTRACKER_CMD_REQ_DISK_SERVER         0x0801          //请求磁盘服务器

//-----------------Error------------------------
#define DISKTRACKER_ERROR_NO_ERROR              0               //成功
#define DISKTRACKER_ERROR_FAILED                1               //失败,通常为系统内部错误

#pragma pack(push, 1)
typedef struct tag_msgheader
{
    unsigned short  cmd;                //命令码
    unsigned short  len;                //命令长度,包头+包体
    unsigned int    seq;                //消息流水号,从1开始自增
}msgheader_t, *pmsgheader_t;

typedef struct tag_request_disk
{
    msgheader_t     header;
    unsigned char   count;              //请求disk server个数
    unsigned char   reserved[3];
}request_disk_t, *prequest_disk_t;

typedef struct tag_disk_server_info
{
    unsigned int    ip;
    unsigned short  port;
    unsigned short  reserved;
}disk_server_info_t, *pdisk_server_info_t;

typedef struct tag_request_disk_rsp
{
    msgheader_t         header;
    unsigned char       result;
    unsigned char       count;          //disk server个数
    unsigned char       reserved[2];
    disk_server_info_t  server[0];
}request_disk_rsp_t, *prequest_disk_rsp_t;
#pragma pack(pop)
