/**	Definition of the class CHardware. Base class for all hardware in the system

*	Prefix: CHW_

*	@author Ramon Molla
	@author David Peris
*	@version 2015-05
*/

#ifndef CHW_HARDWARE
#define CHW_HARDWARE

#include <UGKString.h>
#include <HRTimerManager.h>

#define CHW_NO_TIMER_MNGR NULL

//#define UGKHWR
#define UGKHWR_SDL

//Stencil to replicate where ever needed
#ifdef UGKHWR
#elif defined(UGKHWR_SDL)
#include <SDL.h>
#include <SDL_mixer.h>
#endif

/**
* Definition enum type CHW_HARDWARE_TYPE for clasiffy SOUND, IN/OUT ...
* Available types of hardware (values of the atribute TypeHW)
**/
typedef enum {
	CHW_NO_HW,
	CHW_SOUND,		//Output sound through a sounds card
	CHW_GRAPHIC,	//Output video through a graphics card
	CHW_IN_KEYBOARD,		///< Device Keyboard
	CHW_IN_MOUSE,			///< Device Mouse
	CHW_IN_JOYSTICK,		///< Device Joystick
	CHW_IN_GAMECONTROLLER,	///< Device Game Controller
	CHW_IN_WIIMOTE,			///< Device Wiimote
	CHW_IN_KINECT,			///< Device Kinect
	CHW_IN_WEBCAM,			///< Device Web Cam
	CHW_IN_LEAP,			///< Device Leap Motion
	CHW_IN_GLOVE,			///< Device Guante
	CHW_IN_GENERIC,			///< Device Generic
	CHW_IN_MIC,				///< Device Microphone
	CHW_IN_TOUCHSCREEN,		///< Device Touch Screen. For tablets
	CHW_MAX_HW_TYPE
} CHW_HARDWARE_TYPE;

typedef enum {
	CHW_SND_NO_SOUND,
	CHW_SND_MAX_DEVICE
} CHW_SOUND_TYPE;

typedef enum {
	CHW_GRA
} CHW_GRAPH_TYPE;


typedef enum {
	CHW_HW_NOT_FOUND,
	CHW_HW_NOT_INITIALIZED,
	CHW_HW_INITIALIZED,
	CHW_HW_ACTIVE,
	CHW_HW_PAUSED,
	CHW_HW_MAX_STATUS
} CHW_HW_STATUS;

/**
*	CHardware

*	Manages all the information relative to the general game application.
*	It is implemented as a singleton. This is not the game singleton
*/
namespace UGK
{
	class UGK_API CHardware
	{
	protected:
		/// The name of the hardware given by the OS.
		UGKS_String Name;

	public:

		cHRTimerManager *HRTimerManager;		///<HR counters for delaying the sensitiveness of the device

		//Atributes
		/// Type of hardware: sound, graphics, I/O,...
		unsigned short int	SubTypeHW;
		CHW_HARDWARE_TYPE	TypeHW;
		/// The hardware is active. Implicitly it needs to be alive in order to be active
		CHW_HW_STATUS		Status;

		//Methods
		CHardware();					///<Constructor of the class
		CHardware(unsigned int type);	///<Constructor of the class
		~CHardware();					///<Destructor of the class
		void setType	(unsigned int type);
		void setSubType	(unsigned short int subtype);

		//Setters
		inline void SetName(UGKS_String n)	{ Name = n; }	//Sets the name n of the language
		
		//Getters
		inline UGKS_String	GetName()		{ return Name; }

		//Manage hardware
		virtual CHW_HW_STATUS			findHardware	();	///Finds the hardware
		virtual UGKS_String				getProperties	(); ///Obtains hardware propierties
		virtual CHW_HW_STATUS			Init			(); ///Initializes the hardware
		virtual void					Finish			(); ///Closes the hardware
	};

	typedef std::vector<CHardware*> UGKDM_HardwareVector;
}
#endif