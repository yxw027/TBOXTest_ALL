#include "mainwindow.h"
#include <share.h>
#include <qiterator.h>

#define COUNT_CHECK 23

bool stop_monitorusb = false;
char str_iccid[21]={0};
QString p_name="";
QString p_model="";
QString pn_num="";
QString str_imei="";
QString str_imsi="";
QString sim_num="";
QString tBoxSN3="0000";
QString serial_show="";
bool open_db_flag = true;
bool remove_flag = false;
char software_version[15]={0};

monitorusb::monitorusb()
{
    udev = udev_new();
    if (!udev) {
        qDebug()<<"udev_new fail";
    }
    mon = udev_monitor_new_from_netlink(udev, "udev");
    udev_monitor_filter_add_match_subsystem_devtype(mon, "usb", NULL);
    udev_monitor_enable_receiving(mon);
    fd = udev_monitor_get_fd(mon);
    enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "usb");
    udev_enumerate_scan_devices(enumerate);
    devices = udev_enumerate_get_list_entry(enumerate);
    udev_list_entry_foreach(dev_list_entry, devices) {
        const char *path;
        path = udev_list_entry_get_name(dev_list_entry);
        dev = udev_device_new_from_syspath(udev, path);

        dev = udev_device_get_parent_with_subsystem_devtype(
                    dev,
                    "usb",
                    "usb_device");
        if (!dev) {
            printf("Unable to find parent usb device.");
            DEBUGLOG;
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
    while (true) {
        if(stop_monitorusb)
        {
            break;
        }
        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        tv.tv_sec = 0;
        tv.tv_usec = 0;

        ret = select(fd+1, &fds, NULL, NULL, &tv);
        if (ret > 0 && FD_ISSET(fd, &fds)) {
            dev = udev_monitor_receive_device(mon);
            if (dev) {
                strcpy(buf_devpath, udev_device_get_devpath(dev));
                strcpy(buf, udev_device_get_action(dev));
                fflush(stdout);
                QString str = buf;
                QString str_type = buf_devpath;
                DEBUG_PARAM("str_type:", str_type);
                if(str.contains("remove") )
                {
                    if( str_type.contains("usb2"))
                    {
                        DEBUGLOG;
                        remove_flag = true;
                        DEBUG_PARAM("remove_flag:", remove_flag);
                        emit mainwindow->thread_m->device_disconnect();
                        this->quit();
                    }
                    else if (  str_type.contains("usb1") )
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
            else {
                DEBUGLOG;
                printf("No Device from receive_device(). An error occured.\n");
                fflush(stdout);
                emit mainwindow->thread_m->udisk_disconnect();
                exit(1);
            }
        }
        msleep(200);
        printf(".");
        fflush(stdout);
    }
    udev_unref(udev);
}
/////////////////////////FortuneThread//////////////////////////////
void FortuneThread::iniTableViewByCarinfo()
{
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

void FortuneThread::iniTableViewByqr() 
{
    /*
    if(mainwindow->m_bSIM)
    {
        QString str[] = {"产品名称","产品型号","软件版本号","硬件版本号","SIM/N", "IMEI", "IMSI", "ICCID", "SN", "P/N"};
        for(int i=0; i<sizeof(str)/sizeof(str[0]); i++) 
        {
            FileListItem item(str[i], "", i);
            tableModelQR->addFileListItem(item);
            DEBUG_PARAM("qr=", str[i]);
        }
    }
    else
    {
        QString str[] = {"SN"};
        for(int i=0; i<1; i++)
        {
            FileListItem item(str[i], "", i);
            tableModelQR->addFileListItem(item);
            DEBUG_PARAM("qr=", str[i]);
        }
    }*/
    m_msiQRitem.clear();
    int index = 0;
    QString str[] = {"产品名称","产品型号","软件版本号","硬件版本号","SIM/N", "IMEI", "IMSI", "ICCID", "SN", "P/N"};
    for(int i=0; i<sizeof(str)/sizeof(str[0]); ++i)
    {
        if(i<mainwindow->m_sQRitem.length() && mainwindow->m_sQRitem.at(i).digitValue() == 1)
        {
            FileListItem item(str[i], "", index);
            tableModelQR->addFileListItem(item);
            m_msiQRitem[str[i]] = index++;
        }
    }
    qDebug()<<m_msiQRitem.keys();
}

bool FortuneThread::analyze_section_data()
{
    uint16_t head=0;
    uint16_t msglen=0;
    uint8_t cmd=0;
    if(*readMsg != 0) 
    {
        head = *(uint16_t*)readMsg;
        head = qFromBigEndian(head);
        msglen = *(uint16_t*)(readMsg+2);
        msglen = qFromBigEndian(msglen);
        cmd = *(uint8_t*)(readMsg+4);
    }
    if(head==0xAA55 && cmd==0x02)
        return true;
    else
        return false;
//    switch (cmd) {
//    case 0x01:
//    {
//        if(head == 0xAA55 && cmd==0x01 && tag=0x00) { (0x2A, 0x02, 0x00, 0x27); }//42 02, 00, 39
//    }
//        break;
//    case 0x02:
//        if(head == 0xAA55 && cmd==0x01 && tag=0x00) { sendMsg(0x2A, 0x02, 0x00, 0x27); }//42 02, 00, 39
//    default:
//        break;
//    }
}

void FortuneThread::handle_cfg_mode()
{
    DEBUGLOG;
    uint16_t head=0;
    uint16_t msglen=0;
    uint8_t cmd=0;
    uint8_t msgbody1=0;
    uint8_t msgbody2=0;
    head = *(uint16_t*)readMsg;
    head = qFromBigEndian(head);
    msglen = *(uint16_t*)(readMsg+2);
    msglen = qFromBigEndian(msglen);
    cmd = *(uint8_t*)(readMsg+4);
    msgbody1 = *(uint8_t*)(readMsg+5);
    msgbody2 = *(uint8_t*)(readMsg+6);
    
    char iccid[20]={0};
    memcpy(iccid, readMsg+7, 20);
    DEBUG_PARAM("iccid:", iccid);
    memset(str_iccid, 0, 21);
    memcpy(str_iccid, iccid, 20);
    DEBUG_PARAM("str_iccid:", str_iccid);
    tableModel->setFileNamebyFilePath("ICCID", str_iccid); 
    if(mainwindow->m_bSIM && !(mainwindow->m_bRootkey) && QString::compare(str_iccid, "") != 0)
    {
        if(mainwindow->findData(str_iccid, ""))
        {
            DEBUG_CHAR(str_iccid);
        }
        else
        {
            DEBUGLOG;
            mainwindow->insertData(str_iccid, "");
            sync();
        }
    }
    
    memcpy(&sig_strength, readMsg+27, 1);
    DEBUG_PARAM("sig_strength:", sig_strength);
    emit signal_strength((int)sig_strength);
    
    memcpy(software_version, readMsg+28, 12);
    DEBUG_PARAM("software_version:", software_version);
    tableMode2->setFileNamebyFilePath("软件版本号", software_version);

    char str_hw[16]={0};
    memcpy(str_hw, readMsg+40, 14);//hw--40
    strncpy(hw, str_hw, 11);
    DEBUG_PARAM("hw:", hw);
    tableMode2->setFileNamebyFilePath("硬件版本号", hw);

    char buf[24]={0};//mcu 14bytes
    memcpy(buf, readMsg+54, 14);
    emit mcuVersion(buf);
    DEBUG_PARAM("mcuVersion:", buf);

    memset(buf, 0, sizeof(buf));//app 14bytes
    memcpy(buf, readMsg+68, 14);
    emit appVersion(buf);
    DEBUG_PARAM("appVersion:", buf);

    memset(buf, 0, sizeof(buf));//os 18bytes
    memcpy(buf, readMsg+82, 18);
    emit osVersion(buf);
    DEBUG_PARAM("osVersion:", buf);

    if( head==0xAA55 && cmd==0x01 && msgbody2==0x00 )
    {
        DEBUG_CHAR("cfg mode succeed");
        emit update_iccid();
    }
    else
    {
        emit errorCode("配置测试模式", 200);
        stop = true;
        DEBUG_CHAR("cfg mode failed");
    }
}

void FortuneThread::handle_cfg_modeIMEI()
{
    DEBUGLOG;
    uint16_t head=0;
    uint16_t msglen=0;
    uint8_t cmd=0;
    uint8_t msgbody1=0;
    uint8_t msgbody2=0;
    head = *(uint16_t*)readMsg;
    head = qFromBigEndian(head);
    msglen = *(uint16_t*)(readMsg+2);
    msglen = qFromBigEndian(msglen);
    cmd = *(uint8_t*)(readMsg+4);
    msgbody1 = *(uint8_t*)(readMsg+5);
    msgbody2 = *(uint8_t*)(readMsg+6);

    //4G signal strength
    uint8_t sigLen=0;
    memcpy(&sigLen, readMsg+7, 1);
    memcpy(&sig_strength, readMsg+8, sigLen);
    int offset= 8+sigLen;
    emit signal_strength((int)sig_strength);
    DEBUG_PARAM2("sigLen:", sigLen, "sig_strength:", sig_strength);

    //IMEI
    uint8_t imeiLen=0;
    memcpy(&imeiLen, readMsg+offset, 1);
    offset = offset+1;
    memcpy(imei, readMsg+offset, imeiLen);
    offset = offset+imeiLen;
    DEBUG_PARAM2("imeiLen:", imeiLen, "imei:", imei);
    if(QString::compare(imei, "") == 0)
    {
        DEBUG_CHAR("IMEI is empty!!!");
        emit errorCode("IMEI", 4);
    }
    else
    {
        if(mainwindow->findData("", imei))// imei is no empty
        {
            m_imei = imei;
            DEBUG_PARAM("m_imei:", m_imei);

        }
        else
        {
           m_imei = imei;
           mainwindow->insertData("", m_imei);
        }
        sync();
    }

    //4G软件版本号
    uint8_t swLen=0;
    memcpy(&swLen, readMsg+offset, 1);
    offset = offset+1;
    memcpy(software_version, readMsg+offset, swLen);
    offset = offset+swLen;
    DEBUG_PARAM2("swLen:", swLen, "software_version:", software_version);
    QString str = software_version;
    if(str=="")
    {
        DEBUG_CHAR("software_version is empty!!!");
        emit errorCode("软件版本号", 7);
    }
    else
    {
        emit appVersion(str);
    }
    tableMode2->setFileNamebyFilePath("软件版本号", software_version);

    //MCU版本
    uint8_t mcuLen=0;
    char mcu_buf[16]={0};
    memcpy(&mcuLen, readMsg+offset, 1);
    offset = offset+1;
    memcpy(mcu_buf, readMsg+offset, mcuLen);
    offset = offset+mcuLen;
    DEBUG_PARAM2("mcuLen:", mcuLen, "mcu version:", mcu_buf);
    emit mcuVersion(mcu_buf);

    //硬件版本号
    uint8_t hwLen=0;
    char buf[8]={0};
    memcpy(&hwLen, readMsg+offset, 1);
    offset = offset+1;
    memcpy(buf, readMsg+offset, hwLen);//hwLen
    offset = offset+hwLen;
    DEBUG_PARAM2("hw hwLen:", hwLen, "hw version:", buf);
    hwIMEI = buf;
    if(hwIMEI =="")
    {
        emit errorCode("硬件版本号", 6);
    }
    else
    {
        tableMode2->setFileNamebyFilePath("硬件版本号", hwIMEI);
    }
    /*
    //APP版本
    uint8_t appLen=0;
    char app_buf[8]={0};
    memcpy(&appLen, readMsg+offset, 1);
    offset = offset+1;
    memcpy(app_buf, readMsg+offset, appLen);
    offset = offset+appLen;
    DEBUG_PARAM("appLen:", appLen);
    DEBUG_PARAM("app version:", app_buf);
    emit appVersion(app_buf);

    //OS版本--4G
    uint8_t osLen=0;
    char os_buf[8]={0};
    memcpy(&osLen, readMsg+offset, 1);
    offset = offset+1;
    memcpy(os_buf, readMsg+offset, osLen);
    offset = offset+osLen;
    emit osVersion(os_buf);
    DEBUG_PARAM("osLen:", osLen);
    DEBUG_PARAM("os version:", os_buf);

    //系统版本
    uint8_t sysLen=0;
    char sys_buf[8]={0};
    memcpy(&sysLen, readMsg+offset, 1);
    offset = offset+1;
    memcpy(sys_buf, readMsg+offset, sysLen);
    offset = offset+sysLen;
    emit sysVersion(sys_buf);
    DEBUG_PARAM("sysLen:", sysLen);
    DEBUG_PARAM("sys version:", sys_buf);
    */
    uint8_t sysLen=0;//system version
    char sys_buf[16]={0};
    memcpy(&sysLen, readMsg+offset, 1);
    offset = offset+1;
    memcpy(sys_buf, readMsg+offset, sysLen);
    offset = offset+sysLen;
    DEBUG_PARAM2("sysLen:", sysLen, "sys version:", sys_buf);
    emit sysVersion(sys_buf);

    uint8_t osLen=0;//os version
    char os_buf[16]={0};
    memcpy(&osLen, readMsg+offset, 1);
    offset = offset+1;
    memcpy(os_buf, readMsg+offset, osLen);
    offset = offset+osLen;
    DEBUG_PARAM2("osLen:", osLen, "os version:", os_buf);
    emit osVersion(os_buf);

    if( head==0xAA55 && cmd==0x01 && msgbody2==0x00 )
    {
        DEBUG_CHAR("cfg mode succeed");
        emit update_sn();
    }
    else
    {
        emit errorCode("配置测试模式", 200);
        stop = true;
        DEBUG_CHAR("cfg mode failed");
    }
}

void FortuneThread::handle_cfg_modeNew()
{
    DEBUGLOG;
    uint16_t head=0;
    uint16_t msglen=0;
    uint8_t cmd=0;
    uint8_t msgbody1=0;
    uint8_t msgbody2=0;
    head = *(uint16_t*)readMsg;
    head = qFromBigEndian(head);
    msglen = *(uint16_t*)(readMsg+2);
    msglen = qFromBigEndian(msglen);
    cmd = *(uint8_t*)(readMsg+4);
    msgbody1 = *(uint8_t*)(readMsg+5);
    msgbody2 = *(uint8_t*)(readMsg+6);
    
    //4G signal strength
    memcpy(&sig_strength, readMsg+7, 1);
    emit signal_strength((int)sig_strength);
    DEBUG_PARAM("sig strength:", sig_strength);
    
    //iccid
    char buffer[1] = {0};
    int tmpIndex = 8;
    DEBUG_PARAM("readMsg:", sizeof(readMsg)/sizeof(readMsg[0]));
    for(int i=8; i<sizeof(readMsg)/sizeof(readMsg[0]); ++i)
    {
        memset(buffer, 0, 1);
        memcpy(buffer, readMsg+i, 1);
        if(*buffer == '\0')
        {
            tmpIndex = i;
            break;
        }
    }
    memcpy(str_iccid, readMsg+8, tmpIndex-8);
    DEBUG_PARAM("str_iccid:", str_iccid);
    tableModel->setFileNamebyFilePath("ICCID", str_iccid);
    int tmpIndex1 = ++tmpIndex;
    
    //imei
    for(int i=tmpIndex1; i<sizeof(readMsg)/sizeof(readMsg[0]); ++i)
    {
        memset(buffer, 0, 1);
        memcpy(buffer, readMsg+i, 1);
        if(*buffer == '\0')
        {
            tmpIndex = i;
            break;
        }
    }
    memcpy(imei, readMsg+tmpIndex1, tmpIndex-tmpIndex1);
    DEBUG_PARAM("imei:", imei);
    tmpIndex1 = ++tmpIndex;
    if(!mainwindow->m_bSIM)
    {
        if(QString::compare(imei, "") == 0)
        {
            DEBUG_CHAR("IMEI is empty!!!");
            emit errorCode("IMEI", 4);
        }
        else
        {
            if(mainwindow->findData("", imei))// imei is no empty
            {
                m_imei = imei;
                DEBUG_PARAM("m_imei:", m_imei);
    
            }
            else
            {
               m_imei = imei;
               mainwindow->insertData("", m_imei);
            }
            sync();
        }
    }
    
    //4G软件版本号
    for(int i=tmpIndex1; i<sizeof(readMsg)/sizeof(readMsg[0]); ++i)
    {
        memset(buffer, 0, 1);
        memcpy(buffer, readMsg+i, 1);
        if(*buffer == '\0')
        {
            tmpIndex = i;
            break;
        }
    }
    memcpy(software_version, readMsg+tmpIndex1, tmpIndex-tmpIndex1);
    DEBUG_PARAM("4g software version:", software_version);
    tableMode2->setFileNamebyFilePath("软件版本号", software_version);
    tmpIndex1 = ++tmpIndex;
    
    //4G版本号(内部查看)
    char buf[24]={0};
    for(int i=tmpIndex1; i<sizeof(readMsg)/sizeof(readMsg[0]); ++i)
    {
        memset(buffer, 0, 1);
        memcpy(buffer, readMsg+i, 1);
        if(*buffer == '\0')
        {
            tmpIndex = i;
            break;
        }
    }
    memcpy(buf, readMsg+tmpIndex1, tmpIndex-tmpIndex1);
    DEBUG_PARAM("4g version:", buf);
    emit appVersion(buf);
    tmpIndex1 = ++tmpIndex;
    
    //4G系统版本号(boot)
    memset(buf, 0, sizeof(buf));
    for(int i=tmpIndex1; i<sizeof(readMsg)/sizeof(readMsg[0]); ++i)
    {
        memset(buffer, 0, 1);
        memcpy(buffer, readMsg+i, 1);
        if(*buffer == '\0')
        {
            tmpIndex = i;
            break;
        }
    }
    memcpy(buf, readMsg+tmpIndex1, tmpIndex-tmpIndex1);
    DEBUG_PARAM("4g system version:", buf);
    emit osVersion(buf);
    tmpIndex1 = ++tmpIndex;
    
    //mcu
    memset(buf, 0, sizeof(buf));
    for(int i=tmpIndex1; i<sizeof(readMsg)/sizeof(readMsg[0]); ++i)
    {
        memset(buffer, 0, 1);
        memcpy(buffer, readMsg+i, 1);
        if(*buffer == '\0')
        {
            tmpIndex = i;
            break;
        }
    }
    memcpy(buf, readMsg+tmpIndex1, tmpIndex-tmpIndex1);
    DEBUG_PARAM("mcu version:", buf);
    emit mcuVersion(buf);
    tmpIndex1 = ++tmpIndex;
    
    //hw
    memset(buf, 0, sizeof(buf));
    for(int i=tmpIndex1; i<sizeof(readMsg)/sizeof(readMsg[0]); ++i)
    {
        memset(buffer, 0, 1);
        memcpy(buffer, readMsg+i, 1);
        if(*buffer == '\0')
        {
            tmpIndex = i;
            break;
        }
    }
    memcpy(hw, readMsg+tmpIndex1, tmpIndex-tmpIndex1);
    DEBUG_PARAM("hw version:", hw);
    tableMode2->setFileNamebyFilePath("硬件版本号", hw);
    
    if( head==0xAA55 && cmd==0x01 && msgbody2==0x00 )
    {
        DEBUG_CHAR("cfg mode succeed");
        if(mainwindow->m_bSIM)
        {
            emit update_iccid();
        }
        else
        {
            emit update_sn();
        }
    }
    else
    {
        emit errorCode("配置测试模式", 200);
        stop = true;
        DEBUG_CHAR("cfg mode failed");
    }
}
//"IMEI", "ICCID", "IMSI", "序列号", "供应商零件
void FortuneThread::handleqrCode()
{
    int i;
    uint8_t tag;
    uint16_t taglen;
    int offset=0;
    char buf[35]={1};
    QString content;
    tag = *(uint8_t*)(readMsg+5);
    taglen = *(uint16_t*)(readMsg+6);
    offset = offset + 8;
    if(tag==0x71)
    {
        if(m_msiQRitem.find("产品名称") != m_msiQRitem.end())
        {
            DEBUG_PARAM("product name:", p_name);
            QByteArray ba = p_name.toUtf8();
            qrcodeStr.append("产品名称: ");
            qrcodeStr.append(ba.data());
            qrcodeStr.append("\n");
            tableModelQR->setFileNamebyFilePath("产品名称", p_name);
        }
        
        if(m_msiQRitem.find("产品型号") != m_msiQRitem.end())
        {
            DEBUG_PARAM("product model:", p_model);
            qrcodeStr.append("产品型号: ");
            qrcodeStr.append(p_model.toLatin1().data());
            qrcodeStr.append("\n");
            tableModelQR->setFileNamebyFilePath("产品型号", p_model);
        }

        if(m_msiQRitem.find("软件版本号") != m_msiQRitem.end())
        {
            DEBUG_PARAM("software version:", software_version);
            qrcodeStr.append("软件版本号: ");
            qrcodeStr.append(software_version);
            qrcodeStr.append("\n");
            tableModelQR->setFileNamebyFilePath("软件版本号", QString(software_version).toLocal8Bit());
        }

        if(m_msiQRitem.find("硬件版本号") != m_msiQRitem.end())
        {
            DEBUG_PARAM("hardware version:", hw);
            qrcodeStr.append("硬件版本号: ");
            qrcodeStr.append(hw);
            qrcodeStr.append("\n");
            tableModelQR->setFileNamebyFilePath("硬件版本号", hw);
        }

        if(m_msiQRitem.find("SIM/N") != m_msiQRitem.end())
        {
            DEBUG_PARAM("SIM/N:", sim_num.toLatin1().data());
            qrcodeStr.append("SIM/N: ");
            qrcodeStr.append(sim_num.toLatin1().data());
            qrcodeStr.append("\n");
            tableModelQR->setFileNamebyFilePath("SIM/N",sim_num.toLocal8Bit());
        }
        //ICCID
        memset(buf, 0, 35);
        for(i=0; i<20; i++)
        {
            buf[i] = *(readMsg+offset+i);
        }
        content = QString::fromLocal8Bit(buf);
        offset=offset+20;
        if(m_msiQRitem.find("ICCID") != m_msiQRitem.end())
        {
            DEBUG_PARAM("ICCID:", content);
            tableModelQR->setFileNamebyFilePath("ICCID", content);
            content.prepend("ICCID: ");
            qrcodeStr.append(content);
            qrcodeStr.append("\n");
        }
        content.clear();
        //IMEI
        memset(buf, 0, 35);
        for(i=0; i<15; i++)
        {
            buf[i] = *(readMsg+offset+i);
        }
        offset = offset + 15;
        str_imei = buf;
        if(str_imei=="")
        {
            emit errorCode("IMEI", 4);
        }
        content = QString::fromLocal8Bit(buf);
        DEBUG_PARAM("IMEI:", content);
        tableMode2->setFileNamebyFilePath("IMEI", content);
        if(m_msiQRitem.find("IMEI") != m_msiQRitem.end())
        {
            tableModelQR->setFileNamebyFilePath("IMEI", content);
            content.prepend("IMEI: ");
            qrcodeStr.append(content);
            qrcodeStr.append("\n");
        }
        content.clear();
        //IMSI
        memset(buf, 0, 35);
        for(i=0; i<15; i++)
        {
            buf[i] = *(readMsg+offset+i);
        }
        offset = offset + 15;
        str_imsi = buf;
        if(str_imsi=="")
        {
            emit errorCode("IMSI", 1);
        }
        content = QString::fromLocal8Bit(buf);
        DEBUG_PARAM("IMSI:", content);
        tableModel->setFileNamebyFilePath("IMSI", content);
        if(m_msiQRitem.find("IMSI") != m_msiQRitem.end())
        {
            tableModelQR->setFileNamebyFilePath("IMSI", content);
            content.prepend("IMSI: ");
            qrcodeStr.append(content);
            qrcodeStr.append("\n");
        }
        content.clear();
        //序列号
        memset(buf, 0, 35);
        for(i=0; i<30; i++)
        {
            buf[i] = *(readMsg+offset+i);
        }
        offset=offset+30;
        content = QString::fromLocal8Bit(buf);
        if(m_msiQRitem.find("SN") != m_msiQRitem.end())
        {
            qrcodeStr.append("SN: ");
            qrcodeStr.append(serial_show);
            qrcodeStr.append("\n");
            content.clear();
            tableModelQR->setFileNamebyFilePath("SN", serial_show);
        }

/*
        memset(buf, 0, 35);//供应商零件
        for(i=0; i<16; i++)
        {
            buf[i] = *(readMsg+offset+i);
            printf("qrcode 供应商零件=%d\n", buf[i]);
            fflush(stdout);
        }
        offset=offset+16;
        content = QString::fromLocal8Bit(buf);
        qDebug("供应商零件 content = %s", qPrintable(content));
*/

        if(m_msiQRitem.find("P/N") != m_msiQRitem.end())
        {
            qrcodeStr.append("P/N: ");
            qrcodeStr.append(pn_num.toLatin1().data());
            qrcodeStr.append("\n");
            tableModelQR->setFileNamebyFilePath("P/N", pn_num);
        }
    }
    mainwindow->updateOtherByIccid(str_iccid, "IMEI", str_imei);
    mainwindow->updateOtherByIccid(str_iccid, "IMSI", str_imsi);
    sync();
    DEBUG_PARAM("qrcodeStr:", qrcodeStr.data());
}

void FortuneThread::handleqrCodeIMEI() 
{
    uint8_t tag;
    uint16_t taglen;
    int offset=0;
    char buf[35]={1};
    QString content;
    tag = *(uint8_t*)(readMsg+5);
    taglen = *(uint16_t*)(readMsg+6);
    offset = offset + 8;
    if(tag==0x71)
    {
        /*
        qDebug("产品名称=%s", qPrintable(p_name));
        QByteArray ba = p_name.toUtf8();
        qrcodeStr.append("产品名称: ");
        qrcodeStr.append(ba.data());
        qrcodeStr.append("\n");

        qDebug("产品型号=%s", qPrintable(p_model));
        qrcodeStr.append("产品型号: ");
        qrcodeStr.append(p_model);
        qrcodeStr.append("\n");

        qDebug("软件版本号=%s", qPrintable(software_version));
        qrcodeStr.append("软件版本号: ");
        qrcodeStr.append(software_version);
        qrcodeStr.append("\n");

        qrcodeStr.append("硬件版本号: ");
        qrcodeStr.append(hw);
        qrcodeStr.append("\n");*/

        /*
        qDebug("SIM/N:=%s", qPrintable(sim_num.toLatin1().data()));
        qrcodeStr.append("SIM/N: ");
        qrcodeStr.append(sim_num.toLatin1().data());
        qrcodeStr.append("\n");*/

        /*
        memset(buf, 0, 35);//ICCID
        for(i=0; i<20; i++)
        {
            buf[i] = *(readMsg+offset+i);
            //            printf("qrcode ICCID=%d\n", buf[i]);
            //            fflush(stdout);
        }
        offset=offset+20;
        QString str = buf;
        tableModelQR->setFileNamebyFilePath("ICCID", str);
        //        printf("ICCID buf =%s", buf);
        //        fflush(stdout);
        content = QString::fromLocal8Bit(buf);
        tableModelQR->setFileNamebyFilePath("ICCID", content);
        content.prepend("ICCID: ");
        qrcodeStr.append(content);
        qrcodeStr.append("\n");
        content.clear();*/

        //IMEI
        /*
        memset(buf, 0, 35);
        for(i=0; i<15; i++)
        {
            buf[i] = *(readMsg+offset+i);
        }
        str_imei = buf;
        offset=offset+15;
        */

        if(imei=="")
        {
            emit errorCode("IMEI", 4);
        }
        printf("IMEI buf =%s", imei);
        fflush(stdout);
        tableMode2->setFileNamebyFilePath("IMEI", imei);
//        tableModelQR->setFileNamebyFilePath("IMEI", imei);
//        content = QString::fromLocal8Bit(imei);
//        tableModelQR->setFileNamebyFilePath("IMEI", content);
//        content.prepend("IMEI: ");
//        qrcodeStr.append(content);
//        qrcodeStr.append("\n");
//        content.clear();

        /*
        memset(buf, 0, 35);//IMSI
        for(i=0; i<15; i++)
        {
            buf[i] = *(readMsg+offset+i);
            //            printf("qrcode IMSI=%d\n", buf[i]);
            //            fflush(stdout);
        }
        offset=offset+15;
        //        printf("IMSI buf =%s", buf);
        //        fflush(stdout);
        str_imsi = buf;
        if(str_imsi=="")
        {
            emit errorCode("IMSI", 1);
        }
        tableModel->setFileNamebyFilePath("IMSI", buf);
        content = QString::fromLocal8Bit(buf);
        tableModelQR->setFileNamebyFilePath("IMSI", content);
        content.prepend("IMSI: ");
        qrcodeStr.append(content);
        qrcodeStr.append("\n");
        content.clear();*/

        //序列号
        /*
        memset(buf, 0, 35);
        for(i=0; i<17; i++)
        {
            buf[i] = *(readMsg+offset+i);
        }
        offset=offset+30;*/
        content = QString::fromLocal8Bit(buf);
//        qrcodeStr.append("SN: ");
        qrcodeStr.append(m_serial);
        qrcodeStr.append("\n");
        content.clear();

        /*
        memset(buf, 0, 35);//供应商零件
        for(i=0; i<16; i++)
        {
            buf[i] = *(readMsg+offset+i);
            printf("qrcode 供应商零件=%d\n", buf[i]);
            fflush(stdout);
        }
        offset=offset+16;
        content = QString::fromLocal8Bit(buf);
        qDebug("供应商零件 content = %s", qPrintable(content));
*/

        /*
        qrcodeStr.append("P/N: ");
        qrcodeStr.append(pn_num.toLatin1().data());
        qrcodeStr.append("\n");*/

//        tableModelQR->setFileNamebyFilePath("产品名称", p_name);
//        tableModelQR->setFileNamebyFilePath("产品型号", p_model);
//        tableModelQR->setFileNamebyFilePath("软件版本号", sw_str.toLocal8Bit());
//        tableModelQR->setFileNamebyFilePath("硬件版本号", hw);
        tableModelQR->setFileNamebyFilePath("SN", m_serial);
//        tableModelQR->setFileNamebyFilePath("P/N", pn_num);
//        tableModelQR->setFileNamebyFilePath("SIM/N",sim_num.toLocal8Bit());
    }
    DEBUG_PARAM("qrcodeStr = ", qrcodeStr.data());
}

void FortuneThread::handleSetFile() 
{
    if( !analyze_section_data() ) 
    {
        emit errorCode("配置", 190);//接收的数据错误
    }
    uint8_t tag;
    uint16_t taglen;
    uint8_t tagbody;
    tag = *(uint8_t*)(readMsg+5);
    taglen = *(uint16_t*)(readMsg+6);
    tagbody = *(uint8_t*)(readMsg+8);
    DEBUG_PARAM("tagbody:", tagbody);
    if(tag == 0x61 && tagbody == 0x01)
    {
        DEBUGLOG;
        //emit nextOne();
    }
    else
    {
        stop = true;
        emit errorCode("配置", 190);
    }
}

void FortuneThread::handleCan()
{
    mainwindow->can_dbus_interface->canwrite(id_test, 1);
    DEBUGLOG;
    sleep(5);
    if(can_flag[3]==1)
    {
        DEBUGLOG;
        stop = true;
        emit errorCode("CAN通讯", 8);
    }
    else if(can_flag[1]==1)
    {
        DEBUGLOG;
        stop = true;
        emit errorCode("CAN通讯", 81);
    }
    else if(can_flag[2]==1)
    {
        DEBUGLOG;
        stop = true;
        emit errorCode("CAN通讯", 82);
    }/*
    else if(can_flag[0]==1)
    {
        DEBUGLOG;
        stop = true;
        emit errorCode("CAN唤醒", 83);
    }*/
    else
    {
        DEBUGLOG;
        //emit nextOne();
        read = true;
    }
}

void FortuneThread::handleCanAwake()
{
    mainwindow->can_dbus_interface->canwrite(id_test, 1);
    DEBUGLOG;
    sleep(5);
    if(can_flag[0]==1)
    {
        DEBUGLOG;
        stop = true;
        emit errorCode("CAN唤醒", 83);
    }
    else
    {
        DEBUGLOG;
        //emit nextOne();
        read = true;
    }
}
//eventlist_page.visible = false;
void FortuneThread::handle6AxisSensor() 
{
    if( !analyze_section_data() )
    {
        emit errorCode("6轴传感器", 9);
    }
    uint8_t tag;
    uint16_t taglen;
    uint8_t tagbody;
    tag = *(uint8_t*)(readMsg+5);
    taglen = *(uint16_t*)(readMsg+6);
    tagbody = *(uint8_t*)(readMsg+8);
    DEBUG_PARAM2("tag:", tag, "tagbody:", tagbody);
    if(tag == 0x64 && tagbody == 0x01)
    {
        DEBUGLOG;
        //emit nextOne();
    }
    else
    {
        DEBUG_CHAR("6轴传感器错误");
        stop = true;
        emit errorCode("6轴传感器", 9);
    }
}

void FortuneThread::handleWIFI() 
{
    if( !analyze_section_data() ) 
    {
        emit errorCode("WIFI", 110);
    }
    uint8_t name_len = 0;
    uint8_t passw_len = 0;
    char wifi_name[20]={0};
    char wifi_passw[20]={0};
    uint8_t tag;
    tag = *(uint8_t*)(readMsg+5);
    if( tag==0x66 )
    {
        name_len = *(uint8_t*)(readMsg+6);
        qDebug("wifi name_len =%d", name_len);
        memcpy(wifi_name, readMsg+7, name_len);
        passw_len = *(uint8_t*)(readMsg+7+name_len);
        qDebug("wifi passw_len =%d", passw_len);
        memcpy(wifi_passw, readMsg+8+name_len, passw_len);
        DEBUG_PARAM("wifi_name", wifi_name);
        DEBUG_PARAM("wifi_passw:", wifi_passw);
        char buf_ssid[1024]={0};
        FILE* ptr = popen("iwlist scanning | grep ESSID", "r");
        fread(buf_ssid, 1, 1024, ptr);
        QString str = buf_ssid;
        DEBUG_PARAM("str_ssid:", str);
        if(str.contains(wifi_name))
        {
            DEBUGLOG;
            emit show_wifi();
            //emit nextOne();
        }
        else
        {
            DEBUGLOG;
            stop = true;
            emit errorCode("WIFI", 110);
        }
        printf("wifi_name=%s\n", wifi_name);
        printf("wifi_passw=%s\n", wifi_passw);
        fflush(stdout);
    }
    else
    {
        stop = true;
        emit errorCode("WIFI", 110);
    }
}

void FortuneThread::handleIVIT()
{
    if( !analyze_section_data() ) 
    {
        emit errorCode("IVIT", 0);
    }
    uint8_t tag = *(uint8_t*)(readMsg+5);
    uint16_t taglen = *(uint16_t*)(readMsg+6);
    uint8_t tagbody = *(uint8_t*)(readMsg+8);
    DEBUG_PARAM2("tag:", tag, "tagbody:", tagbody);
    if(tag == 0x68 && tagbody == 0x01)
    {
        DEBUGLOG;
        //emit nextOne();
    }
    else
    {
        qDebug()<<"IVIT检测错误,tag:"<<tag<<"tagbody:"<<tagbody;
        stop = true;
        emit errorCode("IVIT", 0);
    }
}

void FortuneThread::handleEMMC()
{
    if( !analyze_section_data() ) 
    {
        emit errorCode("EMMC", 270);
    }
    uint8_t tag = *(uint8_t*)(readMsg+5);
    uint16_t taglen = *(uint16_t*)(readMsg+6);
    uint8_t tagbody = *(uint8_t*)(readMsg+8);
    DEBUG_PARAM2("tag:", tag, "tagbody:", tagbody);
    if(tag == 0x65 && tagbody == 0x01)
    {
        DEBUGLOG;
        //emit nextOne();
    }
    else
    {
        qDebug()<<"EMMC检测错误,tag:"<<tag<<"tagbody:"<<tagbody;
        stop = true;
        emit errorCode("EMMC", 270);
    }
}

void FortuneThread::handleCharge()
{
    if( !analyze_section_data() ) 
    {
        emit errorCode("充电", 280);
    }
    uint8_t tag = *(uint8_t*)(readMsg + 5);
    uint16_t taglen = *(uint16_t*)(readMsg + 6);
    uint8_t tagbody = *(uint8_t*)(readMsg + 8);
    DEBUG_PARAM2("tag:", tag, "tagbody:", tagbody);
    if(tag == 0x6F && tagbody == 0x01)
    {
        DEBUGLOG;
        //emit nextOne();
    }
    else
    {
        qDebug()<<"Charge检测错误,tag:"<<tag<<"tagbody:"<<tagbody;
        stop = true;
        emit errorCode("充电", 280);
    }
}

void FortuneThread::handleIVI() 
{
    QString str;
    char buf[1024];
    memset(buf, 0 , 1024);
    DEBUGLOG;
    FILE* fl ;
    int count=1;
    while(count--)
    {
        fl = popen("ping -w 6 www.baidu.com -c 3", "r");//ping www.baidu.com -c 1
        memset(buf, 0, 1024);
        fread(buf, 1, sizeof(buf), fl);
        str.append(buf);
        sleep(2);
        DEBUG_PARAM("ivi buf: ", buf);
    }
    if( str.contains("time=") )
    {
        DEBUGLOG;
        //emit nextOne();
        read = true;
    }
    else
    {
        DEBUGLOG;
        stop = true;
        emit errorCode("网络连接", 120);
    }
}

void FortuneThread::handleAirBag()
{
    /*DEBUG_PARAM("m_playFinished:",mainwindow->m_playFinished);
    if(!mainwindow->m_playFinished)
    {
        DEBUGLOG;
        static int flag = 1;
        if(flag)
        {
            flag = 0;
            emit mainwindow->sigBroadcastRing();
        }
        //handleAirBag();
    }*/
    FILE* fl;
    if( !analyze_section_data() ) 
    {
        emit errorCode("SOS", 130);//接收的数据错误
    }
    uint8_t tag;
    uint16_t taglen;
    uint8_t tagbody;
    tag = *(uint8_t*)(readMsg+5);
    taglen = *(uint16_t*)(readMsg+6);
    tagbody = *(uint8_t*)(readMsg+8);
    DEBUG_PARAM2("tag:", tag, "tagbody:", tagbody);
    if(tag == 0x6A && tagbody == 0x01)
    {
        //emit ring_pickdown();
        fl = popen("echo 1 > /sys/devices/platform/soc/481c0000.adc-keys/tbox_current_detection/pwm", "r");
        pclose(fl);
        //emit mainwindow->m_pCallInterface->broadcastRing();
//        DEBUGLOG;
//        player->setMedia(QMediaContent(QUrl::fromLocalFile("/run/media/usb/test.mp3")));//run/media/usb/
//        player->setVolume(80);//1200
//        player->play();
//        sleep(3);
//        player->stop();
    }
    else
    {
        stop = true;
        emit errorCode("SOS", 130);
    }
}

void FortuneThread::handleGPSOpen()
{
    if( !analyze_section_data() ) 
    {
        emit errorCode("GPS天线检测", 140);
    }
    uint8_t tag;
    uint16_t taglen;
    uint8_t tagbody;
    tag = *(uint8_t*)(readMsg+5);
    taglen = *(uint16_t*)(readMsg+6);
    tagbody = *(uint8_t*)(readMsg+8);
    DEBUG_PARAM2("tag:", tag, "tagbody:", tagbody);
    if(tag == 0x6B && tagbody == 0x01)
    {
        DEBUGLOG;
        //emit nextOne();
    }
    else
    {
        stop = true;
        emit errorCode("GPS天线检测", 140);
    }
}

void FortuneThread::handleGPSSignal() 
{
    int i;
    int gt30=0;
    uint8_t pcs=0;
    uint8_t tag;
    uint16_t taglen;
    uint8_t number;
    uint8_t strength;
    tag = *(uint8_t*)(readMsg+5);//0x6D
    taglen = *(uint16_t*)(readMsg+6);
    pcs = *(uint8_t*) (readMsg+8);
    DEBUG_PARAM2("tag:", tag, "pcs:", pcs);
    if( tag == 0x6D && pcs>0 )
    {
        for(i=0; i<pcs; i++)
        {
            number = 0;
            strength = 0;
            number = *(uint8_t*) ( readMsg+9+ 2*i );
            strength = *(uint8_t*) ( readMsg+10+ 2*i );
            if(strength>20)
            {
                gt30++;
            }
            qDebug("number=====%d", number);
            qDebug("strength=====%d", strength);
            emit gpsBarData((int)number, (int)strength);
        }
        qDebug("gt30=====%d", gt30);
        QString num;
        char buf[2];
        sprintf(buf, "%d", (pcs++));
        num =buf;
        emit gps_start_num(num);
    }
    else
    {
        stop = true;
        emit errorCode("GPS信号", 150);
    }

    if( gt30>=3 )
    {
        DEBUGLOG;
        //emit nextOne();
    }
    else //卫星信号/个数不足
    {
        stop = true;
        emit errorCode("GPS信号", 150);
    }
}

void FortuneThread::handleMajorPower() 
{
    if( !analyze_section_data() )
    {
        emit errorCode("主电源", 160);
    }
    uint8_t tag;
    uint16_t taglen;
    uint8_t tagbody;
    tag = *(uint8_t*)(readMsg+5);
    taglen = *(uint16_t*)(readMsg+6);
    tagbody = *(uint8_t*)(readMsg+8);
    DEBUG_PARAM2("tag:", tag, "tagbody:", tagbody);
    if(tag == 0x6E && tagbody == 0x01)
    {
        DEBUGLOG;
        //emit nextOne();
    }
    else
    {
        stop = true;
        emit errorCode("主电源", 160);
    }
}

void FortuneThread::handleACCOFF() 
{
    if( !analyze_section_data() )
    {
        emit errorCode("ACC OFF", 170);
    }
    uint8_t tag;
    uint16_t taglen;
    uint8_t tagbody;
    tag = *(uint8_t*)(readMsg+5);
    taglen = *(uint16_t*)(readMsg+6);
    tagbody = *(uint8_t*)(readMsg+8);
    DEBUG_PARAM2("tag:", tag, "tagbody:", tagbody);
    if( tag == 0x70 && tagbody == 0x01 && detect_dark_current() )
    {
        DEBUGLOG;
        //emit qrcode();  
        //mainwindow->update_db_flag(true);
        //read = true;
    }
    else
    {
        stop = true;
        emit errorCode("ACC OFF", 170);
    }
    disable_12V();
}

bool FortuneThread::detect_dark_current()//20秒以后每隔1秒读取一次暗电流，读3次，有2次小于120；成功
{
    sleep(30);
    for(int i=0;i<6;i++)
    {
        if(detect_dark_current_read())
            return true;
    }
    return false;
}

bool FortuneThread::detect_dark_current_read()
{
    FILE *pstr; char cmd[128],buff[512];
    memset(cmd, 0,128);

    sprintf(cmd, "cat /sys/devices/platform/soc/481c0000.adc-keys/tbox_current_detection/tbox_current_detection");
    int num_flag=0;
    int darck_current=0;
    for(int i=0; i<50; i++)
    {
        pstr=popen(cmd, "r");
        if(pstr==NULL)
        {
            DEBUG_CHAR("open failed!");
        }
        memset(buff, 0, 512);
        fgets(buff, 512 ,pstr);
        darck_current = atoi(buff);
        DEBUG_PARAM("darcK_curr:::::::::::::::::::::::", darck_current);
        num_flag+=darck_current;
        pclose(pstr);
        QThread::msleep(200);
    }
    if(num_flag/50<=100)
    {
        DEBUGLOG;
        return true;
    }
    return false;
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
//读取U盘的数据并封包
void FortuneThread::readDisk()
{
    DEBUGLOG;
    if( access("/run/media/usb/1.ini", 0) == 0 )
    {
        DEBUG_CHAR("1.ini file exist!!!");
        //power
        char cmd[128]={0};
        char buf_power[8]={0};
        double power_val=0;
        sprintf(cmd, "cat /sys/devices/platform/soc/481c0000.adc-keys/tbox_current_detection/BAT");
        FILE* fl = popen(cmd, "r");
        if(fl==NULL)
        {
            printf("open file fail\n");
        }
        fgets(buf_power, 512 ,fl);
        power_val = atof(buf_power)/100;
        DEBUG_PARAM("buf_power:", buf_power);
        DEBUG_PARAM("power_val:", power_val);
        if((13.5<power_val) && (power_val<18.0))
        {
            DEBUGLOG;
            emit power_signal(power_val, true);
        }
        else
        {
            DEBUGLOG;
            emit power_signal(power_val, false);
        }
        pclose(fl);
        
        sk = setting->value("SK/sk").toString();
        DEBUG_PARAM("sk:", sk);
        tBoxSN1 = setting->value("TBoxSN1/sn1").toString();
        DEBUG_PARAM("TBoxSN1:", tBoxSN1);
        tBoxSN2 = setting->value("TBoxSN2/sn2").toString();
        DEBUG_PARAM("TBoxSN2:", tBoxSN2);
        if(tBoxSN2.length() == 2)
        {
            if(QString::compare("00", tBoxSN2) == 0)
            {
                DEBUGLOG;
                vehicle="通用型";
            }
            else if(QString::compare("01", tBoxSN2) == 0)
            {
                DEBUGLOG;
                vehicle="EV200";
            }
            else if(QString::compare("02", tBoxSN2) == 0)
            {
                DEBUGLOG;
                vehicle="A6";
            }
            else if(QString::compare("03", tBoxSN2) == 0)
            {
                DEBUGLOG;
                vehicle="EC3";
            }
            else
            {
                vehicle=tBoxSN2;
            }
            DEBUG_PARAM("vehicle:", vehicle);
            tBoxSN3 = setting->value("TBoxSN3/sn3").toString();
            DEBUG_PARAM("SN3:", tBoxSN3);
            btName = tBoxSN3.mid(3);
            DEBUG_PARAM("btName/tBoxSN3:", btName);
        }
        else
        {
            vehicle = setting->value("vehicle/modle").toString();
            DEBUG_PARAM("vehicle:", vehicle);
        }
        
        phone_number = setting->value("Phone/number").toString();
        DEBUG_PARAM("phone_number:", phone_number);
        p_name = setting->value("NAME/pname").toString();
        DEBUG_PARAM("p_name:", p_name);
        p_model = setting->value("Version/pversion").toString();
        DEBUG_PARAM("p_model:", p_model);
        pn_num = setting->value("PN/pn").toString();
        DEBUG_PARAM("pn_num:", pn_num);
        
        emit setTitleText(mainwindow->m_sProName);
    }
    else 
    {
        stop = true;
        emit udisk_disconnect();
        DEBUG_CHAR("1.ini file no exist!!!");
    }
    DEBUGLOG;
    tableModel->setFileNamebyFilePath("车型号", vehicle);
}
//读取U盘的数据并封包
void FortuneThread::readDiskIMEI()
{
    DEBUGLOG;
    if( access("/run/media/usb/1.ini", 0) == 0 )
    {
        DEBUG_CHAR("1.ini file exist!!!");
        //power
        char cmd[128]={0};
        char buf_power[8]={0};
        double power_val=0;
        sprintf(cmd, "cat /sys/devices/platform/soc/481c0000.adc-keys/tbox_current_detection/BAT");
        FILE* fl = popen(cmd, "r");
        if(fl==NULL)
        {
            printf("open file fail\n");
        }
        fgets(buf_power, 512 ,fl);
        power_val = atof(buf_power)/100;
        DEBUG_PARAM("power_val:", power_val);
        if((13.5<power_val) && (power_val<18.0))
        {
            DEBUGLOG;
            emit power_signal(power_val, true);
        }
        else
        {
            DEBUGLOG;
            emit power_signal(power_val, false);
        }
        pclose(fl);
        
        sk = setting->value("SK/sk").toString();
        qDebug("SK=%s", qPrintable(sk));
        tBoxSN1 = setting->value("TBoxSN1/sn1").toString();
        DEBUG_PARAM("TBoxSN1:", tBoxSN1);
        tBoxSN2 = setting->value("TBoxSN2/sn2").toString();
        DEBUG_PARAM("TBoxSN2:", tBoxSN2);
        if(QString::compare("00", tBoxSN2) == 0)
        {
            DEBUGLOG;
            vehicle="通用型";
        }
        else if(QString::compare("01", tBoxSN2) == 0)
        {
            DEBUGLOG;
            vehicle="EV200";
        }
        else if(QString::compare("02", tBoxSN2) == 0)
        {
            DEBUGLOG;
            vehicle="A6";
        }
        else if(QString::compare("03", tBoxSN2) == 0)
        {
            DEBUGLOG;
            vehicle="EC3";
        }
        else
        {
            vehicle=tBoxSN2;
        }
        DEBUG_PARAM("vehicle:", vehicle);
        tBoxSN3 = setting->value("TBoxSN3/sn3").toString();
        btName = tBoxSN3.mid(3);
        DEBUG_PARAM("btName/tBoxSN3:", btName);
        phone_number = setting->value("Phone/number").toString();
        DEBUG_PARAM("phone_number:", phone_number);
        p_name = setting->value("NAME/pname").toString();
        DEBUG_PARAM("p_name:", qPrintable(p_name));
        p_model = setting->value("ProModel/pmodel").toString();
        DEBUG_PARAM("p_model:", p_model);
        
        emit setTitleText(mainwindow->m_sProName);
    }
    else
    {
        stop = true;
        emit udisk_disconnect();
        DEBUG_CHAR("1.ini file no exist!!!");
    }
    DEBUGLOG;
    tableModel->setFileNamebyFilePath("车型号", vehicle);
}

void FortuneThread::tag_pack( uint8_t cmd, uint8_t tag, uint16_t tlvLen)
{
    DEBUGLOG;
    switch(cmd)
    {
    case 0x01: //send mode tag:0 cfg;1:detecting
    {
        memcpy(buf+offset, &tag, sizeof(tag));
        offset += sizeof(tag);
    }
        break;
    case 0x02://send config data
    {
        if(tag == 0x01) //配置文件
        {
            DEBUG_CHAR("generating configuration files...");
            memcpy(buf+offset, &tag, 1);
            offset += 1;
            tlvLen = qFromBigEndian(tlvLen);
            memcpy(buf+offset, &tlvLen, 2);
            offset += 2;

            uint8_t len = 30;//序列号
            memcpy(buf+offset, &len, 1);
            offset += 1;
            memcpy(buf+offset, m_serial.toLatin1().data(), 30);//序列号
            offset += len;

            len = 6;//sk
            memcpy(buf+offset, &len, 1);
            offset += 1;
            memcpy(buf+offset, sk.toLatin1().data(), len);
            offset +=  len;

            len =  1;//power
            uint8_t power_pos;
            memcpy(buf+offset, &len, 1);
            offset += 1;
            if(m_power == "12")
            {
                DEBUG_PARAM("power_pos:", power_pos);
                power_pos = 1;
                memcpy(buf+offset, &power_pos, len);
            }
            else if(m_power == "24")
            {
                DEBUG_PARAM("power_pos:", power_pos);
                power_pos = 2;
                memcpy(buf+offset, &power_pos, len);
            }
            offset +=  len;

            len =  64;//rootKey
            memcpy(buf+offset, &len, 1);
            offset += 1;
            memcpy(buf+offset, mainwindow->m_rootKey.toLatin1().data(), len);
            offset +=  len;
        }
        else if(tag == 0x0A) //安全气囊
        {
            memcpy(buf+offset, &tag, 1);
            offset += 1;
            tlvLen = qFromBigEndian(tlvLen);
            memcpy(buf+offset, &tlvLen, 2);
            offset += 2;
            DEBUG_PARAM("airbag_phone_number:", phone_number);
            memcpy(buf+offset, phone_number.toLatin1().data(), 11);
            DEBUG_PARAM("buf:", (buf+offset));
            offset += 11;
        }
        else
        {
            memcpy(buf+offset, &tag, 1);
            offset += 1;
        }
    }
        break;
    }
}

void FortuneThread::tag_packIMEI( uint8_t cmd, uint8_t tag, uint16_t tlvLen)
{
    DEBUGLOG;
    switch(cmd)
    {
    case 0x01: //send mode tag:0 cfg;1:detecting
    {
        memcpy(buf+offset, &tag, sizeof(tag));
        offset += sizeof(tag);
    }
        break;
    case 0x02://send config data
    {
        if(tag == 0x01) //配置文件
        {
            uint8_t len;
            qDebug()<<"配置文件生成中";
            memcpy(buf+offset, &tag, 1);
            offset += 1;
            tlvLen = qFromBigEndian(tlvLen);
            memcpy(buf+offset, &tlvLen, 2);
            offset += 2;

            len = 17;//序列号
            memcpy(buf+offset, &len, 1);
            offset += 1;
            DEBUG_PARAM("m_serial:", m_serial);
            memcpy(buf+offset, m_serial.toLatin1().data(), 17);//序列号
            offset += len;
        }
        else if(tag == 0x0A) //安全气囊
        {
            memcpy(buf+offset, &tag, 1);
            offset += 1;
            tlvLen = qFromBigEndian(tlvLen);
            memcpy(buf+offset, &tlvLen, 2);
            offset += 2;
            DEBUG_PARAM("airbag_phone_number:", phone_number);
            memcpy(buf+offset, phone_number.toLatin1().data(), 11);
            DEBUG_PARAM("buf:", (buf+offset));
            offset += 11;
        }
        else
        {
            memcpy(buf+offset, &tag, 1);
            offset += 1;
        }
    }
        break;
    }
}

void FortuneThread::tag_packNew(uint8_t cmd, uint8_t tag, uint16_t tlvLen)
{
    DEBUGLOG;
    QString sep = "\0";
    switch(cmd)
    {
    case 0x01: //send mode tag:0 cfg;1:detecting
    {
        memcpy(buf+offset, &tag, sizeof(tag));
        offset += sizeof(tag);
    }
        break;
    case 0x02://send config data
    {
        if(tag == 0x01) //配置文件
        {
            DEBUG_CHAR("generating configuration files...");
            memcpy(buf+offset, &tag, 1);
            offset += 1;
            tlvLen = qFromBigEndian(tlvLen);
            memcpy(buf+offset, &tlvLen, 2);
            offset += 2;
            
            //serial
            memcpy(buf+offset, m_serial.toLatin1().data(), m_serial.length());//序列号
            offset += m_serial.length();
            memcpy(buf+offset, sep.toLatin1().data(), 1);
            offset += 1;
            
            //sk
            if(!sk.isEmpty())
            {
                memcpy(buf+offset, sk.toLatin1().data(), sk.length());
                offset += sk.length();
            }
            memcpy(buf+offset, sep.toLatin1().data(), 1);
            offset += 1;

            //power
            /*
            uint8_t power_pos = 0;
            if(m_power == "12")
            {
                DEBUG_PARAM("power_pos:", power_pos);
                power_pos = 1;
                memcpy(buf+offset, &power_pos, 1);
            }
            else if(m_power == "24")
            {
                DEBUG_PARAM("power_pos:", power_pos);
                power_pos = 2;
                memcpy(buf+offset, &power_pos, 1);
            }
            offset += 1;*/
            memcpy(buf+offset, sep.toLatin1().data(), 1);
            offset += 1;
            
            //rootkey
            if(!mainwindow->m_rootKey.isEmpty())
            {
                memcpy(buf+offset, mainwindow->m_rootKey.toLatin1().data(), mainwindow->m_rootKey.length());
                offset += mainwindow->m_rootKey.length();
            }
            memcpy(buf+offset, sep.toLatin1().data(), 1);
            offset += 1;
            
            //vpn
            QString str = "0";
            QString str1 = "1";
            int iVpn = m_vpn.left(2).toInt();
            DEBUG_PARAM2("vpn", m_vpn.right(2), " int vpn:", m_vpn.left(2).toInt());
            if(iVpn > 0)
            {
                str1 = "1";
            }
            else if(iVpn == 0)
            {
                str1 = "0";
            }
            DEBUG_PARAM("str:", str1);
            memcpy(buf+offset, str.toLatin1().data(), 1);
            offset += 1;
            memcpy(buf+offset, str.toLatin1().data(), 1);
            offset += 1;
            memcpy(buf+offset, str1.toLatin1().data(), 1);
            offset += 1;
            
//            for(int i=0; i<sizeof(buf)/sizeof(buf[0]); ++i)
//            {
//                DEBUG_PARAM("buf:", *(buf+i));
//            }
        }
        else if(tag == 0x0A) //安全气囊
        {
            memcpy(buf+offset, &tag, 1);
            offset += 1;
            DEBUG_PARAM("airbag_phone_number:", phone_number);
            memcpy(buf+offset, phone_number.toLatin1().data(), 11);
            offset += 11;
            memcpy(buf+offset, sep.toLocal8Bit().data(), 1);
            offset += 1;
        }
        else
        {
            memcpy(buf+offset, &tag, 1);
            offset += 1;
        }
    }
        break;
    }
}
//sendMsg(0x02, 0x01, 0x00, 0x00);
void FortuneThread::sendMsg(uint16_t msgBodyLen, uint8_t cmd, uint8_t tag, uint16_t tlvLen) 
{
    offset = 0;
    memset(buf, 0, sizeof(buf));
    uint16_t head = 0x55AA;
    uint16_t crc_m = 0x0000;
    uint8_t tail = 0x0A;
    qint64 data_len;
    head = qFromBigEndian(head);
    msgBodyLen = qFromBigEndian(msgBodyLen);
    crc_m = qFromBigEndian(crc_m);

    memcpy(buf, &head, sizeof(head));
    offset +=2;
    memcpy(buf+offset, &msgBodyLen, 2);
    offset += 2;
    memcpy(buf+offset, &cmd, 1);
    offset += 1;
    
    tag_packNew(cmd, tag, tlvLen);
    /*if(mainwindow->m_bSIM && mainwindow->m_sProName == PRO_NAME)
    {
        tag_pack( cmd, tag,  tlvLen);
    }
    else if(mainwindow->m_bSIM && mainwindow->m_sProName != PRO_NAME)
    {
        tag_packNew(cmd, tag,  tlvLen);
    }
    else if(!mainwindow->m_bSIM)
    {
        tag_packIMEI(cmd, tag, tlvLen);
    }*/
    
    memcpy(buf+offset, &crc_m, 2);
    offset += 2;
    memcpy(buf+offset, &tail, 1);
    offset += 1;
    if(socket_m->waitForConnected())
    {
        data_len =  socket_m->write(buf, offset);
        if( !socket_m->flush() )
            DEBUG_CHAR("send data fail!!!");
        DEBUG_PARAM("send data_len:", (int)data_len);
    }
    else
    {
        DEBUGLOG;
        stop = true;
        emit device_disconnect();
        DEBUG_CHAR("连接不成功不发送数据");
    }
}

FortuneThread::FortuneThread(): QQuickImageProvider(QQuickImageProvider::Pixmap)
{
    db_init_flag = false;
    m_serial = "";
    tBoxSN1= "";
    tBoxSN2 = "";
    tBoxSN3= "";
    phone_number="";
    stop = false;
    read = false;
    write_flag =true;
    change_sn = false;
    sos_flag = true;
    btName="";
    bt_flag = false;
    m_bt_flag = false;
    m_checkItem = "";
    hwIMEI = "";
    lock_flag = true;
    unlock_flag = true;
    m_vpn = "";
    m_bA5 = false;
    m_bTB = false;
    m_power = "";
}

FortuneThread::~FortuneThread()
{
    mutex.lock();
    quit = true;
    cond.wakeOne();
    mutex.unlock();
    wait();
}

void FortuneThread::thread_eixt()
{
    this->exit(0);
}

void MainWindow::onbroadTest(int value)
{
    DEBUG_CHAR("onbroadTest is running!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    for(int i=0; i<4; i++)
    {
        qDebug("can_flag[%d]=%d", i, thread_m->can_flag[i]);
    }
    DEBUG_PARAM("can_value:", value);

    if(value== 0x00)
    {
        thread_m->can_flag[3] = 1;
    }
    else if((value== 0x11) || (value == 0x12) || (value == 0x21))//wake up
    {
      DEBUGLOG;
      thread_m->can_flag[0] = 1;
    }
    else if((value&0x0F) == 0)//can1
    {
        DEBUGLOG;
       thread_m->can_flag[1] = 1;
    }
    else if((value&0xF0) == 0)//can2
    {
        DEBUGLOG;
       thread_m->can_flag[2] = 1;
    }
    for(int i=0; i<4; i++)
    {
        qDebug("---can_flag[%d]=%d", i, thread_m->can_flag[i]);
    }
}

void FortuneThread::stop_flag()
{
    stop = true;
}

void FortuneThread::initListView()
{
    DEBUGLOG;
    if(access("/run/media/usb/1.ini", 0) == 0 )
    {
        DEBUG_CHAR("1.ini file exist!!!");
        setting = new QSettings(QString::fromStdString("/run/media/usb/1.ini"), QSettings::IniFormat);
        setting->setIniCodec("UTF-8");
        QString checkItem = setting->value("CfgItem/value").toString();
        DEBUG_PARAM("checkItem:", checkItem);
        bool ok;
        m_checkItem = QString("%1").arg(checkItem.toInt(&ok, 16)&0xFFFFFF, 4*checkItem.length(), 2, QLatin1Char('0'));
        DEBUG_PARAM("checkItem:", m_checkItem);
        
        m_vpn = setting->value("VPN/value").toString();
        QString vpn = QString("%1").arg(m_vpn.toInt(&ok, 16)&0xFFFFFF, 4*checkItem.length(), 2, QLatin1Char('0'));
        if(m_vpn.left(2) == "00")
        {
            vpn.prepend("0000");
        }
        DEBUG_PARAM2("vpn:", m_vpn, "vpn:", vpn);
        for(int i=0; i<8; ++i)
        {
            if(vpn.at(16+i).digitValue() == 1 && vpn.at(i).digitValue() == 0)
            {
                m_bA5 = true;
            }
            else if(vpn.at(16+i).digitValue() == 1 && vpn.at(i).digitValue() == 1)
            {
                m_bTB = true;
            }
        }
        DEBUG_PARAM2("A5 ivi:", m_bA5, "TBOX ivi:", m_bTB);
    }
    
//    QString str[] = {"[1] 配置", "[2] CAN通讯", "[3] 网络连接",
//                     "[4] 主电电源测试", "[5]BLE通信检测", "[6]NFC",
//                     "[7]BLE连接检测", "[8]常闭测试", "[9]常开测试",
//                     "[10]动力开关检测", "[11]寻车检测", "[12] GPS天线检测",
//                     "[13] GPS信号", "[14] ACC OFF", "", ""};
//    QString str[] = {"[1] 配置", "[2] CAN通讯", "[3] 6轴传感器",  "[4] WIFI",
//                       "[5] 网络连接", "[6] SOS", "[7] GPS天线检测", "[8] GPS信号", 
//                     "[9] 主电电源测试", "[10] ACC OFF", "", ""};
    
    FileListItem item;
    QString str[] = {"[01] 配置", "CAN通讯", "CAN唤醒", "6轴传感器", "WIFI", "网络连接(A5)",
                     "网络连接(TBOX)", "EMMC", "充电检测", "SOS", "GPS天线检测", "GPS信号", 
                     "主电电源测试", "BLE通信检测", "BLE连接检测", "NFC", "常闭测试", "常开测试", 
                     "动力开关检测", "寻车检测", "ACC OFF", "", ""};
    item = FileListItem(str[0], "未测试", 0 );
    listModel->addFileListItem(item);
    int index = 1;
    QString strIndex;
    for(int i=1; i<(COUNT_CHECK-2); i++) 
    {
        if(i<=m_checkItem.size() && m_checkItem.at(i-1).digitValue() == 1)
        {
            if(i == 5 && !m_bA5)
            {
                DEBUGLOG;
                continue;
            }
            if(i == 6 && !m_bTB)
            {
                DEBUGLOG;
                continue;
            }
            if((index+1) < 10)
            {
                strIndex = QString("0%1").arg(index+1);
            }
            else
            {
                strIndex = QString("%1").arg(index+1);
            }
            item = FileListItem(QString("[%1] %2").arg(strIndex).arg(str[i]), "未测试", index);
            listModel->addFileListItem(item);
            index++;
        }
    }
    item = FileListItem(str[COUNT_CHECK-2], "未测试", index );
    listModel->addFileListItem(item);
    index++;
    item = FileListItem(str[COUNT_CHECK-1], "未测试", index );
    listModel->addFileListItem(item);
    for(int i=0;i<listModel->rowCount(); ++i)
    {
        DEBUG_PARAM2("index:", i, "listmodel:", listModel->getFilePathByIndex(i));
    }
}

void FortuneThread::init()
{
    DEBUGLOG;
    sleep(20);
    system("dhclient usb0");
    FILE* ptr;
    QString str_usb0;
    char check_usb0[254];
    int count=0;
    while(1)
    {
        count++;
        str_usb0.clear();
        memset(check_usb0, 0, 254);
        ptr = popen("ifconfig usb0", "r");
        fread(check_usb0, 1, 254, ptr);
        str_usb0 = check_usb0;
//        if(str_usb0.contains("usb0"))
        DEBUG_PARAM("str_usb0:", str_usb0);
        if(str_usb0.contains("usb0") && str_usb0.contains("192.168.100"))
        {
            DEBUGLOG;
            break;
        }
        else
        {
            system("dhclient usb0");
        }
        if(count==10)
        {
            DEBUG_PARAM("count", count);
            stop = true;
//            emit device_disconnect();
            break;
        }
        sleep(1);
        DEBUGLOG;
    }
    pclose(ptr);

    DEBUGLOG;
//    QString str[] = {"need_set_mode", "qrcode", "send_set_file", "can_comm", "ivi",
//                     "major_power", "btcom","nfc", "btCon", "lock",
//                     "unlock", "outage", "lamp", "gps_open", "gps_signal",
//                     "acc_off"};
    QString str[] = {"need_set_mode", "qrcode", "send_set_file", "can_comm", "can_awake",
                     "6axis_sensor", "wifi",  "ivi", "iviT", "emmc", "charge", "air_bag",
                     "gps_open", "gps_signal", "major_power", "btcom", "btCon", "nfc",
                     "lock", "unlock", "outage", "lamp", "acc_off"};
    m_vsTestName.clear();
    for(int i=0; i<3; ++i)
    {
        m_vsTestName.append(str[i]);
    }
    for(int i=3; i<COUNT_CHECK; i++)
    {
        if((i-3)<m_checkItem.size() && m_checkItem.at(i-3).digitValue() == 1)
        {
            if(i == 7 && !m_bA5)
            {
                continue;
            }
            if(i == 8 && !m_bTB)
            {
                continue;
            }
            m_vsTestName.append(str[i]);
        }
    }
    for(int i=0; i<m_vsTestName.count(); ++i)
    {
        DEBUG_PARAM2("index:", i, "testname:", m_vsTestName.at(i));
    }
    
    DEBUGLOG;
    int connect_num=0;
    bool socket_connect = false;
    socket_m = new QTcpSocket;
    connect(socket_m, SIGNAL(readyRead()), this, SLOT(read_data()));
    do{
        if( !socket_m->waitForConnected(1000)) 
        {
            socket_m->connectToHost("192.168.100.1", 20001);
            if( socket_m->waitForConnected())
            {
                DEBUG_CHAR("socket connected");
                emit show_main_page();
                socket_connect = true;
            }
            else
            {
                socket_m->disconnectFromHost();
            }
        }
        sleep(2);
        connect_num++;
        DEBUG_PARAM("connect_num:",connect_num);
        if(connect_num>90)
        {
            DEBUGLOG;
            stop = true;
            emit device_disconnect();
            break;
        }
    }while( !socket_connect );
    DEBUGLOG;
    if(remove_flag)
    {
      DEBUGLOG;
      stop = true;
    }
}

void FortuneThread::getInfo(QString hostName, quint16 port)
{
    this->hostName = hostName;
    this->port = port;
}

void FortuneThread::on_start_thread()
{
    if(!this->isRunning())
    { 
        this->start();
    }
}

void FortuneThread::read_data()
{
    DEBUG_CHAR("read data");
    int data_len=0;
    QByteArray ba;
    memset(readMsg, 0, 256);
    ba = socket_m->readAll();
    data_len = ba.size();
    test_len = data_len;
    memcpy(readMsg, ba.data(), data_len);
    read = true;
}

void FortuneThread::run()
{
    DEBUGLOG;
    if( access("/run/media/usb", 0) != 0 )
    {
        DEBUGLOG;
        emit udisk_disconnect();
    }
#ifdef UPDATE
    if(access("/run/media/usb/upgrade", F_OK) == 0)//update file is exit
    {
        DEBUGLOG;
        sleep(5);
        emit mainwindow->thread_m->upgrade("系统正在升级中...");
        DEBUGLOG;
        sleep(5);
        mainwindow->thread_m->stop=true;
        mainwindow->mon1->deleteLater();;
        if(access("/run/media/usb/upgrade/upgrade.sh", F_OK) == 0)
        {  system("chmod 777 /run/media/usb/upgrade/upgrade.sh");
            system("source /run/media/usb/upgrade/upgrade.sh");
            sync();
            DEBUGLOG;
            emit mainwindow->thread_m->upgrade("升级完成,请拔出升级U盘");
            sleep(10);
            DEBUGLOG;
            mainwindow->deleteLater();
            system("reboot -f");
        }
    }
#endif

    DEBUGLOG;
    int index=0;
    int sosTime=0;
    int timeout=0;
    QString testname = "need_set_mode";
    bool bEnd = false;
    write_flag = true;
    stop = false;
    while(1)
    {
        msleep(500);
        ++timeout;
        
        if(testname == "gps_open")
        {
            sosTime++;
            if(sosTime==70)//for sos timeout
            {
                if(sos_flag)
                {
                    stop = true;
                    DEBUGLOG;
                    emit errorCode("SOS", 130);
                }
            }
        }
        if( write_flag &&  (!stop) )
        {
            DEBUG_CHAR("write in!");
            if(testname == "need_set_mode")
            {
                if(true)
                {
                    DEBUG_CHAR("request set mode...");
                    sendMsg(0x02, 0x01, 0x00, 0x00);
                }
                else
                {
                    read = true;
                }
            }
            else if(testname == "qrcode" )
            {
                if(true)
                {
                    DEBUG_CHAR("sending qrcode information...");
                    sendMsg(2, 0x02,  0x11,  0);
                }
                else
                {
                    read = true;
                }
            }
            else if(testname == "send_set_file")
            {
                if(true)
                {
                    DEBUG_CHAR("sending set file...");
                    sendMsg(173, 0x02, 0x01, 170);
                }
                else
                {
                    read = true;
                }
            }
            else if(testname == "can_comm")
            {
                DEBUG_CHAR("sending CAN communication...");
                handleCan();
            }
            else if(testname == "can_awake")
            {
                DEBUG_CHAR("sending CAN awake...");
                handleCanAwake();
            }
            else if(testname == "6axis_sensor")
            {
                DEBUG_CHAR("sending 6 axis sensor...");
                sendMsg(2, 0x02,  0x04,  0); 
            }
            else if(testname == "wifi")
            {
                DEBUG_CHAR("sending wifi...");
                sendMsg(2, 0x02,  0x06,  0);
            }
            /*else if(testname == "bt" )
            {
                sendMsg(2, 0x02,  0x07,  0);
                qDebug()<<"蓝牙发送中...";
            }*/
            else if(testname == "ivi" )
            {
                DEBUG_CHAR("sending IVI internet...");
                handleIVI();
            }
            else if(testname == "iviT")
            {
                DEBUG_CHAR("sending IVIT internet...");
                sendMsg(2, 0x02, 0x08, 0);
            }
            else if(testname == "emmc")
            {
                qDebug()<<"sending emmc...";
                sendMsg(2, 0x02,  0x05,  0);
            }
            else if(testname == "charge")
            {
                DEBUG_CHAR("sending charge...");
                sendMsg(2, 0x02, 0x0F, 0);
            }
            /*else if(testname == "apn" )
            {
                sendMsg(2, 0x02, 0x09,  0);
                qDebug()<<"登入指定服务器发送中...";
            }*/
            else if(testname == "air_bag" )
            {
                DEBUG_CHAR("sending SOS...");
                if(phone_number=="")
                {
                    emit errorCode("SOS", 130);
                }
                else
                {
                    DEBUGLOG;
                    sendMsg(14, 0x02,  0x0A,  11);
                }
            }
            else if(testname == "gps_open" )
            {
                DEBUG_CHAR("sending GPS open...");
                sendMsg(2, 0x02,  0x0B,  0);
            }
            else if(testname == "gps_signal" )
            {
                DEBUG_CHAR("sending GPS signal...");
                sendMsg(2, 0x02,  0x0D,  0);
            }
            /*else if(testname == "gps_short" )
            {
                //int byte, char* gpio_path, char* gpio_val, char* direction_path, char* dir_val, int dir_val_byte
                set_gpio_val( 112, true, 1);
                sendMsg(2, 0x02,  0x0C,  0);
                qDebug()<<"GPS短路发送中...";
            }*/
            else if(testname == "major_power" )
            {
                DEBUG_CHAR("sending major power test...");
                sendMsg(2, 0x02,  0x0E,  0);
            }
            /*else if(testname == "minor_power" )
            {//int byte, char* gpio_path, char* gpio_val, char* direction_path, char* dir_val, int dir_val_byte
                set_gpio_val( 6, true, 0 );
                sendMsg(2, 0x02,  0x0F,  0);
                qDebug()<<"备电电源测试发送中...";
            }*/
            else if(testname == "acc_off" )
            {
                DEBUG_CHAR("sending Acc off...");
                set_gpio_val(101, true, 0 );
                sendMsg(2, 0x02,  0x10,  0);
            }
            else if(testname == "btcom")
            {
                DEBUG_CHAR("sending bluetooth communication test...");
                sendMsg(2, 0x02,  0x07,  0);
            }
            else if(testname == "btCon")
            {
                DEBUG_CHAR("sending bluetooth connection test...");
                handleBt(true);
            }
            else if(testname == "nfc")
            {
                DEBUG_CHAR("sending NFC test...");
                sendMsg(2, 0x02,  0x17,  0);
            }
            else if(testname == "lock")
            {
                DEBUG_CHAR("sending lock car test...");
                if(checkGPIO(30, true) != 1)
                {
                    lock_flag = false;
                }
                sendMsg(2, 0x02,  0x12,  0);
            }
            else if(testname == "unlock")
            {
                DEBUG_CHAR("sending unlock test...");
                if(checkGPIO(35, true) != 1)
                {
                    unlock_flag = false;
                }
                sendMsg(2, 0x02,  0x13,  0);
            }
            else if(testname == "outage")
            {
                DEBUG_CHAR("sending outage test...");
                sendMsg(2, 0x02,  0x15,  0);
            }
            else if(testname == "lamp")
            {
                DEBUG_CHAR("sending lamp test...");
                sendMsg(2, 0x02,  0x16,  0);
            }
            write_flag = false;
        }
        
        if( read &&  (!stop) )
        {
            timeout=0;
            DEBUG_CHAR("read in!!!!");
            if(testname == "need_set_mode")
            {
                if(true)
                {
                    /*if(mainwindow->m_bSIM)
                    {
                        DEBUG_CHAR("receiving cfg mode data...");
                        handle_cfg_mode();
                    }
                    else
                    {
                        DEBUG_CHAR("receiving cfg mode data...");
                        handle_cfg_modeIMEI();
                    }*/
                    DEBUG_CHAR("receiving cfg mode data...");
                    handle_cfg_modeNew();
                }
            }
            else if(testname == "qrcode" )
            {
                if(true)
                {
                    DEBUG_CHAR("receiving qrcode data...");
                    handleqrCode();
                }
            } 
            else if(testname == "send_set_file")
            {
                if(true)
                {
                    DEBUG_CHAR("receiving set file data...");
                    handleSetFile();
                }
            }
            else if(testname == "6axis_sensor")
            {
                DEBUG_CHAR("receiving 6 axis sensor data...");
                handle6AxisSensor();
            }
            else if(testname == "wifi")
            {
                DEBUG_CHAR("receiving WIFI data...");
                handleWIFI();
            }
            else if(testname == "iviT")
            {
                DEBUG_CHAR("receiving iviT data...");
                handleIVIT();
            }
            else if(testname == "emmc" )
            {
                DEBUG_CHAR("receiving EMMC data...");
                handleEMMC();
            }
            else if(testname == "charge")
            {
                DEBUG_CHAR("reciving charge data...");
                handleCharge();
            }
            /*else if( testname == "bt" )
             {
                 handleBT();
                 qDebug()<<"接收数据:蓝牙";
             }*/
            else if(testname == "air_bag")
            {
                DEBUG_CHAR("receiving air_bag data...");
                handleAirBag();
            }
            else if(testname == "gps_open" )
            {
                DEBUG_CHAR("reveiving GPS open data...");
                handleGPSOpen();
            }
            else if(testname == "gps_signal" )
            {
                DEBUG_CHAR("receiving GPS signal data...");
                handleGPSSignal();
            }
            /*else if( testname == "gps_short" )
            {
                handleGPShort();
                qDebug()<<"接收数据:GPS短路";
            }*/
            else if(testname == "major_power" )
            {
                DEBUG_CHAR("receiving major power data...");
                handleMajorPower();
            }
            /*else if( testname == "minor_power" )
            {
                handleMinorPower();
                qDebug()<<"接收数据:备电电源测试";
            }*/
            else if(testname == "acc_off" )
            {
                DEBUG_CHAR("receiving acc off data...");
                stop_monitorusb=true;
                handleACCOFF();
            }
            else if(testname == "btcom")
            {
                DEBUG_CHAR("receiving bluetooth communication data...");
                handleBtCom();
            }
            else if(testname == "nfc")
            {
                DEBUG_CHAR("receiving NFC data...");
                handleNFC();
            }
            else if(testname == "lock")
            {
                DEBUG_CHAR("receiving lock data...");
                handleLockCar();
            }
            else if(testname == "unlock")
            {
                DEBUG_CHAR("receiving unlock data...");
                handleUnlockCar();
            }
            else if(testname == "outage")
            {
                DEBUG_CHAR("receiving outage data...");
                handleCarDoor();
            }
            else if(testname == "lamp")
            {
                DEBUG_CHAR("receiving lamp data...");
                handleCarLamp();
            }
            
            read = false;
            write_flag = true;
            if( index<m_vsTestName.size()-1 && !stop) //17项  (index<14) && (testname!="air_bag")
            {
                if( testname =="air_bag")
                {
                    write_flag = false;
                }
                if(testname != "need_set_mode" && testname != "qrcode")
                {
                    emit nextOne();
                }
                index++;
                testname = m_vsTestName.at(index);
            }
            else if(index >= m_vsTestName.size()-1 && !stop)
            {
                bEnd = true;
                write_flag = false;
            }
            DEBUG_PARAM2("testname:", testname, "index:", index);
        }
        
        if(bEnd)
        {
            DEBUG_CHAR("test end");
            bEnd = false;
            emit qrcode();
            mainwindow->update_db_flag(true);
            stop_monitorusb=true;
        }
    }
}
//btCom
void FortuneThread::handleBtCom()
{
    if( !analyze_section_data() )
    {
        emit errorCode("蓝牙通信", 262);
    }
    uint8_t tag;
    uint16_t taglen;
    uint8_t tagbody;
    tag = *(uint8_t*)(readMsg+5);
    taglen = *(uint16_t*)(readMsg+6);
    tagbody = *(uint8_t*)(readMsg+8);
    DEBUG_PARAM2("tag:", tag, "tagbody:", tagbody);
    if(tag == 0x67 && tagbody == 0x01)
    {
        DEBUGLOG;
        //emit nextOne();
    }
    else
    {
        stop = true;
        emit errorCode("蓝牙通信", 262);
    }
}
//btCon
void FortuneThread::handleBt(bool state)
{
    DEBUG_CHAR("打开蓝牙设备");
    m_btInterface->request_OpenDevice();
}

void FortuneThread::onSigBleDevName(QString name)
{
    int count=30;
    while(count--)
    {
        if(QString::compare(name, btName) == 0 )//btName
        {
            m_btInterface->request_ScanGatt(0);
            DEBUG_CHAR("蓝牙名称匹配成功");
            bt_flag = true;
            if(!m_bt_flag)
            {
                DEBUGLOG;
                m_bt_flag = true;
                //emit nextOne();
                read = true;
            }
            m_btInterface->request_CloseDevice();
            break;
        }
    }
    if(count==-1)
    {
        emit errorCode("蓝牙连接测试", 260);
        DEBUG_CHAR("蓝牙连接失败!!!");
    }
    DEBUG_PARAM("scan bluetooth name:", name);
    DEBUG_PARAM("btName bluetooth name:", btName);
    DEBUG_PARAM("count:", count);
}

void FortuneThread::onSigSwitchStatus(bool status)
{
    DEBUG_PARAM("status:", status);
//    DEBUG_PARAM("bt_sigOPenCount:", bt_sigOPenCount);
    if(status)
    {
        sleep(3);
        m_btInterface->request_ScanGatt(1);
    }
    /*
    else
    {
        bt_sigOPenCount++;
        DEBUG_PARAM("bt_sigOPenCount:", bt_sigOPenCount);
    }
    if(bt_sigOPenCount==5)
    {
        DEBUGLOG;
        sleep(2);
        m_btInterface->request_CloseDevice();
        sleep(2);
        m_btInterface->request_OpenDevice();
    }
    if(bt_sigOPenCount==7 && (!status))
    {
        DEBUG_CHAR("蓝牙设备打开失败");
        emit errorCode("蓝牙连接测试", 260);
    }*/
}
//NFC
void FortuneThread::handleNFC()
{
    if( !analyze_section_data() ) 
    {
        emit errorCode("NFC", 261);
    }
    uint8_t tag;
    uint16_t taglen;
    uint8_t tagbody;
    tag = *(uint8_t*)(readMsg+5);
    taglen = *(uint16_t*)(readMsg+6);
    tagbody = *(uint8_t*)(readMsg+8);
    DEBUG_PARAM2("tag:", tag, "tagbody:", tagbody);
    if(tag == 0x77 && tagbody == 0x01)
    {
        DEBUGLOG;
        //emit nextOne();
    }
    else
    {
        stop = true;
        emit errorCode("NFC", 261);
    }
}
//lock unlock
int FortuneThread::checkGPIO(int port, bool flag)
{
    char buf[100];
    if(flag)
    {
        memset(buf, 0 , sizeof(buf));
        sprintf(buf, "echo %d > /sys/class/gpio/export", port);//add port
        qDebug("buf=%s", buf);
        system(buf);

        memset(buf, 0 , sizeof(buf));
        sprintf(buf, "chmod 777 /sys/class/gpio/gpio%d -R", port);
        qDebug("buf=%s", buf);
        system(buf);
    }

    memset(buf, 0 , sizeof(buf));
    sprintf(buf, "cat /sys/class/gpio/gpio%d/value", port);//cat value
    qDebug("buf=%s", buf);
    FILE* ptr = popen(buf, "r");
    char rbuf[8]={0};
    if(ptr<0)
    {
        DEBUG_CHAR("open check gpio is fail");
        pclose(ptr);
        return 3;
    }
    fread(rbuf, 1, 8, ptr);
    pclose(ptr);
    DEBUG_PARAM("rbuf:", rbuf);
    int pos = atoi(rbuf);
    DEBUG_PARAM("rbuf_level:", pos);
    if(pos==1)
    {
        return 1;
    }
    else if(pos==0)
    {
        return 0;
    }
    else
        return 3;
}

void FortuneThread::handleLockCar()
{
    if( !analyze_section_data() )
    {
        emit errorCode("锁车", 230);
    }
    uint8_t tag;
    uint16_t taglen;
    uint8_t tagbody;
    tag = *(uint8_t*)(readMsg+5);
    taglen = *(uint16_t*)(readMsg+6);
    tagbody = *(uint8_t*)(readMsg+8);
    int pos=checkGPIO(30, false);
    DEBUG_PARAM2("tag:", tag, "tagbody:", tagbody);
    DEBUG_PARAM2("pos:", pos, "lock_flag:", lock_flag);
    if(tag == 0x72 && tagbody == 0x01  && lock_flag && (pos==0))
    {
        DEBUGLOG;
        //emit nextOne();
    }
    else
    {
        DEBUGLOG;
        stop = true;
        emit errorCode("锁车", 230);
    }
}

void FortuneThread::handleUnlockCar()
{
    if( !analyze_section_data() ) 
    {
        emit errorCode("解锁", 220);
    }
    uint8_t tag;
    uint16_t taglen;
    uint8_t tagbody;
    tag = *(uint8_t*)(readMsg+5);
    taglen = *(uint16_t*)(readMsg+6);
    tagbody = *(uint8_t*)(readMsg+8);
    int pos=checkGPIO(35, false);
    DEBUG_PARAM2("tag:", tag, "tagbody:", tagbody);
    DEBUG_PARAM2("pos:", pos, "unlock_flag:", unlock_flag);
    if(tag == 0x73 && tagbody == 0x01 && unlock_flag && pos==0)//
    {
        DEBUGLOG;
        //emit nextOne();
    }
    else
    {
        stop = true;
        emit errorCode("解锁", 220);
    }
}
//car door
void FortuneThread::handleCarDoor()
{
    //level>0.5-->OK
   char command[100]={0};
   char buf[8]={0};
   sprintf(command, "cat /sys/devices/platform/soc/481c0000.adc-keys/tbox_current_detection/BLE");
   excutePopen(command, buf, sizeof(buf));
   float level = atoi(buf)*3.3/1024;
   DEBUG_PARAM("door-level:", level);
   if( !analyze_section_data() )
   {
       emit errorCode("动力断电", 250);
   }
   uint8_t tag;
   uint16_t taglen;
   uint8_t tagbody;
   tag = *(uint8_t*)(readMsg+5);
   taglen = *(uint16_t*)(readMsg+6);
   tagbody = *(uint8_t*)(readMsg+8);
   DEBUG_PARAM2("tag:", tag, "tagbody:", tagbody);
   if(tag == 0x75 && tagbody == 0x01 && (level>0.5))
   {
       DEBUGLOG;
       //emit nextOne();
   }
   else
   {
       stop = true;
       emit errorCode("动力断电", 250);
   }
}

void FortuneThread::excutePopen(char* scr, char* dst, int size_n)
{
    FILE* ptr = popen(scr, "r");
    fread(dst, 1, size_n, ptr);
    pclose(ptr);
    DEBUG_PARAM("command:", scr);
    DEBUG_PARAM("return:", dst);
}
//car lamp
void FortuneThread::handleCarLamp()
{
    //level>0.5-->OK
   char command[100]={0};
   char buf[8]={0};
   sleep(1);
   sprintf(command, "cat /sys/devices/platform/soc/481c0000.adc-keys/tbox_current_detection/LED");
   excutePopen(command, buf, sizeof(buf));
   float level = atoi(buf)*3.3/1024;
   DEBUG_PARAM("LED-level:", level);
   if( !analyze_section_data() )
   {
       emit errorCode("车灯", 240);
   }
   uint8_t tag;
   uint16_t taglen;
   uint8_t tagbody;
   tag = *(uint8_t*)(readMsg+5);
   taglen = *(uint16_t*)(readMsg+6);
   tagbody = *(uint8_t*)(readMsg+8);
   DEBUG_PARAM2("tag:", tag, "tagbody:", tagbody);
   if(tag == 0x76 && tagbody == 0x01 && (level>0.5))
   {
       DEBUGLOG;
       //emit nextOne();
   }
   else
   {
       stop = true;
       emit errorCode("车灯", 240);
   }
}

void FortuneThread::chang_stop_flag()
{
    qDebug()<<"chang stop flsg is be running!!!";
    stop = true;
}

void FortuneThread::clear_socket()
{
    socket_m->flush();
}

void FortuneThread::test()
{
    DEBUG_CHAR("nextOne is emit");
}

void FortuneThread::restart()
{
    iniTableViewByCarinfo();
    iniTableViewByqr();
    initListView();
}

void FortuneThread::change_serial()
{
    char buf[4]={0};//测试完成后更新ini文件
    int pos = atoi(tBoxSN2.toLatin1().data());
    DEBUG_PARAM("tBoxSN2:", tBoxSN2);
    pos++;
    if(pos<10)
    {
        sprintf(buf, "000%d", pos);
    }
    else if((pos>=10) && (pos<100))
    {
        sprintf(buf, "00%d", pos);
    }
    else if((pos>=100) && (pos<1000))
    {
        sprintf(buf, "0%d", pos);
    }
    else if((pos>=1000) && (pos<10000))
    {
        sprintf(buf, "%d", pos);
    }
    DEBUG_PARAM("buf:", buf);
    QString str = buf;
    setting->setValue("TBoxSN2/sn2", str);
    sync();
}

////////////////////////////MainWindow///////////////////////////
MainWindow::MainWindow() 
{
    DEBUGLOG;
    m_rootKey = "";
    ring_num = 0;
    m_bSIM = true;
    m_bRootkey = false;
    m_sDBTerm = "";
    m_sProName = "";
    m_dbName = "";
    m_msiDBTerm.clear();
    thread_m = new FortuneThread;
    //init_db();
    connect(thread_m, SIGNAL(update_iccid()), this, SLOT(on_update_iccid()), Qt::QueuedConnection );
    connect(thread_m, SIGNAL(update_sn()), this, SLOT(on_update_sn()), Qt::QueuedConnection );
    rootContext()->setContextProperty("Thread", thread_m);
    connect(thread_m, SIGNAL(nextOne()), thread_m, SLOT(test()));
    m_harkey = new ComTiotDbusHardkeyInterface("com.tiot.dbus.hardkey", "/", QDBusConnection::systemBus(), this);
    m_harkey->wakeUp();
    connect(m_harkey, SIGNAL(sigKeyEvent(int, int)), this, SLOT(test(int, int)));
    rootContext()->setContextProperty("HardKey", m_harkey);
    thread_m->listModel = new FileListItemModel;
    thread_m->tableModel = new FileListItemModel;
    thread_m->tableMode2 = new FileListItemModel;
    thread_m->tableModelQR = new FileListItemModel;
    rootContext()->setContextProperty("DataModel", thread_m->listModel);
    rootContext()->setContextProperty("TestNameModel", thread_m->tableModel);
    rootContext()->setContextProperty("TestNameMode2", thread_m->tableMode2);
    rootContext()->setContextProperty("TableModelQR", thread_m->tableModelQR);
    m_pConnectServerTime = new QTimer;
    connect( m_pConnectServerTime,SIGNAL(timeout()), this, SLOT(onConnectServer()) );
    m_pInitTimer = new QTimer;
    connect(m_pInitTimer, SIGNAL(timeout()), this, SLOT(init()));
    can_dbus_interface = new ComQtYeedonCanInterface("com.qt.yeedon.can", "/", QDBusConnection::systemBus(), this);
    m_pCallInterface = new ComQtYeedonCallInterface("com.qt.yeedon.call", "/", QDBusConnection::systemBus(), this);
    connect(m_pCallInterface, SIGNAL(broadcastRing()), this, SLOT(onSigBroadcastRing()));
    connect(can_dbus_interface, SIGNAL(broadTest(int)), this, SLOT(onbroadTest(int)));
    thread_m->m_btInterface = new ComQtYeedonBtInterface("com.qt.yeedon.bt", "/",  QDBusConnection::systemBus(), this);
    connect(thread_m->m_btInterface, SIGNAL(sigBleDevName(QString)), thread_m, SLOT(onSigBleDevName(QString)));
    connect(thread_m->m_btInterface, SIGNAL(sigSwitchStatus(bool)), thread_m, SLOT(onSigSwitchStatus(bool)));
    mon1 = new monitorusb;
    system("rm test1.wav -f");
    DEBUGLOG;
}

MainWindow::~MainWindow()
{
    free(thread_m->readMsg);
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
    m_pInitTimer->stop();
    init_db();
    thread_m->iniTableViewByCarinfo();
    thread_m->iniTableViewByqr();
    thread_m->initListView();
    //thread_m->readDisk();
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
    
    /*if(m_bSIM && m_bRootkey && !access("/run/media/usb/tbox/SIM_RootKey.txt", F_OK))
    {
        DEBUGLOG;
        initDatabase("/run/media/usb/tbox/SIM_RootKey.txt");
        system("mv /run/media/usb/tbox/ /run/media/usb/tbox_after/");
        system("sync");
    }
    else if(!m_bSIM && access(m_dbName.data(), F_OK) != 0)
    {
        DEBUGLOG;
        initDatabase("");
        system("sync");
        DEBUG_PARAM("----------------:", access(m_dbName.data(), F_OK));
    }*/
}

void MainWindow::onConnectServer()
{
    m_pConnectServerTime->stop();
    DEBUGLOG;
    thread_m->init();
    DEBUGLOG;
    mon1->start();
    thread_m->readDisk();
    DEBUGLOG;
    if(!thread_m->isRunning()) { thread_m->start(); }
}
/*
void MainWindow::getDBTerm()
{
    DEBUGLOG;
    int ret;
    sqlite3_stmt *stmt;
    DEBUG_PARAM("open_db_flag:", open_db_flag);
    if(open_db_flag)
    {
        open_db_flag = false;
        if((ret = sqlite3_open(m_dbName.data(),&m_pdb)) != SQLITE_OK)
        {
            fprintf(stderr,"Can't open databaseOne: %s\n", sqlite3_errmsg(m_pdb));
            sqlite3_close(m_pdb);
        }
    }

    char *sql = sqlite3_mprintf("PRAGMA table_info('%s')", TABLE_NAME);
    DEBUG_PARAM("sql:", sql);
    fflush(stdout);
    if((ret = sqlite3_prepare(m_pdb, sql, strlen(sql), &stmt, 0)) != SQLITE_OK)
    {
        fprintf(stderr, "select error: %s\n", sqlite3_errmsg(m_pdb));
    }
    //execute
    DEBUG_PARAM("ret:", ret);
    if(ret == SQLITE_DONE)
    {
        DEBUG_CHAR("sqlite3_step ok!");
        fflush(stdout);
    }
    
    m_msiDBTerm.clear();
    int index = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) 
    {
        char *theGetData = (char *)sqlite3_column_text(stmt, 1);
        DEBUG_PARAM("data:", theGetData);
        m_msiDBTerm[QString(theGetData)] = index++;
    }
    qDebug()<<m_msiDBTerm.keys();
    
    sqlite3_finalize(stmt);
}
*/
void MainWindow::onSigBroadcastRing()
{
    thread_m->sos_flag = false;
    DEBUG_PARAM("thread_m->sos_flag:", thread_m->sos_flag);
    FILE* fl;
    fl = popen("echo 0 > /sys/devices/platform/soc/481c0000.adc-keys/tbox_current_detection/pwm", "r");
    pclose(fl);
    m_pCallInterface->pickup();
    DEBUGLOG;
    //system("amixer -c3 sset \"4-Ampli\" On");//7652功放
    system("amixer -c3 set \"Mute Master\" Off");
    system("amixer -c3 set Source main");
    system("amixer -c3 set \"Scaler Primary Voice Volume Master\" 1200");//must
    system("amixer -c 3 set \"Volume Master\" 1200");
    system("amixer -c3 set \"ADCMIC CHSEL\" 22");//切换成录制通道
    system("amixer -c3 set \"Scaler ADC Volume Master\" 1200");//must

    system("amixer -c 3 set \"Volume Rear Left\" 1100");//控制播放声音
    system("arecord -D hw:1,0 -r 48000 -f S16_LE -c1 test1.wav &");
    system("aplay -D hw:2,0 /run/media/usb/1k.wav");
    system("killall arecord");
    system("amixer -c 3 set \"Volume Rear Left\" 1200");//控制播放录制声音
    system("aplay -D hw:2,0 test1.wav");
    DEBUGLOG;
    m_pCallInterface->pickdown();
    DEBUG_PARAM("stop:", thread_m->stop);
    if(!thread_m->stop)
    {
        DEBUG_PARAM("stop:", thread_m->stop);
        thread_m->write_flag = true;
        DEBUGLOG;
        emit thread_m->nextOne();
    }
}

int MainWindow::initHotPlugSocket()
{
    bool device_flag = false;
    bool udisk_flag = false;
    char buf[2048]={0};
    while(1)
    {
        FILE* fl = popen("ifconfig -a", "r");
        fread(buf, 1, sizeof(buf), fl);
        //printf("buffffffffffffff= %s\n", buf);
        //fflush(stdout);
        QString str = buf;
        if( str.contains("usb0") && (!device_flag) )
        {
            device_flag = true;
            system("dhclient usb0");
        }
        else
        {
            DEBUGLOG;
            thread_m->stop = true;
            emit thread_m->device_disconnect();
        }
        if( access("/run/media/usb", 0) == 0 )
        {
            DEBUGLOG;
            qDebug()<<"access(/run/media/usb, 0) == 0 is being!!!";
            udisk_flag = true;
        }
        else
        {
            DEBUGLOG;
            qDebug()<<"udisk_disconnect is emit!!!!!!!!!!!!!!!";
            udisk_flag = false;
            thread_m->stop = true;
            emit thread_m->udisk_disconnect();
        }
        //sleep(1);
    }
    return 0;
}

void MainWindow::setAudioPlayState()
{
    m_playFinished = true;
}

void *MainWindow::initHotPlugThread(void *args)
{
    pthread_detach(pthread_self());
    while(1)
    {
        if(mainwindow->initHotPlugSocket() < 0)
        {
            DEBUGLOG;
        }
        else
        {
            ::close(mainwindow->m_hotplug_sd);
            mainwindow->m_hotplug_sd = -1;
            pthread_exit(0);
        }
        sleep(2);
    }
}

bool FortuneThread::set_gpio_val( int num, bool dir, int value )
{
    char direction[100]={0};
    char valuepath[100]={0};
    if(dir){
        sprintf(direction,  "echo out > /sys/class/gpio/gpio%d/direction", num);
        system(direction);
    }else{
        sprintf(direction,  "echo in > /sys/class/gpio/gpio%d/direction", num);
        system(direction);
    }
    if(value==1){
        sprintf(valuepath,  "echo 1 > /sys/class/gpio/gpio%d/value", num);
        system(valuepath);
    }else
    {
        sprintf(valuepath,  "echo 0 > /sys/class/gpio/gpio%d/value", num);
        system(valuepath);
    }
    return true;
}

void MainWindow::initDatabase(QString filePath)
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    int ret;
    char *pErrMsg;
    char *sql = NULL;

    if(open_db_flag)
    {
        open_db_flag = false;
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
/*
bool MainWindow::checkTermExist(const QString term)
{
    QMap<QString, int>::iterator iter = m_msiDBTerm.find(term);
    if(iter != m_msiDBTerm.end())
    {
        return true;
    }
    return false;
}
*/
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

void MainWindow::on_update_iccid()
{
    DEBUG_PARAM("str_iccid:", str_iccid);
    m_rootKey = getData(str_iccid, "rootKey");
    DEBUG_PARAM("m_rootKey:", m_rootKey);
    if(m_rootKey == "")
    {
        emit thread_m->errorCode("rootKey", 180);
    }
    thread_m->tableModel->setFileNamebyFilePath("ICCID", str_iccid);  
    sim_num = getData(str_iccid, "sim");
    if(sim_num=="")
    {
        emit thread_m->errorCode("SIM", 3);
    }
    else
    {
        thread_m->tableModel->setFileNamebyFilePath("SIM", sim_num);
    }

    serial_show = getData(str_iccid, "SN");//序列号不等空
    DEBUG_PARAM("serial_show:", serial_show);
    if(serial_show == "")//sn from udisk
    {
        thread_m->change_sn = true;
        char buf[35]={0};
        memset(buf, 0, 35);
        sprintf( buf, "%s%s%s", thread_m->tBoxSN1.toLocal8Bit().data(), thread_m->tBoxSN2.toLocal8Bit().data(), tBoxSN3.toLocal8Bit().data() );
        thread_m->m_serial = buf;
        memset(buf, 0, 35);
        sprintf( buf, "%s%s", thread_m->tBoxSN1.toLocal8Bit().data(), thread_m->tBoxSN2.toLocal8Bit().data());
        serial_show = buf;
        DEBUG_PARAM("serial_show:",serial_show);
        thread_m->change_serial();
        updateOtherByIccid(str_iccid, "SN", serial_show);//sn
    }
    else
    {
        thread_m->m_serial = serial_show;
        thread_m->m_serial.append("0000");
    }
    DEBUG_PARAM("serial_show:", serial_show);
    thread_m->tableMode2->setFileNamebyFilePath("序列号", serial_show);
    updateOtherByIccid(str_iccid, "product", pn_num);
    updateOtherByIccid(str_iccid, "swversion", software_version);
    updateOtherByIccid(str_iccid, "hwversion", thread_m->hw);
    sync();
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
/*
void MainWindow::insertData(QString iccid, QString imei, QString imsi, QString sn, QString swversion, QString hwversion, QString rootKey, QString sim, QString productModel, int flag, QString project)
{
    DEBUGLOG;
    int ret;
    sqlite3_stmt *stmt;
    char *sql = sqlite3_mprintf("insert into %s values(NULL,'%s','%s','%s','%s','%s','%s','%s','%s','%s','%d','%s')",
                                TABLE_NAME,
                                iccid.toLocal8Bit().data(),
                                imei.toLocal8Bit().data(),
                                imsi.toLocal8Bit().data(),
                                sn.toLocal8Bit().data(),
                                swversion.toLocal8Bit().data(),
                                hwversion.toLocal8Bit().data(),
                                rootKey.toLocal8Bit().data(),
                                sim.toLocal8Bit().data(),
                                productModel.toLocal8Bit().data(),
                                flag,
                                project.toLocal8Bit().data());
    DEBUG_PARAM("sql:",sql);

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
}
*/
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
    DEBUG_PARAM("iccid:", iccid);
    DEBUG_PARAM("iccid::", iccid.length());
    DEBUG_PARAM("data:", data);
    
    int ret;
    sqlite3_stmt *stmt;

    if(open_db_flag)
    {
        open_db_flag = false;
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

    if(QString(theGetDate) != "")
    {
        return QString(theGetDate);
    }
    else
        return "";

    sqlite3_finalize(stmt);
}
/*********************************************************/
void MainWindow::on_update_sn()
{
    //序列号
    thread_m->m_serial = getData(thread_m->m_imei, "SN");//序列号不等空
    DEBUG_PARAM("m_serial:", thread_m->m_serial);
    if(thread_m->m_serial == "")//sn from udisk
    {
        DEBUGLOG;
        thread_m->change_sn = true;
        char buf[35]={0};
        sprintf( buf, "%s%s%s", thread_m->tBoxSN1.toLocal8Bit().data(), thread_m->tBoxSN2.toLocal8Bit().data(), thread_m->tBoxSN3.toLocal8Bit().data() );
        thread_m->m_serial = buf;
        thread_m->change_serial();
        updateOtherByImei(thread_m->m_imei, "SN", thread_m->m_serial);//sn
    }
    else
    {
        thread_m->btName.clear();
        thread_m->btName = thread_m->m_serial.mid(9);
        DEBUG_PARAM("btName:", thread_m->btName);
    }
    DEBUG_PARAM("thread_m->m_serial:", thread_m->m_serial);
    serial_show = thread_m->m_serial;
    thread_m->tableMode2->setFileNamebyFilePath("序列号", thread_m->m_serial);
    updateOtherByImei(thread_m->m_imei, "product", p_model);
    updateOtherByImei(thread_m->m_imei, "swversion", software_version);
    updateOtherByImei(thread_m->m_imei, "hwversion", thread_m->hw);
    sync();
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
/*
void MainWindow::insertData(QString imei, QString sn, QString swversion, QString hwversion, QString productModel, QString flag)
{
    DEBUGLOG;
    int ret;
    sqlite3_stmt *stmt;
    char *sql = sqlite3_mprintf("insert into %s values(NULL,'%s','%s','%s','%s','%s','%s')",
                                TABLE_NAME,
                                imei.toLocal8Bit().data(),
                                sn.toLocal8Bit().data(),
                                swversion.toLocal8Bit().data(),
                                hwversion.toLocal8Bit().data(),
                                productModel.toLocal8Bit().data(),
                                flag.toLocal8Bit().data());
    DEBUG_PARAM("sql:",sql);

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
    DEBUG_PARAM("ret:", ret);

    //free memory
    sqlite3_finalize(stmt);
}
*/
void MainWindow::updateOtherByImei(QString imei, QString model,QString data)
{
    DEBUG_PARAM("imei", imei);
    DEBUG_PARAM("term", model);
    
    int ret;
    sqlite3_stmt *stmt;
    char *sql = sqlite3_mprintf("update %s set %s='%s' where IMEI='%s'",
                                TABLE_NAME,
                                model.toLocal8Bit().data(),
                                data.toLocal8Bit().data(),
                                imei.toLocal8Bit().data());
    printf("%s\n", sql);

    DEBUG_PARAM("open_db_flag:", open_db_flag);
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
    DEBUG_PARAM("imei:", imei);
    DEBUG_PARAM("data:", data);
    
    int ret;
    sqlite3_stmt *stmt;
    DEBUG_PARAM("open_db_flag:", open_db_flag);
    if(open_db_flag)
    {
        open_db_flag = false;
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

    if(QString(theGetDate) != "")
    {
        return QString(theGetDate);
    }
    else
        return "";

    sqlite3_finalize(stmt);
}

bool MainWindow::findData(const QString iccid, const QString imei)
{   
    int ret;
    sqlite3_stmt *stmt;

    if(open_db_flag)
    {
        open_db_flag = false;
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
    char *theGetDate = (char *)sqlite3_column_text(stmt, 0);

    if(QString(theGetDate) != "")
    {
        return true;
    }
    else
        return false;
    sqlite3_finalize(stmt);
}

//////////////////////////////encode//////////////////////////////////
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
