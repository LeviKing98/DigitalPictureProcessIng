/*#include <opencv.hpp>
#include <iostream>
#define pi 3.14
using namespace cv;
using namespace std;

void SetHist(Mat srcMat, int nX, int nY, float* ref_hist);
float CmpHist(float* ref_hist1, float* ref_hist2, int nX, int nY);

int main()
{
	Mat orgMat = imread("K:\\学习\\数图\\img.png", 0);  //323*241
	Mat srcMat = imread("K:\\学习\\数图\\template.png", 0);  //108*48
    Mat ROIMat;

	int CellSize = 16;
	int nX = srcMat.cols / CellSize;
	int nY = srcMat.rows / CellSize;

	int bins = 8 * nX * nY;
	float* ref_hist1 = new float[bins];
	float* ref_hist2 = new float[bins];

	memset(ref_hist1, 0, sizeof(float) * bins);
	memset(ref_hist2, 0, sizeof(float) * bins);

	float dist1;
	float Mindist = 10000;

	SetHist(srcMat, nX, nY, ref_hist1);

	for (int i = 0; i < 215; i++) {
		for (int j = 0; j < 198; j++) {
			ROIMat = orgMat(Range(0+j, 48+j), Range(0+i, 108+i));
			SetHist(ROIMat, nX, nY, ref_hist2);
			dist1 = CmpHist(ref_hist1, ref_hist2, nX, nY);
			if (Mindist > dist1) {
				dist1 = Mindist;
				cout << "dist1 = " << dist1 << endl;
			}
		}
	}
	
	imshow("原图", orgMat);
	imshow("图1", srcMat);

	delete[] ref_hist1;
	delete[] ref_hist2;
	
	waitKey(0);
}

int QuantAngle(float angle)
{
	return (int)(angle / 45);
}

void SetHist(Mat srcMat, int nX, int nY, float* ref_hist)
{
	Mat gx, gy;
	Mat mag, angle;
	int count = -1;
	Sobel(srcMat, gx, CV_32F, 1, 0, 1);
	Sobel(srcMat, gy, CV_32F, 0, 1, 1);

	cartToPolar(gx, gy, mag, angle, true);

	for (int i = 0; i < nY; i++) {
		for (int j = 0; j < nX; j++) {
			count++;
			for (int m = 0; m < 16; m++) {
				for (int n = 0; n < 16; n++) {
					ref_hist[count * 8 + QuantAngle(angle.at<float>(i * 16 + m, j * 16 + n))] += mag.at<float>(i * 16 + m, j * 16 + n);
				}
			}
		}
	}
}

float CmpHist(float* ref_hist1, float* ref_hist2, int nX, int nY)
{
	float sum = 0;
	for (int i = 0; i < nX * nY; i++) {
		sum += (ref_hist1[i] - ref_hist2[i]) * (ref_hist1[i] - ref_hist2[i]);
	}
	return sqrt(sum);
}
*/
#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

float* Cal_cellHist(Mat src)
{
	//计算角度及梯度
	Mat gx, gy;
	Mat mag, angle;
	Sobel(src, gx, CV_32F, 1, 0, 1);
	Sobel(src, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);

	float hist[8] = { 0 };
	for (int j = 0; j < 16; j++)
	{
		for (int i = 0; i < 16; i++)
		{
			if (angle.at<float>(j, i) >= 0 && angle.at<float>(j, i) < 45)
			{
				hist[0] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) >= 45 && angle.at<float>(j, i) < 90)
			{
				hist[1] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) >= 90 && angle.at<float>(j, i) < 135)
			{
				hist[2] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) >= 135 && angle.at<float>(j, i) < 180)
			{
				hist[3] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) >= 180 && angle.at<float>(j, i) < 225)
			{
				hist[4] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) >= 225 && angle.at<float>(j, i) < 270)
			{
				hist[5] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) >= 270 && angle.at<float>(j, i) < 315)
			{
				hist[6] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) >= 315 && angle.at<float>(j, i) < 360)
			{
				hist[7] += mag.at<float>(j, i);
			}
		}
	}
	return hist;
}


int main()
{
	Mat img1 = imread("K:\\学习\\数图\\template.png", 0);
	Mat srcimg2 = imread("K:\\学习\\数图\\img.png", 0);
	int cellSize = 16;
	int nX = img1.cols / cellSize;
	int nY = img1.rows / cellSize;
	Mat img2 = Mat::zeros(img1.rows, img1.cols, CV_8UC1);
	int num = nX * nY * 8;

	float* srcHist = new float[num];
	memset(srcHist, 0, sizeof(float) * num);

	float* img1Hist = new float[num];
	memset(img1Hist, 0, sizeof(float) * num);

	float* img2Hist = new float[num];
	memset(img2Hist, 0, sizeof(float) * num);

	int cnt1 = 0;
	int cnt2 = 0;
	float distance = 0;
	float distance_min = 10e100;
	int x = 0;
	int y = 0;
	for (int q = 80; q < /*srcimg2.rows- img1.rows*/110; q++) {
		for (int p = 80; p < /*srcimg2.cols - img1.cols*/110; p++) {
			for (int m = 0; m < img1.rows; m++) {
				for (int n = 0; n < img1.cols; n++) {
					img2.at<uchar>(m, n) = srcimg2.at<uchar>(q + m, p + n);
				}
			}
			//img1
			cnt1 = 0;
			for (int j = 0; j < nY; j++)
			{
				for (int i = 0; i < nX; i++)
				{
					Rect rectL(i * cellSize, j * cellSize, cellSize, cellSize);
					Mat nowMat = img1(rectL);
					for (int k = 0; k < 8; k++)
					{
						img1Hist[k + cnt1 * 8] = Cal_cellHist(nowMat)[k];
					}
					cnt1++;
				}
			}
			//img2
			cnt2 = 0;
			for (int j = 0; j < nY; j++)
			{
				for (int i = 0; i < nX; i++)
				{
					Rect rectL(i * cellSize, j * cellSize, cellSize, cellSize);
					Mat nowMat = img2(rectL);
					for (int k = 0; k < 8; k++)
					{
						img2Hist[k + cnt2 * 8] = Cal_cellHist(nowMat)[k];
					}
					cnt2++;
				}
			}
			distance = 0;
			for (int i = 0; i < num; i++)
			{
				distance += (img1Hist[i] - img2Hist[i]) * (img1Hist[i] - img2Hist[i]);
				if (distance < distance_min) {
					distance_min = distance;
					x = q;
					y = p;
				}
			}
		}
	}
	cout << "最小值" << distance_min << endl;
	cout << "x" << x << endl;
	cout << "y" << y << endl;
	Rect rect(y, x, img1.cols, img1.rows);//左上坐标（x,y）和矩形的长(x)宽(y)
	cv::rectangle(srcimg2, rect, Scalar(255, 0, 0), 1, LINE_8, 0);
	imshow("dstMat", srcimg2);
	waitKey(0);
	delete[] img1Hist;
	delete[] img2Hist;
	return 0;

}