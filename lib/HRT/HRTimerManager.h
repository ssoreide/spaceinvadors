/**
 * @file HRTimerManager.h
 *	Class header for the High Resolution Timers Manager

 * @Prephix = HRTM_	Comes from High Resolution Timer Manager

 * @Author: Ramón Mollá
 * @version: 2.0
 * @Date:	02/2013

 * Creative Commons: Attribution-NonCommercial 3.0 Unported (CC BY-NC 3.0) 2012-10 Valencia
 *
 * Update:	
 * Date:	
 * Changes:
 */

#ifndef HRTIMERM_H
#define HRTIMERM_H

#include <vector>
#include <HRTimer.h>

#define HRTM_NO_SAMPLING_FREQUENCY -1
#define HRTM_NO_TIMER_CREATED -1
#define HRTM_TIMER_BAD_CREATED -2
#define HRTM_NOT_ENOUGH_TIMERS_CREATED -3

#define HRTM_FAST true
#define HRTM_SLOW false

/**
	\enum HRTM_ERRORS
	\brief Different errors that mey happen when managing HR Timers
*/
typedef enum 
{
	HRTM_NO_ERROR,
	HRTM_NO_TIMERS_CREATED,
	HRTM_MAX_ERRORS
} HRTM_ERRORS;

/**
	\class cHRTimerManager
	\brief Manages an array of High Resolution Timers.
*/
class HRT_API cHRTimerManager
{
protected:
	/// Hardware clock sampling frequency. This is the common sampling frequency that all timers
	/// managed by this manager will share among them
	std::vector<cHRTimer>	Timers;
	HRTM_SF	*SF;

public:
	//Methods
	inline cHRTimerManager(void)	{ 
		DestroyAllTimers();
		SF = new HRTM_SF();

		SF->SamplingFrequency = HRTM_NO_SAMPLING_FREQUENCY;
		SF->SFms			  = HRTM_NO_SAMPLING_FREQUENCY;
		SF->msXTick			  = HRTM_NO_SAMPLING_FREQUENCY;
	}
	inline ~cHRTimerManager() { DestroyAllTimers(); delete SF; }

	void			ResetSamplingFrequencynb(void);	//Non blocking version
	void			ResetSamplingFrequencyb (void); //Blocking version
	
	/**
	*	\fn int	CreateTimers (unsigned int T)
	*	Creates T timers in total
	*	\param[in] T The amount of timers to have in total containing the amount that existed before
	*	returns The amount of timers available. Returns HRTM_NO_TIMER_CREATED if there is an error or if no timer has been created
	*/
	int				CreateTimers	(unsigned int T);
	inline int		CreateMoreTimers(unsigned int T) {return CreateTimers(Timers.size()+T); }
	unsigned int	NewTimer		();

	void			SetTimersName	(HRT_String TimerNames[]);	///<Assign names to all timers. Premise: TimerNames.length == Timers.size()
	void			SetTimersName	(HRT_String TimerNames[], int FirstIndex, int Length);	///<Assign names to the first length timers starting from the FirstIndex timer, included

	HRT_String		ErrorMsg(HRTM_ERRORS E);

	inline void		DestroyAllTimers			()	{Timers.clear();}
	inline bool		SamplingFrequencyAvailable	()	{return HRTM_NO_SAMPLING_FREQUENCY != SF->SamplingFrequency;}

	///Gets the performance frequency and stores it in an private attribute.
	void			ResetSamplingFrequency		(bool fast);

	inline void		ResetAllTimers				(void)	{for (unsigned int i = 0; i < Timers.size(); i++) Timers[i].Reset();}

	inline void		SetSamplingFrequency(RTT_Time SFreq) {
		SF->SamplingFrequency = SFreq;
		SF->SFms			  = SF->SamplingFrequency*0.001;
		SF->msXTick			  = 1.0 / SF->SFms;
	}

	inline RTT_Time GetSamplingFrequency()					{ return SF->SamplingFrequency; }
	inline HRTM_SF* GetSF() { return SF; }

	cHRTimer *GetTimer(unsigned int T);
	inline cHRTimer *GetNewTimer		()	{ return GetTimer(NewTimer()); };
	inline unsigned int GetTimerAmount	()	{ return Timers.size(); };
};
#endif
