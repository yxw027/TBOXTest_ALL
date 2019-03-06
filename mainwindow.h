#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include "sim800_interface.h"
#include "bt_interface.h"
#include <QMediaPlayer>
#include <QFile>
#include <QTextCodec>
#include <sqlite3.h>
#define SQLITE_DATABASE_ONE     "/run/media/usb/"
#define TABLE_NAME          "TBoxData"
#include "hardkeymonitorinterface_interface.h"
//LiberationMono-Regular.ttf
//LiberationSerif-Regular.ttf
//LiberationSans-Regular.ttf
//
#define FONT_PATH "/usr/lib/fonts/MicroVistaHei.ttf"
//#define FONT_NAME "WenQuanYi Micro Hei"
#define FONT_NAME "MicroVistaHei"

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

#ifndef UPDATE//系统升级
    #define UPDATE 01
#elif
    #define UPDATE
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
    void readDisk();
    //void readDiskIMEI();
    void getInfo(QString hostName, quint16 port);
    void run() Q_DECL_OVERRIDE;
    Q_INVOKABLE void handleSetFile();
    Q_INVOKABLE void handleCan();
    Q_INVOKABLE void handleCanAwake();
    Q_INVOKABLE void handle6AxisSensor();
    Q_INVOKABLE void handleEMMC();
    Q_INVOKABLE void handleCharge();
    Q_INVOKABLE void handleWIFI();
    Q_INVOKABLE void handleBtCom();
    Q_INVOKABLE void handleNFC();
    Q_INVOKABLE void handleIVI();
    Q_INVOKABLE void handleIVIT();
    //Q_INVOKABLE void handleLoginSever();
    Q_INVOKABLE void handleAirBag();
    Q_INVOKABLE void handleGPSOpen();
    //Q_INVOKABLE void handleGPShort();
    Q_INVOKABLE void handleGPSSignal();
    Q_INVOKABLE void handleMajorPower();
    //Q_INVOKABLE void handleMinorPower();
    Q_INVOKABLE void handleACCOFF();
    Q_INVOKABLE void restart();
    Q_INVOKABLE void stop_flag();
    Q_INVOKABLE void thread_eixt();
    Q_INVOKABLE void change_serial();
    Q_INVOKABLE void change_serialCY();
    void handleBt(bool state);
    int checkGPIO(int port, bool flag);
    void handleLockCar();
    void handleUnlockCar();
    void handleCarDoor();
    void excutePopen(char* scr, char* dst, int size_n);
    void handleCarLamp();
    bool detect_dark_current();
    bool detect_dark_current_read();
    bool set_gpio_val( int num, bool dir,int value );
    //void handle_cfg_mode();
    //void handle_cfg_modeIMEI();
    void handle_cfg_modeNew();
    //void tag_pack( uint8_t cmd, uint8_t tag, uint16_t tlvLen);
    //void tag_packIMEI( uint8_t cmd, uint8_t tag, uint16_t tlvLen);
    void tag_packNew( uint8_t cmd, uint8_t tag, uint16_t tlvLen );
    void handleqrCode();
    void handleqrCodeIMEI();
    Q_INVOKABLE void chang_stop_flag();
    Q_INVOKABLE void disable_12V();
    QPixmap generateQRcode(QString tempstr);
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
    Q_INVOKABLE void sendMsg(uint16_t msgBodyLen, uint8_t cmd, uint8_t tag, uint16_t tlvLen);
    //void setTestname(QString testName) { this->testname = testName; emit testnameChanged(); }
    void initListView();
    void iniTableViewByCarinfo();
    void iniTableViewByqr();
    Q_INVOKABLE void init();
    Q_INVOKABLE void clear_socket();

signals:
    void errorCode(QString functionName, int param);
    void qrcode();
    void gpsBarData(QVariant num, QVariant strengthNum);
    void gps_start_num(QString num);
    void nextOne();
    void time_start(QString testname);
    void time_stop();
    void msg(QByteArray msg);
    void testnameChanged();
    void device_disconnect();
    void udisk_disconnect();
    void power_signal(double power, bool val);
    void pwm_start();
    void pwm_stop();
    void signal_strength(int strength);
    void update_iccid();
    void update_sn();
    void show_main_page();
    void show_wifi();
    void m_hardkey(int msgID);
    void mcuVersion(QString mcu_buf);
    void appVersion(QString app_buf);
    void osVersion(QString os_buf);
    void sysVersion(QString sys_buf);
    void setTitleText(QString tText);
    //void ring_pickdown();
#ifdef UPDATE
    void upgrade(QString text);
#endif

