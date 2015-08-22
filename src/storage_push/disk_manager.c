#include "protocol.h"
#include "camera_log.h"
#include "ly_time.h"
#include "disk_manager.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

static unsigned int disk_requst_sequence_id = 1;

static int wait_data(int fd,int timeout)
{
	fd_set read_set;

	FD_ZERO(&read_set);
	FD_SET(fd, &read_set);	

	if(timeout <= 0)
		timeout = 3000;

	struct timeval tv;
	tv.tv_sec = timeout / 1000;
	tv.tv_usec = 1000 * (timeout % 1000);
	int ret = select(fd + 1, &read_set, NULL, NULL, &tv);
	if(ret <= 0){
		printf("select error,ret:%d\n",ret);
		return -1;
	}

	if (FD_ISSET(fd, &read_set)) {
		return 0;		
	}

	printf("selct fd:%d not in read_set\n",fd);
	return -1;

}


static int parse_disk_server_list(unsigned char* data,int data_len,disk_server_t* ds,uint8b_t* num)
{
	unsigned char* tmp = data;
	tmp = tmp + sizeof(msgheader_t);
	unsigned char result = *tmp++;
	if(result != DISKTRACKER_ERROR_NO_ERROR){
		gerr("parse request_disk reply, result is error :%d",result);
		return -1;
	}

	unsigned char count = *tmp++;
	if(count == 0){
		gerr("parse request_disk reply,get no disks server");
		return -1;
	}

	*num = count;
	tmp = tmp + 2;
	int i;
	disk_server_t* dst = ds;
	for(i=0;i<count;i++)
	{
		disk_server_info_t* dsi = (disk_server_info_t*)tmp;
		dst[i].server_port = dsi->port;
		memset(dst[i].server_ip,0,sizeof(dst[i].server_ip));
		unsigned char* ip_str = (unsigned char*)&(dsi->ip);
		sprintf(dst[i].server_ip,"%d.%d.%d.%d",ip_str[3],ip_str[2],ip_str[1],ip_str[0]);
		gmsg("parse disk server ip = %s , port = %d",dst[i].server_ip,dst[i].server_port);
		tmp = tmp + sizeof(disk_server_info_t);
	}

	gmsg("get disk server info success ,count:%d",count);
	return 0;
	
}


static int sendUDP(char* ip,int port,char* data,int data_len,disk_server_t* ds,uint8b_t* num)
{
	
	struct sockaddr_in addr;
	int sock;

	if ((sock=socket(AF_INET, SOCK_DGRAM, 0))<0)
	{
		gerr("sendUDP creat socket failed,ip:%s,port:%d",ip,port);
		*num = 0;
		return -1;
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);
	if (addr.sin_addr.s_addr == INADDR_NONE)
	{
		gerr("Incorrect ip address! ip:%s",ip);
		close(sock);
		*num = 0;
		return -1;
	}

	unsigned char buff[1024]={0};
    socklen_t len = sizeof(addr);

	int n;
    n = sendto(sock, data, data_len, 0, (struct sockaddr *)&addr, sizeof(addr));
    if (n < 0)
    {
    	gerr("sendUDP sendto failed,ip:%s,port:%d",ip,port);
        close(sock);
		*num = 0;
        return -1;
    }

	if(wait_data(sock,3000) == -1){
		close(sock);
		*num = 0;
		return -1;
	}
	
    n = recvfrom(sock, buff, sizeof(buff), 0, (struct sockaddr *)&addr, &len);
    if (n>0)
    {
    	if(parse_disk_server_list(buff,n,ds,num) != 0){
			close(sock);
			*num = 0;
			return -1;
		}

		close(sock);
		return 0;
    }
    else
        gerr("sendUDP recvfrom failed,ip:%s,port:%d",ip,port);
	
	close(sock);
	*num = 0;
	return -1;
		
}


static int have_same_disk_server_info(disk_server_t* ds,uint8b_t disk_num)
{
	int i,j;

	if(disk_num<=1)
		return 0;
	
	for(i=0;i<disk_num-1;i++){
		for(j=i+1;j<disk_num;j++){
			if((strcmp(ds[i].server_ip,ds[j].server_ip) == 0)&&(ds[i].server_port == ds[j].server_port))
				return 1;
		}
	}
	return 0;
}

int get_disk_server_list(char* ip,int port,disk_server_t** ds,uint8b_t disk_num,uint8b_t* real_disk_num)
{
	request_disk_t rdt;
	rdt.header.cmd = DISKTRACKER_CMD_REQ_DISK_SERVER;
	rdt.header.len = sizeof(request_disk_t);
	rdt.header.seq = disk_requst_sequence_id++;
	rdt.count = disk_num;

	if(disk_num == 0)
	{
		*ds = NULL;
		*real_disk_num = 0;
		return -1;
	}

	*ds = (disk_server_t*)malloc(sizeof(disk_server_t)*disk_num);
	if(*ds == NULL){
		gerr("get disk server list malloc failed");
		*real_disk_num = 0;
		return -1;
	}

	disk_server_t* tmp_disk_server = *ds;
	uint8b_t tmp_disk_num = 0;
	int run_count = 0;
	while(1)
	{
		int ret = sendUDP(ip,port,(char*)&rdt,sizeof(request_disk_t),tmp_disk_server,&tmp_disk_num);
		if(ret == -1){
			delay_mseconds(500);
			rdt.header.seq = disk_requst_sequence_id++;
			run_count++;
			if(run_count>=20){
				gerr("connect disk schedule server failed,server ip:%s,port:%d",ip,port);
				free(*ds);
				*ds = NULL;
				*real_disk_num = 0;
				return -1;
			}
			continue;
		}

		*real_disk_num = tmp_disk_num;
		break;
	}

	if(have_same_disk_server_info(tmp_disk_server,*real_disk_num)){
		gerr("==========get %d disk,but have same disk server info================",*real_disk_num);
		free(*ds);
		*ds = NULL;
		*real_disk_num = 0;
		return -1;
	}


	gmsg("==========get disk server list success,want disk_num:%d real disk num:%d ================",disk_num,*real_disk_num);
	return 0;
	
}


