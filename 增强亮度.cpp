#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


// ����ͼ���ƽ��ֵ�ͱ�׼��
void calculateMeanStd(Mat& img, double& mean, double& stdDev) {
    Scalar meanScalar, stdDevScalar;
    meanStdDev(img, meanScalar, stdDevScalar);
    mean = meanScalar[0];
    stdDev = stdDevScalar[0];
}

// ��ͼ�����������ǿ
void enhanceBrightness(Mat& img, double alpha, double beta) {
    Mat dst;
    img.convertTo(dst, -1, alpha, beta);
    img = dst.clone();
}


int main(int argc, char** argv) {
    // ��ȡͼ��
    Mat img = imread("Resources/B1.jpg", IMREAD_GRAYSCALE);
    imshow("input", img);
    // ����ͼ���ƽ��ֵ�ͱ�׼��
    double mean, stdDev;
    calculateMeanStd(img, mean, stdDev);

    // ����������ǿ�Ĳ���
    double alpha = 2.0, beta = -mean / stdDev;
    enhanceBrightness(img, alpha, beta);

    // ��ʾͼ��
    imshow("Output", img);
    waitKey(0);

    return 0;
}
