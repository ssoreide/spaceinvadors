/** Header with definitions needed for the management of any generic web camera
*	Prefix: UGKWEBCAM_H	for class Web Cam
*	@file	UGKWebCam.h
*	@brief	Base class for the management of any generic web camera
*	Prefix  UGKWC_
*	@author Javier Jorge
*	@date	2015-01-30
*/
#ifndef UGKWEBCAM_H
#define UGKWEBCAM_H
#include <UGKHardware.h>


//#define UGKWC_OPENCV
//#define UGKWC_DLIB

#ifdef UGKWC_OPENCV
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
#elif defined UGKWC_DLIB
#endif


typedef enum
{
	UGKWC_OK,
	UGKWC_ERROR,
	UGKWC_MAX_RESULTS
} UGKWC_RESULT;

namespace UGK
{
	/**
	*	UGKWebCam

	*	Manages all the information relative to the general game application.
	*	It is implemented as a singleton. This is not the game singleton
	*/

	class UGK_API UGKWebCam : public CHardware
	{
		
		public:
			unsigned int XRes, YRes;

			//Methods
			UGKWebCam ();		///<Constructor of the class
			~UGKWebCam () {}	///<Destructor of the class

			//Virtual methods redefined
			CHW_HW_STATUS		findHardware();		///<Find cam
			CHW_HW_STATUS		Init(void);			///<start cam

			//Public methods
			//Face detection
			UGKWC_RESULT	simpleDetectAndDraw();

#ifdef UGKWC_OPENCV
			void detectAndDraw( Mat& img, CascadeClassifier& cascade,
						CascadeClassifier& nestedCascade,
						double scale, bool tryflip );

			//ACHTUNG: mask Point class depending of using OpenCV o Dlib
			Point	getPosition();
			void	detectAndDraw( Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale);
			Point	detectAndGetPosition( Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale);
#elif defined UGKWC_DLIB
#endif

			//Take a picture
			void showPicture();
			void takePicture();

			////Mat takePicture_img();
			void showVideo();
			bool getCapture();

		private:
			
#ifdef UGKWC_OPENCV
			double		scale;
			CvCapture*	capture;
			Mat			image;
			Mat			frame, frameCopy;
			IplImage*	iplImg;
#elif defined UGKWC_DLIB
#endif
	};	
}
#endif