// 例程 6-19 Percent描述方式
#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "gts.h"

#define AXIS_X		1
#define AXIS_Y		2
#define TABLE_X		1
#define TABLE_Y		2
#define LOOP_COUNT	2


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
	short sRtn;
	long mask;
	// X轴的数据点参数
	double time_x[7] = {0, 1000, 2000, 3000, 4000, 5000, 6000};
	double pos_x[7] = {0, 5000, 15000, 20000, 15000, 5000, 0};
	double percent_x[7] = {60, 0, 60, 60, 0, 60, 0};
	// Y轴的数据点参数
	double time_y[5] = {2000, 2500, 3500, 4000, 5000};
	double pos_y[5] = {0, 2500, 12500, 15000, 15000};
	double percent_y[5] = {60, 0, 60, 0, 0};
	double prfVel[2], prfPos[2], time[2];
	short tableId[2];
	
	
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
	sRtn = GT_AxisOn(AXIS_X);
	commandhandler("GT_AxisOn", sRtn);
	sRtn = GT_AxisOn(AXIS_Y);
	commandhandler("GT_AxisOn", sRtn);
	// 等待伺服使能就绪
	Sleep(1000);
	// 将X轴设置为PVT模式
	sRtn = GT_PrfPvt(AXIS_X);
	commandhandler("GT_PrfPvt", sRtn);
	// 将Y轴设置为PVT模式
	sRtn = GT_PrfPvt(AXIS_Y);
	commandhandler("GT_PrfPvt", sRtn);
	// 向X轴的数据表发送数据
	sRtn = GT_PvtTablePercent(TABLE_X, 7, &time_x[0], &pos_x[0], &percent_x[0], 0);
	commandhandler("GT_PvtTablePercent", sRtn);
	// 向Y轴的数据表发送数据
	sRtn = GT_PvtTablePercent(TABLE_Y, 5, &time_y[0], &pos_y[0], &percent_y[0], 0);
	commandhandler("GT_PvtTablePercent", sRtn);
	// X轴选择数据表TABLE_X
	sRtn = GT_PvtTableSelect(AXIS_X, TABLE_X);
	commandhandler("GT_PvtTableSelect", sRtn);
	// Y轴选择数据表TABLE_Y
	sRtn = GT_PvtTableSelect(AXIS_Y, TABLE_Y);
	commandhandler("GT_PvtTableSelect", sRtn);
	// 设置循环次数
	sRtn = GT_SetPvtLoop(AXIS_X, LOOP_COUNT);
	commandhandler("GT_SetPvtLoop", sRtn);
	// 设置循环次数
	sRtn = GT_SetPvtLoop(AXIS_Y, 2*LOOP_COUNT-1);
	commandhandler("GT_SetPvtLoop", sRtn);
	// 同时启动X轴和Y轴
	// 由于Y轴的第1个数据点时间为2000ms
	// 因此X轴启动2000ms以后，Y轴才开始运动
	mask = 1<<(AXIS_X-1);
	mask |= 1<<(AXIS_Y-1);
	sRtn = GT_PvtStart(mask);
	commandhandler("GT_PvtStart", sRtn);

	while(!kbhit())
	{
		// 读取数据表和运动时间
		sRtn = GT_PvtStatus(AXIS_X, &tableId[0], &time[0]);
		sRtn = GT_PvtStatus(AXIS_Y, &tableId[1], &time[1]);
		// 读取规划速度
		sRtn = GT_GetPrfVel(AXIS_X, &prfVel[0]);
		sRtn = GT_GetPrfVel(AXIS_Y, &prfVel[1]);
		// 读取规划位置
		sRtn = GT_GetPrfPos(AXIS_X, &prfPos[0]);
		sRtn = GT_GetPrfPos(AXIS_Y, &prfPos[1]);
		printf("x:%2d %10.0lf %10.2lf %10.1lf y:%2d %10.0lf %10.2lf %10.1lf\r", 
			tableId[0], time[0], prfVel[0], prfPos[0], tableId[1], time[1], prfVel[1], prfPos[1]);
	}
	// 伺服关闭
	sRtn = GT_AxisOff(AXIS_X);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, AXIS_X);
	sRtn = GT_AxisOff(AXIS_Y);
	printf("GT_AxisOff()=%d, Axis:%d\n", sRtn, AXIS_Y);
	getch();
	return 0;
}
