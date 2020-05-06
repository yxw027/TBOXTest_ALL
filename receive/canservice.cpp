#include "cantaskevent.h"
#include "canservice.h"
#include "log.h"
#include "observer.h"
#include "gdbusiface.h"
#include <time.h>
#include <stdio.h>
#include <string>
#include <linux/input.h>

#include <sys/prctl.h>

#define CANRXMESSAGESIZE    168


CanTaskEvent *m_pCanTaskEvent;

//sxd
gboolean udpateTime(gpointer t)
{
    if(GET_SINGLETON_INSTANCE(CanService)->m_iTimeTimer)
    {
        struct tm *tblock;
        time_t timer = time(NULL);
        tblock = localtime(&timer);
        string stime = asctime(tblock);
        string sHour = stime.substr(11, 2);
        int hour = atoi(sHour.c_str());
        if(GET_SINGLETON_INSTANCE(CanService)->m_iTimeMode == 12 && hour > 12)
        {
            hour -= 12;
            char tmp[2];
            sprintf(tmp, "%02d", hour);
            sHour = tmp;
        }
        int hour1 = atoi(sHour.substr(0, 1).c_str());
        int hour2 = atoi(sHour.substr(1, 1).c_str());
        int min1 = atoi(stime.substr(14, 1).c_str());
        int min2 = atoi(stime.substr(15, 1).c_str());

        unsigned char *numberCode = GET_SINGLETON_INSTANCE(CanService)->numberCode;

        unsigned char data[4] = {
            numberCode[hour1],
            numberCode[hour2],
            numberCode[min1],
            numberCode[min2]
        };

        GET_SINGLETON_INSTANCE(CanService)->SendMsg2MCU(0x4D, data, 4);
        static bool bLight = false;
        if(!bLight)
        {
            data[3] = data[3] & (~(0x80));
        }
        else if(bLight)
        {
            data[3] = data[3] | (0x80);
        }
        GET_SINGLETON_INSTANCE(CanService)->SendMsg2MCU(0x4D, data, 4);
        bLight = !bLight;
    }
    return GET_SINGLETON_INSTANCE(CanService)->m_iTimeTimer;
}

gboolean flashHour(gpointer h)
{
    if(GET_SINGLETON_INSTANCE(CanService)->m_iHourTimer)
    {
        string hour = GET_SINGLETON_INSTANCE(CanService)->m_sCurHour;
        string min = GET_SINGLETON_INSTANCE(CanService)->m_sCurMinute;
        //LOGMSG(OUTPUT, ("flash hour:%s:%s\n", hour.c_str(), min.c_str()));
        int hour1 = atoi(hour.substr(0, 1).c_str());
        int hour2 = atoi(hour.substr(1, 1).c_str());
        int min1 = atoi(min.substr(0, 1).c_str());
        int min2 = atoi(min.substr(1, 1).c_str());

        unsigned char *numberCode = GET_SINGLETON_INSTANCE(CanService)->numberCode;

        unsigned char data[4] = {
            numberCode[hour1],
            numberCode[hour2],
            numberCode[min1],
            numberCode[min2]
        };

        static bool bLight = false;
        if(bLight)
        {
            data[0] = 0xFF;
            data[1] = 0xFF;
        }
        GET_SINGLETON_INSTANCE(CanService)->SendMsg2MCU(0x4D, data, 4);
        data[3] = data[3] & (~(0x80));

        GET_SINGLETON_INSTANCE(CanService)->SendMsg2MCU(0x4D, data, 4);
        bLight = !bLight;
    }
    return GET_SINGLETON_INSTANCE(CanService)->m_iHourTimer;
}

