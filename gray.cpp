#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	string path = "Resources/4.jpg";
	Mat img = imread(path);
	Mat res;
	cvtColor(img, res, COLOR_BGR2GRAY);
	imwrite("Template_4.jpg", res);
	imshow("Image", res);
	
	waitKey(0);
	return 0;
}