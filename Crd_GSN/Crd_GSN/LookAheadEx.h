//�û�ʹ�õ�ͷ�ļ�
#pragma once
//#include "MB.h"

#define LA_AXIS_NUM    8
#define LA_WORK_AXIS_NUM  6

//��Ĳ�����Ϣ����������ٶȣ����������ٶȣ���������ٶȱ仯�����Ƿ������ٶ�ģʽ
#define AXIS_LIMIT_NONE       0       //��������
#define AXIS_LIMIT_MAX_VEL    1       //������ٶ�����
#define AXIS_LIMIT_MAX_ACC    2       //�������ٶ�����
#define AXIS_LIMIT_MAX_DV     4       //������ٶ�����������

#define KIN_MSG_BUFFER_SIZE   32

//�ٶȹ滮ģʽ
enum EVelMode
{
	T_CURVE=0,
	S_CURVE,
	S_CURVE_NEW,                  //���ݼӼ��ٶȡ������ٶȽ���S�����ٶ�ǰհ��2015.11.16
	S_CURVE_SMOOTH,               

	VEL_MODE_MAX=0x10000,         //ȷ������Ϊ4Byte
};

//��������ϵ�¹켣�Ƿ������ٶ�ģʽ
enum EWorkLimitMode
{
	WORK_LIMIT_INVALID=0,      //��������ϵ��Ϣ������
	WORK_LIMIT_VALID,          //��������ϵ������Ч

	WORK_LIMIT_MODE_MAX=0x10000,//ȷ������Ϊ4Byte
};

//���õ��ٶȶ������
enum EVelSettingDef
{
	NORMAL_DEF_VEL=0,             //����Ϊ������ϵ������ĺϳ��ٶ�
	NUM_DEF_VEL,                  //��NUMϵͳ�Ĺ�����
	CUT_DEF_VEL,                  //�ٶ�Ϊ�����ٶ�

	VEL_SETTING_DEF_MAX=0x10000,  //ȷ������Ϊ4Byte
};

//���õļ��ٶȶ������
enum EAccSettingDef
{
	NORMAL_DEF_ACC=0,             //���뼴���
	LONG_AXIS_ACC,                //��������ٶ�

	ACC_SETTING_DEF_MAX=0x10000,  //ȷ������Ϊ4Byte
};

//��������
enum EMachineMode
{
	NORMAL_THREE_AXIS=0,      //��׼�������ģʽ
	MULTI_AXES,               //��������ģʽ
	FIVE_AXIS,                //�������ģʽ,������ϵΪ������������ϵΪ��
	FIVE_AXIS_WORK,           //�������ģʽ����������ϵΪ����������ϵΪ��
	ROBOT,                    //������ģʽ��������ϵΪ������������ϵΪ����2014.12.3
	ROBOT_WORK,

	MACHINE_MODE_MAX=0x10000, //ȷ������Ϊ4Byte
};

//ǰհ�����ṹ��
struct TLookAheadParameter
{
	int lookAheadNum;					//ǰհ����
	double time;						//ʱ�䳣��
	double radiusRatio;					//�������Ƶ��ڲ���
	double vMax[LA_AXIS_NUM];			//���������ٶ�
	double aMax[LA_AXIS_NUM];			//����������ٶ�
	double DVMax[LA_AXIS_NUM];			//���������ٶȱ仯������ʱ�䳣���ڣ�
	double scale[LA_AXIS_NUM];			//��������嵱��
	short axisRelation[LA_AXIS_NUM];	//����������ڲ�����Ķ�Ӧ��ϵ
	char machineCfgFileName[128];		//���������ļ���
};

//////////////////////////////////////
typedef struct
{
	short RobotType;
	short reserved1;

	short KinParUse[18];
	double KinPar[18];
	short KinLimitUse[12];
	double KinLimitMin[12];
	double KinLimitMax[12];
	double KinLimitMinShift[12];
	double KinLimitMaxShift[12];

	short AxisUse[8];
	char AxisPosSignSwitch[8];
	double AxisPosOffset[8];

	short CartUnitUse[6];
	char CartPosKCSSignSwitch[6];
	short reserved2[3];
	double CartPosKCSOffset[6];
}RC_KIN_CONFIG;

typedef struct
{
	char Error;
	short ErrorID;
	char Message[129];
}RC_ERROR_INTERFACE;

