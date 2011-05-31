#pragma once

#include <IwResource.h>
#include "toeEventArgs.h"

namespace TinyOpenEngine
{
	class CtoeEntity;
	class CtoeSubsystem;
	class CtoeEntity;
	class CtoeWorld;
	class CtoeComponent : public CIwManaged
	{
	protected:
		uint32 subsystemHash;
		CtoeSubsystem* subsystem;
		int32 subsystemIndex;
		//TODO: save id of the entity + world
		CtoeEntity*entity;
	public:
		//Constructor
		CtoeComponent();
		//Desctructor
		virtual ~CtoeComponent();

		inline CtoeEntity* GetEntity() const {return entity;}
		CtoeWorld* GetWorld() const;

		virtual void BeforeDestruction(CtoeEntity*);
		virtual void BeforeInitialization(CtoeEntity*);
		virtual void EntityStructureUpdated(CtoeEntity*);
		virtual void OnAttachedToSubsytem(CtoeSubsystem*);
		virtual void OnDetachedFromSubsytem(CtoeSubsystem*);

		// Recieve message sent by CtoeEntity->SendMessage
		virtual void RecieveMessage(uint32 eventNameHast, CtoeEventArgs*eventArgs);

		
		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();

#ifdef IW_BUILD_RESOURCES
		//Parses from text file: start block.
		virtual	void	ParseOpen(CIwTextParserITX* pParser);
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
		//Parses from text file: end block.
		virtual	void	ParseClose(CIwTextParserITX* pParser);
#endif
	};
}