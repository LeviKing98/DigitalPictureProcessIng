#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("G://jlw//metal-part-distorted-03.png", 0);
	Mat canny;
	Canny(srcMat, canny, 120, 150);

	vector<Vec4f> lines;
	HoughLinesP(canny, lines, 1, CV_PI / 180,30,8,10);

	Mat lineMat;
	HoughLines(canny, lineMat, 1, CV_PI / 180,100);
	
	vector<Vec4f>::iterator it = lines.begin();
	for (; it != lines.end(); ++it) {
		Point pt1, pt2;
		pt1.x = (*it)[0];
		pt1.y = (*it)[1];
		pt2.x = (*it)[2];
		pt2.y = (*it)[3];
		line(srcMat, pt1, pt2, Scalar(0, 0, 255), 1, CV_AA);
	}
	imshow("canny", canny);
	imshow("srcMat", srcMat);
	waitKey(0);

}