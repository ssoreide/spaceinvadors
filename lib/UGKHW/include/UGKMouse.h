/** Definition of the class Mouse
*   @file: UGKMouse.h
*	Prefix: MO_
*
*	@version 2017
*/


#ifndef MO_MOUSE //S'elimina la macro del ratolí
#define MO_MOUSE //Es defineix la macro del ratolí
//Es defineix macro per a llibreries de windows
#ifndef  WINDOWS_LOADED
#define WINDOWS_LOADED
#include <Windows.h>
#endif // ! WINDOWS_LOADED

#include <UGKHardware.h>
#include <map>
#include <SDL_mouse.h>

#define MO_ACTION unsigned char
#define MO_ACTIVE_ACTION std::list<MO_ACTION>


// Helpful macros for the mouse
#define SDL_BUTTON(X)		(SDL_PRESSED<<(X-1))
#define SDL_BUTTON_LEFT		1
#define SDL_BUTTON_MIDDLE	2
#define SDL_BUTTON_RIGHT	3
#define SDL_BUTTON_WHEELUP	4
#define SDL_BUTTON_WHEELDOWN	5
#define SDL_BUTTON_LMASK	SDL_BUTTON(SDL_BUTTON_LEFT)
#define SDL_BUTTON_MMASK	SDL_BUTTON(SDL_BUTTON_MIDDLE)
#define SDL_BUTTON_RMASK	SDL_BUTTON(SDL_BUTTON_RIGHT)
#define SDL_BUTTON_UMASK	SDL_BUTTON(SDL_BUTTON_WHEELUP)
#define SDL_BUTTON_DMASK	SDL_BUTTON(SDL_BUTTON_WHEELDOWN)

namespace UGK
{
	class CMouse : public CHardware {
	protected:
		unsigned char ActionSize;
		/// Position in the array means the code of the button pressed on the mouse in order to start up an action on the game
		
		/// List is replaced by a map, therefers to the button pressed and the value associate refers to the action on the game  
		std::map<unsigned char, MO_ACTION>	ActionButton;
		std::map<char, char>				SDL2UGK;	///< Translation table from SDL input codification to UGK codification

	public:
		CMouse();	///< Constructor of the class
		~CMouse();	///< Destructor of the class
		float sensitivity;

		// Virtual methods redefined
		CHW_HW_STATUS	findHardware();	///< Find mouse
		CHW_HW_STATUS	Init(void);		///< Start mouse

		bool leftButtonPressed();	///< left button pressed?
		bool rightButtonPressed();	///< right button pressed?
		bool midButtonPressed();	///< middle button pressed?
		bool wheelUpHappened();		///< wheel moved upwards?
		bool wheelDownHappened();	///< wheel moved downwards?
	};
}

#endif
