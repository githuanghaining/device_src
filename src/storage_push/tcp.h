#ifndef __TCP_H__
#define __TCP_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <ctype.h>
#include <stddef.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/epoll.h>

#include "typedef.h"
#include "list.h"
#include "file.h"
#include "typedef.h"


#define VIDEO_SOURCE	1

//
#define SHAKE_HAND_ACTION_UPLOAD		1
#define SHAKE_HAND_ACTION_DOWNLOAD	2
#define SHAKE_HAND_ACTION_KEEPALIVE	3
#pragma pack(1)
struct shake_hand{
	uint32b_t source;
	uint32b_t time;
	uint32b_t action;
};
#pragma pack()



int tcp_connect2(const char *ip, int port);

int tcp_connect(const char *ip, int port);


int tcp_recv(int fd, uint8b_t *buffer, int len);


int tcp_send(int fd, uint8b_t *buffer, int len);

int tcp_send2(int fd, uint8b_t *buffer, int len,int* send_len);


int tcp_send_noblock(int fd, uint8b_t *buffer, int len);

int tcp_recv_noblock(int fd, uint8b_t *buffer, int len);

void tcp_close(int fd);


#endif


