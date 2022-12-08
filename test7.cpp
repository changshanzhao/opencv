#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
//颜色检测
int hmin = 0, smin = 0, vmin = 0;
int hmax = 255, smax = 255, vmax = 255;
int main(int argc, char* argv[])
{
	string path = "Resources/6.jpg";
	Mat img = imread(path);
	Mat imgHSV,mask;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);//色相最大是180 0-179
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);
	while (true)
	{
		Scalar lower(hmin, smin, vmin);//色度 饱和度 亮度 HSV模型
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);
		imshow("Image", img);
		imshow("ImageHSV", imgHSV);
		imshow("mask", mask);
		waitKey(1);
	}
	
	return 0;
}