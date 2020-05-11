#include "mainwindow.h"
#include <share.h>
#include <qiterator.h>
#include "common.h"
#include <map>
#include <pthread.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/time.h>
#include <string>
#include <assert.h>
#include <sstream>
//#include "receive/canservice.h"


using namespace std;

int strTestItemHexFlag[] =
{
    TEST_CAN_MODULE,
    DID_HW_VERSION,
    DID_SW_VERSION,
    TEST_WATCHDOG_MODULE,
    TEST_6AXIS_MODULE,          //4
    TEST_ETHERNET_MODULE,
    TEST_WIFI_MODULE,
    TEST_4GUART_MODULE,
    TEST_4GIOT_MODULE,          //8
    TEST_4GWAKE_MODULE,
    TEST_GPS_MODULE,
    TEST_MIC_MODULE,
    TEST_SYATEM_SLEEP_MODULE,   //12
    TEST_V2X_MODULE,
    TEST_USB_MODULE,
    TEST_PWR_MODULE,
    TEST_SPK_MODULE,            //16
    TEST_RS232_MODULE,
    TEST_GPIO_MODULE,
    TEST_ADC_MODULE,
    TEST_VIN_WRITE,             //20
    TEST_PD_TIME_WRITE,
    TEST_QR_SHOW
    //reserved2
    //reserved3
    
};

#define COUNT_CHECK 26
#define TJ "GV1350"
#define CJ "DP9680"
#define CY "GG1660"

bool stop_monitorusb = false;
char str_iccid[21]={0};
QString str_imsi="";
bool remove_flag = false;
char software_version[15]={0};

monitorusb::monitorusb()
{
    udev = udev_new();
    if (!udev)
    {
        DEBUG_CHAR("udev_new fail");
    }
    mon = udev_monitor_new_from_netlink(udev, "udev");
    udev_monitor_filter_add_match_subsystem_devtype(mon, "usb", NULL);
    udev_monitor_enable_receiving(mon);
    fd = udev_monitor_get_fd(mon);
    enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "usb");
    udev_enumerate_scan_devices(enumerate);
    devices = udev_enumerate_get_list_entry(enumerate);
    udev_list_entry_foreach(dev_list_entry, devices);
    {
        const char *path;
        path = udev_list_entry_get_name(dev_list_entry);
        dev = udev_device_new_from_syspath(udev, path);
        dev = udev_device_get_parent_with_subsystem_devtype(dev, "usb", "usb_device");
        if (!dev)
        {
            DEBUG_CHAR("Unable to find parent usb device.");
            fflush(stdout);
            //emit mainwindow->thread_m->udisk_disconnect();
            //exit(1);
        }
        udev_device_unref(dev);
    }
    udev_enumerate_unref(enumerate);
}

void monitorusb::run()
{
    char buf[10];
    char buf_devpath[50];
    fd_set fds;
    struct timeval tv;
    int ret;
    sleep(10);
    while (true)
    {
        if(stop_monitorusb)
        {
            break;
        }
        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        ret = select(fd+1, &fds, NULL, NULL, &tv);
        if (ret > 0 && FD_ISSET(fd, &fds))
        {
            dev = udev_monitor_receive_device(mon);
            if (dev)
            {
                strcpy(buf_devpath, udev_device_get_devpath(dev));
                strcpy(buf, udev_device_get_action(dev));
                fflush(stdout);
                QString str = buf;
                DEBUG_PARAM("str:", str);
                QString str_type = buf_devpath;
                DEBUG_PARAM("str_type:", str_type);
                if(str.contains("remove"))
                {
                    if(str_type.contains("usb2"))
                    {
                        remove_flag = true;
                        DEBUG_PARAM("remove_flag:", remove_flag);
                        emit mainwindow->thread_m->device_disconnect();
                        this->quit();
                    }
                    else if (str_type.contains("usb1"))
                    {
                        DEBUGLOG;
                        emit mainwindow->thread_m->udisk_disconnect();
                        this->quit();
                    }
                }
                printf("   Action: %s\n", udev_device_get_action(dev));
                fflush(stdout);
                udev_device_unref(dev);
            }
            else
            {
                DEBUGLOG;
                printf("No Device from receive_device(). An error occured.\n");
                fflush(stdout);
                emit mainwindow->thread_m->udisk_disconnect();
                exit(1);
            }
        }
        msleep(200);
        fflush(stdout);
    }
    udev_unref(udev);
}

FortuneThread::FortuneThread(): QQuickImageProvider(QQuickImageProvider::Pixmap)
{
    //    qrcodeStr.clear();
    //    qrcodeStr.append("产品名称:GP9710\r\n");
    //    qrcodeStr.append("产品型号:CN\r\n");
    //    qrcodeStr.append("软件版本号:v1.0.1\r\n");
    //    qrcodeStr.append("硬件版本号:v1.0.2\r\n");
    //    qrcodeStr.append("IP地址:192.168.1.123\r\n");
    //    qrcodeStr.append("生产日期:2020-4-21\r\n");
    //    qrcodeStr.append("WIFI名称:chanry\r\n");
    //    qrcodeStr.append("VIN码:0000000000.000000\r\n");
    
    m_sim_number = "";
    m_imei = "";
    m_imsi = "";
    m_iccid = "";
    m_sn = "";
    m_pn = "";
    reserved1 = "";
    reserved2 = "";
    m_readDIDInfo = "";
    m_productName = "";
    m_productType = "";
    m_sw_version = "";
    m_hw_version = "";
    m_v2x_version = "";
    m_hp_version = "";
    m_app_version = "";
    m_vinCode = "";
    m_productDate = "";
    m_suplayerCode = "";
    m_ipAddr = "";
    m_wifiName = "";
    m_can_init_status = false;
    m_readDIDLen = 0;
    m_curTestItemIndex = 0;
    m_mailbox_readfd = -1;
    m_mailbox_writefd = -1;
    m_canWriteData.hlc = 0;
    m_canWriteData.dlc = 12;
    m_canWriteData.canId = 0x02F3;
    memset(m_canWriteData.header,0,sizeof(m_canWriteData.header));
    //FIXME: QTimer ERROR
    //    m_pTestItemTimer = new QTimer;
    //    connect( m_pTestItemTimer,SIGNAL(timeout()), this, SLOT(onTestItemTimeout()));
    connect(this,SIGNAL(sigQrGroup()), this, SLOT(onSigQrGroup()));
}

FortuneThread::~FortuneThread()
{
    mutex.lock();
    cond.wakeOne();
    mutex.unlock();
    wait();
}

void FortuneThread::iniTableViewByCarinfo()
{
    DEBUGLOG;
    int i;
    QString str[] = { "车型号", "IMSI", "ICCID", "SIM", "IMEI", "序列号", "硬件版本号", "软件版本号"};
    for(i=0; i<4; i++)
    {
        FileListItem item(str[i], "XXXXXXXXXX", i);
        tableModel->addFileListItem(item);
    }
    for(i=4; i<8; i++)
    {
        FileListItem item(str[i], "XXXXXXXXXX", i);
        tableMode2->addFileListItem(item);
    }
}

