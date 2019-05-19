using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace WPF_Pinger
{
    public class Manager
    {
        /// <summary>
        /// Return a list of ipAddress
        /// </summary>
        /// <returns>List<Computer></returns>
        public static List<Computer> GetIpAddress()
        {
            var list = new List<Computer>();

            XmlDocument doc = new XmlDocument();
            doc.Load("IpAddressList.xml");

            foreach (XmlNode node in doc.DocumentElement.ChildNodes)
            {
                var name = node.FirstChild.InnerText;
                var ip = node.LastChild.InnerText;

                var c = new Computer();
                c.Name = name;
                c.Ip = ip;

                list.Add(c);
            }

            return list;
        }
    }
}
