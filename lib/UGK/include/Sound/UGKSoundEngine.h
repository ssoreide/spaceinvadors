/**	Definition of the sound engine

*	Prefix: UGKSNDENG_

*	@author Leopoldo Pla 
*	@version 2015-01
*   @NewVersion Carlos Pérez 2016-01-27 - Added errors and fx modes
*/

#ifndef UGKSNDENG_SOUNDENGINE
#define UGKSNDENG_SOUNDENGINE

// Be careful, use only one API every time
// The value in the definition is used to correctly identify the definition, if you
// remove the value VS generates error c1017
//#define UGKSNDENG_FMOD375 1 // bugs, set to SDL to avoid compilation problems (sjimenez)
//#define UGKSNDENG_FMODEx 2
//#define UGKSNDENG_FMODStudio 3
//#define UGKSNDENG_OAL 4
#define UGKSNDENG_SDL 5

//Different sampling frequencies
#define UGKSNDENG_FREQ_CD4	11025
#define UGKSNDENG_FREQ_CD2	22050
#define UGKSNDENG_FREQ_CD	44100
#define UGKSNDENG_FREQ_DV	48000
#define UGKSNDENG_FREQ_DV	48000
#define UGKSNDENG_FREQ_2CD	88200
#define UGKSNDENG_FREQ_DVD	96000
#define UGKSNDENG_FREQ_BR	192000
#define UGKSNDENG_FREQ_DXD	352800

//Different output channel configurations
typedef enum
{
	UGKSNDENG_MONNO,
	UGKSNDENG_STEREO,
	UGKSNDENG_QUADRAPHONIC,
	UGKSNDENG_SURROUND51,
	UGKSNDENG_SURROUND71,
	UGKSNDENG_MAX_OUTPUT_CHANNELS
} UGKSNDENG_OUTPUT_CHANNELS;

//Stencil to replicate where ever needed
#ifdef UGKSNDENG_FMOD375
#elif defined(UGKSNDENG_FMODEx)
#elif defined(UGKSNDENG_FMODStudio)
#elif defined(UGKSNDENG_OAL)
#elif defined(UGKSNDENG_SDL)
#endif

#ifdef UGKSNDENG_FMOD375
	#include <fmod.h>
	enum SND_ERRORS 
	{
		//Matching UGK errors to fmod errors
		UGKSNDENG_ERR_NONE,             /* No errors */
		UGKSNDENG_ERR_BUSY,             /* Cannot call this command after FSOUND_Init.  Call FSOUND_Close first. */
		UGKSNDENG_ERR_UNINITIALIZED,    /* This command failed because FSOUND_Init or FSOUND_SetOutput was not called */
		UGKSNDENG_ERR_INIT,             /* Error initializing output device. */
		UGKSNDENG_ERR_ALLOCATED,        /* Error initializing output device, but more specifically, the output device is already in use and cannot be reused. */
		UGKSNDENG_ERR_PLAY,             /* Playing the sound failed. */
		UGKSNDENG_ERR_OUTPUT_FORMAT,    /* Soundcard does not support the features needed for this soundsystem (16bit stereo output) */
		UGKSNDENG_ERR_COOPERATIVELEVEL, /* Error setting cooperative level for hardware. */
		UGKSNDENG_ERR_CREATEBUFFER,     /* Error creating hardware sound buffer. */
		UGKSNDENG_ERR_FILE_NOTFOUND,    /* File not found */
		UGKSNDENG_ERR_FILE_FORMAT,      /* Unknown file format */
		UGKSNDENG_ERR_FILE_BAD,         /* Error loading file */
		UGKSNDENG_ERR_MEMORY,           /* Not enough memory or resources */
		UGKSNDENG_ERR_VERSION,          /* The version number of this file format is not supported */
		UGKSNDENG_ERR_INVALID_PARAM,    /* An invalid parameter was passed to this function */
		UGKSNDENG_ERR_NO_EAX,           /* Tried to use an EAX command on a non EAX enabled channel or output. */
		UGKSNDENG_ERR_CHANNEL_ALLOC,    /* Failed to allocate a new channel */
		UGKSNDENG_ERR_RECORD,           /* Recording is not supported on this machine */
		UGKSNDENG_ERR_MEDIAPLAYER,      /* Windows Media Player not installed so cannot play wma or use internet streaming. */
		UGKSNDENG_ERR_CDDEVICE,         /* An error occured trying to open the specified CD device */

		//UGK API Errors
		UGKSNDENG_ERR_UNKNOWN,          /* Error unknown */
		UGKSNDENG_ERR_MAX				  /* For accounting purpouses only. This error has to be always the last one*/
	};

	enum UGKSNDENG_FX_MODES
	{
		UGKSNDENG_FX_CHORUS,
		UGKSNDENG_FX_COMPRESSOR,
		UGKSNDENG_FX_DISTORTION,
		UGKSNDENG_FX_ECHO,
		UGKSNDENG_FX_FLANGER,
		UGKSNDENG_FX_GARGLE,
		UGKSNDENG_FX_I3DL2REVERB,
		UGKSNDENG_FX_PARAMEQ,
		UGKSNDENG_FX_WAVES_REVERB,

		UGKSNDENG_FX_MAX
	};

	typedef unsigned char	Uint8;
	typedef signed char		Sint8;
	typedef unsigned short	Uint16;
	typedef signed short	Sint16;

	#define UGKSNDENG_Sample	FSOUND_SAMPLE*
	#define UGKSNDENG_MusicType FMUSIC_MODULE*

	class CChannel
	{
		int Frequency;
	};
#elif defined(UGKSNDENG_FMODEx)
#elif defined(UGKSNDENG_FMODStudio)
#elif defined(UGKSNDENG_OAL)
	#include <OpenAL/AL/al.h>
	#include <OpenAL/AL/alc.h>
	#include "OpenAL/vorbis/vorbisfile.h"

	typedef unsigned char	Uint8;
	typedef signed char		Sint8;
	typedef unsigned short	Uint16;
	typedef signed short	Sint16;

	#define UGKSNDENG_MusicType int

	enum SND_ERRORS
	{
		UGKSNDENG_ERR_NONE,             /* No errors */
		UGKSNDENG_ERR_MEMORY,
		UGKSNDENG_EFREAD,
		UGKSNDENG_EFWRITE,
		UGKSNDENG_EFSEEK,
		UGKSNDENG_UNSUPPORTED,

		//UGK API Errors
		UGKSNDENG_ERR_UNKNOWN,          /* Error unknown */
		UGKSNDENG_ERR_MAX
	};

#elif defined(UGKSNDENG_SDL)
	#include <SDL.h>
	#include <SDL_mixer.h>
	
	#define UGKSNDENG_Sample	Mix_Chunk*
	#define UGKSNDENG_MusicType Mix_Music*

	enum SND_ERRORS
	{
		UGKSNDENG_ERR_NONE,             /* No errors */
		UGKSNDENG_ERR_MEMORY,
		UGKSNDENG_EFREAD,
		UGKSNDENG_EFWRITE,
		UGKSNDENG_EFSEEK,
		UGKSNDENG_UNSUPPORTED,

		//UGK API Errors
		UGKSNDENG_ERR_UNKNOWN,          /* Error unknown */
		UGKSNDENG_ERR_MAX
	};


#endif

#define UGKSND_PLAY_BACK_DEVICES	0
#define UGKSND_RECORDING_DEVICES	1

#endif
