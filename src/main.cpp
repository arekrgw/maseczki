#include "Resources.h"
#include "FaceDetection.h"
#include "EyesDetection.h"
#include "MaskDetection.h"
#include "MaskColor.h"
#include "Painter.h"
#include <iostream>
#include <string>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char** argv)
{
	if (argc < 2 || std::strcmp(argv[1], "image") == 0)
	{

		std::string fileName(ASSET_PATH("/arek_clean_full.jpg"));

		try
		{
			cv::Mat image = cv::imread(fileName, cv::IMREAD_COLOR);
			MaskDetection maskDetection;
			Rect face, eyePair, mouth, nose;

			MaskOn result = maskDetection.detect(image, face, eyePair, mouth, nose);

			Painter::paintFaceCharacteristics(image, face, eyePair, mouth, nose, result);

			imshow("Image", image);

			waitKey(0);
		}
		catch (std::exception e)
		{
			std::cout << e.what();
		}
	}

	else if (std::strcmp(argv[1], "camera") == 0)
	{
		Mat frame;
		VideoCapture cap;
		MaskDetection maskDetection;
		cap.open(0);
		std::cout << cap.get(CAP_PROP_FRAME_WIDTH);

		if (!cap.isOpened())
		{
			std::cerr << "ERROR! Unable to open camera\n";
			return -1;
		}

		for (;;)
		{
			cap.read(frame);

			if (frame.empty())
			{
				std::cerr << "ERROR! blank frame grabbed\n";
				break;
			}
			Rect face, eyePair, mouth,nose;

			MaskOn result = maskDetection.detect(frame, face, eyePair, mouth,nose);

			Painter::paintFaceCharacteristics(frame, face, eyePair, mouth, nose, result);

			if (result == MaskOn::CORRECT)
			{
				Painter::paintText(frame, "Mask detected", Scalar(0, 255, 0));
			}
			else if (result == MaskOn::NONE)
			{
				Painter::paintText(frame, "Mask not detected", Scalar(0, 0, 255));
			}

			imshow("Live", frame);
			if (waitKey(5) >= 0)
				break;
		}
	}

	return 0;
}