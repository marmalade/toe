#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwHTTP.h>
#include "TinyOpenEngine.h"
#include "toeLuaState.h"
#include "s3eOSReadString.h"

using namespace TinyOpenEngine;


namespace TinyOpenEngine
{
	void toeExitApplication();
	int toeLuaExit(lua_State* L)
	{
		toeExitApplication();
		return 0;
	}
	int toeLuaCloseWorld(lua_State* L)
	{
		toeCloseWorld();
		return 0;
	}
	int toeLuaOpenWorld(lua_State* L)
	{
		const char* s1 = luaL_checkstring(L,1);
		const char* s2 = luaL_checkstring(L,2);
		toeOpenWorld(s1,s2);
		return 0;
	}
	int toeLuaOpenGroupWorld(lua_State* L)
	{
		const char* s1 = luaL_checkstring(L,1);
		toeOpenGroupWorld(s1);
		return 0;
	}
	
	int toeLuaDeviceCheckPauseRequest(lua_State* L)
	{
		lua_pushboolean(L,s3eDeviceCheckPauseRequest());
		return 0;
	}


	int toeUrlEncode(lua_State* L)
	{
		const char* s1 = luaL_checkstring(L,1);
		std::string s2;
		while (*s1)
		{
			if (*s1 == ' ')
				s2+=('+');
			else
				s2+=(*s1);
			++s1;
		}
		lua_pushstring(L,s2.c_str());
		return 1;
	}

	void toeRegisterLua(lua_State* state)
	{
		lua_register(state,"toeCloseWorld",toeLuaCloseWorld);
		lua_register(state,"toeOpenWorld",toeLuaOpenWorld);
		lua_register(state,"toeOpenGroupWorld",toeLuaOpenGroupWorld);
		//lua_register(state,"toeReadString",toeLuaReadString);
		//lua_register(state,"toeAssertMsg",toeLuaAssertMsg);

		
		//lua_register(state,"toeUrlEncode",toeUrlEncode);
		
		lua_register(state,"toeExit",toeLuaExit);
		lua_register(state,"toeDeviceCheckPauseRequest",toeLuaDeviceCheckPauseRequest);
		//luaL_register(state,0, toeModule);
	}
}

