#include "cantaskevent.h"
#include "canservice.h"
#include "log.h"
//#include "observer.h"
//#include "gdbusiface.h"
#include <time.h>
#include <stdio.h>
#include <string>
#include <linux/input.h>
#include <sys/prctl.h>
#include <common.h>

#define CANRXMESSAGESIZE    168

CanTaskEvent *m_pCanTaskEvent;

BOOL CanService::Init()
{
    memset(mReceiveData, 0, PackageLen);
    m_pCanTaskEvent = GET_SINGLETON_INSTANCE(CanTaskEvent);

    bool ret = m_pCanTaskEvent->Init();

    pthread_cond_init(&m_cond, NULL);
    pthread_mutex_init(&m_lock, NULL);

    if(ret)
    {
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

BOOL CanService::Processing()
{
    prctl(PR_SET_NAME,"*****THREAD1");

    int longCommand=0;
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
                printf("[<<<<%s  %d>>>>]\n", __FUNCTION__, __LINE__);
                struct rpmsg_css_msg data;

                memset(&data, 0, sizeof(rpmsg_css_msg));

                read(m_pCanTaskEvent->m_pollfd[0].fd, &data, sizeof(struct rpmsg_css_msg));

                if(id_factory_low == data.id || id_factory_high == data.id)
                {
                    printf("ID:::::%d\n", data.id);
                    printf("DATA:::::%X\n", data.data);

                    if(id_factory_low == data.id)
                    {
                        memset(mReceiveData, 0, PackageLen);
                        memcpy(mReceiveData, &data.data, sizeof(int));
                    }
                    else if(id_factory_high == data.id)
                    {
                         pthread_mutex_lock(&m_lock);
                         memcpy(mReceiveData+4, &data.data, sizeof(int));
                         if((1==mReceiveData[1]%16) && (0xFE == mReceiveData[0]))
                         {
                             printf("<<<<<<<<FillDIDData>>>>>>>>\n");
                             longCommand = (mReceiveData[2]<<8)+ mReceiveData[3];
                             FillDIDData(longCommand, mReceiveData, strlen((char*)mReceiveData));
                         }
                         else
                         {
                             pthread_cond_signal(&m_cond);
                         }
                         pthread_mutex_unlock(&m_lock);


                         printf("[<<<<%s  %d>>>>]\n", __FUNCTION__, __LINE__);
                    }
                }
                else
                {
                    memset(&data, 0, sizeof(rpmsg_css_msg));
                }
            }

            else if(m_pCanTaskEvent->m_pollfd[1].revents & (POLLIN|POLLPRI))
            {
                m_pCanTaskEvent->m_pollfd[1].revents=0;
                read(m_pCanTaskEvent->m_pollfd[1].fd, buff,128);
                printf("[<<<<%s  %d>>>>]\n", __FUNCTION__, __LINE__);
            }
            else if(m_pCanTaskEvent->m_pollfd[2].revents & (POLLIN|POLLPRI))
            {

            }
            else if(m_pCanTaskEvent->m_pollfd[3].revents & (POLLIN))
            {
                printf("[<<<<%s  %d>>>>]\n", __FUNCTION__, __LINE__);

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
//                            NOTIFY_OBSERVER(SIGNAL_TO_CLIENT, OP_TYPE_SIGNAL_MUSIC_KNOB, -(my_event->value), -1);
                        }
                    }
                }
            }
            else if(m_pCanTaskEvent->m_pollfd[4].revents & POLLIN)
            {
                printf("[<<<<%s  %d>>>>]\n", __FUNCTION__, __LINE__);

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
//                    NOTIFY_OBSERVER(SIGNAL_TO_CLIENT, OP_TYPE_SIGNAL_VOLUME_KNOB, -(my_event->value), -1);
                }
            }

        }
    }

    return TRUE;
}


