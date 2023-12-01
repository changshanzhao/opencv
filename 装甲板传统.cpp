#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;
//两图片相减部分
vector<double> val;
vector<Point> loc;
vector<Mat> myTemplate;
Mat re_size(Mat input_pre)
{
    Mat res1;
    resize(input_pre, res1, cv::Size(), 0.75, 0.75, cv::INTER_CUBIC);
    return res1;
}


int main(int argc, char* argv[])
{
    Mat src1 = imread("Resources/122.jpg");//读取图片1
    Mat src2;
    Mat src3;
    cvtColor(src1, src2, 6);  //CV_BGR2GRAY
    threshold(src2, src3, 145, 255, 0);//该阈值越小，可以去除的高亮度噪音越多，但数字5缺失几率增加
    //Mat src2 = imread("2.png");//读取图片2(二值化、腐蚀膨胀（凸包检测）后的灰度图）
    if (src1.empty()) {
        printf("Could not find image file");
        return -1;
    }
    imshow("灰度", src2);
    imshow("二值化1", src3);


    Mat dst2;
    subtract(src2, src3, dst2);//减法操作输入图片1，图片2，输出图片3
    imshow("subtract-demo", dst2);
    Mat src4;
    threshold(dst2, src4, 80, 255, 0);//该阈值设的越小，数字5保留的越完整但是噪音增多
    imshow("threshold", src4);



    //闭运算修复
    //Mat src6;
    //morphologyEx(src5, src6, MORPH_CLOSE, element);
    //imshow("close", src6);能使数字边缘向外扩大一点，但对本图来说可以但没必要

    //取预处理后最大的连通域
    Mat labels;
    //1. 标记连通域
    int n_comps = connectedComponents(src4, labels, 4, CV_16U);//灰度图：CV_8U
    vector<int> histogram_of_labels;

    for (int i = 0; i < n_comps; i++)//初始化labels的个数为0
    {
        histogram_of_labels.push_back(0);
    }

    int rows = labels.rows;
    int cols = labels.cols;
    for (int row = 0; row < rows; row++) //计算每个labels的个数
    {
        for (int col = 0; col < cols; col++)
        {
            histogram_of_labels.at(labels.at<unsigned short>(row, col)) += 1;
        }
    }
    histogram_of_labels.at(0) = 0; //将背景的labels个数设置为0

    //2. 计算最大的连通域labels索引
    int maximum = 0;
    int max_idx = 0;
    for (int i = 0; i < n_comps; i++)
    {
        if (histogram_of_labels.at(i) > maximum)
        {
            maximum = histogram_of_labels.at(i);
            max_idx = i;
        }
    }

    //3. 将最大连通域标记为1
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            if (labels.at<unsigned short>(row, col) == max_idx)
            {
                labels.at<unsigned short>(row, col) = 255;
            }
            else
            {
                labels.at<unsigned short>(row, col) = 0;
            }
        }
    }
    //4. 将图像更改为CV_8U格式
    labels.convertTo(labels, CV_8U);
    imshow("保留最大连通域", labels);

    //开运算（先腐蚀后膨胀）去白点
    Mat src5;
    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2, 2));
    morphologyEx(labels, src5, MORPH_OPEN, element);
    imshow("open", src5);//直接开运算效果不好，即使核很小也容易将数字截断
    imwrite("Resources/test/5.png", src5);
    for (int i = 0; i < 10; i++)
    {
        Mat temp1 = imread("Resources/" + to_string(i) + ".jpg", 1);
        if (temp1.empty()) {
            printf("Could not find image file");
            return -1;
        }
        bitwise_not(temp1, temp1);
        myTemplate.push_back(temp1);
    }

    Mat input_pre = imread("Resources/test/5.png",1);

    Mat input = re_size(input_pre);
    for (int j = 0; j < 10; j++)
    {
        Mat res;
        Mat Template = myTemplate[j];
        matchTemplate(input, Template, res, TM_CCOEFF_NORMED);
        Point minLoc, maxLoc;
        double maxVal, minVal;
        minMaxLoc(res, &minVal, &maxVal, &minLoc, &maxLoc);
        val.push_back(maxVal);
        loc.push_back(maxLoc);
    }
    int maxPosition = max_element(val.begin(), val.end()) - val.begin();

    cout << maxPosition << endl;
    rectangle(input, Rect(loc[maxPosition].x, loc[maxPosition].y, 30, 30), Scalar(0, 0, 255), 2);
    imshow("img", input);
    cout << maxPosition << endl;


    waitKey(0);

    return 0;
}