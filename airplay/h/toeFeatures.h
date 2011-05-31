#pragma once

#include <time.h>
#include <s3eLocation.h>
#include "toeIntrusiveList.h"
#include "toeScriptingSubsystem.h"

namespace TinyOpenEngine
{
	class CtoeFeature;

	TtoeIntrusiveList<CtoeFeature> * toeGetActiveFeatures();

	class CtoeFeature: public TtoeIntrusiveListItem<CtoeFeature>
	{
		bool m_started;
		time_t m_lasttime;
	public:
		CtoeFeature();
		virtual ~CtoeFeature();
		void Start();
		void Stop();
	protected:
		virtual void StartFeature() {};
		virtual void StopFeature() {};
	};

	class CtoeAccelerometer: public CtoeFeature
	{
	public: 
		virtual ~CtoeAccelerometer();

		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();
		static bool IsAvailable();
		static int GetX();
		static int GetY();
		static int GetZ();
	protected:
		static CtoeAccelerometer* RequestFeature();
		virtual void StartFeature();
		virtual void StopFeature();
	};

	class CtoeVideo: public CtoeFeature
	{
	public: 
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();

		static bool IsAvailable();
		static bool PlayFile(const char*, int repeatCount);
	};

	class CtoeCompass: public CtoeFeature
	{
	public: 
		~CtoeCompass();
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();

		static bool IsAvailable();

		static int GetX();
		static int GetY();
		static int GetZ();
	protected:
		static CtoeCompass* RequestFeature();
		virtual void StartFeature();
		virtual void StopFeature();
	};
	class CtoeLocation: public CtoeFeature
	{

	public: 
		private:
		s3eLocation l;
		time_t m_recievedAt;

	public: 
		virtual ~CtoeLocation();

		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();
		static bool IsAvailable();
		static float GetLatitude();
		static float GetLongitude();
	protected:
		static CtoeLocation* RequestFeature();
		static int32 Callback (void* systemData, void* userData);
		virtual void StartFeature();
		virtual void StopFeature();
		void SaveToConfig();
		void LoadFromConfig();

	};
	class CtoeAudio: public CtoeFeature
	{
	public: 
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();

		static bool IsAvailable();
		static bool PlayFile(const char*, int repeatCount);
	};
}