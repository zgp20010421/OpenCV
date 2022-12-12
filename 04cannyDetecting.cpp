#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	system("color F9");
	string path = "Resources/lena.jpg";
	
	Mat img;

	img = imread(path);
	
	// 1.����ɫ��ͼ���Ϊ��ɫͼ��(0,255)
	Mat imgGray;
	// cvtColor(����ͼ�����ͼ�񣬸ı��ʲô��ɫ)
	cvtColor(img, imgGray, COLOR_BGR2GRAY);

	// 2.����ɫͼ����и�˹ģ��,��˹�˲���
	Mat imgBlur;
	Size size(3, 3);
	// GaussianBlur������ͼ�����ͼ�񣬸�˹ģ���Ĵ�С����������
	GaussianBlur(imgGray, imgBlur, size, 3, 0);

	// 3.����˹ģ����ͼ�����canny��Ե���
	Mat imgCanny;
	// Canny(����ͼ�񣨻�ɫͼ�񣬵�ͨ����ͼ�񣩣����ͼ��ȡֵ:0--255)
	// �ҵ�ͼ��ı�Ե�������˵�����Ҫ�ı���
	Canny(imgBlur, imgCanny, 75, 125);

	// 4.��canny��Ե�����ͼ���������
	// matrix ����
	Mat imgDilate;
	
	// kerner �ں�
	// size(3,3)����5��5����ֻ��������
	// getStructuringElement���������ͣ�����˵Ĵ�С��
	Mat kerner = getStructuringElement(MORPH_RECT, size);

	// dilate������ͼ��Canny��,���ͼ���ںˣ�
	dilate(imgCanny, imgDilate, kerner);

	// 5.���и�ʴ erode
	Mat imgErode;
	// erode(����ͼ�����ͼ���ں˴�С)
	erode(imgDilate, imgErode, kerner);

	// ͼ���ض����С

	//resize(img,img,Size(0,0),0.5,0.5);
	/*int width = int(img.rows / 2); // ͼ��Ŀ�
	int height = int(img.cols / 2); // ͼ��ĸ�
	resize(img, img, Size(width, height));*/

	// reszie(����ͼ�����ͼ��ͼ���С����͸ߣ������ߣ�
	resize(img, img, Size(0, 0), 0.5, 0.5);
	resize(imgGray, imgGray, Size(0, 0), 0.5, 0.5);
	resize(imgBlur, imgBlur, Size(0, 0), 0.5, 0.5);
	resize(imgCanny, imgCanny, Size(0, 0), 0.5, 0.5);
	resize(imgDilate, imgDilate, Size(0, 0), 0.5, 0.5);
	resize(imgErode, imgErode, Size(0, 0), 0.5, 0.5);

	imshow("img", img);
	imshow("imgGray", imgGray);
	imshow("imgBlur", imgBlur);
	imshow("imgCanny", imgCanny);
	imshow("imgDilate", imgDilate);
	imshow("imgErode", imgErode);

	waitKey(0);
	destroyAllWindows();

	return 0;
}