void CanService::FillDIDData(int command, uint8_t* data, int len)
{
    uint8_t buf[len+1] = {0};
    memcpy(buf, data, len);

    switch (command)
    {
    case DID_SW_VERSION:
        printf(">>>>>DID_SW_VERSION<<<<<<");
        AppendData(m_softwareVersion, data, SoftWareVer_Len, len);
        if(SoftWareVer_Len == strlen((char*)m_softwareVersion))
        {
            for(int i=0; i<SoftWareVer_Len; i++)
                printf("m_softwareVersion[%d]::: %X\n", i, m_softwareVersion[i]);

            pthread_cond_signal(&m_cond);
        }
        break;

    case DID_HW_VERSION:
        printf(">>>>>DID_HW_VERSION<<<<<<");
        AppendData(m_hardwareVersion, data, HardWareVer_Len, len);
        if(HardWareVer_Len == strlen((char*)m_hardwareVersion))
        {
             for(int i=0; i<HardWareVer_Len; i++)
                printf("m_hardwareVersion[%d]:::  %X\n", i, m_hardwareVersion[i]);

             pthread_cond_signal(&m_cond);

        }
        break;

    case DID_V2X_VERSION:
        printf(">>>>>DID_V2X_VERSION<<<<<<");
        AppendData(m_v2xVersion, data, V2XVer_Len, len);
        if(V2XVer_Len == strlen((char*)m_v2xVersion))
        {
            for(int i=0; i<V2XVer_Len; i++)
                printf("m_v2xVersion[%d]:::  %X\n", i, m_v2xVersion[i]);

            pthread_cond_signal(&m_cond);


        }
        break;

    case DID_HP_VERSION:
        AppendData(m_highAccuracyVersion, data, HighAccuracyVer_Len, len);

        if(HighAccuracyVer_Len == strlen((char*)m_highAccuracyVersion))
        {
            printf(">>>>>DID_HP_VERSION<<<<<<\n");
            for(int i=0; i<HighAccuracyVer_Len; i++)
                printf("m_highAccuracyVersion[%d]::: %X\n", i, m_highAccuracyVersion[i]);

            pthread_cond_signal(&m_cond);
        }
        break;

    case DID_APP_VERSION:
        printf(">>>>>DID_APP_VERSION<<<<<<");
        AppendData(m_appVersion, data, AppVer_Len, len);
        if(AppVer_Len == strlen((char*)m_appVersion))
        {
            for(int i=0; i<AppVer_Len; i++)
                printf("m_appVersion[%d]::: %X\n", i, m_appVersion[i]);

            pthread_cond_signal(&m_cond);
        }
        break;

    default:
        break;
    }
}

void CanService::AppendData(uint8_t* des, uint8_t* data, int d_len, int s_len)
{
    if(NULL!=des && NULL!=data && d_len>0 && s_len>0 && 1==data[1]%16)
    {
        switch (data[1]/10)
        {
        case 0x00:
            if(d_len>=3)
                memcpy(des, &data[5], 3);
            else
                memcpy(des, &data[5], d_len-strlen((char*)des));
            break;

        case 0x01:
            if(d_len>=7)
                memcpy(des+3, &data[4], 4);
            else
                memcpy(des+3, &data[4], d_len-strlen((char*)des));
            break;

        case 0x02:
            if(d_len>=11)
                memcpy(des+7, &data[4], 4);
            else
                memcpy(des+7, &data[4], d_len-strlen((char*)des));
            break;

        case 0x03:
            if(d_len>=19)
                memcpy(des+11, &data[4], 4);
            else
                memcpy(des+11, &data[4], d_len-strlen((char*)des));
            break;

        case 0x04:
            if(d_len>=19)
                memcpy(des+15, &data[4], 4);
            else
                memcpy(des+15, &data[4], d_len-strlen((char*)des));
            break;

        case 0x05:
            if(d_len>=23)
                memcpy(des+19, &data[4], 4);
            else
                memcpy(des+19, &data[4], d_len-strlen((char*)des));
            break;

        case 0x06:
            if(d_len>=27)
                memcpy(des+23, &data[4], 4);
            else
                memcpy(des+23, &data[4], d_len-strlen((char*)des));
            break;

        case 0x07:
            if(d_len>=31)
                memcpy(des+27, &data[4], 4);
            else
                memcpy(des+27, &data[4], d_len-strlen((char*)des));
            break;

        case 0x08:
            if(d_len>=35)
                memcpy(des+31, &data[4], 4);
            else
                memcpy(des+31, &data[4], d_len-strlen((char*)des));
            break;

        default:
            break;
        }
    }
    else
    {
        printf("[ %s  %d]\n", __FUNCTION__, __LINE__);
    }
}
