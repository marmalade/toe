#include "s3e.h"
#include "s3eCompass.h"
#include "iwgx.h"
#include "toeFeatures.h"
#include <time.h>

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	CtoeCompass* g_toeCompass = 0;
}

//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeCompass::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeCompass> d ("CtoeCompass",
		ScriptTraits::Method("IsAvailable", &CtoeCompass::IsAvailable),
		ScriptTraits::Method("GetX", &CtoeCompass::GetX),
		ScriptTraits::Method("GetY", &CtoeCompass::GetY),
		ScriptTraits::Method("GetZ", &CtoeCompass::GetZ),
			0);
	return &d;
}
CtoeCompass::~CtoeCompass()
{
	g_toeCompass = 0;
}
CtoeCompass* CtoeCompass::RequestFeature()
{
	if (g_toeCompass)
		return g_toeCompass;
	if (!IsAvailable())
		return 0;
	g_toeCompass = new CtoeCompass();
	g_toeCompass->Start();
	return g_toeCompass;
}
bool CtoeCompass::IsAvailable()
{
	return s3eCompassAvailable() != 0;
}
void CtoeCompass::StartFeature()
{
	s3eCompassStart();
}
void CtoeCompass::StopFeature()
{
	s3eCompassStop();
}
int CtoeCompass::GetX()
{
	if (RequestFeature())
	{
		s3eCompassHeading dir;
		s3eCompassGetHeading(&dir);
		return dir.m_X;
	}
	return 0;
}
int CtoeCompass::GetY()
{
	if (RequestFeature())
	{
		s3eCompassHeading dir;
		s3eCompassGetHeading(&dir);
		return dir.m_Y;
	}
	return 0;
}
int CtoeCompass::GetZ()
{
	if (RequestFeature())
	{
		s3eCompassHeading dir;
		s3eCompassGetHeading(&dir);
		return dir.m_Z;
	}
	return 0;
}
