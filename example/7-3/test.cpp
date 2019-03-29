// 例程 7-3 访问DAC
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
	// 电压值
	short sSetValue;
	short sGetValue;

	sRtn = GT_Open();
	commandhandler("GT_Open", sRtn);
	// 控制器复位，所有轴都为脉冲控制模式
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// 计算轴4的电压输出值
	sSetValue = (short) 32767*5/10;
	// 设置轴4的输出电压
	sRtn = GT_SetDac(4, &sSetValue, 1);
	// 读取轴4的输出电压值
	sRtn = GT_GetDac(4, &sGetValue, 1);

	return 0;
}
