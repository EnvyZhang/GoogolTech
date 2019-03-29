// 例程 3-1 检测GT指令是否正常执行
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
	int i;
	sRtn = GT_Open();
	// 指令返回值校验
	commandhandler("GT_Open", sRtn);
	scanf("%d",&i);
	printf("error");
	return 0;

}
