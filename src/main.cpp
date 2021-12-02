#include "Resources.h"
#include "FaceDetection.h"
#include "EyesDetection.h"
#include "Properties.h"
#include "MaskDetection.h"
#include "MaskColor.h"
#include "Painter.h"
#include "Timer.h"
#include <iostream>
#include <string>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char **argv)
{
	int correctCount = 0;
	int frameCount = 1;
	bool start = false;
	bool isOn = false;
	bool detectionFin = true;
	Mat frame, org;
	VideoCapture cap;
	cap.open(0);

	if (!cap.isOpened())
	{
		std::cerr << "ERROR! Unable to open camera\n";
		return -1;
	}

	Properties props;
	Timer timer = Timer();

	props.calculateProperties(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT));
	MaskDetection maskDetection(props);

	for (;;)
	{
		Mat raw, rawBlurred;

		cap.read(raw);
		GaussianBlur(raw, rawBlurred, Size(1, 1), 0);
		flip(rawBlurred, frame, 1);

		if (frame.empty())
		{
			std::cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		Rect face, eyePair, mouth, nose;

		MaskOn result = maskDetection.detect(frame, face, eyePair, mouth, nose);

		Painter::paintOutline(frame, props);

		Painter::paintFaceCharacteristics(frame, face, eyePair, mouth, nose, result);

		
		if (start) {
			Painter::paintText(frame, "Detection started", Scalar(0, 120, 255));
		}
		else if (detectionFin) {
			Painter::paintText(frame, "Fit face into outline...", Scalar(255, 255, 255));
		}
		else if (isOn && !start)
		{
			Painter::paintText(frame, "Mask detected", Scalar(0, 255, 0));
		}
		else if (!isOn && !start)
		{
			Painter::paintText(frame, "Mask not detected", Scalar(0, 0, 255));
		}
		
		
		if (timer.CheckTimeCounter(3) && !start) {
			detectionFin = true;
		}

		if (start)
		{
			

			if (timer.CheckTimeCounter(5))
			{
				int percent = (correctCount * 100) / frameCount;
				std::cout << percent << "% " << frameCount+correctCount<< std::endl;
				if (percent >= PASS_PRECENTAGE_THRESHOLD && frameCount + correctCount > MINIMAL_FRAME_THRESHOLD)
				{
					isOn = true;
					std::cout << "maska jest zalozona" << std::endl;
				}
				else
				{
					std::cout << "maski nie wykryto" << std::endl;
					isOn = false;
				}
				timer.StartTimeCounter();
				start = false;
				detectionFin = false;
			}
		}

		if (result == MaskOn::CORRECT)
		{
			if (!start && timer.CheckTimeCounter(3))
			{
				
				std::cout << "start wykrywania" << std::endl;
				frameCount = 1;
				correctCount = 0;
				start = true;
				isOn = false;
				timer.StartTimeCounter();
			}
			else
			{
				frameCount++;
				correctCount++;
			}
		}
		else if (result == MaskOn::NONE)
		{
			if (start)
			{
				frameCount++;
			}
			//Painter::paintText(frame, "Mask not detected", Scalar(0, 0, 255));
		}

		imshow("Live", frame);
		if (waitKey(5) >= 0)
			break;
	}

	return 0;
}