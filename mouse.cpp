#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
Mat img, imgPoint;
Point prePoint;
void mouse(int event, int x, int y, int flags, void*);
int main()
{
	string path = "Resources/10.png";
	img = imread(path);
	if (!img.data)
	{
		cout << "��ȷ������ͼ�������Ƿ���ȷ��" << endl;
		return -1;
	}
	img.copyTo(imgPoint);
	imshow("img", img);
	imshow("imgPoint", imgPoint);
	setMouseCallback("img", mouse, 0);
	waitKey(0);
	return 0;
}
void mouse(int event, int x, int y, int flags, void*)
{
	if (event == EVENT_RBUTTONDOWN)
	{
		cout << "����������ſ��Ի��ƹ켣" << endl;
	}
	if (event == EVENT_LBUTTONDOWN)
	{
		prePoint = Point(x, y);
		cout << "�켣��ʼ����" << prePoint << endl;
	}
	if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
	{
		imgPoint.at<Vec3b>(y, x) = Vec3b(0, 255, 0);
		imgPoint.at<Vec3b>(y, x-1) = Vec3b(0, 255, 0);
		imgPoint.at<Vec3b>(y, x+1) = Vec3b(0, 255, 0);
		imgPoint.at<Vec3b>(y-1, x) = Vec3b(0, 255, 0);
		imgPoint.at<Vec3b>(y+1, x) = Vec3b(0, 255, 0);
		imshow("imgPoint", imgPoint);
		Point pt(x, y);
		line(img, prePoint, pt, Scalar(0, 255, 0), 2, 8, 0);
		prePoint = pt;
		imshow("img", img);
	}
}