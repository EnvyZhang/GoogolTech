// 例程 10-2 运动程序多线程累加求和
#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include "gts.h"

int main(int argc, char* argv[])
{
	short rtn;
	TCompileInfo compile;
	short funId;
	TVarInfo sum,begin,end;
	double value;
	TThreadSts thread;
	
	// 打开运动控制器
	rtn = GT_Open();
	printf("GT_Open()=%d\n",rtn);

	// 复位运动控制器
	rtn = GT_Reset();
	printf("GT_Reset()=%d\n",rtn);

	// 编译运动程序sum.c
	// 请使用MCT2008->工具->运动控制器编译器进行编译
	// 编译成功以后生成sum.bin和sum.ini
	// 必须保证error.ini文件位于工程文件夹中
	//rtn = GT_Compile("sum.c",&compile);
	//printf("GT_Compile()=%d\n",rtn);

	// 下载运动程序sum.bin
	rtn = GT_Download("sum.bin");
	printf("GT_Download()=%d\n",rtn);
	
	// 获取函数ID
	rtn = GT_GetFunId("add",&funId);
	printf("GT_GetFunId()=%d\n",rtn);
	
	// 获取全局变量sum的ID
	rtn = GT_GetVarId(NULL,"sum",&sum);
	printf("GT_GetVarId()=%d\n",rtn);

	// 获取局部变量begin的ID
	rtn = GT_GetVarId("add","begin",&begin);
	printf("GT_GetVarId()=%d\n",rtn);

	// 获取局部变量end的ID
	rtn = GT_GetVarId("add","end",&end);
	printf("GT_GetVarId()=%d\n",rtn);
	
	// 绑定线程，函数，数据页
	rtn = GT_Bind(0,funId,0);
	printf("GT_Bind()=%d\n",rtn);

	// 绑定线程，函数，数据页
	rtn = GT_Bind(1,funId,1);
	printf("GT_Bind()=%d\n",rtn);

	value = 0;
	// 初始化运动程序的全局变量sum
	rtn = GT_SetVarValue(-1,&sum,&value);
	printf("GT_SetVarValue()=%d\n",rtn);

	value = 1;
	// 初始化运动程序的局部变量begin
	rtn = GT_SetVarValue(0,&begin,&value);
	printf("GT_SetVarValue()=%d\n",rtn);
	
	value = 50;
	// 初始化运动程序的局部变量end
	rtn = GT_SetVarValue(0,&end,&value);
	printf("GT_SetVarValue()=%d\n",rtn);

	value = 51;
	// 初始化运动程序的局部变量begin
	rtn = GT_SetVarValue(1,&begin,&value);
	printf("GT_SetVarValue()=%d\n",rtn);
	
	value = 100;
	// 初始化运动程序的局部变量end
	rtn = GT_SetVarValue(1,&end,&value);
	printf("GT_SetVarValue()=%d\n",rtn);
	
	// 启动线程
	rtn = GT_RunThread(0);
	printf("GT_RunThread()=%d\n",rtn);

	// 启动线程
	rtn = GT_RunThread(1);
	printf("GT_RunThread()=%d\n",rtn);

	do
	{
		// 查询线程状态
		rtn = GT_GetThreadSts(0,&thread);
	}while( 1 == thread.run );	// 等待线程运行结束

	do
	{
		// 查询线程状态
		rtn = GT_GetThreadSts(1,&thread);
	}while( 1 == thread.run );	// 等待线程运行结束

	// 查询全局变量sum的值
	rtn = GT_GetVarValue(-1,&sum,&value);
	printf("sum=%-10.0lf",value);

	getch();

	return 0;
}

