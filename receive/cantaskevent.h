#ifndef CANTASKEVENT_H
#define CANTASKEVENT_H

//#include "cantaskmsg.h"
#if defined(__cplusplus)
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <stropts.h>
#include <sys/poll.h>
#include <sys/stropts.h>
#include <sys/ioctl.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <poll.h>
}
#include "singletonbase.h"

#define MAILBOX_PATH    "/dev/mailbox_test"
#define RVC_PATH    "/dev/rpmsg_mm0"
#define CSS0_PATH   "/dev/rpmsg_css0"
#define EVENT_1_PATH "/dev/input/event1"
#define EVENT_2_PATH "/dev/input/event2"
#define RPMSG_MM_REARGEAR_STATUS_ACK 14

#define RPMSG_MM_IOC_MAGIC      'L'

#define RPMSG_MM_IOC_GET_RG_STATUS  _IOR(RPMSG_MM_IOC_MAGIC, 1, int)
#define RPMSG_MM_IOC_STOP_ANIM	  	_IOW(RPMSG_MM_IOC_MAGIC, 2, int)
#define RPMSG_MM_IOC_STOP_RVC		_IOW(RPMSG_MM_IOC_MAGIC, 3, int)
#define RPMSG_MM_IOC_START_RVC		_IOW(RPMSG_MM_IOC_MAGIC, 4, int)
#define RPMSG_MM_IOC_RVC_DEBUG_MODE	_IOW(RPMSG_MM_IOC_MAGIC, 5, int)

class CanMsgEventThread;

enum user_event {
    STOP_ANIM,
    START_RVC,
    STOP_RVC,
    RVC_NORMAL,
    RVC_MANUAL_TOGGLING,
    RVC_AUTO_TOGGLING
};

enum rpmsg_mm_rvc_debug_mode {
    RVC_DEBUG_MODE_NORMAL, /*!< rear gear controlled by GPIO input */
    RVC_DEBUG_MODE_MANUAL_TOGGLING, /*!< rear gear toggling on demand */
    RVC_DEBUG_MODE_AUTO_TOGGLING /*!< rear gear toggling periodically */
};

struct write_data{
//  unsigned int hlen;
//  unsigned char hbuf[8];
//  unsigned int dlen;
  unsigned int id;
  unsigned int data;
};

struct can_data{
  unsigned int hlen;
  unsigned char hbuf[8];
  unsigned int dlen;
  unsigned int id;
  unsigned char data[8];
};

struct rpmsg_mm_msg_hdr {
    int info;
    int len;
    char data[0];
};

struct rpmsg_css_msg {
    int id;
    int data;
};


class CanTaskEvent
{
    REGISTER_SINGLETON(CanTaskEvent)
    friend class CanService;

public:
    bool Init();
    void Deinit();

public:
    bool Write2MCU(unsigned int msgID, unsigned int param);
    bool Write2MCU(unsigned int msgID, unsigned char data[], int size);
    void Sendevent(int event);

private:
    struct pollfd m_pollfd[5];
    struct write_data m_data = {0};
    struct can_data m_canData = {0};
    int m_writefd;
    int m_rvcfd;
    int m_css0fd;
    int m_event1_fd;
    int m_event2_fd;
    int m_log_fd;
};

#endif // CANTASKEVENT_H
