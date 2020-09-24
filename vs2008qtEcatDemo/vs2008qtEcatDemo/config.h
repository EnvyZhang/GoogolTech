#pragma once

#define RES_LIMIT                       (8)
#define RES_ALARM                       (8)
#define RES_HOME                        (8)
#define RES_GPI                         (16)
#define RES_ARRIVE                      (8)
#define RES_MPG                         (7)

#define RES_ENABLE                      (8)
#define RES_CLEAR                       (8)
#define RES_GPO                         (16)

#define RES_DAC                         (12)
#define RES_STEP                        (8)
#define RES_PULSE                       (8)
#define RES_ENCODER                     (11)
#define RES_LASER                       (2)  

#define AXIS_MAX                        (8)
#define PROFILE_MAX                     (8)
#define CONTROL_MAX                     (8)

#define PRF_MAP_MAX                     (2)
#define ENC_MAP_MAX                     (2)

typedef struct DiConfig
{
	short active;
	short reverse;
	short filterTime;
} TDiConfig;

typedef struct CountConfig
{
	short active;
	short reverse;
	short filterType;

	short captureSource;
	short captureHomeSense;
	short captureIndexSense;
} TCountConfig;

typedef struct DoConfig
{
	short active;
	short axis;
	short axisItem;
	short reverse;
} TDoConfig;

typedef struct StepConfig
{
	short active;
	short axis;
	short mode;
	short parameter;
	short reverse;
} TStepConfig;

typedef struct DacConfig
{
	short active;
	short control;
	short reverse;
	short bias;
	short limit;
} TDacConfig;

// y=ax+b,y是电压，x是ADC输入
typedef struct AdcConfig
{
	short active;
	short reverse;
	double a;
	double b;
	short filterMode;
} TAdcConfig;

typedef struct ControlConfig
{
	short active;
	short axis;
	short encoder1;
	short encoder2;
	long  errorLimit;
	short filterType[3];
	short encoderSmooth;
	short controlSmooth;
} TControlConfig;

typedef struct ControlConfigEx
{
	short refType;
	short refIndex;

	short feedbackType;
	short feedbackIndex;

	long  errorLimit;
	short feedbackSmooth;
	short controlSmooth;
} TControlConfigEx;

typedef struct ProfileConfig
{
	short  active;
	double decSmoothStop;
	double decAbruptStop;
} TProfileConfig;

typedef struct AxisConfig
{
	short active;
	short alarmType;
	short alarmIndex;
	short limitPositiveType;
	short limitPositiveIndex;
	short limitNegativeType;
	short limitNegativeIndex;
	short smoothStopType;
	short smoothStopIndex;
	short abruptStopType;
	short abruptStopIndex;
	long  prfMap;
	long  encMap;
	short prfMapAlpha[PRF_MAP_MAX];
	short prfMapBeta[PRF_MAP_MAX];
	short encMapAlpha[ENC_MAP_MAX];
	short encMapBeta[ENC_MAP_MAX];
} TAxisConfig;

typedef struct McConfig
{
	TProfileConfig profile[PROFILE_MAX];
	TAxisConfig    axis[AXIS_MAX];
	TControlConfig control[CONTROL_MAX];
	TDacConfig     dac[RES_DAC];
	TStepConfig    step[RES_STEP];
	TCountConfig   encoder[RES_ENCODER];
	TCountConfig   pulse[RES_PULSE];
	TDoConfig      enable[RES_ENABLE];
	TDoConfig      clear[RES_CLEAR];
	TDoConfig      gpo[RES_GPO];
	TDiConfig      limitPositive[RES_LIMIT];
	TDiConfig      limitNegative[RES_LIMIT];
	TDiConfig      alarm[RES_ALARM];
	TDiConfig      home[RES_HOME];
	TDiConfig      gpi[RES_GPI];
	TDiConfig      arrive[RES_ARRIVE];
	TDiConfig      mpg[RES_MPG];
} TMcConfig;

GT_API GT_SaveConfig(char *pFile);
GT_API GT_SetDiConfig(short diType,short diIndex,TDiConfig *pDi);
GT_API GT_GetDiConfig(short diType,short diIndex,TDiConfig *pDi);
GT_API GT_SetDoConfig(short doType,short doIndex,TDoConfig *pDo);
GT_API GT_GetDoConfig(short doType,short doIndex,TDoConfig *pDo);
GT_API GT_SetStepConfig(short step,TStepConfig *pStep);
GT_API GT_GetStepConfig(short step,TStepConfig *pStep);
GT_API GT_SetDacConfig(short dac,TDacConfig *pDac);
GT_API GT_GetDacConfig(short dac,TDacConfig *pDac);
GT_API GT_SetAdcConfig(short adc,TAdcConfig *pAdc);
GT_API GT_GetAdcConfig(short adc,TAdcConfig *pAdc);
GT_API GT_SetCountConfig(short countType,short countIndex,TCountConfig *pCount);
GT_API GT_GetCountConfig(short countType,short countIndex,TCountConfig *pCount);
GT_API GT_SetControlConfig(short control,TControlConfig *pControl);
GT_API GT_GetControlConfig(short control,TControlConfig *pControl);
GT_API GT_SetControlConfigEx(short control,TControlConfigEx *pControl);
GT_API GT_GetControlConfigEx(short control,TControlConfigEx *pControl);
GT_API GT_SetProfileConfig(short profile,TProfileConfig *pProfile);
GT_API GT_GetProfileConfig(short profile,TProfileConfig *pProfile);
GT_API GT_SetAxisConfig(short axis,TAxisConfig *pAxis);
GT_API GT_GetAxisConfig(short axis,TAxisConfig *pAxis);
GT_API GT_ProfileScale(short axis,short alpha,short beta);
GT_API GT_EncScale(short axis,short alpha,short beta);

