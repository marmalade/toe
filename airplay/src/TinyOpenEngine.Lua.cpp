#include "TinyOpenEngine.Lua.h"
#include "toeLuaScript.h"
#include "toeLuaState.h"


using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	bool isTinyOpenEngineLuaInitialized = false;
}

void TinyOpenEngine::toeLuaInit()
{
	if (isTinyOpenEngineLuaInitialized)
		return;
	isTinyOpenEngineLuaInitialized = true;

	#ifdef IW_BUILD_RESOURCES
	IwGetResManager()->AddHandler(new CtoeLuaScriptResHandler);
	#endif

	IW_CLASS_REGISTER(CtoeLuaScript);
	IW_CLASS_REGISTER(CtoeLuaState);
}

void TinyOpenEngine::toeLuaTerminate()
{
	if (!isTinyOpenEngineLuaInitialized)
		return;
	isTinyOpenEngineLuaInitialized = false;
}