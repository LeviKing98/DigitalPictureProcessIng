#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

float myfabs(float a, float b);
void catchFire(Mat frtMat);

int main()
{
	VideoCapture cap;
	cap.open("K:\\Ñ§Ï°\\ÊýÍ¼\\IMG_0589.TRIM.mp4");
	Mat frame;
	while (1)
	{
		cap >> frame;
		if (frame.empty()) break;
		catchFire(frame);
		imshow("Exameple", frame);
		if (waitKey(33) >= 0) break;
	}
}

void catchFire(Mat frtMat)
{
	Mat srcMat;
	Mat hsvMat;
	Mat detectMat;
	Mat fliterMat;
	Mat dilaMat;

	double i_minH = 0;
	double i_maxH = 30;

	double i_minS = 100;
	double i_maxS = 200;

	double i_minV = 180;
	double i_maxV = 255;

	frtMat.copyTo(srcMat);

	cvtColor(srcMat, hsvMat, COLOR_BGR2HSV);

	srcMat.copyTo(detectMat);

	cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

	medianBlur(detectMat, fliterMat,5);

	Mat Core = getStructuringElement(MORPH_ELLIPSE, Size(7, 7));
	dilate(fliterMat, dilaMat, Core);

	Mat lableMat;
	Mat statsMat;
	Mat centerMat;

	int nComp = cv::connectedComponentsWithStats(fliterMat,
		lableMat,
		statsMat,
		centerMat,
		8,
		CV_32S);

	for (int i = 1; i < nComp; i++)
	{
		Rect bndbox;
		bndbox.x = statsMat.at<int>(i, 0);
		bndbox.y = statsMat.at<int>(i, 1);
		bndbox.width = statsMat.at<int>(i, 2);
		bndbox.height = statsMat.at<int>(i, 3);
		//rectangle(fliterMat, bndbox, CV_RGB(255, 255, 255), 1, 8, 0);
	}

	imshow("dilaMat", dilaMat);
	imshow("hsvMat", hsvMat);
	imshow("detectMat", detectMat);
	imshow("fliterMat", fliterMat);
	imshow("frtMat", frtMat);
}

float myfabs(float a, float b)
{
	if (a > b)
		return a - b;
	else
		return b - a;
}
