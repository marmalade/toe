#include <Box2D\Box2D.h>
#include <IwTextParserITX.h>
#include "toeBox2DBox.h"
#include "toeBox2DWorld.h"

using namespace TinyOpenEngine;

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeBox2DBox);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeBox2DBox);

//Constructor
CtoeBox2DBox::CtoeBox2DBox()
{
	//IwDebugTraceLinePrintf("CtoeBox2DBox(0x%08X)",this);
	width = 10;
	height = 10;
	center = b2Vec2_zero;
	angle = 0;
	
}

//Desctructor
CtoeBox2DBox::~CtoeBox2DBox()
{
	//IwDebugTraceLinePrintf("~CtoeBox2DBox(0x%08X)",this);
}


void CtoeBox2DBox::CreateShape(b2Body* groundBody)
{
	b2PolygonShape dynamicBox;
	CtoeBox2DWorld*w = GetBox2DWorld();
	b2Vec2 size = w->GetBox2DPosition(CIwVec3((int32)width,(int32)height,0));
	dynamicBox.SetAsBox(size.x*0.5f, size.y*0.5f, center, angle);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	fixtureDef.isSensor = isSensor;
	fixtureDef.filter.categoryBits  = categoryBits;
	fixtureDef.filter.maskBits  = maskBits;
	fixtureDef.filter.groupIndex  = groupIndex;
	fixture = groundBody->CreateFixture(&fixtureDef);
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeBox2DBox::Serialise ()
{
	CtoeBox2DSingleShape::Serialise();
	IwSerialiseFloat(width);
	IwSerialiseFloat(height);
	IwSerialiseFloat(center.x);
	IwSerialiseFloat(center.y);
	IwSerialiseFloat(angle);
	
}

#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeBox2DBox::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp(pAttrName,"width"))
	{
		pParser->ReadFloat(&width);
		return true;
	}
	if (!stricmp(pAttrName,"height"))
	{
		pParser->ReadFloat(&height);
		return true;
	}
	if (!stricmp(pAttrName,"angle"))
	{
		pParser->ReadFloat(&angle);
		return true;
	}
	
	return CtoeBox2DSingleShape::ParseAttribute(pParser,pAttrName);
}
#endif