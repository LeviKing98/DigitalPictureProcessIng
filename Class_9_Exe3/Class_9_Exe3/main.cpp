#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

float myfabs(float a, float b);

int main()
{
	double scale = 0.2;
	Mat frtMat = imread("G:\\jlw\\Picture\\topic1.jpg");
	Mat srcMat ;
	Mat gryMat ;
	Mat dstMat ;
	
	Size ResImgSiz = Size(frtMat.cols*scale, frtMat.rows*scale);
	srcMat = Mat(ResImgSiz, frtMat.type());
	dstMat = srcMat;
	resize(frtMat, srcMat, ResImgSiz, INTER_LINEAR);
	cvtColor(srcMat, gryMat, COLOR_BGR2GRAY);

	double i_minH = 1;
	double i_maxH = 180;

	double i_minS = 43;
	double i_maxS = 255;

	double i_minV = 43;
	double i_maxV = 255;

	Mat hsvMat;
	Mat detectMat;
	Mat MedMat;
	Mat resMat;

	cvtColor(srcMat, hsvMat, COLOR_BGR2HSV);

	srcMat.copyTo(detectMat);

	cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

	Size2f lmtSizeMax = { 10000,10000 };
	Size2f lmtSizeMin = { 100,100 };

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(detectMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++) {
		RotatedRect rbox = minAreaRect(contours[i]);
		if (rbox.size.height > lmtSizeMin.height && rbox.size.width > lmtSizeMin.width
			&&rbox.size.height < lmtSizeMax.height && rbox.size.width < lmtSizeMax.width
			&& myfabs(rbox.size.height, rbox.size.width) < 1000) {
			drawContours(dstMat, contours, i, Scalar(0, 255, 255), 1, 8);
			Point2f vtx[4];
			rbox.points(vtx);
			for (int j = 0; j < 4; j++) {
				line(dstMat, vtx[j], vtx[j < 3 ? j + 1 : 0], Scalar(0, 0, 255), 2, CV_AA);
			}
		}
	}

	imshow("hsvMat", hsvMat); 
	imshow("srcMat", srcMat);
	imshow("dstMat", dstMat);
	imshow("detectMat", detectMat);
	waitKey(0);
}
float myfabs(float a, float b)
{
	if (a > b)
		return a - b;
	else
		return b - a;
}