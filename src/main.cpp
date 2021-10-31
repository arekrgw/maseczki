#include "Resources.h"
#include "FaceDetection.h"
#include "EyesDetection.h"
#include <iostream>

int main(int argc, char** argv)
{
	std::cout << ASSETS_PATH;


	if (argc < 2 || std::strcmp(argv[1], "image") == 0)
	{

		std::string fileName(ASSET_PATH("/easy/adrian_clean_semi.jpg"));
		std::cout << fileName;

		try
		{
			cv::Mat image = cv::imread(fileName, cv::IMREAD_COLOR);
			EyesDetection ed;
			cv::Mat imgToFindFace;
			cv::Rect eyes;
			ed.detect(image, eyes);
			std::cout << std::endl<< eyes<<std::endl <<std::endl;

			cv::waitKey(0);
		}
		catch (std::exception e)
		{
			std::cout << e.what();
		}
	}

	// else if (std::strcmp(argv[1], "camera") == 0)
	// {
	// 	Mat frame;
	// 	VideoCapture cap;
	// 	// MaskDetect maskDetect;
	// 	cap.open(0);

	// 	if (!cap.isOpened())
	// 	{
	// 		std::cerr << "ERROR! Unable to open camera\n";
	// 		return -1;
	// 	}

	// 	for (;;)
	// 	{
	// 		cap.read(frame);

	// 		if (frame.empty())
	// 		{
	// 			std::cerr << "ERROR! blank frame grabbed\n";
	// 			break;
	// 		}

	// 		// Mat imgWithFaces = maskDetect.DetectFace(frame);

	// 		// imshow("Live", imgWithFaces);
	// 		if (waitKey(5) >= 0)
	// 			break;
	// 	}

	// 	std::cout << "camera";
	// }

	return 0;
}