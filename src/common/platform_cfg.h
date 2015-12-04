#ifndef _PLATFORM_CFG
#define _PLATFORM_CFG

typedef struct platform_config
{
    char rtmp_url[200];
    char rtmp_log_dir[200];
    char *rtmp_fun[2];
    char rtmp_record_imgAddr[50];
    int rtmp_record_imgPort;
    char web_server_ip[32];
    int web_server_port;
    int web_server_timeout;
    int cid;
    char hashid[20];
}platform_config_t;

#endif
