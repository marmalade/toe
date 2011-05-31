#include <IwTextParserITX.h>
#include <IwResManager.h>
#include "toeComponent.h"
#include "toeEntity.h"
#include "toeWorld.h"

using namespace TinyOpenEngine;

//Constructor
CtoeEntity::CtoeEntity()
{
	world = 0;
	entityId = 0;
	entityUid = 0;
	list = 0;
	nextEntity = 0;
	prevEntity = 0;
	numActiveComponents = 0;
	numTotalComponents = 0;
	position = CIwVec3::g_Zero;
	rotation = CIwQuat::g_Identity;
}

//Desctructor
CtoeEntity::~CtoeEntity()
{
	for (uint32 i=0; i<numTotalComponents;++i)
	{
		if (components[i].component) 
		{
			if (i<numActiveComponents) components[i].component->BeforeDestruction(this);
			delete components[i].component;
		}
	}
}
//Reads/writes a binary file using @a IwSerialise interface.
void CtoeEntity::Serialise ()
{
	/*if (numActiveComponents != numTotalComponents)
		IwAssertMsg(TOE,false,("Can not serialise incomplete entity"));*/

	IwSerialiseUInt32(entityUid);
	position.Serialise();
	rotation.Serialise();

	if (IwSerialiseIsReading())
	{
		uint32 t;
		IwSerialiseUInt32(t);
		for (uint32 i=0; i<t; ++i)
		{
			uint32 h;
			CIwManaged* m;
			IwSerialiseUInt32(h);
			IwSerialiseManagedObject(m);
			PushComponent(h,static_cast<CtoeComponent*>(m));
		}
	}
	else
	{
		IwSerialiseUInt32(numTotalComponents);
		for (uint32 i=0; i<numTotalComponents; ++i)
		{
			IwSerialiseUInt32(components[i].componentNameHash);
			CIwManaged * m = 0;
			if (components[i].component)
				m = static_cast<CIwManaged*>(components[i].component);
			IwSerialiseManagedObject(m);
		}
	}
}
void CtoeEntity::Detach()
{
	if (!list) return;
	if (list->last == this) list->last = prevEntity;
	if (list->first == this) list->first = nextEntity;
	if (nextEntity) nextEntity->prevEntity = prevEntity;
	if (prevEntity) prevEntity->nextEntity = nextEntity;
	list = 0;
}
void CtoeEntity::AttachToList(toeEntityList* list)
{
	if (this->list == list) return;
	Detach();
	prevEntity = list->last;
	nextEntity = 0;
	list->last = this;
	if (!list->first)
		list->first = this;
	else
		prevEntity->nextEntity = this;
	this->list = list;
}
void CtoeEntity::SendMessage(uint32 eventNameHash,CtoeEventArgs* args)
{
	for (uint32 i=0; i<numActiveComponents;++i)
	{
		components[i].component->RecieveMessage(eventNameHash,args);
	}
}
void CtoeEntity::CompleteInitialization()
{
	for (uint32 i=numActiveComponents; i<numTotalComponents;++i)
	{
		for (uint32 j=0; j<numActiveComponents;++j)
		{
			if (components[i].componentNameHash == components[j].componentNameHash)
			{
				if (components[j].component)
					components[j].component->BeforeDestruction(this);
				components[j].component = components[i].component;
				if (components[j].component)
					components[j].component->BeforeInitialization(this);
				else
				{
					--numActiveComponents;
					components[j] = components[numActiveComponents];
					components[numActiveComponents].component = 0;
				}
				goto nextComponent;
			}
		}
		if (components[i].component)
		{
			if (i != numActiveComponents)
			{
				components[numActiveComponents] = components[i];
				components[i].component = 0;
			}
			components[numActiveComponents].component->BeforeInitialization(this);
			++numActiveComponents;
		}
		nextComponent:;
	}
	numActiveComponents = numTotalComponents;
	for (uint32 j=0; j<numActiveComponents;++j)
		components[j].component->EntityStructureUpdated(this);
	AttachToList(&world->activeEntities);
}
void CtoeEntity::PushComponent(uint32 hash, CtoeComponent* component)
{
	if (world->IsInTrashCan(this))
	{
		if (component) delete component;
		return;
	}
	for (uint32 i=numActiveComponents; i<numTotalComponents;++i)
	{
		if (components[i].componentNameHash == hash)
		{
			if (components[i].component) delete components[i].component;
			components[i].component = component;
			return;
		}
	}
	if (numTotalComponents == world->GetMaxComponentsPerEntity())
	{
		//TODO: maybe we should reallocate components
		IwAssertMsg(TOE,false,("Total number of components (active and unactive) should be less than %d",numTotalComponents));
	}
	components[numTotalComponents].componentNameHash = hash;
	components[numTotalComponents].component = component;
	++numTotalComponents;
	AttachToList(&world->activeEntitiesToUpdate);
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeEntity::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp(pAttrName, "pos"))
	{
		float vec3[3];
		pParser->ReadFloatArray(vec3,3);
		position = CIwVec3((int)vec3[0],(int)vec3[1],(int)vec3[2]);
		return true;
	}
	if (!strcmp(pAttrName, "rot"))
	{
		float	f[4];
		pParser->ReadFloatArray(f, 4);
		CIwQuat	q;
		q.s	= (int32)(f[0] * (1 << 30));
		q.x	= (int32)(f[1] * (1 << 30));
		q.y	= (int32)(f[2] * (1 << 30));
		q.z	= (int32)(f[3] * (1 << 30));
		rotation = q;
		return true;
	}
	if (!stricmp(pAttrName, "lookAt"))
	{
		float from[3];
		float to[3];
		float up[3];
		pParser->ReadFloatArray(from,3);
		pParser->ReadFloatArray(to,3);
		pParser->ReadFloatArray(up,3);
		CIwMat m;
		CIwVec3 vfrom = CIwVec3((int32)from[0],(int32)from[1],(int32)from[2]);
		CIwVec3 vto = CIwVec3((int32)to[0],(int32)to[1],(int32)to[2]);
		position = vfrom;
		m.LookAt(vfrom, vfrom+vfrom-vto, CIwVec3(IW_FIXED(up[0]),IW_FIXED(up[1]),IW_FIXED(up[2])));
		CIwQuat q(m);
		rotation = q;
		return true;
	}
	return false;
}
#endif