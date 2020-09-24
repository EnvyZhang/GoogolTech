#include "stdafx.h"
#include "ecatdemo.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//加载语言文件
	QTranslator translator;
	translator.load(":/EcatDemo/vs2008qtecatdemo_zh.qm");//从本地系统加载
	a.installTranslator(&translator);

	EcatDemo w;
	w.show();
	return a.exec();
}
