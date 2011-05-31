#include "TinyOpenEngine.Input.h"
#include "toeInputSubsystem.h"

using namespace TinyOpenEngine;

void TinyOpenEngine::toeInputInit()
{
	#ifdef IW_BUILD_RESOURCES
	//IwClassFactoryAdd("Cb4aLevelMaterial", Cb4aLevelMaterialFactory, 0);
	#endif

	IW_CLASS_REGISTER(CtoeInputSubsystem);
}

void TinyOpenEngine::toeInputTerminate()
{
}