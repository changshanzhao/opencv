#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("jx.jpg");
	if (!srcImage.data) {
		cout << "failed to read" << endl;
		system("pause");
		return -1;
	}
	imshow("srcImage", srcImage);
	//存储彩色直方图及图像通道向量
	Mat colorHeqImage;
	vector<Mat> BGR_plane;
	//分离BGR通道
	split(srcImage, BGR_plane);
	//分别对BGR通道进行直方图均衡化
	for (int i = 0; i < BGR_plane.size(); i++) {
		equalizeHist(BGR_plane[i], BGR_plane[i]);
	}
	//合并通道
	merge(BGR_plane, colorHeqImage);
	imshow("heqResult", colorHeqImage);
	waitKey(0);
	return 0;
}