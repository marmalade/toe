#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeSimpleMenuRow.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuRow);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuRow);

//Constructor
CtoeSimpleMenuRow::CtoeSimpleMenuRow()
{

}
//Desctructor
CtoeSimpleMenuRow::~CtoeSimpleMenuRow()
{
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuRow::Serialise ()
{
	CtoeSimpleMenuItem::Serialise();
}
void CtoeSimpleMenuRow::Prepare(toeSimpleMenuItemContext* renderContext,int16 width)
{
	CtoeSimpleMenuItem::Prepare(renderContext,width);
}

//Render image on the screen surface
void CtoeSimpleMenuRow::Render(toeSimpleMenuItemContext* renderContext)
{
	CtoeSimpleMenuItem::Render(renderContext);
}

#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuRow::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	return CtoeSimpleMenuItem::ParseAttribute(pParser, pAttrName);
}

#endif
