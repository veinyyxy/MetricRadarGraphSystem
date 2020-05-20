/****************************************************************************
** Meta object code from reading C++ file 'RadarPlotPicker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../RadarPlotPicker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RadarPlotPicker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RadarPlotPicker_t {
    QByteArrayData data[4];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RadarPlotPicker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RadarPlotPicker_t qt_meta_stringdata_RadarPlotPicker = {
    {
QT_MOC_LITERAL(0, 0, 15), // "RadarPlotPicker"
QT_MOC_LITERAL(1, 16, 12), // "CurrentPoint"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 4) // "posF"

    },
    "RadarPlotPicker\0CurrentPoint\0\0posF"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RadarPlotPicker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPointF,    3,

       0        // eod
};

void RadarPlotPicker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RadarPlotPicker *_t = static_cast<RadarPlotPicker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CurrentPoint((*reinterpret_cast< const QPointF(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RadarPlotPicker::*_t)(const QPointF & ) const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RadarPlotPicker::CurrentPoint)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject RadarPlotPicker::staticMetaObject = {
    { &QwtPlotPicker::staticMetaObject, qt_meta_stringdata_RadarPlotPicker.data,
      qt_meta_data_RadarPlotPicker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RadarPlotPicker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RadarPlotPicker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RadarPlotPicker.stringdata0))
        return static_cast<void*>(const_cast< RadarPlotPicker*>(this));
    return QwtPlotPicker::qt_metacast(_clname);
}

int RadarPlotPicker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtPlotPicker::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void RadarPlotPicker::CurrentPoint(const QPointF & _t1)const
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(const_cast< RadarPlotPicker *>(this), &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
