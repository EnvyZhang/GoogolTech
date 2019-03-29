// ���� 6-6 �ɼ��е�followģʽӦ��
#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include "stdio.h"
#include "gts.h"

#define MASTER					1
#define SLAVE					2

// �ú������ĳ��GTָ���ִ�н����commandΪָ�����ƣ�errorΪָ��ִ�з���ֵ
void commandhandler(char *command, short error)
{
	// ���ָ��ִ�з���ֵΪ��0��˵��ָ��ִ�д�������Ļ���������
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

	// ���˶�������
	sRtn = GT_Open();
	// ָ���ֵ���
	commandhandler("GT_Open", sRtn);
	// ��λ�˶�������
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// �����˶�������
	// ע�⣺�����ļ�test.cfgȡ���˸���ı�������λ
	sRtn = GT_LoadConfig("test.cfg");
	commandhandler("GT_LoadConfig", sRtn);
	// �������ı�������λ
	sRtn = GT_ClrSts(1, 8);
	commandhandler("GT_ClrSts", sRtn);
	// �ŷ�ʹ��
	sRtn = GT_AxisOn(MASTER);
	commandhandler("GT_AxisOn", sRtn);
	sRtn = GT_AxisOn(SLAVE);
	commandhandler("GT_AxisOn", sRtn);
	// λ������
	sRtn = GT_ZeroPos(MASTER);
	commandhandler("GT_ZeroPos", sRtn);
	sRtn = GT_ZeroPos(SLAVE);
	commandhandler("GT_ZeroPos", sRtn);
	// ��������ΪJogģʽ
	sRtn = GT_PrfJog(MASTER);
	commandhandler("GT_PrfJog", sRtn);
	// ���������˶�����
	sRtn = GT_GetJogPrm(MASTER, &jog);
	commandhandler("GT_GetJogPrm", sRtn);
	jog.acc = 1;
	sRtn = GT_SetJogPrm(MASTER, &jog);
	commandhandler("GT_GetJogPrm", sRtn);
	sRtn = GT_SetVel(MASTER, 10);
	commandhandler("GT_SetVel", sRtn);
	// ��������
	sRtn = GT_Update(1<<(MASTER-1));
	commandhandler("GT_Update", sRtn);
	// ��������ΪFollowģʽ
	sRtn = GT_PrfFollow(SLAVE);
	commandhandler("GT_PrfFollow", sRtn);
	// ��մ���FIFO1
	sRtn = GT_FollowClear(SLAVE, 0);
	commandhandler("GT_FollowClear", sRtn);
	// ��մ���FIFO2
	sRtn = GT_FollowClear(SLAVE, 1);
	commandhandler("GT_FollowClear", sRtn);
	// �������ᣬĬ�ϸ�������滮λ��
	sRtn = GT_SetFollowMaster(SLAVE, MASTER);
	commandhandler("GT_SetFollowMaster", sRtn);
	// ��ѯFollowģʽFIFO1��ʣ��ռ�
	sRtn = GT_FollowSpace(SLAVE, &space, 0);
	printf("GT_FollowSpace()=%d space=%d\n", sRtn, space);
	// ��FIFO1�������˶�����
	masterPos = 5000;
	slavePos  = 2500;
	sRtn = GT_FollowData(SLAVE, masterPos, slavePos, FOLLOW_SEGMENT_NORMAL, 0);
	commandhandler("GT_FollowData", sRtn);

	// ��ѯFollowģʽFIFO2��ʣ��ռ�
	sRtn = GT_FollowSpace(SLAVE, &space, 1);
	printf("GT_FollowSpace()=%d space=%d\n", sRtn, space);
	// ��FIFO2�������˶�����
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

	// ����������������
	sRtn = GT_SetFollowEvent(SLAVE, FOLLOW_EVENT_START, 1);
	commandhandler("GT_SetFollowEvent", sRtn);
	// ��������Follow�˶�
	sRtn = GT_FollowStart(1<<(SLAVE-1),0);
	commandhandler("GT_FollowStart", sRtn);

	// �л�Follow��ʹ�õ�FIFO1��FIFO2
	sRtn = GT_FollowSwitch(1<<(SLAVE-1));
	commandhandler("GT_FollowSwitch", sRtn);

	// ����Follow��ѭ������Ϊ10��
	sRtn = GT_SetFollowLoop(SLAVE,10);
	commandhandler("GT_SetFollowLoop", sRtn);

	do 
	{
		sRtn = GT_GetSts(SLAVE,&sts);
		// ��ѯ����Ĺ滮�ٶ�
		sRtn = GT_GetPrfVel(1, prfVel, 8);
		printf("master=%-10.2lf\tslave=%-10.2lf\r", 
			prfVel[MASTER-1], prfVel[SLAVE-1]);
	} while(sts&0x400);	

	// �ŷ��ر�
	sRtn = GT_AxisOff(MASTER);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, MASTER);
	sRtn = GT_AxisOff(SLAVE);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, SLAVE);


	getch();
	return 0;
}