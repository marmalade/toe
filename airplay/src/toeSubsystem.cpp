#include <IwTextParserITX.h>
#include <IwResManager.h>
#include "toeSubsystem.h"
#include "toeWorld.h"

using namespace TinyOpenEngine;

//Constructor
CtoeSubsystem::CtoeSubsystem()
{
}

//Desctructor
CtoeSubsystem::~CtoeSubsystem()
{
}

//Update subsystem state
void CtoeSubsystem::Update(iwfixed dt)
{
}


//Render image on the screen surface
void CtoeSubsystem::Render()
{
}
//Find all entities under the pointer
void CtoeSubsystem::PointerHitTest(HitTestContext* htc)
{
}

//Prepare subsystem
void CtoeSubsystem::Initialize(CtoeWorld*w)
{
	toeWorld = w;
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSubsystem::Serialise ()
{
	CIwManaged::Serialise();
}
//Project screen point into system scene
CIwVec3 CtoeSubsystem::ProjectScreenPoint(const CIwVec3 & screenPoint)
{
	return screenPoint;
}

//Adds component to the subsystem
uint32 CtoeSubsystem::RegisterComponent(CtoeComponent* component)
{
	return 0;
}
// Recieve message sent by CtoeEntity->SendMessage
void CtoeSubsystem::RecieveMessage(uint32 eventNameHast, CtoeEventArgs*eventArgs)
{
}
void CtoeSubsystem::UnhandledTouchEvent(TouchContext* touchContext)
{
}
void CtoeSubsystem::UnhandledTouchReleaseEvent(TouchContext* touchContext)
{
}
void CtoeSubsystem::UnhandledTouchMotionEvent(TouchContext* touchContext)
{
}
void CtoeSubsystem::UnhandledKeyEvent(KeyContext* keyContext)
{
}
//Removes component to the subsystem. It doesn't always means that component is deleted. It also used in case of component been "disabled"
void CtoeSubsystem::UnregisterComponent(uint32)
{
}

#ifdef IW_BUILD_RESOURCES


//Parses from text file: start block.
void	CtoeSubsystem::ParseOpen(CIwTextParserITX* pParser)
{
}

//Parses from text file: parses attribute/value pair.
bool	CtoeSubsystem::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	return CIwManaged::ParseAttribute(pParser, pAttrName);
}

//Parses from text file: end block.
void	CtoeSubsystem::ParseClose(CIwTextParserITX* pParser)
{
	CtoeWorld* p = dynamic_cast<CtoeWorld*>(pParser->GetObject(-1));
	p->AddSubsystem(this);
	//IwGetResManager()->GetCurrentGroup()->AddRes(IwHashString("CtoeSubsystem"), this);
}

//Extends CIwParseable interface with this extra function: called on any "parent" object, if the "child" has not implemented ParseClose.
void	CtoeSubsystem::ParseCloseChild(CIwTextParserITX* pParser, CIwManaged* pChild)
{
}
#endif