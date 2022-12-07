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
	resize(img, imgResize, Size(),0.4,0.4);//后两个数调缩放比例
	Rect roi(100, 100, 1000, 1000);//矩形数据类型,(100,100)是起始点，后面两个是宽和高
	imgCrop = img(roi);//裁剪，上面是参数
	imshow("Image Reszie", imgResize);
	imshow("1", imgCrop);
	waitKey(0);

}