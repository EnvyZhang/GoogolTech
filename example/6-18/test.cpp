// 例程 6-18 Complete描述方式
#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "math.h"
#include "stdlib.h"
#include "gts.h"

#define AXIS		1
#define TABLE1		1
#define TABLE2		2
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

void Calculate(double amplitude, long n, double *pTime, double *pPos)
{
	long i;
	for(i=0;i<n;++i)
	{
		pPos[i] = amplitude*sin(PI/2000*pTime[i])*sin(PI/2000*pTime[i]);
	}
}

int main(int argc, char* argv[])
{
	short sRtn;
	long mask;
	// X轴的数据点参数
	double time[5]={0, 500, 1000, 1500, 2000};
	double pos[5];
	double a[5], b[5], c[5];
	double prfVel, prfPos, t;
	short tableId;
	double amplitude = 40000;
	short table = TABLE1;
	char key;

	// 打开运动控制器
	sRtn = GT_Open();
	commandhandler("GT_Open", sRtn);
	// 复位运动控制器
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// 配置运动控制器
	// 注意：配置文件取消了各轴的报警和限位
	sRtn = GT_LoadConfig("test.cfg");
	commandhandler("GT_LoadConfig", sRtn);
	// 清除各轴报警和限位
	sRtn = GT_ClrSts(1, 8);
	commandhandler("GT_ClrSts", sRtn);
	sRtn = GT_AxisOn(AXIS);
	commandhandler("GT_AxisOn", sRtn);
	// 等待伺服使能就绪
	Sleep(1000);
	// 设置为PVT模式
	sRtn = GT_PrfPvt(AXIS);
	commandhandler("GT_PrfPvt", sRtn);
	Calculate(amplitude, 5, &time[0], &pos[0]);
	// 发送数据
	sRtn = GT_PvtTableComplete(table, 5, &time[0], &pos[0], &a[0], &b[0], &c[0], 0, 0);
	commandhandler("GT_PvtTableComplete", sRtn);
	// 选择数据表
	sRtn = GT_PvtTableSelect(AXIS, table);
	commandhandler("GT_PvtTableSelect", sRtn);
	// 设置为循环执行
	sRtn = GT_SetPvtLoop(AXIS, 0);
	commandhandler("GT_SetPvtLoop", sRtn);
	mask = 1<<(AXIS-1);
	sRtn = GT_PvtStart(mask);
	commandhandler("GT_PvtStart", sRtn);

	while(1)
	{
		// 读取数据表和运动时间
		sRtn = GT_PvtStatus(AXIS, &tableId, &t);
		// 读取规划速度
		sRtn = GT_GetPrfVel(AXIS, &prfVel);
		// 读取规划位置
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		if( kbhit() )
		{
			key = getch();
			if( 'A' == toupper(key) )
			{
				amplitude *= 1.5;
			}
			if( 'B' == toupper(key) )
			{
				amplitude *= 0.5;	
			}
			if( ( 'A' == toupper(key) ) || ( 'B' == toupper(key) ) )
			{
				Calculate(amplitude, 5, &time[0], &pos[0]);
				table = TABLE1 + TABLE2 - tableId;
				// 发送数据
				sRtn = GT_PvtTableComplete(table, 5, &time[0], &pos[0], &a[0], 
						&b[0], &c[0], 0, 0);
				if( 0 != sRtn )
				{
					commandhandler("GT_PvtTableComplete", sRtn);
					exit(0);
				}
				// 选择数据表
				sRtn = GT_PvtTableSelect(AXIS, table);
				if( 0 != sRtn )
				{
					commandhandler("\nGT_PvtTableSelect", sRtn);
					exit(0);
				}
			}

			if( 'Q' == toupper(key) )
			{
				mask = 1 << (AXIS-1);
				GT_Stop(mask, 0);
				exit(0);
			}
		}
		printf("%2d %10.0lf %10.2lf %10.1lf\r", tableId, t, prfVel, prfPos);
	}
	// 伺服关闭
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d\n", sRtn);
	getch();
	return 0;
}
