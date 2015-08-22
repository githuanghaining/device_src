#ifndef __LY_TIME_H__
#define __LY_TIME_H__

#include "typedef.h"


/**
 * \brief 程序启动到当前运行的时间，与系统时间无关
 *
 * \param[in] 	无
 * \param[out] 	无
 *
 * \return 当前时间，以秒为单位
 */
uint32b_t monotonic_seconds();

/**
 * \brief 程序启动到当前运行的时间，与系统时间无关
 *
 * \param[in] 	无
 * \param[out] 	无
 *
 * \return 当前时间，以毫秒为单位
 */
uint64b_t monotonic_mseconds();



/**
 * \brief 1970-1-1 0:0:0到现在的秒数，与系统时间有关
 *
 * \param[in] 	无
 * \param[out] 	无
 *
 * \return 当前时间，以秒为单位
 */
uint32b_t real_seconds();

/**
 * \brief 1970-1-1 0:0:0到现在的毫秒数，与系统时间有关
 *
 * \param[in] 	无
 * \param[out] 	无
 *
 * \return 当前时间，以毫秒为单位
 */
uint64b_t read_mseconds();

/**
 * \brief 设置系统时间
 *
 * \param[in] 	time_secs 1970-1-1 0:0:0到现在的秒数
 * \param[out] 	无
 *
 * \return 当前时间，以秒为单位
 */

int32b_t set_systime(uint32b_t time_secs);


/**
 * \brief 延迟等待
 *
 * \param[in] 	ms 以毫秒为单位的睡眠等待
 * \param[out] 	无
 *
 * \return 无
 */
void delay_mseconds(int32b_t ms);


#endif

