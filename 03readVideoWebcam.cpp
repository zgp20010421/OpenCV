#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	system("color F9");
	
	// 1.��ȡ��Ƶ
	// ��Ƶ·��
	string path = "Resources/test_video.mp4";

	VideoCapture video(path);
	// �ж��Ƿ�ɹ���ȡ��Ƶ
	if (!video.isOpened())
	{
		cout << "·���������Ƶ�����ڣ�" << endl;
		return 1;
	}
	Mat img;
	// ��whileѭ��ȥһ֡һ֡��һ��һ��ͼ�񣩵Ķ�ȡ��Ƶ
	while (true)
	{
		// ��ȡÿһ֡��img������д洢ÿһ֡
		video.read(img);


		imshow("video", img);
		int c = waitKey(30);
		// 27������Ǽ�����ESC
		if (c == 27)
		{
			break;
		}
	}

	destroyAllWindows();
	// �ͷ���Ƶ��ȡ��Դ
	video.release();
	return 0; 
}