// 例程 8-4 探针捕获
#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "gts.h"

#define AXIS					1 

#define SEARCH_PROBE		-2000000  // 假设在该路程内能找到探针信号

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
	double prfPos, encPos; 

	// 打开运动控制器 
	sRtn = GT_Open(); 
	// 复位运动控制器 
	sRtn = GT_Reset(); 
	// 配置运动控制器 
	sRtn = GT_LoadConfig("test.cfg");
	// 清除指定轴的报警和限位 
	sRtn = GT_ClrSts(AXIS); 
	// 驱动器使能 
	sRtn = GT_AxisOn(AXIS);
	// 启动Probe 捕获 
	sRtn = GT_SetCaptureMode(AXIS, CAPTURE_PROBE); 
	// 切换到点位运动模式 
	sRtn = GT_PrfTrap(AXIS); 
	// 读取、设置点位模式运动参数
	sRtn = GT_GetTrapPrm(AXIS, &trapPrm); 
	trapPrm.acc = 0.25;
	trapPrm.dec = 0.25; 
	sRtn = GT_SetTrapPrm(AXIS, &trapPrm); 
	// 设置点位模式目标速度，即回原点速度 
	sRtn = GT_SetVel(AXIS, 10); 
	// 设置点位模式目标位置，即原点搜索距离 
	sRtn = GT_SetPos(AXIS, SEARCH_PROBE); 
	// 启动运动 
	sRtn = GT_Update(1<<(AXIS-1)); 
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
		printf("capture=%d prfPos=%lf encPos=%lf\r", capture, prfPos, encPos); 
		// 如果运动停止，返回出错信息 
		if( 0 == ( status & 0x400 ) ) 
		{ 
		printf("\nno Probe found\n"); 
		getch(); 
		return 1; 
		} 
	// 等待捕获触发
	}while( 0 == capture ); 
	// 显示捕获位置 
	printf("\nProbe captured pos = %ld\n", pos); 
	// 伺服关闭
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d\n", sRtn);

	getch();
	return 0;
}
