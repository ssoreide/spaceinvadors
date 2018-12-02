/**	Definition of the class UGKkinect. Methods for using a kinect device.
*
*	Prefix: KNT_
*
*	@file	 UGKKinect.h
*	@brief	Class for using a kinect device.
*	@Author	 Jordi Mansanet versión
*	@version 2011-12
*	@NewVersion Francisco Romero 2014-10 - UGK_API conversion and update to NiTE v2.2
*   @References:
*		NiTE Writing an application http://www.openni.ru/resources/index.html
*		OpenNI/NiTE 2 Migration Guide http://com.occipital.openni.s3.amazonaws.com/OpenNI_Migration_Guide_1_to_2.pdf
**/

#ifndef KNT_KINECT //Se borra la macro del Kinect
#define KNT_KINECT //Se define la macro del Kinect

// Be careful, use only one API every time
// The value in the definition is used to correctly identify the definition, if you
// remove the value VS generates error c1017
//#define CHW_USE_KINECT 1
//#define CHW_USE_KINECT_1_3 2

/**
* CHW_USE_KINECT definition for UGKKinect version 2014-10 (using OpenNi/NiTE 2.2)
*/
#ifdef CHW_USE_KINECT

	#include <OpenNI.h> 
	#include <NiTE.h>
	#include <Hardware\UGKHardware.h>

	///We work at UGK namespace
	namespace UGK 
	{

	/**   
	* It defines the types of movements kinect
	* @param enum K_SHIP_MOVE which lists the moves allowed the kinect
	*/
	typedef enum {
		K_STOP_MOVE,	///<Code for stop move
		K_LEFT_MOVE,	///<Code for left move (X)
		K_RIGHT_MOVE,	///<Code for right move (-X)
		K_UP_MOVE,		///<Code for up move (Y)
		k_DOWN_MOVE,	///<Code for down move (-Y)
		K_FORWARD_MOVE,	///<Code for forward move (-Z)
		K_BACKWARD_MOVE,///<Code for backward move (Z)
		K_MAX_MOVE		///<Amount of DIFERENT MOVEMENTS the player has
	} K_SHIP_MOVE;

	/**   
	* It defines the types of kinect's messages
	* @param enum KNT_KinectMsg which lists the message allowed the kinect
	*/
	typedef enum {
		KNT_BAD_INIT,
		KNT_BAD_TRACKER,
		KNT_WAVE_OR_CLICK,
		KNT_BAD_FRAME,
		KNT_LEFT,
		KNT_CENTER,
		KNT_RIGHT,
		KNT_UP,		
		kNT_DOWN,	
		KNT_FORWARD,	
		KNT_BACKWARD,
		KNT_WRONG_VALUE_SLIDER,
		KNT_ERROR_MAX_MSG
	} KNT_KinectMsg;

	#define KNT_SENSIBILITY_DEFAULT 50.0f; ///<Sensibility range by default for LEFT-CENTER-RIGTH, UP-CENTER-DOWN and FORWARD-CENTER-BACKWARD

	/**
	*	CKinect
	*
	*	Manages all the information relative to the kinect device.
	*	Using OpenNi/NiTE 2.2
	*/
	class CKinect: public CHardware
	{
		
		private:

			//Atributes
			
			nite::HandTracker handTracker;				///<Main object of the Hand tracker Algorithm
			nite::Status niteRc;						///<Status of the kinect device
			nite::HandTrackerFrameRef handTrackerFrame;	///<Snapshot (single frame) of the handTracker
			K_SHIP_MOVE g_dir;							///<Last direction 

			UGKS_String direccion_horizontal,
						direccion_vertical,
						direccion_profundidad;

		public: 

			//Atributes
			
			float sensibility;			///<Sensibility range LEFT-CENTER-RIGTH, UP-CENTER-DOWN and FORWARD-CENTER-BACKWARD

			//Methods
			
			CKinect(void);				///<Constructor of the class			
			~CKinect(void);				///<Destructor of the class
			
			//Virtual methods redefined
			CHW_HW_STATUS	findHardware	();			///<Find kinect
			UGKS_String		getProperties	();			///<Get kinect properties
			CHW_HW_STATUS	Init			(void);		///<start kinect
			void			Finish			();			///<Exit kinect

			bool waitKinect();			///<kinect is waiting to person perform wave gesture
			K_SHIP_MOVE updateKinect();	///<kinect returns new hand position (hand movement)

	}; //CKinect

	} //namespace UGK



