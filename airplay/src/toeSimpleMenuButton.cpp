#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeSimpleMenuButton.h"
#include "toeSimpleMenuRoot.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuButton);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuButton);

//Constructor
CtoeSimpleMenuButton::CtoeSimpleMenuButton()
{

}
//Desctructor
CtoeSimpleMenuButton::~CtoeSimpleMenuButton()
{
}
uint32 CtoeSimpleMenuButton::GetElementNameHash()
{
	static uint32 name = IwHashString("BUTTON");
	return name;
}
//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeSimpleMenuButton::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeSimpleMenuButton> d ("CtoeSimpleMenuItem",
			ScriptTraits::Method("GetRoot", &CtoeSimpleMenuButton::GetRoot),
			ScriptTraits::Method("GetChildAt", &CtoeSimpleMenuButton::GetChildAt),
			ScriptTraits::Method("GetChildItemsCount", &CtoeSimpleMenuButton::GetChildItemsCount),
			0);
	return &d;
}