gboolean flashMinute(gpointer m)
{
    if(GET_SINGLETON_INSTANCE(CanService)->m_iMinTimer)
    {
        string hour = GET_SINGLETON_INSTANCE(CanService)->m_sCurHour;
        string min = GET_SINGLETON_INSTANCE(CanService)->m_sCurMinute;
        //LOGMSG(OUTPUT, ("flash minute:%s:%s\n", hour.c_str(), min.c_str()));
        int hour1 = atoi(hour.substr(0, 1).c_str());
        int hour2 = atoi(hour.substr(1, 1).c_str());
        int min1 = atoi(min.substr(0, 1).c_str());
        int min2 = atoi(min.substr(1, 1).c_str());

        unsigned char *numberCode = GET_SINGLETON_INSTANCE(CanService)->numberCode;

        unsigned char data[4] = {
            numberCode[hour1],
            numberCode[hour2],
            numberCode[min1],
            numberCode[min2]
        };

        static bool bLight = false;
        if(bLight)
        {
            data[2] = 0xFF;
            data[3] = 0xFF;
        }
        GET_SINGLETON_INSTANCE(CanService)->SendMsg2MCU(0x4D, data, 4);
        data[3] = data[3] & (~(0x80));
        //data[3] = data[3] | (0x80);
        GET_SINGLETON_INSTANCE(CanService)->SendMsg2MCU(0x4D, data, 4);
        bLight = !bLight;
    }

    return GET_SINGLETON_INSTANCE(CanService)->m_iMinTimer;
}

BOOL CanService::Init()
{
    //sxd
    m_iDataId = 0x4D;
    m_iLEDModeId = 0x4E;
    m_iFlashInterval = 500;
    m_iTimeTimer = 0;
    m_iHourTimer = 0;
    m_iMinTimer = 0;
    m_iSetTimeMode = 2;
    m_iTimeMode = 24;

    m_pCanTaskEvent = GET_SINGLETON_INSTANCE(CanTaskEvent);

    bool ret = m_pCanTaskEvent->Init();

    pthread_cond_init(&m_cond, NULL);
    pthread_mutex_init(&m_lock, NULL);

    printf("%s..%d.. %d\n",__FUNCTION__,__LINE__, ret);

    if(ret)
    {
        printf("%s..%d..\n",__FUNCTION__,__LINE__);

        CreateThread(1,0,true);

        usleep(300000);

        InformThread();
    }
    return ret;
}

void CanService::Deinit()
{
    pthread_mutex_destroy(&m_lock);
    pthread_cond_destroy(&m_cond);

    m_pCanTaskEvent->Deinit();

    KillThread();

    RELEASE_SINGLETON_INSTANCE(CanTaskEvent);
}

bool CanService::SendMsg2MCU(unsigned int msgID, unsigned int param)
{
    return m_pCanTaskEvent->Write2MCU(msgID, param);
}

bool CanService::SendMsg2MCU(unsigned int msgID, unsigned char param[], int size)
{
    return m_pCanTaskEvent->Write2MCU(msgID, param, size);
}

void CanService::Sendevent(int event)
{
    m_pCanTaskEvent->Sendevent(event);;
}

//hbx 2019-06-27
void CanService::setPlayerProgress(unsigned int second)
{
    char data[134] = {0};

    unsigned int m_min = second/60;
    unsigned int m_second = second%60;

    if(m_min<10)
    {
        if(m_second<10)
        {
            sprintf(data, "0%d0%d", m_min, m_second);
        }
        else
        {
            sprintf(data, "0%d%d", m_min, m_second);
        }
    }
    else
    {
        if(m_second<10)
        {
            sprintf(data, "%d0%d", m_min, m_second);
        }
        else
        {
            sprintf(data, "%d%d", m_min, m_second);
        }
    }
    int tmp = atoi(data);

    uint32_t test = (changeTable(tmp/1000));
    test |= changeTable(tmp/100%10)<<8;
    test |= changeTable(tmp/10%10)<<16;
    test |= ((changeTable(tmp%100%10)<<24) & (0x7fffffff));

    data[3] &= (~0x80);

    SendMsg2MCU(0x4D, test);
}

