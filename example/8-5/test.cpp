
// 例程 8-5 HSIO捕获用法示例
#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "gts.h"

#define AXIS					1 
#define AXIS_2					2

#define HSIO_OUTPUT_POS			1000  // hsio在编码器位1000时输出hsio信号

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
	long hsioOptPos[1];
	long mask;
	
	// 打开运动控制器 
	sRtn = GT_Open(); 
	// 复位运动控制器 
	sRtn = GT_Reset(); 
	// 配置运动控制器 
	sRtn = GT_LoadConfig("test.cfg");

	hsioOptPos[0] = HSIO_OUTPUT_POS;
	// 设置位置比较数据，启动位置比较输出
	sRtn = GT_CompareData(	1,						// 对1轴进行位置比较输出
							1,						// 需要进行比较的数据源为外部编码器
							0,						// 到达比较位置后输出脉冲
							0,	 					// 初始状态为低电平
							500,					// 脉冲宽度为500us
							hsioOptPos,				// HSIO0的比较位置缓冲区数据起始地址
							1,						// HSIO0的比较位置缓冲区数据长度
							NULL,
							0);
	// 启动Hsio 捕获 
	sRtn = GT_SetCaptureMode(AXIS_2, CAPTURE_HSIO0); 
	for (int i=1; i<=2; i++)
	{
		// 清除指定轴的报警和限位 
		sRtn = GT_ClrSts(i); 
		// 驱动器使能 
		sRtn = GT_AxisOn(i);
		// 切换到点位运动模式 
		sRtn = GT_PrfTrap(i); 
		// 读取、设置点位模式运动参数
		sRtn = GT_GetTrapPrm(i, &trapPrm); 
		trapPrm.acc = 0.25;
		trapPrm.dec = 0.25; 
		sRtn = GT_SetTrapPrm(i, &trapPrm); 
		// 设置点位模式目标速度，即运动速度 
		sRtn = GT_SetVel(i, 10); 
		// 设置点位模式目标位置，使HSIO触发输出
		sRtn = GT_SetPos(i, HSIO_OUTPUT_POS+500); 
		mask = mask | 1<<(i-1);
	}

	// 启动运动 
	sRtn = GT_Update(mask); 

	do 
	{
		// 读取轴状态 
		sRtn = GT_GetSts(AXIS, &status); 
		// 读取捕获状态 
		sRtn = GT_GetCaptureStatus(AXIS_2, &capture, &pos); 
		// 读取规划位置 
		sRtn = GT_GetPrfPos(AXIS, &prfPos); 
		// 读取编码器位置 
		sRtn = GT_GetEncPos(AXIS, &encPos); 
		printf("capture=%d prfPos=%lf encPos=%lf\r", capture, prfPos, encPos); 
		// 等待捕获触发
	}while( 0 == capture ); 

	// 显示捕获位置 
	printf("\nHsio captured pos = %ld\n", pos);
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, AXIS);
	sRtn = GT_AxisOff(AXIS_2);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, AXIS_2);

	getch();
	return 0;
}
