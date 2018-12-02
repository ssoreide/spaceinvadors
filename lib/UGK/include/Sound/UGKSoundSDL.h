/**	Definition of the class Sound for the UPV Game Kernel
*	Implementation using SDL v3.75
*	Prefix: UGKSND_

*	@author Ramon Molla
*	@version 2018-01
*/

#ifndef UGKSND_SOUND_SDL
#define UGKSND_SOUND_SDL

#include <UGKBasicSound.h>

#define UGKSND_DEFAULT_VOLUME		 -1		///< Default volume of the sound.
#define UGKSND_VOLUME_INCREMENT		  3		///< Increment of volume for ramp fading in or out
#define UGKSND_ULTRA_LOW_VOLUME	      8		///< A VERY low value of volume
#define UGKSND_LOW_VOLUME			 16		///< The low value of volume
#define UGKSND_LOW_MED_VOLUME		 45		///< Low to medium value of volume
#define UGKSND_MEDIUM_VOLUME		 64     ///< The medium value of volume
#define UGKSND_VOLUME_60			 77     ///< 60% of the maximun volume
#define UGKSND_VOLUME_80			102     ///< 80% of the maximun volume
#define UGKSND_MAX_VOLUME			SDL_MIX_MAXVOLUME		///< The maximun value a sound can reach at the top of its power

#define UGKSND_Sound_Length Uint32
#define UGKSND_Sound_Buffer Uint8*

class UGKSND_SoundType
{
public:
	UGKSND_Sound_Buffer	Buffer;
	UGKSND_Sound_Length	Length;
	SDL_AudioSpec		Specs;

	UGKSND_SoundType()
	{
		Buffer = NULL;
		Length = 0;
		Specs.callback = NULL;
		SDL_memset(&Specs, 0, sizeof(Specs));
	}
}; 

namespace UGK
{
	/**
	*	\class CSound
	*	Manages a single sound: loads it, unloads, plays, change intensity,...
	*/

	class UGK_API CSound : public CBSound
	{
	protected:
		/**
		*	\fn CBSound::SetVolume()
		*	\brief Set the volume of one channel
		*/
		inline bool SetVolume2() {
			if (NULL != Sound)
				if (!Mix_VolumeChunk(Sound, Volume))
					return false;
			return true;
		}
		
		/**
		*	\fn PlayChannel(int channel, int loops)
		*	\brief Plays a sample in a channel
		*	\param[in] channel The channel
		*	\param[in] loops The number of loops (0 is none, -1 is infinite, other is the number of loops)
		*/
		inline int PlayChannel(int channel, int loops)
		{
			if (NULL != Sound)
				return Mix_PlayChannel(channel, Sound, loops);
			return UGKSND_NO_CHANNEL;
		}

		/**
		*	\fn PlayChannel(int loops)
		*	\brief Plays a sample in a channel
		*	\param[in] loops The number of loops (0 is none, -1 is infinite, other is the number of loops)
		*/
		inline int PlayChannel(int loops)
		{
			if (NULL != Sound)
				return Mix_PlayChannel(LastChannel, Sound, loops);
			return UGKSND_NO_CHANNEL;
		}


	public:

		//Atributes
		SDL_AudioSpec		Specs;

		//Methods
		CSound() {};	///< Constructor of the class
		CSound	(UGKS_String name, int vol, UGKS_String path)
		{
			Name	= name;
			Path	= path;
			Volume	= vol;
		}
		~CSound() {};	///< Destructor of the class

		inline bool Load()
		{
			UGKS_String FullPath;

			// load sample.wav in to sample (you must call OpenAudio before this method)
			UGKS_GenerateFullPathName(FullPath, Path, Name);
			Sound = Mix_LoadWAV(FullPath.c_str());

			return NULL != Sound;
		}

		/**
		*	\fn Resume()
		*	\brief Resume a channel
		*	\return True or false result
		*/
		inline bool Resume() {
			Mix_Resume(LastChannel);
			return true;
		}

		/**
		*	\fn CBSound::Expire( int ticks)
		*	\brief Expire a channel after some time
		*	\param[in] ticks The number of ticks to wait
		*/
		void Expire(int ticks) {
			Mix_ExpireChannel(LastChannel, ticks);
		}

		/**
		*	\fn void close()
		*	Close the stream of the sound
		*/
		inline void Close()
		{
			if (NULL != Sound)
			{
				Mix_FreeChunk(Sound);
				Sound = NULL;
			}
		}

		/**
		*	\fn Pause()
		*	\brief Pause a channel
		*/

		inline bool Pause() {
			Mix_Pause(LastChannel);
			return true;
		}

		/**
		*	\fn Stop()
		*	\brief Stop a specified channel
		*	\return True or false result
		*/
		inline bool Stop() { return Mix_HaltChannel(LastChannel); }
	};
}
#endif
