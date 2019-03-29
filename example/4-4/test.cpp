// ���� 4-4 ���õ�1��Ϊ�ջ����Ʒ�ʽ
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
	// PID�ṹ�����
	TPid pid;
	// ���˶�������
	sRtn = GT_Open();
	// ָ���ֵ���
	commandhandler("GT_Open", sRtn);
	// ϵͳ��λ
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// ������1Ϊģ�������ģʽ
	sRtn = GT_CtrlMode(1, 0);
	commandhandler("GT_CtrlMode", sRtn);
	// ������1���������Ч
	sRtn = GT_AlarmOff(1);
	commandhandler("GT_AlarmOff", sRtn);
	// ������1������λ��Ч
	sRtn = GT_LmtsOff(1, -1);	
	commandhandler("GT_LmtsOff", sRtn);
	// ������ɺ�Ҫ����״̬
	sRtn = GT_ClrSts(1);	
	commandhandler("GT_ClrSts", sRtn);
	// ��ȡ��ǰpid����
	sRtn = GT_GetPid(1, 1, &pid);	
	commandhandler("GT_GetPid", sRtn);
	// ���Խ׶Σ�ֻ���޸�һ��kp��һ����С��ֵ
	pid.kp = 1;
	// ����PID����
	sRtn = GT_SetPid(1, 1, &pid);
	commandhandler("GT_SetPid", sRtn);
	// ��1�ŷ�ʹ��
	sRtn = GT_AxisOn(1);
	commandhandler("GT_AxisOn", sRtn);
	// �ŷ�ʹ�ܺ������ַɳ�������Ҫͨ������GT_EncSns()ָ�����޸ı�������������
	// �ȴ��ŷ��ȶ�
	Sleep(200);

	return 0;
}
