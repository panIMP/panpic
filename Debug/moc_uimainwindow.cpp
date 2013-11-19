/****************************************************************************
** Meta object code from reading C++ file 'uimainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../uimainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uimainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UiMainWindow_t {
    QByteArrayData data[25];
    char stringdata[276];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_UiMainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_UiMainWindow_t qt_meta_stringdata_UiMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 12),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 11),
QT_MOC_LITERAL(4, 39, 17),
QT_MOC_LITERAL(5, 57, 16),
QT_MOC_LITERAL(6, 74, 7),
QT_MOC_LITERAL(7, 82, 7),
QT_MOC_LITERAL(8, 90, 7),
QT_MOC_LITERAL(9, 98, 4),
QT_MOC_LITERAL(10, 103, 6),
QT_MOC_LITERAL(11, 110, 13),
QT_MOC_LITERAL(12, 124, 17),
QT_MOC_LITERAL(13, 142, 7),
QT_MOC_LITERAL(14, 150, 7),
QT_MOC_LITERAL(15, 158, 7),
QT_MOC_LITERAL(16, 166, 8),
QT_MOC_LITERAL(17, 175, 12),
QT_MOC_LITERAL(18, 188, 5),
QT_MOC_LITERAL(19, 194, 15),
QT_MOC_LITERAL(20, 210, 15),
QT_MOC_LITERAL(21, 226, 12),
QT_MOC_LITERAL(22, 239, 9),
QT_MOC_LITERAL(23, 249, 16),
QT_MOC_LITERAL(24, 266, 8)
    },
    "UiMainWindow\0ImageChanged\0\0ImageLoaded\0"
    "MouseOnPicWheeled\0PicIndexSwitched\0"
    "OpenPic\0NextPic\0PrevPic\0Save\0SaveAs\0"
    "RotateClkwise\0RotateCntrClkwise\0MirrorH\0"
    "MirrorV\0ZoomPic\0curValue\0ZoomRateDisp\0"
    "value\0ShowCurIndexPic\0ShowCurPicIndex\0"
    "EqualizeHist\0MatchHist\0CreateHistDialog\0"
    "HasImage\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UiMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       1,  156, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  119,    2, 0x05,
       3,    1,  120,    2, 0x05,
       4,    1,  123,    2, 0x05,
       5,    2,  126,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       6,    0,  131,    2, 0x0a,
       7,    0,  132,    2, 0x0a,
       8,    0,  133,    2, 0x0a,
       9,    0,  134,    2, 0x0a,
      10,    0,  135,    2, 0x0a,
      11,    0,  136,    2, 0x0a,
      12,    0,  137,    2, 0x0a,
      13,    0,  138,    2, 0x0a,
      14,    0,  139,    2, 0x0a,
      15,    1,  140,    2, 0x0a,
      15,    0,  143,    2, 0x0a,
      17,    1,  144,    2, 0x0a,
      19,    0,  147,    2, 0x0a,
      20,    2,  148,    2, 0x0a,
      21,    0,  153,    2, 0x0a,
      22,    0,  154,    2, 0x0a,
      23,    0,  155,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      24, QMetaType::Bool, 0x00495003,

 // properties: notify_signal_id
       1,

       0        // eod
};

void UiMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UiMainWindow *_t = static_cast<UiMainWindow *>(_o);
        switch (_id) {
        case 0: _t->ImageChanged(); break;
        case 1: _t->ImageLoaded((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->MouseOnPicWheeled((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->PicIndexSwitched((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->OpenPic(); break;
        case 5: _t->NextPic(); break;
        case 6: _t->PrevPic(); break;
        case 7: _t->Save(); break;
        case 8: _t->SaveAs(); break;
        case 9: _t->RotateClkwise(); break;
        case 10: _t->RotateCntrClkwise(); break;
        case 11: _t->MirrorH(); break;
        case 12: _t->MirrorV(); break;
        case 13: _t->ZoomPic((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->ZoomPic(); break;
        case 15: _t->ZoomRateDisp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->ShowCurIndexPic(); break;
        case 17: _t->ShowCurPicIndex((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 18: _t->EqualizeHist(); break;
        case 19: _t->MatchHist(); break;
        case 20: _t->CreateHistDialog(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UiMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UiMainWindow::ImageChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (UiMainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UiMainWindow::ImageLoaded)) {
                *result = 1;
            }
        }
        {
            typedef void (UiMainWindow::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UiMainWindow::MouseOnPicWheeled)) {
                *result = 2;
            }
        }
        {
            typedef void (UiMainWindow::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UiMainWindow::PicIndexSwitched)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject UiMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_UiMainWindow.data,
      qt_meta_data_UiMainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *UiMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UiMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UiMainWindow.stringdata))
        return static_cast<void*>(const_cast< UiMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int UiMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = HasImage(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: SetHasImage(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void UiMainWindow::ImageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void UiMainWindow::ImageLoaded(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UiMainWindow::MouseOnPicWheeled(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void UiMainWindow::PicIndexSwitched(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
