#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat dstMat;
	Mat srcMat = imread("G:\\jlw\\timg.jpg", 1);

	if (srcMat.empty()) return -1;

	/*
	const Point2f src_pt[] = {
		Point2f(200,200),
		Point2f(250,200),
		Point2f(200,100)
	};

	const Point2f dst_pt[] = {
		Point2f(300,100),
		Point2f(300,50),
		Point2f(200,100)
	};
    const Mat affine_matrix = getAffineTransform(src_pt, dst_pt);

	warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());*/

	double angle = 90;
	double scale = 1.5;

	Point2f center(srcMat.cols / 2.0, srcMat.rows / 2.0);
	Mat rot = getRotationMatrix2D(center, angle, scale);

	Rect bbox = RotatedRect(center, srcMat.size(), angle).boundingRect();
	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;

	warpAffine(srcMat, dstMat, rot, bbox.size());

	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);
}