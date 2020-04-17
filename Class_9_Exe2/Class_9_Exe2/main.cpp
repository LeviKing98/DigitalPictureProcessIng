#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("G:\\jlw\\Picture\\die_on_chip.png", 0);
	Mat bnyMat;
	Mat disMat = imread("G:\\jlw\\Picture\\die_on_chip.png");
	Size2f lmtSize = { 50,50 };

	threshold(srcMat, bnyMat, 160, 255, THRESH_BINARY);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(bnyMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++) {
		RotatedRect rbox = minAreaRect(contours[i]);
		if (rbox.size.height > lmtSize.height && rbox.size.width > lmtSize.width) {
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