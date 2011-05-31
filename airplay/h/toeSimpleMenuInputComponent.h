#pragma once

#include <toeComponent.h>
namespace TinyOpenEngine
{
	class CtoeSimpleMenuInputComponent : public CtoeComponent
	{
	protected:
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeSimpleMenuInputComponent);
		//Constructor
		CtoeSimpleMenuInputComponent();
		//Desctructor
		virtual ~CtoeSimpleMenuInputComponent();

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();

		virtual void BeforeDestruction(CtoeEntity* e);
		virtual void BeforeInitialization(CtoeEntity* e);
		virtual void OnAttachedToSubsytem(CtoeSubsystem*);
		virtual void OnDetachedFromSubsytem(CtoeSubsystem*);

		// Recieve message sent by CtoeEntity->SendMessage
		virtual void RecieveMessage(uint32 eventNameHast, CtoeEventArgs*eventArgs);

#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	protected:
	};
}