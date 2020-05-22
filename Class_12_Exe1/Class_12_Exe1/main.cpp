#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	float gamma = 0.45;
	float Excel[256] = { 0 };
	for (int i = 0; i < 256; i++) {
		Excel[i] = pow(i * 1.0 / 255, gamma);
	}
	cv::Mat srcMat = imread("‪D:\\face.jpg", 0);
	cv::Mat srcMat = imread("D:\\face.jpg", 0);
	for (int i = 0; i < srcMat.rows; i++)
	{
		for (int j = 0; j < srcMat.cols; j++)
		{
			srcMat.at<uchar>(i, j) = Excel[srcMat.at<uchar>(i, j)] * 255;
		}
	}

	imshow("srcMat", srcMat);
	waitKey(0);
	return 0;
}
