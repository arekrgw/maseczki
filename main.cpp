#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

int main(int argc, char **argv)
{
	std::string fileName("testImage.jpg");

	if (argc > 1)
	{
		fileName = argv[1];
	}

	cv::Mat image = cv::imread(fileName, cv::IMREAD_COLOR);

	if (image.empty())
	{
		std::cout << "Could not find or open the image." << std::endl;
		exit(-1);
	}
	cv::Mat grayscale;
	cv::Mat equalized;
	cv::cvtColor(image, grayscale, cv::COLOR_BGR2GRAY);
	cv::equalizeHist(grayscale, equalized);
	cv::imshow("Grayscale img", grayscale);
	cv::waitKey(0);
	cv::imshow("equalized image", equalized);
	cv::waitKey(0);

	return 0;
}