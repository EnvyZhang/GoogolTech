// ���� 6-5 ���ӳ��ָ���
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
	sRtn = GT_SetVel(MASTER, 100);
	commandhandler("GT_SetVel", sRtn);
	// ��������
	sRtn = GT_Update(1<<(MASTER-1));
	commandhandler("GT_Update", sRtn);
	// ��������ΪGearģʽ
	sRtn = GT_PrfGear(SLAVE);
	commandhandler("GT_PrfGear", sRtn);
	// �������ᣬĬ�ϸ�������滮λ��
	sRtn = GT_SetGearMaster(SLAVE, MASTER);
	commandhandler("GT_SetGearMaster", sRtn);
	// ���ô���Ĵ����Ⱥ������
	sRtn = GT_SetGearRatio(SLAVE, 2, 1, 100000);
	commandhandler("GT_SetGearRatio", sRtn);
	// ��������
	sRtn = GT_GearStart(1<<(SLAVE-1));
	commandhandler("GT_GearStart", sRtn);

	while(!kbhit())
	{
		// ��ѯ����Ĺ滮�ٶ�
		sRtn = GT_GetPrfVel(1, prfVel, 8);
		printf("master vel=%-10.2lf\tslave vel=%-10.2lf\r", 
		prfVel[MASTER-1], prfVel[SLAVE-1]);
	}

	// �ŷ��ر�
	sRtn = GT_AxisOff(MASTER);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, MASTER);
	sRtn = GT_AxisOff(SLAVE);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, SLAVE);


	getch();
	return 0;

}

