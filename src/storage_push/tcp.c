#include "tcp.h"

#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/resource.h>


#include "list.h"
#include "camera_log.h"
#include "ly_time.h"
#include "lock.h"


int tcp_connect(const char *ip, int port){

	/*socket*/
	int fd=socket(AF_INET, SOCK_STREAM, 0);
	if(fd==-1){
		gerr("socket fail.:%d,ip:%s,port:%d", errno,ip,port);
		return -1;
	}
	fcntl(fd, F_SETFL, fcntl(fd, F_GETFL)|O_NONBLOCK);
	/*peer address*/
	struct sockaddr_in peer_addr;
	bzero(&peer_addr, sizeof(struct sockaddr_in));
	peer_addr.sin_family=AF_INET;
	peer_addr.sin_port=htons(port);
	peer_addr.sin_addr.s_addr=inet_addr(ip);
	/*local address*/

	int opt = 1024 * 1024;
	
	/*connect*/
	int ret=0;
	int len=sizeof(struct sockaddr_in);
	ret=connect(fd, (struct sockaddr *)&peer_addr, len);
	/*nonblock connect okay.*/
	if(ret==0){
		gdebug("nonblock connect success.");
		
		ret = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (char*)&opt, sizeof(int));
		if(ret != 0) {
			gerr("setsockopt failure.");
			close(fd);
			return -1;
		}
		
		return fd;
	}
	/*go on*/
	if(errno!=EINPROGRESS){
		gerr("nonblock connect not in progress error.ip:%s,port:%d",ip,port);
		close(fd);
		return -1;
	}
	
	/*select msg*/
	fd_set r, w;
	struct timeval t;
	t.tv_sec=10;
	t.tv_usec=0;
	FD_ZERO(&r);
	FD_ZERO(&w);
	FD_SET(fd, &r);
	FD_SET(fd, &w);
	ret=select(fd+1, &r, &w, NULL, &t);
	if(ret==-1){
		gerr("select fail.ip:%s,port:%d",ip,port);
		close(fd);
		return -1;
	}else if(ret==0){
		gerr("select time out.ip:%s,port:%d",ip,port);
		close(fd);
		return -1;
	}
	int sock_err;
	int slen=sizeof(sock_err);
	if(FD_ISSET(fd, &r)||FD_ISSET(fd, &w)){
		ret=getsockopt(fd, SOL_SOCKET, SO_ERROR, &sock_err, (socklen_t *)&slen);
		if(ret!=0){
			gerr("getsockopt fail.ip:%s,port:%d",ip,port);
			close(fd);
			return -1;
		}
		if(sock_err==0){
			ret = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (char*)&opt, sizeof(int));
			if(ret != 0) {
				gerr("setsockopt failure.");
				close(fd);
				return -1;
			}
			gdebug("select getsockopt then connect success.");
			return fd;
		}else{
			gerr("select getsockopt then connect fail.ip:%s,port:%d,sock_err:%d",ip,port,sock_err);
			close(fd);
			return -1;
		}
	}else{
		gerr("socket not set error.ip:%s,port:%d",ip,port);
		close(fd);
		return -1;
	}

	return -1;
}


int tcp_connect2(const char *ip, int port){

	//
	int fd=socket(AF_INET, SOCK_STREAM, 0);	
	if(fd==-1){
		gdebug("socket fail.:%d", errno);
		return -1;
	}
	//
	struct sockaddr_in peer_addr;
	bzero(&peer_addr, sizeof(struct sockaddr_in));
	peer_addr.sin_family=AF_INET;
	peer_addr.sin_port=htons(port);
	peer_addr.sin_addr.s_addr=inet_addr(ip);

	//
	int ret=0;
	int len=sizeof(struct sockaddr_in);
	ret=connect(fd, (struct sockaddr *)&peer_addr, len);
	if(ret!=0){
		//shutdown(fd, SHUT_RDWR);
		close(fd);
		gerr("connect failure.:%d", errno);
		return -1;
	}

	int keepAlive = 60;
	setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepAlive, sizeof(keepAlive));
	fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
	return fd;
}



int tcp_recv(int fd, uint8b_t *buffer, int len) {
	int run_count = 0;
	int ret = 0;
	int recv_len = 0;
	while(run_count <500){
		ret = tcp_recv_noblock(fd,buffer+recv_len,len-recv_len);
		if(ret == -1)
			return -1;
		
		recv_len +=ret;

		if(recv_len == len){
			return recv_len;
		}
		delay_mseconds(20);
		run_count++;
	}
	return -1;
}


int tcp_recv_noblock(int fd, uint8b_t *buffer, int len) {
	int ret = 0;
	uint8b_t *p = buffer;
	int left = len;
	ret = recv(fd, p, left, 0);
	if(ret == -1){
		 if(errno == EAGAIN || errno == EWOULDBLOCK)
		 	return 0;
		 else 
  	 	 {
  			gerr("recv error.errno:%d",errno);
  			return -1;
  		 }
	}
	else if(ret == 0){
		gerr("recv 0 bytes.peer has performed an ordly shutdown.");
		return -1;
	}
	else
		return ret;
}


int tcp_send_noblock(int fd, uint8b_t *buffer, int len) {
	int ret = 0;
	ret = send(fd,buffer,len,0);
	if(ret == -1){
		 if(errno == EAGAIN || errno == EWOULDBLOCK)
		 	return 0;
		 else if(errno == EPIPE){
			gerr("send error EPIPE.");
			return -1;
		 }else if(errno == EBADF){
			gerr("send error EBADF.");
			return -1;
		 }else if(errno == ECONNRESET){
			gerr("send error ECONNRESET.");
			return -1;
		 }
		 else 
  	 	 {
  			gerr("send error.errno:%d",errno);
  			return -1;
  		 }
	}

	return ret;
}


int tcp_send(int fd, uint8b_t *buffer, int len) {
	int run_count = 0;
	int ret = 0;
	int send_len = 0;
	while(run_count <500){
		ret = tcp_send_noblock(fd,buffer+send_len,len-send_len);
		if(ret == -1)
			return -1;
		
		send_len +=ret;

		if(send_len == len){
			return send_len;
		}
		delay_mseconds(20);
		run_count++;
	}
	return -1;
}


int tcp_send2(int fd, uint8b_t *buffer, int len,int* send_len) {
	int run_count = 0;
	int ret = 0;
	*send_len = 0;
	while(run_count <500){
		ret = tcp_send_noblock(fd,buffer+*send_len,len-*send_len);
		if(ret == -1)
			return -1;
		
		*send_len +=ret;

		if(*send_len == len){
			return *send_len;
		}
		delay_mseconds(20);
		run_count++;
	}
	return -2;
}


void tcp_close(int fd) {
	
	//shutdown(fd, SHUT_RDWR);
	close(fd);
	gdebug("tcp close:%d",fd);
}




