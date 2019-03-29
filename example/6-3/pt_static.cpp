// ���� 6-3 PT��̬FIFO
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
	short sRtn, space;
	double pos;
	long time;
	long sts;
	double prfPos, prfVel;

	// ���˶�������
	sRtn = GT_Open();
	// ָ���ֵ���
	commandhandler("GT_Open", sRtn);
	// ��λ������
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);	
	// �����˶�������
	// ע�⣺�����ļ�ȡ���˸���ı�������λ
	sRtn = GT_LoadConfig("test.cfg");
	commandhandler("GT_LoadConfig", sRtn); 
	// �������ı�������λ
	sRtn = GT_ClrSts(1, 8);
	commandhandler("GT_ClrSts", sRtn);
	// �ŷ�ʹ��
	sRtn = GT_AxisOn(AXIS);
	commandhandler("GT_AxisOn", sRtn);
	// λ������
	sRtn = GT_ZeroPos(AXIS);
	commandhandler("GT_ZeroPos", sRtn); 
	// ��AXIS����ΪPTģʽ
	sRtn = GT_PrfPt(AXIS);
	commandhandler("GT_PrfPt", sRtn); 
	// ���AXIS���FIFO
	sRtn = GT_PtClear(AXIS);
	commandhandler("GT_PtClear", sRtn); 
	// ��ѯPTģʽFIFO��ʣ��ռ�
	sRtn = GT_PtSpace(AXIS, &space);
	printf("GT_PtSpace()=%d\tspace=%d\n", sRtn, space);
	// ��FIFO�������˶�����
	pos = 1024;
	time = 1024;
	sRtn = GT_PtData(AXIS, pos, time);
	commandhandler("GT_PtData", sRtn);
	// ��ѯPTģʽFIFO��ʣ��ռ�
	sRtn = GT_PtSpace(AXIS, &space);
	printf("GT_PtSpace()=%d\tspace=%d\n", sRtn, space);
	// ��FIFO�������˶�����
	pos += 2048;
	time += 1024;
	sRtn = GT_PtData(AXIS, pos, time);
	commandhandler("GT_PtData", sRtn);
	// ��ѯPTģʽFIFO��ʣ��ռ�
	sRtn = GT_PtSpace(AXIS, &space);
	printf("GT_PtSpace()=%d\tspace=%d\n", sRtn, space);
	// ��FIFO�������˶�����
	pos += 1024;
	time += 1024;
	sRtn = GT_PtData(AXIS, pos, time);
	commandhandler("GT_PtData", sRtn);
	// ����PT�˶�
	sRtn = GT_PtStart(1<<(AXIS-1));
	commandhandler("GT_PtStart", sRtn);

	while(!kbhit())
	{
		// ��ȡAXIS���״̬
		sRtn = GT_GetSts(AXIS, &sts);
		// ��ȡAXIS��Ĺ滮λ��
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		// ��ȡAXIS��Ĺ滮�ٶ�
		sRtn = GT_GetPrfVel(AXIS, &prfVel);
		printf("sts=0x%-10lxprfVel=%-10.2lfprfPos=%-10.1lf\r", sts, prfVel, prfPos);
	}

	// �ŷ��ر�
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d\n", sRtn);
	getch();
	return 0;

}

