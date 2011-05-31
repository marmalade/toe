#include "s3e.h"
#include "s3eLocation.h"
#include "s3eAudio.h"
#include "s3eVideo.h"
#include "s3eCompass.h"
#include "iwgx.h"
#include "toeFeatures.h"
#include <time.h>

using namespace TinyOpenEngine;


CtoeFeature::CtoeFeature():m_started(false),m_lasttime(time(0))
{
	AttachTail(toeGetActiveFeatures());
}
CtoeFeature::~CtoeFeature()
{
	Stop();
}

void CtoeFeature::Start()
{
	m_lasttime = time(0);
	if (m_started)
		return;
	m_started = true;
	StartFeature();
}
void CtoeFeature::Stop()
{
	if (!m_started)
		return;
	m_started = false;
	StopFeature();
}








//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeAudio::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeAudio> d ("CtoeAudio",
		ScriptTraits::Method("IsAvailable", &CtoeAudio::IsAvailable),
		ScriptTraits::Method("PlayFile", &CtoeAudio::PlayFile),
			0);
	return &d;
}
bool CtoeAudio::IsAvailable()
{
	return s3eAudioGetInt(S3E_AUDIO_AVAILABLE) != 0;
}
bool CtoeAudio::PlayFile(const char* fileName, int repeatCount)
{
	return S3E_RESULT_SUCCESS == s3eAudioPlay(fileName, (uint32)repeatCount);
}


//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeVideo::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeVideo> d ("CtoeVideo",
		ScriptTraits::Method("IsAvailable", &CtoeVideo::IsAvailable),
		ScriptTraits::Method("PlayFile", &CtoeVideo::PlayFile),
			0);
	return &d;
}
bool CtoeVideo::IsAvailable()
{
	return s3eVideoGetInt(S3E_VIDEO_AVAILABLE) != 0;
}
bool CtoeVideo::PlayFile(const char* fileName, int repeatCount)
{
	return S3E_RESULT_SUCCESS == s3eVideoPlay(fileName, (uint32)repeatCount,0,0,IwGxGetScreenWidth(),IwGxGetScreenHeight());
}
