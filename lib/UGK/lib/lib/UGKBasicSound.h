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
		virtual bool SetVolume2();		///< Internal volume change function specific for every kind of sound management API

		virtual void PlayChannel(int channel, int loops);

		UGKS_String Path,	///<Path to the sound.
					Name;	///<Name of the sound file.

	public:

		UGKSNDENG_Sample Sound;			///<The sound to be played in fmod type.
		int Volume,						///<The intensity of the sound. 0 no sound, 255 maximun power (in SDL the maximun is 128)
			Position,					///<The position of the sound.
			Channel;					///< HW audio channel where is being played this sound

		//Methods
		/**
		*	\fn void CSound::Init()
		*	Basic constructor
		*/
		inline  void Init() { Path.clear(); Name.clear(); Position = 0; SetVolume(0);}
		virtual void Reset();

		/// Initializes a new sound
		virtual bool Load();
		inline  bool Load(UGKS_String File, UGKS_String P) { Name = File;  Path = P; return Load(); }
		/**
		*	\fn void Init(UGKS_String name, int vol, UGKS_String path)
		*	Loads a given sound when initializinf it
		*	\param[in] name The name of the sound
		*	\param[in] vol  The volume of the sound
		*	\param[in] path The path to the directory of the sound
		*/
		inline  bool Init(UGKS_String name, int vol, UGKS_String path)
		{
			Position = 0; //Reset to the very beginning of the sound
			if (Load(name, path))
			{
				//Sound loaded. Proceed
				SetVolume(vol);
				return true;
			}
			else return false;
		}

		CBSound(){Init();}		///< Constructor of the class
		/**
		*	\fn void CBSound::CBSound(CString P,int v, CString c)
		*	Constructor of the class.
		*	\param[in] Name Path where the sound is
		*	\param[in] Vol Volume of the sound
		*	\param[in] Path Path where the sound is
		*/
		CBSound(UGKS_String name, int vol, UGKS_String path) { Init(name, vol, path); }
		/**
		*	\fn void CBSound::~CBSound()
		*	Destructor of the Class. Close the Stream.
		*/
		~CBSound() { Close(); };

		//Setters and Getters
		/**
		*	\fn void CSound::SetName (CString name)
		*	Specifies the name of a sound
		*	\param[in] name The name of the sound
		*/
		inline void SetName(UGKS_String name) { Name = name; }
		
		/**
		*	\fn void CSound::SetPath (CString path)
		*	Specifies the name of a sound
		*	\param[in] path The name of the path of the sound
		*/
		inline void SetPath(UGKS_String path){ Path = path; }
		
		inline UGKS_String GetName() { return Name; }
		inline UGKS_String GetPath() { return Path; }
		
		/**
		*	\fn void Play(int vol)
		*	Plays the own Sound
		*	\param[in] vol Volume to play this sound
		*/
		inline  void Play(int vol)	///< Plays this sound with a determined volume (v can be NULL) 
		{
			SetVolume2(vol);
			PlayChannel(UGKSND_ANY_CHANNEL, 0);
		}

		/**
		*	\fn void Play()
		*	Plays the own Sound with its default volume
		*/
		inline void Play()
		{
			SetVolume2();
			PlayChannel(UGKSND_ANY_CHANNEL, 0);
		}

		virtual UGKSNDENG_Sample getStream(); ///< Get the stream of the sound

		virtual bool Stop();
		
		void SetVolume(int vol); ///< Set new volume
		/**
		*	\fn UGKSNDENG_Sample CSound::getStream()
		*	gets the stream of the sound
		*/
		inline UGKSNDENG_Sample GetSound(){return Sound;}

		/**
		*	\fn void CSound::SetPosition(int position)
		*	Sets a new Position to the sound
		*	\param[in] position New position to the sound
		*/
		inline void SetPosition(int position) { if(0 > position) Position = 0; else Position=position;}

		virtual bool Pause();
		virtual bool Resume();
		virtual void Expire(int ticks);
		virtual void Close(); ///<Close the stream of the sound
	
	};
}
#endif
