#include "cantaskevent.h"
#include "log.h"

bool CanTaskEvent::Init()
{
    int loop = 3;
    while(loop)
    {
        m_writefd = open(CSS0_PATH, O_RDWR);
        if(m_writefd ==-1)
        {
            usleep(10000);
            loop--;
        }
        else
        {
            break;
        }
    }
    loop = 3;
    while(loop)
    {
        m_rvcfd = open(RVC_PATH, O_RDONLY);
        if(m_rvcfd ==-1)
        {
            usleep(10000);
            loop--;
        }
        else
        {
            break;
        }
    }
//    loop = 3;
//    while(loop)
//    {
//        m_css0fd = open(CSS0_PATH, O_RDONLY);
//        if(m_css0fd ==-1)
//        {
//            usleep(10000);
//            loop--;
//        }
//        else
//        {
//            break;
//        }
//    }
    m_event1_fd = open(EVENT_1_PATH, O_RDONLY);
    m_event2_fd = open(EVENT_2_PATH, O_RDONLY);


    m_pollfd[0].fd = m_writefd;
    m_pollfd[1].fd = m_rvcfd;
    m_pollfd[2].fd = m_css0fd;
    m_pollfd[3].fd = m_event1_fd;
    m_pollfd[4].fd = m_event2_fd;

    m_pollfd[0].events = (POLLIN | POLLPRI);
    m_pollfd[1].events = (POLLIN | POLLPRI);
    m_pollfd[2].events = (POLLIN | POLLPRI);
    m_pollfd[3].events = (POLLIN);
    m_pollfd[4].events = (POLLIN);

//    return (m_writefd >1&&
//            m_readfd >1&&
//            m_rvcfd >1&&
//            m_css0fd >1&&
//            m_event1_fd >1&&
//            m_event2_fd >1);

    return true;
}

void CanTaskEvent::Deinit()
{
//    ::close(m_css0fd);
    ::close(m_rvcfd);
    ::close(m_writefd);
    ::close(m_event1_fd);
    ::close(m_event2_fd);
}

void CanTaskEvent::Sendevent(int event)
{
    int  retval;
    enum rpmsg_mm_rvc_debug_mode mode;
    switch (event)
    {
    case STOP_ANIM:
        ioctl(m_rvcfd,RPMSG_MM_IOC_STOP_ANIM,&retval);
        break;
    case START_RVC:
        ioctl(m_rvcfd, RPMSG_MM_IOC_START_RVC, &retval);
        break;
    case STOP_RVC:
        ioctl(m_rvcfd, RPMSG_MM_IOC_STOP_RVC, &retval);
        break;
    case RVC_NORMAL:
        mode = RVC_DEBUG_MODE_NORMAL;
        ioctl(m_rvcfd, RPMSG_MM_IOC_RVC_DEBUG_MODE, &mode);
        break;
    case RVC_MANUAL_TOGGLING:
        mode = RVC_DEBUG_MODE_MANUAL_TOGGLING;
        ioctl(m_rvcfd, RPMSG_MM_IOC_RVC_DEBUG_MODE, &mode);
        break;
    case RVC_AUTO_TOGGLING:
        mode = RVC_DEBUG_MODE_AUTO_TOGGLING;
        ioctl(m_rvcfd, RPMSG_MM_IOC_RVC_DEBUG_MODE, &mode);
        break;
    default:
        break;
    }
}

bool CanTaskEvent::Write2MCU(unsigned int msgID, unsigned int param)
{
    if(-1 != m_writefd)
    {
//        m_data.dlen=8;
//        m_data.hlen=8;
        m_data.id=msgID;
        m_data.data=param;

        write(m_writefd, &m_data, sizeof(write_data));

        return true;
    }
    else
    {
        return false;
    }
}

bool CanTaskEvent::Write2MCU(unsigned int msgID, unsigned char data[], int size)
{
    if(-1 != m_writefd)
    {
        m_canData.dlen=8;
        m_canData.hlen=8;
        m_canData.id=msgID;
        memcpy(m_canData.data, data, sizeof(unsigned char)*size);

        write(m_writefd, &m_canData, sizeof(can_data));
        return true;
    }
    else
    {
        return false;
    }
}
