#pragma once

#include "IwArray.h"
#include "toeComponent.h"
#include "toeSubsystem.h"

namespace TinyOpenEngine
{
	template <class T> class TtoeSubsystemItem
	{
	public:
		int32 next;
		int32 prev;
		T* component;

		TtoeSubsystemItem():next(-1),prev(-1),component(0) {}
		~TtoeSubsystemItem() {}
	};

	template <class T> class TtoeSubsystemItems
	{
		int32 firstFreeItem;
		int32 lastFreeItem;
		int32 firstItem;
		int32 lastItem;
		CIwArray<TtoeSubsystemItem<T> > items;
	public:
		inline int32 GetFirstItem() const {return firstItem;}
		inline int32 GetLastItem() const {return lastItem;}
		inline int32 GetNextItem(int32 pos) const {return items[pos].next;}
		inline T* GetItemAt(int32 pos) const {return items[pos].component;}

		TtoeSubsystemItems():firstFreeItem(-1),lastFreeItem(-1),firstItem(-1),lastItem(-1){};

		//Adds component to the subsystem
		uint32 RegisterComponent(T* c)
		{
			int32 i;
			TtoeSubsystemItem<T>* item;
			if (firstFreeItem<0)
			{
				i = items.size();
				items.push_back(TtoeSubsystemItem<T>());
				item = &items[i];
			}
			else
			{
				i = firstFreeItem;
				item = &items[i];
				firstFreeItem = item->next;
				if (firstFreeItem >= 0)
					items[firstFreeItem].prev = -1;
				else
					lastFreeItem = -1;
			}
			if (lastItem >= 0)
				items[lastItem].next = i;
			else
				firstItem = i;
			item->prev = lastItem;
			lastItem = i;
			item->component = c;
			return i;
		}
		//Removes component to the subsystem. It doesn't always means that component is deleted. It also used in case of component been "disabled"
		void UnregisterComponent(uint32 i)
		{
			TtoeSubsystemItem<T>* item = &items[i];

			if (item->next >= 0)
				items[item->next].prev = item->prev;
			if (item->prev >= 0)
				items[item->prev].next = item->next;
			if (firstItem == (int32)i)
				firstItem = item->next;
			if (lastItem == (int32)i)
				lastItem = item->prev;

			if (lastFreeItem >= 0)
				items[lastFreeItem].next = i;
			else
				firstFreeItem = i;
			item->prev = lastFreeItem;
			item->next = -1;
			lastFreeItem = i;
		}
	};

	template <class T> class TtoeSubsystem: public CtoeSubsystem
	{
	protected:
		TtoeSubsystemItems<T> items;
	public:
		//Adds component to the subsystem
		virtual uint32 RegisterComponent(CtoeComponent* c)
		{
			return items.RegisterComponent(static_cast<T*>(c));
		}
		//Removes component to the subsystem. It doesn't always means that component is deleted. It also used in case of component been "disabled"
		virtual void UnregisterComponent(uint32 i)
		{
			items.UnregisterComponent(i);
		}
	};
}