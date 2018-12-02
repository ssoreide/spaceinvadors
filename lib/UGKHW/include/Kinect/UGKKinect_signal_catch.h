/**	
*	Methods for using a kinect device using framework OpenNI & midleware NITE 1.3
*	Prefix: KNT_
*	@Author: Jordi Mansanet 
*	versión 2011-12
*	@NewVersion Francisco Romero 2014-10 - UGK_API conversion and refactoring to NiTE v2.2
**/
#ifdef CHW_USE_KINECT_1.3

#ifndef __SIGNAL_CATCH_H__
#define __SIGNAL_CATCH_H__

#include <XnPlatform.h>

#if XN_PLATFORM == XN_PLATFORM_WIN32

#define CatchSignals(x)

#else
// Stores pointer to bSignalWasCaught, and starts catching signals
// when a signal is caught, *bSignalWasCaught will be set to true
void CatchSignals(XnBool* bSignalWasCaught);
#endif

#endif

#endif //CHW_USE_KINECT_1.3