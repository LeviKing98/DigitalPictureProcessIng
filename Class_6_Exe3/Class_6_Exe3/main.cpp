#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap;
	cap.open(0);

	double scale = 0.5;

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
		Mat detectMatX;

		cap >> frame;
		Size ResImgSiz = Size(frame.cols*scale, frame.rows*scale);
		Size CoreSiz = Size(3, 3);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);

		//cvtColor(rFrame,hsvMat, COLOR_BGR2HSV);

		//rFrame.copyTo(detectMat);

		//cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

		GaussianBlur(rFrame, detectMatX, CoreSiz,1,1);

		imshow("while:in the range", detectMatX);
		imshow("frame", rFrame);

		waitKey(30);
	}
}