#include <IwTextParserITX.h>
#include <IwResManager.h>
#include "toeComponent.h"
#include "toeWorld.h"
#include "toeSubsystem.h"

using namespace TinyOpenEngine;


//Constructor
CtoeComponent::CtoeComponent()
{
	subsystemHash = 0;
	subsystem = 0;
	subsystemIndex = 0;
	//IwDebugTraceLinePrintf("CtoeComponent(0x%08X)",this);
}

//Desctructor
CtoeComponent::~CtoeComponent()
{
	//IwDebugTraceLinePrintf("~CtoeComponent(0x%08X)",this);
}
CtoeWorld* CtoeComponent::GetWorld() const {return GetEntity()->GetWorld();}
void CtoeComponent::BeforeDestruction(CtoeEntity* entity)
{
	//IwDebugTraceLinePrintf("BeforeDestruction(0x%08X)",entity);
	if (subsystem)
	{
		OnDetachedFromSubsytem(subsystem);
		subsystem->UnregisterComponent(subsystemIndex);
		subsystem = 0;
	}
}
void CtoeComponent::BeforeInitialization(CtoeEntity* newEntity)
{
	entity = newEntity;
	//IwDebugTraceLinePrintf("BeforeInitialization(0x%08X)",entity);
	if (subsystemHash != 0)
	{
		subsystem = entity->GetWorld()->GetSubsystem(subsystemHash);
		if (subsystem)
		{
			subsystemIndex = subsystem->RegisterComponent(this);
			OnAttachedToSubsytem(subsystem);
		}
	}

}
void CtoeComponent::EntityStructureUpdated(CtoeEntity* entity)
{
	//IwDebugTraceLinePrintf("EntityStructureUpdated(0x%08X)",entity);
}
void CtoeComponent::RecieveMessage(uint32 eventNameHast, CtoeEventArgs*eventArgs)
{
}
//Reads/writes a binary file using @a IwSerialise interface.
void CtoeComponent::Serialise ()
{
	CIwManaged::Serialise();
	IwSerialiseUInt32(subsystemHash);
}

void CtoeComponent::OnAttachedToSubsytem(CtoeSubsystem* s)
{
}
void CtoeComponent::OnDetachedFromSubsytem(CtoeSubsystem* s)
{
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: start block.
void	CtoeComponent::ParseOpen(CIwTextParserITX* pParser)
{
}

//Parses from text file: parses attribute/value pair.
bool	CtoeComponent::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!strcmp(pAttrName,"attachTo"))
	{
		pParser->ReadStringHash(&subsystemHash);
		return true;
	}
	return CIwManaged::ParseAttribute(pParser, pAttrName);
}

//Parses from text file: end block.
void	CtoeComponent::ParseClose(CIwTextParserITX* pParser)
{
	CtoeWorld::CtoeEntityProxy* p = dynamic_cast<CtoeWorld::CtoeEntityProxy*>(pParser->GetObject(-1));
	p->PushComponent(this);
}
#endif