void FortuneThread::initTestListView()// test item list
{
    DEBUGLOG;
    int tempHex;
    int serial = 1;
    QString strTestItem;
    QString strTestItemHex;
    QString strTestItemName;
    FileListItem item;
    listModel->clear();
    
    if(access("/run/media/usb/1.ini", 0) == 0 )
    {
        DEBUG_CHAR("1.ini file exist!!!");

        //read ini DBTerm
        setting = new QSettings(QString::fromStdString("/run/media/usb/1.ini"), QSettings::IniFormat);
        setting->setIniCodec("UTF-8");
        m_testItemConfig  = setting->value("DBTerm/value").toString();
        m_testItemConfig  = QString("%1").arg(m_testItemConfig.toInt(Q_NULLPTR,16),4*m_testItemConfig.length(),2,QLatin1Char('0'));

#if DEBUG
        printf("[chen]m_testItemConfig:");
        for(int j=0;j<m_testItemConfig.length();j++)
        {
            printf("%d ",m_testItemConfig.at(j).digitValue());
        }
        printf(" end data:%s ---- len:%d\r\n",m_testItemConfig.toLatin1().data(),m_testItemConfig.length());
        printf("\r\n");
#endif

        //parse DBTerm to view
        m_MapTestItemFlag.clear();
        for(int i=0;i<sizeof(strTestItemHexFlag)/sizeof(strTestItemHexFlag[0]);i++)
        {
            printf("strTestItemHexFlag: %4x\n", strTestItemHexFlag[i]);
            
            DEBUG_PARAM("m_testItemConfig ",m_testItemConfig.at(i).digitValue());
            
            m_MapTestItemFlag.insert(strTestItemHexFlag[i],m_testItemConfig.at(i).digitValue());
        }

        //bind step to view
        item = FileListItem("开始测试", "0000", 0);
        listModel->addFileListItem(item);

        for(int i=1; i<= TEST_MAX_ITEM; i++)
        {
            strTestItem = QString("TestStep%1/value").arg(i);
            strTestItemHex = setting->value(strTestItem).toString();
            printf("strTestItemHex:%4x\n", strTestItemHex.toInt(Q_NULLPTR,16));
            
            if(0 == strTestItemHex.length())
            {
                m_testItemCount = listModel->rowCount();
                printf("m_testItemCount: %d\n", m_testItemCount);
                break;
            }
            
            tempHex = strTestItemHex.toInt(Q_NULLPTR,16);
            if(m_MapTestItemFlag.find(tempHex).value() == 1)
            {
                strTestItemName = getNameForIndex(serial, tempHex);
                DEBUG_PARAM("strTestItemName:", strTestItemName);
                
                item = FileListItem(strTestItemName,strTestItemHex,serial);
                listModel->addFileListItem(item);
                serial++;
            }
        }
        item = FileListItem("", "0000", m_testItemCount);
        listModel->addFileListItem(item);
        item = FileListItem("", "0000", m_testItemCount+1);
        listModel->addFileListItem(item);
        
        //TUC/VPM
        m_qrShowFlag    = m_MapTestItemFlag.find(TEST_QR_SHOW).value();
        m_qrShowConfig  = setting->value("QRcode/value").toString();
        m_qrShowConfig  = QString("%1").arg(m_qrShowConfig.toInt(Q_NULLPTR,16),4*m_qrShowConfig.length(),2,QLatin1Char('0'));
        m_canidRead     = setting->value("FctyRxCanID/value").toInt();//canid
        m_canidWrite    = setting->value("FctyTxCanID/value").toInt();//canid
        m_productName   = setting->value("ProjectName/value").toString();
        m_productType   = setting->value("ProductType/value").toString();
        m_vinCode       = setting->value("F190/value").toString();
        m_productDate   = setting->value("F191/value").toString();
        m_suplayerCode  = setting->value("F170/value").toString();
        m_ipAddr        = setting->value("F180/value").toString();
        m_wifiName      = setting->value("F181/value").toString();
        printf("[chen]m_qrShowFlag:%d \r\n",m_qrShowFlag);
        printf("[chen]m_qrShowConfig:%s \r\n",m_qrShowConfig.toLatin1().data());
    }
    else
    {
        DEBUG_CHAR("1.ini file no exist!!!");
    }
}

void FortuneThread::qrcodeGroup()
{
    FileListItem item;
    
    QString strQrItemName[] =
    {
        "产品名称:","产品型号:","软件版本号:","硬件版本号:",
        "生产日期:","VIN码:","IP地址:","WIFI名称:","SIM卡号:",
        "IMEI:","IMSI:","ICCID:","SN:","P/N:","预留1:","预留2:"
    };
    
    QString strQrItemValue[] =
    {
        m_productName,m_productType,m_sw_version,m_hw_version,
        m_productDate,m_vinCode,m_ipAddr,m_wifiName,m_sim_number,
        m_imei,m_imsi,m_iccid,m_sn,m_pn,reserved1,reserved2
    };
    
    qrcodeStr.clear();
    tableModelQR->clear();
    for(int i=0;i<m_qrShowConfig.length();i++)
    {
        if(m_qrShowConfig.at(i).digitValue() == 1)
        {
            qrcodeStr.append(strQrItemName[i]);
            qrcodeStr.append(strQrItemValue[i]);
            qrcodeStr.append("\r\n");
            item = FileListItem(strQrItemName[i],strQrItemValue[i],i);
            tableModelQR->addFileListItem(item);
        }
    }
    
    emit qrcode();
}

void FortuneThread::onSigQrGroup()
{
    qrcodeGroup();
}

void FortuneThread::onTestItemTimeout()
{
    
    DEBUGLOG;
    //    m_pTestItemTimer->stop();
    
    if(m_canWriteData.cmdId == TEST_FACTORY_MODULE)
    {
        m_canWriteData.cmdId = TEST_FACTORY_MODULE;
        DEBUG_CHAR("[BEFORE]********canWriteData********");
        canWriteData(m_canWriteData);
        //        m_pTestItemTimer->start(2000);//2s
        sleep(2);
        DEBUG_CHAR("TEST_FACTORY_MODULE timeout");
    }
    else
    {
        if(m_canWriteData.cmdId == TEST_DID_READ || m_canWriteData.cmdId == TEST_DID_WRITE)
        {
            handleErrorItem(m_canWriteData.dataHeader);
        }
        else
        {
            handleErrorItem(m_canWriteData.cmdId);
        }
        
    }
    
    
}

QString FortuneThread::getNameForIndex(int index, int command)
{
    QString str = "";
    char buf[8] = {0};
    
    if(command != 0)
    {
        if(index<10)
        {
            sprintf(buf, "[0%d]", index);
        }
        else
        {
            sprintf(buf, "[%d]", index);
        }
        
        switch (command)
        {
        case TEST_FACTORY_MODULE:
            str = "进入工厂模式";
            break;
            
        case TEST_CAN_MODULE:
            str = "CAN通讯";
            break;
            
        case TEST_WATCHDOG_MODULE:
            str = "加密测试";
            break;
            
        case TEST_ETHERNET_MODULE:
            str = "以太网测试";
            break;
            
        case TEST_WIFI_MODULE:
            str = "WIFI测试";
            break;
            
        case TEST_6AXIS_MODULE:
            str = "6轴陀螺测试";
            break;
            
        case TEST_V2X_MODULE:
            str = "V2X通讯";
            break;
            
        case TEST_USB_MODULE://
            str = "USB测试";
            break;
            
        case TEST_4GUART_MODULE:
            str = "4G模块UART通信测试";
            break;
            
        case TEST_4GWAKE_MODULE:
            str = "4G休眠唤醒测试";
            break;
            
        case TEST_4GIOT_MODULE:
            str = "4G联网测试";
            break;
            
        case TEST_GPS_MODULE:
            str = "GPS信号测试";
            break;
            
        case TEST_MIC_MODULE:
            str = "MIC测试";
            break;
            
        case TEST_SPK_MODULE:
            str = "SPK测试";
            break;
            
        case TEST_SYATEM_SLEEP_MODULE:
            str = "系统点火休眠测试";
            break;
            
        case TEST_RS232_MODULE:
            str = "RS232测试";
            break;
            
        case TEST_GPIO_MODULE:
            str = "GPIO测试";
            break;
            
        case TEST_ADC_MODULE:
            str = "ADC测试";
            break;
            
        case TEST_PWR_MODULE:
            str = "B+供电控制口测试";
            break;

        case DID_HW_VERSION:
            str = "读取硬件版本";
            break;

        case DID_SW_VERSION:
            str = "读取软件版本";
            break;

        default:
            break;
        }
        
        str.push_front(buf);
        
        return str;
        
    }
    else
    {
        return "";
    }
}

void FortuneThread::init()
{
    DEBUGLOG;
}

void FortuneThread::disable_12V()
{
    stop_monitorusb = true;
    system("echo out > /sys/class/gpio/gpio6/direction");
    system("echo 0 > /sys/class/gpio/gpio6/value");
}

QPixmap FortuneThread::generateQRcode(QString tempstr)
{
    QRcode *qrcode; //二维码数据
    //QR_ECLEVEL_Q 容错等级
    char*  ch;
    QByteArray ba = tempstr.toUtf8();
    ch=ba.data();
    qrcode = QRcode_encodeString(ch, 2, QR_ECLEVEL_Q, QR_MODE_8, 1);
    qint32 temp_width= 200; //二维码图片的大小
    qint32 temp_height= 200;
    qint32 qrcode_width = qrcode->width > 0 ? qrcode->width : 1;
    double scale_x = (double)temp_width / (double)qrcode_width; //二维码图片的缩放比例
    double scale_y =(double) temp_height /(double) qrcode_width;
    QImage mainimg=QImage(temp_width,temp_height,QImage::Format_ARGB32);
    QPainter painter(&mainimg);
    QColor background(Qt::white);
    painter.setBrush(background);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, temp_width, temp_height);
    QColor foreground(Qt::black);
    painter.setBrush(foreground);
    for( qint32 y = 0; y < qrcode_width; y ++)
    {
        for(qint32 x = 0; x < qrcode_width; x++)
        {
            unsigned char b = qrcode->data[y * qrcode_width + x];
            if(b & 0x01)
            {
                QRectF r(x * scale_x, y * scale_y, scale_x, scale_y);
                painter.drawRects(&r, 1);
            }
        }
    }
    QPixmap mainmap = QPixmap::fromImage(mainimg);
    return mainmap;
}

