using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using EXControls;
using System.Threading;

namespace EXListViewDemo
{
    public partial class MyForm : Form
    {
        private delegate void del_do_update(ProgressBar pb);
        private delegate void del_do_changetxt(LinkLabel l, string text);

        public MyForm()
        {
            InitializeComponent();
        }

        private void llbl_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            LinkLabel l = (LinkLabel)sender;
            if (l.Text == "Downloading") return;
            EXControlListViewSubItem subitem = l.Tag as EXControlListViewSubItem;
            ProgressBar p = subitem.MyControl as ProgressBar;
            Thread th = new Thread(new ParameterizedThreadStart(UpdateProgressBarMethod));
            th.IsBackground = true;
            th.Start(p);
            ((LinkLabel)sender).Text = "Downloading";
        }

        private void lstv_MouseMove(object sender, MouseEventArgs e)
        {
            ListViewHitTestInfo lstvinfo = lstv.HitTest(e.X, e.Y);
            ListViewItem.ListViewSubItem subitem = lstvinfo.SubItem;
            if (subitem == null) return;
            if (subitem is EXListViewSubItemAB)
            {
                toolstripstatuslabel1.Text = ((EXListViewSubItemAB)subitem).MyValue;
            }
        }

        private void ChangeTextMethod(LinkLabel l, string text)
        {
            l.Text = text;
        }

        private void UpdateProgressBarMethod(object pb)
        {
            ProgressBar pp = (ProgressBar)pb;
            if (pp.Value == pp.Maximum) pp.Value = 0;
            del_do_update delupdate = new del_do_update(do_update);
            for (int i = pp.Value; i < pp.Maximum; i++)
            {
                pp.BeginInvoke(delupdate, new object[] { pp });
                Thread.Sleep(10);
            }
            ListViewItem item = (ListViewItem)pp.Tag;
            LinkLabel l = ((LinkLabel)((EXControlListViewSubItem)item.SubItems[4]).MyControl);
            del_do_changetxt delchangetxt = new del_do_changetxt(ChangeTextMethod);
            l.BeginInvoke(delchangetxt, new object[] { l, "OK" });
        }

        private void do_update(ProgressBar p)
        {
            p.PerformStep();
        }

        private void btn_Click(object sender, EventArgs e)
        {
            lstv.RemoveControlFromSubItem((EXControlListViewSubItem)lstv.Items[1].SubItems[4]);
        }

        private void btn2_Click(object sender, EventArgs e)
        {
            ((EXMultipleImagesListViewSubItem)lstv.Items[1].SubItems[2]).MyImages.Clear();
            lstv.Invalidate(lstv.Items[1].SubItems[2].Bounds);
        }
    }
}
