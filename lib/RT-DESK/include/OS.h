/**
/**	OS.h: Definition of the Operating System the API is running on
*
* Copyright(C) 2016
*
*	Prefix: OS_

* @Author:	Dr. Ramón Mollá Vayá
* @Date:	02/2016
* @Version: 2.0
*
* Update:
* Date:
* Version:
* Changes:
*
*/

#ifndef OS_OPERATINGSYTEM
#define OS_OPERATINGSYTEM

#define HRT_STL

#ifdef HRT_STL
#include <string>
#define HRT_String std::string
#endif

#define OS_MSWINDOWS
//#define OS_LINUX
//#define OS_OSX
//#define OS_ANDROID

#define OS_32BITS
//#define OS_64BITS

#ifdef	OS_MSWINDOWS

#define DLL_EXPORTS
//#define DLL_IMPORTS

#ifdef DLL_EXPORTS
#define HRT_API __declspec(dllexport)
#elif defined(DLL_IMPORTS)
#define HRT_API __declspec(dllimport)
#else
//For .lib files. No DLL. Static linking
#define UGKMMO_API
#define UGK_API
#endif

#ifndef HRT_STL	
#include <atlstr.h>
#define HRT_String CString
#endif

#define HRT_MAX_TIME LLONG_MAX

#elif	defined(OS_LINUX)
#elif	defined(OS_OSX)
#elif	defined(OS_ANDROID)
#endif

#endif
