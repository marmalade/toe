#pragma once

#include <toeComponent.h>
#include <toeSelfRenderedComponent.h>
namespace TinyOpenEngine
{
	class Ctoe3DModel : public CtoeSelfRenderedComponent
	{
	protected:
		int32 width;
		int32 height;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(Ctoe3DModel);
		//Constructor
		Ctoe3DModel();
		//Desctructor
		virtual ~Ctoe3DModel();

		virtual void Render(CtoeRenderContext*);

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();
#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}