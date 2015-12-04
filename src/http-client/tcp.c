#include "tcp.h"
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>

#ifdef OPENSSL
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/pem.h>
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/ssl.h>	

#else
#include "polarssl/config.h"
#include "polarssl/net.h"
#include "polarssl/ssl.h"
#include "polarssl/entropy.h"
#include "polarssl/ctr_drbg.h"
#include "polarssl/error.h"
#include "polarssl/certs.h"

#endif


#ifdef OPENSSL
static void*						ClientCTX = NULL;
static void*						ClientMethod = NULL;
#else

typedef struct _polarssl_context
{
	entropy_context entropy;
    ctr_drbg_context ctr_drbg;
    ssl_context ssl;
    int fd;
}polarssl_context;

#endif
int init_ssl()
{
#ifdef OPENSSL
	if(ClientCTX == NULL)
	{
		SSL_load_error_strings();
		SSL_library_init();
		ClientMethod = SSLv3_client_method();
		ClientCTX = SSL_CTX_new((SSL_METHOD*)ClientMethod);
		if (ClientCTX == NULL)
		{
			return -1;
		}
		SSL_CTX_set_quiet_shutdown((SSL_CTX*)ClientCTX,1);
	}
	return 0;

#else

	return 0;	
#endif
}

void http_delay_mseconds(int ms) {
	int fd = 0;
	struct timeval tv;
	tv.tv_sec = ms / 1000;
	tv.tv_usec = 1000 * (ms % 1000);
	select(fd + 1, NULL, NULL, NULL, &tv);
	return ;
}

void set_socket_noblock(int fd)
{
	int flags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, flags|O_NONBLOCK);
}

int tcp_connect(const char *ip, int port){

	/*socket*/
	struct hostent *host = NULL;
	int fd=socket(AF_INET, SOCK_STREAM, 0);
	if(fd==-1){
		printf("socket fail.:%d,ip:%s,port:%d\n", errno,ip,port);
		return -1;
	}

	int flags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, flags|O_NONBLOCK);

	/*peer address*/
	struct sockaddr_in peer_addr;
	bzero(&peer_addr, sizeof(struct sockaddr_in));
	peer_addr.sin_family=AF_INET;
	peer_addr.sin_port=htons(port);
	/*local address*/

	unsigned long inaddr;
	inaddr = inet_addr(ip);
	if(inaddr==INADDR_NONE)
    {       
		if((host=gethostbyname(ip))==NULL) /*是主机名*/
        {    
        	printf("gethostbyname failed ip:%s\n",ip);
			return -1;
        }
        memcpy((char*)&peer_addr.sin_addr,host->h_addr,host->h_length);
    }
    else    /*是ip地址*/
    {
    	peer_addr.sin_addr.s_addr=inet_addr(ip);
	}


	int opt = 1024 * 1024;
	
	/*connect*/
	int ret=0;
	int len=sizeof(struct sockaddr_in);
	ret=connect(fd, (struct sockaddr *)&peer_addr, len);
	/*nonblock connect okay.*/
	if(ret==0){
		printf("nonblock connect success.\n");
		
		ret = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (char*)&opt, sizeof(int));
		if(ret != 0) {
			printf("setsockopt failure.\n");
			close(fd);
			return -1;
		}
		
		return fd;
	}
	/*go on*/
	if(errno!=EINPROGRESS){
		printf("nonblock connect not in progress error.ip:%s,port:%d\n",ip,port);
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
		printf("select fail.ip:%s,port:%d\n",ip,port);
		close(fd);
		return -1;
	}else if(ret==0){
		printf("select time out.ip:%s,port:%d\n",ip,port);
		close(fd);
		return -1;
	}
	int sock_err;
	int slen=sizeof(sock_err);
	if(FD_ISSET(fd, &r)||FD_ISSET(fd, &w)){
		ret=getsockopt(fd, SOL_SOCKET, SO_ERROR, &sock_err, (socklen_t *)&slen);
		if(ret!=0){
			printf("getsockopt fail.ip:%s,port:%d\n",ip,port);
			close(fd);
			return -1;
		}
		if(sock_err==0){
			ret = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (char*)&opt, sizeof(int));
			if(ret != 0) {
				printf("setsockopt failure.\n");
				close(fd);
				return -1;
			}
			//printf("select getsockopt then connect success.\n");
			fcntl(fd, F_SETFL, flags);
			return fd;
		}else{
			printf("select getsockopt then connect fail.ip:%s,port:%d,sock_err:%d\n",ip,port,sock_err);
			close(fd);
			return -1;
		}
	}else{
		printf("socket not set error.ip:%s,port:%d\n",ip,port);
		close(fd);
		return -1;
	}

	return -1;
}


