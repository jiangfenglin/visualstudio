using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.NetworkInformation;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WPF_Pinger
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            try
            {
                InitializeComponent();

                var Computers = Manager.GetIpAddress();

                if (Computers.Count > 0)
                {
                    List<RowItem> items = new List<RowItem>();

                    Parallel.ForEach(Computers, (cabinet) =>
                    {
                        if (PingHost(cabinet.Ip))
                        {

                            items.Add(new RowItem() { InfoTime = DateTime.Now.ToString("HH:mm:ss"), Name = cabinet.Name, IpAddress = cabinet.Ip, Ping = true });
                        }
                        else
                        {
                            items.Add(new RowItem() { Name = cabinet.Name, IpAddress = cabinet.Ip, Ping = false });
                        }
                    });


                    icTodoList.ItemsSource = items.OrderBy(x => x.Name);
                }

                int PingTime = Pinger.Default.PingTime;
                Timer t = new Timer(PingTime); // 1 sec = 1000, 60 sec = 60000

                t.AutoReset = true;

                t.Elapsed += new System.Timers.ElapsedEventHandler(t_Elapsed);

                t.Start();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        /// <summary>
        /// Send ping to one ipAddress
        /// </summary>
        /// <param name="Address">string IP Address</param>
        /// <returns>bools</returns>
        private static bool PingHost(string Address)
        {
            bool pingable = false;
            Ping pinger = null;

            try
            {
                pinger = new Ping();
                PingReply reply = pinger.Send(Address, 1000);
                pingable = reply.Status == IPStatus.Success;
            }
            catch (PingException)
            {
                // Discard PingExceptions and return false;
            }
            finally
            {
                if (pinger != null)
                {
                    pinger.Dispose();
                }
            }

            return pingable;
        }

        /// <summary>
        /// Handler for refresh info in Mainwindow.xaml.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void t_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
  

            foreach (RowItem cabinet in icTodoList.Items)
            {
                if (PingHost(cabinet.IpAddress))
                {
                    cabinet.InfoTime = DateTime.Now.ToString("HH:mm:ss");

                    cabinet.Ping = true;
                }
                else
                {
                    cabinet.Ping = false;
                }
            }

            this.Dispatcher.Invoke((Action)(() =>
            {
                icTodoList.Items.Refresh();
            }));
        }
    }
}
