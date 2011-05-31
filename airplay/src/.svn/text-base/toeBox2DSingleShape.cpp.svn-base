#include <Box2D\Box2D.h>
#include <IwTextParserITX.h>
#include <toeBox2DSingleShape.h>
#include "toeBox2DWorld.h"

using namespace TinyOpenEngine;

//Constructor
CtoeBox2DSingleShape::CtoeBox2DSingleShape()
{
	//IwDebugTraceLinePrintf("CtoeBox2DSingleShape(0x%08X)",this);
	density = 1;
	friction = 0.3f;
	restitution = 0.0f;
	fixture= 0;
	categoryBits = 0x0001;
	maskBits = 0xFFFF;
	groupIndex = 0;
	isSensor = false;
}

//Desctructor
CtoeBox2DSingleShape::~CtoeBox2DSingleShape()
{
	//IwDebugTraceLinePrintf("~CtoeBox2DSingleShape(0x%08X)",this);
}


void CtoeBox2DSingleShape::CreateShape(b2Body* groundBody)
{
	
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeBox2DSingleShape::Serialise ()
{
	CtoeBox2DBody::Serialise();
	
	IwSerialiseFloat(friction);
	IwSerialiseFloat(restitution);
	IwSerialiseBool(isSensor);
	IwSerialiseUInt16(categoryBits);
	IwSerialiseUInt16(maskBits);
	IwSerialiseInt16(groupIndex);
	IwSerialiseFloat(density);
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeBox2DSingleShape::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp(pAttrName,"density"))
	{
		pParser->ReadFloat(&density);
		return true;
	}
	return CtoeBox2DBody::ParseAttribute(pParser,pAttrName);
}
#endif