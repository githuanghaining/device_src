/**
 * \file 	file.h
 * \brief	文件操作.
 * \author	liuyong 120031860@qq.com
 *
 */

#ifndef __FILE_H__
#define __FILE_H__

#include "typedef.h"
#include "list.h"

int file_exist(const char *pathname);
int file_create(const char *pathname);
int file_delete(const char *pathname);
int64b_t file_size(const char *pathname);
int file_alloc(const char *pathname, int size);
int dir_exist(const char *pathname);
int dir_create(const char *pathname);
int dir_delete(const char *dir_pathname);

/**
 * \brief 获取某个目录的最大磁盘空间
 *
 * \param[in] dir_pathname
 *
 * \return 返回空间大小，如果失败返回0
 */
unsigned long long get_dir_all_space(const char *dir_pathname);


/**
 * \brief 获取某个目录的最大磁盘可用空间
 *
 * \param[in] dir_pathname
 *
 * \return 返回可用空间大小，如果失败返回0
 */
unsigned long long get_dir_avail_space(const char *dir_pathname);


/**
 * \brief 磁盘挂载
 *
 * \param[in] dir_pathname
 * \param[in] partition_pathname
 * \param[in] fs_type
 *
 * \return 成功返回0，失败返回-1
 */
int partition_mount(const char *dir_pathname, const char *partition_pathname, const char *fs_type);

/**
 * \brief 磁盘卸载
 *
 * \param[in] dir_pathname
 *
 * \return 成功返回0，失败返回-1
 */
int partition_unmount(const char *dir_pathname);


#endif


