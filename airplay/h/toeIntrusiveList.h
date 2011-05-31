#pragma once

namespace TinyOpenEngine
{
	template<class T,typename TAG=void> class TtoeIntrusiveList;

	template<class T,typename TAG=void> class TtoeIntrusiveListItem
	{
		friend class TtoeIntrusiveList<T,TAG>;
	protected:
		TtoeIntrusiveList<T,TAG>*	listContainer;
		TtoeIntrusiveListItem<T,TAG>* prevSibling;
		TtoeIntrusiveListItem<T,TAG>* nextSibling;
	public:
		inline TtoeIntrusiveListItem():listContainer(0),prevSibling(0),nextSibling(0){}
		inline virtual ~TtoeIntrusiveListItem(){Detach();}

		inline T* GetPrevious() const {return static_cast<T*>(prevSibling); }
		inline T* GetNext() const {return static_cast<T*>(nextSibling); }

		void AttachHead(TtoeIntrusiveList<T,TAG>* node);
		void AttachTail(TtoeIntrusiveList<T,TAG>* node);
		void SwapNext();
		void SwapPrev();
		void InsertBefore(TtoeIntrusiveListItem<T,TAG>* node);
		void InsertAfter(TtoeIntrusiveListItem<T,TAG>* node);
		void Detach();
	};

	template<class T,typename TAG> class TtoeIntrusiveList
	{
		friend class TtoeIntrusiveListItem<T,TAG>;
	protected:
		TtoeIntrusiveListItem<T,TAG>* firstChild;
		TtoeIntrusiveListItem<T,TAG>* lastChild;
	public:
		inline TtoeIntrusiveList():firstChild(0),lastChild(0){}

		inline T* GetFirstChild() const {return static_cast<T*>(firstChild); }
		inline T* GetLastChild() const {return static_cast<T*>(lastChild); }

		inline void AttachHead(TtoeIntrusiveListItem<T,TAG>* node) { if(node) node->AttachHead(this);}
		inline void AttachTail(TtoeIntrusiveListItem<T,TAG>* node) { if(node) node->AttachTail(this);}
	};

	template<class T,typename TAG> inline void TtoeIntrusiveListItem<T,TAG>::AttachTail(TtoeIntrusiveList<T,TAG>* list)
	{
		Detach();
		listContainer = list;
		if (listContainer)
		{
			prevSibling = listContainer->lastChild;
			nextSibling = 0;
			listContainer->lastChild = this;
			if (!listContainer->firstChild)
				listContainer->firstChild = this;
			else
				prevSibling->nextSibling = this;
		}
	};


	template<class T,typename TAG> inline void TtoeIntrusiveListItem<T,TAG>::AttachHead(TtoeIntrusiveList<T,typename TAG>* list)
	{
		Detach();
		listContainer = list;
		if (listContainer)
		{
			prevSibling = 0;
			nextSibling = listContainer->firstChild;
			listContainer->firstChild = this;
			if (!listContainer->lastChild)
				listContainer->lastChild = this;
			else
				nextSibling->prevSibling = this;
		}
	};


	template<class T,typename TAG> inline void TtoeIntrusiveListItem<T,TAG>::Detach()
	{
		if (!listContainer) return;
		if (listContainer->lastChild == this) listContainer->lastChild = prevSibling;
		if (listContainer->firstChild == this) listContainer->firstChild = nextSibling;
		if (nextSibling) nextSibling->prevSibling = prevSibling;
		if (prevSibling) prevSibling->nextSibling = nextSibling;
		listContainer = 0;
	};

}