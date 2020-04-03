#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap;
	cap.open(0);

	double scale = 0.5;

	double i_minH = 0;
	double i_maxH = 20;

	double i_minS = 43;
	double i_maxS = 255;

	double i_minV = 43;
	double i_maxV = 255;

	while (1)
	{
		Mat frame;
		Mat hsvMat;
		Mat detectMat;
		Mat MedMat;
		Mat resMat;
		cap >> frame;
		Size ResImgSiz = Size(frame.cols*scale, frame.rows*scale);
		Size CoreSiz = Size(7, 7);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);

		cvtColor(rFrame,hsvMat, COLOR_BGR2HSV);

		rFrame.copyTo(detectMat);

		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);
		
		//GaussianBlur(rFrame, MedMat, CoreSiz, 50, 50);
		blur(rFrame, MedMat, CoreSiz);

		rFrame.copyTo(resMat);

		MedMat.copyTo(resMat, detectMat);

		imshow("detectMat", detectMat);

		imshow("resMat", resMat);
		
		imshow("frame", rFrame);

		waitKey(30);
	}
}
