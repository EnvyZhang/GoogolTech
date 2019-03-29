// ���� 11-1 ��ȡ�˶��������汾��
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
	short sRtn;
	char *pVersion;								// ����ָ��汾���ַ�����ָ��

	// ���˶�������
	sRtn = GT_Open();
	// ָ���ֵ���
	commandhandler("GT_Open", sRtn);
	// ϵͳ��λ
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	sRtn = GT_GetVersion(&pVersion);			// ��ȡ�汾��
	commandhandler("GT_GetVersion", sRtn);
	printf("%s\n", pVersion);
	sRtn = GT_Close();
	commandhandler("GT_Close", sRtn);
	
	return TRUE;

}
