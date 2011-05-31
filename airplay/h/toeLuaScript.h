#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>
#include "toeLua.h"

namespace TinyOpenEngine
{
	class CtoeLuaScript : public CIwResource
	{
	private:
		char* buffer;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeLuaScript);
		//Constructor
		CtoeLuaScript();
		//Desctructor
		virtual ~CtoeLuaScript();

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();

		void AssignBuffer(char* buf);
		const char* GetText() const {return buffer;}
	};

#ifdef IW_BUILD_RESOURCES
	class CtoeLuaScriptResHandler : public CIwResHandler
	{
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeLuaScriptResHandler);

		//Constructor
		CtoeLuaScriptResHandler();
		//Desctructor
		virtual ~CtoeLuaScriptResHandler();

		//Buid resource method
		virtual CIwResource*	Build(const CIwStringL& pathname);
	};
#endif
}