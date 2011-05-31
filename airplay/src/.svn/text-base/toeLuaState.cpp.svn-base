#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <TinyOpenEngine.h>
#include "toeLuaState.h"
#include "toeLuaScript.h"
#include "lauxlib.h"

using namespace TinyOpenEngine;

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeLuaState);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeLuaState);


namespace TinyOpenEngine
{
	struct toeLuaUserDataContainer
	{
		void* userData;
	};
	int toeLuaAssert(lua_State *L, int res)
	{
		if (res)
		{
			const char *msg = lua_tostring(L, -1);
			if (!msg) msg = "(error with no message)";
			IwAssertMsg(TOE,false,(msg));
			//fprintf(stderr, "ERROR: %s\n", msg);
			lua_pop(L, 1);
		}
		return res;
	}

	 void toeLuaStackDump (lua_State *L) {
          int i=lua_gettop(L);
          IwTrace(TOE, (" Lua Stack: %d ----------------", i ));
          while(  i   ) {
            int t = lua_type(L, i);
            switch (t) {
              case LUA_TSTRING:
				  IwTrace(TOE, ("%d:`%s'", i, lua_tostring(L, i)));
              break;
              case LUA_TBOOLEAN:
                IwTrace(TOE, ("%d: %s",i,lua_toboolean(L, i) ? "true" : "false"));
              break;
              case LUA_TNUMBER:
                IwTrace(TOE, ("%d: %g",  i, lua_tonumber(L, i)));
             break;
             default:IwTrace(TOE, ("%d: %s", i, lua_typename(L, t))); break;
            }
           i--;
          }
    }

	void toeRegisterLua(lua_State*);

	//typedef struct { T *pT; } userdataType;
	//typedef int (T::*mfp)(lua_State *L);
 // typedef struct { const char *name; mfp mfunc; } RegType;



	// member function dispatcher
  int CtoeLuaState::toeLuaMethodCall(lua_State *L) {

	  
	  //toeLuaUserDataContainer *ud = static_cast<toeLuaUserDataContainer*>(lua_touserdata(L, 1));
	  CtoeScriptableClassDeclaration*c = static_cast<CtoeScriptableClassDeclaration*>(lua_touserdata(L, lua_upvalueindex(1)));
	  CtoeScriptableMethodDeclaration*m = static_cast<CtoeScriptableMethodDeclaration*>(lua_touserdata(L, lua_upvalueindex(2)));
	  CtoeLuaState*state = static_cast<CtoeLuaState*>(lua_touserdata(L, lua_upvalueindex(3)));

	  //toeLuaUserDataContainer *ud = static_cast<toeLuaUserDataContainer*>(luaL_checkudata(L, 0, c->GetClassName()));
	  state->currentArg = 0;
	  int r = state->CallMethod(c,m,state->PopArgClass(c));
	  return r;
  }
	// member function dispatcher
  int CtoeLuaState::toeLuaStaticMethodCall(lua_State *L) {

	  CtoeScriptableClassDeclaration*c = static_cast<CtoeScriptableClassDeclaration*>(lua_touserdata(L, lua_upvalueindex(1)));
	  CtoeScriptableMethodDeclaration*m = static_cast<CtoeScriptableMethodDeclaration*>(lua_touserdata(L, lua_upvalueindex(2)));
	  CtoeLuaState*state = static_cast<CtoeLuaState*>(lua_touserdata(L, lua_upvalueindex(3)));

	  //toeLuaUserDataContainer *ud = static_cast<toeLuaUserDataContainer*>(luaL_checkudata(L, 0, c->GetClassName()));
	  state->currentArg = 0;
	  int r = state->CallMethod(c,m,0);
	  return r;
  }
  int CtoeLuaState::CallMethod(CtoeScriptableClassDeclaration* c,CtoeScriptableMethodDeclaration* m,void*o)
  {
	  int prevNumRes = numRes;
	  int prevcurrentArg = currentArg;
	  numRes = 0;
	  m->Call(this,c, o);
	  int r = numRes;
	  numRes = prevNumRes;
	  currentArg = prevcurrentArg;
	  return r;
  }
  // create a new T object and
  // push onto the Lua stack a userdata containing a pointer to T object
  static int new_T(lua_State *L) {
    //lua_remove(L, 1);   // use classname:new(), instead of classname.new()
    //T *obj = new T(L);  // call constructor for T objects
    //userdataType *ud =
    //  static_cast<userdataType*>(lua_newuserdata(L, sizeof(userdataType)));
    //ud->pT = obj;  // store pointer to object in userdata
    //luaL_getmetatable(L, T::className);  // lookup metatable in Lua registry
    //lua_setmetatable(L, -2);
    //return 1;  // userdata containing pointer to T object
	//  toeLuaStackDump(L);
	  CtoeScriptableClassDeclaration*l = static_cast<CtoeScriptableClassDeclaration*>(lua_touserdata(L, lua_upvalueindex(1)));
	  lua_remove(L, 1);
	  void* instance = l->CreateInstance();
	  toeLuaUserDataContainer *ud = static_cast<toeLuaUserDataContainer*>(lua_newuserdata(L, sizeof(toeLuaUserDataContainer)));
	  ud->userData = instance;
	  luaL_getmetatable(L, l->GetClassName());
	  lua_setmetatable(L, -2);
	 // toeLuaStackDump(L);
	  return 1;
  }

