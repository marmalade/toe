#include <IwTextParserITX.h>
#include "toeBox2DWorld.h"
#include "toeBox2DBody.h"
#include "toeWorld.h"

using namespace TinyOpenEngine;

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeBox2DWorld);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeBox2DWorld);


namespace TinyOpenEngine
{
	inline b2Vec2 GetBox2DVec2(const CIwVec2 & v, float scale) {return b2Vec2(scale*v.x,scale*v.y);}

	class CtoeBox2DQueryCallback: public b2QueryCallback
	{
	protected:
		CtoeBox2DWorld* world;
		HitTestContext* htc;
	public:
		CtoeBox2DQueryCallback(CtoeBox2DWorld*w,HitTestContext* h):world(w),htc(h)
		{
		}
		/// Called for each fixture found in the query AABB.
		/// @return false to terminate the query.
		virtual bool ReportFixture(b2Fixture* fixture) 
		{
			CtoeBox2DBody* b = (CtoeBox2DBody*)fixture->GetBody()->GetUserData();
			htc->callback(htc,b->GetEntity());
			return true;
		}
	};
}

bool CtoeBox2DContactFilter::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB)
{
	return b2ContactFilter::ShouldCollide(fixtureA, fixtureB);
}


//Constructor
CtoeBox2DWorld::CtoeBox2DWorld()
{
	//IwDebugTraceLinePrintf("CtoeBox2DCircle(0x%08X)",this);
	world = 0;
	toeWorld = 0;
	hitTestProjection = 0;
	gravity = CIwVec2::g_Zero;
	gravity.y = 1;
	velocityIterations = 10;
	positionIterations = 8;
	doSleep = false;
	scale = 1;
}

//Desctructor
CtoeBox2DWorld::~CtoeBox2DWorld()
{
	if (world)
		delete world;
	//IwDebugTraceLinePrintf("~CtoeBox2DCircle(0x%08X)",this);
}
//Update subsystem state
void CtoeBox2DWorld::Update(iwfixed dt)
{
	world->Step(dt/(float)IW_GEOM_ONE, velocityIterations, positionIterations);
	world->ClearForces();
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		void * ud = b->GetUserData();
		if (ud)
			((CtoeBox2DBody*)ud)->UpdateEntityTransform();
	}
}
//Find all entities under the pointer
void CtoeBox2DWorld::PointerHitTest(HitTestContext* htc)
{
	CtoeBox2DQueryCallback qc(this,htc);
	CtoeSubsystem* proj = toeWorld->GetSubsystem(hitTestProjection);
	CIwVec3 worldPoint(htc->screenSpacePoint.x,htc->screenSpacePoint.y,0);
	if (proj)
	{
		worldPoint = proj->ProjectScreenPoint(worldPoint);
	}
	b2Vec2 p = GetBox2DPosition(worldPoint);
	
	b2AABB box;
	box.lowerBound = p;
	box.upperBound = p;
	world->QueryAABB(&qc, box);

}


//Prepare subsystem
void CtoeBox2DWorld::Initialize(CtoeWorld*w)
{
	CtoeSubsystem::Initialize(w);
	if (!world)
	{
		world = new b2World(GetBox2DVec2(gravity,scale),doSleep);
		world->SetContactFilter(&contactFilter);
	}
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeBox2DWorld::Serialise ()
{
	CtoeSubsystem::Serialise();
	IwSerialiseFloat(scale);
	IwSerialiseInt32(gravity.x,2);
	IwSerialiseUInt32(hitTestProjection);
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool CtoeBox2DWorld::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp("scale", pAttrName))
	{
		pParser->ReadFloat(&scale);
		return true;
	}
	if (!stricmp("gravity", pAttrName))
	{
		pParser->ReadInt32Array(&gravity.x,2);
		return true;
	}
	if (!stricmp("hitTestProjection", pAttrName))
	{
		pParser->ReadStringHash(&hitTestProjection);
		return true;
	}
	return CtoeSubsystem::ParseAttribute(pParser,pAttrName);
}
#endif