#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat dstMat;
	Mat srcMat = imread("G:\\jlw\\timg.jpg", 1);

	if (srcMat.empty()) return -1;

	const Point2f pts1[] = {
		Point2f(150,150),
		Point2f(150,300),
		Point2f(350,300),
		Point2f(350,150)
	};

	const Point2f pts2[] = {
		Point2f(200,150),
		Point2f(200,300),
		Point2f(340,270),
		Point2f(340,180)
	};

    Mat perspective_matrix = getPerspectiveTransform(pts1, pts2);

	warpPerspective(srcMat, dstMat, perspective_matrix, srcMat.size());

	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);
}