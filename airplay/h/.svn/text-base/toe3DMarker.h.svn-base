#pragma once

#include <toeComponent.h>
#include <toeSelfRenderedComponent.h>
#include <toeFreeTypeFont.h>

namespace TinyOpenEngine
{
	class Ctoe3DMarker : public CtoeSelfRenderedComponent
	{
	protected:
		CIwStringL text;
		uint32 fontHash;
		CtoeFreeTypeFont* font;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(Ctoe3DMarker);
		//Constructor
		Ctoe3DMarker();
		//Desctructor
		virtual ~Ctoe3DMarker();

		virtual void Render(CtoeRenderContext*);

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();
#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}