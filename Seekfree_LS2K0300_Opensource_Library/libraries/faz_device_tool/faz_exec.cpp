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
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     执行命令
// 参数说明     cmd               你要执行的命令，比如"udhcpc -i wlan0"，"sync"，"poweroff"等
// 使用示例     exec("sync");//同步数据
//             exec("poweroff");//关机跑路
//-------------------------------------------------------------------------------------------------------------------
string exec(const char* cmd) {
    char buffer[128];
    string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}