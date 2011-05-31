#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeSimpleMenuImage.h"
#include "TinyOpenEngine.FreeType.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuImage);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuImage);

//Constructor
CtoeSimpleMenuImage::CtoeSimpleMenuImage()
{
	InitImage();
}
//Constructor
CtoeSimpleMenuImage::CtoeSimpleMenuImage(uint32 t)
{
	InitImage();
	textureHash = t;
}
//Desctructor
CtoeSimpleMenuImage::~CtoeSimpleMenuImage()
{
	if (material)
		delete material;
}
void CtoeSimpleMenuImage::InitImage()
{
	textureHash = 0;
	texture = 0;
	material = 0;
	rectPos = CIwSVec2::g_Zero;
	rectColour.Set(0xFFFFFFFF);

	styleSheetHash = 0;
	styleSheet = 0;

}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuImage::Serialise ()
{
	CtoeSimpleMenuTerminalItem::Serialise();
	IwSerialiseUInt32(textureHash);
}
void CtoeSimpleMenuImage::Prepare(toeSimpleMenuItemContext* renderContext,int16 width)
{
	if (textureHash == 0)
		return;
	CombineStyle(renderContext);
	if (!material)
	{
		texture = (CIwTexture*)IwGetResManager()->GetResHashed(textureHash, IW_GX_RESTYPE_TEXTURE);
		//CIwImage::Format f = texture->GetFormat();
		material = new CIwMaterial();
		material->SetTexture(texture);
	}
	rectSize = CIwSVec2::g_Zero;
	if (texture)
	{
		rectSize.x = texture->GetWidth();
		rectSize.y = texture->GetHeight();
		int16 contentWidth = width-(GetMarginLeft()+GetPaddingLeft()+GetMarginRight()+GetPaddingRight());
		if (rectSize.x > contentWidth)
		{
			rectSize.y = (int16)((int32)rectSize.y*(int32)width/(int32)rectSize.x);
			rectSize.x = contentWidth;
		}
		size.y = rectSize.y;
		size.x = contentWidth;
	}
	RearrangeChildItems();
}
void CtoeSimpleMenuImage::RearrangeChildItems()
{
}
//Render image on the screen surface
void CtoeSimpleMenuImage::Render(toeSimpleMenuItemContext* renderContext)
{
	if (textureHash == 0)
		return;

	CIwSVec2 rectPos = GetOrigin();
	rectPos.y += GetMarginTop()+GetPaddingTop();
	int16 width = GetSize().x;
	rectPos.x += GetMarginLeft()+GetPaddingLeft();
	int16 contentWidth = width-(GetMarginLeft()+GetPaddingLeft()+GetMarginRight()+GetPaddingRight());
	rectPos.x += (contentWidth-rectSize.x)*combinedStyle.HorizontalAlignment/IW_GEOM_ONE;

	IwGxSetMaterial(material);
	CIwSVec2* v = IW_GX_ALLOC(CIwSVec2,4);
	v[0] = CIwSVec2(rectPos.x, rectPos.y);
	v[1] = CIwSVec2(rectPos.x, rectPos.y+rectSize.y);
	v[2] = CIwSVec2(rectPos.x+rectSize.x, rectPos.y+rectSize.y);
	v[3] = CIwSVec2(rectPos.x+rectSize.x, rectPos.y);
	CIwSVec2* uv = IW_GX_ALLOC(CIwSVec2,4);
	uv[0] = CIwSVec2(0,0);
	uv[1] = CIwSVec2(0,IW_GEOM_ONE);
	uv[2] = CIwSVec2(IW_GEOM_ONE,IW_GEOM_ONE);
	uv[3] = CIwSVec2(IW_GEOM_ONE,0);
	CIwColour* col =IW_GX_ALLOC(CIwColour,4);
	col[0] = col[1] = col[2] = col[3] = rectColour;

	toeTransformScreenSpace3D(v,v+4,renderContext->transformation, renderContext->viewportSize);

	IwGxSetVertStreamScreenSpace(v,4);
	IwGxSetColStream(col);
	IwGxSetUVStream(uv);
	IwGxDrawPrims(IW_GX_QUAD_LIST, 0, 4);
}
uint32 CtoeSimpleMenuImage::GetElementNameHash()
{
	static uint32 name = IwHashString("IMAGE");
	return name;
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuImage::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp("texture",pAttrName))
	{
		pParser->ReadStringHash(&textureHash);
		return true;
	}
	if (!stricmp("styleSheet",pAttrName))
	{
		pParser->ReadStringHash(&styleSheetHash);
		return true;
	}
	return CtoeSimpleMenuTerminalItem::ParseAttribute(pParser, pAttrName);
}

#endif
