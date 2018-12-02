/**	Definition of the class CHardware. Base class for all hardware in the system

*	Prefix: CHW_

*	@author Ramon Molla
	@author David Peris
*	@version 2015-05
*/

#ifndef CHW_HARDWARE_LIST
#define CHW_HARDWARE_LIST

//#define CHW_USE_KINECT
//#define CHW_USE_LEAP
//#define CHW_USE_WIIMOTE

#include <UGKAudioHardware.h>
#include <UGKGameController.h>
#include <UGKGraphicsCard.h>
#include <UGKJoystick.h>
#include <UGKKeyboard.h>
#include <UGKMouse.h>

#ifdef CHW_USE_WIIMOTE
#include <UGKWiimote.h>
#endif

#ifdef CHW_USE_LEAP
#include <UGKLeap.h>
#endif

#ifdef CHW_USE_KINECT
#include <UGKKinect.h>
#endif

#include <UGKWebCam.h>

#endif