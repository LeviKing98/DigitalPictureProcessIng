#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

float myfabs(float a, float b);

int main()
{
	Mat srcMat = imread("G:\\jlw\\Picture\\rim.png", 0);
	Mat bnyMat;
	Mat disMat = imread("G:\\jlw\\Picture\\rim.png");
	Size2f lmtSizeMax = { 100,100 };
	Size2f lmtSizeMin = { 30,30 };

	threshold(srcMat, bnyMat, 110, 255, THRESH_BINARY_INV);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(bnyMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++){
		RotatedRect rbox = minAreaRect(contours[i]);
		if (rbox.size.height > lmtSizeMin.height && rbox.size.width > lmtSizeMin.width
			&&rbox.size.height < lmtSizeMax.height && rbox.size.width < lmtSizeMax.width
			&& myfabs(rbox.size.height, rbox.size.width) < 10) {
			drawContours(disMat, contours, i, Scalar(0, 255, 255), 1, 8);
			Point2f vtx[4];
			rbox.points(vtx);
			for (int j = 0; j < 4; j++) {
				line(disMat, vtx[j], vtx[j < 3 ? j + 1 : 0], Scalar(0, 0, 255), 2, CV_AA);
			}
		}
	}

	imshow("bnyMat", bnyMat);
	imshow("disMat", disMat);
	waitKey(0);
}
float myfabs(float a, float b)
{
	if (a > b)
		return a - b;
	else
		return b - a;
}