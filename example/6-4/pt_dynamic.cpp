// 例程 6-4 PT动态FIFO
#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include "math.h"
#include "gts.h"

#define AXIS		1

#define A			50				// 幅值
#define T			1				// 周期
#define DELTA		0.016			// 时间分段
#define LOOP		2				// 循环次数

#define PI			3.1415926

// 该函数检测某条GT指令的执行结果，command为指令名称，error为指令执行返回值
void commandhandler(char *command, short error)
{
	// 如果指令执行返回值为非0，说明指令执行错误，向屏幕输出错误结果
	if(error)
	{
		printf("%s = %d\n", command, error);
	}
}

int main(int argc, char* argv[])
{
	short sRtn, space;
	double pos, vel, velPre, time;
	long sts;
	double prfPos, prfVel;
	short start, loop;

	// 打开运动控制器
	sRtn = GT_Open();
	// 指令返回值检测
	commandhandler("GT_Open", sRtn);
	// 配置运动控制器
	// 注意：配置文件取消了各轴的报警和限位
	sRtn = GT_LoadConfig("test.cfg");
	commandhandler("GT_LoadConfig", sRtn);
	// 清除各轴的报警和限位
	sRtn = GT_ClrSts(1, 8);
	commandhandler("GT_ClrSts", sRtn);
	// 伺服使能
	sRtn = GT_AxisOn(AXIS);
	commandhandler("GT_AxisOn", sRtn);
	// 位置清零
	sRtn = GT_ZeroPos(AXIS);
	commandhandler("GT_ZeroPos", sRtn);
	// 将AXIS轴设为PT模式
	sRtn = GT_PrfPt(AXIS, PT_MODE_DYNAMIC);
	commandhandler("GT_PrfPt", sRtn);
	// 清空AXIS轴的FIFO
	sRtn = GT_PtClear(AXIS);
	commandhandler("GT_PtClear", sRtn);
	pos = 0;
	vel = velPre = 0;
	time = 0;
	start = 0;
	loop = 1;
	while(1)
	{
		// 查询PT模式FIFO的剩余空间
		sRtn = GT_PtSpace(AXIS, &space);
		if( space > 0 )
		{
			time += DELTA;
			// 计算段末速度
			vel = A*sin((2*PI)/T*time);
			// 计算段内位移
			pos += 1000*(vel+velPre)*DELTA/2;
			velPre = vel;
			if(time < loop*T)
			{
				// 发送新数据
				sRtn = GT_PtData(AXIS, pos, (long)(time*1000));
				if( 0 != sRtn )
				{
					printf("\nGT_PtData()=%d\n", sRtn);
					getch();
					return 1;
				}
			}
			else
			{
				// 发送终点数据
				sRtn = GT_PtData(AXIS, 0, loop*T*1000, PT_SEGMENT_STOP);
				if( 0 != sRtn )
				{
					printf("\nGT_PtData()=%d\n", sRtn);
					getch();
					return 1;
				}
				pos = 0;
				time = loop*T;
				velPre = 0;
				++loop;
				if( loop > LOOP )
				{
					break;
				}
			}
		}
		else if( 0 == start )
		{
			// 启动PT运动
			sRtn = GT_PtStart(1<<(AXIS-1));
			commandhandler("GT_PtStart", sRtn);
			start = 1;
		}
		// 读取AXIS轴的状态
		sRtn = GT_GetSts(AXIS, &sts);
		// 读取AXIS轴的规划位置
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		// 读取AXIS轴的规划速度
		sRtn = GT_GetPrfVel(AXIS, &prfVel);
		printf("sts=0x%-10lxprfVel=%-10.2lfprfPos=%-10.1lf\r", sts, prfVel, prfPos);
	}

	while(!kbhit())
	{
		// 读取AXIS轴的状态
		sRtn = GT_GetSts(AXIS, &sts);
		// 读取AXIS轴的规划位置
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		// 读取AXIS轴的规划速度
		sRtn = GT_GetPrfVel(AXIS, &prfVel);
		printf("sts=0x%-10lxprfVel=%-10.2lfprfPos=%-10.1lf\r", sts, prfVel, prfPos);
	}
	// 伺服关闭
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d\n", sRtn);
	getch();
	return 0;
}

