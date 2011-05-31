#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>

#include <toeInput.h>
#include <string>
#include "toeSimpleMenuStyleSheet.h"
#include "toeSimpleMenuItem.h"

namespace TinyOpenEngine
{
	class CtoeSimpleMenu;
	//class CtoeSimpleMenuItem;
	class CtoeSimpleMenuRoot : public CIwResource
	{
		friend class CtoeSimpleMenuItem;

		std::string onLoad;
		std::string onUpdate;
	protected:
		CIwManagedList childItems;
		uint32 styleSheetHash;
		CtoeSimpleMenuStyleSettings styleSettings;
		CtoeSimpleMenuStyle style;
		CtoeSimpleMenuStyleSheet* styleSheet;
		int16 contentOffset;
		int16 scrollAnimation;
		int16 contentAreaHeight;
		int16 contentAreaOffset;
		int16 scrollAnimationAcc;
		bool isVerticalScrolled;
		CIwArray<CtoeSimpleMenuItem*> collection;
		TouchContext* activeTouch;
		CtoeSimpleMenuItem* activeItem;
		CtoeSimpleMenu*simpleMenu;
		TtoeIntrusiveList<CtoeSimpleMenuLazyEvent> lazyEvents;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeSimpleMenuRoot);
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();
		//Get scriptable class declaration
		virtual CtoeScriptableClassDeclaration* GetInstanceClassDescription() {return GetClassDescription(); };
		//Constructor
		CtoeSimpleMenuRoot();
		//Desctructor
		virtual ~CtoeSimpleMenuRoot();

		void Initialize(CtoeSimpleMenu*);

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();
		//Render image on the screen surface
		void Render();
		//Update
		void Update(iwfixed dt);

		void AlignBlocks();

		CtoeSimpleMenuItem* GetContent() const { return (childItems.GetSize() > 0)?static_cast<CtoeSimpleMenuItem*>(childItems[0]):(CtoeSimpleMenuItem*)0;}
		CtoeSimpleMenuItem* GetHeader() const { return (childItems.GetSize() > 1)?static_cast<CtoeSimpleMenuItem*>(childItems[1]):(CtoeSimpleMenuItem*)0;}
		CtoeSimpleMenuItem* GetFooter() const { return (childItems.GetSize() > 2)?static_cast<CtoeSimpleMenuItem*>(childItems[2]):(CtoeSimpleMenuItem*)0;}
		CtoeSimpleMenuItem* GetItemById(const char*) const;
		CtoeSimpleMenuItem* GetItemByHash(uint32 h) const;
		CtoeSimpleMenuItem* FindActiveItemAt(const CIwVec2 & coord);
		
		bool VisitForward(ItoeSimpleMenuVisitor* visitor) const;
		bool VisitBackward(ItoeSimpleMenuVisitor* visitor) const;	

		virtual bool TouchEvent(TouchContext* touchContext);
		virtual bool TouchReleaseEvent(TouchContext* touchContext);
		virtual bool TouchMotionEvent(TouchContext* touchContext);
		virtual bool KeyEvent(KeyContext* keyContext);
		void SetFocusTo(CtoeSimpleMenuItem*);
		void ScrollToItem(CtoeSimpleMenuItem*);
		void Eval(CtoeSimpleMenuItem*, const char*s);

#ifdef IW_BUILD_RESOURCES
		//Parses from text file: start block.
		virtual	void	ParseOpen(CIwTextParserITX* pParser);
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
		//Parses from text file: end block.
		virtual	void	ParseClose(CIwTextParserITX* pParser);
		//Extends CIwParseable interface with this extra function: called on any "parent" object, if the "child" has not implemented ParseClose.
		virtual	void	ParseCloseChild(CIwTextParserITX* pParser, CIwManaged* pChild);
#endif
	};

#ifdef IW_BUILD_RESOURCES
	class CtoeSimpleMenuRootResHandler : public CIwResHandler
	{
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeSimpleMenuRootResHandler);

		//Constructor
		CtoeSimpleMenuRootResHandler();
		//Desctructor
		virtual ~CtoeSimpleMenuRootResHandler();

		//Buid resource method
		virtual CIwResource*	Build(const CIwStringL& pathname);
	};
#endif
}