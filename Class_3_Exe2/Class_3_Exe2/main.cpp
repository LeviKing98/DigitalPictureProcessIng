#include <opencv.hpp>
using namespace cv;

int main()
{
	VideoCapture cap;
	cap.open(0);

	double fps = cap.get(CAP_PROP_FPS);
	std::cout << "fps" << std::endl;
	while (1)
	{
		cv::Mat frame;
		bool rSucess = cap.read(frame);
		cv::imshow("frame", frame);
		waitKey(30);
	}
}