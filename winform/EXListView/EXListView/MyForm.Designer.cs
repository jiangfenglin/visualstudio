namespace EXListViewDemo
{
    using System.Windows.Forms;
    using EXControls;
    using System.Drawing;
    using System.Collections;
    using System;

    partial class MyForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        private EXListView lstv;
        private Button btn;
        private Button btn2;
        private StatusStrip statusstrip1;
        private ToolStripStatusLabel toolstripstatuslabel1;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Text = "Form1";

            //imglst_genre
            ImageList imglst_genre = new ImageList();
            imglst_genre.ColorDepth = ColorDepth.Depth32Bit;
            imglst_genre.Images.Add(Image.FromFile("music.png"));
            imglst_genre.Images.Add(Image.FromFile("love.png"));
            imglst_genre.Images.Add(Image.FromFile("comedy.png"));
            imglst_genre.Images.Add(Image.FromFile("drama.png"));
            imglst_genre.Images.Add(Image.FromFile("horror.ico"));
            imglst_genre.Images.Add(Image.FromFile("family.ico"));
            //excmbx_genre
            EXComboBox excmbx_genre = new EXComboBox();
            excmbx_genre.DropDownStyle = ComboBoxStyle.DropDownList;
            excmbx_genre.MyHighlightBrush = Brushes.Goldenrod;
            excmbx_genre.ItemHeight = 20;
            excmbx_genre.Items.Add(new EXComboBox.EXImageItem(imglst_genre.Images[0], "Music"));
            excmbx_genre.Items.Add(new EXComboBox.EXImageItem(imglst_genre.Images[1], "Romantic"));
            excmbx_genre.Items.Add(new EXComboBox.EXImageItem(imglst_genre.Images[2], "Comedy"));
            excmbx_genre.Items.Add(new EXComboBox.EXImageItem(imglst_genre.Images[3], "Drama"));
            excmbx_genre.Items.Add(new EXComboBox.EXImageItem(imglst_genre.Images[4], "Horror"));
            excmbx_genre.Items.Add(new EXComboBox.EXImageItem(imglst_genre.Images[5], "Family"));
            excmbx_genre.Items.Add(new EXComboBox.EXMultipleImagesItem(new ArrayList(new object[] { Image.FromFile("love.png"), Image.FromFile("comedy.png") }), "Romantic comedy"));
            //excmbx_rate
            EXComboBox excmbx_rate = new EXComboBox();
            excmbx_rate.MyHighlightBrush = Brushes.Goldenrod;
            excmbx_rate.DropDownStyle = ComboBoxStyle.DropDownList;
            ImageList imglst_rate = new ImageList();
            imglst_rate.ColorDepth = ColorDepth.Depth32Bit;
            imglst_rate.Images.Add(Image.FromFile("rate.png"));
            //for (int i = 1; i < 6; i++)
            //{
            //    ArrayList _arlst1 = new ArrayList();
            //    for (int j = 0; j < i; j++)
            //    {
            //        _arlst1.Add(imglst_rate.Images[0]);
            //    }
            //    excmbx_rate.Items.Add(new EXComboBox.EXMultipleImagesItem("", _arlst1, i.ToString()));
            //}
            //lstv
            lstv = new EXListView();
            lstv.MySortBrush = SystemBrushes.ControlLight;
            lstv.MyHighlightBrush = Brushes.Goldenrod;
            lstv.GridLines = true;
            lstv.Location = new Point(10, 40);
            lstv.Size = new Size(500, 400);
            lstv.ControlPadding = 4;
            lstv.MouseMove += new MouseEventHandler(lstv_MouseMove);
            lstv.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) | System.Windows.Forms.AnchorStyles.Left) | System.Windows.Forms.AnchorStyles.Right)));
            //add SmallImageList to ListView - images will be shown in ColumnHeaders
            ImageList colimglst = new ImageList();
            colimglst.Images.Add("down", Image.FromFile("down.png"));
            colimglst.Images.Add("up", Image.FromFile("up.png"));
            colimglst.ColorDepth = ColorDepth.Depth32Bit;
            colimglst.ImageSize = new Size(20, 20); // this will affect the row height
            lstv.SmallImageList = colimglst;
            //add columns and items
            lstv.Columns.Add(new EXEditableColumnHeader("Movie", 20));
            lstv.Columns.Add(new EXColumnHeader("Progress", 120));
            lstv.Columns.Add(new EXEditableColumnHeader("Genre", excmbx_genre, 60));
            lstv.Columns.Add(new EXEditableColumnHeader("Rate", excmbx_rate, 100));
            lstv.Columns.Add(new EXColumnHeader("Status", 80));
            EXBoolColumnHeader boolcol = new EXBoolColumnHeader("Conclusion", 80);
            boolcol.Editable = true;
            boolcol.TrueImage = Image.FromFile("true.png");
            boolcol.FalseImage = Image.FromFile("false.png");
            lstv.Columns.Add(boolcol);
            lstv.BeginUpdate();
            for (int i = 0; i < 100; i++)
            {
                //movie
                EXListViewItem item = new EXListViewItem(i.ToString());
                EXControlListViewSubItem cs = new EXControlListViewSubItem();
                ProgressBar b = new ProgressBar();
                b.Tag = item;
                b.Minimum = 0;
                b.Maximum = 1000;
                b.Step = 1;
                item.SubItems.Add(cs);
                lstv.AddControlToSubItem(b, cs);
                //genre
                item.SubItems.Add(new EXMultipleImagesListViewSubItem(new ArrayList(new object[] { imglst_genre.Images[1], imglst_genre.Images[2] }), "Romantic comedy"));
                //rate
                item.SubItems.Add(new EXMultipleImagesListViewSubItem(new ArrayList(new object[] { imglst_rate.Images[0] }), "1"));
                //cancel and resume
                EXControlListViewSubItem cs1 = new EXControlListViewSubItem();
                LinkLabel llbl = new LinkLabel();
                llbl.Text = "Start";
                llbl.Tag = cs;
                llbl.LinkClicked += new LinkLabelLinkClickedEventHandler(llbl_LinkClicked);
                item.SubItems.Add(cs1);
                lstv.AddControlToSubItem(llbl, cs1);
                //conclusion
                item.SubItems.Add(new EXBoolListViewSubItem(true));
                lstv.Items.Add(item);
            }
            lstv.EndUpdate();
            //statusstrip1
            statusstrip1.Items.AddRange(new ToolStripItem[] { toolstripstatuslabel1 });
            //btn
            btn.Location = new Point(10, 450);
            btn.Text = "Remove Control";
            btn.AutoSize = true;
            btn.Click += new EventHandler(btn_Click);
            //btn2
            btn2.Location = new Point(btn.Right + 20, 450);
            btn2.Text = "Remove Image";
            btn2.AutoSize = true;
            btn2.Click += new EventHandler(btn2_Click);
            //this
            this.ClientSize = new Size(520, 510);
            this.Controls.Add(statusstrip1);
            Label lbl = new Label();
            lbl.Text = "Doubleclick on the subitems to edit...";
            lbl.Bounds = new Rectangle(10, 10, 480, 20);
            this.Controls.Add(lbl);
            this.Controls.Add(lstv);
            this.Controls.Add(btn);
            this.Controls.Add(btn2);
        }

        #endregion
    }
}

