/**
 * RTDeskEntity.cpp: Basic class Entity declarations
 *
 * Copyright(C) 2013
 *
 * Prefix: RTDE_

 * @Author: Dr. Ramón Mollá Vayá
 * @Date:	02/2013
 * @Version: 2.0
 *
 * Update:	Verify that hierarchy is encapsulated
 * Date:	15/10/2012
 * Version:	2.0
 * Changes:
 */

#ifndef RTDESK_ENTITY_H
#define RTDESK_ENTITY_H

class RTDESK_CMsgDispatcher;
class RTDESK_CEngine;

#include <RTDeskMsg.h>

class RTDESK_API RTDESK_CEntity
{
	RTDESK_CMsgDispatcher	*MsgDispatcher;	///< Memory Manager to whom this entity can ask for an enveloppe to send a message

public:

	inline RTDESK_CEntity	(){MsgDispatcher = NULL;}
	inline ~RTDESK_CEntity	(){}

	RTDESK_CMsg *GetMsgToFill(unsigned int MsgType);
	RTDESK_TIME	ms2Ticks(double ms);
	double		Ticks2ms(RTDESK_TIME ticks);
	
	/**
	* @fn void SendMsg(RTDESK_CMsg *pMsg, RTDESK_CEntity *pReceiver, RTDESK_TIME DeltaTime)
	* Establishes Keys delays. This sets the minimun repeating period of a key.
	* @param[in] void *pMsg. The content of the message.
	* @param[in] RTDESK_CEntity *pReceiver. The entity that is going to receive the message.
	* @param[in] RTDESK_TIME DeltaTime. When the message has to be sent in simulation time. Time relative from current simulation time. Internally it is transformed into an absolute time
	*/
	void SendMsg(RTDESK_CMsg *pMsg, RTDESK_CEntity *pReceiver, RTDESK_TIME DeltaTime);
	inline void	SendMsg	(RTDESK_CMsg *pMsg, RTDESK_CEntity *pReceiver, double DeltaTimems)	{SendMsg(pMsg, pReceiver, ms2Ticks(DeltaTimems));}

	/**
	* @fn void SendMsg(RTDESK_CMsg *pMsg, RTDESK_CEntity *pReceiver)
	* Sender sends inmediately a msg to the reciver. The msg is not managed by the system. It is only managed by both the sender and the receiver alone
	* @param[in] void *pMsg. The content of the message.
	* @param[in] RTDESK_CEntity *pReceiver. The entity that is going to receive the message.
	*/
	void SendMsg(RTDESK_CMsg *pMsg, RTDESK_CEntity *pReceiver);

	inline void	SendSelfMsg	(RTDESK_CMsg *pMsg, RTDESK_TIME DeltaTime)	{SendMsg(pMsg, this, DeltaTime);}
	inline void	SendSelfMsg	(RTDESK_CMsg *pMsg, double DeltaTimems)		{SendSelfMsg(pMsg, ms2Ticks(DeltaTimems));}

	//The programmer that makes all objects in the virtual world a derivated class form this one 
	//has to redefine what to do when receiving a msg
	virtual void	ReceiveMessage		(RTDESK_CMsg *pMsg) = 0;

	RTDESK_CMsgDispatcher *	GetMsgDispatcher();
	void	SetMsgDispatcher(RTDESK_CMsgDispatcher *D);
	void	SetMsgDispatcher(RTDESK_CEngine *E);

	bool DeleteMsg(RTDESK_CMsg *pMsg);
};

#endif
