// 例程 11-4 比较位置输出
//
// 本例程演示如何使用位置比较输出功能，假设需要在-55000到65000等间距输出13个脉冲，并使用位置输出通道1的信号进行捕获
// 由于位置比较功能接收的位置数据是输出位置相对于命令执行时编码器的位置数据，且仅接受递增正位置数据（或递减负位置数
// 据），因此程序首先控制比较轴运动到-65000，再设置设置位置数据为10000到130000之间等间距的13个数（相对位置）
#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include "gts.h"

#define AXIS		1
#define POS_NUM		13
#define START_POS	10000
#define END_POS		130000

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
	long Buf1[20];
	int i;
	long interval;
	short pSts;
	long pCount;

	// 打开运动控制器
	sRtn = GT_Open();
	// 指令返回值检测
	commandhandler("GT_Open", sRtn);
	// 配置运动控制器
	// 注意：配置文件取消了各轴的报警和限位
	sRtn = GT_LoadConfig("test.cfg");
	commandhandler("GT_LoadConfig ", sRtn);
	// 清除各轴的报警和限位
	sRtn = GT_ClrSts(1, 8);
	commandhandler("GT_ClrSts", sRtn);
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
	// 伺服使能
	sRtn = GT_AxisOn(AXIS);
	commandhandler("GT_AxisOn", sRtn);
	// 设置AXIS轴的目标位置
	sRtn = GT_SetPos(AXIS, -65000L);
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

	// 计算比较位置
	interval = (END_POS - START_POS) / (POS_NUM - 1);
	Buf1[0] = START_POS;
	for(i=1;i<POS_NUM;i++)
	{
		Buf1[i] = Buf1[i-1] + interval;
	}
	
	// 设置位置比较数据，启动位置比较输出
	sRtn = GT_CompareData(1, 1, 0, 0, 100, Buf1, POS_NUM, NULL, 0);
	commandhandler("GT_CompareData", sRtn);
	// 设置AXIS轴的目标位置
	sRtn = GT_SetPos(AXIS, 7000L);
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
		// 读取比较输出脉冲个数
		sRtn = GT_CompareStatus(&pSts, &pCount);
		printf("sts=0x%-10lx prfPos=%-10.1lf outputed hsio=%d\r", sts, prfPos, pCount);
	}while(sts&0x400);	// 等待AXIS轴规划停止

	// 伺服关闭
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d\n", sRtn);
	getch();
	return 0;

}