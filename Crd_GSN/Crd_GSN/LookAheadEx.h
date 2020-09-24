//用户使用的头文件
#pragma once
//#include "MB.h"

#define LA_AXIS_NUM    8
#define LA_WORK_AXIS_NUM  6

//轴的参数信息（各轴最大速度，各轴最大加速度，各轴最大速度变化量）是否限制速度模式
#define AXIS_LIMIT_NONE       0       //轴无限制
#define AXIS_LIMIT_MAX_VEL    1       //轴最大速度限制
#define AXIS_LIMIT_MAX_ACC    2       //轴最大加速度限制
#define AXIS_LIMIT_MAX_DV     4       //轴最大速度跳变量限制

#define KIN_MSG_BUFFER_SIZE   32

//速度规划模式
enum EVelMode
{
	T_CURVE=0,
	S_CURVE,
	S_CURVE_NEW,                  //根据加加速度、最大加速度进行S曲线速度前瞻，2015.11.16
	S_CURVE_SMOOTH,               

	VEL_MODE_MAX=0x10000,         //确保长度为4Byte
};

//工件坐标系下轨迹是否限制速度模式
enum EWorkLimitMode
{
	WORK_LIMIT_INVALID=0,      //工件坐标系信息不限制
	WORK_LIMIT_VALID,          //工件坐标系限制生效

	WORK_LIMIT_MODE_MAX=0x10000,//确保长度为4Byte
};

//设置的速度定义规则
enum EVelSettingDef
{
	NORMAL_DEF_VEL=0,             //输入为轴坐标系所有轴的合成速度
	NUM_DEF_VEL,                  //以NUM系统的规则定义
	CUT_DEF_VEL,                  //速度为切削速度

	VEL_SETTING_DEF_MAX=0x10000,  //确保长度为4Byte
};

//设置的加速度定义规则
enum EAccSettingDef
{
	NORMAL_DEF_ACC=0,             //输入即输出
	LONG_AXIS_ACC,                //长轴最大速度

	ACC_SETTING_DEF_MAX=0x10000,  //确保长度为4Byte
};

//机床类型
enum EMachineMode
{
	NORMAL_THREE_AXIS=0,      //标准三轴机床模式
	MULTI_AXES,               //多轴联动模式
	FIVE_AXIS,                //五轴机床模式,轴坐标系为主，工件坐标系为辅
	FIVE_AXIS_WORK,           //五轴机床模式，工件坐标系为主，轴坐标系为辅
	ROBOT,                    //机器人模式，轴坐标系为主，工件坐标系为辅，2014.12.3
	ROBOT_WORK,

	MACHINE_MODE_MAX=0x10000, //确保长度为4Byte
};

//前瞻参数结构体
struct TLookAheadParameter
{
	int lookAheadNum;					//前瞻段数
	double time;						//时间常数
	double radiusRatio;					//曲率限制调节参数
	double vMax[LA_AXIS_NUM];			//各轴的最大速度
	double aMax[LA_AXIS_NUM];			//各轴的最大加速度
	double DVMax[LA_AXIS_NUM];			//各轴的最大速度变化量（在时间常数内）
	double scale[LA_AXIS_NUM];			//各轴的脉冲当量
	short axisRelation[LA_AXIS_NUM];	//输入坐标和内部坐标的对应关系
	char machineCfgFileName[128];		//机床配置文件名
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

//正逆解方向
enum ETransDir
{
	FORWARD_TRANS=0,  //正解
	INVERSE_TRANS,    //逆解

	TRANS_DIR_MAX = 0x10000,	// 确保长度为4Byte
};

//旋转轴范围设置
struct TRotationAxisRange
{
	int primaryAxisRangeOn;              //第一旋转轴限定范围是否生效，0：不生效，1：生效
	int slaveAxisRangeOn;                //第二旋转轴限定范围是否生效，0：不生效，1：生效
	double maxPrimaryAngle;              //第一旋转轴最大值
	double minPrimaryAngle;              //第一旋转轴最小值
	double maxSlaveAngle;                //第二旋转轴最大值
	double minSlaveAgnle;                //第二旋转轴最小值
};

//选解参数
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
	INIT_ERROR=1,		//没有进行参数初始化
	PASSWORD_ERROR,		//密码错误，请在固高运动控制平台上运行
	INDATA_ERROR,		//输入数据错误（检查圆弧数据是否正确）
	PRE_PROCESS_ERROR,	//
	TOOL_RADIUS_COMPENSATE_ERROR_INOUT,		//刀具半径补偿错误：进入/结束刀补处不能是圆弧
	TOOL_RADIUS_COMPENSATE_ERROR_NOCROSS,	//刀具半径补偿错误：数据不合理，无法计算交点
	USERDATA_ERROR,
};

//轨迹优化参数结构体
typedef struct OptimizeParamUser 
{
	OptimizeState usePathOptimize;	//是否使用路径优化：OPT_OFF:不使用	OPT_ON:使用

	float tolerance;				//公差(suggest: rough:0.1, pre-finish:0.05, finish:0.01)

	OptimizeMethod optimizeMethod;	//选择曲线优化方式

	OptimizeState keepLargeArc;		//是否保留大圆弧：OPT_OFF：不保留， OPT_ON：保留

	float blendingMinError;			//blending的最小设定误差

	float blendingMaxAngle;			//blending的最大角度限制（即当线段向量角度大于该角度时，不做blending，单位：度）

}TOptimizeParamUser;

struct TErrorInfo 
{
	ErrorID errorID;		//错误号(INIT_ERROR:未初始化参数；PRE_PROCESS_ERROR:预处理模块错误；
	//TOOL_RADIUS_COMPENSATE_ERROR:刀具半径补偿错误；)
	long errorRowNum;		//错误行号
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





