#include "Resources.h"
#include "FaceDetection.h"
#include "EyesDetection.h"
#include "MaskDetection.h"
#include "MaskColor.h"
#include "Painter.h"
#include <iostream>
#include <string>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char **argv)
{
	if (argc < 2 || std::strcmp(argv[1], "image") == 0)
	{

		std::string fileName("C:/Users/Adrian/source/repos/maseczeki-pk/assets/easy/arek_clean_off.jpg");
	
		MaskColor mask;


		Mat frame;
		VideoCapture cap;
		MaskDetection maskDetection;
		cap.open(0);

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
			Rect face, eyePair, mouth;

			MaskOn result = maskDetection.detect(frame, face, eyePair, mouth);

			Painter::paintFaceCharacteristics(frame, face, eyePair, mouth, result);

			MaskColor color;
			int colorValue = color.detect(frame);
			std::string col = std::to_string(colorValue);
			if (result == MaskOn::CORRECT)
			{
				Painter::paintText(frame, col, Scalar(0, 255, 0));
			}
			else if (result == MaskOn::NONE)
			{
				Painter::paintText(frame, col, Scalar(0, 0, 255));
			}

			imshow("Live", frame);
			if (waitKey(5) >= 0)
				break;
		}
	}

	/*	try
		{
			cv::Mat image = cv::imread(fileName, cv::IMREAD_COLOR);
			MaskDetection maskDetection;
			Rect face, eyePair, mouth;

			MaskOn result = maskDetection.detect(image, face, eyePair, mouth);

			Painter::paintFaceCharacteristics(image, face, eyePair, mouth, result);

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
			Rect face, eyePair, mouth;

			MaskOn result = maskDetection.detect(frame, face, eyePair, mouth);

			Painter::paintFaceCharacteristics(frame, face, eyePair, mouth, result);

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
	*/
	return 0;
}