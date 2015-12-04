#include "file.h"

#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/vfs.h>
#include <sys/statfs.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <strings.h>

#include "typedef.h"
#include "log.h"




int file_exist(const char *pathname) {
	int flag = 0;
	struct stat stat_file;
	bzero(&stat_file, sizeof(struct stat));
	flag = stat(pathname, &stat_file);
	if(flag == -1) {
		return 0;
	}
	return 1;
}
int file_create(const char *pathname) {
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

int file_delete(const char *pathname) {
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
int64b_t file_size(const char *pathname) {
	int flag = 0;
	struct stat stat_file;
	bzero(&stat_file, sizeof(struct stat));
	flag = stat(pathname, &stat_file);
	if(flag == -1) {
		return -1;
	}
	return (uint64b_t)stat_file.st_size;
}
int file_alloc(const char *pathname, int size) {
	int ret = 0;
	if(!file_exist(pathname)) {
		gdebug("file not exist error.");
		return -1;
	}
	int fd = open(pathname, O_RDWR);
	if(fd == -1) {
		gerr("open failure.");
		gmsg("errno:%d", errno);
		return -1;
	}
	ret = posix_fallocate(fd, 0, size);
	if(ret != 0) {
		gerr("fallocate failure. errno:%d", errno);
		return -1;
	}
	close(fd);
	return 0;
}

int dir_exist(const char *pathname) {
	return file_exist(pathname);
}
int dir_create(const char *pathname) {
	int ret = mkdir(pathname, 0777);
	if(ret != 0) {
		gerr("mkdir failure.");
		return -1;
	}
	if(!dir_exist(pathname)) {
		gerr("dir not exist error.");
		return -1;
	}
	return 0;
}
int dir_delete(const char *dir_pathname) {
	return file_delete(dir_pathname);
}


unsigned long long get_dir_all_space(const char *dir_pathname) {
	int flag = 0;
	unsigned long long bsize = 0;
	unsigned long long blocks = 0;
	struct statfs fs;
	flag = statfs(dir_pathname, &fs);
	if(flag == -1) {
		gmsg("statfs failure.");
		return 0;
	}
	bsize = (unsigned long long)(fs.f_bsize);
	blocks = (unsigned long long)(fs.f_blocks);

	unsigned long long space = bsize * blocks;
	return space;
}
unsigned long long get_dir_avail_space(const char *dir_pathname) {
	int flag = 0;
	unsigned long long bsize = 0;
	unsigned long long availblocks = 0;
	struct statfs fs;
	flag = statfs(dir_pathname, &fs);
	if(flag == -1) {
		gmsg("statfs failure.");
		return 0;
	}
	bsize = (unsigned long long)(fs.f_bsize);
	availblocks = (unsigned long long)(fs.f_bavail);
	return bsize * availblocks;
}
int partition_mount(const char *dir_pathname, const char *partition_pathname, const char *fs_type) {
	int ret = 0;
	ret = mount(partition_pathname, dir_pathname,
				fs_type,
				0, NULL);
	if(ret != 0) {
		gmsg("mount failure:%s-%s-%s", partition_pathname, dir_pathname, fs_type);
		gmsg("errno:%d", errno);
		return -1;
	}
	gmsg("mount OK.");
	return 0;
}
int partition_unmount(const char *dir_pathname) {
	int ret = 0;
	ret = umount(dir_pathname);
	if(ret != 0) {
		gmsg("umount failure:%s", dir_pathname);
		gmsg("errno:%d", errno);
		return -1;
	}
	return 0;
}

