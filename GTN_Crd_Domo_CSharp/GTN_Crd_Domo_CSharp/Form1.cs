using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace GTN_Crd_Domo_CSharp
{
    public partial class Form1 : Form
    {
        //声明返回值
        public short rtn;

        bool aHead, newAhead, oldAhead, watchOn, axisFlag = false;

        public Form1()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            COMBOBOX_AXISNUM.SelectedIndex = 0;
            BUTTON_INITIAL_COORDINATE.Enabled = false;
            BUTTON_LINEAR_MOTION.Enabled = false;
        }

        private void BUTTON_INITIAL_Click(object sender, EventArgs e)
        {
            short axis = Convert.ToInt16(COMBOBOX_AXISNUM.TabIndex + 1);
            rtn = GTN.mc.GTN_Open(0, 1);
            if (rtn != 0)
            {
                MessageBox.Show("开卡失败");
            }
            rtn = GTN.mc.GTN_Reset(1);
            rtn = GTN.mc.GTN_Reset(2);
            //for (short i = 1; i < 13; i++)
            //{
            //rtn = GTN.mc.GTN_LmtsOff(1, 1, i);
            //rtn = GTN.mc.GTN_AlarmOff(1, 1);
            //rtn = GTN.mc.GTN_LmtsOff(1, 2, i);
            //rtn = GTN.mc.GTN_AlarmOff(1, 2);
            //}
            rtn = GTN.mc.GTN_LoadConfig(1, "gtn_core1.cfg");
            if (rtn != 0)
            {
                MessageBox.Show("加载核1配置文件失败");
            }

            rtn = GTN.mc.GTN_LoadConfig(2, "gtn_core2.cfg");
            if (rtn != 0)
            {
                MessageBox.Show("加载核2配置文件失败");
            }

            rtn = GTN.mc.GTN_ClrSts(1, axis, 12);
            rtn = GTN.mc.GTN_ClrSts(2, axis, 12);
            rtn = GTN.mc.GTN_ZeroPos(1, axis, 12);
            rtn = GTN.mc.GTN_ZeroPos(2, axis, 12);

            BUTTON_INITIAL_COORDINATE.Enabled = true;
            textBox_SetExtAo.Text =Convert.ToString(5);
        }

        private void BUTTON_INITIAL_COORDINATE_Click(object sender, EventArgs e)
        {
            GTN.mc.TCrdPrm crdprm1;

            crdprm1.dimension = 3;//坐标系的维数为4维
            crdprm1.synVelMax = 500;//最大合成速度为500
            crdprm1.synAccMax = 100;//最大合成加速度为100
            crdprm1.evenTime = 10;//最小匀速时间为50ms
            crdprm1.profile1 = 1;//规划器1对应X轴
            crdprm1.profile2 = 2;//规划器2对应Y轴
            crdprm1.profile3 = 3;//规划器3对应Z轴
            crdprm1.profile4 = 0;//规划器2对应A轴
            crdprm1.profile5 = 0;//规划器1对应X轴
            crdprm1.profile6 = 0;//规划器2对应Y轴
            crdprm1.profile7 = 0;//规划器3对应Z轴
            crdprm1.profile8 = 0;//规划器2对应A轴
            crdprm1.setOriginFlag = 1;//1表示需要用户指定坐标原点的规划位置
            crdprm1.originPos1 = 0;//1轴的规划位置为0
            crdprm1.originPos2 = 0;//2轴的规划位置为0
            crdprm1.originPos3 = 0;//3轴的规划位置为0
            crdprm1.originPos4 = 0;//2轴的规划位置为0
            crdprm1.originPos5 = 0;//1轴的规划位置为0
            crdprm1.originPos6 = 0;//2轴的规划位置为0
            crdprm1.originPos7 = 0;//3轴的规划位置为0
            crdprm1.originPos8 = 0;//2轴的规划位置为0

            rtn = GTN.mc.GTN_SetCrdPrm(1, 1, ref crdprm1);//建立1号坐标系

            BUTTON_LINEAR_MOTION.Enabled = true;
        }

        private void BUTTON_LINEAR_MOTION_Click(object sender, EventArgs e)
        {
            short rtn;
            short core = 1;
            if (aHead == false)//aHead为假执行老前瞻插补，单位为步长（pulse），速度（pulse/ms），加速度（pulse/ms^2)
            {
                System.IntPtr[] pCrdData = new IntPtr[200];
                rtn = GTN.mc.GTN_LnXY(core, 1, 0, 20000, 10, 0.1, 0, 0);								 //压入第一段位置指令 
                rtn = GTN.mc.GTN_LnXY(core, 1, 20000, 20000, 10, 0.1, 0, 0);                           //压入第二段位置指令 
                rtn = GTN.mc.GTN_LnXY(core, 1, 20000, 0, 10, 0.1, 0, 0);								 //压入第三段位置指令  
                rtn = GTN.mc.GTN_LnXY(core, 1, 0, 0, 10, 0.1, 0, 0);									//压入第四段位置指令
                rtn = GTN.mc.GTN_CrdData(core, 1, pCrdData[0], 0);											//将前瞻缓存区中的数据压入控制器
            } else if (aHead == true)//aHead为真则执行新前瞻插补，单位为步长（mm），速度（mm/s），加速度（mm/s^2)
            {
                System.IntPtr[] pCrdData = new IntPtr[200];
                rtn = gts.mc_la.GT_LnXYEx(1, 0, 20, 10, 100, 0, 0, 0);								 //压入第一段位置指令 
                rtn = gts.mc_la.GT_LnXYEx(1, 20, 20, 10, 100, 0, 0, 0);								//压入第二段位置指令 
                rtn = gts.mc_la.GT_LnXYEx(1, 20, 0, 10, 100, 0, 0, 0);								 //压入第三段位置指令  
                rtn = gts.mc_la.GT_LnXYEx(1, 0, 0, 10, 100, 0, 0, 0);									//压入第四段位置指令
                rtn = gts.mc_la.GT_CrdDataEx(1, pCrdData[0], 0);											//将前瞻缓存区中的数据压入控制器
            }
            rtn = GTN.mc.GTN_CrdStart(1, 1, 0);														//启动插补运动
        }

        private void BUTTON_CLOSE_Click(object sender, EventArgs e)
        {
            rtn = GTN.mc.GTN_Stop(1, 0xFFF, 0xFFF); 
        }

        private void BUTTON_PTP_Click(object sender, EventArgs e)
        {
            short axis = Convert.ToInt16(COMBOBOX_AXISNUM.TabIndex + 1);
            GTN.mc.TTrapPrm trap;

            rtn = GTN.mc.GTN_PrfTrap(1, axis);
            rtn = GTN.mc.GTN_GetTrapPrm(1, axis, out trap);
            trap.acc = 0.5;
            trap.dec = 0.5;
            trap.smoothTime = 50;
            rtn = GTN.mc.GTN_SetTrapPrm(1, axis, ref trap);
            rtn = GTN.mc.GTN_SetVel(1, axis, 50);
            rtn = GTN.mc.GTN_SetPos(1, axis, 100000);
            rtn = GTN.mc.GTN_Update(1, 1 << (axis - 1));
        }

        private void BUTTON_HOME_Click(object sender, EventArgs e)
        {
            //程序演示了对第一个轴进行回原点的操作，用户可以同时完成多个轴的回原点操作。
            short axis = Convert.ToInt16(COMBOBOX_AXISNUM.TabIndex + 1);
            GTN.mc.THomePrm homeprm;
            rtn = GTN.mc.GTN_AxisOn(1, axis);
            rtn = GTN.mc.GTN_GetHomePrm(1, axis, out homeprm);//获取当前轴的回原点的参数
            homeprm.mode = 20;//home回原点模式
            homeprm.moveDir = 1;//1：正方向，-1：负方向
            homeprm.indexDir = 1;//1：正方向，-1：负方向
            homeprm.edge = 0;//设置捕获沿：0-下降沿，1-上升沿
            homeprm.velHigh = 5;
            homeprm.velLow = 1;
            homeprm.acc = 0.5;
            homeprm.dec = 0.5;
            homeprm.homeOffset = 0;//最终的停止位置相对于原点的偏移量
            homeprm.searchHomeDistance = 0;//Home最大搜索距离，0表示不限制搜索距离
            homeprm.searchIndexDistance = 30000;//Index最大搜索距离，0表示不限制搜索距离
            homeprm.escapeStep = 0;//采用限位回原点时，反方向离开限位的脱离步长

            rtn = GTN.mc.GTN_GoHome(1, axis, ref homeprm);//启动快速回原点
        }

        private void BUTTON_NJOG_MouseDown(object sender, MouseEventArgs e)
        {
            short axis = Convert.ToInt16(COMBOBOX_AXISNUM.SelectedIndex + 1);
            GTN.mc.TJogPrm jog;
            rtn = GTN.mc.GTN_PrfJog(1, axis);
            rtn = GTN.mc.GTN_GetJogPrm(1, axis, out jog);
            jog.acc = 0.5;
            jog.dec = 0.5;
            // 设置 Jog 运动参数
            rtn = GTN.mc.GTN_SetJogPrm(1, axis, ref jog);
            rtn = GTN.mc.GTN_SetVel(1, axis, -200);
            rtn = GTN.mc.GTN_Update(1, 1 << (axis - 1));
        }

        private void BUTTON_NJOG_MouseUp(object sender, MouseEventArgs e)
        {
            rtn = GTN.mc.GTN_Stop(1, 0xff, 0xff);
        }

        private void BUTTON_PJOG_MouseDown(object sender, MouseEventArgs e)
        {
            short axis = Convert.ToInt16(COMBOBOX_AXISNUM.SelectedIndex + 1);
            GTN.mc.TJogPrm jog;
            rtn = GTN.mc.GTN_PrfJog(1, axis);
            rtn = GTN.mc.GTN_GetJogPrm(1, axis, out jog);
            jog.acc = 0.5;
            jog.dec = 0.5;
            // 设置 Jog 运动参数
            rtn = GTN.mc.GTN_SetJogPrm(1, axis, ref jog);
            rtn = GTN.mc.GTN_SetVel(1, axis, 200);
            rtn = GTN.mc.GTN_Update(1, 1 << (axis - 1));
        }
        
        private void button_SetDoEx_Click(object sender, EventArgs e)
        {
            int pOutput = Convert.ToInt32(textBox_Output.Text);
            rtn = GTN.mc.GTN_SetDoEx(1, GTN.mc.MC_GPO, ref pOutput, 1);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            short rtn;
            double pvalue = Convert.ToDouble(textBox_SetExtAo.Text);
            rtn = GTN.mc.GTN_ExtModuleInit(1,1);//初始化扩展模块
            rtn = GTN.mc.GTN_SetExtAo(1, 1, ref pvalue, 1);//设置核1第1路AO为5v
        }

        private void BUTTON_PJOG_MouseUp(object sender, MouseEventArgs e)
        {
            rtn = GTN.mc.GTN_Stop(1, 0xff, 0xff);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            short run;
            int segment;
            int space;
            UInt32 pClock;
            double[] prfPos = new double[3];
            int[] sts = new int[6];
            GTN.mc.THomeStatus homests;

            rtn = GTN.mc.GTN_GetPrfPos(1, 1, out prfPos[0], 3, out pClock);       // 读1~3轴的规划位置
            rtn = GTN.mc.GT_CrdStatus(1, out run, out segment, 0);               // 读取坐标系运动状态
            rtn = GTN.mc.GTN_GetHomeStatus(1, 1, out homests);
            rtn = GTN.mc.GTN_CrdSpace(1, 1, out space, 0);
            //rtn = GTN.mc.GTN_GetSts(1, 1, out sts[0], 6, out pClock);
            //rtn = GTN.mc.GTN_GetUserSegNum(1, 1, out segment, 0);

            this.textBox_PrfPos1.Text = Math.Round(prfPos[0], 1).ToString();
            this.textBox_PrfPos2.Text = Math.Round(prfPos[1], 1).ToString();
            this.textBox_PrfPos3.Text = Math.Round(prfPos[2], 1).ToString();
            if (run == 0) { this.textBox_CrdStatus.Text = "静止"; }
            else { this.textBox_CrdStatus.Text = "运动"; }
            this.textBox_Segment.Text = Math.Round(segment * 1.00, 1).ToString();

            int[] pIntput = new int[2];                                           //声明一个长度为2的数组
            rtn = GTN.mc.GTN_GetDiEx(1, GTN.mc.MC_GPI, out pIntput[0], 2);        //当一个核中的DI数量大于32时，要将Count增加，Count数量取决于DI数
            this.textBox_GetDiEx1.Text = Convert.ToString(pIntput[0], 2);         //以2进制显示第一组di 
            this.textBox_GetDiEx2.Text = Convert.ToString(pIntput[1], 2);         //超过32位的di在第二个数组中显示
                                                                              
            double poutval, pinval;
            rtn = GTN.mc.GTN_GetExtAo(1, 1, out poutval, 1);                    //读取核1第1路AO
            rtn = GTN.mc.GTN_GetExtAi(1, 1, out pinval, 1);                     //读取核1第1路AI
            this.textBox_GetExtAo.Text = Math.Round(poutval, 1).ToString();
            this.textBox_GetExtAi.Text = Math.Round(pinval, 1).ToString();
        }

        private void radOldahead_CheckedChanged(object sender, EventArgs e)
        {
            if (radOldahead.Checked) //当单选框选中
            {
                if (oldAhead == false)  //判断状态，保证只建立一次前瞻
                {
                    GTN.mc.TCrdData[] crdData = new GTN.mc.TCrdData[200];// 定义前瞻缓存区内存区
                    rtn = GTN.mc.GTN_InitLookAhead(1, 1, 0, 5, 1, 200, ref crdData[0]);// 初始化坐标系1的FIFO0的前瞻模块
                    if (rtn == 0)
                    {
                        aHead = false;
                        oldAhead = true;//指令执行成功，标志位置起
                    } else
                    {
                        MessageBox.Show("前瞻初始化错误：" + rtn.ToString());
                        radOldahead.Checked = false;
                    }
                }
            } else if (radOldahead.Checked == false && oldAhead == false)
            {
                MessageBox.Show("前瞻已建立");
            }
        }
                    
        private void IDC_radNewahead_CheckedChanged(object sender, EventArgs e)
        {
            short core = 1;
            short crd = 1;
            short fifo = 0;
            int lookAheadNum = 200;
            //*****************************************************新前瞻标准使用方法*************************************************************
	        //初始化多轴前瞻模块
            if (radNewahead.Checked)
            {
                if (newAhead == false)
                {
                    gts.mc_la.EMachineMode machineMode; //机床类型
                    gts.mc_la.EVelSettingDef velDefineMode; //速度定义模式
                    int[] axisLimitMode = new int[8]; //轴限制模式
                    gts.mc_la.EWorkLimitMode workLimitMode;  //工件坐标系限制模式
                    int[] axisFollowMode = new int[8]; //轴跟随模式
                    gts.mc_la.TLookAheadParameter lookAheadPara;  //前瞻参数

                    machineMode = gts.mc_la.EMachineMode.NORMAL_THREE_AXIS; //标准三轴机床
                    velDefineMode = gts.mc_la.EVelSettingDef.NORMAL_DEF_VEL; //输入速度为三轴合成速度
                    workLimitMode = gts.mc_la.EWorkLimitMode.WORK_LIMIT_VALID; //工件坐标系限制生效
                    for (int i = 0; i < 8; ++i)
                    {
                        axisLimitMode[i] = gts.mc_la.AXIS_LIMIT_NONE; //轴限制不生效
                        axisFollowMode[i] = 0; //非跟随轴
                    }

                    lookAheadPara.lookAheadNum = lookAheadNum;
                    lookAheadPara.time = 1;//时间常数
                    lookAheadPara.radiusRatio = 50;//曲率参数
                    lookAheadPara.machineCfgFileName = "";
                    
                        lookAheadPara.vMax1 = 5000;	//轴最大速度限制
                        lookAheadPara.aMax1 = 100;//轴最大加速度限制
                        lookAheadPara.DVMax1 = 500;//轴跳变速度限制
                        lookAheadPara.axisRelation1 = 1;	//坐标系轴与前瞻轴一一映射
                        lookAheadPara.scale1 = 1000;	//脉冲当量

                        lookAheadPara.vMax2 = 5000;	//轴最大速度限制
                        lookAheadPara.aMax2 = 100;//轴最大加速度限制
                        lookAheadPara.DVMax2 = 500;//轴跳变速度限制
                        lookAheadPara.axisRelation2 = 2;	//坐标系轴与前瞻轴一一映射
                        lookAheadPara.scale2 = 1000;	//脉冲当量

                        lookAheadPara.vMax3 = 5000;	//轴最大速度限制
                        lookAheadPara.aMax3= 100;//轴最大加速度限制
                        lookAheadPara.DVMax3 = 500;//轴跳变速度限制
                        lookAheadPara.axisRelation3 = 3;	//坐标系轴与前瞻轴一一映射
                        lookAheadPara.scale3 = 1000;	//脉冲当量

                        lookAheadPara.vMax4 = 5000;	//轴最大速度限制
                        lookAheadPara.aMax4 = 100;//轴最大加速度限制
                        lookAheadPara.DVMax4 = 500;//轴跳变速度限制
                        lookAheadPara.axisRelation4 = 4;	//坐标系轴与前瞻轴一一映射
                        lookAheadPara.scale4 = 1000;	//脉冲当量

                        lookAheadPara.vMax5 = 5000;	//轴最大速度限制
                        lookAheadPara.aMax5 = 100;//轴最大加速度限制
                        lookAheadPara.DVMax5 = 500;//轴跳变速度限制
                        lookAheadPara.axisRelation5 = 5;	//坐标系轴与前瞻轴一一映射
                        lookAheadPara.scale5 = 1000;	//脉冲当量

                        lookAheadPara.vMax6 = 5000;	//轴最大速度限制
                        lookAheadPara.aMax6 = 100;//轴最大加速度限制
                        lookAheadPara.DVMax6 = 500;//轴跳变速度限制
                        lookAheadPara.axisRelation6 = 6;	//坐标系轴与前瞻轴一一映射
                        lookAheadPara.scale6 = 1000;	//脉冲当量

                        lookAheadPara.vMax7 = 5000;	//轴最大速度限制
                        lookAheadPara.aMax7 = 100;//轴最大加速度限制
                        lookAheadPara.DVMax7 = 500;//轴跳变速度限制
                        lookAheadPara.axisRelation7 = 7;	//坐标系轴与前瞻轴一一映射
                        lookAheadPara.scale7 = 1000;	//脉冲当量

                        lookAheadPara.vMax8 = 5000;	//轴最大速度限制
                        lookAheadPara.aMax8 = 100;//轴最大加速度限制
                        lookAheadPara.DVMax8 = 500;//轴跳变速度限制
                        lookAheadPara.axisRelation8 = 8;	//坐标系轴与前瞻轴一一映射
                        lookAheadPara.scale8 = 1000;	//脉冲当量

                    rtn = gts.mc_la.GT_SetupLookAheadCrd(crd, machineMode);//设置机床模式
                    //rtn += gts.mc_la.GT_SetAxisFollowModeLa(crd, axisFollowMode);//设置跟随模式
                    rtn += gts.mc_la.GT_SetAxisLimitModeLa( crd, ref axisLimitMode[0]);//设置轴限制模式
                    rtn += gts.mc_la.GT_SetAxisVelValidModeLa(crd, 0xF);//设置轴速度有效，按位设置，0xF表示前4个轴
                    gts.mc_la.TPreStartPos pPreStartPos;
                    pPreStartPos.Pos1 = 0;
                    pPreStartPos.Pos2 = 0;
                    pPreStartPos.Pos3 = 0;
                    pPreStartPos.Pos4 = 0;
                    pPreStartPos.Pos5 = 0;
                    pPreStartPos.Pos6 = 0;
                    pPreStartPos.Pos7 = 0;
                    pPreStartPos.Pos8 = 0;
                    rtn += gts.mc_la.GT_InitLookAheadEx(crd, ref lookAheadPara, fifo, 0, ref pPreStartPos); //设置前瞻参数（需要放在最后设置）
                    if (rtn == 0)
                    {
                        aHead = true;
                        newAhead = true;
                    }
                    else
                    {
                        MessageBox.Show("新前瞻初始化错误：" + rtn.ToString());
                        radNewahead.Checked=false;
                    }
                }
            } else if (radNewahead.Checked == false && newAhead == true)
            {
                MessageBox.Show("新前瞻已建立");
            }

        }

    }
}