/**
* CHW_USE_KINECT_1_3 definition for UGKKinect version 2011-12 (using OpenNi/NiTE 1.3)
*/
#elif defined(CHW_USE_KINECT_1_3)

	#include <Hardware\UGKHardware.h>
	
	//-----------------------------------------------------------------------------
	// Headers
	//-----------------------------------------------------------------------------

	// OpenNI headers
	#include <XnOpenNI.h> //Libreria para Kinect NI(Interaccion Humana)
	// NITE headers
	#include <XnCppWrapper.h>
	#include <XnVHandPointContext.h>
	#include <XnVSessionManager.h>
	#include <XnVFlowRouter.h>
	#include <XnVSelectableSlider1D.h>

	#include "UGKKinect_signal_catch.h"

	namespace UGK 
	{
		/**   
		* It defines the types of movements kinect
		* @param enum K_SHIP_MOVE which lists the moves allowed the kinect
		*/
		typedef enum {
			K_LEFT_MOVE,	// Code for left move
			K_STOP_MOVE,	// Code for stop move
			K_RIGHT_MOVE,	// Code for right move
			K_MAX_MOVE	// Amount of extra lasers the player has
		} K_SHIP_MOVE;

		/**   
		* It defines the types of kinect's messages
		* @param enum KNT_KinectMsg which lists the message allowed the kinect
		*/
		typedef enum {
			KNT_BAD_ITEM,
			KNT_SLIDER_BAD_DIR,
			KNT_WRONG_DIR,
			KNT_LEFT,
			KNT_CENTER,
			KNT_RIGHT,
			KNT_WRONG_VALUE_SLIDER,
			KNT_INIT_FROM_XML,
			KNT_INIT_FROM_XML_FILE,
			KNT_FIND_DEPTH_GEN,
			KNT_COULD_NOT_INIT_SESSION,
			KNT_WAVE_GESTURE,
			KNT_HIT_ANY_2_EXIT,
			KNT_ERROR_MAX_MSG
		} KNT_KinectMsg;


		/**
		*	CKinect
		*
		*	Manages all the information relative to the kinect device.
		*	Using OpenNi/NiTE 1.5
		*/
		class CKinect : public CHardware 
		{

		private:

			/**   
			 * Starts an example of kinect to use
			*/
			//#define SAMPLE_XML_FILE "C:/Program Files/PrimeSense/NITE/Data/Sample-Tracking.xml"
			//#define SAMPLE_XML_FILE_LOCAL "Sample-Tracking.xml"
			#define SAMPLE_XML_FILE "C:/Program Files/PrimeSense/NITE/Data/SamplesConfig.xml"
			#define SAMPLE_XML_FILE_LOCAL "SamplesConfig.xml"

			/**   
			* We define a function of connectivity Kinect review
			*/
			#define CHECK_RC(rc, what)											
				if (rc != XN_STATUS_OK)											
			{																
				printf("%s failed: %s\n", what, xnGetStatusString(rc));		
				return rc;													
			}

			/**   
			* We define a function for review of errors that are generated with the Kinect
			*/
			#define CHECK_ERRORS(rc, errors, what)		
				if (rc == XN_STATUS_NO_NODE_PRESENT)	
				{										
					XnChar strError[1024];				
					errors.ToString(strError, 1024);	
					printf("%s\n", strError);			
					return (rc);						
				}

			//-----------------------------------------------------------------------------
			// Callbacks
			//-----------------------------------------------------------------------------
			void XN_CALLBACK_TYPE MainSlider_OnSelect(XnInt32 nItem, XnVDirection dir, void* cxt); ///<detect selection
			void XN_CALLBACK_TYPE MainSlider_OnValueChange(XnFloat fValue, void* cxt); ///<detect hand position inside the slider
			void XN_CALLBACK_TYPE MainSlider_OnActivate(void* cxt); ///<Activo  
			void XN_CALLBACK_TYPE MainSlider_OnDeactivate(void* cxt); ///<Desactivado
			void XN_CALLBACK_TYPE MainSlider_OnPrimaryCreate(const XnVHandPointContext* hand, const XnPoint3D& ptFocus, void* cxt);
			void XN_CALLBACK_TYPE MainSlider_OnPrimaryDestroy(XnUInt32 nID, void* cxt);

		public:

			//Methods
			void Init ();

			UGKKinect();					///<Constructor of the class
			~UGKKinect();					///<Destructor of the class

			XnBool fileExists(const char *fn);
			bool waitKinect();				///<kinect is waiting to person perform wave gesture
			K_SHIP_MOVE updateKinect();		///<kinect returns new hand position

			//Virtual methods redefined
			CHW_HW_STATUS	findHardware	();			///<Find kinect
			CHW_HW_STATUS		Init			(void);		///<start kinect
			void				Finish			();			///<Exit kinect

		}; //CKinect

	} //namespace UGK

#endif //CHW_USE_KINECT_1_3

#endif //KINECT_H