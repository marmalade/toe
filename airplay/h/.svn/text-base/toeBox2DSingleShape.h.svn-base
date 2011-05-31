#pragma once

#include <toeBox2DBody.h>
#include <Box2D\Box2D.h>

namespace TinyOpenEngine
{
	class CtoeBox2DSingleShape : public CtoeBox2DBody
	{
	protected:
		/// The friction coefficient, usually in the range [0,1].
		float32 friction;

		/// The restitution (elasticity) usually in the range [0,1].
		float32 restitution;

		/// The density, usually in kg/m^2.
		float32 density;

		/// A sensor shape collects contact information but never generates a collision
		/// response.
		bool isSensor;

		/// The collision category bits. Normally you would just set one bit.
		uint16 categoryBits;

		/// The collision mask bits. This states the categories that this
		/// shape would accept for collision.
		uint16 maskBits;

		/// Collision groups allow a certain group of objects to never collide (negative)
		/// or always collide (positive). Zero means no collision group. Non-zero group
		/// filtering always wins against the mask bits.
		int16 groupIndex;
		b2Fixture* fixture;
	public:
		//Constructor
		CtoeBox2DSingleShape();
		//Desctructor
		virtual ~CtoeBox2DSingleShape();

		virtual void CreateShape(b2Body* body);

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();
#ifdef IW_BUILD_RESOURCES

		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}