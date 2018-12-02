/**
 * RTDeskEngine.h: The core engine for RTDESK
 *
 * Copyright(C) 2013
 *
 * Prefix: RTDESK_

 * @Author:	Dr. Ramón Mollá Vayá
 * @Date:	18/5/2016
 * @Version: 2.0
 *
 * Update:
 * Date:	
 * Version: 
 * Changes:
 *
 */

#ifndef RTDESK_ENGINE_H
#define RTDESK_ENGINE_H

#include <RTDeskMsgFactory.h>

class RTDESK_CMsgPoolManager;
class RTDESK_CMsgDispatcher;
class cHRTimerManager;

class RTDESK_API RTDESK_CEngine
{
	HRT_String		Version;
	void			SetVersion();

	cHRTimer		*SystemClock;	///<Real Time Clock

	RTDESK_CMsgPoolManager	*MsgPoolManager;
	RTDESK_CMsgDispatcher	*MsgDispatcher;

	cHRTimerManager			*HRTimerManager;

public:

	//Constructor
	RTDESK_CEngine	();
	inline ~RTDESK_CEngine	(){Reset();};

	void		Reset		();
	bool		StartUp		();

	inline void ShutDown	(){Reset();}
	void		Delay		(double lMilliseconds);
	
	//Getters and Setters
	RTDESK_CMsgDispatcher	*GetMsgDispatcher();
	void					 SetMsgDispatcher(RTDESK_CMsgDispatcher	* MSGD);

	//Time management
	void		SynchSim2RealTime	(RTDESK_TIME Ticks);
	void		SynchSim2RealTime	(double ms);
	
	void		SetStoreSlackTime	(RTDESK_TIME SlackTime);
	void		SetDeliverSlackTime	(RTDESK_TIME SlackTime);

	bool		SetMaxMsgTypes		(unsigned int MsgTypes);
	void		SetMsgType			(unsigned int MsgType, unsigned int BunchSize);	///<Set the parameters of a given message
	inline void	SetMsgType			(unsigned int MsgType){SetMsgType(MsgType, 1);}	///<Set the parameters of a given message

	RTDESK_TIME	Simulate			();
	void		EndSimulation		();

	void		InitTimeManager		();

	void		SetMsgFactory		(RTDeskMsgCFactory *MF);
};
#endif