public slots:
    void on_start_thread();
    void test();
    void read_data();
    void onSigBleDevName(QString name);//
    void onSigSwitchStatus(bool status);
    
public:
    QTcpSocket* socket_m;
    FileListItemModel* listModel;
    FileListItemModel* tableModel;
    FileListItemModel* tableMode2;
    FileListItemModel* tableModelQR;
    setFile setfile_m;
    int test_len;
    char buf[256];
    int offset = 0;
    char readMsg[256];
    bool stop;
    int can_flag[4]={0};
    bool write_flag;
    QString list1;
    QString list2;
    uint8_t sig_strength;
    bool db_init_flag;
    QString tBoxSN1;
    QString tBoxSN2;
    QString tBoxSN3;
    bool m_bt_flag;
    char hw[16]={0};
    ComQtYeedonBtInterface* m_btInterface;
    QSettings* setting;
    QString  m_serial;
    QString phone_number;
    bool change_sn;
    bool sos_flag;
    bool lock_flag;
    bool unlock_flag;
    bool bt_flag;
    QString m_power;
    QString btName;
    
    QString m_imei;
    char imei[24]={0};
    QString hwIMEI;
    QString m_sProductModel;
    QString m_sProductNumber;

private:
    QByteArray qrcodeStr = " ";
    QString qrcodeStr_m;
    QString hostName;
    quint16 port; 
    QMutex mutex;
    QWaitCondition cond;
    bool quit;
    bool read;
    QString vehicle;
    QString sk;
    QString m_vpn;
    int m_acc;
    bool m_bA5;
    bool m_bTB;
    bool analyze_section_data();
    QVector<QString> m_vsTestName;
    QString m_checkItem;
    QMap<QString, int> m_msiQRitem;
    QString m_sProductName;
};

class MainWindow : public QQuickView
{
    Q_OBJECT
    //Q_PROPERTY
public:
    explicit MainWindow();
    ~MainWindow();
    void initDatabase(QString filePath);
    void deinitDatabase();
    void insertData(QString iccid, QString rootKey, QString sim);
    //void insertData(QString iccid, QString imei, QString imsi, QString sn, QString swversion, QString hwversion, QString rootKey, QString sim, QString productModel, int flag, QString project);
    void updateFlagByIccid(QString iccid, QString flag);
    void updateOtherByIccid(QString iccid, QString model,QString data);
    void readDataFile(QString filePath);
    QString getData(QString iccid,QString data);
    static void *initHotPlugThread(void *args);
    int initHotPlugSocket();
    Q_INVOKABLE void setAudioPlayState();
    Q_INVOKABLE void update_db_flag(bool flag);
    void init_db();
    /*********************************************/
    void insertData(const QString iccid, const QString imei);
    //void insertData(QString imei, QString sn, QString swversion, QString hwversion, QString productModel, QString flag);
    void updateOtherByImei(QString imei, QString model,QString data);
    QString getDataByIMEI(QString imei,QString data);
    bool findData(const QString iccid, const QString imei);
    
private:
    //bool checkTermExist(const QString term);
    //void getDBTerm();

signals:
    void start_thread();
    void sigLoadLocalFileListWithOutUSBInform();
    void sigPlayListClear();
    void sigSearchMediaFileTimer();
    void plug_in_udisk();
    void plug_in_device();
    void sigPlayAudio(QString filePath);
    void sigBroadcastRing();

public slots:
    void init();
    void onSigBroadcastRing();
    void onbroadTest(int value);
    void on_update_iccid();
    void on_update_sn();
    void onConnectServer();
    void test(int msgID, int param);

public:
    ComQtYeedonCanInterface* can_dbus_interface;
    ComQtYeedonCallInterface* m_pCallInterface;
    bool m_playFinished = false;
    monitorusb * mon1;
    monitorrndis * mon2;
    QTimer *m_pConnectServerTime;
    QTimer *m_pInitTimer;
    FortuneThread* thread_m = NULL;
    ComTiotDbusHardkeyInterface* m_harkey=NULL;
    encode * in = NULL;
    QString  m_rootKey;
    int ring_num;
    bool m_bSIM;
    bool m_bRootkey;
    QString m_sQRitem;
    QString m_sProName;
    QString m_sSIMnumber;
    QString m_sSerialShow;
    
private:
    int m_hotplug_sd;
    bool m_usbPullout;
    sqlite3 *m_pdb;   //need memory?
    QString m_sDBTerm;
    QByteArray m_dbName;
    QMap<QString, int> m_msiDBTerm;
    bool m_bOpenDB;
};

extern MainWindow* mainwindow;
extern FortuneThread* thread_m;
#endif // MAINWINDOW_H
