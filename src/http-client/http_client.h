#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

int init_ssl();
int http_post_image(char*ip,int port,char ssl_flag,char *token,char* hash_id, int timestamp,int image_type,char* image_buffer, long image_size);

int http_post_jsonData(char*ip,int port,char ssl_flag,char *token, char *post_url, char *msg_buffer, long msg_size);


#endif
