#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;

int getSpeed(const cv::Mat& roiImage, vector<cv::Mat> myTemplate, vector<cv::Mat> myTemplate_2)
{
	for (int j = 0; j < 10; j++)
	{
		cv::Mat matDst1, matDst2;
		cv::resize(roiImage, matDst1, cv::Size(8, 8), 0, 0, cv::INTER_CUBIC);
		cv::resize(myTemplate[j], matDst2, cv::Size(8, 8), 0, 0, cv::INTER_CUBIC);

		int iAvg1 = 0, iAvg2 = 0;
		int arr1[64], arr2[64];

		for (int i = 0; i < 8; i++)
		{
			uchar* data1 = matDst1.ptr<uchar>(i);
			uchar* data2 = matDst2.ptr<uchar>(i);

			int tmp = i * 8;

			for (int j = 0; j < 8; j++)
			{
				int tmp1 = tmp + j;

				arr1[tmp1] = data1[j] / 4 * 4;
				arr2[tmp1] = data2[j] / 4 * 4;

				iAvg1 += arr1[tmp1];
				iAvg2 += arr2[tmp1];
			}
		}

		iAvg1 /= 64;
		iAvg2 /= 64;

		for (int i = 0; i < 64; i++)
		{
			arr1[i] = (arr1[i] >= iAvg1) ? 1 : 0;
			arr2[i] = (arr2[i] >= iAvg2) ? 1 : 0;
		}

		int iDiffNum = 0;

		for (int i = 0; i < 64; i++)
			if (arr1[i] != arr2[i])
				++iDiffNum;

		//cout << "iDiffNum = " << iDiffNum << endl;
		if (iDiffNum <= 7)
		{
			return j;
		}

	}
	return 0;
}

int main()
{

	// 模板加载
	vector<cv::Mat> myTemplate;
	cv::Mat frame;
	for (int i = 1; i < 5; i++)
	{
		cv::Mat temp = cv::imread("Resources/" + to_string(i) + ".jpg", 0);
		myTemplate.push_back(temp);
	}

	// 数字ROI区域获取
	cv::Rect temp;
	temp.x = 578;
	temp.y = 60;
	temp.width = 12;
	temp.height = 31;
	for (int i = 0; i < ; i++)
	{
		cv::Mat roiImage1(frame, cv::Rect(temp));
		cv::cvtColor(roiImage1, roiImage1, cv::COLOR_BGR2GRAY);
		//cv::imshow("1", roiImage1);

		// 先存为模板
		cv::imwrite("./number_2/" + to_string(rand() % 300) + ".jpg", roiImage1);    //写入文件

		// 模板比对
		int result3 = getSpeed(roiImage3, myTemplate, myTemplate_2);
		cout << endl;
	}
	

}

