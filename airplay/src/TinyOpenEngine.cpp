#include <s3e.h>
#include <IwGx.h>
#include <IwGraphics.h>
#include <IwTextParserITX.h>
//#include <s3eTouchpad.h>
#include "TinyOpenEngine.h"
#include "toeConfig.h"
#include "toeLoadingScreen.h"
#include "toeUtils.h"
#include "toeWorld.h"
#include "toeScriptingSubsystem.h"
#include "toeComponent.h"
#include "toeSubsystem.h"
#include "toeFeatures.h"
#include "toeDefaultHitTest.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	bool isTinyOpenEngineInitialized = false;
	bool exitApplication = false;
	CIwStringL* nextWorld = 0;
	uint32 nextWorldHash = 0;
	s3eSocket* g_toeTraceSocket=0;
	CIwArray<CtoeScriptableClassDeclaration*>* toe_scriptClassDeclarations=0;
	TtoeIntrusiveList<CtoeFeature> * toe_featuresList = 0;
	TtoeIntrusiveList<CtoeFeature> * toeGetActiveFeatures()
	{
		if (!toe_featuresList)
			toe_featuresList = new TtoeIntrusiveList<CtoeFeature>();
		return toe_featuresList;
	}
	void toeLoadingCallback()
	{
		if (IwSerialiseIsReading())
			CtoeLoadingScreen::Render();
	}

	void toeLoadAndRunNextWorld();
	void toeExitApplication()
	{
		exitApplication = true;
	}
	CtoeInputFilter* inputFilter = 0;

	void toeKeyboardKeyEvent(s3eKeyboardEvent*e, void*)
	{
		inputFilter->KeyboardKeyEvent(e);
	}
	void toePointerTouchEvent(s3ePointerTouchEvent*e, void*)
	{
		inputFilter->PointerTouchEvent(e);
	}
	void toePointerTouchMotionEvent(s3ePointerTouchMotionEvent*e, void*)
	{
		inputFilter->PointerTouchMotionEvent(e);
	}
	void toePointerButtonEvent(s3ePointerEvent*e, void*)
	{
		inputFilter->PointerButtonEvent(e);
	}
	void toePointerMotionEvent(s3ePointerMotionEvent*e, void*)
	{
		inputFilter->PointerMotionEvent(e);
	}
	
}
//Reads/writes a binary file using @a IwSerialise interface.
void TinyOpenEngine::toeSerialiseString (std::string & s)
{
	if (IwSerialiseIsWriting())
	{
		uint32 len = s.size();
		IwSerialiseUInt32(len);
		for (std::string::iterator i=s.begin(); i!=s.end();++i)
		{
			IwSerialiseChar(*i);
		}
	}
	else
	{
		uint32 len;
		IwSerialiseUInt32(len);
		if (!len)
		{
			s.clear();
		}
		else
		{
			s.resize(len,' ');
			for (std::string::iterator i=s.begin(); i!=s.end() && len;++i,--len)
			{
				IwSerialiseChar(*i);
			}
		}
	}
}
void	TinyOpenEngine::toeReadString(CIwTextParserITX* pParser, std::string* s)
{
		char* c = pParser->ReadString();
		*s = c;
		delete c;
}
void TinyOpenEngine::toeTrace(const char* format, ...)
{
	if (!toeIsTraceEnabled())
		return;
	if (!g_toeTraceSocket)
	{
		g_toeTraceSocket = s3eSocketCreate(S3E_SOCKET_UDP);
		int on = 1;
		//s3eSocketSetOpt(g_toeTraceSocket, S3E_SOCKET_NODELAY, &on, sizeof(on));
		s3eSocketSetOpt(g_toeTraceSocket, S3E_SOCKET_BROADCAST, &on, sizeof(on));
		s3eInetAddress          g_MyAddr;
		memset(&g_MyAddr, 0, sizeof(g_MyAddr));
		//g_MyAddr.m_Port = s3eInetHtons(23456);
		s3eSocketBind(g_toeTraceSocket, &g_MyAddr, 1);
	}
	s3eInetAddress          toMyAddr;
	memset(&toMyAddr, 0, sizeof(toMyAddr));
	toMyAddr.m_Port = s3eInetHtons(23456);
	toMyAddr.m_IPAddress = 0xFFFFFFFF;
	s3eSocketSendTo(g_toeTraceSocket, format, strlen(format), 0, &toMyAddr);
}
bool TinyOpenEngine::toeIsTraceEnabled()
{
	return false;
	//return 0!=s3eDebugGetInt(S3E_DEBUG_TRACE_ENABLED);
}
void TinyOpenEngine::toeInit()
{
	IwGxInit();
	IwResManagerInit();
	IwGraphicsInit();

	CtoeLoadingScreen::Render();

	if (isTinyOpenEngineInitialized)
		return;
	isTinyOpenEngineInitialized = true;

	#ifdef IW_BUILD_RESOURCES
	IwGetResManager()->AddHandler(new CtoeWorldResHandler);
	#endif

	if (toeIsTraceEnabled())
		toeTrace("Application started");

	IW_CLASS_REGISTER(CtoeWorld);
	IW_CLASS_REGISTER(CtoeDefaultHitTest);

	toe_scriptClassDeclarations = new CIwArray<CtoeScriptableClassDeclaration*>;
	toeRegisterClass(CtoeConfig::GetClassDescription());
	toeRegisterClass(CtoeAccelerometer::GetClassDescription());
	toeRegisterClass(CtoeLocation::GetClassDescription());
	toeRegisterClass(CtoeCompass::GetClassDescription());
	toeRegisterClass(CtoeAudio::GetClassDescription());
	toeRegisterClass(CtoeUtils::GetClassDescription());

	CtoeConfig::Load();

	IwSerialiseSetCallbackPeriod(4*1024);
	IwSerialiseSetCallback(TinyOpenEngine::toeLoadingCallback);
	IwGetResManager()->SetBuildGroupCallbackPre(TinyOpenEngine::toeLoadingCallback);
	IwGetResManager()->SetBuildGroupCallbackPost(TinyOpenEngine::toeLoadingCallback);


	if (!inputFilter)
		inputFilter = new CtoeInputFilter();
	
	s3eKeyboardRegister(S3E_KEYBOARD_KEY_EVENT, (s3eCallback)toeKeyboardKeyEvent, 0);
	if (s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE))
	{
		s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)toePointerTouchEvent, 0);
		s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)toePointerTouchMotionEvent, 0);
	}
	else
	{
		s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)toePointerButtonEvent, 0);
		s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)toePointerMotionEvent, 0);
	}
	/*if (s3eTouchpadAvailable ())
	{
		s3eTouchpadRegister ( S3E_TOUCHPAD_EVENT, (s3eCallback)toeTouchpadEvent, 0);
		s3eTouchpadRegister ( S3E_TOUCHPAD_MOTION_EVENT, (s3eCallback)toeTouchpadMotionEvent, 0);
	}*/
}

