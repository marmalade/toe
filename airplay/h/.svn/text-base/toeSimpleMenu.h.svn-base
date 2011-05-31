#pragma once

#include <IwGeom.h>
#include <toeSubsystem.h>
#include <toeSubsystemItems.h>
#include <toeScriptingSubsystem.h>

namespace TinyOpenEngine
{
	class CtoeSimpleMenuRoot;
	class CtoeSimpleMenuItem;

	class CtoeSimpleMenu : public CtoeSubsystem
	{
	protected:
		uint32 menulayout;
		CtoeSimpleMenuRoot* menu;
		uint32 scriptSubsystemHash;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeSimpleMenu);
		//Constructor
		CtoeSimpleMenu();
		//Desctructor
		virtual ~CtoeSimpleMenu();

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

		virtual void UnhandledTouchEvent(TouchContext* touchContext);
		virtual void UnhandledTouchReleaseEvent(TouchContext* touchContext);
		virtual void UnhandledTouchMotionEvent(TouchContext* touchContext);
		virtual void UnhandledKeyEvent(KeyContext* keyContext);
		void Eval(void*item, CtoeScriptableClassDeclaration*d, const char*s);
#ifdef IW_BUILD_RESOURCES

		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}