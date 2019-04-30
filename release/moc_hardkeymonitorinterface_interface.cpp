/****************************************************************************
** Meta object code from reading C++ file 'hardkeymonitorinterface_interface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../hardkeymonitorinterface_interface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hardkeymonitorinterface_interface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ComTiotDbusHardkeyInterface_t {
    QByteArrayData data[10];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ComTiotDbusHardkeyInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ComTiotDbusHardkeyInterface_t qt_meta_stringdata_ComTiotDbusHardkeyInterface = {
    {
QT_MOC_LITERAL(0, 0, 27), // "ComTiotDbusHardkeyInterface"
QT_MOC_LITERAL(1, 28, 11), // "sigKeyEvent"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 5), // "msgID"
QT_MOC_LITERAL(4, 47, 5), // "param"
QT_MOC_LITERAL(5, 53, 12), // "QDBusVariant"
QT_MOC_LITERAL(6, 66, 12), // "sendKeyEvent"
QT_MOC_LITERAL(7, 79, 19), // "QDBusPendingReply<>"
QT_MOC_LITERAL(8, 99, 15), // "sendKeyEventInt"
QT_MOC_LITERAL(9, 115, 6) // "wakeUp"

    },
    "ComTiotDbusHardkeyInterface\0sigKeyEvent\0"
    "\0msgID\0param\0QDBusVariant\0sendKeyEvent\0"
    "QDBusPendingReply<>\0sendKeyEventInt\0"
    "wakeUp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ComTiotDbusHardkeyInterface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       1,    2,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   49,    2, 0x0a /* Public */,
       8,    2,   54,    2, 0x0a /* Public */,
       9,    0,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, 0x80000000 | 5, QMetaType::QVariantList,    3,    4,

 // slots: parameters
    0x80000000 | 7, 0x80000000 | 5, QMetaType::QVariantList,    3,    4,
    0x80000000 | 7, QMetaType::Int, QMetaType::Int,    3,    4,
    0x80000000 | 7,

       0        // eod
};

void ComTiotDbusHardkeyInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ComTiotDbusHardkeyInterface *_t = static_cast<ComTiotDbusHardkeyInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigKeyEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->sigKeyEvent((*reinterpret_cast< const QDBusVariant(*)>(_a[1])),(*reinterpret_cast< const QVariantList(*)>(_a[2]))); break;
        case 2: { QDBusPendingReply<> _r = _t->sendKeyEvent((*reinterpret_cast< const QDBusVariant(*)>(_a[1])),(*reinterpret_cast< const QVariantList(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = std::move(_r); }  break;
        case 3: { QDBusPendingReply<> _r = _t->sendKeyEventInt((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = std::move(_r); }  break;
        case 4: { QDBusPendingReply<> _r = _t->wakeUp();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QDBusVariant >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QDBusVariant >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ComTiotDbusHardkeyInterface::*_t)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComTiotDbusHardkeyInterface::sigKeyEvent)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ComTiotDbusHardkeyInterface::*_t)(const QDBusVariant & , const QVariantList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComTiotDbusHardkeyInterface::sigKeyEvent)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ComTiotDbusHardkeyInterface::staticMetaObject = {
    { &QDBusAbstractInterface::staticMetaObject, qt_meta_stringdata_ComTiotDbusHardkeyInterface.data,
      qt_meta_data_ComTiotDbusHardkeyInterface,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ComTiotDbusHardkeyInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ComTiotDbusHardkeyInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ComTiotDbusHardkeyInterface.stringdata0))
        return static_cast<void*>(this);
    return QDBusAbstractInterface::qt_metacast(_clname);
}

int ComTiotDbusHardkeyInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ComTiotDbusHardkeyInterface::sigKeyEvent(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ComTiotDbusHardkeyInterface::sigKeyEvent(const QDBusVariant & _t1, const QVariantList & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
