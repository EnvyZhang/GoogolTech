// ���� 7-2 ��ȡ8����������͸���������λ��ֵ
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
	short sRtn, i;
	double enc[9];

	sRtn = GT_Open();
	commandhandler("GT_Open", sRtn);
	while(1)
	{
		// ��ȡ8����������λ��
		GT_GetEncPos(1, &enc[0], 8);
		// ��ȡ������������λ��
		GT_GetEncPos(9, &enc[8], 1);
		for(i=0;i<9;++i)
		{
			printf("%8.0lf", enc[i]);
		}
		printf("\r");
	}
	return 0;
}
