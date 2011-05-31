#include <IwManaged.h>
#include "toeScriptingSubsystem.h"
#include "toeScriptingBinds.h"

using namespace TinyOpenEngine;

ItoeScriptingSubsystem::~ItoeScriptingSubsystem()
{
	
}


CtoeScriptableClassDeclaration* TinyOpenEngine::ScriptTraits::GetManagedInstanceClassDescription(CIwManaged* t)
{
	static  TtoeScriptableClassDeclaration<CIwManaged> d ("CIwManaged",
		ScriptTraits::Method("GetClassName", &CIwManaged::GetClassName),
			0);
	return &d;
}
