// ���� 5-1 ��ȡ��1����״̬���˶�ģʽ��λ�á��ٶȺͼ��ٶ�
#include "windows.h"
#include "stdio.h"
#include "gts.h"

#define AXIS				1			// �������
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
	short bFlagAlarm = FALSE;			// �ŷ�������־
	short bFlagMError = FALSE;			// �������Խ�ޱ�־
	short bFlagPosLimit = FALSE;		// ����λ������־
	short bFlagNegLimit = FALSE;		// ����λ������־
	short bFlagSmoothStop = FALSE;		// ƽ��ֹͣ��־
	short bFlagAbruptStop = FALSE;		// ��ͣ��־
	short bFlagServoOn = FALSE;			// �ŷ�ʹ�ܱ�־
	short bFlagMotion = FALSE;			// �滮���˶���־
	double dPrfPos;						// �滮λ��
	double dPrfVel;						// �滮�ٶ�
	double dPrfAcc;						// �滮���ٶ�
	long lPrfMode;						// �˶�ģʽ
	char chPrfMode[20];					// �˶�ģʽ���ַ�������
	short sRtn;							// ָ���ֵ����
	long lAxisStatus;					// ��״̬

	// ���˶�������
	sRtn = GT_Open();
	// ָ���ֵ���
	commandhandler("GT_Open", sRtn);
	// ϵͳ��λ
	sRtn = GT_Reset();
	commandhandler("GT_Reset", sRtn);
	// ��ȡ��״̬
	sRtn = GT_GetSts(AXIS, &lAxisStatus);
	commandhandler("GT_GetSts" , sRtn);

	// �ŷ�������־
	if (lAxisStatus & 0x2)
	{
		bFlagAlarm = TRUE;
		printf("�ŷ�����\n");
	}
	else
	{
		bFlagAlarm = FALSE;
		printf("�ŷ�����\n");
	}
	// �������Խ�ޱ�־
	if (lAxisStatus & 0x10)
	{
		bFlagMError = TRUE;
		printf("�˶�����\n");
	}
	else
	{
		bFlagMError = FALSE;
		printf("�˶�����\n");
	}
	// ������λ
	if (lAxisStatus & 0x20)
	{
		bFlagPosLimit = TRUE;
		printf("����λ����\n");
	}
	else
	{
		bFlagPosLimit = FALSE;
		printf("����λδ����\n");
	}
	// ������λ
	if (lAxisStatus & 0x40)
	{
		bFlagNegLimit = TRUE;
		printf("����λ����\n");
	}
	else
	{
		bFlagNegLimit = FALSE;
		printf("����λδ����\n");
	}
	// ƽ��ֹͣ
	if (lAxisStatus & 0x80)
	{
		bFlagSmoothStop = TRUE;
		printf("ƽ��ֹͣ����\n");
	}
	else
	{
		bFlagSmoothStop = FALSE;
		printf("ƽ��ֹͣδ����\n");
	}
	// ��ͣ��־
	if (lAxisStatus & 0x100)
	{
		bFlagAbruptStop = TRUE;
		printf("��ͣ����\n");
	}
	else
	{
		bFlagAbruptStop = FALSE;
		printf("��ͣδ����\n");
	}
	// �ŷ�ʹ�ܱ�־
	if(lAxisStatus & 0x200)
	{
		bFlagServoOn = TRUE;
		printf("�ŷ�ʹ��\n");
	}
	else
	{
		bFlagServoOn = FALSE;
		printf("�ŷ��ر�\n");
	}
	// �滮�������˶���־
	if (lAxisStatus & 0x400)
	{
		bFlagMotion = TRUE;
		printf("�滮�������˶�\n");
	}
	else
	{
		bFlagMotion = FALSE;
		printf("�滮����ֹͣ\n");
	} 

	// ��ȡ�˶�����
	sRtn = GT_GetPrfPos(AXIS, &dPrfPos);
	commandhandler("GT_GetPrfPos", sRtn);
	printf("�滮λ�� %8.2f\n", dPrfPos);
	sRtn = GT_GetPrfVel(AXIS, &dPrfVel);
	commandhandler("GT_GetPrfVel", sRtn);
	printf("�滮�ٶ� %8.2f\n", dPrfVel);
	sRtn=GT_GetPrfAcc(AXIS, &dPrfAcc);
	commandhandler("GT_GetPrfAcc", sRtn);
	printf("�滮���ٶ� %8.2f\n", dPrfAcc);

	// ��ȡ�˶�ģʽ
	sRtn = GT_GetPrfMode(AXIS, &lPrfMode);
	commandhandler("GT_GetPrfMode", sRtn);
	// ����ַ���
	memset(chPrfMode, '\0', 20);
	switch(lPrfMode) 
	{
		case 0:
			sprintf(chPrfMode, "Trap");
		break;
		case 1:
			sprintf(chPrfMode, "Jog");
		break;
		case 2:
			sprintf(chPrfMode, "PT");
		break;
		case 3:
			sprintf(chPrfMode, "Gear");
		break;
		case 4:
			sprintf(chPrfMode, "Follow");
		break;
		case 5:
			sprintf(chPrfMode, "Interpolation");
		break;
		case 6:
			sprintf(chPrfMode, "PVT");
		break;
		default:
		break;
	}
	printf("�˶�ģʽ %s\n", chPrfMode);

	return TRUE;

}
