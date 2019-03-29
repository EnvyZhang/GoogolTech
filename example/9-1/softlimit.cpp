// 例程 9-1 软限位使用
#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include "gts.h"

#define AXIS		1

int main(int argc, char* argv[])
{
	// 指令返回值
	short sRtn;
	// 轴状态变量
	long sts;
	// 点位运动结构体变量
	TTrapPrm trap;
	// 规划位置
	double prfPos;

	// 打开运动控制器
	sRtn = GT_Open();
	// 复位
	sRtn = GT_Reset();
	// 控制器配置
	sRtn = GT_LoadConfig("test.cfg");
	// 清除轴状态
	sRtn = GT_ClrSts(1, 8);
	// 设置软限位
	sRtn = GT_SetSoftLimit(AXIS, 20000, -20000);
	// 将第一轴设置为点位运动模式
	sRtn = GT_PrfTrap(AXIS);
	// 设置点位运动参数
	sRtn = GT_GetTrapPrm(AXIS, &trap);
	trap.acc = 0.125;
	trap.dec = 0.125;
	sRtn = GT_SetTrapPrm(AXIS, &trap);
	// 设置点位运动目标速度
	sRtn = GT_SetVel(AXIS, 50);
	// 设置点位运动目标位置
	sRtn = GT_SetPos(AXIS, 1000000L);
	// 启动点位运动
	sRtn = GT_Update(1<<(AXIS-1));

	while(!kbhit())
	{
		// 读取第一轴轴状态
		sRtn = GT_GetSts(AXIS, &sts);
		// 读取第一轴规划位置
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		printf("sts=0x%-8lx prfPos=%-10.2lf\r", sts, prfPos);
	}
	return 0;
}


