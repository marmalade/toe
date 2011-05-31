#pragma once

#include <IwGeom.h>
#include <toeSubsystem.h>
#include <toeSubsystemItems.h>
#include <toeBox2DBody.h>
#include <Box2D/Box2D.h>

namespace TinyOpenEngine
{
	class CtoeBox2DContactFilter:public b2ContactFilter
	{
	public:
		/// Return true if contact calculations should be performed between these two shapes.
		/// @warning for performance reasons this is only called when the AABBs begin to overlap.
		virtual bool ShouldCollide(b2Fixture* shape1, b2Fixture* shape2);
	};
	class CtoeBox2DContactListener: public b2ContactListener
	{
	};

	class CtoeBox2DWorld : public TtoeSubsystem<CtoeBox2DBody>
	{
	protected:
		CIwVec2 gravity;
		bool doSleep;
		float scale;
		int32 velocityIterations;
		int32 positionIterations;
		b2World* world;
		uint32 hitTestProjection;
		CtoeWorld* toeWorld;
		CtoeBox2DContactFilter contactFilter;
		CtoeBox2DContactListener contactListener;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeBox2DWorld);
		//Constructor
		CtoeBox2DWorld();
		//Desctructor
		virtual ~CtoeBox2DWorld();

		//Prepare subsystem
		virtual void Initialize(CtoeWorld*);
		//Update subsystem state
		virtual void Update(iwfixed dt);
		//Find all entities under the pointer
		virtual void PointerHitTest(HitTestContext* htc);

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();
#ifdef IW_BUILD_RESOURCES

		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif

		b2World* GetWorld() const { return world;}
		b2Vec2 GetBox2DPosition(const CIwVec3& pos) const {return b2Vec2((float)pos.x*scale,(float)pos.y*scale); };
		CIwVec3 GetGamePosition(const b2Vec2& pos) const {return CIwVec3((int32)(pos.x/scale),(int32)(pos.y/scale),0); };
	};
}