QPixmap FortuneThread::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = 200;
    int height = 200;
    if (size)
        *size = QSize(width, height);
    QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
                   requestedSize.height() > 0 ? requestedSize.height() : height);
    pixmap = generateQRcode(qrcodeStr);
    return pixmap;
}

void FortuneThread::run()
{
    DEBUGLOG;
    int msgLen;
    int numready;
    int loop = 3;
    
    while(loop)
    {
        if(m_mailbox_writefd == -1)
        {
            m_mailbox_writefd = open(MAILBOX_PATH, O_RDWR);
        }
        
        if(m_mailbox_readfd == -1)
        {
            m_mailbox_readfd  = open(MAILBOX_PATH, O_RDONLY);
        }
        
        if(m_mailbox_writefd > 0 && m_mailbox_readfd > 0)
        {
            DEBUG_CHAR("open mailbox read and write success 17:38! \r\n");
            break;
        }
        
        loop--;
        usleep(100 * 1000);
    }
    
    m_can_init_status = (m_mailbox_writefd > 0 && m_mailbox_readfd > 0);
    
    if(m_can_init_status)
    {
        DEBUGLOG;
        m_pollfd[0].fd = m_mailbox_readfd;
        m_pollfd[0].events = (POLLIN | POLLPRI);
    }
    
    DEBUG_CHAR(" TEST_FACTORY_MODULE \r\n");
    
    m_canWriteData.cmdId = TEST_FACTORY_MODULE;
    m_canWriteData.dataHeader = 0X00;
    memset(m_canWriteData.data,0,sizeof(m_canWriteData.data));
    
    //FIXME: fpp
    //    DEBUGLOG;
    //    //fix timer
    //    m_pTestItemTimer = new QTimer;
    //    connect( m_pTestItemTimer,SIGNAL(timeout()), this, SLOT(onTestItemTimeout()));
    
    //    DEBUGLOG;
    //    m_pTestItemTimer->start(2000);//2s
    //    DEBUGLOG;
    //        Timer t;
    //    p_ftimer->StartTimer(2000, std::bind(testTimeout));
    
    //    this->exec();
    
    std::thread([this](){


        std::this_thread::sleep_for(std::chrono::seconds(2));

        if(m_canWriteData.cmdId == TEST_FACTORY_MODULE)
        {
            DEBUG_CHAR("send  TEST_FACTORY_MODULE \r\n");
            DEBUG_CHAR("[BEFORE]********canWriteData********");
            m_canWriteData.cmdId = TEST_FACTORY_MODULE;
            canWriteData(m_canWriteData);
        }
        else
        {
            if(m_canWriteData.cmdId == TEST_DID_READ || m_canWriteData.cmdId == TEST_DID_WRITE)
            {
                handleErrorItem(m_canWriteData.dataHeader);
            }
            else
            {
                handleErrorItem(m_canWriteData.cmdId);
            }

        }


    }
    
    ).detach();
    
    
    
    /*********************
    m_canWriteData.cmdId = TEST_DID_READ;
    m_canWriteData.dataHeader = 0X00;
    memset(m_canWriteData.data,0,sizeof(m_canWriteData.data));
    
    Mailbox_Read_Msg_ST t_readData;
    t_readData.canId = 0x7D0D;
    t_readData.dataHeader = DID_SW_VERSION;
    
    //1
    memset(&t_readData.data,0,sizeof(t_readData.data));
    t_readData.cmdId = 0xFE01;
    t_readData.data[0] = 0x0f;
    t_readData.data[1] = 0x44;
    t_readData.data[2] = 0x50;
    t_readData.data[3] = 0x39;
    handleCandataMessage(t_readData);
    
    //2
    memset(&t_readData.data,0,sizeof(t_readData.data));
    t_readData.cmdId = 0xFE11;
    t_readData.data[0] = 0x37;
    t_readData.data[1] = 0x31;
    t_readData.data[2] = 0x30;
    t_readData.data[3] = 0x5f;
    handleCandataMessage(t_readData);
    
    //3
    memset(&t_readData.data,0,sizeof(t_readData.data));
    t_readData.cmdId = 0xFE21;
    t_readData.data[0] = 0x30;
    t_readData.data[1] = 0x31;
    t_readData.data[2] = 0x5f;
    t_readData.data[3] = 0x56;
    handleCandataMessage(t_readData);
    
    //4
    memset(&t_readData.data,0,sizeof(t_readData.data));
    t_readData.cmdId = 0xFE31;
    t_readData.data[0] = 0x31;
    t_readData.data[1] = 0x2e;
    t_readData.data[2] = 0x30;
    t_readData.data[3] = 0x37;
    handleCandataMessage(t_readData);
    **********************/
    
    while (m_can_init_status)
    {
        /*********************
        Mailbox_Write_Msg_ST writeData;
        writeData.hlc = 0;
        writeData.dlc = 12;
        writeData.canId = 0x0202;
        writeData.cmdId = 0x0101;
        writeData.dataHeader = 0x0100;
        memset(&writeData.data,0,sizeof(writeData.data));
        memset(&writeData.header,0,sizeof(writeData.header));
        //canWriteData(writeData);
        **********************/
        
        DEBUG_CHAR("loop ~~~~~~~~\r\n");
        

        
        numready = poll(m_pollfd, MAX_POLL_EVENT, -1);
        
        DEBUG_PARAM("numready == ",numready);
        
        if ((numready == -1) && (errno == EINTR))
        {
            DEBUG_CHAR("Interrupt signal，waiting... \r\n");
            continue;
        }
        
        if(numready == -1)
        {
            DEBUG_CHAR("poll fail!!! \r\n");
            break;
        }
        else if(numready == 0)
        {
            DEBUG_CHAR("poll timeout.... \r\n");
            continue;
        }
        else
        {
            DEBUGLOG;
            if(m_pollfd[0].revents & (POLLIN|POLLPRI))
            {
                m_pollfd[0].revents=0;
                msgLen = read(m_pollfd[0].fd,&m_canReadData, sizeof(Mailbox_Read_Msg_ST));
                m_canReadData.cmdId = htons(m_canReadData.cmdId);
                m_canReadData.dataHeader = htons(m_canReadData.dataHeader);
                printf("Can Receive Data,canid:%4x--cmdid:%4x--header:%4x--len:%d\n",m_canReadData.canId,m_canReadData.cmdId,m_canReadData.dataHeader,msgLen);
                for(int i=0;i<4;i++)
                {
                    printf("%02x ",m_canReadData.data[i]);
                }
                printf("\r\n");
                handleCandataMessage(m_canReadData);
            }
        }
        
        usleep(10 * 1000);
    }
    
    if(m_mailbox_writefd > 0)
    {
        close(m_mailbox_writefd);
    }
    if(m_mailbox_readfd > 0)
    {
        close(m_mailbox_readfd);
    }
    
    
    //    exec();
}

