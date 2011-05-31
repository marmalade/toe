#include <IwTextParserITX.h>
#include <IwResManager.h>
#include "toeDefaultHitTest.h"

using namespace TinyOpenEngine;

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeDefaultHitTest);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeDefaultHitTest);


namespace TinyOpenEngine
{
}


//Constructor
CtoeDefaultHitTest::CtoeDefaultHitTest()
{

}

//Desctructor
CtoeDefaultHitTest::~CtoeDefaultHitTest()
{
}
//Update subsystem state
void CtoeDefaultHitTest::Update(iwfixed dt)
{
}
//Find all entities under the pointer
void CtoeDefaultHitTest::PointerHitTest(HitTestContext* htc)
{
	int32 i = items.GetFirstItem();
	while (i >= 0)
	{
		htc->callback(htc, items.GetItemAt(i)->GetEntity());
		i = items.GetNextItem(i);
	}
}

//Render image on the screen surface
void CtoeDefaultHitTest::Render()
{
}

//Prepare subsystem
void CtoeDefaultHitTest::Initialize(CtoeWorld*w)
{
	TtoeSubsystem<CtoeComponent>::Initialize(w);
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeDefaultHitTest::Serialise ()
{
	TtoeSubsystem<CtoeComponent>::Serialise();
}


#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool CtoeDefaultHitTest::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	return TtoeSubsystem<CtoeComponent>::ParseAttribute(pParser,pAttrName);
}
#endif