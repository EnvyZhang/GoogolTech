/****************************************************************************
** Meta object code from reading C++ file 'ecatprob.h'
**
** Created: Tue Sep 15 15:14:56 2020
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../ecatprob.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ecatprob.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EcatProb[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      38,    9,    9,    9, 0x08,
      66,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_EcatProb[] = {
    "EcatProb\0\0probelPrmWidgetChangeSlot()\0"
    "on_pushButton_set_clicked()\0"
    "on_pushButton_get_clicked()\0"
};

const QMetaObject EcatProb::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EcatProb,
      qt_meta_data_EcatProb, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EcatProb::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EcatProb::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EcatProb::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EcatProb))
        return static_cast<void*>(const_cast< EcatProb*>(this));
    return QWidget::qt_metacast(_clname);
}

int EcatProb::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: probelPrmWidgetChangeSlot(); break;
        case 1: on_pushButton_set_clicked(); break;
        case 2: on_pushButton_get_clicked(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
