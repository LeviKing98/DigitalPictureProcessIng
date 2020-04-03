#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{

	while (1)
	{
		Mat frame = imread("G:\\jlw\\timg.jpg",1);
		Mat frame_gray = imread("G:\\jlw\\timg.jpg", 0);

		Mat detectMatX, detectMatXAbs;
		Mat detectMatY, detectMatYAbs;
		Mat dstImage_1, dstImage_2;

		Sobel(frame, detectMatX, CV_16SC1, 1, 0, 3);
		convertScaleAbs(detectMatX, detectMatXAbs);
		Sobel(frame, detectMatY, CV_16SC1, 0, 1, 3);
		convertScaleAbs(detectMatY, detectMatYAbs);

		Canny(detectMatX,
			detectMatY,
			dstImage_1,
			120, 150);

		Canny(frame_gray, dstImage_2, 120, 150);
		//addWeighted(detectMatXAbs, 0.5, detectMatYAbs, 0.5, 0, dstImage);

		imshow("detectMatX", detectMatXAbs);
		imshow("detectMatY", detectMatYAbs);
		imshow("dstImage1", dstImage_1);
		imshow("dstImage2", dstImage_2);

		waitKey(30);
	}
}