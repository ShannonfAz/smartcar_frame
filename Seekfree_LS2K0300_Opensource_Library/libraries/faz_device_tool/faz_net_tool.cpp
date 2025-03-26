#include "zf_device_ips200_fb.h"
#include "faz_exec.h"
#include "faz_net_tool.h"
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
using namespace std;
// 获取无线接口
string get_wireless_interface() {
    try {
        string output = exec("iwconfig 2>&1");
        istringstream iss(output);
        string line;
        while (getline(iss, line)) {
            if (line.find("IEEE 802.11") != string::npos) {
                return line.substr(0, line.find(" "));
            }
        }
    } catch (...) {}
    return "wlan0"; // 默认值
}
// 获取并解析网络列表
vector<NetworkInfo> get_networks(const string& interface) {
    vector<NetworkInfo> networks;
    string cmd = "wpa_cli -i " + interface + " list_networks";
    string output = exec(cmd.c_str());

    istringstream iss(output);
    string line;
    bool header_found = false;

    while (getline(iss, line)) {
        // 改进的标题检测逻辑
        if (!header_found) {
            if (line.find("network id") != string::npos) {
                header_found = true;
            }
            continue;
        }

        // 改进的字段解析逻辑
        regex re("\\t+");
        sregex_token_iterator it(line.begin(), line.end(), re, -1);
        vector<string> parts(it, {});

        if (parts.size() >= 3) {
            NetworkInfo info;
            info.id = parts[0];
            info.ssid = parts[1];
            info.flags = parts.size() >=4 ? parts[3] : "";
            networks.push_back(info);
        }
    }
    return networks;
}
// 选择指定网络
bool select_network(const string& interface, const string& net_id) {
    string cmd = "wpa_cli -i " + interface + " select_network " + net_id;
    string result = exec(cmd.c_str());

    if (result.find("OK") != string::npos) {
        exec(("wpa_cli -i " + interface + " save_config").c_str());
        //cout << "已成功选择网络，正在连接..." << endl;
		exec("udhcpc -i wlan0");
        // 释放和获取IP地址
        system(("dhclient -r " + interface + " >/dev/null 2>&1").c_str());
        system(("dhclient " + interface + " >/dev/null 2>&1").c_str());
        return true;
    }
    return false;
}
vector<string> ips_wlan_list;
string interface = get_wireless_interface();
vector<NetworkInfo> find_wifi(){
	ips_wlan_list.clear();
	// 获取无线接口
	//cout << "当前无线接口: " << interface << endl;

	// 获取网络列表
	auto networks = get_networks(interface);
	//cout <<networks.empty()<<endl;
	if (networks.empty()) {
		//cerr << "没有找到已保存的网络" << endl;
		//return 1;
	}

	// 显示网络列表
	//cout << "\n已保存的WiFi网络:" << endl;
	for (size_t i = 0; i < networks.size(); ++i) {
		string status = (networks[i].flags.find("CURRENT") != string::npos) ?
					   "当前连接" : "已保存";
		//cout << i+1 << ". " << networks[i].ssid << " (" << status << ")" << endl;
		if(status == "当前连接")ips_wlan_list.push_back(to_string(i+1)+"."+networks[i].ssid+"(connect)");
		else ips_wlan_list.push_back(to_string(i+1)+"."+networks[i].ssid);
	}
	return networks;
}
void connect_wifi(vector<NetworkInfo> networks,int choice){
	// 用户输入处理
	//cout << "\n请输入要连接的网络编号: ";
	// int choice;
	// cin >> choice;

	if (cin.fail() || choice < 1 || choice > static_cast<int>(networks.size())) {
		//cerr << "无效的输入" << endl;
		//return 1;
	}

	// 执行网络切换
	if (select_network(interface, networks[choice-1].id)) {
		//cout << "\n连接状态:" << endl;
		string status = exec(("wpa_cli -i " + interface + " status").c_str());
		//cout << status;
	} else {
		//cerr << "网络切换失败" << endl;
		//return 1;
	}
}
char eth0[INET_ADDRSTRLEN];
char wlan0[INET_ADDRSTRLEN];
int show_eth0_on_screen(){
    // 创建socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        //std::cerr << "无法创建socket" << std::endl;
    }

    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ - 1);

    // 获取IPv4地址
    if (ioctl(sockfd, SIOCGIFADDR, &ifr) == -1) {
        //std::cerr << "无法获取IP地址（请检查接口名称和权限）" << std::endl;
        close(sockfd);
        return 0;
    }

    // 转换二进制地址为字符串
    struct sockaddr_in* ipaddr = (struct sockaddr_in*)&ifr.ifr_addr;
    if (inet_ntop(AF_INET, &ipaddr->sin_addr, eth0, sizeof(eth0))) {
        //std::cout << "eth0 IP地址: " << eth0 << std::endl;
        ips200_show_string( 0 , 0,   "eth0:");
        ips200_show_string( 0 , 16,   eth0);
    } else {
        //std::cerr << "地址转换失败" << std::endl;
        close(sockfd);
    }
    
    close(sockfd);
    return 0;
}
int show_wlan0_on_screen(){
    // 创建socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        //std::cerr << "无法创建socket" << std::endl;
    }

    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, "wlan0", IFNAMSIZ - 1);

    // 获取IPv4地址
    if (ioctl(sockfd, SIOCGIFADDR, &ifr) == -1) {
        //std::cerr << "无法获取IP地址（请检查接口名称和权限）" << std::endl;
        close(sockfd);
        return 0;
    }

    // 转换二进制地址为字符串
    struct sockaddr_in* ipaddr = (struct sockaddr_in*)&ifr.ifr_addr;
    if (inet_ntop(AF_INET, &ipaddr->sin_addr, wlan0, sizeof(wlan0))) {
        //std::cout << "wlan0 IP地址: " << wlan0 << std::endl;
        ips200_show_string( 0 , 32,   "wlan0:");
        ips200_show_string( 0 , 48,   wlan0);
    } else {
        //std::cerr << "地址转换失败" << std::endl;
        close(sockfd);
    }

    close(sockfd);
    return 0;
}