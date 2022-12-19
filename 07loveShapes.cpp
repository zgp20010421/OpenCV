#include <opencv2\opencv.hpp>
#include <iostream>
#include <cmath>


using namespace std;
using namespace cv;

// дһ���ж�������Ƿ��ڰ��ĵ�����
bool check(double x, double y)
{
	//pow(x * x + y * y + 1, 3.0) + x * x * y * y * y < 0
	//����ǰ������߹�ʽ
	return pow(x * x + y * y - 1, 3.0) + x * x *x * y * y < 0;
}

// ����BGR ͨ������

const int M = 600, N = 600;
double B[M][N], G[M][N], R[M][N];


int main()
{
	system("color F9");
	// ��BGR��ͨ���ľ�����и�ֵ
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			// ������ڰ��������ȡֵ��Χ
			// {[-1.5,1.5],[-1.5,1.5]}
			if (check((double)i/M*3-1.5,(double)j/N*3-1.5))
			{
				B[i][j] = abs(50 -i/6);
				G[i][j] = abs(56 -i/6);
				R[i][j] = abs(255-i/6-j/6);
			}
			else
			{
				// ���ڰ��������ڸ�ֵΪ��ɫ
				B[i][j] = G[i][j] = R[i][j] = 255;
			}
		}
	}

	// �����������ͣ��Ծ������ͽ�����ɫֵ�ĸ�ֵ
	Mat Love = Mat(M, N, CV_8UC3);
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Love.ptr<uchar>(i)[j * 3] = B[i][j];
			Love.ptr<uchar>(i)[j * 3 + 1] = G[i][j];
			Love.ptr<uchar>(i)[j * 3 + 2] = R[i][j];
		}
	}
	imshow("Love", Love);

	string savePath = "love.jpg";
	imwrite(savePath, Love);
	waitKey(0);
	destroyAllWindows();

	return 0;
}
