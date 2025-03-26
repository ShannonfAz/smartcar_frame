#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "camera_test.h"
#include "imgprocess.h"
#include "faz_ips200_addons.h"
#include "faz_key.h"
#include "faz_bat_warning.h"
#include "zf_driver_delay.h"
#include "zf_device_ips200_fb.h"

using namespace cv;
using namespace std;

#define KEY_0       "/dev/zf_driver_gpio_key_0"
#define KEY_1       "/dev/zf_driver_gpio_key_1"
#define KEY_2       "/dev/zf_driver_gpio_key_2"
#define KEY_3       "/dev/zf_driver_gpio_key_3"

unsigned int imgW_test = 160,imgH_test = 120;
// static unsigned int imgW,imgH;

// static Mat img,imggray,binimg,binimg1;
uint8_t *rgay_image;

// static int videocap(int code,int fps,int imgw,int imgh) {
// 	switch (code) {
// 	case 0:
// 		cap.set(CAP_PROP_FOURCC, VideoWriter::fourcc('M', 'J', 'P', 'G'));
// 		break;
// 	case 1:
// 		cap.set(CAP_PROP_FOURCC, VideoWriter::fourcc('Y', 'U', 'Y', 'V'));
// 		break;
// 	default:
// 		cerr << "Error : wrong code" << endl;
// 		return 0;
// 	}
// 	cap.set(CAP_PROP_FPS, fps);
// 	cap.set(cv::CAP_PROP_FRAME_WIDTH, imgw);
// 	cap.set(cv::CAP_PROP_FRAME_HEIGHT, imgh);
// 	cap.read(img);
// 	imgW = imgw;
// 	imgH = imgh;
// 	//USE_num = imgH * 3;
// 	return 1;
// }



int camera_test(){
	Mat img,imggray;
	VideoCapture cap1(0);
    int videostate = videocap(cap1,0,60,160,120,imgW_test,imgH_test,img);
    if (videostate == 0)return 0;
    while(1){
		batt_monitor();
        cap1.read(img);
        if (img.size().width > 1)cvtColor(img, imggray, COLOR_BGR2GRAY);
        // rgay_image = reinterpret_cast<uint8_t *>(imggray.ptr(0));
        ips200_show_mat_color_image(0, 0, img);
		//ips200_show_mat_gray_image(0,0,imggray,imgW,imgH);
        ips200_list_string(1,19,"press P13 key");
		ips200_list_string(1,20,"for 0.2s to quit");
        if(key_mode_1(KEY_0,200)){
            cap1.release();
            ips200_clear();
            return 0;
        }
        system_delay_ms(2);
    }
}