
// ���� 8-5 HSIO�����÷�ʾ��
#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "gts.h"

#define AXIS					1 
#define AXIS_2					2

#define HSIO_OUTPUT_POS			1000  // hsio�ڱ�����λ1000ʱ���hsio�ź�

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
	long hsioOptPos[1];
	long mask;
	
	// ���˶������� 
	sRtn = GT_Open(); 
	// ��λ�˶������� 
	sRtn = GT_Reset(); 
	// �����˶������� 
	sRtn = GT_LoadConfig("test.cfg");

	hsioOptPos[0] = HSIO_OUTPUT_POS;
	// ����λ�ñȽ����ݣ�����λ�ñȽ����
	sRtn = GT_CompareData(	1,						// ��1�����λ�ñȽ����
							1,						// ��Ҫ���бȽϵ�����ԴΪ�ⲿ������
							0,						// ����Ƚ�λ�ú��������
							0,	 					// ��ʼ״̬Ϊ�͵�ƽ
							500,					// ������Ϊ500us
							hsioOptPos,				// HSIO0�ıȽ�λ�û�����������ʼ��ַ
							1,						// HSIO0�ıȽ�λ�û��������ݳ���
							NULL,
							0);
	// ����Hsio ���� 
	sRtn = GT_SetCaptureMode(AXIS_2, CAPTURE_HSIO0); 
	for (int i=1; i<=2; i++)
	{
		// ���ָ����ı�������λ 
		sRtn = GT_ClrSts(i); 
		// ������ʹ�� 
		sRtn = GT_AxisOn(i);
		// �л�����λ�˶�ģʽ 
		sRtn = GT_PrfTrap(i); 
		// ��ȡ�����õ�λģʽ�˶�����
		sRtn = GT_GetTrapPrm(i, &trapPrm); 
		trapPrm.acc = 0.25;
		trapPrm.dec = 0.25; 
		sRtn = GT_SetTrapPrm(i, &trapPrm); 
		// ���õ�λģʽĿ���ٶȣ����˶��ٶ� 
		sRtn = GT_SetVel(i, 10); 
		// ���õ�λģʽĿ��λ�ã�ʹHSIO�������
		sRtn = GT_SetPos(i, HSIO_OUTPUT_POS+500); 
		mask = mask | 1<<(i-1);
	}

	// �����˶� 
	sRtn = GT_Update(mask); 

	do 
	{
		// ��ȡ��״̬ 
		sRtn = GT_GetSts(AXIS, &status); 
		// ��ȡ����״̬ 
		sRtn = GT_GetCaptureStatus(AXIS_2, &capture, &pos); 
		// ��ȡ�滮λ�� 
		sRtn = GT_GetPrfPos(AXIS, &prfPos); 
		// ��ȡ������λ�� 
		sRtn = GT_GetEncPos(AXIS, &encPos); 
		printf("capture=%d prfPos=%lf encPos=%lf\r", capture, prfPos, encPos); 
		// �ȴ����񴥷�
	}while( 0 == capture ); 

	// ��ʾ����λ�� 
	printf("\nHsio captured pos = %ld\n", pos);
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, AXIS);
	sRtn = GT_AxisOff(AXIS_2);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, AXIS_2);

	getch();
	return 0;
}
