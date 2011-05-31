#pragma once

#include <string>

class CIwTextParserITX;

namespace TinyOpenEngine
{
	class CtoeWorld;
	class ItoeScriptingSubsystem;
	class CtoeScriptableClassDeclaration;

	void toeInit();
	void toeTerminate();
	void toeRunWorld(CtoeWorld*);
	void toeOpenWorld(const char*resource,const char*world);
	void toeOpenGroupWorld(const char*resource);
	void toeCloseWorld();
	void toeTrace(const char*, ...);
	bool toeIsTraceEnabled();
	void toeRegisterClass(CtoeScriptableClassDeclaration*);
	void toeRegisterScriptableClasses(ItoeScriptingSubsystem*);

	void toeSerialiseString(std::string & s);
	void toeReadString(CIwTextParserITX* pParser, std::string * s);
}