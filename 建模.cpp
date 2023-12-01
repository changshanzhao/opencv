#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main() {
	cv::Mat src = cv::imread("C:/Users/Lenovo/Desktop/Attachment/Attachment/Attachment 1/171.jpg");
	cv::Mat blurredImage;
	cv::namedWindow("blurredImage", 1);
	// ��˹�˲�
	cv::GaussianBlur(src, blurredImage, cv::Size(3, 3), 0);
	cv::imshow("blurredImage", blurredImage);
	std::vector<cv::Mat> channels;
	cv::split(src, channels);

	// Rͨ����ȥGͨ��
	cv::Mat diffImage;
	cv::subtract(channels[1], channels[2], diffImage);

	// ��ʾԭʼͼ���ͨ��������ͼ��
	cv::imshow("Difference Image", diffImage);
	// ��ֵ��
	cv::Mat binaryImage;
	double thresholdValue = 64;  // ��ֵ
	double maxValue = 255;  // ���ֵ
	cv::threshold(diffImage, binaryImage, thresholdValue, maxValue, cv::THRESH_BINARY);
	cv::imshow("binaryImage", binaryImage);
    // ��ͨ�������
    cv::Mat labels, stats, centroids;
    int numLabels = cv::connectedComponentsWithStats(binaryImage, labels, stats, centroids);

    // ����Сɫ�鲢ͳ������
    int minAreaThreshold = 10;  // ��С�����ֵ
    int filteredBlobCount = 0;
    cv::Mat filteredImage = cv::Mat::zeros(src.size(), CV_8UC1);

    for (int i = 1; i < numLabels; i++)
    {
        int area = stats.at<int>(i, cv::CC_STAT_AREA);

        if (area >= minAreaThreshold)
        {
            cv::Mat mask = (labels == i);
            filteredImage.setTo(255, mask);
            filteredBlobCount++;
        }
    }
    std::cout << "���˺��ɫ����Ŀ�� " << filteredBlobCount << std::endl;


	cv::waitKey(0);

	return 0;
}