#pragma once

#include <toeComponent.h>
#include <toeSelfRenderedComponent.h>
#include <s3eCamera.h>
#include <IwImage.h>
#include <IwTexture.h>

namespace TinyOpenEngine
{
	class CtoeLiveCameraFeed : public CtoeSelfRenderedComponent
	{
	protected:
		CIwImage* image;
		int16* activeBuffer;
		int16* completeBuffer;
		CIwTexture* texture;
		//uint16* m_FrameData;
		//int32 m_FrameWidth;
		//int32 m_FrameHeight;
		//int32 m_FramePitch;
		bool started;
		int32 feedWidth;
		int32 feedHeight;
		bool feedUpdated;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeLiveCameraFeed);
		//Constructor
		CtoeLiveCameraFeed();
		//Desctructor
		virtual ~CtoeLiveCameraFeed();

		virtual void Render(CtoeRenderContext*);

		virtual void BeforeDestruction(CtoeEntity*);
		virtual void BeforeInitialization(CtoeEntity*);

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();
		void RequireImage(int16 w, int16 h);
		bool FlipCoordinates() const {return true;};
#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	protected:
		static int32 CameraUpdate(void* systemData, void* userData);
	};
}