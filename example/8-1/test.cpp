// 例程 8-1 Home/Index捕获
#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "gts.h"

#define ENCODER			1

// 该函数检测某条GT指令的执行结果，command为指令名称，error为指令执行返回值
void commandhandler(char *command, short error)
{
	// 如果指令执行返回值为非0，说明指令执行错误，向屏幕输出错误结果
	if(error)
	{
		printf("%s = %d\n", command, error);
	}
}

void CaptureIndex(void)
{
	short sRtn, status;
	long pos;
	double encPos;

	// 启动Index捕获
	sRtn = GT_SetCaptureMode(ENCODER, CAPTURE_INDEX);
	commandhandler("GT_SetCaptureMode", sRtn);

	printf("\n");

	do
	{
		// 查询捕获状态
		GT_GetCaptureStatus(ENCODER, &status, &pos);
		// 读取编码器位置
		// 该指令和捕获无关，仅用于显示编码器位置
		GT_GetEncPos(ENCODER, &encPos);
		// 显示捕获状态和编码器位置
		printf("status = %d enc = %-8.0lf\r", status, encPos);
		// 当指定轴捕获触发时退出循环
	}while( 0 == status );

	// 显示捕获位置
	printf("\ncapture = %-8ld\n", pos);
}

void CaptureHome(void)
{
	short sRtn, status;
	long pos;
	double encPos;

	// 启动Home捕获
	sRtn = GT_SetCaptureMode(ENCODER, CAPTURE_HOME);
	commandhandler("GT_SetCaptureMode", sRtn);

	printf("\n");

	do
	{
		// 查询捕获状态
		GT_GetCaptureStatus(ENCODER, &status, &pos);
		// 读取编码器位置
		// 该指令和捕获无关，仅用于显示编码器位置
		GT_GetEncPos(ENCODER, &encPos);
		// 显示捕获状态和编码器位置
		printf("status = %d enc = %-8.0lf\r", status, encPos);
		// 当指定轴捕获触发时退出循环
	}while( 0 == status );
	// 显示捕获位置
	printf("\ncapture = %-8ld\n", pos);
}

int main(int argc, char* argv[])
{
	char ch;
	short sRtn;

	sRtn = GT_Open();
	commandhandler("GT_Open", sRtn);

	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	while(1)
	{
		// 选择捕获模式，H：Home捕获，I：Index捕获，Q：退出程序
		printf("\n[H:Home|I:Index|Q:Quit]:");
		ch=toupper(getche());
		switch(ch)
		{
		case 'H': CaptureHome();break;
		case 'I': CaptureIndex(); break;
		case 'Q': return 0;
		}
	}
}
