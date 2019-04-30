/****************************************************************************
** Meta object code from reading C++ file 'filelistitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../filelistitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filelistitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FileListItemModel_t {
    QByteArrayData data[12];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileListItemModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileListItemModel_t qt_meta_stringdata_FileListItemModel = {
    {
QT_MOC_LITERAL(0, 0, 17), // "FileListItemModel"
QT_MOC_LITERAL(1, 18, 18), // "getFilePathByIndex"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 5), // "index"
QT_MOC_LITERAL(4, 44, 18), // "setFileNamebyIndex"
QT_MOC_LITERAL(5, 63, 8), // "fileName"
QT_MOC_LITERAL(6, 72, 18), // "setFilePathbyIndex"
QT_MOC_LITERAL(7, 91, 8), // "filePath"
QT_MOC_LITERAL(8, 100, 21), // "setFileNamebyFilePath"
QT_MOC_LITERAL(9, 122, 5), // "clear"
QT_MOC_LITERAL(10, 128, 3), // "get"
QT_MOC_LITERAL(11, 132, 4) // "role"

    },
    "FileListItemModel\0getFilePathByIndex\0"
    "\0index\0setFileNamebyIndex\0fileName\0"
    "setFilePathbyIndex\0filePath\0"
    "setFileNamebyFilePath\0clear\0get\0role"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileListItemModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x02 /* Public */,
       4,    2,   47,    2, 0x02 /* Public */,
       6,    2,   52,    2, 0x02 /* Public */,
       8,    2,   57,    2, 0x02 /* Public */,
       9,    0,   62,    2, 0x02 /* Public */,
      10,    2,   63,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::QString, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    5,
    QMetaType::Void,
    QMetaType::QVariant, QMetaType::Int, QMetaType::QString,    3,   11,

       0        // eod
};

void FileListItemModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FileListItemModel *_t = static_cast<FileListItemModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QString _r = _t->getFilePathByIndex((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->setFileNamebyIndex((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->setFilePathbyIndex((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->setFileNamebyFilePath((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->clear(); break;
        case 5: { QVariant _r = _t->get((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject FileListItemModel::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_FileListItemModel.data,
      qt_meta_data_FileListItemModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FileListItemModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileListItemModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FileListItemModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int FileListItemModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
