#ifndef COMMON_H
#define COMMON_H
#include <string>
#include <QString>

using namespace std;

#define TEST_MAX_ITEM    30
#define TEST_MAX_QRSHOW  16
#define TagLen 8

#define CANID_H 0xF185
#define CANID_L 0xF188

#define HardWareVer_Len 6
#define SoftWareVer_Len 6
#define V2XVer_Len 6
#define HighAccuracyVer_Len 6
#define AppVer_Len 6
#define MacAddress_len 17

#define WIFIName_Len 12
#define IPAdress_len 4
#define SupplyNumber_Len 4
#define ProductDate_Len 6
#define VINCode_Len 17


#define id_factory_low 38//94
#define id_factory_high 39//95
#define id_send_factory_low 40
#define id_send_factory_high 41

#define MAILBOX_PATH            "/dev/mailbox_test"
#define RPMSG_CSS0_PATH         "/dev/rpmsg_css0"
#define MAX_POLL_EVENT          (1)
#define CAN_HEADER_LEN           8
#define CAN_DATA_LEN             4

typedef struct _mailbox_write_msg_tag
{
    uint32_t  hlc;//4
    uint8_t   header[CAN_HEADER_LEN];//8
    uint32_t  dlc;//4
    uint32_t  canId;//4
    uint16_t  cmdId;//2
    uint16_t  dataHeader;//2
    uint8_t   data[CAN_DATA_LEN];//4
}Mailbox_Write_Msg_ST;

typedef struct _mailbox_read_msg_tag
{
    uint32_t  canId;//4
    uint8_t   data[CAN_DATA_LEN];//4
    uint16_t  dataHeader;//2
    uint16_t  cmdId;//2
}Mailbox_Read_Msg_ST;

enum{
    QR_HIDE = 0,
    QR_SHOW = 1,
};

enum{
    DID_WRITE_DATA_ONE_FAIL,
    DID_WRITE_DATA_TWO_FAIL,
    DID_WRITE_DATA_THREE_FAIL,
    DID_WRITE_DATA_FOUR_FAIL,
};

typedef enum _project_info_tag
{
    DID_SW_VERSION     = 0xF184,
    DID_HW_VERSION     = 0xF185,
    DID_VIN            = 0xF190,
    DID_PRODUCED_DATE  = 0xF191,
    DID_V2X_VERSION    = 0xF1A0,
    DID_HP_VERSION     = 0xF1A1,
    DID_APP_VERSION    = 0xF1B0,
    DID_SUPPLIER       = 0xF170,
    DID_IP_ADDR        = 0xF180,
    DID_WIFI_AP_NAME   = 0xF181
}PROJECT_INFO_EN;

typedef enum _test_mode_tag
{
    TEST_FACTORY_MODULE     = 0xFF01,
    TEST_FACTORY_CHECK      = 0xFF03,

    TEST_DID_READ           = 0xFE01,
    TEST_DID_WRITE          = 0xFE02,

    TEST_CAN_MODULE         = 0xFD00,
    TEST_WATCHDOG_MODULE    = 0xFD01,
    TEST_ETHERNET_MODULE    = 0xFD02,
    TEST_WIFI_MODULE        = 0xFD03,
    TEST_6AXIS_MODULE       = 0xFD04,
    TEST_V2X_MODULE         = 0xFD05,
    TEST_USB_MODULE         = 0xFD06,
    TEST_4GUART_MODULE      = 0xFD07,//
    TEST_4GWAKE_MODULE      = 0xFD08,//
    TEST_4GIOT_MODULE       = 0xFD09,
    TEST_GPS_MODULE         = 0xFD0A,
    TEST_SYATEM_SLEEP_MODULE= 0xFD0C,
    TEST_PWR_MODULE         = 0xFD0D,

    TEST_MIC_MODULE         = 0xFC01,//
    TEST_SPK_MODULE         = 0xFC02,
    TEST_RS232_MODULE       = 0xFC03,
    TEST_GPIO_MODULE        = 0xFC04,
    TEST_ADC_MODULE         = 0xFC05,
    TEST_VIN_WRITE          = 0xFC06,
    TEST_PD_TIME_WRITE      = 0xFC07,

    TEST_QR_SHOW            = 0xFB01
}Test_Mode_EN;

enum{
    ErrorCodeCan = 10,
    ErrorCodeIVI = 20,
    ErrorCodePower = 30,
    ErrorCodeMIC = 40,
    ErrorCodeSecret = 50,
    ErrorCodeWIFI = 60,
    ErrorCodeSixAxisSensor = 70,
    ErrorCodeV2XCommunicate = 90,
    ErrorCodeM34GCommunicate = 110,
    ErrorCodeGPIO = 120,
    ErrorCodeGPS = 80,
    ErrorCode4GTest = 130,
    ErrorCodeACC = 100,
    ErrorCodeUSBRW = 140,
    ErrorCodeRS232 = 150,



    ErrorCodeSoftWare = 200,
    ErrorCodeHardWare = 201,
    ErrorCodeV2XVersion = 202,
    ErrorCodeHighAccuracyVersion = 203,
    ErrorCodeAPPVersion = 204,
    ErrorCodeMacAddress = 205,
    ErrorCodeVINCode = 207,
    ErrorCodeDate = 208,
    ErrorCodeSupplayNumber = 209,
    ErrorCodeWIFIName = 210,
    ErrorCodeIPAdress = 211,

    ErrorFactory = 300,
};

typedef enum _test_result_tag{

    TESTRESULT_FAIL = 0,
    TESTRESULT_OK

}TESTRESULT;




typedef struct _qrcode_show_flag_tag
{
    uint8_t Bit16:1;
    uint8_t Bit15:1;
    uint8_t Bit14:1;
    uint8_t Bit13:1;
    uint8_t Bit12:1;
    uint8_t Bit11:1;
    uint8_t Bit10:1;
    uint8_t Bit9:1;
    uint8_t Bit8:1;
    uint8_t Bit7:1;
    uint8_t Bit6:1;
    uint8_t Bit5:1;
    uint8_t Bit4:1;
    uint8_t Bit3:1;
    uint8_t Bit2:1;
    uint8_t Bit1:1;
}Qrcode_Show_Flag_ST;


typedef struct _test_item_flag_tag
{
    uint32_t Bit8:1;
    uint32_t Bit7:1;
    uint32_t Bit6:1;
    uint32_t Bit5:1;
    uint32_t Bit4:1;
    uint32_t Bit3:1;
    uint32_t Bit2:1;
    uint32_t Bit1:1;

    uint32_t Bit16:1;
    uint32_t Bit15:1;
    uint32_t Bit14:1;
    uint32_t Bit13:1;
    uint32_t Bit12:1;
    uint32_t Bit11:1;
    uint32_t Bit10:1;
    uint32_t Bit9:1;

    uint32_t Bit24:1;
    uint32_t Bit23:1;
    uint32_t Bit22:1;
    uint32_t Bit21:1;
    uint32_t Bit20:1;
    uint32_t Bit19:1;
    uint32_t Bit18:1;
    uint32_t Bit17:1;

    uint32_t Bit32:1;
    uint32_t Bit31:1;
    uint32_t Bit30:1;
    uint32_t Bit29:1;
    uint32_t Bit28:1;
    uint32_t Bit27:1;
    uint32_t Bit26:1;
    uint32_t Bit25:1;
}Test_Item_Flag_ST;

#endif // COMMON_H
