#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

///////////////  Project 1   virtual painter //////////////////////

/*
����ʹ��HSV�ռ�����ɫ��������ɫ
�������ҵ��������ڵ�����
�ҵ�����������ȡ X �� Y������Щλ�ã����ǽ�����һ��ԲȦ
����һ���ϣ����ȱ����ҵ���ɫ

���ǽ��ж��mask������������ڼ�� green and purple 
���ǽ���green mask and purple mask

*/

// ����������������������ɫ���������������ɫ������⵽2.
// һ������������һ����ɫ,ʹ����ɫѡ������������ɫ
// �����ɫ
// hmin,smin,vmin,hmax,smax,vmax
vector<vector<int>> myColors{
	{141, 62, 175, 179, 255, 247},	//pink
	{97, 120, 74, 114, 234, 221}	//blue
};

//������ɫ��������Ҫ��ʾ����ɫ
vector<Scalar> myColorValues{
	{255,0,255},	//pink
	{255,255,50}	//blue
};

Mat img;
// { {x�����꣬y�����꣬0 ��ʾmyClolor�еĵ�һ����ɫ}��{x,y,1}}
vector<vector<int>> newPoints;


Point getContours(Mat imgDil)
{
	// contours is a vector����������һ���б�
	vector<vector<Point>> contours;
	// û�нṹ��4��int����
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 255, 20), 2, LINE_AA);

	// ������Ϻ�Ķ��������
	vector<vector<Point>> conPoly(contours.size());
	// �洢Χ�����ı߽���������
	vector<Rect> boundRect(contours.size());

	// ����Point
	Point myPoint;

	// ������������Ҫ���ù������������������һ���ķ�Χ��
	// loop all shapes area of contours 
	for (int i = 0; i < contours.size(); i++)
	{

		int area = contourArea(contours[i]);
		cout << area << endl;
		if (area > 1000)
		{
			// �ҵ�������ˣ��ҵ�������write here patty and ����
			// ʹ�������ҵ�������
			// �ҵ��ǵ�����ξ��е���������
			// ������ξ����ĸ����߻��ĸ��ǵ㣬��Ϊ���Σ�������������
			// ����4���ǵ㣬circle

			// ��ȡ���߻���������Ϊ�պ�״̬��float��
			float peri = arcLength(contours[i], true);

			// ��һ�������⻬�������߻�����ͼ����������ж�������
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			cout << conPoly[i].size() << endl;

			// �ҵ���Χ�ı߽�����������ֻ��Ҫһ�����ӣ����ǿ����ҵ�
			// �õ��߽����ֻ�贫�����ǵĶ��������
			// �������ǵõ��ǵ����Ľ���ֵ,���ǽ��䴫�ݽ�������������һ���߿�
			// ���߸�������Χ�����ı߽���������
			boundRect[i] = boundingRect(conPoly[i]);

			// �Ӷ����м�λ�û滭
			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;

			// ������Ϻ�Ķ��������
			drawContours(img, conPoly, i, Scalar(255, 255, 20), 2);

			// tl()�߽������������㣬br()�߽�������������
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 20), 1, LINE_AA);
		}

	}
	return myPoint;
}

vector<vector<int>> findColor(Mat img)
{
	Mat imgHSV,mask;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	// һ����ɫ��Ҫһ��mask��so ������Ҫ����ѭ��
	for (int i = 0; i < myColors.size(); i++)
	{
		// HSV��ɫ�ռ���ɫ���ֵ-���ֵ
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		inRange(imgHSV, lower, upper, mask);
		//imshow(to_string(i), mask);
		Point myPoint = getContours(mask);

		// �жϵ��Ƿ����
		if (myPoint.x != 0 && myPoint.y != 0)
		{
			newPoints.push_back({ myPoint.x, myPoint.y, i });	// i��ʾ��ɫ
		}

	}

	return newPoints;
}

void drawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> myColorValues)
{
	for (int i = 0; i < newPoints.size(); i++)
	{
		circle(img, Point(newPoints[i][0], newPoints[i][1]), 20, myColorValues[newPoints[i][2]], FILLED, LINE_AA);
	}
}

int main() {
	system("color F9");
	VideoCapture cap(0);

	if (!cap.isOpened())
	{
		cout << "����ͷû��" << endl;
		return -1;
	}

	while (true)
	{
		cap.read(img);
		// ������ɫ������ͼ����������ɫ
		findColor(img);
		drawOnCanvas(newPoints, myColorValues);

		// ��Ƶ��ת
		Mat imgFlip;
		flip(img, imgFlip, 1);
		

		imshow("Image", imgFlip);

		
		int c = waitKey(10);
		if (c == 27)
		{
			break;
		}
		else if (c == '6')
		{
			break;
		}
	}
	destroyAllWindows();
	cap.release();
	return 0;
}