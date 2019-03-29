// 例程 7-1 访问数字IO
#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "gts.h"

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
	// 指令返回值
	short sRtn;
	// 通用输入读取值
	long lGpiValue;
	// 正限位输入变化次数
	unsigned long lPosLmtReverseCount;
	// 负限位输入变化次数
	unsigned long lNegLmtReverseCount;

	// 打开运动控制器
	sRtn = GT_Open();
	// 指令返回值检测
	commandhandler("GT_Open", sRtn);
	// 系统复位
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);

	// 初始化变化次数为0
	lPosLmtReverseCount = 0;
	lNegLmtReverseCount = 0;

	// 读取EXI3输入值
	sRtn = GT_GetDi(MC_GPI, &lGpiValue);
	// 此函数为检测指令返回值函数，参看例程 2 1检测GT指令是否正常执行
	commandhandler("GT_GetDi" , sRtn);
	// 如果为高电平，说明按键正在被按下，则不检测，返回1
	if( lGpiValue & (1<<3))
		return 1;
	// EXO6输出高电平，使指示灯灭
	sRtn = GT_SetDo(MC_GPO, 1<<6);
	commandhandler("GT_SetDo" , sRtn);
	// 按键没有被按下，循环。如果EXI3输入值为高电平，即按键按下，则退出循环
	while( ! (lGpiValue & (1<<3)))
	{
		// 读取正限位输入变化次数
		sRtn = GT_GetDiReverseCount(
			MC_LIMIT_POSITIVE,			// 指定数字IO类型是正限位
			1,							// 指定正限位1
			&lPosLmtReverseCount,		// 读取的值
			1);							// 一次读一个数字量输入
		commandhandler("GT_GetDiReverseCount" , sRtn);
		// 读取负限位输入变化次数
		sRtn = GT_GetDiReverseCount(
			MC_LIMIT_NEGATIVE,			// 指定数字IO类型是负限位
			1,							// 指定负限位1
			&lNegLmtReverseCount,		// 读取的值
			1);							// 一次读一个数字量输入
		commandhandler("GT_GetDiReverseCount" , sRtn);
		// 将结果输出到显示器
		printf("PosLmtReverseCount = %d\n NegLmtReverseCount = %d\n", 
			lPosLmtReverseCount, lNegLmtReverseCount);
		// 如果正负限位的输入变化次数都超过10次
		if(( lPosLmtReverseCount >= 10) &&( lNegLmtReverseCount >= 10) )
		{
			// 重新归为0
			lPosLmtReverseCount = 0;
			lNegLmtReverseCount = 0;
			// 设置正限位输入变化次数
			sRtn = GT_SetDiReverseCount(
				MC_LIMIT_POSITIVE,		// 指定数字IO类型是正限位
				1,						// 指定正限位1
				&lPosLmtReverseCount,	// 读取的值
				1);						// 一次设置一个数字量输入
			commandhandler("GT_SetDiReverseCount" , sRtn);
			// 设置负限位输入变化次数
			sRtn = GT_SetDiReverseCount(
				MC_LIMIT_NEGATIVE,	// 指定数字IO类型是负限位
				1,						// 指定负限位1
				&lNegLmtReverseCount,	// 读取的值
				1);						// 一次设置一个数字量输入
			commandhandler("GT_SetDiReverseCount" , sRtn);
			// EXO6输出高电平，使指示灯亮
			sRtn = GT_SetDoBit(
				MC_GPO,				// 指定数字IO类型是通用输出
				7,						// 指定第7个通用输出，即EXO6
				0);						// 输出低电平
			commandhandler("GT_SetDoBit" , sRtn);
		}
		// 不断读取通用输入，已检测EXI3的电平状态
		sRtn = GT_GetDi(MC_GPI, &lGpiValue);
		commandhandler("GT_GetDi" , sRtn);
	}
	getch();
	return 0;

}
