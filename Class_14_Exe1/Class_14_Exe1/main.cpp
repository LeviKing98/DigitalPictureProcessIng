#include <opencv.hpp>
#include <iostream>
#define pi 3.14
using namespace cv;
using namespace std;

void SetHist(Mat srcMat, int nX, int nY, float* ref_hist);
float CmpHist(float* ref_hist1, float* ref_hist2, int nX, int nY);

int main()
{
	Mat orgMat = imread("K:\\学习\\数图\\img.png", 0); //241*323
	Mat srcMat = imread("K:\\学习\\数图\\template.png", 0); //48*108
	Mat ROIMat;

	Rect rect;
	
	int CellSize = 16;
	int nX = srcMat.cols / CellSize;
	int nY = srcMat.rows / CellSize;

	int bins = 8 * nX * nY;
	float* ref_hist1 = new float[bins];
	float* ref_hist2 = new float[bins];

	memset(ref_hist1, 0, sizeof(float) * bins);
	memset(ref_hist2, 0, sizeof(float) * bins);

	SetHist(srcMat, nX, nY, ref_hist2);

	float dist;
	float MinDist = 10000;
	int tgt_x = 0;
	int tgt_y = 0;
	
	for (int i=0; i < orgMat.cols- srcMat.cols; i++) {
		for (int j=0; j < orgMat.rows-srcMat.rows; j++) {
			rect = Rect(i, j, 108, 48);
			ROIMat = orgMat(rect);
			SetHist(ROIMat, nX, nY, ref_hist1);
			dist = CmpHist(ref_hist1, ref_hist2, nX, nY);
			if (dist < MinDist) {
				MinDist = dist;
				tgt_x = i;
				tgt_y = j;
				cout << "i = " << i << endl;
				cout << "j = " << j << endl;
				cout << "dist = " << dist << endl;
			}
		}
	}

	rect = Rect(tgt_x, tgt_y, 108, 48);
	rectangle(orgMat, rect, Scalar(255, 0, 0), 1, LINE_8, 0);

	imshow("原图", orgMat);

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
	//直方图清零
	for (int i = 0; i < 8 * nY * nX; i++)
		ref_hist[i] = 0;
	//直方图计算
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

