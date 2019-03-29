// 例程 11-2 电机到位检测功能
#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "gts.h"

#define AXIS_X		1
#define AXIS_Y		2

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
	TPid pid;
	TTrapPrm trap;
	long sts;
	long posX, posY;
	double prfPos, prfVel;
	
	// 打开运动控制器
	sRtn = GT_Open();
	commandhandler("GT_Open", sRtn);
	// 复位控制器
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// 配置运动控制器为伺服模式
	sRtn = GT_LoadConfig("servo.cfg");
	commandhandler("GT_LoadConfig", sRtn);
	// 延时一段时间
	Sleep(100);
	// 清除各轴的报警和限位
	sRtn = GT_ClrSts(1, 8);
	commandhandler("GT_ClrSts", sRtn);
	// 读取X轴PID参数
	sRtn = GT_GetPid(AXIS_X, 1, &pid);
	commandhandler("GT_GetPid", sRtn);
	pid.kp = 10;
	// 更新X轴PID参数
	sRtn = GT_SetPid(AXIS_X, 1, &pid);
	commandhandler("GT_SetPid", sRtn);
	// 读取Y轴PID参数
	sRtn = GT_GetPid(AXIS_Y, 1, &pid);
	commandhandler("GT_GetPid", sRtn);
	pid.kp = 10;
	// 更新Y轴PID参数
	sRtn = GT_SetPid(AXIS_Y, 1, &pid);
	commandhandler("GT_SetPid", sRtn);
	// X轴伺服使能
	sRtn = GT_AxisOn(AXIS_X);
	commandhandler("GT_AxisOn", sRtn);
	// Y轴伺服使能
	sRtn = GT_AxisOn(AXIS_Y);
	commandhandler("GT_AxisOn", sRtn);
	// 延时一段时间，等待伺服稳定
	Sleep(200);
	// 位置清零, 并进行自动零漂补偿
	sRtn = GT_ZeroPos(AXIS_X);
	commandhandler("GT_ZeroPos", sRtn);
	// 设置X轴到位误差带
	sRtn = GT_SetAxisBand(AXIS_X, 20, 5);
	commandhandler("GT_SetAxisBand", sRtn); 
	// 位置清零, 并进行自动零漂补偿
	sRtn= GT_ZeroPos(AXIS_Y);
	commandhandler("GT_ZeroPos", sRtn);
	// 设置Y轴到位误差带
	sRtn = GT_SetAxisBand(AXIS_Y, 20, 5);
	commandhandler("GT_SetAxisBand", sRtn);
	// X轴设为点位模式
	sRtn = GT_PrfTrap(AXIS_X);
	commandhandler("GT_PrfTrap", sRtn);
	// 读取X轴点位运动参数
	sRtn = GT_GetTrapPrm(AXIS_X, &trap);
	commandhandler("GT_GetTrapPrm", sRtn);
	trap.acc = 1;
	trap.dec = 0.5;
	// 设置X轴点位运动参数
	sRtn = GT_SetTrapPrm(AXIS_X, &trap);
	commandhandler("GT_SetTrapPrm", sRtn);
	// 设置X轴的目标速度
	sRtn = GT_SetVel(AXIS_X, 10);
	commandhandler("GT_SetVel", sRtn);
	// Y轴设为点位模式
	sRtn = GT_PrfTrap(AXIS_Y);
	commandhandler("GT_PrfTrap", sRtn);
	// 读取Y轴点位运动参数
	sRtn = GT_GetTrapPrm(AXIS_Y, &trap);
	commandhandler("GT_GetTrapPrm", sRtn);
	trap.acc = 1;
	trap.dec = 0.5;
	// 设置Y轴点位运动参数
	sRtn = GT_SetTrapPrm(AXIS_Y, &trap);
	commandhandler("GT_SetTrapPrm", sRtn);
	// 设置Y轴的目标速度
	sRtn = GT_SetVel(AXIS_Y, 10);
	commandhandler("GT_SetVel", sRtn);

	posX = 10000;
	posY = 20000;
	while(!kbhit())
	{
		// 设置X轴目标位置
		sRtn = GT_SetPos(AXIS_X, posX);
		commandhandler("GT_SetPos", sRtn);
		// 启动X轴的运动
		sRtn = GT_Update(1<<(AXIS_X-1));
		commandhandler("GT_Update", sRtn);

		posX = - posX;

		// 等待X轴进入误差带
		do
		{
		GT_GetSts(AXIS_X, &sts);
		GT_GetPrfPos(AXIS_X, &prfPos);
		GT_GetPrfVel(AXIS_X, &prfVel);
			printf("x pos=%-10.2lf vel=%-6.2lf\r", prfPos, prfVel);
		}while( 0x800 != ( sts & 0x800 ) );

		printf("\n");
		// 设置Y轴目标位置
		sRtn = GT_SetPos(AXIS_Y, posY);
		commandhandler("GT_SetPos", sRtn);
		// 启动Y轴的运动
		sRtn = GT_Update(1<<(AXIS_Y-1));
		commandhandler("GT_Update", sRtn);

		posY = - posY;
		// 等待Y轴进入误差带
		do
		{
		GT_GetSts(AXIS_Y, &sts);
		GT_GetPrfPos(AXIS_Y, &prfPos);
		GT_GetPrfVel(AXIS_Y, &prfVel);
			printf("y pos=%-10.2lf vel=%-6.2lf\r", prfPos, prfVel);
		}while( 0x800 != ( sts & 0x800 ) );
		printf("\n");
	}
	//伺服关闭
	sRtn = GT_AxisOff(AXIS_X);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, AXIS_X);
	sRtn = GT_AxisOff(AXIS_Y);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, AXIS_Y);

	return 0;
}
