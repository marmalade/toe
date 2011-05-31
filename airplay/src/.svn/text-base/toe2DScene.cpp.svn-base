#include <IwGx.h>
#include "toe2DScene.h"

using namespace TinyOpenEngine;

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(Ctoe2DScene);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(Ctoe2DScene);

//Constructor
Ctoe2DScene::Ctoe2DScene()
{
	//IwDebugTraceLinePrintf("CtoeBox2DScene(0x%08X)",this);
}

//Desctructor
Ctoe2DScene::~Ctoe2DScene()
{
	//IwDebugTraceLinePrintf("~CtoeBox2DScene(0x%08X)",this);
}

void Ctoe2DScene::Render()
{
	for (int32 i=items.GetFirstItem();i>=0;i=items.GetNextItem(i))
		items.GetItemAt(i)->Render(0);
}