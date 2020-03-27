#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap;
	cap.open(0);

	double scale = 0.6;

	/*double i_minH = 0;
	double i_maxH = 20;

	double i_minS = 43;
	double i_maxS = 255;

	double i_minV = 55;
	double i_maxV = 255;*/

	while (1)
	{
		Mat frame;
		//Mat hsvMat;
		Mat detectMatX, detectMatXAbs;
		Mat detectMatY, detectMatYAbs;
		Mat dstImage;

		cap >> frame;
		Size ResImgSiz = Size(frame.cols*scale, frame.rows*scale);
		Size CoreSiz = Size(3, 3);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);

		//cvtColor(rFrame,hsvMat, COLOR_BGR2HSV);

		//rFrame.copyTo(detectMat);

		//cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

		Sobel(rFrame, detectMatX, CV_16SC1, 1, 0, 3);
		convertScaleAbs(detectMatX, detectMatXAbs);
		Sobel(rFrame, detectMatY, CV_16SC1, 0, 1, 3);
		convertScaleAbs(detectMatY, detectMatYAbs);

		addWeighted(detectMatXAbs,0.5, detectMatYAbs,0.5,0, dstImage);

		imshow("detectMatX", detectMatX);
		imshow("detectMatY", detectMatY);
		imshow("dstImage", dstImage);
		imshow("frame", rFrame);

		waitKey(30);
	}
}