void FortuneThread::readDID(Mailbox_Read_Msg_ST &message)
{
    QString m_tempDIDInfo;
    
    if((message.cmdId & 0xFF0F) == 0xFE01)//read ack
    {
        if(message.cmdId == 0xFE01)
        {
            m_readDIDLen = message.data[3];
            m_tempDIDInfo = QString((char*)(message.data)).mid(0,3);
            //            m_readDIDInfo.append(m_tempDIDInfo);

            m_readDIDInfo.append(m_tempDIDInfo.at(2));
            m_readDIDInfo.append(m_tempDIDInfo.at(1));
            m_readDIDInfo.append(m_tempDIDInfo.at(0));
            qDebug()<<1<< m_tempDIDInfo ;
            qDebug()<<1<< m_readDIDInfo ;

        }
        else
        {

            m_tempDIDInfo = QString((char*)(message.data)).mid(0,4);
            //            m_readDIDInfo.append(m_tempDIDInfo)

            m_readDIDInfo.append(m_tempDIDInfo.at(3));
            m_readDIDInfo.append(m_tempDIDInfo.at(2));
            m_readDIDInfo.append(m_tempDIDInfo.at(1));
            m_readDIDInfo.append(m_tempDIDInfo.at(0));

            qDebug()<<2<< m_tempDIDInfo ;
            qDebug()<<2<< m_readDIDInfo ;

        }

        DEBUG_PARAM("m_readDIDLen  ",m_readDIDLen);
        DEBUG_PARAM("m_readDIDInfo.size  ",m_readDIDInfo.size());

        if(m_readDIDLen > m_readDIDInfo.size())
        {
            return;
        }
        else
        {
            qDebug()<<3<< m_tempDIDInfo ;
            qDebug()<<3<< m_readDIDInfo ;

            DEBUG_CHAR("===============================");
            m_readDIDInfo = m_readDIDInfo.mid(0,m_readDIDLen);
            printf("m_readDIDInfo:%s\r\n",m_readDIDInfo.toLocal8Bit().data());
        }
    }
    else
    {
        return;
    }
    
    switch (message.dataHeader) {
    case DID_SW_VERSION:
        m_sw_version = m_readDIDInfo;
        printf(">>>>>DID_SW_VERSION : %s<<<<<< \n",m_sw_version.toLocal8Bit().data());
        break;
        
    case DID_HW_VERSION:
        m_hw_version = m_readDIDInfo;
        printf(">>>>>DID_HW_VERSION : %s<<<<<< \n",m_hw_version.toLocal8Bit().data());
        break;
        
    case DID_V2X_VERSION:
        m_v2x_version = m_readDIDInfo;
        printf(">>>>>DID_V2X_VERSION : %s<<<<<< \n",m_v2x_version.toLocal8Bit().data());
        break;
        
    case DID_HP_VERSION:
        m_hp_version = m_readDIDInfo;
        printf(">>>>>DID_HP_VERSION : %s<<<<<< \n",m_hp_version.toLocal8Bit().data());
        break;
        
    case DID_APP_VERSION:
        m_app_version = m_readDIDInfo;
        printf(">>>>>DID_APP_VERSION : %s<<<<<< \n",m_app_version.toLocal8Bit().data());
        break;
        
    default:
        break;
    }
    
    DEBUG_PARAM("m_readDIDLen  ",m_readDIDLen);
    DEBUG_PARAM("m_readDIDInfo.size  ",m_readDIDInfo.size());

    DEBUGLOG;
    if(m_readDIDLen <= m_readDIDInfo.size()){
        DEBUGLOG;


        qDebug()<<tableMode2->getFilePathByIndex(4);
        qDebug()<<tableMode2->getFilePathByIndex(5);
        qDebug()<<tableMode2->getFilePathByIndex(6);
        qDebug()<<tableMode2->getFilePathByIndex(7);

        qDebug()<<tableMode2->getFileNameByIndex(4);
        qDebug()<<tableMode2->getFileNameByIndex(5);
        qDebug()<<tableMode2->getFileNameByIndex(6);
        qDebug()<<tableMode2->getFileNameByIndex(7);

        tableMode2->setFileNamebyIndex(7, m_readDIDInfo);

        qDebug()<<"after -- " << tableMode2->getFilePathByIndex(7);

        startNextTestItem();

        m_readDIDLen = 0;
        m_readDIDInfo = "";
    }
}

void FortuneThread::handleCandataMessage(Mailbox_Read_Msg_ST &message)
{
    DEBUGLOG;
    uint16_t m_tempCmdId = message.cmdId & 0xFF0F;
    
    if(m_canWriteData.cmdId != m_tempCmdId)
    {
        printf("invalid cmdid:%4x! ---writeid:%4x\r\n",message.cmdId,m_canWriteData.cmdId);
        return;
    }
    
    switch (m_tempCmdId) {
    case TEST_FACTORY_MODULE:
    {
        DEBUG_CHAR("rec TEST_FACTORY_MODULE ack! \r\n");
        DEBUGLOG;
        if(message.dataHeader > 0)
        {
            //            m_pTestItemTimer->stop();
            int hwVerReadFlag = m_MapTestItemFlag.find(DID_SW_VERSION).value();
            int swVerReadFlag = m_MapTestItemFlag.find(DID_HW_VERSION).value();
            
            DEBUG_PARAM("hwVerReadFlag ",hwVerReadFlag);
            DEBUG_PARAM("swVerReadFlag ",swVerReadFlag);
            
            if(hwVerReadFlag > 1 || swVerReadFlag > 1)
            {
                DEBUGLOG;
                m_canWriteData.cmdId = TEST_DID_READ;
                if(swVerReadFlag > 1)
                {
                    m_canWriteData.dataHeader = DID_SW_VERSION;
                    DEBUG_CHAR("[BEFORE]********canWriteData********");
                    canWriteData(m_canWriteData);
                }
                if(hwVerReadFlag > 1)
                {
                    m_canWriteData.dataHeader = DID_HW_VERSION;
                    DEBUG_CHAR("[BEFORE]********canWriteData********");
                    canWriteData(m_canWriteData);
                }
            }
            else
            {
                DEBUGLOG;
                startNextTestItem();
            }
        }
        else
        {
            DEBUGLOG;
            handleErrorItem(ErrorFactory);
        }
    }
        break;
    case TEST_DID_READ:
    {
        DEBUG_CHAR("rec TEST_DID_READ ack! \r\n");
        readDID(message);
    }
        break;
    case TEST_CAN_MODULE:
        DEBUG_CHAR("rec TEST_CAN_MODULE ack! \r\n");
        handleTestItemAck(message.dataHeader,m_tempCmdId);
        break;
    case TEST_WATCHDOG_MODULE:
        DEBUG_CHAR("rec TEST_WATCHDOG_MODULE ack! \r\n");
        handleTestItemAck(message.dataHeader,m_tempCmdId);
        break;
    case TEST_ETHERNET_MODULE:
        DEBUG_CHAR("rec TEST_ETHERNET_MODULE ack! \r\n");
        handleTestItemAck(message.dataHeader,m_tempCmdId);
        break;
    case TEST_WIFI_MODULE:
        DEBUG_CHAR("rec TEST_WIFI_MODULE ack! \r\n");
        handleTestItemAck(message.dataHeader,m_tempCmdId);
        break;
    case TEST_6AXIS_MODULE:
        DEBUG_CHAR("rec TEST_6AXIS_MODULE ack! \r\n");
        handleTestItemAck(message.dataHeader,m_tempCmdId);
        break;
    case TEST_V2X_MODULE:
        DEBUG_CHAR("rec TEST_V2X_MODULE ack! \r\n");
        handleTestItemAck(message.dataHeader,m_tempCmdId);
        break;
    case TEST_USB_MODULE:
        DEBUG_CHAR("rec TEST_USB_MODULE ack! \r\n");
        handleTestItemAck(message.dataHeader,m_tempCmdId);
        break;
    case TEST_4GUART_MODULE:
        DEBUG_CHAR("rec TEST_4GUART_MODULE ack! \r\n");
        handleTestItemAck(message.dataHeader,m_tempCmdId);
        break;
    case TEST_4GWAKE_MODULE:
        DEBUG_CHAR("rec TEST_4GWAKE_MODULE ack! \r\n");
        handleTestItemAck(message.dataHeader,m_tempCmdId);
        break;
    case TEST_4GIOT_MODULE:
        DEBUG_CHAR("rec TEST_4GIOT_MODULE ack! \r\n");
        handleTestItemAck(message.dataHeader,m_tempCmdId);
        break;
    case TEST_GPS_MODULE:
        DEBUG_CHAR("rec TEST_GPS_MODULE ack! \r\n");
        handleTestItemAck(message.dataHeader,m_tempCmdId);
        break;
    case TEST_SYATEM_SLEEP_MODULE:
        DEBUG_CHAR("rec TEST_SYATEM_SLEEP_MODULE ack! \r\n");
        handleTestItemAck(message.dataHeader,m_tempCmdId);
        break;
    case TEST_PWR_MODULE:
        DEBUG_CHAR("rec TEST_PWR_MODULE ack! \r\n");
        handleTestItemAck(message.dataHeader,m_tempCmdId);
        break;
    case TEST_MIC_MODULE:
        DEBUG_CHAR("rec TEST_MIC_MODULE ack! \r\n");
        handleTestItemAck(message.dataHeader,m_tempCmdId);
        break;
    case TEST_SPK_MODULE:
        DEBUG_CHAR("rec TEST_SPK_MODULE ack! \r\n");
        handleTestItemAck(message.dataHeader,m_tempCmdId);
        break;
    case TEST_RS232_MODULE:
        DEBUG_CHAR("rec TEST_RS232_MODULE ack! \r\n");
        handleTestItemAck(message.dataHeader,m_tempCmdId);
        break;
    case TEST_GPIO_MODULE:
        DEBUG_CHAR("rec TEST_GPIO_MODULE ack! \r\n");
        handleTestItemAck(message.dataHeader,m_tempCmdId);
        break;
    case TEST_ADC_MODULE:
        DEBUG_CHAR("rec TEST_ADC_MODULE ack! \r\n");
        handleTestItemAck(message.dataHeader,m_tempCmdId);
        break;
    case TEST_DID_WRITE:
    {
        if(message.dataHeader > 0)
        {
            handleQrcode();
        }
        else
        {
            handleErrorItem(message.dataHeader);
        }
        DEBUG_CHAR("rec TEST_VIN_WRITE ack! \r\n");
    }
        break;
    default:
        break;
    }

    DEBUG_PARAM("m_tempCmdId  ",m_tempCmdId);
    DEBUG_PARAM("message.cmdId  ",message.cmdId);

    /********
    if(m_tempCmdId != TEST_FACTORY_MODULE &&
            m_tempCmdId != TEST_DID_WRITE &&
            m_tempCmdId != TEST_DID_READ &&
            message.cmdId >= 0xFC01 &&
            message.dataHeader > 0)
    {
        DEBUGLOG;
        DEBUG_CHAR("[BEFORE]********canWriteData********");
        canWriteData(m_canWriteData);
    }

    */
}

