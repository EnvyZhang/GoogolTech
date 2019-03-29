// ���� 8-4 ̽�벶��
#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "gts.h"

#define AXIS					1 

#define SEARCH_PROBE		-2000000  // �����ڸ�·�������ҵ�̽���ź�

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
	double prfPos, encPos; 

	// ���˶������� 
	sRtn = GT_Open(); 
	// ��λ�˶������� 
	sRtn = GT_Reset(); 
	// �����˶������� 
	sRtn = GT_LoadConfig("test.cfg");
	// ���ָ����ı�������λ 
	sRtn = GT_ClrSts(AXIS); 
	// ������ʹ�� 
	sRtn = GT_AxisOn(AXIS);
	// ����Probe ���� 
	sRtn = GT_SetCaptureMode(AXIS, CAPTURE_PROBE); 
	// �л�����λ�˶�ģʽ 
	sRtn = GT_PrfTrap(AXIS); 
	// ��ȡ�����õ�λģʽ�˶�����
	sRtn = GT_GetTrapPrm(AXIS, &trapPrm); 
	trapPrm.acc = 0.25;
	trapPrm.dec = 0.25; 
	sRtn = GT_SetTrapPrm(AXIS, &trapPrm); 
	// ���õ�λģʽĿ���ٶȣ�����ԭ���ٶ� 
	sRtn = GT_SetVel(AXIS, 10); 
	// ���õ�λģʽĿ��λ�ã���ԭ���������� 
	sRtn = GT_SetPos(AXIS, SEARCH_PROBE); 
	// �����˶� 
	sRtn = GT_Update(1<<(AXIS-1)); 
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
		printf("capture=%d prfPos=%lf encPos=%lf\r", capture, prfPos, encPos); 
		// ����˶�ֹͣ�����س�����Ϣ 
		if( 0 == ( status & 0x400 ) ) 
		{ 
		printf("\nno Probe found\n"); 
		getch(); 
		return 1; 
		} 
	// �ȴ����񴥷�
	}while( 0 == capture ); 
	// ��ʾ����λ�� 
	printf("\nProbe captured pos = %ld\n", pos); 
	// �ŷ��ر�
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d\n", sRtn);

	getch();
	return 0;
}
