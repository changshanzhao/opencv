#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
vector<vector<int>> myColors{ {124,48,117,143,170,255},{68,72,156,102,126,255}};
vector<Scalar> myColorValues{ {255,0,255},{0,255,0} };
Mat img;
vector<vector<int>> newPoints;
Point getContours(Mat imgDil)
{
	vector<vector<Point>> contours;//vector<vector<Point>>��һ�����ͣ���������һ�������������������һ����
	vector<Vec4i> hierarchy;
	Point myPoint(0, 0);
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//contours���� hierarchy�㼶
	vector<Rect> boundRect(contours.size());
	vector<vector<Point>> conPoly(contours.size());
	string objectType;
	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl;//��ӡ��ÿ���Ĵ�С�����ݴ�Сѡ��
		if (area > 1000)//����
		{

			float peri = arcLength(contours[i], true);//����
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);//����αƽ�������ٶ�

			cout << conPoly[i].size() << endl;//��ĸ������ܷ�Ӧ����״������
			boundRect[i] = boundingRect(conPoly[i]);
			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);//2�Ǻ�� i��λ�øĳ�-1����ȫ��
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2);//�����̿�
			putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }, FONT_HERSHEY_COMPLEX, 0.75, Scalar(0, 255, 0), 2);
		}
	}
	return myPoint;
}
vector<vector<int>> findColor(Mat img)
{
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	for (int i = 0; i < myColors.size(); i++)
	{
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		Mat mask;
		inRange(imgHSV, lower, upper, mask);
		//imshow(to_string(i), mask);
		Point myPoint = getContours(mask);
		if (myPoint.x != 0 && myPoint.y != 0)
		{
			newPoints.push_back({ myPoint.x,myPoint.y,i });
		}
		
	}
	return newPoints;
}
void drawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> myColorValues)
{
	for (int i = 0; i < newPoints.size(); i++)
	{
		circle(img, Point(newPoints[i][0],newPoints[i][1]),10,myColorValues[newPoints[i][2]],FILLED);
	}

}
int main(int argc, char* argv[])
{
	//string path = "Resources/4.mp4";
	VideoCapture cap(0);//0������ͷ
	
	while (true)
	{
		cap.read(img);
		newPoints = findColor(img);
		drawOnCanvas(newPoints,myColorValues);
		imshow("Image", img);
		waitKey(1);
	}
	return 0;
}