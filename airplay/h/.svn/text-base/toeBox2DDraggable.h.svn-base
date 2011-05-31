#pragma once

#include <toeComponent.h>

namespace TinyOpenEngine
{
	class CtoeBox2DWorld;
	class CtoeBox2DDraggable : public CtoeComponent
	{
	protected:
		
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeBox2DDraggable);
		//Constructor
		CtoeBox2DDraggable();
		//Desctructor
		virtual ~CtoeBox2DDraggable();

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();

		// Recieve message sent by CtoeEntity->SendMessage
		virtual void RecieveMessage(uint32 eventNameHast, CtoeEventArgs*eventArgs);

#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}