#include <IwGx.h>
#include "TinyOpenEngine.FreeType.h"
#include "toeFreeTypeFont.h"


using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	bool isTinyOpenEngineFreeTypeInitialized = false;
	FT_Error  error;
    FT_Library  library=0;      /* the FreeType library */

	FT_Library toeGetFreeTypeLibrary()
	{
		return library;
	}

	int32 toeGetScreenDPI_iOS()
	{
		uint32 w = IwGxGetScreenWidth();
		uint32 h = IwGxGetScreenHeight();
		if (w<h)
		{
			uint32 i = w;w=h;h=i;
		}
		if (w == 480)
			return 163;
		if (w == 1024)
			return 132;
		if (w == 326)
			return 326;
		return 163;

		//const char* deviceID = s3eDeviceGetString(S3E_DEVICE_ID);
		//return 326; //Retina display 960x640
		//return 132; //iPad 1024x768
		//return 163; //old ipod/iphone; 480x320
	}
}


void TinyOpenEngine::toeFreeTypeInit()
{
	if (isTinyOpenEngineFreeTypeInitialized)
		return;
	isTinyOpenEngineFreeTypeInitialized = true;

	#ifdef IW_BUILD_RESOURCES
	IwGetResManager()->AddHandler(new CtoeFreeTypeFontResHandler("ttf","toeFreeTypeTTF"));
	#endif

	IW_CLASS_REGISTER(CtoeFreeTypeFont);

	error = FT_Init_FreeType( &library );
	IwAssertMsg(FT, !error, ("Could not initialize FreeType library") );


}

void TinyOpenEngine::toeFreeTypeTerminate()
{
	if (!isTinyOpenEngineFreeTypeInitialized)
		return;
	isTinyOpenEngineFreeTypeInitialized = false;

	FT_Done_FreeType( library );
}

int32 TinyOpenEngine::toeGetScreenDPI()
{
	int32 os = s3eDeviceGetInt(S3E_DEVICE_OS);
	switch (os)
	{
	case S3E_OS_ID_IPHONE:
		return toeGetScreenDPI_iOS();
	default:
		break;
	}
	return 163;
}
void TinyOpenEngine::toeTransformScreenSpace3D(CIwSVec2*begin,CIwSVec2*end,const CIwMat & t)
{
	toeTransformScreenSpace3D(begin, end, t, CIwSVec2(IwGxGetScreenWidth(),IwGxGetScreenHeight()));
}
void TinyOpenEngine::toeTransformScreenSpace3D(CIwSVec2*begin,CIwSVec2*end,const CIwMat & t,const CIwSVec2 & screenSize)
{
	if (t.IsIdentity())
		return;
	CIwSVec2 center(screenSize.x/2, screenSize.y/2);
	for (CIwSVec2*a = begin; a!=end; ++a)
	{
		CIwVec3 v = t.TransformVec(CIwSVec3(a->x,a->y,0));
		if (v.z != 0)
		{
			a->x = center.x+(a->x-center.x)*(screenSize.x)/(v.z+screenSize.x);
			a->y = center.y+(a->y-center.y)*(screenSize.y)/(v.z+screenSize.y);
		}
	}
}
