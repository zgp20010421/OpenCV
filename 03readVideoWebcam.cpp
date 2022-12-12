#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	// ���Ʊ�ɰ�ɫ����ɫ����
	system("color F9");
	
	// 1.��ȡ��Ƶ
	// ��Ƶ·��
	//string path = "Resources/test_video.mp4";

	// ��Ƶ��������
	//VideoCapture video(path);

	// ��������ͷ
	// �����Դ�����ͷ
	int index = 0;
	VideoCapture webCam(index);


	// �ж��Ƿ�ɹ���ȡ��Ƶ
	if (!webCam.isOpened())
	{
		cout << "·���������Ƶ�����ڣ�" << endl;
		return 1;
	}

	//// ��ӡ
	//cout << endl;
	//// CAP_PROP_FRAME_COUNT ��Ƶ����֡��
	//cout << "��Ƶ����֡��:" << video.get(CAP_PROP_FRAME_COUNT) << endl;
	//// CAP_PROP_FPS ��Ƶһ���Ӳ��ŵ�֡��
	//cout << "��Ƶһ���Ӳ��ŵ�֡��:" << video.get(CAP_PROP_FPS) << endl;
	//// CAP_PROP_FRAME_HEIGHT ��Ƶ�ĸ߶�
	//cout << "��Ƶ�ĸ߶�:" << video.get(CAP_PROP_FRAME_HEIGHT) << endl;
	//// CAP_PROP_FRAME_WIDTH ��Ƶ�Ŀ��
	//cout << "��Ƶ�Ŀ��:" << video.get(CAP_PROP_FRAME_WIDTH) << endl;
	//cout << endl;
	//// ������Ƶʱ��
	//// ��֡��/ÿһ���ӵ�֡��
	//cout << "��Ƶ����ʱ��:" << video.get(CAP_PROP_FRAME_COUNT) / video.get(CAP_PROP_FPS) << " s" << endl;
	//cout << endl;


	// ����һ����������
	Mat img;

	// ��whileѭ��ȥһ֡һ֡��һ��һ��ͼ�񣩵Ķ�ȡ��Ƶ
	while (true)
	{
		// ��ȡÿһ֡��img������д洢ÿһ֡
		webCam.read(img);

		// ͼ��ת���� 
		//flip(����ͼ�����ͼ��1�����ҷ�ת/-1�����·�ת)
		int code = 1;
		flip(img, img, code);

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
	webCam.release();
	return 0; 
}