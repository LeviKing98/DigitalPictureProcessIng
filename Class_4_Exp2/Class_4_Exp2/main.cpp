#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat result_1, result_2;
	Mat srcMat = imread("G:\\jlw\\timg.jpg", 0);
	threshold(srcMat, result_1,100,255,THRESH_BINARY);
	adaptiveThreshold(srcMat, result_2, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 15, 10);
	imshow("src", srcMat);
	imshow("res_1", result_1);
	imshow("res_2", result_2);
	waitKey(0);
}