typedef struct  
{
	short ErrorID;
	char Message[129];
	char LogTime[32];
	long InternalID;
}RC_MSG_BUFFER_ELEMENT;

typedef struct  
{
	short LastMsgIndex;
	RC_MSG_BUFFER_ELEMENT MsgElement[KIN_MSG_BUFFER_SIZE];
	long LastMsgID;
}RC_MSG_BUFFER;

//����ⷽ��
enum ETransDir
{
	FORWARD_TRANS=0,  //����
	INVERSE_TRANS,    //���

	TRANS_DIR_MAX = 0x10000,	// ȷ������Ϊ4Byte
};

//��ת�᷶Χ����
struct TRotationAxisRange
{
	int primaryAxisRangeOn;              //��һ��ת���޶���Χ�Ƿ���Ч��0������Ч��1����Ч
	int slaveAxisRangeOn;                //�ڶ���ת���޶���Χ�Ƿ���Ч��0������Ч��1����Ч
	double maxPrimaryAngle;              //��һ��ת�����ֵ
	double minPrimaryAngle;              //��һ��ת����Сֵ
	double maxSlaveAngle;                //�ڶ���ת�����ֵ
	double minSlaveAgnle;                //�ڶ���ת����Сֵ
};

//ѡ�����
enum EGroupSelect
{
	Continuous=0,
	Group_1,
	Group_2,
};

enum OptimizeState
{
	OPT_OFF=0,
	OPT_ON,
};

enum OptimizeMethod
{
	NO_OPT=0,
	OPT_BLENDING,
	OPT_CIRCLEFITTING,
	OPT_CUBICSPLINE,
	OPT_BSPLINE,
};

enum ErrorID
{
	INIT_ERROR=1,		//û�н��в�����ʼ��
	PASSWORD_ERROR,		//����������ڹ̸��˶�����ƽ̨������
	INDATA_ERROR,		//�������ݴ��󣨼��Բ�������Ƿ���ȷ��
	PRE_PROCESS_ERROR,	//
	TOOL_RADIUS_COMPENSATE_ERROR_INOUT,		//���߰뾶�������󣺽���/����������������Բ��
	TOOL_RADIUS_COMPENSATE_ERROR_NOCROSS,	//���߰뾶�����������ݲ������޷����㽻��
	USERDATA_ERROR,
};

//�켣�Ż������ṹ��
typedef struct OptimizeParamUser 
{
	OptimizeState usePathOptimize;	//�Ƿ�ʹ��·���Ż���OPT_OFF:��ʹ��	OPT_ON:ʹ��

	float tolerance;				//����(suggest: rough:0.1, pre-finish:0.05, finish:0.01)

	OptimizeMethod optimizeMethod;	//ѡ�������Ż���ʽ

	OptimizeState keepLargeArc;		//�Ƿ�����Բ����OPT_OFF���������� OPT_ON������

	float blendingMinError;			//blending����С�趨���

	float blendingMaxAngle;			//blending�����Ƕ����ƣ������߶������Ƕȴ��ڸýǶ�ʱ������blending����λ���ȣ�

}TOptimizeParamUser;

struct TErrorInfo 
{
	ErrorID errorID;		//�����(INIT_ERROR:δ��ʼ��������PRE_PROCESS_ERROR:Ԥ����ģ�����
	//TOOL_RADIUS_COMPENSATE_ERROR:���߰뾶��������)
	long errorRowNum;		//�����к�
};

struct TPreStartPos
{
	double Pos[LA_AXIS_NUM];
};

GT_API GT_SetupLookAheadCrd(short crd,EMachineMode machineMode);
GT_API GT_SetVelDefineModeLa(short crd,EVelSettingDef velDefMode);
GT_API GT_SetAccDefineModeLa(short crd,EAccSettingDef accDefMode);
GT_API GT_SetAxisLimitModeLa(short crd,int *pAxisLimitMode);
GT_API GT_SetWorkLimitModeLa(short crd,EWorkLimitMode workLimitMode);
GT_API GT_SetAxisFollowModeLa(short crd,int *pFollowMode);
GT_API GT_SetAxisVelValidModeLa(short crd,int velValidAxis);
GT_API GT_SetArcAllowErrorLa(short crd, double error);
GT_API GT_SetMinEvenVelTime(short crd, double evenTime);
GT_API GT_SetMinDccAngle(short crd, double dccAngle);
GT_API GT_SetProfilePeriod(short crd, double profilePeriod);
GT_API GT_SetFilterTime(short crd, long filtNum);
GT_API GT_SetPrecisionControl(short crd, short mode,double error);
GT_API GT_SetVelSmoothModeLa(short crd, short smoothMode);
GT_API GT_SetVelModeLa(short crd,EVelMode velMode);
GT_API GT_InitLookAheadEx(short crd,TLookAheadParameter *pLookAheadPara,short fifo,short motionMode=0,TPreStartPos *pPreStartPos=NULL);
GT_API GT_PrintLACmdLa(short crd,int printFlag, int clearFile);

