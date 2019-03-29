// 例程 6-8 Follow双FIFO切换
#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include "gts.h"

#define MASTER					1
#define SLAVE					2

#define STAGE_FIFO1				1
#define STAGE_TO_FIFO2			2
#define STAGE_TO_FIFO1			3
#define STAGE_END				4

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
	short stage, pressKey;

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
	masterPos = 20000;
	slavePos  = 10000;
	sRtn = GT_FollowData(SLAVE, masterPos, slavePos, FOLLOW_SEGMENT_NORMAL, 0);
	commandhandler("GT_FollowData", sRtn);
	// 查询Follow模式FIFO1的剩余空间
	sRtn = GT_FollowSpace(SLAVE, &space, 0);
	printf("GT_FollowSpace()=%d space=%d\n", sRtn, space);
	// 向FIFO1中增加运动数据
	masterPos += 20000;
	slavePos  += 20000;
	sRtn = GT_FollowData(SLAVE, masterPos, slavePos, FOLLOW_SEGMENT_NORMAL, 0);
	commandhandler("GT_FollowData", sRtn);
	// 查询Follow模式FIFO1的剩余空间
	sRtn = GT_FollowSpace(SLAVE, &space, 0);
	printf("GT_FollowSpace()=%d space=%d\n", sRtn, space);
	// 向FIFO1中增加运动数据
	masterPos += 20000;
	slavePos  += 10000;
	sRtn = GT_FollowData(SLAVE, masterPos, slavePos, FOLLOW_SEGMENT_NORMAL, 0);
	commandhandler("GT_FollowData", sRtn);
	// 设置从轴循环次数为无限循环
	sRtn = GT_SetFollowLoop(SLAVE, 0);
	commandhandler("GT_FollowLoop", sRtn);

	// 设置启动跟随条件
	sRtn = GT_SetFollowEvent(SLAVE, FOLLOW_EVENT_START, 1);
	commandhandler("GT_SetFollowEvent", sRtn);
	// 启动从轴Follow运动
	sRtn = GT_FollowStart(1<<(SLAVE-1));
	commandhandler("GT_FollowStart", sRtn);
	stage = STAGE_FIFO1;
	pressKey = 0;

	while(1)
	{
		// 检查是否有按键
		if(kbhit())
		{
			getch();
			pressKey = 1;
		}
		// 如果当前运行FIFO1中的数据并且检测到按键，则切换运行FIFO2中的数据
		if( STAGE_FIFO1 == stage )
		{
			if( 1 == pressKey )
			{
				pressKey = 0;
				stage = STAGE_TO_FIFO2;
				// 向FIFO2中发送过渡数据
				sRtn = GT_FollowClear(SLAVE, 1);
				masterPos = 20000;
				slavePos  = 10000;
				sRtn = GT_FollowData(SLAVE, masterPos, slavePos, 
						FOLLOW_SEGMENT_CONTINUE, 1);
				masterPos+= 20000;
				slavePos += 20000;
				sRtn = GT_FollowData(SLAVE, masterPos, slavePos, 
						FOLLOW_SEGMENT_NORMAL, 1);
				masterPos+= 20000;
				slavePos += 16000;
				sRtn = GT_FollowData(SLAVE, masterPos, slavePos, 
						FOLLOW_SEGMENT_NORMAL, 1);		
				// 切换到FIFO2
				// 当前工作FIFO中的数据遍历完以后才会切换FIFO
				sRtn = GT_FollowSwitch(1<<(SLAVE-1));
			}
		}

		// 检查FIFO1是否被清空，如果已被清空，则将新的速度规划传入FIFO1中，并且切换运行FIFO1中数据
		if( STAGE_TO_FIFO2 == stage )
		{
			// 查询FIFO1的剩余空间
			GT_FollowSpace(SLAVE, &space, 0);
			// 如果FIFO1被清空，说明已经切换到FIFO2
			if( 16 == space )
			{
				stage = STAGE_TO_FIFO1;
				masterPos = 20000;
				slavePos  = 16000;
				sRtn = GT_FollowData(SLAVE, masterPos, slavePos, 
						FOLLOW_SEGMENT_CONTINUE, 0);
				masterPos+= 20000;
				slavePos += 20000;
				sRtn = GT_FollowData(SLAVE, masterPos, slavePos, 
						FOLLOW_SEGMENT_NORMAL, 0);
				masterPos+= 20000;
				slavePos += 16000;
				sRtn = GT_FollowData(SLAVE, masterPos, slavePos, 
						FOLLOW_SEGMENT_NORMAL, 0);
				// 切换到FIFO1
				// 当前工作FIFO遍历完以后才会切换FIFO
				sRtn = GT_FollowSwitch(1<<(SLAVE-1));
			}
		}

		if( STAGE_TO_FIFO1 == stage )
		{
			// 查询FIFO2的剩余空间
			GT_FollowSpace(SLAVE, &space, 1);
			// 如果FIFO2被清空，说明已经切换到FIFO1
			if( 16 == space )
			{
				stage = STAGE_END;
			}
		}
		
		// 查询各轴的规划速度
		sRtn = GT_GetPrfVel(1, prfVel, 8);
		printf("master=%-10.2lf\tslave=%-10.2lf\r", 
			prfVel[MASTER-1], prfVel[SLAVE-1]);

		if( STAGE_END == stage )
		{
			if( 1 == pressKey )
			{
				pressKey = 0;
				break;
			}
		}
	}

	// 伺服关闭
	sRtn = GT_AxisOff(MASTER);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, MASTER);
	sRtn = GT_AxisOff(SLAVE);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, SLAVE);

	getch();
	return 0;
}