#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeWorld.h"
#include "toeComponent.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeWorld);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeWorld);

//Constructor
CtoeWorld::CtoeWorld()
{
	maxComponentsPerEntity = 8;
	subsystemInitialized = false;
	entities.resize(32);
	entityComponents.resize(entities.size()*maxComponentsPerEntity);

	for (uint32 i=0; i<entities.size(); ++i)
	{
		entities[i].entityId = i;
		entities[i].world = this;
		entities[i].components = GetFirstComponentInfo(i);

		//Use 0 index entity for NullObject pattern for better stability
		//http://en.wikipedia.org/wiki/Null_Object_pattern
		if (i)
			entities[i].AttachToList(&availableEntities);
	}
}

//Desctructor
CtoeWorld::~CtoeWorld()
{
	entities.clear();
	subsystems.Delete();
}

CtoeEntity* CtoeWorld::AllocateSpecificEntity(uint32 i)
{
	CtoeEntity* e = &entities[i];
	e->AttachToList(&activeEntities);
	return e;
}
CtoeEntity* CtoeWorld::AllocateNextAvailableEntity()
{
	if (!availableEntities.first)
		IwAssertMsg(TOE,false,("There is not available entity slots left!"));

	CtoeEntity* e = availableEntities.first;
	e->AttachToList(&activeEntities);
	return e;
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeWorld::Serialise ()
{
	CIwResource::Serialise();

	subsystems.Serialise();
	IwDebugTraceLinePrintf("CtoeWorld::subsystems.GetSize()=%d",subsystems.GetSize());

	hittestOrder.SerialiseHeader();
	for (uint32 i=0; i<hittestOrder.size(); ++i)
		IwSerialiseUInt32(hittestOrder[i]);

	pointerHandlersOrder.SerialiseHeader();
	for (uint32 i=0; i<pointerHandlersOrder.size(); ++i)
		IwSerialiseUInt32(pointerHandlersOrder[i]);

	keyboardHandlersOrder.SerialiseHeader();
	for (uint32 i=0; i<keyboardHandlersOrder.size(); ++i)
		IwSerialiseUInt32(keyboardHandlersOrder[i]);

	renderOrder.SerialiseHeader();
	for (uint32 i=0; i<renderOrder.size(); ++i)
		IwSerialiseUInt32(renderOrder[i]);

	updateOrder.SerialiseHeader();
	for (uint32 i=0; i<updateOrder.size(); ++i)
		IwSerialiseUInt32(updateOrder[i]);

	if (IwSerialiseIsReading())
	{
		InitializeSubsystems();
		uint32 e;
		for (;;)
		{
			IwSerialiseUInt32(e);
			if (!e) break;
			CtoeEntity*en = &entities[e];
			en->AttachToList(&activeEntities);
			en->Serialise();
		}
		CompleteEntityInitialization();
	}
	else
	{
		uint32 zeroIndex = 0;

		CtoeEntity* en = activeEntities.first;
		while (en)
		{
			IwSerialiseUInt32(en->entityId);
			en->Serialise();
			en = en->nextEntity;
		}
		IwSerialiseUInt32(zeroIndex);
	}
}
void CtoeWorld::Update (iwfixed dt)
{
	for (uint32 i=0; i<updateOrder.size(); ++i)
	{
		CtoeSubsystem*s = GetSubsystem(updateOrder[i]);
		if (s)
			s->Update(dt);
	}
}

void CtoeWorld::Render ()
{
	// Set field of view
    IwGxSetPerspMul(0xa0);
    // Set near and far planes
    IwGxSetFarZNearZ(0x1000, 0x10);

	IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
	//IwGxClear(IW_GX_DEPTH_BUFFER_F);

	static CIwMat modelMatrix;
	modelMatrix.SetIdentity();
	IwGxSetModelMatrix(&modelMatrix);

	for (uint32 i=0; i<renderOrder.size(); ++i)
	{
		CtoeSubsystem*s = GetSubsystem(renderOrder[i]);
		if (s)
			s->Render();
	}

	IwGxFlush();
	IwGxSwapBuffers();

}
void CtoeWorld::PointerHitTest(HitTestContext* htc)
{
	for (uint32 i=0; i<hittestOrder.size(); ++i)
	{
		CtoeSubsystem*s = GetSubsystem(hittestOrder[i]);
		if (s)
		{
			s->PointerHitTest(htc);
		}
	}
}
void CtoeWorld::InitializeSubsystems()
{
	if (subsystemInitialized) return;
	subsystemInitialized= true;

	for (uint32 i=0; i<subsystems.GetSize(); ++i)
		GetSubsystemAt(i)->Initialize(this);
}
void CtoeWorld::CompleteEntityInitialization()
{
	while (activeEntitiesToUpdate.first)
	{
		activeEntitiesToUpdate.first->CompleteInitialization();
	}
}

void CtoeWorld::AddSubsystem(CtoeSubsystem*s)
{
	if (subsystemInitialized)
		IwAssertMsg(TOE,false,("Can not add subsystem after world was created"));
	subsystems.Add(s);
}

CtoeSubsystem* CtoeWorld::GetSubsystem(uint32 hash) const
{
	CIwManaged*m= subsystems.GetObjHashed(hash);
	if (!m) return 0;
	return static_cast<CtoeSubsystem*>(m);
}
void CtoeWorld::UnhandledTouchEvent(TouchContext* touchContext)
{
	for (uint32 i=0; i<pointerHandlersOrder.size(); ++i)
		GetSubsystem(pointerHandlersOrder[i])->UnhandledTouchEvent(touchContext);
}

void CtoeWorld::UnhandledTouchReleaseEvent(TouchContext* touchContext)
{
	for (uint32 i=0; i<pointerHandlersOrder.size(); ++i)
		GetSubsystem(pointerHandlersOrder[i])->UnhandledTouchReleaseEvent(touchContext);
}

void CtoeWorld::UnhandledTouchMotionEvent(TouchContext* touchContext)
{
	for (uint32 i=0; i<pointerHandlersOrder.size(); ++i)
		GetSubsystem(pointerHandlersOrder[i])->UnhandledTouchMotionEvent(touchContext);
}
void CtoeWorld::UnhandledKeyEvent(KeyContext* keyContext)
{
	for (uint32 i=0; i<keyboardHandlersOrder.size(); ++i)
		GetSubsystem(keyboardHandlersOrder[i])->UnhandledKeyEvent(keyContext);
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: start block.
void	CtoeWorld::ParseOpen(CIwTextParserITX* pParser)
{
	entity_proxy.world = this;
}

//Parses from text file: parses attribute/value pair.
bool	CtoeWorld::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp("hittest",pAttrName))
	{
		uint32 hash;
		pParser->ReadStringHash(&hash);
		hittestOrder.push_back(hash);
		return true;
	}
	if (!stricmp("pointerHandler",pAttrName))
	{
		uint32 hash;
		pParser->ReadStringHash(&hash);
		pointerHandlersOrder.push_back(hash);
		return true;
	}
	if (!stricmp("keyboardHandler",pAttrName))
	{
		uint32 hash;
		pParser->ReadStringHash(&hash);
		keyboardHandlersOrder.push_back(hash);
		return true;
	}
	if (!stricmp("update",pAttrName))
	{
		uint32 hash;
		pParser->ReadStringHash(&hash);
		updateOrder.push_back(hash);
		return true;
	}
	if (!strcmp("render",pAttrName))
	{
		uint32 hash;
		pParser->ReadStringHash(&hash);
		renderOrder.push_back(hash);
		return true;
	}
	if (!strcmp("CtoeEntity",pAttrName))
	{
		InitializeSubsystems();
		pParser->PushObject(&entity_proxy);
		entity_proxy.entity = 0;
		return true;
	}
	return CIwResource::ParseAttribute(pParser, pAttrName);
}

