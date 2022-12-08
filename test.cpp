#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
/*
int main(int argc, char* argv[])
{
	string path = "Resources/1.jpg";
	Mat img = imread(path);
	imshow("Image", img);
	waitKey(0);
	return 0;
}
*/
int main(int argc, char* argv[]) 
{
	string path = "Resources/4.mp4";
	VideoCapture cap(0);//0ÊÇÉãÏñÍ·
	Mat img;
	while (true)
	{
		cap.read(img);
		imshow("Image", img);
		waitKey(1);
	}
	return 0;
}