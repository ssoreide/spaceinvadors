/**	Selection of the Sound class implementation for the UPV Game Kernel

*	Prefix: UGKSND_

*	@author Ramon Molla
*	@version 2018-01
*/

#ifndef UGKSND_SOUND
#define UGKSND_SOUND

#include <UGKSoundEngine.h>

#define UGKSND_NO_CHANNEL   -1
#define UGKSND_ANY_CHANNEL  -1
#define UGKSND_ALL_CHANNELS -1

#ifdef UGKSNDENG_FMOD375
	#include <UGKSoundFMOD375.h>
#elif defined(UGKSNDENG_FMODEx)
#elif defined(UGKSNDENG_FMODStudio)
#elif defined(UGKSNDENG_OAL)
	#include <UGKSoundOAL.h>
#elif defined(UGKSNDENG_SDL)
	#include <UGKSoundSDL.h>
#endif

#endif
