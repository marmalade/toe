#pragma once

#include "toeScriptingSubsystem.h"

namespace TinyOpenEngine
{
	class CtoeUtils
	{
	public:
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();

		static CIwManaged* GetResourceByName(const char* id,const char* type);

		static const char* GetDeviceID();
		static const char* GetDevicePhone();
		static const char* GetDeviceOS();
		static const char* GetDeviceClass();
		static const char* GetDeviceArchitecture();
		static const char* GetDeviceS3eVersion();
		static int GetDeviceTotalRam();
		static int GetDeviceFreeRam();
		static void AssertMsg(const char *m);
		static const char* ReadString(const char * t,const char * def);
		static unsigned int DecodeUtf8(const void * p, unsigned int & returnValue);
		static std::string UrlEncode(const char* s);
	};
}
