#include "http_client.h"
#include "tcp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int create_image_request(char* buffer,int timestamp,int image_type,char* image_buffer, long image_size)
{
	int len = 0;
	strcat(buffer,"------WebKitFormBoundary3B1nByE04BkAcEQe\r\n");
	len +=strlen("------WebKitFormBoundary3B1nByE04BkAcEQe\r\n");
	strcat(buffer,"Content-Disposition: form-data; name=\"type\"\r\n\r\n");
	len +=strlen("Content-Disposition: form-data; name=\"type\"\r\n\r\n");
	char tmp[150];
	memset(tmp,0,sizeof(tmp));
	snprintf(tmp,sizeof(tmp)-1,"%d\r\n",image_type);
	strcat(buffer,tmp);
	len +=strlen(tmp);

	strcat(buffer,"------WebKitFormBoundary3B1nByE04BkAcEQe\r\n");
	len +=strlen("------WebKitFormBoundary3B1nByE04BkAcEQe\r\n");
	strcat(buffer,"Content-Disposition: form-data; name=\"timestamp\"\r\n\r\n");
	len +=strlen("Content-Disposition: form-data; name=\"timestamp\"\r\n\r\n");
	
	memset(tmp,0,sizeof(tmp));
	snprintf(tmp,sizeof(tmp)-1,"%d\r\n",timestamp);
	strcat(buffer,tmp);
	len +=strlen(tmp);

	strcat(buffer,"------WebKitFormBoundary3B1nByE04BkAcEQe\r\n");
	len +=strlen("------WebKitFormBoundary3B1nByE04BkAcEQe\r\n");
	strcat(buffer,"Content-Disposition: form-data; name=\"pic\"; filename=\"cover\"\r\n");
	len +=strlen("Content-Disposition: form-data; name=\"pic\"; filename=\"cover\"\r\n");
	strcat(buffer,"Content-Type: application/octet-stream\r\n\r\n");
	len +=strlen("Content-Type: application/octet-stream\r\n\r\n");

	memcpy(buffer+len,image_buffer,image_size);
	len += image_size;

	char* pos = buffer+len;
	strcat(pos,"\r\n------WebKitFormBoundary3B1nByE04BkAcEQe--\r\n");
	len +=strlen("\r\n------WebKitFormBoundary3B1nByE04BkAcEQe--\r\n");
	
	return len;
}

int http_post_image(char*ip,int port,char ssl_flag,char *token,char* hash_id, int timestamp,int image_type,char* image_buffer, long image_size)
{
	//printf("http_post_image ==== ip:%s, port:%d, ssl_flag:%d\n",ip,port,ssl_flag);
	void* ssl_session = NULL;
	int fd = tcp_connect(ip,port);
	if(fd == -1)
		return -1;

	if(ssl_flag)
	{
		ssl_session = ssl_connect(fd);
		if(ssl_session == NULL)
		{
			tcp_close(fd);
			printf("ssl connect failed\n");
			return -1;
		}
	}

	set_socket_noblock(fd);
	
	http_session_t session;
	session.fd = fd;
	session.ssl_session = ssl_session;
	session.ssl_flag = ssl_flag;

	int content_length;

	char* content_buffer = (char*)malloc(image_size+1024);
	if(content_buffer == NULL){
		if(ssl_flag)
			ssl_close(ssl_session);

		tcp_close(fd);
		return -1;
	}
	
	memset(content_buffer,0,image_size+1024);
	content_length = create_image_request(content_buffer,timestamp,image_type,image_buffer,image_size);

	
	char http_head[1500];
	memset(http_head,0,sizeof(http_head));
	char tmp[150];
	memset(tmp,0,sizeof(tmp));
	snprintf(tmp,sizeof(tmp)-1,"POST /API/cameras/%s/images/upload HTTP/1.1\r\n",hash_id);
	strcat(http_head,tmp);
	memset(tmp,0,sizeof(tmp));
	snprintf(tmp,sizeof(tmp)-1,"Host: %s\r\n",ip);
	strcat(http_head,tmp);
	strcat(http_head,"Connection: keep-alive\r\n");
	
	memset(tmp,0,sizeof(tmp));
	snprintf(tmp,sizeof(tmp)-1,"Content-Length: %d\r\n",content_length);
	strcat(http_head,tmp);
	strcat(http_head,"Cache-Control: no-cache\r\n");
	strcat(http_head,"Content-Type: multipart/form-data; boundary=----WebKitFormBoundary3B1nByE04BkAcEQe\r\n");

	memset(tmp,0,sizeof(tmp));
	snprintf(tmp,sizeof(tmp)-1,"X-Camera-Token: %s\r\n",token);
	strcat(http_head,tmp);

	strcat(http_head,"Accept: */*\r\n");
	strcat(http_head,"Accept-Encoding: gzip, deflate\r\n");
	strcat(http_head,"Accept-Language: zh-CN,zh;q=0.8,de;q=0.6,en;q=0.4,es;q=0.2,fr;q=0.2,ja;q=0.2,pt;q=0.2,ru;q=0.2,th;q=0.2,tr;q=0.2,ur;q=0.2,zh-TW;q=0.2\r\n\r\n");


	int ret = http_send_data(&session,http_head,strlen(http_head));
	if(ret == -1)
	{
		if(ssl_flag)
			ssl_close(ssl_session);

		tcp_close(fd);
		free(content_buffer);
		return -1;
	}

	ret = http_send_data(&session,content_buffer,content_length);
	if(ret == -1)
	{
		if(ssl_flag)
			ssl_close(ssl_session);

		tcp_close(fd);
		free(content_buffer);
		return -1;
	}

	int status_code;
	char content[500];
	int content_len;
	memset(content,0,sizeof(content));
	ret = parse_http_reply(&session,&status_code,content,&content_len);
	
	if(ssl_flag)
		ssl_close(ssl_session);

	tcp_close(fd);
	free(content_buffer);
	
	if(ret != 0)
		return -1;
#if	1
	return status_code;
#else
	printf("status code:%d content :%s content size:%d\n",status_code,content,content_len);
	if(status_code != 200)
		return -1;
	return 0;
#endif	
}


