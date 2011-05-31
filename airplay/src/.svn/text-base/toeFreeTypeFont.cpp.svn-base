#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeFreeTypeFont.h"
#include "TinyOpenEngine.FreeType.h"
#include <freetype/ftglyph.h>

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	FT_Library toeGetFreeTypeLibrary();

}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeFreeTypeFont);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeFreeTypeFont);

//Constructor
CtoeFreeTypeFont::CtoeFreeTypeFont()
{
	face = 0;
	isFaceLoaded = false;
}
//Constructor
CtoeFreeTypeFont::CtoeFreeTypeFont(const CIwStringL& p)
{
	face = 0;
	pathname = p;
	isFaceLoaded = false;
}
//Desctructor
CtoeFreeTypeFont::~CtoeFreeTypeFont()
{
	if (isFaceLoaded)
	{
		FT_Done_Face(face);
	}
	for (CIwArray<CtoeFreeTypeAtlas>::iterator i=atlases.begin(); i!=atlases.end(); ++i)
	{
		delete i->image;
		delete i->texture;
	}
}
void CtoeLength::Serialise()
{
	IwSerialiseInt32(Value);
	IwSerialiseEnum(&Unit);
}
void CtoeLength::ParseAttribute(CIwTextParserITX* pParser)
{
	pParser->ReadFixed(&Value);
	uint32 unitHash;
	pParser->ReadStringHash(&unitHash);

	switch (unitHash)
	{
	case 0x00597929:
		Unit = PT;
		break;
	case 0x0059792d:
		Unit = PX;
		break;
	case 0x0002b5ca:
		Unit = PERCENT;
		Value = Value/100;
		break;
	case 0x0059783c: //IN
		Unit = PT;
		Value *= 72;
		break;
	case 0x00597775: //CM
		Unit = PT;
		Value = Value*7200/254;
		break;
	default:
		IwAssertMsg(TOE,false,("Unknown unit name (pt,px,in,cm)"));
		break;
	}
}
void CtoeLength4::Serialise()
{
	left.Serialise();
	top.Serialise();
	right.Serialise();
	bottom.Serialise();
}
void CtoeLength4::ParseAttribute(CIwTextParserITX* pParser)
{
	left.ParseAttribute(pParser);
	top.ParseAttribute(pParser);
	right.ParseAttribute(pParser);
	bottom.ParseAttribute(pParser);
}
void CtoeLength2::Serialise()
{
	x.Serialise();
	y.Serialise();
}
void CtoeLength2::ParseAttribute(CIwTextParserITX* pParser)
{
	x.ParseAttribute(pParser);
	y.ParseAttribute(pParser);
	
}
bool CtoeFreeTypeAtlas::TryToAllocateRect(int16 x,int16 y,int16 w,int16 h)
{
	for (int16 yy=y; yy<y+h; ++yy)
		for (int16 xx=x; xx<x+w; ++xx)
			if (GetMask(xx,yy))
				return false;
	for (int16 yy=y; yy<y+h; ++yy)
		for (int16 xx=x; xx<x+w; ++xx)
			SetMask(xx,yy);
	return true;
}
CtoeFreeTypeAtlas* CtoeFreeTypeFont::FindSpaceOnTextureAtlas(int16 w, int16 h, int16*x,int16*y)
{
	CtoeFreeTypeAtlas*res;

	*x = 0;
	*y = 0;
	int16 blockW = (w+TOE_GLYPHSTEP-1)/TOE_GLYPHSTEP;
	int16 blockH = (h+TOE_GLYPHSTEP-1)/TOE_GLYPHSTEP;
	for (uint32 i=0; i<atlases.size(); ++i)
	{
		res = &atlases[i];
		for (int16 xx=0; xx<=TOE_GLYPHATLASSIZE/TOE_GLYPHSTEP-blockW; ++xx)
			for (int16 yy=0; yy<=TOE_GLYPHATLASSIZE/TOE_GLYPHSTEP-blockH; ++yy)
			{
				if (res->TryToAllocateRect(xx,yy,blockW,blockH))
				{
					*x = xx*TOE_GLYPHSTEP;
					*y = yy*TOE_GLYPHSTEP;
					return res;
				}
			}
	}

	atlases.push_back();
	res = &atlases.back();
	res->isUploaded = false;
	res->texture = new CIwTexture();
	res->texture->SetMipMapping(false);
	res->texture->SetModifiable(true);
	res->texture->SetFormatHW(CIwImage::ABGR_4444);
	res->texture->SetFormatSW(CIwImage::ABGR_4444);
	res->image = new CIwImage();
	res->image->SetFormat(CIwImage::ABGR_4444);
	res->image->SetWidth(TOE_GLYPHATLASSIZE);
	res->image->SetHeight(TOE_GLYPHATLASSIZE);
	
	res->image->SetBuffers();
	uint8*texels = res->image->GetTexels();
	memset(texels,0,res->image->GetPitch()*TOE_GLYPHATLASSIZE);
	memset(res->mask,0,sizeof(res->mask));
	res->texture->SetImage(res->image);
	res->TryToAllocateRect(0,0,blockW,blockH);
	return res;
}
CtoeFreeTypeGlyph* CtoeFreeTypeFont::GetGlyph(int32 charCode, int32 size)
{
	if (charCode < 0)
		return 0;

	CtoeFreeTypeGlyphSet* set = 0;
	for (CIwArray<CtoeFreeTypeGlyphSet>::iterator iterator = glyphSets.begin(); iterator!=glyphSets.end(); ++iterator)
		if (iterator->pixelSize == size)
			set = &(*iterator);
	if (!set)
	{
		glyphSets.push_back(CtoeFreeTypeGlyphSet());
		set = &glyphSets.back();
		set->pixelSize = size;
		set->glyphs.resize(face->num_glyphs+1);
	}
	int32 glyphIndex = FT_Get_Char_Index( face, (uint32)charCode );
	if (set->glyphs.size() <= (uint32)glyphIndex)
		return 0;

	CtoeFreeTypeGlyph* glyph = &set->glyphs[glyphIndex];
	if (!glyph->isLoaded)
	{
		IwTrace(TOE, ("Load glyph %d (char %c)",glyphIndex, charCode));
		FT_Set_Char_Size(face, size<<6, size<<6, 96, 96);
		glyph->isLoaded = true;
		if(FT_Load_Glyph( face, glyphIndex, FT_LOAD_DEFAULT ))
		{
			IwAssertMsg(TOE,false,("Can not load glyph"));
			return glyph;
		}
		FT_Glyph ft_glyph;
		if(FT_Get_Glyph( face->glyph, &ft_glyph ))
		{
			IwAssertMsg(TOE,false,("Can not get glyph"));
			return glyph;
		}
		
		if (FT_Glyph_To_Bitmap( &ft_glyph, ft_render_mode_normal, 0, 1 ))
		{
			IwAssertMsg(TOE,false,("Can not get glyph bitmap"));
			FT_Done_Glyph(ft_glyph);
			return glyph;
		}
		FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)ft_glyph;
		FT_Bitmap& bitmap=bitmap_glyph->bitmap;
		glyph->width = (int16)bitmap.width;
		glyph->height = (int16)bitmap.rows;
		glyph->advance.x = (int16)(ft_glyph->advance.x>>16);
		glyph->advance.y = (int16)(ft_glyph->advance.y>>16);
		glyph->offset.x = (int16)(bitmap_glyph->left);
	
		glyph->offset.y = (int16)(-bitmap_glyph->top);
		CtoeFreeTypeAtlas* a = FindSpaceOnTextureAtlas(glyph->width+2,glyph->height+2,&glyph->x,&glyph->y);
		if (a)
		{
			
			glyph->texture = a;
			if (a->texture)
			{
				CIwImage &image = glyph->texture->texture->GetImage();
				uint8*texels =image.GetTexels();
				for (int yy=0; yy<bitmap.rows;++yy)
				{
					uint8* dst = (texels+image.GetPitch()*(yy+glyph->y)+(2*glyph->x));
					for (int xx=0; xx<bitmap.width;++xx)
					{
						uint8 src = bitmap.buffer[xx+yy*bitmap.pitch];
						*dst = 255; ++dst;
						*dst = ((src>>4)<<4)+15; ++dst;
					}
				}
				glyph->texture->texture->ChangeTexels(texels,CIwImage::ABGR_4444);
				glyph->texture->isUploaded = false;
				//glyph->texture->Upload();
			}
			//if (IsRightToLeft(charCode))
			//{
			//	//glyph->x += glyph->width-1;
			//	//glyph->width = -glyph->width;
			//	glyph->advance.x = -glyph->advance.x;
			//}
		}

		
		FT_Done_Glyph(ft_glyph);
	}
	
	return glyph;
}
bool CtoeFreeTypeFont::IsRightToLeft(int32 charCode)
{
		return (charCode >= 0x0590) && (charCode <= 0x07FA);
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeFreeTypeFont::Serialise ()
{
	CIwResource::Serialise();
	pathname.Serialise();

	if (IwSerialiseIsReading())
		LoadFace();
}
void CtoeFreeTypeFont::LoadFace()
{
	if (isFaceLoaded)
		return;
	isFaceLoaded = true;
	if (pathname.length() == 0)
		return;
	FT_Error error = FT_New_Face( toeGetFreeTypeLibrary() ,
		pathname.c_str(),
        0,
        &face );
	if (error)
		IwAssertMsg(FT, false, ("Could not load face") );
}
bool CtoeFreeTypeFont::IsRightToLeft()
{
	int32 l = s3eDeviceGetInt(S3E_DEVICE_LANGUAGE);
	return (l == S3E_DEVICE_LANGUAGE_ARABIC) || (l == S3E_DEVICE_LANGUAGE_HEBREW);
}
void CtoeFreeTypeFont::LayoutGlyphs(const char* utf8string, CtoeFreeTypeGlyphLayoutData&layoutData)
{
	layoutData.actualSize = CIwSVec2::g_Zero;
	layoutData.actualOrigin = CIwSVec2::g_Zero;
	layoutData.glyphs.clear();
	if (!utf8string || !*utf8string)
	{
		return;
	}
	
	const char* c = utf8string;
	uint32 startRow=0;
	int16 currentY=0;
	while (*c)
	{
		int32 code = ExtractUtfCode(c);
		if ((code == '\n' && *c == '\r') || (code == '\r' && *c == '\n'))
		{
			++c;
			AlignRow(layoutData,currentY,startRow);
			startRow = layoutData.glyphs.size();
			continue;
		}
		if (code == '\n' || code == '\r')
		{
			AlignRow(layoutData,currentY,startRow);
			startRow = layoutData.glyphs.size();
			continue;
		}
		if (code < 0) break;
		layoutData.glyphs.push_back();
		layoutData.glyphs.back().charCode = code;
		layoutData.glyphs.back().glyph = GetGlyph(code, layoutData.size.y);
	}
	if (startRow != layoutData.glyphs.size())
		AlignRow(layoutData,currentY,startRow);
	layoutData.actualSize.y = currentY;
	/*if (IsWhiteSpace(code))
			{
				newWord = true;
				continue;
			}
			if (code == '\n')
			{
				xPos =IwGxGetScreenWidth()/2;
				yPos += 32;
				newWord = true;
			}
			bool isCurrentleftToRight = CtoeFreeTypeFont::IsRightToLeft(code);
			newWord |= isCurrentleftToRight!=leftToRight;
			leftToRight = isCurrentleftToRight;
			CtoeFreeTypeGlyph* glyph = f->GetGlyph(code, renderContext->fontSize);
			if (glyph)
			{
				if (newWord)
				{
					cachedGlyphs.push_back();
					newWord = false;
				}
				cachedGlyphs.back().push_back();
				CtoeCachedGlyphData & g = cachedGlyphs.back().back();
				g.texture = glyph->texture;
				g.uv.x = glyph->x*IW_GEOM_ONE/TOE_GLYPHATLASSIZE;
				g.uv.y = glyph->y*IW_GEOM_ONE/TOE_GLYPHATLASSIZE;
				g.uvSize.x = (glyph->width)*IW_GEOM_ONE/TOE_GLYPHATLASSIZE;
				g.uvSize.y = (glyph->height)*IW_GEOM_ONE/TOE_GLYPHATLASSIZE;
				g.stepX = glyph->width;
				g.stepY = glyph->height;
				if (glyph->advance.x < 0)
					xPos+=glyph->advance.x;
				g.pos.x = xPos+glyph->offset.x;
				g.pos.y = yPos+glyph->offset.y;
				g.size.x = glyph->width;
				g.size.y = glyph->height;
				if (glyph->advance.x > 0)
					xPos+=glyph->advance.x;
				++totalGlyphs;
			}*/

}
void CtoeFreeTypeFont::AlignRow(CtoeFreeTypeGlyphLayoutData& layoutData, int16& currentY, uint32 startRow)
{
	ReorderGlyphs(layoutData,startRow);
	SplitRowInLines(layoutData,currentY, startRow);
}
void CtoeFreeTypeFont::SplitRowInLines(CtoeFreeTypeGlyphLayoutData& layoutData,int16& currentY, uint32 startRow)
{
	uint32 startLine = startRow;
	uint32 endLine = startRow;
	bool inWord = false;
	int32 width = 0;

	uint32 i=startRow;
	for (;i<layoutData.glyphs.size();++i)
	{
		int32 cc = layoutData.glyphs[i].charCode;
		if (IsWhiteSpace(cc))
		{
			if (inWord)
				endLine = i;
			inWord = false;
		}
		else
			inWord = true;
		if (width + layoutData.glyphs[i].glyph->advance.x > layoutData.size.x)
		{
			if (endLine == startLine)
				endLine = i;
			PositionLine(layoutData,currentY,startLine,endLine);
			
			for (;endLine<layoutData.glyphs.size();++endLine)
				if (!IsWhiteSpace(layoutData.glyphs[endLine].charCode))
					break;
			startLine=endLine;
			i = startLine-1;
			inWord = false;
			width = 0;
			continue;
		}
		width += layoutData.glyphs[i].glyph->advance.x;
	}
	if (startLine != i)
	{
		PositionLine(layoutData,currentY,startLine,i);
		
	}
}
void CtoeFreeTypeFont::PositionLine(CtoeFreeTypeGlyphLayoutData& layoutData, int16& currentY, uint32 start, uint32 end)
{
	int16 xPos = layoutData.origin.x;
	int16 w = 0;
	for (uint32 i=start;i<end;++i)
		w += layoutData.glyphs[i].glyph->advance.x;
	if (layoutData.isRightToLeft)
	{
		xPos += layoutData.size.x - (layoutData.size.x-w)*layoutData.textAlignment/IW_GEOM_ONE;
	}
	else
	{
		xPos += (layoutData.size.x-w)*layoutData.textAlignment/IW_GEOM_ONE;
	}
	int16 baseLine = currentY+ layoutData.size.y+layoutData.size.y/4;
	for (uint32 i=start;i<end;++i)
	{
		CtoeFreeTypeGlyphLayout& g = layoutData.glyphs[i];
		g.uv.x = g.glyph->x*IW_GEOM_ONE/TOE_GLYPHATLASSIZE;
		g.uv.y = g.glyph->y*IW_GEOM_ONE/TOE_GLYPHATLASSIZE;
		g.uvSize.x = (g.glyph->width)*IW_GEOM_ONE/TOE_GLYPHATLASSIZE;
		g.uvSize.y = (g.glyph->height)*IW_GEOM_ONE/TOE_GLYPHATLASSIZE;
		if (layoutData.isRightToLeft)
			xPos-=g.glyph->advance.x;
		g.pos.x = xPos+g.glyph->offset.x;
		g.pos.y = baseLine+g.glyph->offset.y;
		g.size.x = g.glyph->width;
		g.size.y = g.glyph->height;
		if (!layoutData.isRightToLeft)
			xPos+=g.glyph->advance.x;
	}
	currentY += layoutData.size.y+layoutData.size.y/2;
}
void CtoeFreeTypeFont::ReorderGlyphs(CtoeFreeTypeGlyphLayoutData& layoutData, uint32 startRow)
{
	for (uint32 i=startRow;i<layoutData.glyphs.size();++i)
	{
		if (IsRightToLeft(layoutData.glyphs[i].charCode) != layoutData.isRightToLeft)
		{
			uint32 j=i+1;
			for (;j<layoutData.glyphs.size();++j)
			{
				int32 cc = layoutData.glyphs[j].charCode;
				if (IsWhiteSpace(cc))
					continue;
				if ((IsRightToLeft(cc) == layoutData.isRightToLeft))
					break;
			}
			uint32 ii = i;
			uint32 jj = j-1;
			for (;jj>ii;--jj)
				if (!IsWhiteSpace(layoutData.glyphs[jj].charCode))
					break;
			while (ii < jj)
			{
				CtoeFreeTypeGlyphLayout tmp = layoutData.glyphs[ii];
				layoutData.glyphs[ii] = layoutData.glyphs[jj];
				layoutData.glyphs[jj] = tmp;
				++ii;
				--jj;
			}
			i=j-1;
		}
	}
}
int32 CtoeFreeTypeFont::ExtractUtfCode(const char* & c)
{
	if (!*c)
		return -1;
	int32 r = (uint8)*c;
	++c;
	if (0==(r & 0x080))
		return r;
	if (0x0C0 == (r & 0x0E0))
	{
		r = r&0x01F;
		r = (r<<6) | (0x3F&(uint8)*c);
		++c;
	}
	else if (0x0E0 == (r & 0x0F0))
	{
		r = r&0x0F;
		r = (r<<6) | (0x3F&(uint8)*c);
		++c;
		r = (r<<6) | (0x3F&(uint8)*c);
		++c;
	}
	else if (0x0F0 == (r & 0x0F8))
	{
		r = r&0x07;
		r = (r<<6) | (0x3F&(uint8)*c);
		++c;
		r = (r<<6) | (0x3F&(uint8)*c);
		++c;
	}
	return r;
}
bool CtoeFreeTypeFont::IsSeparator(int32 code)
{
	if (code == '.' || code == ',')
		return true;
	return false;
}
bool CtoeFreeTypeFont::IsWhiteSpace(int32 code)
{
	if (code == ' ' || code == '\t')
		return true;
	return false;
}
void CtoeFreeTypeGlyphLayoutData::RenderAt(const CIwSVec2 & pos,const CIwSVec2 & viewport)
{
	CIwColour c;c.Set(0xFFFFFFFF);
	RenderAt(pos,viewport,CIwMat::g_Identity,c);
}
void CtoeFreeTypeGlyphLayoutData::RenderAt(const CIwSVec2 & pos, const CIwSVec2 & viewport,const CIwMat & t)
{
	CIwColour c;c.Set(0xFFFFFFFF);
	RenderAt(pos,viewport,t,c);
}
void CtoeFreeTypeGlyphLayoutData::RenderAt(const CIwSVec2 & pos, const CIwSVec2 & viewport,const CIwMat & transformation, const CIwColour& col)
{
	if (glyphs.size() == 0)
		return;

	CIwMaterial* m=0;
	CIwTexture* prevTex=0;
	IwGxLightingOff();

	renderBufferPos.clear();
	renderBufferPos.resize(glyphs.size()*4);
	renderBufferUV.clear();
	renderBufferUV.resize(glyphs.size()*4);

	CIwSVec2* vec = &renderBufferPos.front();// IW_GX_ALLOC(CIwSVec2,glyphs.size()*4);
	CIwSVec2* uv = &renderBufferUV.front(); // IW_GX_ALLOC(CIwSVec2,glyphs.size()*4);
	uint32 start=0,cur = 0;
	for (CIwArray<CtoeFreeTypeGlyphLayout>::iterator glyph=glyphs.begin(); glyph!=glyphs.end();++glyph)
	{
		if (start+2000 == cur)
		{
			toeTransformScreenSpace3D(vec+start,vec+cur,transformation, viewport);
			IwGxSetVertStreamScreenSpace(vec+start,cur-start);
			IwGxSetUVStream(uv+start);
			IwGxSetColStream(0);
			IwGxDrawPrims(IW_GX_QUAD_LIST,0,cur-start);
			start = cur;
		}
		if (prevTex != glyph->glyph->texture->texture)
		{
			if (start != cur)
			{
				toeTransformScreenSpace3D(vec+start,vec+cur,transformation,viewport);
				IwGxSetVertStreamScreenSpace(vec+start,cur-start);
				IwGxSetUVStream(uv+start);
				IwGxSetColStream(0);
				IwGxDrawPrims(IW_GX_QUAD_LIST,0,cur-start);
				start = cur;
			}
			prevTex = glyph->glyph->texture->GetTexture();
			m = IW_GX_ALLOC_MATERIAL();
			m->SetTexture(prevTex);
			m->SetColEmissive(255,255,255,255);
			m->SetColDiffuse(255,255,255,255);
			m->SetColAmbient(col.r,col.g,col.b,col.a);
			m->SetAlphaMode(CIwMaterial::ALPHA_BLEND);
			m->SetModulateMode(CIwMaterial::MODULATE_RGB);
			IwGxSetMaterial(m);
		}
		vec[cur] = glyph->pos+pos;
		uv[cur] = glyph->uv;
		++cur;
		vec[cur] = glyph->pos+pos+CIwSVec2(0,glyph->size.y);
		uv[cur] = glyph->uv+CIwSVec2(0,glyph->uvSize.y);
		++cur;
		vec[cur] = glyph->pos+pos+CIwSVec2(glyph->size.x,glyph->size.y);
		uv[cur] = glyph->uv+CIwSVec2(glyph->uvSize.x,glyph->uvSize.y);
		++cur;
		vec[cur] = glyph->pos+pos+CIwSVec2(glyph->size.x,0);
		uv[cur] = glyph->uv+CIwSVec2(glyph->uvSize.x,0);
		++cur;
		//IwGxDrawRectScreenSpace (&glyph->pos,&glyph->size,&glyph->uv,&glyph->uvSize,glyphColor);
	}
	if (start != cur)
	{
		toeTransformScreenSpace3D(vec+start,vec+cur,transformation, viewport);
		IwGxSetVertStreamScreenSpace(vec+start,cur-start);
		IwGxSetUVStream(uv+start);
		IwGxSetColStream(0);
		IwGxDrawPrims(IW_GX_QUAD_LIST,0,cur-start);
	}
}

#ifdef IW_BUILD_RESOURCES


IW_MANAGED_IMPLEMENT(CtoeFreeTypeFontResHandler)

//Constructor
CtoeFreeTypeFontResHandler::CtoeFreeTypeFontResHandler(const char * ext, const char* name): CIwResHandler(ext, "CtoeFreeTypeFont")
{
	SetName(name);
}
//Desctructor
CtoeFreeTypeFontResHandler::~CtoeFreeTypeFontResHandler()
{
}
//Buid resource method
CIwResource*	CtoeFreeTypeFontResHandler::Build(const CIwStringL& pathname)
{
	//IwGetTextParserITX()->ParseFile(pathname.c_str());
	CtoeFreeTypeFont* res = new CtoeFreeTypeFont(pathname);
	return res;
}

#endif