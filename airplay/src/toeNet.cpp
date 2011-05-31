#include <IwResManager.h>
#include <IwHTTP.h>
#include "toeNet.h"
#include "toeLoadingScreen.h"
#include "toeUtils.h"


using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	class CtoeHTTPRequest
	{
	protected:
		bool isActive;
		CIwHTTP transport;
		CIwArray<char> response;
		uint32 responseSize;
	public:
		CtoeHTTPRequest()
		{
			responseSize = 0;
			isActive = false;
		}
		virtual ~CtoeHTTPRequest()
		{
			Cancel();
		}
		bool IsActive() const { return isActive;}
		char* GetResponseString() const { if (response.size() == 0) return ""; return &*response.begin();}
		void Cancel()
		{
			if (isActive)
			{
				transport.Cancel();
				isActive = false;
			}
		}

		CIwHTTP& GetTransport() {return transport;}

	protected:
		virtual void OnError()
		{
			isActive = false;
		}
		virtual void OnResponseComplete()
		{
			isActive = false;
		}
		virtual void OnHeadersComplete()
		{
			if (transport.GetStatus() == S3E_RESULT_ERROR)
			{
				OnError();
				return;
			}
			RawDownloadResponse();
		}
		virtual void OnChunkComplete()
		{
			if (transport.GetStatus() == S3E_RESULT_ERROR)
			{
				OnError();
				return;
			}
			response[transport.ContentReceived()] = 0;
			if (transport.ContentReceived() != transport.ContentLength())
			{
				uint32 oldLen = responseSize;
				if (responseSize < transport.ContentExpected())
					responseSize = transport.ContentExpected();
				else
					responseSize += 1024;

				response.resize(responseSize+1);
				transport.ReadDataAsync(&*response.begin(), responseSize - oldLen, 10000, RawChunkComplete, this);
			}
			else
			{
				OnResponseComplete();
			}
		}
		void RawDownloadResponse()
		{
			responseSize = transport.ContentExpected();
			if (!responseSize) responseSize = 1024;
			response.resize(responseSize);
			response[0] = 0;
			transport.ReadDataAsync(&*response.begin(), 
											responseSize,
											10000,
											RawChunkComplete, this);

		}
		static int RawChunkComplete(void*sys,void*http)
		{
			((CtoeHTTPRequest*)http)->OnChunkComplete();
			return 0;
		}
		static int RawHeadersComplete(void*sys,void*http)
		{
			((CtoeHTTPRequest*)http)->OnHeadersComplete();
			return 0;
		}
		void RawGet(const char* gUrl)
		{
			if (isActive)
			{
				IwAssertMsg(TOE,false,("Another request isn't complete yet"));
				OnError();
				return;
			}
			isActive = true;
			if (S3E_RESULT_SUCCESS != transport.Get(gUrl, RawHeadersComplete, this))
			{
				OnError();
			}
		}
	};
	class CtoeHTTPDownloadString: public CtoeHTTPRequest
	{
	public:
		void Get(const char* s)
		{
			RawGet(s);
		}
	/*protected:
		virtual void OnResponseComplete()
		{
			CtoeLoadingScreen::Render();
			CtoeHTTPRequest::OnResponseComplete();
		}
		virtual void OnHeadersComplete()
		{
			CtoeLoadingScreen::Render();
			CtoeHTTPRequest::OnHeadersComplete();
		}
		virtual void OnChunkComplete()
		{
			CtoeLoadingScreen::Render();
			CtoeHTTPRequest::OnChunkComplete();
		}*/
	};
}


//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeNet::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeNet> d ("CtoeNet",
			ScriptTraits::Method("DownloadString", &CtoeNet::DownloadString),
			0);
	return &d;
}

int32 toeSendHTTPGetComplete(void* systemData, void* userData)
{
	CIwHTTP* http = (CIwHTTP*)userData;
	http->Cancel();
	delete http;
	return 0;
}

std::string CtoeNet::DownloadString(const char* s1)
{
	CtoeHTTPDownloadString http;
	http.Get(s1);
	while (http.IsActive())
	{
		CtoeLoadingScreen::Render();
		s3eDeviceYield(30);
	}
	return std::string(http.GetResponseString());
}
