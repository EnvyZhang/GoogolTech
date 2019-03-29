// ���� 6-7 Follow��FIFOģʽ
#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include "gts.h"

#define MASTER			1
#define SLAVE			2

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
	long loop;

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
	// ��մ���FIFO
	sRtn = GT_FollowClear(SLAVE);
	commandhandler("GT_FollowClear", sRtn);
	// �������ᣬĬ�ϸ�������滮λ��
	sRtn = GT_SetFollowMaster(SLAVE, MASTER);
	commandhandler("GT_SetFollowMaster", sRtn);
	// ��ѯFollowģʽ��ʣ��ռ�
	sRtn = GT_FollowSpace(SLAVE, &space);
	printf("GT_FollowSpace()=%d space=%d\n", sRtn, space);
	// ��FIFO�������˶�����
	masterPos = 20000;
	slavePos = 10000;
	sRtn = GT_FollowData(SLAVE, masterPos, slavePos);
	commandhandler("GT_FollowData", sRtn);
	// ��ѯFollowģʽ��ʣ��ռ�
	sRtn = GT_FollowSpace(SLAVE, &space);
	printf("GT_FollowSpace()=%d space=%d\n", sRtn, space);
	// ��FIFO�������˶�����
	masterPos += 20000;
	slavePos += 20000;
	sRtn = GT_FollowData(SLAVE, masterPos, slavePos);
	commandhandler("GT_FollowData", sRtn);
	// ��ѯFollowģʽ��ʣ��ռ�
	sRtn = GT_FollowSpace(SLAVE, &space);
	printf("GT_FollowSpace()=%d space=%d\n", sRtn, space);
	// ��FIFO�������˶�����
	masterPos += 20000;
	slavePos += 10000;
	sRtn = GT_FollowData(SLAVE, masterPos, slavePos);
	commandhandler("GT_FollowData", sRtn);
	// ����ѭ������Ϊ����ѭ��
	sRtn = GT_SetFollowLoop(SLAVE, 0);
	commandhandler("GT_SetFollowLoop", sRtn);
	// ����������������
	sRtn = GT_SetFollowEvent(SLAVE, FOLLOW_EVENT_PASS, 1, 50000);
	commandhandler("GT_SetFollowEvent", sRtn);
	// ��������Follow�˶�
	sRtn = GT_FollowStart(1<<(SLAVE-1));
	commandhandler("GT_FollowStart", sRtn);

	while(!kbhit())
	{
		// ��ѯ����Ĺ滮�ٶ�
		sRtn = GT_GetPrfVel(1, prfVel, 8);
		// ��ѯѭ������
		sRtn = GT_GetFollowLoop(SLAVE, &loop);
		printf("master=%-10.2lf\tslave=%-10.2lf\tloop=%d      \r", 
			prfVel[MASTER-1], prfVel[SLAVE-1], loop);
	}

	// �ŷ��ر�
	sRtn = GT_AxisOff(MASTER);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, MASTER);
	sRtn = GT_AxisOff(SLAVE);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, SLAVE);

	getch();
	return 0;

}