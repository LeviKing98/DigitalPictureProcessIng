#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat srcMat = imread("G:\\jlw\\lena_rot.jpg");
	cv::Mat cortMat = imread("G:\\jlw\\lena.jpg",0);
	Mat dstMat;

	Point2f left_1 = { 0,0};
	Point2f left_2 = { 0,0};

	Point2f right_1 = { 0,0 };
	Point2f right_2 = { 0,0 };

	int height = srcMat.rows;
	int width = srcMat.cols;

	std::cout << height << endl;
	std::cout << width << endl;

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			float sum = (srcMat.at<Vec3b>(j, i)[0]
				+ srcMat.at<Vec3b>(j, i)[1]
				+ srcMat.at<Vec3b>(j, i)[2]);
			if (j == 0 && sum < 750)
			{
				left_1.y = j;
				left_1.x = i;
			}
			if (i == width - 1 && sum < 750)
			{
				left_2.y = j;
				left_2.x = i;
			}
			if (i == 0 && sum < 750)
			{
				right_1.y = j;
				right_1.x = i;
			}
			if (j == height-1 && sum < 750)
			{
				right_2.y = j;
				right_2.x = i;
			}
		}
	}

	const Point2f pts1[] = {
		left_1,
		left_2,
		right_1,
		right_2
	};

	const Point2f pts2[] = {
		Point2f(0,0),
		Point2f(512,0),
		Point2f(0,512),
		Point2f(512,512)
	};

	Mat perspective_matrix = getPerspectiveTransform(pts1, pts2);

	warpPerspective(srcMat, dstMat, perspective_matrix, srcMat.size());

	imshow("src", srcMat);
	imshow("cortMat", cortMat);
	imshow("dst", dstMat);
	waitKey(0);
}
