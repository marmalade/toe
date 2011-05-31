#include <IwGx.h>
#include <s3eCamera.h>
#include <IwGxDebug.h>
#include <IwTextParserITX.h>
#include "toeLiveCameraFeed.h"
#include "toeEntity.h"

using namespace TinyOpenEngine;

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeLiveCameraFeed);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeLiveCameraFeed);

namespace TinyOpenEngine
{
	
	


}

//Constructor
CtoeLiveCameraFeed::CtoeLiveCameraFeed()
{
	//IwDebugTraceLinePrintf("CtoeBox2DCircle(0x%08X)",this);
	//m_FrameData = 0;
	//m_FrameWidth = 0;
	//m_FrameHeight = 0;
	//m_FramePitch = 0;
	image = 0;
	texture = 0;
	activeBuffer= 0;
	completeBuffer = 0;
	feedUpdated = false;
	started = false;
}

//Desctructor
CtoeLiveCameraFeed::~CtoeLiveCameraFeed()
{
	//IwDebugTraceLinePrintf("~CtoeBox2DCircle(0x%08X)",this);
	//if (m_FrameData)
	//	s3eFree(m_FrameData);
	if (image)
		delete image;
	if (activeBuffer) delete []activeBuffer;
	if (completeBuffer) delete []completeBuffer;
	if (texture)
		delete texture;
}

void CtoeLiveCameraFeed::BeforeDestruction(CtoeEntity* e)
{
	if (started)
	{
		s3eCameraStop();
		s3eCameraUnRegister(S3E_CAMERA_UPDATE_STREAMING, CameraUpdate);
		started = false;
	}
	CtoeSelfRenderedComponent::BeforeDestruction(e);
}

void CtoeLiveCameraFeed::BeforeInitialization(CtoeEntity* e)
{
	CtoeSelfRenderedComponent::BeforeInitialization(e);
	if (!started)
	{
		if (s3eCameraAvailable())
		{
			if (S3E_RESULT_ERROR == s3eCameraRegister(S3E_CAMERA_UPDATE_STREAMING, CameraUpdate, this))
	        {
				return;
			}

			if (s3eCameraStart(S3E_CAMERA_STREAMING_SIZE_HINT_SMALLEST, S3E_CAMERA_PIXEL_TYPE_RGB565_CONVERTED) == S3E_RESULT_SUCCESS)
			{
				started = true;
			}
		}
	}
}
void CtoeLiveCameraFeed::RequireImage(int16 reqw, int16 reqh)
{
	// Rotate image on 90'
	if (FlipCoordinates())
	{
		int16 a = reqw; reqw = reqh; reqh = a;
	}

	if (image)
	{
		int16 imageW = image->GetWidth();
		int16 imageH = image->GetHeight();
		if (imageW >= reqw && imageH >= reqh)
			return;
		delete image;
		delete [] completeBuffer;
		delete [] activeBuffer;
	}
	feedWidth = reqw;
	feedHeight = reqh;

	int w = 1; while (w < reqw) w = w<<1;
	int h = 1; while (h < reqh) h = h<<1;
	IwTrace(TOE,("Allocate camera feed buffer %dx%d",w,h));
	image = new CIwImage();
	image->SetFormat(CIwImage::RGB_565);
	image->SetWidth(w);
	image->SetHeight(h);
	image->SetBuffers();
	completeBuffer = new int16[image->GetPitch()/2*image->GetHeight()];
	activeBuffer = new int16[image->GetPitch()/2*image->GetHeight()];
	texture = new CIwTexture();
	texture->SetModifiable(true);
	texture->SetMipMapping(false);
	texture->SetImage(image);
}
// Callback that gets filled with camera buffer data
int32 CtoeLiveCameraFeed::CameraUpdate(void* systemData, void* userData)
{
	CtoeLiveCameraFeed* g_currentFeed = (CtoeLiveCameraFeed*)userData;
	if (!g_currentFeed)
		return 0;
	if (g_currentFeed->feedUpdated)
		return 0;
	// Frame data is no longer valid once s3eCameraStop is called

	s3eCameraFrameData* m_Frame = (s3eCameraFrameData*)systemData;

	g_currentFeed->RequireImage(m_Frame->m_Width,m_Frame->m_Height);

	int16*texels;

	//texels = g_currentFeed->completeBuffer; g_currentFeed->completeBuffer=g_currentFeed->activeBuffer; g_currentFeed->activeBuffer = texels;
	texels = g_currentFeed->activeBuffer;

	for (int yy=0; yy<(int)m_Frame->m_Height;++yy)
		for (int xx=0; xx<(int)m_Frame->m_Width;++xx)
		{
			int dx = xx;
			int dy = yy;
			// Rotate image on 90'
			if (g_currentFeed->FlipCoordinates())
			{
				dx = (int)m_Frame->m_Height-1-yy;
				dy = xx;
			}
			*(int16*)(texels+g_currentFeed->image->GetPitch()/2*dy+dx) = *(int16*)((uint8*)m_Frame->m_Data+xx*2+yy*m_Frame->m_Pitch);
		}

	g_currentFeed->activeBuffer=g_currentFeed->completeBuffer; g_currentFeed->completeBuffer = texels;
	g_currentFeed->feedUpdated = true;

	return 0;
}
void CtoeLiveCameraFeed::Render(CtoeRenderContext*)
{
	// Display status info
    //int32 camStatus;
    //const int textHeight = s3eDebugGetInt(S3E_DEBUG_FONT_SIZE_HEIGHT);

  
    // Copy frame data to screen
//    if (m_FrameData)
//    {
//        uint8* screen = (uint8*)s3eSurfacePtr();
//        uint8* buffer = (uint8*)m_FrameData;
//
//#define min(a,b) a < b ? a : b
//
//        const int screen_height = s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);
//        const int screen_pitch  = s3eSurfaceGetInt(S3E_SURFACE_PITCH);
//
//        const int height = min(m_FrameHeight, screen_height);
//        const int pitch  = min(m_FramePitch,  screen_pitch);
//
//		//IwGxFlush();
//
//        for (int y = 0; y < height-1; y++)
//        {
//            memcpy(&screen[y * screen_pitch], 
//                   &buffer[y * m_FramePitch], pitch);
//        }
//    }

	if (texture)
	{
		if (feedUpdated)
		{
			texture->ChangeTexels((uint8*)completeBuffer, CIwImage::RGB_565);
			texture->Upload();
			feedUpdated = false;
		}

		CIwMaterial* m = IW_GX_ALLOC_MATERIAL();
		m->SetTexture(texture);
		m->SetColAmbient(255,255,255,255);
		IwGxSetMaterial(m);
		static CIwSVec2 pos = CIwSVec2::g_Zero;
		int32 w = (int32)IwGxGetScreenWidth();
		int32 h = (int32)IwGxGetScreenHeight();
		static CIwSVec2 dx = CIwSVec2(w,h);
		static CIwSVec2 uv = CIwSVec2::g_Zero;
		static CIwSVec2 uvSize;
		uvSize = CIwSVec2((int16)(feedWidth*IW_GEOM_ONE/texture->GetWidth()), (int16)(feedHeight*IW_GEOM_ONE/texture->GetHeight()));
		IwGxDrawRectScreenSpace(&pos, &dx,&uv,&uvSize);
	}

}
//Reads/writes a binary file using @a IwSerialise interface.
void CtoeLiveCameraFeed::Serialise ()
{
	CtoeSelfRenderedComponent::Serialise();
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeLiveCameraFeed::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	
	return CtoeSelfRenderedComponent::ParseAttribute(pParser,pAttrName);
}
#endif