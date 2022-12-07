#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main(int argc, char* argv[])
{
	string path = "Resources/5.jpg";
	Mat img = imread(path);
	Mat imgResize,imgCrop;
	resize(img, imgResize, Size(),0.4,0.4);//�������������ű���
	Rect roi(100, 100, 1000, 1000);//������������,(100,100)����ʼ�㣬���������ǿ�͸�
	imgCrop = img(roi);//�ü��������ǲ���
	imshow("Image Reszie", imgResize);
	imshow("1", imgCrop);
	waitKey(0);

}