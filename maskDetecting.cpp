#include <opencv2\opencv.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// ��ɫѡ��
void colorPicker(Mat img) {
	Mat imgHSV;
	// ת��Ϊ HSV ɫ�ʿռ�
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	// ����HSV��ɫ�ռ����ʼ��ĩβֵ
	int hmin = 0, smin = 0, vmin = 0;
	int hmax = 179, smax = 255, vmax = 255;

	// ��������
	namedWindow("TrackBar",WINDOW_FREERATIO);
	// ����������������������Ҫ����ɫ��������Ӧ��HSV����ɫֵ
	createTrackbar("Hua Min", "TrackBar", &hmin, 179);
	createTrackbar("Hua Max", "TrackBar", &hmax, 179);
	createTrackbar("Sat Min", "TrackBar", &smin, 255);
	createTrackbar("Sat Max", "TrackBar", &smax, 255);
	createTrackbar("Val Min", "TrackBar", &vmin, 255);
	createTrackbar("Val Max", "TrackBar", &vmax, 255);

	imshow("imgHSV", imgHSV);

	while (true)
	{
		//����������
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);

		// �Բ�����ɫ�����ڵ���mask��Ĥ��
		// ����ͼ�����ɫ��⣬���Խ���������
		Mat mask;
		inRange(imgHSV, lower, upper, mask);
		imshow("mask", mask);
		cout << hmin << "," << smin << "," << vmin << endl;
		cout << hmax << "," << smax << "," << vmax << endl;
		int c = waitKey(2);
		if (c == 27)
		{
			break;
		}
	}
}

// �洢������ɫ
vector<vector<int>> maskColor = {
	{17,0,0,127,11,255},	 // white 
	{0,0,98,179,28,207},	 // gray
	{20,42,163,105,255,255}, // blue
};

// �洢��ɫlabel
vector<string> mask_label = {
	"white","gray","blue"
};

// ����ֵ�Ϳ�����ɫindex
vector<vector<int>> rect_ColorId;

// mask������Ϣ
Rect Maskrect;

// ��ÿ�������
Rect findMaskRect(Mat mask,Mat faceRoi)
{
	// ����������洢����
	vector<vector<Point>> contours;
	// ����������ĵȼ����Ⱥ�
	vector<Vec4i> hierarchy;
	// ��������
	findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	// �洢������������
	vector<Rect> boundRect(contours.size());
	// ������Ϻ�Ķ����������
	vector <vector<Point>> conPloy(contours.size());
	

	// ����ÿ�����������
	for (int i = 0; i < contours.size(); i++)
	{
		int contoursArea = contourArea(contours[i]);
		cout << "Area:" << contoursArea << endl;
		if (contoursArea > 2000)
		{
			// ��ȡ����
			float peri = arcLength(contours[i], true);
			// ����maskͼ�����
			approxPolyDP(contours[i], conPloy[i], peri * 0.02, true);
			// �ҵ�mask����ת��Ϊ����
			boundRect[i] = boundingRect(conPloy[i]);
			Maskrect.x = boundRect[i].x;
			Maskrect.y = boundRect[i].y;
			Maskrect.width = boundRect[i].width;
			Maskrect.height = boundRect[i].height;

			/*rectangle(faceRoi, Rect(boundRect[i].x,boundRect[i].y,boundRect[i].width,boundRect[i].height), 
				Scalar(11,255,66),2, LINE_AA);*/
		}
	}
	return Maskrect;
}

