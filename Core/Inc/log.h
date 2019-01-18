/*
 * log.h
 *
 *  Created on: Jan 17, 2019
 *      Author: eug
 */

#ifndef CORE_INC_LOG_H_
#define CORE_INC_LOG_H_


void LogInit(void);

void lprint(const char * fmt, ...);
void Error_Handler(void);

#ifdef DEBUG
#define LOG_DEBUG lprint
else
#define LOG_DEBUG
#endif

#endif /* CORE_INC_LOG_H_ */