int tcp_recv(int fd,  char* buffer, int len) {
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
		http_delay_mseconds(20);
		run_count++;
	}
	return -1;
}


int tcp_recv_noblock(int fd,  char* buffer, int len) {
	int ret = 0;
	char *p = buffer;
	int left = len;
	ret = recv(fd, p, left, 0);
	if(ret == -1){
		 if(errno == EAGAIN || errno == EWOULDBLOCK)
		 	return 0;
		 else 
  	 	 {
  			printf("recv error.errno:%d\n",errno);
  			return -1;
  		 }
	}
	else if(ret == 0){
		printf("recv 0 bytes.peer has performed an ordly shutdown. errno:%d\n",errno);
		return -1;
	}
	else
		return ret;
}


int tcp_send_noblock(int fd,  char* buffer, int len) {
	int ret = 0;
	ret = send(fd,buffer,len,0);
	if(ret == -1){
		 if(errno == EAGAIN || errno == EWOULDBLOCK)
		 	return 0;
		 else if(errno == EPIPE){
			printf("send error EPIPE.\n");
			return -1;
		 }else if(errno == EBADF){
			printf("send error EBADF.\n");
			return -1;
		 }else if(errno == ECONNRESET){
			printf("send error ECONNRESET.\n");
			return -1;
		 }
		 else 
  	 	 {
  			printf("send error.errno:%d\n",errno);
  			return -1;
  		 }
	}

	return ret;
}


int tcp_send(int fd,  char* buffer, int len) {
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
		http_delay_mseconds(20);
		run_count++;
	}
	return -1;
}


void tcp_close(int fd) {
	shutdown(fd, SHUT_RDWR);
	close(fd);
	//printf("tcp close:%d\n",fd);
}

void ssl_close(void* ssl_session)
{
#ifdef OPENSSL
	SSL_shutdown ((SSL*)ssl_session);
	SSL_free ((SSL*)ssl_session);
#else
	polarssl_context* ptr_context = (polarssl_context*)ssl_session;
	ssl_close_notify(&ptr_context->ssl);
	ssl_free(&ptr_context->ssl);
	free(ptr_context);
#endif
}


