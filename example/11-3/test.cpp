// 例程 11-3 自动回原点
#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include "gts.h"

#define AXIS				1				// 定义轴号
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
	unsigned short sts1, sts2;
	sRtn = GT_Open();						// 打开运动控制器
	sRtn = GT_Reset();						// 复位运动控制器
	sRtn = GT_LoadConfig("test.cfg");		// 下载配置文件
	sRtn = GT_ClrSts(1, 8);					// 清楚状态
	sRtn = GT_HomeInit();					// 初始化自动回原点功能
	sRtn = GT_AxisOn(1);						// 使能轴1
	sRtn = GT_AxisOn(2);						// 使能轴2
	sRtn = GT_Index(1, 20000, 2000);			// 轴1为Home+Index回零模式
	sRtn = GT_Home(1, 200000, 50, 0.5, 2000);
	sRtn = GT_Home(2, 200000, 50, 0.5, 3000);// 轴2为Home回零模式
	while (!kbhit())
	{
		sRtn = GT_HomeSts(1, &sts1);			// 查询返回状态
		sRtn = GT_HomeSts(2, &sts2);
		printf("%d %d %d\r", sts1, sts2, sRtn);
	}
	// 伺服关闭
	sRtn = GT_AxisOff(1);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, 1);
	sRtn = GT_AxisOff(2);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, 2);
	
	getch();
	return 0;
}
