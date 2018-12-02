/**	Definition of the class Sound for the UPV Game Kernel
*	Implementation using OAL
*	Prefix: UGKSND_

*	@author Ramon Molla
*	@version 2018-01
*/

#ifndef UGKSND_SOUND_OAL
#define UGKSND_SOUND_OAL

#include <UGKBasicSound.h>

// The volume values will later be converted to a 0.0 - 1.0 scale
#define UGKCSND_DEFAULT_VOLUME		255	///< Default volume of the sound.
#define UGKCSND_VOLUME_INCREMENT	  5		///< Increment of volume for ramp fading in or out
#define UGKCSND_ULTRA_LOW_VOLUME	 16		///< A VERY low value of volume
#define UGKCSND_LOW_VOLUME			 32		///< The low value of volume
#define UGKCSND_LOW_MED_VOLUME		 90		///< Low to medium value of volume
#define UGKCSND_MEDIUM_VOLUME		128     ///< The medium value of volume
#define UGKCSND_VOLUME_60			153     ///< 60% of the maximun volume
#define UGKCSND_VOLUME_80			204     ///< 80% of the maximun volume
#define UGKCSND_MAX_VOLUME			255		///< The maximun value a sound can reach at the top of its power
#define UGKCSND_MAX_VOLUMEf			255.0f	///< The maximun value a sound can reach at the top of its power


#define UGKSND_Sound_Length ALsizei
#define UGKSND_Sound_Buffer ALvoid*

class UGKSND_SoundType
{
public:
	UGKSND_Sound_Buffer	Buffer;
	UGKSND_Sound_Length	Length;

	UGKSND_SoundType()
	{
		Buffer = NULL;
		Length = 0;
	}
};

#define UGKSNDENG_Sample	UGKSND_SoundType

namespace UGK
{
	/**
	*	\class CSound
	*	Manages a single sound: loads it, unloads, plays, change intensity,...
	*/

	class UGK_API CSound : public CBSound
	{
		bool SetVolume2();		///< Internal volume change function specific for every kind of sound management API
		int PlayChannel(int channel, int loops);

	public:

		ALuint bufferID;            // The OpenAL sound buffer ID
		ALuint sourceID;            // The OpenAL sound source
		ALenum format;              // The sound data format
		ALsizei freq;               // The frequency of the sound data
		
		//Methods
		CSound() {}						///< Constructor of the class
		CSound(UGKS_String name, int vol, UGKS_String path) { CBSound(name, vol, path); }
		~CSound() {};

		bool Reset(UGKS_String name, int vol, UGKS_String path);

		UGKSNDENG_Sample getStream(); ///< Get the stream of the sound

		bool Load();
		bool LoadOgg(UGKS_String fileName, UGKSNDENG_Sample &buffer, ALenum &format, ALsizei &freq);

		bool Pause();
		bool Resume();
		void Expire(int ticks);
		void Close(); ///<Close the stream of the sound	
		bool Stop();
	};
}

#endif
