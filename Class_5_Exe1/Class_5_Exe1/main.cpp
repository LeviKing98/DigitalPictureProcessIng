#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat result_1, result_2, result_3, result_4;
	Mat srcMat = imread("G:\\jlw\\coin.png", 0);
	Mat dstMat ;
	Mat Core = getStructuringElement(MORPH_RECT,Size(3,3));
	threshold(srcMat, dstMat, 100, 255, THRESH_BINARY);
	erode(dstMat, result_1, Core);
	dilate(dstMat, result_2, Core);
	morphologyEx(dstMat, result_3, MORPH_OPEN,Core);
	morphologyEx(dstMat, result_4, MORPH_CLOSE, Core);
	
	//adaptiveThreshold(srcMat, result_2, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 15, 10);
	imshow("src", srcMat);
    imshow("res_1", result_1);
	imshow("res_2", result_2);
	imshow("res_3", result_3);
	imshow("res_4", result_4);
	waitKey(0);
}