GT_API GT_EncSns(unsigned short sense);
GT_API GT_LmtSns(unsigned short sense);
GT_API GT_GpiSns(unsigned short sense);
GT_API GT_SetAdcFilter(short adc,short filterTime);


GT_API GT_GetConfigTable(short type,short *pCount);
GT_API GT_GetConfigTableAll();

GT_API GT_SetMcConfig(TMcConfig *pMc);
GT_API GT_GetMcConfig(TMcConfig *pMc);

GT_API GT_SetMcConfigToFile(TMcConfig *pMc,char *pFile);
GT_API GT_GetMcConfigFromFile(TMcConfig *pMc,char *pFile);

GT_API GT_LoadConfigEx(short core,char *pFile);
GT_API GT_SaveConfigEx(short core,char *pFile);
GT_API GT_LoadModuleConfig(short core,char *pFile);
GT_API GT_SaveModuleConfig(short core,char *pFile);

GT_API GTN_SaveConfig(short core,char *pFile);
GT_API GTN_SetDiConfig(short core,short diType,short diIndex,TDiConfig *pDi);
GT_API GTN_GetDiConfig(short core,short diType,short diIndex,TDiConfig *pDi);
GT_API GTN_SetDoConfig(short core,short doType,short doIndex,TDoConfig *pDo);
GT_API GTN_GetDoConfig(short core,short doType,short doIndex,TDoConfig *pDo);
GT_API GTN_SetStepConfig(short core,short step,TStepConfig *pStep);
GT_API GTN_GetStepConfig(short core,short step,TStepConfig *pStep);
GT_API GTN_SetDacConfig(short core,short dac,TDacConfig *pDac);
GT_API GTN_GetDacConfig(short core,short dac,TDacConfig *pDac);
GT_API GTN_SetAdcConfig(short core,short adc,TAdcConfig *pAdc);
GT_API GTN_GetAdcConfig(short core,short adc,TAdcConfig *pAdc);
GT_API GTN_SetCountConfig(short core,short countType,short countIndex,TCountConfig *pCount);
GT_API GTN_GetCountConfig(short core,short countType,short countIndex,TCountConfig *pCount);
GT_API GTN_SetControlConfig(short core,short control,TControlConfig *pControl);
GT_API GTN_GetControlConfig(short core,short control,TControlConfig *pControl);
GT_API GTN_SetControlConfigEx(short core,short control,TControlConfigEx *pControl);
GT_API GTN_GetControlConfigEx(short core,short control,TControlConfigEx *pControl);
GT_API GTN_SetProfileConfig(short core,short profile,TProfileConfig *pProfile);
GT_API GTN_GetProfileConfig(short core,short profile,TProfileConfig *pProfile);
GT_API GTN_SetAxisConfig(short core,short axis,TAxisConfig *pAxis);
GT_API GTN_GetAxisConfig(short core,short axis,TAxisConfig *pAxis);
GT_API GTN_ProfileScale(short core,short axis,short alpha,short beta);
GT_API GTN_EncScale(short core,short axis,short alpha,short beta);

typedef struct ThreadStatus
{
	short link;
	unsigned long  address;
	short size;
	unsigned long  page;
	short delay;
	short priority;
	short ptr;
	short status;
	short error;
	short result[4];
	short resultType;
	short breakpoint;
	short period;
	short count;
	short function;
} TThreadStatus;

GT_API GT_ClearPlc(void);
GT_API GT_LoadPlc(short id,short returnType);
GT_API GT_LoadPlcCommand(short id,short count,short *pData);
GT_API GT_StepThread(short thread);
GT_API GT_RunThreadToBreakpoint(short thread,short line);
GT_API GT_GetThread(short thread,TThreadStatus *pThread);

GT_API GTN_StepThread(short core,short thread);

#define WATCH_LIST_MAX                                  (8)
#define WATCH_LENGTH_MAX                                (32)
#define WATCH_FIFO_SIZE                                 (0x1E0)       // 480 word

