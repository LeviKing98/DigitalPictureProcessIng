#include <opencv.hpp>
using namespace cv;

int main()
{
	cv::Mat dispMat;
	cv::Point pt1, pt2;
	line(dispMat, pt1, pt2, CV_RGB(255, 0, 0), 1, 8, 0);

	cv::Rect rect;
	rect.x = 10;
	rect.y = 10;
	rect.width=640;
	rect.height=320;
	rectangle(dispMat, rect, CV_RGB(255, 0, 0), 1, 8, 0);

	waitKey(0);
}