using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content.Pipeline;
using Microsoft.Xna.Framework.Content.Pipeline.Graphics;
using Microsoft.Xna.Framework.Content.Pipeline.Processors;
using Microsoft.Xna.Framework.Content.Pipeline.Serialization.Compiler;
using TinyOpenEngine.AirplayContent;

namespace TinyOpenEngine.Xna.AirplayContent
{
	/// <summary>
	/// This class will be instantiated by the XNA Framework Content Pipeline
	/// to write the specified data type into binary .xnb format.
	///
	/// This should be part of a Content Pipeline Extension Library project.
	/// </summary>
	[ContentTypeWriter]
	public class ResGroupBinWriter : ContentTypeWriter<CIwResGroup>
	{
		protected override void Write(ContentWriter output, CIwResGroup value)
		{
			value.Serialise(new IwSerialiseWrite(output));
		}

		public override string GetRuntimeReader(TargetPlatform targetPlatform)
		{
			// TODO: change this to the name of your ContentTypeReader
			// class which will be used to load this data.
			return "MyNamespace.MyContentReader, MyGameAssembly";
		}
	}
}
