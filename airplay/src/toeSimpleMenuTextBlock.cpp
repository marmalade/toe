#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeSimpleMenuTextBlock.h"
#include "toeSimpleMenuRoot.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuTextBlock);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuTextBlock);

//Constructor
CtoeSimpleMenuTextBlock::CtoeSimpleMenuTextBlock()
{
	utf8string = 0;
	//cachedWithCombinedStyle;
	cachedWithWidth = -100;
}
//Constructor
CtoeSimpleMenuTextBlock::CtoeSimpleMenuTextBlock(char*buf)
{
	utf8string = buf;
}
//Desctructor
CtoeSimpleMenuTextBlock::~CtoeSimpleMenuTextBlock()
{
	if (utf8string)
	{
		delete [] utf8string;
		utf8string= 0;
	}
}
//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuTextBlock::Serialise ()
{
	CtoeSimpleMenuTerminalItem::Serialise();
	style.Serialise();
	size_t len = 0;
	if (IwSerialiseIsReading())
	{
		IwSerialiseUInt32(len);
		if (len)
		{
			utf8string = new char[len+1];
			IwSerialiseString(utf8string);
		}
	}
	else
	{
		if (utf8string)
		{
			len = strlen(utf8string);
			IwSerialiseUInt32(len);
			if (len > 0)
				IwSerialiseString(utf8string);
		}
		else
		{
			IwSerialiseUInt32(len);
		}
	}
}
//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeSimpleMenuTextBlock::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeSimpleMenuTextBlock> d ("CtoeSimpleMenuTextBlock",
			ScriptTraits::Method("GetRoot", &CtoeSimpleMenuTextBlock::GetRoot),
			ScriptTraits::Method("GetText", &CtoeSimpleMenuTextBlock::GetText),
			ScriptTraits::Method("SetText", &CtoeSimpleMenuTextBlock::SetText),
			0);
	return &d;
}
const char* CtoeSimpleMenuTextBlock::GetText() const
{
	return utf8string;
}
void CtoeSimpleMenuTextBlock::SetText(const char* t)
{
	cachedWithCombinedStyle = CtoeSimpleMenuStyleSettings();
	if (utf8string)
	{
		delete utf8string;
		utf8string = 0;
	}
	if (t)
	{
		utf8string = new char[strlen(t)+1];
		strcpy(utf8string,t);
	}
}

void CtoeSimpleMenuTextBlock::Prepare(toeSimpleMenuItemContext* renderContext,int16 width)
{
	CombineStyle(renderContext);
	if (cachedWithWidth == width && combinedStyle == cachedWithCombinedStyle)
		return;
	cachedWithCombinedStyle = combinedStyle;
	cachedWithWidth = width;
	CtoeFreeTypeFont* f = combinedStyle.Font;
	if (!f)
		return;
	int16 contentWidth = width - GetMarginLeft() - GetMarginRight() - GetPaddingLeft() - GetPaddingRight();
	CIwArray<CtoeFreeTypeGlyphLayout> layout;
	layoutData.origin = CIwSVec2::g_Zero;
	layoutData.size.x = contentWidth;
	layoutData.size.y = combinedStyle.FontSize.GetPx(width);
	layoutData.textAlignment = combinedStyle.HorizontalAlignment;//IW_GEOM_ONE/3;
	layoutData.isRightToLeft = false;//CtoeFreeTypeFont::IsRightToLeft();
	layoutData.actualSize.y = 0;
	layoutData.actualSize.x = width;
	if (utf8string)
	{
		f->LayoutGlyphs(utf8string, layoutData);
	}

	size.x = width;
	size.y = layoutData.actualSize.y + GetMarginTop()+GetMarginBottom()+GetPaddingTop()+GetPaddingBottom();
}
//Render image on the screen surface
void CtoeSimpleMenuTextBlock::Render(toeSimpleMenuItemContext* renderContext)
{
	if (!IsVisible(renderContext)) return;
	RenderShadow(renderContext);
	RenderBackgroud(renderContext);
	RenderBorder(renderContext);
	CIwSVec2 p = GetOrigin()+CIwSVec2(GetMarginLeft()+GetPaddingLeft(),GetMarginTop()+GetPaddingTop());
	layoutData.RenderAt(p,renderContext->viewportSize,renderContext->transformation,combinedStyle.FontColor);
	
}
void CtoeSimpleMenuTextBlock::RearrangeChildItems()
{
	CtoeSimpleMenuTerminalItem::RearrangeChildItems();
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuTextBlock::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp("text",pAttrName))
	{
		utf8string = pParser->ReadString();
		return true;
	}
	return CtoeSimpleMenuTerminalItem::ParseAttribute(pParser, pAttrName);
}

#endif
