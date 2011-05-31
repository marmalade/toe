#pragma once

#include <IwGeom.h>
#include <string>
#include <IwString.h>
#include <toeSubsystem.h>
#include <toeSubsystemItems.h>
#include "toeLua.h"
#include "toeScriptingSubsystem.h"

namespace TinyOpenEngine
{
	class CtoeLuaStateRoot;

	class CtoeLuaState : public CtoeSubsystem, public ItoeScriptingSubsystem
	{
	protected:
		lua_State *L;
		int currentArg;
		int numRes;
		CIwArray<uint32> openScripts;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeLuaState);
		//Constructor
		CtoeLuaState();
		//Desctructor
		virtual ~CtoeLuaState();

		//Prepare subsystem
		virtual void Initialize(CtoeWorld*);
		//Update subsystem state
		virtual void Update(iwfixed dt);
		//Render image on the screen surface
		virtual void Render();

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();

		virtual void RegisterClass(CtoeScriptableClassDeclaration* c);
		virtual void Eval(const char*s, void* instance, CtoeScriptableClassDeclaration*c);

		virtual void ReturnNil();
		virtual void Return();
		virtual void Return(int i);
		virtual void Return(bool i);
		virtual void Return(float i);
		virtual void Return(const char*);
		virtual void Return(void*,CtoeScriptableClassDeclaration*);
		//virtual void Return(const std::string&);
		//virtual void Return(const CIwStringL&);
		//virtual void Return(const CIwStringS&);

		virtual int PopArgInt();
		virtual bool PopArgBool();
		virtual float PopArgFloat();
		virtual const char* PopArgStr();
		virtual void* PopArgClass(CtoeScriptableClassDeclaration*);

	protected:
		static int toeLuaMethodCall(lua_State *L);
		static int toeLuaStaticMethodCall(lua_State *L);
		int CallMethod(CtoeScriptableClassDeclaration* c,CtoeScriptableMethodDeclaration* m,void*o);
#ifdef IW_BUILD_RESOURCES

		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}