#ifndef ECATOBJECT_H
#define ECATOBJECT_H

#include <QWidget>
#include "ui_ecatobject.h"

class EcatObject : public QWidget
{
	Q_OBJECT

public:
	EcatObject(QWidget *parent = 0);
	~EcatObject();

	void refreshEcatObjectValue();

private:
	Ui::EcatObject ui;
};

#endif // ECATOBJECT_H
