/**	Definition of the class Basic Sound for the UPV Game Kernel

*	Prefix: UGKBSND_

*	@author Ramon Molla, Carlos Martinez Perez
*	@version 2011-07
*	@version Alfonso Pérez 2013-03
	@version Ramón Mollá 2014-05 - 1st API conversion and refactoring
	@NewVersion Ramón Mollá 2017-12 - 2nd API conversion and refactoring
*/

#ifndef UGKBSND_BASIC_SOUND
#define UGKBSND_BASIC_SOUND

#include <stdlib.h>
#include <UGKSoundEngine.h>
#include <UGKString.h>
#include <HRTimer.h>

#define UGKSND_HALF_POSITION 1000
#define UGKSND_STRD_POSITION 2000
#define UGKSND_NOT_SET -1

#define UGKSND_MUTE				  0		///< Volume muted

namespace UGK
{
	/**
	*	\class CBSound
	*	Manages a single sound: loads it, unloads, plays, change intensity,...
	*/

	class UGK_API CBSound
	{

	protected:
		/**
		*	\fn bool SetVolume2(int V)
		*	\brief	Setter of the volume of the sample
					Internal volume change function specific for every kind of sound management API
		*	\param[in] V The volume
		*	\return True or False result
		*/
		inline bool SetVolume2(int V) {
			Volume = V;
			return SetVolume2();
		};	
		virtual bool SetVolume2() { return false; }		///< Internal volume change function specific for every kind of sound management API
		virtual int  PlayChannel(int channel, int loops) { return 0; }

		UGKSNDENG_Sample	Sound;		///<The sound to be played in fmod type.
		int Volume,						///<The default intensity of the sound. 0 no sound, 255 maximun power (in SDL the maximun is 128)
			LastChannel,				///<Last sound channel used to 
			Loops;						///<Amount of consecutive replays. 0 no loop; only one reproduction. 

	public:
		UGKS_String	Path,		///<Path to the sound.
					Name;		///<Name of the sound file.

		//Methods
		/**
		*	\fn void CSound::Init()
		*	Basic constructor
		*/
		inline  void Init() { Path.clear(); Name.clear(); SetVolume(UGKSND_MUTE);}
		virtual void Reset() {}

		/// Initializes a new sound
		virtual bool Load() { return false; }

		CBSound();  //Reset to the very beginning of the sound

		/**
		*	\fn void CBSound::CBSound(CString P,int v, CString c)
		*	Constructor of the class.
		*	\param[in] Name Path where the sound is
		*	\param[in] Vol Volume of the sound
		*	\param[in] Path Path where the sound is
		*/
		CBSound(UGKS_String name, int vol, UGKS_String path);

		/**
		*	\fn void CBSound::~CBSound()
		*	Destructor of the Class. Close the Stream.
		*/
		~CBSound();

		
		/**
		*	\fn void Play(int vol)
		*	Plays the own Sound
		*	\param[in] vol Volume to play this sound
		*/
		inline  int Play(int vol)	///< Plays this sound with a determined volume (v can be NULL) 
		{
			SetVolume2(vol);
			return PlayChannel(UGKSND_ANY_CHANNEL, 0);
		}

		/**
		*	\fn void Play()
		*	Plays the own Sound with its default volume
		*/
		inline int Play()
		{
			SetVolume2();
			return LastChannel = PlayChannel(UGKSND_ANY_CHANNEL, Loops);
		}

		virtual UGKSNDENG_Sample getStream() { return NULL; } ///< Get the stream of the sound

		/**
		*	\fn Stop()
		*	\brief Stop a specified channel
		*	\return True or false result
		*/
		virtual bool Stop() { return false; }
		
		void SetVolume(int vol); ///< Set new volume

		/**
		*	\fn UGKSNDENG_Sample CSound::getStream()
		*	gets the stream of the sound
		*/
		inline UGKSNDENG_Sample GetSound(){return Sound;}

		/**
		*	\fn Pause()
		*	\brief Pause a channel
		*/
		virtual bool Pause() { return false; }

		/**
		*	\fn Resume()
		*	\brief Resume a channel
		*	\return True or false result
		*/
		virtual bool Resume() { return false; }

		/**
		*	\fn Expire( int ticks)
		*	\brief Expire a channel after some time
		*	\param[in] ticks The number of ticks to wait
		*/
		virtual void Expire(int ticks) {}

		/**
		*	\fn virtual void close()
		*	Close the stream of the sound
		*/
		virtual void Close() {}
	};
}
#endif
