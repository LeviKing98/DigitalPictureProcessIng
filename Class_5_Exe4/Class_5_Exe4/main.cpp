#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int myfabs(int a, int b)
{
	if( a > b)
		return a - b;
	else
		return b - a;
}

int main()
{
	Mat lableMat;
	Mat statsMat;
	Mat centerMat;
	Mat resultMat;
	Mat srcMat = imread("G:\\jlw\\clip.png", 0);
	Mat dstMat;
	Mat Core = getStructuringElement(MORPH_ELLIPSE, Size(10, 10));
	int i;
	int count=0;
	//threshold(srcMat, dstMat, 100, 255, THRESH_BINARY);
    threshold(srcMat, dstMat, 100, 255, THRESH_BINARY_INV);
	dilate(dstMat, resultMat, Core);

	int nComp = cv::connectedComponentsWithStats(dstMat,
		lableMat,
		statsMat,
		centerMat,
		8,
		CV_32S);

	for ( i = 1; i < nComp; i++)
	{
		if (statsMat.at<int>(i, 4) > 1000
			&&myfabs(statsMat.at<int>(i, 2), statsMat.at<int>(i, 3))<400)
		{
			count++;
			cout << "connected Components NO." << count << endl;
			cout << "pixels = " << statsMat.at<int>(i, 4) << endl;
			cout << "width = " << statsMat.at<int>(i, 2) << endl;
			cout << "height = " << statsMat.at<int>(i, 3) << endl;
			cout << endl;
		}
	}
	cout << "Final Components Num = TotalNum/2-1=" << i/2-1 << endl;

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
	imshow("result", resultMat);
	waitKey(0);
}