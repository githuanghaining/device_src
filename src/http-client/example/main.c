#include "http_client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


int read_file_data(char* file_name,char** buffer, int* buffer_size)
{
	int flag = 0,file_size,read_size;
	int now_size = 0;
	FILE *fp = NULL;
#ifndef WIN32
	struct stat stat_file;
	fp = fopen(file_name,"r");
#else
	struct _stat stat_file;
	fp = fopen(file_name,"rb");
#endif

	if(NULL == fp)
	{
		return 0;//Òª·µ»Ø´íÎó´úÂë
	}

#ifndef WIN32
	bzero(&stat_file, sizeof(struct stat));
	flag = stat(file_name, &stat_file);
#else
	memset(&stat_file,0,sizeof(struct _stat));
	flag = _stat(file_name, &stat_file);
#endif	
	if(flag == -1) {
		printf("read_file_data stat file failed\n");
		fclose(fp);
		return 0;
	}

	file_size = stat_file.st_size;
	*buffer = (char*)malloc(file_size);
	memset(*buffer,0,file_size);
	if(*buffer == NULL){
		printf("read_file_data malloc failed\n");
		fclose(fp);
		return 0;
	}

	do 
	{
		read_size = fread(*buffer,sizeof(char),file_size,fp);
		if (read_size > 0)
		{
			now_size += read_size;
		}
		else
		{
			printf("===========read error\n");
		}		

	} while (now_size < file_size);

	*buffer_size = file_size;
	fclose(fp);
	return 1;
}


int main(int argc,char** argv)
{
	char filename[128] = {0};
	char* file_buffer = NULL;
	int file_buffer_size;
	strcpy(filename,"test.jpg");
	int ret;
	init_ssl();
	if(!read_file_data(filename,&file_buffer,&file_buffer_size))
	{
		printf("read file date failed =================\n");
		return 0;
	}

	ret = http_post_image("192.168.2.221",443,1,"23500F00FA284D56FFFFFF2759CFF89371DFD4FDCAD4011C3CC92ACD","ED23E700B30F7850",1447758720,1,file_buffer,file_buffer_size);
	free(file_buffer);
	printf("http post image ret:%d\n",ret);


	ret = http_post_jsonData("192.168.2.221",443,1,"23500F00FA284D56FFFFFF2759CFF89371DFD4FDCAD4011C3CC92ACD","/API/cameras/ED23E700B30F7850/extra","{\"extra\":\"{\\\"property\\\":1}\"}",strlen("{\"extra\":\"{\\\"property\\\":1}\"}"));
	printf("http_post_jsonData ret:%d\n",ret);

	ret = http_post_jsonData("192.168.2.221", 80, 0, "23500F00FA284D56FFFFFF2759CFF89371DFD4FDCAD4011C3CC92ACD","/API/cameras/ED23E700B30F7850/extra","{\"extra\":\"{\\\"property\\\":1}\"}",strlen("{\"extra\":\"{\\\"property\\\":1}\"}"));
	printf("http_post_jsonData ret:%d\n",ret);
	//ret = http_post_jsonData("api.topvdn.com",80,0,"23500F00FA284D56FFFFFF2759CFF89371DFD4FDCAD4011C3CC92ACD","/API/cameras/public/5A9DF200600F934E/addr/remove",NULL,0);
	//printf("http_post_jsonData remove addr ret:%d\n",ret);
		
}

