#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
Mat imgOri, imgGray, imgCanny, imgThre, imgBlur, imgDil;
vector<Point> initPoint, docPoints;
Mat preProcessing(Mat img)
{
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur, Size(7, 7), 5, 0);
	Canny(imgBlur, imgCanny, 50, 150);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
	dilate(imgCanny, imgDil, kernel);
	//erode(imgDil, imgErode, kernel);
	return imgDil;
}
vector<Point> getContours(Mat imgDil)
{
	vector<vector<Point>> contours;//vector<vector<Point>>是一个类型，向量里有一个向量，这个向量里是一个点
	vector<Vec4i> hierarchy;
	
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//contours轮廓 hierarchy层级
	vector<Rect> boundRect(contours.size());
	vector<vector<Point>> conPoly(contours.size());
	vector<Point> biggest;
	int maxArea = 1000;
	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl;//打印出每个的大小，根据大小选择
		if (area > 1000)//降噪
		{

			float peri = arcLength(contours[i], true);//弧长
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);//多边形逼近，具体百度
			if (area > maxArea && conPoly[i].size()==4 )
			{
				biggest = { conPoly[i][0],conPoly[i][1],conPoly[i][2],conPoly[i][3] };
				maxArea = area;
			}
			drawContours(imgOri, conPoly, i, Scalar(255, 0, 255), 2);//2是厚度 i的位置改成-1代表全部
			
		}
	}
	return biggest;
}
void drawPoints(vector<Point> points, Scalar color)
{
	for (int i = 0; i < points.size(); i++)
	{
		circle(imgOri, points[i], 10, color, FILLED);
		putText(imgOri, to_string(i), points[i], FONT_HERSHEY_PLAIN, 2, color, 2);
	}
	
}
vector<Point> reorder(vector<Point> points)
{
	vector<Point> newPoints;
	vector<int> sumPoints, subPoints;
	for (int i = 0; i < 4; i++)
	{
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);

	}
	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);//0
	newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);//1
	newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);//2
	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);//3
	return newPoints;
}
int main(int argc, char* argv[])
{
	string path = "Resources/10.png";
	Mat imgOri = imread(path);
	//resize(imgOri, imgOri, Size(), 0.2, 0.2);
	imgThre = preProcessing(imgOri);
	initPoint = getContours(imgThre);
	drawPoints(initPoint, Scalar(255, 0, 0));
	//docPoints = reorder(initPoint);
	//drawPoints(docPoints, Scalar(255, 0, 255));
	imshow("Image", imgOri);
	
	waitKey(0);
	return 0;
}
