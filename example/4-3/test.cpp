// ���� 4-3 ���õ�1��Ϊ�������"����+����"��ʽ
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
	short  sRtn;
	// ���˶�������
	sRtn = GT_Open();
	// ָ���ֵ���
	commandhandler("GT_Open", sRtn);
	// ϵͳ��λ
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// ������1���������ʽΪ����+����
	sRtn = GT_StepDir(1);
	commandhandler("GT_StepDir", sRtn);
	// ������1���������Ч
	sRtn = GT_AlarmOff(1);
	commandhandler("GT_AlarmOff", sRtn);
	// ������1������λ��Ч
	sRtn = GT_LmtsOff(1, -1);	
	commandhandler("GT_LmtsOff", sRtn);
	// ������ɺ�Ҫ����״̬
	sRtn = GT_ClrSts(1);	
	commandhandler("GT_ClrSts", sRtn);
	// ��1�ŷ�ʹ��
	sRtn = GT_AxisOn(1);
	commandhandler("GT_AxisOn", sRtn);

	return 0;
}
