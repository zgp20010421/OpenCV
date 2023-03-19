#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include <vector>

using namespace std;
using namespace cv;



////////////// Project 2 Document Scanner  ///////////////

Mat imgOriginal, imgGray, imgCanny, imgThre, imgBlur, imgDil, imgErode, imgWrap, imgCrop;
vector<Point> initialPoints, docPoints;

// ���� A4 ֽ���
float w = 360, h = 580;

Mat Preprocessing(Mat img)
{
	cvtColor(img, imgGray, COLOR_BGR2GRAY);

	//��˹ģ��
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	//Canny��Ե�����
	Canny(imgBlur, imgCanny, 25, 75);
	// only use odd (3,3) or (5,5)
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	//����
	dilate(imgCanny, imgDil, kernel);
	//��ʴ
	/*erode(imgDil, imgErode, kernel);*/

	return imgDil;
}

vector<Point> getContours(Mat image)
{

	// ��ά�����б�
	vector<vector<Point>> contours;
	// 4��int��������
	vector<Vec4i> hierarchy;

	findContours(image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	// ������Ϻ��������
	vector<vector<Point>> conPloy (contours.size());

	vector<Rect>boundRect(contours.size());
	// ���ص�����
	vector<Point> biggest;
	// ������
	int maxArea = 0;

	for (int i = 0; i < contours.size(); i++)
	{
		int Area = contourArea(contours[i]);
		// cout << Area << endl;
		if (Area > 1000)
		{
			// ��ȡ��������,�պ�״̬
			float peri = arcLength(contours[i], true);

			// �����⻬������϶����������
			approxPolyDP(contours[i], conPloy[i], 0.02 * peri, true);
			// cout << conPloy[i] << endl;

			if (Area > maxArea && conPloy[i].size() == 4)
			{
				// ��������
				//drawContours(imgOriginal, conPloy, i, Scalar(255, 0, 255), 5, LINE_AA);
				// ����������Ƿ�Ϊ�������
				biggest = { conPloy[i][0], conPloy[i][1] ,conPloy[i][2] ,conPloy[i][3] };
				maxArea = Area;
			}

			//// ��������
			//drawContours(imgOriginal, conPloy, i, Scalar(255, 255, 20), 2, LINE_AA);
		}
	}
	return biggest;
}

// 
void drawPoints(vector<Point>points, Scalar color)
{
	for (int i = 0; i < points.size(); i++)
	{
		circle(imgOriginal, points[i], 10, color, FILLED);
		// ��ʾ��ĸ���
		putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 4, color, 4);
	}
}

// ���������
vector<Point> reorder(vector<Point> points)
{
	/*
		
		(35,45)  80
		(40,60)  100
		(350,400)  750
		(310,200)  510
		
		{80,100,750,510}}
	*/
	vector<Point> newPoints;
	vector<int> sumPoints, subPoints;
	for (int i = 0; i < points.size(); i++)
	{
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);
	}

	// ���sumPoint��������Сֵ������ֵ ��index��
	// min_element(sumPoint.begin(), sumPoint.end()) - sumPoint.begin()

	// ���sumPoint��������Сֵ
	// *min_element(sumPoint.begin(), sumPoint.end())

	//min_element() �������㷨ͷ�Ŀ⺯����
	//���ڴӷ�Χ��Ѱ����С��Ԫ�أ�������һ��������Χ[��ʼ������]��
	//������һ��ָ�������Χ�ھ�����Сֵ��Ԫ�صĵ�������


	// ��ȡ�������
	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);	//0
	newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);	//1
	newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);	//2
	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);	//3

	return newPoints;
}

Mat getWrap(Mat image, vector<Point>points, float w, float h)
{
	Point2f src[4] = {points[0],points[1], points[2], points[3]};
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	Mat matrix = getPerspectiveTransform(src, dst);
	warpPerspective(imgOriginal, imgWrap, matrix, Point(w,h));

	return imgWrap;
}


int main()
{
	system("color F9");
	string path = "Resources/paper.jpg";
	imgOriginal = imread(path);
	
	// ��С
	 resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);
	// �ҳ����Ե�����Ǿ�֪��ֽ�����ģ�������ֽ�ŵ�����
	// ��ȡ�ĸ�����ĸ���


	//	1.	Preprocessing  ͼ��Ԥ���� ���Ҷȣ���˹���ˣ���Ե���ң�
	imgThre = Preprocessing(imgOriginal);
	//	2.	Get contours - Biggest ����������A4ֽ������ͼ�������ľ���
	initialPoints = getContours(imgThre);
	drawPoints(initialPoints,Scalar(0,255,20));
	// ��Ҫ����һ���º������жԵ������
	docPoints = reorder(initialPoints);
	//drawPoints(docPoints, Scalar(255, 255, 20));
	//	3.	Wrap image ͸�ӱ任
	imgWrap = getWrap(imgOriginal,docPoints,w,h);

	// Crop
	int cropValue = 5;
	Rect roi(cropValue,cropValue,w - (2 * cropValue),h - (2 * cropValue));
	imgCrop = imgWrap(roi);

	imshow("image", imgOriginal);
	//imshow("image Dil", imgThre);
	//namedWindow("image Dil", WINDOW_FREERATIO);
	imshow("image warp", imgWrap);
	imshow("image Crop", imgCrop);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