#define WATCH_ADDRESS_TYPE_PRF_POS						(0)
#define WATCH_ADDRESS_TYPE_PRF_VEL						(1)
#define WATCH_ADDRESS_TYPE_ENC_POS						(2)
#define WATCH_ADDRESS_TYPE_ENC_VEL						(3)
#define WATCH_ADDRESS_TYPE_AXIS_PRF_POS					(4)
#define WATCH_ADDRESS_TYPE_AXIS_PRF_VEL					(5)
#define WATCH_ADDRESS_TYPE_AXIS_ENC_POS					(6)
#define WATCH_ADDRESS_TYPE_AXIS_ENC_VEL					(7)
#define WATCH_ADDRESS_TYPE_DAC							(8)
#define WATCH_ADDRESS_TYPE_LMT_POS						(9)
#define WATCH_ADDRESS_TYPE_LMT_NEG						(10)
#define WATCH_ADDRESS_TYPE_ALARM						(11)
#define WATCH_ADDRESS_TYPE_HOME							(12)
#define WATCH_ADDRESS_TYPE_GPI							(13)
#define WATCH_ADDRESS_TYPE_ENABLE						(14)
#define WATCH_ADDRESS_TYPE_CLEAR						(15)
#define WATCH_ADDRESS_TYPE_GPO							(16)
#define WATCH_ADDRESS_TYPE_CLOCK						(17)
#define WATCH_ADDRESS_TYPE_FLASH_BUFFER					(18)
#define WATCH_ADDRESS_TYPE_CRD_VEL						(19)
#define WATCH_ADDRESS_TYPE_ARRIVE						(20)
#define WATCH_ADDRESS_TYPE_POS_LOOP_ERROR				(21)
#define WATCH_ADDRESS_TYPE_POS_LOOP_OUTPUT				(22)
#define WATCH_ADDRESS_TYPE_POS_LOOP_INTERGRAL			(23)
#define WATCH_ADDRESS_TYPE_VEL_LOOP_ERROR				(24)
#define WATCH_ADDRESS_TYPE_VEL_LOOP_INTERGRAL			(25)
#define WATCH_ADDRESS_TYPE_SPRING_OFFSET				(26)
#define WATCH_ADDRESS_TYPE_BEFORE_SPRING				(27)
#define WATCH_ADDRESS_TYPE_AFTER_SPRING					(28)
#define WATCH_ADDRESS_TYPE_OBSERVER_LOWPASS_OUTPUT		(29)
#define WATCH_ADDRESS_TYPE_OBSERVER_OUTPUT_PRE			(30)
#define WATCH_ADDRESS_TYPE_OBSERVER_TORQUE_CMD_PRE		(31)
#define WATCH_ADDRESS_TYPE_OBSERVER_VEL_FEEDBACK_INTERGRAL		(32)
#define WATCH_ADDRESS_TYPE_OBSERVER_VEL_ERR_FEEDBACK_INTERGRAL	(33)

#define WATCH_ADDRESS_TYPE_ADC							(40)

#define WATCH_ADDRESS_TYPE_SCAN_SEGMENT_NUMBER			(200)

#define WATCH_ADDRESS_TYPE_SCAN_PRF_VEL					(210)

#define WATCH_ADDRESS_TYPE_SCAN_CRD_POS_X				(220)
#define WATCH_ADDRESS_TYPE_SCAN_CRD_POS_Y				(221)

#define WATCH_ADDRESS_TYPE_LASER_HSIO					(230)

#define WATCH_ADDRESS_TYPE_LASER_POWER					(240)

typedef struct Watch
{
	short count;
	short interval;
	unsigned long address[WATCH_LIST_MAX];
	short length[WATCH_LIST_MAX];
	unsigned long threshold;
} TWatch;

GT_API GT_SetWatch(TWatch *pWatch);
GT_API GT_StartWatch(void);
GT_API GT_StartWatchStatic(void);
GT_API GT_StopWatch(void);
GT_API GT_StopWatchStatic(void);
GT_API GT_LoadWatchFifo(short fifo,short *pBuf);
GT_API GT_GetWatchFifo(short *pFifo);
GT_API GT_GetWatchAddress(short type,short index,unsigned long *pAddress,short count=1);
GT_API GT_GetWatchSts(short *pRun,unsigned long *pCount);
GT_API GT_GetWatchData(unsigned long offset,short *pData,short count=1);

typedef struct
{
	short vender;
	short deviceSizeExp;
	short eraseBlockRegion;
	short sector[4];
	short density[4];
} TFlashInfo;


GT_API GT_FlashToSdram(long *pRetry=NULL);
GT_API GT_SdramToFlash(long *pRetry=NULL);
GT_API GT_SdramToFlash2(long *pRetry=NULL);

GT_API GT_TestSdram(void);
GT_API GT_SetMemory(unsigned long address,short count,short *pData);
GT_API GT_GetMemory(unsigned long address,short count,short *pData);

GT_API GT_FlashQuery(TFlashInfo *pFlashInfo);
GT_API GT_FlashReadId(short *pMid,short *pDid);
GT_API GT_FlashBlockErase(unsigned long offset);
GT_API GT_FlashRead(unsigned long offset,short count,short *pData);
GT_API GT_FlashProgram(unsigned long offset,short count,short *pData,long *pRetry=NULL);
GT_API GT_FlashSetReg(short chip,short index,short value);
GT_API GT_FlashGetReg(short chip,short index,short *pValue);
GT_API GT_FlashSelect(short chip,short port,short module);
GT_API GT_SetRetainValue(unsigned long address,short count,short *pData);
GT_API GT_GetRetainValue(unsigned long address,short count,short *pData);

GT_API GTN_FlashToSdram(short core,long *pRetry);
GT_API GTN_SdramToFlash(short core,long *pRetry);

