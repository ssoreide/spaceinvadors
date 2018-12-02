/**
 * RRTimer.h : Class header for the Real Time Timers

 * @Prephix = RTT_

 * @Author: Ramón Mollá
 * @version: 2.1
 * @Date:	07/2014

 * Creative Commons: Attribution-NonCommercial 3.0 Unported (CC BY-NC 3.0) 2012-10 Valencia
 *
 * Update:
 * Date:
 * Version:
 * Changes:
 */

#ifndef RTTIMER_H
#define RTTIMER_H

#include <OS.h>

//#define RTT_MM_COUNTERS
#define RTT_TIME_STAMP_ASM
#define RTT_NO_SAMPLING_FREQUENCYf  -1.0
#define RTT_NO_SAMPLING_FREQUENCY	-1

#define DLL_EXPORTS

#ifdef	OS_MSWINDOWS
	#include <windows.h>
	#include <stdint.h>
	#define RTT_MAXTIME INT64_MAX
	#define RTT_Time long long
	
#elif	defined(OS_LINUX)
	#include <limits.h>
	#define RTT_MAXTIME LONG_MAX
	#include <sys/time.h> 
	#include <time.h>

	#ifdef RTT_TIME_STAMP_ASM
		#define RTT_Time long long
	#elif defined (RTT_MM_COUNTERS)
		#define RTT_Time timeval
	#endif

#elif	defined(OS_OSX)
#elif	defined(OS_ANDROID)
#endif

typedef unsigned char		RTT_Shorts	[8];
typedef unsigned short int	RTT_Ints	[4];
typedef unsigned long		RTT_Longs	[2];

#define RTT_Timems double


typedef struct
{
	RTT_Time	SamplingFrequency;
	RTT_Timems	SFms,				///Sampling frequency in ms. SFms = SamplingFrequency*0.001
				msXTick;			///Inverse of frequency = period, time lasted for a single closk tick msXTick = 1/SFms
} HRTM_SF;

class HRT_API cRTTimer
{
	///Performance attributes
private:
	///Processor sampling frequency for this given performance counter. Units: System Clock Ticks per second	
	RTT_Time	Time;

	HRTM_SF	*SF;
	
public:
	//Methods
	inline cRTTimer	()	{}
	inline ~cRTTimer()	{}

	inline void		SetSF(HRTM_SF	*SFreq) { SF = SFreq; } ///<Sets the sampling frequency and derived values obtained outside the RTTimer. This is in order to avoid time penalties.
	inline HRTM_SF* GetSF()					{ return SF ; } ///<Gets the sampling frequency and derived values obtained outside the RTTimer. This is in order to avoid time penalties.

	inline RTT_Time GetSamplingFreq		()				{ return SF->SamplingFrequency;}
	inline RTT_Time *GetRefSamplingFreq	()				{ return &SF->SamplingFrequency; }

	///Time in ms
	inline RTT_Timems	Ticks2ms		(RTT_Time T)	{ return T*SF->msXTick; }
	inline RTT_Time		ms2Ticks		(RTT_Timems ms)	{ RTT_Time aux; aux = SF->SFms*ms; return aux; }

	inline RTT_Timems GetSamplingFreqms	()				{ return SF->SFms; }
	//Sets in the T parameter the current real Time value in ticks
	inline RTT_Time GetRealTime()
	{
	#ifdef RTT_MM_COUNTERS
		#ifdef	OS_MSWINDOWS
			QueryPerformanceCounter((LARGE_INTEGER *)&Time);
		#elif	defined(OS_LINUX)
			gettimeofday((RTT_Time *)&Time, NULL);
		#elif	defined(OS_OSX)
		#elif	defined(OS_ANDROID)
		#endif
	#elif defined(RTT_TIME_STAMP_ASM)
		RTT_Time *Aux = &Time;
		//Intel or AMD assembler
		
		#ifdef	OS_MSWINDOWS
				__asm
				{
					rdtsc
					mov ebx, Aux
					mov [ebx], eax
					mov [ebx+4], edx
				}
		#elif	defined(OS_LINUX)
					asm("rdtsc");
					asm("mov ebx,Aux");
					asm("mov [ebx], eax");
					asm("mov [ebx+4], edx");

		#elif	defined(OS_OSX)
		#elif	defined(OS_ANDROID)
		#endif
	#endif
	return Time;
	}
};
#endif