int CanService::changeTable(int param)
{
    int tmp;
    switch (param) {
    case 0:
        tmp = 0xC0;
        break;
    case 1:
        tmp = 0xF9;
        break;
    case 2:
        tmp = 0xA4;
        break;
    case 3:
        tmp = 0xB0;
        break;
    case 4:
        tmp = 0x99;
        break;
    case 5:
        tmp = 0x92;
        break;
    case 6:
        tmp = 0x82;
        break;
    case 7:
        tmp = 0xF8;
        break;
    case 8:
        tmp = 0x80;
        break;
    case 9:
        tmp = 0x90;
        break;

    default:
        tmp = NONE;
        break;
    }
    return tmp;
}

//sxd 2019-06-26
void CanService::setLEDMode(LED_MODE mode)
{
    unsigned char data[4] = {mode, 0x0, 0x0, 0x0};
    SendMsg2MCU(m_iLEDModeId, data, 4);
}

void CanService::startTimer(int id)
{
    switch (id)
    {
    case 0: //time
    {
        if(m_id_timer_clock == -1)
        {
            m_iTimeTimer = 1;
            m_iHourTimer = 0;
            m_iMinTimer = 0;
            m_id_timer_clock = g_timeout_add(m_iFlashInterval, udpateTime, 0);
        }
    }
        break;
    case 1: //hour
    {
        if(m_id_timer_clock_set_hour == -1)
        {
            m_iTimeTimer = 0;
            m_iHourTimer = 1;
            m_iMinTimer = 0;
            m_id_timer_clock_set_hour = g_timeout_add(m_iFlashInterval, flashHour, 0);
        }
    }
        break;
    case 2: //minute
    {
        if(m_id_timer_clock_set_minu == -1)
        {
            m_iTimeTimer = 0;
            m_iHourTimer = 0;
            m_iMinTimer = 1;
            m_id_timer_clock_set_minu = g_timeout_add(m_iFlashInterval, flashMinute, 0);
        }
    }
    default:
        break;
    }
}

//mode set
void CanService::setLEDFMMode(const bool bNormal)
{
    if(bNormal)
    {
        setLEDMode(FM_NORMAL_MODE);
    }
    else if(!bNormal)
    {
        setLEDMode(FM_SEEK_MODE);
    }
}

void CanService::setLEDAMMode(const bool bNormal)
{
    if(bNormal)
    {
        setLEDMode(AM_NORMAL_MODE);
    }
    else if(!bNormal)
    {
        setLEDMode(AM_SEEK_MODE);
    }
}

void CanService::setLEDBTMode(const bool bBtMode)
{
    if(bBtMode)
    {
        setLEDMode(BT_NORMAL_MODE);
    }
    else
    {
        setLEDMode(BT_SEEK_MODE);
    }
}

void CanService::setLEDUSBMode(const bool bUsbMode)
{
    if(!bUsbMode)
    {
        setLEDMode(USB_MODE_BUT_NOT_IN_SUB_MODE);
    }
    else if(bUsbMode)
    {
        setLEDMode(USB_NORMAL_MODE);
    }
}

void CanService::setCloseLEDMode()
{
    setLEDMode(HI);
    unsigned char data[4] = {NONE, NONE, NONE, NONE};
    SendMsg2MCU(m_iDataId, data, 4);
}

//radio
void CanService::setCurFreq(const int freq, bool bFm)
{
    char tmp[4] = {0};
    sprintf(tmp, "%04d", freq);
    string sFreq = tmp;

    int min1 = atoi(sFreq.substr(0, 1).c_str());
    int min2 = atoi(sFreq.substr(1, 1).c_str());
    int sec1 = atoi(sFreq.substr(2, 1).c_str());
    int sec2 = atoi(sFreq.substr(3, 1).c_str());

    unsigned char *numberCode = GET_SINGLETON_INSTANCE(CanService)->numberCode;

    unsigned char data[4] = {
        (min1==0)?NONE:(numberCode[min1]),
        numberCode[min2],
        numberCode[sec1],
        numberCode[sec2]
    };

    GET_SINGLETON_INSTANCE(CanService)->SendMsg2MCU(0x4D, data, 4);
    if(bFm)
    {
        data[2] = data[2] & (~(0x80));
    }
    else
    {
        data[2] = data[2] | (0x80);
    }
    GET_SINGLETON_INSTANCE(CanService)->SendMsg2MCU(0x4D, data, 4);
}

