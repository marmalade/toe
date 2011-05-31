#include "TinyOpenEngine.Box2D.h"
#include "toeBox2DBody.h"
#include "toeBox2DCircle.h"
#include "toeBox2DBox.h"
#include "toeBox2DWorld.h"
#include "toeBox2DDraggable.h"

using namespace TinyOpenEngine;

void TinyOpenEngine::toeBox2DInit()
{
	IW_CLASS_REGISTER(CtoeBox2DCircle);
	IW_CLASS_REGISTER(CtoeBox2DBox);
	IW_CLASS_REGISTER(CtoeBox2DWorld);
	IW_CLASS_REGISTER(CtoeBox2DDraggable);
}

void TinyOpenEngine::toeBox2DTerminate()
{
}