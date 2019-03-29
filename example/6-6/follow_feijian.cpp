// 例程 6-6 飞剪中的follow模式应用
#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include "stdio.h"
#include "gts.h"

#define MASTER					1
#define SLAVE					2

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
	long masterPos,sts;
	double slavePos;

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
	sRtn = GT_SetVel(MASTER, 10);
	commandhandler("GT_SetVel", sRtn);
	// 启动主轴
	sRtn = GT_Update(1<<(MASTER-1));
	commandhandler("GT_Update", sRtn);
	// 将从轴设为Follow模式
	sRtn = GT_PrfFollow(SLAVE);
	commandhandler("GT_PrfFollow", sRtn);
	// 清空从轴FIFO1
	sRtn = GT_FollowClear(SLAVE, 0);
	commandhandler("GT_FollowClear", sRtn);
	// 清空从轴FIFO2
	sRtn = GT_FollowClear(SLAVE, 1);
	commandhandler("GT_FollowClear", sRtn);
	// 设置主轴，默认跟随主轴规划位置
	sRtn = GT_SetFollowMaster(SLAVE, MASTER);
	commandhandler("GT_SetFollowMaster", sRtn);
	// 查询Follow模式FIFO1的剩余空间
	sRtn = GT_FollowSpace(SLAVE, &space, 0);
	printf("GT_FollowSpace()=%d space=%d\n", sRtn, space);
	// 向FIFO1中增加运动数据
	masterPos = 5000;
	slavePos  = 2500;
	sRtn = GT_FollowData(SLAVE, masterPos, slavePos, FOLLOW_SEGMENT_NORMAL, 0);
	commandhandler("GT_FollowData", sRtn);

	// 查询Follow模式FIFO2的剩余空间
	sRtn = GT_FollowSpace(SLAVE, &space, 1);
	printf("GT_FollowSpace()=%d space=%d\n", sRtn, space);
	// 向FIFO2中增加运动数据
	masterPos = 1000;
	slavePos  = 1000;
	sRtn = GT_FollowData(SLAVE, masterPos, slavePos, FOLLOW_SEGMENT_EVEN, 1);
	commandhandler("GT_FollowData", sRtn);

	masterPos = 4000;
	slavePos  = 3400;
	sRtn = GT_FollowData(SLAVE, masterPos, slavePos, FOLLOW_SEGMENT_NORMAL, 1);
	commandhandler("GT_FollowData", sRtn);

	masterPos = 6000;
	slavePos  = 4600;
	sRtn = GT_FollowData(SLAVE, masterPos, slavePos, FOLLOW_SEGMENT_EVEN, 1);
	commandhandler("GT_FollowData", sRtn);

	masterPos = 9000;
	slavePos  = 7000;
	sRtn = GT_FollowData(SLAVE, masterPos, slavePos, FOLLOW_SEGMENT_NORMAL, 1);
	commandhandler("GT_FollowData", sRtn);

	masterPos = 10000;
	slavePos  = 8000;
	sRtn = GT_FollowData(SLAVE, masterPos, slavePos, FOLLOW_SEGMENT_EVEN, 1);
	commandhandler("GT_FollowData", sRtn);

	// 设置启动跟随条件
	sRtn = GT_SetFollowEvent(SLAVE, FOLLOW_EVENT_START, 1);
	commandhandler("GT_SetFollowEvent", sRtn);
	// 启动从轴Follow运动
	sRtn = GT_FollowStart(1<<(SLAVE-1),0);
	commandhandler("GT_FollowStart", sRtn);

	// 切换Follow所使用的FIFO1到FIFO2
	sRtn = GT_FollowSwitch(1<<(SLAVE-1));
	commandhandler("GT_FollowSwitch", sRtn);

	// 设置Follow的循环次数为10次
	sRtn = GT_SetFollowLoop(SLAVE,10);
	commandhandler("GT_SetFollowLoop", sRtn);

	do 
	{
		sRtn = GT_GetSts(SLAVE,&sts);
		// 查询各轴的规划速度
		sRtn = GT_GetPrfVel(1, prfVel, 8);
		printf("master=%-10.2lf\tslave=%-10.2lf\r", 
			prfVel[MASTER-1], prfVel[SLAVE-1]);
	} while(sts&0x400);	

	// 伺服关闭
	sRtn = GT_AxisOff(MASTER);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, MASTER);
	sRtn = GT_AxisOff(SLAVE);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, SLAVE);


	getch();
	return 0;
}