GT_API GTN_FlashQuery(short core,TFlashInfo *pFlashInfo);
GT_API GTN_FlashReadId(short core,short *pMid,short *pDid);
GT_API GTN_FlashBlockErase(short core,unsigned long offset);
GT_API GTN_FlashRead(short core,unsigned long offset,short count,short *pData);
GT_API GTN_FlashProgram(short core,unsigned long offset,short count,short *pData,long *pRetry=NULL);
GT_API GTN_FlashSetReg(short core,short chip,short index,short value);
GT_API GTN_FlashGetReg(short core,short chip,short index,short *pValue);
GT_API GTN_FlashSelect(short core,short chip,short port,short module);

GT_API GT_LinkCaptureOffset(short encoder,short source);
GT_API GT_SetCaptureOffset(short encoder,long *pOffset,short count,long loop);
GT_API GT_GetCaptureOffset(short encoder,long *pOffset,short *pCount,long *pLoop);
GT_API GT_GetCaptureOffsetStatus(short encoder,short *pCount,long *pLoop,long *pCapturePos);

GT_API GT_SetCaptureEncoder(short trigger,short encoder);
GT_API GT_GetCaptureWidth(short trigger,short *pWidth,short count);

GT_API GT_AutoCaptureOn(short encoder);
GT_API GT_AutoCaptureOff(short encoder);
GT_API GT_SetCaptureCount(short encoder,unsigned long count);
GT_API GT_GetCaptureCount(short encoder,unsigned long *pCount,short count=1,unsigned long *pClock=NULL);

GT_API GTN_LinkCaptureOffset(short core,short encoder,short source);
GT_API GTN_SetCaptureOffset(short core,short encoder,long *pOffset,short count,long loop);
GT_API GTN_GetCaptureOffset(short core,short encoder,long *pOffset,short *pCount,long *pLoop);
GT_API GTN_GetCaptureOffsetStatus(short core,short encoder,short *pCount,long *pLoop,long *pCapturePos);

typedef struct ControlInfo
{
	double refPos;
	double refPosFilter;
	double refPosFilter2;
	double cntPos;
	double cntPosFilter;

	double error;
	double refVel;
	double refAcc;

	short value;
	short valueFilter;

	short offset;
} TControlInfo;

typedef struct
{
	unsigned long notify;
	unsigned long receive;
	unsigned long execute;
	unsigned long retry;
	unsigned long receiveError;
	unsigned long echo;
} TCommandCount;

GT_API GT_ClearCommandCount(void);
GT_API GT_GetCommandCount(TCommandCount *pCommandCount);
GT_API GT_SetServoTime(long servoTime,long delay,long stepCoef);
GT_API GT_GetServoTime(long *pServoTime,long *pDelay,long *pStepCoef);
GT_API GT_GetControlInfo(short control,TControlInfo *pControlInfo);
GT_API GT_ClearMcStatus(void);
GT_API GT_SetMcInfo(long info,long index,unsigned long data);
GT_API GT_GetMcInfo(long info,long index,unsigned long *pData);

GT_API GTN_ClearCommandCount(short core);
GT_API GTN_GetCommandCount(short core,TCommandCount *pCommandCount);
GT_API GTN_SetServoTime(short core,long servoTime,long delay,long stepCoef);
GT_API GTN_GetServoTime(short core,long *pServoTime,long *pDelay,long *pStepCoef);
GT_API GTN_GetControlInfo(short core,short control,TControlInfo *pControlInfo);
GT_API GTN_ClearMcStatus(short core);
GT_API GTN_SetMcInfo(short core,long info,long index,unsigned long data);
GT_API GTN_GetMcInfo(short core,long info,long index,unsigned long *pData);

GT_API GT_GetEncPosModulo(short encoder,double *pValue,short count=1,unsigned long *pClock=NULL);
GT_API GT_GetEncPosRegist(short encoder,double *pValue,short count=1,unsigned long *pClock=NULL);

GT_API GT_GetFlashPassword(unsigned short *pPassword);
GT_API GT_CheckFlashPassword(void);

GT_API GT_CheckPassword(char *pPassword);
GT_API GT_ModifyPassword(char *pOldPassword,char *pNewPassword);

#define WATCH_VAR_CLOCK						(1200)
#define WATCH_VAR_PRF_LOOP					(1201)

#define WATCH_VAR_SKIP_MODULE				(1211)
#define WATCH_VAR_TEST_MODE					(1212)

#define WATCH_VAR_COMMAND_CODE				(1220)
#define WATCH_VAR_COMMAND_DATA				(1221)
#define WATCH_VAR_COMMAND_COUNT				(1222)
#define WATCH_VAR_COMMAND_READ_FLAG 		(1223)

#define WATCH_VAR_LINK_PORT_TX_USE			(1660)
#define WATCH_VAR_LINK_PORT_TX_REQUIRE		(1661)

#define WATCH_VAR_PRF_POS					(6000)
#define WATCH_VAR_PRF_VEL					(6001)
#define WATCH_VAR_PRF_ACC					(6002)

#define WATCH_VAR_PRF_RUN					(6200)

#define WATCH_VAR_PT_PRF_POS_F64			(6650)

#define WATCH_VAR_CRD_PRF_POS				(8000)
#define WATCH_VAR_CRD_PRF_VEL				(8001)
#define WATCH_VAR_CRD_PRF_ACC				(8002)

#define WATCH_VAR_CRD_RUN					(8200)

#define WATCH_VAR_CRD_SEGMENT_NUMBER		(8202)
#define WATCH_VAR_CRD_SEGMENT_NUMBER_USER	(8203)
#define WATCH_VAR_CRD_COMMAND_RECEIVE		(8204)
#define WATCH_VAR_CRD_COMMAND_EXECUTE		(8205)

