// 例程 11-1 读取运动控制器版本号
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
	short sRtn;
	char *pVersion;								// 定义指向版本号字符串的指针

	// 打开运动控制器
	sRtn = GT_Open();
	// 指令返回值检测
	commandhandler("GT_Open", sRtn);
	// 系统复位
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	sRtn = GT_GetVersion(&pVersion);			// 读取版本号
	commandhandler("GT_GetVersion", sRtn);
	printf("%s\n", pVersion);
	sRtn = GT_Close();
	commandhandler("GT_Close", sRtn);
	
	return TRUE;

}
