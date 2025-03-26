#include <fstream>
#include <iostream>
#include "zf_common_headfile.h"
#include "pid_setting.h"

#define KEY_0       "/dev/zf_driver_gpio_key_0"
#define KEY_1       "/dev/zf_driver_gpio_key_1"
#define KEY_2       "/dev/zf_driver_gpio_key_2"
#define KEY_3       "/dev/zf_driver_gpio_key_3"

using namespace std;
unsigned int pid_choose_num;
vector<string> pid_options = {
    "1.motor_l_speed",
    "2.motor_r_speed",
    "3.servo_p",
    "4.servo_d",
    "5.motor_p",
    "6.motor_i",
    
};
vector<string> motor_speed_options = {
    "1.+100",
    "2.+10",
    "3.+1",
    "4.-1",
    "5.-10",
    "6.-100",
    
};
vector<string> pid_num_options = {
    "1.+1",
    "2.+0.1",
    "3.-0.1",
    "4.-1",
};
void pid_show(unsigned int& pid_choose_num){
    ips200_clear();
    if(pid_choose_num == 0)pid_choose_num = 1;
    if(pid_choose_num == pid_options.size() + 1)pid_choose_num = pid_options.size();
    unsigned int i = 0;
    for(i = 0;i < pid_options.size();i++)ips200_list_string(1,i+1,pid_options[i].c_str());
    ips200_list_string(1,18,"up:p16,down:p15,quit:p13");
    ips200_list_string(1,19,"press p14 to set:");
    ips200_list_string(1,20,pid_options[pid_choose_num-1].c_str());
}
void motor_speed_show(unsigned int& motor_speed_num,int speed){
    ips200_clear();
    ips200_list_string(1,17,"motor_speed=");
    ips200_show_uint(130,256,speed,10);
    if(motor_speed_num == 0)motor_speed_num = 1;
    if(motor_speed_num == motor_speed_options.size() + 1)motor_speed_num = motor_speed_options.size();
    unsigned int i = 0;
    for(i = 0;i < motor_speed_options.size();i++)ips200_list_string(1,i+1,motor_speed_options[i].c_str());
    ips200_list_string(1,18,"up:p16,down:p15,quit:p13");
    ips200_list_string(1,19,"press p14 to set:");
    ips200_list_string(1,20,motor_speed_options[motor_speed_num-1].c_str());
}
void pid_set_show(unsigned int& pid_set_num,float num){
    ips200_clear();
    ips200_list_string(1,17,"num=");
    ips200_show_float(130,256,num,2,2);
    if(pid_set_num == 0)pid_set_num = 1;
    if(pid_set_num == pid_num_options.size() + 1)pid_set_num = pid_num_options.size();
    unsigned int i = 0;
    for(i = 0;i < pid_num_options.size();i++)ips200_list_string(1,i+1,pid_num_options[i].c_str());
    ips200_list_string(1,18,"up:p16,down:p15,quit:p13");
    ips200_list_string(1,19,"press p14 to set:");
    ips200_list_string(1,20,pid_num_options[pid_set_num-1].c_str());
}
int motor_l_speed(){
    int speed;
    a1:ifstream motor_l_speed;
    motor_l_speed.open("pid_setting/motor_l_speed.txt",ios::in);
    motor_l_speed >> speed;
    motor_l_speed.close();
    if(speed == EOF){
        ofstream motor_l_speed;
        motor_l_speed.open("pid_setting/motor_l_speed.txt",ios::out);
        motor_l_speed << 0 << endl;
        motor_l_speed.close();
        goto a1;
    }
    else{
        unsigned int motor_speed_num = 1;
        motor_speed_show(motor_speed_num,speed);
        while(1){
            if(key_mode_1(KEY_3,50)){
                motor_speed_num--;
                motor_speed_show(motor_speed_num,speed);
            }
            if(key_mode_1(KEY_2,50)){
                motor_speed_num++;
                motor_speed_show(motor_speed_num,speed);
            }
            if(key_mode_1(KEY_1,50)){
                ofstream motor_l_speed;
                switch(motor_speed_num){
                    case 1:
                    speed += 100;
                    if(speed > 10000)speed = 10000;
                    if(speed < 0)speed = 0;
                    motor_l_speed.open("pid_setting/motor_l_speed.txt",ios::out|ios::trunc);
                    motor_l_speed << speed << endl;
                    motor_l_speed.close();
                    break;
                    case 2:
                    speed += 10;
                    if(speed > 10000)speed = 10000;
                    if(speed < 0)speed = 0;
                    motor_l_speed.open("pid_setting/motor_l_speed.txt",ios::out|ios::trunc);
                    motor_l_speed << speed << endl;
                    motor_l_speed.close();
                    break;
                    case 3:
                    speed += 1;
                    if(speed > 10000)speed = 10000;
                    if(speed < 0)speed = 0;
                    motor_l_speed.open("pid_setting/motor_l_speed.txt",ios::out|ios::trunc);
                    motor_l_speed << speed << endl;
                    motor_l_speed.close();
                    break;
                    case 4:
                    speed -= 1;
                    if(speed > 10000)speed = 10000;
                    if(speed < 0)speed = 0;
                    motor_l_speed.open("pid_setting/motor_l_speed.txt",ios::out|ios::trunc);
                    motor_l_speed << speed << endl;
                    motor_l_speed.close();
                    break;
                    case 5:
                    speed -= 10;
                    if(speed > 10000)speed = 10000;
                    if(speed < 0)speed = 0;
                    motor_l_speed.open("pid_setting/motor_l_speed.txt",ios::out|ios::trunc);
                    motor_l_speed << speed << endl;
                    motor_l_speed.close();
                    break;
                    case 6:
                    speed -= 100;
                    if(speed > 10000)speed = 10000;
                    if(speed < 0)speed = 0;
                    motor_l_speed.open("pid_setting/motor_l_speed.txt",ios::out|ios::trunc);
                    motor_l_speed << speed << endl;
                    motor_l_speed.close();
                    break;
                }
                motor_speed_show(motor_speed_num,speed);
            }
            if(key_mode_1(KEY_0,200)){
                ips200_clear();
                return 0;
            }
        }
    }
}
int motor_r_speed(){
    int speed;
    a1:ifstream motor_r_speed;
    motor_r_speed.open("pid_setting/motor_r_speed.txt",ios::in);
    motor_r_speed >> speed;
    motor_r_speed.close();
    if(speed == EOF){
        ofstream motor_r_speed;
        motor_r_speed.open("pid_setting/motor_r_speed.txt",ios::out);
        motor_r_speed << 0 << endl;
        motor_r_speed.close();
        goto a1;
    }
    else{
        unsigned int motor_speed_num = 1;
        motor_speed_show(motor_speed_num,speed);
        while(1){
            if(key_mode_1(KEY_3,50)){
                motor_speed_num--;
                motor_speed_show(motor_speed_num,speed);
            }
            if(key_mode_1(KEY_2,50)){
                motor_speed_num++;
                motor_speed_show(motor_speed_num,speed);
            }
            if(key_mode_1(KEY_1,50)){
                ofstream motor_r_speed;
                switch(motor_speed_num){
                    case 1:
                    speed += 100;
                    if(speed > 10000)speed = 10000;
                    if(speed < 0)speed = 0;
                    motor_r_speed.open("pid_setting/motor_r_speed.txt",ios::out|ios::trunc);
                    motor_r_speed << speed << endl;
                    motor_r_speed.close();
                    break;
                    case 2:
                    speed += 10;
                    if(speed > 10000)speed = 10000;
                    if(speed < 0)speed = 0;
                    motor_r_speed.open("pid_setting/motor_r_speed.txt",ios::out|ios::trunc);
                    motor_r_speed << speed << endl;
                    motor_r_speed.close();
                    break;
                    case 3:
                    speed += 1;
                    if(speed > 10000)speed = 10000;
                    if(speed < 0)speed = 0;
                    motor_r_speed.open("pid_setting/motor_r_speed.txt",ios::out|ios::trunc);
                    motor_r_speed << speed << endl;
                    motor_r_speed.close();
                    break;
                    case 4:
                    speed -= 1;
                    if(speed > 10000)speed = 10000;
                    if(speed < 0)speed = 0;
                    motor_r_speed.open("pid_setting/motor_r_speed.txt",ios::out|ios::trunc);
                    motor_r_speed << speed << endl;
                    motor_r_speed.close();
                    break;
                    case 5:
                    speed -= 10;
                    if(speed > 10000)speed = 10000;
                    if(speed < 0)speed = 0;
                    motor_r_speed.open("pid_setting/motor_r_speed.txt",ios::out|ios::trunc);
                    motor_r_speed << speed << endl;
                    motor_r_speed.close();
                    break;
                    case 6:
                    speed -= 100;
                    if(speed > 10000)speed = 10000;
                    if(speed < 0)speed = 0;
                    motor_r_speed.open("pid_setting/motor_r_speed.txt",ios::out|ios::trunc);
                    motor_r_speed << speed << endl;
                    motor_r_speed.close();
                    break;
                }
                motor_speed_show(motor_speed_num,speed);
            }
            if(key_mode_1(KEY_0,200)){
                ips200_clear();
                return 0;
            }
        }
    }
}
int servo_p(){
    float p;
    a1:ifstream servo_p;
    servo_p.open("pid_setting/servo_p.txt",ios::in);
    servo_p >> p;
    servo_p.close();
    if(p == EOF){
        ofstream servo_p;
        servo_p.open("pid_setting/servo_p.txt",ios::out);
        servo_p << 0 << endl;
        servo_p.close();
        goto a1;
    }
    else{
        unsigned int pid_choose_num = 1;
        pid_set_show(pid_choose_num,p);
        while(1){
            if(key_mode_1(KEY_3,50)){
                pid_choose_num--;
                pid_set_show(pid_choose_num,p);
            }
            if(key_mode_1(KEY_2,50)){
                pid_choose_num++;
                pid_set_show(pid_choose_num,p);
            }
            if(key_mode_1(KEY_1,50)){
                ofstream servo_p;
                switch(pid_choose_num){
                    case 1:
                    p += 1;
                    if(p < 0)p = 0;
                    servo_p.open("pid_setting/servo_p.txt",ios::out|ios::trunc);
                    servo_p << p << endl;
                    servo_p.close();
                    break;
                    case 2:
                    p += 0.1;
                    if(p < 0)p = 0;
                    servo_p.open("pid_setting/servo_p.txt",ios::out|ios::trunc);
                    servo_p << p << endl;
                    servo_p.close();
                    break;
                    case 3:
                    p -= 0.1;
                    if(p < 0)p = 0;
                    servo_p.open("pid_setting/servo_p.txt",ios::out|ios::trunc);
                    servo_p << p << endl;
                    servo_p.close();
                    break;
                    case 4:
                    p -= 1;
                    if(p < 0)p = 0;
                    servo_p.open("pid_setting/servo_p.txt",ios::out|ios::trunc);
                    servo_p << p << endl;
                    servo_p.close();
                    break;
                }
                pid_set_show(pid_choose_num,p);
            }
            if(key_mode_1(KEY_0,200)){
                ips200_clear();
                return 0;
            }
        }
    }
}
int servo_d(){
    float d;
    a1:ifstream servo_d;
    servo_d.open("pid_setting/servo_d.txt",ios::in);
    servo_d >> d;
    servo_d.close();
    if(d == EOF){
        ofstream servo_d;
        servo_d.open("pid_setting/servo_d.txt",ios::out);
        servo_d << 0 << endl;
        servo_d.close();
        goto a1;
    }
    else{
        unsigned int pid_choose_num = 1;
        pid_set_show(pid_choose_num,d);
        while(1){
            if(key_mode_1(KEY_3,50)){
                pid_choose_num--;
                pid_set_show(pid_choose_num,d);
            }
            if(key_mode_1(KEY_2,50)){
                pid_choose_num++;
                pid_set_show(pid_choose_num,d);
            }
            if(key_mode_1(KEY_1,50)){
                ofstream servo_d;
                switch(pid_choose_num){
                    case 1:
                    d += 1;
                    if(d < 0)d = 0;
                    servo_d.open("pid_setting/servo_d.txt",ios::out|ios::trunc);
                    servo_d << d << endl;
                    servo_d.close();
                    break;
                    case 2:
                    d += 0.1;
                    if(d < 0)d = 0;
                    servo_d.open("pid_setting/servo_d.txt",ios::out|ios::trunc);
                    servo_d << d << endl;
                    servo_d.close();
                    break;
                    case 3:
                    d -= 0.1;
                    if(d < 0)d = 0;
                    servo_d.open("pid_setting/servo_d.txt",ios::out|ios::trunc);
                    servo_d << d << endl;
                    servo_d.close();
                    break;
                    case 4:
                    d -= 1;
                    if(d < 0)d = 0;
                    servo_d.open("pid_setting/servo_d.txt",ios::out|ios::trunc);
                    servo_d << d << endl;
                    servo_d.close();
                    break;
                }
                pid_set_show(pid_choose_num,d);
            }
            if(key_mode_1(KEY_0,200)){
                ips200_clear();
                return 0;
            }
        }
    }
}
int motor_p(){
    float p;
    a1:ifstream motor_p;
    motor_p.open("pid_setting/motor_p.txt",ios::in);
    motor_p >> p;
    motor_p.close();
    if(p == EOF){
        ofstream motor_p;
        motor_p.open("pid_setting/motor_p.txt",ios::out);
        motor_p << 0 << endl;
        motor_p.close();
        goto a1;
    }
    else{
        unsigned int pid_choose_num = 1;
        pid_set_show(pid_choose_num,p);
        while(1){
            if(key_mode_1(KEY_3,50)){
                pid_choose_num--;
                pid_set_show(pid_choose_num,p);
            }
            if(key_mode_1(KEY_2,50)){
                pid_choose_num++;
                pid_set_show(pid_choose_num,p);
            }
            if(key_mode_1(KEY_1,50)){
                ofstream motor_p;
                switch(pid_choose_num){
                    case 1:
                    p += 1;
                    if(p < 0)p = 0;
                    motor_p.open("pid_setting/motor_p.txt",ios::out|ios::trunc);
                    motor_p << p << endl;
                    motor_p.close();
                    break;
                    case 2:
                    p += 0.1;
                    if(p < 0)p = 0;
                    motor_p.open("pid_setting/motor_p.txt",ios::out|ios::trunc);
                    motor_p << p << endl;
                    motor_p.close();
                    break;
                    case 3:
                    p -= 0.1;
                    if(p < 0)p = 0;
                    motor_p.open("pid_setting/motor_p.txt",ios::out|ios::trunc);
                    motor_p << p << endl;
                    motor_p.close();
                    break;
                    case 4:
                    p -= 1;
                    if(p < 0)p = 0;
                    motor_p.open("pid_setting/motor_p.txt",ios::out|ios::trunc);
                    motor_p << p << endl;
                    motor_p.close();
                    break;
                }
                pid_set_show(pid_choose_num,p);
            }
            if(key_mode_1(KEY_0,200)){
                ips200_clear();
                return 0;
            }
        }
    }
}
int motor_i(){
    float i;
    a1:ifstream motor_i;
    motor_i.open("pid_setting/motor_i.txt",ios::in);
    motor_i >> i;
    motor_i.close();
    if(i == EOF){
        ofstream motor_i;
        motor_i.open("pid_setting/motor_i.txt",ios::out);
        motor_i << 0 << endl;
        motor_i.close();
        goto a1;
    }
    else{
        unsigned int pid_choose_num = 1;
        pid_set_show(pid_choose_num,i);
        while(1){
            if(key_mode_1(KEY_3,50)){
                pid_choose_num--;
                pid_set_show(pid_choose_num,i);
            }
            if(key_mode_1(KEY_2,50)){
                pid_choose_num++;
                pid_set_show(pid_choose_num,i);
            }
            if(key_mode_1(KEY_1,50)){
                ofstream motor_i;
                switch(pid_choose_num){
                    case 1:
                    i += 1;
                    if(i < 0)i = 0;
                    motor_i.open("pid_setting/motor_i.txt",ios::out|ios::trunc);
                    motor_i << i << endl;
                    motor_i.close();
                    break;
                    case 2:
                    i += 0.1;
                    if(i < 0)i = 0;
                    motor_i.open("pid_setting/motor_i.txt",ios::out|ios::trunc);
                    motor_i << i << endl;
                    motor_i.close();
                    break;
                    case 3:
                    i -= 0.1;
                    if(i < 0)i = 0;
                    motor_i.open("pid_setting/motor_i.txt",ios::out|ios::trunc);
                    motor_i << i << endl;
                    motor_i.close();
                    break;
                    case 4:
                    i -= 1;
                    if(i < 0)i = 0;
                    motor_i.open("pid_setting/motor_i.txt",ios::out|ios::trunc);
                    motor_i << i << endl;
                    motor_i.close();
                    break;
                }
                pid_set_show(pid_choose_num,i);
            }
            if(key_mode_1(KEY_0,200)){
                ips200_clear();
                return 0;
            }
        }
    }
}


