// 例程 4-1 修改编码器计数方向
#include "windows.h"
#include "stdio.h"
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
	// 指令返回值变量
	short sRtn;
	// 状态值变量
	unsigned short sValue;

	sRtn = GT_Open();
	// 指令返回值校验
	commandhandler("GT_Open", sRtn);
	sRtn = GT_Reset();
	// 指令返回值校验
	commandhandler("GT_Reset", sRtn);

	// 初始化使所有位都为1
	sValue = 0xffff;
	// 使第0位为0，即轴1所对应的位
	sValue &= ~(1);
	// 使第3位为0，即轴4所对应的位
	sValue &= ~(1<<3);
	// 设置编码器计数方向
	sRtn = GT_EncSns(sValue);
	// 指令返回值校验
	commandhandler("GT_EncSns", sRtn);

	return 0;
}
