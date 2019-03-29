// 例程 7-4 访问ADC
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
	double dGetVoltageValue[4];
	// 数字转换值
	short sGetDigitalValue[4];

	sRtn = GT_Open();
	commandhandler("GT_Open", sRtn);
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// 读取4个通道的输入电压
	sRtn = GT_GetAdc(1, &dGetVoltageValue[0], 4);
	// 读取4个通道输入电压的数字转换值
	sRtn = GT_GetAdcValue(1, &sGetDigitalValue[0], 4);

	return 0;
}