void* ssl_connect(int fd)
{
#ifdef OPENSSL
	void* ssl_session = SSL_new((SSL_CTX*)ClientCTX);
	if (ssl_session == NULL)
	{
		return NULL;
	}


	SSL_set_fd ((SSL*)ssl_session,fd);
	int err =  SSL_connect((SSL*)ssl_session);
	err = SSL_get_error((SSL*)ssl_session, err);

	switch (err)
	{
	case SSL_ERROR_NONE:
		break;

	case SSL_ERROR_WANT_WRITE:
	case SSL_ERROR_WANT_READ:
	case SSL_ERROR_WANT_X509_LOOKUP:
		break;

	case SSL_ERROR_SYSCALL: 				
	case SSL_ERROR_SSL:
	case SSL_ERROR_ZERO_RETURN:
		err = -10010;
		break;

	default:
		err = -10020;
		break;
	}

	if (err != SSL_ERROR_NONE)
	{
		SSL_free ((SSL*)ssl_session);
		ssl_session = NULL;
		return NULL;
	}

	return ssl_session;
#else
	
	const char *pers = "ssl_client1";
	polarssl_context* ptr_context = calloc(sizeof(polarssl_context),1);
	if(ptr_context == NULL)
		return NULL;
	

	int ret;

	/*
	 * 0. Initialize the RNG and the session data
	 */
	ptr_context->fd = fd;
	memset(&ptr_context->ssl, 0, sizeof(ssl_context));
	entropy_init(&ptr_context->entropy);
	if((ret = ctr_drbg_init(&ptr_context->ctr_drbg, entropy_func,&ptr_context->entropy,
							   (const unsigned char *) pers,
							   strlen(pers))) != 0 )
	{
		printf( " failed\n	! ctr_drbg_init returned %d\n",ret);
		free(ptr_context);
		return NULL;
	}


	if( ret < 0 )
	{
		printf( " failed\n	!  x509parse_crt returned -0x%x\n\n", -ret );
		free(ptr_context);
		return NULL;
	}

	if((ret = ssl_init(&ptr_context->ssl)) != 0 )
    {
 	   printf( " failed\n  ! ssl_init returned %d\n\n", ret );
	   free(ptr_context);
 	   return NULL;
    }

	//ssl_set_min_version(&ptr_context->ssl, SSL_MAJOR_VERSION_3,0);
	//ssl_set_max_version(&ptr_context->ssl, SSL_MAJOR_VERSION_3,0);
    ssl_set_endpoint(&ptr_context->ssl, SSL_IS_CLIENT );
    /* OPTIONAL is not optimal for security,
 	* but makes interop easier in this simplified example */
    ssl_set_authmode(&ptr_context->ssl, SSL_VERIFY_NONE);
    ssl_set_rng(&ptr_context->ssl, ctr_drbg_random, &ptr_context->ctr_drbg );
    ssl_set_bio(&ptr_context->ssl, net_recv, &ptr_context->fd,net_send, &ptr_context->fd);

	int count = 0;
	while((ret = ssl_handshake(&ptr_context->ssl)) != 0 )
    {
        if( ret != POLARSSL_ERR_NET_WANT_READ && ret != POLARSSL_ERR_NET_WANT_WRITE )
        {
            printf( " failed\n  ! ssl_handshake returned -0x%x\n\n", -ret );
            free(ptr_context);
 	  		return NULL;
        }
		count++;
		if(count>20)
		{
			printf("ssl_handshake timeout\n");
			free(ptr_context);
 	  		return NULL;
		}

		http_delay_mseconds(200);
    }
	return ptr_context;

#endif
}

int ssl_recv_noblock(void* ssl_session, char* buffer,int len)
{
#ifdef OPENSSL
	int	nRet = SSL_read ((SSL*)ssl_session,buffer, len);
	int nErrorNum = SSL_get_error((SSL*)ssl_session, nRet);
	if (nErrorNum == SSL_ERROR_NONE)
	{
		return nRet;
	}
	else if(nErrorNum == SSL_ERROR_WANT_READ)
	{
		return 0;
	}

	return -1;
#else
	polarssl_context* ptr_context = (polarssl_context*)ssl_session;
	int ret = ssl_read(&ptr_context->ssl,buffer,len);
    if( ret == POLARSSL_ERR_NET_WANT_READ)
        return 0;

    if( ret == POLARSSL_ERR_SSL_PEER_CLOSE_NOTIFY )
        return -1;

    if( ret <= 0 )
    {
        printf( "failed\n  ! ssl_read returned %d\n\n", ret );
       	return -1;
    }

  	return ret;

#endif
}

int ssl_send_noblock(void* ssl_session, char* buffer,int len)
{
#ifdef OPENSSL
	int nRet = SSL_write((SSL*)ssl_session,buffer, len);
	int nErrorNum = SSL_get_error((SSL*)ssl_session, nRet);
	if (nErrorNum == SSL_ERROR_NONE)
	{
		return nRet;
	}
	else if(nErrorNum == SSL_ERROR_WANT_WRITE)
	{
		return 0;
	}

	return -1;
#else
	polarssl_context* ptr_context = (polarssl_context*)ssl_session;
	int ret = ssl_write(&ptr_context->ssl, buffer,len);
	if(ret <= 0)
	{
		if(ret != POLARSSL_ERR_NET_WANT_WRITE )
        {
           return -1;
        }
		return 0;
	}
	return ret;
#endif
}

