#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "TinyOpenEngine.h"
#include "toeSimpleMenuClickable.h"
#include "toeSimpleMenuRoot.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuClickable);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuClickable);

//Constructor
CtoeSimpleMenuClickable::CtoeSimpleMenuClickable()
{

}
//Desctructor
CtoeSimpleMenuClickable::~CtoeSimpleMenuClickable()
{
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuClickable::Serialise ()
{
	CtoeSimpleMenuItem::Serialise();
	toeSerialiseString(onClick);
}
void CtoeSimpleMenuClickable::Prepare(toeSimpleMenuItemContext* renderContext,int16 width)
{
	CtoeSimpleMenuItem::Prepare(renderContext,width);
}

//Render image on the screen surface
void CtoeSimpleMenuClickable::Render(toeSimpleMenuItemContext* renderContext)
{
	CtoeSimpleMenuItem::Render(renderContext);
}
uint32 CtoeSimpleMenuClickable::GetElementNameHash()
{
	static uint32 name = IwHashString("CLICKABLE");
	return name;
}
void CtoeSimpleMenuClickable::TouchReleased(TouchContext* touchContext)
{
	SendLazyEvent(new CtoeSimpleMenuLazyClick(this));
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuClickable::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp(pAttrName, "onclick"))
	{
		toeReadString(pParser, &onClick);
		return true;
	}
	return CtoeSimpleMenuItem::ParseAttribute(pParser, pAttrName);
}

#endif
