// ���� 4-1 �޸ı�������������
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

	// ��ʼ��ʹ����λ��Ϊ1
	sValue = 0xffff;
	// ʹ��0λΪ0������1����Ӧ��λ
	sValue &= ~(1);
	// ʹ��3λΪ0������4����Ӧ��λ
	sValue &= ~(1<<3);
	// ���ñ�������������
	sRtn = GT_EncSns(sValue);
	// ָ���ֵУ��
	commandhandler("GT_EncSns", sRtn);

	return 0;
}
