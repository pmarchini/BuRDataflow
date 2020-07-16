using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace SampleCommon
{
    public partial class ControlNodeEditor : UserControl
    {
        public ControlNodeEditor()
        {
            InitializeComponent();
        }

        private void buttonProcess_Click(object sender, EventArgs e)
        {
            nodesControl.Execute();            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            File.WriteAllText("export.xml", nodesControl.ExportToXml());
            MessageBox.Show("Export complete", "Info", MessageBoxButtons.OK);
        }
    }
}
