#include <opencv.hpp>
using namespace cv;

int main()
{
	float Pix[256];
	cv::Mat srcMat = imread("G:\\jlw\\timg.jpg");
	int height = srcMat.rows;
	int width = srcMat.cols;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			uchar average = (srcMat.at<Vec3b>(j, i)[0]
				+ srcMat.at<Vec3b>(j, i)[1]
				+ srcMat.at<Vec3b>(j, i)[2]) / 3;
			Pix[average]++;
		}
	}
	for (int i = 0; i < 256; i++)
	{
		Pix[i]= Pix[i]/(height*width);
	}
	waitKey(0);
}
