#include <iostream>
#include <opencv2/opencv.hpp>.
using namespace std;
using namespace cv;

int main()
{
	Mat frame;
	Mat bgMat;
	Mat subMat;
	Mat bny_subMat;

	while (1)
	{
		capVideo >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		if (cnt == 0) {
			frame.copyTo(bgMat);
		}
		else {
			absdiff(frame, bgMat, subMat);
			threshold(subMat, bny_subMat, 50, 255, CV_THRESH_BINARY);

			imshow("b_subMat",bny_subMat);
			imshow("subMat", subMat);
			waitKey(30);
		}
	}
}