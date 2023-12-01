#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int hmin = 0, smin = 0, vmin = 23;
int hmax = 255, smax = 255, vmax = 33;
Mat imgHSV, mask;
Mat imgGray, imgBlur, imgCanny, imgDil, imgCrop, imgCanny2, imgDil2;
class bottle
{
private:
	Mat img;
	float body_length;
	float body_width;
	float mouth_length;
	float mouth_width;
public:
	bottle(Mat i, float a, float b, float c, float d);
	float get_bodylen();
	float get_bodywid();
	float get_mouthlen();
	float get_mouthwid();
};
bottle::bottle(Mat i, float a, float b, float c, float d) : img(i), body_length(a), body_width(b), mouth_length(c), mouth_width(d)
{

}
float bottle::get_bodylen()
{
	float bodylen = this->body_length;
	return bodylen;
}
float bottle::get_bodywid()
{
	float bodywid = this->body_width;
	return bodywid;
}
float bottle::get_mouthlen()
{
	float mouthlen = this->mouth_length;
	return mouthlen;
}
float bottle::get_mouthwid()
{
	float mouthwid = this->mouth_width;
	return mouthwid;
}

void getContours(Mat imgDil, Mat img)
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//contours轮廓 hierarchy层级
	vector<Rect> boundRect(contours.size());
	vector<vector<Point>> conPoly(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		//cout << area << endl;//打印出每个的大小，根据大小选择
		if (area > 8000)//降噪
		{

			float peri = arcLength(contours[i], true);//弧长
			//approxPolyDP(contours[i], conPoly[i], 0.01 * peri, false);//多边形逼近
			boundRect[i] = boundingRect(contours[i]);
			//drawContours(img, contours, -1, Scalar(255, 0, 255), 1);//2是厚度 i的位置改成-1代表全部
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2);//画出绿框
			float body_len = boundRect[i].width;
			float body_wid = boundRect[i].height;
			putText(img,"bodylenth: " + to_string(body_len), {boundRect[i].x,boundRect[i].y + 25}, FONT_HERSHEY_COMPLEX, 0.75, Scalar(0, 255, 0), 2);
			putText(img, "bodywidth: " + to_string(body_wid), {boundRect[i].x,boundRect[i].y + 50}, FONT_HERSHEY_COMPLEX, 0.75, Scalar(0, 255, 0), 2);
		}
	}
}
void getContours2(Mat imgDil, Mat img)
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//contours轮廓 hierarchy层级
	vector<Rect> boundRect(contours.size());
	vector<vector<Point>> conPoly(contours.size());
	float Xmouth_wid = 0;
	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl;//打印出每个的大小，根据大小选择
		if (area > 1000)//降噪
		{

			float peri = arcLength(contours[i], true);//弧长
			//approxPolyDP(contours[i], conPoly[i], 0.01 * peri, false);//多边形逼近
			boundRect[i] = boundingRect(contours[i]);
			//drawContours(img, contours, i, Scalar(255, 0, 255), 1);//2是厚度 i的位置改成-1代表全部
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2);//画出绿框
			Xmouth_wid = boundRect[i].width;
		}
		else if (area > 500 && area<1000)//降噪
		{

			float peri = arcLength(contours[i], true);//弧长
			//approxPolyDP(contours[i], conPoly[i], 0.01 * peri, false);//多边形逼近
			boundRect[i] = boundingRect(contours[i]);
			//drawContours(img, contours, i, Scalar(255, 0, 255), 1);//2是厚度 i的位置改成-1代表全部
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2);//画出绿框
			float mouth_wid = boundRect[i].width - Xmouth_wid;
			float mouth_len = boundRect[i].height;
			putText(img, "wid" + to_string(mouth_wid), { boundRect[i].x ,boundRect[i].y + 20 }, FONT_HERSHEY_COMPLEX, 0.75, Scalar(0, 255, 0), 2);
			putText(img, "len" + to_string(mouth_len), { boundRect[i].x ,boundRect[i].y + 45 }, FONT_HERSHEY_COMPLEX, 0.75, Scalar(0, 255, 0), 2);
		}
	}
}
int main()
{
	string path = "Resources/OK.bmp";
	Mat img = imread(path);
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	Scalar lower(hmin, smin, vmin);//色度 饱和度 亮度 HSV模型
	Scalar upper(hmax, smax, vmax);
	inRange(imgHSV, lower, upper, mask);
	
	Canny(mask, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
	Rect roi(1089, 18, 200, 300);
	imgCrop = img(roi);//裁剪，上面是参数,把瓶口裁出来
	GaussianBlur(imgCrop, imgBlur, Size(3, 3), 5, 5);
	Canny(imgBlur, imgCanny2, 25, 75);
	dilate(imgCanny2, imgDil2, kernel);
	getContours(imgDil, img);
	getContours2(imgDil2, imgCrop);
	imshow("Image", img);
	waitKey(0);
	return 0;
}
