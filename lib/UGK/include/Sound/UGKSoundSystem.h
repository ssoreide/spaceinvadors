/**	Definition of the class Sound System for the UPV Game Kernel

*	@Prefix: UGKCSNDS_

*	@author Ramon Molla
*	@NewVersion Ramón Mollá 2014-05 - API conversion and refactoring
*/

#ifndef UGKCSNDS_SOUND_SYSTEM
#define UGKCSNDS_SOUND_SYSTEM

#include <UGKSound.h>

namespace UGK
{
	class UGK_API CSoundSystem
	{

	public:

		#ifdef UGKSNDENG_FMOD375
		// FMOD CALLBACKS
		signed short	*OscBuffer;
		int				 OscBlock ;

		FSOUND_DSPUNIT* dspUnitSounds;		// DSP SOUNDS (UNIT)
		FSOUND_DSPUNIT* dspUnitSpectrum;	// DSP SPECTRUM (UNIT)
		#elif defined UGKSNDENG_FMODEx
		#elif defined UGKSNDENG_OAL
		#elif defined UGKSNDENG_SDL
		#endif
	
		//Methods
		void Init (void);
	
		CSoundSystem(){Init();}			// Constructor of the class

		static UGKS_String ErrorMsg(unsigned int errcode);
	};
}

#endif