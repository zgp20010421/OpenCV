#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	// ��ȡappleͼ��
	string apple_P = "Resources/apple.jpg";
	string orange_P = "Resources/orange.jpg";
	Mat apple = imread(apple_P);
	Mat orange = imread(orange_P);

	if (apple.empty() || orange.empty())
	{
		cout << "ͼ�񲻴��ڻ�·������" << endl;
		return -1;
	}

	// �ں�ͼ��
	// ͼ��Ĵ�СҪ��ͬ����������ȣ�
	int apple_w = apple.rows; //��
	int apple_h = apple.cols;//��

	// ��orangeͼ����Ϊ��appleͼ����ͬ
	resize(orange, orange, Size(apple_w, apple_h));
	
	// ��ӡapple��orangeͼ��Ĵ�С
	cout << endl;
	cout << apple.size()<< endl;
	cout << orange.size() << endl;

	// �ں�ͼ��
	Mat imgBit;
	//bitwise_and(�ں�ͼ��1, �ں�ͼ��2, �ںϺ��ͼ�� mask����);
	bitwise_and(apple,orange,imgBit);

	// mask
	Mat mask = Mat(512, 512, CV_8UC1, Scalar(0, 0, 0));

	// Rect ������������ rect��������x,y,width,height��
	Rect rect(150, 150, 200, 200);

	// Scalar() ��ɫ����
	// ������ѡ����ε����������ɫ��ֵ
	mask(rect) = Scalar(255, 255, 255); // ��ɫ
	
	Mat imgMask;
	bitwise_and(apple, orange, imgMask, mask);

	// 1.��Ҫָ����������
	// 2.��ȡͼ���еľ�������
	Mat imgRoi = imgBit(rect);

	imshow("apple", apple);
	imshow("orange", orange);
	imshow("imgBit", imgBit);
	imshow("mask", mask);
	imshow("imgMask", imgMask);
	imshow("imgRoi", imgRoi);

	// ����
	string imgname = "Roi.jpg";
	//imwrite(imgname, ����ͼ��);
	imwrite(imgname, imgRoi);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