int http_post_jsonData(char*ip,int port,char ssl_flag,char *token, char *post_url, char *msg_buffer, long msg_size)
{
	
	//printf("http_post_jsondata ==== ip:%s, port:%d, ssl_flag:%d\n",ip,port,ssl_flag);
	void* ssl_session = NULL;
	int fd = tcp_connect(ip,port);
	if(fd == -1)
		return -1;

	if(ssl_flag)
	{
		ssl_session = ssl_connect(fd);
		if(ssl_session == NULL)
		{
			tcp_close(fd);
			printf("ssl connect failed\n");
			return -1;
		}
	}

	set_socket_noblock(fd);
	http_session_t session;
	session.fd = fd;
	session.ssl_session = ssl_session;
	session.ssl_flag = ssl_flag;

	char http_head[1500];
	memset(http_head,0,sizeof(http_head));
	char tmp[150];
	memset(tmp,0,sizeof(tmp));
	snprintf(tmp,sizeof(tmp)-1,"POST %s HTTP/1.1\r\n",post_url);
	strcat(http_head,tmp);
	memset(tmp,0,sizeof(tmp));
	snprintf(tmp,sizeof(tmp)-1,"Host: %s\r\n",ip);
	strcat(http_head,tmp);
	strcat(http_head,"Accept: */*\r\n");

	memset(tmp,0,sizeof(tmp));
	snprintf(tmp,sizeof(tmp)-1,"X-Camera-Token: %s\r\n",token);
	strcat(http_head,tmp);

	strcat(http_head,"Content-Type: application/json; charset=utf-8\r\n");
	memset(tmp,0,sizeof(tmp));
	snprintf(tmp,sizeof(tmp)-1,"Content-Length: %d\r\n\r\n",msg_size);
	strcat(http_head,tmp);

	int ret = http_send_data(&session,http_head,strlen(http_head));
	if(ret == -1)
	{
		if(ssl_flag)
			ssl_close(ssl_session);

		tcp_close(fd);
		return -1;
	}

	if(msg_size > 0){
		ret = http_send_data(&session,msg_buffer,msg_size);
		if(ret == -1)
		{
			if(ssl_flag)
				ssl_close(ssl_session);

			tcp_close(fd);
			return -1;
		}
	}

	int status_code;
	char content[500];
	int content_len;
	memset(content,0,sizeof(content));
	ret = parse_http_reply(&session,&status_code,content,&content_len);
	
	if(ssl_flag)
		ssl_close(ssl_session);

	tcp_close(fd);
	if(ret != 0)
		return -1;
#if 1
	printf("status code:%d content :%s content size:%d\n",status_code,content,content_len);
	return status_code;
#else	
	printf("status code:%d content :%s content size:%d\n",status_code,content,content_len);
	if(status_code != 200)
		return -1;
	
	return 0;	
#endif
}

