#include <opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("‪K:\\学习\\数图\\gtest.jpg", 1);			//原图
	if (srcImage.empty())
	{
		printf("Could not find the image!\n");
		return -1;
	}
	//【转化为灰度图】
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	int row_num = srcImage.rows;
	int col_num = srcImage.cols;
	//进行表的建立
	float gama = 0.3;
	float LUT[256] = { 0 };
	for (int i = 0; i < 256; i++)
	{
		LUT[i] = pow(i * 1.0 / 255, gama);
	}
	for (int i = 0; i < row_num; i++)	//行循环
	{
		for (int j = 0; j < col_num; j++)	//列循环
		{
			srcImage.at<uchar>(i, j) = LUT[srcImage.at<uchar>(i, j)] * 255;
		}
	}

	//【显示结果】
	namedWindow("gama", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
	imshow("gama", srcImage);
	waitKey(0);
	return 0;
}