#define WATCH_VAR_POS_COMPARE_COMMAND_RECEIVE	(17422)
#define WATCH_VAR_POS_COMPARE_COMMAND_SEND		(17423)
#define WATCH_VAR_POS_COMPARE_COMMAND_LEFT		(17424)
#define WATCH_VAR_POS_COMPARE_COMMAND_TX		(17425)

#define WATCH_VAR_SCAN_PRF_POS				(18000)
#define WATCH_VAR_SCAN_PRF_VEL				(18001)
#define WATCH_VAR_SCAN_PRF_ACC				(18002)

#define WATCH_VAR_SCAN_PRF_POS_X			(18010)
#define WATCH_VAR_SCAN_PRF_POS_Y			(18020)

#define WATCH_VAR_SCAN_RUN					(18200)

#define WATCH_VAR_SCAN_SEGMENT_NUMBER		(18202)

#define WATCH_VAR_SCAN_COMMAND_RECEIVE		(18422)
#define WATCH_VAR_SCAN_COMMAND_SEND			(18423)
#define WATCH_VAR_SCAN_COMMAND_LEFT			(18424)
#define WATCH_VAR_SCAN_COMMAND_TX			(18425)

#define WATCH_VAR_LASER_HSIO				(18600)
#define WATCH_VAR_LASER_POWER				(18601)

#define WATCH_VAR_AXIS_PRF_POS				(20000)
#define WATCH_VAR_AXIS_PRF_VEL				(20001)
#define WATCH_VAR_AXIS_PRF_ACC				(20002)

#define WATCH_VAR_AXIS_PRF_POS_OTHER		(20004)
#define WATCH_VAR_AXIS_PRF_VEL_OTHER		(20005)

#define WATCH_VAR_AXIS_PRF_VEL_FILTER		(20011)

#define WATCH_VAR_AXIS_STATUS		        (20100)

#define WATCH_VAR_ENC_POS					(30000)

#define WATCH_VAR_GPI						(31000)
#define WATCH_VAR_LIMIT_POSITIVE			(31010)
#define WATCH_VAR_LIMIT_NEGATIVE			(31020)
#define WATCH_VAR_ALARM   		        	(31030)
#define WATCH_VAR_HOME             			(31040)
#define WATCH_VAR_ARRIVE           			(31050)

#define WATCH_VAR_GPO						(32000)
#define WATCH_VAR_ENABLE					(32010)
#define WATCH_VAR_CLEAR 					(32020)

#define WATCH_VAR_AI     					(33000)

#define WATCH_VAR_AO     					(34000)

#define WATCH_VAR_TRIGGER_EXECUTE			(38000)
#define WATCH_VAR_TRIGGER_STATUS			(38001)
#define WATCH_VAR_TRIGGER_POSITION			(38002)

#define WATCH_VAR_TRIGGER_COUNT				(38010)

#define WATCH_VAR_TRIGGER_NOTIFY_ENABLE			(38020)
#define WATCH_VAR_TRIGGER_NOTIFY_STATUS_ECHO	(38021)
#define WATCH_VAR_TRIGGER_NOTIFY_CLEAR_WAIT		(38022)

#define WATCH_VAR_TRIGGER_DELTA_CROSS_COUNT		(38110)

#define WATCH_VAR_POS_LOOP_ERROR			(40000)

#define WATCH_VAR_WATCH_TIME				(52001)

#define WATCH_VAR_INT32						(52020)
#define WATCH_VAR_INT64						(52021)
#define WATCH_VAR_FLOAT						(52022)
#define WATCH_VAR_DOUBLE					(52023)

#define WATCH_VAR_TERMINAL_LIMIT_POSITIVE	(53000)
#define WATCH_VAR_TERMINAL_LIMIT_NEGATIVE	(53001)
#define WATCH_VAR_TERMINAL_ALARM			(53002)
#define WATCH_VAR_TERMINAL_HOME				(53003)
#define WATCH_VAR_TERMINAL_GPI				(53004)
#define WATCH_VAR_TERMINAL_ARRIVE			(53005)

#define WATCH_VAR_TERMINAL_MPG				(53009)
#define WATCH_VAR_TERMINAL_ENABLE			(53010)
#define WATCH_VAR_TERMINAL_CLEAR			(53011)
#define WATCH_VAR_TERMINAL_GPO				(53012)

#define WATCH_VAR_TERMINAL_DAC				(53020)

#define WATCH_VAR_TERMINAL_PULSE			(53022)
#define WATCH_VAR_TERMINAL_ENCODER			(53023)
#define WATCH_VAR_TERMINAL_ADC				(53024)

#define WATCH_VAR_TERMINAL_AU_ENCODER		(53026)

#define WATCH_VAR_TERMINAL_PRF_POS			(53030)

#define WATCH_VAR_TERMINAL_TRIGGER_POSITION	(53040)
#define WATCH_VAR_TERMINAL_TRIGGER_STATUS	(53041)

#define WATCH_VAR_TERMINAL_COMMAND			(53100)
#define WATCH_VAR_TERMINAL_STATUS			(53101)

