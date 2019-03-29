// ���� 6-2 Jog�˶�
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
	TJogPrm jog;
	long sts;
	double prfPos, prfVel;

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
	
	// ��AXIS����ΪJogģʽ
	sRtn = GT_PrfJog(AXIS);
	commandhandler("GT_PrfTrap", sRtn);
	// ��ȡJog�˶�����
	sRtn = GT_GetJogPrm(AXIS, &jog);
	commandhandler("GT_GetJogPrm", sRtn);
	jog.acc = 0.0625;
	jog.dec = 0.0625;
	// ����Jog�˶�����
	sRtn = GT_SetJogPrm(AXIS, &jog);
	commandhandler("GT_SetJogPrm", sRtn);
	// ����AXIS���Ŀ���ٶ�
	sRtn = GT_SetVel(AXIS, 100);
	commandhandler("GT_SetVel", sRtn);
	// ����AXIS����˶�
	sRtn = GT_Update(1<<(AXIS-1));
	commandhandler("GT_Update", sRtn);
	
	while(1)
	{
		// ��ȡAXIS���״̬
		sRtn = GT_GetSts(AXIS, &sts);
		// ��ȡAXIS��Ĺ滮λ��
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		// ��ȡAXIS��Ĺ滮�ٶ�
		sRtn = GT_GetPrfVel(AXIS, &prfVel);
		printf("sts=0x%-10lxprfPos=%-10.1lfprfVel=%-10.1lf\r", sts, prfPos, prfVel);
		if(prfPos >= 100000)
		{
			// ����AXIS���µ�Ŀ���ٶ�
			sRtn = GT_SetVel(AXIS, 50);
			commandhandler("GT_SetVel", sRtn);
			// AXIS���µ�Ŀ���ٶ���Ч
			sRtn = GT_Update(1<<(AXIS-1));
			commandhandler("GT_Update", sRtn);
			break;
		}
	} 
	while(!kbhit())
	{
		// ��ȡAXIS���״̬
		sRtn = GT_GetSts(AXIS, &sts);
		// ��ȡAXIS��Ĺ滮λ��
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		// ��ȡAXIS��Ĺ滮�ٶ�
		sRtn = GT_GetPrfVel(AXIS, &prfVel);
		printf("sts=0x%-10lxprfPos=%-10.1lfprfVel=%-10.1lf\r", sts, prfPos, prfVel);
	} 

	// �ŷ��ر�
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d\n", sRtn);

	getch();
	return 0;
}

