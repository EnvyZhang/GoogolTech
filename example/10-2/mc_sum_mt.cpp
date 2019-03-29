// ���� 10-2 �˶�������߳��ۼ����
#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include "gts.h"

int main(int argc, char* argv[])
{
	short rtn;
	TCompileInfo compile;
	short funId;
	TVarInfo sum,begin,end;
	double value;
	TThreadSts thread;
	
	// ���˶�������
	rtn = GT_Open();
	printf("GT_Open()=%d\n",rtn);

	// ��λ�˶�������
	rtn = GT_Reset();
	printf("GT_Reset()=%d\n",rtn);

	// �����˶�����sum.c
	// ��ʹ��MCT2008->����->�˶����������������б���
	// ����ɹ��Ժ�����sum.bin��sum.ini
	// ���뱣֤error.ini�ļ�λ�ڹ����ļ�����
	//rtn = GT_Compile("sum.c",&compile);
	//printf("GT_Compile()=%d\n",rtn);

	// �����˶�����sum.bin
	rtn = GT_Download("sum.bin");
	printf("GT_Download()=%d\n",rtn);
	
	// ��ȡ����ID
	rtn = GT_GetFunId("add",&funId);
	printf("GT_GetFunId()=%d\n",rtn);
	
	// ��ȡȫ�ֱ���sum��ID
	rtn = GT_GetVarId(NULL,"sum",&sum);
	printf("GT_GetVarId()=%d\n",rtn);

	// ��ȡ�ֲ�����begin��ID
	rtn = GT_GetVarId("add","begin",&begin);
	printf("GT_GetVarId()=%d\n",rtn);

	// ��ȡ�ֲ�����end��ID
	rtn = GT_GetVarId("add","end",&end);
	printf("GT_GetVarId()=%d\n",rtn);
	
	// ���̣߳�����������ҳ
	rtn = GT_Bind(0,funId,0);
	printf("GT_Bind()=%d\n",rtn);

	// ���̣߳�����������ҳ
	rtn = GT_Bind(1,funId,1);
	printf("GT_Bind()=%d\n",rtn);

	value = 0;
	// ��ʼ���˶������ȫ�ֱ���sum
	rtn = GT_SetVarValue(-1,&sum,&value);
	printf("GT_SetVarValue()=%d\n",rtn);

	value = 1;
	// ��ʼ���˶�����ľֲ�����begin
	rtn = GT_SetVarValue(0,&begin,&value);
	printf("GT_SetVarValue()=%d\n",rtn);
	
	value = 50;
	// ��ʼ���˶�����ľֲ�����end
	rtn = GT_SetVarValue(0,&end,&value);
	printf("GT_SetVarValue()=%d\n",rtn);

	value = 51;
	// ��ʼ���˶�����ľֲ�����begin
	rtn = GT_SetVarValue(1,&begin,&value);
	printf("GT_SetVarValue()=%d\n",rtn);
	
	value = 100;
	// ��ʼ���˶�����ľֲ�����end
	rtn = GT_SetVarValue(1,&end,&value);
	printf("GT_SetVarValue()=%d\n",rtn);
	
	// �����߳�
	rtn = GT_RunThread(0);
	printf("GT_RunThread()=%d\n",rtn);

	// �����߳�
	rtn = GT_RunThread(1);
	printf("GT_RunThread()=%d\n",rtn);

	do
	{
		// ��ѯ�߳�״̬
		rtn = GT_GetThreadSts(0,&thread);
	}while( 1 == thread.run );	// �ȴ��߳����н���

	do
	{
		// ��ѯ�߳�״̬
		rtn = GT_GetThreadSts(1,&thread);
	}while( 1 == thread.run );	// �ȴ��߳����н���

	// ��ѯȫ�ֱ���sum��ֵ
	rtn = GT_GetVarValue(-1,&sum,&value);
	printf("sum=%-10.0lf",value);

	getch();

	return 0;
}

