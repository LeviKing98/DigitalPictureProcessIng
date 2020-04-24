#include <opencv.hpp>
#include <iostream>
#define pi 3.14
using namespace cv;
using namespace std;

void SetHist(Mat srcMat, int nX, int nY, float * ref_hist);
float CmpHist(float * ref_hist1, float * ref_hist2, int nX, int nY);

int main()
{
	Mat orgMat = imread("G:\\jlw\\Picture\\hogTemplate.jpg",0);
	Mat cmpMat1 = imread("G:\\jlw\\Picture\\img1.jpg",0);
	Mat cmpMat2 = imread("G:\\jlw\\Picture\\img2.jpg",0);

	int CellSize = 16;
	int nX = orgMat.cols / CellSize;
	int nY = orgMat.rows / CellSize;

    int bins = 8 * nX*nY;
	float * ref_hist1 = new float[bins];
	float * ref_hist2 = new float[bins];
	float * ref_hist3 = new float[bins];
	
	memset(ref_hist1, 0, sizeof(float)*bins);
	memset(ref_hist2, 0, sizeof(float)*bins);
	memset(ref_hist3, 0, sizeof(float)*bins);

	float dist1;
	float dist2;

	SetHist(orgMat, nX, nY, ref_hist1);
	SetHist(cmpMat1, nX, nY, ref_hist2);
	SetHist(cmpMat2, nX, nY, ref_hist3);

	dist1 = CmpHist(ref_hist1, ref_hist2, nX, nY);
	dist2 = CmpHist(ref_hist1, ref_hist3, nX, nY);
	
	cout << "dist1 = " << dist1 << endl;
	cout << "dist2 = " << dist2 << endl;

	if (dist1 < dist2) {
		cout << "图一与原图更相似 "  << endl;
	}
	else {
		cout << "图二与原图更相似 " << endl;
	}

	imshow("原图",orgMat);
	imshow("图1", cmpMat1);
	imshow("图2", cmpMat2);

	delete[] ref_hist1;
	delete[] ref_hist2;
	delete[] ref_hist3;
	
	waitKey(0);
}

int QuantAngle(float angle)
{
	return (int)(angle /45);
}

void SetHist(Mat srcMat,int nX,int nY,float * ref_hist)
{
	Mat gx, gy;
	Mat mag, angle;
	int count = -1;
	Sobel(srcMat, gx, CV_32F, 1, 0, 1);
	Sobel(srcMat, gy, CV_32F, 0, 1, 1);

	cartToPolar(gx, gy, mag, angle, false);

	for (int i = 0; i < nY; i++) {
		for (int j = 0; j < nX; j++) {
			count++;
			for (int m = 0; m < 16; m++) {
				for (int n = 0; n < 16; n++){
					ref_hist[count*8+ QuantAngle(angle.at<float>(i * 16 + m, j * 16 + n))]+= mag.at<float>(i * 16 + m, j * 16 + n);
				}
			}
		}
	}
}

float CmpHist(float * ref_hist1, float * ref_hist2,int nX,int nY)
{
	float sum = 0;
	for (int i = 0; i < nX*nY; i++) {
		sum += (ref_hist1[i] - ref_hist2[i])*(ref_hist1[i] - ref_hist2[i]);
	}
	return sqrt(sum);
}

