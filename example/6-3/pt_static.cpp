// 例程 6-3 PT静态FIFO
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
	short sRtn, space;
	double pos;
	long time;
	long sts;
	double prfPos, prfVel;

	// 打开运动控制器
	sRtn = GT_Open();
	// 指令返回值检测
	commandhandler("GT_Open", sRtn);
	// 复位控制器
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);	
	// 配置运动控制器
	// 注意：配置文件取消了各轴的报警和限位
	sRtn = GT_LoadConfig("test.cfg");
	commandhandler("GT_LoadConfig", sRtn); 
	// 清除各轴的报警和限位
	sRtn = GT_ClrSts(1, 8);
	commandhandler("GT_ClrSts", sRtn);
	// 伺服使能
	sRtn = GT_AxisOn(AXIS);
	commandhandler("GT_AxisOn", sRtn);
	// 位置清零
	sRtn = GT_ZeroPos(AXIS);
	commandhandler("GT_ZeroPos", sRtn); 
	// 将AXIS轴设为PT模式
	sRtn = GT_PrfPt(AXIS);
	commandhandler("GT_PrfPt", sRtn); 
	// 清除AXIS轴的FIFO
	sRtn = GT_PtClear(AXIS);
	commandhandler("GT_PtClear", sRtn); 
	// 查询PT模式FIFO的剩余空间
	sRtn = GT_PtSpace(AXIS, &space);
	printf("GT_PtSpace()=%d\tspace=%d\n", sRtn, space);
	// 向FIFO中增加运动数据
	pos = 1024;
	time = 1024;
	sRtn = GT_PtData(AXIS, pos, time);
	commandhandler("GT_PtData", sRtn);
	// 查询PT模式FIFO的剩余空间
	sRtn = GT_PtSpace(AXIS, &space);
	printf("GT_PtSpace()=%d\tspace=%d\n", sRtn, space);
	// 向FIFO中增加运动数据
	pos += 2048;
	time += 1024;
	sRtn = GT_PtData(AXIS, pos, time);
	commandhandler("GT_PtData", sRtn);
	// 查询PT模式FIFO的剩余空间
	sRtn = GT_PtSpace(AXIS, &space);
	printf("GT_PtSpace()=%d\tspace=%d\n", sRtn, space);
	// 向FIFO中增加运动数据
	pos += 1024;
	time += 1024;
	sRtn = GT_PtData(AXIS, pos, time);
	commandhandler("GT_PtData", sRtn);
	// 启动PT运动
	sRtn = GT_PtStart(1<<(AXIS-1));
	commandhandler("GT_PtStart", sRtn);

	while(!kbhit())
	{
		// 读取AXIS轴的状态
		sRtn = GT_GetSts(AXIS, &sts);
		// 读取AXIS轴的规划位置
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		// 读取AXIS轴的规划速度
		sRtn = GT_GetPrfVel(AXIS, &prfVel);
		printf("sts=0x%-10lxprfVel=%-10.2lfprfPos=%-10.1lf\r", sts, prfVel, prfPos);
	}

	// 伺服关闭
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d\n", sRtn);
	getch();
	return 0;

}

