// ���� 7-4 ����ADC
#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "gts.h"

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
	// ָ���ֵ
	short sRtn;
	// ��ѹֵ
	double dGetVoltageValue[4];
	// ����ת��ֵ
	short sGetDigitalValue[4];

	sRtn = GT_Open();
	commandhandler("GT_Open", sRtn);
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// ��ȡ4��ͨ���������ѹ
	sRtn = GT_GetAdc(1, &dGetVoltageValue[0], 4);
	// ��ȡ4��ͨ�������ѹ������ת��ֵ
	sRtn = GT_GetAdcValue(1, &sGetDigitalValue[0], 4);

	return 0;
}
