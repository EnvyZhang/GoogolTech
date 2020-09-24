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
	bool bLmtNDi;//直接从EcaAxis读到
	bool bLmtPDi;//直接从EcatAxis读到
	bool bHome;
	float fPrfPos;
	float fEncPos;
	long lEcatPos;
	long lLastEcatPos;
	short sMovStatus;//-1，0，1

	unsigned short usStatusWord;//状态字0x6041
	unsigned short usHomeStatus;
}TAxisStatus;
// 资源信息
typedef struct _ResInfo
{
	short sCoreCnt;//几个核
	short sCoreAxisResCnt;//每个核有多少轴
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
	unsigned char uchType1		:1;//0.单次1.连续
	unsigned char uchRevser11	:2;
	unsigned char uchRising1		:1;//上升沿触发0.无效，1有效
	unsigned char uchFalling1		:1;//下降沿触发0.无效，1有效
	unsigned char uchRevser12	:2;

	unsigned char uchProbel2		:1;//0.off 1.enable
	unsigned char uchType2		:1;//0.单次1.连续
	unsigned char uchRevser21	:2;
	unsigned char uchRising2		:1;//上升沿触发0.无效，1有效
	unsigned char uchFalling2		:1;//下降沿触发0.无效，1有效
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


extern short g_sCurCore;//当前核号
extern short g_sCurAxis;//当前轴号


extern TAxisStatus g_tAxisStatus;
extern TResInfo g_tResInfo;

extern TEcatHomePrm g_tEcatHomePrm;

extern TProbelStstus g_tProbelStatus;
extern UProbelPrm g_uProbelPrm;

extern TObjectValue g_tObjectValue;
