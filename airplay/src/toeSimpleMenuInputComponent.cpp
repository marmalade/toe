#include <IwGx.h>
#include <s3eCamera.h>
#include <IwGxDebug.h>
#include <IwTextParserITX.h>
#include "toeSimpleMenuInputComponent.h"
#include "toeEntity.h"
#include "toeWorld.h"

using namespace TinyOpenEngine;

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuInputComponent);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuInputComponent);

namespace TinyOpenEngine
{
	
	


}

//Constructor
CtoeSimpleMenuInputComponent::CtoeSimpleMenuInputComponent()
{
}

//Desctructor
CtoeSimpleMenuInputComponent::~CtoeSimpleMenuInputComponent()
{
}

void CtoeSimpleMenuInputComponent::BeforeDestruction(CtoeEntity* e)
{
	CtoeComponent::BeforeDestruction(e);
}

void CtoeSimpleMenuInputComponent::BeforeInitialization(CtoeEntity* e)
{
	CtoeComponent::BeforeInitialization(e);
}
void CtoeSimpleMenuInputComponent::OnAttachedToSubsytem(CtoeSubsystem*s)
{
	CtoeComponent::OnAttachedToSubsytem(s);
}
void CtoeSimpleMenuInputComponent::OnDetachedFromSubsytem(CtoeSubsystem*s)
{
	CtoeComponent::OnDetachedFromSubsytem(s);
}

// Recieve message sent by CtoeEntity->SendMessage
void CtoeSimpleMenuInputComponent::RecieveMessage(uint32 eventNameHast, CtoeEventArgs*eventArgs)
{
	GetWorld()->Close();
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuInputComponent::Serialise ()
{
	CtoeComponent::Serialise();
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuInputComponent::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	
	return CtoeComponent::ParseAttribute(pParser,pAttrName);
}
#endif