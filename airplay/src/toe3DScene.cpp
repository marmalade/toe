#include <IwGx.h>
#include "toe3DScene.h"
#include <toeWorld.h>

using namespace TinyOpenEngine;

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(Ctoe3DScene);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(Ctoe3DScene);

void Ctoe3DRenderContext::SetCameraEntity(CtoeEntity* e)
{
	viewMatrix.SetIdentity();
	if (e)
	{
		viewMatrix = e->GetRotation();
		viewMatrix.t = e->GetPosition();
	}
	viewMatrix = CIwQuat(0,1073741824,0,0)*viewMatrix;
	IwGxSetViewMatrix(&viewMatrix);
}

//Constructor
Ctoe3DScene::Ctoe3DScene()
{
	//IwDebugTraceLinePrintf("CtoeBox3DScene(0x%08X)",this);
}

//Desctructor
Ctoe3DScene::~Ctoe3DScene()
{
	//IwDebugTraceLinePrintf("~CtoeBox3DScene(0x%08X)",this);
}

//Reads/writes a binary file using @a IwSerialise interface.
void Ctoe3DScene::Serialise ()
{
	CtoeSubsystem::Serialise();
	cameraEntity.Serialise();
}

void Ctoe3DScene::Render()
{
	Ctoe3DRenderContext context;
	CtoeEntity* e = cameraEntity.Get(toeWorld);
	context.SetCameraEntity(e);
	for (int32 i=items.GetFirstItem();i>=0;i=items.GetNextItem(i))
		items.GetItemAt(i)->Render(&context);
}