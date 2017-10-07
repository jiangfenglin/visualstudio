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

namespace DllConfigDemo
{
	public class ConfigFile : MarshalByRefObject
	{
		public string ReadConfig()
		{
			Console.Write("调用DllConfigFile.ReadConfig()得到：");
			return ConfigurationManager.AppSettings["DemoData"];
		}
	}
}
