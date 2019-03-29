// 例程 6-7 Follow单FIFO模式
#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include "gts.h"

#define MASTER			1
#define SLAVE			2

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
	double prfVel[8];
	TJogPrm jog;
	short space;
	long masterPos;
	double slavePos;
	long loop;

	// 打开运动控制器
	sRtn = GT_Open();
	// 指令返回值检测
	commandhandler("GT_Open", sRtn);
	// 复位运动控制器
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// 配置运动控制器
	// 注意：配置文件test.cfg取消了各轴的报警和限位
	sRtn = GT_LoadConfig("test.cfg");
	commandhandler("GT_LoadConfig", sRtn);
	// 清除各轴的报警和限位
	sRtn = GT_ClrSts(1, 8);
	commandhandler("GT_ClrSts", sRtn);
	// 伺服使能
	sRtn = GT_AxisOn(MASTER);
	commandhandler("GT_AxisOn", sRtn);
	sRtn = GT_AxisOn(SLAVE);
	commandhandler("GT_AxisOn", sRtn);
	// 位置清零
	sRtn = GT_ZeroPos(MASTER);
	commandhandler("GT_ZeroPos", sRtn);
	sRtn = GT_ZeroPos(SLAVE);
	commandhandler("GT_ZeroPos", sRtn);
	// 将主轴设为Jog模式
	sRtn = GT_PrfJog(MASTER);
	commandhandler("GT_PrfJog", sRtn);
	// 设置主轴运动参数
	sRtn = GT_GetJogPrm(MASTER, &jog);
	commandhandler("GT_GetJogPrm", sRtn);
	jog.acc = 1;
	sRtn = GT_SetJogPrm(MASTER, &jog);
	commandhandler("GT_GetJogPrm", sRtn);
	sRtn = GT_SetVel(MASTER, 50);
	commandhandler("GT_SetVel", sRtn);
	// 启动主轴
	sRtn = GT_Update(1<<(MASTER-1));
	commandhandler("GT_Update", sRtn);
	// 将从轴设为Follow模式
	sRtn = GT_PrfFollow(SLAVE);
	commandhandler("GT_PrfFollow", sRtn);
	// 清空从轴FIFO
	sRtn = GT_FollowClear(SLAVE);
	commandhandler("GT_FollowClear", sRtn);
	// 设置主轴，默认跟随主轴规划位置
	sRtn = GT_SetFollowMaster(SLAVE, MASTER);
	commandhandler("GT_SetFollowMaster", sRtn);
	// 查询Follow模式的剩余空间
	sRtn = GT_FollowSpace(SLAVE, &space);
	printf("GT_FollowSpace()=%d space=%d\n", sRtn, space);
	// 向FIFO中增加运动数据
	masterPos = 20000;
	slavePos = 10000;
	sRtn = GT_FollowData(SLAVE, masterPos, slavePos);
	commandhandler("GT_FollowData", sRtn);
	// 查询Follow模式的剩余空间
	sRtn = GT_FollowSpace(SLAVE, &space);
	printf("GT_FollowSpace()=%d space=%d\n", sRtn, space);
	// 向FIFO中增加运动数据
	masterPos += 20000;
	slavePos += 20000;
	sRtn = GT_FollowData(SLAVE, masterPos, slavePos);
	commandhandler("GT_FollowData", sRtn);
	// 查询Follow模式的剩余空间
	sRtn = GT_FollowSpace(SLAVE, &space);
	printf("GT_FollowSpace()=%d space=%d\n", sRtn, space);
	// 向FIFO中增加运动数据
	masterPos += 20000;
	slavePos += 10000;
	sRtn = GT_FollowData(SLAVE, masterPos, slavePos);
	commandhandler("GT_FollowData", sRtn);
	// 设置循环次数为无限循环
	sRtn = GT_SetFollowLoop(SLAVE, 0);
	commandhandler("GT_SetFollowLoop", sRtn);
	// 设置启动跟随条件
	sRtn = GT_SetFollowEvent(SLAVE, FOLLOW_EVENT_PASS, 1, 50000);
	commandhandler("GT_SetFollowEvent", sRtn);
	// 启动从轴Follow运动
	sRtn = GT_FollowStart(1<<(SLAVE-1));
	commandhandler("GT_FollowStart", sRtn);

	while(!kbhit())
	{
		// 查询各轴的规划速度
		sRtn = GT_GetPrfVel(1, prfVel, 8);
		// 查询循环次数
		sRtn = GT_GetFollowLoop(SLAVE, &loop);
		printf("master=%-10.2lf\tslave=%-10.2lf\tloop=%d      \r", 
			prfVel[MASTER-1], prfVel[SLAVE-1], loop);
	}

	// 伺服关闭
	sRtn = GT_AxisOff(MASTER);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, MASTER);
	sRtn = GT_AxisOff(SLAVE);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, SLAVE);

	getch();
	return 0;

}