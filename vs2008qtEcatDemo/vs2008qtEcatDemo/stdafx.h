#include <QtGui>
#include <Windows.h>
#include "gts.h"
//#include "config.h"
#pragma comment(lib,"gts.lib")


typedef struct AxisStatus
{
	short sEcatMode;
	bool bAlarm;
	bool bEnable;
	bool bMtn;
	bool bLmtP;
	bool bLmtN;
	bool bLmtNDi;//ֱ�Ӵ�EcaAxis����
	bool bLmtPDi;//ֱ�Ӵ�EcatAxis����
	bool bHome;
	float fPrfPos;
	float fEncPos;
	long lEcatPos;
	long lLastEcatPos;
	short sMovStatus;//-1��0��1

	unsigned short usStatusWord;//״̬��0x6041
	unsigned short usHomeStatus;
}TAxisStatus;
// ��Դ��Ϣ
typedef struct _ResInfo
{
	short sCoreCnt;//������
	short sCoreAxisResCnt;//ÿ�����ж�����
}TResInfo;
// 
typedef struct _HomePrm
{
	short sMethod;
	double dSpeed1;
	double dSpeed2;
	double dAcc;
	long lOffset;
	short probe;
}TEcatHomePrm;

// 
typedef struct _ProbelPrmBit
{
	unsigned char uchProbel1		:1;//0.off 1.enable
	unsigned char uchType1		:1;//0.����1.����
	unsigned char uchRevser11	:2;
	unsigned char uchRising1		:1;//�����ش���0.��Ч��1��Ч
	unsigned char uchFalling1		:1;//�½��ش���0.��Ч��1��Ч
	unsigned char uchRevser12	:2;

	unsigned char uchProbel2		:1;//0.off 1.enable
	unsigned char uchType2		:1;//0.����1.����
	unsigned char uchRevser21	:2;
	unsigned char uchRising2		:1;//�����ش���0.��Ч��1��Ч
	unsigned char uchFalling2		:1;//�½��ش���0.��Ч��1��Ч
	unsigned char uchRevser22	:2;
}TProbelPrmBit;
// 
typedef union _UProbelPrm
{
	short sProbelPrm;
	TProbelPrmBit tProbelPrmBit;
}UProbelPrm;
// 
typedef struct _ProbelStatusBit
{
	unsigned char uchProbel1 :1;
	unsigned char uchRising1	:1;
	unsigned char uchFalling1	:1;
	unsigned char uchRevser1	:5;

	unsigned char uchProbel2 :1;
	unsigned char uchRising2	:1;
	unsigned char uchFalling2	:1;
	unsigned char uchRevser2	:5;
}TProbelStatusBit;
// 
typedef union _UProbelStatus
{
	unsigned short sProbelStatus;
	TProbelStatusBit tProbelStatusBit;
}UProbelStatus;
// 
typedef struct _ProbelStstus
{
	UProbelStatus uProbelStatus;
	long lProbelRiseValue1;
	long lProbelFallValue1;
	long lProbelRiseValue2;
	long lProbelFallValue2;
}TProbelStstus;

// 
typedef struct _ObjectValue
{
	short sStatusWord;
	short sCtrlWord;
	int iTargePos;
	int iEncPos;
	char chSetMode;
	char chShowMode;
	unsigned int uiDiStatus;
	unsigned int uiDoStatus;
	unsigned short usProbelPrm;
	unsigned short usProbelStatus;

}TObjectValue;


extern short g_sCurCore;//��ǰ�˺�
extern short g_sCurAxis;//��ǰ���


extern TAxisStatus g_tAxisStatus;
extern TResInfo g_tResInfo;

extern TEcatHomePrm g_tEcatHomePrm;

extern TProbelStstus g_tProbelStatus;
extern UProbelPrm g_uProbelPrm;

extern TObjectValue g_tObjectValue;
