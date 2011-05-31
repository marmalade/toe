#include <IwFile.h>
#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeLuaScript.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeLuaScript);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeLuaScript);

//Constructor
CtoeLuaScript::CtoeLuaScript()
{
	buffer = 0;
}
//Desctructor
CtoeLuaScript::~CtoeLuaScript()
{
	AssignBuffer(0);
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeLuaScript::Serialise ()
{
	CIwResource::Serialise();
	if (IwSerialiseIsReading())
	{
		uint32 len = 0;
		IwSerialiseUInt32(len);
		if (len)
		{
			buffer = new char[len+1];
			IwSerialiseChar(*buffer,len,8);
			buffer[len] = '\0';
		}
	}
	else
	{
		uint32 len = 0;
		if (buffer)
		{
			len = strlen(buffer);
			IwSerialiseUInt32(len);
			if (len > 0)
				IwSerialiseChar(*buffer,len,8);
		}
		else
		{
			IwSerialiseUInt32(len);
		}
	}
}
void CtoeLuaScript::AssignBuffer(char* buf)
{
	if (buffer) delete [] buffer;
	buffer = buf;
}
#ifdef IW_BUILD_RESOURCES


IW_MANAGED_IMPLEMENT(CtoeLuaScriptResHandler)

//Constructor
CtoeLuaScriptResHandler::CtoeLuaScriptResHandler(): CIwResHandler("lua", "CtoeLuaScript")
{
	SetName("TOELUASCRIPT");
}
//Desctructor
CtoeLuaScriptResHandler::~CtoeLuaScriptResHandler()
{
}

//Buid resource method
CIwResource*	CtoeLuaScriptResHandler::Build(const CIwStringL& pathname)
{
	s3eFile* pFile = IwFileOpenPrefixed(pathname.c_str(), "rb");
	if (!pFile)
	{
		IwAssertMsg(TOE, false, ("Invalid file %s", pathname.c_str()));
		return 0;
	}
	CtoeLuaScript* res = new CtoeLuaScript();
	s3eFileSeek(pFile, 0, S3E_FILESEEK_END);
	int32 len = s3eFileTell(pFile);
	s3eFileSeek(pFile, 0, S3E_FILESEEK_SET);
	char* buf = new char[len+1];
	s3eFileRead(buf,1,len,pFile);
	buf[len] = '\0';
	res->AssignBuffer(buf);
	s3eFileClose(pFile);
	return res;
}

#endif