void FortuneThread::handleTestItemAck(uint16_t result,uint16_t cmdid)
{

    DEBUGLOG;
    if(result > 0)
    {
        if(confirmTestResult(cmdid) == 1)
        {
            DEBUGLOG;
            startNextTestItem();
        }
        else
        {
            handleErrorItem(cmdid);//20200428
        }
    }
    else
    {
        handleErrorItem(cmdid);
    }
}

int  FortuneThread::confirmTestResult(uint16_t cmdid)
{
    int ret = 0;
    
    switch (cmdid) {
    case TEST_GPIO_MODULE:
        break;
        
    case TEST_RS232_MODULE:
        ret = 1;
        break;
        
    case TEST_ADC_MODULE:
        break;

    default:
        ret = 1;
        break;
    }
    
    return ret;
}

void FortuneThread::testTimeout()
{
    qDebug()<< "testTimeout ...  \r\n";
    
}

void FortuneThread::startNextTestItem()
{
    emit nextOne();
    m_curTestItemIndex++;
    if(m_curTestItemIndex != listModel->rowCount()-1)
    {
        DEBUGLOG;
        m_canWriteData.cmdId = listModel->getFileNameByIndex(m_curTestItemIndex).toInt(Q_NULLPTR,16);
        
        switch (m_canWriteData.cmdId) {
        case DID_SW_VERSION:
            m_canWriteData.cmdId = TEST_DID_READ;
            m_canWriteData.dataHeader = DID_SW_VERSION;
            break;
        case DID_HW_VERSION:
            m_canWriteData.cmdId = TEST_DID_READ;
            m_canWriteData.dataHeader = DID_HW_VERSION;
            break;
        default:
            break;
        }
        DEBUG_CHAR("[BEFORE]********canWriteData********");
        canWriteData(m_canWriteData);
    }
    else
    {
        DEBUGLOG;
        m_canWriteData.cmdId = TEST_DID_WRITE;
        int vinFlag = m_MapTestItemFlag.find(TEST_VIN_WRITE).value();
        int pdateFlag = m_MapTestItemFlag.find(TEST_PD_TIME_WRITE).value();
        bool bret = (vinFlag > 0 || pdateFlag > 0);
        if(bret)
        {
            if(vinFlag > 0)
            {
                writeDID(TEST_DID_WRITE,DID_VIN);
            }
            if(pdateFlag > 0)
            {
                writeDID(TEST_DID_WRITE,DID_PRODUCED_DATE);
            }
        }
        else
        {
            handleQrcode();
        }
    }
}

void FortuneThread::handleErrorItem(int curItem)
{
    int errorNumber;
    QString errorName;
    
    switch(curItem)
    {
    case TEST_CAN_MODULE:
        errorName = "CAN通讯";
        errorNumber = ErrorCodeCan;
        break;
        
    case TEST_FACTORY_CHECK:
        errorName = "进入工厂模式";
        errorNumber = ErrorCodeSecret;
        break;
        
    case TEST_WATCHDOG_MODULE:
        errorName = "加密模块";
        errorNumber = ErrorCodeSecret;
        break;
        
    case TEST_ETHERNET_MODULE:
        errorName = "以太网模块";
        errorNumber = ErrorCodeIVI;
        break;
        
    case TEST_WIFI_MODULE:
        errorName = "WIFI模块";
        errorNumber = ErrorCodeWIFI;
        break;
        
    case TEST_6AXIS_MODULE:
        errorName = "陀螺模块";
        errorNumber = ErrorCodeSixAxisSensor;
        break;
        
    case TEST_V2X_MODULE:
        errorName = "V2X模块";
        errorNumber = ErrorCodeV2XCommunicate;
        break;
        
    case TEST_USB_MODULE:
        errorName = "USB模块";
        errorNumber = ErrorCodeUSBRW;
        break;
        
    case TEST_4GUART_MODULE:
        errorName = "4G串口模块";
        errorNumber = ErrorCodeM34GCommunicate;
        break;
        
    case TEST_4GWAKE_MODULE:
        errorName = "4G唤醒模块";
        errorNumber = ErrorCodeGPIO;
        break;
        
    case TEST_4GIOT_MODULE:
        errorName = "4G联网模块";
        errorNumber = ErrorCode4GTest;
        break;
        
    case TEST_GPS_MODULE:
        errorName = "GPS模块";
        errorNumber = ErrorCodeGPS;
        break;
        
    case TEST_MIC_MODULE:
        errorName = "MIC模块";
        errorNumber = ErrorCodeMIC;
        break;
        
    case DID_SW_VERSION:
        errorName = "软件版本";
        errorNumber = ErrorCodeSoftWare;
        break;
        
    case DID_HW_VERSION:
        errorName = "硬件版本";
        errorNumber = ErrorCodeHardWare;
        break;
        
    case DID_V2X_VERSION:
        errorName = "V2X版本";
        errorNumber = ErrorCodeV2XVersion;
        break;
        
    case DID_HP_VERSION:
        errorName = "高精度版本";
        errorNumber = ErrorCodeHighAccuracyVersion;
        break;
        
    case DID_APP_VERSION:
        errorName = "APP版本";
        errorNumber = ErrorCodeAPPVersion;
        break;
        
    case DID_VIN:
        errorName = "VIN码写入";
        errorNumber = ErrorCodeVINCode;
        break;
        
    case DID_PRODUCED_DATE:
        errorName = "生产日期写入";
        errorNumber = ErrorCodeDate;
        break;
        
    case DID_SUPPLIER:
        errorName = "供应商编码";
        errorNumber = ErrorCodeSupplayNumber;
        break;
        
    case DID_IP_ADDR:
        errorName = "IP地址";
        errorNumber = ErrorCodeIPAdress;
        break;
        
    case DID_WIFI_AP_NAME:
        errorName = "WIFI名称写入";
        errorNumber = ErrorCodeWIFIName;
        break;

    case TEST_RS232_MODULE:
        errorName = "RS232通讯";
        errorNumber = ErrorCodeRS232;
        break;

    default:
        break;
    }
    
    emit errorCode(errorName,errorNumber);
}

void FortuneThread::handleQrcode()
{
    if(m_qrShowFlag == 1)
    {
        emit sigQrGroup();
        printf("[chen]****** want to show QR code******\n");
    }
    else
    {
        printf("[chen]****** don't want to show QR code******\n");
    }
}

