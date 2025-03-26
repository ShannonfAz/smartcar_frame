#ifndef _faz_net_tool_h_
#define _faz_net_tool_h_
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
string get_wireless_interface();
// 网络信息结构体
struct NetworkInfo {
    string id;
    string ssid;
    string flags;
};
vector<NetworkInfo> get_networks(const string& interface);
bool select_network(const string& interface, const string& net_id);
extern vector<string> ips_wlan_list;
extern string interface;
vector<NetworkInfo> find_wifi();
void connect_wifi(vector<NetworkInfo> networks,int choice);
extern char eth0[INET_ADDRSTRLEN];
extern char wlan0[INET_ADDRSTRLEN];
int show_eth0_on_screen();
int show_wlan0_on_screen();
#endif