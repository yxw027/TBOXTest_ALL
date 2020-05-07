/****************************************************************************
** Meta object code from reading C++ file 'bt_interface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../bt_interface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bt_interface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ComQtYeedonBtInterface_t {
    QByteArrayData data[63];
    char stringdata0[1010];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ComQtYeedonBtInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ComQtYeedonBtInterface_t qt_meta_stringdata_ComQtYeedonBtInterface = {
    {
QT_MOC_LITERAL(0, 0, 22), // "ComQtYeedonBtInterface"
QT_MOC_LITERAL(1, 23, 13), // "sigBleDevName"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 4), // "name"
QT_MOC_LITERAL(4, 43, 16), // "sigConnectStatus"
QT_MOC_LITERAL(5, 60, 4), // "type"
QT_MOC_LITERAL(6, 65, 15), // "sigContactsInfo"
QT_MOC_LITERAL(7, 81, 6), // "number"
QT_MOC_LITERAL(8, 88, 17), // "sigDownloadStatus"
QT_MOC_LITERAL(9, 106, 6), // "status"
QT_MOC_LITERAL(10, 113, 16), // "sigHfpCallStatus"
QT_MOC_LITERAL(11, 130, 15), // "sigHfpCommandOK"
QT_MOC_LITERAL(12, 146, 10), // "sigIapData"
QT_MOC_LITERAL(13, 157, 4), // "info"
QT_MOC_LITERAL(14, 162, 14), // "sigInquiryInfo"
QT_MOC_LITERAL(15, 177, 4), // "addr"
QT_MOC_LITERAL(16, 182, 3), // "cod"
QT_MOC_LITERAL(17, 186, 4), // "rssi"
QT_MOC_LITERAL(18, 191, 16), // "sigInquiryStatus"
QT_MOC_LITERAL(19, 208, 18), // "sigLocalDeviceInfo"
QT_MOC_LITERAL(20, 227, 12), // "sigMusicInfo"
QT_MOC_LITERAL(21, 240, 5), // "title"
QT_MOC_LITERAL(22, 246, 6), // "artist"
QT_MOC_LITERAL(23, 253, 5), // "album"
QT_MOC_LITERAL(24, 259, 18), // "sigMusicPlayStatus"
QT_MOC_LITERAL(25, 278, 14), // "sigMusicSource"
QT_MOC_LITERAL(26, 293, 13), // "sigPairedInfo"
QT_MOC_LITERAL(27, 307, 14), // "sigRecordsInfo"
QT_MOC_LITERAL(28, 322, 4), // "time"
QT_MOC_LITERAL(29, 327, 22), // "sigRemoteConnectStatus"
QT_MOC_LITERAL(30, 350, 23), // "sigRemotePairingRequest"
QT_MOC_LITERAL(31, 374, 10), // "sigSppData"
QT_MOC_LITERAL(32, 385, 15), // "sigSwitchStatus"
QT_MOC_LITERAL(33, 401, 4), // "echo"
QT_MOC_LITERAL(34, 406, 26), // "QDBusPendingReply<QString>"
QT_MOC_LITERAL(35, 433, 20), // "request_AvrcpCommand"
QT_MOC_LITERAL(36, 454, 23), // "QDBusPendingReply<bool>"
QT_MOC_LITERAL(37, 478, 19), // "request_CloseDevice"
QT_MOC_LITERAL(38, 498, 19), // "QDBusPendingReply<>"
QT_MOC_LITERAL(39, 518, 26), // "request_DeletePairedDevice"
QT_MOC_LITERAL(40, 545, 7), // "address"
QT_MOC_LITERAL(41, 553, 28), // "request_GetAutoConnectStatus"
QT_MOC_LITERAL(42, 582, 29), // "request_GetAutoReactionStatus"
QT_MOC_LITERAL(43, 612, 22), // "QDBusPendingReply<int>"
QT_MOC_LITERAL(44, 635, 24), // "request_GetConnectStatus"
QT_MOC_LITERAL(45, 660, 18), // "request_HfpCommand"
QT_MOC_LITERAL(46, 679, 6), // "Number"
QT_MOC_LITERAL(47, 686, 18), // "request_OpenDevice"
QT_MOC_LITERAL(48, 705, 21), // "request_PairingDevice"
QT_MOC_LITERAL(49, 727, 22), // "request_PairingRespond"
QT_MOC_LITERAL(50, 750, 20), // "request_PbapDownLoad"
QT_MOC_LITERAL(51, 771, 18), // "request_ScanDevice"
QT_MOC_LITERAL(52, 790, 16), // "request_ScanGatt"
QT_MOC_LITERAL(53, 807, 21), // "request_SendDataToIap"
QT_MOC_LITERAL(54, 829, 21), // "request_SendDataToSpp"
QT_MOC_LITERAL(55, 851, 19), // "request_SetA2dpMute"
QT_MOC_LITERAL(56, 871, 6), // "action"
QT_MOC_LITERAL(57, 878, 28), // "request_SetAutoConnectStatus"
QT_MOC_LITERAL(58, 907, 29), // "request_SetAutoReactionStatus"
QT_MOC_LITERAL(59, 937, 3), // "sec"
QT_MOC_LITERAL(60, 941, 26), // "request_SetLocalDeviceName"
QT_MOC_LITERAL(61, 968, 18), // "request_SetMicMute"
QT_MOC_LITERAL(62, 987, 22) // "request_connectProfile"

    },
    "ComQtYeedonBtInterface\0sigBleDevName\0"
    "\0name\0sigConnectStatus\0type\0sigContactsInfo\0"
    "number\0sigDownloadStatus\0status\0"
    "sigHfpCallStatus\0sigHfpCommandOK\0"
    "sigIapData\0info\0sigInquiryInfo\0addr\0"
    "cod\0rssi\0sigInquiryStatus\0sigLocalDeviceInfo\0"
    "sigMusicInfo\0title\0artist\0album\0"
    "sigMusicPlayStatus\0sigMusicSource\0"
    "sigPairedInfo\0sigRecordsInfo\0time\0"
    "sigRemoteConnectStatus\0sigRemotePairingRequest\0"
    "sigSppData\0sigSwitchStatus\0echo\0"
    "QDBusPendingReply<QString>\0"
    "request_AvrcpCommand\0QDBusPendingReply<bool>\0"
    "request_CloseDevice\0QDBusPendingReply<>\0"
    "request_DeletePairedDevice\0address\0"
    "request_GetAutoConnectStatus\0"
    "request_GetAutoReactionStatus\0"
    "QDBusPendingReply<int>\0request_GetConnectStatus\0"
    "request_HfpCommand\0Number\0request_OpenDevice\0"
    "request_PairingDevice\0request_PairingRespond\0"
    "request_PbapDownLoad\0request_ScanDevice\0"
    "request_ScanGatt\0request_SendDataToIap\0"
    "request_SendDataToSpp\0request_SetA2dpMute\0"
    "action\0request_SetAutoConnectStatus\0"
    "request_SetAutoReactionStatus\0sec\0"
    "request_SetLocalDeviceName\0"
    "request_SetMicMute\0request_connectProfile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ComQtYeedonBtInterface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      41,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      19,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  219,    2, 0x06 /* Public */,
       4,    1,  222,    2, 0x06 /* Public */,
       6,    3,  225,    2, 0x06 /* Public */,
       8,    2,  232,    2, 0x06 /* Public */,
      10,    2,  237,    2, 0x06 /* Public */,
      11,    2,  242,    2, 0x06 /* Public */,
      12,    1,  247,    2, 0x06 /* Public */,
      14,    4,  250,    2, 0x06 /* Public */,
      18,    1,  259,    2, 0x06 /* Public */,
      19,    2,  262,    2, 0x06 /* Public */,
      20,    3,  267,    2, 0x06 /* Public */,
      24,    1,  274,    2, 0x06 /* Public */,
      25,    0,  277,    2, 0x06 /* Public */,
      26,    2,  278,    2, 0x06 /* Public */,
      27,    4,  283,    2, 0x06 /* Public */,
      29,    2,  292,    2, 0x06 /* Public */,
      30,    0,  297,    2, 0x06 /* Public */,
      31,    1,  298,    2, 0x06 /* Public */,
      32,    1,  301,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      33,    0,  304,    2, 0x0a /* Public */,
      35,    1,  305,    2, 0x0a /* Public */,
      37,    0,  308,    2, 0x0a /* Public */,
      39,    1,  309,    2, 0x0a /* Public */,
      41,    0,  312,    2, 0x0a /* Public */,
      42,    0,  313,    2, 0x0a /* Public */,
      44,    0,  314,    2, 0x0a /* Public */,
      45,    2,  315,    2, 0x0a /* Public */,
      47,    0,  320,    2, 0x0a /* Public */,
      48,    2,  321,    2, 0x0a /* Public */,
      49,    1,  326,    2, 0x0a /* Public */,
      50,    1,  329,    2, 0x0a /* Public */,
      51,    1,  332,    2, 0x0a /* Public */,
      52,    1,  335,    2, 0x0a /* Public */,
      53,    1,  338,    2, 0x0a /* Public */,
      54,    1,  341,    2, 0x0a /* Public */,
      55,    1,  344,    2, 0x0a /* Public */,
      57,    1,  347,    2, 0x0a /* Public */,
      58,    2,  350,    2, 0x0a /* Public */,
      60,    1,  355,    2, 0x0a /* Public */,
      61,    2,  358,    2, 0x0a /* Public */,
      62,    0,  363,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,    3,    7,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    5,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    5,    9,
    QMetaType::Void, QMetaType::QByteArray,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   15,    3,   16,   17,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   15,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   21,   22,   23,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   15,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,    3,    7,   28,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   15,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   13,
    QMetaType::Void, QMetaType::Bool,    9,

 // slots: parameters
    0x80000000 | 34,
    0x80000000 | 36, QMetaType::Int,    5,
    0x80000000 | 38,
    0x80000000 | 36, QMetaType::QString,   40,
    0x80000000 | 36,
    0x80000000 | 43,
    0x80000000 | 36,
    0x80000000 | 38, QMetaType::Int, QMetaType::QString,    5,   46,
    0x80000000 | 38,
    0x80000000 | 38, QMetaType::QString, QMetaType::Bool,   40,    9,
    0x80000000 | 38, QMetaType::Int,    9,
    0x80000000 | 36, QMetaType::Int,    5,
    0x80000000 | 38, QMetaType::Bool,    9,
    0x80000000 | 38, QMetaType::Int,    5,
    0x80000000 | 43, QMetaType::QByteArray,   13,
    0x80000000 | 43, QMetaType::QByteArray,   13,
    0x80000000 | 36, QMetaType::Int,   56,
    0x80000000 | 36, QMetaType::Bool,    9,
    0x80000000 | 36, QMetaType::Int, QMetaType::Int,    5,   59,
    0x80000000 | 36, QMetaType::QString,    3,
    0x80000000 | 36, QMetaType::QString, QMetaType::Int,   40,   56,
    0x80000000 | 36,

       0        // eod
};

void ComQtYeedonBtInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ComQtYeedonBtInterface *_t = static_cast<ComQtYeedonBtInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigBleDevName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->sigConnectStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sigContactsInfo((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->sigDownloadStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->sigHfpCallStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->sigHfpCommandOK((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 6: _t->sigIapData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 7: _t->sigInquiryInfo((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 8: _t->sigInquiryStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->sigLocalDeviceInfo((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 10: _t->sigMusicInfo((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 11: _t->sigMusicPlayStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->sigMusicSource(); break;
        case 13: _t->sigPairedInfo((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 14: _t->sigRecordsInfo((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 15: _t->sigRemoteConnectStatus((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 16: _t->sigRemotePairingRequest(); break;
        case 17: _t->sigSppData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 18: _t->sigSwitchStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: { QDBusPendingReply<QString> _r = _t->echo();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<QString>*>(_a[0]) = std::move(_r); }  break;
        case 20: { QDBusPendingReply<bool> _r = _t->request_AvrcpCommand((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<bool>*>(_a[0]) = std::move(_r); }  break;
        case 21: { QDBusPendingReply<> _r = _t->request_CloseDevice();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = std::move(_r); }  break;
        case 22: { QDBusPendingReply<bool> _r = _t->request_DeletePairedDevice((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<bool>*>(_a[0]) = std::move(_r); }  break;
        case 23: { QDBusPendingReply<bool> _r = _t->request_GetAutoConnectStatus();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<bool>*>(_a[0]) = std::move(_r); }  break;
        case 24: { QDBusPendingReply<int> _r = _t->request_GetAutoReactionStatus();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<int>*>(_a[0]) = std::move(_r); }  break;
        case 25: { QDBusPendingReply<bool> _r = _t->request_GetConnectStatus();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<bool>*>(_a[0]) = std::move(_r); }  break;
        case 26: { QDBusPendingReply<> _r = _t->request_HfpCommand((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = std::move(_r); }  break;
        case 27: { QDBusPendingReply<> _r = _t->request_OpenDevice();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = std::move(_r); }  break;
        case 28: { QDBusPendingReply<> _r = _t->request_PairingDevice((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = std::move(_r); }  break;
        case 29: { QDBusPendingReply<> _r = _t->request_PairingRespond((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = std::move(_r); }  break;
        case 30: { QDBusPendingReply<bool> _r = _t->request_PbapDownLoad((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<bool>*>(_a[0]) = std::move(_r); }  break;
        case 31: { QDBusPendingReply<> _r = _t->request_ScanDevice((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = std::move(_r); }  break;
        case 32: { QDBusPendingReply<> _r = _t->request_ScanGatt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = std::move(_r); }  break;
        case 33: { QDBusPendingReply<int> _r = _t->request_SendDataToIap((*reinterpret_cast< const QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<int>*>(_a[0]) = std::move(_r); }  break;
        case 34: { QDBusPendingReply<int> _r = _t->request_SendDataToSpp((*reinterpret_cast< const QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<int>*>(_a[0]) = std::move(_r); }  break;
        case 35: { QDBusPendingReply<bool> _r = _t->request_SetA2dpMute((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<bool>*>(_a[0]) = std::move(_r); }  break;
        case 36: { QDBusPendingReply<bool> _r = _t->request_SetAutoConnectStatus((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<bool>*>(_a[0]) = std::move(_r); }  break;
        case 37: { QDBusPendingReply<bool> _r = _t->request_SetAutoReactionStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<bool>*>(_a[0]) = std::move(_r); }  break;
        case 38: { QDBusPendingReply<bool> _r = _t->request_SetLocalDeviceName((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<bool>*>(_a[0]) = std::move(_r); }  break;
        case 39: { QDBusPendingReply<bool> _r = _t->request_SetMicMute((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<bool>*>(_a[0]) = std::move(_r); }  break;
        case 40: { QDBusPendingReply<bool> _r = _t->request_connectProfile();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<bool>*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ComQtYeedonBtInterface::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonBtInterface::sigBleDevName)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ComQtYeedonBtInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonBtInterface::sigConnectStatus)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ComQtYeedonBtInterface::*_t)(const QString & , const QString & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonBtInterface::sigContactsInfo)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ComQtYeedonBtInterface::*_t)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonBtInterface::sigDownloadStatus)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (ComQtYeedonBtInterface::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonBtInterface::sigHfpCallStatus)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (ComQtYeedonBtInterface::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonBtInterface::sigHfpCommandOK)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (ComQtYeedonBtInterface::*_t)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonBtInterface::sigIapData)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (ComQtYeedonBtInterface::*_t)(const QString & , const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonBtInterface::sigInquiryInfo)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (ComQtYeedonBtInterface::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonBtInterface::sigInquiryStatus)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (ComQtYeedonBtInterface::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonBtInterface::sigLocalDeviceInfo)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (ComQtYeedonBtInterface::*_t)(const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonBtInterface::sigMusicInfo)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (ComQtYeedonBtInterface::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonBtInterface::sigMusicPlayStatus)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (ComQtYeedonBtInterface::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonBtInterface::sigMusicSource)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (ComQtYeedonBtInterface::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonBtInterface::sigPairedInfo)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (ComQtYeedonBtInterface::*_t)(const QString & , const QString & , const QString & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonBtInterface::sigRecordsInfo)) {
                *result = 14;
                return;
            }
        }
        {
            typedef void (ComQtYeedonBtInterface::*_t)(const QString & , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonBtInterface::sigRemoteConnectStatus)) {
                *result = 15;
                return;
            }
        }
        {
            typedef void (ComQtYeedonBtInterface::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonBtInterface::sigRemotePairingRequest)) {
                *result = 16;
                return;
            }
        }
        {
            typedef void (ComQtYeedonBtInterface::*_t)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonBtInterface::sigSppData)) {
                *result = 17;
                return;
            }
        }
        {
            typedef void (ComQtYeedonBtInterface::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonBtInterface::sigSwitchStatus)) {
                *result = 18;
                return;
            }
        }
    }
}

const QMetaObject ComQtYeedonBtInterface::staticMetaObject = {
    { &QDBusAbstractInterface::staticMetaObject, qt_meta_stringdata_ComQtYeedonBtInterface.data,
      qt_meta_data_ComQtYeedonBtInterface,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ComQtYeedonBtInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ComQtYeedonBtInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ComQtYeedonBtInterface.stringdata0))
        return static_cast<void*>(this);
    return QDBusAbstractInterface::qt_metacast(_clname);
}

int ComQtYeedonBtInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 41)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 41;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 41)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 41;
    }
    return _id;
}

// SIGNAL 0
void ComQtYeedonBtInterface::sigBleDevName(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ComQtYeedonBtInterface::sigConnectStatus(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ComQtYeedonBtInterface::sigContactsInfo(const QString & _t1, const QString & _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ComQtYeedonBtInterface::sigDownloadStatus(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ComQtYeedonBtInterface::sigHfpCallStatus(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ComQtYeedonBtInterface::sigHfpCommandOK(int _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ComQtYeedonBtInterface::sigIapData(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ComQtYeedonBtInterface::sigInquiryInfo(const QString & _t1, const QString & _t2, const QString & _t3, const QString & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ComQtYeedonBtInterface::sigInquiryStatus(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ComQtYeedonBtInterface::sigLocalDeviceInfo(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ComQtYeedonBtInterface::sigMusicInfo(const QString & _t1, const QString & _t2, const QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void ComQtYeedonBtInterface::sigMusicPlayStatus(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void ComQtYeedonBtInterface::sigMusicSource()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void ComQtYeedonBtInterface::sigPairedInfo(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void ComQtYeedonBtInterface::sigRecordsInfo(const QString & _t1, const QString & _t2, const QString & _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void ComQtYeedonBtInterface::sigRemoteConnectStatus(const QString & _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void ComQtYeedonBtInterface::sigRemotePairingRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}

// SIGNAL 17
void ComQtYeedonBtInterface::sigSppData(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void ComQtYeedonBtInterface::sigSwitchStatus(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
