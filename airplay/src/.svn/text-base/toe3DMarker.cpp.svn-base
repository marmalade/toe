#include <IwGx.h>
#include <IwGxDebug.h>
#include <IwTextParserITX.h>
#include "toe3DMarker.h"
#include "toeEntity.h"

using namespace TinyOpenEngine;

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(Ctoe3DMarker);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(Ctoe3DMarker);

//Constructor
Ctoe3DMarker::Ctoe3DMarker()
{
	fontHash = 0;
	font = 0;
}

//Desctructor
Ctoe3DMarker::~Ctoe3DMarker()
{
	//IwDebugTraceLinePrintf("~CtoeBox2DCircle(0x%08X)",this);
}
void Ctoe3DMarker::Render(CtoeRenderContext*)
{
	if (!font)
		return;
	if (!text.size())
		return;

}
//Reads/writes a binary file using @a IwSerialise interface.
void Ctoe3DMarker::Serialise ()
{
	CtoeSelfRenderedComponent::Serialise();
	text.Serialise();
	IwSerialiseUInt32(fontHash);
	if (IwSerialiseIsReading())
	{
		font = (CtoeFreeTypeFont*)IwGetResManager()->GetResHashed(fontHash,"CtoeFreeTypeFont");
	}
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	Ctoe3DMarker::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp(pAttrName,"text"))
	{
		pParser->ReadString(text);
		return true;
	}
	if (!stricmp(pAttrName,"font"))
	{
		pParser->ReadStringHash(&fontHash);
		return true;
	}
	return CtoeSelfRenderedComponent::ParseAttribute(pParser,pAttrName);
}
#endif