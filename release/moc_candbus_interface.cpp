/****************************************************************************
** Meta object code from reading C++ file 'candbus_interface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../candbus_interface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'candbus_interface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ComQtYeedonCanInterface_t {
    QByteArrayData data[41];
    char stringdata0[971];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ComQtYeedonCanInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ComQtYeedonCanInterface_t qt_meta_stringdata_ComQtYeedonCanInterface = {
    {
QT_MOC_LITERAL(0, 0, 23), // "ComQtYeedonCanInterface"
QT_MOC_LITERAL(1, 24, 9), // "broadTest"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "value"
QT_MOC_LITERAL(4, 41, 17), // "broadcastAbsFault"
QT_MOC_LITERAL(5, 59, 22), // "broadcastAcPowerOutput"
QT_MOC_LITERAL(6, 82, 15), // "broadcastAccOff"
QT_MOC_LITERAL(7, 98, 33), // "broadcastAppointmentStateOfCh..."
QT_MOC_LITERAL(8, 132, 30), // "broadcastBatteryPackSocLowRank"
QT_MOC_LITERAL(9, 163, 32), // "broadcastBatteryPackVoltageFault"
QT_MOC_LITERAL(10, 196, 38), // "broadcastChargerPowerLineConn..."
QT_MOC_LITERAL(11, 235, 33), // "broadcastChargerSystemFaultSt..."
QT_MOC_LITERAL(12, 269, 23), // "broadcastChargingStatus"
QT_MOC_LITERAL(13, 293, 32), // "broadcastDisconnectChargerRemind"
QT_MOC_LITERAL(14, 326, 35), // "broadcastElectronicBreakFault..."
QT_MOC_LITERAL(15, 362, 23), // "broadcastEpsFaultStatus"
QT_MOC_LITERAL(16, 386, 35), // "broadcastEstimateRemainningDi..."
QT_MOC_LITERAL(17, 422, 18), // "broadcastGearState"
QT_MOC_LITERAL(18, 441, 40), // "broadcastHighVoltageIsolation..."
QT_MOC_LITERAL(19, 482, 25), // "broadcastMotorFaultStatus"
QT_MOC_LITERAL(20, 508, 35), // "broadcastMotorOverTemperature..."
QT_MOC_LITERAL(21, 544, 25), // "broadcastMotorPowerOutput"
QT_MOC_LITERAL(22, 570, 31), // "broadcastPowerBatteryDisconnect"
QT_MOC_LITERAL(23, 602, 32), // "broadcastPowerBatteryFaultStatus"
QT_MOC_LITERAL(24, 635, 19), // "broadcastSimArray03"
QT_MOC_LITERAL(25, 655, 19), // "broadcastSimArray12"
QT_MOC_LITERAL(26, 675, 19), // "broadcastSimArray47"
QT_MOC_LITERAL(27, 695, 20), // "broadcastSimArray811"
QT_MOC_LITERAL(28, 716, 24), // "broadcastVcamFaultStatus"
QT_MOC_LITERAL(29, 741, 28), // "broadcastVehicleAveragePower"
QT_MOC_LITERAL(30, 770, 34), // "broadcastVehicleInstantaneous..."
QT_MOC_LITERAL(31, 805, 19), // "broadcastVinArray03"
QT_MOC_LITERAL(32, 825, 21), // "broadcastVinArray1215"
QT_MOC_LITERAL(33, 847, 19), // "broadcastVinArray16"
QT_MOC_LITERAL(34, 867, 19), // "broadcastVinArray47"
QT_MOC_LITERAL(35, 887, 20), // "broadcastVinArray811"
QT_MOC_LITERAL(36, 908, 8), // "canwrite"
QT_MOC_LITERAL(37, 917, 23), // "QDBusPendingReply<bool>"
QT_MOC_LITERAL(38, 941, 2), // "id"
QT_MOC_LITERAL(39, 944, 6), // "wakeUp"
QT_MOC_LITERAL(40, 951, 19) // "QDBusPendingReply<>"

    },
    "ComQtYeedonCanInterface\0broadTest\0\0"
    "value\0broadcastAbsFault\0broadcastAcPowerOutput\0"
    "broadcastAccOff\0broadcastAppointmentStateOfCharge\0"
    "broadcastBatteryPackSocLowRank\0"
    "broadcastBatteryPackVoltageFault\0"
    "broadcastChargerPowerLineConnectStatus\0"
    "broadcastChargerSystemFaultStatus\0"
    "broadcastChargingStatus\0"
    "broadcastDisconnectChargerRemind\0"
    "broadcastElectronicBreakFaultStatus\0"
    "broadcastEpsFaultStatus\0"
    "broadcastEstimateRemainningDistance\0"
    "broadcastGearState\0"
    "broadcastHighVoltageIsolationFaultStatus\0"
    "broadcastMotorFaultStatus\0"
    "broadcastMotorOverTemperatureStatus\0"
    "broadcastMotorPowerOutput\0"
    "broadcastPowerBatteryDisconnect\0"
    "broadcastPowerBatteryFaultStatus\0"
    "broadcastSimArray03\0broadcastSimArray12\0"
    "broadcastSimArray47\0broadcastSimArray811\0"
    "broadcastVcamFaultStatus\0"
    "broadcastVehicleAveragePower\0"
    "broadcastVehicleInstantaneousPower\0"
    "broadcastVinArray03\0broadcastVinArray1215\0"
    "broadcastVinArray16\0broadcastVinArray47\0"
    "broadcastVinArray811\0canwrite\0"
    "QDBusPendingReply<bool>\0id\0wakeUp\0"
    "QDBusPendingReply<>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ComQtYeedonCanInterface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      35,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      33,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  189,    2, 0x06 /* Public */,
       4,    1,  192,    2, 0x06 /* Public */,
       5,    1,  195,    2, 0x06 /* Public */,
       6,    0,  198,    2, 0x06 /* Public */,
       7,    1,  199,    2, 0x06 /* Public */,
       8,    1,  202,    2, 0x06 /* Public */,
       9,    1,  205,    2, 0x06 /* Public */,
      10,    1,  208,    2, 0x06 /* Public */,
      11,    1,  211,    2, 0x06 /* Public */,
      12,    1,  214,    2, 0x06 /* Public */,
      13,    1,  217,    2, 0x06 /* Public */,
      14,    1,  220,    2, 0x06 /* Public */,
      15,    1,  223,    2, 0x06 /* Public */,
      16,    1,  226,    2, 0x06 /* Public */,
      17,    1,  229,    2, 0x06 /* Public */,
      18,    1,  232,    2, 0x06 /* Public */,
      19,    1,  235,    2, 0x06 /* Public */,
      20,    1,  238,    2, 0x06 /* Public */,
      21,    1,  241,    2, 0x06 /* Public */,
      22,    1,  244,    2, 0x06 /* Public */,
      23,    1,  247,    2, 0x06 /* Public */,
      24,    1,  250,    2, 0x06 /* Public */,
      25,    1,  253,    2, 0x06 /* Public */,
      26,    1,  256,    2, 0x06 /* Public */,
      27,    1,  259,    2, 0x06 /* Public */,
      28,    1,  262,    2, 0x06 /* Public */,
      29,    1,  265,    2, 0x06 /* Public */,
      30,    1,  268,    2, 0x06 /* Public */,
      31,    1,  271,    2, 0x06 /* Public */,
      32,    1,  274,    2, 0x06 /* Public */,
      33,    1,  277,    2, 0x06 /* Public */,
      34,    1,  280,    2, 0x06 /* Public */,
      35,    1,  283,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      36,    2,  286,    2, 0x0a /* Public */,
      39,    0,  291,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    0x80000000 | 37, QMetaType::Int, QMetaType::Int,   38,    3,
    0x80000000 | 40,

       0        // eod
};

void ComQtYeedonCanInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ComQtYeedonCanInterface *_t = static_cast<ComQtYeedonCanInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->broadTest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->broadcastAbsFault((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->broadcastAcPowerOutput((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->broadcastAccOff(); break;
        case 4: _t->broadcastAppointmentStateOfCharge((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->broadcastBatteryPackSocLowRank((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->broadcastBatteryPackVoltageFault((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->broadcastChargerPowerLineConnectStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->broadcastChargerSystemFaultStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->broadcastChargingStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->broadcastDisconnectChargerRemind((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->broadcastElectronicBreakFaultStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->broadcastEpsFaultStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->broadcastEstimateRemainningDistance((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->broadcastGearState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->broadcastHighVoltageIsolationFaultStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->broadcastMotorFaultStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->broadcastMotorOverTemperatureStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->broadcastMotorPowerOutput((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->broadcastPowerBatteryDisconnect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->broadcastPowerBatteryFaultStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->broadcastSimArray03((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->broadcastSimArray12((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->broadcastSimArray47((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->broadcastSimArray811((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->broadcastVcamFaultStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->broadcastVehicleAveragePower((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->broadcastVehicleInstantaneousPower((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->broadcastVinArray03((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->broadcastVinArray1215((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->broadcastVinArray16((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->broadcastVinArray47((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->broadcastVinArray811((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: { QDBusPendingReply<bool> _r = _t->canwrite((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<bool>*>(_a[0]) = std::move(_r); }  break;
        case 34: { QDBusPendingReply<> _r = _t->wakeUp();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadTest)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastAbsFault)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastAcPowerOutput)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastAccOff)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastAppointmentStateOfCharge)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastBatteryPackSocLowRank)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastBatteryPackVoltageFault)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastChargerPowerLineConnectStatus)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastChargerSystemFaultStatus)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastChargingStatus)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastDisconnectChargerRemind)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastElectronicBreakFaultStatus)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastEpsFaultStatus)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastEstimateRemainningDistance)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastGearState)) {
                *result = 14;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastHighVoltageIsolationFaultStatus)) {
                *result = 15;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastMotorFaultStatus)) {
                *result = 16;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastMotorOverTemperatureStatus)) {
                *result = 17;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastMotorPowerOutput)) {
                *result = 18;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastPowerBatteryDisconnect)) {
                *result = 19;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastPowerBatteryFaultStatus)) {
                *result = 20;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastSimArray03)) {
                *result = 21;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastSimArray12)) {
                *result = 22;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastSimArray47)) {
                *result = 23;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastSimArray811)) {
                *result = 24;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastVcamFaultStatus)) {
                *result = 25;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastVehicleAveragePower)) {
                *result = 26;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastVehicleInstantaneousPower)) {
                *result = 27;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastVinArray03)) {
                *result = 28;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastVinArray1215)) {
                *result = 29;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastVinArray16)) {
                *result = 30;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastVinArray47)) {
                *result = 31;
                return;
            }
        }
        {
            typedef void (ComQtYeedonCanInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ComQtYeedonCanInterface::broadcastVinArray811)) {
                *result = 32;
                return;
            }
        }
    }
}

const QMetaObject ComQtYeedonCanInterface::staticMetaObject = {
    { &QDBusAbstractInterface::staticMetaObject, qt_meta_stringdata_ComQtYeedonCanInterface.data,
      qt_meta_data_ComQtYeedonCanInterface,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ComQtYeedonCanInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ComQtYeedonCanInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ComQtYeedonCanInterface.stringdata0))
        return static_cast<void*>(this);
    return QDBusAbstractInterface::qt_metacast(_clname);
}

int ComQtYeedonCanInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 35)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 35;
    }
    return _id;
}

