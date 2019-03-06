TEMPLATE = app

QT += qml quick core
#QT += core gui
#QT += widgets
QT += network
QT += dbus
QT += multimedia

#TARGET += TBOXTest

CONFIG += c++11
CONFIG += qdbus
CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp \
    mainwindow.cpp \
    filelistitem.cpp \
    QRCode/bitstream.c \
    QRCode/mask.c \
    QRCode/mmask.c \
    QRCode/mqrspec.c \
    QRCode/qrencode.c \
    QRCode/qrinput.c \
    QRCode/qrspec.c \
    QRCode/rscode.c \
    QRCode/split.c \
    candbus_interface.cpp \
    sim800_interface.cpp \
    uartcheck.cpp \
    hardkeymonitorinterface_interface.cpp \
    bt_interface.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    filelistitem.h \
    QRCode/bitstream.h \
    QRCode/config.h \
    QRCode/mask.h \
    QRCode/mmask.h \
    QRCode/mqrspec.h \
    QRCode/qrencode_inner.h \
    QRCode/qrencode.h \
    QRCode/qrinput.h \
    QRCode/qrspec.h \
    QRCode/rscode.h \
    QRCode/split.h \
    candbus_interface.h \
    sim800_interface.h \
    share.h \
    uartcheck.h \
    mainwindow.h \
    hardkeymonitorinterface_interface.h \
    bt_interface.h


unix:!macx: LIBS += -L$$PWD/../../../../../opt/poky-st/2.2.1/sysroots/cortexa7hf-neon-poky-linux-gnueabi/usr/lib/ -lsqlite3

unix:!macx: LIBS += -L$$PWD/../../../../../opt/poky-st/2.2.1/sysroots/cortexa7hf-neon-poky-linux-gnueabi/usr/lib/ -ludev

INCLUDEPATH += $$PWD/../../../../../opt/poky-st/2.2.1/sysroots/cortexa7hf-neon-poky-linux-gnueabi/usr/include
DEPENDPATH += $$PWD/../../../../../opt/poky-st/2.2.1/sysroots/cortexa7hf-neon-poky-linux-gnueabi/usr/include



unix:!macx: LIBS += -lasound