typedef struct
{
	short enable;						// 采集使能
	short run;							// 采集状态
	unsigned long time;					// 采集次数
	unsigned long head;					// 头指针
	unsigned long threshold;			// 最多容纳采集次数

	short interval;						// 采集间隔
	short mode;							// 采集模式
	unsigned short countBeforeEvent;	// 事件触发之前的采集数量
	unsigned short countAfterEvent;		// 事件触发以后的采集数量
	unsigned short varCount;			// 采集变量数量
	unsigned short eventCount;			// 采集事件数量
} TWatchInfo;

typedef struct
{
	short width;
	short precision;
	char seperator;
	short hex;
} TWatchFormat;

GT_API GT_GetWatchInfo(TWatchInfo *pInfo);
GT_API GT_SetWatchFormat(const TWatchFormat *pFormat);
GT_API GT_GetWatchFormat(TWatchFormat *pFormat);
GT_API GT_GetWatchInfoEx(short group,TWatchInfo *pInfo);
GT_API GT_SetWatchFormatEx(short group,const TWatchFormat *pFormat);
GT_API GT_GetWatchFormatEx(short group,TWatchFormat *pFormat);

GT_API GTN_GetWatchInfo(short core,TWatchInfo *pInfo);
GT_API GTN_SetWatchFormat(short core,const TWatchFormat *pFormat);
GT_API GTN_GetWatchFormat(short core,TWatchFormat *pFormat);
GT_API GTN_SetWatchFormatEx(short core,short group,const TWatchFormat *pFormat);
GT_API GTN_GetWatchFormatEx(short core,short group,TWatchFormat *pFormat);
GT_API GTN_GetWatchInfoEx(short core,short group,TWatchInfo *pInfo);

#define TERMINAL_OPERATION_NONE             (0)
#define TERMINAL_OPERATION_SKIP             (1)
#define TERMINAL_OPERATION_CLEAR            (2)
#define TERMINAL_OPERATION_RESET_MODULE     (3)

#define TERMINAL_OPERATION_PROGRAM          (11)

typedef struct
{
	unsigned long portACrcOkCnt;
	unsigned short portACrcErrorCnt;
	unsigned long portBCrcOkCnt;
	unsigned short portBCrcErrorCnt;
	unsigned long reserve;//目前用于读取FLASH总数据长度
} TRingNetCrcStatus;

typedef struct
{
	unsigned short errorCountReceive;
	unsigned short errorCountPackageDown;
	unsigned short errorCountPackageUp;
	/*unsigned long portACrcOkCnt;
	unsigned short portACrcErrorCnt;
	unsigned long portBCrcOkCnt;
	unsigned short portBCrcErrorCnt;*/
	unsigned short reserve[13];
} TTerminalError;

typedef struct
{
	short moduleDataType;
	short moduleDataIndex;
	short dataIndex;
	short dataCount;
} TTerminalMap;

GT_API GT_SaveTerminalConfig(short core,char *pFile);
GT_API GT_TerminalOn(short index);
GT_API GT_TerminalSynch(short index);
GT_API GT_GetRintNetCrcStatus(short index,TRingNetCrcStatus *pRingNetCrcStatus);
GT_API GT_GetTerminalStatus(short index,TTerminalStatus *pTerminalStatus);
GT_API GT_GetTerminalError(short core,short station,TTerminalError *pTerminalError);
GT_API GT_SetTerminalType(short count,short *pType);
GT_API GT_SetTerminalSafeMode(short core,short index,short safeMode);
GT_API GT_GetTerminalSafeMode(short core,short index,short *pSafeMode);
GT_API GT_ClearTerminalSafeMode(short port,short index);
GT_API GT_GetTerminalType(short count,unsigned short *pType,short *pTypeConnect);
GT_API GT_GetTerminalPhyId(short count,short *pPhyId);
GT_API GT_GetTerminalLinkStatus(short core,short count,short *ringNetType,short *pLinkStatus);
GT_API GT_SetTerminalMap(short dataType,short moduleIndex,TTerminalMap *pMap);
GT_API GT_GetTerminalMap(short dataType,short moduleIndex,TTerminalMap *pMap);
GT_API GT_ClearTerminalMap(short dataType);
GT_API GT_SetTerminalMode(short core,short index,unsigned short mode);
GT_API GT_GetTerminalMode(short core,short index,unsigned short *pMode);
GT_API GT_SetTerminalTest(short core,short station,short index,unsigned short value);
GT_API GT_GetTerminalTest(short core,short station,short index,unsigned short *pValue);
GT_API GT_SetTerminalOperation(short operation);
GT_API GT_GetTerminalOperation(short *pOperation);
//GT_API GT_SetMailbox(short station,unsigned short address,unsigned short *pData,unsigned short count=1);
GT_API GT_SetMailbox(short core,short station,unsigned short byteAddress,unsigned short *pData,unsigned short wordCount,unsigned short dataMode,unsigned short desId,unsigned short type);
GT_API GT_GetMailbox(short core,short station,unsigned short byteAddress,unsigned short *pData,unsigned short wordCount,unsigned short dataMode,unsigned short desId,unsigned short type);
GT_API GTN_SaveTerminalConfig(short core,char *pFile);
GT_API GTN_TerminalOn(short core,short index);
GT_API GTN_TerminalSynch(short core,short index);
GT_API GTN_GetRingNetCrcStatus(short core,short index,TRingNetCrcStatus *pRingNetCrcStatus);
GT_API GTN_GetTerminalError(short core,short index,TTerminalError *pTerminalError);
GT_API GTN_SetTerminalType(short core,short count,short *pType);
GT_API GTN_GetTerminalPhyId(short core,short count,short *pPhyId);
GT_API GTN_GetTerminalLinkStatus(short core,short count,short *ringNetType,short *pLinkStatus);
GT_API GTN_SetTerminalMap(short core,short dataType,short moduleIndex,TTerminalMap *pMap);
GT_API GTN_GetTerminalMap(short core,short dataType,short moduleIndex,TTerminalMap *pMap);
GT_API GTN_ClearTerminalMap(short core,short dataType);
GT_API GTN_SetTerminalMode(short core,short station,unsigned short mode);
GT_API GTN_GetTerminalMode(short core,short station,unsigned short *pMode);
GT_API GTN_SetTerminalTest(short core,short station,short index,unsigned short value);
GT_API GTN_GetTerminalTest(short core,short station,short index,unsigned short *pValue);
GT_API GTN_SetTerminalOperation(short core,short operation);
GT_API GTN_GetTerminalOperation(short core,short *pOperation);
GT_API  GTN_SetMailbox(short core,short station,unsigned short byteAddress,unsigned short *pData,unsigned short wordCount,unsigned short dataMode,unsigned short desId,unsigned short type);
GT_API GTN_GetMailbox(short core,short station,unsigned short byteAddress,unsigned short *pData,unsigned short wordCount,unsigned short dataMode,unsigned short desId,unsigned short type);
GT_API GTN_GetUuid(short core,char *pCode,short count);
GT_API GTN_SetUuid(short core,char *pCode,short count);
GT_API GTN_GetTerminalPhyId(short core,short count,short *pPhyId);
typedef struct
{
	short active;
	short checkError;
	short linkError;
	short packageErrorCount;
	short pad[8];
} TExtModuleStatus;