GT_API GT_GetLookAheadSegCountEx(short crd,long *pSegCount,short fifo=0);
GT_API GT_GetMotionTimeEx(short crd,double *pTime,short fifo=0);
GT_API GT_SetUserSegNumEx(short crd,long segNum,short fifo=0);
GT_API GT_CrdDataEx(short crd,TCrdData *pCrdData,short fifo=0);

GT_API GT_LnXYEx(short crd,double x,double y,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_LnXYG0Ex(short crd,double x,double y,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_LnXYZEx(short crd,double x,double y,double z,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_LnXYZG0Ex(short crd,double x,double y,double z,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_LnXYZAEx(short crd,double x,double y,double z,double a,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_LnXYZAG0Ex(short crd,double x,double y,double z,double a,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_LnXYZACEx(short crd,double *pPos,short posMask,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_LnXYZACG0Ex(short crd,double *pPos,short posMask,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_LnXYZACUVWEx(short crd,double *pPos,short posMask,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_LnXYZACUVWG0Ex(short crd,double *pPos,short posMask,double synVel,double synAcc,long segNum,short override2,short fifo=0);

GT_API GT_ArcXYREx(short crd,double x,double y,double radius,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_ArcYZREx(short crd,double y,double z,double radius,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_ArcZXREx(short crd,double z,double x,double radius,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_ArcXYCEx(short crd,double x,double y,double xCenter,double yCenter,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_ArcYZCEx(short crd,double y,double z,double yCenter,double zCenter,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_ArcZXCEx(short crd,double z,double x,double zCenter,double xCenter,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_ArcXYZEx(short crd,double x,double y,double z,double interX,double interY,double interZ,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_HelixXYRZEx(short crd,double x,double y,double z,double radius,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_HelixXYCZEx(short crd,double x,double y,double z,double xCenter,double yCenter,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_HelixYZRXEx(short crd,double x,double y,double z,double radius,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_HelixYZCXEx(short crd,double x,double y,double z,double yCenter,double zCenter,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_HelixZXRYEx(short crd,double x,double y,double z,double radius,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_HelixZXCYEx(short crd,double x,double y,double z,double zCenter,double xCenter,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);

GT_API GT_HelixXYRMultiZEx(short crd,double *pPos,double radius,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_HelixXYCMultiZEx(short crd,double *pPos,double xCenter,double yCenter,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_HelixYZRMultiXEx(short crd,double *pPos,double radius,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_HelixYZCMultiXEx(short crd,double *pPos,double yCenter,double zCenter,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_HelixZXRMultiYEx(short crd,double *pPos,double radius,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GT_HelixZXCMultiYEx(short crd,double *pPos,double zCenter,double xCenter,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);

GT_API GT_BufDelayEx(short crd,unsigned short delayTime,short fifo=0);
GT_API GT_BufIOEx(short crd,unsigned short doType,unsigned short doMask,unsigned short doValue,short fifo=0);
GT_API GT_BufDAEx(short crd,short channel,short daValue,short fifo=0);
GT_API GT_BufEnableDoBitPulseEx(short crd,short doType,short doIndex,unsigned short highLevelTime,unsigned short lowLevelTime,long pulseNum,short firstLevel,short fifo);
GT_API GT_BufDisableDoBitPulseEx(short crd,short doType,short doIndex,short fifo);
GT_API GT_BufGearEx(short crd,short gearAxis,double deltaPos,short fifo=0);
GT_API GT_BufMoveEx(short crd,short moveAxis,double pos,double vel,double acc,short modal,short fifo=0);

//GT_API GT_BufFollowMasterEx(short crd,TBufFollowMaster *pBufFollowMaster,short fifo=0);
//GT_API GT_BufFollowEventCrossEx(short crd,TBufFollowEventCross *pEventCross,short fifo=0);
//GT_API GT_BufFollowEventTriggerEx(short crd,TBufFollowEventTrigger *pEventTrigger,short fifo=0);
GT_API GT_BufFollowStartEx(short crd,long masterSegment,long slaveSegment,long masterFrameWidth,short fifo=0);
GT_API GT_BufFollowNextEx(short crd,long width,short fifo=0);
GT_API GT_BufFollowReturnEx(short crd,double vel,double acc,short smoothPercent,short fifo=0);

GT_API GT_BufSmartCutterOnEx(short crd,short index,short fifo);
GT_API GT_BufSmartCutterOffEx(short crd,short index,short fifo);

GT_API GT_BufLaserOnEx(short crd,short fifo=0,short channel=0);
GT_API GT_BufLaserOffEx(short crd,short fifo=0,short channel=0);
GT_API GT_BufLaserFollowModeEx(short crd,short source,short fifo,short channel,double startPower=0);
GT_API GT_BufLaserFollowTableEx(short crd,short tableId,double minPower,double maxPower,short fifo,short channel);
GT_API GT_BufLaserFollowOffEx(short crd,short fifo,short channel);
GT_API GT_BufLaserPrfCmdEx(short crd,double laserPower,short fifo=0,short channel=0);
GT_API GT_BufLaserFollowRatioEx(short crd,double ratio,double minPower,double maxPower,short fifo,short channel);
GT_API GTN_SetupLookAheadCrd(short core,short crd,EMachineMode machineMode);
GT_API GTN_SetAxisFollowModeLa(short core,short crd,int *pFollowMode);
GT_API GTN_SetVelDefineModeLa(short core,short crd,EVelSettingDef velDefMode);
GT_API GTN_SetAccDefineModeLa(short core,short crd,EAccSettingDef accDefMode);
GT_API GTN_SetAxisLimitModeLa(short core,short crd,int *pAxisLimitMode);
GT_API GTN_SetWorkLimitModeLa(short core,short crd,EWorkLimitMode workLimitMode);
GT_API GTN_SetAxisVelValidModeLa(short core,short crd,int velValidAxis);
GT_API GTN_SetVelModeLa(short core,short crd,EVelMode velMode);
GT_API GTN_SetVelSmoothModeLa(short core,short crd,short smoothMode);
GT_API GTN_PrintLACmdLa(short core,short crd,int printFlag, int clearFile);
GT_API GTN_InitLookAheadEx(short core,short crd,TLookAheadParameter *pLookAheadParameter,short fifo, short motionMode=0,TPreStartPos *pPreStartPos=NULL);

GT_API GTN_GetLookAheadSegCountEx(short core,short crd,long *pSegCount,short fifo=0);
GT_API GTN_GetMotionTimeEx(short core,short crd,double *pTime,short fifo);
GT_API GTN_SetUserSegNumEx(short core,short crd,long segNum,short fifo);
GT_API GTN_CrdDataEx(short core,short crd,TCrdData *pCrdData,short fifo=0);

GT_API GTN_LnXYEx(short core,short crd,double x,double y,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GTN_LnXYG0Ex(short core,short crd,double x,double y,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GTN_LnXYZEx(short core,short crd,double x,double y,double z,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GTN_LnXYZG0Ex(short core,short crd,double x,double y,double z,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GTN_LnXYZAEx(short core,short crd,double x,double y,double z,double a,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GTN_LnXYZAG0Ex(short core,short crd,double x,double y,double z,double a,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GTN_LnXYZACEx(short core,short crd,double *pPos,short posMask,double synVel,double synAcc,long segNum,short override2,short fifo);
GT_API GTN_LnXYZACG0Ex(short core,short crd,double *pPos,short posMask,double synVel,double synAcc,long segNum,short override2,short fifo);
GT_API GTN_LnXYZACUVWEx(short core,short crd,double *pPos,short posMask,double synVel,double synAcc,long segNum,short override2,short fifo);
GT_API GTN_LnXYZACUVWG0Ex(short core,short crd,double *pPos,short posMask,double synVel,double synAcc,long segNum,short override2,short fifo);
GT_API GTN_ArcXYREx(short core,short crd,double x,double y,double radius,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GTN_ArcYZREx(short core,short crd,double y,double z,double radius,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GTN_ArcZXREx(short core,short crd,double z,double x,double radius,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GTN_ArcXYCEx(short core,short crd,double x,double y,double xCenter,double yCenter,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GTN_ArcYZCEx(short core,short crd,double y,double z,double yCenter,double zCenter,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GTN_ArcZXCEx(short core,short crd,double z,double x,double zCenter,double xCenter,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GTN_ArcXYZEx(short core,short crd,double x,double y,double z,double interX,double interY,double interZ,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GTN_HelixXYRZEx(short core,short crd,double x,double y,double z,double radius,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GTN_HelixXYCZEx(short core,short crd,double x,double y,double z,double xCenter,double yCenter,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GTN_BufDelayEx(short core,short crd,unsigned short delayTime,short fifo=0);
GT_API GTN_BufGearEx(short core,short crd,short gearAxis,double deltaPos,short fifo=0);
GT_API GTN_BufMoveEx(short core,short crd,short moveAxis,double pos,double vel,double acc,short modal,short fifo=0);
GT_API GTN_BufIOEx(short core,short crd,unsigned short doType,unsigned short doMask,unsigned short doValue,short fifo=0);
GT_API GTN_BufEnableDoBitPulseEx(short core,short crd,short doType,short doIndex,unsigned short highLevelTime,unsigned short lowLevelTime,long pulseNum,short firstLevel,short fifo);
GT_API GTN_BufDisableDoBitPulseEx(short core,short crd,short doType,short doIndex,short fifo);
GT_API GTN_BufDAEx(short core,short crd,short chn,short daValue,short fifo=0);

//GT_API GTN_BufFollowMasterEx(short core,short crd,TBufFollowMaster *pBufFollowMaster,short fifo=0);
//GT_API GTN_BufFollowEventCrossEx(short core,short crd,TBufFollowEventCross *pEventCross,short fifo=0);
// GT_API GTN_BufFollowEventTriggerEx(short core,short crd,TBufFollowEventTrigger *pEventTrigger,short fifo=0);
GT_API GTN_BufFollowStartEx(short core,short crd,long masterSegment,long slaveSegment,long masterFrameWidth,short fifo=0);
GT_API GTN_BufFollowNextEx(short core,short crd,long width,short fifo=0);
GT_API GTN_BufFollowReturnEx(short core,short crd,double vel,double acc,short smoothPercent,short fifo=0);

GT_API GTN_BufSmartCutterOnEx(short core,short crd,short index,short fifo=0);
GT_API GTN_BufSmartCutterOffEx(short core,short crd,short index,short fifo=0);

GT_API GTN_BufLaserOnEx(short core,short crd,short fifo=0,short channel=0);
GT_API GTN_BufLaserOffEx(short core,short crd,short fifo=0,short channel=0);
GT_API GTN_BufLaserFollowModeEx(short core,short crd,short source,short fifo,short channel,double startPower=0);
GT_API GTN_BufLaserFollowTableEx(short core,short crd,short tableId,double minPower,double maxPower,short fifo,short channel);
GT_API GTN_BufLaserFollowOffEx(short core,short crd,short fifo,short channel);
GT_API GTN_BufLaserPrfCmdEx(short core,short crd,double laserPower,short fifo=0,short channel=0);
GT_API GTN_BufLaserFollowRatioEx(short core,short crd,double ratio,double minPower,double maxPower,short fifo,short channel);

GT_API GT_BufWaitDiEx(short crd, short diType, unsigned short diIndex,unsigned short level, short continueTime, long overTime, short flagMode,long segNum, short fifo);
GT_API GT_BufWaitLongVarEx(short crd,short index,long value,long overTime,short flagMode,long segNum,short fifo);
GT_API GTN_BufWaitDiEx(short core,short crd, short diType, unsigned short diIndex,unsigned short level, short continueTime, long overTime, short flagMode,long segNum, short fifo);
GT_API GTN_BufWaitLongVarEx(short core,short crd, short index,long value,long overTime,short flagMode,long segNum,short fifo);

GT_API GT_BufDoBitEx(short crd,unsigned short doType,unsigned short index,short value,short fifo);
GT_API GTN_BufDoBitEx(short core,short crd,unsigned short doType,unsigned short index,short value,short fifo);
GT_API GTN_BufDoBitDelayEx(short core,short crd,unsigned short doType,unsigned short index,short value,long delayTime,short fifo);

//GT_API GTN_BufPosComparePsoPrmEx(short core,short crd,short index,TPosComparePsoPrm *pPrm,short fifo);

//add 2019.11.13
GT_API GT_UpdateMachineBuildingFileLa(short crd, int update);
GT_API GT_InitialMachineBuilding(short crd, char *pMachineCfgFileName,double *machineCoordCenter, double *workCoordCenter, double toolLength);
//GT_API GT_InitialMachineBuildingPara(short crd, TMachCfgInfo *pMachCfgInfo,double *machineCoordCenter, double *workCoordCenter, double toolLength);
GT_API GT_SetMinDccAngleLa(short crd, double dccAngle);
GT_API GT_SetMinEvenVelTimeLa(short crd, double evenTime);
GT_API GT_SetMaxOverrideLa(short crd,double maxSynVelRatio);
GT_API GT_SetArcAllowErrorLa(short crd, double error);
GT_API GT_SetSoftLimitTrimMode(short enable);
GT_API GT_GetSoftLimitTrimMode(short *enable);
GT_API GT_SetAxisVelValidCompModeLa(short crd, int enable, int *pCompAxis);
GT_API GT_SetFollowAxisProcessModeLa(short crd,int AxisFollowMode);
GT_API GT_SetCmdVelLimitLa(short crd, int enable, int n1, int n2, int mode);
GT_API GT_SetCrdParallelAxisMask(short crd,unsigned short mask,short fifo);
GT_API GT_GetCrdParallelAxisMask(short crd,unsigned short *pMask,short fifo);
//GT_API GT_HelixXYRMultiZEx(short crd,double *pPos,double radius,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
//GT_API GT_HelixXYCMultiZEx(short crd,double *pPos,double xCenter,double yCenter,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
//GT_API GT_HelixYZRMultiXEx(short crd,double *pPos,double radius,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
//GT_API GT_HelixYZCMultiXEx(short crd,double *pPos,double yCenter,double zCenter,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
//GT_API GT_HelixZXRMultiYEx(short crd,double *pPos,double radius,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
//GT_API GT_HelixZXCMultiYEx(short crd,double *pPos,double zCenter,double xCenter,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);

GT_API GTN_UpdateMachineBuildingFileLa(short core,short crd, int update);
GT_API GTN_InitialMachineBuilding(short core,short crd, char *pMachineCfgFileName,double *machineCoordCenter, double *workCoordCenter, double toolLength);
//GT_API GTN_InitialMachineBuildingPara(short core,short crd, TMachCfgInfo *pMachCfgInfo,double *machineCoordCenter, double *workCoordCenter, double toolLength);
GT_API GTN_SetMinDccAngleLa(short core,short crd, double dccAngle);
GT_API GTN_SetMinEvenVelTimeLa(short core,short crd, double evenTime);
GT_API GTN_SetMaxOverrideLa(short core,short crd,double maxSynVelRatio);
GT_API GTN_SetArcAllowErrorLa(short core,short crd,double error);
GT_API GTN_SetSoftLimitTrimMode(short core,short enable);
GT_API GTN_GetSoftLimitTrimMode(short core,short *enable);
GT_API GTN_SetAxisVelValidCompModeLa(short core,short crd, int enable, int *pCompAxis);
GT_API GTN_SetFollowAxisProcessModeLa(short core,short crd,int AxisFollowMode);
GT_API GTN_SetCmdVelLimitLa(short core,short crd, int enable, int n1, int n2, int mode);
GT_API GTN_SetCrdParallelAxisMask(short core,short crd,unsigned short mask,short fifo);
GT_API GTN_GetCrdParallelAxisMask(short core,short crd,unsigned short *pMask,short fifo);
GT_API GTN_HelixXYRMultiZEx(short core,short crd,double *pPos,double radius,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GTN_HelixXYCMultiZEx(short core,short crd,double *pPos,double xCenter,double yCenter,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GTN_HelixYZRMultiXEx(short core,short crd,double *pPos,double radius,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GTN_HelixYZCMultiXEx(short core,short crd,double *pPos,double yCenter,double zCenter,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GTN_HelixZXRMultiYEx(short core,short crd,double *pPos,double radius,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);
GT_API GTN_HelixZXCMultiYEx(short core,short crd,double *pPos,double zCenter,double xCenter,short circleDir,double synVel,double synAcc,long segNum,short override2,short fifo=0);





