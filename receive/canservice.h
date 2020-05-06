#ifndef CANMSGEVENTTHREAD_H
#define CANMSGEVENTTHREAD_H
#include "thread.h"
#include "singletonbase.h"
#include <string>
using namespace std;




enum
{
    OP_TYPE_SET_WAKE_UP,
    OP_TYPE_SET_MSG_TO_MCU,
    OP_TYPE_SET_EVENT_TO_MCU,
    OP_TYPE_SET_DATA_TO_MCU,
    OP_TYPE_SET_USB_POSITION,
    OP_TYPE_SET_LED_AM_MODE,
    OP_TYPE_SET_LED_FM_MODE,
    OP_TYPE_SET_LED_BT_MODE,
    OP_TYPE_SET_LED_USB_MODE,
    OP_TYPE_SET_CUR_RADIO_FREQ,
    OP_TYPE_SET_USB_MUSIC_INDEX,
    OP_TYPE_SET_BT_MUSIC_MODE,
    OP_TYPE_SET_BT_PHONE_ON,
    OP_TYPE_SET_BT_PHONE_OFF,
    OP_TYPE_SET_START_CLOCK,
    OP_TYPE_SET_STOP_CLOCK,
    OP_TYPE_SET_SHOW_APP_LINK,
    OP_TYPE_SET_FLASH_CLOCK_HOUR,
    OP_TYPE_SET_FLASH_CLOCK_MINUTE,
    OP_TYPE_SET_STOP_FLASH_CLOCK_HOUR,
    OP_TYPE_SET_STOP_FLASH_CLOCK_MINUTE,
    OP_TYPE_SET_CUR_CLOCK_HOUR,
    OP_TYPE_SET_CUR_CLOCK_MINUTE,
    OP_TYPE_SET_12_TIMEFORMAT,
    OP_TYPE_SET_24_TIMEFORMAT,
    OP_TYPE_SET_CUR_VOLUME,
    OP_TYPE_SET_UPDATE_SYS_TIME,
    OP_TYPE_SET_ADD_SYS_TIME_HOUR,
    OP_TYPE_SET_ADD_SYS_TIME_MINUTE,
    OP_TYPE_SET_HI_EQ_MODE,
    OP_TYPE_SET_LOW_EQ_MODE,
    OP_TYPE_SET_CLOSE_ALL_LED,
    OP_TYPE_SET_SHOW_LINE_MODE,
    OP_TYPE_SET_SHOW_SYS_VERSION,
    OP_TYPE_SET_SHOW_RVC,
    OP_TYPE_SET_SHOW_ONE,
    OP_TYPE_SET_SHOW_ALL,
    OP_TYPE_SET_SHOW_RADOM,
    OP_TYPE_SET_SHOW_FIND,
    OP_TYPE_GET_MSG_FROM_MCU,
    OP_TYPE_SET_RESTART_FLASH_HOUR,
    OP_TYPE_SET_RESTART_FLASH_MINUTE,
    OP_TYPE_SET_SHOW_ERR,
    OP_TYPE_SET_SHOW_NOFILE,
    OP_TYPE_SIGNAL_MUSIC_KNOB,
    OP_TYPE_SIGNAL_VOLUME_KNOB,
    OP_TYPE_SIGNAL_CAN_DATA = 0xEF,
    OP_TYPE_SIGNAL_SINGLE_DATA = 0xFE
};


enum LED_MODE
{
    HI = 0,
    USB_MODE_BUT_NOT_IN_SUB_MODE = 0x1,
    USB_NORMAL_MODE = 0x2,
    FM_NORMAL_MODE = 0x3,
    FM_SEEK_MODE = 0x4,
    AM_NORMAL_MODE = 0x5,
    AM_SEEK_MODE = 0x6,
    BT_NORMAL_MODE = 0x7,
    BT_SEEK_MODE = 0x8,
    SET_TIMER_MODE = 0x9
};

enum CHAR_DATA
{
    NONE = 0xFF,
    ZERO = 0xC0,
    ONE = 0xF9,
    TWO = 0xA4,
    THREE = 0xB0,
    FOUR = 0x99,
    FIVE = 0x92,
    SIX = 0x82,
    SEVEN = 0xF8,
    EIGHT = 0x80,
    NINE = 0x90,
    NEG = 0xBF,
    A = 0x88,
    B = 0x83,
    C = 0xC6,
    D = 0xA1,
    E = 0x86,
    F = 0x8E,
    L = 0xC7,
    I = 0xCF,
    H = 0x89,
    N = 0xC8,
    O = 0xC0,
    P = 0x8C,
    r = 0xCD,
    U = 0xC1
};

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

