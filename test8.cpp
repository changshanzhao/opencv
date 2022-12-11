#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
Mat imgGray, imgBlur, imgCanny, imgDil;
void getContours(Mat imgDil,Mat img)
{
	vector<vector<Point>> contours;//vector<vector<Point>>是一个类型，向量里有一个向量，这个向量里是一个点
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//contours轮廓 hierarchy层级
	vector<Rect> boundRect(contours.size());
	vector<vector<Point>> conPoly(contours.size());
	string objectType;
	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl;//打印出每个的大小，根据大小选择
		if (area > 1000)//降噪
		{
			
			float peri = arcLength(contours[i], true);//弧长
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, false);//多边形逼近，具体百度
			
			cout<<conPoly[i].size()<<endl;//点的个数可能反应了形状的类型
			boundRect[i] = boundingRect(conPoly[i]);
			
			int objCor = (int)conPoly[i].size();
			if (objCor == 3) { objectType = "Tri"; }
			else if (objCor == 4) 
			{ 
				float aspRatio =(float) boundRect[i].width / (float) boundRect[i].height;
				if (aspRatio > 0.95 && aspRatio < 1.05)
				{
					objectType = "Square";
				}
				else
				{
					objectType = "Rect";
				}
				
			}
			else if (objCor > 4) { objectType = "Circle"; }
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);//2是厚度 i的位置改成-1代表全部
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2);//画出绿框
			putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }, FONT_HERSHEY_COMPLEX, 0.75, Scalar(0, 255, 0), 2);
		}
	}
}
int main(int argc, char* argv[])
{
	string path = "Resources/OK.bmp";
	Mat img = imread(path);
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
	getContours(imgDil, img);
	imshow("Image", img);
	waitKey(0);
	return 0;
}