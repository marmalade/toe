#include <IwGx.h>
#include <IwGxDebug.h>
#include <IwTextParserITX.h>
#include "toe2DBox.h"
#include "toeEntity.h"

using namespace TinyOpenEngine;

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(Ctoe2DBox);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(Ctoe2DBox);

//Constructor
Ctoe2DBox::Ctoe2DBox()
{
	//IwDebugTraceLinePrintf("CtoeBox2DCircle(0x%08X)",this);
	width = 10;
	height = 10;
}

//Desctructor
Ctoe2DBox::~Ctoe2DBox()
{
	//IwDebugTraceLinePrintf("~CtoeBox2DCircle(0x%08X)",this);
}
void Ctoe2DBox::Render(CtoeRenderContext*)
{
	CIwMaterial* m =  IW_GX_ALLOC_MATERIAL();
	m->SetColDiffuse(255,255,255,255);
	IwGxSetMaterial(m);

	CIwMat t = GetEntity()->GetWorldTransform();
	int w2 = width/2;
	int h2 = height/2;
	CIwSVec2* pVecs = IW_GX_ALLOC(CIwSVec2,4);
	CIwVec3 v = t.TransformVec(CIwVec3(-w2,-h2,0));
	pVecs[0] = CIwSVec2(v.x,v.y);
	v = t.TransformVec(CIwVec3(w2,-h2,0));
	pVecs[1] = CIwSVec2(v.x,v.y);
	v = t.TransformVec(CIwVec3(w2,h2,0));
	pVecs[2] = CIwSVec2(v.x,v.y);
	v = t.TransformVec(CIwVec3(-w2,h2,0));
	pVecs[3] = CIwSVec2(v.x,v.y);
	IwGxSetVertStreamScreenSpace(pVecs, 4); 

	IwGxSetUVStream(NULL);
	IwGxSetColStream(NULL);

	uint16* pInds = IW_GX_ALLOC(uint16, 8); 
	pInds[0] = 0;
	pInds[1] = 1;
	pInds[2] = 1;
	pInds[3] = 2;
	pInds[4] = 2;
	pInds[5] = 3;
	pInds[6] = 3;
	pInds[7] = 0;
	IwGxDrawPrims(IW_GX_LINE_LIST, pInds, 8); 
}
//Reads/writes a binary file using @a IwSerialise interface.
void Ctoe2DBox::Serialise ()
{
	CtoeSelfRenderedComponent::Serialise();
	IwSerialiseInt32(width);
	IwSerialiseInt32(height);
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	Ctoe2DBox::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp(pAttrName,"width"))
	{
		float f;
		pParser->ReadFloat(&f);
		width = (int)(f);
		return true;
	}
	if (!stricmp(pAttrName,"height"))
	{
		float f;
		pParser->ReadFloat(&f);
		height = (int)(f);
		return true;
	}
	return CtoeSelfRenderedComponent::ParseAttribute(pParser,pAttrName);
}
#endif