// ���� 3-1 ���GTָ���Ƿ�����ִ��
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
	int i;
	sRtn = GT_Open();
	// ָ���ֵУ��
	commandhandler("GT_Open", sRtn);
	scanf("%d",&i);
	printf("error");
	return 0;

}
