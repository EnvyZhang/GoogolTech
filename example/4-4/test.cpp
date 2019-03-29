// 例程 4-4 设置第1轴为闭环控制方式
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
	// PID结构体变量
	TPid pid;
	// 打开运动控制器
	sRtn = GT_Open();
	// 指令返回值检测
	commandhandler("GT_Open", sRtn);
	// 系统复位
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// 配置轴1为模拟量输出模式
	sRtn = GT_CtrlMode(1, 0);
	commandhandler("GT_CtrlMode", sRtn);
	// 配置轴1报警输出无效
	sRtn = GT_AlarmOff(1);
	commandhandler("GT_AlarmOff", sRtn);
	// 配置轴1正负限位无效
	sRtn = GT_LmtsOff(1, -1);	
	commandhandler("GT_LmtsOff", sRtn);
	// 配置完成后要更新状态
	sRtn = GT_ClrSts(1);	
	commandhandler("GT_ClrSts", sRtn);
	// 获取当前pid参数
	sRtn = GT_GetPid(1, 1, &pid);	
	commandhandler("GT_GetPid", sRtn);
	// 调试阶段，只需修改一下kp到一个较小的值
	pid.kp = 1;
	// 设置PID参数
	sRtn = GT_SetPid(1, 1, &pid);
	commandhandler("GT_SetPid", sRtn);
	// 轴1伺服使能
	sRtn = GT_AxisOn(1);
	commandhandler("GT_AxisOn", sRtn);
	// 伺服使能后若出现飞车，则需要通过调用GT_EncSns()指令来修改编码器计数方向
	// 等待伺服稳定
	Sleep(200);

	return 0;
}
