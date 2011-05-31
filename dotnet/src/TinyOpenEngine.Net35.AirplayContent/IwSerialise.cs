
using System.IO;
namespace TinyOpenEngine.AirplayContent
{
	public abstract class IwSerialise
	{
		public abstract Stream BaseStream {get;}
		public abstract bool IwIsSerialiseOpen();
		public abstract void IwSerialiseBool(ref bool var);
		public abstract void IwSerialiseBool8Bits(ref bool var);
		public abstract void IwSerialiseClose();

		public abstract bool  IwSerialiseEOF ();
		public bool IwSerialiseExists(string filename)
		{
			return File.Exists(filename);
		}
		public ushort IwSerialiseGetUserVersion()
		{
			return 1;
		}
		public abstract bool  IwSerialiseIsReading ();
		public abstract bool  IwSerialiseIsWriting ();

		public abstract void IwSerialiseInt8(ref sbyte val);
		public abstract void IwSerialiseInt16(ref short val);
		public abstract void IwSerialiseInt32(ref int val);
		public abstract void IwSerialiseInt64(ref long val);

		public abstract void IwSerialiseUInt8(ref byte val);
		public abstract void IwSerialiseUInt16(ref ushort val);
		public abstract void IwSerialiseUInt32(ref uint val);
		public abstract void IwSerialiseUInt64(ref ulong val);
		/*
	void  IwSerialiseChar (char &var, int n=1, int numBits=sizeof(int8)*8-1, int stride=sizeof(char)) 
	void  IwSerialiseCharBitDepthRequired (char &var, int n=1, int stride=sizeof(char)) 
	void  IwSerialiseDouble (double &var, int n=1, int numBits=sizeof(double)*8, int stride=sizeof(double)) 
	void  IwSerialiseEnum (void *pVar) 
	void  IwSerialiseFloat (float &var, int n=1, int numBits=sizeof(float)*8, int stride=sizeof(float)) 
	void  IwSerialiseInt16 (int16 &var, int n=1, int numBits=sizeof(int16)*8-1, int stride=sizeof(int16)) 
	void  IwSerialiseInt16BitDepthRequired (int16 &var, int n=1, int stride=sizeof(int16)) 
	void  IwSerialiseInt32 (int32 &var, int n=1, int numBits=sizeof(int32)*8-1, int stride=sizeof(int32)) 
	void  IwSerialiseInt32BitDepthRequired (int32 &var, int n=1, int stride=sizeof(int32)) 
	void  IwSerialiseInt64 (int64 &var, int n=1, int numBits=sizeof(int64)*8-1, int stride=sizeof(int64)) 
	void  IwSerialiseInt8 (int8 &var, int n=1, int numBits=sizeof(int8)*8-1, int stride=sizeof(int8)) 
	void  IwSerialiseInt8BitDepthRequired (int8 &var, int n=1, int stride=sizeof(int8)) 
	void  IwSerialiseManagedHash (void *pptr) 
	void  IwSerialiseManagedObject (CIwManaged *&pObj) 
	void  IwSerialiseMappedData (const uint16 *pMap, void *_pData, int numStructs, int stride) 
	void  IwSerialiseSetUserVersion (uint16 v) 
	void  IwSerialiseString (char *text, int maxLen=0) 
	void  IwSerialiseUInt16 (uint16 &var, int n=1, int numBits=sizeof(uint16)*8, int stride=sizeof(uint16)) 
	void  IwSerialiseUInt16BitDepthRequired (uint16 &var, int n=1, int stride=sizeof(uint16)) 
	void  IwSerialiseUInt32 (uint32 &var, int n=1, int numBits=sizeof(uint32)*8, int stride=sizeof(uint32)) 
	void  IwSerialiseUInt32BitDepthRequired (uint32 &var, int n=1, int stride=sizeof(uint32)) 
	void  IwSerialiseUInt64 (uint64 &var, int n=1, int numBits=sizeof(uint64)*8, int stride=sizeof(uint64)) 
	void  IwSerialiseUInt8 (uint8 &var, int n=1, int numBits=sizeof(uint8)*8, int stride=sizeof(uint8)) 
	void  IwSerialiseUInt8BitDepthRequired (uint8 &var, int n=1, int stride=sizeof(uint8)) 

	void  IwSerialiseFile (CIwTextParserITX *pParser, char const *filename, void *pptr, bool read) 
	void  IwSerialiseFile (CIwTextParserITX *pParser, char const *filename, void *pptr, IwSerialiseMode mode) 
	void  IwSerialiseOpen (const char *filename, bool read, bool ram=false) 
	void  IwSerialiseOpen (const char *filename, IwSerialiseMode mode, bool ram=false) 
	void  IwSerialiseOpenFromMemory (void *pBuffer, int size, bool read) 
	void  IwSerialiseOpenFromMemory (void *pBuffer, int size, IwSerialiseMode mode) 
	void  IwSerialiseResetCallbackCount () 
	void  IwSerialiseSetCallback (IwSerialiseUserCallback cb) 
	void  IwSerialiseSetCallbackPeriod (uint32 p) 
*/

		public abstract void IwSerialiseString(ref string name);
	}
}
