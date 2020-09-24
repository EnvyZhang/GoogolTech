/****************************************************************************
** Meta object code from reading C++ file 'ecathome.h'
**
** Created: Thu Aug 20 20:22:50 2020
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../ecathome.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ecathome.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EcatHome[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   10,    9,    9, 0x08,
      62,    9,    9,    9, 0x08,
      95,    9,    9,    9, 0x08,
     127,    9,    9,    9, 0x08,
     161,    9,    9,    9, 0x08,
     194,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_EcatHome[] = {
    "EcatHome\0\0index\0"
    "on_comboBox_homeMode_currentIndexChanged(int)\0"
    "on_pushButton_homeMode_clicked()\0"
    "on_pushButton_cspMode_clicked()\0"
    "on_pushButton_startHome_clicked()\0"
    "on_pushButton_stopHome_clicked()\0"
    "on_pushButton_servOn_clicked()\0"
};

const QMetaObject EcatHome::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EcatHome,
      qt_meta_data_EcatHome, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EcatHome::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EcatHome::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EcatHome::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EcatHome))
        return static_cast<void*>(const_cast< EcatHome*>(this));
    return QWidget::qt_metacast(_clname);
}

int EcatHome::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_comboBox_homeMode_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: on_pushButton_homeMode_clicked(); break;
        case 2: on_pushButton_cspMode_clicked(); break;
        case 3: on_pushButton_startHome_clicked(); break;
        case 4: on_pushButton_stopHome_clicked(); break;
        case 5: on_pushButton_servOn_clicked(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
