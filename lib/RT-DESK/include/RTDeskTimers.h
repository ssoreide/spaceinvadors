/**
 * RTDeskTimers.h: Description of the global performance counters needed for testing RTDESK
 *
 * Copyright(C) 2013
 *
 * Prefix: RTDT_

 * @Author:	Dr. Ramón Mollá Vayá
 * @Date:	02/2013
 * @Version: 2.0
 *
 * Update:
 * Date:	
 * Version: 
 * Changes:
 *
 */

#ifndef RTDESK_TIMER_H
#define RTDESK_TIMER_H

#include <RTDeskTime.h>

typedef enum{
	//Insert here as many timers as needed
	RTDT_DEFAULT,
	RTDT_GLOBAL,
	RTDT_SYSTEM,
	RTDT_MAX_TIMERS
}RTDESK_TIMERS;

typedef enum
{
	RTDT_INMEDIATELY, 	//When delivering events just right now. Maximun priority and Store Slack Time is allowed
	RTDT_1MS,			//1 ms
	RTDT_120FPS,		//120 frames per second
	RTDT_100FPS,		//100 frames per second
	RTDT_60FPS,			//60 frames per second
	RTDT_30FPS,			//30 frames per second
	RTDT_25FPS,			//25 frames per second
	RTDT_12FPS,			//12 frames per second
	RTDT_10FPS,			//10 frames per second
	RTDT_1HZ,			//Once per second
	RTDT_MAX_PREDEFINED_TIMES
} RTDT_PREDEFINED_TIMES;

extern HRT_String	RTDT_TimerNames[RTDT_MAX_TIMERS];
extern RTDESK_TIME	RTDT_PredefinedTimes[RTDT_MAX_PREDEFINED_TIMES];

void RTDT_InitPredefinedTimes(cHRTimer *Timer);

#endif
