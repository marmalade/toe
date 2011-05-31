using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content.Pipeline;
using Microsoft.Xna.Framework.Content.Pipeline.Graphics;
using TinyOpenEngine.AirplayContent;
using System.IO;

namespace TinyOpenEngine.Xna.AirplayContent
{
	/// <summary>
	/// This class will be instantiated by the XNA Framework Content Pipeline
	/// to import a file from disk into the specified type, TImport.
	/// 
	/// This should be part of a Content Pipeline Extension Library project.
	/// 
	/// TODO: change the ContentImporter attribute to specify the correct file
	/// extension, display name, and default processor for this importer.
	/// </summary>
	[ContentImporter(".bin", DisplayName = "Airplay SDK IwResGroup binary importer", DefaultProcessor = "ResGroupProcessor")]
	public class ResGroupBinImporter : ContentImporter<CIwResGroup>
	{
		public override CIwResGroup Import(string filename, ContentImporterContext context)
		{
			var res = new CIwResGroup();
			res.Serialise(new IwSerialiseRead(new BinaryReader(File.OpenRead(filename))));
			return res;
		}
	}
}
