#pragma once

#include <IwGeom.h>
#include <IwResource.h>
#include "toeComponent.h"
#include "toeInput.h"

namespace TinyOpenEngine
{
	class CtoeSubsystem : public CIwManaged
	{
	protected:
		CtoeWorld* toeWorld;
	public:
		//Constructor
		CtoeSubsystem();
		//Desctructor
		virtual ~CtoeSubsystem();

		//Prepare subsystem
		virtual void Initialize(CtoeWorld*);

		//Update subsystem state
		virtual void Update(iwfixed dt);
		//Render image on the screen surface
		virtual void Render();
		//Find all entities under the pointer
		virtual void PointerHitTest(HitTestContext* htc);

		//Project screen point into system scene
		virtual CIwVec3 ProjectScreenPoint(const CIwVec3 & screenPoint);

		//Adds component to the subsystem
		virtual uint32 RegisterComponent(CtoeComponent*);
		//Removes component to the subsystem. It doesn't always means that component is deleted. It also used in case of component been "disabled"
		virtual void UnregisterComponent(uint32);

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();

		// Recieve message sent by CtoeEntity->SendMessage
		virtual void RecieveMessage(uint32 eventNameHast, CtoeEventArgs*eventArgs);

		virtual void UnhandledTouchEvent(TouchContext* touchContext);
		virtual void UnhandledTouchReleaseEvent(TouchContext* touchContexty);
		virtual void UnhandledTouchMotionEvent(TouchContext* touchContext);
		virtual void UnhandledKeyEvent(KeyContext* keyContext);
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
	};


}