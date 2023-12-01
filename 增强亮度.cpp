#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


// 计算图像的平均值和标准差
void calculateMeanStd(Mat& img, double& mean, double& stdDev) {
    Scalar meanScalar, stdDevScalar;
    meanStdDev(img, meanScalar, stdDevScalar);
    mean = meanScalar[0];
    stdDev = stdDevScalar[0];
}

// 对图像进行亮度增强
void enhanceBrightness(Mat& img, double alpha, double beta) {
    Mat dst;
    img.convertTo(dst, -1, alpha, beta);
    img = dst.clone();
}


int main(int argc, char** argv) {
    // 读取图像
    Mat img = imread("Resources/B1.jpg", IMREAD_GRAYSCALE);
    imshow("input", img);
    // 计算图像的平均值和标准差
    double mean, stdDev;
    calculateMeanStd(img, mean, stdDev);

    // 计算亮度增强的参数
    double alpha = 2.0, beta = -mean / stdDev;
    enhanceBrightness(img, alpha, beta);

    // 显示图像
    imshow("Output", img);
    waitKey(0);

    return 0;
}
