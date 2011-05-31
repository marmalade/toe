#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeSimpleMenuBackground.h"
#include "TinyOpenEngine.FreeType.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuBackground);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
//IW_MANAGED_IMPLEMENT(CtoeSimpleMenuBackground);


//Constructor
CtoeSimpleMenuBackground::CtoeSimpleMenuBackground()
{
	textureHash = 0;
	texture = 0;
}
//Desctructor
CtoeSimpleMenuBackground::~CtoeSimpleMenuBackground()
{
}

void CtoeSimpleMenuBackground::Serialise()
{
	CIwManaged::Serialise();
	IwSerialiseUInt32(textureHash);
	if (textureHash && IwSerialiseIsReading())
		texture = (CIwTexture*)IwGetResManager()->GetResHashed(textureHash,"CIwTexture");
	points.SerialiseHeader();
	for (uint32 i=0; i<points.size(); ++i)
	{
		points[i].Colour.Serialise();
		points[i].Position.Serialise();
	}
}

void CtoeSimpleMenuBackground::Render(const CIwSVec2& origin, const CIwSVec2& size,const CIwSVec2 & viewport, const CIwMat & transformation)
{
	if (points.size() == 0)
		return;
	uint32 vertices = (points.size()+1)*2;
	CIwSVec2* v = IW_GX_ALLOC(CIwSVec2,vertices);
	CIwSVec2* uv = IW_GX_ALLOC(CIwSVec2,vertices);
	CIwColour* col =IW_GX_ALLOC(CIwColour,vertices);
	uint16* indices = IW_GX_ALLOC(uint16,points.size()*4);
	CIwMaterial* m = IW_GX_ALLOC_MATERIAL();
	if (texture)
		m->SetTexture(texture);
	m->SetColAmbient(255,255,255,255);
	uint32 numIndices = 0;
	uint32 numP = 0;
	bool alpha = false;
	for (uint32 i=0; i<points.size(); ++i)
	{
		int32 h = points[i].Position.GetPx(size.y);
		indices[numIndices] = numP;
		++numIndices;
		indices[numIndices] = numP+2;
		++numIndices;
		indices[numIndices] = numP+3;
		++numIndices;
		indices[numIndices] = numP+1;
		++numIndices;

		v[numP].x = origin.x;
		v[numP].y = origin.y+h;
		uv[numP].x = 0;
		uv[numP].y = h*IW_GEOM_ONE/size.y;
		col[numP] = points[i].Colour;
		++numP;
		v[numP].x = origin.x+size.x;
		v[numP].y = origin.y+h;
		uv[numP].x = IW_GEOM_ONE;
		uv[numP].y = h*IW_GEOM_ONE/size.y;
		col[numP] = points[i].Colour;
		++numP;
		if (points[i].Colour.a != 255)
			alpha = true;
	}
	v[numP].x = origin.x;
	v[numP].y = origin.y+size.y;
	uv[numP].x = 0;
	uv[numP].y = IW_GEOM_ONE;
	col[numP] = points.back().Colour;
	++numP;
	v[numP].x = origin.x+size.x;
	v[numP].y = origin.y+size.y;
	uv[numP].x = IW_GEOM_ONE;
	uv[numP].y = IW_GEOM_ONE;
	col[numP] = points.back().Colour;
	++numP;
	if (alpha)
		m->SetAlphaMode(CIwMaterial::ALPHA_BLEND);
	IwGxSetMaterial(m);
	toeTransformScreenSpace3D(v,v+numP,transformation, viewport);
	IwGxSetVertStreamScreenSpace(v,vertices);
	IwGxSetUVStream(uv);
	IwGxSetColStream(col);
	if (numIndices > 0)
		IwGxDrawPrims(IW_GX_QUAD_LIST, indices, numIndices);
}

#ifdef IW_BUILD_RESOURCES
//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuBackground::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp("color", pAttrName) || !stricmp("colour", pAttrName))
	{
		uint8 c[4];
		pParser->ReadUInt8Array(c,4);
		CIwColour col;
		col.Set(c[0],c[1],c[2],c[3]);

		points.push_back();
		points.back().Colour = col;
		points.back().Position.Value = 0;
		return true;
	}
	if (!stricmp("point", pAttrName))
	{
		uint8 c[4];
		pParser->ReadUInt8Array(c,4);
		CIwColour col;
		col.Set(c[0],c[1],c[2],c[3]);

		points.push_back();
		points.back().Colour = col;
		points.back().Position.ParseAttribute(pParser);
		return true;
	}
	if (!stricmp("texture", pAttrName))
	{
		pParser->ReadStringHash(&textureHash);
		return true;
	}
	return CIwManaged::ParseAttribute(pParser, pAttrName);
}

void	CtoeSimpleMenuBackground::ParseClose(CIwTextParserITX* pParser)
{
}
#endif