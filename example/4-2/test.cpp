// ���� 4-2 �޸���λ���ش�����ƽ
#include "windows.h"
#include "stdio.h"
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
	// ָ���ֵ����
	short sRtn;
	// ״ֵ̬����
	unsigned short sValue;

	sRtn = GT_Open();
	// ָ���ֵУ��
	commandhandler("GT_Open", sRtn);
	sRtn = GT_Reset();
	// ָ���ֵУ��
	commandhandler("GT_Reset", sRtn);

	// ��ʼ��ʹ����λ��Ϊ0
	sValue = 0;
	// ʹ��0, 1λΪ1������1������λ����Ӧ��λ
	sValue |= 0x3;
	// ʹ��6, 7λΪ1������4������λ����Ӧ��λ
	sValue |= 1<<6;
	sValue |= 1<<7;
	// ������λ���ش�����ƽ
	sRtn = GT_LmtSns(sValue);
	// ָ���ֵУ��
	commandhandler("GT_LmtSns", sRtn);

	return 0;
}
