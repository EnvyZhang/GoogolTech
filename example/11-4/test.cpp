// ���� 11-4 �Ƚ�λ�����
//
// ��������ʾ���ʹ��λ�ñȽ�������ܣ�������Ҫ��-55000��65000�ȼ�����13�����壬��ʹ��λ�����ͨ��1���źŽ��в���
// ����λ�ñȽϹ��ܽ��յ�λ�����������λ�����������ִ��ʱ��������λ�����ݣ��ҽ����ܵ�����λ�����ݣ���ݼ���λ����
// �ݣ�����˳������ȿ��ƱȽ����˶���-65000������������λ������Ϊ10000��130000֮��ȼ���13���������λ�ã�
#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include "gts.h"

#define AXIS		1
#define POS_NUM		13
#define START_POS	10000
#define END_POS		130000

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
	long Buf1[20];
	int i;
	long interval;
	short pSts;
	long pCount;

	// ���˶�������
	sRtn = GT_Open();
	// ָ���ֵ���
	commandhandler("GT_Open", sRtn);
	// �����˶�������
	// ע�⣺�����ļ�ȡ���˸���ı�������λ
	sRtn = GT_LoadConfig("test.cfg");
	commandhandler("GT_LoadConfig ", sRtn);
	// �������ı�������λ
	sRtn = GT_ClrSts(1, 8);
	commandhandler("GT_ClrSts", sRtn);
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
	// �ŷ�ʹ��
	sRtn = GT_AxisOn(AXIS);
	commandhandler("GT_AxisOn", sRtn);
	// ����AXIS���Ŀ��λ��
	sRtn = GT_SetPos(AXIS, -65000L);
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

	// ����Ƚ�λ��
	interval = (END_POS - START_POS) / (POS_NUM - 1);
	Buf1[0] = START_POS;
	for(i=1;i<POS_NUM;i++)
	{
		Buf1[i] = Buf1[i-1] + interval;
	}
	
	// ����λ�ñȽ����ݣ�����λ�ñȽ����
	sRtn = GT_CompareData(1, 1, 0, 0, 100, Buf1, POS_NUM, NULL, 0);
	commandhandler("GT_CompareData", sRtn);
	// ����AXIS���Ŀ��λ��
	sRtn = GT_SetPos(AXIS, 7000L);
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
		// ��ȡ�Ƚ�����������
		sRtn = GT_CompareStatus(&pSts, &pCount);
		printf("sts=0x%-10lx prfPos=%-10.1lf outputed hsio=%d\r", sts, prfPos, pCount);
	}while(sts&0x400);	// �ȴ�AXIS��滮ֹͣ

	// �ŷ��ر�
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d\n", sRtn);
	getch();
	return 0;

}