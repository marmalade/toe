#include <s3e.h>
#include <IwGx.h>
#include "TinyOpenEngine.h"
#include "TinyOpenEngine.FreeType.h"
#include "TinyOpenEngine.Net.h"
#include "TinyOpenEngine.SimpleMenu.h"
#include "toeScriptingSubsystem.h"
#include "toeSimpleMenu.h"
#include "toeSimpleMenuInputComponent.h"
#include "toeSimpleMenuItem.h"
#include "toeSimpleMenuRoot.h"
#include "toeSimpleMenuTextBlock.h"
#include "toeSimpleMenuImage.h"
#include "toeSimpleMenuBackground.h"
#include "toeSimpleMenuImageCarousel.h"
#include "toeSimpleMenuCompass.h"
#include "toeSimpleMenuStyle.h"
#include "toeSimpleMenuSlider.h"
#include "toeSimpleMenuButton.h"
#include "toeSimpleMenuCanvas.h"
#include "toeSimpleMenuRow.h"
#include "toeSimpleMenuGrid.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	bool isTinyOpenEngineSimpleMenuInitialized = false;
}

void TinyOpenEngine::toeSimpleMenuInit()
{
	if (isTinyOpenEngineSimpleMenuInitialized)
		return;
	isTinyOpenEngineSimpleMenuInitialized = true;

	toeFreeTypeInit();
	toeNetInit();

	#ifdef IW_BUILD_RESOURCES
	IwGetResManager()->AddHandler(new CtoeSimpleMenuRootResHandler);
	IwGetResManager()->AddHandler(new CtoeSimpleMenuStyleSheetResHandler);
	#endif

	IW_CLASS_REGISTER(CtoeSimpleMenu);
	IW_CLASS_REGISTER(CtoeSimpleMenuBackground);
	IW_CLASS_REGISTER(CtoeSimpleMenuClickable);
	IW_CLASS_REGISTER(CtoeSimpleMenuCanvas);
	IW_CLASS_REGISTER(CtoeSimpleMenuRoot);
	IW_CLASS_REGISTER(CtoeSimpleMenuImage);
	IW_CLASS_REGISTER(CtoeSimpleMenuImageCarousel);
	IW_CLASS_REGISTER(CtoeSimpleMenuInputComponent);
	IW_CLASS_REGISTER(CtoeSimpleMenuItem);
	IW_CLASS_REGISTER(CtoeSimpleMenuTextBlock);
	IW_CLASS_REGISTER(CtoeSimpleMenuStyleSheet);
	IW_CLASS_REGISTER(CtoeSimpleMenuSlider);
	IW_CLASS_REGISTER(CtoeSimpleMenuButton);
	IW_CLASS_REGISTER(CtoeSimpleMenuRow);
	IW_CLASS_REGISTER(CtoeSimpleMenuCompass);
	IW_CLASS_REGISTER(CtoeSimpleMenuGrid);

	//void* test = ScriptTraits::Method("Test", &CtoeSimpleMenuItem::Test);

	
	toeRegisterClass(CtoeSimpleMenuItem::GetClassDescription());
	toeRegisterClass(CtoeSimpleMenuButton::GetClassDescription());
	toeRegisterClass(CtoeSimpleMenuTextBlock::GetClassDescription());
	toeRegisterClass(CtoeSimpleMenuRoot::GetClassDescription());
	//toeRegisterClass(CtoeSimpleMenuCompass::GetClassDescription());

}

void TinyOpenEngine::toeSimpleMenuTerminate()
{
	if (!isTinyOpenEngineSimpleMenuInitialized)
		return;
	isTinyOpenEngineSimpleMenuInitialized = false;

	toeFreeTypeTerminate();
	toeNetTerminate();
}

void TinyOpenEngine::toeDrawSimpleMenuScrollbar(const CIwSVec2 & pos,const CIwSVec2 & size,const CIwSVec2 & spos,const CIwSVec2 & ssize)
{
	CIwMaterial* m = IW_GX_ALLOC_MATERIAL();
	CIwColour c;
	c.Set(0xFFFFFFFF);
	m->SetColAmbient(c);
	m->SetAlphaMode(CIwMaterial::ALPHA_BLEND);
	IwGxSetMaterial(m);
	CIwSVec2* points = IW_GX_ALLOC(CIwSVec2,8);
	CIwColour* cols = IW_GX_ALLOC(CIwColour,8);
	points[0] = pos+CIwSVec2(0,0);
	points[1] = pos+CIwSVec2(0,size.y);
	points[2] = pos+CIwSVec2(size.x,size.y);
	points[3] = pos+CIwSVec2(size.x,0);
	c.Set(0x20,0x20,0x20,0x20);
	cols[0] = cols[1] = cols[2] = cols[3] = c;
	points[4] = spos+CIwSVec2(0,0);
	points[5] = spos+CIwSVec2(0,ssize.y);
	points[6] = spos+CIwSVec2(ssize.x,ssize.y);
	points[7] = spos+CIwSVec2(ssize.x,0);
	c.Set(0xFF,0xFF,0xFF,0x80);
	cols[4] = cols[5] = cols[6] = cols[7] = c;
	IwGxSetVertStreamScreenSpace(points,8);
	IwGxSetColStream(cols);
	IwGxDrawPrims(IW_GX_QUAD_LIST,0,8);
}