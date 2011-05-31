#include <IwTextParserITX.h>
#include "toeBox2DDraggable.h"
#include "toeBox2DWorld.h"
#include "toeEntity.h"

using namespace TinyOpenEngine;

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeBox2DDraggable);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeBox2DDraggable);

//Constructor
CtoeBox2DDraggable::CtoeBox2DDraggable()
{
}

//Desctructor
CtoeBox2DDraggable::~CtoeBox2DDraggable()
{
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeBox2DDraggable::Serialise ()
{
	CtoeComponent::Serialise();
}

// Recieve message sent by CtoeEntity->SendMessage
void CtoeBox2DDraggable::RecieveMessage(uint32 eventNameHast, CtoeEventArgs*eventArgs)
{
	switch (eventNameHast)
	{
	case PointerTouch:
		eventArgs->Handled();
		return;
	case PointerTouchRelease:
		eventArgs->Handled();
		return;
	case PointerTouchMotion:
		eventArgs->Handled();
		return;
	case PointerFoucusLost:
		eventArgs->Handled();
		return;
	case PointerFoucusRecieved:
		eventArgs->Handled();
		return;
	}
}

#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeBox2DDraggable::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	return CtoeComponent::ParseAttribute(pParser,pAttrName);
}
#endif