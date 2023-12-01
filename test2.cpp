#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main(int argc, char* argv[])
{
	string path = "Resources/5.jpg";
	Mat img = imread(path);
	Mat imgGray, imgBlur,imgCanny,imgDil,imgErode;
	cvtColor(img,imgGray,COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur,Size(7,7),5,0);
	Canny(imgBlur, imgCanny, 50, 150);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
	dilate(imgCanny, imgDil, kernel);
	erode(imgDil, imgErode, kernel);
	imshow("Image", img);
	imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dilation", imgDil);//dilation ≈Ú’Õ
	imshow("Image Erode", imgErode);//Erode ∑ÁªØ
	waitKey(0);
	

}