  // garbage collection metamethod
  static int gc_T(lua_State *L) {
	  //CtoeScriptableClassDeclaration*l = static_cast<CtoeScriptableClassDeclaration*>(lua_touserdata(L, lua_upvalueindex(1)));
	  //toeLuaUserDataContainer *ud = static_cast<toeLuaUserDataContainer*>(lua_touserdata(L, 1));
	  //l->DestroyInstance(ud->userData);
	return 0;
  }

  static int tostring_T (lua_State *L) {
	  CtoeScriptableClassDeclaration*l = static_cast<CtoeScriptableClassDeclaration*>(lua_touserdata(L, lua_upvalueindex(1)));
	   toeLuaUserDataContainer *ud = static_cast<toeLuaUserDataContainer*>(lua_touserdata(L, 1));
	   lua_pushstring(L, l->ToString(ud->userData));
   /* char buff[32];
    userdataType *ud = static_cast<userdataType*>(lua_touserdata(L, 1));
    T *obj = ud->pT;
    sprintf(buff, "%p", obj);
    lua_pushfstring(L, "%s (%s)", T::className, buff);*/
    //return 1;

	  return 1;
  }
}
void CtoeLuaState::Return()
{
}
void CtoeLuaState::ReturnNil()
{
	++numRes;
	lua_pushnil(L);
}
void CtoeLuaState::Return(int i)
{
	++numRes;
	lua_pushinteger(L,i);
}
void CtoeLuaState::Return(bool i)
{
	++numRes;
	lua_pushboolean(L,i);
}
void CtoeLuaState::Return(float i)
{
	++numRes;
	lua_pushnumber(L,i);
}
void CtoeLuaState::Return(const char*s)
{
	++numRes;
	if (!s)
		lua_pushnil(L);
	return
		lua_pushstring(L,s);
}
//void CtoeLuaState::Return(const std::string& s)
//{
//	++numRes;
//	lua_pushstring(L,s.c_str());
//}
//void CtoeLuaState::Return(const CIwStringL& s)
//{
//	++numRes;
//	lua_pushstring(L,s.c_str());
//}
//void CtoeLuaState::Return(const CIwStringS& s)
//{
//	++numRes;
//	lua_pushstring(L,s.c_str());
//}
void CtoeLuaState::Return(void*instance,CtoeScriptableClassDeclaration*l)
{
	++numRes;
	if (!instance)
	{
		lua_pushnil(L);
		return;
	}
	toeLuaUserDataContainer *ud = static_cast<toeLuaUserDataContainer*>(lua_newuserdata(L, sizeof(toeLuaUserDataContainer)));
	ud->userData = instance;
	luaL_getmetatable(L, l->GetClassName());
	lua_setmetatable(L, -2);
}
bool CtoeLuaState::PopArgBool()
{
	++currentArg;
	return luaL_checkint(L,currentArg) != 0;
}
int CtoeLuaState::PopArgInt()
{
	++currentArg;
	return luaL_checkint(L,currentArg);
}
float CtoeLuaState::PopArgFloat()
{
	++currentArg;
	return (float)luaL_checknumber(L,currentArg);
}
const char* CtoeLuaState::PopArgStr()
{
	++currentArg;
	return luaL_checkstring(L,currentArg);
}
void* CtoeLuaState::PopArgClass(CtoeScriptableClassDeclaration*c)
{
	++currentArg;
	toeLuaUserDataContainer* ud = (toeLuaUserDataContainer*)luaL_checkudata(L,currentArg,c->GetClassName());
	if (!ud)
		return ud;
	return ud->userData;
}

//Constructor
CtoeLuaState::CtoeLuaState()
{
	L = 0;
	numRes = 0;
	currentArg = 0;
}

//Desctructor
CtoeLuaState::~CtoeLuaState()
{
	if (L)
	{
		lua_close(L);
		L = 0;
	}
}
//Update subsystem state
void CtoeLuaState::Update(iwfixed dt)
{

}


//Render image on the screen surface
void CtoeLuaState::Render()
{
}

