/****************************************************************************
** Meta object code from reading C++ file 'ecatdemo.h'
**
** Created: Thu Aug 20 20:26:32 2020
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../ecatdemo.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ecatdemo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EcatDemo[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   10,    9,    9, 0x08,
      58,   10,    9,    9, 0x08,
     100,    9,    9,    9, 0x08,
     128,    9,    9,    9, 0x08,
     157,    9,    9,    9, 0x08,
     186,    9,    9,    9, 0x08,
     215,    9,    9,    9, 0x08,
     244,    9,    9,    9, 0x08,
     273,    9,    9,    9, 0x08,
     302,    9,    9,    9, 0x08,
     331,    9,    9,    9, 0x08,
     361,    9,    9,    9, 0x08,
     392,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_EcatDemo[] = {
    "EcatDemo\0\0index\0"
    "on_comboBox_core_currentIndexChanged(int)\0"
    "on_comboBox_axis_currentIndexChanged(int)\0"
    "on_pushButton_clr_clicked()\0"
    "on_pushButton_serv_clicked()\0"
    "on_pushButton_zero_clicked()\0"
    "on_pushButton_stop_clicked()\0"
    "on_pushButton_jogN_clicked()\0"
    "on_pushButton_jogP_clicked()\0"
    "on_pushButton_home_clicked()\0"
    "on_pushButton_prob_clicked()\0"
    "on_pushButton_alarm_clicked()\0"
    "on_pushButton_object_clicked()\0"
    "refreshStatusInfoSlot()\0"
};

const QMetaObject EcatDemo::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EcatDemo,
      qt_meta_data_EcatDemo, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EcatDemo::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EcatDemo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EcatDemo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EcatDemo))
        return static_cast<void*>(const_cast< EcatDemo*>(this));
    return QWidget::qt_metacast(_clname);
}

int EcatDemo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_comboBox_core_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: on_comboBox_axis_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: on_pushButton_clr_clicked(); break;
        case 3: on_pushButton_serv_clicked(); break;
        case 4: on_pushButton_zero_clicked(); break;
        case 5: on_pushButton_stop_clicked(); break;
        case 6: on_pushButton_jogN_clicked(); break;
        case 7: on_pushButton_jogP_clicked(); break;
        case 8: on_pushButton_home_clicked(); break;
        case 9: on_pushButton_prob_clicked(); break;
        case 10: on_pushButton_alarm_clicked(); break;
        case 11: on_pushButton_object_clicked(); break;
        case 12: refreshStatusInfoSlot(); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
