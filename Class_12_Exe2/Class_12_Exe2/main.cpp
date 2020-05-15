#include <opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("‪K:\\学习\\数图\\etest.jpg",1),dstImage;			//原图
	if (srcImage.empty())
	{
		printf("Could not find the image!\n");
		return -1;
	}
	//首先分到三个通道里面去
	Mat channels[3];
	Mat dst_channels[3];
	//src为要分离的Mat对象  
	split(srcImage, channels);               //利用vector对象分离  

	imshow("B", channels[0]);
	imshow("G", channels[1]);
	imshow("R", channels[2]);
	//对每个通道的图像进行均衡化
	for (int i = 0;i <= 2;i++)
	{
		equalizeHist(channels[i], dst_channels[i]);
	}
	//合并
	 merge(dst_channels,3, dstImage);
	//【显示结果】
	namedWindow("经过直方图均衡化后的图", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
	imshow("经过直方图均衡化后的图", dstImage);
	waitKey(0);
	return 0;
}