void CanService::setShowSysVersion(int version)
{
    setShowUSBIndex(version);
}

void CanService::setShowUSBIndex(int index)
{
#if 0
    if(index > 9999)
    {
        index = 9999;
    }
    char tmp[4] = {0};
    sprintf(tmp, "%04d", index);
    string sindex = tmp;
    int data0 = atoi(sindex.substr(0, 1).c_str());
    int data1 = atoi(sindex.substr(1, 1).c_str());
    int data2 = atoi(sindex.substr(2, 1).c_str());
    int data3 = atoi(sindex.substr(3, 1).c_str());

    unsigned char *numberCode = GET_SINGLETON_INSTANCE(CanService)->numberCode;

    unsigned char data[4] = {
        numberCode[data0],
        numberCode[data1],
        numberCode[data2],
        numberCode[data3]
    };
#else
    if(index > 999)
    {
        index = 999;
    }
    char tmp[4] = {0};
    sprintf(tmp, "%03d", index);
    string sindex = tmp;
    int data0 = atoi(sindex.substr(0, 1).c_str());
    int data1 = atoi(sindex.substr(1, 1).c_str());
    int data2 = atoi(sindex.substr(2, 1).c_str());

    unsigned char *numberCode = GET_SINGLETON_INSTANCE(CanService)->numberCode;

    unsigned char data[4] = {
        F,
        numberCode[data0],
        numberCode[data1],
        numberCode[data2]
    };
#endif

    GET_SINGLETON_INSTANCE(CanService)->SendMsg2MCU(m_iDataId, data, 4);
}

//bt
void CanService::setShowBTMusic()
{
    unsigned char data[4] = {A, TWO, D, P};
    SendMsg2MCU(m_iDataId, data, 4);
}

void CanService::setBtPhoneOn()
{
    unsigned char data[4] = {NONE, O, N, NONE};
    SendMsg2MCU(m_iDataId, data, 4);
}

void CanService::setBtPhonetOff()
{
    unsigned char data[4] = {NONE, O, F, F};
    SendMsg2MCU(m_iDataId, data, 4);
}
//link
void CanService::showLink()
{
    unsigned char data[4] = {L, I, N, H};
    SendMsg2MCU(m_iDataId, data, 4);
}

//line
void CanService::showLine()
{
    unsigned char data[4] = {L, I, N, E};
    SendMsg2MCU(m_iDataId, data, 4);
}

//rvc
void CanService::setShowRearVideoCamera()
{
    unsigned char data[4] = {NONE, P, NONE, NONE};
    SendMsg2MCU(m_iDataId, data, 4);
}

void CanService::setShowOne()
{
    unsigned char data[4] = {NONE, O, N, E};
    SendMsg2MCU(m_iDataId, data, 4);
}

void CanService::setShowAll()
{
    unsigned char data[4] = {NONE, A, L, L};
    SendMsg2MCU(m_iDataId, data, 4);
}

void CanService::setShowRadom()
{
    unsigned char data[4] = {FIVE, H, U, F};
    SendMsg2MCU(m_iDataId, data, 4);
}

void CanService::setShowFind()
{
    unsigned char data[4] = {NONE, U, FIVE, B};
    SendMsg2MCU(m_iDataId, data, 4);
}

void CanService::showErr()
{
    unsigned char data[4] = {NONE, E, r, r};
    SendMsg2MCU(m_iDataId, data, 4);
}

void CanService::showNOFile()
{
    unsigned char data[4] = {N, O, NONE, F};
    SendMsg2MCU(m_iDataId, data, 4);
}

//set time
void CanService::changeTimeMode()
{
    if(m_iSetTimeMode == 2) //format
    {
        if(m_iTimeMode == 12)
        {
            setTwelveFormat();
        }
        else if(m_iTimeMode == 24)
        {
            setTwentyFourFormat();
        }
    }
    else if(m_iSetTimeMode == 0) //hour
    {
        setFlashHour();
    }
    else if(m_iSetTimeMode == 1) //minute
    {
        setFlashMinute();
    }
    LOGMSG(OUTPUT, ("setTimeMode:%d\n", m_iSetTimeMode));
}

