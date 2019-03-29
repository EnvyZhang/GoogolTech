// ���� 6-4 PT��̬FIFO
#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include "math.h"
#include "gts.h"

#define AXIS		1

#define A			50				// ��ֵ
#define T			1				// ����
#define DELTA		0.016			// ʱ��ֶ�
#define LOOP		2				// ѭ������

#define PI			3.1415926

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
	short sRtn, space;
	double pos, vel, velPre, time;
	long sts;
	double prfPos, prfVel;
	short start, loop;

	// ���˶�������
	sRtn = GT_Open();
	// ָ���ֵ���
	commandhandler("GT_Open", sRtn);
	// �����˶�������
	// ע�⣺�����ļ�ȡ���˸���ı�������λ
	sRtn = GT_LoadConfig("test.cfg");
	commandhandler("GT_LoadConfig", sRtn);
	// �������ı�������λ
	sRtn = GT_ClrSts(1, 8);
	commandhandler("GT_ClrSts", sRtn);
	// �ŷ�ʹ��
	sRtn = GT_AxisOn(AXIS);
	commandhandler("GT_AxisOn", sRtn);
	// λ������
	sRtn = GT_ZeroPos(AXIS);
	commandhandler("GT_ZeroPos", sRtn);
	// ��AXIS����ΪPTģʽ
	sRtn = GT_PrfPt(AXIS, PT_MODE_DYNAMIC);
	commandhandler("GT_PrfPt", sRtn);
	// ���AXIS���FIFO
	sRtn = GT_PtClear(AXIS);
	commandhandler("GT_PtClear", sRtn);
	pos = 0;
	vel = velPre = 0;
	time = 0;
	start = 0;
	loop = 1;
	while(1)
	{
		// ��ѯPTģʽFIFO��ʣ��ռ�
		sRtn = GT_PtSpace(AXIS, &space);
		if( space > 0 )
		{
			time += DELTA;
			// �����ĩ�ٶ�
			vel = A*sin((2*PI)/T*time);
			// �������λ��
			pos += 1000*(vel+velPre)*DELTA/2;
			velPre = vel;
			if(time < loop*T)
			{
				// ����������
				sRtn = GT_PtData(AXIS, pos, (long)(time*1000));
				if( 0 != sRtn )
				{
					printf("\nGT_PtData()=%d\n", sRtn);
					getch();
					return 1;
				}
			}
			else
			{
				// �����յ�����
				sRtn = GT_PtData(AXIS, 0, loop*T*1000, PT_SEGMENT_STOP);
				if( 0 != sRtn )
				{
					printf("\nGT_PtData()=%d\n", sRtn);
					getch();
					return 1;
				}
				pos = 0;
				time = loop*T;
				velPre = 0;
				++loop;
				if( loop > LOOP )
				{
					break;
				}
			}
		}
		else if( 0 == start )
		{
			// ����PT�˶�
			sRtn = GT_PtStart(1<<(AXIS-1));
			commandhandler("GT_PtStart", sRtn);
			start = 1;
		}
		// ��ȡAXIS���״̬
		sRtn = GT_GetSts(AXIS, &sts);
		// ��ȡAXIS��Ĺ滮λ��
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		// ��ȡAXIS��Ĺ滮�ٶ�
		sRtn = GT_GetPrfVel(AXIS, &prfVel);
		printf("sts=0x%-10lxprfVel=%-10.2lfprfPos=%-10.1lf\r", sts, prfVel, prfPos);
	}

	while(!kbhit())
	{
		// ��ȡAXIS���״̬
		sRtn = GT_GetSts(AXIS, &sts);
		// ��ȡAXIS��Ĺ滮λ��
		sRtn = GT_GetPrfPos(AXIS, &prfPos);
		// ��ȡAXIS��Ĺ滮�ٶ�
		sRtn = GT_GetPrfVel(AXIS, &prfVel);
		printf("sts=0x%-10lxprfVel=%-10.2lfprfPos=%-10.1lf\r", sts, prfVel, prfPos);
	}
	// �ŷ��ر�
	sRtn = GT_AxisOff(AXIS);
	printf("\nGT_AxisOff()=%d\n", sRtn);
	getch();
	return 0;
}

