#include <s3e.h>
#include <IwGx.h>
#include "TinyOpenEngine.h"
#include "TinyOpenEngine.Net.h"
#include "toeNet.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	bool isTinyOpenEngineNetInitialized = false;
}
void TinyOpenEngine::toeNetInit()
{
	if (isTinyOpenEngineNetInitialized)
		return;
	isTinyOpenEngineNetInitialized = true;

	toeRegisterClass(CtoeNet::GetClassDescription());
}

void TinyOpenEngine::toeNetTerminate()
{
	if (!isTinyOpenEngineNetInitialized)
		return;
	isTinyOpenEngineNetInitialized = false;
}