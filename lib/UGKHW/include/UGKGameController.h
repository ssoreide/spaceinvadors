/** Definition of the class GameController
*	@file UGKGameController
*	Prefix: GC_
*
*   @version Ramón Mollá 2017-12
*/

#ifndef GC_GAMECONTROLLER
#define GC_GAMECONTROLLER

#include <UGKHardware.h>
#include <UGKJoystick.h>
#include <SDL_gamecontroller.h>

#define GC_ACTION unsigned char
#define GC_ACTIVE_ACTION std::list<GC_ACTION>

namespace UGK
{
	class CGameController : public CHardware {
	protected:
		int device_index;
		SDL_GameController* sdl_controller;
		bool vibration;

	public:
		CGameController(int id); ///< Constructor of the class
		~CGameController();

		CHW_HW_STATUS findHardware(); ///< Find Game Controller
		CHW_HW_STATUS Init(void);	  ///< Start Game Controller

		Sint16 getAxis(SDL_GameControllerAxis axis); ///< get Axis state
		Uint8 getButton(SDL_GameControllerButton  button); ///< get Button state

		CJoystick getJoystick(); ///< get equivalent Joystick

		static std::list<CGameController> getGameControllers();
		static CHW_HW_STATUS InitSubSystem();
		inline void setVibration(bool vibration) { this->vibration = vibration; }
		inline void setIndex(unsigned int index) { this->device_index = index; }

	};
}

#endif // !GC_GAMECONTROLLER

