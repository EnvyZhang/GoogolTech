// ���� 8-6 �ظ�����ʹ��˵��
#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "gts.h"

#define AXIS					1 

#define HSIO_OUTPUT_POS			10000

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
	long status;
	long pos[5]; 
	double prfPos, encPos; 
	long hsioOptPos[5];
	int i;

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
	for(i=0;i<5;i++)
	{
		hsioOptPos[i] = (i+1)*1000;
	}
	// ����λ�ñȽ����ݣ�����λ�ñȽ����
	sRtn = GT_CompareData(	1,						// ��1�����λ�ñȽ����
							1,						// ��Ҫ���бȽϵ�����ԴΪ�ⲿ������
							0,						// ����Ƚ�λ�ú��������
							0,	 					// ��ʼ״̬Ϊ�͵�ƽ
							500,					// ������Ϊ500us
							hsioOptPos,				// HSIO0�ıȽ�λ�û�����������ʼ��ַ
							5,						// HSIO0�ıȽ�λ�û��������ݳ���
							NULL,
							0);
	// ����Hsio ���� 
	sRtn = GT_SetCaptureMode(AXIS, CAPTURE_HSIO0); 
	sRtn = GT_SetCaptureRepeat(AXIS, 5);
	// �л�����λ�˶�ģʽ 
	sRtn = GT_PrfTrap(AXIS); 
	// ��ȡ�����õ�λģʽ�˶�����
	sRtn = GT_GetTrapPrm(AXIS, &trapPrm); 
	trapPrm.acc = 0.25;
	trapPrm.dec = 0.25; 
	sRtn = GT_SetTrapPrm(AXIS, &trapPrm); 
	// ���õ�λģʽĿ���ٶȣ����˶��ٶ� 
	sRtn = GT_SetVel(AXIS, 10); 
	// ���õ�λģʽĿ��λ�ã�ʹHSIO�������
	sRtn = GT_SetPos(AXIS, HSIO_OUTPUT_POS); 
	// �����˶� 
	sRtn = GT_Update(1<<(AXIS-1)); 
	do 
	{
		// ��ȡ��״̬ 
		sRtn = GT_GetSts(AXIS, &status); 
		// ��ȡ����״̬ 
		sRtn = GT_GetCaptureRepeatStatus(AXIS, &capture); 
		// ��ȡ�滮λ�� 
		sRtn = GT_GetPrfPos(AXIS, &prfPos); 
		// ��ȡ������λ�� 
		sRtn = GT_GetEncPos(AXIS, &encPos); 
		printf("capture=%d prfPos=%lf encPos=%lf\r", capture, prfPos, encPos); 
	// �ȴ����񴥷�
	}while( capture < 5 ); 
	// ��ȡ����λ��ֵ
	sRtn = GT_GetCaptureRepeatPos(1, pos, 1, 5);
	for(i=0;i<5;i++)
	{
		// ��ʾ����λ�� 
		printf("\nNo. %d Hsio captured pos = %ld\n", i, pos[i]); 
	}
	// �ŷ��ر�
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d\n", sRtn);

	getch();
	return 0;
}
