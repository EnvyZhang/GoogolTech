// ���� 9-1 ����λʹ��
#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include "gts.h"

#define AXIS		1

int main(int argc, char* argv[])
{
	// ָ���ֵ
	short sRtn;
	// ��״̬����
	long sts;
	// ��λ�˶��ṹ�����
	TTrapPrm trap;
	// �滮λ��
	double prfPos;

	// ���˶�������
	sRtn = GT_Open();
	// ��λ
	sRtn = GT_Reset();
	// ����������
	sRtn = GT_LoadConfig("test.cfg");
	// �����״̬
	sRtn = GT_ClrSts(1, 8);
	// ��������λ
	sRtn = GT_SetSoftLimit(AXIS, 20000, -20000);
	// ����һ������Ϊ��λ�˶�ģʽ
	sRtn = GT_PrfTrap(AXIS);
	// ���õ�λ�˶�����
	sRtn = GT_GetTrapPrm(AXIS, &trap);
	trap.acc = 0.125;
	trap.dec = 0.125;
	sRtn = GT_SetTrapPrm(AXIS, &trap);
	// ���õ�λ�˶�Ŀ���ٶ�
	sRtn = GT_SetVel(AXIS, 50);
	// ���õ�λ�˶�Ŀ��λ��
	sRtn = GT_SetPos(AXIS, 1000000L);
	// ������λ�˶�
	sRtn = GT_Update(1<<(AXIS-1));

	while(!kbhit())
	{
		// ��ȡ��һ����״̬
		sRtn = GT_GetSts(AXIS, &sts);
		// ��ȡ��һ��滮λ��
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		printf("sts=0x%-8lx prfPos=%-10.2lf\r", sts, prfPos);
	}
	return 0;
}


