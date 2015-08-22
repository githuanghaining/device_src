#include "camera_log.h"
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "platform_cfg.h"

#define HTTP_POST_LOG_FILE_NAME "http_post.log"
#define HTTP_POST_LOG_FILE_NAME_BCAKUP "http_post.log.1"
#define HTTP_POST_LOG_FILE_SIZE (20 * 1024 * 1024)


#define LOG_FILE_NAME "camera_error.log"
#define LOG_FILE_NAME_BCAKUP "camera_error.log.1"
#define LOG_FILE_SIZE (10 * 1024 * 1024)


extern platform_config_t platform_global_config;


static int file_exist(const char *pathname) {
	int flag = 0;
	struct stat stat_file;
	bzero(&stat_file, sizeof(struct stat));
	flag = stat(pathname, &stat_file);
	if(flag == -1) {
		return 0;
	}
	return 1;
}
static int file_create(const char *pathname) {
	if(file_exist(pathname)) {
		return 0;
	}
	int ret = 0;
	ret = creat(pathname, 0777);
	if(ret == -1) {
		gdebug("create failure.");
		gmsg("errno:%d", errno);
		return -1;
	}
	close(ret);

	return 0;
}

static int file_delete(const char *pathname) {
	if(!file_exist(pathname)) {
		return 0;
	}
	int flag = remove(pathname);
	if(flag == -1) {
		return -1;
	}
	if(file_exist(pathname)) {
		return -1;
	}
	return 0;
}
static int file_size(const char *pathname) {
	int flag = 0;
	struct stat stat_file;
	bzero(&stat_file, sizeof(struct stat));
	flag = stat(pathname, &stat_file);
	if(flag == -1) {
		return -1;
	}
	return (int)stat_file.st_size;
}



void write_log(const char * fmt, ...) {
	char msg[512] = {0};
	int file_len = 0;
	char filename[200];
	char filename_bak[200];
	memset(filename,0,sizeof(filename));
	memset(filename_bak,0,sizeof(filename_bak));
	strcat(filename,platform_global_config.rtmp_log_dir);
	strcat(filename,LOG_FILE_NAME);

	strcat(filename_bak,platform_global_config.rtmp_log_dir);
	strcat(filename_bak,LOG_FILE_NAME_BCAKUP);

	
	file_len = file_size(filename);
	if (file_len + sizeof(msg) > LOG_FILE_SIZE) {
		if (1 == file_exist(filename_bak)) {
			file_delete(filename_bak);
		}
		if (0 != rename(filename, filename_bak))
			return;
	}

	va_list args;
	va_start(args, fmt);
	vsnprintf(msg, sizeof(msg) - 1, fmt, args);
	va_end(args);
	
	int file_id = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666);
	if (-1 == file_id) 
		return;
	int ret = write(file_id, msg, strlen(msg));
	if (ret < 0) {
		printf("write_log failed. errno=%d", errno);
	}
	fprintf(stderr, "%s", msg);
	fflush(stderr);
	
	close(file_id);

	return;
}

void _write_log(const char * file, int line, const char * func, const char * fmt, ...) {
	char msg[512] = {0};
	int file_len = 0;

	char filename[200];
	char filename_bak[200];
	memset(filename,0,sizeof(filename));
	memset(filename_bak,0,sizeof(filename_bak));
	strcat(filename,platform_global_config.rtmp_log_dir);
	strcat(filename,LOG_FILE_NAME);

	strcat(filename_bak,platform_global_config.rtmp_log_dir);
	strcat(filename_bak,LOG_FILE_NAME_BCAKUP);

	
	file_len = file_size(filename);
	if (file_len + sizeof(msg) > LOG_FILE_SIZE) {
		if (1 == file_exist(filename_bak)) {
			file_delete(filename_bak);
		}
		if (0 != rename(filename, filename_bak))
			return;
	}

	va_list args;
	va_start(args, fmt);
	vsnprintf(msg, sizeof(msg) - 1, fmt, args);
	va_end(args);

	int size = strlen(msg);
	if (size + 1 <= sizeof(msg)) {
		time_t now = time(0);
		struct tm * tm_now = localtime(&now); 
		snprintf(msg + size, sizeof(msg) - size - 1, "=======> File : %s, Line : %d, Func: %s, DateTime : %s",	\
		file, line, func, asctime(tm_now)); 
	}
	int file_id = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666);
	if (-1 == file_id) 
		return;
	int ret = write(file_id, msg, strlen(msg));
	if (ret < 0) {
		printf("write_log failed. errno=%d", errno);
	}

	fprintf(stderr, "%s", msg);
	fflush(stderr);
	
	close(file_id);

	return;
}


void http_write_log(const char * file, int line, const char * func, const char * fmt, ...) {
	char msg[512] = {0};
	int file_len = 0;
	char filename[200];
	char filename_bak[200];
	memset(filename,0,sizeof(filename));
	memset(filename_bak,0,sizeof(filename_bak));
	strcat(filename,platform_global_config.rtmp_log_dir);
	strcat(filename,HTTP_POST_LOG_FILE_NAME);

	strcat(filename_bak,platform_global_config.rtmp_log_dir);
	strcat(filename_bak,HTTP_POST_LOG_FILE_NAME_BCAKUP);

	
	file_len = file_size(filename);
	if (file_len + sizeof(msg) > HTTP_POST_LOG_FILE_SIZE) {
		if (1 == file_exist(filename_bak)) {
			file_delete(filename_bak);
		}
		if (0 != rename(filename, filename_bak))
			return;
	}

	va_list args;
	va_start(args, fmt);
	vsnprintf(msg, sizeof(msg) - 1, fmt, args);
	va_end(args);

	int size = strlen(msg);
	if (size + 1 <= sizeof(msg)) {
		time_t now = time(0);
		struct tm * tm_now = localtime(&now); 
		snprintf(msg + size, sizeof(msg) - size - 1, "=======> File : %s, Line : %d, Func: %s, DateTime : %s",	\
		file, line, func, asctime(tm_now)); 
	}
	int file_id = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666);
	if (-1 == file_id) 
		return;
	int ret = write(file_id, msg, strlen(msg));
	if (ret < 0) {
		printf("write_log failed. errno=%d", errno);
	}

	fprintf(stderr, "%s", msg);
	fflush(stderr);
	
	close(file_id);

	return;
}

