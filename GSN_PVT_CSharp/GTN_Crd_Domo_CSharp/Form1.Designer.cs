namespace GTN_Crd_Domo_CSharp
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.textBox_PrfPos2 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.textBox_PrfPos1 = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.button_zeroPos = new System.Windows.Forms.Button();
            this.label11 = new System.Windows.Forms.Label();
            this.button_axisOnOff = new System.Windows.Forms.Button();
            this.BUTTON_INITIAL = new System.Windows.Forms.Button();
            this.COMBOBOX_CORENUM = new System.Windows.Forms.ComboBox();
            this.label10 = new System.Windows.Forms.Label();
            this.BUTTON_HOME = new System.Windows.Forms.Button();
            this.BUTTON_CLOSE = new System.Windows.Forms.Button();
            this.BUTTON_NJOG = new System.Windows.Forms.Button();
            this.BUTTON_PJOG = new System.Windows.Forms.Button();
            this.COMBOBOX_AXISNUM = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.BUTTON_PTP = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.COMBOBOX_DATACOUNT = new System.Windows.Forms.ComboBox();
            this.label28 = new System.Windows.Forms.Label();
            this.dataGridView = new System.Windows.Forms.DataGridView();
            this.button_CLEAR = new System.Windows.Forms.Button();
            this.button_DELECT = new System.Windows.Forms.Button();
            this.button_ADD = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.COMBOBOX_LOOPCOUNT = new System.Windows.Forms.ComboBox();
            this.label8 = new System.Windows.Forms.Label();
            this.button_updata = new System.Windows.Forms.Button();
            this.button_PVTStart = new System.Windows.Forms.Button();
            this.COMBOBOX_MODE = new System.Windows.Forms.ComboBox();
            this.label9 = new System.Windows.Forms.Label();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.textBox_ptpSmTime = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.textBox_ptpPos = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.textBox_ptpAcc = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.textBox_ptpVel = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.Column_Time = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column_Pos = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column_Vel = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column_Acc = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column_Percent = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.groupBox2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).BeginInit();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.textBox_PrfPos2);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.textBox_PrfPos1);
            this.groupBox2.Location = new System.Drawing.Point(13, 422);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox2.Size = new System.Drawing.Size(205, 101);
            this.groupBox2.TabIndex = 3;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "运动状态";
            // 
            // textBox_PrfPos2
            // 
            this.textBox_PrfPos2.Location = new System.Drawing.Point(109, 69);
            this.textBox_PrfPos2.Margin = new System.Windows.Forms.Padding(4);
            this.textBox_PrfPos2.Name = "textBox_PrfPos2";
            this.textBox_PrfPos2.ReadOnly = true;
            this.textBox_PrfPos2.Size = new System.Drawing.Size(87, 25);
            this.textBox_PrfPos2.TabIndex = 5;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 73);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(82, 15);
            this.label2.TabIndex = 2;
            this.label2.Text = "轴实际位置";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 28);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(82, 15);
            this.label1.TabIndex = 1;
            this.label1.Text = "轴规划位置";
            // 
            // textBox_PrfPos1
            // 
            this.textBox_PrfPos1.Location = new System.Drawing.Point(109, 25);
            this.textBox_PrfPos1.Margin = new System.Windows.Forms.Padding(4);
            this.textBox_PrfPos1.Name = "textBox_PrfPos1";
            this.textBox_PrfPos1.ReadOnly = true;
            this.textBox_PrfPos1.Size = new System.Drawing.Size(87, 25);
            this.textBox_PrfPos1.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.button_zeroPos);
            this.groupBox1.Controls.Add(this.label11);
            this.groupBox1.Controls.Add(this.button_axisOnOff);
            this.groupBox1.Controls.Add(this.BUTTON_INITIAL);
            this.groupBox1.Controls.Add(this.COMBOBOX_CORENUM);
            this.groupBox1.Controls.Add(this.label10);
            this.groupBox1.Controls.Add(this.BUTTON_HOME);
            this.groupBox1.Controls.Add(this.BUTTON_CLOSE);
            this.groupBox1.Controls.Add(this.BUTTON_NJOG);
            this.groupBox1.Controls.Add(this.BUTTON_PJOG);
            this.groupBox1.Controls.Add(this.COMBOBOX_AXISNUM);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Location = new System.Drawing.Point(13, 9);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox1.Size = new System.Drawing.Size(205, 405);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            // 
            // button_zeroPos
            // 
            this.button_zeroPos.Location = new System.Drawing.Point(27, 163);
            this.button_zeroPos.Margin = new System.Windows.Forms.Padding(4);
            this.button_zeroPos.Name = "button_zeroPos";
            this.button_zeroPos.Size = new System.Drawing.Size(148, 40);
            this.button_zeroPos.TabIndex = 9;
            this.button_zeroPos.Text = "清除位置";
            this.button_zeroPos.UseVisualStyleBackColor = true;
            this.button_zeroPos.Click += new System.EventHandler(this.button_zeroPos_Click);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(11, 90);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(52, 15);
            this.label11.TabIndex = 8;
            this.label11.Text = "核号：";
            // 
            // button_axisOnOff
            // 
            this.button_axisOnOff.Location = new System.Drawing.Point(104, 22);
            this.button_axisOnOff.Margin = new System.Windows.Forms.Padding(4);
            this.button_axisOnOff.Name = "button_axisOnOff";
            this.button_axisOnOff.Size = new System.Drawing.Size(91, 47);
            this.button_axisOnOff.TabIndex = 7;
            this.button_axisOnOff.Text = "未使能";
            this.button_axisOnOff.UseVisualStyleBackColor = true;
            this.button_axisOnOff.Click += new System.EventHandler(this.button_axisOnOff_Click);
            // 
            // BUTTON_INITIAL
            // 
            this.BUTTON_INITIAL.Location = new System.Drawing.Point(11, 22);
            this.BUTTON_INITIAL.Margin = new System.Windows.Forms.Padding(4);
            this.BUTTON_INITIAL.Name = "BUTTON_INITIAL";
            this.BUTTON_INITIAL.Size = new System.Drawing.Size(87, 47);
            this.BUTTON_INITIAL.TabIndex = 0;
            this.BUTTON_INITIAL.Text = "初始化";
            this.BUTTON_INITIAL.UseVisualStyleBackColor = true;
            this.BUTTON_INITIAL.Click += new System.EventHandler(this.BUTTON_INITIAL_Click);
            // 
            // COMBOBOX_CORENUM
            // 
            this.COMBOBOX_CORENUM.Items.AddRange(new object[] {
            "1",
            "2"});
            this.COMBOBOX_CORENUM.Location = new System.Drawing.Point(65, 84);
            this.COMBOBOX_CORENUM.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.COMBOBOX_CORENUM.Name = "COMBOBOX_CORENUM";
            this.COMBOBOX_CORENUM.Size = new System.Drawing.Size(110, 23);
            this.COMBOBOX_CORENUM.TabIndex = 5;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(11, 92);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(0, 15);
            this.label10.TabIndex = 6;
            // 
            // BUTTON_HOME
            // 
            this.BUTTON_HOME.Location = new System.Drawing.Point(27, 281);
            this.BUTTON_HOME.Margin = new System.Windows.Forms.Padding(4);
            this.BUTTON_HOME.Name = "BUTTON_HOME";
            this.BUTTON_HOME.Size = new System.Drawing.Size(148, 40);
            this.BUTTON_HOME.TabIndex = 4;
            this.BUTTON_HOME.Text = "回零功能";
            this.BUTTON_HOME.UseVisualStyleBackColor = true;
            this.BUTTON_HOME.Click += new System.EventHandler(this.BUTTON_HOME_Click);
            // 
            // BUTTON_CLOSE
            // 
            this.BUTTON_CLOSE.Location = new System.Drawing.Point(27, 340);
            this.BUTTON_CLOSE.Margin = new System.Windows.Forms.Padding(4);
            this.BUTTON_CLOSE.Name = "BUTTON_CLOSE";
            this.BUTTON_CLOSE.Size = new System.Drawing.Size(148, 40);
            this.BUTTON_CLOSE.TabIndex = 2;
            this.BUTTON_CLOSE.Text = "停止运动";
            this.BUTTON_CLOSE.UseVisualStyleBackColor = true;
            this.BUTTON_CLOSE.Click += new System.EventHandler(this.BUTTON_CLOSE_Click);
            // 
            // BUTTON_NJOG
            // 
            this.BUTTON_NJOG.Font = new System.Drawing.Font("宋体", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.BUTTON_NJOG.Location = new System.Drawing.Point(27, 222);
            this.BUTTON_NJOG.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.BUTTON_NJOG.Name = "BUTTON_NJOG";
            this.BUTTON_NJOG.Size = new System.Drawing.Size(67, 40);
            this.BUTTON_NJOG.TabIndex = 2;
            this.BUTTON_NJOG.Text = "←";
            this.BUTTON_NJOG.UseVisualStyleBackColor = true;
            this.BUTTON_NJOG.MouseDown += new System.Windows.Forms.MouseEventHandler(this.BUTTON_NJOG_MouseDown);
            this.BUTTON_NJOG.MouseUp += new System.Windows.Forms.MouseEventHandler(this.BUTTON_NJOG_MouseUp);
            // 
            // BUTTON_PJOG
            // 
            this.BUTTON_PJOG.Font = new System.Drawing.Font("宋体", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.BUTTON_PJOG.Location = new System.Drawing.Point(108, 222);
            this.BUTTON_PJOG.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.BUTTON_PJOG.Name = "BUTTON_PJOG";
            this.BUTTON_PJOG.Size = new System.Drawing.Size(67, 40);
            this.BUTTON_PJOG.TabIndex = 3;
            this.BUTTON_PJOG.Text = "→";
            this.BUTTON_PJOG.UseVisualStyleBackColor = true;
            this.BUTTON_PJOG.MouseDown += new System.Windows.Forms.MouseEventHandler(this.BUTTON_PJOG_MouseDown);
            this.BUTTON_PJOG.MouseUp += new System.Windows.Forms.MouseEventHandler(this.BUTTON_PJOG_MouseUp);
            // 
            // COMBOBOX_AXISNUM
            // 
            this.COMBOBOX_AXISNUM.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10",
            "11",
            "12"});
            this.COMBOBOX_AXISNUM.Location = new System.Drawing.Point(65, 121);
            this.COMBOBOX_AXISNUM.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.COMBOBOX_AXISNUM.Name = "COMBOBOX_AXISNUM";
            this.COMBOBOX_AXISNUM.Size = new System.Drawing.Size(110, 23);
            this.COMBOBOX_AXISNUM.TabIndex = 0;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(11, 123);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(52, 15);
            this.label6.TabIndex = 1;
            this.label6.Text = "轴号：";
            // 
            // BUTTON_PTP
            // 
            this.BUTTON_PTP.Location = new System.Drawing.Point(679, 19);
            this.BUTTON_PTP.Margin = new System.Windows.Forms.Padding(4);
            this.BUTTON_PTP.Name = "BUTTON_PTP";
            this.BUTTON_PTP.Size = new System.Drawing.Size(89, 35);
            this.BUTTON_PTP.TabIndex = 4;
            this.BUTTON_PTP.Text = "启动运动";
            this.BUTTON_PTP.UseVisualStyleBackColor = true;
            this.BUTTON_PTP.Click += new System.EventHandler(this.BUTTON_PTP_Click);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // COMBOBOX_DATACOUNT
            // 
            this.COMBOBOX_DATACOUNT.FormattingEnabled = true;
            this.COMBOBOX_DATACOUNT.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7"});
            this.COMBOBOX_DATACOUNT.Location = new System.Drawing.Point(123, 363);
            this.COMBOBOX_DATACOUNT.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.COMBOBOX_DATACOUNT.Name = "COMBOBOX_DATACOUNT";
            this.COMBOBOX_DATACOUNT.Size = new System.Drawing.Size(103, 23);
            this.COMBOBOX_DATACOUNT.TabIndex = 18;
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Location = new System.Drawing.Point(48, 370);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(60, 15);
            this.label28.TabIndex = 17;
            this.label28.Text = "数据点:";
            // 
            // dataGridView
            // 
            this.dataGridView.AllowUserToAddRows = false;
            this.dataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Column_Time,
            this.Column_Pos,
            this.Column_Vel,
            this.Column_Acc,
            this.Column_Percent,
            this.Column1,
            this.Column2,
            this.Column3});
            this.dataGridView.Location = new System.Drawing.Point(6, 73);
            this.dataGridView.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.dataGridView.Name = "dataGridView";
            this.dataGridView.RowHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.None;
            this.dataGridView.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.AutoSizeToFirstHeader;
            this.dataGridView.RowTemplate.Height = 27;
            this.dataGridView.Size = new System.Drawing.Size(763, 273);
            this.dataGridView.TabIndex = 24;
            // 
            // button_CLEAR
            // 
            this.button_CLEAR.Location = new System.Drawing.Point(679, 23);
            this.button_CLEAR.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button_CLEAR.Name = "button_CLEAR";
            this.button_CLEAR.Size = new System.Drawing.Size(89, 35);
            this.button_CLEAR.TabIndex = 23;
            this.button_CLEAR.Text = "清除所有";
            this.button_CLEAR.UseVisualStyleBackColor = true;
            this.button_CLEAR.Click += new System.EventHandler(this.button_CLEAR_Click);
            // 
            // button_DELECT
            // 
            this.button_DELECT.Location = new System.Drawing.Point(575, 23);
            this.button_DELECT.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button_DELECT.Name = "button_DELECT";
            this.button_DELECT.Size = new System.Drawing.Size(89, 35);
            this.button_DELECT.TabIndex = 22;
            this.button_DELECT.Text = "删除数据";
            this.button_DELECT.UseVisualStyleBackColor = true;
            this.button_DELECT.Click += new System.EventHandler(this.button_DELECT_Click);
            // 
            // button_ADD
            // 
            this.button_ADD.Location = new System.Drawing.Point(463, 23);
            this.button_ADD.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button_ADD.Name = "button_ADD";
            this.button_ADD.Size = new System.Drawing.Size(89, 35);
            this.button_ADD.TabIndex = 21;
            this.button_ADD.Text = "增加数据";
            this.button_ADD.UseVisualStyleBackColor = true;
            this.button_ADD.Click += new System.EventHandler(this.button_ADD_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.COMBOBOX_LOOPCOUNT);
            this.groupBox3.Controls.Add(this.label8);
            this.groupBox3.Controls.Add(this.button_updata);
            this.groupBox3.Controls.Add(this.button_PVTStart);
            this.groupBox3.Controls.Add(this.dataGridView);
            this.groupBox3.Controls.Add(this.button_CLEAR);
            this.groupBox3.Controls.Add(this.button_DELECT);
            this.groupBox3.Controls.Add(this.button_ADD);
            this.groupBox3.Controls.Add(this.COMBOBOX_MODE);
            this.groupBox3.Controls.Add(this.label9);
            this.groupBox3.Controls.Add(this.COMBOBOX_DATACOUNT);
            this.groupBox3.Controls.Add(this.label28);
            this.groupBox3.Location = new System.Drawing.Point(239, 9);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(782, 442);
            this.groupBox3.TabIndex = 25;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "PVT运动";
            // 
            // COMBOBOX_LOOPCOUNT
            // 
            this.COMBOBOX_LOOPCOUNT.FormattingEnabled = true;
            this.COMBOBOX_LOOPCOUNT.Items.AddRange(new object[] {
            "0(无限循环)",
            "1",
            "2",
            "3",
            "5",
            "10",
            "20",
            "50",
            "100"});
            this.COMBOBOX_LOOPCOUNT.Location = new System.Drawing.Point(122, 399);
            this.COMBOBOX_LOOPCOUNT.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.COMBOBOX_LOOPCOUNT.Name = "COMBOBOX_LOOPCOUNT";
            this.COMBOBOX_LOOPCOUNT.Size = new System.Drawing.Size(104, 23);
            this.COMBOBOX_LOOPCOUNT.TabIndex = 34;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(46, 402);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(75, 15);
            this.label8.TabIndex = 33;
            this.label8.Text = "循环次数:";
            // 
            // button_updata
            // 
            this.button_updata.Location = new System.Drawing.Point(575, 383);
            this.button_updata.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button_updata.Name = "button_updata";
            this.button_updata.Size = new System.Drawing.Size(89, 35);
            this.button_updata.TabIndex = 32;
            this.button_updata.Text = "更新数据";
            this.button_updata.UseVisualStyleBackColor = true;
            this.button_updata.Click += new System.EventHandler(this.button_updata_Click);
            // 
            // button_PVTStart
            // 
            this.button_PVTStart.Location = new System.Drawing.Point(680, 383);
            this.button_PVTStart.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button_PVTStart.Name = "button_PVTStart";
            this.button_PVTStart.Size = new System.Drawing.Size(89, 35);
            this.button_PVTStart.TabIndex = 31;
            this.button_PVTStart.Text = "启动运动";
            this.button_PVTStart.UseVisualStyleBackColor = true;
            this.button_PVTStart.Click += new System.EventHandler(this.button_PVTStart_Click);
            // 
            // COMBOBOX_MODE
            // 
            this.COMBOBOX_MODE.FormattingEnabled = true;
            this.COMBOBOX_MODE.Items.AddRange(new object[] {
            "PVT",
            "Complete",
            "Percent",
            "Continuous"});
            this.COMBOBOX_MODE.Location = new System.Drawing.Point(89, 30);
            this.COMBOBOX_MODE.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.COMBOBOX_MODE.Name = "COMBOBOX_MODE";
            this.COMBOBOX_MODE.Size = new System.Drawing.Size(114, 23);
            this.COMBOBOX_MODE.TabIndex = 18;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(44, 33);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(45, 15);
            this.label9.TabIndex = 17;
            this.label9.Text = "模式:";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.textBox_ptpSmTime);
            this.groupBox4.Controls.Add(this.label7);
            this.groupBox4.Controls.Add(this.textBox_ptpPos);
            this.groupBox4.Controls.Add(this.label5);
            this.groupBox4.Controls.Add(this.textBox_ptpAcc);
            this.groupBox4.Controls.Add(this.label4);
            this.groupBox4.Controls.Add(this.textBox_ptpVel);
            this.groupBox4.Controls.Add(this.label3);
            this.groupBox4.Controls.Add(this.BUTTON_PTP);
            this.groupBox4.Location = new System.Drawing.Point(239, 457);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(782, 66);
            this.groupBox4.TabIndex = 26;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "点位运动";
            // 
            // textBox_ptpSmTime
            // 
            this.textBox_ptpSmTime.Location = new System.Drawing.Point(572, 23);
            this.textBox_ptpSmTime.Name = "textBox_ptpSmTime";
            this.textBox_ptpSmTime.Size = new System.Drawing.Size(84, 25);
            this.textBox_ptpSmTime.TabIndex = 12;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(499, 29);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(82, 15);
            this.label7.TabIndex = 11;
            this.label7.Text = "平滑时间：";
            // 
            // textBox_ptpPos
            // 
            this.textBox_ptpPos.Location = new System.Drawing.Point(248, 24);
            this.textBox_ptpPos.Name = "textBox_ptpPos";
            this.textBox_ptpPos.Size = new System.Drawing.Size(84, 25);
            this.textBox_ptpPos.TabIndex = 10;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(176, 30);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(60, 15);
            this.label5.TabIndex = 9;
            this.label5.Text = " 位移：";
            // 
            // textBox_ptpAcc
            // 
            this.textBox_ptpAcc.Location = new System.Drawing.Point(403, 23);
            this.textBox_ptpAcc.Name = "textBox_ptpAcc";
            this.textBox_ptpAcc.Size = new System.Drawing.Size(84, 25);
            this.textBox_ptpAcc.TabIndex = 8;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(338, 29);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(67, 15);
            this.label4.TabIndex = 7;
            this.label4.Text = "加速度：";
            // 
            // textBox_ptpVel
            // 
            this.textBox_ptpVel.Location = new System.Drawing.Point(78, 26);
            this.textBox_ptpVel.Name = "textBox_ptpVel";
            this.textBox_ptpVel.Size = new System.Drawing.Size(84, 25);
            this.textBox_ptpVel.TabIndex = 6;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(14, 32);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(52, 15);
            this.label3.TabIndex = 5;
            this.label3.Text = "速度：";
            // 
            // Column_Time
            // 
            this.Column_Time.HeaderText = "时间";
            this.Column_Time.Name = "Column_Time";
            this.Column_Time.Width = 70;
            // 
            // Column_Pos
            // 
            this.Column_Pos.HeaderText = "位置";
            this.Column_Pos.Name = "Column_Pos";
            this.Column_Pos.Width = 70;
            // 
            // Column_Vel
            // 
            this.Column_Vel.HeaderText = "速度";
            this.Column_Vel.Name = "Column_Vel";
            this.Column_Vel.Width = 70;
            // 
            // Column_Acc
            // 
            this.Column_Acc.HeaderText = "加速度";
            this.Column_Acc.Name = "Column_Acc";
            this.Column_Acc.Width = 90;
            // 
            // Column_Percent
            // 
            this.Column_Percent.HeaderText = "百分比";
            this.Column_Percent.Name = "Column_Percent";
            this.Column_Percent.Width = 90;
            // 
            // Column1
            // 
            this.Column1.HeaderText = "最大速度";
            this.Column1.Name = "Column1";
            this.Column1.Width = 110;
            // 
            // Column2
            // 
            this.Column2.HeaderText = "段内加速度";
            this.Column2.Name = "Column2";
            this.Column2.Width = 120;
            // 
            // Column3
            // 
            this.Column3.HeaderText = "段内减速度";
            this.Column3.Name = "Column3";
            this.Column3.Width = 120;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1043, 534);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "Form1";
            this.Text = "GSN_Test";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).EndInit();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox textBox_PrfPos2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBox_PrfPos1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button BUTTON_CLOSE;
        private System.Windows.Forms.Button BUTTON_INITIAL;
        private System.Windows.Forms.Button BUTTON_PJOG;
        private System.Windows.Forms.Button BUTTON_NJOG;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox COMBOBOX_AXISNUM;
        private System.Windows.Forms.Button BUTTON_HOME;
        private System.Windows.Forms.Button BUTTON_PTP;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button button_axisOnOff;
        private System.Windows.Forms.ComboBox COMBOBOX_CORENUM;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.ComboBox COMBOBOX_DATACOUNT;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.DataGridView dataGridView;
        private System.Windows.Forms.Button button_CLEAR;
        private System.Windows.Forms.Button button_DELECT;
        private System.Windows.Forms.Button button_ADD;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button button_updata;
        private System.Windows.Forms.Button button_PVTStart;
        private System.Windows.Forms.Button button_zeroPos;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.TextBox textBox_ptpAcc;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBox_ptpVel;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBox_ptpSmTime;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textBox_ptpPos;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox COMBOBOX_LOOPCOUNT;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.ComboBox COMBOBOX_MODE;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column_Time;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column_Pos;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column_Vel;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column_Acc;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column_Percent;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column1;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column2;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column3;
    }
}

