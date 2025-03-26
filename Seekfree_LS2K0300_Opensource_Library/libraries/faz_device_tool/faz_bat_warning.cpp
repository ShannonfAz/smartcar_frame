#include "zf_device_ips200_fb.h"
#include "zf_driver_adc.h"
#include "faz_ips200_addons.h"
#define  ADC_REG_PATH "/sys/bus/iio/devices/iio:device0/in_voltage7_raw"
#define  ADC_SCALE_PATH "/sys/bus/iio/devices/iio:device0/in_voltage_scale"

float batt_v;
unsigned int batt_S;
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     电池电压检测初始化，无参数
//-------------------------------------------------------------------------------------------------------------------
void bat_warning_init(){
    batt_v = (float)adc_convert(ADC_REG_PATH) * adc_get_scale(ADC_SCALE_PATH) * 11.0 / 1000.0;
    if(batt_v < 10)batt_S = 2;
    else batt_S = 3;
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     电池电压显示，显示在屏幕第17行
//-------------------------------------------------------------------------------------------------------------------
void batt_monitor(){
    batt_v = (float)adc_convert(ADC_REG_PATH) * adc_get_scale(ADC_SCALE_PATH) * 11.0 / 1000.0;
    switch(batt_S){
        case 2:
        if(batt_v < 7.4)ips200_list_string(1,17,"byd go to charge the bat now!");
        else{
            ips200_list_string(1,17,"battery_voltage        V");
            ips200_show_float(130,256,batt_v,2,2);
        }
        break;
        case 3:
        if(batt_v < 11.1)ips200_list_string(1,17,"byd go to charge the bat now!");
        else{
            ips200_list_string(1,17,"battery_voltage        V");
            ips200_show_float(130,256,batt_v,2,2);
        }
        break;
    }
}