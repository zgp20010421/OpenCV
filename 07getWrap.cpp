#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	system("color F9");
	String path = "Resources/cards.jpg"; 
	Mat img = imread(path);
	if (img.empty())
	{
		cout <<"image not opened !" << endl;
		return -1;
	}

	// ����͸�ӱ任��ͼ��ĳ��Ϳ�(float)
	float width = 360 ,height = 540;

	// �ҵ�K��Ƭ���ĸ��ǵ㣨����㣩
	// ���ϣ����ϣ����£�����
	Point2f srcK[4] = { {528,145},{769,190},{406,392},{675,455} };

	// ͸�ӱ任��ͼ����ĸ��ǵ㣨����㣩
	Point2f dstK[4] = { {0.0f,0.0f},{width,0.0f},{0.0f,height},{width,height} };

	// �ҵ�͸�ӱ任��ת������
	// getPerspectiveTransform(K��Ƭ���ĸ��ǵ�, ͸�ӱ任��ͼ����ĸ��ǵ�);
	Mat matrixK = getPerspectiveTransform(srcK, dstK);

	cout << matrixK << endl;

	// ��Ť���任�õ��任���ͼ��
	Mat imgWrap;
	warpPerspective(img, imgWrap, matrixK, Size(width, height));

	// ��Сһ��
	resize(img, img, Size(), 0.5, 0.5);
	imshow("img", img);
	imshow("imgWarp", imgWrap);


	waitKey(0);
	destroyAllWindows();

	return 0;
}