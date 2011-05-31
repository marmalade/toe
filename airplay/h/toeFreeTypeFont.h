#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>
#include <IwTexture.h>
#include <IwImage.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#define TOE_GLYPHSTEP (4)
#define TOE_GLYPHATLASSIZE (256)

namespace TinyOpenEngine
{
	int32 toeGetScreenDPI();
	struct CtoeFreeTypeAtlas;

	// Length
	struct CtoeLength
	{
		enum toeLengthUnit
		{
			PX, //Pixels
			PT, //Points (1/72 of inch)
			PERCENT //Percent
		};

		iwfixed Value;
		toeLengthUnit Unit;

		inline bool IsZero() const {return Value == 0;}

		int32 GetPx(int32 total) const
		{
			if (Value == 0)
				return 0;
			int32 res = 0;
			switch (Unit)
			{
			case PX:
				res = Value/IW_GEOM_ONE;
				if (res == 0) { if (Value>0) res=1; else res=-1;}
				break;
			case PT:
				res = Value*toeGetScreenDPI()/72/IW_GEOM_ONE;
				if (res == 0) { if (Value>0) res=1; else res=-1;}
				break;
			case PERCENT:
				res = Value*total/IW_GEOM_ONE;
				if (res == 0 && total != 0) { if (Value*total>0) res=1; else res=-1;}
				break;
			default:
				break;
			}
			return res;
		}
		CtoeLength(int32 v, toeLengthUnit u):Value(v),Unit(u){}
		CtoeLength():Value(0),Unit(PX){}
		void Serialise();
		void	ParseAttribute(CIwTextParserITX* pParser);
		bool operator == (const CtoeLength & other) const
		{
			return (Value == other.Value)
				&& (Unit == other.Unit || Value == 0);
		}
		

	};
	struct CtoeLength2
	{
		CtoeLength x;
		CtoeLength y;
		inline bool IsZero() const {return x.IsZero() && y.IsZero();}
		bool operator == (const CtoeLength2 & other) const
		{
			return (x == other.y)
				&& (x == other.y);
		}

		void Serialise();
		void ParseAttribute(CIwTextParserITX* pParser);
	};
	struct CtoeLength4
	{
		CtoeLength left;
		CtoeLength top;
		CtoeLength right;
		CtoeLength bottom;

		inline bool IsZero() const {return left.IsZero() && right.IsZero() && top.IsZero() && bottom.IsZero();}
		bool operator == (const CtoeLength4 & other) const
		{
			return (left == other.left)
				&& (top == other.top)
				&& (right == other.right)
				&& (bottom == other.bottom);
		}

		void Serialise();
		void ParseAttribute(CIwTextParserITX* pParser);
	};
	enum toeFreeTypeHAlign
	{
		TOE_FTHALIGN_NATURAL,
		TOE_FTHALIGN_CONTRA,
		TOE_FTHALIGN_CENTER
	};
	struct CtoeFreeTypeGlyph
	{
		bool isLoaded;
		CIwSVec2 advance;
		CIwSVec2 offset;
		int16 width;
		int16 height;
		int16 x;
		int16 y;
		CtoeFreeTypeAtlas* texture;
		CtoeFreeTypeGlyph():isLoaded(false),width(0),height(0),x(0),y(0),texture(0){}
	};

	struct CtoeFreeTypeGlyphSet
	{
		int32 pixelSize;
		CIwArray<CtoeFreeTypeGlyph> glyphs;

		CtoeFreeTypeGlyphSet():pixelSize(0){}
	};
	struct CtoeFreeTypeGlyphLayout
	{
		int32 charCode;
		CtoeFreeTypeGlyph*glyph;
		CIwSVec2 uv;
		CIwSVec2 uvSize;
		CIwSVec2 pos;
		CIwSVec2 size;

