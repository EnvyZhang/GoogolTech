// 例程 7-2 读取8个轴编码器和辅助编码器位置值
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
	short sRtn, i;
	double enc[9];

	sRtn = GT_Open();
	commandhandler("GT_Open", sRtn);
	while(1)
	{
		// 读取8个编码器的位置
		GT_GetEncPos(1, &enc[0], 8);
		// 读取辅助编码器的位置
		GT_GetEncPos(9, &enc[8], 1);
		for(i=0;i<9;++i)
		{
			printf("%8.0lf", enc[i]);
		}
		printf("\r");
	}
	return 0;
}
