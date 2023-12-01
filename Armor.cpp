#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main(int argc, char* argv[])
{
	string path = "Resources/3.mp4";
	VideoCapture cap(path);
	Mat frame;
	while (true)
	{
		cap >> frame;
		if (frame.empty())
		{
			break;
		}
		imshow("video", frame);
		waitKey(1000 / cap.get(CAP_PROP_FPS));
	}
	return 0;
}