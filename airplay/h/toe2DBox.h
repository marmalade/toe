#pragma once

#include <toeComponent.h>
#include <toeSelfRenderedComponent.h>
namespace TinyOpenEngine
{
	class Ctoe2DBox : public CtoeSelfRenderedComponent
	{
	protected:
		int32 width;
		int32 height;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(Ctoe2DBox);
		//Constructor
		Ctoe2DBox();
		//Desctructor
		virtual ~Ctoe2DBox();

		virtual void Render(CtoeRenderContext*);

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();
#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}