typedef enum {
    btservice_message = -4,
    hmi_get_current_source = -3,
    HardKey_message_id = -2,
    can_message_id = -1,

    id_gear_level_pos =0,
    id_abs_flt_sts, //1
    id_hv_isolation_status,//2
    id_vcam_status,//3
    id_motor_status,//4
    id_motor_over_temp_status,//5
    id_elec_brake_status,//6
    id_elec_steer_status,//7
    id_soc_rank_status,
    id_charger_line_status,
    id_power_batt_connect_status,
    id_power_batt_status,
    id_charger_status,
    id_disconnect_charger_status,
    id_charging_status,
    id_batt_volt_status,
    id_ac_power_out,
    id_estimate_remaining_distance,
    id_motor_power_out,//18
    id_energy_recovery_Level,
    id_vehicle_instance_power_out,
    id_vehicle_average_power_out,
    id_appointment_state_of_charge,
    id_iccid_array_0_3,
    id_iccid_array_4_7,
    id_iccid_array_8_11,//25
    id_iccid_array_12_15,//26
    id_iccid_array_16_19,//27
    id_vin_array_0_3,
    id_vin_array_4_7,
    id_vin_array_8_11,
    id_vin_array_12_15,//31
    id_vin_array_16,//32
    id_province_type,
    id_city_type,
    id_country_type,
    id_weather_type,
    id_temperature_status,
    id_pm25_status,
    id_offsetday_type,//39
    id_year_value,
    id_month_value,
    id_day_value,
    id_hours_value,
    id_minute_value,
    id_second_value,
    id_power_status,//46 equal to acc id
    id_upgrade_status,//47
    id_poweroff_status,//48
    id_key_mode,//49
    id_key_mute,//50
    id_key_pwr,//not use in A7
    id_key_pwrmute,//not use in A7
    id_key_volume_down,//53
    id_key_volume_up,//54
    id_key_phone,//接听 55
    id_key_phone_end, //挂断 56
    id_key_seek_up,//57
    id_key_seek_down,//58
    id_bl_status,//59
    id_rvc_status, //60 // 倒车状态 0 off 1 on
    id_acc_app_start,//61
    id_power_mode, //62
    id_rtc_time,//63
    id_power_startup_status,//64
    id_radio_seek_up,
    id_radio_seek_down,
    id_btmusic_seek_up,
    id_btmusic_seek_down,
    id_usbaudio_seek_up,
    id_usbaudio_seek_down,
    id_usbvideo_seek_up,//71
    id_usbvideo_seek_down,
    id_usbphoto_seek_up,
    id_usbphoto_seek_down, //74
    id_acc_startup_status, //75
    id_reboot_system, //76
    id_led_display,//77
    id_led_mode_set,//78
    id_key_clock,//79
    id_key_music,//80
    id_usbaudio_seek_upup,//81
    id_usbaudio_seek_downdown,//82
    id_usbvideo_seek_upup,//83
    id_usbvideo_seek_downdown, //84
	id_music_knob,
    id_volume_knob,
    id_steer_rotation,
    id_ak8859_addr,
    id_ak8859_value,
    id_usb_status,
    id_source_mode_restore

}EX50_MessageID, *PEX50_CanMessageID;

enum
{
    Camera_Off,
    Camera_On,
    Camera_Unkown
};

class CanService: public CThread
{
    REGISTER_SINGLETON(CanService)

    public:

    pthread_mutex_t m_lock;
    pthread_cond_t m_cond;

    BOOL Init();
    void Deinit();
    bool SendMsg2MCU(unsigned int msgID, unsigned int param);
    bool SendMsg2MCU(unsigned int msgID, unsigned char param[], int size);
    void Sendevent(int event);
    void setPlayerProgress(unsigned int second);//hbx
    //sxd 2019-06-26
    //mode
    void setLEDFMMode(const bool bNormal); //seek false, listen true
    void setLEDAMMode(const bool bNormal);
    void setLEDBTMode(const bool bBtMode); //dev_in not in BT mode false, dev_in and in BT mode true
    void setLEDUSBMode(const bool bUsbMode); //
    void setCloseLEDMode();
    //radio
    void setCurFreq(const int freq, bool bFm);
    //usb
    void setShowUSBIndex(int index);
    void setShowUSBTime(const int seconds);
    //bt
    void setShowBTMusic();
    void setBtPhoneOn();
    void setBtPhonetOff();
    //link
    void showLink();
    void showLine();
    //set time
    void changeTimeMode();
    void setTwelveFormat();
    void setTwentyFourFormat();
    void showCurrentTimeFormat();
    void setFlashHour();
    void setCurrentHour(const int hour);
    void setFlashMinute();
    void setCurrentMinte(const int min);
    void SetstartUpdateTime();
    void SetstopUpdateTime();
    void stopFlashHour();
    void stopFlashMinute();
    //volume
    void showVolume(const int volume);
    void setShowHiEq(int eq);
    void setShowLowEq(int eq);

    void setShowSysVersion(int version);
    void setShowRearVideoCamera();
    void setShowOne();
    void setShowAll();
    void setShowRadom();
    void setShowFind();

    //xxx
    void showErr();
    void showNOFile();

    //hbx
    void updateSysTime();
    void addSysTimeHour(bool add);//true add;false sub
    void addSysTimeMinute(bool add);//true add;false sub
    void RestartFlashHour();
    void RestartFlashMinute();

private:
    int changeTable(int param);
    void setLEDMode(LED_MODE mode);
    void startTimer(int id);
    void setCurHour();
    void setCurMinute();

public:
    int m_testData;
    int m_iTimeTimer;
    int m_iHourTimer;
    int m_iMinTimer;

    int m_iTimeMode;
    int m_iSetTimeMode; //0 format, 1 hour, 2 minute
    string m_sCurHour;
    string m_sCurMinute;
    int m_iCurHour;
    int m_iCurMinute;
    unsigned int m_iDataId;
    unsigned int m_iLEDModeId;
    int m_id_timer_clock = -1;
    int m_id_timer_clock_set_hour = -1;
    int m_id_timer_clock_set_minu = -1;
    unsigned char numberCode[10]={ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE};

private:
    int m_iFlashInterval = 1000;
    CanMessage m_CanRxMessage;
    int m_iRvc_status = Camera_Unkown;

protected:
    BOOL Processing();
};

extern CanService *g_pcanservice;

#endif // CANMSGEVENTTHREAD_H
