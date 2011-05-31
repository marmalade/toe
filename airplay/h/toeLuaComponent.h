#pragma once

#include <toeComponent.h>
namespace TinyOpenEngine
{
	class CtoeLuaComponent : public CtoeComponent
	{
	protected:
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeLuaComponent);
		//Constructor
		CtoeLuaComponent();
		//Desctructor
		virtual ~CtoeLuaComponent();

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();
#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	protected:
	};
}