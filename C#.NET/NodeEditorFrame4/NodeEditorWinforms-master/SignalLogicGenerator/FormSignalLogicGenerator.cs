using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using BR.AN.PviServices;


namespace SignalLogicGenerator
{
    public partial class FormSignalLogicGenerator : Form
    {
        LogicalContext context = new LogicalContext();
        TreeNode SelectedNode = new TreeNode();
        String SelectedFile;
        private bool TransferEnable;
        private Service myService;
        private Cpu cpu;

        private static int _MAX_N_NODES = 25;

        public BR.AN.PviServices.Task GateTask { get; private set; }
        private Variable DynamicGatePar;
        private Variable DownloadRecipeBool;

        private Variable GatePar_1;
        private Variable GatePar_2;
        private Variable GatePar_3;
        private Variable GatePar_4;
        private Variable GatePar_5;

        public FormSignalLogicGenerator()
        {
            InitializeComponent();
        }

        private void FormSignalLogicGenerator_Load(object sender, EventArgs e)
        {
            //Context assignment
            controlNodeEditor.nodesControl.Context = context;
            controlNodeEditor.nodesControl.OnNodeContextSelected += NodesControlOnOnNodeContextSelected;
            controlNodeEditor.Enabled = false;

            //PVI
            myService = new Service("Service");
            myService.Connected += MyService_Connected;
            myService.Connect();

        }

        /*********PVI**************/
        private void MyService_Connected(object sender, PviEventArgs e)
        {
            if(cpu == null)
            {
                cpu = new Cpu(myService, "Cpu");
                cpu.Connection.DeviceType = DeviceType.TcpIp;
                cpu.Connection.TcpIp.DestinationIpAddress = "127.0.0.1";
                cpu.Connection.TcpIp.SourceStation = Convert.ToByte(16);
                cpu.Connection.TcpIp.DestinationPort = 11160;
                cpu.Connection.TcpIp.DestinationStation = Convert.ToByte(1);
                cpu.Error += Cpu_Error;
                cpu.Connected += Cpu_Connected;
                cpu.Connect();
                GateTask = new BR.AN.PviServices.Task(cpu, "DynamicGat");
                GateTask.Connected += GateTask_Connected;
                GateTask.Connect();
            }
        }

        private void GateTask_Connected(object sender, PviEventArgs e)
        {
            //DynamicGate_1_Par
            this.DynamicGatePar = new Variable(this.GateTask, "DynamicGate_1_Par");
            this.DynamicGatePar.Connected += DynamicGatePar_Connected;
            this.DynamicGatePar.ReadOnly = false;
            this.DynamicGatePar.RefreshTime = 500;
            this.DynamicGatePar.WriteValueAutomatic = false;
            this.DynamicGatePar.Connect();

            this.DownloadRecipeBool = new Variable(this.GateTask, "DownloadGateRecipe");
            this.DownloadRecipeBool.Connect();

            this.GatePar_1 = new Variable(this.GateTask, "LogicGate_Data_1");
            this.GatePar_2 = new Variable(this.GateTask, "LogicGate_Data_2");
            this.GatePar_3 = new Variable(this.GateTask, "LogicGate_Data_3");
            this.GatePar_4 = new Variable(this.GateTask, "LogicGate_Data_4");
            this.GatePar_5 = new Variable(this.GateTask, "LogicGate_Data_5");

            this.GatePar_1.Connect();
            this.GatePar_2.Connect();
            this.GatePar_3.Connect();
            this.GatePar_4.Connect();
            this.GatePar_5.Connect();

        }

        private void DynamicGatePar_Connected(object sender, PviEventArgs e)
        {
            this.TransferEnable = true;
        }

        private void WriteParams(int [,] Matrix, int Max_X)
        {
            int[] tmp = new int[Max_X];
            
            for(int i = 0; i < Max_X; i++)
            {
                /*
                this.DynamicGatePar.StructureMembers["Format_NodeTyp"].Value[i] = (Value)Matrix[i, 0];
                this.DynamicGatePar.StructureMembers["Format_I_1_typ"].Value[i] = (Value)Matrix[i, 1];
                this.DynamicGatePar.StructureMembers["Format_I_1_ref"].Value[i] = (Value)Matrix[i, 2];
                this.DynamicGatePar.StructureMembers["Format_I_2_typ"].Value[i] = (Value)Matrix[i, 3];
                this.DynamicGatePar.StructureMembers["Format_I_2_ref"].Value[i] = (Value)Matrix[i, 4];
                */
                GatePar_1.Value[i] = Matrix[i, 0];
                GatePar_1.WriteValue();

                GatePar_2.Value[i] = Matrix[i, 1];
                GatePar_2.WriteValue();

                GatePar_3.Value[i] = Matrix[i, 2];
                GatePar_3.WriteValue();

                GatePar_4.Value[i] = Matrix[i, 3];
                GatePar_4.WriteValue();

                GatePar_5.Value[i] = Matrix[i, 4];
                GatePar_5.WriteValue();
            }

            int report = this.DynamicGatePar.WriteValue();

            DownloadRecipeBool.Value = 1;
            report = DownloadRecipeBool.WriteValue();
        }

