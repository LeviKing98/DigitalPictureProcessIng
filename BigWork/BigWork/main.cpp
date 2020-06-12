#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void catchFire(Mat frtMat, Mat& outMat, int& fireX, int& fireY);
bool polynomial_curve_fit(std::vector<cv::Point>& key_point, int n, cv::Mat& A);
void findWaterPoint(Mat& binMat, std::vector<cv::Point>& key_point);
void fitWater(Mat frtMat, Mat& outMat, int fireX, int fireY);
double myfabs(double a, double b);

int main()
{
	VideoCapture cap;
	cap.open("K:\\学习\\数图\\IMG_0589.TRIM.mp4");
	Mat frame;
	Mat firebin;
	Mat resMat;
	int fireX,  fireY;
	while (1)
	{
		cap >> frame;
		if (frame.empty()) break;
		frame.copyTo(resMat);
		catchFire(frame, resMat, fireX, fireY);
		fitWater(frame, resMat, fireX, fireY);
		imshow("resMat", resMat);
		if (waitKey(33) >= 0) break;
	}
}
void catchFire(Mat frtMat,Mat& outMat,int& fireX,int& fireY)
{
	Mat srcMat;
	Mat hsvMat;
	Mat detectMat;
	Mat fliterMat;
	Mat dilaMat;

	double i_minH = 0;
	double i_maxH = 30;

	double i_minS = 100;
	double i_maxS = 220;

	double i_minV = 180;
	double i_maxV = 255;

	frtMat.copyTo(srcMat);

	cvtColor(srcMat, hsvMat, COLOR_BGR2HSV);

	srcMat.copyTo(detectMat);

	cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

	medianBlur(detectMat, fliterMat,7);

	Mat Core = getStructuringElement(MORPH_ELLIPSE, Size(17, 17));
	dilate(fliterMat, dilaMat, Core);

	Mat lableMat;
	Mat statsMat;
	Mat centerMat;

	int nComp = cv::connectedComponentsWithStats(dilaMat,
		lableMat,
		statsMat,
		centerMat,
		8,
		CV_32S);

	for (int i = 1; i < nComp; i++)
	{
		Rect bndbox;
		bndbox.x = statsMat.at<int>(i, 0);
		bndbox.y = statsMat.at<int>(i, 1);
		bndbox.width = statsMat.at<int>(i, 2);
		bndbox.height = statsMat.at<int>(i, 3);
		fireX = bndbox.x;
		fireY = bndbox.y;
		rectangle(outMat, bndbox, CV_RGB(255, 255, 255), 1, 8, 0);
	}
	imshow("dilaMat", dilaMat);
	//imshow("hsvMat", hsvMat);
	//imshow("detectMat", detectMat);
	//imshow("fliterMat", fliterMat);
	//imshow("frtMat", frtMat);
}
bool polynomial_curve_fit(std::vector<cv::Point>& key_point, int n, cv::Mat& A)
{
	//Number of key points
	int N = key_point.size();

	//构造矩阵X
	cv::Mat X = cv::Mat::zeros(n + 1, n + 1, CV_64FC1);
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			for (int k = 0; k < N; k++)
			{
				X.at<double>(i, j) = X.at<double>(i, j) +
					std::pow(key_point[k].x, i + j);
			}
		}
	}

	//构造矩阵Y
	cv::Mat Y = cv::Mat::zeros(n + 1, 1, CV_64FC1);
	for (int i = 0; i < n + 1; i++)
	{
		for (int k = 0; k < N; k++)
		{
			Y.at<double>(i, 0) = Y.at<double>(i, 0) +
				std::pow(key_point[k].x, i) * key_point[k].y;
		}
	}

	A = cv::Mat::zeros(n + 1, 1, CV_64FC1);
	//求解矩阵A
	cv::solve(X, Y, A, cv::DECOMP_LU);
	return true;
}
void findWaterPoint(Mat& binMat, std::vector<cv::Point>& key_point)
{
	for (int i = 170; i < 430; i++)	//列循环
	{
		for (int j = 30; j < 230; j++)	//行循环
		{
			if (binMat.at<uchar>(j, i) == 255)
			{
				key_point.push_back(cv::Point(i, j));
				//cout << "point " << i << " " << j << endl;
				break;
			}
		}
	}
}
void fitWater(Mat frtMat,  Mat& outMat,int fireX,int fireY)
{
	static int cnt = 0;
	static Mat bgMat;
	Mat frame;
	Mat subMat;
	Mat bny_subMat;
	//Mat waterMat;
	std::vector<cv::Point> points;;
	std::vector<cv::Point> points_fitted;
	cv::Mat A;
	frtMat.copyTo(frame);
	cvtColor(frame, frame, COLOR_BGR2GRAY);
	if (cnt == 0) {
		frame.copyTo(bgMat);
	}
	else {
		absdiff(frame, bgMat, subMat);
		//将已知水龙头的位置左边与上边的差分灰度图的灰度全部置0
		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < subMat.cols; j++)
			{
				subMat.at<uchar>(i, j) = 0;
			}
		}
		for (int i = 0; i < 90; i++)
		{
			for (int j = 320; j < subMat.cols; j++)
			{
				subMat.at<uchar>(i, j) = 0;
			}
		}
		for (int i = 0; i < subMat.rows; i++)	//行循环
		{
			for (int j = 0; j < 180; j++)	//列循环
			{
				subMat.at<uchar>(i, j) = 0;
			}
		}
		for (int i = fireY-30; i < subMat.rows; i++)	//行循环
		{
			for (int j = 0; j < subMat.cols; j++)	//列循环
			{
				subMat.at<uchar>(i, j) = 0;
			}
		}
		threshold(subMat, bny_subMat, 80, 255, CV_THRESH_BINARY);
		//medianBlur(bny_subMat, bny_subMat, 3);
		findWaterPoint(bny_subMat, points);
		polynomial_curve_fit(points, 2, A);
		for (int x = 170; x < 430; x++)
		{
			double y = A.at<double>(0, 0) + A.at<double>(1, 0) * x +
				A.at<double>(2, 0) * std::pow(x, 2) ;

			points_fitted.push_back(cv::Point(x, y));
		}
		polylines(outMat, points_fitted, false, cv::Scalar(0, 255, 255), 1, 8, 0);
		imshow("bny_subMat", bny_subMat);
		//imshow("subMat", subMat);
		//imshow("frame", frame);
	}
	cnt = 1;
}
double myfabs(double a, double b)
{
	if (a > b)
		return a - b;
	else
		return b - a;
}