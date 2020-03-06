#include <opencv.hpp>
using namespace cv;

int main()
{
	cv::Mat dispMat1 = imread("G:\\jlw\\timg.jpg");;
	cv::Point pt1, pt2;
	pt1.x = 10;
	pt1.y = 10;
	pt2.x = 20;
	pt2.y = 20;
	line(dispMat1, pt1, pt2, CV_RGB(255, 0, 0), 1, 8, 0);

	cv::Mat dispMat2 = imread("G:\\jlw\\timg.jpg");;
	cv::Rect rect;
	rect.x = 10;
	rect.y = 10;
	rect.width=640;
	rect.height=320;
	rectangle(dispMat2, rect, CV_RGB(255, 0, 0), 1, 8, 0);

	cv::imshow("1", dispMat1);
	cv::imshow("2", dispMat2);

	waitKey(0);
}