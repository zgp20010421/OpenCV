#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	// ���廭��
	Mat painter = Mat(512, 512, CV_8UC3, Scalar(255, 255, 255));

	// opencv BGR 
	// blue
	Mat painter_blue = Mat(512, 512, CV_8UC3, Scalar(255, 0, 0));
	// green
	Mat painter_green = Mat(512, 512, CV_8UC3, Scalar(0, 255, 0));
	// red
	Mat painter_red = Mat(512, 512, CV_8UC3, Scalar(0, 0, 255));

	// ����Բ
	//circle(����ͼ��, ���ĵ㣺Point(256, 256), �뾶��
	// 160, Scalar(255, 0, 255), �ߵĺ�ȣ�5, ��ƽ����LINE_AA);
	/*circle(painter, Point(256, 256), 160, Scalar(255, 0, 255), 5, LINE_AA);*/
	circle(painter, Point(256, 256), 160, Scalar(255, 0, 255), -1, LINE_AA);

	// ����
	// rectangle(input, ���ε�����Rect(206, 206, 100, 100), Scalar(255, 90, 100), 5, LINE_AA);
	rectangle(painter, Rect(206, 206, 100, 100), Scalar(255, 90, 100), 5, LINE_AA);

	// ����
	//line(painter, ��ߵĵ㣺Point(100, 350), �ұߵĵ㣺Point(412, 350), Scalar(125, 250, 110), 5, LINE_AA);
	line(painter, Point(100, 350), Point(412, 350), Scalar(125, 250, 110), 5, LINE_AA);

	// �ı�
	/*putText(���룺painter, �ı���"OpenCV", λ�ã�Point(50, 50),
		�������ʽ��FONT_HERSHEY_SCRIPT_SIMPLEX, ����Ĵ�С��2, Scalar(125, 200, 255), 4, LINE_AA);*/
	/*putText(painter, "OpenCV", Point(50, 50),
		FONT_HERSHEY_SCRIPT_SIMPLEX, 2, Scalar(125, 200, 255), 4, LINE_AA);*/

	putText(painter, "OpenCV", Point(50, 50),
		FONT_HERSHEY_COMPLEX, 2, Scalar(125, 200, 255), 4, LINE_AA);


	imshow("painter", painter);
	imshow("painter_blue", painter_blue);
	imshow("painter_green", painter_green);
	imshow("painter_red", painter_red);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