//Parses from text file: end block.
void	CtoeWorld::ParseClose(CIwTextParserITX* pParser)
{
	CompleteEntityInitialization();
	IwGetResManager()->GetCurrentGroup()->AddRes(IwHashString("CtoeWorld"), this);
}

//Extends CIwParseable interface with this extra function: called on any "parent" object, if the "child" has not implemented ParseClose.
void	CtoeWorld::ParseCloseChild(CIwTextParserITX* pParser, CIwManaged* pChild)
{
}


//Parses from text file: parses attribute/value pair.
bool	CtoeWorld::CtoeEntityProxy::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!strcmp("id", pAttrName))
	{
		uint32 id;
		pParser->ReadUInt32(&id);
		if (entity)
			IwAssertMsg(TOE,false,("id must be the fist attribute in CtoeEntity!"));
		entity = world->AllocateSpecificEntity(id);
		return true;
	}
	if (!entity)
		entity = world->AllocateNextAvailableEntity();
	if (!stricmp(pAttrName, "componentSlot"))
	{
		pParser->ReadStringHash(&componentHash);
		return true;
	}
	return entity->ParseAttribute(pParser,pAttrName);
}
void	CtoeWorld::CtoeEntityProxy::PushComponent(CtoeComponent* pChild)
{
	entity->PushComponent(componentHash, pChild);
}



IW_MANAGED_IMPLEMENT(CtoeWorldResHandler)

CtoeWorldResHandler::CtoeWorldResHandler() : CIwResHandler("toeworld", "CtoeWorld")
{
	SetName("TOEWORLD");
}

CtoeWorldResHandler::~CtoeWorldResHandler()
{
}

CIwResource* CtoeWorldResHandler::Build(const CIwStringL& pathname)
{
	IwGetTextParserITX()->ParseFile(pathname.c_str());
	return NULL;
}

#endif