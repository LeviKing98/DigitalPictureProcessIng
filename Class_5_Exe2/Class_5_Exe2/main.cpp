#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat lableMat;
	Mat statsMat;
	Mat centerMat;
	Mat srcMat = imread("G:\\jlw\\coin.png", 0);
	Mat dstMat;

	threshold(srcMat, dstMat, 100, 255, THRESH_BINARY);

	int nComp=cv::connectedComponentsWithStats(dstMat,
		lableMat,
		statsMat,
		centerMat,
		8,
		CV_32S);

	for (int i = 1; i < nComp; i++)
	{
		cout << "connected Components NO." << i << endl;
		cout << "pixels = " << statsMat.at<int>(i, 4) << endl;
		cout << "width = " << statsMat.at<int>(i, 2) << endl;
		cout << "height = " << statsMat.at<int>(i, 3) << endl;
		cout << endl;
	}

	for (int i = 1; i < nComp; i++)
	{
		Rect bndbox;
		bndbox.x = statsMat.at<int>(i, 0);
		bndbox.y = statsMat.at<int>(i, 1);
		bndbox.width = statsMat.at<int>(i, 2);
		bndbox.height = statsMat.at<int>(i, 3);
		rectangle(dstMat, bndbox, CV_RGB(255, 255, 255), 1, 8, 0);
	}
	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);
}
