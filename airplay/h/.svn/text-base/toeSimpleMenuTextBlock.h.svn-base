#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>
#include "toeSimpleMenuTerminalItem.h"

namespace TinyOpenEngine
{
	class CtoeSimpleMenuTextBlock : public CtoeSimpleMenuTerminalItem
	{
	private:
		char* utf8string;
		CtoeSimpleMenuStyleSettings cachedWithCombinedStyle;
		int16 cachedWithWidth;
		CtoeFreeTypeGlyphLayoutData layoutData;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeSimpleMenuTextBlock);
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();
		//Get scriptable class declaration
		virtual CtoeScriptableClassDeclaration* GetInstanceClassDescription() {return GetClassDescription(); };
		//Constructor
		CtoeSimpleMenuTextBlock();
		//Constructor
		CtoeSimpleMenuTextBlock(char* buf);
		//Desctructor
		virtual ~CtoeSimpleMenuTextBlock();

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();

		virtual void Prepare(toeSimpleMenuItemContext* renderContext,int16 width);
		//Render image on the screen surface
		virtual void Render(toeSimpleMenuItemContext* renderContext);
		virtual void RearrangeChildItems();

		const char* GetText() const;
		void SetText(const char*);
#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}