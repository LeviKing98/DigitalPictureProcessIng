#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("G://jlw//metal-part-distorted-03.png", 0);
	Mat canny;
	Canny(srcMat, canny, 120, 150);

	vector<Vec2f> lines;
	HoughLines(canny, lines, 1, CV_PI / 180,100);

	Mat lineMat;
	HoughLines(canny, lineMat, 1, CV_PI / 180,100);
	
	vector<Vec2f>::iterator it = lines.begin();
	for (; it != lines.end(); ++it) {
		float rho = (*it)[0], theta = (*it)[1];
		Point pt1, pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a*rho;
		double y0 = b*rho;
		pt1.x = saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = saturate_cast<int>(y0 + 1000 * (a));
		pt2.x = saturate_cast<int>(x0 - 1000 * (-b));
		pt2.y = saturate_cast<int>(y0 - 1000 * (a));
		line(srcMat, pt1, pt2, Scalar(0, 0, 255), 1, CV_AA);
	}
	imshow("canny", canny);
	imshow("srcMat", srcMat);
	waitKey(0);
}