#ifndef _imgprocess_h_
#define _imgprocess_h_
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
//static VideoCapture cap(0);//在此决定使用哪个摄像头，一般是0
// static unsigned int imgW = 320,imgH = 240;
int videocap(VideoCapture cap,int code,int fps,unsigned int imgw,unsigned int imgh,unsigned int& imgW,unsigned int& imgH,Mat& img);
void imgprocess(unsigned int& imgW,unsigned int& imgH,Mat& img,Mat& imggray,Mat& binimg,Mat& imgoutput);
#endif