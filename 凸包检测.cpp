#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat src, dst;
char imgsrc[] = "源图", imgdst[] = "目标图", imgdraw[] = "绘制图";
int main()
{
	src = imread("Resources/B1.jpg");
	namedWindow(imgsrc, WINDOW_AUTOSIZE);
	namedWindow(imgdst, WINDOW_AUTOSIZE);
	cvtColor(src, dst, COLOR_BGR2GRAY);
	blur(dst, dst, Size(3, 3));
	threshold(dst, dst, 100, 255, THRESH_BINARY);
	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	findContours(dst, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	vector<vector<Point>> convexs(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
	{
		convexHull(contours[i], convexs[i], false, true);
	}
	RNG rng(12345);
	Mat drawdst = Mat::zeros(src.size(), CV_8UC3);
	for (size_t k = 0; k < contours.size(); k++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawdst, contours, k, color);
		drawContours(drawdst, convexs, k, color);
	}
	imshow(imgdraw, drawdst);
	imshow(imgsrc, src);
	imshow(imgdst, dst);
	waitKey(0);
	return 0;
}