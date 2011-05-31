#include <IwResManager.h>
#include "toeUtils.h"
#include "pugixml.hpp"
#include "s3eOSReadString.h"


using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	unsigned int UTF8_MALFORMED((unsigned int)0xfffd);

	bool toeContinuationUtf8(const unsigned char * data, int count)
	{
	  for (int i = 0; i < count; ++i)
	  {
		if ((data[i]&0xC0)!= 0x80)
		  return false;
	  }
	  return true;
	}

}
//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeUtils::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeUtils> d ("CtoeUtils",
			ScriptTraits::Method("GetResourceByName", &CtoeUtils::GetResourceByName),
			ScriptTraits::Method("GetDeviceID", &CtoeUtils::GetDeviceID),
			ScriptTraits::Method("GetDevicePhone", &CtoeUtils::GetDevicePhone),
			ScriptTraits::Method("GetDeviceOS", &CtoeUtils::GetDeviceOS),
			ScriptTraits::Method("GetDeviceClass", &CtoeUtils::GetDeviceClass),
			ScriptTraits::Method("GetDeviceArchitecture", &CtoeUtils::GetDeviceArchitecture),
			ScriptTraits::Method("GetDeviceS3eVersion", &CtoeUtils::GetDeviceS3eVersion),
			ScriptTraits::Method("GetDeviceTotalRam", &CtoeUtils::GetDeviceTotalRam),
			ScriptTraits::Method("GetDeviceFreeRam", &CtoeUtils::GetDeviceFreeRam),
			ScriptTraits::Method("AssertMsg", &CtoeUtils::AssertMsg),
			ScriptTraits::Method("ReadString", &CtoeUtils::ReadString),
			ScriptTraits::Method("UrlEncode", &CtoeUtils::UrlEncode),
			0);
	return &d;
}