void FortuneThread::writeDID(Test_Mode_EN cmdId,PROJECT_INFO_EN infoType)
{
    DEBUG_CHAR("===================writeDID=================== \r\n");
    string data;
    int m_dataLen;
    int t_dataLen;
    int frame = 1;
    
    switch (infoType) {
    case DID_VIN:
        data = m_vinCode.toStdString();
        t_dataLen = m_dataLen = m_vinCode.size();
        break;
        
    case DID_PRODUCED_DATE:
        data = m_productDate.toStdString();
        t_dataLen = m_dataLen = m_productDate.size();
        break;
        
    case DID_SUPPLIER:
        data = m_suplayerCode.toStdString();
        t_dataLen = m_dataLen = m_suplayerCode.size();
        break;
        
    case DID_IP_ADDR:
        data = m_ipAddr.toStdString();
        t_dataLen = m_dataLen = m_ipAddr.size();
        break;
        
    case DID_WIFI_AP_NAME:
        data = m_wifiName.toStdString();
        t_dataLen = m_dataLen = m_wifiName.size();
        break;
    default:
        break;
    }
    
    while (t_dataLen>0)
    {
        if(frame == 1)
        {
            if(t_dataLen <= 3)
            {
                t_dataLen = 0;
            }
            else{
                t_dataLen -= 3;
            }
            
            m_canWriteData.dataHeader = infoType;
            m_canWriteData.data[0] = m_dataLen;
            memcpy(m_canWriteData.data+1,data.substr(0,m_dataLen-t_dataLen).c_str(),m_dataLen-t_dataLen);
        }
        else
        {
            if(t_dataLen <= 4)
            {
                memcpy(m_canWriteData.data,data.substr(3+(frame-2)*4,t_dataLen).c_str(),t_dataLen);
                t_dataLen = 0;
            }
            else{
                t_dataLen -= 4;
                memcpy(m_canWriteData.data,data.substr(3+(frame-2)*4,4).c_str(),4);
            }
        }
        m_canWriteData.cmdId = (cmdId & 0xFF00) | frame;
        DEBUGLOG;
        DEBUG_CHAR("[BEFORE]********canWriteData********");
        canWriteData(m_canWriteData);
        frame++;
    }
}

void FortuneThread::canWriteData(Mailbox_Write_Msg_ST data)
{
    int len;
#if 1
    //    data.canId = 0x0003;
    //    data.cmdId = 0x0002;
    //    data.dataHeader=0x0703;
    //    data.data[0] = 0x0a;
    //    data.data[1] = 0x0b;
    //    data.data[2] = 0x0c;
    //    data.data[3] = 0x0d;
    DEBUG_CHAR("\r\n");
    printf("hlc:%04x\r\n",data.hlc);
    printf("dlc:%04x\r\n",data.dlc);
    printf("canId:%04x\r\n",data.canId);
    printf("cmdId:%04x\r\n",data.cmdId);
    printf("dataHeader:%04x\r\n",data.dataHeader);
    for(int i=0;i<CAN_DATA_LEN;i++)
        printf("data:%02x \r\n",data.data[i]);
    DEBUG_CHAR("\r\n");
#endif
    
    len = write(m_mailbox_writefd, &data,sizeof(Mailbox_Write_Msg_ST));
    if(len == -1)
    {
        DEBUG_CHAR("m_mailboxfd write fail! \r\n");
    }
    else
    {
        DEBUG_CHAR("m_mailboxfd write successed! \r\n");
    }
}

void FortuneThread::restart()
{
    m_curTestItemIndex=0;
    iniTableViewByCarinfo();
    initTestListView();
}

void FortuneThread::thread_eixt()
{
    this->exit(0);
}

MainWindow::MainWindow() 
{
    DEBUGLOG;
    m_iCanCfg = 0;
    m_bSIM = true;
    m_bOpenDB = true;
    m_rootKey = "";
    m_sDBTerm = "";
    m_sProName = "";
    m_dbName = "";
    m_sSIMnumber = "";
    m_sSerialShow = "";
    m_msiDBTerm.clear();
    
    thread_m = new FortuneThread;
    rootContext()->setContextProperty("Thread", thread_m);
    
    m_harkey = new ComTiotDbusHardkeyInterface("com.tiot.dbus.hardkey", "/", QDBusConnection::systemBus(), this);
    m_harkey->wakeUp();
    connect(m_harkey, SIGNAL(sigKeyEvent(int, int)), this, SLOT(test(int, int)));
    rootContext()->setContextProperty("HardKey", m_harkey);
    
    thread_m->listModel     = new FileListItemModel;
    thread_m->tableModel    = new FileListItemModel;
    thread_m->tableMode2    = new FileListItemModel;
    thread_m->tableModelQR  = new FileListItemModel;
    rootContext()->setContextProperty("DataModel", thread_m->listModel);
    rootContext()->setContextProperty("TestNameModel", thread_m->tableModel);
    rootContext()->setContextProperty("TestNameMode2", thread_m->tableMode2);
    rootContext()->setContextProperty("TableModelQR", thread_m->tableModelQR);
    
    m_pConnectServerTime = new QTimer;
    connect( m_pConnectServerTime,SIGNAL(timeout()), this, SLOT(onConnectServer()));
    
    DEBUGLOG;
}

MainWindow::~MainWindow()
{
    deinitDatabase();
}

void MainWindow::test(int msgID, int param)
{
    DEBUG_CHAR("OOOOOOOOOOOOOOOOOOOO");
    DEBUG_CHAR("OOOOOOOOOOOOOOOOOOOO");
    DEBUG_CHAR("OOOOOOOOOOOOOOOOOOOO");
    DEBUG_CHAR("OOOOOOOOOOOOOOOOOOOO");
    DEBUG_CHAR("OOOOOOOOOOOOOOOOOOOO");
    emit thread_m->m_hardkey(msgID);
}

void MainWindow::init()
{
    DEBUGLOG;
    //init_db();
    thread_m->iniTableViewByCarinfo();
    thread_m->initTestListView();
}

void MainWindow::init_db()
{
    DEBUGLOG;
    if(!access("/run/media/usb/1.ini", F_OK))
    {
        DEBUG_CHAR("1.ini exists");
        QSettings set("/run/media/usb/1.ini", QSettings::IniFormat);
        set.setIniCodec("UTF-8");
        m_bSIM = set.value("SIMCheckCfg/value", 1).toBool();
        DEBUG_PARAM("sim:", m_bSIM);
        
        QString dbTerm = set.value("DBTerm/value", "").toString();
        DEBUG_PARAM("DBTerm:", dbTerm);
        bool ok;
        m_sDBTerm = QString("%1").arg(dbTerm.toInt(&ok, 16)&0xFFFF, 4*dbTerm.length(), 2, QLatin1Char('0'));
        DEBUG_PARAM("DBTerm:", m_sDBTerm);
        
        m_sProName = set.value("ProjectName/value").toString();
        DEBUG_PARAM("ProjectName:", m_sProName);
        m_dbName = QString("%1%2.db").arg(SQLITE_DATABASE_ONE).arg(m_sProName).toLatin1();
        DEBUG_PARAM("DatabaseName:", m_dbName);
        
        QString qr = set.value("QRcode/value").toString();
        DEBUG_PARAM("QRcode:", qr);
        m_sQRitem = QString("%1").arg(qr.toInt(&ok, 16)&0xFFFF, 4*qr.length(), 2, QLatin1Char('0'));
        DEBUG_PARAM("QRcode:", m_sQRitem);
        
        m_iCanCfg = set.value("CanCfg/value").toInt();
        DEBUG_PARAM("cancfg:", m_iCanCfg);
        can_dbus_interface->canwrite(id_canConfig, m_iCanCfg);
    }
    
    DEBUG_PARAM("db:", access(m_dbName.data(), F_OK));
    if(access(m_dbName.data(), F_OK) != 0)
    {
        initDatabase("");
        system("sync");
    }
    
    DEBUGLOG;
    if(m_bSIM && !access("/run/media/usb/tbox/SIM_RootKey.txt", F_OK))
    {
        readDataFile("/run/media/usb/tbox/SIM_RootKey.txt");
        system("mv /run/media/usb/tbox/ /run/media/usb/tbox_after/");
        system("sync");
    }
}

void MainWindow::onConnectServer()
{
    m_pConnectServerTime->stop();
    DEBUGLOG;
    thread_m->init();
    if(!thread_m->isRunning())
    {
        thread_m->start();
    }
}

