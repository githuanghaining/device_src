#ifndef __TCP_H__
#define __TCP_H__

typedef struct http_session
{
	int fd;
	void* ssl_session;
	int ssl_flag;
}http_session_t;

int init_ssl();

void set_socket_noblock(int fd);

void delay_mseconds(int ms);

int tcp_connect(const char* ip, int port);

int tcp_recv(int fd, char* buffer, int len);

int tcp_send(int fd, char* buffer, int len);

int tcp_send_noblock(int fd, char* buffer, int len);

int tcp_recv_noblock(int fd, char* buffer, int len);

void tcp_close(int fd);


void* ssl_connect(int fd);

void ssl_close(void* ssl_session);

int ssl_recv_noblock(void* ssl_session, char* buffer,int len);

int ssl_send_noblock(void* ssl_session, char* buffer,int len);

int http_recv_noblock(http_session_t* session, char* buffer,int len);

int http_send_noblock(http_session_t* session, char* buffer,int len);

int http_send_data(http_session_t* session, char* buffer,int len);


int parse_http_reply(http_session_t* session,int* status_code,char* content,int* content_len);

#endif


