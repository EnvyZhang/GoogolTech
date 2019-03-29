// ���� 8-2 Home��ԭ��
#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "gts.h"

#define AXIS			1

#define SEARCH_HOME		-200000
#define HOME_OFFSET		-2000


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
	short sRtn, capture;
	TTrapPrm trapPrm;
	long status, pos;
	double prfPos, encPos, axisPrfPos, axisEncPos;
	// ���˶�������
	sRtn = GT_Open();
	commandhandler("GT_Open", sRtn);
	// ��λ�˶�������
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// �����˶�������
	// ע�⣺�����ļ�test.cfgȡ���˸���ı�������λ
	sRtn = GT_LoadConfig("test.cfg");
	commandhandler("GT_LoadConfig", sRtn);
	// ���ָ����ı�������λ
	sRtn = GT_ClrSts(AXIS);
	commandhandler("GT_ClrSts", sRtn);
	// ������ʹ��
	sRtn = GT_AxisOn(AXIS);
	commandhandler("GT_AxisOn", sRtn);
	// ����Home����
	sRtn = GT_SetCaptureMode(AXIS, CAPTURE_HOME);
	commandhandler("GT_SetCaptureMode", sRtn);
	// �л�����λ�˶�ģʽ
	sRtn = GT_PrfTrap(AXIS);
	commandhandler("GT_PrfTrap", sRtn);
	// ��ȡ��λģʽ�˶�����
	sRtn = GT_GetTrapPrm(AXIS, &trapPrm);
	commandhandler("GT_GetTrapPrm", sRtn);
	trapPrm.acc = 0.25;
	trapPrm.dec = 0.25;
	// ���õ�λģʽ�˶�����
	sRtn = GT_SetTrapPrm(AXIS, &trapPrm);
	commandhandler("GT_SetTrapPrm", sRtn);
	// ���õ�λģʽĿ���ٶȣ�����ԭ���ٶ�
	sRtn = GT_SetVel(AXIS, 10);
	commandhandler("GT_SetVel", sRtn);
	// ���õ�λģʽĿ��λ�ã���ԭ����������
	sRtn = GT_SetPos(AXIS, SEARCH_HOME);
	commandhandler("GT_SetPos", sRtn);
	// �����˶�
	sRtn = GT_Update(1<<(AXIS-1));
	commandhandler("GT_Update", sRtn);
	printf("\nWaiting for home signal...\n");
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
		printf("capture=%d prfPos=%.2lf encPos=%.2lf\r", capture, prfPos, encPos);
		// ����˶�ֹͣ�����س�����Ϣ
		if( 0 == ( status & 0x400 ) )
		{
			printf("\nno home found\n");
			getch();
			return 1;
		}
	// �ȴ����񴥷�
	}while( 0 == capture );
	// ��ʾ����λ��
	printf("\ncapture pos = %ld\n", pos);
	// �˶���"����λ��+ƫ����"
	sRtn = GT_SetPos(AXIS, pos + HOME_OFFSET);
	commandhandler("GT_SetPos", sRtn);
	// ���˶�״̬�¸���Ŀ��λ��
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
	// �ȴ��˶�ֹͣ
	}while( status & 0x400 );
	// ����Ƿ񵽴�"Home����λ��+ƫ����"
	if( prfPos != pos+HOME_OFFSET )
	{
		printf("\nmove to home pos error\n");
		getch();
		return 2;
	}
	printf("\nHome finish\n");
	// ��ʱһ��ʱ�䣬�ȴ����ͣ��
	Sleep(200);
	printf("\nPress any key to set pos as 0...\n");
	getch();
	// λ������
	sRtn = GT_ZeroPos(AXIS);
	commandhandler("GT_ZeroPos", sRtn);
	// ��ȡ�滮λ��
	sRtn = GT_GetPrfPos(AXIS, &prfPos);
	// ��ȡ������λ��
	sRtn = GT_GetEncPos(AXIS, &encPos);
	// ��ȡaxis�滮λ��
	sRtn = GT_GetAxisPrfPos(AXIS, &axisPrfPos);
	// ��ȡaxis������λ��
	sRtn = GT_GetAxisEncPos(AXIS, &axisEncPos);
	printf("\nprfPos=%-10.0lf encPos=%-10.0lf axisPrfPos=%-10.0lf axisEncPos=%-10.0lf", 
		prfPos, encPos, axisPrfPos, axisEncPos);
	// �ŷ��ر�
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d\n", sRtn);

	getch();
	return 0;
}
