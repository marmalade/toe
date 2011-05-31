#include "IwGx.h"
#include "toeLoadingScreen.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	iwangle g_toeLoadingAngle=0;
}

CtoeScriptableClassDeclaration* CtoeLoadingScreen::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeLoadingScreen> d ("CtoeLoadingScreen",
			ScriptTraits::Method("Render", &CtoeLoadingScreen::Render),
			0);
	return &d;
}

void CtoeLoadingScreen::Render()
{
	iwangle step = IW_GEOM_ONE/32;
	g_toeLoadingAngle = (g_toeLoadingAngle+step) %IW_GEOM_ONE;
	int32 h = (int32)IwGxGetScreenHeight();
	int32 w = (int32)IwGxGetScreenWidth();
	int32 x = w/2;
	int32 y = h/2;
	int r = (x<y)?(x/2):(y/2);
	int r2 = r*8/10;

	//iwfixed c = IwGeomCos(g_toeLoadingAngle);
	//iwfixed s = IwGeomCos(g_toeLoadingAngle);
	int32 vertices = 10*4;
	CIwSVec2* v = IW_GX_ALLOC(CIwSVec2,vertices);
	CIwColour* col = IW_GX_ALLOC(CIwColour,vertices);
	int index = 0;
	CIwColour c; c.Set(0xFFFFFFFF);
	col[index] = c;
	v[index++] = CIwSVec2(0,0);
	col[index] = c;
	v[index++] = CIwSVec2(0,h);
	col[index] = c;
	v[index++] = CIwSVec2(w,h);
	col[index] = c;
	v[index++] = CIwSVec2(w,0);
	iwangle a = g_toeLoadingAngle;
	int colS = 250/(vertices/4);
	for (int i=1; i<(vertices/4);++i)
	{
		iwfixed c1 = IwGeomCos(a);
		iwfixed s1 = IwGeomSin(a);
		a += step;
		iwfixed c2 = IwGeomCos(a);
		iwfixed s2 = IwGeomSin(a);
		c.r = c.g = c.b = 255-i*colS;
		col[index] = c;		v[index++] = CIwSVec2(x+c1*r/IW_GEOM_ONE,y+s1*r/IW_GEOM_ONE);
		col[index] = c;		v[index++] = CIwSVec2(x+c1*r2/IW_GEOM_ONE,y+s1*r2/IW_GEOM_ONE);
		c.r = c.g = c.b = 255-(i+1)*colS;
		col[index] = c;		v[index++] = CIwSVec2(x+c2*r2/IW_GEOM_ONE,y+s2*r2/IW_GEOM_ONE);
		col[index] = c;		v[index++] = CIwSVec2(x+c2*r/IW_GEOM_ONE,y+s2*r/IW_GEOM_ONE);

	}
	CIwMaterial* m = IW_GX_ALLOC_MATERIAL();
	m->SetColAmbient(255,255,255,255);
	IwGxClear(IW_GX_DEPTH_BUFFER_F);
	IwGxSetMaterial(m);
	IwGxLightingOff();
	IwGxSetVertStreamScreenSpace(v,vertices);
	IwGxSetUVStream(0);
	IwGxSetColStream(col);
	IwGxDrawPrims(IW_GX_QUAD_LIST, 0, index);
	IwGxFlush();
	IwGxSwapBuffers();
}