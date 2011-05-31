#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>
#include "toeSimpleMenuItem.h"
#include "toeSimpleMenuRoot.h"

namespace TinyOpenEngine
{
	class CtoeSimpleMenuCompass : public CtoeSimpleMenuItem
	{
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeSimpleMenuCompass);
		//Constructor
		CtoeSimpleMenuCompass();
		//Desctructor
		virtual ~CtoeSimpleMenuCompass();

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();
		//Render image on the screen surface
		virtual void Render(toeSimpleMenuItemContext* renderContext);

		uint32 GetElementNameHash();
#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}