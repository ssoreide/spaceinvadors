/**
 * HRTimerManager.cpp : Class methods declaration for the High Resolution Timers Manager

 * @Prephix = HRTM_	Comes from High Resolution Timer Manager

 * @Author: Ramón Mollá
 * Version: 2.0
 * Creative Commons: Attribution-NonCommercial 3.0 Unported (CC BY-NC 3.0) 2012-10 Valencia
 *
 * Update:	
 * Date:	

 * Changes:
 */

#include <HRTimerManager.h>

//Mind the order in which HRTM errors are defined on the HRTM_ERRORS enum type
HRT_String HRTM_ErrorMsg[HRTM_MAX_ERRORS] =
{
	"No error",									//Corresponds to HRTM_NO_ERROR error
	"No timer has been possible to be created"	//Corresponds to HRTM_NO_TIMERS_CREATED error
};

/**
* @fn void cHRTimerManager::ResetSampFreq(void)
* Performs a reset of the sampling frequency by a blocking mode
*/
void cHRTimerManager::ResetSamplingFrequencyb(void)
{
	LARGE_INTEGER SFreq;

#ifdef	OS_MSWINDOWS
	QueryPerformanceFrequency(&SFreq);
#ifdef RTT_TIME_STAMP_ASM
	LARGE_INTEGER	TS, TS1S;	//Time Stamp and TS plus one second
	cHRTimer HRTimer;

	QueryPerformanceCounter(&TS);
	HRTimer.Start();
	for (TS1S.QuadPart = TS.QuadPart + SFreq.QuadPart; TS.QuadPart < TS1S.QuadPart; QueryPerformanceCounter(&TS));
	SetSamplingFrequency(HRTimer.TicksUntilNow());
#elif
	SetSamplingFrequency (SFreq.QuadPart);
#endif
#elif	defined(OS_LINUX)
#elif	defined(OS_OSX)
#elif	defined(OS_ANDROID)
#endif
}

/**
* @fn void cHRTimerManager::ResetSamplingFrequency(bool fast)
* @param bool fast Sets if the time is going to be calculated blocking (false) or first an coarse approximation and later a fine one using a non blocking mode
* Gets the new clock sampling frequency by a blocking method
*/
void cHRTimerManager::ResetSamplingFrequency(bool fast)
{
	LARGE_INTEGER SFreq, TS, TS1S;	//Time Stamp and TS plus one second
	cHRTimer HRTimer;

	if (fast)
	{
#ifdef	OS_MSWINDOWS
		QueryPerformanceFrequency(&SFreq);
#ifdef RTT_TIME_STAMP_ASM
		//Divide the sampling frequency by three orders of magnitud (1024), so the sampling frequency has an error three orders of magnitud higher
		//This is a fast first coarse approximation 
		SFreq.QuadPart = SFreq.QuadPart >> 12;
		QueryPerformanceCounter(&TS);
		HRTimer.Start();
		for (TS1S.QuadPart = TS.QuadPart + SFreq.QuadPart; TS.QuadPart < TS1S.QuadPart; QueryPerformanceCounter(&TS));
		SetSamplingFrequency (HRTimer.TicksUntilNow() << 12);
		//Now that there is a coarse approx. Tune the sampling freq. completely meanwhile
		ResetSamplingFrequencynb();
#elif 
		SetSamplingFrequency(SFreq.QuadPart);
#endif
#elif	defined(OS_LINUX)
#elif	defined(OS_OSX)
#elif	defined(OS_ANDROID)
#endif
	}
	else
		ResetSamplingFrequencyb();
}

/**   
* @fn DWORD WINAPI HRTM_ResetSF(LPVOID TimerManager) 
* Gets the new clock sampling frequency
* Thread for nonblocking call
*/
DWORD WINAPI HRTM_ResetSF(LPVOID TimerManager) 
{
	((cHRTimerManager*)TimerManager)->ResetSamplingFrequencyb();
	return 0;
}

/**
void cHRTimerManager::ResetSamplingFrequencynb(void)
* Gets the new clock sampling frequency without blocking the main program one second in case of using assembler timing.
*/
void cHRTimerManager::ResetSamplingFrequencynb(void)
{
	HANDLE  hThread;
	DWORD   dwThreadId;

	//Creates a thread in order to avoid one second blocking of the program
	hThread = CreateThread( 
		NULL,               // default security attributes
		0,                  // use default stack size  
		HRTM_ResetSF,		// thread function name
		this,				// argument to thread function 
		0,                  // use default creation flags 
		&dwThreadId);		// returns the thread identifier 

	//Verifies that everything is fine
	if (NULL == dwThreadId) 
		ResetSamplingFrequencyb(); //Blocking version
}

void cHRTimerManager::SetTimersName(HRT_String TimerNames[])
{
	unsigned int  i;

	for (i=0;i<Timers.size();i++)
		Timers[i].SetName(TimerNames[i]);
}

void cHRTimerManager::SetTimersName(HRT_String TimerNames[], int FirstIndex, int Length)
{
	int Ti,		//Timers index
		TNi,	//Timer Names index
		End;

	End = FirstIndex + Length;
	for (Ti = FirstIndex, TNi = 0; Ti<End; Ti++, TNi++)
		Timers[Ti].SetName(TimerNames[TNi]);
}


HRT_String cHRTimerManager::ErrorMsg(HRTM_ERRORS E)	{ return HRTM_ErrorMsg[E]; };

int cHRTimerManager::CreateTimers(unsigned int T)
{
	unsigned int	Size = Timers.size(),
					NewSize;

	if (Size == T) return Size;	//There is nothing to do. Demanded as many timers as existed
	Timers.resize(T);
	NewSize = Timers.size();

	if (Size > T)
		if (NewSize == T) return T;	//Size reduced correctly to the amount of timers demanded
		else 
			{
				if (NewSize > Size)
					//Associate the Timers Manager Sampling frequency to every new HRTimer
					for (; Size < NewSize; Size++) Timers[Size].SetSF(SF);
				return HRTM_TIMER_BAD_CREATED;	//There is a different number of timers than demanded
			}			 
	else //Size < T. Demanded more timers than existing
		if (NewSize <= Size) return HRTM_TIMER_BAD_CREATED;	//No timers created and/or additionally some were destroyed
		else //NewSize > Size
		{
			//Associate the Timers Manager Sampling frequency to every new HRTimer
			for (; Size < NewSize; Size++) Timers[Size].SetSF(SF);
			if (NewSize == T)
				return NewSize;	//Everything fine
			else if (NewSize < T)
				return HRTM_NOT_ENOUGH_TIMERS_CREATED;	//Not enough timers created. Perhaps it is because there was not enough dinamic memory available
			else //NewSize > T. Created more timers than demanded
				return  HRTM_TIMER_BAD_CREATED;
		}
}

unsigned int cHRTimerManager::NewTimer()
{
	unsigned int i,
		Size = Timers.size();

	for (i = 0; i < Size; i++)
	if (Timers[i].IsInActive())
	{
		Timers[i].Activate();
		return i;
	}

	Timers.resize(++Size); 
	Timers[i].SetSF(SF);
	return i;
}

cHRTimer* cHRTimerManager::GetTimer(unsigned int T)
{
	return &Timers[T];
}