void TinyOpenEngine::toeTerminate()
{
	if (!isTinyOpenEngineInitialized)
		return;
	isTinyOpenEngineInitialized = false;

	CtoeConfig::Save();
	CtoeConfig::Close();

	IwSerialiseSetCallback(0);
	IwGetResManager()->SetBuildGroupCallbackPre(0);
	IwGetResManager()->SetBuildGroupCallbackPost(0);

	if (g_toeTraceSocket)
	{
		s3eSocketClose(g_toeTraceSocket);
		//delete g_toeTraceSocket;
		g_toeTraceSocket = 0;
	}

	if (toe_featuresList)
	{
		while (toe_featuresList->GetFirstChild())
			delete toe_featuresList->GetFirstChild();
		delete toe_featuresList;
		toe_featuresList = 0;
	}

	if (inputFilter)
	{
		delete inputFilter;
		inputFilter = 0;
	}


	s3eKeyboardUnRegister(S3E_KEYBOARD_KEY_EVENT, (s3eCallback)toeKeyboardKeyEvent);
	if (s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE))
	{
		s3ePointerUnRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)toePointerTouchEvent);
		s3ePointerUnRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)toePointerTouchMotionEvent);
	}
	else
	{
		s3ePointerUnRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)toePointerButtonEvent);
		s3ePointerUnRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)toePointerMotionEvent);
	}

	if (toe_scriptClassDeclarations)
	{
		for (CIwArray<CtoeScriptableClassDeclaration*>::iterator i = toe_scriptClassDeclarations->begin(); i!=toe_scriptClassDeclarations->end(); ++i)
		{
			(*i)->Close();
			//delete(*i);
		}
		delete toe_scriptClassDeclarations;
		toe_scriptClassDeclarations = 0;
	}

	if (toeIsTraceEnabled())
		toeTrace("Application closed gracefully");

	IwGraphicsTerminate();
	IwResManagerTerminate();
	IwGxTerminate();
}
void TinyOpenEngine::toeLoadAndRunNextWorld()
{
	while (nextWorld)
	{
		IwTrace(TOE, ("Load world \"%s\", resource hash 0x%08x",nextWorld->c_str(), nextWorldHash));
		CIwResGroup* fx_group = IwGetResManager()->LoadGroup(nextWorld->c_str());
		delete nextWorld;
		nextWorld = 0;

		CtoeWorld* w = 0;
		if (nextWorldHash)
			w = (CtoeWorld*)fx_group->GetResHashed(nextWorldHash, "CtoeWorld");
		else
		{
			CIwResList* l = fx_group->GetListNamed("CtoeWorld");
			if (l == 0 || l->m_Resources.GetSize() == 0)
				IwAssertMsg(TOE,false,("No CtoeWorld found in group"));
			w = (CtoeWorld*)l->m_Resources[0];
		}
		if (w)
			toeRunWorld(w);
		IwGetResManager()->DestroyGroup(fx_group);
	}
}
void TinyOpenEngine::toeOpenGroupWorld(const char*resource)
{
	toeOpenWorld(resource,0);
}
void TinyOpenEngine::toeOpenWorld(const char*resource,const char*world)
{
	CtoeWorld* w = inputFilter->GetCurrentWorld();
	if (nextWorld) delete nextWorld;
	nextWorld = new CIwStringL(resource);
	if (world)
		nextWorldHash = IwHashString(world);
	else
		nextWorldHash = 0;
	if (w)
	{
		w->Close();
	}
	else
	{
		toeLoadAndRunNextWorld();
	}
}
void TinyOpenEngine::toeCloseWorld()
{
	CtoeWorld* w = inputFilter->GetCurrentWorld();
	w->Close();
}
void TinyOpenEngine::toeRunWorld(CtoeWorld*w)
{
	if (!w) return;
	w->Open();
	CtoeWorld*old = inputFilter->GetCurrentWorld();
	inputFilter->SetCurrentWorld(w);


	int32 prevFrame = (int32)s3eTimerGetMs();
	int32 newFrame = prevFrame;
	int32 dt=0;
	int32 preferedFrameTime = 1000/30;

	while (1)
	{
		newFrame = (int32)s3eTimerGetMs();
		dt = newFrame-prevFrame;
		toeTrace("Application frame %d",dt);
		//If game runs slow we shall limit lags
		if (dt > preferedFrameTime*2) dt = preferedFrameTime*2;
		if (dt < preferedFrameTime)
		{
				s3eDeviceYield(preferedFrameTime-dt);
				newFrame = (int32)s3eTimerGetMs();
				dt = newFrame-prevFrame;
		}
		else
		{
			s3eDeviceYield(0);
		}
		prevFrame = newFrame;

		s3eKeyboardUpdate();
		s3ePointerUpdate();

		/*if (g_actions.size() > 0)
		{
			for (uint32 ai=0; ai<g_actions.size(); ++ai)
			{
				g_actions[ai]->DoAction();
				delete g_actions[ai];
				g_actions[ai] = 0;
			}
			g_actions.clear();
		}*/
		bool result = true;
		if	(
			(result == false) ||
			(s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN) ||
			(s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN) ||
			(s3eDeviceCheckQuitRequest()) || exitApplication
			)
			break;

		w->Update((dt*IW_GEOM_ONE)/1000);
		w->Render();
		if (w->IsClosed())
			break;
	}
	if (!w->IsClosed())
		w->Close();
	inputFilter->SetCurrentWorld(old);
}
void TinyOpenEngine::toeRegisterClass(CtoeScriptableClassDeclaration* c)
{
	toe_scriptClassDeclarations->push_back(c);
}
void TinyOpenEngine::toeRegisterScriptableClasses(ItoeScriptingSubsystem* system)
{
	if (!toe_scriptClassDeclarations)
		return;
	for (CIwArray<CtoeScriptableClassDeclaration*>::iterator i = toe_scriptClassDeclarations->begin(); i!=toe_scriptClassDeclarations->end(); ++i)
	{
		system->RegisterClass(*i);
	}
}