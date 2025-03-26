#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
#include "zf_common_headfile.h"
#include "your_program.h"
#include "imgprocess.h"
#include "faz_bat_warning.h"

#define MOTOR1_DIR   "/dev/zf_driver_gpio_motor_1"
#define MOTOR1_PWM   "/dev/zf_device_pwm_motor_1"

#define MOTOR2_DIR   "/dev/zf_driver_gpio_motor_2"
#define MOTOR2_PWM   "/dev/zf_device_pwm_motor_2"

#define ENCODER_1           "/dev/zf_encoder_1"
#define ENCODER_2           "/dev/zf_encoder_2"

#define SERVO_MOTOR1_PWM            "/dev/zf_device_pwm_servo"
#define SERVO_MIDDLE 92

#define KEY_0       "/dev/zf_driver_gpio_key_0"
#define KEY_1       "/dev/zf_driver_gpio_key_1"
#define KEY_2       "/dev/zf_driver_gpio_key_2"
#define KEY_3       "/dev/zf_driver_gpio_key_3"

struct pwm_info motor_1_pwm_info;
struct pwm_info motor_2_pwm_info;
struct pwm_info servo_pwm_info;

#define SERVO_MOTOR_FREQ            (servo_pwm_info.freq)  

#define MOTOR1_PWM_DUTY_MAX    (motor_1_pwm_info.duty_max)       
#define MOTOR2_PWM_DUTY_MAX    (motor_2_pwm_info.duty_max)    
#define PWM_DUTY_MAX                (servo_pwm_info.duty_max)  
#define SERVO_MOTOR_L_MAX           (75+SERVO_MIDDLE-90)                       
#define SERVO_MOTOR_R_MAX           (105+SERVO_MIDDLE-90)      
#define SERVO_MOTOR_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))

using namespace cv;
using namespace std;

void sigint_handler(int signum) 
{
    printf("收到Ctrl+C，程序即将退出\n");
    exit(0);
}


//逐飞示例的cleanup魔改板
//请注意：若使用本gui框架，那么能不用全局变量就不用全局变量，逐飞的zf_device_uvc.cpp以及.h全被我disable掉了
//因为里面的全局VideoCapture cap;会在启动程序时直接吃掉摄像头资源，导致camera_test与your_program全部报错
//如果需要使用，则需要把camera_test.cpp与.h删掉，然后把main.cpp里的
/*case 4:
ips200_clear();
camera_test();
break;*/
//全部删掉
//接着把本程序的所有cap2相关全删
//但为什么不拿opencv直接处理图像呢（
void cleanup()
{
    printf("程序异常退出，执行清理操作\n");
	ips200_clear();
    // 关闭电机
    pwm_set_duty(MOTOR1_PWM, 0);   
    pwm_set_duty(MOTOR2_PWM, 0);  
    pwm_set_duty(SERVO_MOTOR1_PWM, 0);    
}
int16 encoder_left;
int16 encoder_right;

//逐飞的编码器示例原版函数
void pit_callback()
{
    encoder_left  = encoder_get_count(ENCODER_1);
    encoder_right = encoder_get_count(ENCODER_2);
}



unsigned int imgW = 320,imgH = 240;//提前定义一下

//自己写的垃圾斑马线判断函数，就不删了
int BANMA(Mat& binimg,Mat& imgoutput) {
	int banma = 0, i, black = 0, white, banmacount = 0, region = 0, j;//斑马线识别
	rectangle(imgoutput, Point(60, 100), Point(260, 200), Scalar(255, 0, 255), 1);
	for (j = 100;j <= 200;j++)
	{
		for (i = 60;i <= 260;i++)
		{
			if (binimg.at<uchar>(j,i) == 255)
			{
				white = 1;
			}
			else
			{
				white = 0;
			}
			if (white != black)
			{
				black = white;
				banmacount++;
			}
			if (banmacount > 30)
			{
				banmacount = 0;
				region++;
			}
		}
	}
	if (region > 15)
	{
		banma = 1;
	}
	return banma;
}



int your_program() {
	VideoCapture cap2(0);
	ips200_list_string(1,18,"quit:p13");
	Mat img,imggray,binimg,imgoutput;
	Mat img_test;//测试彩色图像显示功能用，到时候可删
	unsigned int motorl_speed,motorr_speed;
	float servop,servod,motorp,motori;
	pid_read_settings(motorl_speed,motorr_speed,servop,servod,motorp,motori);
    pwm_get_dev_info(MOTOR1_PWM, &motor_1_pwm_info);
    pwm_get_dev_info(MOTOR2_PWM, &motor_2_pwm_info);
    pwm_get_dev_info(SERVO_MOTOR1_PWM, &servo_pwm_info);

    atexit(cleanup);
    signal(SIGINT, sigint_handler);
    gpio_set_level(MOTOR1_DIR, 1);                                      // DIR输出高电平，1为正转

    pwm_set_duty(MOTOR1_PWM, motorl_speed);       

    gpio_set_level(MOTOR2_DIR, 1);                                      // DIR输出高电平
    pwm_set_duty(MOTOR2_PWM, motorr_speed);
	pit_ms_init(10, pit_callback);
	int videostate = videocap(cap2,0,60,320,240,imgW,imgH,img);
	if (videostate == 0)return 0;
	int banma = 0;
	while (true) {
		batt_monitor();
		cap2.read(img);
		imgprocess(imgW,imgH,img,imggray,binimg,imgoutput);
		banma = BANMA(binimg,imgoutput);
		if (banma == 1) {
			cout<<"这是斑马线，或者你可能byd跑出赛道了"<<endl;
			// cap2.release();//一个比较垃圾的斑马线检测功能，如果要开启就把这三行注释取消
			// cleanup();
			// return 0;
		}
		resize(img,img_test,Size(240,(unsigned int)(imgH*240/imgW)));
		ips200_show_mat_color_image(0,0,img_test);//,240,(unsigned int)(imgH*240/imgW));
		cout<<"左轮占空比："<<(float)motorl_speed/10000.0<<endl;
		cout<<"右轮占空比："<<(float)motorr_speed/10000.0<<endl;
		cout<<"舵机p"<<servop<<endl;
		cout<<"舵机d"<<servod<<endl;
		cout<<"电机p"<<motorp<<endl;
		cout<<"电机i"<<motori<<endl;
		cout<<"左轮速度（编码器）："<<encoder_left<<endl;
		cout<<"右轮速度（编码器）："<<-encoder_right<<endl;
        if(key_mode_1(KEY_0,200)){
			cap2.release();
			cleanup();
            return 0;
        }
		system_delay_ms(2);
	}
}