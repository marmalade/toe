using System.IO;
using System.Collections.Generic;
using System.Text;

namespace TinyOpenEngine.AirplayContent
{
	public class IwSerialiseRead : IwSerialise
	{
		public override Stream BaseStream { get { return reader.BaseStream; } }
		BinaryReader reader;
		public IwSerialiseRead(BinaryReader reader)
		{
			this.reader = reader;
		}
		public override bool IwIsSerialiseOpen()
		{
			return reader != null;
		}
		public override void IwSerialiseString(ref string name)
		{
			List<byte> buf = new List<byte>();
			for (; ; )
			{
				var b = reader.ReadByte();
				if (b <= 0) break;
				buf.Add((byte)b);
			}
			name = Encoding.UTF8.GetString(buf.ToArray());
		}
		public override void IwSerialiseBool(ref bool val)
		{
			val = 0 != reader.ReadUInt32();
		}
		public override void IwSerialiseBool8Bits(ref bool val)
		{
			val = 0 != reader.ReadByte();
		}
		public override void IwSerialiseClose()
		{
			reader.Close();
			reader = null;
		}
		public override bool  IwSerialiseEOF ()
		{
			return !reader.BaseStream.CanRead;
		}
	
		public override bool  IwSerialiseIsReading ()
		{
			return true;
		}
		public override bool  IwSerialiseIsWriting ()
		{
			return false;
		}
		public override void IwSerialiseInt8(ref sbyte val)
		{
			val = reader.ReadSByte();
		}
		public override void IwSerialiseInt16(ref short val)
		{
			val = reader.ReadInt16();
		}
		public override void IwSerialiseInt32(ref int val)
		{
			val = reader.ReadInt32();
		}
		public override void IwSerialiseInt64(ref long val)
		{
			val = reader.ReadInt64();
		}

		public override void IwSerialiseUInt8(ref byte val)
		{
			val = reader.ReadByte();
		}
		public override void IwSerialiseUInt16(ref ushort val)
		{
			val = reader.ReadUInt16();
		}
		public override void IwSerialiseUInt32(ref uint val)
		{
			val = reader.ReadUInt32();
		}
		public override void IwSerialiseUInt64(ref ulong val)
		{
			val = reader.ReadUInt64();
		}

	}
}
