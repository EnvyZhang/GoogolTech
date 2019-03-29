// ���� 6-1 ��λ�˶�
#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include "gts.h"

#define AXIS		1

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
	TTrapPrm trap;
	long sts;
	double prfPos;

	// ���˶�������
	sRtn = GT_Open();
	// ָ���ֵ���
	commandhandler("GT_Open", sRtn);
	// ��λ�˶�������
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// �����˶�������
	// ע�⣺�����ļ�ȡ���˸���ı�������λ
	sRtn = GT_LoadConfig("test.cfg");
	commandhandler("GT_LoadConfig ", sRtn);
	// �������ı�������λ
	sRtn = GT_ClrSts(1, 8);
	commandhandler("GT_ClrSts", sRtn);
	// �ŷ�ʹ��
	sRtn = GT_AxisOn(AXIS);
	commandhandler("GT_AxisOn", sRtn);

	// λ������
	sRtn = GT_ZeroPos(AXIS);
	commandhandler("GT_ZeroPos", sRtn);
	// AXIS��滮λ������
	sRtn = GT_SetPrfPos(AXIS, 0);
	commandhandler("GT_SetPrfPos", sRtn);
	// ��AXIS����Ϊ��λģʽ
	sRtn = GT_PrfTrap(AXIS);
	commandhandler("GT_PrfTrap", sRtn);
	// ��ȡ��λ�˶�����
	sRtn = GT_GetTrapPrm(AXIS, &trap);
	commandhandler("GT_GetTrapPrm", sRtn);
	trap.acc = 0.25;
	trap.dec = 0.125;
	trap.smoothTime = 25;
	// ���õ�λ�˶�����
	sRtn = GT_SetTrapPrm(AXIS, &trap);
	commandhandler("GT_SetTrapPrm", sRtn);
	// ����AXIS���Ŀ��λ��
	sRtn = GT_SetPos(AXIS, 50000L);
	commandhandler("GT_SetPos", sRtn);
	// ����AXIS���Ŀ���ٶ�
	sRtn = GT_SetVel(AXIS, 50);
	commandhandler("GT_SetVel", sRtn);
	// ����AXIS����˶�
	sRtn = GT_Update(1<<(AXIS-1));
	commandhandler("GT_Update", sRtn);

	do
	{
		// ��ȡAXIS���״̬
		sRtn = GT_GetSts(AXIS, &sts);
		// ��ȡAXIS��Ĺ滮λ��
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		printf("sts=0x%-10lxprfPos=%-10.1lf\r", sts, prfPos);
	}while(sts&0x400);	// �ȴ�AXIS��滮ֹͣ

	// �ŷ��ر�
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d\n", sRtn);
	getch();
	return 0;

}

