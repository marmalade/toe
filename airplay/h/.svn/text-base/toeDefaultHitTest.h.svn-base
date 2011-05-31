#pragma once

#include <IwGeom.h>
#include <toeSubsystem.h>
#include <toeSubsystemItems.h>
#include <toeComponent.h>

namespace TinyOpenEngine
{
	class CtoeDefaultHitTest : public TtoeSubsystem<CtoeComponent>
	{
	protected:
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeDefaultHitTest);
		//Constructor
		CtoeDefaultHitTest();
		//Desctructor
		virtual ~CtoeDefaultHitTest();

		//Prepare subsystem
		virtual void Initialize(CtoeWorld*);
		//Update subsystem state
		virtual void Update(iwfixed dt);
		//Render image on the screen surface
		virtual void Render();
		//Find all entities under the pointer
		virtual void PointerHitTest(HitTestContext* htc);

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();
#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}