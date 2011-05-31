#pragma once

#include <IwResource.h>
#include <IwGeom.h>
#include "toeEventArgs.h"

namespace TinyOpenEngine
{
	class CtoeWorld;
	class CtoeComponent;
	class CtoeEntity;
	struct CtoeEntityComponentInfo;

	struct toeEntityList
	{
		CtoeEntity* first;
		CtoeEntity* last;

		inline toeEntityList():first(0),last(0){}
	};

	class CtoeEntity
	{
		friend class CtoeWorld;
	protected:
		//pointer to container
		CtoeWorld* world;
		CtoeEntityComponentInfo* components;
		//Position of entity in the world list of entities
		uint32 entityId;
		//Unique token to verify entity links.
		uint32 entityUid;
		//number of actual components in the entity
		uint32 numActiveComponents;
		//TODO: implement the queue conception
		uint32 numTotalComponents;

		toeEntityList* list;
		CtoeEntity* prevEntity;
		CtoeEntity* nextEntity;
		
		CIwVec3 position;
		CIwQuat rotation;
	public:
		//Constructor
		CtoeEntity();
		//Desctructor
		~CtoeEntity();

		//Reads/writes a binary file using @a IwSerialise interface.
		void Serialise ();

		uint32 GetId() const { return entityId; }
		uint32 GetUid() const { return entityUid; }
		const CIwVec3& GetPosition() const { return position; }
		const CIwQuat& GetRotation() const { return rotation; }
		void SetPosition(const CIwVec3& p) { position=p; }
		void SetRotation(const CIwQuat& r) { rotation=r; }
		CIwMat GetWorldTransform() const {return CIwMat(rotation,position);}

#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif

		void SendMessage(uint32 eventNameHash,CtoeEventArgs* args);

		inline CtoeWorld* GetWorld() const {return world;}
	protected:
		void PushComponent(uint32 hash, CtoeComponent* component);
		void Detach();
		void AttachToList(toeEntityList* list);
		void CompleteInitialization();
	};

	class CtoeEntityWeakPointer
	{
	protected:
		//Position of entity in the world list of entities
		uint32 entityId;
		//Unique token to verify entity links.
		uint32 entityUid;
	public:
		inline CtoeEntityWeakPointer():entityId(0),entityUid(0){}
		inline CtoeEntityWeakPointer(const CtoeEntityWeakPointer&b):entityId(b.entityId),entityUid(b.entityUid){}
		inline CtoeEntityWeakPointer(CtoeEntity*e) { if (e) {entityId=e->GetId(); entityUid=e->GetUid();} else {entityId=entityUid=0;}}
		inline CtoeEntityWeakPointer(uint32 id, uint32 uid):entityId(id),entityUid(uid){}
		inline CtoeEntityWeakPointer& operator =(const CtoeEntityWeakPointer& b) {entityId=b.entityId;entityUid=b.entityUid;return *this;}

		inline bool operator ==(const CtoeEntityWeakPointer& b) const {return entityId==b.entityId && ((entityId==0)||(entityUid==b.entityUid));}

		inline bool HasEntity() const {return (entityId!=0); }
		bool HasEntity(const CtoeWorld*world) const;
		CtoeEntity* Get(const CtoeWorld*world) const;
		void Serialise () {IwSerialiseUInt32(entityId); IwSerialiseUInt32(entityUid);}
	};
}