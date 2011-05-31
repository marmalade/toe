#pragma once

#include <toeComponent.h>
#include <toeSelfRenderedComponent.h>
namespace TinyOpenEngine
{
	class CtoeGeoGpsLocation : public CtoeComponent
	{
	protected:
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeGeoGpsLocation);
		//Constructor
		CtoeGeoGpsLocation();
		//Desctructor
		virtual ~CtoeGeoGpsLocation();

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();
#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}