void MainWindow::initDatabase(QString filePath)
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    int ret;
    char *pErrMsg;
    char *sql = NULL;
    
    if(m_bOpenDB)
    {
        m_bOpenDB = false;
        if((ret = sqlite3_open(m_dbName.data(), &m_pdb)) != SQLITE_OK)
        {
            fprintf(stderr,"Can't open databaseOne: %s\n", sqlite3_errmsg(m_pdb));
            sqlite3_close(m_pdb);
        }
        DEBUG_CHAR("open databaseOne successfully!");
    }
    
    QString sqlStr;
    int index = 0;
    QString term[] = {"ID", "iccid", "IMEI", "IMSI", "SN", "swversion", "hwversion", "rootKey", "sim", "product", "flag", "project"};
    if(m_sDBTerm.size() > 0 && m_sDBTerm.at(0).digitValue() == 1)
    {
        sqlStr += term[0];
        sqlStr += " INTEGER primary key, ";
        m_msiDBTerm[term[0]] = index++;
    }
    for(int i=1; i<sizeof(term)/sizeof(term[0]); ++i)
    {
        if(i < m_sDBTerm.size() && m_sDBTerm.at(i).digitValue() == 1)
        {
            sqlStr += term[i];
            sqlStr += " verchar, ";
            m_msiDBTerm[term[i]] = index++;
        }
    }
    sqlStr.chop(2);
    qDebug()<<m_msiDBTerm.keys();
    qDebug()<<m_msiDBTerm.values();
    qDebug()<<sqlStr;
    //create table
    //sql = sqlite3_mprintf("create table %s(id INTEGER primary key, iccid varchar, IMEI varchar,IMSI varchar,SN varchar, swversion varchar, hwversion varchar,rootKey varchar,sim varchar,product varchar, flag INTEGER)", TABLE_NAME);
    QByteArray bt = QString("create table %1(%2)").arg(TABLE_NAME).arg(sqlStr).toLatin1();
    sql = bt.data();
    DEBUG_PARAM("sql:\n", sql);
    
    if ((ret = sqlite3_exec(m_pdb,sql,NULL,NULL,&pErrMsg)) != SQLITE_OK)
    {
        fprintf(stderr, "create table_1 error: %s\n", pErrMsg);
    }
    else
    {
        DEBUG_CHAR("create table_1 ok!");
    }
}

void MainWindow::readDataFile(QString filePath)
{
    DEBUG_PARAM("filePath:", filePath);
    QFile file1(filePath);
    //判断文件是否存在
    if(file1.exists()){
        DEBUG_CHAR("file exit.");
    }else{
        DEBUG_CHAR("file dosen't exit.");
    }
    //已读写方式打开文件，
    //如果文件不存在会自动创建文件
    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text)){
        DEBUG_CHAR("打开失败");
    }else{
        DEBUG_CHAR("打开成功");
        //读取文件
        QTextStream txtInput(&file1);
        QString lineStr;
        while(!txtInput.atEnd())
        {
            lineStr = txtInput.readLine();
            QStringList qlineList = lineStr.split(",");
            //DEBUG_PARAM("qlineList.length:", qlineList.length());
            if(qlineList.length() >= 4)
            {
                //DEBUG_PARAM("qlineList.at(0):",qlineList.at(0));
                //DEBUG_PARAM("qlineList.at(3):",qlineList.at(3));
                insertData(qlineList.at(0), qlineList.at(3), qlineList.at(2));
            }
        }
    }
    //关闭文件
    file1.close();
}

void MainWindow::deinitDatabase()
{
    sqlite3_close(m_pdb);
}

void MainWindow::update_db_flag(bool flag)
{
    //    sql = sqlite3_mprintf("create table %s(id INTEGER primary key, iccid varchar,
    //IMEI varchar,IMSI varchar,SN varchar, swversion varchar, hwversion varchar,
    //rootKey varchar,sim varchar,flag INTEGER)", TABLE_NAME);
    if(m_bSIM)
    {
        if(flag)
        {
            updateFlagByIccid(str_iccid, "1");
        }
        else
        {
            updateFlagByIccid(str_iccid, "0");
        }
        sync();
        DEBUGLOG;
    }
    else
    {
        if(flag)
        {
            updateOtherByImei(thread_m->m_imei, "flag", "1");
        }
        else
        {
            updateOtherByImei(thread_m->m_imei, "flag", "0");
        }
        sync();
        DEBUGLOG;
    }
}

void MainWindow::insertData(QString iccid, QString rootKey, QString sim)
{
    DEBUGLOG;
    int ret;
    sqlite3_stmt * stmt;
    char *sql = sqlite3_mprintf("insert into %s(iccid, rootKey, sim) values('%s', '%s', '%s')",
                                TABLE_NAME,
                                iccid.toLocal8Bit().data(),
                                rootKey.toLocal8Bit().data(),
                                sim.toLocal8Bit().data());
    DEBUG_PARAM("sql:\n", sql);
    if((ret = sqlite3_prepare(m_pdb, sql, strlen(sql), &stmt, 0)) != SQLITE_OK)
    {
        fprintf(stderr, "insert error: %s\n", sqlite3_errmsg(m_pdb));
    }
    //execute
    ret = sqlite3_step(stmt);
    if(ret == SQLITE_DONE)
        DEBUG_CHAR("sqlite3_step ok!");
    
    //free memory
    sqlite3_finalize(stmt);
    
    updateOtherByIccid(iccid, "project", m_sProName);
}

void MainWindow::updateFlagByIccid(QString iccid, QString flag)
{
    DEBUG_PARAM("str_iccid:", str_iccid);
    int ret;
    sqlite3_stmt *stmt;
    char *sql = sqlite3_mprintf("update %s set flag='%s' where iccid='%s'",
                                TABLE_NAME,
                                flag.toLocal8Bit().data(),
                                iccid.toLocal8Bit().data());
    printf("%s\n", sql);
    
    if((ret = sqlite3_prepare(m_pdb, sql, strlen(sql), &stmt, 0)) != SQLITE_OK)
    {
        fprintf(stderr, "updateFlagByIccid error: %s\n", sqlite3_errmsg(m_pdb));
    }
    
    ret = sqlite3_step(stmt);
    if(ret == SQLITE_DONE)
        DEBUG_CHAR("sqlite3_step ok!");
    
    sqlite3_finalize(stmt);
}

void MainWindow::updateOtherByIccid(QString iccid, QString model,QString data)
{
    DEBUG_PARAM("iccid:", iccid);
    int ret;
    sqlite3_stmt *stmt;
    char *sql = sqlite3_mprintf("update %s set %s='%s' where iccid='%s'",
                                TABLE_NAME,
                                model.toLocal8Bit().data(),
                                data.toLocal8Bit().data(),
                                iccid.toLocal8Bit().data());
    printf("%s\n", sql);
    
    if((ret = sqlite3_prepare(m_pdb, sql, strlen(sql), &stmt, 0)) != SQLITE_OK)
    {
        fprintf(stderr, "updateOtherByIccid error: %s\n", sqlite3_errmsg(m_pdb));
    }
    
    ret = sqlite3_step(stmt);
    if(ret == SQLITE_DONE)
        DEBUG_CHAR("sqlite3_step ok!");
    
    sqlite3_finalize(stmt);
}

QString MainWindow::getData(QString iccid,QString data)
{
    DEBUG_PARAM2("iccid:", iccid, "data:", data);
    
    int ret;
    sqlite3_stmt *stmt;
    
    if(m_bOpenDB)
    {
        m_bOpenDB = false;
        if((ret = sqlite3_open(m_dbName.data(),&m_pdb)) != SQLITE_OK)
        {
            fprintf(stderr,"Can't open databaseOne: %s\n", sqlite3_errmsg(m_pdb));
            sqlite3_close(m_pdb);
        }
    }
    
    char *sql = sqlite3_mprintf("select %s from %s where iccid='%s'",data.toLocal8Bit().data(), TABLE_NAME, iccid.toLatin1().data());
    
    DEBUG_PARAM("sql:", sql);
    fflush(stdout);
    
    if((ret = sqlite3_prepare(m_pdb, sql, strlen(sql), &stmt, 0)) != SQLITE_OK)
    {
        fprintf(stderr, "select error: %s\n", sqlite3_errmsg(m_pdb));
    }
    
    //execute
    ret = sqlite3_step(stmt);
    if(ret == SQLITE_DONE)
    {
        DEBUG_CHAR("sqlite3_step ok!");
        fflush(stdout);
    }
    char *theGetDate = (char *)sqlite3_column_text(stmt, 0);
    QString strGet = QString(theGetDate);
    sqlite3_finalize(stmt);
    
    if(strGet != "")
    {
        return strGet;
    }
    else
        return "";
}

void MainWindow::insertData(const QString iccid, const QString imei)
{
    DEBUG_PARAM("imei:", imei);
    int ret;
    sqlite3_stmt *stmt;
    char *sql;
    if(iccid != "" && imei == "")
    {
        sql = sqlite3_mprintf("insert into %s(iccid) values('%s')", TABLE_NAME, iccid.toLocal8Bit().data());
    }
    else if(iccid == "" && imei != "")
    {
        sql = sqlite3_mprintf("insert into %s(IMEI) values('%s')", TABLE_NAME, imei.toLocal8Bit().data());
    }
    DEBUG_PARAM("sql:", sql);
    if((ret = sqlite3_prepare(m_pdb, sql, strlen(sql), &stmt, 0)) != SQLITE_OK)
    {
        fprintf(stderr, "insert error: %s\n", sqlite3_errmsg(m_pdb));
    }
    //execute
    ret = sqlite3_step(stmt);
    if(ret == SQLITE_DONE)
    {
        DEBUG_CHAR("sqlite3_step ok!");
    }
    //free memory
    sqlite3_finalize(stmt);
    
    if(iccid != "" && imei == "")
    {
        updateOtherByIccid(iccid, "project", m_sProName);
    }
    else if(iccid == "" && imei != "")
    {
        updateOtherByImei(imei, "project", m_sProName);
    }
}

