#pragma once

#include "toeScriptingSubsystem.h"

namespace TinyOpenEngine
{
	class CtoeConfig
	{
	public:
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();

		static void SetInteger(const char* name, int val);
		static void SetFloat(const char* name, float val);
		static void SetString(const char* name, const char* val);

		static bool IsExist(const char* name);

		static int GetInteger(const char* name);
		static float GetFloat(const char* name);
		static const char* GetString(const char* name);

		static void Load();
		static void Save();
		static void Close();
	};
}
