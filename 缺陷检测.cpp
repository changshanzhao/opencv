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
			std_l = arcLength(contours[i], true) - 9700;
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
	//vector<Mat> NG;
	//for (int i = 1; i <= 11; i++) {
		//NG.push_back(imread("Resources/NG/" + to_string(i) + ".png",1));
	//}
	
	Mat src = imread("Resources/NG/standard.png",1);
	Mat std;
	cvtColor(src, std, COLOR_BGR2GRAY);
	GaussianBlur(std, Blur, Size(1, 1), 5, 0);
	
	//namedWindow("Blur", 0);
	//imshow("Blur", Blur);
	threshold(Blur, std, 80, 255, 0);
	de(std);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(31, 31));
	dilate(std, dil, kernel);
	erode(std, ero, kernel);
	//vector<Vec2f> lines;
	//Canny(std, canny, 0, 20, 3);
	//namedWindow("canny", 0);
	//imshow("canny", canny);
	//namedWindow("res", 0);
	//imshow("res", res);
	//HoughLines(canny, lines, 1, CV_PI / 180, 200,0,0);

	//morphologyEx(std, close, MORPH_CLOSE, kernel);
	//morphologyEx(std, open, MORPH_OPEN, kernel);
	//double delt1 = (std_l - get_len(dil))/std_l;
	//double delt2 = (std_l - get_len(ero))/std_l;
	//double delt = delt2 - delt1;
	cout << get_len(dil) << "\t" << get_len(ero) << endl;
	cout << get_len(std) << endl;
	//cout << delt1 << "\t" << delt2 << "\t";
	//cout << delt << endl;

	//for (size_t i = 0; i < lines.size(); i++)
	//{
		//float rho = lines[i][0], theta = lines[i][1];
		//Point pt1, pt2;
		//double a = cos(theta), b = sin(theta);
		//double x0 = a * rho, y0 = b * rho;
		//pt1.x = cvRound(x0 + 1000 * (-b));
		//pt1.y = cvRound(y0 + 1000 * (a));
		//pt2.x = cvRound(x0 - 1000 * (-b));
		//pt2.y = cvRound(y0 - 1000 * (a));
		//line(src, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
	//}
	//namedWindow("std", 0);
	//imshow("std", std);
	//namedWindow("src", 0);
	//imshow("src", src);
	//namedWindow("dil", 0);
	//imshow("dil", dil);
	//namedWindow("ero", 0);
	//imshow("ero", ero);
	//namedWindow("open", 0);
	//imshow("open", open);
	/*
	if (fabs(delt) > 4 || fabs(delt1) < 0.8)
	{
		cout << "NG!" << endl;
	}
	else cout << "合格" << endl;
	*/
	waitKey(0);
	return 0;
}