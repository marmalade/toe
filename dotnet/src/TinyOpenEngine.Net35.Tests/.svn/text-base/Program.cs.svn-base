using System;
using System.Collections.Generic;
using NUnit.ConsoleRunner;

namespace TinyOpenEngine.Net35.Tests
{
	class Program
	{
		static void Main(string[] args)
		{
			List<string> a = new List<string>();
			a.Add(typeof(Program).Assembly.Location);
			a.AddRange(args);
			Runner.Main(a.ToArray());

			Console.WriteLine("Press any key to continue.");
			Console.ReadKey();
		}
	}
}
