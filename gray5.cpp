#define k_size 2
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int ks = k_size;
Mat gray(Mat img)
{
	int i;
	int j;
	
	for (i = 0; i < 480; i+=ks)
	{
		for (j = 0; j < 640; j += ks)
		{
			int ave = img.at<uchar>(i, j) + img.at<uchar>(i + 1, j) + img.at<uchar>(i, j + 1) + img.at<uchar>(i + 1, j + 1) / (ks * ks);
			int val = ave / 51;
			switch (val)
			{
			case 0:
				img.at<uchar>(i, j) = 0;
				img.at<uchar>(i, j+1) = 0;
				img.at<uchar>(i+1, j) = 0;
				img.at<uchar>(i+1, j+1) = 0;
				break;
			case 1:
				img.at<uchar>(i, j) = 0;
				img.at<uchar>(i, j+1) = 0;
				img.at<uchar>(i+1, j) = 255;
				img.at<uchar>(i+1, j+1) = 0;
				break;
			case 2:
				img.at<uchar>(i, j) = 0;
				img.at<uchar>(i, j+1) = 255;
				img.at<uchar>(i+1, j) = 255;
				img.at<uchar>(i+1, j+1) = 0;
				break;
			case 3:
				img.at<uchar>(i, j) = 0;
				img.at<uchar>(i, j+1) = 255;
				img.at<uchar>(i+1, j) = 255;
				img.at<uchar>(i+1, j+1) = 255;
				break;
			default:
				img.at<uchar>(i, j) = 255;
				img.at<uchar>(i, j+1) = 255;
				img.at<uchar>(i+1, j) = 255;
				img.at<uchar>(i+1, j+1) = 255;
				break;
			}
		}
	}
	return img;
}
int main(int argc, char* argv[])
{
	string path = "Resources/3.mp4";//640 480
	VideoCapture cap(path);
	Mat frame;
	while (true)
	{
		cap >> frame;
		if (frame.empty())
		{
			break;
		}
		Mat img;
		cvtColor(frame, img, COLOR_BGR2GRAY);
		Mat imggray = gray(img);
		imshow("video", imggray);
		waitKey(1000 / cap.get(CAP_PROP_FPS));
	}
	return 0;
}