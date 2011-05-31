#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeSimpleMenuImageCarousel.h"
#include "toeSimpleMenuRoot.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuImageCarousel);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuImageCarousel);

//Constructor
CtoeSimpleMenuImageCarousel::CtoeSimpleMenuImageCarousel()
{
	carouselOffset = 0;
}
//Desctructor
CtoeSimpleMenuImageCarousel::~CtoeSimpleMenuImageCarousel()
{
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuImageCarousel::Serialise ()
{
	CtoeSimpleMenuItem::Serialise();
	IwSerialiseInt16(carouselOffset);
	if (IwSerialiseIsReading())
	{
		uint32 len;
		IwSerialiseUInt32(len);
		for (uint32 i=0; i<len;++i)
		{
			uint32 h;
			IwSerialiseUInt32(h);
			textures.push_back((CIwTexture*)IwGetResManager()->GetResHashed(h,"CIwTexture"));
		}
	}
	else
	{
		uint32 len = textures.size();
		IwSerialiseUInt32(len);
		for (uint32 i=0; i<len;++i)
		{
			uint32 h = textures[i]->m_Hash;
			IwSerialiseUInt32(h);
		}
	}
}
void CtoeSimpleMenuImageCarousel::Prepare(toeSimpleMenuItemContext* renderContext,int16 width)
{
	CtoeSimpleMenuItem::Prepare(renderContext,width);

	size.y = 0;
	int16 totalWidth = 0;
	for (uint32 i=0; i<textures.size();++i)
	{
		int16 h = (int16)textures[i]->GetHeight();
		if (size.y < h)
			size.y = h;
		totalWidth += (int16)textures[i]->GetWidth();
	}
	if (carouselOffset < width-totalWidth)
		carouselOffset = width-totalWidth;
	if (carouselOffset > 0)
		carouselOffset = 0;
	int16 maxH = (int16)IwGxGetScreenHeight();
	if (size.y > maxH)
		size.y = maxH;
}

//Render image on the screen surface
void CtoeSimpleMenuImageCarousel::Render(toeSimpleMenuItemContext* renderContext)
{
	CtoeSimpleMenuItem::Render(renderContext);
	CIwSVec2 pos = GetOrigin();
	pos.x += carouselOffset;
	for (uint32 i=0; i<textures.size();++i)
	{
		CIwSVec2 texSize = CIwSVec2((int16)textures[i]->GetWidth(), (int16)textures[i]->GetHeight());
		CIwMaterial* m = IW_GX_ALLOC_MATERIAL();
		m->SetColAmbient(255,255,255,255);
		m->SetTexture(textures[i]);
		IwGxSetMaterial(m);
		CIwSVec2* p = IW_GX_ALLOC(CIwSVec2,4);
		CIwSVec2* uv = IW_GX_ALLOC(CIwSVec2,4);
		p[0] = pos;
		p[1] = pos+CIwSVec2(0,texSize.y);
		p[2] = pos+texSize;
		p[3] = pos+CIwSVec2(texSize.x,0);
		uv[0] = CIwSVec2(0,0);
		uv[1] = CIwSVec2(0,IW_GEOM_ONE);
		uv[2] = CIwSVec2(IW_GEOM_ONE,IW_GEOM_ONE);
		uv[3] = CIwSVec2(IW_GEOM_ONE,0);
		IwGxSetVertStreamScreenSpace(p,4);
		IwGxSetUVStream(uv);
		IwGxDrawPrims(IW_GX_QUAD_LIST,0,4);
		pos.x += texSize.x;
	}
}
void CtoeSimpleMenuImageCarousel::TouchMotion(TouchContext* touchContext)
{
	carouselOffset += touchContext->currentPoistion.x-touchContext->lastKnownPoistion.x;
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuImageCarousel::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp(pAttrName,"image") || !stricmp(pAttrName,"texture"))
	{
		uint32 hashName;
		pParser->ReadStringHash(&hashName);
		textures.push_back((CIwTexture*)IwGetResManager()->GetResHashed(hashName,"CIwTexture"));
		return true;
	}
	return CtoeSimpleMenuItem::ParseAttribute(pParser, pAttrName);
}

#endif
