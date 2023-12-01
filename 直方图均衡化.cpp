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
	//�洢��ɫֱ��ͼ��ͼ��ͨ������
	Mat colorHeqImage;
	vector<Mat> BGR_plane;
	//����BGRͨ��
	split(srcImage, BGR_plane);
	//�ֱ��BGRͨ������ֱ��ͼ���⻯
	for (int i = 0; i < BGR_plane.size(); i++) {
		equalizeHist(BGR_plane[i], BGR_plane[i]);
	}
	//�ϲ�ͨ��
	merge(BGR_plane, colorHeqImage);
	imshow("heqResult", colorHeqImage);
	waitKey(0);
	return 0;
}