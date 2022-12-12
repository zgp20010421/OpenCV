#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{

	string path = "Resources/ml.png";
	Mat img = imread(path);
	Mat imgRGB, imgYUV, imgHSV, imgLab, imgGRAY;

	cvtColor(img, imgRGB, COLOR_BGR2RGB);

	// YUVģ���ǵ����ź�ϵͳ�����õĵ���ɫ���뷽ʽ��
	// Y:��ʾ����	U����ʾ��ɫ�����ȵĲ�ֵ V����ʾ��ɫ�����ȵĲ�ֵ
	cvtColor(img, imgYUV, COLOR_BGR2YUV);

	/*
	HSV��ɫ�ȣ�Hua�������Ͷȣ�Saturation�������ȣ�Value��
	*/

	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	/*
	Lab��ɫģ�;��ǲ���RGBģ�͵Ĳ��㣬��һ���豸�޹ص���ɫģ��
	L��ʾ����  a��b��ͨ��ֵ
	*/

	cvtColor(img, imgLab, COLOR_BGR2Lab);

	/*
		�Ҷ�ͼ��
	*/

	cvtColor(img, imgGRAY, COLOR_BGR2GRAY);

	imshow("img", img);
	imshow("imgRGB", imgRGB);
	imshow("imgYUV", imgYUV);
	imshow("imgHSV", imgHSV);
	imshow("imgLab", imgLab);
	imshow("imgGRAY", imgGRAY);



	waitKey(0);
	destroyAllWindows();

	return 0;
}