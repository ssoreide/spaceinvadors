#include "windows.h"
#include "DebugLog.h"
//#include <debugapi.h>

void DebugLog(const std::wstring& logmsg) {
	OutputDebugString(logmsg.c_str());
}

void DebugLog(const std::string& logmsg) {
	std::wstring wsTmp(logmsg.begin(), logmsg.end());
	DebugLog(wsTmp);
}