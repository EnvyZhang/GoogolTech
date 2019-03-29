// ���� 8-1 Home/Index����
#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "gts.h"

#define ENCODER			1

// �ú������ĳ��GTָ���ִ�н����commandΪָ�����ƣ�errorΪָ��ִ�з���ֵ
void commandhandler(char *command, short error)
{
	// ���ָ��ִ�з���ֵΪ��0��˵��ָ��ִ�д�������Ļ���������
	if(error)
	{
		printf("%s = %d\n", command, error);
	}
}

void CaptureIndex(void)
{
	short sRtn, status;
	long pos;
	double encPos;

	// ����Index����
	sRtn = GT_SetCaptureMode(ENCODER, CAPTURE_INDEX);
	commandhandler("GT_SetCaptureMode", sRtn);

	printf("\n");

	do
	{
		// ��ѯ����״̬
		GT_GetCaptureStatus(ENCODER, &status, &pos);
		// ��ȡ������λ��
		// ��ָ��Ͳ����޹أ���������ʾ������λ��
		GT_GetEncPos(ENCODER, &encPos);
		// ��ʾ����״̬�ͱ�����λ��
		printf("status = %d enc = %-8.0lf\r", status, encPos);
		// ��ָ���Ჶ�񴥷�ʱ�˳�ѭ��
	}while( 0 == status );

	// ��ʾ����λ��
	printf("\ncapture = %-8ld\n", pos);
}

void CaptureHome(void)
{
	short sRtn, status;
	long pos;
	double encPos;

	// ����Home����
	sRtn = GT_SetCaptureMode(ENCODER, CAPTURE_HOME);
	commandhandler("GT_SetCaptureMode", sRtn);

	printf("\n");

	do
	{
		// ��ѯ����״̬
		GT_GetCaptureStatus(ENCODER, &status, &pos);
		// ��ȡ������λ��
		// ��ָ��Ͳ����޹أ���������ʾ������λ��
		GT_GetEncPos(ENCODER, &encPos);
		// ��ʾ����״̬�ͱ�����λ��
		printf("status = %d enc = %-8.0lf\r", status, encPos);
		// ��ָ���Ჶ�񴥷�ʱ�˳�ѭ��
	}while( 0 == status );
	// ��ʾ����λ��
	printf("\ncapture = %-8ld\n", pos);
}

int main(int argc, char* argv[])
{
	char ch;
	short sRtn;

	sRtn = GT_Open();
	commandhandler("GT_Open", sRtn);

	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	while(1)
	{
		// ѡ�񲶻�ģʽ��H��Home����I��Index����Q���˳�����
		printf("\n[H:Home|I:Index|Q:Quit]:");
		ch=toupper(getche());
		switch(ch)
		{
		case 'H': CaptureHome();break;
		case 'I': CaptureIndex(); break;
		case 'Q': return 0;
		}
	}
}
