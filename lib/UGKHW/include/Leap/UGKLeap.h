/**	
*	Prefix: 
*	@Author: Juan Cerrón, Cédric Marco
*	@version: 2013-14
**/

#ifndef USELEAP_H
#define USELEAP_H

#include <UGKLeapGestureTreatment.h>
#include <UGKHardware.h>

namespace UGK
{
	class UGK_API  UseLeap : public CHardware
	{

	  public:
		UseLeap();		///<Constructor of the class
		~UseLeap() {}	///<Destructor of the class
	
		//Virtual methods redefined
		CHW_HW_STATUS	findHardware();		///<Find Leap
		CHW_HW_STATUS		Init(void);			///<start Leap
		void				Finish();			///<Exit Leap

	private:
		Leap::Controller	controller;
		CGestureTreatment	detectorMovimientos;
	};
}
#endif