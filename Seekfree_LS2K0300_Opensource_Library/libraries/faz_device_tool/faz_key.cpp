#include "zf_driver_gpio.h"
#include "zf_driver_delay.h"
#include "faz_net_tool.h"
int key_mode_1(const char key[],unsigned int delay_ms){//松手触发，触发后返回1
    if(!gpio_get_level(key)){
        system_delay_ms(delay_ms);
        while(!gpio_get_level(key));
        return 1;
    }
    return 0;
}
