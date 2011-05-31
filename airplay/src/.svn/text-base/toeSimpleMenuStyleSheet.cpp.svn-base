#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeSimpleMenuStyleSheet.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuStyleSheet);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuStyleSheet);

//Constructor
CtoeSimpleMenuStyleSheet::CtoeSimpleMenuStyleSheet()
{
}
//Desctructor
CtoeSimpleMenuStyleSheet::~CtoeSimpleMenuStyleSheet()
{
	childItems.Delete();
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuStyleSheet::Serialise ()
{
	CIwResource::Serialise();
	childItems.Serialise();
	map.SerialiseHeader();
	for (uint32 i=0; i<map.size(); ++i)
	{
		IwSerialiseUInt32(map[i].NameHash);
		IwSerialiseUInt32(map[i].ClassHash);
		IwSerialiseUInt32(map[i].StateHash);
		IwSerialiseUInt32(map[i].Index);
	}
	styles.SerialiseHeader();
	for (uint32 i=0; i<styles.size(); ++i)
	{
		styles[i].Serialise();
	}
}

void CtoeSimpleMenuStyleSheet::Apply(CtoeSimpleMenuStyleSettings* other, uint32 n, uint32 c, uint32 s)
{
	for (uint32 i=0; i<map.size(); ++i)
	{
		toeSimpleMenuStyleSheetItem& st = map[i];
		if (((st.ClassHash == c) || (st.ClassHash == TOE_ANYSTYLE)) &&
			((st.NameHash == n) || (st.NameHash == TOE_ANYSTYLE)) &&
			((st.StateHash == s) || (st.StateHash == TOE_ANYSTYLE)))
		{
			styles[map[i].Index].Apply(other);
		}
	}
}

#ifdef IW_BUILD_RESOURCES
//Parses from text file: start block.
void	CtoeSimpleMenuStyleSheet::ParseOpen(CIwTextParserITX* pParser)
{
	CIwResource::ParseOpen(pParser);
}
//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuStyleSheet::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp("bindto", pAttrName))
	{
		map.push_back();
		pParser->ReadStringHash(&map.back().NameHash);
		pParser->ReadStringHash(&map.back().ClassHash);
		pParser->ReadStringHash(&map.back().StateHash);
		map.back().Index = styles.size();
		return true;
	}
	if (!stricmp("style", pAttrName))
	{
		styles.push_back();
		pParser->PushObject(&styles.back());
		return true;
	}
	return CIwResource::ParseAttribute(pParser, pAttrName);
}
//Parses from text file: end block.
void	CtoeSimpleMenuStyleSheet::ParseClose(CIwTextParserITX* pParser)
{
	IwGetResManager()->GetCurrentGroup()->AddRes(IwHashString("CtoeSimpleMenuStyleSheet"), this);
}
//Extends CIwParseable interface with this extra function: called on any "parent" object, if the "child" has not implemented ParseClose.
void	CtoeSimpleMenuStyleSheet::ParseCloseChild(CIwTextParserITX* pParser, CIwManaged* pChild)
{
	if (pChild == ((CIwManaged*)&styles.back()))
		return;
	//CIwResource::ParseCloseChild(pParser, pChild);
	childItems.Add(pChild);
}

IW_MANAGED_IMPLEMENT(CtoeSimpleMenuStyleSheetResHandler)

//Constructor
CtoeSimpleMenuStyleSheetResHandler::CtoeSimpleMenuStyleSheetResHandler(): CIwResHandler("simplemenustyle", "CtoeSimpleMenuStyleSheet")
{
	SetName("TOESIMPLEMENUSTYLE");
}
//Desctructor
CtoeSimpleMenuStyleSheetResHandler::~CtoeSimpleMenuStyleSheetResHandler()
{
}

//Buid resource method
CIwResource*	CtoeSimpleMenuStyleSheetResHandler::Build(const CIwStringL& pathname)
{
	IwGetTextParserITX()->ParseFile(pathname.c_str());
	return NULL;
}

#endif