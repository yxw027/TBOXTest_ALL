#include "thread.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>
#include <errno.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>

CThread::CThread()
{
    m_bExit = TRUE;

    m_bIsRunning = FALSE;

    m_hThread = 0;

//    pthread_mutex_init(&m_hMutex, NULL);

    SetThreadAttribute();//set thread attribute->priority etc.

    InitCondAttribute();//set condition attribute->clock monotonic etc.
}

CThread::~CThread()
{
    KillThread();
    pthread_attr_destroy(&m_attr_thread);
//    pthread_mutex_destroy(&m_hMutex);
    pthread_condattr_destroy(&m_hCondAttr);
//    pthread_cond_destroy(&m_hEvtThread);
    //printf("%s..%d..\n",__FUNCTION__,__LINE__);
}

BOOL CThread::CreateThread(int tv_sec_val ,
                           long tv_nsec_val,
                           BOOL bCreateRun)
{
    int ret = 0;

    m_hMainThread = pthread_self();

    if(0 == m_hThread)
    {
        m_bExit = FALSE;
        printf("%s..%d..\n",__FUNCTION__,__LINE__);

        ret = pthread_create(&m_hThread, NULL, ThreadProcess, this);

        if(ret != 0)
        {
            m_bExit = TRUE;

            printf("%s..%d..%s\n",__FUNCTION__,__LINE__,strerror(ret));
        }
        else
        {
            while(!m_bIsRunning)
            {
                usleep(50000);
            }
            if(bCreateRun)
            {
                InformThread();
            }
        }

        m_tv_sec_val = tv_sec_val;
        m_tv_nano_val = tv_nsec_val;
    }
    return (0==ret)?TRUE:FALSE;
}

void CThread::KillThread()
{
    if(m_hThread != 0)
    {
        m_bExit = TRUE;
//        pthread_cond_signal(&m_hEvtThread);
        pthread_join(m_hThread, NULL);//NULL
        m_hThread = 0;
        m_bIsRunning = FALSE;
    }
}

void CThread::InformThread()
{
    Lock();

    m_bExit = FALSE;

    pthread_cond_signal(&m_hEvtThread);

    Unlock();
}

void *CThread::ThreadProcess(void *pArg)
{
    pthread_t tid = pthread_self();
    printf("[ %s  %d ]    tid2: %lu     \n", __FUNCTION__, __LINE__, (int)tid);

    pthread_detach(pthread_self());

    CThread *pThis = (CThread *)pArg;

    if(pThis != NULL)
    {

        struct timespec timeout_val;

        pthread_detach(pthread_self());

        pThis->m_bIsRunning = TRUE;

        printf("child thread process runing.\n");

        for(;!pThis->m_bExit;)
        {
            clock_gettime(CLOCK_MONOTONIC, &timeout_val);

            timeout_val.tv_sec += pThis->m_tv_sec_val;

            timeout_val.tv_nsec += pThis->m_tv_nano_val;

            pThis->Lock();

            int ret = pthread_cond_timedwait(&(pThis->m_hEvtThread), &(pThis->m_hMutex), &timeout_val);

            if(!pThis->m_bExit)
            {
                switch(ret)
                {
                case 0:
                {

                    pThis->Processing();
                }
                    break;
                case ETIMEDOUT:
                {
//                    printf("%s..%d..\n",__FUNCTION__,__LINE__);
                    pThis->TimeoutProcessing();
                }
                    break;
                default:
                    //printf("%s..%d..%s.\n",__FUNCTION__,__LINE__, strerror(ret));
                    break;
                }
            }
            else
            {
                pThis->Unlock();
                break;
            }
            pThis->Unlock();
        }
    }


    return (void*)0;
}

BOOL CThread::TimeoutProcessing()
{
    //printf("%s..%d..time out.\n",__FUNCTION__,__LINE__);

    return TRUE;
}

void CThread::Sleep(int microseconds)
{
    struct timeval tempval;
    int secconds = microseconds / 1000000;
    tempval.tv_sec = secconds;
    tempval.tv_usec = microseconds-(secconds * 1000000);
    select(0, NULL, NULL, NULL, &tempval);
}

inline void CThread::Lock()
{
//    pthread_mutex_lock(&m_hMutex);
}

inline void CThread::Unlock()
{
//    pthread_mutex_unlock(&m_hMutex);
}

void CThread::InitCondAttribute()
{
    int ret = pthread_condattr_init(&m_hCondAttr);
    if(0 == ret)
    {
        ret = pthread_condattr_setclock(&m_hCondAttr, CLOCK_MONOTONIC);//设置事件的参考时钟为系统开机时刻，为接下来的pthread_cond_timedwait调用起到超时控制之用。
        if(ret != 0)
        {
            printf("%s..%d..%s\n",__FUNCTION__,__LINE__,strerror(ret));
        }
        else
        {
            ret = pthread_cond_init(&m_hEvtThread, &m_hCondAttr);
            if(ret != 0)
                printf("%s..%d..%s\n",__FUNCTION__,__LINE__,strerror(ret));
            //else
            //printf("%s..%d..%s\n",__FUNCTION__,__LINE__,strerror(ret));
        }
    }
    else
    {
        printf("%s..%d..%s\n",__FUNCTION__,__LINE__,strerror(ret));
    }
}

void CThread::SetThreadAttribute()
{
    int ret, inherit, policy;

    struct sched_param tparam;

    pthread_attr_init(&m_attr_thread);

    pthread_attr_setdetachstate(&m_attr_thread, PTHREAD_CREATE_DETACHED);//设置线程为游离线程，即线程资源的回收可以交给系统自己完成，无需在
    //调用pthread_join函数等待线程退出

    ret = pthread_attr_getinheritsched(&m_attr_thread, &inherit);

    if(0 == ret)
    {
        uid_t id = getuid();
        //printf("user id %d\n",id);
        if(id != 0)//not root user
        {
            if(PTHREAD_EXPLICIT_SCHED == inherit)
                inherit = PTHREAD_INHERIT_SCHED;
            policy = SCHED_OTHER;//SCHED_FIFO,SCHED_RR,SCHED_OTHER
        }
        else //root user
        {
            if(PTHREAD_INHERIT_SCHED == inherit)
                inherit = PTHREAD_EXPLICIT_SCHED;
            policy = SCHED_FIFO;//SCHED_FIFO,SCHED_RR,SCHED_OTHER
        }
        ret = pthread_attr_setinheritsched(&m_attr_thread, inherit);//root user.必须设置为PTHREAD_EXPLICIT_SCHED属性,否则，设置的SCHED_FIFO属性不起作用
        if(0 == ret)
        {
            ret = pthread_attr_setschedpolicy(&m_attr_thread, policy);//
            if(0==ret && policy!=SCHED_OTHER)//just for root user
            {
                tparam.sched_priority = __THREAD_PRIORITY__;
                ret = pthread_attr_setschedparam(&m_attr_thread, &tparam);
                if(0 == ret)
                {
                    //printf("%s..%d..success.\n",__FUNCTION__,__LINE__);
                }
                else
                    printf("%s..%d..%s\n",__FUNCTION__,__LINE__,strerror(ret));
            }
            else
                printf("%s..%d..%s\n",__FUNCTION__,__LINE__,strerror(ret));
        }
        else
            printf("%s..%d..%s\n",__FUNCTION__,__LINE__,strerror(ret));
    }
    else
        printf("%s..%d..%s\n",__FUNCTION__,__LINE__,strerror(ret));
}

