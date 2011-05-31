#include <s3e.h>
#include <s3ePointer.h>
#include <s3eKeyboard.h>
#include <IwGx.h>
#include <IwGraphics.h>
#include <TinyOpenEngine.h>
#include <TinyOpenEngine.Camera.h>
#include <TinyOpenEngine.Box2D.h>
#include <TinyOpenEngine.ScreenSpace2D.h>
#include <TinyOpenEngine.SimpleMenu.h>
#include <TinyOpenEngine.Lua.h>
#include <TinyOpenEngine.Geo.h>
#include <TinyOpenEngine.Scene3D.h>
#include <toeWorld.h>
#include <toeSubsystemItems.h>
#include <IwHashString.h>

using namespace TinyOpenEngine;


//-----------------------------------------------------------------------------
// Main global function
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
//uint32 PointerTouch = IwHashString("PointerTouch");
//uint32 PointerTouchReleased = IwHashString("PointerTouchReleased");
//uint32 PointerTouchMotion = IwHashString("PointerTouchMotion");
//uint32 PointerFoucusRecieved = IwHashString("PointerFoucusRecieved");
//uint32 PointerFoucusLost = IwHashString("PointerFoucusLost");


	IwGxInit();
	IwResManagerInit();
	IwGraphicsInit();
	TinyOpenEngine::toeInit();
	TinyOpenEngine::toeBox2DInit();
	TinyOpenEngine::toeCameraInit();
	TinyOpenEngine::toeLuaInit();
	TinyOpenEngine::toeSimpleMenuInit();
	TinyOpenEngine::toeScreenSpace2DInit();
	TinyOpenEngine::toeScene3DInit();
	TinyOpenEngine::toeGeoInit();

	IwGxSetColClear(0x3f, 0x3f, 0x3f, 0x0);
	IwGxPrintSetColour(128, 128, 128);

	toeOpenGroupWorld("./menu/mainmenu.group");

	TinyOpenEngine::toeGeoTerminate();
	TinyOpenEngine::toeScene3DTerminate();
	TinyOpenEngine::toeScreenSpace2DTerminate();
	TinyOpenEngine::toeSimpleMenuTerminate();
	TinyOpenEngine::toeLuaTerminate();
	TinyOpenEngine::toeCameraTerminate();
	TinyOpenEngine::toeBox2DTerminate();
	TinyOpenEngine::toeTerminate();
	IwGraphicsTerminate();
	IwResManagerTerminate();
	IwGxTerminate();
	return 0;
}