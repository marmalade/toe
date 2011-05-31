#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeSimpleMenuSlider.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuSlider);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuSlider);

//Constructor
CtoeSimpleMenuSlider::CtoeSimpleMenuSlider()
{

}
//Desctructor
CtoeSimpleMenuSlider::~CtoeSimpleMenuSlider()
{
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuSlider::Serialise ()
{
	CtoeSimpleMenuItem::Serialise();
}
void CtoeSimpleMenuSlider::Prepare(toeSimpleMenuItemContext* renderContext,int16 width)
{
	CtoeSimpleMenuItem::Prepare(renderContext,width);
}

//Render image on the screen surface
void CtoeSimpleMenuSlider::Render(toeSimpleMenuItemContext* renderContext)
{
	CtoeSimpleMenuItem::Render(renderContext);
}

#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuSlider::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	return CtoeSimpleMenuItem::ParseAttribute(pParser, pAttrName);
}

#endif