void CanService::setTwelveFormat()
{
    m_iSetTimeMode = 0;
    m_iTimeMode = 12;
    unsigned char data[4] = {NONE, ONE, TWO, H};
    SendMsg2MCU(m_iDataId, data, 4);
}

void CanService::setTwentyFourFormat()
{
    m_iSetTimeMode = 0;
    m_iTimeMode = 24;
    unsigned char data[4] = {NONE, TWO, FOUR, H};
    SendMsg2MCU(m_iDataId, data, 4);
}

void CanService::setFlashHour()
{
    stopFlashMinute();
    m_iSetTimeMode = 1;
    struct tm *tblock;
    time_t timer = time(NULL);
    tblock = localtime(&timer);
    string stime = asctime(tblock);
    m_sCurHour = stime.substr(11, 2);
    m_iCurHour = atoi(m_sCurHour.c_str());
    m_sCurMinute = stime.substr(14, 2);
    m_iCurMinute = atoi(m_sCurMinute.c_str());
    startTimer(1);
}

void CanService::setCurrentHour(const int hour)
{
    stopFlashHour();
    m_iCurHour = hour;
    setCurHour();
    char tmp[4] = {0};
    sprintf(tmp, "%02d", hour);
    string sindex = tmp;
    int data0 = atoi(sindex.substr(0, 1).c_str());
    int data1 = atoi(sindex.substr(1, 1).c_str());
    int data2 = atoi(m_sCurMinute.substr(0, 1).c_str());
    int data3 = atoi(m_sCurMinute.substr(1, 1).c_str());

    unsigned char *numberCode = GET_SINGLETON_INSTANCE(CanService)->numberCode;
    unsigned char data[4] = {
        numberCode[data0],
        numberCode[data1],
        numberCode[data2],
        numberCode[data3]
    };
    SendMsg2MCU(m_iDataId, data, 4);
    data[3] = data[3] & (~(0x80));
    SendMsg2MCU(m_iDataId, data, 4);
}

void CanService::setFlashMinute()
{
    stopFlashHour();
    m_iSetTimeMode = 2;
    struct tm *tblock;
    time_t timer = time(NULL);
    tblock = localtime(&timer);
    string stime = asctime(tblock);
    m_sCurHour = stime.substr(11, 2);
    m_iCurHour = atoi(m_sCurHour.c_str());
    m_sCurMinute = stime.substr(14, 2);
    m_iCurMinute = atoi(m_sCurMinute.c_str());
    startTimer(2);
}

void CanService::setCurrentMinte(const int min)
{
    stopFlashMinute();
    m_iCurMinute = min;
    setCurMinute();
    char tmp[4] = {0};
    sprintf(tmp, "%02d", min);
    string sindex = tmp;
    int data0 = atoi(m_sCurHour.substr(0, 1).c_str());
    int data1 = atoi(m_sCurHour.substr(1, 1).c_str());
    int data2 = atoi(sindex.substr(0, 1).c_str());
    int data3 = atoi(sindex.substr(1, 1).c_str());

    unsigned char *numberCode = GET_SINGLETON_INSTANCE(CanService)->numberCode;
    unsigned char data[4] = {
        numberCode[data0],
        numberCode[data1],
        numberCode[data2],
        numberCode[data3]
    };
    SendMsg2MCU(m_iDataId, data, 4);
    data[3] = data[3] & (~(0x80));
    SendMsg2MCU(m_iDataId, data, 4);
}

void CanService::setCurHour()
{
    char tmp[2] = {0};
    sprintf(tmp, "%02d", m_iCurHour);
    m_sCurHour = tmp;
}

void CanService::setCurMinute()
{
    char tmp[2] = {0};
    sprintf(tmp, "%02d", m_iCurMinute);
    m_sCurMinute = tmp;
}

