#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main() {
	cv::Mat src = cv::imread("C:/Users/Lenovo/Desktop/Attachment/Attachment/Attachment 1/171.jpg");
	cv::Mat blurredImage;
	cv::namedWindow("blurredImage", 1);
	// 高斯滤波
	cv::GaussianBlur(src, blurredImage, cv::Size(3, 3), 0);
	cv::imshow("blurredImage", blurredImage);
	std::vector<cv::Mat> channels;
	cv::split(src, channels);

	// R通道减去G通道
	cv::Mat diffImage;
	cv::subtract(channels[1], channels[2], diffImage);

	// 显示原始图像和通道相减后的图像
	cv::imshow("Difference Image", diffImage);
	// 二值化
	cv::Mat binaryImage;
	double thresholdValue = 64;  // 阈值
	double maxValue = 255;  // 最大值
	cv::threshold(diffImage, binaryImage, thresholdValue, maxValue, cv::THRESH_BINARY);
	cv::imshow("binaryImage", binaryImage);
    // 连通组件分析
    cv::Mat labels, stats, centroids;
    int numLabels = cv::connectedComponentsWithStats(binaryImage, labels, stats, centroids);

    // 过滤小色块并统计数量
    int minAreaThreshold = 10;  // 最小面积阈值
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
    std::cout << "过滤后的色块数目： " << filteredBlobCount << std::endl;


	cv::waitKey(0);

	return 0;
}