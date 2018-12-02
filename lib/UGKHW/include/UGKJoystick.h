/** Definition of the class Joystick
*	@file: UGKJoystick.h
*	Prefix: JS_
*
*   @version Ramón Mollá 2017-12
*/

#ifndef JS_JOYSTICK
#define JS_JOYSTICK

#include <UGKHardware.h>
#include <SDL_joystick.h>
#include <list>

#define JS_ACTION unsigned char
#define JS_ACTIVE_ACTION std::list<JS_ACTION>

namespace UGK
{
	class CJoystick : public CHardware {
	protected:
		int device_index;
		SDL_Joystick* sdl_joystick;
		bool vibration;
		unsigned int n_buttons;
	public:
		CJoystick(int id);	///< Constructor of the class
		CJoystick(SDL_Joystick* joy); ///< Alternative constructor of the class
		~CJoystick();	///< Destructor of the class

		CHW_HW_STATUS findHardware();	///< Find joystick
		CHW_HW_STATUS Init(void);		///< Start joystick

		Sint16 getAxis(int axis); ///< get Axis state
		Uint8 getButton(int button); ///< get Button state
		Uint8 getHat(int hat); ///< get POV Hat state

		static std::list<CJoystick> getJoysticks();
		static CHW_HW_STATUS InitSubSystem();

		inline void setVibration(bool vibration) { this->vibration = vibration; }
		inline void setButtons(unsigned int n_buttons) { this->n_buttons = n_buttons; }
		inline void setIndex(unsigned int index) { this->device_index = index; }
	};
}

#endif // !JS_JOYSTICK
