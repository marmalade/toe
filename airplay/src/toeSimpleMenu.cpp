#include <IwTextParserITX.h>
#include <IwResManager.h>
#include "toeSimpleMenu.h"
#include "toeSimpleMenuRoot.h"
#include <toeScriptingSubsystem.h>
#include <toeWorld.h>

using namespace TinyOpenEngine;

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenu);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenu);


namespace TinyOpenEngine
{
}


//Constructor
CtoeSimpleMenu::CtoeSimpleMenu()
{
	menulayout= 0;
	menu= 0;
	scriptSubsystemHash = 0;
}

//Desctructor
CtoeSimpleMenu::~CtoeSimpleMenu()
{
}
//Update subsystem state
void CtoeSimpleMenu::Update(iwfixed dt)
{
	if (menu)
		menu->Update(dt);
}
//Find all entities under the pointer
void CtoeSimpleMenu::PointerHitTest(HitTestContext* htc)
{
}

void CtoeSimpleMenu::UnhandledTouchEvent(TouchContext* touchContext)
{
	if (menu)
		menu->TouchEvent(touchContext);
}
void CtoeSimpleMenu::UnhandledTouchReleaseEvent(TouchContext* touchContext)
{
	if (menu)
		menu->TouchReleaseEvent(touchContext);
}
void CtoeSimpleMenu::UnhandledTouchMotionEvent(TouchContext* touchContext)
{
	if (menu)
		menu->TouchMotionEvent(touchContext);
}
void CtoeSimpleMenu::UnhandledKeyEvent(KeyContext* keyContext)
{
	if (menu)
		menu->KeyEvent(keyContext);
}
//Render image on the screen surface
void CtoeSimpleMenu::Render()
{
	if (menu)
	{
		menu->Render();
	}
}

//Prepare subsystem
void CtoeSimpleMenu::Initialize(CtoeWorld*w)
{
	CtoeSubsystem::Initialize(w);
	if (menulayout)
	{
		if (!menu)
		{
			menu = (CtoeSimpleMenuRoot*)IwGetResManager()->GetResHashed(menulayout,"CtoeSimpleMenuRoot");
			if (menu)
			{
				menu->Initialize(this);
			}
		}
	}
}

void CtoeSimpleMenu::Eval(void*item, CtoeScriptableClassDeclaration*d, const char*s)
{
	if (!scriptSubsystemHash)
		return;
	ItoeScriptingSubsystem* i = dynamic_cast<ItoeScriptingSubsystem*>(toeWorld->GetSubsystem(scriptSubsystemHash));
	if (i)
	{
		i->Eval(s, item, d);
	}
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenu::Serialise ()
{
	CtoeSubsystem::Serialise();
	IwSerialiseUInt32(menulayout);
	IwSerialiseUInt32(scriptSubsystemHash);
}


#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool CtoeSimpleMenu::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp("menulayout", pAttrName))
	{
		pParser->ReadStringHash(&menulayout);
		return true;
	}
	if (!stricmp("script", pAttrName))
	{
		pParser->ReadStringHash(&scriptSubsystemHash);
		return true;
	}
	
	return CtoeSubsystem::ParseAttribute(pParser,pAttrName);
}
#endif