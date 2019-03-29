// 例程 5-1 获取轴1的轴状态、运动模式、位置、速度和加速度
#include "windows.h"
#include "stdio.h"
#include "gts.h"

#define AXIS				1			// 定义轴号
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
	short bFlagAlarm = FALSE;			// 伺服报警标志
	short bFlagMError = FALSE;			// 跟随误差越限标志
	short bFlagPosLimit = FALSE;		// 正限位触发标志
	short bFlagNegLimit = FALSE;		// 负限位触发标志
	short bFlagSmoothStop = FALSE;		// 平滑停止标志
	short bFlagAbruptStop = FALSE;		// 急停标志
	short bFlagServoOn = FALSE;			// 伺服使能标志
	short bFlagMotion = FALSE;			// 规划器运动标志
	double dPrfPos;						// 规划位置
	double dPrfVel;						// 规划速度
	double dPrfAcc;						// 规划加速度
	long lPrfMode;						// 运动模式
	char chPrfMode[20];					// 运动模式，字符串变量
	short sRtn;							// 指令返回值变量
	long lAxisStatus;					// 轴状态

	// 打开运动控制器
	sRtn = GT_Open();
	// 指令返回值检测
	commandhandler("GT_Open", sRtn);
	// 系统复位
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// 读取轴状态
	sRtn = GT_GetSts(AXIS, &lAxisStatus);
	commandhandler("GT_GetSts" , sRtn);

	// 伺服报警标志
	if (lAxisStatus & 0x2)
	{
		bFlagAlarm = TRUE;
		printf("伺服报警\n");
	}
	else
	{
		bFlagAlarm = FALSE;
		printf("伺服正常\n");
	}
	// 跟随误差越限标志
	if (lAxisStatus & 0x10)
	{
		bFlagMError = TRUE;
		printf("运动出错\n");
	}
	else
	{
		bFlagMError = FALSE;
		printf("运动正常\n");
	}
	// 正向限位
	if (lAxisStatus & 0x20)
	{
		bFlagPosLimit = TRUE;
		printf("正限位触发\n");
	}
	else
	{
		bFlagPosLimit = FALSE;
		printf("正限位未触发\n");
	}
	// 负向限位
	if (lAxisStatus & 0x40)
	{
		bFlagNegLimit = TRUE;
		printf("负限位触发\n");
	}
	else
	{
		bFlagNegLimit = FALSE;
		printf("负限位未触发\n");
	}
	// 平滑停止
	if (lAxisStatus & 0x80)
	{
		bFlagSmoothStop = TRUE;
		printf("平滑停止触发\n");
	}
	else
	{
		bFlagSmoothStop = FALSE;
		printf("平滑停止未触发\n");
	}
	// 急停标志
	if (lAxisStatus & 0x100)
	{
		bFlagAbruptStop = TRUE;
		printf("急停触发\n");
	}
	else
	{
		bFlagAbruptStop = FALSE;
		printf("急停未触发\n");
	}
	// 伺服使能标志
	if(lAxisStatus & 0x200)
	{
		bFlagServoOn = TRUE;
		printf("伺服使能\n");
	}
	else
	{
		bFlagServoOn = FALSE;
		printf("伺服关闭\n");
	}
	// 规划器正在运动标志
	if (lAxisStatus & 0x400)
	{
		bFlagMotion = TRUE;
		printf("规划器正在运动\n");
	}
	else
	{
		bFlagMotion = FALSE;
		printf("规划器已停止\n");
	} 

	// 读取运动数据
	sRtn = GT_GetPrfPos(AXIS, &dPrfPos);
	commandhandler("GT_GetPrfPos", sRtn);
	printf("规划位置 %8.2f\n", dPrfPos);
	sRtn = GT_GetPrfVel(AXIS, &dPrfVel);
	commandhandler("GT_GetPrfVel", sRtn);
	printf("规划速度 %8.2f\n", dPrfVel);
	sRtn=GT_GetPrfAcc(AXIS, &dPrfAcc);
	commandhandler("GT_GetPrfAcc", sRtn);
	printf("规划加速度 %8.2f\n", dPrfAcc);

	// 读取运动模式
	sRtn = GT_GetPrfMode(AXIS, &lPrfMode);
	commandhandler("GT_GetPrfMode", sRtn);
	// 清空字符串
	memset(chPrfMode, '\0', 20);
	switch(lPrfMode) 
	{
		case 0:
			sprintf(chPrfMode, "Trap");
		break;
		case 1:
			sprintf(chPrfMode, "Jog");
		break;
		case 2:
			sprintf(chPrfMode, "PT");
		break;
		case 3:
			sprintf(chPrfMode, "Gear");
		break;
		case 4:
			sprintf(chPrfMode, "Follow");
		break;
		case 5:
			sprintf(chPrfMode, "Interpolation");
		break;
		case 6:
			sprintf(chPrfMode, "PVT");
		break;
		default:
		break;
	}
	printf("运动模式 %s\n", chPrfMode);

	return TRUE;

}
