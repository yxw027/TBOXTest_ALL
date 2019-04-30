#ifndef SHARE_H
#define SHARE_H

#define MESSAGE_BASE            2000
#define MAIN_SHOWHIDE           MESSAGE_BASE + 1        //1 show 0 hide
#define RADIO_SHOWHIDE          MESSAGE_BASE + 3
#define SSPLINK_SHOWHIDE        MESSAGE_BASE + 5
#define BT_SHOWHIDE             MESSAGE_BASE + 7
#define NAVI_SHOWHIDE           MESSAGE_BASE + 9
#define USB_SHOWHIDE            MESSAGE_BASE + 11
#define WEATHER_SHOWHIDE        MESSAGE_BASE + 13
#define SUBAPP_ISREADY          MESSAGE_BASE + 15
#define BTPAIR_SHOWHIDE         MESSAGE_BASE + 16
#define CALENDAR_SHOWHIDE       MESSAGE_BASE + 18
#define SETTING_SHOWHIDE        MESSAGE_BASE + 20
#define CARINFO_SHOWHIDE        MESSAGE_BASE + 22
#define BT_ISREADY              MESSAGE_BASE + 24
#define BT_ISCALLING            MESSAGE_BASE + 25       //1 call 0 end
#define USB_PULLOUT             MESSAGE_BASE + 26
#define BT_ISPLAYING_MUSIC      MESSAGE_BASE + 27       //1 play 0 stop
#define BT_ISCONNEST            MESSAGE_BASE + 28       //1 yes  0 no
#define RADIO_ISREADY           MESSAGE_BASE + 29
#define USB_ISREADY             MESSAGE_BASE + 30
#define WEATHER_ISREADY         MESSAGE_BASE + 31
#define CALENDAR_ISREADY        MESSAGE_BASE + 32
#define SETTING_ISREADY         MESSAGE_BASE + 33
#define CARINFO_ISREADY         MESSAGE_BASE + 34
#define SSPLINK_LOADFINISHED    MESSAGE_BASE + 35
#define TBTNAVI_SHOWHIDE        MESSAGE_BASE + 36
#define TBTNAVI_ISREADY         MESSAGE_BASE + 37
#define INTO_SOUND_SETTING      MESSAGE_BASE + 38
#define USB_PLUGGED_IN          MESSAGE_BASE + 39
#define TBTNAVI_IS_WAKEUP       MESSAGE_BASE + 40       //1 wake 0 no
#define LANGUAGE_SWITCH         MESSAGE_BASE + 41       //1 ch 0 en
#define BT_TURN_ON_STATE        MESSAGE_BASE + 42       //1 open 0 close
#define VEHICLE_FAULT_WARNING   MESSAGE_BASE + 43
#define BATTERY_VOLTAGE_MSG     MESSAGE_BASE + 44       //电池电压 0 normal 1 fault
#define HEADLIGHT_STATE         MESSAGE_BASE + 45       //大灯 0 off 1 on
#define KEY_UP_DOWM_LEFT_RIGHT  MESSAGE_BASE + 46       //0 prev music 1 next music 2 phone answer 3 phone hang up
#define REVERSING_STATE         MESSAGE_BASE + 47       //倒车状态 0 off 1 on
#define HARDKEY_MODE            MESSAGE_BASE + 48
#define BACKLIGHT_ON_OFF        MESSAGE_BASE + 49       //背光开关通知 1开 0关
#define HARDKEY_HOME            MESSAGE_BASE + 50       //home key
#define BL_SSP_REQUEST_SOURCE   MESSAGE_BASE + 51       //0 request 1 success
#define BL_SSP_EXIT_SOURCE      MESSAGE_BASE + 52
#define BL_SSP_CONNECT_STATE    MESSAGE_BASE + 53       //0 disconnected 1 connected
#define BL_HARDKEY_MUTE         MESSAGE_BASE + 54
#define BL_SSP_BACKSTAGE        MESSAGE_BASE + 55
#define BL_HARDKEY_VOLUME       MESSAGE_BASE + 56       //1 add -1 sub
#define MUSIC_SHOWHIDE          MESSAGE_BASE + 57
#define VIDEO_SHOWHIDE          MESSAGE_BASE + 58



#define BTPAIR_YES           MESSAGE_BASE + 106
#define BTPAIR_NO            MESSAGE_BASE + 107

//can dbus
typedef enum message_id{
    id_gear_level_pos =0,
    id_abs_flt_sts,
    id_hv_isolation_status,
    id_vcam_status,
    id_motor_status,
    id_motor_over_temp_status,
    id_elec_brake_status,
    id_elec_steer_status,
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
    id_motor_power_out,
    //add
    id_energy_recovery_Level,
    //end
    id_vehicle_instance_power_out,
    id_vehicle_average_power_out,
    //add
    id_appointment_state_of_charge,
    id_sim_array_0_3,
    id_sim_array_4_7,
    id_sim_array_8_11,
    id_sim_array_12,
    id_vin_array_0_3,
    id_vin_array_4_7,
    id_vin_array_8_11,
    id_vin_array_12_15,
    id_vin_array_16,
    //end
    id_poweroff_status,
    id_upgrade_status,
    id_acc_status,
    id_acc_app_start,
    id_test,
    id_canConfig
}CanMessageID;

#endif // SHARE_H
