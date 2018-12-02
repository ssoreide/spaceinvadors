/**	Definition of the class Sound for the UPV Game Kernel
*	Implementation using FMOD v3.75
*	Prefix: UGKSND_

*	@author Ramon Molla
*	@version 2018-01
*/

#ifndef UGKSND_SOUND_FMOD375
#define UGKSND_SOUND_FMOD375

#include <UGKBasicSound.h>

#define UGKSND_DEFAULT_VOLUME		 -1		///< Default volume of the sound.
#define UGKSND_VOLUME_INCREMENT		  5		///< Increment of volume for ramp fading in or out
#define UGKSND_ULTRA_LOW_VOLUME	     16		///< A VERY low value of volume
#define UGKSND_LOW_VOLUME			 32		///< The low value of volume
#define UGKSND_LOW_MED_VOLUME		 90		///< Low to medium value of volume
#define UGKSND_MEDIUM_VOLUME		128     ///< The medium value of volume
#define UGKSND_VOLUME_60			153     ///< 60% of the maximun volume
#define UGKSND_VOLUME_80			204     ///< 80% of the maximun volume
#define UGKSND_MAX_VOLUME			255		///< The maximun value a sound can reach at the top of its power

namespace UGK
{
	/**
	*	\class CSound
	*	Manages a single sound: loads it, unloads, plays, change intensity,...
	*/

	class UGK_API CSound : public CBSound
	{
		bool SetVolume2();		///< Internal volume change function specific for every kind of sound management API
		int  PlayChannel(int channel, int loops);

	public:

		//Atributes
		FSOUND_DSPUNIT* dspUnit;
		//FMUSIC_MODULE	Music;
		
		//Methods
		CSound()	{}						///< Constructor of the class
		CSound(UGKS_String name, int vol, UGKS_String path) {CBSound(name, vol, path);}
		~CSound()	{};

		UGKSNDENG_Sample getStream(); ///< Get the stream of the sound

		bool Load();
		bool Pause();
		bool Resume();
		void Expire(int ticks);
		void Close(); ///<Close the stream of the sound
		bool Stop();
	};
}

void * F_CALLBACKAPI dspCallbackSounds(void *originalbuffer, void *newbuffer, int length, int param);
signed char F_CALLBACKAPI metacallback(char *name, char *value, int userdata);


#endif
