// ���� 8-3 Home+Index��ԭ��
#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "gts.h"

// �������
#define AXIS						1
// ����home������������
#define SEARCH_HOME					-200000
// ���嵽home����λ�õ�ƫ����
#define HOME_OFFSET					-2000
// ����index������������
#define SEARCH_INDEX				15000
// ���嵽index����λ�õ�ƫ����
#define INDEX_OFFSET				1000



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
	// ���巵��ֵ����
	short sRtn;
	// ����״̬
	short capture;
	// ��λ�˶������ṹ��
	TTrapPrm trapPrm;
	// ��״̬
	long status;
	// ����λ��
	long pos;
	// �ֱ��ǹ滮λ�ã�������λ�ã���Ĺ滮λ�ã���ı�����λ��
	double prfPos, encPos, axisPrfPos, axisEncPos;
	// ���˶�������
	sRtn = GT_Open();
	commandhandler("GT_Open", sRtn);
	// ��λ
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// ���������ļ�
	sRtn = GT_LoadConfig("test.cfg");
	commandhandler("GT_LoadConfig", sRtn);
	// ��״̬
	sRtn = GT_ClrSts(AXIS);
	commandhandler("GT_ClrSts", sRtn);
	// ���ŷ�ʹ��
	sRtn = GT_AxisOn(AXIS);
	commandhandler("GT_AxisOn", sRtn);
	// �������home������
	sRtn = GT_SetCaptureMode(AXIS, CAPTURE_HOME);
	commandhandler("GT_SetCaptureMode", sRtn);
	// ������Ϊ��λ�˶�ģʽ
	sRtn = GT_PrfTrap(AXIS);
	commandhandler("GT_PrfTrap", sRtn);
	// ��ȡ��λ�˶�����
	sRtn = GT_GetTrapPrm(AXIS, &trapPrm);
	commandhandler("GT_GetTrapPrm", sRtn);

	trapPrm.acc = 0.25;
	trapPrm.dec = 0.25;
	// ���õ�λ�˶�����
	sRtn = GT_SetTrapPrm(AXIS, &trapPrm);
	commandhandler("GT_SetTrapPrm", sRtn);
	// ����Ŀ���ٶ�
	sRtn = GT_SetVel(AXIS, 10);
	commandhandler("GT_SetVel", sRtn);
	// ����Ŀ��λ��
	sRtn = GT_SetPos(AXIS, SEARCH_HOME);
	commandhandler("GT_SetPos", sRtn);
	// �����˶����ȴ�home�źŴ���
	sRtn = GT_Update(1<<(AXIS-1));
	commandhandler("GT_Update", sRtn);
	printf("\nWaiting for home signal...\n");
	// ���home����û�д�������һֱѭ��
	do
	{
		// ��ȡ��״̬
		sRtn = GT_GetSts(AXIS, &status);
		// ��ȡ����״̬
		sRtn = GT_GetCaptureStatus(AXIS, &capture, &pos);
		// ��ȡ�滮λ��
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		// ��ȡ������λ��
		sRtn = GT_GetEncPos(AXIS, &encPos);
		printf("capture=%d prfPos=%-10.1lf encPos=%-10.1lf\r", capture, prfPos, encPos);
		// ����Ѿ�ֹͣ��˵����������������home�ź�һֱû�д���
		if( 0 == ( status & 0x400 ) )
		{
			printf("\nno home found");
			return 1;
		}
	// ���home�ź��Ѿ����������˳�ѭ��������λ���Ѿ���pos�����б���
	}while( 0 == capture );
	printf("\ncapture pos = %ld\n", pos);
	// �趨Ŀ��λ��Ϊ����λ��+ƫ����
	sRtn = GT_SetPos(AXIS, pos + HOME_OFFSET);
	commandhandler("GT_SetPos", sRtn);
	// �����˶�
	sRtn = GT_Update(1<<(AXIS-1));
	commandhandler("GT_Update", sRtn);

	do
	{
		// ��ȡ��״̬
		sRtn = GT_GetSts(AXIS, &status);
		// ��ȡ�滮λ��
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		// ��ȡ������λ��
		sRtn = GT_GetEncPos(AXIS, &encPos);
		printf("status=0x%-8lx prfPos=%-10.1lf encPos=%-10.1lf\r", status, prfPos, encPos);
	}while( status & 0x400 );

	if( prfPos != pos + HOME_OFFSET) 
	{
		printf("\nmove to home pos error");
		return 2;
	}
	// home�������
	printf("\nHome finish\n");
	Sleep(200);
	// ����index����
	sRtn = GT_SetCaptureMode(AXIS, CAPTURE_INDEX);
	commandhandler("GT_SetCaptureMode", sRtn);
	// ���õ�ǰλ��+index��������ΪĿ��λ��
	sRtn = GT_SetPos(AXIS, (long)(prfPos + SEARCH_INDEX));
	commandhandler("GT_SetPos", sRtn);
	// �����˶�
	sRtn = GT_Update(1<<(AXIS-1));
	commandhandler("GT_Update", sRtn);
	// �ȴ�index�����źŴ���
	printf("\nWaiting for index signal...\n");	

	do
	{
		// ��ȡ��״̬
		sRtn = GT_GetSts(AXIS, &status);
		// ��ȡ����״̬
		sRtn = GT_GetCaptureStatus(AXIS, &capture, &pos);
		// ��ȡ�滮λ��
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		// ��ȡ������λ��
		sRtn = GT_GetEncPos(AXIS, &encPos);
		printf("capture=%d prfPos=%-10.1lf encPos=%-10.1lf\r", capture, prfPos, encPos);
		// ����Ѿ�ֹͣ��˵����������������index�ź�һֱû�д���
		if( 0 == ( status & 0x400 ) )
		{
			printf("\nno index found\n");
			getch();
			return 1;
		}
	// ���index�ź��Ѿ����������˳�ѭ��������λ���Ѿ���pos�����б���
	}while( 0 == capture );

	printf("\ncapture pos = %ld\n", pos);
	// ���ò���λ��+indexƫ����ΪĿ��λ��
	sRtn = GT_SetPos(AXIS, pos+ INDEX_OFFSET);
	commandhandler("GT_SetPos", sRtn);
	// �����˶�
	sRtn = GT_Update(1<<(AXIS-1));
	commandhandler("GT_Update", sRtn);

	do
	{
		// ��ȡ��״̬
		sRtn = GT_GetSts(AXIS, &status);
		// ��ȡ�滮λ��
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		// ��ȡ������λ��
		sRtn = GT_GetEncPos(AXIS, &encPos);
		printf("status=0x%-8lx prfPos=%-10.1lf encPos=%-10.1lf\r", status, prfPos, encPos);
	}while( status & 0x400 );

	if( prfPos != pos+ INDEX_OFFSET) 
	{
		printf("\nmove to index pos error\n");
		getch();
		return 2;
	}
	// home+index�������
	printf("\nHome+Index finish\n");
	printf("\nPress any key to set pos as 0...\n");
	getch();

	Sleep(200);
	// ����ԭ��λ��
	sRtn = GT_ZeroPos(AXIS);
	printf("GT_ZeroPos", sRtn);

	sRtn = GT_GetPrfPos(AXIS, &prfPos);
	sRtn = GT_GetEncPos(AXIS, &encPos);
	sRtn = GT_GetAxisPrfPos(AXIS, &axisPrfPos);
	sRtn = GT_GetAxisEncPos(AXIS, &axisEncPos);
	printf("\nprfPos=%-10.0lf encPos=%-10.0lf axisPrfPos=%-10.0lf axisEncPos=%-10.0lf", 
		prfPos, encPos, axisPrfPos, axisEncPos);
	// �ŷ��ر�
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d\n", sRtn);

	getch();
	return 0;
}
