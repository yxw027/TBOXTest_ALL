#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>

#ifndef BOOL
typedef int BOOL;
#endif

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE 
#define FALSE (0)
#endif

#define __THREAD_PRIORITY__ (99)
#define __THREAD_TV_SEC__VAL__ (1) //second
#define __THREAD_TV_NSEC_VAL__ (0) //nano second

class CThread
{
public:
	CThread();
	virtual ~CThread();
    virtual BOOL Processing() = 0;
    virtual BOOL TimeoutProcessing();
	
protected:
    inline void Lock();
    inline void Unlock();

public:
    static void Sleep(int microseconds);//use select function to implicate sleep
		
protected:
    virtual BOOL CreateThread(int tv_sec_val = __THREAD_TV_SEC__VAL__ /*seconds*/,
                              long tv_nsec_val = __THREAD_TV_NSEC_VAL__, /*nano second*/
                              BOOL bCreateRun = TRUE);//bCreateRun=FALSE表示：仅仅创建线程，并让线程处于wait状态，有设置wait的超时时间
	//bCreateRun=TRUE 表示创建线程并立即使其运行
    virtual void InformThread();//向线程发送事件，使其执行具体的任务
	virtual void KillThread();//结束线程
	
protected:
    volatile BOOL   	m_bIsRunning;//线程的过程函数是否已经运行起来
    volatile BOOL 		m_bExit;//控制线程运行状态
    pthread_t           m_hMainThread;//parent thread ID


private:
    pthread_t 			m_hThread;//child线程ID
    pthread_mutex_t 	m_hMutex;//线程互斥
    pthread_cond_t 		m_hEvtThread;//线程的事件
	pthread_condattr_t 	m_hCondAttr;//线程条件属性
    pthread_attr_t      m_attr_thread;//线程属性
    int                 m_tv_sec_val;
    long                m_tv_nano_val;
	
private:
	virtual void SetThreadAttribute();//设置线程属性，比如线程优先级，线程的栈空间大小，是否是游离线程等
	virtual void InitCondAttribute();//主要是设置了
	static void* ThreadProcess(void *lpArg);//线程主函数
};


#endif

