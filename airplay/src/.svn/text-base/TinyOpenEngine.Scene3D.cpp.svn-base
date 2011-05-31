#include "TinyOpenEngine.Scene3D.h"
#include "toe3DModel.h"
#include "toe3DMarker.h"
#include "toe3DScene.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	bool isTinyOpenEngineScene3DInitialized = false;
}

void TinyOpenEngine::toeScene3DInit()
{
	if (isTinyOpenEngineScene3DInitialized)
		return;
	isTinyOpenEngineScene3DInitialized = true;

	IW_CLASS_REGISTER(Ctoe3DModel);
	IW_CLASS_REGISTER(Ctoe3DMarker);
	IW_CLASS_REGISTER(Ctoe3DScene);
}

void TinyOpenEngine::toeScene3DTerminate()
{
	if (!isTinyOpenEngineScene3DInitialized)
		return;
	isTinyOpenEngineScene3DInitialized = false;
}