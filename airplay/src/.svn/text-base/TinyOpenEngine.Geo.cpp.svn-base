#include "TinyOpenEngine.Geo.h"
//#include "toeLiveGeoFeed.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	bool isTinyOpenEngineGeoInitialized = false;
}

void TinyOpenEngine::toeGeoInit()
{
	if (isTinyOpenEngineGeoInitialized)
		return;
	isTinyOpenEngineGeoInitialized = true;

	//IW_CLASS_REGISTER(CtoeLiveGeoFeed);
}

void TinyOpenEngine::toeGeoTerminate()
{
	if (!isTinyOpenEngineGeoInitialized)
		return;
	isTinyOpenEngineGeoInitialized = false;
}