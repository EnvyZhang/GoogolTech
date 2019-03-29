// ���� 11-2 �����λ��⹦��
#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "gts.h"

#define AXIS_X		1
#define AXIS_Y		2

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
	TPid pid;
	TTrapPrm trap;
	long sts;
	long posX, posY;
	double prfPos, prfVel;
	
	// ���˶�������
	sRtn = GT_Open();
	commandhandler("GT_Open", sRtn);
	// ��λ������
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// �����˶�������Ϊ�ŷ�ģʽ
	sRtn = GT_LoadConfig("servo.cfg");
	commandhandler("GT_LoadConfig", sRtn);
	// ��ʱһ��ʱ��
	Sleep(100);
	// �������ı�������λ
	sRtn = GT_ClrSts(1, 8);
	commandhandler("GT_ClrSts", sRtn);
	// ��ȡX��PID����
	sRtn = GT_GetPid(AXIS_X, 1, &pid);
	commandhandler("GT_GetPid", sRtn);
	pid.kp = 10;
	// ����X��PID����
	sRtn = GT_SetPid(AXIS_X, 1, &pid);
	commandhandler("GT_SetPid", sRtn);
	// ��ȡY��PID����
	sRtn = GT_GetPid(AXIS_Y, 1, &pid);
	commandhandler("GT_GetPid", sRtn);
	pid.kp = 10;
	// ����Y��PID����
	sRtn = GT_SetPid(AXIS_Y, 1, &pid);
	commandhandler("GT_SetPid", sRtn);
	// X���ŷ�ʹ��
	sRtn = GT_AxisOn(AXIS_X);
	commandhandler("GT_AxisOn", sRtn);
	// Y���ŷ�ʹ��
	sRtn = GT_AxisOn(AXIS_Y);
	commandhandler("GT_AxisOn", sRtn);
	// ��ʱһ��ʱ�䣬�ȴ��ŷ��ȶ�
	Sleep(200);
	// λ������, �������Զ���Ư����
	sRtn = GT_ZeroPos(AXIS_X);
	commandhandler("GT_ZeroPos", sRtn);
	// ����X�ᵽλ����
	sRtn = GT_SetAxisBand(AXIS_X, 20, 5);
	commandhandler("GT_SetAxisBand", sRtn); 
	// λ������, �������Զ���Ư����
	sRtn= GT_ZeroPos(AXIS_Y);
	commandhandler("GT_ZeroPos", sRtn);
	// ����Y�ᵽλ����
	sRtn = GT_SetAxisBand(AXIS_Y, 20, 5);
	commandhandler("GT_SetAxisBand", sRtn);
	// X����Ϊ��λģʽ
	sRtn = GT_PrfTrap(AXIS_X);
	commandhandler("GT_PrfTrap", sRtn);
	// ��ȡX���λ�˶�����
	sRtn = GT_GetTrapPrm(AXIS_X, &trap);
	commandhandler("GT_GetTrapPrm", sRtn);
	trap.acc = 1;
	trap.dec = 0.5;
	// ����X���λ�˶�����
	sRtn = GT_SetTrapPrm(AXIS_X, &trap);
	commandhandler("GT_SetTrapPrm", sRtn);
	// ����X���Ŀ���ٶ�
	sRtn = GT_SetVel(AXIS_X, 10);
	commandhandler("GT_SetVel", sRtn);
	// Y����Ϊ��λģʽ
	sRtn = GT_PrfTrap(AXIS_Y);
	commandhandler("GT_PrfTrap", sRtn);
	// ��ȡY���λ�˶�����
	sRtn = GT_GetTrapPrm(AXIS_Y, &trap);
	commandhandler("GT_GetTrapPrm", sRtn);
	trap.acc = 1;
	trap.dec = 0.5;
	// ����Y���λ�˶�����
	sRtn = GT_SetTrapPrm(AXIS_Y, &trap);
	commandhandler("GT_SetTrapPrm", sRtn);
	// ����Y���Ŀ���ٶ�
	sRtn = GT_SetVel(AXIS_Y, 10);
	commandhandler("GT_SetVel", sRtn);

	posX = 10000;
	posY = 20000;
	while(!kbhit())
	{
		// ����X��Ŀ��λ��
		sRtn = GT_SetPos(AXIS_X, posX);
		commandhandler("GT_SetPos", sRtn);
		// ����X����˶�
		sRtn = GT_Update(1<<(AXIS_X-1));
		commandhandler("GT_Update", sRtn);

		posX = - posX;

		// �ȴ�X���������
		do
		{
		GT_GetSts(AXIS_X, &sts);
		GT_GetPrfPos(AXIS_X, &prfPos);
		GT_GetPrfVel(AXIS_X, &prfVel);
			printf("x pos=%-10.2lf vel=%-6.2lf\r", prfPos, prfVel);
		}while( 0x800 != ( sts & 0x800 ) );

		printf("\n");
		// ����Y��Ŀ��λ��
		sRtn = GT_SetPos(AXIS_Y, posY);
		commandhandler("GT_SetPos", sRtn);
		// ����Y����˶�
		sRtn = GT_Update(1<<(AXIS_Y-1));
		commandhandler("GT_Update", sRtn);

		posY = - posY;
		// �ȴ�Y���������
		do
		{
		GT_GetSts(AXIS_Y, &sts);
		GT_GetPrfPos(AXIS_Y, &prfPos);
		GT_GetPrfVel(AXIS_Y, &prfVel);
			printf("y pos=%-10.2lf vel=%-6.2lf\r", prfPos, prfVel);
		}while( 0x800 != ( sts & 0x800 ) );
		printf("\n");
	}
	//�ŷ��ر�
	sRtn = GT_AxisOff(AXIS_X);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, AXIS_X);
	sRtn = GT_AxisOff(AXIS_Y);
	printf("\nGT_AxisOff()=%d, Axis:%d\n", sRtn, AXIS_Y);

	return 0;
}
