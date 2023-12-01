#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
bool drawing_box;
Rect box;
int box_array_max_index = -1;
vector<Rect> box_array(100);
void my_mouse_callback(int event, int x, int y, int flags, void* param)
{
	//event：事件 x，y：鼠标在窗口坐标  param：其他东西
	Mat* image = (Mat*)param;
	switch (event)
	{
	case EVENT_LBUTTONDOWN:
	{
		drawing_box = true;
		box = Rect(x, y, 0, 0);
	}
	break;
	case EVENT_MOUSEMOVE:
		if (drawing_box)
		{
			box.width = x - box.x;
			box.height = y - box.y;
		}
	break;
	case EVENT_LBUTTONUP:
	{
		if (box.width < 0)
		{
			box.x += box.width;
			box.width *= -1;
		}
		if (box.height < 0)
		{
			box.y += box.height;
			box.height *= -1;
		}
		box_array_max_index++;
		box_array[box_array_max_index].x = box.x;
		box_array[box_array_max_index].y = box.y;
		box_array[box_array_max_index].width = box.width;
		box_array[box_array_max_index].height = box.height;
		drawing_box = false;
	}
	break;

	default:
		break;
	}
}

int detect(VideoCapture& capture)
{
	if (!capture.isOpened())
	{
		printf("打开视频或摄像头失败");
		return -1;
	}
	printf("点击鼠标左键拖拉形成一个四边形检测区域，最后点击右键形成检测区域开始检测\n");
	Mat currImage;
	capture >> currImage;
	namedWindow("画出检测区域");
	setMouseCallback(
		"画出检测区域",		//窗口名字
		my_mouse_callback,  //回调函数
		(void*)(&currImage) //传给回调函数的参数，背景图，这里面把第一张图片当做背景图
	);
	while (true)
	{
		Mat temp;
		currImage.copyTo(temp);
	}
}
int main()
{
	printf("视频文件测试输入（0），摄像头捕捉视频测试输入（1）：\n");
	int videType;
	scanf("%d", &videType);
	VideoCapture capture;
	if (videType == 0)
	{
		capture.open("car.avi");
	}
	else if (videType == 1)
	{
		int camera_id = 0;
		capture.open(camera_id);
	}
	int ret = detect(capture);

	return ret;
}