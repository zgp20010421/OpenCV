#include <opencv2\opencv.hpp>
#include <iostream>


using namespace std;
using namespace cv;

// ��HSV��ɫ�ռ������ɫ���
/*
	Hue:��ɫ�ı��Ͷ�
	Saturation: ��ɫ������ 
	Value: ��ɫ��ֵ

	��Ҫ����������ʵʱ�ı��HSV��ֵ��Ѱ��������Ҫ����ɫ
	����Ҳ����ͨ����ɫ�ļ�������������⣬����:���ּ��
	HSV��ɫ�ռ���ڼ������˵�����׽��и�֪��ɫ
*/


// ��HSV��ɫֵ���и���

// ����HSV����ɫ�����ֵ����Сֵ
int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;


int main()
{
	system("color F9");
	String path = "Resources/shapes.png";
	Mat img = imread(path);
	if (img.empty())
	{
		cout << "image not opened !" << endl;
		return -1;
	}

	// ��ͼ��ת��Ϊ HSVͼ��
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	
	// �������ǵ�׷����
	namedWindow("TrackBar", WINDOW_AUTOSIZE); // ����һ������������
	// createTrackbar("������������", "��������", ��ʼֵ, �������ķ�Χ);
	createTrackbar("hmin", "TrackBar", &hmin, 179);
	createTrackbar("hmax", "TrackBar", &hmax, 179);
	createTrackbar("smin", "TrackBar", &smin, 255);
	createTrackbar("smax", "TrackBar", &smax, 255);
	createTrackbar("vmin", "TrackBar", &vmin, 255);
	createTrackbar("vmax", "TrackBar", &vmax, 255);

	imshow("img", img);
	imshow("imgHSV", imgHSV);

	while (true)
	{
		// ����HSV��ɫֵ��������
		// ����
		Scalar lower(hmin, smin, vmin);
		// ����
		Scalar upper(hmax, smax, vmax);

		// ͬ�����޵ķ�Χ�ҵ� mask(��Ĥ����ɫ)����ɫ������������ҵ���ɫ����
		Mat mask;
		//inRange(HSVͼ��, HSV��ɫֵ������, HSV��ɫֵ������, mask���ڵ�������Ϊ�������򣬰�ɫ��);
		inRange(imgHSV, lower, upper, mask);

		imshow("mask", mask);
		cout << hmin << "," << smin << "," << vmin << "," << hmax << "," << smax << "," << vmax << endl;
		int c = waitKey(10);
		// ��ESC�˳�
		if (c == 27)
		{
			break;
		}
	}

	destroyAllWindows();

	return 0;
}