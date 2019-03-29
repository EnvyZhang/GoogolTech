// ���� 6-20 Continuous������ʽ
#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "gts.h"

#define AXIS_X		1
#define AXIS_Y		2
#define TABLE_X		1
#define TABLE_Y		2



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
	short sRtn;
	long mask;
	// X������ݵ����
	double pos_x[2] = {0, 30000};
	double vel_x[2] = {0, 0};
	double percent_x[2] = {100, 100};
	double velMax_x[2] = {10, 10};
	double acc_x[2] = {0.01, 0.01};
	double dec_x[2] = {0.01, 0.01};
	double time_x[2];
	double timeBegin_x;
	
	// Y������ݵ����
	double pos_y[2] = {0, 20000};
	double vel_y[2] = {0, 0};
	double percent_y[2] = {100, 100};
	double velMax_y[2] = {10, 10};
	double acc_y[2] = {0.01, 0.01};
	double dec_y[2] = {0.01, 0.01};
	double time_y[2];
	double timeBegin_y;
	double prfVel[2], prfPos[2], time[2];
	short tableId[2];
	
	// ���˶�������
	sRtn=GT_Open();
	commandhandler("GT_Open", sRtn);
	// ��λ�˶�������
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// �����˶�������
	// ע�⣺�����ļ�ȡ���˸���ı�������λ
	sRtn = GT_LoadConfig("test.cfg");
	commandhandler("GT_LoadConfig", sRtn);
	// ������ᱨ������λ
	sRtn = GT_ClrSts(1, 8);
	commandhandler("GT_ClrSts", sRtn);
	sRtn = GT_AxisOn(AXIS_X);
	commandhandler("GT_AxisOn", sRtn);
	sRtn = GT_AxisOn(AXIS_Y);
	commandhandler("GT_AxisOn", sRtn);
	// �ȴ��ŷ�ʹ�ܾ���
	Sleep(1000);
	// ��X������ΪPVTģʽ
	sRtn = GT_PrfPvt(AXIS_X);
	commandhandler("GT_PrfPvt", sRtn);
	// ��Y������ΪPVTģʽ
	sRtn = GT_PrfPvt(AXIS_Y);
	commandhandler("GT_PrfPvt", sRtn);
	// ����X���˶�ʱ��
	sRtn = GT_PvtContinuousCalculate(2, &pos_x[0], &vel_x[0], &percent_x[0], 	
			&velMax_x[0], &acc_x[0], &dec_x[0], &time_x[0]);
	commandhandler("GT_PvtContinuousCalculate", sRtn);
	// ����Y���˶�ʱ��
	sRtn = GT_PvtContinuousCalculate(2, &pos_y[0], &vel_y[0], &percent_y[0], 
			&velMax_y[0], &acc_y[0], &dec_y[0], &time_y[0]);
	commandhandler("GT_PvtContinuousCalculate", sRtn);
	// ����������ʱ
	if( time_x[1] < time_y[1] )
	{
		timeBegin_x = time_y[1] - time_x[1];
		timeBegin_y = 0;
	}
	else
	{
		timeBegin_x = 0;
		timeBegin_y = time_x[1] - time_y[1];
	}
	// ����X�����ݵ�
	sRtn = GT_PvtTableContinuous(TABLE_X, 2, &pos_x[0], &vel_x[0], &percent_x[0], 
			&velMax_x[0], &acc_x[0], &dec_x[0], timeBegin_x);
	commandhandler("GT_PvtTableContinuous", sRtn);
	// ����Y�����ݵ�
	sRtn = GT_PvtTableContinuous(TABLE_Y, 2, &pos_y[0], &vel_y[0], &percent_y[0], 
			&velMax_y[0], &acc_y[0], &dec_y[0], timeBegin_y);
	commandhandler("GT_PvtTableContinuous", sRtn);
	// X��ѡ�����ݱ�TABLE_X
	sRtn = GT_PvtTableSelect(AXIS_X, TABLE_X);
	commandhandler("GT_PvtTableSelect", sRtn);
	// Y��ѡ�����ݱ�TABLE_Y
	sRtn = GT_PvtTableSelect(AXIS_Y, TABLE_Y);
	commandhandler("GT_PvtTableSelect", sRtn);
	// ͬʱ����X���Y��
	// ����Y��ĵ�1�����ݵ�ʱ��Ϊ2000ms
	// ���X������2000ms�Ժ�Y��ſ�ʼ�˶�
	mask = 1<<(AXIS_X-1);
	mask |= 1<<(AXIS_Y-1);
	sRtn = GT_PvtStart(mask);
	commandhandler("GT_PvtStart", sRtn);
	while(!kbhit())
	{
		// ��ȡ���ݱ���˶�ʱ��
		sRtn = GT_PvtStatus(AXIS_X, &tableId[0], &time[0]);
		sRtn = GT_PvtStatus(AXIS_Y, &tableId[1], &time[1]);
		// ��ȡ�滮�ٶ�
		sRtn = GT_GetPrfVel(AXIS_X, &prfVel[0]);
		sRtn = GT_GetPrfVel(AXIS_Y, &prfVel[1]);
		// ��ȡ�滮λ��
		sRtn = GT_GetPrfPos(AXIS_X, &prfPos[0]);
		sRtn = GT_GetPrfPos(AXIS_Y, &prfPos[1]);
		printf("x:%2d %10.0lf %10.2lf %10.1lf y:%2d %10.0lf %10.2lf %10.1lf\r", 
			tableId[0], time[0], prfVel[0], prfPos[0], tableId[1], time[1], prfVel[1], prfPos[1]);
	}
	// �ŷ��ر�
	sRtn = GT_AxisOff(AXIS_X);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, AXIS_X);
	sRtn = GT_AxisOff(AXIS_Y);
	printf("GT_AxisOff()=%d, Axis:%d\n", sRtn, AXIS_Y);
	getch();

	return 0;
}