typedef struct
{
	short type;
	short input;
	short output;
} TExtModuleType;

typedef struct
{
	short station;
	short module;
	short index;
} TExtIoMap;

GT_API GT_SetILinkDo(short station,short module,unsigned short data,unsigned short mask);
GT_API GT_GetILinkDi(short station,short module,unsigned short *data);
GT_API GT_SetILinkAo(short station,short module,short channel,double data);
GT_API GT_GetILinkAi(short station,short module,short channel,double *data);

GT_API GT_SaveExtModuleConfig(short core,char *pFile);
GT_API GT_ExtModuleOn(short core,short station);
GT_API GT_ExtModuleOff(short core,short station);
GT_API GT_GetExtModuleStatus(short core,short station,TExtModuleStatus *pStatus);
GT_API GT_SetExtModuleId(short core,short station,short count,short *pId);
GT_API GT_GetExtModuleId(short core,short station,short count,short *pId);
GT_API GT_SetExtModuleReverse(short core,short station,short module,short inputCount,short *pInputReverse,short outputCount,short *pOutputReverse);
GT_API GT_GetExtModuleReverse(short core,short station,short module,short inputCount,short *pInputReverse,short outputCount,short *pOutputReverse);
GT_API GT_GetExtModuleCount(short core,short station,short *pCount);
GT_API GT_GetExtModuleType(short core,short station,short module,TExtModuleType *pModuleType);
GT_API GT_SetExtIoMap(short core,short type,short index,TExtIoMap *pMap);
GT_API GT_GetExtIoMap(short core,short type,short index,TExtIoMap *pMap);
GT_API GT_ClearExtIoMap(short core,short type);
GT_API GT_SetExtAoRange(short core,short index,double max,double min);
GT_API GT_GetExtAoRange(short core,short index,double *pMax,double *pMin);
GT_API GT_SetExtAiRange(short core,short index,double max,double min);
GT_API GT_GetExtAiRange(short core,short index,double *pMax,double *pMin);

GT_API GTN_SaveExtModuleConfig(short core,char *pFile);
GT_API GTN_SaveRingNetConfig(short core,char *pFile);
GT_API GTN_ExtModuleOn(short core,short station);
GT_API GTN_ExtModuleOff(short core,short station);
GT_API GTN_GetExtModuleStatus(short core,short station,TExtModuleStatus *pStatus);
GT_API GTN_SetExtModuleId(short core,short station,short count,short *pId);
GT_API GTN_GetExtModuleId(short core,short station,short count,short *pId);
GT_API GTN_SetExtModuleReverse(short core,short station,short module,short inputCount,short *pInputReverse,short outputCount,short *pOutputReverse);
GT_API GTN_GetExtModuleReverse(short core,short station,short module,short inputCount,short *pInputReverse,short outputCount,short *pOutputReverse);
GT_API GTN_GetExtModuleCount(short core,short station,short *pCount);
GT_API GTN_GetExtModuleType(short core,short station,short module,TExtModuleType *pModuleType);
GT_API GTN_SetExtIoMap(short core,short type,short index,TExtIoMap *pMap);
GT_API GTN_GetExtIoMap(short core,short type,short index,TExtIoMap *pMap);
GT_API GTN_ClearExtIoMap(short core,short type);
GT_API GTN_SetExtAoRange(short core,short index,double max,double min);
GT_API GTN_GetExtAoRange(short core,short index,double *pMax,double *pMin);
GT_API GTN_SetExtAiRange(short core,short index,double max,double min);
GT_API GTN_GetExtAiRange(short core,short index,double *pMax,double *pMin);

