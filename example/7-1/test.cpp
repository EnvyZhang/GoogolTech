// ���� 7-1 ��������IO
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
	// ͨ�������ȡֵ
	long lGpiValue;
	// ����λ����仯����
	unsigned long lPosLmtReverseCount;
	// ����λ����仯����
	unsigned long lNegLmtReverseCount;

	// ���˶�������
	sRtn = GT_Open();
	// ָ���ֵ���
	commandhandler("GT_Open", sRtn);
	// ϵͳ��λ
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);

	// ��ʼ���仯����Ϊ0
	lPosLmtReverseCount = 0;
	lNegLmtReverseCount = 0;

	// ��ȡEXI3����ֵ
	sRtn = GT_GetDi(MC_GPI, &lGpiValue);
	// �˺���Ϊ���ָ���ֵ�������ο����� 2 1���GTָ���Ƿ�����ִ��
	commandhandler("GT_GetDi" , sRtn);
	// ���Ϊ�ߵ�ƽ��˵���������ڱ����£��򲻼�⣬����1
	if( lGpiValue & (1<<3))
		return 1;
	// EXO6����ߵ�ƽ��ʹָʾ����
	sRtn = GT_SetDo(MC_GPO, 1<<6);
	commandhandler("GT_SetDo" , sRtn);
	// ����û�б����£�ѭ�������EXI3����ֵΪ�ߵ�ƽ�����������£����˳�ѭ��
	while( ! (lGpiValue & (1<<3)))
	{
		// ��ȡ����λ����仯����
		sRtn = GT_GetDiReverseCount(
			MC_LIMIT_POSITIVE,			// ָ������IO����������λ
			1,							// ָ������λ1
			&lPosLmtReverseCount,		// ��ȡ��ֵ
			1);							// һ�ζ�һ������������
		commandhandler("GT_GetDiReverseCount" , sRtn);
		// ��ȡ����λ����仯����
		sRtn = GT_GetDiReverseCount(
			MC_LIMIT_NEGATIVE,			// ָ������IO�����Ǹ���λ
			1,							// ָ������λ1
			&lNegLmtReverseCount,		// ��ȡ��ֵ
			1);							// һ�ζ�һ������������
		commandhandler("GT_GetDiReverseCount" , sRtn);
		// ������������ʾ��
		printf("PosLmtReverseCount = %d\n NegLmtReverseCount = %d\n", 
			lPosLmtReverseCount, lNegLmtReverseCount);
		// ���������λ������仯����������10��
		if(( lPosLmtReverseCount >= 10) &&( lNegLmtReverseCount >= 10) )
		{
			// ���¹�Ϊ0
			lPosLmtReverseCount = 0;
			lNegLmtReverseCount = 0;
			// ��������λ����仯����
			sRtn = GT_SetDiReverseCount(
				MC_LIMIT_POSITIVE,		// ָ������IO����������λ
				1,						// ָ������λ1
				&lPosLmtReverseCount,	// ��ȡ��ֵ
				1);						// һ������һ������������
			commandhandler("GT_SetDiReverseCount" , sRtn);
			// ���ø���λ����仯����
			sRtn = GT_SetDiReverseCount(
				MC_LIMIT_NEGATIVE,	// ָ������IO�����Ǹ���λ
				1,						// ָ������λ1
				&lNegLmtReverseCount,	// ��ȡ��ֵ
				1);						// һ������һ������������
			commandhandler("GT_SetDiReverseCount" , sRtn);
			// EXO6����ߵ�ƽ��ʹָʾ����
			sRtn = GT_SetDoBit(
				MC_GPO,				// ָ������IO������ͨ�����
				7,						// ָ����7��ͨ���������EXO6
				0);						// ����͵�ƽ
			commandhandler("GT_SetDoBit" , sRtn);
		}
		// ���϶�ȡͨ�����룬�Ѽ��EXI3�ĵ�ƽ״̬
		sRtn = GT_GetDi(MC_GPI, &lGpiValue);
		commandhandler("GT_GetDi" , sRtn);
	}
	getch();
	return 0;

}
