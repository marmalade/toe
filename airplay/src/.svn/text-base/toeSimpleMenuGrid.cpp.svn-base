#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeSimpleMenuGrid.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuGrid);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuGrid);

//Constructor
CtoeSimpleMenuGrid::CtoeSimpleMenuGrid()
{

}
//Desctructor
CtoeSimpleMenuGrid::~CtoeSimpleMenuGrid()
{
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuGrid::Serialise ()
{
	CtoeSimpleMenuItem::Serialise();
}
void CtoeSimpleMenuGrid::Prepare(toeSimpleMenuItemContext* renderContext,int16 width)
{
	CtoeSimpleMenuItem::Prepare(renderContext,width);
}

//Render image on the screen surface
void CtoeSimpleMenuGrid::Render(toeSimpleMenuItemContext* renderContext)
{
	CtoeSimpleMenuItem::Render(renderContext);
}

#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuGrid::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	return CtoeSimpleMenuItem::ParseAttribute(pParser, pAttrName);
}

#endif
