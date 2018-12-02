/**	UGKWiimoteManager.h - Wrapper that manages the Wiimotes

*	Prefix: UGKWMM_
*	@author Ramon Molla, Imanol Fraile
*	@version 2015-05
*/
//#include "Copyright.h"

#ifndef UGKWMM_WIIMOTE_MANAGER
#define UGKWMM_WIIMOTE_MANAGER

#include <Wiimote\UGKWiimote.h>

#define UGKWMM_NO_WIIMOTE	-1
#define UGKWMM_MAX_WIIMOTES	 4

#define UGKWM_WII_USE

typedef enum {
	CWM_NO_WIIMOTES_FOUND,
	CWM_WIIMOTES_CONNECT_FAILED,
	CWM_MAX_MSG
} CWM_WiimoteMsg;

namespace UGK 
{
	class CWiimoteManager
	{

	public:

		int	WiimotesAmount,
			WiimotesFound,
			CurrentWiimote,
			WiimotesConnected;

	#ifdef UGKWM_WII_USE
		UGKWM_WiiMote** WiimoteHW;		///<For internal use of 
	#endif
		std::vector<CWiiMote>	UGKWiiMotes;

		///< Constructor of the class
		CWiimoteManager			(int WiimotesAmount) {WiimotesAmount = WiimotesAmount;
													  UGKWiiMotes = std::vector<CWiiMote>();
													  WiimoteHW = NULL;
													  WiimotesFound = UGKWMM_NO_WIIMOTE;
													  CurrentWiimote = UGKWMM_NO_WIIMOTE;
													  WiimotesConnected = UGKWMM_NO_WIIMOTE;}
		///< Destructor of the class
		~CWiimoteManager		(); // Comprobar si hay que destruir algún puntero hecho con un NEW
		// ESTE DESTRUCTOR ESTÁ LLAMANDO AL CLEANUP

		/// Initialize the Wiimotes array
		void Init (int WiimotesAmount);
		
	#ifdef UGKWM_WII_USE

		/// Find Wiimotes that are in discovery mode (buttons 1+2 pressed)
		inline int Find (int WiimotesAmount)		{return wiiuse_find(WiimoteHW, WiimotesAmount, UGKWM_WIIMOTE_DEFAULT_TIMEOUT);}

		/// Connect to the Wiimotes found
		inline int Connect (int WiimotesAmount)		{return wiiuse_connect(WiimoteHW, WiimotesAmount);}

		/// Disconnect the Wiimotes
		inline void Cleanup (int WiimotesAmount)	{wiiuse_cleanup(WiimoteHW, WiimotesAmount);}

		/// Activates the wiimote to work with from now on
		inline void SetCurrentWiimote (int wm)		{if (wm < WiimotesAmount && wm >= 0) CurrentWiimote = wm;}

		/// HW handles for managing input events
		void HandleEvent		();
		void HandleRead			(byte* data, unsigned short len);
		void HandleCtrlStatus	();
		void HandleDisconnect	();

		void Vibrate			();

	#endif
	};
}
#endif