#include "toeFeatures.h"
#include "s3eLocation.h"
#include "toeConfig.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	CtoeLocation* g_toeLocation = 0;
}

//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeLocation::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeLocation> d ("CtoeLocation",
		ScriptTraits::Method("IsAvailable", &CtoeLocation::IsAvailable),
		ScriptTraits::Method("GetLatitude", &CtoeLocation::GetLatitude),
		ScriptTraits::Method("GetLongitude", &CtoeLocation::GetLongitude),
			0);
	return &d;
}

bool CtoeLocation::IsAvailable()
{
	return s3eLocationAvailable() != 0;
}
CtoeLocation::~CtoeLocation()
{
	g_toeLocation = 0;
}
CtoeLocation* CtoeLocation::RequestFeature()
{
	if (g_toeLocation)
		return g_toeLocation;
	g_toeLocation = new CtoeLocation();
	g_toeLocation->Start();
	return g_toeLocation;
}
void CtoeLocation::SaveToConfig()
{
		CtoeConfig::SetFloat("toe-location-latitude", (float)l.m_Latitude);
		CtoeConfig::SetFloat("toe-location-longitude", (float)l.m_Longitude);
}
void CtoeLocation::LoadFromConfig()
{
		l.m_Latitude = CtoeConfig::GetFloat("toe-location-latitude");
		l.m_Longitude = CtoeConfig::GetFloat("toe-location-longitude");
}
void CtoeLocation::StartFeature()
{
	m_recievedAt = 0;
	s3eLocationStart();
	if (CtoeConfig::IsExist("toe-location-latitude"))
	{
		g_toeLocation->LoadFromConfig();
	}
	else
	{
		s3eLocationGet(&l);
		SaveToConfig();
	}
	s3eLocationRegister(S3E_LOCATION_CALLBACK_LOCATION_UPDATED, Callback, this);
}
int32 CtoeLocation::Callback (void* systemData, void* userData)
{
	if (g_toeLocation)
	{
		g_toeLocation->l = *((s3eLocation*)systemData);
		g_toeLocation->m_recievedAt = time(0);
		g_toeLocation->SaveToConfig();
	}
	return 0;
}
void CtoeLocation::StopFeature()
{
	s3eLocationStop();
	s3eLocationUnRegister(S3E_LOCATION_CALLBACK_LOCATION_UPDATED, Callback);
}
float CtoeLocation::GetLatitude()
{
	return (float)RequestFeature()->l.m_Latitude;
}
float CtoeLocation::GetLongitude()
{
	return (float)RequestFeature()->l.m_Latitude;
}