GT_API GT_OpenExtMdl(char *pDllName);
GT_API GT_CloseExtMdl(void);
GT_API GT_LoadExtConfig(char *pFileName);
GT_API GT_ResetExtMdl(void);
GT_API GT_SetExtIoValue(short module,unsigned short value,short station);
GT_API GT_GetExtIoValue(short module,unsigned short *pValue,short station);
GT_API GT_SetExtIoBit(short module,short index,unsigned short value,short station);
GT_API GT_GetExtIoBit(short module,short index,unsigned short *pValue,short station);
GT_API GT_GetExtDoValue(short module,unsigned short *pValue,short station);
GT_API GT_GetExtAdValue(short module,short channel,unsigned short *pValue,short station);
GT_API GT_SetExtDaValue(short module,short channel,unsigned short value,short station);

struct TScanCommandMotion
{
	long segmentNumber;
	short x;
	short y;
	long deltaX;
	long deltaY;
	long vel;
	long acc;
};

struct TScanCommandMotionDelay
{
	long delay;
};

struct TScanCommandDo
{
	short doType;
	short doMask;
	short doValue;
};

struct TScanCommandDoDelay
{
	long delay;
};

struct TScanCommandLaser
{
	short mask;
	short value;
} ;

struct TScanCommandLaserDelay
{
	long laserOnDelay;
	long laserOffDelay;
} ;

struct TScanCommandLaserPower
{
	long power;
} ;

struct TScanCommandLaserFrequency
{
	long frequency;
} ;

struct TScanCommandLaserPulseWidth
{
	long pulseWidth;
} ;

struct TScanCommandDa
{
	short daIndex;
	short daValue;
} ;

GT_API GT_ScanCrdData(short code ,void *pScanCrdData,short crd=0,short port=1);

typedef struct
{
	short module;
	short fifo;
} TScanMap;

GT_API GT_SetScanMap(short core,short index,TScanMap *pScanMap);
GT_API GT_GetScanMap(short core,short index,TScanMap *pScanMap);
GT_API GT_ClearScanMap(short core);
GT_API GT_UpdateScanMap(short core);

GT_API GTN_SetScanMap(short core,short index,TScanMap *pMap);
GT_API GTN_GetScanMap(short core,short index,TScanMap *pMap);
GT_API GTN_ClearScanMap(short core);
GT_API GTN_UpdateScanMap(short core);

typedef struct
{
	short module;
	short fifo;
} TPosCompareMap;

GT_API GT_SetPosCompareMap(short core,short index,TPosCompareMap *pPosCompare);
GT_API GT_GetPosCompareMap(short core,short index,TPosCompareMap *pPosCompare);
GT_API GT_ClearPosCompareMap(short core);

GT_API GTN_SetPosCompareMap(short core,short index,TPosCompareMap *pMap);
GT_API GTN_GetPosCompareMap(short core,short index,TPosCompareMap *pMap);
GT_API GTN_ClearPosCompareMap(short core);

#define COMPARE_SEND_DATA_MAX			(30)			        //每次最多发送30个位置数据
#define COMPARE_DATA_MAX				(4096)		            //最大位置个数为4096
#define COMPARE_STEP_MAX				(0x1fff)		        //最大单步间隔为14位符号数
#define COMPARE_MAX_NUM					(0x3fffffff)

GT_API GT_ComparePulse(short level,short outputType,short time);
GT_API GT_CompareStop();
GT_API GT_CompareStatus(short *pStatus,long *pCount);
GT_API GT_CompareData(short encoder,short source,short pulseType,short startLevel,short time,
	long *pBuf1,short count1,long *pBuf2,short count2);
GT_API GT_CompareLinear(short encoder,short channel,long startPos,long repeatTimes,long interval,short time,short source);


GT_API GT_SetFollowRegist(short profile,short segment,short fifo);
GT_API GT_GetFollowRegist(short profile,short *pSegment,short fifo);
GT_API GT_GetFollowRegistCount(short profile,unsigned long *pCount);

GT_API GT_SetFollowVirtualSeg(short profile,short segment,short axis,short fifo);
GT_API GT_GetFollowVirtualSeg(short profile,short *pSegment,short *pAxis,short fifo);

GT_API GT_GetFollowVirtualErr(short profile,double *pVirtualErr);
GT_API GT_ClearFollowVirtualErr(short profile);

GT_API GT_HomeInit();
GT_API GT_Home(short axis,long pos,double vel,double acc,long offset);
GT_API GT_Index(short axis,long pos,long offset);
GT_API GT_HomeStop(short axis,long pos,double vel,double acc);
GT_API GT_HomeSts(short axis,unsigned short *pStatus);

//GT_API GT_HandwheelInit();
GT_API GT_SetHandwheelStopDec(short slave,double decSmoothStop,double decAbruptStop);
GT_API GT_StartHandwheel(short slave,short master,short masterEven,short slaveEven,short intervalTime,double acc,double dec,double vel,short stopWaitTime);
GT_API GT_EndHandwheel(short slave);