int pid_setting(){
    unsigned int pid_set_num = 1;
    pid_show(pid_set_num);
    while(1){
        batt_monitor();
        if(key_mode_1(KEY_3,50)){
            pid_set_num--;
            pid_show(pid_set_num);
        }
        if(key_mode_1(KEY_2,50)){
            pid_set_num++;
            pid_show(pid_set_num);
        }
        if(key_mode_1(KEY_1,50)){
            switch(pid_set_num){
                case 1:
                motor_l_speed();
                break;
                case 2:
                motor_r_speed();
                break;
                case 3:
                servo_p();
                break;
                case 4:
                servo_d();
                break;
                case 5:
                motor_p();
                break;
                case 6:
                motor_i();
                break;
            }
            pid_show(pid_set_num);
        }
        if(key_mode_1(KEY_0,200)){
            ips200_clear();
            return 0;
        }
    }
}
void pid_read_settings(unsigned int& motorl_speed,unsigned int& motorr_speed,float& servop,float& servod,float& motorp,float& motori){
    ifstream motor_l_speed;
	motor_l_speed.open("pid_setting/motor_l_speed.txt",ios::in);
	motor_l_speed >> motorl_speed;
	motor_l_speed.close();
    ifstream motor_r_speed;
	motor_r_speed.open("pid_setting/motor_r_speed.txt",ios::in);
	motor_r_speed >> motorr_speed;
	motor_r_speed.close();
    ifstream servo_p;
	servo_p.open("pid_setting/servo_p.txt",ios::in);
	servo_p >> servop;
	servo_p.close();
    ifstream servo_d;
	servo_d.open("pid_setting/servo_d.txt",ios::in);
	servo_d >> servod;
	servo_d.close();
    ifstream motor_p;
	motor_p.open("pid_setting/motor_p.txt",ios::in);
	motor_p >> motorp;
	motor_p.close();
    ifstream motor_i;
	motor_i.open("pid_setting/motor_i.txt",ios::in);
	motor_i >> motori;
	motor_i.close();
}