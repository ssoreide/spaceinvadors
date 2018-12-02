/** KinectManager class and methods for using one or more kinect devices.
*
*	Prefix: KNTM_
*
*	@file	 UGKKinectManager.h
*	@brief	Class for using one or more kinect devices (only one for this first version. 
*			Also is used HR counters for delaying the sensitiveness of the device.
*	@version: 2011-12
*	@NewVersion Francisco Romero 2014-12 - UGKKinectManager like polling controler using UGKKinect.
*
*   @References:
*		NiTE Writing an application http://www.openni.ru/resources/index.html
*		OpenNI/NiTE 2 Migration Guide http://com.occipital.openni.s3.amazonaws.com/OpenNI_Migration_Guide_1_to_2.pdf
**/

#ifndef KNTM_KINECT //Se borra la macro del Kinect
#define KNTM_KINECT //Se define la macro del Kinect


#include <UGKKinect.h>

/**
* CHW_USE_KINECT definition for UGKKinectManager and UGKKinect version 2014-10 (using OpenNi/NiTE 2.2)
*/
#ifdef CHW_USE_KINECT
#include <RTDeskEntity.h>

	namespace UGK 
	{

		#define KNTM_KINECT_MIN_UPDATETIME	40.0f	//ms. None of the kinect devices should update over this period of time.

		/**
		*	CKinectManager
		*
		*	Manages all the information relative to the kinect device.
		*	Using OpenNi/NiTE 2.2
		*/
		class CKinectManager: public CHardware,  public RTDESK_CEntity 
		{
		private:

			CKinect g_kinect;

		public:
			//Atributes

			// Hardware hereditage
			/*
			cHRTimerManager *HRTimerManager;		///<HR counters for delaying the sensitiveness of the device

			/// Type of hardware: sound, graphics, I/O,...
			unsigned short int	SubTypeHW;
			CHW_HARDWARE_TYPE	TypeHW;

			/// The hardware is active. Implicitly it needs to be alive in order to be active
			bool				Active;
			unsigned char	ActionSize;
			*/

			//Methods

			CKinectManager(void);	///<Constructor of the class
			~CKinectManager(void);	///<Destructor of the class

			CHW_HW_STATUS Init (void);
			bool wait(void);
			K_SHIP_MOVE update(void); ///< transform hand events to keyboard events
			void cleanupExit();			///<Exit kinect

			void SetDelay		(HRT_Time D);
			void SetDelay		(float F);

			//RTDesk virtual Function redefinition for later versions
			void ReceiveMessage(RTDESK_CMsg *pMsg);

		};

	} // namespace UGK


/**
* CHW_USE_KINECT_1_3 definition for UGKKinectManager and UGKKinect version 2011-12 (using OpenNi/NiTE 1.3)
*/
#elif defined CHW_USE_KINECT_1_3

// Just for enjoy!!

#endif //CHW_USE_KINECT_1_3



#endif //KNTM_KINECT