void CanService::SetstartUpdateTime()
{
    startTimer(0);
}

void CanService::SetstopUpdateTime()
{
    if(m_id_timer_clock != -1)
    {
        g_source_remove(m_id_timer_clock);
    }
    m_id_timer_clock = -1;
    m_iTimeTimer = 0;
}

void CanService::RestartFlashHour()
{
    startTimer(1);
}

void CanService::stopFlashHour()
{
    if(m_id_timer_clock_set_hour != -1)
    {
        g_source_remove(m_id_timer_clock_set_hour);
    }
    m_id_timer_clock_set_hour = -1;
    m_iHourTimer = 0;
}

void CanService::RestartFlashMinute()
{
    startTimer(2);
}

void CanService::stopFlashMinute()
{
    if(m_id_timer_clock_set_minu != -1)
    {
        g_source_remove(m_id_timer_clock_set_minu);
    }
    m_id_timer_clock_set_minu = -1;
    m_iMinTimer = 0;
}

void CanService::addSysTimeHour(bool add)
{
    if(add)
    {
        m_iCurHour++;
        m_iCurHour = m_iCurHour%24;
    }
    else
    {
        m_iCurHour--;
        if(m_iCurHour<0)
        {
            m_iCurHour = m_iCurHour+24;
        }
    }
    setCurrentHour(m_iCurHour);
}

void CanService::addSysTimeMinute(bool add)
{
    if(add)
    {
        m_iCurMinute++;
        m_iCurMinute = m_iCurMinute%60;
    }
    else
    {
        m_iCurMinute--;
        if(m_iCurMinute<0)
        {
            m_iCurMinute = m_iCurMinute + 60;
        }
    }
    setCurrentMinte(m_iCurMinute);
}

void CanService::updateSysTime()
{
    char buf[24]={0};
    sprintf(buf, "date -s %d:%d:00", m_iCurHour, m_iCurMinute);
    system(buf);
    //LOGMSG(OUTPUT, ("[canservice] updateSysTime: %s\n", buf));
}

void CanService::setShowHiEq(int eq)
{
    int value = eq;
    if(eq < 0)
    {
        value = -eq;
    }
    char tmp[4] = {0};
    sprintf(tmp, "%04d", value);
    string str = tmp;

    int data3 = atoi(str.substr(3, 1).c_str());

    uint32_t  data = H;
    data |= I<<8;
    if(eq < 0)
        data |= NEG<<16;
    else
        data |= NONE<<16;

    data |= numberCode[data3]<<24;

    SendMsg2MCU(m_iDataId, data);
}

void CanService::setShowLowEq(int eq)
{
    int value = eq;

    if(eq < 0)
    {
        value = -eq;
    }
    char tmp[4] = {0};
    sprintf(tmp, "%04d", value);
    string str = tmp;

    int data3 = atoi(str.substr(3, 1).c_str());

    uint32_t  data = L;
    data |= ZERO<<8;
    if(eq < 0)
        data |= NEG<<16;
    else
        data |= NONE<<16;
    data |= numberCode[data3]<<24;

    SendMsg2MCU(m_iDataId, data);
}

void CanService::showVolume(const int volume)
{
    char tmp[4] = {0};
    //LOGMSG(OUTPUT, ("set volume: %d\n", volume));
    sprintf(tmp, "%04d", volume);
    string sindex = tmp;
    //LOGMSG(OUTPUT, ("set tmp: %s\n", tmp));

    int data0 = atoi(sindex.substr(0, 1).c_str());
    data0 = -1;
    int data1 = atoi(sindex.substr(1, 1).c_str());
    int data2 = atoi(sindex.substr(2, 1).c_str());
    data1 = data2;
    int data3 = atoi(sindex.substr(3, 1).c_str());
    data2 = data3;
    data3 = -1;

    uint32_t data;
    data = changeTable(data0);
    data |= changeTable(data1)<<8;
    data |= changeTable(data2)<<16;
    data |= changeTable(data3)<<24;
    SendMsg2MCU(m_iDataId, data);
}