//Prepare subsystem
void CtoeLuaState::Initialize(CtoeWorld*w)
{
	CtoeSubsystem::Initialize(w);
	L = lua_open();
	luaopen_base(L);
	luaopen_table(L);
	//luaopen_io(L);
	luaopen_string(L);
	//luaopen_math(L);
	toeRegisterLua(L);

	toeRegisterScriptableClasses(this);

	for (uint32 i=0; i<openScripts.size(); ++i)
	{
		CtoeLuaScript* s = (CtoeLuaScript*)IwGetResManager()->GetResHashed(openScripts[i], "CtoeLuaScript");
		if (s)
		{
			if (!toeLuaAssert(L, luaL_loadstring(L, s->GetText())))
			{
				toeLuaAssert(L, lua_pcall(L, 0, LUA_MULTRET, 0));
			}
		}
	}
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeLuaState::Serialise ()
{
	CtoeSubsystem::Serialise();
	openScripts.SerialiseHeader();
	for (uint32 i=0; i<openScripts.size(); ++i)
		IwSerialiseUInt32(openScripts[i]);
}
void CtoeLuaState::RegisterClass(CtoeScriptableClassDeclaration* c)
{
	lua_newtable(L);
    int methods = lua_gettop(L);

    luaL_newmetatable(L, c->GetClassName());
    int metatable = lua_gettop(L);

	// store method table in globals so that
    // scripts can add functions written in Lua.
    lua_pushstring(L, c->GetClassName());
    lua_pushvalue(L, methods);
    lua_settable(L, LUA_GLOBALSINDEX);

	lua_pushliteral(L, "__metatable");
    lua_pushvalue(L, methods);
    lua_settable(L, metatable);  // hide metatable from Lua getmetatable()

	lua_pushliteral(L, "__index");
    lua_pushvalue(L, methods);
    lua_settable(L, metatable);

    lua_pushliteral(L, "__tostring");
	lua_pushlightuserdata(L, (void*)c);
	lua_pushcclosure(L, tostring_T, 1);
    lua_settable(L, metatable);

    lua_pushliteral(L, "__gc");
	lua_pushlightuserdata(L, (void*)c);
	lua_pushcclosure(L, gc_T, 1);
    lua_settable(L, metatable);

    lua_newtable(L);                // mt for method table
    int mt = lua_gettop(L);
    lua_pushliteral(L, "__call");
	lua_pushlightuserdata(L, (void*)c);
	lua_pushcclosure(L, new_T, 1);
    lua_pushliteral(L, "new");
    lua_pushvalue(L, -2);           // dup new_T function
    lua_settable(L, methods);       // add new_T to method table
    lua_settable(L, mt);            // mt.__call = new_T
    lua_setmetatable(L, methods);


	int maxm = c->GetMethodsCount();
	for (int i=0; i<maxm; ++i)
	{
		CtoeScriptableMethodDeclaration* m = c->GetMethod(i);
		lua_pushstring(L, m->GetMethodName());
		lua_pushlightuserdata(L, (void*)c);
		lua_pushlightuserdata(L, (void*)m);
		lua_pushlightuserdata(L, (void*)this);
		if (m->IsStatic())
			lua_pushcclosure(L, toeLuaStaticMethodCall, 3);
		else
			lua_pushcclosure(L, toeLuaMethodCall, 3);
		lua_settable(L, methods);
	}
    // fill method table with methods from class T
    //for (RegType *l = T::methods; l->name; l++) {
    ///* edited by Snaily: shouldn't it be const RegType *l ... ? */
    //  lua_pushstring(L, l->name);
    //  lua_pushlightuserdata(L, (void*)l);
    //  lua_pushcclosure(L, thunk, 1);
    //  lua_settable(L, methods);
    //}

    lua_pop(L, 2);  // drop metatable and method table

}
void CtoeLuaState::Eval(const char*s,void* instance, CtoeScriptableClassDeclaration*c)
{
	std::string str = std::string("return function (self)\n")+s+"\nend";
	if (!toeLuaAssert(L, luaL_loadstring(L, str.c_str())))
	{
		if (!toeLuaAssert(L, lua_pcall(L, 0, LUA_MULTRET, 0)))
		{
			Return(instance,c);
			--numRes;
			toeLuaAssert(L, lua_pcall(L, 1, LUA_MULTRET, 0));
		}
	}
	else
	{
	}
	//int res = luaL_dostring(L,s);
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool CtoeLuaState::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp("open", pAttrName))
	{
		uint32 openScript;
		pParser->ReadStringHash(&openScript);
		openScripts.push_back(openScript);
		return true;
	}
	return CtoeSubsystem::ParseAttribute(pParser,pAttrName);
}
#endif