using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

namespace TinyOpenEngine.AirplayContent
{
	public class CIwResGroup
	{
		uint Magic0606033D;
		ushort Magic0000;
		public void Serialise(IwSerialise iwSerialise)
		{
			iwSerialise.IwSerialiseUInt32(ref Magic0606033D);
			iwSerialise.IwSerialiseUInt16(ref Magic0000);
			if (iwSerialise.IwSerialiseIsReading())
			{
				if (Magic0606033D != 0x0606033D) throw new ArgumentException("invalid magic");
				if (Magic0000 != 0x0000) throw new ArgumentException("invalid magic");

				for (; ; )
				{
					uint blockHash=0;
					iwSerialise.IwSerialiseUInt32(ref blockHash);
					if (blockHash == 0)
						break;
					uint blockLen=0;
					iwSerialise.IwSerialiseUInt32(ref blockLen);

					switch (blockHash)
					{
						case 0x8081e087:
							ReadResGroupParams(iwSerialise, blockLen);
							break;
						case 0x3B495DC0:
							iwSerialise.BaseStream.Position += blockLen-4;
							break;
						case 0xdc3c2177:
							iwSerialise.BaseStream.Position += blockLen-4;
							break;
						default:
							throw new ArgumentException("unknown block " + blockHash + " (" + blockLen + " bytes)");
					}
				}
			}
			else
			{
			}
			/*
			//binary header
			// 	_IwGxBinaryBlockSerialise()
			{
				uint hash = 0x8081e087;
				uint len = 0x12; //вернулись-записали? //4
				string name = "name12"; //+zero 10
				uint shared = 1; //4
			}
			{ // вложенная группа
				uint flags2 = 0x3B495DC0;
				uint len ; //вернулись-записали? //4
				byte someByte = 1; //количество групп
				{
				string name = ".//путь"; //+zero 10
				uint data = 0;
				int data2 = 0x00001000;
				uint32 groupnamehash;
				}
			}
			{ // хвост c объектами
				uint flags2 = 0xdc3c2177;
				uint len = 0x8; //вернулись-записали? //4
				uint data; // количество объектов
				{
					uint32 hash;// объекта //0x60d24878
					uint32 num; // количество объектов этого типа
					byte one1=1;
					byte one2=1;
					{
					uint32 длина managed
					uint32 хеш имени объекта;
					//объект
					}
				}

				{ // например текстуры
					hash = 0x3521F539;
					4 текстуры
					1
					1
					длина
					хеш имени
					uint32 texture flags = 0C/14 43 20 00 
					00 
					00 
					IwSVec2 UVScale (int16,int16)
					int16 v
					byte CIwImage::Format 
					int16 image flags = 0x1000
					uint16 width
					uint16 height
					uint16 pitch
					uint32 00 00 00 00 //?compressed image size?

					RGB RGB RGB RGB ... 0 до pitch
					илил
					RGBA RGBA RGBA RGBA ... 0 до pitch
					bool 0

				}
			}
			uint end = 0;
			 */
		}
		string name;
		uint shared=0;
		private void ReadResGroupParams(IwSerialise iwSerialise, uint blockLen)
		{
			iwSerialise.IwSerialiseString(ref name);
			iwSerialise.IwSerialiseUInt32(ref shared);
		}
	}
}
