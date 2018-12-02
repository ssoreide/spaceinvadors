/**	UGKWiimote.h - Wrapper that manages a single Wiimote

*	Prefix: CWM_
*	@author Ramon Molla, Imanol Fraile
*	@version 2015-05
*/
//#include "Copyright.h"

#ifndef CWM_WIIMOTE
#define CWM_WIIMOTE

#include <UGKHardware.h>

#define UGKWM_ACTIVATE		1
#define UGKWM_DEACTIVATE	0

#define UGKWM_WIIMOTE_DEFAULT_TIMEOUT 5

#define UGKWM_WII_USE

#ifdef UGKWM_WII_USE
#include <wiiuse.h>
#define CWM_
#define UGKWM_WiiMote		wiimote

#define UGKWM_BUTTON_PLUS   WIIMOTE_BUTTON_PLUS
#define UGKWM_BUTTON_MINUS  WIIMOTE_BUTTON_MINUS

#define POLLING_EVENT				   WIIUSE_EVENT
#define POLLING_STATUS				   WIIUSE_STATUS
#define POLLING_DISCONNECT			   WIIUSE_DISCONNECT
#define POLLING_UNEXPECTED_DISCONNECT  WIIUSE_UNEXPECTED_DISCONNECT
#endif

namespace UGK
{
	/**
	*	\class CWiiMote
	*	Manages a single wiimote
	*/

	class UGK_API CWiiMote : public CHardware
	{	

	public:

		int uid; // Wiimote unique identifier
		
		#ifdef UGKWM_WII_USE

		UGKWM_WiiMote* WiimoteHW;

		///< Constructor of the class

		CWiiMote(int uid);
		///< Destructor of the class
		~CWiiMote (){};

		//Virtual methods redefined
		CHW_HW_STATUS	findHardware();		///Find wiimote

		/// Check if a button has been pressed (1->pressed, 0->otherwise)
		inline int IsButtonPlusJustPressed  () {return IS_JUST_PRESSED(WiimoteHW, UGKWM_BUTTON_PLUS);}
		inline int IsButtonMinusJustPressed () {return IS_JUST_PRESSED(WiimoteHW, UGKWM_BUTTON_MINUS);}
		
		/// Turn ON|OFF the motion sensing of the current Wiimote
		inline void StartMotionSensing () {wiiuse_motion_sensing(WiimoteHW, UGKWM_ACTIVATE);}
		inline void StopMotionSensing  () {wiiuse_motion_sensing(WiimoteHW, UGKWM_DEACTIVATE);}	
		
		/// Turn ON|OFF the rumble of the current Wiimote
		inline void StartRumble () {wiiuse_rumble(WiimoteHW, UGKWM_ACTIVATE);}
		inline void StopRumble  () {wiiuse_rumble(WiimoteHW, UGKWM_DEACTIVATE);}
		
		/// Turn ON the WIIMOTE_LED (led 1, 2, 3 or 4) of the current Wiimote
		inline void SetLed (int led) {wiiuse_set_leds(WiimoteHW, led);}
		
		/// Check if the current Wiimote is using the Speaker
		inline boolean IsUsingSpeaker () {return WIIUSE_USING_SPEAKER(WiimoteHW);}

		/// Check if the current Wiimote is using the IR sensor
		inline boolean IsUsingIR () {return WIIUSE_USING_IR(WiimoteHW);}

		/// Check if the current Wiimote has a led ON (led 1, 2, 3 or 4)
		inline boolean IsLedSet (int led);

		/// Setters & Getters
		inline void SetWiiMoteHW (UGKWM_WiiMote *wm)	{WiimoteHW = wm;}
		inline UGKWM_WiiMote* GetWiiMoteHW ()			{return WiimoteHW;}

		inline void SetUid (int uid)	{this->uid = uid;}
		inline int  GetUid ()			{return uid;}
		
		#endif
	};
}

#endif