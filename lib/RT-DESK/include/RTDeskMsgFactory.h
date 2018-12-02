/**
*	@file	 RTDeskMsgFactory.h

* Copyright(C) 2013
*
* Prefix: RTDMSG_

* @Author:	Dr. Ramón Mollá Vayá
* @Date:	03/2016
* @Version: 2.0
*
*	@brief	 Definition of interface RTDeskMsgFactory.
*			 Provide methods to create new RTDesk user messages objects.
*           Its methods must be implemented on a child class to provide fully functionallity.
*           Used in RTDEeskMsgPool.
*			 Its behaviour corresponds to an Objects Factory of type RTDeskMsg.
*/


#ifndef RTDMSG_MESSAGE_FACTORY
#define RTDMSG_MESSAGE_FACTORY

#include <RTDeskMsg.h>

	/**
	 * @class RTDeskCMsgFactory
	 * Interface to provide methods to create new RTDesk Message objects.
	 * Represents a Factory of generic RTDesk Messages objects.
	 */
class RTDESK_API RTDeskMsgCFactory
{
public:

	/**
		* @fn     CreateNewMsg
		* @param  int MsgType Type of RTDESK_CMsg to be created.
		* @return Pointer to the new RTDESK_CMsg created.
		* @brief  Creates a new RTDESK_CMsg of the specified type.
		*         Pure Virtual Function. It must be redefined in the child user created class.		 
		*/
	virtual RTDESK_CMsg* CreateNewMsg(int MsgType) = 0; // adding = 0 makes the function pure virtual. Otherwise it is necessary to implement it.
};
#endif