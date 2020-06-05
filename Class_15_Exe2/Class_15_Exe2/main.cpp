#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int createMaskByKmeans(cv::Mat src, cv::Mat& mask);
void segColor();
VideoCapture createInput(bool useCamera, std::string videoPath);

VideoCapture createInput(bool useCamera, std::string videoPath)
{
	VideoCapture capVideo;
	if (useCamera) {
		capVideo.open(0);
	}
	else {
		capVideo.open(videoPath);
	}
	return capVideo;
}

void segColor(Mat src)
{
	//Mat src = imread("K:\\ѧϰ\\��ͼ\\����.jpg");
	Mat mask = Mat::zeros(src.size(), CV_8UC1);
	createMaskByKmeans(src, mask);
}

int createMaskByKmeans(cv::Mat src, cv::Mat& mask)
{
	if ((mask.type() != CV_8UC1)
		|| (src.size() != mask.size())
		) {
		return 0;
	}

	int width = src.cols;
	int height = src.rows;

	int pixNum = width * height;
	int clusterCount = 2;
	Mat labels;
	Mat centers;

	//����kmeans�õ�����
	Mat sampleData = src.reshape(3, pixNum);
	Mat km_data;
	sampleData.convertTo(km_data, CV_32F);

	//ִ��kmeans
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
	kmeans(km_data, clusterCount, labels, criteria, clusterCount, KMEANS_PP_CENTERS, centers);

	//����mask
	uchar fg[2] = { 0,255 };
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			mask.at<uchar>(row, col) = fg[labels.at<int>(row * width + col)];
		}
	}
	if (mask.at<uchar>(0, 0) == 255)
	{
		mask = 255 - mask;
	}
	return 0;
}

int main()
{
	Mat srcframe;
	Mat dstframe;
	Mat ROIMat;
	VideoCapture srcCap;
	srcCap.open("K:\\ѧϰ\\��ͼ\\��Ļ����̹����Ƶ�ز�.mp4");

	VideoCapture dstCap;
	dstCap.open("K:\\ѧϰ\\��ͼ\\VID_20200602_221135.mp4");
	while (1)
	{
		srcCap >> srcframe;
		if (srcframe.empty())
			break;
		dstCap >> dstframe;
		if (dstframe.empty())
			break;
		resize(dstframe, dstframe, srcframe.size());
		ROIMat = Mat::zeros(srcframe.size(), CV_8UC1);
		createMaskByKmeans(srcframe, ROIMat);

		srcframe.copyTo(dstframe, ROIMat);

		imshow("srcframe", srcframe);
		imshow("dstframe", dstframe);
		imshow("ROIMat", ROIMat);
		
		if (waitKey(33) >= 0) 
			break;
	}
}