// 例程 8-2 Home回原点
#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "gts.h"

#define AXIS			1

#define SEARCH_HOME		-200000
#define HOME_OFFSET		-2000


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
	short sRtn, capture;
	TTrapPrm trapPrm;
	long status, pos;
	double prfPos, encPos, axisPrfPos, axisEncPos;
	// 打开运动控制器
	sRtn = GT_Open();
	commandhandler("GT_Open", sRtn);
	// 复位运动控制器
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// 配置运动控制器
	// 注意：配置文件test.cfg取消了各轴的报警和限位
	sRtn = GT_LoadConfig("test.cfg");
	commandhandler("GT_LoadConfig", sRtn);
	// 清除指定轴的报警和限位
	sRtn = GT_ClrSts(AXIS);
	commandhandler("GT_ClrSts", sRtn);
	// 驱动器使能
	sRtn = GT_AxisOn(AXIS);
	commandhandler("GT_AxisOn", sRtn);
	// 启动Home捕获
	sRtn = GT_SetCaptureMode(AXIS, CAPTURE_HOME);
	commandhandler("GT_SetCaptureMode", sRtn);
	// 切换到点位运动模式
	sRtn = GT_PrfTrap(AXIS);
	commandhandler("GT_PrfTrap", sRtn);
	// 读取点位模式运动参数
	sRtn = GT_GetTrapPrm(AXIS, &trapPrm);
	commandhandler("GT_GetTrapPrm", sRtn);
	trapPrm.acc = 0.25;
	trapPrm.dec = 0.25;
	// 设置点位模式运动参数
	sRtn = GT_SetTrapPrm(AXIS, &trapPrm);
	commandhandler("GT_SetTrapPrm", sRtn);
	// 设置点位模式目标速度，即回原点速度
	sRtn = GT_SetVel(AXIS, 10);
	commandhandler("GT_SetVel", sRtn);
	// 设置点位模式目标位置，即原点搜索距离
	sRtn = GT_SetPos(AXIS, SEARCH_HOME);
	commandhandler("GT_SetPos", sRtn);
	// 启动运动
	sRtn = GT_Update(1<<(AXIS-1));
	commandhandler("GT_Update", sRtn);
	printf("\nWaiting for home signal...\n");
	do
	{
		// 读取轴状态
		sRtn = GT_GetSts(AXIS, &status);
		// 读取捕获状态
		sRtn = GT_GetCaptureStatus(AXIS, &capture, &pos);
		// 读取规划位置
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		// 读取编码器位置
		sRtn = GT_GetEncPos(AXIS, &encPos);
		printf("capture=%d prfPos=%.2lf encPos=%.2lf\r", capture, prfPos, encPos);
		// 如果运动停止，返回出错信息
		if( 0 == ( status & 0x400 ) )
		{
			printf("\nno home found\n");
			getch();
			return 1;
		}
	// 等待捕获触发
	}while( 0 == capture );
	// 显示捕获位置
	printf("\ncapture pos = %ld\n", pos);
	// 运动到"捕获位置+偏移量"
	sRtn = GT_SetPos(AXIS, pos + HOME_OFFSET);
	commandhandler("GT_SetPos", sRtn);
	// 在运动状态下更新目标位置
	sRtn = GT_Update(1<<(AXIS-1));
	commandhandler("GT_Update", sRtn);

	do
	{
		// 读取轴状态
		sRtn = GT_GetSts(AXIS, &status);
		// 读取规划位置
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		// 读取编码器位置
		sRtn = GT_GetEncPos(AXIS, &encPos);
		printf("status=0x%-8lx prfPos=%-10.1lf encPos=%-10.1lf\r", status, prfPos, encPos);
	// 等待运动停止
	}while( status & 0x400 );
	// 检查是否到达"Home捕获位置+偏移量"
	if( prfPos != pos+HOME_OFFSET )
	{
		printf("\nmove to home pos error\n");
		getch();
		return 2;
	}
	printf("\nHome finish\n");
	// 延时一段时间，等待电机停稳
	Sleep(200);
	printf("\nPress any key to set pos as 0...\n");
	getch();
	// 位置清零
	sRtn = GT_ZeroPos(AXIS);
	commandhandler("GT_ZeroPos", sRtn);
	// 读取规划位置
	sRtn = GT_GetPrfPos(AXIS, &prfPos);
	// 读取编码器位置
	sRtn = GT_GetEncPos(AXIS, &encPos);
	// 读取axis规划位置
	sRtn = GT_GetAxisPrfPos(AXIS, &axisPrfPos);
	// 读取axis编码器位置
	sRtn = GT_GetAxisEncPos(AXIS, &axisEncPos);
	printf("\nprfPos=%-10.0lf encPos=%-10.0lf axisPrfPos=%-10.0lf axisEncPos=%-10.0lf", 
		prfPos, encPos, axisPrfPos, axisEncPos);
	// 伺服关闭
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d\n", sRtn);

	getch();
	return 0;
}