void MainWindow::updateOtherByImei(QString imei, QString model,QString data)
{
    DEBUG_PARAM2("imei", imei, "term", model);
    
    int ret;
    sqlite3_stmt *stmt;
    char *sql = sqlite3_mprintf("update %s set %s='%s' where IMEI='%s'",
                                TABLE_NAME,
                                model.toLocal8Bit().data(),
                                data.toLocal8Bit().data(),
                                imei.toLocal8Bit().data());
    printf("%s\n", sql);
    
    if((ret = sqlite3_prepare(m_pdb, sql, strlen(sql), &stmt, 0)) != SQLITE_OK)
    {
        fprintf(stderr, "updateOtherByImei error: %s\n", sqlite3_errmsg(m_pdb));
    }
    
    ret = sqlite3_step(stmt);
    if(ret == SQLITE_DONE)
        DEBUG_CHAR("sqlite3_step ok!");
    DEBUG_PARAM("ret:", ret);
    
    sqlite3_finalize(stmt);
}

QString MainWindow::getDataByIMEI(QString imei,QString data)
{
    DEBUG_PARAM2("imei:", imei, "data:", data);
    
    int ret;
    sqlite3_stmt *stmt;
    DEBUG_PARAM("open_db_flag:", m_bOpenDB);
    if(m_bOpenDB)
    {
        m_bOpenDB = false;
        if((ret = sqlite3_open(m_dbName.data(),&m_pdb)) != SQLITE_OK)
        {
            fprintf(stderr,"Can't open databaseOne: %s\n", sqlite3_errmsg(m_pdb));
            sqlite3_close(m_pdb);
        }
    }
    
    char *sql = sqlite3_mprintf("select %s from %s where IMEI='%s'",data.toLocal8Bit().data(), TABLE_NAME, imei.toLatin1().data());
    
    DEBUG_PARAM("sql:", sql);
    fflush(stdout);
    
    if((ret = sqlite3_prepare(m_pdb, sql, strlen(sql), &stmt, 0)) != SQLITE_OK)
    {
        fprintf(stderr, "select error: %s\n", sqlite3_errmsg(m_pdb));
    }
    
    //execute
    ret = sqlite3_step(stmt);
    if(ret == SQLITE_DONE)
    {
        DEBUG_CHAR("sqlite3_step ok!");
        fflush(stdout);
    }
    DEBUG_PARAM("ret:", ret);
    
    char *theGetDate = (char *)sqlite3_column_text(stmt, 0);
    QString strGet = QString(theGetDate);
    sqlite3_finalize(stmt);
    
    if(strGet != "")
    {
        return strGet;
    }
    else
        return "";
}

bool MainWindow::findData(const QString iccid, const QString imei)
{   
    int ret;
    sqlite3_stmt *stmt;
    
    if(m_bOpenDB)
    {
        m_bOpenDB = false;
        if((ret = sqlite3_open(m_dbName.data(),&m_pdb)) != SQLITE_OK)
        {
            DEBUG_PARAM("ret:", ret);
            fprintf(stderr,"Can't open databaseOne: %s\n", sqlite3_errmsg(m_pdb));
            sqlite3_close(m_pdb);
        }
    }
    
    char *sql;
    if(iccid != "" && imei == "")
    {
        sql = sqlite3_mprintf("select * from %s where iccid like '%s'",TABLE_NAME, iccid.toLocal8Bit().data());
    }
    else if(iccid == "" && imei != "")
    {
        sql = sqlite3_mprintf("select * from %s where IMEI like '%s'",TABLE_NAME, imei.toLocal8Bit().data());
    }
    
    DEBUG_PARAM("sql:", sql);
    fflush(stdout);
    
    if((ret = sqlite3_prepare(m_pdb, sql, strlen(sql), &stmt, 0)) != SQLITE_OK)
    {
        fprintf(stderr, "select error: %s\n", sqlite3_errmsg(m_pdb));
    }
    
    //execute
    ret = sqlite3_step(stmt);
    if(ret == SQLITE_DONE)
    {
        DEBUG_CHAR("sqlite3_step ok!");
        fflush(stdout);
    }
    DEBUG_PARAM("ret:", ret);
    
    int cCount = sqlite3_column_count(stmt);
    char *theGetDate = nullptr;
    bool bEmpty = true;
    for(int i=0; i<cCount; ++i)
    {
        theGetDate = (char *)sqlite3_column_text(stmt, i);
        DEBUG_PARAM2("index:", i, "text:", QString(theGetDate));
        if(QString(theGetDate) != "")
        {
            bEmpty = false;
            break;
        }
    }
    sqlite3_finalize(stmt);
    DEBUG_PARAM("is exist:", bEmpty);
    if(bEmpty)
    {
        return false;
    }
    else
        return true;
}

encode::encode(QString path)
{
    DEBUGLOG;
    /* Open PCM device for recording (capture). */
    /* 打开 PCM capture 捕获设备 */
    char*  ch;
    QByteArray ba = path.toLatin1(); // must
    ch=ba.data();
    fp = fopen(ch,"wb");
    snd_pcm_open(&handle, "hw:1,0",SND_PCM_STREAM_CAPTURE, 0);
    DEBUGLOG;
    /* Allocate a hardware parameters object. */
    /* 分配一个硬件参数结构体 */
    snd_pcm_hw_params_alloca(&params);
    
    DEBUGLOG;
    /* Fill it in with default values. */
    /* 使用默认参数 */
    snd_pcm_hw_params_any(handle, params);
    
    DEBUGLOG;
    /* Set the desired hardware parameters. */
    
    /* Interleaved mode */
    snd_pcm_hw_params_set_access(handle, params,
                                 SND_PCM_ACCESS_RW_INTERLEAVED);
    
    DEBUGLOG;
    /* Signed 16-bit little-endian format */
    /* 16位 小端 */
    snd_pcm_hw_params_set_format(handle, params,
                                 SND_PCM_FORMAT_S16_LE);
    
    DEBUGLOG;
    /* Two channels (stereo) */
    /* 双通道 */
    snd_pcm_hw_params_set_channels(handle, params, 1);
    
    DEBUGLOG;
    /* 44100 bits/second sampling rate (CD quality) */
    /* 采样率 */
    val = 8000;
    snd_pcm_hw_params_set_rate_near(handle, params,
                                    &val, &dir);
    
    DEBUGLOG;
    /* Set period size to 32 frames. */
    /* 一个周期有 32 帧 */
    frames = 32;
    snd_pcm_hw_params_set_period_size_near(handle,
                                           params, &frames, &dir);
    
    DEBUGLOG;
    /* Write the parameters to the driver */
    /* 参数生效 */
    rc = snd_pcm_hw_params(handle, params);
    
    DEBUGLOG;
    /* Use a buffer large enough to hold one period */
    /* 得到一个周期的数据大小 */
    snd_pcm_hw_params_get_period_size(params,
                                      &frames, &dir);
    DEBUGLOG;
    /* 16位 双通道，所以要 *4 */
    size = frames * 2; /* 2 bytes/sample, 2 channels */
    buffer = (char *) malloc(size);
    
    DEBUGLOG;
    /* We want to loop for 5 seconds */
    /* 等到一个周期的时间长度 */
    snd_pcm_hw_params_get_period_time(params,&val, &dir);
    DEBUGLOG;
}

void encode::run()
{
    while (flag) {
        QThread::msleep(10);
        //DEBUGLOG;
        /* 捕获数据 */
        rc = snd_pcm_readi(handle, buffer, frames);
        if (rc == -EPIPE) {
            /* EPIPE means overrun */
            snd_pcm_prepare(handle);
        } else if (rc < 0) {
            
        } else if (rc != (int)frames) {
            
        }
        /* 写入到标准输出中去 */
        fwrite(buffer,1,64,fp);
    }
    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    fclose(fp);
    free(buffer);
}

void encode::stoprecord()
{
    flag=false;
}
