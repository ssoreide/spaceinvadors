/*
RTDESK means Game Discrete Event Simulation Kernel. It came from a sw called DESK used for discrete 
events simulation in general systems based on queues, works, marks and so on.
This kernel has a dispatcher that worked only in simulation time. It weas modified in order to get 
synchronized to real time. As a real time simulation kernel it may be user 
with environments like virtual and augmented reality applications and video games, but not only.

DESK was developped by Inma Garc�a Garc�a (ingarcia@dsic.upv.es) when developping her master thesis 
at the Universitat Polit�cnica de Val�ncia following directives from Ram�n Moll� Vay� (rmolla@dsic.upv.es). 
Lately it was upgraded to support real time generating the RTDESK. RTDESK is the result of 
Dr. Inma's PhD. thesis under the direction of Dr. Ram�n Moll�

Currently it is being used at the IARFID master studies (http://www.popinformatica.upv.es/iarfid.html) 
supported by the Computer Systems and Computation Department at the Universitat Polit�cnica de Val�ncia.
In 2012, it was refactored and doxygened by Dr. Ram�n Moll� in order to be used at 

We also would like to thank the researcher Antonio Barella (tbarella@dsic.upv.es) his collaboration with 
us during the execution of the research project funded by the Generalitat Valenciana ref, OCYT CTIDIB/2002/344. 
His collaboration was really useful for the development and adaptation of this software to the Fly3D game 
kernel in order to extract real results and confirm theoretical conclusions.

Copyright:
Dr. Ram�n Moll�
*/

/**
 * RTDeskDefCom.h: Common definitions and constants for RTDESK
 *
 * Copyright(C) 2013
 *
 * Prefix: RTDESK_

 * @Author:Dr. Ram�n Moll� Vay�
 * @Date:	02/2013
 * @Version: 2.0
 *
 * Update:
 * Date:	
 * Version: 
 * Changes:
 *
 */

#ifndef RTDESK_DEF_COM_H
#define RTDESK_DEF_COM_H

#include <RTDeskTime.h>

#define RTDESK_USE_ENGINE
//For exporting functionality through a lib file
#define RTDESKENGINE_LIB

#ifdef RTDESKENGINE_LIB
#define RTDESK_API 
#else	//DLL
	// The following ifdef block is the standard way of creating macros which make exporting 
	// from a DLL simpler. All files within this DLL are compiled with the RTDESKENGINE_EXPORTS
	// symbol defined on the command line. This symbol should not be defined on any project
	// that uses this DLL. This way any other project whose source files include this file see 
	// RTDESK_API functions as being imported from a DLL, wheras this DLL sees symbols
	// defined with this macro as being exported.

	//For exporting functionality through a dll file
	//#define RTDESKENGINE_EXPORTS

	#ifdef RTDESKENGINE_EXPORTS
	#define RTDESK_API __declspec(dllexport)
	#else
	#define RTDESK_API __declspec(dllimport)
	#endif
#endif

///Time slot that discretizes the time in small slices so that if an event 
///is going to happen within a slack time from now on, it is delivered before passing the control outside RTDESK. 
///If the event is going to be stored in the event list but it is going to happen within a slack time from now on, it is delivered without storing it in the event list
//For the configuration of the msg dispatcher
#define RTDESK_NO_SLACK_TIME			RTDESKT_NOTIME
#define RTDESK_SLACK_TIME				RTDESKT_FASTEST

#ifdef OS_Windows
	#define itoa _itoa
#elif	defined(OS_LINUX)
#elif	defined(OS_OSX)
#elif	defined(OS_ANDROID)
#endif

//Performance implementation
//#define RTDL_TREE_LIST 0
#define RTDL_LIST2D 1
#define RTDL_Shorts 0
//#define RTDL_Ints	1

#endif
