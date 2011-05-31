#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>
#include <toeFreeTypeFont.h>
#include <toeSimpleMenuBackground.h>

namespace TinyOpenEngine
{
	struct CtoeSimpleMenuStyleSettings
	{
		uint32 FontHash;
		CtoeFreeTypeFont* Font;
		CtoeLength FontSize;
		CIwColour FontColor;
		CtoeSimpleMenuBackground Background;
		CtoeLength4 Margin;
		CtoeLength4 Padding;
		CtoeLength4 Border;
		CIwColour BorderColor;
		CIwColour ShadowColor;
		CtoeLength ShadowSize;
		CtoeLength2 ShadowOffset;
		bool DropShadow;
		iwfixed HorizontalAlignment;
		iwfixed VerticalAlignment;
		CtoeSimpleMenuStyleSettings():
			FontHash(0),Font(0),
			FontSize(8,CtoeLength::PT),
			HorizontalAlignment(0),VerticalAlignment(IW_GEOM_ONE/2),
			ShadowSize(3, CtoeLength::PT),
			DropShadow(false)
			{ FontColor.Set(0xFF000000); BorderColor.Set(0xFF000000); ShadowColor.Set(0x40000000);}
		void Serialise();
		void Inherit(CtoeSimpleMenuStyleSettings* other)
		{
			if (!other)
				return;
			FontHash = other->FontHash;
			Font = other->Font;
			FontSize = other->FontSize;
			FontColor = other->FontColor;
			BorderColor = other->BorderColor;
			ShadowSize = other->ShadowSize;
			ShadowOffset = other->ShadowOffset;
			HorizontalAlignment = other->HorizontalAlignment;
			VerticalAlignment = other->VerticalAlignment;
		}
		inline int16 GetMarginLeft(int16 total)const {return (int16)Margin.left.GetPx(total);}
		inline int16 GetMarginTop(int16 total)const {return (int16)Margin.top.GetPx(total);}
		inline int16 GetMarginRight(int16 total)const {return (int16)Margin.right.GetPx(total);}
		inline int16 GetMarginBottom(int16 total)const {return (int16)Margin.bottom.GetPx(total);}

		inline int16 GetBorderLeft(int16 total)const {return (int16)Border.left.GetPx(total);}
		inline int16 GetBorderTop(int16 total)const {return (int16)Border.top.GetPx(total);}
		inline int16 GetBorderRight(int16 total)const {return (int16)Border.right.GetPx(total);}
		inline int16 GetBorderBottom(int16 total)const {return (int16)Border.bottom.GetPx(total);}

		inline int16 GetPaddingLeft(int16 total)const {return (int16)Padding.left.GetPx(total);}
		inline int16 GetPaddingTop(int16 total)const {return (int16)Padding.top.GetPx(total);}
		inline int16 GetPaddingRight(int16 total)const {return (int16)Padding.right.GetPx(total);}
		inline int16 GetPaddingBottom(int16 total)const {return (int16)Padding.bottom.GetPx(total);}

		bool operator == (const CtoeSimpleMenuStyleSettings & other)const
		{
			return (Font == other.Font)
				&& (FontSize == other.FontSize)
				&& (FontColor == other.FontColor)
				&& (Background == other.Background)
				&& (Margin == other.Margin)
				&& (Padding == other.Padding)
				&& (Border == other.Border)
				&& (ShadowColor == other.ShadowColor)
				&& (ShadowOffset == other.ShadowOffset)
				&& (ShadowColor == other.ShadowColor)
				&& (DropShadow == other.DropShadow)
				&& (BorderColor == other.BorderColor)
				&& (VerticalAlignment == other.VerticalAlignment)
				&& (HorizontalAlignment == other.HorizontalAlignment);
		}
	};

	class CtoeSimpleMenuStyle: public CIwManaged
	{
	public:
		CtoeSimpleMenuStyleSettings settings;
	protected:
		bool isFont;
		bool isFontSize;
		bool isFontColor;
		bool isBackground;
		bool isMargin;
		bool isPadding;
		bool isBorder;
		bool isShadowSize;
		bool isShadowOffset;
		bool isShadowColor;
		bool isDropShadow;
		bool isBorderColor;
		bool isHorizontalAlignment;
		bool isVerticalAlignment;
	public:
		CtoeSimpleMenuStyle():isFont(false),isFontSize(false),isFontColor(false),isBackground(false),isMargin(false),isPadding(false),
			isShadowSize(false),isShadowOffset(false),isShadowColor(false),isDropShadow(false),
			isBorder(false),isBorderColor(false),isHorizontalAlignment(false),isVerticalAlignment(false){}
		virtual void Serialise();
		void Apply(CtoeSimpleMenuStyleSettings* other)
		{
			if (isFont)
			{
				other->FontHash = settings.FontHash;
				other->Font = settings.Font;
			}
			if (isFontSize)
				other->FontSize = settings.FontSize;
			if (isFontColor)
				other->FontColor = settings.FontColor;
			if (isBackground)
				other->Background = settings.Background;
			if (isMargin)
				other->Margin = settings.Margin;
			if (isBorderColor)
				other->BorderColor = settings.BorderColor;
			if (isBorder)
				other->Border = settings.Border;
			if (isDropShadow)
				other->DropShadow = settings.DropShadow;
			if (isShadowColor)
				other->ShadowColor = settings.ShadowColor;
			if (isShadowOffset)
				other->ShadowOffset = settings.ShadowOffset;
			if (isShadowSize)
				other->ShadowSize = settings.ShadowSize;
			if (isPadding)
				other->Padding = settings.Padding;
			if (isHorizontalAlignment)
				other->HorizontalAlignment = settings.HorizontalAlignment;
			if (isVerticalAlignment)
				other->VerticalAlignment = settings.VerticalAlignment;
		}

#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}