#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap;
	cap.open(0);

	double scale = 0.6;

	while (1)
	{
		Mat frame;
		Mat detectMatX, detectMatXAbs;
		Mat detectMatY, detectMatYAbs;
		Mat dstImage;

		cap >> frame;
		Size ResImgSiz = Size(frame.cols*scale, frame.rows*scale);
		Size CoreSiz = Size(3, 3);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);
		Mat GrayFrame;

		//cvtColor(rFrame, GrayFrame,CV_RGB2GRAY);
		Sobel(rFrame, detectMatX, CV_16SC1, 1, 0, 3);
		convertScaleAbs(detectMatX, detectMatXAbs);
		Sobel(rFrame, detectMatY, CV_16SC1, 0, 1, 3);
		convertScaleAbs(detectMatY, detectMatYAbs);

		addWeighted(detectMatXAbs, 0.5, detectMatYAbs, 0.5, 0, dstImage);

		imshow("detectMatX", detectMatX);
		imshow("detectMatY", detectMatY);
		imshow("dstImage", dstImage);
		imshow("frame", rFrame);

		waitKey(30);
	}
}