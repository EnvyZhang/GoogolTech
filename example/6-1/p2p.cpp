// 例程 6-1 点位运动
#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include "gts.h"

#define AXIS		1

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
	TTrapPrm trap;
	long sts;
	double prfPos;

	// 打开运动控制器
	sRtn = GT_Open();
	// 指令返回值检测
	commandhandler("GT_Open", sRtn);
	// 复位运动控制器
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// 配置运动控制器
	// 注意：配置文件取消了各轴的报警和限位
	sRtn = GT_LoadConfig("test.cfg");
	commandhandler("GT_LoadConfig ", sRtn);
	// 清除各轴的报警和限位
	sRtn = GT_ClrSts(1, 8);
	commandhandler("GT_ClrSts", sRtn);
	// 伺服使能
	sRtn = GT_AxisOn(AXIS);
	commandhandler("GT_AxisOn", sRtn);

	// 位置清零
	sRtn = GT_ZeroPos(AXIS);
	commandhandler("GT_ZeroPos", sRtn);
	// AXIS轴规划位置清零
	sRtn = GT_SetPrfPos(AXIS, 0);
	commandhandler("GT_SetPrfPos", sRtn);
	// 将AXIS轴设为点位模式
	sRtn = GT_PrfTrap(AXIS);
	commandhandler("GT_PrfTrap", sRtn);
	// 读取点位运动参数
	sRtn = GT_GetTrapPrm(AXIS, &trap);
	commandhandler("GT_GetTrapPrm", sRtn);
	trap.acc = 0.25;
	trap.dec = 0.125;
	trap.smoothTime = 25;
	// 设置点位运动参数
	sRtn = GT_SetTrapPrm(AXIS, &trap);
	commandhandler("GT_SetTrapPrm", sRtn);
	// 设置AXIS轴的目标位置
	sRtn = GT_SetPos(AXIS, 50000L);
	commandhandler("GT_SetPos", sRtn);
	// 设置AXIS轴的目标速度
	sRtn = GT_SetVel(AXIS, 50);
	commandhandler("GT_SetVel", sRtn);
	// 启动AXIS轴的运动
	sRtn = GT_Update(1<<(AXIS-1));
	commandhandler("GT_Update", sRtn);

	do
	{
		// 读取AXIS轴的状态
		sRtn = GT_GetSts(AXIS, &sts);
		// 读取AXIS轴的规划位置
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		printf("sts=0x%-10lxprfPos=%-10.1lf\r", sts, prfPos);
	}while(sts&0x400);	// 等待AXIS轴规划停止

	// 伺服关闭
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d\n", sRtn);
	getch();
	return 0;

}

