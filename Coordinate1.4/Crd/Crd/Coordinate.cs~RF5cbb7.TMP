using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Crd
{
    public partial class Coordinate : Form
    {
        short sRtn, core, crd, fifo, dms, et, axis_x, axis_y, axis_z, axis_a, axis_c, plab, circleDir,
             gearAxis, moveAxis, modal, chn, doValue, limitType, axis;
        double sVM, sAM, T, accMAX, synVel, synAcc, velEnd, radius, xCenter, yCenter,
            vel, acc;
        int ogp_x, ogp_y, ogp_z, ogp_a, ogp_c, pos; 
        int x, y, z = 0;
        ushort doMask, udoValue, doType;
        uint delayTime;

        GTN.mc.TCrdData[] crdData = new GTN.mc.TCrdData[200];// 定义前瞻缓存区内存区
        uint clk;//时钟参数
        public Coordinate()
        {
            InitializeComponent();
        }
        private void Coordinate_Load(object sender, EventArgs e)//窗口初始化
        {
            //默认文本显示
            this.ComboBox_CORENUM.SelectedIndex = 0;                
            this.ComboBox_COORDINATE.SelectedIndex = 0;
            this.ComboBox_FIFO.SelectedIndex = 0;
            this.ComboBox_DIMENSION.SelectedIndex = 2;
            this.ComboBox_AXIS_X.SelectedIndex = 1;
            this.ComboBox_AXIS_Y.SelectedIndex = 2;
            this.ComboBox_AXIS_Z.SelectedIndex = 3;
            this.ComboBox_AXIS_A.SelectedIndex = 0;
            this.ComboBox_AXIS_C.SelectedIndex = 0;
            this.comboBox_DATATYPE.SelectedIndex = 0;
            //文本框状态
            textBox_ORIGINPOS_X.Enabled = false;
            textBox_ORIGINPOS_Y.Enabled = false;
            textBox_ORIGINPOS_Z.Enabled = false;
            textBox_ORIGINPOS_A.Enabled = false;
            textBox_ORIGINPOS_C.Enabled = false;
            //初始化控制卡
            sRtn = GTN.mc.GTN_Open(0, 1);                           // 打开运动控制器
            sRtn = GTN.mc.GTN_Reset(1);                             // 复位运动控制器
            sRtn = GTN.mc.GTN_Reset(2);
            sRtn = GTN.mc.GTN_LoadConfig(1, "gtn_core1.cfg");            // 下载控制器配置文件
            if (sRtn != 0)
            {
                MessageBox.Show("核1配置文件加载失败");
            }
            sRtn = GTN.mc.GTN_LoadConfig(2, "gtn_core2.cfg");
            sRtn = GTN.mc.GTN_ClrSts(1, 1, 5);                      // 清除1~5轴的轴状态
            sRtn = GTN.mc.GTN_ClrSts(2, 1, 5);
            for (short i = 1; i <= 5; ++i)
            {
                sRtn = GTN.mc.GTN_AxisOn(1, i);                      // 使能运动轴
            }
            sRtn = GTN.mc.GTN_ZeroPos(1, 1, 5);                      // 轴位置清零
            sRtn = GTN.mc.GTN_ZeroPos(2, 1, 5); 
            //启动定时器刷新状态
            timer1.Start();
        }
        private void timer1_Tick(object sender, EventArgs e)                    //设置定时器读取状态
        {
            double[] prfPos = new double[5];
            short run;
            int segment, space;

            core = Convert.ToInt16(this.ComboBox_CORENUM.SelectedIndex + 1);    //读取数据
            crd = Convert.ToInt16(this.ComboBox_COORDINATE.SelectedIndex + 1);
            fifo = Convert.ToInt16(this.ComboBox_FIFO.SelectedIndex);
            sRtn = GTN.mc.GTN_GetPrfPos(core, 1, out prfPos[0], 5, out clk);    // 读1~5轴的规划位置
            sRtn = GTN.mc.GTN_CrdStatus(core, crd, out run, out segment, fifo); // 读取坐标系运动状态
            sRtn = GTN.mc.GTN_CrdSpace(core, crd, out space, fifo);             // 查询运动缓存区空间

            this.label_PRFPOS_X.Text = Math.Round(prfPos[0], 1).ToString();     //X~C轴规划位置
            this.label_PRFPOS_Y.Text = Math.Round(prfPos[1], 1).ToString();
            this.label_PRFPOS_Z.Text = Math.Round(prfPos[2], 1).ToString();
            this.label_PRFPOS_A.Text = Math.Round(prfPos[3], 1).ToString();
            this.label_PRFPOS_C.Text = Math.Round(prfPos[4], 1).ToString();
            if (run == 1)
                this.label_RUN_STATUS.Text = "运动";
            else if (run == 0)
                this.label_RUN_STATUS.Text = "静止";
            // this.textBox4.Text = Math.Round(segment*1.00, 1).ToString();
            this.label_CRD_SPACE.Text = space.ToString();       //插补空间
            this.label_SEGMENT_STATUS.Text = segment.ToString();//坐标系段号
        }
        private void button_INIT_Click(object sender, EventArgs e)//建立坐标系
        {
            //读取数据
            core = Convert.ToInt16(this.ComboBox_CORENUM.SelectedIndex + 1);
            crd = Convert.ToInt16(this.ComboBox_COORDINATE.SelectedIndex + 1);
            fifo = Convert.ToInt16(this.ComboBox_FIFO.SelectedIndex);
            dms = Convert.ToInt16(this.ComboBox_DIMENSION.SelectedIndex + 1);
            sVM = Convert.ToDouble(this.TextBox_SYNVELMAX.Text);
            sAM = Convert.ToDouble(this.TextBox_SYNACCMAX.Text);
            et = Convert.ToInt16(this.TextBox_EVENTIME.Text);
            
            axis_x = Convert.ToInt16(this.ComboBox_AXIS_X.SelectedIndex);
            axis_y = Convert.ToInt16(this.ComboBox_AXIS_Y.SelectedIndex);
            axis_z = Convert.ToInt16(this.ComboBox_AXIS_Z.SelectedIndex);
            axis_a = Convert.ToInt16(this.ComboBox_AXIS_A.SelectedIndex);
            axis_c = Convert.ToInt16(this.ComboBox_AXIS_C.SelectedIndex);

            ogp_x = Convert.ToInt32(this.textBox_ORIGINPOS_X.Text);
            ogp_y = Convert.ToInt32(this.textBox_ORIGINPOS_Y.Text);
            ogp_z = Convert.ToInt32(this.textBox_ORIGINPOS_Z.Text);
            ogp_a = Convert.ToInt32(this.textBox_ORIGINPOS_A.Text);
            ogp_c = Convert.ToInt32(this.textBox_ORIGINPOS_C.Text);
            // TCrdPrm结构体变量，该结构体定义了坐标系
            GTN.mc.TCrdPrm crdPrm;
            // 为结构体赋值
            crdPrm.dimension = dms; // 坐标系为三维坐标系
            crdPrm.synVelMax = sVM; // 最大合成速度：500pulse/ms
            crdPrm.synAccMax = sAM; // 最大加速度：2pulse/ms^2
            crdPrm.evenTime = et; // 最小匀速时间：50ms
            crdPrm.profile1 = axis_x; // 规划器1对应到X轴
            crdPrm.profile2 = axis_y; // 规划器2对应到Y轴
            crdPrm.profile3 = axis_z; // 规划器3对应到Z轴
            crdPrm.profile4 = axis_a;
            crdPrm.profile5 = axis_c;
            crdPrm.profile6 = 0;
            crdPrm.profile7 = 0;
            crdPrm.profile8 = 0;
            crdPrm.setOriginFlag = crd; // 表示需要指定坐标系的原点坐标的规划位置
            crdPrm.originPos1 = ogp_x; // 加工坐标系原点位置在(0,0,0)，即与机床坐标系原点重合
            crdPrm.originPos2 = ogp_y;
            crdPrm.originPos3 = ogp_z;
            crdPrm.originPos4 = ogp_a;
            crdPrm.originPos5 = ogp_c;
            crdPrm.originPos6 = 0;
            crdPrm.originPos7 = 0;
            crdPrm.originPos8 = 0;
            // 建立1号坐标系，设置坐标系参数
            sRtn = GTN.mc.GTN_SetCrdPrm(core, crd, ref crdPrm);
            // 即将把数据存入坐标系1的FIFO0中，所以要首先清除此缓存区中的数据
            sRtn = GTN.mc.GTN_CrdClear(core, crd, fifo);
        }
        private void checkBox_ORIGINCRD_CheckedChanged(object sender, EventArgs e)//坐标系开启
        {
            if (checkBox_ORIGINCRD.Checked)
            {
                textBox_ORIGINPOS_X.Enabled = true;
                textBox_ORIGINPOS_Y.Enabled = true;
                textBox_ORIGINPOS_Z.Enabled = true;
                textBox_ORIGINPOS_A.Enabled = true;
                textBox_ORIGINPOS_C.Enabled = true;
            }
            else
            {
                textBox_ORIGINPOS_X.Enabled = false;
                textBox_ORIGINPOS_Y.Enabled = false;
                textBox_ORIGINPOS_Z.Enabled = false;
                textBox_ORIGINPOS_A.Enabled = false;
                textBox_ORIGINPOS_C.Enabled = false;
            }
        }
        private void checkBox_LOOKAHEAD_CheckedChanged(object sender, EventArgs e)//前瞻开启
        {
            if (checkBox_LOOKAHEAD.Checked)
            {
                crd = Convert.ToInt16(this.ComboBox_COORDINATE.SelectedIndex + 1);
                fifo = Convert.ToInt16(this.ComboBox_FIFO.SelectedIndex);
                T = Convert.ToDouble(this.textBox_T.Text);
                accMAX = Convert.ToDouble(this.textBox_ACCMAX.Text);
                plab = Convert.ToInt16(this.textBox_PLOOKAHEADBUF.Text);
                // 初始化坐标系1的FIFO0的前瞻模块
                sRtn = GTN.mc.GT_InitLookAhead(crd, fifo, T, accMAX, plab, ref crdData[0]);
            }
            else
            {
            }
        }

        //数据段操作
        private void button_ADD_Click(object sender, EventArgs e)//添加数据
        {
            switch(comboBox_DATATYPE.SelectedItem.ToString())
            {                  
            case"LnXY":
                dataGridView.Columns[0].HeaderCell.Value = "CrdID";//设置列标题值
                dataGridView.Columns[1].HeaderCell.Value = "X";
                dataGridView.Columns[2].HeaderCell.Value = "Y";
                dataGridView.Columns[3].HeaderCell.Value = "synVel";
                dataGridView.Columns[4].HeaderCell.Value = "synAcc";
                dataGridView.Columns[5].HeaderCell.Value = "velEnd";
                dataGridView.Columns[6].HeaderCell.Value = "段号";
                dataGridView.Rows.Add("LnXY", "0.000", "0.000", "0.000", "0.000", "0.000","0");//添加行值
                break;
             case"LnXYG0":
                dataGridView.Columns[0].HeaderCell.Value = "CrdID";
                dataGridView.Columns[1].HeaderCell.Value = "X";
                dataGridView.Columns[2].HeaderCell.Value = "Y";
                dataGridView.Columns[3].HeaderCell.Value = "synVel";
                dataGridView.Columns[4].HeaderCell.Value = "synAcc";
                dataGridView.Columns[5].HeaderCell.Value = "段号";
                dataGridView.Columns[6].HeaderCell.Value = "段号";
                dataGridView.Rows.Add("LnXYG0", "0.000", "0.000", "0.000","0.000","0");
                break;
             case "LnXYZ":
                dataGridView.Columns[0].HeaderCell.Value = "CrdID";
                dataGridView.Columns[1].HeaderCell.Value = "X";
                dataGridView.Columns[2].HeaderCell.Value = "Y";
                dataGridView.Columns[3].HeaderCell.Value = "Z";
                dataGridView.Columns[4].HeaderCell.Value = "synVel";
                dataGridView.Columns[5].HeaderCell.Value = "synAcc";
                dataGridView.Columns[6].HeaderCell.Value = "velEnd";
                dataGridView.Columns[7].HeaderCell.Value = "段号";
                dataGridView.Rows.Add("LnXYZ", "0.000", "0.000", "0.000", "0.000", "0.000", "0.000","0");
                break;
             case "LnXYZG0":
                dataGridView.Columns[0].HeaderCell.Value = "CrdID";
                dataGridView.Columns[1].HeaderCell.Value = "X";
                dataGridView.Columns[2].HeaderCell.Value = "Y";
                dataGridView.Columns[3].HeaderCell.Value = "Z";
                dataGridView.Columns[4].HeaderCell.Value = "synVel";
                dataGridView.Columns[5].HeaderCell.Value = "synAcc";
                dataGridView.Columns[6].HeaderCell.Value = "段号";
                dataGridView.Rows.Add("LnXYZG0", "0.000", "0.000", "0.000", "0.000", "0.000", "0.000", "0");
                break;
             case "ArcXYR":
                dataGridView.Columns[0].HeaderCell.Value = "CrdID";
                dataGridView.Columns[1].HeaderCell.Value = "X";
                dataGridView.Columns[2].HeaderCell.Value = "Y";
                dataGridView.Columns[3].HeaderCell.Value = "radius";
                dataGridView.Columns[4].HeaderCell.Value = "circleDir";
                dataGridView.Columns[5].HeaderCell.Value = "synVel";
                dataGridView.Columns[6].HeaderCell.Value = "synAcc";
                dataGridView.Columns[7].HeaderCell.Value = "velEnd";
                dataGridView.Columns[8].HeaderCell.Value = "段号";
                dataGridView.Rows.Add("ArcXYR", "0.000", "0.000", "0.000", "0", "0.000", "0.000", "0.000", "0");
                break;
             case "ArcXYC":
                dataGridView.Columns[0].HeaderCell.Value = "CrdID";
                dataGridView.Columns[1].HeaderCell.Value = "X";
                dataGridView.Columns[2].HeaderCell.Value = "Y";
                dataGridView.Columns[3].HeaderCell.Value = "xCenter";
                dataGridView.Columns[4].HeaderCell.Value = "yCenter";
                dataGridView.Columns[5].HeaderCell.Value = "circleDir";
                dataGridView.Columns[6].HeaderCell.Value = "synVel";
                dataGridView.Columns[7].HeaderCell.Value = "synAcc";
                dataGridView.Columns[8].HeaderCell.Value = "velEnd";
                dataGridView.Columns[9].HeaderCell.Value = "段号";
                dataGridView.Rows.Add("ArcXYC", "0.000", "0.000", "0.000", "0.000", "0", "0.000", "0.000", "0.000", "0");
                break;
             case "ArcZXR":
                dataGridView.Columns[0].HeaderCell.Value = "CrdID";
                dataGridView.Columns[1].HeaderCell.Value = "X";
                dataGridView.Columns[2].HeaderCell.Value = "Z";
                dataGridView.Columns[3].HeaderCell.Value = "radius";
                dataGridView.Columns[4].HeaderCell.Value = "circleDir";
                dataGridView.Columns[5].HeaderCell.Value = "synVel";
                dataGridView.Columns[6].HeaderCell.Value = "synAcc";
                dataGridView.Columns[7].HeaderCell.Value = "velEnd";
                dataGridView.Columns[8].HeaderCell.Value = "段号";
                dataGridView.Rows.Add("ArcZXR", "0.000", "0.000", "0.000", "0", "0.000", "0.000", "0.000", "0");
                break;
             case "ArcZXC":
                dataGridView.Columns[0].HeaderCell.Value = "CrdID";
                dataGridView.Columns[1].HeaderCell.Value = "X";
                dataGridView.Columns[2].HeaderCell.Value = "Z";
                dataGridView.Columns[3].HeaderCell.Value = "xCenter";
                dataGridView.Columns[4].HeaderCell.Value = "yCenter";
                dataGridView.Columns[5].HeaderCell.Value = "circleDir";
                dataGridView.Columns[6].HeaderCell.Value = "synVel";
                dataGridView.Columns[7].HeaderCell.Value = "synAcc";
                dataGridView.Columns[8].HeaderCell.Value = "velEnd";
                dataGridView.Columns[9].HeaderCell.Value = "段号";
                dataGridView.Rows.Add("ArcZXC", "0.000", "0.000", "0.000", "0.000", "0", "0.000", "0.000", "0.000", "0");
                break;
             case "ArcYZR":
                dataGridView.Columns[0].HeaderCell.Value = "CrdID";
                dataGridView.Columns[1].HeaderCell.Value = "Y";
                dataGridView.Columns[2].HeaderCell.Value = "Z";
                dataGridView.Columns[3].HeaderCell.Value = "radius";
                dataGridView.Columns[4].HeaderCell.Value = "circleDir";
                dataGridView.Columns[5].HeaderCell.Value = "synVel";
                dataGridView.Columns[6].HeaderCell.Value = "synAcc";
                dataGridView.Columns[7].HeaderCell.Value = "velEnd";
                dataGridView.Columns[8].HeaderCell.Value = "段号";
                dataGridView.Rows.Add("ArcYZR", "0.000", "0.000", "0.000", "0", "0.000", "0.000", "0.000", "0");
                break;
             case "ArcYZC":
                dataGridView.Columns[0].HeaderCell.Value = "CrdID";
                dataGridView.Columns[1].HeaderCell.Value = "Y";
                dataGridView.Columns[2].HeaderCell.Value = "Z";
                dataGridView.Columns[3].HeaderCell.Value = "xCenter";
                dataGridView.Columns[4].HeaderCell.Value = "yCenter";
                dataGridView.Columns[5].HeaderCell.Value = "circleDir";
                dataGridView.Columns[6].HeaderCell.Value = "synVel";
                dataGridView.Columns[7].HeaderCell.Value = "synAcc";
                dataGridView.Columns[8].HeaderCell.Value = "velEnd";
                dataGridView.Columns[9].HeaderCell.Value = "段号";
                dataGridView.Rows.Add("ArcYZC", "0.000", "0.000", "0.000", "0.000", "0", "0.000", "0.000", "0.000", "0");
                break;
             case "BufIo":
                dataGridView.Columns[0].HeaderCell.Value = "BufID";
                dataGridView.Columns[1].HeaderCell.Value = "doType";
                dataGridView.Columns[2].HeaderCell.Value = "doMask";
                dataGridView.Columns[3].HeaderCell.Value = "doValue";
                dataGridView.Rows.Add("BufIo", "0", "0", "0");
                DataGridViewComboBoxCell cbBufIo = new DataGridViewComboBoxCell();//将dataGridView的某个单元格设为ComboBox的样式
                string[] bufioStr = new string[] {"ENABLE", "CLEAR", "GPO"};
                cbBufIo.DataSource = bufioStr;
                cbBufIo.Value = "ENABLE";
                int rows = dataGridView.Rows.Count;//获取datagridview的总行数（不可见）
                dataGridView.Rows[rows - 1].Cells["Column_X"] = cbBufIo;
                break;
             case "BufDelay":
                dataGridView.Columns[0].HeaderCell.Value = "BufDelay";
                dataGridView.Columns[1].HeaderCell.Value = "delayTime";
                dataGridView.Rows.Add("BufDelay", "0");
                break;
             case "BufDA":
                dataGridView.Columns[0].HeaderCell.Value = "BufDA";
                dataGridView.Columns[1].HeaderCell.Value = "channel";
                dataGridView.Columns[2].HeaderCell.Value = "value";
                dataGridView.Rows.Add("BufDA", "1", "0");
                DataGridViewComboBoxCell cbBufDa = new DataGridViewComboBoxCell();//将dataGridView的某个单元格设为ComboBox的样式
                string[] bufdaStr = new string[] { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
                cbBufDa.DataSource = bufdaStr;
                cbBufDa.Value = "1";
                int rows1 = dataGridView.Rows.Count;//获取datagridview的总行数（不可见）
                dataGridView.Rows[rows1 - 1].Cells["Column_X"] = cbBufDa;
                break;
             case "BufMove":
                dataGridView.Columns[0].HeaderCell.Value = "BufMove";//设置列标题值
                dataGridView.Columns[1].HeaderCell.Value = "moveAxis";
                dataGridView.Columns[2].HeaderCell.Value = "pos";
                dataGridView.Columns[3].HeaderCell.Value = "vel";
                dataGridView.Columns[4].HeaderCell.Value = "acc";
                dataGridView.Columns[5].HeaderCell.Value = "modal";
                dataGridView.Rows.Add("BufMove", "1", "0.000", "0.000", "0.000", "0");//添加行值
                DataGridViewComboBoxCell cbBufMove = new DataGridViewComboBoxCell();//将dataGridView的某个单元格设为ComboBox的样式
                string[] bufmoveStr = new string[] { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
                cbBufMove.DataSource = bufmoveStr;
                cbBufMove.Value = "1";
                int rows2 = dataGridView.Rows.Count;//获取datagridview的总行数（不可见）
                dataGridView.Rows[rows2 - 1].Cells["Column_X"] = cbBufMove;
                break;
             case "BufGear":
                dataGridView.Columns[0].HeaderCell.Value = "BufGear";
                dataGridView.Columns[1].HeaderCell.Value = "gearAxis";
                dataGridView.Columns[2].HeaderCell.Value = "pos";
                dataGridView.Rows.Add("BufGear", "1", "0.000");
                DataGridViewComboBoxCell cbBufGear = new DataGridViewComboBoxCell();//将dataGridView的某个单元格设为ComboBox的样式
                string[] bufgearStr = new string[] { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12" };
                cbBufGear.DataSource = bufgearStr;
                cbBufGear.Value = "1";
                int rows3 = dataGridView.Rows.Count;//获取datagridview的总行数（不可见）
                dataGridView.Rows[rows3 - 1].Cells["Column_X"] = cbBufGear;
                break;
             case "BufSetStopIo":
                dataGridView.Columns[0].HeaderCell.Value = "BufSetStopIo";
                dataGridView.Rows.Add("BufSetStopIo");
                break;
             case "BufLmtsOn":
                dataGridView.Columns[0].HeaderCell.Value = "BufLmtsOn";
                dataGridView.Columns[1].HeaderCell.Value = "channel";
                dataGridView.Rows.Add("BufLmtsOn", "1");
                DataGridViewComboBoxCell cbBufLmtsOn = new DataGridViewComboBoxCell();//将dataGridView的某个单元格设为ComboBox的样式
                string[] buflmtonStr = new string[] { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12" };
                cbBufLmtsOn.DataSource = buflmtonStr;
                cbBufLmtsOn.Value = "1";
                int rows4 = dataGridView.Rows.Count;//获取datagridview的总行数（不可见）
                dataGridView.Rows[rows4 - 1].Cells["Column_X"] = cbBufLmtsOn;
                break;
             case "BufLmtsOff":
                dataGridView.Columns[0].HeaderCell.Value = "BufLmtsOff";
                dataGridView.Columns[1].HeaderCell.Value = "channel";
                dataGridView.Rows.Add("BufLmtsOff", "1");
                DataGridViewComboBoxCell cbBufLmtsOff = new DataGridViewComboBoxCell();//将dataGridView的某个单元格设为ComboBox的样式
                string[] buflmtoffStr = new string[] { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12" };
                cbBufLmtsOff.DataSource = buflmtoffStr;
                cbBufLmtsOff.Value = "1";
                int rows5 = dataGridView.Rows.Count;//获取datagridview的总行数（不可见）
                dataGridView.Rows[rows5 - 1].Cells["Column_X"] = cbBufLmtsOff;
                break;
            }
            dataGridView.ClearSelection(); //DataGridView取消默认选中行
            dataGridView.Columns[0].ReadOnly = true;// 设置 DataGridView1 的第2列整列单元格为只读
            dataGridView.AutoResizeColumns(DataGridViewAutoSizeColumnsMode.AllCells);// 让dataGridView的所有列宽自动调整。
        }
        private void button_DELECT_Click(object sender, EventArgs e)
        {
            //向上遍历
            //int row = this.dataGridView.CurrentRow.Index - 1;
            //if (row < 0)
            //row = this.dataGridView.RowCount - 1;
            //this.dataGridView.CurrentCell = this.dataGridView[0, row];
             int rowIndex = this.dataGridView.CurrentCell.RowIndex;//取得当前单元格所在的行的Index
             dataGridView.Rows.RemoveAt(rowIndex);//根据索引删除选中行
        }
        private void button_CLEAR_Click(object sender, EventArgs e)//清空所有数据
        {
            dataGridView.Rows.Clear();
        }
        private void dataGridView_RowStateChanged(object sender, DataGridViewRowStateChangedEventArgs e)//将序号显示在Row的HeaderCell上
        {
            for (int i = 0; i < this.dataGridView.Rows.Count; i++)
            {
                DataGridViewRow r = this.dataGridView.Rows[i];
                r.HeaderCell.Value = string.Format("{0}", i + 1);
            }
            this.dataGridView.Refresh();
        }
        
        //插补操作
        private void button_START_Click(object sender, EventArgs e)//启动坐标系1的FIFO0的插补运动
        {
            //MessageBox.Show(dataGridView.Rows[0].Cells[1].Value.ToString());
            core = Convert.ToInt16(this.ComboBox_CORENUM.SelectedIndex + 1);
            crd = Convert.ToInt16(this.ComboBox_COORDINATE.SelectedIndex + 1);
            fifo = Convert.ToInt16(this.ComboBox_FIFO.SelectedIndex);
            sRtn = GTN.mc.GTN_CrdClear(core, crd, fifo);//清除缓存区中的数据
            int rows = dataGridView.Rows.Count;//获取datagridview的总行数（不可见）
            for (int i = 0; i < rows; ++i)
            {
                switch (comboBox_DATATYPE.SelectedItem.ToString())
                {
                    case "LnXY":
                        x = Convert.ToInt32(dataGridView.Rows[i].Cells[1].Value);//获取某个（指定的）单元格的值
                        y = Convert.ToInt32(dataGridView.Rows[i].Cells[2].Value);
                        synVel = Convert.ToDouble(dataGridView.Rows[i].Cells[3].Value);
                        synAcc = Convert.ToDouble(dataGridView.Rows[i].Cells[4].Value);
                        velEnd = Convert.ToDouble(dataGridView.Rows[i].Cells[5].Value);
                        sRtn = GTN.mc.GTN_LnXY(core, crd, x, y, synVel, synAcc, velEnd, fifo);
                        x += x; y += y;
                        break;
                    case "LnXYG0":
                        x = Convert.ToInt32(dataGridView.Rows[i].Cells[1].Value);
                        y = Convert.ToInt32(dataGridView.Rows[i].Cells[2].Value);
                        synVel = Convert.ToDouble(dataGridView.Rows[i].Cells[3].Value);
                        synAcc = Convert.ToDouble(dataGridView.Rows[i].Cells[4].Value);
                        sRtn = GTN.mc.GTN_LnXYG0(core, crd, x, y, synVel, synAcc, fifo);
                        x += x; y += y;
                        break;
                    case "LnXYZ":
                        x = Convert.ToInt32(dataGridView.Rows[i].Cells[1].Value);
                        y = Convert.ToInt32(dataGridView.Rows[i].Cells[2].Value);
                        z = Convert.ToInt32(dataGridView.Rows[i].Cells[3].Value);
                        synVel = Convert.ToDouble(dataGridView.Rows[i].Cells[4].Value);
                        synAcc = Convert.ToDouble(dataGridView.Rows[i].Cells[5].Value);
                        velEnd = Convert.ToDouble(dataGridView.Rows[i].Cells[6].Value);
                        sRtn = GTN.mc.GTN_LnXYZ(core, crd, x, y, z, synVel, synAcc, velEnd, fifo);
                        x += x; y += y; z += z;
                        break;
                    case "LnXYZG0":
                        x = Convert.ToInt32(dataGridView.Rows[i].Cells[1].Value);
                        y = Convert.ToInt32(dataGridView.Rows[i].Cells[2].Value);
                        z = Convert.ToInt32(dataGridView.Rows[i].Cells[3].Value);
                        synVel = Convert.ToDouble(dataGridView.Rows[i].Cells[4].Value);
                        synAcc = Convert.ToDouble(dataGridView.Rows[i].Cells[5].Value);
                        sRtn = GTN.mc.GTN_LnXYZG0(core, crd, x, y, z, synVel, synAcc, fifo);
                        x += x; y += y; z += z;
                        break;
                    case "ArcXYR":
                        x = Convert.ToInt32(dataGridView.Rows[i].Cells[1].Value);
                        y = Convert.ToInt32(dataGridView.Rows[i].Cells[2].Value);
                        radius = Convert.ToDouble(dataGridView.Rows[i].Cells[3].Value);
                        circleDir = Convert.ToInt16(dataGridView.Rows[i].Cells[4].Value);
                        synVel = Convert.ToDouble(dataGridView.Rows[i].Cells[5].Value);
                        synAcc = Convert.ToDouble(dataGridView.Rows[i].Cells[6].Value);
                        velEnd = Convert.ToDouble(dataGridView.Rows[i].Cells[7].Value);
                        sRtn = GTN.mc.GTN_ArcXYR(core, crd, x, y, radius, circleDir, synVel, synAcc, velEnd, fifo);
                        x += x; y += y;
                        break;
                    case "ArcXYC":
                        x = Convert.ToInt32(dataGridView.Rows[i].Cells[1].Value);
                        y = Convert.ToInt32(dataGridView.Rows[i].Cells[2].Value);
                        xCenter = Convert.ToDouble(dataGridView.Rows[i].Cells[3].Value);
                        yCenter = Convert.ToDouble(dataGridView.Rows[i].Cells[4].Value);
                        circleDir = Convert.ToInt16(dataGridView.Rows[i].Cells[5].Value); 
                        synVel = Convert.ToDouble(dataGridView.Rows[i].Cells[6].Value);
                        synAcc = Convert.ToDouble(dataGridView.Rows[i].Cells[7].Value);
                        velEnd = Convert.ToDouble(dataGridView.Rows[i].Cells[8].Value);
                        sRtn = GTN.mc.GTN_ArcXYC(core, crd, x, y, xCenter, yCenter, circleDir, synVel, synAcc, velEnd, fifo);
                        x += x; y += y;
                        break;
                    case "ArcZXR":
                        x = Convert.ToInt32(dataGridView.Rows[i].Cells[1].Value);
                        z = Convert.ToInt32(dataGridView.Rows[i].Cells[2].Value);
                        radius = Convert.ToDouble(dataGridView.Rows[i].Cells[3].Value);
                        circleDir = Convert.ToInt16(dataGridView.Rows[i].Cells[4].Value);
                        synVel = Convert.ToDouble(dataGridView.Rows[i].Cells[5].Value);
                        synAcc = Convert.ToDouble(dataGridView.Rows[i].Cells[6].Value);
                        velEnd = Convert.ToDouble(dataGridView.Rows[i].Cells[7].Value);
                        sRtn = GTN.mc.GTN_ArcXYR(core, crd, x, z, radius, circleDir, synVel, synAcc, velEnd, fifo);
                        x += x; z += z;
                        break;
                    case "ArcZXC":
                        x = Convert.ToInt32(dataGridView.Rows[i].Cells[1].Value);
                        z = Convert.ToInt32(dataGridView.Rows[i].Cells[2].Value);
                        xCenter = Convert.ToDouble(dataGridView.Rows[i].Cells[3].Value);
                        yCenter = Convert.ToDouble(dataGridView.Rows[i].Cells[4].Value);
                        circleDir = Convert.ToInt16(dataGridView.Rows[i].Cells[5].Value);
                        synVel = Convert.ToDouble(dataGridView.Rows[i].Cells[6].Value);
                        synAcc = Convert.ToDouble(dataGridView.Rows[i].Cells[7].Value);
                        velEnd = Convert.ToDouble(dataGridView.Rows[i].Cells[8].Value);
                        sRtn = GTN.mc.GTN_ArcXYC(core, crd, x, z, xCenter, yCenter, circleDir, synVel, synAcc, velEnd, fifo);
                        x += x; z += z;
                        break;
                    case "ArcYZR":
                        y = Convert.ToInt32(dataGridView.Rows[i].Cells[1].Value);
                        z = Convert.ToInt32(dataGridView.Rows[i].Cells[2].Value);
                        radius = Convert.ToDouble(dataGridView.Rows[i].Cells[3].Value);
                        circleDir = Convert.ToInt16(dataGridView.Rows[i].Cells[4].Value);
                        synVel = Convert.ToDouble(dataGridView.Rows[i].Cells[5].Value);
                        synAcc = Convert.ToDouble(dataGridView.Rows[i].Cells[6].Value);
                        velEnd = Convert.ToDouble(dataGridView.Rows[i].Cells[7].Value);
                        sRtn = GTN.mc.GTN_ArcXYR(core, crd, y, z, radius, circleDir, synVel, synAcc, velEnd, fifo);
                        y += y; z += z;
                        break;
                    case "ArcYZC":
                        y = Convert.ToInt32(dataGridView.Rows[i].Cells[1].Value);
                        z = Convert.ToInt32(dataGridView.Rows[i].Cells[2].Value);
                        xCenter = Convert.ToDouble(dataGridView.Rows[i].Cells[3].Value);
                        yCenter = Convert.ToDouble(dataGridView.Rows[i].Cells[4].Value);
                        circleDir = Convert.ToInt16(dataGridView.Rows[i].Cells[5].Value);
                        synVel = Convert.ToDouble(dataGridView.Rows[i].Cells[6].Value);
                        synAcc = Convert.ToDouble(dataGridView.Rows[i].Cells[7].Value);
                        velEnd = Convert.ToDouble(dataGridView.Rows[i].Cells[8].Value);
                        sRtn = GTN.mc.GTN_ArcXYC(core, crd, y, z, xCenter, yCenter, circleDir, synVel, synAcc, velEnd, fifo);
                        y += y; z += z;
                        break;
                    case "BufIo":
                        switch (dataGridView.Rows[i].Cells[1].Value.ToString())
                        {
                            case "ENABLE":
                                doType = 10;
                                break;
                            case "CLEAR":
                                doType = 11;
                                break;
                            case "GPO":
                                doType = 12;
                                break;
                        }
                        doMask = Convert.ToUInt16(dataGridView.Rows[i].Cells[2].Value);
                        udoValue = Convert.ToUInt16(dataGridView.Rows[i].Cells[3].Value);
                        sRtn = GTN.mc.GT_BufIO(crd, doType, doMask, udoValue, fifo);
                        break;
                    case "BufDelay":
                        delayTime = Convert.ToUInt32(dataGridView.Rows[i].Cells[1].Value);
                        sRtn = GTN.mc.GT_BufDelay(crd, delayTime, fifo);
                        break;
                    case "BufDA":
                        chn = Convert.ToInt16(dataGridView.Rows[i].Cells[1].Value);
                        doValue = Convert.ToInt16(dataGridView.Rows[i].Cells[2].Value);
                        sRtn = GTN.mc.GT_BufDA(crd, chn, doValue, fifo);
                        break;
                    case "BufMove":
                        moveAxis = Convert.ToInt16(dataGridView.Rows[i].Cells[1].Value);
                        pos = Convert.ToInt32(dataGridView.Rows[i].Cells[2].Value);
                        vel = Convert.ToDouble(dataGridView.Rows[i].Cells[3].Value);
                        acc = Convert.ToDouble(dataGridView.Rows[i].Cells[4].Value);
                        modal = Convert.ToInt16(dataGridView.Rows[i].Cells[5].Value);
                        sRtn = GTN.mc.GT_BufMove(crd, moveAxis, pos, vel, acc, modal, fifo);
                        break;
                    case "BufGear":
                        gearAxis = Convert.ToInt16(dataGridView.Rows[i].Cells[1].Value);
                        pos = Convert.ToInt32(dataGridView.Rows[i].Cells[2].Value);
                        sRtn = GTN.mc.GT_BufGear(crd, gearAxis, pos, fifo);
                        break;
                    case "BufSetStopIo":
                        //sRtn = GTN.mc.GT_BufSetStopIo(crd, gearAxis, pos, fifo);
                        break;
                    case "BufLmtsOn":
                        axis = Convert.ToInt16(dataGridView.Rows[i].Cells[1].Value);
                        limitType = Convert.ToInt16(dataGridView.Rows[i].Cells[2].Value);
                        sRtn = GTN.mc.GT_BufLmtsOn(crd, axis, limitType, fifo);
                        break;
                    case "BufLmtsOff":
                        axis = Convert.ToInt16(dataGridView.Rows[i].Cells[1].Value);
                        limitType = Convert.ToInt16(dataGridView.Rows[i].Cells[2].Value);
                        sRtn = GTN.mc.GT_BufLmtsOff(crd, axis, limitType, fifo);
                        break;
                }
            }
            sRtn = GTN.mc.GTN_CrdStart(core, 1, fifo);
        }
        private void button_STOP_Click(object sender, EventArgs e)//停止运动1~5轴
        {
            core = Convert.ToInt16(this.ComboBox_CORENUM.SelectedIndex + 1);
            for (int i = 1; i <= 5; ++i)
                sRtn = GTN.mc.GTN_Stop(core, 1 << (i - 1), 1);
        }
    }
}