// SIGNAL 0
void ComQtYeedonCanInterface::broadTest(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ComQtYeedonCanInterface::broadcastAbsFault(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ComQtYeedonCanInterface::broadcastAcPowerOutput(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ComQtYeedonCanInterface::broadcastAccOff()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ComQtYeedonCanInterface::broadcastAppointmentStateOfCharge(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ComQtYeedonCanInterface::broadcastBatteryPackSocLowRank(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ComQtYeedonCanInterface::broadcastBatteryPackVoltageFault(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ComQtYeedonCanInterface::broadcastChargerPowerLineConnectStatus(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ComQtYeedonCanInterface::broadcastChargerSystemFaultStatus(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ComQtYeedonCanInterface::broadcastChargingStatus(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ComQtYeedonCanInterface::broadcastDisconnectChargerRemind(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void ComQtYeedonCanInterface::broadcastElectronicBreakFaultStatus(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void ComQtYeedonCanInterface::broadcastEpsFaultStatus(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void ComQtYeedonCanInterface::broadcastEstimateRemainningDistance(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void ComQtYeedonCanInterface::broadcastGearState(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void ComQtYeedonCanInterface::broadcastHighVoltageIsolationFaultStatus(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void ComQtYeedonCanInterface::broadcastMotorFaultStatus(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void ComQtYeedonCanInterface::broadcastMotorOverTemperatureStatus(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void ComQtYeedonCanInterface::broadcastMotorPowerOutput(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void ComQtYeedonCanInterface::broadcastPowerBatteryDisconnect(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void ComQtYeedonCanInterface::broadcastPowerBatteryFaultStatus(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void ComQtYeedonCanInterface::broadcastSimArray03(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void ComQtYeedonCanInterface::broadcastSimArray12(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void ComQtYeedonCanInterface::broadcastSimArray47(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void ComQtYeedonCanInterface::broadcastSimArray811(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void ComQtYeedonCanInterface::broadcastVcamFaultStatus(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void ComQtYeedonCanInterface::broadcastVehicleAveragePower(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void ComQtYeedonCanInterface::broadcastVehicleInstantaneousPower(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void ComQtYeedonCanInterface::broadcastVinArray03(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void ComQtYeedonCanInterface::broadcastVinArray1215(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void ComQtYeedonCanInterface::broadcastVinArray16(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void ComQtYeedonCanInterface::broadcastVinArray47(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 31, _a);
}

// SIGNAL 32
void ComQtYeedonCanInterface::broadcastVinArray811(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 32, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
