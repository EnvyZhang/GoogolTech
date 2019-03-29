// 例程 8-3 Home+Index回原点
#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "gts.h"

// 定义轴号
#define AXIS						1
// 定义home回零搜索距离
#define SEARCH_HOME					-200000
// 定义到home捕获位置的偏移量
#define HOME_OFFSET					-2000
// 定义index回零搜索距离
#define SEARCH_INDEX				15000
// 定义到index捕获位置的偏移量
#define INDEX_OFFSET				1000



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
	// 定义返回值变量
	short sRtn;
	// 捕获状态
	short capture;
	// 点位运动参数结构体
	TTrapPrm trapPrm;
	// 轴状态
	long status;
	// 捕获位置
	long pos;
	// 分别是规划位置，编码器位置，轴的规划位置，轴的编码器位置
	double prfPos, encPos, axisPrfPos, axisEncPos;
	// 打开运动控制器
	sRtn = GT_Open();
	commandhandler("GT_Open", sRtn);
	// 复位
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// 加载配置文件
	sRtn = GT_LoadConfig("test.cfg");
	commandhandler("GT_LoadConfig", sRtn);
	// 清状态
	sRtn = GT_ClrSts(AXIS);
	commandhandler("GT_ClrSts", sRtn);
	// 轴伺服使能
	sRtn = GT_AxisOn(AXIS);
	commandhandler("GT_AxisOn", sRtn);
	// 开启轴的home捕获功能
	sRtn = GT_SetCaptureMode(AXIS, CAPTURE_HOME);
	commandhandler("GT_SetCaptureMode", sRtn);
	// 设置轴为点位运动模式
	sRtn = GT_PrfTrap(AXIS);
	commandhandler("GT_PrfTrap", sRtn);
	// 读取点位运动参数
	sRtn = GT_GetTrapPrm(AXIS, &trapPrm);
	commandhandler("GT_GetTrapPrm", sRtn);

	trapPrm.acc = 0.25;
	trapPrm.dec = 0.25;
	// 设置点位运动参数
	sRtn = GT_SetTrapPrm(AXIS, &trapPrm);
	commandhandler("GT_SetTrapPrm", sRtn);
	// 设置目标速度
	sRtn = GT_SetVel(AXIS, 10);
	commandhandler("GT_SetVel", sRtn);
	// 设置目标位置
	sRtn = GT_SetPos(AXIS, SEARCH_HOME);
	commandhandler("GT_SetPos", sRtn);
	// 启动运动，等待home信号触发
	sRtn = GT_Update(1<<(AXIS-1));
	commandhandler("GT_Update", sRtn);
	printf("\nWaiting for home signal...\n");
	// 如果home捕获没有触发，就一直循环
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
		printf("capture=%d prfPos=%-10.1lf encPos=%-10.1lf\r", capture, prfPos, encPos);
		// 电机已经停止，说明整个搜索过程中home信号一直没有触发
		if( 0 == ( status & 0x400 ) )
		{
			printf("\nno home found");
			return 1;
		}
	// 如果home信号已经触发，则退出循环，捕获位置已经在pos变量中保存
	}while( 0 == capture );
	printf("\ncapture pos = %ld\n", pos);
	// 设定目标位置为捕获位置+偏移量
	sRtn = GT_SetPos(AXIS, pos + HOME_OFFSET);
	commandhandler("GT_SetPos", sRtn);
	// 启动运动
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
	}while( status & 0x400 );

	if( prfPos != pos + HOME_OFFSET) 
	{
		printf("\nmove to home pos error");
		return 2;
	}
	// home捕获完毕
	printf("\nHome finish\n");
	Sleep(200);
	// 启动index捕获
	sRtn = GT_SetCaptureMode(AXIS, CAPTURE_INDEX);
	commandhandler("GT_SetCaptureMode", sRtn);
	// 设置当前位置+index搜索距离为目标位置
	sRtn = GT_SetPos(AXIS, (long)(prfPos + SEARCH_INDEX));
	commandhandler("GT_SetPos", sRtn);
	// 启动运动
	sRtn = GT_Update(1<<(AXIS-1));
	commandhandler("GT_Update", sRtn);
	// 等待index捕获信号触发
	printf("\nWaiting for index signal...\n");	

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
		printf("capture=%d prfPos=%-10.1lf encPos=%-10.1lf\r", capture, prfPos, encPos);
		// 电机已经停止，说明整个搜索过程中index信号一直没有触发
		if( 0 == ( status & 0x400 ) )
		{
			printf("\nno index found\n");
			getch();
			return 1;
		}
	// 如果index信号已经触发，则退出循环，捕获位置已经在pos变量中保存
	}while( 0 == capture );

	printf("\ncapture pos = %ld\n", pos);
	// 设置捕获位置+index偏移量为目标位置
	sRtn = GT_SetPos(AXIS, pos+ INDEX_OFFSET);
	commandhandler("GT_SetPos", sRtn);
	// 启动运动
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
	}while( status & 0x400 );

	if( prfPos != pos+ INDEX_OFFSET) 
	{
		printf("\nmove to index pos error\n");
		getch();
		return 2;
	}
	// home+index捕获完毕
	printf("\nHome+Index finish\n");
	printf("\nPress any key to set pos as 0...\n");
	getch();

	Sleep(200);
	// 更新原点位置
	sRtn = GT_ZeroPos(AXIS);
	printf("GT_ZeroPos", sRtn);

	sRtn = GT_GetPrfPos(AXIS, &prfPos);
	sRtn = GT_GetEncPos(AXIS, &encPos);
	sRtn = GT_GetAxisPrfPos(AXIS, &axisPrfPos);
	sRtn = GT_GetAxisEncPos(AXIS, &axisEncPos);
	printf("\nprfPos=%-10.0lf encPos=%-10.0lf axisPrfPos=%-10.0lf axisEncPos=%-10.0lf", 
		prfPos, encPos, axisPrfPos, axisEncPos);
	// 伺服关闭
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d\n", sRtn);

	getch();
	return 0;
}