// ���ҿ�����ɫ������ֵindex
vector<vector<int>> findMaskColorIdx(Mat faceRoi, vector<vector<int>> maskColor) {
	
	Mat imgHSV,mask;
	// ת��ΪHSV
	cvtColor(faceRoi, imgHSV, COLOR_BGR2HSV);

	for (int i = 0; i < maskColor.size(); i++)
	{
		// ����HSV��ɫ�ռ��������
		Scalar lower(maskColor[i][0], maskColor[i][1], maskColor[i][2]);
		Scalar upper(maskColor[i][3], maskColor[i][4], maskColor[i][5]);
		// �Կ�����������ڵ���mask��Ĥ��
		inRange(imgHSV, lower, upper, mask);
		/*imshow(to_string(i) + "mask", mask);*/
		int countNums = 0;
		int maxNums = 4600;
		for (int i = 0; i < mask.rows; i++)
		{
			for (int j = 0; j < mask.cols; j++)
			{
				if (mask.ptr<uchar>(i)[j] == 255)
				{
					countNums++;
				}
			}
		}
		
		if (countNums > maxNums)
		{
			/*imshow("mask", mask);*/
			// ��ȡ��������ľ���
			Rect rect = findMaskRect(mask, faceRoi);
			if (!rect.empty())
			{
				rect_ColorId.push_back({ rect.x,rect.y,rect.width,rect.height,i });
			}

		}

		//// ��ȡ��������ľ���
		//vector<Rect> rect = findMaskRect(mask, faceRoi);
		/*if (!rect.empty())
		{
			rect_ColorId.push_back({ rect[i].x,rect[i].y,rect[i].width,rect[i].height,i });
		}*/
	}
	
	return rect_ColorId;
}

// ����
void drawCavans(vector<vector<int>> rect_ColorId,Mat faceRoi){
	for (int i = 0; i < rect_ColorId.size(); i++)
	{
		// ����
		Rect rect(rect_ColorId[i][0], rect_ColorId[i][1], rect_ColorId[i][2], rect_ColorId[i][3]);
		// ���ƾ���
		rectangle(faceRoi, rect, Scalar(255, 0, 255), 2, LINE_AA);
		// ���ƿ�����ɫ
		putText(faceRoi, mask_label[rect_ColorId[i][4]],
			Point(rect_ColorId[i][0]+30, rect_ColorId[i][1] - 20), 
			FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2, LINE_AA);
	}
	imshow("Mask", faceRoi);
}



int main()
{
	system("color F9");
	string path = "Resources/Mask02.webp";
	Mat img = imread(path);
	Mat imgOriginal;
	img.copyTo(imgOriginal);

	if (img.empty())
	{
		cout << "img not find or path not exit" << endl;
		return -1;
	}


	// ģ�͵�·��
	string root_dir = "D:/APP/OpenCV/opencv/sources/samples/dnn/face_detector/";
	// ��ȡģ��
	dnn::Net net = dnn::readNetFromTensorflow(root_dir + "opencv_face_detector_uint8.pb", root_dir + "opencv_face_detector.pbtxt");
	Mat blob = dnn::blobFromImage(img, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false);
	net.setInput(blob);// NCHW��������������ֵ
	Mat probs = net.forward(); // ����Ԥ�⣬��������
	// probs.size[2]:��        probs.size[3]:��
	Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());

	for (int i = 0; i < detectionMat.rows; i++) {
		float confidence = detectionMat.at<float>(i, 2);
		if (confidence > 0.5) {
			//��ȡ�������꣨��3��4��5��6������
			/*
				static_cast<new_type>(expression)��ǿ��ת��
				new_typeΪĿ���������ͣ�expressionΪԭʼ�������ͱ�������ʽ
			*/
			int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * img.cols);
			int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * img.rows);
			int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * img.cols);
			int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * img.rows);
			Rect box(x1, y1, x2 - x1, y2 - y1);
			rectangle(imgOriginal, box, Scalar(188, 125, 0), 3, 8, 0);
			Mat faceRoi = img(box);
			imshow("img", img);
			imshow("face" + to_string(i), faceRoi);
			imshow("original", imgOriginal);
			// ѡ����ɫ����
			/*colorPicker(faceRoi);*/
			
			findMaskColorIdx(faceRoi,maskColor);
			drawCavans(rect_ColorId, faceRoi);
		}
	}

	waitKey(0);
	destroyAllWindows();

	return 0;
}