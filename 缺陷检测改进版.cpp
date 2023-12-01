#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <math.h>
using namespace cv;
using namespace std;
Mat dil, ero, Blur, canny, open, close;
double std_l;
void de(Mat& std)
{
	bitwise_not(std, std); //这里先变反转颜色
	//std.copyTo(res);
	//res = Scalar::all(0);
	vector<vector<Point> > contours; // Vector for storing contours

	findContours(std, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); // Find the contours in the image
	for (size_t i = 0; i < contours.size(); i++) // iterate through each contour.
	{
		double area = contourArea(contours[i]); // 填充无关图像
		if (area < 1000000)
		{
			drawContours(std, contours, i, Scalar(0), FILLED);
		}
		else // 忽略内部情况
		{
			std_l = arcLength(contours[i], true);
			drawContours(std, contours, i, Scalar(255), FILLED);
		}
	}
	GaussianBlur(std, std, Size(5, 5), 5, 0);
}
double get_len(Mat& std)
{
	vector<vector<Point> > contours; // Vector for storing contours
	findContours(std, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); // Find the contours in the image
	return arcLength(contours[0], true);
}
int main()
{
	vector<Mat> NG;
	for (int i = 1; i <= 11; i++) {
		NG.push_back(imread("Resources/NG/" + to_string(i) + ".png",1));
		Mat src = NG[i-1];
		Mat std;
		cvtColor(src, std, COLOR_BGR2GRAY);
		GaussianBlur(std, Blur, Size(1, 1), 5, 0);
		threshold(Blur, std, 80, 255, 0);
		de(std);
		Mat kernel = getStructuringElement(MORPH_RECT, Size(31, 31));
		dilate(std, dil, kernel);
		erode(std, ero, kernel);
		/*
		double delt1 = (std_l - get_len(dil)) / std_l;
		double delt2 = (std_l - get_len(ero)) / std_l;
		double delt = delt2 - delt1;
		cout << delt1 << "\t" << delt2 << "\t";
		cout << delt << endl;
		if (fabs(delt) > 4 || fabs(delt1) < 0.8)
		{
			cout << "NG!" << endl;
		}
		else cout << "合格" << endl;
		*/
		float nameta = 50;
		float len_dil = 9691.79;
		float len_ero = 9424.63;
		float len_std = 9585;
		double d1 = 1 - ((get_len(dil) - len_dil) - (nameta * (get_len(std) - len_std))) / len_std;
		double d2 = 1 - ((get_len(ero) - len_ero) - (nameta * (get_len(std) - len_std))) / len_std;
		cout << to_string(i) << "的d1是" << d1 << endl;
		cout << to_string(i) << "的d2是" << d2 << endl;
	}
	waitKey(0);
	return 0;
}