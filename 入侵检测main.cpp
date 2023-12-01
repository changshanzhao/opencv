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
	//event���¼� x��y������ڴ�������  param����������
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
		printf("����Ƶ������ͷʧ��");
		return -1;
	}
	printf("��������������γ�һ���ı��μ������������Ҽ��γɼ������ʼ���\n");
	Mat currImage;
	capture >> currImage;
	namedWindow("�����������");
	setMouseCallback(
		"�����������",		//��������
		my_mouse_callback,  //�ص�����
		(void*)(&currImage) //�����ص������Ĳ���������ͼ��������ѵ�һ��ͼƬ��������ͼ
	);
	while (true)
	{
		Mat temp;
		currImage.copyTo(temp);
	}
}
int main()
{
	printf("��Ƶ�ļ��������루0��������ͷ��׽��Ƶ�������루1����\n");
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