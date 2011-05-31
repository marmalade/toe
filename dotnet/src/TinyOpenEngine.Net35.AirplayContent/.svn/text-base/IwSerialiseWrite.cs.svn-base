using System.IO;
using System.Text;

namespace TinyOpenEngine.AirplayContent
{
	public class IwSerialiseWrite : IwSerialise
	{
		public override Stream BaseStream { get { return writer.BaseStream; } }
		BinaryWriter writer;
		public IwSerialiseWrite(BinaryWriter writer)
		{
			this.writer = writer;
		}
		public override bool IwIsSerialiseOpen ()
		{
			return writer != null;
		}
		public override void  IwSerialiseBool (ref bool val)
		{
			writer.Write(val?(int)1:(int)0);
		}
		public override void  IwSerialiseBool8Bits (ref bool val)
		{
			writer.Write(val?(byte)1:(byte)0);
		}
		public override void IwSerialiseClose()
		{
			writer.Close();
			writer = null;
		}
		public override bool IwSerialiseEOF()
		{
			return false;
		}
		public override void IwSerialiseString(ref string name)
		{
			if (name != null)
				writer.Write(Encoding.UTF8.GetBytes(name));
			writer.Write((byte)0);
		}

		public override bool IwSerialiseIsReading()
		{
			return false;
		}
		public override bool IwSerialiseIsWriting()
		{
			return true;
		}
		public override void IwSerialiseInt8(ref sbyte val)
		{
			writer.Write(val);
		}
		public override void IwSerialiseInt16(ref short val)
		{
			writer.Write(val);
		}
		public override void IwSerialiseInt32(ref int val)
		{
			writer.Write(val);
		}
		public override void IwSerialiseInt64(ref long val)
		{
			writer.Write(val);
		}

		public override void IwSerialiseUInt8(ref byte val)
		{
			writer.Write(val);
		}
		public override void IwSerialiseUInt16(ref ushort val)
		{
			writer.Write(val);
		}
		public override void IwSerialiseUInt32(ref uint val)
		{
			writer.Write(val);
		}
		public override void IwSerialiseUInt64(ref ulong val)
		{
			writer.Write(val);
		}
	}
}
