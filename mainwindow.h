#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "common.h"
#include <map>
#include "receive/canservice.h"

extern "C" {
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <netdb.h>
//#include </opt/poky-st/2.2.1/sysroots/cortexa7hf-neon-poky-linux-gnueabi/usr/include/libudev.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <net/if.h>
#include <pthread.h>
#include <linux/types.h>
#include <linux/netlink.h>
#include <libudev.h>
#include <alsa/asoundlib.h>
#include <stdio.h>
}

#include<qsettings.h>
#include<QFontDatabase>
#include <QThread>
#include <QQuickView>
#include <filelistitem.h>
#include <QQmlContext>
#include <QTimer>
#include <QIODevice>
#include <QString>
#include <QThread>
#include <QDebug>
#include <QTcpSocket>
#include <QtNetwork>
#include <QAbstractSocket>
#include <QByteArray> 
#include <QQuickImageProvider>
#include <QPainter>
#include <QByteArray>
#include <QVector>
#include <QSoundEffect>
#include <QMap>

#include <candbus_interface.h>
#include "./QRCode/config.h"
#include "./QRCode/mask.h"
#include "./QRCode/mmask.h"
#include "./QRCode/mqrspec.h"
#include "./QRCode/qrencode.h"
#include "./QRCode/qrencode_inner.h"
#include "./QRCode/qrinput.h"
#include "./QRCode/qrspec.h"
#include "./QRCode/rscode.h"
#include "./QRCode/split.h"
#include "./QRCode/bitstream.h"
#include <QQuickImageProvider>
#include <QQmlExtensionPlugin>
#include <qendian.h>
#include <candbus_interface.h>
#include <QMediaPlayer>
#include <QFile>
#include <QTextCodec>
#include <sqlite3.h>


#include <ftimer.h>


#define SQLITE_DATABASE_ONE   "/run/media/usb/"
#define TABLE_NAME          "TBoxData"
#include "hardkeymonitorinterface_interface.h"
//LiberationMono-Regular.ttf
//LiberationSerif-Regular.ttf
//LiberationSans-Regular.ttf
//
#define FONT_PATH "/usr/lib/fonts/MicroVistaHei.ttf"
//#define FONT_NAME "WenQuanYi Micro Hei"
#define FONT_NAME "MicroVistaHei"

#define NonDATONG 00

using namespace std;

class FileListItemModel ;

struct setFile{
    uint8_t serial_number_len;
    char serial_number[30];
    uint8_t vehicle_type_len;
    char vehicle_type;
    uint8_t sk_len;
    char sk[6];
    uint8_t power_len;
    char power[2];
    uint8_t rootkey_len;
    char rootkey[16];
}__attribute__ ((packed));

#define UEVENT_BUFFER_SIZE 2048

#ifndef DEBUG
#define DEBUG 01
#endif

#if DEBUG
#define DEBUGLOG                qDebug()<<"### TBox(DEBUG) ###"<<"["<<__FUNCTION__<<":"<<__LINE__<<"]"
#define DEBUG_PARAM(str, param) qDebug()<<"### TBox(DEBUG) ###"<<"["<<__FUNCTION__<<":"<<__LINE__<<"]"<<str<<param
#define DEBUG_CHAR(str)         qDebug()<<"### TBox(DEBUG) ###"<<"["<<__FUNCTION__<<":"<<__LINE__<<"]"<<str
#define DEBUG_PARAM2(str1, param1, str2, param2) qDebug()<<"### TBox(DEBUG) ###"<<"["<<__FUNCTION__<<":"<<__LINE__<<"]"<<str1<<param1<<", "<<str2<<param2
#else
    #define  DEBUGLOG
    #define  DEBUG_PARAM(str, param)
    #define  DEBUG_CHAR(str)
    #define  DEBUG_PARAM(str1, param1, str2, param2)
#endif

class encode : public QThread
{
public:
    encode(QString path);
    void run();
    void stoprecord();
    snd_pcm_t *handle;
    snd_pcm_hw_params_t *params;
    snd_pcm_uframes_t frames;
    unsigned int val;
    int dir;
    long loops;
    int rc;
    int size;
    char *buffer;
    bool flag=true;
    FILE * fp;
};

class monitorusb : public QThread
{
public:
    monitorusb();
    ~monitorusb() {}
    void run();
    struct udev *udev;
    struct udev_enumerate *enumerate;
    struct udev_list_entry *devices, *dev_list_entry;
    struct udev_device *dev;
    struct udev_monitor *mon;
    int fd;
};

class monitorrndis : public QThread
{
public:
    monitorrndis();
    ~monitorrndis() {}
    void run();
    struct udev *udev;
    struct udev_enumerate *enumerate;
    struct udev_list_entry *devices, *dev_list_entry;
    struct udev_device *dev;
    struct udev_monitor *mon;
    int fd;
};

