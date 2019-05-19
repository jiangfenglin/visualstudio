using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF_Pinger
{
    public class RowItem
    {
        public string Name { get; set; }
        public string IpAddress { get; set; }
        public string InfoTime { get; set; }
        public bool Ping { get; set; }
    }
}
