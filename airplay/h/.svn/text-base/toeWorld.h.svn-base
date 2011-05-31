#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>
#include "toeSubsystem.h"
#include "toeEntity.h"

namespace TinyOpenEngine
{
	struct CtoeEntityComponentInfo
	{
		uint32 componentNameHash;
		CtoeComponent* component;

		inline CtoeEntityComponentInfo():component(0){}
	};

	class CtoeWorld : public CIwResource
	{
	public:
		friend class CtoeEntity;
#ifdef IW_BUILD_RESOURCES
		class CtoeEntityProxy: public CIwManaged
		{
		public:
			CtoeWorld* world;
			CtoeEntity* entity;
			uint32 componentHash;
			inline CtoeEntityProxy():world(0),entity(0),componentHash(0){};
			//Parses from text file: parses attribute/value pair.
			void PushComponent(CtoeComponent*);
			virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
		};
		CtoeEntityProxy entity_proxy;
#endif
	private:
		struct EntityComponentQueueItem
		{
			uint32 entityId;
			uint32 entityUid;
			uint32 componentNameHash;
			CtoeComponent* component;
		};
		//Max components per entity
		uint32 maxComponentsPerEntity;
		//Entities
		CIwArray<CtoeEntity> entities;
		//Components per each entity
		CIwArray<CtoeEntityComponentInfo> entityComponents;

		CIwManagedList subsystems;
		bool subsystemInitialized;
		CIwArray<uint32> hittestOrder;
		CIwArray<uint32> updateOrder;
		CIwArray<uint32> renderOrder;
		CIwArray<uint32> pointerHandlersOrder;
		CIwArray<uint32> keyboardHandlersOrder;

		toeEntityList availableEntities;
		toeEntityList activeEntities;
		toeEntityList activeEntitiesToUpdate;
		toeEntityList trashCan;
		bool closed;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeWorld);
		//Constructor
		CtoeWorld();
		//Desctructor
		virtual ~CtoeWorld();

		inline bool CheckEntityUid(uint32 entityId,uint32 entityUid) const {if (entityId>=entities.size()) return false; return entities[entityId].entityUid==entityUid;}
		inline CtoeEntity* GetEntity(uint32 entityId,uint32 entityUid) const {if (entityId>=entities.size()) return 0; CtoeEntity*  e=&entities[entityId]; if (e->entityUid!=entityUid) return 0; return e;}

		inline bool IsInTrashCan(const CtoeEntity* entity) const {return &trashCan==entity->list;}
		inline bool IsActiveEntity(const CtoeEntity* entity) const {return &activeEntities==entity->list || &activeEntitiesToUpdate==entity->list;}
		inline uint32 GetMaxComponentsPerEntity() const {return maxComponentsPerEntity;}
		inline uint32 GetEntityId(const CtoeEntity* entity) const {return &entities.front()-entity;}
		inline CtoeEntityComponentInfo* GetFirstComponentInfo(uint32 entityId) {return &entityComponents[entityId*maxComponentsPerEntity];}
		inline const CtoeEntityComponentInfo* GetFirstComponentInfo(uint32 entityId) const {return &entityComponents[entityId*maxComponentsPerEntity];}

		CtoeSubsystem* GetSubsystem(uint32 hash) const;
		CtoeSubsystem* GetSubsystemAt(uint32 i) const {return static_cast<CtoeSubsystem*>(subsystems[i]);};

		CtoeEntity* AllocateSpecificEntity(uint32);
		CtoeEntity* AllocateNextAvailableEntity();

		void UnhandledTouchEvent(TouchContext* touchContext);
		void UnhandledTouchReleaseEvent(TouchContext* touchContext);
		void UnhandledTouchMotionEvent(TouchContext* touchContext);
		void UnhandledKeyEvent(KeyContext* keyContext);
		void Update (iwfixed dt);
		void Render();
		void PointerHitTest(HitTestContext* htc);

		void Close() {closed = true;}
		void Open() {closed = false;}
		bool IsClosed() const {return closed;}

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();

#ifdef IW_BUILD_RESOURCES
		//Parses from text file: start block.
		virtual	void	ParseOpen(CIwTextParserITX* pParser);
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
		//Parses from text file: end block.
		virtual	void	ParseClose(CIwTextParserITX* pParser);
		//Extends CIwParseable interface with this extra function: called on any "parent" object, if the "child" has not implemented ParseClose.
		virtual	void	ParseCloseChild(CIwTextParserITX* pParser, CIwManaged* pChild);
#endif
		void AddSubsystem(CtoeSubsystem*);
	protected:
		//void	PutComponentIntoSlot(uint32 e, uint32 c, uint32 hash, CtoeComponent* component);
		void CompleteEntityInitialization();
		void InitializeSubsystems();
	};

#ifdef IW_BUILD_RESOURCES
	class CtoeWorldResHandler : public CIwResHandler
	{
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeWorldResHandler);

		//Constructor
		CtoeWorldResHandler();
		//Desctructor
		virtual ~CtoeWorldResHandler();

		//Buid resource method
		virtual CIwResource*	Build(const CIwStringL& pathname);
	};
#endif
	inline CtoeEntity* CtoeEntityWeakPointer::Get(const CtoeWorld*world) const { if (!entityId) return false; return world->GetEntity(entityId,entityUid); }
	inline bool CtoeEntityWeakPointer::HasEntity(const CtoeWorld*world) const {if (!entityId) return false; return world->CheckEntityUid(entityId,entityUid); }
}