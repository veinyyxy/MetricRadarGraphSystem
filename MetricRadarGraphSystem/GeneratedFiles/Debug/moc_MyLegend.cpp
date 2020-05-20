/****************************************************************************
** Meta object code from reading C++ file 'MyLegend.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../MyLegend.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyLegend.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MyLegend_t {
    QByteArrayData data[6];
    char stringdata0[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyLegend_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyLegend_t qt_meta_stringdata_MyLegend = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MyLegend"
QT_MOC_LITERAL(1, 9, 12), // "updateLegend"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 8), // "itemInfo"
QT_MOC_LITERAL(4, 32, 20), // "QList<QwtLegendData>"
QT_MOC_LITERAL(5, 53, 4) // "data"

    },
    "MyLegend\0updateLegend\0\0itemInfo\0"
    "QList<QwtLegendData>\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyLegend[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QVariant, 0x80000000 | 4,    3,    5,

       0        // eod
};

void MyLegend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyLegend *_t = static_cast<MyLegend *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateLegend((*reinterpret_cast< const QVariant(*)>(_a[1])),(*reinterpret_cast< const QList<QwtLegendData>(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject MyLegend::staticMetaObject = {
    { &QwtLegend::staticMetaObject, qt_meta_stringdata_MyLegend.data,
      qt_meta_data_MyLegend,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MyLegend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyLegend::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MyLegend.stringdata0))
        return static_cast<void*>(const_cast< MyLegend*>(this));
    return QwtLegend::qt_metacast(_clname);
}

int MyLegend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtLegend::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
