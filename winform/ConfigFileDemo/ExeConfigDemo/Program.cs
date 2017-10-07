/* Author: Bearhand
 * Date:   2008.09.06
 * 
 * Copyright C Bearhand.cnblogs.com
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Configuration;
using DllConfigDemo;

namespace ExeConfigDemo
{
	class Program
	{
		static void Main(string[] args)
		{
			// 1、使用OpenExeConfiguration(string exePath)解决三个问题
			//Configuration config = ConfigurationManager.OpenExeConfiguration("C:\\xxx.exe.config");
			//Configuration config = ConfigurationManager.OpenExeConfiguration("C:\\xxx.exe");
			//Configuration config = ConfigurationManager.OpenExeConfiguration("C:\\xxx");
			Configuration config = ConfigurationManager.OpenExeConfiguration("C:\\xxx.dll");
			DllInfo dllInfo = config.GetSection("DllInfo") as DllInfo;
			Console.WriteLine(dllInfo);

			// 2、创建新AppDomain，让类库能够读取自己默认的配置文件xxx.dll.config
			// exe内直接使用ConfigurationManager读取的是exe.config里面的信息；
			Console.WriteLine(ConfigurationManager.AppSettings["DemoData"]);
			// 同一个AppDomain内的dll，使用ConfigurationManager读取的也仍然是exe.config里面的信息；
			ConfigFile dll1 = new ConfigFile();
			Console.WriteLine(dll1.ReadConfig());
			// 创建新AppDomain
			AppDomainSetup setup = new AppDomainSetup();
			setup.ApplicationBase = Environment.CurrentDirectory;
			setup.ConfigurationFile = "DllConfigDemo.dll.config";
			AppDomain newAppDomain = AppDomain.CreateDomain("NewAppDomain", AppDomain.CurrentDomain.Evidence, setup);
			ConfigFile dll2 = newAppDomain.CreateInstanceFromAndUnwrap(dllInfo.Name + ".dll", dllInfo.Type) as ConfigFile;
			Console.WriteLine(dll2.ReadConfig());

			Console.WriteLine("Press any key to exit...");
			Console.ReadKey();
		}
	}
}
