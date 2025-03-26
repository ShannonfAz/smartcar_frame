#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include "zf_common_headfile.h"
#include "imgprocess.h"
using namespace cv;
using namespace std;
int videocap(VideoCapture cap,int code,int fps,unsigned int imgw,unsigned int imgh,unsigned int& imgW,unsigned int& imgH,Mat& img) {
	switch (code) {
	case 0:
		cap.set(CAP_PROP_FOURCC, VideoWriter::fourcc('M', 'J', 'P', 'G'));
		break;
	case 1:
		cap.set(CAP_PROP_FOURCC, VideoWriter::fourcc('Y', 'U', 'Y', 'V'));
		break;
	default:
		cerr << "Error : wrong code" << endl;
		return 0;
	}
	cap.set(CAP_PROP_FPS, fps);
	cap.set(cv::CAP_PROP_FRAME_WIDTH, imgw);
	cap.set(cv::CAP_PROP_FRAME_HEIGHT, imgh);
	cap.read(img);
	imgW = imgw;
	imgH = imgh;
	//USE_num = imgH * 3;
	return 1;
}
void imgprocess(unsigned int& imgW,unsigned int& imgH,Mat& img,Mat& imggray,Mat& binimg,Mat& imgoutput) {
    Mat binimg1;
	if (img.size().width > 1)cvtColor(img, imggray, COLOR_BGR2GRAY);
	threshold(imggray, binimg, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
	Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	erode(binimg, binimg1, kernel);
	dilate(binimg1, binimg, kernel);
	//封框
	line(binimg, Point(0, 0), Point(imgW, 0), Scalar(0), 3, 8, 0);
	line(binimg, Point(imgW, 0), Point(imgW, imgH), Scalar(0), 3, 8, 0);
	line(binimg, Point(imgW, imgH), Point(0, imgH), Scalar(0), 3, 8, 0);
	line(binimg, Point(0, imgH), Point(0, 0), Scalar(0), 3, 8, 0);
	cvtColor(binimg, imgoutput, COLOR_GRAY2BGR);//输出图像为imgoutput
}