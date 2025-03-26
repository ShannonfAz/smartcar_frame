#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "zf_device_ips200_fb.h"
#include "faz_ips200_addons.h"
using namespace cv;
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 更易读的显示字符串
// 参数说明     start_line               从第start_line行开始显示 参数范围（建议） [1,20]
// 参数说明     line               于第line行显示 参数范围（建议） [1,21-x]
// 参数说明     dat             需要显示的字符串，最长30个字母（每个字母width为8），如果需要显示c++ string请自行变量名.c_str()
// 返回参数     void
// 使用示例     ips200_list_string(1,1,"you gotta code");               // 在第一行显示you gotta code
//-------------------------------------------------------------------------------------------------------------------
void ips200_list_string(uint8 start_line,uint8 line,const char dat[]){
    ips200_show_string(0,16*(line+start_line-2),dat);
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 直接显示opencv通过Mat存储的灰度图，想全程用opencv处理图像然后嫌图像显示麻烦？我来助你！
// 参数说明     x               图像左上角x坐标
// 参数说明     y               图像左上角y坐标
// 参数说明     img             用Mat存储的图像，必须必须是灰度图
// 自动获取图像长宽，不用输imgW和imgH了
// 使用示例     ips200_show_mat_gray_image(0,0,imggray);               // 在屏幕左上角显示imggray存储的灰度图像
//-------------------------------------------------------------------------------------------------------------------
void ips200_show_mat_gray_image(uint16 x,uint16 y,Mat img){
    uint8_t *rgay_image;
    rgay_image = reinterpret_cast<uint8_t *>(img.ptr(0));
    unsigned int imgW = img.size().width;
    unsigned int imgH = img.size().height;
    ips200_show_gray_image(0, 0, rgay_image, imgW, imgH);
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 直接显示opencv通过Mat存储的彩色图，即cap.read(img)拿到的img之类的，想显示彩图？我来助你！
// 参数说明     x               图像左上角x坐标
// 参数说明     y               图像左上角y坐标
// 参数说明     img             用Mat存储的图像，必须必须是三通道bgr彩色图，放心，摄像头拿到的默认就是了
// 自动获取图像长宽，不用输imgW和imgH了
// 使用示例     ips200_show_mat_color_image(0,0,img);               // 在屏幕左上角显示img存储的图像
// 备注信息     不建议在循迹时显示什么彩图，保证卡死你，设计各种算法时用一用就好了
//-------------------------------------------------------------------------------------------------------------------
void ips200_show_mat_color_image(uint16 x, uint16 y,Mat img){
    uint32 x_start = 0, y_start = 0;
    uint16 color = 0;
    Vec3b pixel;// = img.at<Vec3b>(y,x);
    unsigned int imgW = img.size().width;
    unsigned int imgH = img.size().height;
    for(y_start = y; y_start < (y + imgH); y_start++) 
    {
        for(x_start = x; x_start < (x + imgW); x_start++)
        {
            pixel = img.at<Vec3b>(y_start,x_start);
            uint16_t r = (pixel[2] >> 3) & 0b11111;
            uint16_t g = (pixel[1] >> 2) & 0b111111;
            uint16_t b = (pixel[0] >> 3) & 0b11111;
            color = (r << 11) | (g << 5) | (b << 0);
            
            ips200_draw_point(x_start, y_start,  color);
        }
    }    
}