BOOL CanService::Processing()
{
    prctl(PR_SET_NAME,"*****THREAD1");

//    while(1)
//    {
//        pthread_mutex_lock(&m_lock);

//        if(m_testData == 0)
//        {
//            printf("hello1\n");
//            m_testData = 0x01;
//        }

//        pthread_cond_broadcast(&m_cond);
//        pthread_mutex_unlock(&m_lock);


//        sleep(6);

//    }


    int numready;
    unsigned char buff[CANRXMESSAGESIZE];
    LOGMSG(OUTPUT, ("[canservice] child process running.....\n"));
    while(!m_bExit)
    {
        numready = poll(m_pCanTaskEvent->m_pollfd, 5, 100);

        if ((numready == -1) && (errno == EINTR))
            continue;        //被信号中断，继续等待

        if(numready == -1)
        {
            LOGMSG(OUTPUT, ("[canservice]....system ..error...\n"));
            break;
        }
        else if(numready ==0)//timeout
        {
            ;
        }
        else
        {
            memset(buff, 0, CANRXMESSAGESIZE);

            if(m_pCanTaskEvent->m_pollfd[0].revents & (POLLIN|POLLPRI))//can big data
            {

                m_pCanTaskEvent->m_pollfd[0].revents=0;

                if(read(m_pCanTaskEvent->m_pollfd[0].fd, buff, sizeof(CanMessage))==sizeof(CanMessage))
                {
                    //:/dev/mailbox_test
                    memcpy(&m_CanRxMessage, buff, sizeof(CanMessage));

                    LOGMSG(OUTPUT, ("receive CAN message CanData_12A %02x %02x \tCanData_17D %02x %02x\tCanData_1E5 %02x %02x %02x %02x %02x %02x %02x %02x\tCanData_1F1 %02x %02x !!!\n",
                            m_CanRxMessage.CanData_12A.Data[0],
                            m_CanRxMessage.CanData_12A.Data[1],
                            m_CanRxMessage.CanData_17D.Data[0],
                            m_CanRxMessage.CanData_17D.Data[1],
                            m_CanRxMessage.CanData_1E5.Data[0],
                            m_CanRxMessage.CanData_1E5.Data[1],
                            m_CanRxMessage.CanData_1E5.Data[2],
                            m_CanRxMessage.CanData_1E5.Data[3],
                            m_CanRxMessage.CanData_1E5.Data[4],
                            m_CanRxMessage.CanData_1E5.Data[5],
                            m_CanRxMessage.CanData_1E5.Data[6],
                            m_CanRxMessage.CanData_1E5.Data[7],
                            m_CanRxMessage.CanData_1F1.Data[0],
                            m_CanRxMessage.CanData_1F1.Data[1]));

                    if((m_CanRxMessage.CanData_1E5.Data[0]&0x80) == 0)//valid
                    {
                        short tmp = (m_CanRxMessage.CanData_1E5.Data[1] << 8 | m_CanRxMessage.CanData_1E5.Data[2]);

                        short ang = (tmp*0.0625);

                        NOTIFY_OBSERVER(SIGNAL_TO_CLIENT, OP_TYPE_SIGNAL_SINGLE_DATA, id_steer_rotation, (int)ang);

                        LOGMSG(OUTPUT, ("[%s:%d]receive ang %d sucessed!!!\n", __FUNCTION__, __LINE__, ang));
                    }
                    else
                    {
                        //此处接收到自动化ID的
                        pthread_mutex_lock(&m_lock);
                        m_testData =  (int)*buff;
                        pthread_cond_signal(&m_cond);
                        pthread_mutex_unlock(&m_lock);
                        //end
                        LOGMSG(OUTPUT, ("[%s:%d]receive invalid ang data!!!\n", __FUNCTION__, __LINE__));
                    }
                }
            }
            else if(m_pCanTaskEvent->m_pollfd[1].revents & (POLLIN|POLLPRI))
            {
                uint32_t *pstatus = NULL;

                struct rpmsg_mm_msg_hdr * pdata;

                m_pCanTaskEvent->m_pollfd[1].revents=0;

                int bytes = read(m_pCanTaskEvent->m_pollfd[1].fd, buff,128);

                //LOGMSG(OUTPUT, ("[recive data from '\"'/dev/rpmsg_mm0'\"']bytes:%d, len:%d\n",bytes, pdata->len));

                if (bytes >= pdata->len)
                {
                    pdata = (struct rpmsg_mm_msg_hdr *)buff;

                    pstatus = (uint32_t *)&pdata->data[0];

                    if(*pstatus == 1)
                    {
                        m_iRvc_status = Camera_On;
                        NOTIFY_OBSERVER(SIGNAL_TO_CLIENT, OP_TYPE_SIGNAL_SINGLE_DATA, id_rvc_status, CAMERA_RVC_ON);
                    }
                    else if(*pstatus == 0)
                    {
                        m_iRvc_status = Camera_Off;
                        NOTIFY_OBSERVER(SIGNAL_TO_CLIENT, OP_TYPE_SIGNAL_SINGLE_DATA, id_rvc_status, CAMERA_RVC_OFF);
                    }
                }
            }
            else if(m_pCanTaskEvent->m_pollfd[2].revents & (POLLIN|POLLPRI))
            {
                struct rpmsg_css_msg data;

                m_pCanTaskEvent->m_pollfd[2].revents=0;

                read(m_pCanTaskEvent->m_pollfd[2].fd, &data, sizeof(struct rpmsg_css_msg));

                //LOGMSG(OUTPUT, ("[recive data from '\"'/dev/rpmsg_css0'\"']bytes:%d\n",bytes));

                //if (bytes >= 128)
                {
                    //LOGMSG(OUTPUT, ("[%s:%d]css0 id:%d, data:%d\n", __FUNCTION__, __LINE__, data.id, data.data));
                    if(m_iRvc_status == Camera_On)
                    {//at the WULING.QINGDAO car factory 2019.09.16
                        if(data.id ==id_key_phone ||
                                data.id ==id_key_phone_end ||
                                data.id ==id_power_status ||
                                data.id ==id_rvc_status)
                        {
                            NOTIFY_OBSERVER(SIGNAL_TO_CLIENT, OP_TYPE_SIGNAL_SINGLE_DATA, data.id, data.data);
                        }
                    }
                    else
                    {
                        NOTIFY_OBSERVER(SIGNAL_TO_CLIENT, OP_TYPE_SIGNAL_SINGLE_DATA, data.id, data.data);
                    }
                }
            }
            else if(m_pCanTaskEvent->m_pollfd[3].revents & (POLLIN))
            {
                memset(buff, 0, CANRXMESSAGESIZE);
                int readn = read(m_pCanTaskEvent->m_pollfd[3].fd, buff, sizeof(struct input_event));
                if (readn <= 0)
                {
                    continue;
                }
                struct input_event *my_event=(struct input_event*)buff;
                if(my_event->type == EV_REL)
                {
                    if(my_event->code == REL_Y)
                    {
                        //music
                        //if(m_iRvc_status !=Camera_On)
                        {//at the WULING.QINGDAO car factory 2019.09.16
                            NOTIFY_OBSERVER(SIGNAL_TO_CLIENT, OP_TYPE_SIGNAL_MUSIC_KNOB, -(my_event->value), -1);
                        }
                    }
                }
            }
            else if(m_pCanTaskEvent->m_pollfd[4].revents & POLLIN)
            {
                memset(buff, 0, CANRXMESSAGESIZE);
                int readn = read(m_pCanTaskEvent->m_pollfd[4].fd, buff, sizeof(struct input_event));
                if (readn <= 0)
                {
                    continue;
                }
                struct input_event *my_event=(struct input_event*)buff;
                if(my_event->type == EV_REL)
                {
                    //volume
                    NOTIFY_OBSERVER(SIGNAL_TO_CLIENT, OP_TYPE_SIGNAL_VOLUME_KNOB, -(my_event->value), -1);
                }
            }
        }
    }

    return TRUE;
}
