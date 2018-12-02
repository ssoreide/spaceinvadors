/**
 * HRTimer.h : Class header for the High Resolution Timers

 * @Prephix = HRT_

 * @Author: Ramón Mollá
 * @version: 2.0
 * @Date:	12/2013
 * Creative Commons: Attribution-NonCommercial 3.0 Unported (CC BY-NC 3.0) 2012-10 Valencia
 *
 * Update:
 * Date:
 * Version:
 * Changes:
 */

#ifndef HRTIMER_H
#define HRTIMER_H

#include <RTTimer.h>

#define HRT_Time	RTT_Time
#define HRT_Timems	RTT_Timems

#ifdef	OS_MSWINDOWS
#elif	defined(OS_LINUX)
#elif	defined(OS_OSX)
#elif	defined(OS_ANDROID)
#endif

//64 bits constants
#define HRT_TIME_INVALID	-1LL
#define HRT_NOTIME			 0LL
#define HRT_INMEDIATELY		 0LL

typedef enum
{
	HRT_INACTIVE,	///The HRT is not counting now. State reached just after EndCounting(); is invoked
	HRT_ACTIVE,		///The HRT is counting now. State reached just after InitCounting(); is invoked
	HRT_MAX_STATES	///Amount of different states a HRT can reach
} HRT_STATES;

class HRT_API cHRTimer: public cRTTimer
{
	HRT_String Name;

protected:

	HRT_STATES State;

	///Performance attributes

	HRT_Time	InitialCounter,	///<Initial performance counter value at the very beginning of the measured process. Units: System Clock Ticks
				FinalCounter,	///<Final performance counter value at the very end of the measured process. Units: System Clock Ticks

	///Statistical derived values
				Accumulated,	///<Total performance counter values accumulated during every measured process. Units: System Clock Ticks
								///The same use as Accumulatedms but in ticks. Take into account that the amount of ticks used to perform a computational task 
				AccumulatedACPI,///<remains always equal even if the system clock frequency changes, but not time consumed.
				LastPeriod,		///<Performance counter values accumulated during the last measured process. Units: System Clock Ticks
				MaxPartial,		///<Maximun partial period detected during every measured process. Units: System Clock Ticks
				MinPartial,		///<Maximun partial period detected during every measured process. Units: System Clock Ticks
				AlarmPeriod;	///<Total Amount of time to wait from now on until the alarm sounds

	unsigned int	Periods;		///<Amount of times a period has been accumulated

public:
	//Methods
	cHRTimer	();
	//~cHRTimer	() {}

	//Ticks management
	void			ResetSamplingFrequency	(HRTM_SF *SF);
	inline void		EndCounting				()	{FinalCounter = GetRealTime(); LastPeriod = FinalCounter - InitialCounter;}
	inline HRT_Time TicksUntilNow			()	{EndCounting(); return LastPeriod;}
	inline HRT_Time TotalTicksUntilNow		()	{HRT_Time T; TicksUntilNow(); T = Accumulated + LastPeriod; return T;}
	inline void		Accumulate				()	{Accumulated += LastPeriod; Periods++;}
	inline void		AccumulateUntilNow		()	{Accumulated += TicksUntilNow(); Periods++;InitCounting	();}
	inline void		ResetAccumulate			()	{Accumulated = 0; Periods = 0; }
	inline void		InitCounting			()	{InitialCounter = GetRealTime(); FinalCounter = InitialCounter; }
	inline void		Start					()	{InitCounting(); Activate();}

	//Tunning the clock
	inline void		AdvanceTime				(HRT_Time T)	{ InitialCounter += T; }	///< Moves forward time on the InitialCounter
	inline void		DelayTime				(HRT_Time T)	{ InitialCounter -= T; }	///< Moves backward time on the InitialCounter

	inline void		ResetName				()
	{ 
		#ifdef HRT_STL
			Name.clear();
		#else
			Name.Empty();
		#endif
	}

	inline void		Reset()
	{
		AccumulatedACPI	= HRT_NOTIME;
		InitialCounter	= HRT_NOTIME;
		FinalCounter	= HRT_NOTIME;
		Accumulated		= HRT_NOTIME;
		LastPeriod		= HRT_NOTIME;
		MaxPartial		= HRT_NOTIME;
		DisableAlarm();

		Periods			= 0;
		MinPartial		= RTT_MAXTIME;

		Start	();
	}

	void UpdateMinMax();	///<Updates the statistical private attributes MaxPartial and MinPartial

	///Accessing to private attributes for read only mode
	inline HRT_Time GetAccumulated		()	{return Accumulated;}
	inline HRT_Time GetAccumulatedACPI	()	{return AccumulatedACPI;}
	inline HRT_Time GetLastPeriod		()	{return LastPeriod;}
	inline HRT_Time GetMaxPartial		()	{return MaxPartial;}
	inline HRT_Time GetMinPartial		()	{return MinPartial;}
	inline unsigned int	 GetPeriods		()	{return Periods;}

	///Next computations are multiplied by 1000 ms in a second
	inline HRT_Timems GetAccumulatedms	()	{ return Ticks2ms(Accumulated); }
	inline HRT_Timems GetLastPeriodms	()	{ return Ticks2ms(LastPeriod); }
	inline HRT_Timems GetMaxPartialms	()	{ return Ticks2ms(MaxPartial); }
	inline HRT_Timems GetMinPartialms	()	{ return Ticks2ms(MinPartial); }

	//Alarms
	inline void			SetAlarm		(HRT_Time A)	{ AlarmPeriod = A; ResetAlarm();}
	inline void			SetAlarm		(HRT_Timems A)	{ SetAlarm(ms2Ticks(A)); }
	inline void			SetAlarmms		(HRT_Timems A)  { SetAlarm(ms2Ticks(A)); }
	inline HRT_Time		GetAlarmPeriod	()				{ return AlarmPeriod; }
	inline HRT_Timems	GetAlarmPeriodms()				{ return Ticks2ms(AlarmPeriod); }
	inline bool			IsSounding		()				{ if (IsActive()) { EndCounting(); return AlarmPeriod < LastPeriod; } else return false; }
	inline void			StartSounding	()				{ FinalCounter = GetRealTime(); InitialCounter = FinalCounter - AlarmPeriod; Activate();}
	inline void			ResetAlarm		()				{ InitCounting(); Activate(); }
	inline void			AdvanceOneAlarmPeriod()			{ AdvanceTime(AlarmPeriod); }	///< Do not reset the alarm. It discounts one alarm period. Perhaps it may go on sounding
	inline void			DisableAlarm	()				{ DeActivate(); }
	inline void			EnableAlarm		()				{ Activate(); }

	//Miscelanea
	void				SetName		(HRT_String N);
	HRT_String			GetName		();

	inline bool			IsActive	()				{ return	HRT_ACTIVE == State;}
	inline bool			IsInActive	()				{ return	HRT_INACTIVE == State; }
	inline void			SetState	(HRT_STATES S)	{ State = S; }
	inline HRT_STATES	GetState	()				{ return State; }

	inline void			Activate	()				{State = HRT_ACTIVE;}
	inline void			DeActivate	()				{State = HRT_INACTIVE;}
};
#endif