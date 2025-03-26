#include <iostream>
#include <cstring>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <regex>
#include "zf_common_headfile.h"
#include "menu.h"

#define KEY_0       "/dev/zf_driver_gpio_key_0"
#define KEY_1       "/dev/zf_driver_gpio_key_1"
#define KEY_2       "/dev/zf_driver_gpio_key_2"
#define KEY_3       "/dev/zf_driver_gpio_key_3"

#define  ADC_REG_PATH "/sys/bus/iio/devices/iio:device0/in_voltage7_raw"
#define  ADC_SCALE_PATH "/sys/bus/iio/devices/iio:device0/in_voltage_scale"



vector<string> menu_options = {
    "1.wifi_setting_tool",
    "2.your program",
    "3.pid setting",
    "4.camera test",
    "5.reboot",
    "6.poweroff",
    
};
void menu_show(unsigned int& choose_num){
    if(choose_num == 0)choose_num = 1;
    if(choose_num == menu_options.size() + 1)choose_num = menu_options.size();
    ips200_clear();
    unsigned int i = 0;
    for(i = 0;i < menu_options.size();i++)ips200_list_string(1,i+1,menu_options[i].c_str());
    ips200_list_string(1,18,"up:p16,down:p15,quit:p13");
    ips200_list_string(1,19,"press p14 to run:");
    ips200_list_string(1,20,menu_options[choose_num-1].c_str());
}
int menu(){
    unsigned int choose_num = 1;
    a1:menu_show(choose_num);
    while(1){
        batt_monitor();

        if(key_mode_1(KEY_3,50)){
            choose_num--;
            menu_show(choose_num);
        }
        if(key_mode_1(KEY_2,50)){
            choose_num++;
            menu_show(choose_num);
        }
        if(key_mode_1(KEY_1,50)){
            return choose_num;
        }
        if(key_mode_1(KEY_0,200)){
            ips200_clear();
            ips200_list_string(1,1,"Are you sure?");
            ips200_list_string(1,2,"p13:quit p14:back");
            while(1){
                if(key_mode_1(KEY_1,50))goto a1;
                if(key_mode_1(KEY_0,200))break;
            }
            ips200_clear();
            return 0;
        }
    }
}

using namespace std;