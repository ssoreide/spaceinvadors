/**
*	@file	 UGKDeviceManager.cpp
*	@author  Ramón Mollá
*	@date	 2017-03
*   @version 1.0
*
*	@brief	Class that manages all HW / devices involved with our application
*
*	Prefix: UGKDM_
**/


#ifndef UGKDM_DEVICE_MANAGER
#define UGKDM_DEVICE_MANAGER

#include <UGKHardware.h>

namespace UGK
{
	class CDeviceManager
	{
		UGKDM_HardwareVector	hardware_vector;
		std::vector <bool>		active_vector;

	public:
		CDeviceManager();
		~CDeviceManager();
		void pushBack(CHardware *hw);
		void deleteHardware(int index);
		void verificationHardware(int i);
		void verification();
		UGKDM_HardwareVector getHardware();
		CHardware*			 getHardware(int index);
		bool isActive(int index);

		CHardware * NewHW(CHW_HARDWARE_TYPE HWType);
	};
}

#endif