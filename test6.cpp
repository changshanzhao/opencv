#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
float w = 57, h = 69;
Mat matrix, imgWarp;
int main(int argc, char* argv[])
{
	string path = "Resources/2.jpg";
	Mat img = imread(path);
	Point2f src[4] = { {13,25},{70,25},{31,74},{87,74} };
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };
	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));
	imshow("Image", img);
	imshow("Image Warp", imgWarp);
	waitKey(0);
	

}