const char* CtoeUtils::GetDeviceID() { return s3eDeviceGetString(S3E_DEVICE_ID);  }
const char* CtoeUtils::GetDevicePhone() { return s3eDeviceGetString(S3E_DEVICE_PHONE_NUMBER);  }
const char* CtoeUtils::GetDeviceOS() { return s3eDeviceGetString(S3E_DEVICE_OS);  }
const char* CtoeUtils::GetDeviceClass() { return s3eDeviceGetString(S3E_DEVICE_CLASS);  }
const char* CtoeUtils::GetDeviceArchitecture() { return s3eDeviceGetString(S3E_DEVICE_ARCHITECTURE);  }
const char* CtoeUtils::GetDeviceS3eVersion() { return s3eDeviceGetString(S3E_DEVICE_S3E_VERSION);  }
int CtoeUtils::GetDeviceTotalRam() { return s3eDeviceGetInt(S3E_DEVICE_TOTAL_RAM);  }
int CtoeUtils::GetDeviceFreeRam() { return s3eDeviceGetInt(S3E_DEVICE_FREE_RAM);  }
void CtoeUtils::AssertMsg(const char *m)
{
	IwDebugAssertShow(m,"",0,true);
}
unsigned int CtoeUtils::DecodeUtf8(const void * p, unsigned int & returnValue)
{
  const unsigned char * data = static_cast<const unsigned char*>(p);
  int returnLength = 1;
  if (data[0] < 0x80) {
    // regular ASCII char
    // 0x00000000 - 0x0000007F:
    returnValue = data[0];
    return 1;
  }
  if (data[0] < 0xC0 || data[0] > 0xfd)
  {
    // not a valid start byte.
    goto malformed;
  }

  if ( (data[0] & 0xE0) == 0xC0) {
    // 0x00000080 - 0x000007FF:
    if (toeContinuationUtf8(&data[1],1)) {
      returnValue =  ((data[0] & 0x1f)<<6) | (data[1]&0x3f);
      returnLength = 2;
      goto checkLength;
    } else {
      goto malformed;
    }
  }
  if ( (data[0] & 0xF0) == 0xE0) {
    // 0x00000800 - 0x0000FFFF:
    if (toeContinuationUtf8(&data[1],2)) {
      returnValue =  ((data[0] & 0xf)<<(12)) | ((data[1]&0x3f)<<6) | (data[2]&0x3f);
      returnLength = 3;
      goto checkLength;
    } else {
      goto malformed;
    }
  }

  if ( (data[0] & 0xF8) == 0xF0) {
    // 0x00010000 - 0x001FFFFF:
    if (toeContinuationUtf8(&data[1],3)) {
      returnValue =  ((data[0] & 0x7)<<(18)) | ((data[1]&0x3f)<<12) | ((data[2]&0x3f)<<6) | (data[3]&0x3f);
      returnLength = 4;
      goto checkLength;
    } else {
      goto malformed;
    }
  }

  if ( (data[0] & 0xFC) == 0xF8) {
    //0x00200000 - 0x03FFFFFF:
    if (toeContinuationUtf8(&data[1],4)) {
      returnValue =  ((data[0] & 0x3)<<(24)) | ((data[1]&0x3f)<<18) | ((data[2]&0x3f)<<12) | ((data[3]&0x3f)<<6) | (data[4]&0x3f);
      returnLength = 5;
      goto checkLength;
    } else {
      goto malformed;
    }
  }
  if ( (data[0] & 0xFE) == 0xFC) {
    // 0x04000000 - 0x7FFFFFFF:
    if (toeContinuationUtf8(&data[1],5)) {
      returnValue =  ((data[0] & 0x1)<<(30)) | ((data[1]&0x3f)<<24) | ((data[2]&0x3f)<<18) | ((data[3]&0x3f)<<12) | ((data[4]&0x3f)<<6)
        | (data[5]&0x3f);
      returnLength = 6;
      goto checkLength;
    } else {
      goto malformed;
    }
  }

  // not implemented
  returnValue =  data[0];
  return 1;
malformed:
  returnValue = UTF8_MALFORMED;
  return 1;
checkLength:
  if (
         ( (returnLength > 1) && (returnValue < 0x80))
      || ( (returnLength > 2) && (returnValue < 0x800))
      || ( (returnLength > 3) && (returnValue < 0x10000))
      || ( (returnLength > 4) && (returnValue < 0x200000))
      || ( (returnLength > 5) && (returnValue < 0x4000000))
     )
      {
    returnValue = UTF8_MALFORMED;
  }
  if (returnValue != UTF8_MALFORMED &&
      ( ( returnValue >= 0xd800 && returnValue <= 0xdfff)
        || returnValue == 0xfffe
        || returnValue == 0xffff
      )
     )
  {
    returnValue = UTF8_MALFORMED;
  }
  return returnLength;
}
std::string CtoeUtils::UrlEncode(const char* s) {
        std::string encoded;
		if (!s || !*s) return encoded;
		while (*s) {
                unsigned int ch;
				int len = DecodeUtf8(s,ch);
				if (UTF8_MALFORMED == ch)
					return encoded;
				s += len;
                if ((ch >= 0x00 && ch <= 0x26) ||
                        ch == 0x2B || ch == 0x2C || ch == 0x2F ||
                        (ch >= 0x3A && ch <= 0x40) || (ch >= 0x7B && ch <= 0x7E) || (ch >= 0x5B && ch <= 0x5E) ||
                        ch == 0x60 || (ch >= 0x80))
                {
					char buf [32];
					if (ch < 128)
						sprintf(buf,"%%%02X",ch);
					else
						sprintf(buf,"%%u%04X",ch);
                    encoded += buf;
                }
                else {
                        encoded += (char)ch;
                }
        }

        return encoded;
}
	 
const char* CtoeUtils::ReadString(const char * t,const char * def)
{
	return s3eOSReadStringUTF8WithDefault(t,def);
}
CIwManaged* CtoeUtils::GetResourceByName(const char* id,const char* type)
{
	return IwGetResManager()->GetResNamed(id,type,IW_RES_PERMIT_NULL_F);
}
