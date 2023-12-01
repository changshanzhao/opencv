#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;
//��ͼƬ�������
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
    Mat src1 = imread("Resources/122.jpg");//��ȡͼƬ1
    Mat src2;
    Mat src3;
    cvtColor(src1, src2, 6);  //CV_BGR2GRAY
    threshold(src2, src3, 145, 255, 0);//����ֵԽС������ȥ���ĸ���������Խ�࣬������5ȱʧ��������
    //Mat src2 = imread("2.png");//��ȡͼƬ2(��ֵ������ʴ���ͣ�͹����⣩��ĻҶ�ͼ��
    if (src1.empty()) {
        printf("Could not find image file");
        return -1;
    }
    imshow("�Ҷ�", src2);
    imshow("��ֵ��1", src3);


    Mat dst2;
    subtract(src2, src3, dst2);//������������ͼƬ1��ͼƬ2�����ͼƬ3
    imshow("subtract-demo", dst2);
    Mat src4;
    threshold(dst2, src4, 80, 255, 0);//����ֵ���ԽС������5������Խ����������������
    imshow("threshold", src4);



    //�������޸�
    //Mat src6;
    //morphologyEx(src5, src6, MORPH_CLOSE, element);
    //imshow("close", src6);��ʹ���ֱ�Ե��������һ�㣬���Ա�ͼ��˵���Ե�û��Ҫ

    //ȡԤ�����������ͨ��
    Mat labels;
    //1. �����ͨ��
    int n_comps = connectedComponents(src4, labels, 4, CV_16U);//�Ҷ�ͼ��CV_8U
    vector<int> histogram_of_labels;

    for (int i = 0; i < n_comps; i++)//��ʼ��labels�ĸ���Ϊ0
    {
        histogram_of_labels.push_back(0);
    }

    int rows = labels.rows;
    int cols = labels.cols;
    for (int row = 0; row < rows; row++) //����ÿ��labels�ĸ���
    {
        for (int col = 0; col < cols; col++)
        {
            histogram_of_labels.at(labels.at<unsigned short>(row, col)) += 1;
        }
    }
    histogram_of_labels.at(0) = 0; //��������labels��������Ϊ0

    //2. ����������ͨ��labels����
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

    //3. �������ͨ����Ϊ1
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
    //4. ��ͼ�����ΪCV_8U��ʽ
    labels.convertTo(labels, CV_8U);
    imshow("���������ͨ��", labels);

    //�����㣨�ȸ�ʴ�����ͣ�ȥ�׵�
    Mat src5;
    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2, 2));
    morphologyEx(labels, src5, MORPH_OPEN, element);
    imshow("open", src5);//ֱ�ӿ�����Ч�����ã���ʹ�˺�СҲ���׽����ֽض�
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