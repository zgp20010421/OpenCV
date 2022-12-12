#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	// ��������ɫ��������ɫ
	system("color F9");


	// Mat���� ��matrix ����
	// 1.(�У��У�type:CV_8UC1 /8���ֽڣ�U��uchar��
	// C��channelͨ����  1��ͨ����Ϊ1)
	Mat a(512, 512, CV_8UC1);
	//cout << a << endl;

	// 2.Mat���͵Ķ���,CV_8UC1
	Mat b = (Mat_<int>(3,3)<< 1,2,3,4,5,6,7,8,9);
	cout << b << endl;
	Mat c = (Mat_<int>(3, 3) << 1, 0, 0, 0, 1, 0, 0, 0, 1);
	
	// �������
	Mat sum = b + c;
	Mat mut = c * 2;

	//��ӡ cout ���
	cout << sum << endl;
	cout << mut << endl;

	// 3.����ȫ1��ȫ0�ľ���
	Mat ones = Mat::ones(Size(512, 512), CV_8UC3);
	Mat zeros = Mat::zeros(Size(512, 512), CV_8UC3);
	// show ,ֻ����ʾ���Ϊ4ͨ����ͼ��
	// ����������ڴ���,д��imshow�������ǰ��

	namedWindow("ones", WINDOW_FREERATIO);
	namedWindow("zeros", WINDOW_FREERATIO);
	imshow("ones", ones);
	imshow("zeros", zeros);
	


	imshow("a", a);
	// ͣ���ڵ�ǰһ֡
	waitKey(0);
	destroyAllWindows();

	return 0;
}