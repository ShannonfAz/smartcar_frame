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
#include "wifi_setting_tool.h"

#define KEY_0       "/dev/zf_driver_gpio_key_0"
#define KEY_1       "/dev/zf_driver_gpio_key_1"
#define KEY_2       "/dev/zf_driver_gpio_key_2"
#define KEY_3       "/dev/zf_driver_gpio_key_3"


using namespace std;


int wifi_setting_tool(){
    exec("wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant.conf");
	exec("udhcpc -i wlan0");
	ips200_init("/dev/fb0");
	ips200_clear();
	unsigned int i;
	//vector<char> wlanlist_temp;
	bool configure_state = 0;
	uint wifi_num = 1;
	while(1){
		auto network = find_wifi();
		while(!configure_state){
			find_wifi();
			ips200_list_string(1,1,"WIFI list");
			for(i = 0;i < ips_wlan_list.size();i++)		ips200_list_string(2,i+1,ips_wlan_list[i].c_str());
			ips200_list_string(1,18,"up:p16,down:p15,quit:p13");
			ips200_list_string(1,19,"press p14 to connect to:");
            if(key_mode_1(KEY_3,50)){
                wifi_num--;
                ips200_clear();
            }
            if(key_mode_1(KEY_2,50)){
                wifi_num++;
                ips200_clear();
            }
			//cout<<wifi_num<<endl;
			if(wifi_num == 0)wifi_num = 1;
			if(wifi_num == ips_wlan_list.size()+1)wifi_num = ips_wlan_list.size();
			ips200_list_string(1,1,"WIFI list");
			for(i = 0;i < ips_wlan_list.size();i++)		ips200_list_string(2,i+1,ips_wlan_list[i].c_str());
			ips200_list_string(1,18,"up:p16,down:p15,quit:p13");
			ips200_list_string(1,19,"press p14 to connect to:");
			ips200_list_string(1,20,ips_wlan_list[wifi_num-1].c_str());
            if(key_mode_1(KEY_1,50)){
                configure_state = 1;
            }
            if(key_mode_1(KEY_0,200)){
                ips200_clear();
                goto a1;
            }
		}
		connect_wifi(network,wifi_num);
		find_wifi();
		ips200_clear();
		ips200_list_string(1,1,"WIFI list");
		for(i = 0;i < ips_wlan_list.size();i++)		ips200_list_string(2,i+1,ips_wlan_list[i].c_str());
		ips200_list_string(1,18,"up:p16,down:p15,quit:p13");
		ips200_list_string(1,19,"press p14 to connect to:");
		ips200_list_string(1,20,ips_wlan_list[wifi_num-1].c_str());
		configure_state = 0;
		if(key_mode_1(KEY_0,200)){
			ips200_clear();
			goto a1;
		}
	}
	a1:ips200_clear();
	while(!gpio_get_level(KEY_0));
	while(1)
    {
        // 此处编写需要循环执行的代码
		show_eth0_on_screen();
		show_wlan0_on_screen();
		ips200_list_string(1,5,"press P13 key");
		ips200_list_string(1,6,"for 0.2s to quit");
            if(key_mode_1(KEY_0,200)){
                ips200_clear();
                return 0;
            }
		system_delay_ms(100);
    }
}