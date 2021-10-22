#include "../include/MaskDetect.h"
#include <iostream>

int main(int argc, char **argv)
{
	std::string fileName("../assets/arek_clean_semi.jpg");
	if (argc > 1)
	{
		fileName = argv[1];
	}

	cv::Mat image = cv::imread(fileName, cv::IMREAD_COLOR);

	MaskDetect md(image);

	cv::Mat imgToFindFace = md.DetectFace();

	cv::imshow("Detected Face", imgToFindFace);

	cv::waitKey(0);

	return 0;
}