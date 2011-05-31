#pragma once

#include <toeBox2DSingleShape.h>
#include <Box2D\Box2D.h>

namespace TinyOpenEngine
{
	class CtoeBox2DBox : public CtoeBox2DSingleShape
	{
	protected:
		float width;
		float height;
		b2Vec2 center;
		float angle;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeBox2DBox);
		//Constructor
		CtoeBox2DBox();
		//Desctructor
		virtual ~CtoeBox2DBox();

		virtual void CreateShape(b2Body* body);

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();
#ifdef IW_BUILD_RESOURCES

		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif

	};
}