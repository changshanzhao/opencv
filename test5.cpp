#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
void main()
{
	Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));
	circle(img, Point(256, 256), 155, Scalar(0, 69, 255),FILLED);//FILLED位置写数字也行，代表线条的厚度
	rectangle(img, Point(130, 266),Point(382, 286), Scalar(255, 255, 255), FILLED);//两个点确定对角线
	line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);
	putText(img, "junbo is a good boy", Point(127, 262), FONT_HERSHEY_COMPLEX, 0.75, Scalar(255, 255, 255), 2);//0.75是大小，2是厚度
	imshow("Image", img);
	waitKey(0);
}