int http_recv_noblock(http_session_t* session, char* buffer,int len)
{
	if(session == NULL)
		return -1;

	if(session->ssl_flag)
	{
		return ssl_recv_noblock(session->ssl_session,buffer,len);
	}
	else
		return tcp_recv_noblock(session->fd,buffer,len);
}

int http_send_noblock(http_session_t* session, char* buffer,int len)
{
	if(session == NULL)
		return -1;

	if(session->ssl_flag)
	{
		return ssl_send_noblock(session->ssl_session,buffer,len);
	}
	else
		return tcp_send_noblock(session->fd,buffer,len);
}

int http_send_data(http_session_t* session, char* buffer,int len)
{
	if(session == NULL)
		return -1;

	int run_count = 0;
	int ret = 0;
	int send_len = 0;
	while(run_count <500){
		ret = http_send_noblock(session,buffer+send_len,len-send_len);
		if(ret == -1)
			return -1;
		
		send_len +=ret;

		if(send_len == len){
			return send_len;
		}
		http_delay_mseconds(20);
		run_count++;
	}
	return -1;
}


void parse_http_head(char* start, char* end,int* status_code,char* content,int* content_len)
{
	//printf("parse http head:%s\n",start);
	if(strncmp(start,"HTTP/1.1",strlen("HTTP/1.1")) == 0)
	{
		char tmp1[20];
		char tmp2[20];
		sscanf(start,"%s %d %s",tmp1,status_code,tmp2);
	}
	else if(strncmp(start,"Content-Length:",strlen("Content-Length:")) == 0)
	{
		char* tmp = start + strlen("Content-Length:");
		tmp++;
		*content_len = atoi(tmp);
	}
}

int parse_http_reply(http_session_t* session,int* status_code,char* content,int* content_len)
{
	int run_count = 0;
	int ret = 0;
	int recv_len = 0;
	char http_reply[1024];
	memset(http_reply,0,sizeof(http_reply));
	int parse_pos = 0;
	int http_head_start_pos = 0;
	char http_head_recv_done[4]={'\r','\n','\r','\n'};
	int http_head_size = 0;
	int http_content_size = 0;
	char http_head_recv_done_flag = 0;
	*content_len = 0;
	while(run_count <500){
		ret = http_recv_noblock(session,http_reply+recv_len,sizeof(http_reply)-recv_len);
		if(ret == -1)
			return -1;
		
		recv_len +=ret;
		while(parse_pos<recv_len){
			char* tmp = http_reply+parse_pos;
			if(http_head_recv_done_flag)
			{
				if(http_head_size + http_content_size == parse_pos+1){
					if(http_content_size != 0)
						memcpy(content,http_reply+http_head_size,http_content_size);

					//printf("parse success content:%s http_content_size:%d\n",content,http_content_size);
					return 0;
				}
			}

			
			if(*tmp == '\n')
			{
				if(parse_pos >= 3)
				{
					if(memcmp(http_head_recv_done,tmp-3,4)==0)
					{
						http_head_size = parse_pos + 1;
						http_head_recv_done_flag = 1;
						parse_pos++;
						http_content_size = *content_len;
						//printf("http head recv finish http_content_size:%d\n",http_content_size);
						if(http_content_size == 0)
							return 0;
						
						continue;
					}
				}

				//parse http head here
				char* http_head_start_addr = http_reply+http_head_start_pos;
				if(*http_head_start_addr != '\r'){
					parse_http_head(http_head_start_addr,tmp,status_code,content,content_len);
				}

				http_head_start_pos = parse_pos + 1;
			}

			parse_pos++;
		}
		
		
		if(recv_len == sizeof(http_reply)){
			return -1;
		}
		http_delay_mseconds(20);
		run_count++;
	}
	return -1;
}




