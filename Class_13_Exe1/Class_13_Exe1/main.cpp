#include <iostream>
#include <opencv2/opencv.hpp>.
using namespace std;
using namespace cv;

int main()
{
	VideoCapture capVideo(0);

	//如果视频打开失败
	if (!capVideo.isOpened()) {
		std::cout << "Unable to open video!" << std::endl;
		return -1;
	}

	Mat frame;
	Mat bgMat;
	Mat subMat;
	Mat bny_subMat;
	int cnt=0;
	while (1)
	{
		capVideo >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		imshow("frame", frame);
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
		cnt=1;
	}
}