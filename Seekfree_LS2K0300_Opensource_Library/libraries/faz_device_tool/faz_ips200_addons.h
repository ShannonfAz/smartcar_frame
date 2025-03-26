#ifndef _faz_ips200_addons_h_
#define _faz_ips200_addons_h_
#include "zf_common_typedef.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
void ips200_list_string(uint8 start_line,uint8 line,const char dat[]);
void ips200_show_mat_gray_image(uint16 x,uint16 y,Mat img);
void ips200_show_mat_color_image(uint16 x, uint16 y,Mat img);
#endif