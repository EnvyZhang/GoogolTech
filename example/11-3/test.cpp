// ���� 11-3 �Զ���ԭ��
#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include "gts.h"

#define AXIS				1				// �������
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
	unsigned short sts1, sts2;
	sRtn = GT_Open();						// ���˶�������
	sRtn = GT_Reset();						// ��λ�˶�������
	sRtn = GT_LoadConfig("test.cfg");		// ���������ļ�
	sRtn = GT_ClrSts(1, 8);					// ���״̬
	sRtn = GT_HomeInit();					// ��ʼ���Զ���ԭ�㹦��
	sRtn = GT_AxisOn(1);						// ʹ����1
	sRtn = GT_AxisOn(2);						// ʹ����2
	sRtn = GT_Index(1, 20000, 2000);			// ��1ΪHome+Index����ģʽ
	sRtn = GT_Home(1, 200000, 50, 0.5, 2000);
	sRtn = GT_Home(2, 200000, 50, 0.5, 3000);// ��2ΪHome����ģʽ
	while (!kbhit())
	{
		sRtn = GT_HomeSts(1, &sts1);			// ��ѯ����״̬
		sRtn = GT_HomeSts(2, &sts2);
		printf("%d %d %d\r", sts1, sts2, sRtn);
	}
	// �ŷ��ر�
	sRtn = GT_AxisOff(1);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, 1);
	sRtn = GT_AxisOff(2);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, 2);
	
	getch();
	return 0;
}