        private void Cpu_Error(object sender, PviEventArgs e)
        {
            MessageBox.Show(cpu.ErrorText);
            //this.Close();
            //Environment.Exit(0);
        }

        private void Cpu_Connected(object sender, PviEventArgs e)
        {
            //CPU_Connected
            MessageBox.Show("CPU Connected");
        }

        /*********END_PVI*********************/

        private void NodesControlOnOnNodeContextSelected(object o)
        {
            controlNodeEditor.propertyGrid.SelectedObject = o;
        }

        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {

        }

        private void SaveButton_Click(object sender, EventArgs e)
        {
            if (SelectedNode.Text != "")
            {
                File.WriteAllBytes(SelectedNode.ToolTipText, controlNodeEditor.nodesControl.Serialize());
            }
        }

        private void treeView1_NodeMouseDoubleClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            if (e.Node.Nodes.Count > 0)
            {
                return;
            }

            foreach (TreeNode p in treeView1.Nodes)
            {
                foreach (TreeNode c in p.Nodes)
                {
                    c.BackColor = Color.Transparent;
                }
            }
            e.Node.BackColor = Color.Green;
            //Apro direttamente il file
            controlNodeEditor.nodesControl.Deserialize(File.ReadAllBytes(e.Node.ToolTipText));
            controlNodeEditor.Enabled = true;
            //Seleziono nodo
            this.SelectedNode = e.Node;
        }

        private void treeView1_BeforeSelect(object sender, TreeViewCancelEventArgs e)
        {
            e.Cancel = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (SelectedFile != null)
                controlNodeEditor.nodesControl.Deserialize(File.ReadAllBytes(SelectedFile));
            else
                controlNodeEditor.nodesControl.Deserialize(File.ReadAllBytes("default.nds"));
        }

        private void splitContainer1_Panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void splitContainer3_Panel2_Paint(object sender, PaintEventArgs e)
        {

        }

        //Load project
        private void openProjectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using (var fbd = new FolderBrowserDialog())
            {
                DialogResult result = fbd.ShowDialog();

                if (result == DialogResult.OK && !string.IsNullOrWhiteSpace(fbd.SelectedPath))
                {
                    String path = fbd.SelectedPath.Substring(fbd.SelectedPath.LastIndexOf("\\") + 1);

                    foreach (TreeNode node in treeView1.Nodes)
                    {
                        if (node.Text == path)
                            return;
                    }

                    TreeNode tmp = new TreeNode();
                    TreeNode subTmp = new TreeNode();
                    tmp.Text = path;
                    tmp.Tag = "Prj";
                    tmp.ToolTipText = fbd.SelectedPath;
                    //treeView1.Nodes.Add(tmp);


                    string[] files = Directory.GetFiles(fbd.SelectedPath);

                    foreach (string file in files)
                    {
                        if (file.Contains(".nds"))
                        {
                            subTmp = new TreeNode();
                            subTmp.Text = file.Substring(file.LastIndexOf("\\") + 1);
                            subTmp.ToolTipText = file;
                            tmp.Nodes.Add(subTmp);
                        }
                    }
                    if (tmp.Nodes.Count != 0)
                    {
                        treeView1.Nodes.Add(tmp);
                        treeView1.EndUpdate();
                    }
                }
            }
        }

        private void treeView1_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            if (e.Button == MouseButtons.Right && e.Node.Tag != null)
            {
                if(e.Node.Tag.ToString() == "Prj")
                {
                    var context = new ContextMenuStrip();
                    context.Items.Add("Add Signal", null, ((o, args) =>
                    {
                        //Aggiungere creazione segnale   
                    }));

                    context.Items.Add(new ToolStripSeparator());

                    context.Items.Add("Info", null, ((o, args) =>
                    {
                        //AggiungereMetodo
                    }));
                    context.Show(MousePosition);
                }
            }
        }

        
        //SaveButtonFromStrip
        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (SelectedNode.Text != "")
            {
                File.WriteAllBytes(SelectedNode.ToolTipText, controlNodeEditor.nodesControl.Serialize());
            }
        }

        private void Parse_Click(object sender, EventArgs e)
        {
            int[,] Matrix = Parser.Parse(controlNodeEditor.nodesControl.ExportToDictionary());
            Parser.PrintMatrixFile(Matrix);
            if (TransferEnable)
            {
                DialogResult dialogResult = MessageBox.Show("Transfer to PLC?", "Send", MessageBoxButtons.YesNo);
                if (dialogResult == DialogResult.Yes)
                    WriteParams(Matrix, _MAX_N_NODES);
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
