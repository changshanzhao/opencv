#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;
int main()
{
	/*
		vector<Mat> myTemplate;
	
		string path = "C:/Users/Lenovo/Pictures/Camera Roll/";
	for (int i = 0; i < 5; i++)
	{
		Mat temp1 = imread(path+to_string(i) + ".jpg", 1);
		myTemplate.push_back(temp1);
		resize(myTemplate[i], myTemplate[i], Size(32, 32), (0, 0), (0, 0));
		vector<int> compression_params;
		compression_params.push_back(IMWRITE_PXM_BINARY);
		compression_params.push_back(1);
		imwrite(to_string(i)+".pgm", myTemplate[i], compression_params);
		//imwrite(path+to_string(i) + ".bmp", myTemplate[i]);
		
	}
	*/
	Mat temp1 = imread("D:/repos/opencv/opencv/Resources/new/A.jpg", 0);
	vector<int> compression_params;
	resize(temp1, temp1, Size(32, 32), (0, 0), (0, 0));
	compression_params.push_back(IMWRITE_PXM_BINARY);
	compression_params.push_back(1);
	imwrite("D:/repos/opencv/opencv/Resources/new/A.pgm", temp1, compression_params);
	return 0;
}