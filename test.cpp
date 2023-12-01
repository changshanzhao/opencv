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
	string path = "C:/Users/Lenovo/Desktop/CUMCM2023Problems/A��/˼·.mp4";
	VideoCapture cap(path);
	Mat frame;
	int i = 0;
	while (true)
	{
		cap >> frame;
		if (frame.empty())
		{
			break;
		}
		imshow("video", frame);
		imwrite("C:/Users/Lenovo/Desktop/CUMCM2023Problems/A��/��ͼ/" + to_string(i) + ".jpg", frame);
		waitKey(20);
		i++;
	}
	return 0;
}