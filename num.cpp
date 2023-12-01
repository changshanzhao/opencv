#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
enum Color
{
	BLUE = 0,
	GREEN = 1,
	RED = 2
};
Color enemyColor = BLUE;
Mat srcImg, warpPerspective_src, srcImg_binary;
void setImg(Mat& src) {

	src.copyTo(srcImg);  //deep copy src to srcImg 深（值）拷贝给srcImg
	(srcImg).copyTo(warpPerspective_src);
	//preprocess srcImg for the goal of acceleration
	cvtColor(warpPerspective_src, warpPerspective_src, 6);  //CV_BGR2GRAY=6
	threshold(warpPerspective_src, warpPerspective_src, 10, 255, THRESH_BINARY);
	srcImg_binary = Mat::zeros(srcImg.size(), CV_8UC1); //color feature image

	//pointer visits all the data of srcImg, the same to bgr channel split 通道相减法的自定义形式，利用指针访问，免去了split、substract和thresh操作，加速了1.7倍
	//data of Mat  bgr bgr bgr bgr
	uchar* pdata = (uchar*)srcImg.data;
	uchar* qdata = (uchar*)srcImg_binary.data;
	int srcData = srcImg.rows * srcImg.cols;
	if (enemyColor == RED)
	{
		for (int i = 0; i < srcData; i++)
		{
			if (*(pdata + 2) - *pdata > 100)
				*qdata = 255;
			pdata += 3;
			qdata++;
		}
	}
	else if (enemyColor == BLUE)
	{
		for (int i = 0; i < srcData; i++)
		{
			if (*pdata - *(pdata + 2) > 90)
				*qdata = 255;
			pdata += 3;
			qdata++;
		}
	}

	Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3)); //kernel for dilate;  shape:ellipse size:Size(3,3) 膨胀操作使用的掩膜
	dilate(srcImg_binary, srcImg_binary, kernel); //dilate the roiImg_binary which can make the lightBar area more smooth 对roiIng_binary进行膨胀操作，试得灯条区域更加平滑有衔接
	imshow("srcImg_binary", srcImg_binary);
}
Mat re_size(Mat input_pre, Mat Template_pre)
{
	Mat res1;
	int x = Template_pre.cols * 5;
	int y = Template_pre.rows * 7;
	resize(input_pre, res1, cv::Size(y, x), 0, 0, cv::INTER_CUBIC);
	return res1;
}
int main(int argc, char* argv[])
{
	vector<Mat> myTemplate;
	vector<Mat> frame;
	for (int i = 0; i < 5; i++)
	{
		Mat temp1 = imread("Resources/" + to_string(i + 1) + ".jpg", 1);
		myTemplate.push_back(temp1);
	}
	for (int i = 0; i < 4; i++)
	{
		Mat temp2 = imread("Resources/B" + to_string(i + 1) + ".jpg", 1);
		frame.push_back(temp2);
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Mat input_pre = frame[i];
			Mat Template_pre = myTemplate[j];
			Mat res;

			Mat input = re_size(input_pre, Template_pre);
			setImg(input_pre);
			Mat Template = Template_pre;


			matchTemplate(input, Template, res, TM_CCOEFF_NORMED);
			Point minLoc, maxLoc;
			double maxVal, minVal;
			minMaxLoc(res, &minVal, &maxVal, &minLoc, &maxLoc);
			rectangle(input, cv::Rect(maxLoc.x, maxLoc.y, Template.cols, Template.rows), Scalar(0, 0, 255), 2);
			//imshow("img", input);
			waitKey(0);
		}
	}
	return 0;
}
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

vector<double> val;
vector<Point> loc;
Mat re_size(Mat input_pre)
{
	Mat res1;
	resize(input_pre, res1, cv::Size(), 0.65, 0.65, cv::INTER_CUBIC);
	return res1;
}

int main(int argc, char* argv[])
{
	vector<Mat> myTemplate;
	for (int i = 0; i < 10; i++)
	{
		Mat temp1 = imread("Resources/" + to_string(i) + ".jpg", 1);
		bitwise_not(temp1, temp1);
		myTemplate.push_back(temp1);
	}
	Mat test = imread("Resources/test" + to_string(5) + ".jpg", 1);
	Mat input_pre = test;
	Mat input = re_size(input_pre);
	for (int j = 0; j < 10; j++)
	{
		Mat res;
		Mat Template = myTemplate[j];
		matchTemplate(input, Template, res, TM_CCOEFF_NORMED);
		Point minLoc, maxLoc;
		double maxVal, minVal;
		minMaxLoc(res, &minVal, &maxVal, &minLoc, &maxLoc);
		val.push_back(maxVal);
		loc.push_back(maxLoc);
	}
	int maxPosition = max_element(val.begin(), val.end()) - val.begin();

	cout << maxPosition << endl;
	rectangle(input, Rect(loc[maxPosition].x, loc[maxPosition].y, 30, 30), Scalar(0, 0, 255), 2);
	imshow("img", input);
	cout << maxPosition << endl;
	waitKey(0);
	return 0;
}
//--------------------
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

vector<double> val;
vector<Point> loc;
Mat re_size(Mat input_pre)
{
	Mat res1;
	resize(input_pre, res1, cv::Size(), 0.65, 0.65, cv::INTER_CUBIC);
	return res1;
}

int main(int argc, char* argv[])
{
	vector<Mat> myTemplate;
	for (int i = 0; i < 10; i++)
	{
		Mat temp1 = imread("Resources/" + to_string(i) + ".jpg", 1);
		bitwise_not(temp1, temp1);
		myTemplate.push_back(temp1);
	}
	Mat test = imread("Resources/test" + to_string(5) + ".png", 1);
	Mat input_pre = test;
	Mat input = re_size(input_pre);
	for (int j = 0; j < 10; j++)
	{
		Mat res;
		Mat Template = myTemplate[j];
		matchTemplate(input, Template, res, TM_CCOEFF_NORMED);
		Point minLoc, maxLoc;
		double maxVal, minVal;
		minMaxLoc(res, &minVal, &maxVal, &minLoc, &maxLoc);
		val.push_back(maxVal);
		loc.push_back(maxLoc);
	}
	int maxPosition = max_element(val.begin(), val.end()) - val.begin();

	cout << maxPosition << endl;
	rectangle(input, Rect(loc[maxPosition].x, loc[maxPosition].y, 30, 30), Scalar(0, 0, 255), 2);
	imshow("img", input);
	cout << maxPosition << endl;
	waitKey(0);
	return 0;
}