// ���� 6-8 Follow˫FIFO�л�
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
	long masterPos;
	double slavePos;
	short stage, pressKey;

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
	sRtn = GT_SetVel(MASTER, 50);
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
	masterPos = 20000;
	slavePos  = 10000;
	sRtn = GT_FollowData(SLAVE, masterPos, slavePos, FOLLOW_SEGMENT_NORMAL, 0);
	commandhandler("GT_FollowData", sRtn);
	// ��ѯFollowģʽFIFO1��ʣ��ռ�
	sRtn = GT_FollowSpace(SLAVE, &space, 0);
	printf("GT_FollowSpace()=%d space=%d\n", sRtn, space);
	// ��FIFO1�������˶�����
	masterPos += 20000;
	slavePos  += 20000;
	sRtn = GT_FollowData(SLAVE, masterPos, slavePos, FOLLOW_SEGMENT_NORMAL, 0);
	commandhandler("GT_FollowData", sRtn);
	// ��ѯFollowģʽFIFO1��ʣ��ռ�
	sRtn = GT_FollowSpace(SLAVE, &space, 0);
	printf("GT_FollowSpace()=%d space=%d\n", sRtn, space);
	// ��FIFO1�������˶�����
	masterPos += 20000;
	slavePos  += 10000;
	sRtn = GT_FollowData(SLAVE, masterPos, slavePos, FOLLOW_SEGMENT_NORMAL, 0);
	commandhandler("GT_FollowData", sRtn);
	// ���ô���ѭ������Ϊ����ѭ��
	sRtn = GT_SetFollowLoop(SLAVE, 0);
	commandhandler("GT_FollowLoop", sRtn);

	// ����������������
	sRtn = GT_SetFollowEvent(SLAVE, FOLLOW_EVENT_START, 1);
	commandhandler("GT_SetFollowEvent", sRtn);
	// ��������Follow�˶�
	sRtn = GT_FollowStart(1<<(SLAVE-1));
	commandhandler("GT_FollowStart", sRtn);
	stage = STAGE_FIFO1;
	pressKey = 0;

	while(1)
	{
		// ����Ƿ��а���
		if(kbhit())
		{
			getch();
			pressKey = 1;
		}
		// �����ǰ����FIFO1�е����ݲ��Ҽ�⵽���������л�����FIFO2�е�����
		if( STAGE_FIFO1 == stage )
		{
			if( 1 == pressKey )
			{
				pressKey = 0;
				stage = STAGE_TO_FIFO2;
				// ��FIFO2�з��͹�������
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
				// �л���FIFO2
				// ��ǰ����FIFO�е����ݱ������Ժ�Ż��л�FIFO
				sRtn = GT_FollowSwitch(1<<(SLAVE-1));
			}
		}

		// ���FIFO1�Ƿ���գ�����ѱ���գ����µ��ٶȹ滮����FIFO1�У������л�����FIFO1������
		if( STAGE_TO_FIFO2 == stage )
		{
			// ��ѯFIFO1��ʣ��ռ�
			GT_FollowSpace(SLAVE, &space, 0);
			// ���FIFO1����գ�˵���Ѿ��л���FIFO2
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
				// �л���FIFO1
				// ��ǰ����FIFO�������Ժ�Ż��л�FIFO
				sRtn = GT_FollowSwitch(1<<(SLAVE-1));
			}
		}

		if( STAGE_TO_FIFO1 == stage )
		{
			// ��ѯFIFO2��ʣ��ռ�
			GT_FollowSpace(SLAVE, &space, 1);
			// ���FIFO2����գ�˵���Ѿ��л���FIFO1
			if( 16 == space )
			{
				stage = STAGE_END;
			}
		}
		
		// ��ѯ����Ĺ滮�ٶ�
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

	// �ŷ��ر�
	sRtn = GT_AxisOff(MASTER);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, MASTER);
	sRtn = GT_AxisOff(SLAVE);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, SLAVE);

	getch();
	return 0;
}