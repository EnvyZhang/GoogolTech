#include "stdafx.h"
#include "ecatdemo.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//���������ļ�
	QTranslator translator;
	translator.load(":/EcatDemo/vs2008qtecatdemo_zh.qm");//�ӱ���ϵͳ����
	a.installTranslator(&translator);

	EcatDemo w;
	w.show();
	return a.exec();
}
