#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

void getContours(Mat imgOriginal, Mat imgDilate)
{
	// ���������洢contours
	// {{{56��23},{52��22},{32��36}}}
	vector<vector<Point>> contours;

	// ���������洢 hierarchy���ȼ��ƶȣ������������ȼ�
	// {{1,2,3,4},{5,6,7,8}}
	vector<Vec4i> hierarchy;

	// ��������
	//findContours(����ͼ�񣨶�ֵ��ͼ��, ����, ���������ȼ�, ���������ļ���ģʽ, ���������Ľ��Ʒ�ʽ);
	findContours(imgDilate, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	// ��������
	// drawContours(����ͼ��, ����, -1���������е�����, Scalar(255, 0, 0), 2, LINE_AA);
	/*drawContours(imgOriginal, contours, -1, Scalar(255, 0, 0), 2, LINE_AA);*/

	// ���������洢����εĽǵ���Ϣ
	// �����ĳ�ʼ������contours��������һ����
	vector<vector<Point>> conPoly(contours.size());

	// ���������洢�߽����
	vector<Rect> boundRect(contours.size());

	cout << contours.size() << endl;

	// ��������
	string obj_name;

	// ����ÿ��������Ϣ����ͼ�ε���� 
	for (int i = 0; i < contours.size(); i++)
	{
		// ����ͼ�ε����
		int Area = contourArea(contours[i]);
		cout << "Area " << i << ":" << Area << endl;
		if (Area > 1000)
		{
			// �������εĻ���
			float peri = arcLength(contours[i], true);
			float epsilon = peri * 0.02;

			// ��϶���εĽǵ�
			approxPolyDP(contours[i],conPoly[i],epsilon,true);

			// ��ÿ��ͼ��Ľǵ���Ƴ���
			drawContours(imgOriginal, conPoly, i, Scalar(255, 45, 100), 2, LINE_AA);

			// ���ǵ���Ϣת��Ϊ����
			boundRect[i] = boundingRect(conPoly[i]);

			// �ǵ���
			int objCor = (int)conPoly[i].size();
			// ������
			if (objCor == 3)
			{
				obj_name = "Triangle";
			}
			// ����
			else if (objCor == 4)
			{
				float apsRatio = boundRect[i].width / boundRect[i].height;
				if (apsRatio > 0.98 && apsRatio < 1.02)
				{
					obj_name = "square";
				}
				else
				{
					obj_name = "rectangle";
				}
			}
			else if (objCor > 4)
			{
				obj_name = "circle";
			}

			Point point(boundRect[i].x-5, boundRect[i].y+5);
			putText(imgOriginal, obj_name, point, 
				FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 20), 1, LINE_AA);

			// ���߽���λ��Ƴ���
			/*rectangle(imgOriginal, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 0, 200), 3, LINE_AA);*/
			imshow("imgOriginal", imgOriginal);
		}
	}
}


int main()
{
	system("color F9");
	string path = "Resources/shapes.png";
	Mat imgShapes = imread(path);
	Mat imgOriginal = imgShapes.clone();
	if (imgShapes.empty())
	{
		printf("img not opened !");
		return -1;
	}

	imshow("imgShapes", imgShapes);

	// һ��ͼ���Ԥ������ͼ���� Cannyͼ�񣬵õ���Ե����ͼ��
	Mat imgGray,imgBlur, imgCanny, imgDilate;
	// 1.����ɫͼ���Ϊ��ɫͼ��
	cvtColor(imgShapes, imgGray, COLOR_BGR2GRAY);
	// 2.��ɫͼ����и�˹ģ��ȥ��
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	// 3.����Canny��Ե���,����ͼ��ֻ��Ϊ��ɫͼ��
	Canny(imgBlur, imgCanny, 75, 125);
	// 4.����Ե������Ϣ�������󣬶�ֵ��ͼ������
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDilate, kernel);

	// ��������������Ϣ
	getContours(imgOriginal, imgDilate);

	/*imshow("imgGray", imgGray);
	imshow("imgBlur", imgBlur);
	imshow("imgCanny", imgCanny);
	imshow("imgDilate", imgDilate);*/

	waitKey(0);
	destroyAllWindows();

	return 0;
}