class FortuneThread : public QThread, public QQuickImageProvider
{
    Q_OBJECT
    //Q_PROPERTY(QString testName WRITE setTestname NOTIFY testnameChanged)
public:
    explicit FortuneThread();
    ~FortuneThread();
    QPixmap generateQRcode(QString tempstr);
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
    QString getNameForIndex(int index, int command);
    void run() Q_DECL_OVERRIDE;
    void qrcodeGroup();
    void initTestListView();
    void iniTableViewByCarinfo();
    void handleCandataMessage(Mailbox_Read_Msg_ST &message);
    void handleQrcode();
    void handleTestItemAck(uint16_t result,uint16_t cmdid);
    void handleErrorItem(int curItem);
    void startNextTestItem();
    void readDID(Mailbox_Read_Msg_ST &message);
    void writeDID(Test_Mode_EN cmdId,PROJECT_INFO_EN infoType);
    void canWriteData(Mailbox_Write_Msg_ST data);
    int  confirmTestResult(uint16_t cmdid);

    static void testTimeout();

    Q_INVOKABLE void init();
    Q_INVOKABLE void restart();
    Q_INVOKABLE void thread_eixt();
    Q_INVOKABLE void disable_12V();

    //fpp
    Q_INVOKABLE void logOut(QString log);

signals:
    void errorCode(QString functionName, int param);
    void qrcode();
    void sigQrGroup();
    void gpsBarData(QVariant num, QVariant strengthNum);
    void gps_start_num(QString num);
    void gps_start_time(QString time);
    void nextOne();
    void time_start(QString testname);
    void time_stop();
    void msg(QByteArray msg);
    void device_disconnect();
    void udisk_disconnect();
    void power_signal(double power, bool val);
    void signal_strength(int strength);
    void show_main_page();
    void show_wifi();
    void m_hardkey(int msgID);
    void mcuVersion(QString mcu_buf);
    void appVersion(QString app_buf);
    void osVersion(QString os_buf);
    void sysVersion(QString sys_buf);
    void setTitleText(QString tText);
    void updateInfo(int index,QString filename);

public slots:
    void onSigQrGroup();
    void onTestItemTimeout();
    
public:
    int m_canidRead;
    int m_canidWrite;
    int m_qrShowFlag;
    int m_testItemCount;

    //Read  DID
    QString m_sw_version;
    QString m_hw_version;
    QString m_v2x_version;
    QString m_hp_version;
    QString m_app_version;

    //Write DID
    QString m_vinCode;
    QString m_productDate;
    QString m_suplayerCode;
    QString m_ipAddr;
    QString m_wifiName;

    QString m_sim_number;
    QString m_imei;
    QString m_imsi;
    QString m_iccid;
    QString m_sn;
    QString m_pn;
    QString reserved1="";
    QString reserved2="";

    QString m_productName;
    QString m_productType;
    QString m_qrShowConfig;
    QString m_testItemConfig;
    Qrcode_Show_Flag_ST Qr_Show_Flag;
    Test_Item_Flag_ST   Test_Item_Flag;
    QMap<int,int> m_MapTestItemFlag;

    FileListItemModel* listModel;
    FileListItemModel* tableModel;
    FileListItemModel* tableMode2;
    FileListItemModel* tableModelQR;
    QSettings* setting;
    QString qrcodeStr = " ";

private:
    struct pollfd m_pollfd[MAX_POLL_EVENT];
    Mailbox_Read_Msg_ST m_canReadData;
    Mailbox_Write_Msg_ST m_canWriteData;
    QMap<QString, int> m_msiQRitem;
    QMutex mutex;
    QWaitCondition cond;
    QString m_readDIDInfo;
    QTimer *m_pTestItemTimer;
    bool m_can_init_status;
    int m_mailbox_readfd;
    int m_mailbox_writefd;
    int m_curTestItemIndex = 0;
    int m_readDIDLen;

    Timer* p_ftimer;
};

class MainWindow : public QQuickView
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();
    void init();
    void init_db();
    void initDatabase(QString filePath);
    void deinitDatabase();
    void insertData(QString iccid, QString rootKey, QString sim);
    void updateFlagByIccid(QString iccid, QString flag);
    void updateOtherByIccid(QString iccid, QString model,QString data);
    void readDataFile(QString filePath);
    QString getData(QString iccid,QString data);
    Q_INVOKABLE void update_db_flag(bool flag);
    /*********************************************/
    void insertData(const QString iccid, const QString imei);
    void updateOtherByImei(QString imei, QString model,QString data);
    QString getDataByIMEI(QString imei,QString data);
    bool findData(const QString iccid, const QString imei);

public slots:
    void onConnectServer();
    void test(int msgID, int param);

public:
    ComQtYeedonCanInterface* can_dbus_interface;
    monitorusb * mon1;
    monitorrndis * mon2;
    QTimer *m_pConnectServerTime;
    FortuneThread* thread_m = NULL;
    ComTiotDbusHardkeyInterface* m_harkey=NULL;
    encode * in = NULL;
    QString  m_rootKey;
    QString m_sQRitem;
    QString m_sProName;
    QString m_sSIMnumber;
    QString m_sSerialShow;
    bool m_bSIM;
    
private:
    sqlite3 *m_pdb;
    QString m_sDBTerm;
    QByteArray m_dbName;
    QMap<QString, int> m_msiDBTerm;
    bool m_bOpenDB;
    int m_iCanCfg; //0 标准帧，500k, 1 标准帧 250k, 2 扩展帧 500k, 3 扩展帧 250k
};

extern MainWindow* mainwindow;
extern FortuneThread* thread_m;
#endif // MAINWINDOW_H
