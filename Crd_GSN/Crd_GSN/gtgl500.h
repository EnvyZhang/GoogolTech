
typedef struct 
{
	UINT8		*databuf;
	UINT32	datalength;
}Program_Prm;

GT_API GT_SetGLinkDo(short slaveno,unsigned short offset,unsigned char *pData,unsigned short bytelength);
GT_API GT_GetGLinkDo(short slaveno,unsigned short offset,unsigned char *pData,unsigned short bytelength);
GT_API GT_GetGLinkDi(short slaveno,unsigned short offset,unsigned char *pData,unsigned short bytelength);
GT_API GT_SetGLinkDoBit(short slaveno,short doIndex,unsigned char value);
GT_API GT_GetGLinkDiBit(short slaveno,short diIndex,unsigned char *pValue);
GT_API GT_SetGLinkAo(short slaveno,unsigned short channel,short *pData,unsigned short count);
GT_API GT_GetGLinkAo(short slaveno,unsigned short channel,short *pData,unsigned short count);
GT_API GT_GetGLinkAi(short slaveno,unsigned short channel,short *pData,unsigned short count);
GT_API GT_GetGLinkOnlineSlaveNum(unsigned char *slavenum);
GT_API GT_SetGLinkModuleConfig(char *pFile);
GT_API GT_GLinkInit(short cardNum);
GT_API GT_GetGLinkDiEx(short slaveno,unsigned char *pData,unsigned short count);	//slaveno����ʼվ�ţ�count��վ����
//��ȡ����Glink��վ��Ϣ��slavenum���ߴ�վ������slavetype 1DIO16 2AIO0606 4DI32  dilength dolength ���� �ֽ�
GT_API GT_GetGLinkModulesInfo(unsigned char *slavenum,unsigned char *slavetype,unsigned char *subslavetype,unsigned char *dilength,unsigned char *dolength);