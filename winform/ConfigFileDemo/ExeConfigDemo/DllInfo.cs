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

namespace ExeConfigDemo
{
	public class DllInfo : ConfigurationSection
	{
		[ConfigurationProperty("name")]
		public string Name
		{
			get
			{
				return (string)this["name"];
			}
			set
			{
				this["name"] = value;
			}
		}

		[ConfigurationProperty("type")]
		public string Type
		{
			get
			{
				return (string)this["type"];
			}
			set
			{
				this["type"] = value;
			}
		}

		public override string ToString()
		{
			return string.Format("Name = {0}, Type = {1}", Name, Type);
		}
	}
}