		CtoeFreeTypeGlyphLayout():pos(0,0),size(0,0),uv(0,0),uvSize(IW_GEOM_ONE,IW_GEOM_ONE){}
	};
	struct CtoeFreeTypeGlyphLayoutData
	{
		//Current Origin (left/top) Of Text (input)
		CIwSVec2 origin;
		//Current size (width is input, heihgt is output)
		CIwSVec2 size;
		//Actual size of area taken by glyphs (output)
		CIwSVec2 actualSize;
		//Actual origin (left/top) of area taken by glyphs (output)
		CIwSVec2 actualOrigin;
		bool isRightToLeft;
		iwfixed textAlignment;

		CIwArray<CtoeFreeTypeGlyphLayout> glyphs;
		CIwArray<CIwSVec2> renderBufferPos;
		CIwArray<CIwSVec2> renderBufferUV;
		void RenderAt(const CIwSVec2 & pos,const CIwSVec2 & viewport);
		void RenderAt(const CIwSVec2 & pos, const CIwSVec2 & viewport,const CIwMat & t);
		void RenderAt(const CIwSVec2 & pos, const CIwSVec2 & viewport,const CIwMat & t, const CIwColour& col);
	};

	struct CtoeFreeTypeAtlas
	{
		bool isUploaded;
		CIwTexture* texture;
		CIwImage* image;
		CIwTexture* GetTexture() { if (!isUploaded) { texture->Upload(); isUploaded = true; } return texture;}
		uint32 mask[(TOE_GLYPHATLASSIZE/TOE_GLYPHSTEP)/32*(TOE_GLYPHATLASSIZE/TOE_GLYPHSTEP)];
		bool GetMask(int16 x,int16 y) { int16 index = x+y*(TOE_GLYPHATLASSIZE/TOE_GLYPHSTEP); return 0!=(mask[index/32]&(1<<(index&31)));}
		void SetMask(int16 x,int16 y) { int16 index = x+y*(TOE_GLYPHATLASSIZE/TOE_GLYPHSTEP); mask[index/32] |= (1<<(index&31));}
		bool TryToAllocateRect(int16 x,int16 y,int16 w,int16 h);
	};

	class CtoeFreeTypeFont : public CIwResource
	{
	protected:
		CIwStringL pathname;
		FT_Face face;
		bool isFaceLoaded;
		CIwArray<CtoeFreeTypeGlyphSet> glyphSets;
		CIwArray<CtoeFreeTypeAtlas> atlases;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeFreeTypeFont);
		//Constructor
		CtoeFreeTypeFont();
		//Constructor
		CtoeFreeTypeFont(const CIwStringL& pathname);
		//Desctructor
		virtual ~CtoeFreeTypeFont();

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();

		//Render text
		void Render(const char* utf8);

		void LoadFace();

		CtoeFreeTypeGlyph* GetGlyph(int32 charCode, int32 sizeInPixels);
		CtoeFreeTypeAtlas* FindSpaceOnTextureAtlas(int16 w, int16 h, int16*x,int16*y);
		void LayoutGlyphs(const char* utf8z, CtoeFreeTypeGlyphLayoutData& layoutDaya);
		static bool IsRightToLeft(int32 charCode);
		static bool IsRightToLeft();
		static int32 ExtractUtfCode(const char* & c);
		static bool IsSeparator(int32 code);
		static bool IsWhiteSpace(int32 code);
		void AlignRow(CtoeFreeTypeGlyphLayoutData& layoutData, int16& currentY, uint32 startRow);
		void ReorderGlyphs(CtoeFreeTypeGlyphLayoutData& layoutData, uint32 startRow);
		void SplitRowInLines(CtoeFreeTypeGlyphLayoutData& layoutData,int16& currentY, uint32 startRow);
		void PositionLine(CtoeFreeTypeGlyphLayoutData& layoutData,int16& currentY, uint32 startRow, uint32 end);
	};

#ifdef IW_BUILD_RESOURCES
	class CtoeFreeTypeFontResHandler : public CIwResHandler
	{
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeFreeTypeFontResHandler);

		//Constructor
		CtoeFreeTypeFontResHandler(const char * ext, const char* name);
		//Desctructor
		virtual ~CtoeFreeTypeFontResHandler();

		//Buid resource method
		virtual CIwResource*	Build(const CIwStringL& pathname);
	};
#endif
}