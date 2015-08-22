/**
 * \file 	log.h
 * \brief	日志 和 调试.
 * \author	liuyong 120031860@qq.com
 *
 */

#ifndef __CAMERA_LOG_H__
#define __CAMERA_LOG_H__

#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <string.h>


void write_log(const char * fmt, ...);
void _write_log(const char * file, int line, const char * func, const char * fmt, ...);
void http_write_log(const char * file, int line, const char * func, const char * fmt, ...);


#define http_msg(fmt, args...)  do {	\
	http_write_log(__FILE__, __LINE__, __func__, fmt, ##args);	\
} while (0)



#define _gmsg(fmt, args...)  do {	\
	time_t t;	\
    struct tm *area;	\
    tzset();	\
    t = time(NULL);	\
    area = localtime(&t);	\
	fprintf(stderr, fmt, ##args);	\
	fprintf(stderr, "=======> File : %s, Line : %d, Func: %s, Time:%s\n",	\
		__FILE__, __LINE__, __func__,asctime(area));	\
	fflush(stderr);	\
} while (0)

#define __gmsg(fmt, args...)  do {	\
	_write_log(__FILE__, __LINE__, __func__, fmt, ##args);	\
} while (0)


#define GMSG 1
#define MSG_WRITE_LOG 1
#if GMSG	
	#if MSG_WRITE_LOG
	#define gmsg(fmt, args...) __gmsg(fmt, ##args)
	#else
	#define gmsg(fmt, args...) _gmsg(fmt, ##args)
	#endif
#else
#define gmsg(fmt, args...)
#endif


#define GERR 1
#define ERR_WRITE_LOG 1
#if GERR
	#if ERR_WRITE_LOG
	#define gerr(fmt, args...) __gmsg(fmt, ##args)
	#else
	#define gerr(fmt, args...) _gmsg(fmt, ##args)
	#endif 
#else
#define gerr(fmt, args...)
#endif


#define GDEBUG 1
#if GDEBUG
#define gdebug(fmt, args...)  _gmsg(fmt, ##args)
#else
#define gdebug(fmt, args...)
#endif

#define GDELAY 0
#if GDELAY
#define gdelay(fmt, args...)  _gmsg(fmt, ##args)
#else
#define gdelay(fmt, args...)
#endif


#define GREPORT 0
#if GREPORT
#define greport(fmt, args...)  _gmsg(fmt, ##args)
#else
#define greport(fmt, args...)
#endif

#define GQUERY 0
#if GQUERY
#define gquery(fmt, args...)  _gmsg(fmt, ##args)
#else
#define gquery(fmt, args...)
#endif

#define GWEB 0
#if GWEB
#define gweb(fmt, args...)  _gmsg(fmt, ##args)
#else
#define gweb(fmt, args...)
#endif





#endif

