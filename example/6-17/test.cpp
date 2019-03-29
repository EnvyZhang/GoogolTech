// ���� 6-17 PVT������ʽ
#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "gts.h"

#define AXIS				1
#define TABLE				1

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
	long mask;
	// X������ݵ����
	double time[6]={0, 1200, 2000, 3000, 3800, 5000};
	double pos[6]={0, 9750, 24483, 44483, 59216, 68966};
	double vel[6]={1, 15.25, 20, 20, 15.25, 1};
	double prfVel, prfPos, t;
	short tableId;

	// ���˶�������
	sRtn = GT_Open();
	commandhandler("GT_Open", sRtn);
	// ��λ�˶�������
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// �����˶�������
	// ע�⣺�����ļ�ȡ���˸���ı�������λ
	sRtn = GT_LoadConfig("test.cfg");
	commandhandler("GT_LoadConfig", sRtn);
	// ������ᱨ������λ
	sRtn = GT_ClrSts(1, 8);
	commandhandler("GT_ClrSts", sRtn);
	sRtn = GT_AxisOn(AXIS);
	commandhandler("GT_AxisOn", sRtn);
	// �ȴ��ŷ�ʹ�ܾ���
	Sleep(1000);
	// ����ΪPVTģʽ
	sRtn = GT_PrfPvt(AXIS);
	commandhandler("GT_PrfPvt", sRtn);
	// ��������
	sRtn = GT_PvtTable(TABLE, 6, &time[0], &pos[0], &vel[0]);
	commandhandler("GT_PvtTable", sRtn);
	// ѡ�����ݱ�
	sRtn = GT_PvtTableSelect(AXIS, TABLE);
	commandhandler("GT_PvtTableSelect", sRtn);
	mask = 1<<(AXIS-1);
	sRtn = GT_PvtStart(mask);
	commandhandler("GT_PvtStart", sRtn);
	while(!kbhit())
	{
		// ��ȡ���ݱ���˶�ʱ��
		sRtn = GT_PvtStatus(AXIS, &tableId, &t);
		// ��ȡ�滮�ٶ�
		sRtn = GT_GetPrfVel(AXIS, &prfVel);
		// ��ȡ�滮λ��
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		printf("%2d %10.0lf %10.2lf %10.1lf\r", tableId, t, prfVel, prfPos);
	}
	// �ŷ��ر�
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d\n", sRtn);
	getch();
	return 0;


}
