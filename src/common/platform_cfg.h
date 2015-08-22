#ifndef _PLATFORM_CFG
#define _PLATFORM_CFG

typedef struct platform_config
{
    char rtmp_url[200];
    char rtmp_log_dir[200];
    char web_server_ip[50];
    int web_server_port;
    int web_server_timeout;
    int cid;
}platform_config_t;

#endif
