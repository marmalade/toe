#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>
#include "toeSimpleMenuItem.h"

namespace TinyOpenEngine
{
	class CtoeSimpleMenuSlider : public CtoeSimpleMenuItem
	{
	private:
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeSimpleMenuSlider);
		//Constructor
		CtoeSimpleMenuSlider();
		//Desctructor
		virtual ~CtoeSimpleMenuSlider();

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();

		virtual void Prepare(toeSimpleMenuItemContext* renderContext,int16 width);
		//Render image on the screen surface
		virtual void Render(toeSimpleMenuItemContext* renderContext);
		virtual bool IsActive() const {return true;}
#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}