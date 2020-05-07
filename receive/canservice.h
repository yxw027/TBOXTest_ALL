#ifndef CANMSGEVENTTHREAD_H
#define CANMSGEVENTTHREAD_H
#include "thread.h"
#include "singletonbase.h"
#include <string>
#include "common.h"
using namespace std;
#define PackageLen 8

typedef union
{
    unsigned char Data[8];
}CanData;

#define CAMERA_RVC_ON 1
#define CAMERA_RVC_OFF 0

typedef struct can_RX_MESSAGE_Tag
{
    CanData CanData_17D;
    CanData CanData_1E5;
    CanData CanData_12A;
    CanData CanData_1F1;

}CanMessage;


class CanService: public CThread
{
    REGISTER_SINGLETON(CanService)

public:
    pthread_mutex_t m_lock;
    pthread_cond_t m_cond;
    bool m_fillEnoughDIDData;
    uint8_t mReceiveData[PackageLen+1];

    uint8_t m_hardwareVersion[HardWareVer_Len+1];//*********************QR CODE  //DID data
    uint8_t m_softwareVersion[SoftWareVer_Len+1];//***********************QR CODE
    uint8_t m_v2xVersion[V2XVer_Len+1];
    uint8_t m_highAccuracyVersion[HighAccuracyVer_Len+1];
    uint8_t m_appVersion[AppVer_Len+1];
    uint8_t m_macAddress[MacAddress_len+1];

    BOOL Init();
    void Deinit();
    bool SendMsg2MCU(unsigned int msgID, unsigned int param);
    bool SendMsg2MCU(unsigned int msgID, unsigned char param[], int size);
    void Sendevent(int event);
    void FillDIDData(int command, uint8_t* data, int len);
    void AppendData(uint8_t* des, uint8_t* data, int d_len, int s_len);

private:
    CanMessage m_CanRxMessage;

protected:
    BOOL Processing();
};

extern CanService* m_canservice;

#endif // CANMSGEVENTTHREAD_H
