#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>
#include "toeSimpleMenuClickable.h"

namespace TinyOpenEngine
{
	class CtoeSimpleMenuButton : public CtoeSimpleMenuClickable
	{
	private:
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeSimpleMenuButton);
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();
		//Get scriptable class declaration
		virtual CtoeScriptableClassDeclaration* GetInstanceClassDescription() {return GetClassDescription(); };
		//Constructor
		CtoeSimpleMenuButton();
		//Desctructor
		virtual ~CtoeSimpleMenuButton();

		virtual uint32 GetElementNameHash();
	};
}