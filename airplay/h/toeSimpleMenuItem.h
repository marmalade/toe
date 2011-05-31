#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>

#include <toeInput.h>
#include <toeFreeTypeFont.h>
#include <toeSimpleMenuStyle.h>
#include <toeSimpleMenuStyleSheet.h>
#include <toeIntrusiveList.h>
#include <toeScriptingSubsystem.h>

namespace TinyOpenEngine
{
	class CtoeSimpleMenuItem;

	class ItoeSimpleMenuVisitor
	{
	public:
		virtual bool Visited(CtoeSimpleMenuItem*)=0;
	};

	struct toeSimpleMenuItemContext
	{
		CtoeSimpleMenuStyleSettings* parentStyle;
		CtoeSimpleMenuStyleSheet* styleSheet;
		CIwSVec2 viewportPos;
		CIwSVec2 viewportSize;
		CIwMat transformation;
		toeSimpleMenuItemContext():parentStyle(0),styleSheet(0),transformation(CIwMat::g_Identity){};
	};
	class CtoeSimpleMenuRoot;

	class CtoeSimpleMenuLazyEvent: public TtoeIntrusiveListItem<CtoeSimpleMenuLazyEvent,CtoeSimpleMenuItem>,public TtoeIntrusiveListItem<CtoeSimpleMenuLazyEvent>
	{
	public:
		virtual ~CtoeSimpleMenuLazyEvent(){}
		virtual void Send(){}
	};


	class CtoeSimpleMenuItem : public CIwManaged
	{
	protected:
		CIwManagedList childItems;
		CIwSVec2 origin;
		CIwSVec2 size;
		uint32 styleClass;
		uint32 state;
		uint32 idHash;
		//CIwSVec4 margin;
		//CIwSVec4 padding;
		CtoeSimpleMenuRoot*root;
		CtoeSimpleMenuItem*parent;
		CtoeSimpleMenuStyle style;
		CtoeSimpleMenuStyleSettings combinedStyle;
		TtoeIntrusiveList<CtoeSimpleMenuLazyEvent,CtoeSimpleMenuItem> lazyEvents;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeSimpleMenuItem);
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();
		//Get scriptable class declaration
		virtual CtoeScriptableClassDeclaration* GetInstanceClassDescription() {return GetClassDescription(); };

		//Constructor
		CtoeSimpleMenuItem();
		//Desctructor
		virtual ~CtoeSimpleMenuItem();

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();

		//Evaluates size of item and prepares all nessesary things to render it
		virtual void Prepare(toeSimpleMenuItemContext* renderContext,int16 width);
		//Render image on the screen surface
		virtual void Render(toeSimpleMenuItemContext* renderContext);

		bool IsVisible(toeSimpleMenuItemContext* renderContext);

		const CIwSVec2& GetOrigin() const {return origin;}
		//Gets size of the item. It's only valid after Prepare method been executed
		const CIwSVec2& GetSize() const {return size;}

		virtual void SetOrigin(const CIwSVec2& v) { if (origin!=v) { origin=v;RearrangeChildItems(); }}

		//Method walks through child items and collect active ones into plain list
		//virtual void CollectActiveItems(CIwArray<CtoeSimpleMenuItem*>& collection);

		virtual void RearrangeChildItems();

		inline int16 GetMarginLeft()const {return combinedStyle.GetMarginLeft(1);}
		inline int16 GetMarginTop()const {return combinedStyle.GetMarginTop(1);}
		inline int16 GetMarginRight()const {return combinedStyle.GetMarginRight(1);}
		inline int16 GetMarginBottom()const {return combinedStyle.GetMarginBottom(1);}

		inline int16 GetBorderLeft()const {return combinedStyle.GetBorderLeft(1);}
		inline int16 GetBorderTop()const {return combinedStyle.GetBorderTop(1);}
		inline int16 GetBorderRight()const {return combinedStyle.GetBorderRight(1);}
		inline int16 GetBorderBottom()const {return combinedStyle.GetBorderBottom(1);}

		inline int16 GetPaddingLeft()const {return combinedStyle.GetPaddingLeft(1);}
		inline int16 GetPaddingTop()const {return combinedStyle.GetPaddingTop(1);}
		inline int16 GetPaddingRight()const {return combinedStyle.GetPaddingRight(1);}
		inline int16 GetPaddingBottom()const {return combinedStyle.GetPaddingBottom(1);}

		inline int16 GetContentOffsetLeft()const {return GetMarginLeft()+GetPaddingLeft()+GetBorderLeft();}
		inline int16 GetContentOffsetRight()const {return GetMarginRight()+GetPaddingRight()+GetBorderRight();}
		inline int16 GetContentOffsetTop()const {return GetMarginTop()+GetPaddingTop()+GetBorderTop();}
		inline int16 GetContentOffsetBottom()const {return GetMarginBottom()+GetPaddingBottom()+GetBorderBottom();}

		inline CtoeSimpleMenuRoot*GetRoot()const{return root;}
		inline CtoeSimpleMenuItem*GetParent()const{return parent;}
		inline CtoeSimpleMenuItem*GetChildAt(int i)const{return static_cast<CtoeSimpleMenuItem*>(childItems[i]);}
		inline int GetChildItemsCount()const{return (int)childItems.GetSize();}

		void CombineStyle(toeSimpleMenuItemContext* renderContext);
		virtual void InheritStyle(CtoeSimpleMenuStyleSettings* parentSettings);
		virtual void ApplyStyleSheet(CtoeSimpleMenuStyleSheet* styleSheet);
		virtual void ApplyStyle(CtoeSimpleMenuStyle* style);
		virtual uint32 GetElementNameHash();
		virtual uint32 GetElementClassHash();
		virtual uint32 GetElementStateHash();
		uint32 GetElementIdHash() { return idHash; }
		//Finds an active item in children
		virtual CtoeSimpleMenuItem* FindActiveItemAt(const CIwVec2 & item);
		virtual void SetFocus(bool f);
		virtual void Touch(TouchContext* touchContext);
		virtual void TouchReleased(TouchContext* touchContext);
		virtual void TouchMotion(TouchContext* touchContext);
		virtual bool IsActive() const {return false;}

		virtual bool VisitForward(ItoeSimpleMenuVisitor* visitor);
		virtual bool VisitBackward(ItoeSimpleMenuVisitor* visitor);

		void InitTree(CtoeSimpleMenuRoot*,CtoeSimpleMenuItem*);

	protected:
		void RenderBackgroud(toeSimpleMenuItemContext* renderContext);
		void RenderShadow(toeSimpleMenuItemContext* renderContext);
		void RenderBorder(toeSimpleMenuItemContext* renderContext);
		void SendLazyEvent(CtoeSimpleMenuLazyEvent*);
	public:
#ifdef IW_BUILD_RESOURCES
		//Parses from text file: start block.
		virtual	void	ParseOpen(CIwTextParserITX* pParser);
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
		//Extends CIwParseable interface with this extra function: called on any "parent" object, if the "child" has not implemented ParseClose.
		virtual	void	ParseCloseChild(CIwTextParserITX* pParser, CIwManaged* pChild);
#endif
	};
}