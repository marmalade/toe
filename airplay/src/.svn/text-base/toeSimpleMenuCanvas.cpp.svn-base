#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeSimpleMenuCanvas.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuCanvas);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuCanvas);

//Constructor
CtoeSimpleMenuCanvas::CtoeSimpleMenuCanvas()
{

}
//Desctructor
CtoeSimpleMenuCanvas::~CtoeSimpleMenuCanvas()
{
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuCanvas::Serialise ()
{
	CtoeSimpleMenuItem::Serialise();
}
void CtoeSimpleMenuCanvas::Prepare(toeSimpleMenuItemContext* renderContext,int16 width)
{
	CombineStyle(renderContext);
	toeSimpleMenuItemContext context = *renderContext;
	context.parentStyle = &combinedStyle;

	int16 contentWidth = width - GetContentOffsetLeft()-GetContentOffsetRight();
	size.x = width;
	size.y = 0;
	for (CIwManaged** i = childItems.GetBegin(); i!=childItems.GetEnd(); ++i)
	{
		CtoeSimpleMenuItem* item = static_cast<CtoeSimpleMenuItem*>(*i);
		item->Prepare(&context,contentWidth);
		int16 h = item->GetSize().y;
		if (h > size.y)
			size.y = h;
	}
	size.y += GetContentOffsetTop()+GetContentOffsetBottom();
	RearrangeChildItems();
}
void CtoeSimpleMenuCanvas::RearrangeChildItems()
{
	CIwSVec2 topLeft = GetOrigin();
	topLeft.x += GetContentOffsetLeft();
	topLeft.y += GetContentOffsetTop();
	CIwSVec2 cs = GetSize()-CIwSVec2(GetContentOffsetLeft()+GetContentOffsetRight(), GetContentOffsetTop()+GetContentOffsetBottom());
	for (CIwManaged** i = childItems.GetBegin(); i!=childItems.GetEnd(); ++i)
	{
		CtoeSimpleMenuItem* item = static_cast<CtoeSimpleMenuItem*>(*i);
		CIwSVec2 is = item->GetSize();
		CIwSVec2 p =  CIwSVec2((int16)((cs.x-is.x) * combinedStyle.HorizontalAlignment/IW_GEOM_ONE),
			(int16)((cs.y-is.y) * combinedStyle.VerticalAlignment/IW_GEOM_ONE));
		item->SetOrigin(topLeft+p);
	}
}
//Render image on the screen surface
void CtoeSimpleMenuCanvas::Render(toeSimpleMenuItemContext* renderContext)
{
	CtoeSimpleMenuItem::Render(renderContext);
}

#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuCanvas::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	return CtoeSimpleMenuItem::ParseAttribute(pParser, pAttrName);
}

#endif
