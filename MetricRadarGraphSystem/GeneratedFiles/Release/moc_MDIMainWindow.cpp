/****************************************************************************
** Meta object code from reading C++ file 'MDIMainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../MDIMainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MDIMainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MDIMainWindow_t {
    QByteArrayData data[22];
    char stringdata0[318];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MDIMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MDIMainWindow_t qt_meta_stringdata_MDIMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MDIMainWindow"
QT_MOC_LITERAL(1, 14, 13), // "slot_openFile"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 12), // "slot_openDir"
QT_MOC_LITERAL(4, 42, 18), // "slot_doubleClicked"
QT_MOC_LITERAL(5, 61, 5), // "index"
QT_MOC_LITERAL(6, 67, 9), // "slot_save"
QT_MOC_LITERAL(7, 77, 12), // "slot_saveall"
QT_MOC_LITERAL(8, 90, 17), // "slot_mainSettings"
QT_MOC_LITERAL(9, 108, 21), // "slot_createColorTable"
QT_MOC_LITERAL(10, 130, 22), // "slot_legendDataChanged"
QT_MOC_LITERAL(11, 153, 8), // "itemInfo"
QT_MOC_LITERAL(12, 162, 20), // "QList<QwtLegendData>"
QT_MOC_LITERAL(13, 183, 4), // "data"
QT_MOC_LITERAL(14, 188, 16), // "slot_TileWindows"
QT_MOC_LITERAL(15, 205, 19), // "slot_CascadeWindows"
QT_MOC_LITERAL(16, 225, 13), // "slot_CloseDir"
QT_MOC_LITERAL(17, 239, 9), // "slot_Exit"
QT_MOC_LITERAL(18, 249, 22), // "slot_CloseAllWinAction"
QT_MOC_LITERAL(19, 272, 23), // "slot_subWindowActivated"
QT_MOC_LITERAL(20, 296, 14), // "QMdiSubWindow*"
QT_MOC_LITERAL(21, 311, 6) // "window"

    },
    "MDIMainWindow\0slot_openFile\0\0slot_openDir\0"
    "slot_doubleClicked\0index\0slot_save\0"
    "slot_saveall\0slot_mainSettings\0"
    "slot_createColorTable\0slot_legendDataChanged\0"
    "itemInfo\0QList<QwtLegendData>\0data\0"
    "slot_TileWindows\0slot_CascadeWindows\0"
    "slot_CloseDir\0slot_Exit\0slot_CloseAllWinAction\0"
    "slot_subWindowActivated\0QMdiSubWindow*\0"
    "window"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MDIMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x0a /* Public */,
       3,    1,   87,    2, 0x0a /* Public */,
       4,    1,   90,    2, 0x0a /* Public */,
       6,    1,   93,    2, 0x0a /* Public */,
       7,    1,   96,    2, 0x0a /* Public */,
       8,    1,   99,    2, 0x0a /* Public */,
       9,    1,  102,    2, 0x0a /* Public */,
      10,    2,  105,    2, 0x0a /* Public */,
      14,    1,  110,    2, 0x0a /* Public */,
      15,    1,  113,    2, 0x0a /* Public */,
      16,    1,  116,    2, 0x0a /* Public */,
      17,    1,  119,    2, 0x0a /* Public */,
      18,    1,  122,    2, 0x0a /* Public */,
      19,    1,  125,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QModelIndex,    5,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QVariant, 0x80000000 | 12,   11,   13,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 20,   21,

       0        // eod
};

void MDIMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MDIMainWindow *_t = static_cast<MDIMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_openFile((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->slot_openDir((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->slot_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: _t->slot_save((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->slot_saveall((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->slot_mainSettings((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->slot_createColorTable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->slot_legendDataChanged((*reinterpret_cast< const QVariant(*)>(_a[1])),(*reinterpret_cast< const QList<QwtLegendData>(*)>(_a[2]))); break;
        case 8: _t->slot_TileWindows((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->slot_CascadeWindows((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->slot_CloseDir((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->slot_Exit((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->slot_CloseAllWinAction((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->slot_subWindowActivated((*reinterpret_cast< QMdiSubWindow*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MDIMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MDIMainWindow.data,
      qt_meta_data_MDIMainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MDIMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MDIMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MDIMainWindow.stringdata0))
        return static_cast<void*>(const_cast< MDIMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MDIMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
