#pragma once

#include "toeScriptingSubsystem.h"

namespace TinyOpenEngine
{
	class CtoeNet
	{
	public:
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();

		static CIwManaged* GetResourceByName(const char* id,const char* type);

		static std::string DownloadString(const char* s);
	};
}
