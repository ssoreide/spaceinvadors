/** 
 *	@file UGKRaphicsCard.h
 *	Header with definitions needed for the management of the graphic card
 *
 *	Prefix: UGKCGC_	for class graphic card
 *
 *	@file UGKGraphicsCard.h
 *	@brief Base class for the management of the graphic card
 *	@author Ramón Mollá
 *	@author Sergio Laguna
 *	@version 2015-11
 */

#ifndef UGKCGC_GRAPHIC_CARD
#define UGKCGC_GRAPHIC_CARD

#include <UGKHardware.h>

#ifdef UGKOS_WINDOWS
	#ifndef WINDOWS_LOADED
	#define WINDOWS_LOADED
	#include <windows.h>
	#endif
#define UGKCGC_PIXEL_FORMAT PIXELFORMATDESCRIPTOR
#define UGKCGC_WINDOW_HANDLE HWND
#define UGKCGC_DEVICE_CONTEXT_HANDLE HDC

#elif	defined(UGKOS_LINUX)
#elif	defined(UGKOS_OSX)
#elif	defined(UGKOS_ANDROID)
#endif

// Video Graphics Array
#define UGKCGC_VGA_HOR_RES		640		///< VGA horizontal resolution
#define UGKCGC_VGA_VER_RES		480		///< VGA vertical resolution
// Super Video Graphics Array
#define UGKCGC_SVGA_HOR_RES		800		///< SVGA horizontal resolution
#define UGKCGC_SVGA_VER_RES		600		///< SVGA vertical resolution
// Extended Graphics Array
#define UGKCGC_XGA_HOR_RES		1024	///< XGA horizontal resolution
#define UGKCGC_XGA_VER_RES		768		///< XGA vertical resolution
// Super Extended Graphics Array
#define UGKCGC_SXGA_HOR_RES		1280	///< SXGA horizontal resolution
#define UGKCGC_SXGA_VER_RES		1024	///< SXGA vertical resolution
#define UGKCGC_SXGA_VER_RES43	960		///< SXGA vertical resolution in 4:3
// Widescreen Super Extended Graphics Array Plus
#define UGKCGC_WSXGA_HOR_RES	1680	///< WSXGA horizontal resolution
#define UGKCGC_WSXGA_VER_RES	1050	///< WSXGA vertical resolution
// Ultra Extended Graphics Array
#define UGKCGC_UXGA_HOR_RES		1600	///< UXGA horizontal resolution
#define UGKCGC_UXGA_VER_RES		1200	///< UXGA vertical resolution
// Full High Definition
#define UGKCGC_FHD_HOR_RES		1920	///< FullHD horizontal resolution
#define UGKCGC_FHD_VER_RES		1080	///< FullHD vertical resolution
// Wide Ultra Extended Graphics Array
#define UGKCGC_WUXGA_HOR_RES	1920	///< WUXGA horizontal resolution
#define UGKCGC_WUXGA_VER_RES	1200	///< WUXGA vertical resolution

#define UGKCGC_DEFAULT_DEPTH	24		///< Color depth

class UGK_API CDeskTop
{
public:
	UGKCGC_WINDOW_HANDLE			hDeskTop;
	UGKCGC_DEVICE_CONTEXT_HANDLE	hDeskTopDC;

	int Width,			///< Width of the desktop
		Height,			///< Height of the desktop
		BitsPerPixel;	///< Color depth of the desktop

#ifdef	UGKOS_WINDOWS

CDeskTop()
	{
		hDeskTop	= GetDesktopWindow();
		hDeskTopDC	= GetDC(hDeskTop);
		Width		= GetDeviceCaps(hDeskTopDC, PLANES) * GetDeviceCaps(hDeskTopDC, HORZRES);
		Height		= GetDeviceCaps(hDeskTopDC, PLANES) * GetDeviceCaps(hDeskTopDC, VERTRES);
	}

	~CDeskTop(){};
#elif	defined(UGKOS_LINUX)
#elif	defined(UGKOS_OSX)
#elif	defined(UGKOS_ANDROID)
#endif

	void SystemMetrics();	///< Gets the desktop information and saves it
};

using namespace UGK;

/**
 *	Manages all the information relative to the general game application.
 *	It is implemented as a singleton. This is not the game singleton
 */
class UGK_API CGraphicCard : public CHardware
{
protected:
	bool	HWAccelerated;	///< The graphic card is accelerated by hardware
	int		bitsPerPixel;	///< Bits Per Pixel

	UGKCGC_PIXEL_FORMAT	PFD;

	void	DetectHWAcceleration();  ///< Detects if the grphics card is accelerated by hardware

public:

	CDeskTop DeskTop;

	// Methods
	CGraphicCard();		///< Constructor of the class
	~CGraphicCard(){};	///< Destructor of the class

	// Public methods
	inline bool IsHWAccelerated() { return HWAccelerated; };	///< Returns if the graphics card is accelerated
	bool ChangeScreenResolution(int Width, int Height, int bitsPerPixel);

	/**
	 * Changes screen resolution using the information about the desktop
	 */
	bool ChangeScreenResolution() { return ChangeScreenResolution(DeskTop.Width, DeskTop.Height, bitsPerPixel); }

	void SystemMetrics();	///< Gets the desktop information and saves it

	//
	#ifdef UGKOS_OPENGL
		/**
		*	@fn GetGraphicVendor
		*	Returns the vendor information
		*/
		UGKS_String GetOpenGLVendor();

		/**
		*	@fn GetGraphicRenderer
		*	Returns the renderer information
		*/
		UGKS_String GetOpenGLRenderer();

		/**
		*	@fn GetOpenGLVersion
		*	Returns the OpenGL version
		*/
		UGKS_String GetOpenGLVersion();

		/**
		*	@fn GetOpenGLExtensions
		*	Returns the supported extensions of OpenGL
		*/
		UGKS_String GetOpenGLExtensions();

	#elif defined UGKOS_DIRECTX
	#endif

	#ifdef UGKOS_WINDOWS
		/**
		*	@fn GetScreenResolution
		*	Returns the actual screen resolution
		*	@param[out] width
		*	@param[out] height
		*/
		void GetScreenResolution(int &width, int &height);
	#elif defined UGKOS_OSX
	#elif defined UGKOS_LINUX
	#elif defined UGKOS_ANDROID
	#endif
	//
};

#endif