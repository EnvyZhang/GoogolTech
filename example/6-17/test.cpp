// 例程 6-17 PVT描述方式
#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "gts.h"

#define AXIS				1
#define TABLE				1

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
	double time[6]={0, 1200, 2000, 3000, 3800, 5000};
	double pos[6]={0, 9750, 24483, 44483, 59216, 68966};
	double vel[6]={1, 15.25, 20, 20, 15.25, 1};
	double prfVel, prfPos, t;
	short tableId;

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
	// 发送数据
	sRtn = GT_PvtTable(TABLE, 6, &time[0], &pos[0], &vel[0]);
	commandhandler("GT_PvtTable", sRtn);
	// 选择数据表
	sRtn = GT_PvtTableSelect(AXIS, TABLE);
	commandhandler("GT_PvtTableSelect", sRtn);
	mask = 1<<(AXIS-1);
	sRtn = GT_PvtStart(mask);
	commandhandler("GT_PvtStart", sRtn);
	while(!kbhit())
	{
		// 读取数据表和运动时间
		sRtn = GT_PvtStatus(AXIS, &tableId, &t);
		// 读取规划速度
		sRtn = GT_GetPrfVel(AXIS, &prfVel);
		// 读取规划位置
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		printf("%2d %10.0lf %10.2lf %10.1lf\r", tableId, t, prfVel, prfPos);
	}
	// 伺服关闭
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d\n", sRtn);
	getch();
	return 0;


}
