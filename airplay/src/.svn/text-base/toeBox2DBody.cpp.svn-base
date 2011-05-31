#include <IwTextParserITX.h>
#include "toeBox2DBody.h"
#include "toeBox2DWorld.h"
#include "toeEntity.h"
#include <Box2D/Box2D.h>

using namespace TinyOpenEngine;


//Constructor
CtoeBox2DBody::CtoeBox2DBody()
{
	body = 0;
	
	dynamicBody = false;
	linearVelocity.Set(0.0f, 0.0f);
	angularVelocity = 0.0f;
	linearDamping = 0.0f;
	angularDamping = 0.0f;
	allowSleep = true;
	awake = true;
	fixedRotation = false;
	bullet = false;
	active = true;
	gravityScale = 1.0f;
}

//Desctructor
CtoeBox2DBody::~CtoeBox2DBody()
{
	DeleteBody();
}
CtoeBox2DWorld* CtoeBox2DBody::GetBox2DWorld() const
{
	if (subsystem)
		return static_cast<CtoeBox2DWorld*>(subsystem);
	return 0;
}
void CtoeBox2DBody::OnAttachedToSubsytem(CtoeSubsystem* s)
{
	CreateBody(static_cast<CtoeBox2DWorld*>(s));
}
void CtoeBox2DBody::OnDetachedFromSubsytem(CtoeSubsystem* s)
{
	DeleteBody();
}
void CtoeBox2DBody::DeleteBody()
{
	if (body)
	{
		CtoeBox2DWorld* w = GetBox2DWorld();
		b2World* world = w->GetWorld();
		world->DestroyBody(body);
		body = 0;
	}
}
void CtoeBox2DBody::CreateBody(CtoeBox2DWorld*w)
{
	b2World* world = w->GetWorld();
	b2BodyDef groundBodyDef;
	b2Vec2 p = w->GetBox2DPosition(GetEntity()->GetPosition());
	groundBodyDef.position.Set(p.x, p.y);
	if (dynamicBody)
		groundBodyDef.type = b2_dynamicBody;
	groundBodyDef.linearVelocity = linearVelocity;
	groundBodyDef.angularVelocity = angularVelocity;
	groundBodyDef.linearDamping = linearDamping;
	groundBodyDef.angularDamping = angularDamping;
	groundBodyDef.allowSleep = allowSleep;
	groundBodyDef.awake = awake;
	groundBodyDef.fixedRotation = fixedRotation;
	groundBodyDef.bullet = bullet;
	groundBodyDef.active = active;
	groundBodyDef.gravityScale = gravityScale;
	body = world->CreateBody(&groundBodyDef);
	body->SetUserData(this);
	CreateShape(body);
}
void CtoeBox2DBody::CreateShape(b2Body* body)
{
}
//Update entity transform
void CtoeBox2DBody::UpdateEntityTransform()
{
	CtoeBox2DWorld*w = GetBox2DWorld();
	CtoeEntity*e = GetEntity();
	CIwVec3 pos = w->GetGamePosition(body->GetPosition());
	if (pos != e->GetPosition())
	{
		e->SetPosition(pos);
	}
	float a = body->GetAngle();
	CIwQuat q(CIwVec3(0,0,IW_GEOM_ONE),(int32)(a*170891318.89410789744557369452759));
	e->SetRotation(q);
}
//Reads/writes a binary file using @a IwSerialise interface.
void CtoeBox2DBody::Serialise ()
{
	CtoeComponent::Serialise();
	IwSerialiseBool(dynamicBody);
	IwSerialiseFloat(linearVelocity.x);
	IwSerialiseFloat(linearVelocity.y);
	IwSerialiseFloat(angularVelocity);
	IwSerialiseFloat(linearDamping);
	IwSerialiseFloat(angularDamping);
	IwSerialiseBool(allowSleep);
	IwSerialiseBool(awake);
	IwSerialiseBool(fixedRotation);
	IwSerialiseBool(bullet);
	IwSerialiseBool(active);
	IwSerialiseFloat(gravityScale);
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeBox2DBody::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp(pAttrName, "dynamic"))
	{
		pParser->ReadBool(&dynamicBody);
		return true;
	}
	if (!stricmp(pAttrName, "gravityScale"))
	{
		pParser->ReadFloat(&gravityScale);
		return true;
	}
	
	return CtoeComponent::ParseAttribute(pParser,pAttrName);
}
#endif