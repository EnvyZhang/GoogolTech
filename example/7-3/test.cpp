// ���� 7-3 ����DAC
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
	short sSetValue;
	short sGetValue;

	sRtn = GT_Open();
	commandhandler("GT_Open", sRtn);
	// ��������λ�������ᶼΪ�������ģʽ
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// ������4�ĵ�ѹ���ֵ
	sSetValue = (short) 32767*5/10;
	// ������4�������ѹ
	sRtn = GT_SetDac(4, &sSetValue, 1);
	// ��ȡ��4�������ѹֵ
	sRtn = GT_GetDac(4, &sGetValue, 1);

	return 0;
}
